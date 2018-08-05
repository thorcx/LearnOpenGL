#pragma once
//#include <GLFW/glfw3.h>

typedef void(*GLFWframebuffersizeCB)(struct GLFWwindow*, int, int);
typedef void(*GLFWKeyCB)(struct GLFWwindow*, int, int, int, int);
typedef void(*GLFWCursorPosCB)(struct GLFWwindow*, double, double);

class CxApp
{

public:

	static void KeyboardCB(struct GLFWwindow *window, int keyCode, int keyScanCode, int keyAction, int comboFlags) {};

	static  void FrameBufferSizeCB(struct GLFWwindow *window, int width, int height) {}

	static void MousePosCB(struct GLFWwindow *window, double x, double y) {}

	virtual void Init(int WindowWidth, int WindowHeight);

	virtual void Run();

	virtual void SetupGlewCallbacks(GLFWframebuffersizeCB fn1, GLFWKeyCB fn2, GLFWCursorPosCB fn3);
protected:
	CxApp();

	virtual ~CxApp();

	

	

	void CalcFPS();

	void RenderFPS();

	float GetRunningTime();
protected:
	struct GLFWwindow  *m_pGLFWwindow;
private:


	long long	m_FrameTime;
	long long	m_StartTime;
	int			m_FrameCount;
	int			m_FPS;
};