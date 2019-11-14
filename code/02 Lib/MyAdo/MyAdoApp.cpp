#include "stdafx.h"
#include "MyAdoApp.h"

#include <objbase.h>

#include "DbServiceThread.h"
#include "DbService.h"


namespace MyAdo
{
	int _nThreadCount = 0;
	DbServiceThread _arrThreads[5];

	bool MyAdoApp::bEnableAutoCloseConnection = true;
	bool MyAdoApp::bEnableAutoSqlLog = true;


	void MyAdoApp::Init(int nThreadCount /*= 1*/)
	{
		CoInitialize(NULL);

		_nThreadCount = nThreadCount;
		for (int i = 0; i < _nThreadCount; i++)
		{
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
}