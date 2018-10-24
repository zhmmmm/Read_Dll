#include <iostream>
#include <Windows.h>


int main()
{
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
	


	system("pause");
	return 0;
}