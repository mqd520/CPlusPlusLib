#include "stdafx.h"
#include "MyAdoApp.h"

#include <objbase.h>

#include "DbServiceThread.h"
#include "DbService.h"


void OnThreadStart(Thread* pThd);

int _nThreadStartedCount = 0;

namespace MyAdo
{
	int _nThreadCount = 0;
	DbServiceThread _arrThreads[32];

	bool MyAdoApp::bEnableAutoCloseConnection = false;
	bool MyAdoApp::bEnableAutoSqlLog = false;


	void MyAdoApp::Init(int nThreadCount /*= 1*/, int nSleepTime /*= 50*/)
	{
		CoInitialize(NULL);

		_nThreadCount = nThreadCount;
		for (int i = 0; i < _nThreadCount; i++)
		{
			_arrThreads[i].SetSleepTime(nSleepTime);
			_arrThreads[i].RegStartEvt(std::bind(OnThreadStart, _1));
			_arrThreads[i].Run();
		}
	}

	void MyAdoApp::Exit(int timeout /*= 1 * 1000*/)
	{
		CoUninitialize();

		for (int i = 0; i < _nThreadCount; i++)
		{
			_arrThreads[i].StopWhile();
		}

		for (int i = 0; i < _nThreadCount; i++)
		{
			_arrThreads[i].Exit(timeout);
		}
	}

	bool MyAdoApp::IsAllThreadStarted()
	{
		return _nThreadStartedCount == _nThreadCount;
	}
}

void OnThreadStart(Thread* pThd)
{
	_nThreadStartedCount++;
}