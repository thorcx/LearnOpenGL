#include <glad/glad.h>
#include "../ogl/ogldev_pipeline.h"
#include "../ogl/ogldev_camera.h"
#include "LightingTechnique.h"
#include "PointLightApp.h"
#include "../CxTexture.h"

struct Vertex
{
	Vector3f m_pos;
	Vector2f m_tex;
	Vector3f m_normal;

	Vertex() {}

	Vertex(Vector3f pos, Vector2f tex)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = Vector3f(0.0f, 0.0f, 0.0f);
	};
	Vertex(const Vector3f& pos, const Vector2f& tex, const Vector3f& normal)
	{
		m_pos = pos;
		m_tex = tex;
		m_normal = normal;
	}
};

static const float FieldDepth = 20.0f;
static const float FieldWidth = 10.0f;

FPointLightApp::FPointLightApp()
	:FLightAPP()
{
	m_DirLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
	m_DirLight.AmbientIntensity = 0.5f;
	m_DirLight.DiffuseIntensity = 0.5f;
	m_DirLight.Direction = Vector3f(1.0f, 0.0f, 0.0f);
}

FPointLightApp::~FPointLightApp()
{

}

void FPointLightApp::FrameBufferSizeCB(struct GLFWwindow *window, int width, int height)
{

}

void FPointLightApp::KeyboardCB(struct GLFWwindow *window, int keyCode, int keyScanCode, int keyAction, int comboFlags)
{
	switch (keyCode)
	{
	case GLFW_KEY_1:
		m_DirLight.AmbientIntensity += 0.1;
		break;
	case GLFW_KEY_2:
		m_DirLight.AmbientIntensity -= 0.1;
		break;
	case GLFW_KEY_3:
		m_DirLight.DiffuseIntensity += 0.1;
		break;

	case GLFW_KEY_4:
		m_DirLight.DiffuseIntensity -= 0.1;
		break;
	default:
		break;
	}
	m_pCamera->OnKeyboardEvent(keyCode);
}

void FPointLightApp::MouseCB(struct GLFWwindow *window, double x, double y)
{
	m_pCamera->OnMouse(x, y);
}

void FPointLightApp::Init(int WindowWidth, int WindowHeight)
{
	CxApp::Init(WindowWidth, WindowHeight);
	Vector3f Pos(5.0f, 1.0f, -3.0f);
	Vector3f Target(0.0f, 0.0f, 1.0f);
	Vector3f Up(0.0, 1.0f, 0.0f);

	m_pCamera = new Camera(WindowWidth, WindowHeight, Pos, Target, Up);

	m_PersProjInfo.FOV = 45.0f;
	m_PersProjInfo.Width = WindowWidth;
	m_PersProjInfo.Height = WindowHeight;
	m_PersProjInfo.zNear = 1.0f;
	m_PersProjInfo.zFar = 50.0f;


	PerpareMesh();

	m_pEffect = new FLightingTechnique();

	if (!m_pEffect->Init())
	{
		printf("Error initializing the lighting technique\n");
		return ;
	}

	m_pEffect->Enable();

	m_pEffect->SetTextureUnit(0);

	m_pTexture = new FCXTexture(GL_TEXTURE_2D, "test.png");

	if (!m_pTexture->Load()) {
		return ;
	}

	return ;
}

void FPointLightApp::Run()
{
	while (!glfwWindowShouldClose(m_pGLFWwindow))
	{
		if (glfwGetKey(m_pGLFWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_pGLFWwindow, true);
		}
		m_pCamera->OnRender();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		m_Scale += 0.0057f;

		PointLight pl[2];
		pl[0].DiffuseIntensity = 0.5f;
		pl[0].Color = Vector3f(1.0f, 0.5f, 0.0f);
		pl[0].Position = Vector3f(3.0f, 1.0f, FieldDepth * (cosf(m_Scale) + 1.0f) / 2.0f);
		pl[0].Attenuation.Linear = 0.1f;
		pl[1].DiffuseIntensity = 0.5f;
		pl[1].Color = Vector3f(0.0f, 0.5f, 1.0f);
		pl[1].Position = Vector3f(7.0f, 1.0f, FieldDepth * (sinf(m_Scale) + 1.0f) / 2.0f);
		pl[1].Attenuation.Linear = 0.1f;
		m_pEffect->SetPointLights(2, pl);

		Pipeline p;
		p.WorldPos(0.0f, 0.0f, 1.0f);
		p.SetCamera(m_pCamera->GetPos(), m_pCamera->GetTarget(), m_pCamera->GetUp());
		p.SetPerspectiveProj(m_PersProjInfo);
		m_pEffect->SetWVP(p.GetWVPTrans());
		const Matrix4f& WorldTrans = p.GetWorldTrans();
		m_pEffect->SetWorldMatrix(WorldTrans);
		m_pEffect->SetDirectionalLight(m_DirLight);
		m_pEffect->SetEyeWorldPos(m_pCamera->GetPos());
		m_pEffect->SetMatSpecularIntensity(1.0f);
		m_pEffect->SetMatSpecularPower(32);
		m_pEffect->Enable();

		BindVAO();
		m_pTexture->Bind(GL_TEXTURE0);

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(m_pGLFWwindow);
		glfwPollEvents();

	}
}

void FPointLightApp::PerpareMesh()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	CreateVertexBuffer(nullptr, 0);
	unsigned int Indices[] = { 0, 1, 2,
		3, 4, 5
		 };
	CreateIndexBuffer(Indices, sizeof(Indices));
	glBindVertexArray(0);
}

void FPointLightApp::CreateVertexBuffer(const unsigned int* pIndices, unsigned int IndexCount)
{
	const Vector3f Normal = Vector3f(0.0, 1.0f, 0.0f);

	Vertex Vertices[6] = {
		Vertex(Vector3f(0.0f, 0.0f, 0.0f),             Vector2f(0.0f, 0.0f), Normal),
		Vertex(Vector3f(0.0f, 0.0f, FieldDepth),       Vector2f(0.0f, 1.0f), Normal),
		Vertex(Vector3f(FieldWidth, 0.0f, 0.0f),       Vector2f(1.0f, 0.0f), Normal),

		Vertex(Vector3f(FieldWidth, 0.0f, 0.0f),       Vector2f(1.0f, 0.0f), Normal),
		Vertex(Vector3f(0.0f, 0.0f, FieldDepth),       Vector2f(0.0f, 1.0f), Normal),
		Vertex(Vector3f(FieldWidth, 0.0f, FieldDepth), Vector2f(1.0f, 1.0f), Normal)
	};

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//绑定顶点位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//绑定顶点纹理坐标
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(3 * sizeof(float)));
	//绑定Normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(5 * sizeof(float)));
}

void FPointLightApp::CreateIndexBuffer(const unsigned int* pIndices, unsigned int SizeInBytes)
{
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeInBytes, pIndices, GL_STATIC_DRAW);
}
