#pragma once

#include "Include/hc/HttpClient.h"

#include <queue>
using namespace std;

#include "Ryeol/RyeolHttpClient.h"
using namespace Ryeol;

namespace hc
{
	// http response info
	typedef struct tagHttpResponseInfo
	{
		HttpClient* phc;		// HttpClient pointer
		HttpResponseData data;	// HttpResponseData
	}HttpResponseInfo;

	// http response mgr
	class HttpResponseMgr
	{
	public:
		HttpResponseMgr();
		~HttpResponseMgr();

	private:
		queue<HttpResponseInfo> quHttpResponses;	// HttpResponseInfo list
		CRITICAL_SECTION section1;					// section to var "quHttpResponses"
		bool bExited;								// whether	exit

	protected:
		void ProcessResponse(HttpResponseInfo& info);

	public:
		//************************************
		// Method:    Push
		// Parameter: HttpResponseData& info
		//************************************
		void Push(HttpResponseInfo& info);

		//************************************
		// Method:    Process HttpResponse
		//************************************
		void ProcessHttpResponse();

		//************************************
		// Method:    Exit
		//************************************
		void Exit();
	};
}