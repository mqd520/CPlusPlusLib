#include "stdafx.h"
#include "WorkerThread.h"


namespace tcp
{
	WorkerThread::WorkerThread() :
		Thread(10, "CompletionPort Thread")
	{
		
	}

	void WorkerThread::OnWhile()
	{
		::GetQueuedCompletionStatus

		__super::OnWhile();
	}

	void WorkerThread::OnExit()
	{
		__super::OnExit();


	}
}