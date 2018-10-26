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
	//调用设置的颜色来清除上一次的颜色数据
	glClear(GL_COLOR_BUFFER_BIT);
	//中间的就是用于绘制的部分在此书写代码
	//OpenGL的一些基本图元类型
	//GL_POINTS				点(一个顶点)
	//GL_LINES				线段(2个顶点)
	//GL_LINE_LOOP			封闭线段//会首尾相连
	//GL_LINE_STRIP			连接线段
	//GL_TRIANGLES			三角形（3个顶点）
	//GL_TRIANGLE_STRIP		连接三角形
	//GL_TRIANGLE_FAN		三角形扇？
	//GL_QUADS				凸四边形
	//GL_QUAD_STRIP			连接凸四边形
	//GL_POLYGON			多边形（>=3个顶点）

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
			//反射 = （投影 = 投影两倍- 投影）,得到反射的向量
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
	//把缓冲中的数据写出
	glFlush();
}
//传入的是改变后的窗口大小的宽高
void ReShape(int width, int height)
{
	//设置当前操作的矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//将投影矩阵单位化
	glViewport(0, 0, width, height);
	//gluPerspective();//设置透视投影
	//gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);//设置正交投影
	gluOrtho2D(0, width, 0, height); //设置正交投影
}
void Mouse_Down(int Button, int State, int Mouse_X, int Mouse_Y)
{
	std::cout << Button << " " << State << " " << Mouse_X << " " << Mouse_Y << std::endl;
	MySpot.m_x = Mouse_X;
	MySpot.m_y = 500 - Mouse_Y;
}
void Mouse_Move(int Mouse_X, int Mouse_Y)
{
	std::cout << "鼠标移动：" << Mouse_X << " " << Mouse_Y << std::endl;
	MySpot.m_x = Mouse_X;
	MySpot.m_y = 500 - Mouse_Y;
}
void Mouse_Passive(int Mouse_X, int Mouse_Y)
{
	std::cout << "鼠标拖拽：" << Mouse_X << " " << Mouse_Y << std::endl;
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
		glutPostRedisplay();//投递重新绘制的消息
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
	Obj.CreateWindows("OpenGL程序");
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