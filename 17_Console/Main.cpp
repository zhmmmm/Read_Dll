#include "OpenGL_Class.h"
#include "CMyBass.h"

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

struct SPOT
{
	CVerctor2D Spot;
	CVerctor2D dir;
};

SPOT Arr[100];

CVerctor2D MySpot = CVerctor2D(10.0f, 10.0f);

CVerctor2D W = CVerctor2D(0.0f, 1.0f);
CVerctor2D H = CVerctor2D(1.0f, 0.0f);

float Speed = 5.0f;
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

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(MySpot.m_x, MySpot.m_y);
	glColor3f(1.0f, 1.0f, 0.0f);
	for (int i = 0; i < 100; i++)
	{
		CVerctor2D DirTemp = Arr[i].dir * Speed;
		Arr[i].Spot += DirTemp;
		if (Arr[i].Spot.m_x < 0 || Arr[i].Spot.m_x > 600)
		{
			//���� = ��ͶӰ = ͶӰ����- ͶӰ��,�õ����������
			Arr[i].dir.m_x = (Arr[i].dir.Projection(W).m_x * 2.0f) - Arr[i].dir.m_x;
		}
		if (Arr[i].Spot.m_y < 0 || Arr[i].Spot.m_y > 500)
		{
			Arr[i].dir.m_y = (Arr[i].dir.Projection(H).m_y * 2.0f) - Arr[i].dir.m_y;
		}
		glVertex2f(Arr[i].Spot.m_x, Arr[i].Spot.m_y);
	}
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			CVerctor2D Dir(Arr[i].Spot.m_x - Arr[j].Spot.m_x, Arr[i].Spot.m_y - Arr[j].Spot.m_y);
			if (Dir.Length() < 70.0f)
			{
				glColor3f(1.0f, 0.0f, 1.0f);
				glVertex2f(Arr[i].Spot.m_x, Arr[i].Spot.m_y);
				glVertex2f(Arr[j].Spot.m_x, Arr[j].Spot.m_y);
			}
		}
	}
	for (int i = 0; i < 100; i++)
	{
		CVerctor2D Dir(Arr[i].Spot.m_x - MySpot.m_x, Arr[i].Spot.m_y - MySpot.m_y);
		if (Dir.Length() < 70.0f)
		{
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2f(Arr[i].Spot.m_x, Arr[i].Spot.m_y);
			glVertex2f(MySpot.m_x, MySpot.m_y);
		}
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
	gluOrtho2D(0, width, 0, height); //��������ͶӰ
}
void Mouse_Down(int Button, int State, int Mouse_X, int Mouse_Y)
{
	std::cout << Button << " " << State << " " << Mouse_X << " " << Mouse_Y << std::endl;
	MySpot.m_x = Mouse_X;
	MySpot.m_y = 500 - Mouse_Y;
}
void Mouse_Move(int Mouse_X, int Mouse_Y)
{
	std::cout << "����ƶ���" << Mouse_X << " " << Mouse_Y << std::endl;
	MySpot.m_x = Mouse_X;
	MySpot.m_y = 500 - Mouse_Y;
}
void Mouse_Passive(int Mouse_X, int Mouse_Y)
{
	std::cout << "�����ק��" << Mouse_X << " " << Mouse_Y << std::endl;
	MySpot.m_x = Mouse_X;
	MySpot.m_y = 500 - Mouse_Y;
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
	int StartTime = GetTickCount();
	//system("cls");
	static int LastTime = 0;
	if (StartTime - LastTime >= 60.0f)
	{
		glutPostRedisplay();//Ͷ�����»��Ƶ���Ϣ
		LastTime = StartTime;
	}
	//Time++;
	//std::cout << Time << std::endl;
}
int main(int argc, char **argv)
{
	srand(GetTickCount());
	for (int i = 0; i < 100; i++)
	{
		Arr[i].Spot.m_x = rand() % 600;
		Arr[i].Spot.m_y = rand() % 500;
		CVerctor2D Dir;
		Dir.m_x = rand() % 600;
		Dir.m_y = rand() % 500;
		Arr[i].dir = Dir.Nomalize();
	}

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