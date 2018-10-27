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
	//gluOrtho2D(0, width, 0, height); //设置正交投影
	gluOrtho2D(0, width,0, height );//设置正交投影
}
void Indle()
{
	int StartTime = GetTickCount();
	system("cls");
	static int LastTime = 0;
	if (StartTime - LastTime >= 60.0f)
	{
		glutPostRedisplay();//投递重新绘制的消息
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
	Obj.CreateWindows("OpenGL程序");
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