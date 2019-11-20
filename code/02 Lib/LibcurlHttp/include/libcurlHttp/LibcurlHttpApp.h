#pragma once

#include <string>
using namespace std;


namespace libcurlHttp
{
	// HttpProxyInfo
	typedef struct tagHttpProxyInfo
	{
		bool bIsSet;		// is set
		string addr;		// addr
		string username;	// username
		string pwd;			// pwd
	}HttpProxyInfo;	// HttpProxyInfo


	// TimeoutInfo
	typedef struct tagTimeoutInfo
	{
		int nConnectTimeout;	// connect timeout(in second)
		int nHttpTimeout;		// http timeout(in second)
	}TimeoutInfo;	// TimeoutInfo


	// LibcurlHttpApp
	class LibcurlHttpApp final
	{
	private:
		LibcurlHttpApp();

	public:
		//************************************
		// Method:    Init
		//************************************
		static void Init();

		//************************************
		// Method:    Exit
		//************************************
		static void Exit();

		//************************************
		// Method:    Set Http Proxy
		// Parameter: const string & addr
		// Parameter: const string & username
		// Parameter: const string & pwd
		//************************************
		static void SetHttpProxy(const string& addr, const string& username = "", const string& pwd = "");

		//************************************
		// Method:    Set Timeout
		// Qualifier:
		// Parameter: int nConnectTimeout(in second)
		// Parameter: int nHttpTimeout(in second)
		//************************************
		static void SetTimeout(int nConnectTimeout = -1, int nHttpTimeout = -1);

		//************************************
		// Method:    Enable Http Req Log
		// Parameter: bool bEnable
		//************************************
		static void EnableHttpReqLog(bool bEnable = true);

		//************************************
		// Method:    Get Http Proxy
		//************************************
		static HttpProxyInfo& GetHttpProxy();

		//************************************
		// Method:    Get Timeout Info
		//************************************
		static TimeoutInfo& GetTimeoutInfo();

		//************************************
		// Method:    Is Enable Http Req Log
		//************************************
		static bool IsEnableHttpReqLog();
	};
}