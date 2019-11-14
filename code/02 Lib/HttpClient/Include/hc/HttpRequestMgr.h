#pragma once

#include "HttpClient.h"

#include <minwindef.h>
#include <queue>
using namespace std;


namespace hc
{
	// http request mgr
	class HttpRequestMgr
	{
	public:
		HttpRequestMgr();
		~HttpRequestMgr();

	private:
		queue<HttpRequestParaInfo> quHttpRequests;		// http request queue
		CRITICAL_SECTION section1;						// section to var "quHttpRequests"
		bool bExited;									// whether exit

	protected:
		void ProcessRequest(HttpRequestParaInfo& info);

	public:
		//************************************
		// Method:    push
		// Parameter: HttpRequestInfo & info
		//************************************
		void Push(HttpRequestParaInfo& info);

		//************************************
		// Method:    process http request
		//************************************
		void ProcessHttpRequest();

		//************************************
		// Method:    exit
		//************************************
		void Exit();
	};
}