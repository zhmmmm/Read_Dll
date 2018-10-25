#include "OpenGL_Class.h"

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

CVerctor2D Spot_0 = CVerctor2D(0.0f,0.0f);
CVerctor2D Spot_1 = CVerctor2D(-297.0f,247.0f);

CVerctor2D MySpot = CVerctor2D(0.0f,0.0f);

int State = 0;

void FuncDir()
{
	if (State == 0)
	{
		CVerctor2D Dir = (Spot_1 - Spot_0).Nomalized();
		CVerctor2D TempDir = Dir * 0.05f;
		Spot_0 += TempDir;
		if (Spot_0.m_x <= Spot_1.m_x && Spot_0.m_y <= Spot_1.m_y)
		{
			State = 1;
		}
	}
}

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

	FuncDir();

	glBegin(GL_POLYGON);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(Spot_0.m_x, Spot_0.m_y);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(Spot_1.m_x, Spot_1.m_y);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(MySpot.m_x, MySpot.m_y);


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
	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);//��������ͶӰ
	//gluOrtho2D(0, width, 0, height); //��������ͶӰ
}

void OrdinaryKeyDown(unsigned char key, int x, int y)
{
	cout << "�㰴����:" << key << " , " << (int)key << endl;
}
void SpecialKeyDown(int key, int x, int y)
{
	cout << "�㰴����:" << key << endl;
	//GLUT_KEY_DOWN
}
void OrdinaryKeyUp(unsigned char key, int x, int y)
{
	cout << "��ſ���:" << key << " , " << (int)key << endl;
}
void SpecialKeyUp(int key, int x, int y)
{
	cout << "��ſ���:" << key << endl;
	//GLUT_KEY_DOWN
}
void Mouse_Down(int Button,int State,int Mouse_X,int Mouse_Y)
{
	std::cout << Button << " " << State <<" "<< Mouse_X<<" " << Mouse_Y << std::endl;
	MySpot.m_x = Mouse_X - 300;
	MySpot.m_y = -(Mouse_Y - 250);
}
void Mouse_Move(int Mouse_X, int Mouse_Y)
{
	std::cout << "����ƶ���" << Mouse_X << " " << Mouse_Y << std::endl;
	MySpot.m_x = Mouse_X - 300;
	MySpot.m_y = -(Mouse_Y - 250);
}
void Mouse_Passive(int Mouse_X, int Mouse_Y)
{
	std::cout << "�����ק��" << Mouse_X << " " << Mouse_Y << std::endl;
	MySpot.m_x = Mouse_X - 300;
	MySpot.m_y = -(Mouse_Y - 250);
}
void Timer(int ID)
{
	if (ID == 10086)
	{
		std::cout << "10086" << std::endl;
		//glutTimerFunc(2000, Timer, 10086);
	}
}
void Indle()
{
	//system("cls");
	//static int Time = 0;
	glutPostRedisplay();//Ͷ�����»��Ƶ���Ϣ
	//Time++;
	//std::cout << Time << std::endl;
}
int main(int argc, char **argv)
{
	OpenGL Obj;

	Obj.Init(&argc, argv);
	Obj.InitMode(GLUT_SINGLE | GLUT_RGBA);
	Obj.InitWinPos(200, 200);
	Obj.InitWindSize(600, 500);
	Obj.CreateWindows("OpenGL����");
	Obj.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Obj.SerDrawCallback(Display);
	Obj.WindSizeOractivation_Reshape(ReShape);

	//Obj.OrdinaryKeyDown(OrdinaryKeyDown);
	//Obj.OrdinaryKeyUp(OrdinaryKeyUp);
	//Obj.SpecialKeyDown(SpecialKeyDown);
	//Obj.SpecialKeyUp(SpecialKeyUp);

	Obj.MouseDown(Mouse_Down);
	Obj.MosueMove(Mouse_Move);
	Obj.MousePassive(Mouse_Passive);



	Obj.WindIdle(Indle);
	Obj.MainWindLoop();
	system("pause");
	return 0;
}