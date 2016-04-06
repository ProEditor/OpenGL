#include "TrianglePractice.h"
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
第一章绘制三角形中的练习
*/
TrianglePractice::TrianglePractice()
{
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	vertextShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 color;\n"
		"layout (location = 2) in vec2 texCoord;\n"
		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 transform;\n"
		"void main()\n"
		"{\n"
		"gl_Position = transform*vec4(position.x, position.y, position.z, 1.0);\n"
		"ourColor=color;\n"
		"TexCoord=vec2(texCoord.x, 1.0 - texCoord.y);\n"
		"}\0";
	yellowFragmentShaderSource = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"in vec2 TexCoord;\n"
		"out vec4 color;\n"
		"uniform sampler2D ourTexture1;\n"
		"uniform sampler2D ourTexture2;\n"
		"void main()\n"
		"{\n"
		"color = texture(ourTexture1, TexCoord);\n"
		"}\n\0";
	redFragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"in vec4 outColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D ourTexture;\n"
		"void main()\n"
		"{\n"
		"color =texture(ourTexture,TexCoord);\n"
		"}\n\0";

	//GLfloat vertices[] = {
	//	-0.5,0.5,0, 1.0f, 0.0f, 0.0f,
	//	-1,0,0, 0.0f, 1.0f, 0.0f,
	//	0,0,0,0.0f, 0.0f, 1.0f,
	//	0,0.5,0,1.0f, 0.0f, 0.0f,
	//	-0.5,-0.5,0, 0.0f, 1.0f, 0.0f,
	//	0.5,-0.5,0,0.0f, 1.0f
	//};

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
	};
	GLfloat vertices1[] = {
		-1.0f,1.0f,0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		 -0.5f, 1.0f,0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, 0,0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-1.0f,0,0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f };

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	GLuint indices1[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};


	//定义对纹理图片那部分进行采样
	GLfloat texCoords[] = {
		0.0f, 0.0f, // 左下角
		1.0f, 0.0f, // 右下角
		0.5f, 1.0f // 顶部位置
	};




	GLFWwindow *window = glfwCreateWindow(800, 600, "TrianglePractice", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "create window failed" << std::endl;
		return;
	}
	else
	{
		glViewport(0, 0, 800, 600);
		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		glewInit();


		vertextShaderId = createVertexShader();
		yellowFragmentShaderId = createYellowFragmentShader();
		redFragmentShaderId = createRedFragmentShader();
		yellowProgramId = createYellowBindProgram();
		redProgramId = createRedBindProgram();

		GLuint VAO, VBO, EBO;
		//GLuint VAO, VBO, VAO2;
		glGenVertexArrays(1, &VAO);


		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);


		glBindVertexArray(VAO);
		//以下操作都是针对顶点VAO的绑定

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);


		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);


		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);


		//解绑VAO
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		GLuint VAO1, VBO1, EBO1;
		glGenVertexArrays(1, &VAO1);
		glBindVertexArray(VAO1);
		glGenBuffers(1, &VBO1);
		glGenBuffers(1, &EBO1);

		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);


		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);




		int width;
		int height;
		unsigned char*  image = SOIL_load_image("C:\\Users\\ProEditor\\Desktop\\texture.png", &width, &height, 0, SOIL_LOAD_RGB);
		GLuint texture;
		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);


		GLuint texture1;
		int width1;
		int height2;
		glActiveTexture(GL_TEXTURE1);
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		unsigned char*  image1 = SOIL_load_image("C:\\Users\\ProEditor\\Desktop\\texture2.jpg", &width1, &height2, 0, SOIL_LOAD_RGB);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image1);
		glBindTexture(GL_TEXTURE_2D, 0);



		while (glfwWindowShouldClose(window) == false)
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(yellowProgramId);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture1);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);


			glBindVertexArray(VAO1);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			GLfloat time = (GLfloat)glfwGetTime();
			glm::mat4 trans;
			//trans = glm::rotate(trans, time*50.0f, glm::vec3(0.0f, 0.0f, 1.0f));




			GLint transformLocation = glGetUniformLocation(yellowProgramId, "transform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(trans));




			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		glfwTerminate();
	}

}


TrianglePractice::~TrianglePractice()
{

}

GLuint TrianglePractice::createVertexShader()
{
	//先创建一个Shader
	//设置Shader的源码
	//编译Shader的源码
	//状态判断,判断是否成功编译了Shader的源码

	GLuint vertextShaderId;
	vertextShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertextShaderId, 1, &vertextShaderSource, NULL);
	glCompileShader(vertextShaderId);

	GLint success;
	GLchar loginfo[512];
	glGetShaderiv(vertextShaderId, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(vertextShaderId, 512, NULL, loginfo);
	if (success == GL_FALSE)
	{
		std::cout << "create vertext shader failed,reason is " << loginfo;
	}
	vertextShaderSource = "";
	return vertextShaderId;
}
GLuint TrianglePractice::createYellowFragmentShader()
{
	GLint fragmentShaderId;
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &yellowFragmentShaderSource, NULL);
	glCompileShader(fragmentShaderId);

	GLint success;
	GLchar loginfo[512];
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, loginfo);
		std::cout << "create yellow fragment shader failed,reason is " << loginfo;
	}
	return fragmentShaderId;
}
GLuint TrianglePractice::createRedFragmentShader()
{
	GLint fragmentShaderId;
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &redFragmentShaderSource, NULL);
	glCompileShader(fragmentShaderId);
	GLint success;
	GLchar loginfo[512];
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, loginfo);
		std::cout << "create red fragment shader failed,reason is " << loginfo;
	}
	return fragmentShaderId;
}
GLint TrianglePractice::createYellowBindProgram()
{
	GLuint fragmentShaderId = createYellowFragmentShader();
	GLint programId = glCreateProgram();
	glAttachShader(programId, vertextShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	GLint success;
	GLchar loginfo[512];

	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetProgramInfoLog(programId, 512, NULL, loginfo);
		std::cout << "create link program  failed,reason is " << loginfo;
	}
	return programId;
}
GLint TrianglePractice::createRedBindProgram()
{
	GLint programId = glCreateProgram();

	glAttachShader(programId, redFragmentShaderId);
	glAttachShader(programId, vertextShaderId);
	glLinkProgram(programId);

	GLint success;
	GLchar loginfo[512];

	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(programId, 512, NULL, loginfo);
	if (success == GL_FALSE)
	{
		glGetProgramInfoLog(programId, 512, NULL, loginfo);
		std::cout << "create link program  failed,reason is " << loginfo;
	}
	return programId;
}



