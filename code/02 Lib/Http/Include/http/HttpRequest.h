#pragma once

#include "Def.h"
#include "HttpHeaderDef.h"
#include "Url.h"
#include "RequestLine.h"
#include "HttpHeader.h"
#include "HttpBody.h"


namespace http
{
	// Http Request
	class HttpRequest
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: const string & strUrl
		// Parameter: const string & method
		// Parameter: const string & contentType
		//************************************
		HttpRequest(const string& strUrl = "", const string& method = "GET", const string& contentType = "");

	protected:
		//************************************
		// Method:    Init
		//************************************
		void Init();

	public:
		string strMethod;			// method, "GET", "POST"
		string strHost;				// host


	public:
		Url url;					// Url object(read-only)
		RequestLine line;			// http request line object(read-only)
		HttpHeader header;			// Http header object(read-only)
		HttpBody body;				// Http body object(ready-only)

	public:
		//************************************
		// Method:    Generate Buf
		// Parameter: BYTE * pBuf
		// Parameter: int len
		//************************************
		int GenerateBuf(BYTE* pBuf, int len);

	public:
		//************************************
		// Method:    Parse Buf
		// Returns:   int
		// Parameter: BYTE * pBuf
		// Parameter: int len
		// Parameter: HttpRequest & req
		// Parameter: int & nUsed
		//************************************
		static bool ParseFromBuf(BYTE* pBuf, int len, HttpRequest& req, int& nUsed);
	};
}