#pragma once

#include "com/Thread.h"
using namespace com;


namespace timer
{
	// Timer trigger thread
	class TimerThread1 : public Thread
	{
	public:
		TimerThread1();

	protected:
		//************************************
		// Method:    Thread inner while evt handler
		//************************************
		void OnWhile() override;
	};
}