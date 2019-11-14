#pragma once

#include "com/Thread.h"
using namespace com;


namespace MyAdo
{
	// DbService Thread
	class DbServiceThread : public Thread
	{
	public:
		DbServiceThread();

	protected:
		//************************************
		// Method:    Thread start evt handler
		//************************************
		void OnStart() override;

		//************************************
		// Method:    Thread exit evt handler
		//************************************
		void OnExit() override;

		//************************************
		// Method:    Thread while evt handler
		//************************************
		void OnWhile() override;

	public:
		//************************************
		// Method:    Exit
		// Parameter: int timeout
		//************************************
		void Exit(int timeout = 1 * 1000) override;
	};
}