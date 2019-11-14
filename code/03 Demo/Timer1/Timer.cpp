// Timer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "TimerDemo.h"


int _tmain(int argc, _TCHAR* argv[])
{

	TimerDemo::Init();


	char ch[1024] = { 0 };
	while (true)
	{
		string cmd = gets_s(ch);
		if (cmd == "exit")
		{
			break;
		}

		else if (cmd == "start")
		{
			TimerDemo::Start();
		}
		else if (cmd == "pause")
		{
			TimerDemo::Pause();
		}
		else if (cmd == "resume")
		{
			TimerDemo::Resume();
		}
		else if (cmd == "stop")
		{
			TimerDemo::Stop();
		}
		else if (cmd == "restart")
		{
			TimerDemo::Restart();
		}
	}


	TimerDemo::Exit();


	printf("Main over \n");
	::Sleep(3 * 1000);

	return 0;
}

