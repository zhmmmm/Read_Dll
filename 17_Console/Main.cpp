#include <iostream>
#include <Windows.h>
#include <Gl/glew.h>//OpenGL��ͷ�ļ�
#include <Gl/glut.h>//����OpenGL������غ�����ͷ�ļ�

using namespace std;
/*
HMODULE hDll = LoadLibraryA("..\\Debug\\ServerDll.dll");
typedef int(*Function)(int, int);
if (hDll)
{
	Function function = (Function)GetProcAddress(hDll,"Function");
	int num = function(10, 20);
	std::cout << "Ok " << num << std::endl;
}
else
{
	return 0;
}
FreeLibrary(hDll);
hDll = NULL;
*/


void Display()
{
	//�������õ���ɫ�������һ�ε���ɫ����
	glClear(GL_COLOR_BUFFER_BIT);
	//�м�ľ������ڻ��ƵĲ����ڴ���д����

	//OpenGL��һЩ����ͼԪ����
	//GL_POINTS				��(һ������)
	//GL_LINES				�߶�(2������)
	//GL_LINE_LOOP			����߶�//����β����
	//GL_LINE_STRIP			�����߶�
	//GL_TRIANGLES			�����Σ�3�����㣩
	//GL_TRIANGLE_STRIP		����������
	//GL_TRIANGLE_FAN		�������ȣ�
	//GL_QUADS				͹�ı���
	//GL_QUAD_STRIP			����͹�ı���
	//GL_POLYGON			����Σ�>=3�����㣩


	glBegin(GL_POINTS);



	glEnd();
	//�ѻ����е�����д��
	glFlush();
}
//������Ǹı��Ĵ��ڴ�С�Ŀ��
void ReShape(int width, int height)
{
	//���õ�ǰ�����ľ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//��ͶӰ����λ��
	glViewport(0, 0, width, height);
	//gluPerspective();//����͸��ͶӰ
	//gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);//��������ͶӰ
	gluOrtho2D(0, width, 0, height); //��������ͶӰ
}

void Keyboard(unsigned char key, int x, int y)
{
	cout << "�㰴����:" << key << " , " << (int)key << endl;
}
void Special(int key, int x, int y)
{
	cout << "�㰴����:" << key << endl;
	//GLUT_KEY_DOWN
}
void KeyboardUp(unsigned char key, int x, int y)
{
	cout << "��ſ���:" << key << " , " << (int)key << endl;
}
void SpecialUp(int key, int x, int y)
{
	cout << "��ſ���:" << key << endl;
	//GLUT_KEY_DOWN
}

class InitOpenGL
{
public:
	//��ʼ��_glut��
	void Init(int *argc, char **argv)
	{
		glutInit(argc, argv);
	}
	//��ʼ��_OpenGL����ʾģʽ
	void InitMode(unsigned int Define)
	{
		glutInitDisplayMode(Define);
	}
	//��ʼ��_���ô��ڿͻ���������������Ͻǵ�λ��
	void InitWinPos(int W, int H)
	{
		glutInitWindowPosition(W, H);
	}
	//��ʼ��_���ô��ڵ����ؿ��(Ҳ���ǿͻ����Ŀ��)
	void InitWindSize(int Size_W, int Size_H)
	{
		glutInitWindowSize(Size_W, Size_H);
	}
	//��ʼ��_�������ڣ���д���ڱ�����������
	void CreateWindows(const char *WindName)
	{
		glutCreateWindow(WindName);
	}
	//��ʼ��_���õ����������һ�λ��Ƶ���ɫ���ݵ���ɫ���൱�ڱ�����ɫ��
	void ClearColor(float R, float G, float B, float Alpha)//Alpha Ϊ͸����
	{
		glClearColor(R, G, B, Alpha);
	}

	//��ʼ��_���û��ƻص�����
	void SerDrawCallback(void (*Func))
	{
		glutDisplayFunc(Display);
	}
	//��ʼ��_�����ڴ�С�ͼ���״̬�ı��ʱ�����õĺ���
	void WindSizeOractivation_Reshape(void (*Func)(int Width,int Height))
	{
		glutReshapeFunc(Func);
	}

	//��ͨ���̻ص�����
	void OrdinaryKeyDown(void (*KeyDown)(unsigned char Key,int Mouse_X,int Mouse_Y))
	{
		glutKeyboardFunc(KeyDown);
	}
	void OrdinaryKeyUp(void(*KeyUp)(unsigned char Key, int Mouse_X, int Mouse_Y))
	{
		glutKeyboardUpFunc(KeyUp);
	}
	//���ܼ��ص�����
	void SpecialKeyDown(void(*KeyDown)(int Key, int Mouse_X, int Mouse_Y))
	{
		glutSpecialFunc(KeyDown);

	}
	void SpecialKeyUp(void(*KeyUp)(int Key, int Mouse_X, int Mouse_Y))
	{
		glutSpecialUpFunc(KeyUp);
	}


	//��ʼ��_����ѭ��
	void MainWindLoop()
	{
		glutMainLoop();
	}
};

int main(int argc, char **argv)
{


	InitOpenGL Obj;

	Obj.Init(&argc, argv);
	Obj.InitMode(GLUT_SINGLE | GLUT_RGBA);
	Obj.InitWinPos(10, 10);
	Obj.InitWindSize(600, 500);
	Obj.CreateWindows("OpenGL����");
	Obj.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Obj.SerDrawCallback(Display);
	Obj.WindSizeOractivation_Reshape(ReShape);

	Obj.OrdinaryKeyDown(Keyboard);
	Obj.OrdinaryKeyUp(KeyboardUp);
	Obj.SpecialKeyDown(Special);
	Obj.SpecialKeyUp(SpecialUp);




	Obj.MainWindLoop();


	system("pause");
	return 0;
}