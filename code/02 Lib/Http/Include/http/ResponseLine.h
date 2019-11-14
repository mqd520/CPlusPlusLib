#pragma once

#include <string>
using namespace std;

#include "HttpSubObject.h"


namespace http
{
	// ResponseLine
	class ResponseLine : public HttpSubObject
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: int code
		// Parameter: const string & text
		// Parameter: const string & protocol
		//************************************
		ResponseLine(int code = 200, const string& text = "OK", const string& protocol = "HTTP/1.1");

	public:
		int nCode;
		string strText;
		string strProtocol;

	public:
		//************************************
		// Method:    Generate Buf
		// Parameter: BYTE * pBuf
		// Parameter: int len
		//************************************
		int GenerateBuf(BYTE* pBuf, int len);

	public:
		//************************************
		// Method:    ParseFromBuf
		// Parameter: BYTE * pBuf
		// Parameter: int len
		// Parameter: ResponseLine & line
		// Parameter: bool & bSuccess
		//************************************
		static int ParseFromBuf(BYTE* pBuf, int len, ResponseLine& line, bool& bSuccess);
	};
}