//Ϊ��ʹ��stb_image.h�����ͷ�ļ�����룬��Ҫ���������
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <stb_image.h>
#include "CxTexture.h"


FCXTexture::FCXTexture(GLenum TextureTarget, const std::string& FileName)
{
	m_TextureTarget = TextureTarget;
	m_FileName = FileName;
}

bool FCXTexture::Load()
{
	

	int width, height, nrChannels;
	unsigned char* data = stbi_load(m_FileName.c_str(), &width, &height, &nrChannels, 0);

	glGenTextures(1, &m_TextureObj);
	glBindTexture(m_TextureTarget, m_TextureObj);
	//TextureObject�洢��ʵ�ʵ�ͼƬ���ݵ�OpenGL��
	//TextureObject��ֱ�Ӱ󶨵�shader�У����ǰ󶨵�һ��texture unit,���Ǵ������unit��index��shader��
	//shaderͨ�����index��������Ӧ��textureObject,�����ʹ�õ�textureunit��Ŀȡ�����Կ�����

	glTexImage2D(m_TextureTarget, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameterf(m_TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(m_TextureTarget, 0);
	return true;
}

void FCXTexture::Bind(GLenum TextureUnit)
{
	//��unit��textureobject��һ���Ǽ����Ӧ��unit
	//�����Ӧ��texture unit��Ԫ
	glActiveTexture(TextureUnit);

	//����unit��bind�����ͻὫ��Ӧ��textureobject�󶨵���ǰ�������texture unit��
	//ÿһ��texture unit����ͬʱ��Ӧ�����ͬ���͵�textureobject. ���ͱ���Ϊtexture target(1D,2D...)
	//�����ͬʱ��textureobjectA�󶨵�unit0��1DTarget,textureobjectB�󶨵�unit0��2DTarget
	glBindTexture(m_TextureTarget, m_TextureObj);
}

