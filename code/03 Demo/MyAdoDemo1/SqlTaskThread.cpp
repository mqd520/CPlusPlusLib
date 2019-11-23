#include "stdafx.h"
#include "SqlTaskThread.h"

#include "SqlTask.h"
#include "MainService.h"


SqlTaskThread::SqlTaskThread()
	: Thread(2 * 1000, "SqlTaskThread")
{

}

void SqlTaskThread::OnStart()
{
	::CoInitialize(NULL);

	__super::OnStart();
}

void SqlTaskThread::OnWhile()
{
	_sqltask.Process();
}

void SqlTaskThread::OnExit()
{
	::CoUninitialize();

	__super::OnExit();
}