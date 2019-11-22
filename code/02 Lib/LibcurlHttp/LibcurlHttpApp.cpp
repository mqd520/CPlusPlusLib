#include "stdafx.h"
#include "LibcurlHttpApp.h"

#include <curl/curl.h>

#include "com/Log.h"
using namespace com;


namespace libcurlHttp
{
	HttpProxyInfo	_httpProxyInfo = { false, "", "", "" };
	TimeoutInfo		_timeoutInfo = { -1, -1 };
	bool			_bEnableHttpReqLog = false;

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

	void LibcurlHttpApp::Exit()
	{
		curl_global_cleanup();
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
}