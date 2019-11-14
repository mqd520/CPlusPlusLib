#pragma once

#include <string>
#include <vector>
using namespace std;

#include "HttpSubObject.h"


namespace http
{
	// Request Line 
	class RequestLine : public HttpSubObject
	{
	public:
		RequestLine(const string& method = "GET");

	public:
		string strMethod;			// method
		string strAbsolutePath;		// AbsolutePath
		string strProtocol;			// protocol
		vector<pair<string, string>> vecQueryParams;

	public:
		//************************************
		// Method:    Get Protocol Name
		//************************************
		string GetProtocolName();

		//************************************
		// Method:    Get Protocol Version
		//************************************
		string GetProtocolVersion();

		//************************************
		// Method:    Generate Buf
		// Returns:   int: generate buf length
		// Parameter: BYTE * pBuf
		// Parameter: int len
		//************************************
		int GenerateBuf(BYTE* pBuf, int len);

		//************************************
		// Method:    Reset
		// Parameter: const string & method
		// Parameter: const string & path
		// Parameter: const string & protocol
		//************************************
		void Reset(const string& method, const string& path, const string& protocol);

	public:
		//************************************
		// Method:    Parse buf
		// Returns:   int
		// Parameter: BYTE * pBuf
		// Parameter: int len
		// Parameter: RequestLine & line
		// Parameter: bool & bSuccess
		//************************************
		static int ParseFromBuf(BYTE* pBuf, int len, RequestLine& line, bool& bSuccess);
	};
}