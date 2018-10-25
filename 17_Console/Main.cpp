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

	FuncDir();

	glBegin(GL_POLYGON);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(Spot_0.m_x, Spot_0.m_y);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(Spot_1.m_x, Spot_1.m_y);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(MySpot.m_x, MySpot.m_y);


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
	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);//设置正交投影
	//gluOrtho2D(0, width, 0, height); //设置正交投影
}

void OrdinaryKeyDown(unsigned char key, int x, int y)
{
	cout << "你按下了:" << key << " , " << (int)key << endl;
}
void SpecialKeyDown(int key, int x, int y)
{
	cout << "你按下了:" << key << endl;
	//GLUT_KEY_DOWN
}
void OrdinaryKeyUp(unsigned char key, int x, int y)
{
	cout << "你放开了:" << key << " , " << (int)key << endl;
}
void SpecialKeyUp(int key, int x, int y)
{
	cout << "你放开了:" << key << endl;
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
	std::cout << "鼠标移动：" << Mouse_X << " " << Mouse_Y << std::endl;
	MySpot.m_x = Mouse_X - 300;
	MySpot.m_y = -(Mouse_Y - 250);
}
void Mouse_Passive(int Mouse_X, int Mouse_Y)
{
	std::cout << "鼠标拖拽：" << Mouse_X << " " << Mouse_Y << std::endl;
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
	glutPostRedisplay();//投递重新绘制的消息
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