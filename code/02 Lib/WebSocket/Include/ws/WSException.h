#pragma once

#include <string>
using namespace std;

namespace ws
{
	// websocket exception code
	enum class EWSExceptionCode : int
	{
		OutBuf			= 101,			// out of buf
		DenyGet			= 102,			// deny http GET request
		KeyEmpty		= 103,			// Key must be not empty
		HttpError		= 104,			// http request error

		None			= 999			// None
	};


	// websocket exception
	class WSException
	{
	public:
		WSException(EWSExceptionCode code);
		~WSException();

	private:
		EWSExceptionCode code;	// websocket exception code

	public:
		//************************************
		// Method:    Get exception code
		//************************************
		EWSExceptionCode GetCode();

		//************************************
		// Method:    Get exception info
		//************************************
		string GetErrorInfo();
	};
}