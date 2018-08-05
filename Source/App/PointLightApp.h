#pragma once

#include "LightApp.h"

class FPointLightApp : public FLightAPP, public ICallbacks
{
public:
	FPointLightApp();
	virtual ~FPointLightApp();

	virtual void FrameBufferSizeCB(struct GLFWwindow *window, int width, int height);

	virtual void KeyboardCB(struct GLFWwindow *window, int keyCode, int keyScanCode, int keyAction, int comboFlags);

	virtual void MouseCB(struct GLFWwindow *window, double x, double y);

	virtual void Init(int WindowWidth, int WindowHeight);

	virtual void Run();

	//virtual void BindVAO();

	virtual void PerpareMesh();

protected:

	void CreateVertexBuffer(const unsigned int* pIndices, unsigned int IndexCount);

	void CreateIndexBuffer(const unsigned int* pIndices, unsigned int SizeInBytes);

	/*void CalcNormals(const unsigned int* pIndices, unsigned int IndexCount,
		struct Vertex* pVertices, unsigned int VertexCount);*/



};
