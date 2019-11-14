#pragma once

#include <minwindef.h>
#include <functional>
using namespace std;
using namespace std::placeholders;

namespace hc
{
	// HttpClient Log Type
	enum class EHttpClientLogType : int
	{
		Info,		// Info
		Debug,		// Debug
		Warn,		// Warn
		Error,		// Error
		Fatal,		// Fatal

		None		// None
	};


	// DbLog Callback fn
	// EHttpClientLogType:	HttpClient Log Type
	// string:				Log
	// bool:				whether output to console
	typedef std::function<void(EHttpClientLogType, string, bool)> HttpClientLogCallback;


	// HttpClient Log
	class HttpClientLog final
	{
	private:
		HttpClientLog();

	private:
		static HttpClientLogCallback fn;		// HttpClient Log Callback fn

	public:
		//************************************
		// Method:    Set callback fn
		// Parameter: HttpClientLogCallback fn
		//************************************
		static void SetCallbackFn(HttpClientLogCallback fn);

		//************************************
		// Method:    WriteLine
		// Parameter: EDbLogType type
		// Parameter: bool bOutputConsole:	whether output to console
		// Parameter: string format
		// Parameter: ...
		//************************************
		static void WriteLine(EHttpClientLogType type, bool bOutputConsole, string format, ...);
	};
}