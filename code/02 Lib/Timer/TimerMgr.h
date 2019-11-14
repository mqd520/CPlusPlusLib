#pragma once

#include <vector>
#include <queue>
using namespace std;

#include "Include/timer/Timer.h"

#include "com/Lock.h"
using namespace com;


namespace timer
{
	// Timer Mgr
	class TimerMgr final
	{
	private:
		TimerMgr();

	private:
		static vector<Timer*> vecTimers;	// timer list
		static queue<int> quUnitTimes;		// unit time queue
		static Lock lock1;
		static Lock lock2;

	public:
		//************************************
		// Method:    Add Timer
		// Parameter: Timer * pTimer
		//************************************
		static void AddTimer(Timer* pTimer);

		//************************************
		// Method:    Remove Timer
		// Parameter: Timer * pTimer
		//************************************
		static void RemoveTimer(Timer* pTimer);

		//************************************
		// Method:    Push Unit Time
		// Parameter: int time
		//************************************
		static void PushUnitTime(int time);

		//************************************
		// Method:    Process Unit Time
		//************************************
		static void ProcessUnitTime();
	};
}