#include "PngLoader.h"

#include "pnginfo.h"

using namespace std;
#define PNG_BYTES_TO_CHECK 4
FPngLoader::FPngLoader()
{

}

bool FPngLoader::LoadFile(std::string FileName)
{
	FILE *fp = nullptr;
	errno_t err;
	err = fopen_s(&fp, FileName.c_str(), "rb");
	if (!fp)
	{
		cout << "Cant open file" << FileName.c_str() << endl;
		return false;
	}
	
	if (!IsPNG(fp))
	{
		cout << "File" << FileName.c_str() <<"is not a valid png file"<< endl;
		return false;
	}

	m_png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (m_png_ptr == NULL)
	{
		cout << "Cant create png_ptr" << FileName.c_str() << endl;
		fclose(fp);
		return false;
	}

	m_info_ptr = png_create_info_struct(m_png_ptr);
	if (m_info_ptr == NULL)
	{
		cout << "Cant create info_ptr" << FileName.c_str() << endl;
		fclose(fp);
		return false;
	}

	//设置失败跳转点，这里是标准libpng c式写法，
	//可以参考引擎写法在png_create_read_struct设置自己的错误处理函数，如果在那里设置了，这里就可以不用setjmp了
	if (setjmp(png_jmpbuf(m_png_ptr)))
	{
		png_destroy_read_struct(&m_png_ptr,&m_info_ptr, NULL);
		fclose(fp);
		return false;
	}

	
	ReadPNGToBuffer(fp);
	
	png_destroy_read_struct(&m_png_ptr, &m_info_ptr, 0);

	fclose(fp);

	return true;

}

//根据libpng中的example.c给出的例子，检查是否是合法的png格式文件
bool FPngLoader::IsPNG(FILE *fp)
{
	char buf[PNG_BYTES_TO_CHECK];

	//读取png标记位
	if (fread(buf, 1, PNG_BYTES_TO_CHECK, fp) != PNG_BYTES_TO_CHECK)
		return false;

	return (!png_sig_cmp(reinterpret_cast<png_const_bytep>(buf), (png_size_t)0, PNG_BYTES_TO_CHECK));

}

void FPngLoader::ReadPNGToBuffer(FILE *fp)
{
	rewind(fp);
	//读取流的方式
	png_init_io(m_png_ptr, fp);

	//直接整个读取图片,PNG_TRANSFORM_EXPAND有如下处理
	//扩展Paletted 颜色到true RGB三元组
	//扩展灰度图到full 8 bits ,从1,2,4bits/pixel
	//扩展Paletted或者RGB图片与alpha通道到RGBA格式
	png_read_png(m_png_ptr, m_info_ptr, PNG_TRANSFORM_EXPAND, 0);

	m_Width		= m_info_ptr->width;
	m_Height	= m_info_ptr->height;
	m_ColorType = m_info_ptr->color_type;
	m_BitDepth = m_info_ptr->pixel_depth;
	png_bytep *row_pointers = png_get_rows(m_png_ptr, m_info_ptr);
	int pos = 0;

	//对RGBA图的处理
	if (m_ColorType == PNG_COLOR_TYPE_RGBA)
	{
		m_RGBA = new unsigned char[m_Width * m_Height * 4];
		memset(m_RGBA, 0, m_Width * m_Height * 4);
		for (int i = 0; i < m_Height; i++)
		{
			for (int j = 0; j < m_Width * 4; j += 4)
			{
				m_RGBA[pos++] = row_pointers[i][j];//R
				m_RGBA[pos++] = row_pointers[i][j + 1];//G
				m_RGBA[pos++] = row_pointers[i][j + 2];//B
				m_RGBA[pos++] = row_pointers[i][j + 3];//A
			}
		}
	}

	

	//png_read_png()
	//png_get_rowbytes(m_png_ptr, m_info_ptr);

//	png_read_info(m_png_ptr, m_info_ptr);

	//png_get_IHDR(m_png_ptr, m_info_ptr, &m_Width, &m_Height, &m_BitDepth, &m_ColorType, nullptr, nullptr);

}

unsigned char* FPngLoader::GetImageBuffer()
{
	return m_RGBA;
}


