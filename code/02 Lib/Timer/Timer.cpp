#include "stdafx.h"
#include "Include/timer/Timer.h"
#include "TimerMgr.h"


namespace timer
{
	Timer::Timer(int interval /*= 1 * 1000*/, int count /*= 0*/) :
		nInterval(interval),
		nElapsedTime(0),
		nTimerCount(0),
		nMaxCount(count),
		bStarted(false)
	{
		TimerMgr::AddTimer(this);
	}

	Timer::~Timer()
	{
		TimerMgr::RemoveTimer(this);
	}

	void Timer::OnElapse(int time)
	{
		if (!bStarted)
		{
			return;
		}

		nElapsedTime += time;
		if (nElapsedTime >= nInterval)
		{
			nElapsedTime = nInterval;
		}

		if (nElapsedTime == nInterval)
		{
			OnTimer();
			nElapsedTime = 0;
		}
	}

	void Timer::OnTimer()
	{
		nTimerCount++;
		if (nMaxCount > 0)
		{
			if (nTimerCount > nMaxCount)
			{
				return;
			}
		}

		if (!fnTimer._Empty())
		{
			fnTimer(this, nTimerCount);
		}
	}

	int Timer::GetInterval() const
	{
		return nInterval;
	}

	void Timer::SetInterval(int interval)
	{
		nInterval = interval;
	}

	void Timer::RegTimerEvt(TimerCallback callback)
	{
		fnTimer = callback;
	}

	void Timer::Start()
	{
		bStarted = true;
	}

	void Timer::Pause()
	{
		bStarted = false;
	}

	void Timer::Resume()
	{
		bStarted = true;
	}

	void Timer::Stop()
	{
		bStarted = false;
		nElapsedTime = 0;
		nTimerCount = 0;
	}

	void Timer::Restart()
	{
		nElapsedTime = 0;
		nTimerCount = 0;
		Start();
	}
}