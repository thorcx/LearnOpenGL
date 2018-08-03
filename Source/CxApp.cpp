#include "CxApp.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ogl\ogldev_util.h"
#include <iostream>

void CxApp::Init(int WindowWidth, int WindowHeight)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//��������
	m_pGLFWwindow = glfwCreateWindow(WindowWidth, WindowHeight, "LearnOpenGL", NULL, NULL);
	if (m_pGLFWwindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	//������һ�������Ĵ���Ϊ��ǰ�߳��ڵ�main context
	glfwMakeContextCurrent(m_pGLFWwindow);

	//ʹ��GLAD������OpenGL�ĺ���ָ��
	//��ϸ���Ͳο�https://learnopengl.com/Getting-started/Creating-a-window
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, WindowWidth, WindowHeight);

}

CxApp::CxApp()
:m_FrameCount(0),m_FrameTime(0),m_FPS(0)
{
	m_FrameTime = m_StartTime = GetCurrentTimeMillis();
}

CxApp::~CxApp()
{
	glfwTerminate();
}

void CxApp::Run()
{
	//���ﴴ����ѭ��
	while (!glfwWindowShouldClose(m_pGLFWwindow))
	{
		if (glfwGetKey(m_pGLFWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_pGLFWwindow, true);
		}
		//Renderָ��
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//����BackBuffer
		glfwSwapBuffers(m_pGLFWwindow);
		glfwPollEvents();

	}
}

void CxApp::SetupGlewCallbacks(GLFWframebuffersizeCB fn1, GLFWKeyCB fn2, GLFWCursorPosCB fn3)
{
	glfwSetFramebufferSizeCallback(m_pGLFWwindow, fn1);
	glfwSetKeyCallback(m_pGLFWwindow, fn2);
	glfwSetCursorPosCallback(m_pGLFWwindow, fn3);
}

void CxApp::CalcFPS()
{
	m_FrameCount++;

	long long time = GetCurrentTimeMillis();

	if (time - m_FrameTime >= 1000)
	{
		m_FrameTime = time;
		m_FPS = m_FrameCount;
		m_FrameCount = 0;
	}

}

void CxApp::RenderFPS()
{

}

float CxApp::GetRunningTime()
{
	float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_StartTime) / 1000.0f;
	return RunningTime;
}

