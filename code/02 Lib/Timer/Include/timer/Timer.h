#pragma once

#include <functional>
using namespace std;
using namespace std::placeholders;


namespace timer
{

	class TimerMgr;
	class Timer;


	// Timer callback fn
	// Timer*:	Timer
	// int:		count
	using TimerCallback = std::function < void(Timer*, int) > ;


	// Timer
	class Timer
	{
	public:
		Timer(int interval = 1 * 1000, int count = 0);

		~Timer();

	protected:
		int nInterval;			// interval time: millseconds
		int nElapsedTime;		// elapse time
		int nMaxCount;			// max count
		int nTimerCount;		// timer count
		TimerCallback fnTimer;	// timer callback
		bool bStarted;			// whether start

	protected:
		friend class TimerMgr;

		void OnElapse(int time);

		void OnTimer();

	public:
		int GetInterval() const;

		void SetInterval(int interval);

		void RegTimerEvt(TimerCallback callback);

		void Start();

		void Pause();

		void Resume();

		void Stop();

		void Restart();
	};
}