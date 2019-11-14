#pragma once

#include <string>
#include <functional>
#include <vector>
using namespace std;
using namespace std::placeholders;


namespace com
{
	// Log Type
	enum class ELogType
	{
		Info = 1,		// Info
		Debug = 2,		// Debug
		Warn = 3,		// Warn
		Error = 4,		// Error
		Fatal = 5,		// Fatal

		Sql = 100,		// Sql request
		Http = 101		// Http request
	};

	// Log Callback
	// ELogType:		Log Type
	// string&:			log
	using LogCallback = std::function < void(ELogType, string&) > ;


	// Log
	class Log final
	{
	private:
		Log();

	private:
		static vector<LogCallback> callbacks;		// callback list

	protected:
		//************************************
		// Method:    Get Log Type Str
		// Parameter: ELogType type
		//************************************
		static string GetLogTypeStr(ELogType type);

	public:
		//************************************
		// Method:    Write to Console
		// Parameter: ELogType type
		// Parameter: const string & log
		// Parameter: bool bWrite2File, whether write to file
		// Parameter: bool bPrefix1, whether show Log Type String
		// Parameter: bool bPrefix2, whether show Datetime String
		// Parameter: bool bColor,   whether show different color
		//************************************
		static void Write_2_Console(ELogType type, const string& log, bool bWrite2File, bool bPrefix1, bool bPrefix2, bool bColor);

		//************************************
		// Method:    Write to Console
		// Parameter: ELogType type
		// Parameter: const string & log
		// Parameter: bool bWrite2File
		//************************************
		static void Write_2_Console(ELogType type, const string& log, bool bWrite2File);

		//************************************
		// Method:    Write to Console
		// Parameter: ELogType type
		// Parameter: bool bWrite2File
		// Parameter: bool bPrefix1
		// Parameter: bool bPrefix2
		// Parameter: bool bColor
		// Parameter: const string & format
		// Parameter: ...
		//************************************
		static void Write_2_Console(ELogType type, bool bWrite2File, bool bPrefix1, bool bPrefix2, bool bColor, const char* format, ...);

		//************************************
		// Method:    Write to Console
		// Parameter: ELogType type
		// Parameter: bool bWrite2File
		// Parameter: const string & format
		// Parameter: ...
		//************************************
		static void Write_2_Console(ELogType type, bool bWrite2File, const char* format, ...);

		//************************************
		// Method:    Write to File
		// Parameter: ELogType type
		// Parameter: const string & log
		//************************************
		static void Write_2_File(ELogType type, const string& log);

		//************************************
		// Method:    Write to File
		// Parameter: ELogType type
		// Parameter: const string & log
		// Parameter: bool bWrite2File, whether write to file
		// Parameter: bool bPrefix1, whether show Log Type String
		// Parameter: bool bPrefix2, whether show Datetime String
		// Parameter: bool bColor,   whether show different color
		//************************************
		static void Write_2_File(ELogType type, const string& log, bool bPrefix1, bool bPrefix2);

		//************************************
		// Method:    Write to File
		// Parameter: ELogType type
		// Parameter: bool bPrefix1
		// Parameter: bool bPrefix2
		// Parameter: const string & format
		// Parameter: ...
		//************************************
		static void Write_2_File(ELogType type, bool bPrefix1, bool bPrefix2, const char* format, ...);

		//************************************
		// Method:    Reg Common Log Callback
		// Parameter: LogCallback callback
		//************************************
		static void RegLogCallback(LogCallback callback);
	};

	// Write to File
	// Parameter: ELogType type
	// Parameter: const string & format
	// Parameter: ...
#define Write2File(type, format, ...)					Log::Write_2_File(type, true, true, format, __VA_ARGS__)

	// Write to Console
	// Parameter: ELogType type
	// Parameter: const string & format
	// Parameter: ...
#define Write2Console(type, format, ...)				Log::Write_2_Console(type, true, format, __VA_ARGS__)

}