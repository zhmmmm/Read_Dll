#include <iostream>
#include <Windows.h>
#include <Gl/glew.h>//OpenGL��ͷ�ļ�
#include <Gl/glut.h>//����OpenGL������غ�����ͷ�ļ�
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

	glBegin(GL_TRIANGLES);

	glColor3f(1.0f,0.0f,0.0f);
	glVertex2d(0.0f,0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2d(0.5f,0.5f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2d(-0.5f, 0.5f);

	glEnd();

	//�ѻ����е�����д��
	glFlush();
}
//������Ǹı��Ĵ��ڴ�С�Ŀ��
void ReShape(int width, int height)
{

	//���õ�ǰ�����ľ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//��ͶӰ����λ��
	glViewport(0, 0, width/2, height);
	//gluPerspective();//����͸��ͶӰ
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);//��������ͶӰ
}

void Keyboard(unsigned char key, int x, int y)
{
	cout << "�㰴����:" << key << " , " << (int)key << endl;
}
void Special(int key, int x, int y)
{
	cout << "�㰴����:" << key << endl;
	//GLUT_KEY_DOWN
}
void KeyboardUp(unsigned char key, int x, int y)
{
	cout << "��ſ���:" << key << " , " << (int)key << endl;
}
void SpecialUp(int key, int x, int y)
{
	cout << "��ſ���:" << key << endl;
	//GLUT_KEY_DOWN
}
class InitOpenGL
{
public:
	//��ʼ��glut��
	void Init(int *argc, char **argv)
	{
		glutInit(argc, argv);
	}
	//��ʼ��OpenGL����ʾģʽ
	void InitMode(unsigned int Define)
	{
		glutInitDisplayMode(Define);
	}
	//���ô��ڿͻ���������������Ͻǵ�λ��
	void InitWinPos(int W, int H)
	{
		glutInitWindowPosition(W, H);
	}
	//���ô��ڵ����ؿ��(Ҳ���ǿͻ����Ŀ��)
	void InitWindSize(int Size_W, int Size_H)
	{
		glutInitWindowSize(Size_W, Size_H);
	}
	//�������ڣ���д���ڱ�����������
	void CreateWindows(const char *WindName)
	{
		glutCreateWindow(WindName);
	}
	//���õ����������һ�λ��Ƶ���ɫ���ݵ���ɫ���൱�ڱ�����ɫ��
	void ClearColor(float R, float G, float B, float Alpha)
	{
		glClearColor(R, G, B, Alpha);
	}
};

//λͼͷ�ļ�14
struct SIZEOF1
{
	WORD buf_int; //��¼�ļ����� 0x4d42
	DWORD buf_size; //��¼λͼ�ļ��Ĵ�С
	//WORD k1; //�����ģ���0
	//WORD k2; //�����ģ���0
	//WORD buf_bit; //��ɫ���ݺ��ļ�ͷ��ƫ���ֽ���
}IMAGE0;
//λͼ��Ϣͷ40
struct SIZEOF2
{
	//DWORD bisize; //������ṹ������ֽ�
	LONG biWidth; //���صĿ�
	LONG biHeight; //���صĸ�
	//WORD biweizhi1; //24λͼ��1
	WORD biSHENDU; //λ��� ��0x18
	//DWORD biyasuo; //��û�б�ѹ����û����0
	DWORD bisizeimage; //ͼƬ�����ֽ���
	//LONG k3; //0Ĭ��
	//LONG k4; //0Ĭ��
	//DWORD k5; //�ж�����ɫ��ʹ��0
	 //DWORD k6;//�ж�����Ҫ����ɫ0
}IMAGE_MAX;

int main(int argc, char **argv)
{

	InitOpenGL Obj;

	Obj.Init(&argc, argv);
	Obj.InitMode(GLUT_SINGLE | GLUT_RGBA);
	Obj.InitWinPos(314, 50);
	Obj.InitWindSize(640, 480);
	Obj.CreateWindows("OpenGL����");
	Obj.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//����OpenGL���ƻص�����
	glutDisplayFunc(Display);

	//�����ڴ�С�ͼ���״̬�ı��ʱ�����õĺ���
	glutReshapeFunc(ReShape);

	//��ͨ���̻ص�����
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	//���ܼ��ص�����
	glutSpecialFunc(Special);
	glutSpecialUpFunc(SpecialUp);

	//glut����ѭ��
	glutMainLoop();

	//FILE *pf = NULL;
	//fopen_s(&pf, "satan.bmp", "rb");
	//if (pf)
	//{
	//	//ȡһ���ļ��Ĵ�С
	//	int max = 0;
	//	fseek(pf, 0, SEEK_END); //�ļ�ĩβ
	//	max = ftell(pf); //��Сȡ����ֵ
	//	rewind(pf); //���°��ļ�ָ��ʼ
	//	//�ж�ǰ�����ֽ��ǲ���0x4d42
	//	fread(&IMAGE0.buf_int, 2, 1, pf); //��ǰ�����ֽ�
	//	if (IMAGE0.buf_int != 0x4d42) //������Ͳ�һ��
	//	{
	//		std::cout << "�ļ�����λͼ�ļ�" << std::endl;
	//		fclose(pf);
	//		system("pause");
	//		return 0;
	//	}
	//	//ȡ�ļ��Ĵ�С
	//	fread(&IMAGE0.buf_size, 4, 1, pf);
	//	if (IMAGE0.buf_size != max) //������²�һ��
	//	{
	//		std::cout << "�ļ������𻵣�" << std::endl;
	//		fclose(pf);
	//		system("pause");
	//		return 0;
	//	}
	//	//����λͼ�Ĵ洢�ռ�
	//	unsigned char *bmp = new unsigned char[max];
	//	rewind(pf); //����ָ��ͷ
	//	fread(bmp, 1, max, pf); //��������Ϣ����bmp��
	//	fclose(pf); //�ر��ļ�
	//	//ͼƬ�Ŀ��
	//	IMAGE_MAX.biWidth = *((int*)(bmp + 18)); //λͼ�Ŀ�
	//	IMAGE_MAX.biHeight = *((int*)(bmp + 22)); //λͼ�ĸ�
	//	//λͼ�����
	//	IMAGE_MAX.biSHENDU = *((WORD*)(bmp + 28)); //λͼ�����
	//	if (IMAGE_MAX.biSHENDU != 24)
	//	{
	//		std::cout << "����24λλͼ��" << std::endl;
	//		delete[] bmp;
	//		bmp = NULL;
	//		system("pause");
	//		return 0;
	//	}
	//	//λͼ��ɫ������
	//	IMAGE_MAX.bisizeimage = *((DWORD*)(bmp + 34)); //�洢��ɫ���ݵ��ĸ��ֽ�
	//	int i = IMAGE_MAX.bisizeimage / IMAGE_MAX.biHeight; //һ�е��ֽ���
	//	for (int j = IMAGE_MAX.biHeight - 1; j >= 0; j--)
	//	{
	//		unsigned char *Hcolor = bmp + 54 + j * i;
	//		for (int k = 0; k < IMAGE_MAX.biWidth; k++)
	//		{
	//			unsigned char *Wcolor = Hcolor + k * 3;
	//			//ע����� �������صĿ�͸���ô���
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