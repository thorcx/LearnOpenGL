//为了使用stb_image.h这个单头文件库编译，先要定义这个宏
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
	//TextureObject存储了实际的图片数据到OpenGL中
	//TextureObject不直接绑定到shader中，而是绑定到一个texture unit,我们传递这个unit的index到shader中
	//shader通过这个index索引到对应的textureObject,具体可使用的textureunit数目取决于显卡能力

	glTexImage2D(m_TextureTarget, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameterf(m_TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(m_TextureTarget, 0);
	return true;
}

void FCXTexture::Bind(GLenum TextureUnit)
{
	//绑定unit与textureobject第一步是激活对应的unit
	//激活对应的texture unit单元
	glActiveTexture(TextureUnit);

	//激活unit后bind操作就会将对应的textureobject绑定到当前被激活的texture unit中
	//每一个texture unit可以同时对应多个不同类型的textureobject. 类型被称为texture target(1D,2D...)
	//你可以同时将textureobjectA绑定到unit0的1DTarget,textureobjectB绑定到unit0的2DTarget
	glBindTexture(m_TextureTarget, m_TextureObj);
}

