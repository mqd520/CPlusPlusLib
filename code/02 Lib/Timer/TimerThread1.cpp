#include "stdafx.h"
#include "TimerThread1.h"
#include "TimerMgr.h"

namespace timer
{
	TimerThread1::TimerThread1() :
		Thread(50, "Timer Process Thread")
	{

	}

	void TimerThread1::OnWhile()
	{
		__super::OnWhile();

		TimerMgr::ProcessUnitTime();
	}
}