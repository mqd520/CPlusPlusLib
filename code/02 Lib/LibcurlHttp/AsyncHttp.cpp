#include "stdafx.h"
#include "AsyncHttp.h"


namespace libcurlHttp
{
	AsyncHttp			_asyncHttp;		// the only AsyncHttp object

	void AsyncHttp::PushHttpReq(AsyncHttpReq& req)
	{
		quHttpReqs.push(req);
	}

	void AsyncHttp::ProcessHttpReq()
	{
		bool b = false;
		AsyncHttpReq req;

		lock1.Enter();

		if (!quHttpReqs.empty())
		{
			b = true;
			req = quHttpReqs.front();
			quHttpReqs.pop();
		}

		lock1.Leave();



		if (b)
		{
			LibcurlHttpResult result;

			if (req.method == "POST")
			{
				if (req.contentType.empty())
				{
					result = req.http.Post(req.url, req.bRecvResponse, req.bRecvHeader);
				}
				else
				{
					result = req.http.Post(req.url, req.bRecvResponse, req.bRecvHeader, req.contentType);
				}
			}
			else if (req.method == "GET")
			{
				if (req.contentType.empty())
				{
					result = req.http.Get(req.url, req.bRecvResponse, req.bRecvHeader);
				}
				else
				{
					result = req.http.Get(req.url, req.bRecvResponse, req.bRecvHeader, req.contentType);
				}
			}

			if (!req.callback._Empty())
			{
				req.callback(result);
			}
		}
	}

	void AsyncHttp::Exit()
	{

	}
}