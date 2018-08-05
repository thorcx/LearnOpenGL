

#include <glad/glad.h>
#include <iostream>

//#include "ShaderManager.h"
#include "ogl/ogldev_math_3d.h"
#include "ogl/ogldev_pipeline.h"
#include "CxTexture.h"
#include "App/LightApp.h"
#include "APP/PointLightApp.h"

static ICallbacks* s_pCallbacks = nullptr;

//窗口大小改变后的回调函数
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	s_pCallbacks->FrameBufferSizeCB(window, width, height);
	//glViewport(0, 0, width, height);
}

//输入回调
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void KeyCallbackFunc(GLFWwindow *window, int keyCode, int keyScanCode, int keyAction, int comboFlags)
{
	s_pCallbacks->KeyboardCB(window,keyCode, keyScanCode, keyAction, comboFlags);
}

void MousePosCallback(GLFWwindow *window, double x, double y)
{
	s_pCallbacks->MouseCB(window, x, y);
}


int main()
{
	//FBasicAPP app;
	//app.Init(800, 600);
	//app.Run();
	//FLightAPP app;
	
	FPointLightApp app;
	app.Init(800, 600);
	s_pCallbacks = &app;

	app.SetupGlewCallbacks(framebuffer_size_callback, KeyCallbackFunc, MousePosCallback);

	app.Run();
	return 0;
}

