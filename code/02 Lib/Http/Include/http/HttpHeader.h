#pragma once

#include <map>
#include <string>
using namespace std;

#include "HttpSubObject.h"


namespace http
{
	// HttpHeader
	class HttpHeader : public HttpSubObject
	{
	protected:
		map<string, string> mapHeaders;

	protected:
		//************************************
		// Method:    Find Header
		// Parameter: const string & key
		//************************************
		map<string, string>::iterator FindHeader(const string& key);

	public:
		//************************************
		// Method:    Whether header exist
		// Parameter: const string & key
		//************************************
		bool IsExistHeader(const string& key);

		//************************************
		// Method:    Set Header
		// Parameter: const string & key
		// Parameter: const string & val
		//************************************
		void SetHeader(const string& key, const string& val);

		//************************************
		// Method:    Set Header
		// Parameter: const string & key
		// Parameter: const BYTE & val
		//************************************
		void SetHeader(const string& key, const BYTE& val);

		//************************************
		// Method:    Set Header
		// Parameter: const string & key
		// Parameter: const INT16 & val
		//************************************
		void SetHeader(const string& key, const INT16& val);

		//************************************
		// Method:    Set Header
		// Parameter: const string & key
		// Parameter: const UINT16 & val
		//************************************
		void SetHeader(const string& key, const UINT16& val);

		//************************************
		// Method:    Set Header
		// Parameter: const string & key
		// Parameter: const INT32 & val
		//************************************
		void SetHeader(const string& key, const INT32& val);

		//************************************
		// Method:    Set Header
		// Parameter: const string & key
		// Parameter: const UINT32 & val
		//************************************
		void SetHeader(const string& key, const UINT32& val);

		//************************************
		// Method:    Set Header
		// Parameter: const string & key
		// Parameter: const INT64 & val
		//************************************
		void SetHeader(const string& key, const INT64& val);

		//************************************
		// Method:    Set Header
		// Parameter: const string & key
		// Parameter: const UINT64 & val
		//************************************
		void SetHeader(const string& key, const UINT64& val);

		//************************************
		// Method:    Set Header
		// Parameter: const string & key
		// Parameter: const UINT64 & val
		// Parameter: const string& trueVal = "True"
		// Parameter: const string& falseVal = "False"
		//************************************
		void SetHeader(const string& key, const bool& val, const string& trueVal, const string& falseVal);

		//************************************
		// Method:    Get Header Value
		// Parameter: const string & key
		//************************************
		string GetHeader(const string& key);

		//************************************
		// Method:    Get Content-Type(not include charset if that exist)
		//************************************
		string GetContentType();

		//************************************
		// Method:    Get Charset
		//************************************
		string GetCharset();

		//************************************
		// Method:    Remove Header
		// Parameter: const string & key
		//************************************
		void RemoveHeader(const string& key);

		//************************************
		// Method:    Get Header list
		//************************************
		map<string, string> GetHeaders();

		//************************************
		// Method:    Clear
		//************************************
		void Clear();

		//************************************
		// Method:    Generate Buf
		// Returns:   int: generate buf length
		// Parameter: BYTE * pBuf
		// Parameter: int len
		//************************************
		int GenerateBuf(BYTE* pBuf, int len);

	public:
		//************************************
		// Method:    Parse buf
		// Returns:   int
		// Parameter: BYTE * pBuf
		// Parameter: int len
		// Parameter: HttpHeader & header
		// Parameter: bool & bSuccess
		//************************************
		static int ParseFromBuf(BYTE* pBuf, int len, HttpHeader& header, bool& bSuccess);
	};
}