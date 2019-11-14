#include "stdafx.h"
#include "Include/ws/WSLog.h"

#define MaxLogBufLen		(1024)			// max log buf len


namespace ws
{
	WSLogCallback WSLog::fn;

	WSLog::WSLog()
	{

	}

	void WSLog::SetCallbackFn(WSLogCallback fn)
	{
		WSLog::fn = fn;
	}

	void WSLog::WriteLine(EWSLogType type, bool bOutputConsole, string format, ...)
	{
		char log[MaxLogBufLen] = { 0 };
		va_list argPtr;
		va_start(argPtr, format);
		vsprintf_s(log, MaxLogBufLen - 1, format.c_str(), argPtr);
		va_end(argPtr);

		if (!WSLog::fn._Empty())
		{
			WSLog::fn(type, log, bOutputConsole);
		}
	}
}