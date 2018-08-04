#pragma once
#include <GLFW/glfw3.h>
#include "ogl/ogldev_math_3d.h"
#include "ogl/ogldev_lights_common.h"
#include "CxApp.h"
#include "IAppCallback.h"
class FLightAPP :public CxApp, public ICallbacks 
{
public:

	FLightAPP();
	~FLightAPP();

	virtual void FrameBufferSizeCB(struct GLFWwindow *window, int width, int height);

	virtual void KeyboardCB(struct GLFWwindow *window, int keyCode, int keyScanCode, int keyAction, int comboFlags);

	virtual void MouseCB(struct GLFWwindow *window, double x, double y);

	virtual void Init(int WindowWidth, int WindowHeight);

	virtual void Run();

	virtual void BindVAO();

	virtual void PerpareMesh();

private:

	

	void CreateVertexBuffer();

	void CreateIndexBuffer();

private:
	GLuint m_VBO;
	GLuint m_IBO;
	//VertexArrayObject
	GLuint m_VAO;

	class FLightingTechnique	*m_pEffect;
	class FCXTexture*	m_pTexture;
	class Camera*		m_pCamera;
	float				m_Scale;
	DirectionalLight	m_DirLight;
	PersProjInfo		m_PersProjInfo;
};