#include "stdafx.h"
#include "Include/timer/TimerApp.h"

#include "TimerThread1.h"
#include "TimerThread2.h"


namespace timer
{
	TimerThread1 thd1;
	TimerThread2 thd2;


	TimerApp::TimerApp()
	{

	}

	void TimerApp::Init()
	{
		if (!thd1.IsRun())
		{
			thd1.Run();
		}

		if (!thd2.IsRun())
		{
			thd2.Run();
		}
	}

	void TimerApp::Exit(int timeout /*= 2 * 1000*/)
	{
		if (thd1.IsRun())
		{
			thd1.Exit(timeout);
		}

		if (thd2.IsRun())
		{
			thd2.Exit(timeout);
		}
	}
}