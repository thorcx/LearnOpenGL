#include "ogl/ogldev_camera.h"
#include "LightingTechnique.h"
#include "LightApp.h"

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


}

void FLightAPP::CreateVertexBuffer()
{
	Vertex Vertices[4] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
		Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f)) };


}

