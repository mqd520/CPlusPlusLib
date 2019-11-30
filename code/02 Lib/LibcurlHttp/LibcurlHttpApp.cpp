#include "stdafx.h"
#include "LibcurlHttpApp.h"

#include <curl/curl.h>

#include "com/Log.h"
#include "com/CommonTool.h"
using namespace com;

#include "AsyncHttpThread.h"


namespace libcurlHttp
{
	void OnThreadStarted(Thread* pThd);

	HttpProxyInfo	_httpProxyInfo = { false, "", "", "" };
	TimeoutInfo		_timeoutInfo = { -1, -1 };
	bool			_bEnableHttpReqLog = false;

	AsyncHttpThread _arrThds[32];
	int				_nThdCount = 0;
	int				_nThdStartedCount = 0;


	LibcurlHttpApp::LibcurlHttpApp()
	{

	}

	void LibcurlHttpApp::Init()
	{
		CURLcode code = curl_global_init(CURL_GLOBAL_DEFAULT);
		if (code != CURLE_OK)
		{
			Log::Write_2_Console(ELogType::Error, "curl global init fail", true, __FUNCTION__, __FILE__, __LINE__);
		}
	}

	void LibcurlHttpApp::Exit(int timeout /*= 1 * 1000*/)
	{
		curl_global_cleanup();

		for (int i = 0; i < _nThdCount; i++)
		{
			_arrThds[i].Exit(timeout);
		}
	}

	void LibcurlHttpApp::SetHttpProxy(const string& addr, const string& username /*= ""*/, const string& pwd /*= ""*/)
	{
		_httpProxyInfo.bIsSet = true;
		_httpProxyInfo.addr = addr;
		_httpProxyInfo.username = username;
		_httpProxyInfo.pwd = pwd;
	}

	void LibcurlHttpApp::SetTimeout(int nConnectTimeout /*= -1*/, int nHttpTimeout /*= -1*/)
	{
		_timeoutInfo.nConnectTimeout = nConnectTimeout;
		_timeoutInfo.nHttpTimeout = nHttpTimeout;
	}

	void LibcurlHttpApp::EnableHttpReqLog(bool bEnable /*= true*/)
	{
		_bEnableHttpReqLog = bEnable;
	}

	HttpProxyInfo& LibcurlHttpApp::GetHttpProxy()
	{
		return _httpProxyInfo;
	}

	TimeoutInfo& LibcurlHttpApp::GetTimeoutInfo()
	{
		return _timeoutInfo;
	}

	bool LibcurlHttpApp::IsEnableHttpReqLog()
	{
		return _bEnableHttpReqLog;
	}

	void LibcurlHttpApp::SetMultiThread(int nCount /*= 1*/, int nSleepTime /*= 50*/)
	{
		_nThdCount = nCount;

		for (int i = 0; i < _nThdCount; i++)
		{
			_arrThds[i].RegStartEvt(std::bind(OnThreadStarted, _1));
			_arrThds[i].SetSleepTime(nSleepTime + (i * 5));
			_arrThds[i].Run();
		}
	}

	bool LibcurlHttpApp::IsAllThreadStarted()
	{
		return _nThdCount == _nThdStartedCount;
	}

	void OnThreadStarted(Thread* pThd)
	{
		_nThdStartedCount++;
	}
}