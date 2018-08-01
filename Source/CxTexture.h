#pragma once
#include <glad/glad.h>
#include <iostream>



class FCXTexture
{
public:
	FCXTexture(GLenum TextureTarget, const std::string& FileName);


	bool Load();

	void Bind(GLenum TextureUnit);

private:
	
	std::string m_FileName;
	GLenum		m_TextureTarget;
	GLuint		m_TextureObj;

};