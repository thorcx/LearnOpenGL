#pragma once
//#include <GLFW/glfw3.h>

typedef void(*GLFWframebuffersizeCB)(struct GLFWwindow*, int, int);

class CxApp
{

public:

	static void KeyboardCB(struct GLFWwindow *window, int keyCode, int keyScanCode, int keyAction, int comboFlags) {};

	static  void FrameBufferSizeCB(struct GLFWwindow *window, int width, int height) {}

	static void MousePosCB(struct GLFWwindow *window, double x, double y) {}

	virtual void Init(int WindowWidth, int WindowHeight);

	virtual void Run();

	virtual void SetupGlewCallbacks(GLFWframebuffersizeCB fn1);
protected:
	CxApp();

	~CxApp();

	

	

	void CalcFPS();

	void RenderFPS();

	float GetRunningTime();

private:

	struct GLFWwindow  *m_pGLFWwindow;

	long long	m_FrameTime;
	long long	m_StartTime;
	int			m_FrameCount;
	int			m_FPS;
};