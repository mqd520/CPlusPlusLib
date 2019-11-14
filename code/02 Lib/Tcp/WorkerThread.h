#pragma once

#include "com/Thread.h"
using namespace com;


namespace tcp
{
	// Worker Thread
	class WorkerThread : public Thread
	{
	public:
		WorkerThread();

	protected:
		//************************************
		// Method:    Thread while evt handler
		//************************************
		void OnWhile() override;

		//************************************
		// Method:    Thread exit evt handler
		//************************************
		void OnExit() override;
	};
}