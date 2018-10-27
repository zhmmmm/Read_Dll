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

int g_Width = 600;
int g_Height = 500;
struct STBMPINFO
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	unsigned char *ColorData;
};

float g_Angle = 0;
bool LoadBmp(const char *FileName, STBMPINFO &Pic)
{
	if (!FileName) { return false; }
	FILE *pf = NULL;
	fopen_s(&pf,FileName,"rb");
	if (pf)
	{
		fread(&Pic.bf,sizeof(Pic.bf),1,pf);
		if (Pic.bf.bfType != 0x4d42) { return false; }
		fread(&Pic.bi, sizeof(Pic.bi), 1, pf);
		if (Pic.bi.biBitCount != 24) { return false; }

		Pic.ColorData = new unsigned char[Pic.bi.biSizeImage];
		fread(Pic.ColorData,1,Pic.bi.biSizeImage,pf);
		fclose(pf);
		pf = NULL;
		return true;
	}
	return false;
}
void CreateDrawList()
{
	glGenLists(1);
	glNewList(1, GL_COMPILE);
	{
		glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(100.0f,100.0f);
		glEnd();
	}
	glEndList();
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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(g_Angle++,0,0,1);
	glCallList(1);


	glutSwapBuffers();
	
}
//������Ǹı��Ĵ��ڴ�С�Ŀ��
void ReShape(int width, int height)
{
	//���õ�ǰ�����ľ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//��ͶӰ����λ��
	glViewport(0, 0, width, height);//Ҫ�������ڵĿ��
	//gluPerspective();//����͸��ͶӰ
	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);//��������ͶӰ
	//gluOrtho2D(0, width, 0, height); //��������ͶӰ
}
void Indle()
{
	float StartTime = GetTickCount();
	//system("cls");
	static float LastTime = 0;
	if (StartTime - LastTime >= 60.0f)
	{
		glutPostRedisplay();//Ͷ�����»��Ƶ���Ϣ
		LastTime = StartTime;
	}
}
void OrdinaryKeyDown(unsigned char Key, int Mouse_X, int Mouse_Y)
{
	if (Key == 13) { exit(0); }
}
int main(int argc, char **argv)
{
	OpenGL Obj;
	Obj.Init(&argc, argv);
	Obj.InitMode(GLUT_DOUBLE | GLUT_RGBA);
	Obj.InitWinPos(100, 100);
	Obj.InitWindSize(g_Width, g_Height);
	Obj.CreateWindows("OpenGL����");
	Obj.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Obj.SerDrawCallback(Display);
	Obj.WindSizeOractivation_Reshape(ReShape);


	CreateDrawList();


	Obj.OrdinaryKeyDown(OrdinaryKeyDown);
	Obj.WindIdle(Indle);
	Obj.MainWindLoop();
	system("pause");
	return 0;
}