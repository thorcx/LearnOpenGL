#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//���ڴ�С�ı��Ļص�����
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//����ص�
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	//GLFW��ʼ�����ṩ��Ҫ��Ϣ����OpenGL
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//������һ�������Ĵ���Ϊ��ǰ�߳��ڵ�main context
	glfwMakeContextCurrent(window);

	//ʹ��GLAD������OpenGL�ĺ���ָ��
	//��ϸ���Ͳο�https://learnopengl.com/Getting-started/Creating-a-window
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//���ﴴ����ѭ��
	while (!glfwWindowShouldClose(window))
	{
		//�����û�����
		processInput(window);
		
		//Renderָ��
		glClearColor(0.8f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//����BackBuffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}