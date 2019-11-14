#include "stdafx.h"
#include "Include/hc/HttpClientApp.h"
#include "HttpRequestThread.h"
#include "HttpResponseThread.h"


#define Max_HttpRequest_ProcessThread_Count			(2)			// max http request process thread count


namespace hc
{
	bool bInited = false;			// whether inited
	bool bExited = false;			// whether exit
	HttpClientMgr hcMgr;			// HttpClientMgr obj
	HttpRequestMgr hReqMgr;			// HttpRequestMgr obj
	HttpResponseMgr hResMgr;		// HttpResponseMgr obj
	HttpRequestThread thRequest[Max_HttpRequest_ProcessThread_Count];
	HttpResponseThread thReponse;	// HttpResponseThread obj


	HttpClientApp::HttpClientApp()
	{

	}

	void HttpClientApp::Init()
	{
		if (!bInited)
		{
			bInited = true;

			for (int i = 0; i < Max_HttpRequest_ProcessThread_Count; i++)
			{
				thRequest[i].Run();
			}

			thReponse.Run();
		}
	}

	void HttpClientApp::Exit()
	{
		if (!bExited)
		{
			bExited = true;

			hcMgr.Remove();
			hResMgr.Exit();
			hResMgr.Exit();

			for (int i = 0; i < Max_HttpRequest_ProcessThread_Count; i++)
			{
				thRequest[i].Exit();
			}

			thReponse.Exit();

			Sleep(500);
		}
	}

	HttpRequestMgr* HttpClientApp::GetHttpRequestMgr()
	{
		return &hReqMgr;
	}

	HttpClientMgr* HttpClientApp::GetHttpClientMgr()
	{
		return &hcMgr;
	}

	HttpResponseMgr* HttpClientApp::GetHttpResponseMgr()
	{
		return &hResMgr;
	}
}