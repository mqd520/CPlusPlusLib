#include "stdafx.h"
#include "Include/ws/WSException.h"

namespace ws
{
	WSException::WSException(EWSExceptionCode code) :
		code(code)
	{

	}

	WSException::~WSException()
	{

	}

	EWSExceptionCode WSException::GetCode()
	{
		return code;
	}

	string WSException::GetErrorInfo()
	{
		if (code == EWSExceptionCode::OutBuf)
		{
			return "out of buf";
		}

		if (code == EWSExceptionCode::HttpError)
		{
			return "parse http request fail";
		}

		if (code == EWSExceptionCode::DenyGet)
		{
			return "only allow http GET request";
		}

		if (code == EWSExceptionCode::KeyEmpty)
		{
			return "ws key must be not empty";
		}

		return "None";
	}
}