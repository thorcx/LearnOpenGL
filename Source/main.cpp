

#include <glad/glad.h>
#include <iostream>

//#include "ShaderManager.h"
#include "ogl/ogldev_math_3d.h"
#include "ogl/ogldev_pipeline.h"
#include "CxTexture.h"
#include "CxApp.h"

struct Vertex
{
	Vector3f m_pos;
	Vector2f m_tex;

	Vertex() {}
	Vertex(Vector3f pos, Vector2f tex) :m_pos(pos), m_tex(tex) {}
};

GLuint g_VBO, g_IBO, g_VAO;


static void CreateVertexBuffer()
{
	Vertex Vertices[4] = {
		Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
		Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f))
	};
	//通知OpenGL,要求一个VertexBufferObject,对应的OpenGL在GPU上创建相应的内存并返回VBO的索引
	//我们在CPU端就可以上传顶点数据给GPU
	glGenBuffers(1, &g_VBO);

	//将VBO绑定到GL_ARRAY_BUFFER这个TYPE,告诉OpenGL这个Buffer的具体数据类型.后续OpenGL根据Buffer的Type来解读其中的数据 
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO);

	//上面绑定后就可以用glBufferData来操作向此VBO填充数据
	//此函数专门用来对指定的BufferType绑定的buffer来传输数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void CreateIndexBuffer()
{
	unsigned int Indices[] = { 0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2 };

	glGenBuffers(1, &g_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}



Camera* pCamera = NULL;
PersProjInfo gPersProjInfo;


GLuint	gSampler;

//Texture *pTexture = NULL;

//窗口大小改变后的回调函数
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
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
	//pCamera->OnKeyboard((OGLDEV_KEY)keyCode);
	pCamera->OnKeyboardEvent(keyCode);
}

void MousePosCallback(GLFWwindow *window, double x, double y)
{
	pCamera->OnMouse(x, y);
}


class FLightAPP :public CxApp
{
public:
	static  void FrameBufferSizeCB(struct GLFWwindow *window, int width, int height);
};

void FLightAPP::FrameBufferSizeCB(struct GLFWwindow *window, int width, int height)
{
	cout << "aaa";
}



int main()
{
	FLightAPP app;
	app.Init(800, 600);

	app.SetupGlewCallbacks(FLightAPP::FrameBufferSizeCB);

	app.Run();
	return 0;
}

//int main()
//{
//	//GLFW初始化，提供必要信息来给OpenGL
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	
//
//	//创建窗口
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	//设置上一步创建的窗口为当前线程内的main context
//	glfwMakeContextCurrent(window);
//
//	//使用GLAD来管理OpenGL的函数指针
//	//详细解释参考https://learnopengl.com/Getting-started/Creating-a-window
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	glViewport(0, 0, 800, 600);
//
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetKeyCallback(window, KeyCallbackFunc);
//	glfwSetCursorPosCallback(window, MousePosCallback);
//
//
//	//创建ShaderProgram,代表VS,FS的集合
//	GLint shaderProgram = glCreateProgram();
//	CompileShaders(shaderProgram, "Source/Shaders/BaseVS.glsl", "Source/Shaders/BaseFS.glsl");
//	gSampler = glGetUniformLocation(shaderProgram, "gSampler");
//
//	//unsigned int VAO,VBO,EBO;
//
//	//先绑定VertexArrayObject,然后绑定VertexBuffer,配置Vertex attributes.
//	//VAO绑定后，后续的vertex attribute操作都会被存在VAO内，所以以后指定vertex attr操作都可以直接通过VAO指定，方便了调用过程。
//	glGenVertexArrays(1, &g_VAO);
//	glBindVertexArray(g_VAO);
//
//	CreateVertexBuffer();
//	
//	
//	//参数是Vertexattribute的location
//	glEnableVertexAttribArray(0);
//	//这里进行attribute的绑定，第一个参数0对应vs中的layout(location 0)
//	//第二个参数指定attribute内的数据的个数，vs中定义的是vec3,也就是包含3个元素
//	//当调用此函数时, VBO与当前被VBO绑定的数据决定了attribute的输入
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(const void*)(3 * sizeof(float)) );
//
//	CreateIndexBuffer();
//
//	//清除GL_ARRAY_BUFFER的绑定，这里因为前面已经通过glVertexAttribPointer保存了VBO对应数据绑定
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	//清除VAO的绑定，这里也是可以的，因为上面的VAO已经记录了所有需要传给GPU的信息，所以这里解除也没问题，以后再用的时候，随时绑定就可以恢复
//	//GPU对应的VAO的状态
//	glBindVertexArray(0);
//
//	FCXTexture tex(GL_TEXTURE_2D, "test.png");
//	if (!tex.Load())
//	{
//		return -1;
//	}
//	//设置FS中uniform变量，采样器与texture unit 0绑定
//	glUniform1i(gSampler, 0);
//	
//
//	Vector3f CameraPos(0.0f, -3.0f, -3.0f);
//	Vector3f CameraTarget(0.0f, 0.0f, 2.0f);
//	Vector3f CameraUp(0.0f, 1.0f, 0.0f);
//	pCamera = new Camera(800, 600, CameraPos, CameraTarget, CameraUp);
//
//	//设置透视参数
//	gPersProjInfo.FOV = 60.0f;
//	gPersProjInfo.Height = 600;
//	gPersProjInfo.Width = 800;
//	gPersProjInfo.zNear = 1.0f;
//	gPersProjInfo.zFar = 100.0f;
//
//
//
//	//这里创建大循环
//	while (!glfwWindowShouldClose(window))
//	{
//		//处理用户输入
//		processInput(window);
//		
//		//Render指令
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//		glFrontFace(GL_CW);
//		glCullFace(GL_BACK);
//		glEnable(GL_CULL_FACE);
//
//		//这里又使用vao绑定，所有前面的vbo的状态被恢复到记录他的时刻
//		glUseProgram(shaderProgram);
//		
//		glBindVertexArray(g_VAO);
//		
//		tex.Bind(GL_TEXTURE0);
//		//线框模式
//		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//		float timeValue = glfwGetTime();
//		float greenValue = sin(timeValue) / 2.0f + 0.5f;
//		int vertexColorLocation = glGetUniformLocation(shaderProgram, "uniColor");
//		
//		static float Scale = 0.0f;
//		Scale += 0.1f;
//		Pipeline p;
//		p.Rotate(0.0f, Scale, 0.0f);
//		p.WorldPos(0.0f, 0.0f, 3.0f);
//		
//		p.SetCamera(*pCamera);
//		p.SetPerspectiveProj(gPersProjInfo);
//		
//		//p.Rotate(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f);
//
//		GLuint gWorldLocation = glGetUniformLocation(shaderProgram, "gWVP");
//
//		glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (const GLfloat*)p.GetWVPTrans());
//		//int scale = glGetUniformLocation(shaderProgram, "gScale");
//		glUniform4f(vertexColorLocation, 0.0f, greenValue, 1.0f, 1.0f);
//
//		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
//		
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//
//		//交换BackBuffer
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	glDeleteVertexArrays(1, &g_VAO);
//	glDeleteBuffers(1, &g_VBO);
//	glDeleteBuffers(1, &g_IBO);
//
//	glfwTerminate();
//	
//	return 0;
//}