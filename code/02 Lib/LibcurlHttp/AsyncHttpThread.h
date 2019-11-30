#pragma once

#include "com/Thread.h"
using namespace com;


namespace libcurlHttp
{
	// Async Http Thread
	class AsyncHttpThread : public Thread
	{
	public:
		AsyncHttpThread();

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