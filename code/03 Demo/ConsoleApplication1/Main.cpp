// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <string>
using namespace std;

#include "InitService.h"


int _tmain(int argc, _TCHAR* argv[])
{
	InitService::Init();

	char chLine[1024] = { 0 };
	while (true)
	{
		string cmd = gets_s(chLine);
		if (cmd == "exit")
		{
			break;
		}
	}

	InitService::Exit();

	return 0;
}

