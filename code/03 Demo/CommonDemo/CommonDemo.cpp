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


#include <queue>
#include <limits>
using namespace std;

#include "com/NumberTool.h"
#include <time.h>
#include "com/TimeTool.h"
#include "com/Log.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//printf("long: %d, short: %d \n", sizeof(long), sizeof(short));


	//printf("Local host endian: %d \n", StreamTool::GetLocalHostEndian());


	//BYTE buf1[] = { 1, 2, 3 };
	//BYTE buf2[] = { 0, 0, 0 };
	//memcpy(buf2, buf1, 3);
	//printf("buf2: %d, %d, %d \n", buf2[0], buf2[1], buf2[2]);




	AesDemo::Test2();









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