#pragma once

#include <process.h>
#include <vector>
#include <string>
#include <minwindef.h>
#include <functional>
using namespace std;
using namespace std::placeholders;

#include "Event.h"


#define ThreadSleepMillTime		(10)	// Thread sleep time(ms) 


namespace com
{
	class Thread;
	class ThreadRun;

	// Thread start callback
	// Thread *:	Thread pointer
	using ThreadStartCallback = std::function < void(Thread*) > ;

	// Thread while callback
	// Thread *:	Thread pointer
	using ThreadWhileCallback = std::function < void(Thread*) > ;

	// Thread exit callback
	// Thread *:	Thread pointer
	using ThreadExitCallback = std::function < void(Thread*) > ;



	// Thread
	class Thread
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: int nMillSecond
		// Parameter: string name
		//************************************
		Thread(int nMillSecond = ThreadSleepMillTime, string name = "Thread");

		virtual ~Thread();

	protected:
		HANDLE	hThd;									// Thread handle
		DWORD dwThreadId;								// Thread Id
		bool bRunning;									// Whether run
		bool bStopWhile;								// Whether while
		string strThreadName;							// Thread name
		int nMillSecond;								// Sleep time(ms) 
		LPVOID lpParam;									// Thread param
		Event evtExit1;									// Event exit
		Event evtExit2;									// Event exit
		vector<ThreadStartCallback> vecStartCallbacks;	// Start callback list
		vector<ThreadWhileCallback> vecWhileCallbacks;	// While callback list
		vector<ThreadExitCallback> vecExitCallbacks;	// Exit callback list

	protected:
		friend class ThreadRun;

		//************************************
		// Method:    Thread main
		//************************************
		virtual int ThreadMain();

		//************************************
		// Method:    Thread start evt handler
		//************************************
		virtual void OnStart();

		//************************************
		// Method:    Thread execute evt handler
		//************************************
		virtual void OnExecute();

		//************************************
		// Method:    Thread while evt handler
		//************************************
		virtual void OnWhile();

		//************************************
		// Method:    Thread exit evt handler
		//************************************
		virtual void OnExit();

	public:
		//************************************
		// Method:    Get thread handle
		//************************************
		HANDLE GetThreadHandle() const;

		//************************************
		// Method:    Get thread id
		//************************************
		int GetThreadId() const;

		//************************************
		// Method:    Is run
		//************************************
		bool IsRun() const;

		//************************************
		// Method:    Get thread name
		//************************************
		string GetThreadName() const;

		//************************************
		// Method:    Set Thread Name
		// Parameter: string name
		//************************************
		void SetThreadName(string name);

		//************************************
		// Method:    Get sleep time(ms)
		//************************************
		int GetSleepTime() const;

		//************************************
		// Method:    Set sleep time(ms)
		// Parameter: int time
		//************************************
		void SetSleepTime(int time);

		//************************************
		// Method:    Run thread
		// Parameter: LPVOID lpParam = nullptr
		//************************************
		virtual void Run(LPVOID lpParam = nullptr);

		//************************************
		// Method:    StopWhile
		//************************************
		virtual void StopWhile();

		//************************************
		// Method:    Exit thread
		// Parameter: int timeout = 1 * 1000
		//************************************
		virtual void Exit(int timeout = 1 * 1000);

		//************************************
		// Method:    Reg Thrad Start Evt
		// Parameter: ThreadStartCallback fn
		//************************************
		void RegStartEvt(ThreadStartCallback fn);

		//************************************
		// Method:    Reg Thrad while Evt
		// Parameter: ThreadWhileCallback fn
		//************************************
		void RegWhileEvt(ThreadWhileCallback fn);

		//************************************
		// Method:    Reg Thrad exit Evt
		// Parameter: ThreadExitCallback fn
		//************************************
		void RegExitEvt(ThreadExitCallback fn);
	};


	// Thread run
	class ThreadRun
	{
	public:
		//************************************
		// Method:    thread entry
		//************************************
		static unsigned int WINAPI Run(LPVOID lParam);
	};
}