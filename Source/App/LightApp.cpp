
#include <glad/glad.h>
#include "../ogl/ogldev_pipeline.h"
#include "../ogl/ogldev_camera.h"
#include "LightingTechnique.h"
#include "LightApp.h"
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
	}
};

FLightAPP::FLightAPP()
:m_pCamera(nullptr),m_pEffect(nullptr),m_pTexture(nullptr),
m_Scale(0.0f)
{
	m_DirLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
	m_DirLight.AmbientIntensity = 0.5f;
	m_DirLight.DiffuseIntensity = 0.5f;
	m_DirLight.Direction = Vector3f(1.0f, 0.0f, 0.0f);
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

void FLightAPP::MouseCB(struct GLFWwindow *window, double x, double y)
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

	Vector3f Pos(0.0f, 0.0f, -3.0f);
	Vector3f Target(0.0f, 0.0f, 1.0f);
	Vector3f Up(0.0, 1.0f, 0.0f);
	m_pCamera = new Camera(WindowWidth, WindowHeight, Pos, Target, Up);

	PerpareMesh();
//	CreateVertexBuffer();
//	CreateIndexBuffer();

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
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		m_Scale += 1;
		
		Pipeline p;
		p.Rotate(0.0f, m_Scale, 0.0f);
		p.WorldPos(0.0f, 0.0f, 10.0f);
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
		
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(m_pGLFWwindow);
		glfwPollEvents();

	}
}

void FLightAPP::BindVAO()
{
	glBindVertexArray(m_VAO);
}

void FLightAPP::PerpareMesh()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	unsigned int Indices[] = { 0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		1, 2, 0 };
	CreateVertexBuffer(Indices, ARRAY_SIZE_IN_ELEMENTS(Indices));
	CreateIndexBuffer(Indices, sizeof(Indices));
	glBindVertexArray(0);
}



void FLightAPP::CreateVertexBuffer(const unsigned int* pIndices, unsigned int IndexCount)
{
	Vertex Vertices[4] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
		Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f)) };

	CalcNormals(pIndices, IndexCount, Vertices, 4);

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

void FLightAPP::CreateIndexBuffer(const unsigned int* pIndices, unsigned int SizeInBytes)
{
	
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeInBytes, pIndices, GL_STATIC_DRAW);
}

void FLightAPP::CalcNormals(const unsigned int* pIndices, unsigned int IndexCount, Vertex* pVertices, unsigned int VertexCount)
{
	// Accumulate each triangle normal into each of the triangle vertices
	for (unsigned int i = 0; i < IndexCount; i += 3) {
		unsigned int Index0 = pIndices[i];
		unsigned int Index1 = pIndices[i + 1];
		unsigned int Index2 = pIndices[i + 2];
		Vector3f v1 = pVertices[Index1].m_pos - pVertices[Index0].m_pos;
		Vector3f v2 = pVertices[Index2].m_pos - pVertices[Index0].m_pos;
		Vector3f Normal = v1.Cross(v2);
		Normal.Normalize();

		pVertices[Index0].m_normal += Normal;
		pVertices[Index1].m_normal += Normal;
		pVertices[Index2].m_normal += Normal;
	}

	// Normalize all the vertex normals
	for (unsigned int i = 0; i < VertexCount; i++) {
		pVertices[i].m_normal.Normalize();
	}
}

