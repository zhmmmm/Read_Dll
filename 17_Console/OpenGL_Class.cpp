#include "OpenGL_Class.h"

//��ʼ��_glut��
void OpenGL::Init(int *argc, char **argv)
{
	glutInit(argc, argv);
}
//��ʼ��_OpenGL����ʾģʽ
void OpenGL::InitMode(unsigned int Define)
{
	glutInitDisplayMode(Define);
}
//��ʼ��_���ô��ڿͻ���������������Ͻǵ�λ��
void OpenGL::InitWinPos(int W, int H)
{
	glutInitWindowPosition(W, H);
}
//��ʼ��_���ô��ڵ����ؿ��(Ҳ���ǿͻ����Ŀ��)
void OpenGL::InitWindSize(int Size_W, int Size_H)
{
	glutInitWindowSize(Size_W, Size_H);
}
//��ʼ��_�������ڣ���д���ڱ�����������
void OpenGL::CreateWindows(const char *WindName)
{
	glutCreateWindow(WindName);
}
//��ʼ��_���õ����������һ�λ��Ƶ���ɫ���ݵ���ɫ���൱�ڱ�����ɫ��
void OpenGL::ClearColor(float R, float G, float B, float Alpha)//Alpha Ϊ͸����
{
	glClearColor(R, G, B, Alpha);
}
//=======================================================
//��ʼ��_���û��ƻص�����
void OpenGL::SerDrawCallback(void(*Func)())
{
	glutDisplayFunc(Func);
}
//��ʼ��_�����ڴ�С�ͼ���״̬�ı��ʱ�����õĺ���
void OpenGL::WindSizeOractivation_Reshape(void(*Func)(int Width, int Height))
{
	glutReshapeFunc(Func);
}

//��ͨ���̻ص�����
void OpenGL::OrdinaryKeyDown(void(*KeyDown)(unsigned char Key, int Mouse_X, int Mouse_Y))
{
	glutKeyboardFunc(KeyDown);
}
void OpenGL::OrdinaryKeyUp(void(*KeyUp)(unsigned char Key, int Mouse_X, int Mouse_Y))
{
	glutKeyboardUpFunc(KeyUp);
}
//���ܼ��ص�����
void OpenGL::SpecialKeyDown(void(*KeyDown)(int Key, int Mouse_X, int Mouse_Y))
{
	glutSpecialFunc(KeyDown);

}
void OpenGL::SpecialKeyUp(void(*KeyUp)(int Key, int Mouse_X, int Mouse_Y))
{
	glutSpecialUpFunc(KeyUp);
}
//���ص�����
//��갴��/̧��
void OpenGL::MouseDown(void(*Mouse_Down)(int Button, int State, int Mouse_X, int Mouse_Y))
{
	//Button:
	//0 ������
	//1 ����м�
	//2 ����Ҽ�
	//3 ��������ǰ
	//4 ���������
	//State:0 ����,1 ̧��
	glutMouseFunc(Mouse_Down);
}
//��껬��
void OpenGL::MosueMove(void(*Mouse_Move)(int Mouse_X, int Mouse_Y))
{
	glutPassiveMotionFunc(Mouse_Move);
}
//�����ק
void OpenGL::MousePassive(void(*Mouse_Passive)(int Mouse_X, int Mouse_Y))
{
	glutMotionFunc(Mouse_Passive);
}
//��ʱ��
void OpenGL::Timer_(unsigned int Millis, void(*Timer)(int Value), int Value)
{
	//���ٺ�����ú�����ֻ����һ��
	glutTimerFunc(2000, Timer, Value);
}
//���ڴ��ڿ��е�ʱ�����
void OpenGL::WindIdle(void(*Indle)())
{
	glutIdleFunc(Indle);
}

//=====================================
//��ʼ��_����ѭ��
void OpenGL::MainWindLoop()
{
	glutMainLoop();
}