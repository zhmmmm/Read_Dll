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

	glBegin(GL_TRIANGLES);

	glColor3f(1.0f,0.0f,0.0f);
	glVertex2d(0.0f,0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2d(0.5f,0.5f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2d(-0.5f, 0.5f);

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
	glViewport(0, 0, width/2, height);
	//gluPerspective();//设置透视投影
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);//设置正交投影
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
	//初始化glut库
	void Init(int *argc, char **argv)
	{
		glutInit(argc, argv);
	}
	//初始化OpenGL的显示模式
	void InitMode(unsigned int Define)
	{
		glutInitDisplayMode(Define);
	}
	//设置窗口客户区相对于桌面左上角的位置
	void InitWinPos(int W, int H)
	{
		glutInitWindowPosition(W, H);
	}
	//设置窗口的像素宽高(也就是客户区的宽高)
	void InitWindSize(int Size_W, int Size_H)
	{
		glutInitWindowSize(Size_W, Size_H);
	}
	//创建窗口，填写窗口标题栏的文字
	void CreateWindows(const char *WindName)
	{
		glutCreateWindow(WindName);
	}
	//设置的用于清除上一次绘制的颜色数据的颜色（相当于背景颜色）
	void ClearColor(float R, float G, float B, float Alpha)
	{
		glClearColor(R, G, B, Alpha);
	}
};

//位图头文件14
struct SIZEOF1
{
	WORD buf_int; //记录文件类型 0x4d42
	DWORD buf_size; //记录位图文件的大小
	//WORD k1; //保留的，填0
	//WORD k2; //保留的，填0
	//WORD buf_bit; //颜色数据和文件头的偏移字节数
}IMAGE0;
//位图信息头40
struct SIZEOF2
{
	//DWORD bisize; //存自身结构体的总字节
	LONG biWidth; //像素的宽
	LONG biHeight; //像素的高
	//WORD biweizhi1; //24位图填1
	WORD biSHENDU; //位深度 填0x18
	//DWORD biyasuo; //有没有被压缩，没有填0
	DWORD bisizeimage; //图片的总字节数
	//LONG k3; //0默认
	//LONG k4; //0默认
	//DWORD k5; //有多少颜色被使用0
	 //DWORD k6;//有多少重要的颜色0
}IMAGE_MAX;

int main(int argc, char **argv)
{

	InitOpenGL Obj;

	Obj.Init(&argc, argv);
	Obj.InitMode(GLUT_SINGLE | GLUT_RGBA);
	Obj.InitWinPos(314, 50);
	Obj.InitWindSize(640, 480);
	Obj.CreateWindows("OpenGL程序");
	Obj.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//设置OpenGL绘制回调函数
	glutDisplayFunc(Display);

	//当窗口大小和激活状态改变的时候会调用的函数
	glutReshapeFunc(ReShape);

	//普通键盘回调函数
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	//功能键回调函数
	glutSpecialFunc(Special);
	glutSpecialUpFunc(SpecialUp);

	//glut窗口循环
	glutMainLoop();

	//FILE *pf = NULL;
	//fopen_s(&pf, "satan.bmp", "rb");
	//if (pf)
	//{
	//	//取一波文件的大小
	//	int max = 0;
	//	fseek(pf, 0, SEEK_END); //文件末尾
	//	max = ftell(pf); //大小取出赋值
	//	rewind(pf); //重新把文件指向开始
	//	//判断前两个字节是不是0x4d42
	//	fread(&IMAGE0.buf_int, 2, 1, pf); //读前两个字节
	//	if (IMAGE0.buf_int != 0x4d42) //如果类型不一样
	//	{
	//		std::cout << "文件不是位图文件" << std::endl;
	//		fclose(pf);
	//		system("pause");
	//		return 0;
	//	}
	//	//取文件的大小
	//	fread(&IMAGE0.buf_size, 4, 1, pf);
	//	if (IMAGE0.buf_size != max) //如果大下不一样
	//	{
	//		std::cout << "文件可能损坏！" << std::endl;
	//		fclose(pf);
	//		system("pause");
	//		return 0;
	//	}
	//	//分配位图的存储空间
	//	unsigned char *bmp = new unsigned char[max];
	//	rewind(pf); //重新指向开头
	//	fread(bmp, 1, max, pf); //二进制信息考到bmp里
	//	fclose(pf); //关闭文件
	//	//图片的宽高
	//	IMAGE_MAX.biWidth = *((int*)(bmp + 18)); //位图的宽
	//	IMAGE_MAX.biHeight = *((int*)(bmp + 22)); //位图的高
	//	//位图的深度
	//	IMAGE_MAX.biSHENDU = *((WORD*)(bmp + 28)); //位图的深度
	//	if (IMAGE_MAX.biSHENDU != 24)
	//	{
	//		std::cout << "不是24位位图！" << std::endl;
	//		delete[] bmp;
	//		bmp = NULL;
	//		system("pause");
	//		return 0;
	//	}
	//	//位图颜色的数据
	//	IMAGE_MAX.bisizeimage = *((DWORD*)(bmp + 34)); //存储颜色数据的四个字节
	//	int i = IMAGE_MAX.bisizeimage / IMAGE_MAX.biHeight; //一行的字节数
	//	for (int j = IMAGE_MAX.biHeight - 1; j >= 0; j--)
	//	{
	//		unsigned char *Hcolor = bmp + 54 + j * i;
	//		for (int k = 0; k < IMAGE_MAX.biWidth; k++)
	//		{
	//			unsigned char *Wcolor = Hcolor + k * 3;
	//			//注意次数 决定像素的宽和高这么多次
	//			Wcolor[0] = Wcolor[1]; //R
	//			Wcolor[1] = Wcolor[1]; //G
	//			Wcolor[2] = Wcolor[1]; //B
	//		}
	//	}
	//	delete[] bmp;
	//	bmp = NULL;
	//}


	//system("pause");
	return 0;
}