#pragma once

#include <process.h>

namespace hc
{
	// Thread
	class Thread
	{
	public:
		Thread();
		virtual ~Thread();

	protected:
		HANDLE hThread;		// thread handle
		bool bExited;		// whether should be quited
		int sleepTime;		// sleep time(ms)

	private:
		//************************************
		// Method:    thread entry
		//************************************
		static unsigned WINAPI Run(LPVOID lParam);

	public:
		//************************************
		// Method:    run thread
		//************************************
		virtual void Run();

		//************************************
		// Method:    while event handler
		//************************************
		virtual void OnWhile();

		//************************************
		// Method:    code execute event handler
		//************************************
		virtual void OnExecute();

		//************************************
		// Method:    thread exit event handler
		//************************************
		virtual void OnExit();

		//************************************
		// Method:    exit thread
		//************************************
		virtual void Exit();

		//************************************
		// Method:    Get thread handle
		//************************************
		HANDLE GetThreadHandle();
	};
}