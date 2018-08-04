//#pragma once
//
//#include <iostream>
//#include "png.h"
//
////��װlibpng�⣬���ڲ�ʹ�ã�����stb_image����� 
//
//class FPngLoader
//{
//public:
//	FPngLoader();
//
//	bool LoadFile(std::string FileName);
//
//	//�Ƿ��ǺϷ���png�ļ�
//	bool IsPNG(FILE *fp);
//
//	void ReadPNGToBuffer(FILE *fp);
//
//	unsigned char* GetImageBuffer();
//
//	int GetImageWidth() const { return m_Width; }
//	int GetImageHeight() const { return m_Height; }
//
//private:
//
//	//��ɫλ��
//	int m_BitDepth;
//
//	int m_Width;
//	int m_Height;
//	int m_ColorType;
//
//	unsigned char* m_BGRA;
//	unsigned char* m_RGBA;
//
//	//libpng�̶���������Ҫ�Ľṹ��ָ�� 
//	png_structp		m_png_ptr;
//	png_infop		m_info_ptr;
//
//};
