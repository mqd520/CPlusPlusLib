#include "stdafx.h"
#include "Thread1.h"

#include <objbase.h>

#include "Task.h"


Thread1::Thread1()
	: Thread(50, "Thread1")
	, bComInited(false)
{

}

void Thread1::OnStart()
{
	CoInitialize(NULL);
	bComInited = true;

	__super::OnStart();
}

void Thread1::OnWhile()
{
	if (bComInited)
	{
		_task.Execute();
	}
}

void Thread1::OnExit()
{
	CoUninitialize();
	bComInited = false;

	__super::OnExit();
}