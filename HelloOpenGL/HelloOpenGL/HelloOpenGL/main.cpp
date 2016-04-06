#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "TrianglePractice.h"

void key_callBack(GLFWwindow* window, int key, int scancode, int action, int mode);
GLuint createVertexShader();
GLuint createFragmentShader();
GLuint createProgram(GLuint vertexShaderId, GLuint fragmentShaderId);
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
int main(int argc, char** argv)
{
	TrianglePractice* triangle = new TrianglePractice();

}
//int main(int argc, char** argv)
//{
//	glfwInit();
//	//下面两行告诉GLFW我们要使用的是OPENGL 3.3 版本
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//
//	//表示我们使用核心模式而不是使用兼容模式,使用核心模式效率更高,但是有一些函数不被支持
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	//表示窗口应该不能被设置成大小
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//
//	//创建指定的窗口
//	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL", nullptr, nullptr);
//	if (window == nullptr)
//	{
//		glfwTerminate();
//	}
//
//
//	glfwMakeContextCurrent(window);
//	glewExperimental = GL_TRUE;//表示GLEW是否使用一些实验性质的功能,如果设置成false可能在核心模式下存在问题
//	if (glewInit() != GLEW_OK)
//	{
//		return -1;
//	}
//	glViewport(0, 0, 800, 600);
//
//
//
//
//	//设置键盘按下时的回调函数
//	glfwSetKeyCallback(window, key_callBack);
//
//	GLuint fragmentShaderId = createFragmentShader();
//	GLuint vertextShaderId = createVertexShader();
//	GLuint programId = createProgram(vertextShaderId, fragmentShaderId);
//
//	GLfloat vertices[] = {
//		0.5f,  0.5f, 0.0f,  // Top Right
//		0.5f, -0.5f, 0.0f,  // Bottom Right
//		-0.5f, -0.5f, 0.0f,  // Bottom Left
//		-0.5f,  0.5f, 0.0f   // Top Left 
//	};
//
//	GLuint indices[] = {
//	 3,2,0,
//	 0,2,1
//	};
//
//	GLuint VBO, VAO, EBO;
//	 
//	//以下三次函数调用分别为生成顶点缓存对象Id,索引缓存对象Id以及顶点数组
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//	glGenVertexArrays(1, &VAO);
//
//	//以下为绑定顶点数组,将VAO与VBO,EBO之间建立关联,EBO中只存了VBO中的索引
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);//生成一个顶点缓冲对象,并将其绑定到VBO Id上
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//设置缓冲对象的数据,其实这里就是给ID为 VBO的缓冲对象设置值
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//
//
//	//调用该方法告诉OpenGL如何解释我们提供的顶点对象
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	//不停的判断窗口是否已经退出了
//	while (!glfwWindowShouldClose(window))
//	{
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glUseProgram(programId);
//		glBindVertexArray(VAO);
//		//glDrawArrays(GL_TRIANGLES, 0, 3);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//		//监听鼠标,键盘等设备的事件
//		glfwPollEvents();
//		//交换缓冲区
//		glfwSwapBuffers(window);
//	}
//
//	glfwTerminate();//在窗口被关闭后,释放所有的资源
//	return 0;
//}

/*
编译一个顶点着色器
*/
GLuint createVertexShader()
{
	GLuint vertextShaderId;
	vertextShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertextShaderId, 1, &vertexShaderSource, NULL);
	glCompileShader(vertextShaderId);

	GLint success;
	GLchar infoLog[512];
	//获取Shader是否编译成功了
	glGetShaderiv(vertextShaderId, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(vertextShaderId, 512, NULL, infoLog);
	if (!success)
	{
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return NULL;
	}
	else
		return vertextShaderId;
}
/*
创建一个片段着色器
*/
GLuint createFragmentShader()
{
	GLuint fragmentShaderId;
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderId);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
	if (!success)
	{
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return NULL;
	}
	else
		return fragmentShaderId;


}
/*
创建链接程序
*/
GLuint createProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
{
	GLuint shaderProgramId;
	shaderProgramId = glCreateProgram();
	glAttachShader(shaderProgramId, vertexShaderId);
	glAttachShader(shaderProgramId, fragmentShaderId);
	glLinkProgram(shaderProgramId);

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
	if (!success)
	{
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return NULL;
	}
	else
	{
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
		return shaderProgramId;
	}


}
//void key_callBack(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	std::cout << key + "scanCode:" << std::endl;
//	if (key == GLFW_KEY_ESCAPE&&action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//	if (key == GLFW_KEY_ENTER&&action == GLFW_PRESS)
//	{
//
//
//	}
//}

