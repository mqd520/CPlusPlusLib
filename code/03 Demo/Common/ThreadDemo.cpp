#include "stdafx.h"
#include "ThreadDemo.h"


void OnStart(Thread* pThd);
void OnWhile(Thread* pThd);
void OnExit(Thread* pThd);

Thread1 ThreadDemo::thd1;


void ThreadDemo::Init()
{
	thd1.RegStartEvt(std::bind(OnStart, _1));
	thd1.RegWhileEvt(std::bind(OnWhile, _1));
	thd1.RegExitEvt(std::bind(OnExit, _1));
}

void ThreadDemo::Exit()
{
	thd1.Exit();
}

void ThreadDemo::Test1()
{
	thd1.Run();
}

void OnStart(Thread* pThd)
{
	printf("ThreadDemo.OnStart \n");
}

void OnWhile(Thread* pThd)
{
	printf("ThreadDemo.OnWhile \n");
}

void OnExit(Thread* pThd)
{
	printf("ThreadDemo.OnExit \n");
}