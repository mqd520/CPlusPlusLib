#include "stdafx.h"
#include "Include/hc/Log.h"


#define MaxLogBufLen		(1024)			// max log buf len


namespace hc
{
	HttpClientLogCallback HttpClientLog::fn;

	HttpClientLog::HttpClientLog()
	{

	}

	void HttpClientLog::SetCallbackFn(HttpClientLogCallback fn)
	{
		HttpClientLog::fn = fn;
	}

	void HttpClientLog::WriteLine(EHttpClientLogType type, bool bOutputConsole, string format, ...)
	{
		char log[MaxLogBufLen] = { 0 };
		va_list argPtr;
		va_start(argPtr, format);
		vsprintf_s(log, MaxLogBufLen - 1, format.c_str(), argPtr);
		va_end(argPtr);

		if (!HttpClientLog::fn._Empty())
		{
			HttpClientLog::fn(type, log, bOutputConsole);
		}
	}
}