
#include <glad/glad.h>
#include "ogl/ogldev_pipeline.h"
#include "ogl/ogldev_camera.h"
#include "LightingTechnique.h"
#include "LightApp.h"
#include "CxTexture.h"


struct Vertex
{
	Vector3f m_pos;
	Vector2f m_tex;

	Vertex() {}

	Vertex(Vector3f pos, Vector2f tex)
	{
		m_pos = pos;
		m_tex = tex;
	}
};

FLightAPP::FLightAPP()
:m_pCamera(nullptr),m_pEffect(nullptr),m_pTexture(nullptr),
m_Scale(0.0f)
{
	m_DirLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
	m_DirLight.AmbientIntensity = 0.5f;

	
}

FLightAPP::~FLightAPP()
{
	delete m_pEffect;
	delete m_pCamera;
	delete m_pTexture;
}

void FLightAPP::FrameBufferSizeCB(struct GLFWwindow *window, int width, int height)
{
	int a = 1;
}

void FLightAPP::KeyboardCB(struct GLFWwindow *window, int keyCode, int keyScanCode, int keyAction, int comboFlags)
{
	m_pCamera->OnKeyboardEvent(keyCode);
}

void FLightAPP::MousePosCB(struct GLFWwindow *window, double x, double y)
{
	m_pCamera->OnMouse(x, y);
}

void FLightAPP::Init(int WindowWidth, int WindowHeight)
{
	CxApp::Init(WindowWidth, WindowHeight);
	m_PersProjInfo.FOV = 60.0f;
	m_PersProjInfo.Width = WindowWidth;
	m_PersProjInfo.Height = WindowHeight;
	m_PersProjInfo.zNear = 1.0f;
	m_PersProjInfo.zFar = 100.0f;

	m_pCamera = new Camera(WindowWidth, WindowHeight);

	m_pEffect = new FLightingTechnique();
	if (!m_pEffect->Init())
	{
		return;
	}
	m_pEffect->Enable();
	m_pEffect->SetTextureUnit(0);
	m_pTexture = new FCXTexture(GL_TEXTURE_2D, "test.png");
	if (!m_pTexture->Load())
	{
		return;
	}

}

void FLightAPP::Run()
{
	while (!glfwWindowShouldClose(m_pGLFWwindow))
	{
		if (glfwGetKey(m_pGLFWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_pGLFWwindow, true);
		}
		m_pCamera->OnRender();
		//Renderָ��
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		m_Scale += 0.1;

		Pipeline p;
		p.Rotate(0.0f, m_Scale, 0.0f);
		p.WorldPos(0.0f, 0.0f, 0.0f);
		p.SetCamera(m_pCamera->GetPos(), m_pCamera->GetTarget(), m_pCamera->GetUp());
		p.SetPerspectiveProj(m_PersProjInfo);
		m_pEffect->SetWVP(p.GetWVPTrans());
		m_pEffect->SetDirectionalLight(m_DirLight);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(3 * sizeof(float)));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		m_pTexture->Bind(GL_TEXTURE0);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		//����BackBuffer
		glfwSwapBuffers(m_pGLFWwindow);
		glfwPollEvents();

	}
}

void FLightAPP::CreateVertexBuffer()
{
	Vertex Vertices[4] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
		Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f)) };

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

void FLightAPP::CreateIndexBuffer()
{
	unsigned int Indices[] = { 0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		1, 2, 0 };

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

