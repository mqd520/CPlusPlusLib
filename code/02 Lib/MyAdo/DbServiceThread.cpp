#include "stdafx.h"
#include "DbServiceThread.h"

#include <objbase.h>

#include "com/Log.h"
using namespace com;

#include "DbService.h"


namespace MyAdo
{
	DbServiceThread::DbServiceThread()
		: Thread(50, "DbService thread")
	{

	}

	void DbServiceThread::OnStart()
	{
		::CoInitialize(NULL);

		__super::OnStart();
	}

	void DbServiceThread::OnWhile()
	{
		_dbSrv.ProcessDbRequest();
	}

	void DbServiceThread::OnExit()
	{
		::CoUninitialize();

		__super::OnExit();
	}

	void DbServiceThread::Exit(int timeout /* = 1 * 1000 */)
	{
		__super::Exit(timeout);
	}
}