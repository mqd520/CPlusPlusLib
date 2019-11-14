#include "stdafx.h"
#include "Include/hc/HttpClient.h"
#include "Include/hc/HttpClientApp.h"

#include "Ryeol/RyeolHttpClient.h"
using namespace Ryeol;

#include "com/CommonTool.h"
using namespace com;


namespace hc
{
	HttpClient::HttpClient(string url /*= ""*/) :
		url(url)
	{
		guid = CommonTool::CreateGuid();
	}

	HttpClient::~HttpClient()
	{

	}

	void HttpClient::OnHttpResponse(HttpResponseData& data)
	{
		if (!fn._Empty())
		{
			fn(this, data);
		}
	}

	void HttpClient::SetCallbackFn(HttpResponseCallback fun)
	{
		this->fn = fun;
	}

	string HttpClient::GetGUID()
	{
		return guid;
	}

	string HttpClient::GetUrl()
	{
		return url;
	}

	void HttpClient::ResetUrl(string url)
	{
		this->url = url;
	}

	void HttpClient::HttpGet(string query, string contentType)
	{
		HttpClientApp::GetHttpClientMgr()->Add(this);

		string url1;
		if (!query.empty())
		{
			url1 = url + "?" + query;
		}
		else
		{
			url1 = url;
		}

		HttpRequestParaInfo info;
		info.guid = guid;
		info.url1 = url1;
		info.url = url;
		info.method = "GET";
		if (!contentType.empty())
		{
			info.vecHeaders.push_back({ "Content-Type", contentType });
		}
		HttpClientApp::GetHttpRequestMgr()->Push(info);
	}

	void HttpClient::HttpGet(string query)
	{
		HttpGet(query, "text/html");
	}

	void HttpClient::HttpGet()
	{
		HttpGet("");
	}

	void HttpClient::HttpPost(vector<pair<string, string>>& params, string query, string contentType)
	{
		HttpClientApp::GetHttpClientMgr()->Add(this);

		string url1;
		if (!query.empty())
		{
			url1 = url + "?" + query;
		}
		else
		{
			url1 = url;
		}

		HttpRequestParaInfo info;
		info.guid = guid;
		info.url1 = url1;
		info.url = url;
		info.method = "POST";
		info.vecParams = params;
		if (!contentType.empty() && contentType != "application/x-www-form-urlencoded")
		{
			info.vecHeaders.push_back({ "Content-Type", contentType });
		}
		HttpClientApp::GetHttpRequestMgr()->Push(info);
	}

	void HttpClient::HttpPost(vector<pair<string, string>>& params)
	{
		HttpPost(params, "", "application/x-www-form-urlencoded");
	}

	void HttpClient::HttpPost(string contentType)
	{
		HttpPost(vector<pair<string, string>>(), "", contentType);
	}

	void HttpClient::HttpPost()
	{
		HttpPost(vector<pair<string, string>>());
	}

	void HttpClient::Exit()
	{
		HttpClientApp::GetHttpClientMgr()->Remove(this);
	}
}