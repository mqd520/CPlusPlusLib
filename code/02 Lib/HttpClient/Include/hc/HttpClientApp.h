#pragma once

#include "HttpRequestMgr.h"
#include "HttpClientMgr.h"
#include "../../HttpResponseMgr.h"

namespace hc
{
	// HttpClientApp
	class HttpClientApp final
	{
	private:
		HttpClientApp();

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
		// Method:    Get HttpRequestMgr obj
		//************************************
		static HttpRequestMgr* GetHttpRequestMgr();

		//************************************
		// Method:    Get HttpClientMgr obj
		//************************************
		static HttpClientMgr* GetHttpClientMgr();

		//************************************
		// Method:    Get HttpResponseMgr obj
		//************************************
		static HttpResponseMgr* GetHttpResponseMgr();
	};
}