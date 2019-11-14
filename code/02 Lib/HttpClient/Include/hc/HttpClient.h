#pragma once

#include <string>
#include <minwindef.h>
#include <functional>
using namespace std;
using namespace std::placeholders;

#include "Ryeol/RyeolHttpClient.h"
using namespace Ryeol;


namespace hc
{
	class HttpClient;
	class HttpResponseMgr;


	// http response data
	typedef struct tagHttpResponseData
	{
		int nStatusCode;						// status code
		string strStatusText;					// status text
		vector<pair<string, string>> vecHeaders;// header list
		string bufContent;						// body buf
		int len;								// body buf len
		string strContentType;					// Content-Type
		string url;								// request url
	}HttpResponseData;


	// http request parameter info
	typedef struct tagHttpRequestParaInfo
	{
		string guid;	// guid
		string method;	// http request method
		string url;		// request url
		string url1;	// request url(not include query string)
		vector<pair<string, string>> vecParams;		// request param
		vector<pair<string, string>> vecHeaders;	// request headers
	}HttpRequestParaInfo;


	// HttpClient Callback fn
	// HttpClient*:			HttpClient obj
	// HttpResponseData&:	HttpResponseData obj
	typedef std::function<void(HttpClient*, HttpResponseData&)> HttpResponseCallback;


	// HttpClient
	class HttpClient
	{
	public:
		//************************************
		// Method:    constructor
		// Parameter: string url
		//************************************
		HttpClient(string url = "");
		~HttpClient();

	protected:
		string url;			// url
		string guid;		// guid
		HttpResponseCallback fn;	// callback fn

	protected:
		friend class HttpResponseMgr;

		//************************************
		// Method:    http response event handler
		// Parameter: HttpClient * phc
		// Parameter: HttpResponseData & data
		//************************************
		void OnHttpResponse(HttpResponseData& data);

	public:
		//************************************
		// Method:    Get guid
		//************************************
		string GetGUID();

		//************************************
		// Method:    Get url
		//************************************
		string GetUrl();

		//************************************
		// Method:    Reset url
		// Parameter: string url
		//************************************
		void ResetUrl(string url);

		//************************************
		// Method:    Set Callback fun
		//************************************
		void SetCallbackFn(HttpResponseCallback fun);

		//************************************
		// Method:    Send http Get request
		// Parameter: query: query param
		// Parameter: contentType: 
		//************************************
		void HttpGet(string query, string contentType);

		//************************************
		// Method:    Send http Get request
		// Parameter: query: query param
		//************************************
		void HttpGet(string query);

		//************************************
		// Method:    Send http Get request
		//************************************
		void HttpGet();

		//************************************
		// Method:    Send http Post request
		// Parameter: params: request param
		// Parameter: query: query param
		// Parameter: contentType: 
		//************************************
		void HttpPost(vector<pair<string, string>>& params, string query, string contentType);

		//************************************
		// Method:    Send http Post request
		// Parameter: params: request param
		//************************************
		void HttpPost(vector<pair<string, string>>& params);

		//************************************
		// Method:    Send http Post request
		// Parameter: contentType: 
		//************************************
		void HttpPost(string contentType);

		//************************************
		// Method:    Send http Post request
		//************************************
		void HttpPost();

		//************************************
		// Method:    Exit
		//************************************
		void Exit();
	};
}
