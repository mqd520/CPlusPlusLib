#include "stdafx.h"
#include "TimerThread2.h"

#include "TimerMgr.h"


#define UnitTime		(100)		// unit time


namespace timer
{
	TimerThread2::TimerThread2() :
		Thread(UnitTime, "Timer Generate Thread")
	{

	}

	void TimerThread2::OnWhile()
	{
		TimerMgr::PushUnitTime(UnitTime);
	}
}