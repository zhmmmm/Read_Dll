#include "OpenGL_Class.h"
#include "CMyBass.h"

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
int Buf[595] = { 0 };
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

	glBegin(GL_LINES);

	glColor3f(0.0f,1.0f,0.0f);
	for (int i = 0; i < 595; i++)
	{
		glVertex2f(5.0f + i * 5,((Buf[i] % 400) % 250) + 250);
		glVertex2f(5.0f + i * 5, 250.0f);
	}
	glEnd();
	glBegin(GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < 595; i++)
	{
		glVertex2f(5.0f + i * 5, 250.0f);
		glVertex2f(5.0f + i * 5, ((Buf[i] % 400) % 250));
	}
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
	//gluOrtho2D(0, width, 0, height); //��������ͶӰ
	gluOrtho2D(0, width,0, height );//��������ͶӰ
}
void Indle()
{
	int StartTime = GetTickCount();
	system("cls");
	static int LastTime = 0;
	if (StartTime - LastTime >= 60.0f)
	{
		glutPostRedisplay();//Ͷ�����»��Ƶ���Ϣ
		LastTime = StartTime;
	}
	GOMUSIC->GetData("China-X.mp3", Buf);
}
void OrdinaryKeyDown(unsigned char Key,int Mouse_X,int Mouse_Y)
{
	if (Key == 13) { exit(0); }
}
int main(int argc, char **argv)
{
	OpenGL Obj;
	Obj.Init(&argc, argv);
	Obj.InitMode(GLUT_SINGLE | GLUT_RGBA);
	Obj.InitWinPos(100, 100);
	Obj.InitWindSize(600, 500);
	Obj.CreateWindows("OpenGL����");
	Obj.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Obj.SerDrawCallback(Display);
	Obj.WindSizeOractivation_Reshape(ReShape);
	Obj.OrdinaryKeyDown(OrdinaryKeyDown);

	GOMUSIC->Init();
	GOMUSIC->LoadMusic("China-X.mp3");
	GOMUSIC->PlayMusic("China-X.mp3");



	Obj.WindIdle(Indle);
	Obj.MainWindLoop();
	system("pause");
	return 0;
}