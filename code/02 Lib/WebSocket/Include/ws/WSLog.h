#pragma once

#include <string>
#include <minwindef.h>
#include <functional>
using namespace std;
using namespace std::placeholders;


namespace ws
{
	// websocket log type
	enum class EWSLogType
	{
		Info,		// Info
		Debug,		// Debug
		Warn,		// Warn
		Error,		// Error
		fatal,		// Fatal
		
		None
	};


	// Ws Log Callback fn
	// EWSLogType:	websocket Log Type
	// string:		Log
	// bool:		whether output to console
	typedef std::function<void(EWSLogType, string, bool)> WSLogCallback;


	// Websocket Log
	class WSLog final
	{
	private:
		WSLog();

	private:
		static WSLogCallback fn;		// websocket Log Callback fn

	public:
		//************************************
		// Method:    Set callback fn
		// Parameter: WSLogCallback fn
		//************************************
		static void SetCallbackFn(WSLogCallback fn);

		//************************************
		// Method:    WriteLine
		// Parameter: EWSLogType type
		// Parameter: bool bOutputConsole:	whether output to console
		// Parameter: string format
		// Parameter: ...
		//************************************
		static void WriteLine(EWSLogType type, bool bIsOutputConsole, string format, ...);
	};
}