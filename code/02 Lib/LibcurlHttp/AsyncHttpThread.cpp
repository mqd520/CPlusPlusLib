#include "stdafx.h"
#include "AsyncHttpThread.h"

#include "AsyncHttp.h"


namespace libcurlHttp
{
	AsyncHttpThread::AsyncHttpThread()
		: Thread(50, "AsyncHttpThread")
	{

	}

	void AsyncHttpThread::OnWhile()
	{
		_asyncHttp.ProcessHttpReq();
	}

	void AsyncHttpThread::OnExit()
	{
		__super::OnExit();
	}
}