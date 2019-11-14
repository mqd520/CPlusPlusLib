#include "stdafx.h"
#include "TimerDemo.h"

#include "timer/TimerApp.h"


void OnTimer(Timer* pTimer, int count);

Timer* p1 = nullptr;

TimerDemo::TimerDemo()
{

}

void TimerDemo::Init()
{
	TimerApp::Init();

	p1 = new Timer(1 * 1000);
	p1->RegTimerEvt(std::bind(OnTimer, _1, _2));
}

void TimerDemo::Start()
{
	p1->Start();
}

void TimerDemo::Pause()
{
	p1->Pause();
}

void TimerDemo::Resume()
{
	p1->Resume();
}

void TimerDemo::Stop()
{
	p1->Stop();
}

void TimerDemo::Restart()
{
	p1->Restart();
}

void TimerDemo::Exit()
{
	if (p1)
	{
		delete p1;
		p1 = nullptr;
	}

	TimerApp::Exit();
}

void OnTimer(Timer* pTimer, int count)
{
	printf("OnTimer: %d \n", count);
}