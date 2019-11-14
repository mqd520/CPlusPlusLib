#pragma once

#include "Def.h"
#include "HttpHeaderDef.h"
#include "ResponseLine.h"
#include "HttpHeader.h"
#include "HttpBody.h"


namespace http
{
	// HttpResponse
	class HttpResponse
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: int code
		// Parameter: const string & text
		// Parameter: const string & protocol
		//************************************
		HttpResponse(int code = 0, const string& text = "OK", const string& protocol = "HTTP/1.1");

	protected:
		//************************************
		// Method:    Init
		//************************************
		void Init();

	public:
		ResponseLine line;			// http response line object(read-only)
		HttpHeader header;			// Http header object(read-only)
		HttpBody body;				// Http body object(ready-only)

	public:
		//************************************
		// Method:    GenerateBuf
		// Parameter: BYTE * pBuf
		// Parameter: int len
		//************************************
		int GenerateBuf(BYTE* pBuf, int len);

	public:
		//************************************
		// Method:    ParseFromBuf
		// Parameter: BYTE * pBuf
		// Parameter: int len
		// Parameter: HttpResponse & res
		// Parameter: int * usedLen
		//************************************
		static bool ParseFromBuf(BYTE* pBuf, int len, HttpResponse& res, int& usedLen);
	};
}