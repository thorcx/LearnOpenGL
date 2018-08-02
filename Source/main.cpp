

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
	//֪ͨOpenGL,Ҫ��һ��VertexBufferObject,��Ӧ��OpenGL��GPU�ϴ�����Ӧ���ڴ沢����VBO������
	//������CPU�˾Ϳ����ϴ��������ݸ�GPU
	glGenBuffers(1, &g_VBO);

	//��VBO�󶨵�GL_ARRAY_BUFFER���TYPE,����OpenGL���Buffer�ľ�����������.����OpenGL����Buffer��Type��������е����� 
	glBindBuffer(GL_ARRAY_BUFFER, g_VBO);

	//����󶨺�Ϳ�����glBufferData���������VBO�������
	//�˺���ר��������ָ����BufferType�󶨵�buffer����������
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
//	//GLFW��ʼ�����ṩ��Ҫ��Ϣ����OpenGL
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	
//
//	//��������
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	//������һ�������Ĵ���Ϊ��ǰ�߳��ڵ�main context
//	glfwMakeContextCurrent(window);
//
//	//ʹ��GLAD������OpenGL�ĺ���ָ��
//	//��ϸ���Ͳο�https://learnopengl.com/Getting-started/Creating-a-window
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
//	//����ShaderProgram,����VS,FS�ļ���
//	GLint shaderProgram = glCreateProgram();
//	CompileShaders(shaderProgram, "Source/Shaders/BaseVS.glsl", "Source/Shaders/BaseFS.glsl");
//	gSampler = glGetUniformLocation(shaderProgram, "gSampler");
//
//	//unsigned int VAO,VBO,EBO;
//
//	//�Ȱ�VertexArrayObject,Ȼ���VertexBuffer,����Vertex attributes.
//	//VAO�󶨺󣬺�����vertex attribute�������ᱻ����VAO�ڣ������Ժ�ָ��vertex attr����������ֱ��ͨ��VAOָ���������˵��ù��̡�
//	glGenVertexArrays(1, &g_VAO);
//	glBindVertexArray(g_VAO);
//
//	CreateVertexBuffer();
//	
//	
//	//������Vertexattribute��location
//	glEnableVertexAttribArray(0);
//	//�������attribute�İ󶨣���һ������0��Ӧvs�е�layout(location 0)
//	//�ڶ�������ָ��attribute�ڵ����ݵĸ�����vs�ж������vec3,Ҳ���ǰ���3��Ԫ��
//	//�����ô˺���ʱ, VBO�뵱ǰ��VBO�󶨵����ݾ�����attribute������
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(const void*)(3 * sizeof(float)) );
//
//	CreateIndexBuffer();
//
//	//���GL_ARRAY_BUFFER�İ󶨣�������Ϊǰ���Ѿ�ͨ��glVertexAttribPointer������VBO��Ӧ���ݰ�
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	//���VAO�İ󶨣�����Ҳ�ǿ��Եģ���Ϊ�����VAO�Ѿ���¼��������Ҫ����GPU����Ϣ������������Ҳû���⣬�Ժ����õ�ʱ����ʱ�󶨾Ϳ��Իָ�
//	//GPU��Ӧ��VAO��״̬
//	glBindVertexArray(0);
//
//	FCXTexture tex(GL_TEXTURE_2D, "test.png");
//	if (!tex.Load())
//	{
//		return -1;
//	}
//	//����FS��uniform��������������texture unit 0��
//	glUniform1i(gSampler, 0);
//	
//
//	Vector3f CameraPos(0.0f, -3.0f, -3.0f);
//	Vector3f CameraTarget(0.0f, 0.0f, 2.0f);
//	Vector3f CameraUp(0.0f, 1.0f, 0.0f);
//	pCamera = new Camera(800, 600, CameraPos, CameraTarget, CameraUp);
//
//	//����͸�Ӳ���
//	gPersProjInfo.FOV = 60.0f;
//	gPersProjInfo.Height = 600;
//	gPersProjInfo.Width = 800;
//	gPersProjInfo.zNear = 1.0f;
//	gPersProjInfo.zFar = 100.0f;
//
//
//
//	//���ﴴ����ѭ��
//	while (!glfwWindowShouldClose(window))
//	{
//		//�����û�����
//		processInput(window);
//		
//		//Renderָ��
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//		glFrontFace(GL_CW);
//		glCullFace(GL_BACK);
//		glEnable(GL_CULL_FACE);
//
//		//������ʹ��vao�󶨣�����ǰ���vbo��״̬���ָ�����¼����ʱ��
//		glUseProgram(shaderProgram);
//		
//		glBindVertexArray(g_VAO);
//		
//		tex.Bind(GL_TEXTURE0);
//		//�߿�ģʽ
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
//		//����BackBuffer
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