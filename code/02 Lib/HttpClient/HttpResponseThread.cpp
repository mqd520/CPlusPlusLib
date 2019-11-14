#include "stdafx.h"
#include "HttpResponseThread.h"
#include "Include/hc/HttpClientApp.h"

namespace hc
{
	HttpResponseThread::HttpResponseThread()
	{

	}

	HttpResponseThread::~HttpResponseThread()
	{

	}

	void HttpResponseThread::OnExecute()
	{
		HttpClientApp::GetHttpResponseMgr()->ProcessHttpResponse();
	}
}