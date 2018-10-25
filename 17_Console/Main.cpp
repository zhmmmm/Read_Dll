#include <iostream>
#include <Windows.h>
#include <Gl/glew.h>//OpenGL的头文件
#include <Gl/glut.h>//创建OpenGL窗口相关函数的头文件

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

void Keyboard(unsigned char key, int x, int y)
{
	cout << "你按下了:" << key << " , " << (int)key << endl;
}
void Special(int key, int x, int y)
{
	cout << "你按下了:" << key << endl;
	//GLUT_KEY_DOWN
}
void KeyboardUp(unsigned char key, int x, int y)
{
	cout << "你放开了:" << key << " , " << (int)key << endl;
}
void SpecialUp(int key, int x, int y)
{
	cout << "你放开了:" << key << endl;
	//GLUT_KEY_DOWN
}

class InitOpenGL
{
public:
	//初始化_glut库
	void Init(int *argc, char **argv)
	{
		glutInit(argc, argv);
	}
	//初始化_OpenGL的显示模式
	void InitMode(unsigned int Define)
	{
		glutInitDisplayMode(Define);
	}
	//初始化_设置窗口客户区相对于桌面左上角的位置
	void InitWinPos(int W, int H)
	{
		glutInitWindowPosition(W, H);
	}
	//初始化_设置窗口的像素宽高(也就是客户区的宽高)
	void InitWindSize(int Size_W, int Size_H)
	{
		glutInitWindowSize(Size_W, Size_H);
	}
	//初始化_创建窗口，填写窗口标题栏的文字
	void CreateWindows(const char *WindName)
	{
		glutCreateWindow(WindName);
	}
	//初始化_设置的用于清除上一次绘制的颜色数据的颜色（相当于背景颜色）
	void ClearColor(float R, float G, float B, float Alpha)//Alpha 为透明度
	{
		glClearColor(R, G, B, Alpha);
	}

	//初始化_设置绘制回调函数
	void SerDrawCallback(void (*Func))
	{
		glutDisplayFunc(Display);
	}
	//初始化_当窗口大小和激活状态改变的时候会调用的函数
	void WindSizeOractivation_Reshape(void (*Func)(int Width,int Height))
	{
		glutReshapeFunc(Func);
	}

	//普通键盘回调函数
	void OrdinaryKeyDown(void (*KeyDown)(unsigned char Key,int Mouse_X,int Mouse_Y))
	{
		glutKeyboardFunc(KeyDown);
	}
	void OrdinaryKeyUp(void(*KeyUp)(unsigned char Key, int Mouse_X, int Mouse_Y))
	{
		glutKeyboardUpFunc(KeyUp);
	}
	//功能键回调函数
	void SpecialKeyDown(void(*KeyDown)(int Key, int Mouse_X, int Mouse_Y))
	{
		glutSpecialFunc(KeyDown);

	}
	void SpecialKeyUp(void(*KeyUp)(int Key, int Mouse_X, int Mouse_Y))
	{
		glutSpecialUpFunc(KeyUp);
	}


	//初始化_窗口循环
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
	Obj.CreateWindows("OpenGL程序");
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