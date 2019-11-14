#pragma once

#include <vector>
using namespace std;

#include "HttpClient.h"

namespace hc
{
	// http client mgr
	class HttpClientMgr
	{
	public:
		HttpClientMgr();
		~HttpClientMgr();

	private:
		vector<HttpClient*> vecHttpClients;		// HttpClient list

	public:
		//************************************
		// Method:    Add a HttpClient obj
		// Parameter: HttpClient * phc
		//************************************
		void Add(HttpClient* phc);

		//************************************
		// Method:    Remove a HttpClient obj
		// Parameter: HttpClient * phc
		//************************************
		void Remove(HttpClient* phc);

		//************************************
		// Method:    Remove a HttpClient obj
		//************************************
		void Remove();

		//************************************
		// Method:    Get a HttpClient obj
		// Parameter: url
		//************************************
		HttpClient* GetByUrl(string url);

		//************************************
		// Method:    Get a HttpClient obj
		// Parameter: string guid
		//************************************
		HttpClient* Get(string guid);
	};
}