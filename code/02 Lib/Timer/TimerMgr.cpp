#include "stdafx.h"
#include "TimerMgr.h"

namespace timer
{
	vector<Timer*>	TimerMgr::vecTimers;
	queue<int>		TimerMgr::quUnitTimes;
	Lock			TimerMgr::lock1;
	Lock			TimerMgr::lock2;


	TimerMgr::TimerMgr()
	{

	}

	void TimerMgr::AddTimer(Timer* pTimer)
	{
		lock2.Enter();

		vecTimers.push_back(pTimer);

		lock2.Leave();
	}

	void TimerMgr::RemoveTimer(Timer* pTimer)
	{
		lock2.Enter();

		for (vector<Timer*>::iterator it = vecTimers.begin(); it != vecTimers.end(); it++)
		{
			if (*it == pTimer)
			{
				vecTimers.erase(it);
				break;
			}
		}

		lock2.Leave();
	}

	void TimerMgr::PushUnitTime(int time)
	{
		lock1.Enter();

		quUnitTimes.push(time);

		lock1.Leave();
	}

	void TimerMgr::ProcessUnitTime()
	{
		while (true)
		{
			int val = 0;

			if (!quUnitTimes.empty())
			{
				lock1.Enter();

				if (!quUnitTimes.empty())
				{
					val = quUnitTimes.front();
					quUnitTimes.pop();
				}

				lock1.Leave();
			}
			else
			{
				break;
			}

			if (val > 0 && !vecTimers.empty())
			{
				lock2.Enter();

				for (auto & it : vecTimers)
				{
					it->OnElapse(val);
				}

				lock2.Leave();
			}
		}
	}
}