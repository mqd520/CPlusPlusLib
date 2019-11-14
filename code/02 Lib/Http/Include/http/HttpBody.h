#pragma once

#include <string>
using namespace std;

#include "Form.h"
#include "HttpSubObject.h"


namespace http
{
	// Http Body
	class HttpBody : public HttpSubObject
	{
	public:
		HttpBody();

	protected:
		string pBuf;			// binary data buf
		int nLen;				// binary data buf length
		string strTextData;		// text data

	public:
		Form form;			// Form object(readonly)

	public:
		//************************************
		// Method:    Is text data or not(binary)
		//************************************
		bool IsTextData();

		//************************************
		// Method:    Set body binary Data
		// Parameter: BYTE * pBuf
		// Parameter: int len
		//************************************
		bool SetBinaryData(BYTE* buf, int len);

		//************************************
		// Method:    Set Text Data
		// Parameter: string strText
		//************************************
		bool SetTextData(string strText);

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
		// Parameter: HttpBody & body
		// Parameter: bool & bSuccess
		//************************************
		static int ParseFromBuf(BYTE* pBuf, int len, HttpBody& body, bool& bSuccess);
	};
}