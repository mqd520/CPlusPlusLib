#include "stdafx.h"
#include "Thread.h"

namespace hc
{
	Thread::Thread() :
		hThread(NULL),
		bExited(false),
		sleepTime(10)
	{

	}

	Thread::~Thread()
	{

	}

	unsigned WINAPI Thread::Run(LPVOID lParam)
	{
		Thread* pThread = (Thread*)lParam;

		pThread->OnWhile();
		pThread->OnExit();

		return 0;
	}

	void Thread::Run()
	{
		if (hThread == NULL)
		{
			hThread = (HANDLE)_beginthreadex(0, 0, Run, this, 0, NULL);
		}
	}

	void Thread::OnWhile()
	{
		while (bExited == false)
		{
			OnExecute();

			Sleep(sleepTime);
		}
	}

	void Thread::OnExecute()
	{

	}

	void Thread::OnExit()
	{
		if (hThread)
		{
			::CloseHandle(hThread);
			hThread = NULL;
		}
	}

	void Thread::Exit()
	{
		bExited = true;
	}

	HANDLE Thread::GetThreadHandle()
	{
		return hThread;
	}
}