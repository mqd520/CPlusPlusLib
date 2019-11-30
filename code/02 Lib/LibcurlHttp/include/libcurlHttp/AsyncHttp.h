#pragma once

#include <queue>
using namespace std;

#include <string>
#include <functional>
using namespace std::placeholders;

#include "com/Lock.h"
using namespace com;

#include "LibcurlHttp.h"


namespace libcurlHttp
{
	// Async Http Callback
	// AdoResult: Ado result
	// lpParam1:  param1
	// lpParam2:  param2
	using AsyncHttpCallback = std::function < void(LibcurlHttpResult& result) >;


	// Async Http Req
	typedef struct tagAsyncHttpReq
	{
		LibcurlHttp http;			// LibcurlHttp
		string		url;			// Url
		string		method;			// Http method
		bool		bRecvResponse;	// Whether recv response
		bool		bRecvHeader;	// Whether recv header
		string		contentType;	// Content-Type
		AsyncHttpCallback callback; // Callback
	}AsyncHttpReq;	// Async Http Req


	// AsyncHttp
	class AsyncHttp
	{
	protected:
		queue<AsyncHttpReq>		quHttpReqs;		// Http req queue
		Lock					lock1;			// Lock

	public:
		//************************************
		// Method:    Push Http Req
		// Parameter: AsyncHttpReq & req
		//************************************
		void PushHttpReq(AsyncHttpReq& req);

		//************************************
		// Method:    Process Http Req
		//************************************
		void ProcessHttpReq();

		//************************************
		// Method:    Exit
		//************************************
		void Exit();
	};

	extern AsyncHttp _asyncHttp;	// the only AsyncHttp object
}