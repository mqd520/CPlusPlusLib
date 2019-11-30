#include "stdafx.h"
#include "TaskThread.h"

#include <objbase.h>

#include "Task.h"


TaskThread::TaskThread()
	: Thread(2 * 1000, "TaskThread")
{

}

void TaskThread::OnStart()
{
	__super::OnStart();
}

void TaskThread::OnWhile()
{
	_task.Process();
}

void TaskThread::OnExit()
{
	__super::OnExit();
}