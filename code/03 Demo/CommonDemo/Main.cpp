// Common.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include "com/CommonTool.h"
#include "com/md5.h"
using namespace com;

#include "StringDemo.h"

#include "ByteStreamDemo.h"
#include "MemoryStreamDemo.h"
#include "StreamToolDemo.h"
#include "NetworkStreamDemo.h"
#include "NetworkStreamReadDemo.h"
#include "NetworkStreamWriteDemo.h"

#include "ThreadDemo.h"

#include "AesDemo.h"

#include "com/UrlTool.h"
using namespace com;


#include <queue>
#include <limits>
using namespace std;

#include "com/NumberTool.h"
#include <time.h>
#include "com/TimeTool.h"
#include "com/CommonTool.h"
#include "com/Log.h"
#include "com/ExceptionHandler.h"
using namespace com;


int _tmain(int argc, _TCHAR* argv[])
{
	ExceptionHandler::Init();
	ExceptionHandler::SetFileName("CommonDemo.exe");


	int i = 0;
	int j = 0;
	int n = i / j;







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