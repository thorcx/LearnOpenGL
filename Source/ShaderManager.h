#pragma once
#include "Common.h"
#include <iostream>

//��ȡShader�ļ�,Attach��ShaderProgram��
static GLuint AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0)
	{
		std::cout << "Error creating shader type:" << ShaderType << std::endl;
		exit(0);
	}
	const char* p[1];
	p[0] = pShaderText;
	GLint lengths[1];
	lengths[0] = static_cast<GLint>(strlen(pShaderText));
	glShaderSource(ShaderObj, 1, p, lengths);
	glCompileShader(ShaderObj);

	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL,InfoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << InfoLog << std::endl;
		exit(1);
	}
	glAttachShader(ShaderProgram, ShaderObj);
	return ShaderObj;
}

static void CompileShaders(GLuint shaderProgram, std::string vsFileName, std::string psFileName)
{
	std::string vs, ps;

	if (!ReadFile(vsFileName, vs))
	{
		exit(1);
	}

	if (!ReadFile(psFileName, ps))
	{
		exit(1);
	}

	GLuint vsobj = AddShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	GLuint fsobj = AddShader(shaderProgram, ps.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	//��ShaderProgram Attach ��Ӧ��Shader����ҪLink
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Success);
	if (!Success)
	{
		GLchar ErrorLog[1024] = { 0 };
		glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << "Error linking shader program: " << ErrorLog << std::endl;
		exit(1);
	}
	
	//�����link�Ὣvs,ps�����������������һ���Ż��������Validate����ݵ�ǰOpenGL context state��ȷ�����ӵ�shader����
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success)
	{
		GLchar ErrorLog[1024] = { 0 };
		glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog),  NULL, ErrorLog);
		std::cout << "Invalide shader program: " << ErrorLog << std::endl;
		exit(1);
	}
	//��shaderAttach����Link�ɹ��󣬾Ϳ����ͷŶ�Ӧ��ShaderObject
	//ע��������ҪDetach,��Delete,���ֱ��Delete,OpenGLֻ�ǽ�ShaderObject������-1�������ܻ�����Դ
	glDetachShader(shaderProgram, vsobj);
	glDeleteShader(vsobj);
	glDetachShader(shaderProgram, fsobj);
	glDeleteShader(fsobj);

}