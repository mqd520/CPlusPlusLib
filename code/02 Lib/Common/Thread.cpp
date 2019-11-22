#include "stdafx.h"
#include "Include/com/Thread.h"

#include "Include/com/Log.h"
#include "Include/com/CommonTool.h"
#include "Include/com/TimeTool.h"


namespace com
{
	typedef vector<ThreadStartCallback>::iterator	IT1;
	typedef vector<ThreadWhileCallback>::iterator	IT2;
	typedef vector<ThreadExitCallback>::iterator	IT3;


	Thread::Thread(int nMillSecond /*= ThreadSleepMillTime*/, string name /*= "Thread"*/)
		: strThreadName(name)
		, bRunning(false)
		, bStopWhile(false)
		, nMillSecond(nMillSecond)
		, hThd(NULL)
		, dwThreadId(0)
		, evtExit1("Common_ThreadExit1_" + CommonTool::FormatGuid())
		, evtExit2("Common_ThreadExit2_" + CommonTool::FormatGuid())
		, lpParam(nullptr)
	{

	}

	Thread::~Thread()
	{

	}

	int Thread::ThreadMain()
	{
		bRunning = true;
		bStopWhile = false;

		OnStart();

		OnExecute();

		OnExit();

		evtExit2.Active();


		/* Do not delete the following code, just for debug */

		//char ch[1024] = { 0 };
		//sprintf_s(ch, "evtExit2.Active();, time: %s, Id: 0x%04x, Handle: 0x%04x \n",
		//	TimeTool::Format("yyyy-mm-dd HH:MM:ss.ff").c_str(),
		//	dwThreadId,
		//	hThd);
		//OutputDebugStringA(ch);

		return 0;
	}

	void Thread::OnStart()
	{
		Log::Write_2_Console(ELogType::Debug, true, __FUNCTION__, __FILE__, __LINE__,
			"Thread start: %s, Id: 0x%04x, Handle: 0x%04x", strThreadName.c_str(), dwThreadId, hThd);

		for (auto & it : vecStartCallbacks)
		{
			if (!it._Empty())
			{
				it(this);
			}
		}
	}

	void Thread::OnExecute()
	{
		while (true)
		{
			OnWhile();

			if (bStopWhile)
			{
				break;
			}

			DWORD dwResult = evtExit1.WaitForSingal(0);
			if (dwResult == WAIT_OBJECT_0)
			{
				/* Do not delete the following code, just for debug */

				//char ch[1024] = { 0 };
				//sprintf_s(ch, "while: dwResult == WAIT_OBJECT_0, time: %s, Id: 0x%04x, Handle: 0x%04x \n",
				//	TimeTool::Format("yyyy-mm-dd HH:MM:ss.ff").c_str(),
				//	dwThreadId,
				//	hThd);
				//OutputDebugStringA(ch);

				break;
			}

			::Sleep(nMillSecond);
		}
	}

	void Thread::OnWhile()
	{
		//for (IT2 it = vecWhileCallbacks.begin(); it != vecWhileCallbacks.end(); it++)
		//{
		//	if (!it->_Empty())
		//	{
		//		(*it)(this);
		//	}
		//}
	}

	void Thread::OnExit()
	{
		Log::Write_2_Console(ELogType::Debug, true, __FUNCTION__, __FILE__, __LINE__,
			"Thread exit: %s", strThreadName.c_str());
	}

	HANDLE Thread::GetThreadHandle() const
	{
		return 0;
	}

	int Thread::GetThreadId() const
	{
		return 0;
	}

	bool Thread::IsRun() const
	{
		return bRunning;
	}

	string Thread::GetThreadName() const
	{
		return strThreadName;
	}

	void Thread::SetThreadName(string name)
	{
		strThreadName = name;
	}

	int Thread::GetSleepTime() const
	{
		return nMillSecond;
	}

	void Thread::SetSleepTime(int time)
	{
		nMillSecond = time;
	}

	void Thread::Run(LPVOID lpParam /*= nullptr*/)
	{
		if (!bRunning && hThd == NULL)
		{
			this->lpParam = lpParam;
			hThd = (HANDLE)_beginthreadex(0, 0, ThreadRun::Run, this, 0, NULL);
			dwThreadId = ::GetThreadId(hThd);


			/* Do not delete the following code, just for debug */

			//char ch[1024] = { 0 };
			//sprintf_s(ch, "Thread, Id: 0x%04x, Handle: 0x%04x, time: %s \n",
			//	dwThreadId,
			//	hThd,
			//	TimeTool::Format("yyyy-mm-dd HH:MM:ss.ff").c_str());
			//OutputDebugStringA(ch);
		}
	}

	void Thread::StopWhile()
	{
		bStopWhile = true;
	}

	void Thread::Exit(int timeout /*= 1 * 1000*/)
	{
		if (bRunning)
		{
			evtExit1.Active();


			/* Do not delete the following code, just for debug */

			//char ch[1024] = { 0 };
			//sprintf_s(ch, "evtExit1.Active(), time: %s, Id: 0x%04x, Handle: 0x%04x \n",
			//	TimeTool::Format("yyyy-mm-dd HH:MM:ss.ff").c_str(),
			//	dwThreadId,
			//	hThd);
			//OutputDebugStringA(ch);


			DWORD dwResult = evtExit2.WaitForSingal(timeout);
			if (dwResult == WAIT_OBJECT_0)
			{
				/* Do not delete the following code, just for debug */

				//char ch2[1024] = { 0 };
				//sprintf_s(ch2, "Exit: dwResult == WAIT_OBJECT_0, time: %s, Id: 0x%04x, Handle: 0x%04x \n",
				//	TimeTool::Format("yyyy-mm-dd HH:MM:ss.ff").c_str(),
				//	dwThreadId,
				//	hThd);
				//OutputDebugStringA(ch2);

				::CloseHandle(hThd);
			}
			else if (dwResult == WAIT_TIMEOUT)
			{
				/* Do not delete the following code, just for debug */

				//char ch1[1024] = { 0 };
				//sprintf_s(ch1, "Exit: dwResult == WAIT_TIMEOUT, time: %s, Id: 0x%04x, Handle: 0x%04x \n",
				//	TimeTool::Format("yyyy-mm-dd HH:MM:ss.ff").c_str(),
				//	dwThreadId,
				//	hThd);
				//OutputDebugStringA(ch1);
			}

			hThd = NULL;
			bRunning = false;
		}
	}

	void Thread::RegStartEvt(ThreadStartCallback fn)
	{
		vecStartCallbacks.push_back(fn);
	}

	void Thread::RegWhileEvt(ThreadWhileCallback fn)
	{
		vecWhileCallbacks.push_back(fn);
	}

	void Thread::RegExitEvt(ThreadExitCallback fn)
	{
		vecExitCallbacks.push_back(fn);
	}


	unsigned int WINAPI ThreadRun::Run(LPVOID lParam)
	{
		int quitCode = 0;

		Thread* pThd = (Thread*)lParam;
		if (pThd)
		{
			quitCode = pThd->ThreadMain();
		}
		else
		{
			Log::Write_2_Console(ELogType::Error, true, __FUNCTION__, __FILE__, __LINE__,
				"Thread start error, name: %s, handle: %d, Id: %d",
				pThd->GetThreadName().c_str(), pThd->GetThreadHandle(), pThd->GetThreadId());

			quitCode = -1;
		}

		return quitCode;
	}
}