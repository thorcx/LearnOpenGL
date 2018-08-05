#pragma once
#include <GLFW/glfw3.h>
#include "../ogl/ogldev_math_3d.h"
#include "../ogl/ogldev_lights_common.h"
#include "CxApp.h"
#include "../IAppCallback.h"

//创建一个金字塔形,并用LightTechnique着色
class FLightAPP :public CxApp, public ICallbacks 
{
public:

	FLightAPP();
	virtual ~FLightAPP();

	virtual void FrameBufferSizeCB(struct GLFWwindow *window, int width, int height);

	virtual void KeyboardCB(struct GLFWwindow *window, int keyCode, int keyScanCode, int keyAction, int comboFlags);

	virtual void MouseCB(struct GLFWwindow *window, double x, double y);

	virtual void Init(int WindowWidth, int WindowHeight);

	virtual void Run();

	virtual void BindVAO();

	virtual void PerpareMesh();

protected:

	

	virtual void CreateVertexBuffer(const unsigned int* pIndices, unsigned int IndexCount);

	virtual void CreateIndexBuffer(const unsigned int* pIndices, unsigned int SizeInBytes);

	virtual void CalcNormals(const unsigned int* pIndices, unsigned int IndexCount,
		struct Vertex* pVertices, unsigned int VertexCount);

protected:
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