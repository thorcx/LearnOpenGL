

#include <glad/glad.h>
#include <iostream>

#include "ShaderManager.h"
#include "ogl/ogldev_math_3d.h"

//����һ����׼����ϵ������
float vertices[] = {
	0.5f,  0.5f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

//����indices
unsigned int indices[] = {
	0,1,3,
	1,2,3
};




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




	//����ShaderProgram,����VS,FS�ļ���
	GLint shaderProgram = glCreateProgram();
	CompileShaders(shaderProgram, "Source/Shaders/BaseVS.glsl", "Source/Shaders/BaseFS.glsl");
	
	unsigned int VAO,VBO,EBO;

	//�Ȱ�VertexArrayObject,Ȼ���VertexBuffer,����Vertex attributes.
	//VAO�󶨺󣬺�����vertex attribute�������ᱻ����VAO�ڣ������Ժ�ָ��vertex attr����������ֱ��ͨ��VAOָ���������˵��ù��̡�
	glGenVertexArrays(1, &VAO);


	//֪ͨOpenGL,Ҫ��һ��VertexBufferObject,��Ӧ��OpenGL��GPU�ϴ�����Ӧ���ڴ沢����VBO������
	//������CPU�˾Ϳ����ϴ��������ݸ�GPU
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	//��VBO�󶨵�GL_ARRAY_BUFFER���TYPE,����OpenGL���Buffer�ľ�����������.����OpenGL����Buffer��Type��������е����� 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//����󶨺�Ϳ�����glBufferData���������VBO�������
	//�˺���ר��������ָ����BufferType�󶨵�buffer����������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//�������attribute�İ󶨣���һ������0��Ӧvs�е�layout(location 0)
	//�ڶ�������ָ��attribute�ڵ����ݵĸ�����vs�ж������vec3,Ҳ���ǰ���3��Ԫ��
	//�����ô˺���ʱ, VBO�뵱ǰ��VBO�󶨵����ݾ�����attribute������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//������Vertexattribute��location
	glEnableVertexAttribArray(0);

	//���GL_ARRAY_BUFFER�İ󶨣�������Ϊǰ���Ѿ�ͨ��glVertexAttribPointer������VBO��Ӧ���ݰ�
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//���VAO�İ󶨣�����Ҳ�ǿ��Եģ���Ϊ�����VAO�Ѿ���¼��������Ҫ����GPU����Ϣ������������Ҳû���⣬�Ժ����õ�ʱ����ʱ�󶨾Ϳ��Իָ�
	//GPU��Ӧ��VAO��״̬
	glBindVertexArray(0);

	//���ﴴ����ѭ��
	while (!glfwWindowShouldClose(window))
	{
		//�����û�����
		processInput(window);
		
		//Renderָ��
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//������ʹ��vao�󶨣�����ǰ���vbo��״̬���ָ�����¼����ʱ��
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//�߿�ģʽ
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "uniColor");
		
		static float Scale = 0.0f;
		Scale += 0.001f;
		Matrix4f World;
		World.m[0][0] = 1.0f; World.m[0][1] = 0.0f; World.m[0][2] = 0.0f; World.m[0][3] = sinf(Scale);
		World.m[1][0] = 0.0f; World.m[1][1] = 1.0f; World.m[1][2] = 0.0f; World.m[1][3] = 0.0f;
		World.m[2][0] = 0.0f; World.m[2][1] = 0.0f; World.m[2][2] = 1.0f; World.m[2][3] = 0.0f;
		World.m[3][0] = 0.0f; World.m[3][1] = 0.0f; World.m[3][2] = 0.0f; World.m[3][3] = 1.0f;
		
		GLuint gWorldLocation = glGetUniformLocation(shaderProgram, "gWorld");

		glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World.m[0][0]);
		//int scale = glGetUniformLocation(shaderProgram, "gScale");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 1.0f, 1.0f);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//����BackBuffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}