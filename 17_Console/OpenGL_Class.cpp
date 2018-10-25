#include "OpenGL_Class.h"

//初始化_glut库
void OpenGL::Init(int *argc, char **argv)
{
	glutInit(argc, argv);
}
//初始化_OpenGL的显示模式
void OpenGL::InitMode(unsigned int Define)
{
	glutInitDisplayMode(Define);
}
//初始化_设置窗口客户区相对于桌面左上角的位置
void OpenGL::InitWinPos(int W, int H)
{
	glutInitWindowPosition(W, H);
}
//初始化_设置窗口的像素宽高(也就是客户区的宽高)
void OpenGL::InitWindSize(int Size_W, int Size_H)
{
	glutInitWindowSize(Size_W, Size_H);
}
//初始化_创建窗口，填写窗口标题栏的文字
void OpenGL::CreateWindows(const char *WindName)
{
	glutCreateWindow(WindName);
}
//初始化_设置的用于清除上一次绘制的颜色数据的颜色（相当于背景颜色）
void OpenGL::ClearColor(float R, float G, float B, float Alpha)//Alpha 为透明度
{
	glClearColor(R, G, B, Alpha);
}
//=======================================================
//初始化_设置绘制回调函数
void OpenGL::SerDrawCallback(void(*Func)())
{
	glutDisplayFunc(Func);
}
//初始化_当窗口大小和激活状态改变的时候会调用的函数
void OpenGL::WindSizeOractivation_Reshape(void(*Func)(int Width, int Height))
{
	glutReshapeFunc(Func);
}

//普通键盘回调函数
void OpenGL::OrdinaryKeyDown(void(*KeyDown)(unsigned char Key, int Mouse_X, int Mouse_Y))
{
	glutKeyboardFunc(KeyDown);
}
void OpenGL::OrdinaryKeyUp(void(*KeyUp)(unsigned char Key, int Mouse_X, int Mouse_Y))
{
	glutKeyboardUpFunc(KeyUp);
}
//功能键回调函数
void OpenGL::SpecialKeyDown(void(*KeyDown)(int Key, int Mouse_X, int Mouse_Y))
{
	glutSpecialFunc(KeyDown);

}
void OpenGL::SpecialKeyUp(void(*KeyUp)(int Key, int Mouse_X, int Mouse_Y))
{
	glutSpecialUpFunc(KeyUp);
}
//鼠标回调函数
//鼠标按下/抬起
void OpenGL::MouseDown(void(*Mouse_Down)(int Button, int State, int Mouse_X, int Mouse_Y))
{
	//Button:
	//0 鼠标左键
	//1 鼠标中键
	//2 鼠标右键
	//3 鼠标滚轮向前
	//4 鼠标滚轮向后
	//State:0 按下,1 抬起
	glutMouseFunc(Mouse_Down);
}
//鼠标滑动
void OpenGL::MosueMove(void(*Mouse_Move)(int Mouse_X, int Mouse_Y))
{
	glutPassiveMotionFunc(Mouse_Move);
}
//鼠标拖拽
void OpenGL::MousePassive(void(*Mouse_Passive)(int Mouse_X, int Mouse_Y))
{
	glutMotionFunc(Mouse_Passive);
}
//计时器
void OpenGL::Timer_(unsigned int Millis, void(*Timer)(int Value), int Value)
{
	//多少毫秒调用函数，只调用一次
	glutTimerFunc(2000, Timer, Value);
}
//窗口处于空闲的时候调用
void OpenGL::WindIdle(void(*Indle)())
{
	glutIdleFunc(Indle);
}

//=====================================
//初始化_窗口循环
void OpenGL::MainWindLoop()
{
	glutMainLoop();
}