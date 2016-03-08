#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<GL/freeglut.h>

#define  void lineSegment();
void main(int argc, char** argv)
{
	glutInit(&argc, argv);//初始化OpenGL
	glutCreateWindow("第一个OpenGL程序");//创建一个窗口
	glutPositionWindow(50, 10);//设置窗口的位置
	glutInitWindowSize(800, 600);//设定窗口的大小
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//使用单缓冲和RGB颜色模型

	glClearColor(1.0, 1.0, 1.0, 0);//设置窗口的背景颜色为白色
	glClear(GL_COLOR_BUFFER_BIT);//

	glMatrixMode(GL_PROJECTION);//使用正投影,投射物体到屏幕中
	gluOrtho2D(0.0, 200, 0.0, 150);//设定
	glutDisplayFunc(lineSegment);//传入一个回调函数,此函数执行绘图操作
	GLenum error;
	error = GetLastError();//获取OpenGL中在执行过程中是否出现错误,如果出现错误将会返回错误代码,如果没有错误则返回GL_NO_ERROR枚举值,需要注意的是OpenGL每次只记录一个出错编码,如果已经记录了某个出错编码,在你调用GetLastError之前,它都不会再记录其他的函数
	if (errno == GL_NO_ERROR)
	{
		printf("在执行绘图任务时没有出现任何错误");
	}
	const GLubyte *errorCode;
	errorCode = gluErrorString(errno);//根据错误代码,获取相应的错误信息
	printf(errorCode);
	glutMainLoop();//完成窗口创建并显示图形
}
void lineSegment()
{
	glColor3f(0.0f, 0.4f, 0.2f);//设置窗口中图元的颜色
	glBegin(GL_LINES);//开始绘图,绘制的类型为线条
	glVertex2i(180, 15);//开始坐标
	glVertex2i(10, 145);//结束坐标
	glEnd();//结束绘图
	glFlush();//清空缓冲,立即执行绘制工作
}