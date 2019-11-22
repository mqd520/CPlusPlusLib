// MyAdoDemo1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <string>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{







	char chLine[1024] = { 0 };
	while (true)
	{
		string cmd = gets_s(chLine);
		if (cmd == "exit")
		{
			break;
		}
	}

	return 0;
}