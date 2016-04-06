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
//	//�������и���GLFW����Ҫʹ�õ���OPENGL 3.3 �汾
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//
//	//��ʾ����ʹ�ú���ģʽ������ʹ�ü���ģʽ,ʹ�ú���ģʽЧ�ʸ���,������һЩ��������֧��
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	//��ʾ����Ӧ�ò��ܱ����óɴ�С
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//
//	//����ָ���Ĵ���
//	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL", nullptr, nullptr);
//	if (window == nullptr)
//	{
//		glfwTerminate();
//	}
//
//
//	glfwMakeContextCurrent(window);
//	glewExperimental = GL_TRUE;//��ʾGLEW�Ƿ�ʹ��һЩʵ�����ʵĹ���,������ó�false�����ں���ģʽ�´�������
//	if (glewInit() != GLEW_OK)
//	{
//		return -1;
//	}
//	glViewport(0, 0, 800, 600);
//
//
//
//
//	//���ü��̰���ʱ�Ļص�����
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
//	//�������κ������÷ֱ�Ϊ���ɶ��㻺�����Id,�����������Id�Լ���������
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//	glGenVertexArrays(1, &VAO);
//
//	//����Ϊ�󶨶�������,��VAO��VBO,EBO֮�佨������,EBO��ֻ����VBO�е�����
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);//����һ�����㻺�����,������󶨵�VBO Id��
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//���û�����������,��ʵ������Ǹ�IDΪ VBO�Ļ����������ֵ
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//
//
//	//���ø÷�������OpenGL��ν��������ṩ�Ķ������
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	//��ͣ���жϴ����Ƿ��Ѿ��˳���
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
//		//�������,���̵��豸���¼�
//		glfwPollEvents();
//		//����������
//		glfwSwapBuffers(window);
//	}
//
//	glfwTerminate();//�ڴ��ڱ��رպ�,�ͷ����е���Դ
//	return 0;
//}

/*
����һ��������ɫ��
*/
GLuint createVertexShader()
{
	GLuint vertextShaderId;
	vertextShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertextShaderId, 1, &vertexShaderSource, NULL);
	glCompileShader(vertextShaderId);

	GLint success;
	GLchar infoLog[512];
	//��ȡShader�Ƿ����ɹ���
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
����һ��Ƭ����ɫ��
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
�������ӳ���
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

