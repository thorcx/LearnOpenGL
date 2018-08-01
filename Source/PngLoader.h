#pragma once

#include <iostream>
#include "png.h"

//包装libpng库，现在不使用，改用stb_image这个库 

class FPngLoader
{
public:
	FPngLoader();

	bool LoadFile(std::string FileName);

	//是否是合法的png文件
	bool IsPNG(FILE *fp);

	void ReadPNGToBuffer(FILE *fp);

	unsigned char* GetImageBuffer();

	int GetImageWidth() const { return m_Width; }
	int GetImageHeight() const { return m_Height; }

private:

	//颜色位深
	int m_BitDepth;

	int m_Width;
	int m_Height;
	int m_ColorType;

	unsigned char* m_BGRA;
	unsigned char* m_RGBA;

	//libpng固定两个最重要的结构体指针 
	png_structp		m_png_ptr;
	png_infop		m_info_ptr;

};
