#pragma once

#include "timer/Timer.h"
using namespace timer;


class TimerDemo final
{
private:
	TimerDemo();

public:
	static void Init();

	static void Start();

	static void Pause();

	static void Resume();

	static void Stop();

	static void Restart();

	static void Exit();
};