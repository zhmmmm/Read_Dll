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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(g_Angle++,0,0,1);
	glCallList(1);


	glutSwapBuffers();
	
}
//传入的是改变后的窗口大小的宽高
void ReShape(int width, int height)
{
	//设置当前操作的矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//将投影矩阵单位化
	glViewport(0, 0, width, height);//要画到窗口的宽高
	//gluPerspective();//设置透视投影
	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);//设置正交投影
	//gluOrtho2D(0, width, 0, height); //设置正交投影
}
void Indle()
{
	float StartTime = GetTickCount();
	//system("cls");
	static float LastTime = 0;
	if (StartTime - LastTime >= 60.0f)
	{
		glutPostRedisplay();//投递重新绘制的消息
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
	Obj.CreateWindows("OpenGL程序");
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