#pragma once

#include "com/Thread.h"
using namespace com;


namespace timer
{
	// Timer generate thread
	class TimerThread2 : public Thread
	{
	public:
		TimerThread2();

	protected:
		//************************************
		// Method:    Thread while evt handler
		//************************************
		void OnWhile() override;
	};
}