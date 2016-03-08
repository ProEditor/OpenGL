#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<GL/freeglut.h>

#define  void lineSegment();
void main(int argc, char** argv)
{
	glutInit(&argc, argv);//��ʼ��OpenGL
	glutCreateWindow("��һ��OpenGL����");//����һ������
	glutPositionWindow(50, 10);//���ô��ڵ�λ��
	glutInitWindowSize(800, 600);//�趨���ڵĴ�С
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//ʹ�õ������RGB��ɫģ��

	glClearColor(1.0, 1.0, 1.0, 0);//���ô��ڵı�����ɫΪ��ɫ
	glClear(GL_COLOR_BUFFER_BIT);//

	glMatrixMode(GL_PROJECTION);//ʹ����ͶӰ,Ͷ�����嵽��Ļ��
	gluOrtho2D(0.0, 200, 0.0, 150);//�趨
	glutDisplayFunc(lineSegment);//����һ���ص�����,�˺���ִ�л�ͼ����
	GLenum error;
	error = GetLastError();//��ȡOpenGL����ִ�й������Ƿ���ִ���,������ִ��󽫻᷵�ش������,���û�д����򷵻�GL_NO_ERRORö��ֵ,��Ҫע�����OpenGLÿ��ֻ��¼һ���������,����Ѿ���¼��ĳ���������,�������GetLastError֮ǰ,���������ټ�¼�����ĺ���
	if (errno == GL_NO_ERROR)
	{
		printf("��ִ�л�ͼ����ʱû�г����κδ���");
	}
	const GLubyte *errorCode;
	errorCode = gluErrorString(errno);//���ݴ������,��ȡ��Ӧ�Ĵ�����Ϣ
	printf(errorCode);
	glutMainLoop();//��ɴ��ڴ�������ʾͼ��
}
void lineSegment()
{
	glColor3f(0.0f, 0.4f, 0.2f);//���ô�����ͼԪ����ɫ
	glBegin(GL_LINES);//��ʼ��ͼ,���Ƶ�����Ϊ����
	glVertex2i(180, 15);//��ʼ����
	glVertex2i(10, 145);//��������
	glEnd();//������ͼ
	glFlush();//��ջ���,����ִ�л��ƹ���
}