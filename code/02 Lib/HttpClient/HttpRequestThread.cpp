#include "stdafx.h"
#include "HttpRequestThread.h"
#include "Include/hc/HttpClientApp.h"

namespace hc
{
	HttpRequestThread::HttpRequestThread()
	{

	}

	HttpRequestThread::~HttpRequestThread()
	{

	}

	void HttpRequestThread::OnExecute()
	{
		HttpClientApp::GetHttpRequestMgr()->ProcessHttpRequest();
	}
}