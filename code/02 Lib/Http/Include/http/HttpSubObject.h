#pragma once

#include <string>
using namespace std;

#include "Def.h"


namespace http
{
	class HttpRequest;
	class HttpResponse;
	class HttpHeader;


	// Http Sub Object
	class HttpSubObject
	{
	protected:
		void* pObj;
		EHttpType httpType;

	public:
		//************************************
		// Method:    Attach Http Obj(HttpRequest or HttpResponse)
		// Parameter: void * pObj
		// Parameter: EHttpType type
		//************************************
		void AttachHttpObj(void* pObj, EHttpType type = EHttpType::Request);

		//************************************
		// Method:    Get Http Type
		//************************************
		EHttpType GetHttpType();

		//************************************
		// Method:    Get HttpRequest poinetr
		//************************************
		HttpRequest* GetHttpRequest();

		//************************************
		// Method:    Get HttpResponse poinetr
		//************************************
		HttpResponse* GetHttpResponse();

		//************************************
		// Method:    Get Method
		//************************************
		string GetMethod();

		//************************************
		// Method:    Get Content-Type
		//************************************
		string GetContentType();

		//************************************
		// Method:    Get Content-Length
		//************************************
		int GetContentLength();

		//************************************
		// Method:    Get Charset
		//************************************
		string GetCharset();
	};
}