#pragma once
#include <iostream>
#include <Windows.h>
#include <Gl/glew.h>//OpenGL的头文件
#include <Gl/glut.h>//创建OpenGL窗口相关函数的头文件
#include "CVerctor2D.h"
#include "CMatrix3.h"

class OpenGL
{
public:
	//初始化_glut库
	void Init(int *argc, char **argv);
	//初始化_OpenGL的显示模式
	void InitMode(unsigned int Define);
	//初始化_设置窗口客户区相对于桌面左上角的位置
	void InitWinPos(int W, int H);
	//初始化_设置窗口的像素宽高(也就是客户区的宽高)
	void InitWindSize(int Size_W, int Size_H);
	//初始化_创建窗口，填写窗口标题栏的文字
	void CreateWindows(const char *WindName);
	//初始化_设置的用于清除上一次绘制的颜色数据的颜色（相当于背景颜色）
	void ClearColor(float R, float G, float B, float Alpha);
	//=======================================================
	//初始化_设置绘制回调函数
	void SerDrawCallback(void(*Func)());
	//初始化_当窗口大小和激活状态改变的时候会调用的函数
	void WindSizeOractivation_Reshape(void(*Func)(int Width, int Height));

	//普通键盘回调函数
	void OrdinaryKeyDown(void(*KeyDown)(unsigned char Key, int Mouse_X, int Mouse_Y));
	void OrdinaryKeyUp(void(*KeyUp)(unsigned char Key, int Mouse_X, int Mouse_Y));
	//功能键回调函数
	void SpecialKeyDown(void(*KeyDown)(int Key, int Mouse_X, int Mouse_Y));
	void SpecialKeyUp(void(*KeyUp)(int Key, int Mouse_X, int Mouse_Y));
	//鼠标回调函数
	//鼠标按下/抬起
	void MouseDown(void(*Mouse_Down)(int Button, int State, int Mouse_X, int Mouse_Y));
	//鼠标滑动
	void MosueMove(void(*Mouse_Move)(int Mouse_X, int Mouse_Y));
	//鼠标拖拽
	void MousePassive(void(*Mouse_Passive)(int Mouse_X, int Mouse_Y));
	//计时器
	void Timer_(unsigned int Millis, void(*Timer)(int Value), int Value);
	//窗口处于空闲的时候调用
	void WindIdle(void(*Indle)());
	//=====================================
	//初始化_窗口循环
	void MainWindLoop();
};