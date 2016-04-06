#pragma once
#include<GL\glew.h>
class TrianglePractice
{
public:
	TrianglePractice();
	~TrianglePractice();
	GLuint createVertexShader();
	GLuint createRedFragmentShader();
	GLuint createYellowFragmentShader();
	GLint  createYellowBindProgram();
	/*
	创建与红色片段Shader相关的Program
	*/
	GLint createRedBindProgram();
private:
	const GLchar* vertextShaderSource;
	const GLchar*  yellowFragmentShaderSource;
	const GLchar*  redFragmentShaderSource;
	GLint vertextShaderId;
	GLint redFragmentShaderId;
	GLint yellowFragmentShaderId;
	GLint redProgramId;
	GLint yellowProgramId;
	 
};

