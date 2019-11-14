#include "stdafx.h"
#include "HttpResponseMgr.h"
#include <assert.h>
#include "Include/hc/HttpClient.h"

namespace hc
{
	HttpResponseMgr::HttpResponseMgr() :
		bExited(false)
	{
		InitializeCriticalSection(&section1);
	}

	HttpResponseMgr::~HttpResponseMgr()
	{
		DeleteCriticalSection(&section1);
	}

	void HttpResponseMgr::Push(HttpResponseInfo& info)
	{
		EnterCriticalSection(&section1);

		if (!bExited)
		{
			quHttpResponses.push(info);
		}

		LeaveCriticalSection(&section1);
	}

	void HttpResponseMgr::ProcessResponse(HttpResponseInfo& info)
	{
		if (info.phc)
		{
			info.phc->OnHttpResponse(info.data);
		}
	}

	void HttpResponseMgr::ProcessHttpResponse()
	{
		while (!bExited)
		{
			EnterCriticalSection(&section1);

			if (!quHttpResponses.empty())
			{
				HttpResponseInfo info = quHttpResponses.front();
				assert(!quHttpResponses.empty());
				quHttpResponses.pop();

				LeaveCriticalSection(&section1);

				ProcessResponse(info);
			}
			else
			{
				LeaveCriticalSection(&section1);
				break;
			}
		}
	}

	void HttpResponseMgr::Exit()
	{
		bExited = true;

		while (!quHttpResponses.empty())
		{
			quHttpResponses.pop();
		}
	}
}