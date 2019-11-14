#include "stdafx.h"

#include "Include/hc/HttpRequestMgr.h"
#include "Include/hc/HttpClientApp.h"
#include "Include/hc/Log.h"

#include <assert.h>
#include <tchar.h>
#include <minwinbase.h>

#include "ryeol/RyeolHttpClient.h"
using namespace Ryeol;


#define MaxRecvBufLen	(8096)		// max recv buf length


// http header list
static const char* _headers[] = {
	"Content-Length", "Content-Type",
	"Server", "Date", "X-Powered-By", "Accpet-ranges", "Content-Encoding", "Age", "Expires", "Last-modified", "Vary"
	"Connection", "Cache-control", "Expires", "Set-Cookie", "Transfer-Encoding"
};
static const int _nHeaderCount = sizeof(_headers) / sizeof(char*);		// http header count


namespace hc
{
	HttpRequestMgr::HttpRequestMgr() :
		bExited(false)
	{
		InitializeCriticalSection(&section1);
	}

	HttpRequestMgr::~HttpRequestMgr()
	{
		DeleteCriticalSection(&section1);
	}

	void HttpRequestMgr::Push(HttpRequestParaInfo& info)
	{
		EnterCriticalSection(&section1);

		if (!bExited)
		{
			quHttpRequests.push(info);
		}

		LeaveCriticalSection(&section1);
	}

	void HttpRequestMgr::ProcessRequest(HttpRequestParaInfo& info)
	{
		HttpClient* phc = HttpClientApp::GetHttpClientMgr()->Get(info.guid);
		if (phc)
		{
			CHttpClientA http;
			CHttpResponseA* response = NULL;

			for (vector<pair<string, string>>::iterator it = info.vecHeaders.begin(); it != info.vecHeaders.end(); it++)
			{
				http.SetHeader(it->first.c_str(), it->second.c_str());
			}

			string params = "";
			for (vector<pair<string, string>>::iterator it = info.vecParams.begin(); it != info.vecParams.end(); it++)
			{
				params += it->first + "=" + it->second + ", ";
			}
			HttpClientLog::WriteLine(EHttpClientLogType::Debug, false, "Prepare to send http request, url: %s, paras: %s",
				info.url1.c_str(), params.c_str());

			if (info.method == "GET")
			{
				try
				{
					response = http.RequestGet(info.url.c_str());
				}
				catch (CHttpClient::Exception& e)
				{
					HttpClientLog::WriteLine(EHttpClientLogType::Error, true,
						"Send http request fail, error code: %d, win32 error code: %d, err msg: %s,  url: %s, paras: %s",
						e.LastError(), e.Win32LastError(), e.errmsg(), info.url1.c_str(), params.c_str());

					return;
				}
			}
			else if (info.method == "POST")
			{

				for (vector<pair<string, string>>::iterator it = info.vecParams.begin(); it != info.vecParams.end(); it++)
				{
					http.AddParam(it->first.c_str(), it->second.c_str());
				}

				try
				{
					response = http.RequestPost(info.url.c_str());
				}
				catch (CHttpClient::Exception& e)
				{
					HttpClientLog::WriteLine(EHttpClientLogType::Error, true,
						"Send http request fail, error code: %d, win32 error code: %d, err msg: %s,  url: %s, paras: %s",
						e.LastError(), e.Win32LastError(), e.errmsg(), info.url1.c_str(), params.c_str());

					return;
				}
			}

			BYTE buf[MaxRecvBufLen] = { 0 };
			int len = response->ReadContent(buf, MaxRecvBufLen);

			HttpResponseData data;
			data.bufContent = (char*)buf;
			data.len = len;
			data.nStatusCode = (int)response->GetStatus();

			CHttpClientA::PCSZ pcsz1 = response->GetHeader("Content-Type");
			if (pcsz1)
			{
				data.strContentType = (char*)response->GetHeader("Content-Type");
			}

			data.strStatusText = (char*)response->GetStatusText();

			for (int i = 0; i < _nHeaderCount; i++)
			{
				CHttpClientA::PCSZ pcsz = response->GetHeader(_headers[i]);
				if (pcsz)
				{
					data.vecHeaders.push_back({ (char*)_headers[i], pcsz });
				}
			}

			HttpResponseInfo info = { phc, data };
			HttpClientApp::GetHttpResponseMgr()->Push(info);
		}
	}

	void HttpRequestMgr::ProcessHttpRequest()
	{
		while (!bExited)
		{
			EnterCriticalSection(&section1);

			if (!quHttpRequests.empty())
			{
				HttpRequestParaInfo info = quHttpRequests.front();
				assert(!quHttpRequests.empty());
				quHttpRequests.pop();

				LeaveCriticalSection(&section1);

				ProcessRequest(info);
			}
			else
			{
				LeaveCriticalSection(&section1);
				break;
			}
		}
	}

	void HttpRequestMgr::Exit()
	{
		bExited = true;

		while (!quHttpRequests.empty())
		{
			quHttpRequests.pop();
		}
	}
}