#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//定义一个标准坐标系三角形
float vertices[] = {
	0.5f,  0.5f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

//定义indices
unsigned int indices[] = {
	0,1,3,
	1,2,3
};

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";


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

int main()
{
	//GLFW初始化，提供必要信息来给OpenGL
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//设置上一步创建的窗口为当前线程内的main context
	glfwMakeContextCurrent(window);

	//使用GLAD来管理OpenGL的函数指针
	//详细解释参考https://learnopengl.com/Getting-started/Creating-a-window
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//创建ShaderObject;
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//指定此ShaderOject对应的GLSL文件内容
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//编译此shader
	glCompileShader(vertexShader);
	//检查编译错误
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//FS编译
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//创建ShaderProgram,代表VS,FS的集合
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//检查错误
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	
	unsigned int VAO,VBO,EBO;

	//先绑定VertexArrayObject,然后绑定VertexBuffer,配置Vertex attributes.
	//VAO绑定后，后续的vertex attribute操作都会被存在VAO内，所以以后指定vertex attr操作都可以直接通过VAO指定，方便了调用过程。
	glGenVertexArrays(1, &VAO);


	//通知OpenGL,要求一个VertexBufferObject,对应的OpenGL在GPU上创建相应的内存并返回VBO的索引
	//我们在CPU端就可以上传顶点数据给GPU
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	//将VBO绑定到GL_ARRAY_BUFFER这个TYPE,告诉OpenGL这个Buffer的具体数据类型.后续OpenGL根据Buffer的Type来解读其中的数据 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//上面绑定后就可以用glBufferData来操作向此VBO填充数据
	//此函数专门用来对指定的BufferType绑定的buffer来传输数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//这里进行attribute的绑定，第一个参数0对应vs中的layout(location 0)
	//第二个参数指定attribute内的数据的个数，vs中定义的是vec3,也就是包含3个元素
	//当调用此函数时, VBO与当前被VBO绑定的数据决定了attribute的输入
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//参数是Vertexattribute的location
	glEnableVertexAttribArray(0);

	//清除GL_ARRAY_BUFFER的绑定，这里因为前面已经通过glVertexAttribPointer保存了VBO对应数据绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//清除VAO的绑定，这里也是可以的，因为上面的VAO已经记录了所有需要传给GPU的信息，所以这里解除也没问题，以后再用的时候，随时绑定就可以恢复
	//GPU对应的VAO的状态
	glBindVertexArray(0);

	//这里创建大循环
	while (!glfwWindowShouldClose(window))
	{
		//处理用户输入
		processInput(window);
		
		//Render指令
		glClearColor(0.8f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		//这里又使用vao绑定，所有前面的vbo的状态被恢复到记录他的时刻
		glBindVertexArray(VAO);
		//线框模式
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		//交换BackBuffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}