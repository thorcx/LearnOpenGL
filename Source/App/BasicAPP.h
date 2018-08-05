#pragma once

#pragma once
#include <GLFW/glfw3.h>
#include "../ogl/ogldev_math_3d.h"
#include "../ogl/ogldev_lights_common.h"
#include "CxApp.h"
#include "../IAppCallback.h"
class FBasicAPP :public CxApp, public ICallbacks
{
public:

	FBasicAPP();
	~FBasicAPP();


	virtual void Init(int WindowWidth, int WindowHeight);

	virtual void Run();

	virtual void BindVAO();

	virtual void PerpareMesh();

private:

	void CreateSimpleVB();
	void CreateSimpleIB();

private:
	GLuint m_VBO;
	GLuint m_IBO;
	//VertexArrayObject
	GLuint m_VAO;

	class FBasicShadingEffect	*m_pEffect;
	
};
