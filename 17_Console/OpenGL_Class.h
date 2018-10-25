#pragma once
#include <iostream>
#include <Windows.h>
#include <Gl/glew.h>//OpenGL��ͷ�ļ�
#include <Gl/glut.h>//����OpenGL������غ�����ͷ�ļ�
#include "CVerctor2D.h"
#include "CMatrix3.h"

class OpenGL
{
public:
	//��ʼ��_glut��
	void Init(int *argc, char **argv);
	//��ʼ��_OpenGL����ʾģʽ
	void InitMode(unsigned int Define);
	//��ʼ��_���ô��ڿͻ���������������Ͻǵ�λ��
	void InitWinPos(int W, int H);
	//��ʼ��_���ô��ڵ����ؿ��(Ҳ���ǿͻ����Ŀ��)
	void InitWindSize(int Size_W, int Size_H);
	//��ʼ��_�������ڣ���д���ڱ�����������
	void CreateWindows(const char *WindName);
	//��ʼ��_���õ����������һ�λ��Ƶ���ɫ���ݵ���ɫ���൱�ڱ�����ɫ��
	void ClearColor(float R, float G, float B, float Alpha);
	//=======================================================
	//��ʼ��_���û��ƻص�����
	void SerDrawCallback(void(*Func)());
	//��ʼ��_�����ڴ�С�ͼ���״̬�ı��ʱ�����õĺ���
	void WindSizeOractivation_Reshape(void(*Func)(int Width, int Height));

	//��ͨ���̻ص�����
	void OrdinaryKeyDown(void(*KeyDown)(unsigned char Key, int Mouse_X, int Mouse_Y));
	void OrdinaryKeyUp(void(*KeyUp)(unsigned char Key, int Mouse_X, int Mouse_Y));
	//���ܼ��ص�����
	void SpecialKeyDown(void(*KeyDown)(int Key, int Mouse_X, int Mouse_Y));
	void SpecialKeyUp(void(*KeyUp)(int Key, int Mouse_X, int Mouse_Y));
	//���ص�����
	//��갴��/̧��
	void MouseDown(void(*Mouse_Down)(int Button, int State, int Mouse_X, int Mouse_Y));
	//��껬��
	void MosueMove(void(*Mouse_Move)(int Mouse_X, int Mouse_Y));
	//�����ק
	void MousePassive(void(*Mouse_Passive)(int Mouse_X, int Mouse_Y));
	//��ʱ��
	void Timer_(unsigned int Millis, void(*Timer)(int Value), int Value);
	//���ڴ��ڿ��е�ʱ�����
	void WindIdle(void(*Indle)());
	//=====================================
	//��ʼ��_����ѭ��
	void MainWindLoop();
};