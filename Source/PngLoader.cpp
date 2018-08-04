//#include "PngLoader.h"
//
//#include "pnginfo.h"
//
//using namespace std;
//#define PNG_BYTES_TO_CHECK 4
//FPngLoader::FPngLoader()
//{
//
//}
//
//bool FPngLoader::LoadFile(std::string FileName)
//{
//	FILE *fp = nullptr;
//	errno_t err;
//	err = fopen_s(&fp, FileName.c_str(), "rb");
//	if (!fp)
//	{
//		cout << "Cant open file" << FileName.c_str() << endl;
//		return false;
//	}
//	
//	if (!IsPNG(fp))
//	{
//		cout << "File" << FileName.c_str() <<"is not a valid png file"<< endl;
//		return false;
//	}
//
//	m_png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
//	if (m_png_ptr == NULL)
//	{
//		cout << "Cant create png_ptr" << FileName.c_str() << endl;
//		fclose(fp);
//		return false;
//	}
//
//	m_info_ptr = png_create_info_struct(m_png_ptr);
//	if (m_info_ptr == NULL)
//	{
//		cout << "Cant create info_ptr" << FileName.c_str() << endl;
//		fclose(fp);
//		return false;
//	}
//
//	//����ʧ����ת�㣬�����Ǳ�׼libpng cʽд����
//	//���Բο�����д����png_create_read_struct�����Լ��Ĵ������������������������ˣ�����Ϳ��Բ���setjmp��
//	if (setjmp(png_jmpbuf(m_png_ptr)))
//	{
//		png_destroy_read_struct(&m_png_ptr,&m_info_ptr, NULL);
//		fclose(fp);
//		return false;
//	}
//
//	
//	ReadPNGToBuffer(fp);
//	
//	png_destroy_read_struct(&m_png_ptr, &m_info_ptr, 0);
//
//	fclose(fp);
//
//	return true;
//
//}
//
////����libpng�е�example.c���������ӣ�����Ƿ��ǺϷ���png��ʽ�ļ�
//bool FPngLoader::IsPNG(FILE *fp)
//{
//	char buf[PNG_BYTES_TO_CHECK];
//
//	//��ȡpng���λ
//	if (fread(buf, 1, PNG_BYTES_TO_CHECK, fp) != PNG_BYTES_TO_CHECK)
//		return false;
//
//	return (!png_sig_cmp(reinterpret_cast<png_const_bytep>(buf), (png_size_t)0, PNG_BYTES_TO_CHECK));
//
//}
//
//void FPngLoader::ReadPNGToBuffer(FILE *fp)
//{
//	rewind(fp);
//	//��ȡ���ķ�ʽ
//	png_init_io(m_png_ptr, fp);
//
//	//ֱ��������ȡͼƬ,PNG_TRANSFORM_EXPAND�����´���
//	//��չPaletted ��ɫ��true RGB��Ԫ��
//	//��չ�Ҷ�ͼ��full 8 bits ,��1,2,4bits/pixel
//	//��չPaletted����RGBͼƬ��alphaͨ����RGBA��ʽ
//	png_read_png(m_png_ptr, m_info_ptr, PNG_TRANSFORM_EXPAND, 0);
//
//	m_Width		= m_info_ptr->width;
//	m_Height	= m_info_ptr->height;
//	m_ColorType = m_info_ptr->color_type;
//	m_BitDepth = m_info_ptr->pixel_depth;
//	png_bytep *row_pointers = png_get_rows(m_png_ptr, m_info_ptr);
//	int pos = 0;
//
//	//��RGBAͼ�Ĵ���
//	if (m_ColorType == PNG_COLOR_TYPE_RGBA)
//	{
//		m_RGBA = new unsigned char[m_Width * m_Height * 4];
//		memset(m_RGBA, 0, m_Width * m_Height * 4);
//		for (int i = 0; i < m_Height; i++)
//		{
//			for (int j = 0; j < m_Width * 4; j += 4)
//			{
//				m_RGBA[pos++] = row_pointers[i][j];//R
//				m_RGBA[pos++] = row_pointers[i][j + 1];//G
//				m_RGBA[pos++] = row_pointers[i][j + 2];//B
//				m_RGBA[pos++] = row_pointers[i][j + 3];//A
//			}
//		}
//	}
//
//	
//
//	//png_read_png()
//	//png_get_rowbytes(m_png_ptr, m_info_ptr);
//
////	png_read_info(m_png_ptr, m_info_ptr);
//
//	//png_get_IHDR(m_png_ptr, m_info_ptr, &m_Width, &m_Height, &m_BitDepth, &m_ColorType, nullptr, nullptr);
//
//}
//
//unsigned char* FPngLoader::GetImageBuffer()
//{
//	return m_RGBA;
//}
//
//
