#include <glad/glad.h>
#include "BasicAPP.h"
#include <GLFW/glfw3.h>

#include "../Effects/BasicShadingEffect.h"

FBasicAPP::FBasicAPP()
{

}

FBasicAPP::~FBasicAPP()
{

}

void FBasicAPP::Init(int WindowWidth, int WindowHeight)
{
	CxApp::Init(WindowWidth, WindowHeight);
	PerpareMesh();
	m_pEffect = new FBasicShadingEffect;
	m_pEffect->Init();
	m_pEffect->Enable();
}

void FBasicAPP::Run()
{
	//这里创建大循环
	while (!glfwWindowShouldClose(m_pGLFWwindow))
	{
		if (glfwGetKey(m_pGLFWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_pGLFWwindow, true);
		}
		//Render指令
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		BindVAO();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//交换BackBuffer
		glfwSwapBuffers(m_pGLFWwindow);
		glfwPollEvents();

	}
}

void FBasicAPP::BindVAO()
{
	glBindVertexArray(m_VAO);
}

void FBasicAPP::PerpareMesh()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	CreateSimpleVB();
	CreateSimpleIB();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	glBindVertexArray(0);
}

void FBasicAPP::CreateSimpleVB()
{
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void FBasicAPP::CreateSimpleIB()
{
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}
