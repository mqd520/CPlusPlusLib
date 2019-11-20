#pragma once

#include <string>
#include <functional>
#include <vector>
using namespace std;
using namespace std::placeholders;


#define		ELogType_Custom			(1000)			// custom log type

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


	// Extra log info
	typedef struct tagExtraLogInfo
	{
		string	strFileName;	// file name
		string strFunctionName;	// function name
		int		nRowNo;			// row no.
		DWORD	nThreadId;		// thread Id
		time_t	time;			// time
	}ExtraLogInfo;	// Extra log info


	// Custom Log Type Info
	typedef struct tagCustomLogTypeInfo
	{
		int		type;		// Custom log type
		string	strType;	// Custom log type text
	}CustomLogTypeInfo;


	// Log console callback
	// ELogType:		Log Type
	// string&:			Log
	// ExtraLogInfo&:	Extra log info
	using LogConsoleCallback = std::function < void(ELogType, string&, ExtraLogInfo&) >;


	// Log file callback
	// ELogType:		Log Type
	// string&:			log
	// ExtraLogInfo&:	Extra log info
	using LogFileCallback = std::function < void(ELogType, string&, ExtraLogInfo&) >;


	// Log
	class Log final
	{
	private:
		Log();

	private:
		static vector<LogConsoleCallback>	vecConsoleCallbacks;		// Log console callback list
		static vector<LogFileCallback>		vecFileCallbacks;			// Log file callback list
		static vector<CustomLogTypeInfo>	vecCustomTypes;				// Custom Log type info list

	private:
		//************************************
		// Method:    WriteConsole
		// Parameter: ELogType type
		// Parameter: const string & log
		// Parameter: bool bPrefix1
		// Parameter: bool bPrefix2
		// Parameter: bool bColor
		// Parameter: ExtraLogInfo & info
		//************************************
		static void WriteConsole(ELogType type, const string& log, bool bPrefix1, bool bPrefix2, bool bColor, ExtraLogInfo& info);

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
		static void Write_2_Console(ELogType type, const string& log, bool bWrite2File, bool bPrefix1, bool bPrefix2, bool bColor,
			const string& strFunctionName, const string& strFilePath = __FILE__, int nRowNo = __LINE__);

		//************************************
		// Method:    Write to Console
		// Parameter: ELogType type
		// Parameter: const string & log
		// Parameter: bool bWrite2File
		//************************************
		static void Write_2_Console(ELogType type, const string& log, bool bWrite2File,
			const string& strFunctionName, const string& strFilePath = __FILE__, int nRowNo = __LINE__);

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
		static void Write_2_Console(ELogType type, bool bWrite2File, bool bPrefix1, bool bPrefix2, bool bColor,
			const string& strFunctionName, const string& strFilePath, int nRowNo,
			const char* format, ...);

		//************************************
		// Method:    Write to Console
		// Parameter: ELogType type
		// Parameter: bool bWrite2File
		// Parameter: const string & format
		// Parameter: ...
		//************************************
		static void Write_2_Console(ELogType type, bool bWrite2File,
			const string& strFunctionName, const string& strFilePath, int nRowNo,
			const char* format, ...);

		//************************************
		// Method:    Write to File
		// Parameter: ELogType type
		// Parameter: const string & log
		//************************************
		static void Write_2_File(ELogType type, const string& log,
			const string& strFunctionName, const string& strFilePath = __FILE__, int nRowNo = __LINE__);

		//************************************
		// Method:    Write to File
		// Parameter: ELogType type
		// Parameter: const string & log
		// Parameter: bool bWrite2File, whether write to file
		// Parameter: bool bPrefix1, whether show Log Type String
		// Parameter: bool bPrefix2, whether show Datetime String
		// Parameter: bool bColor,   whether show different color
		//************************************
		static void Write_2_File(ELogType type, const string& log, bool bPrefix1, bool bPrefix2,
			const string& strFunctionName, const string& strFilePath = __FILE__, int nRowNo = __LINE__);

		//************************************
		// Method:    Write to File
		// Parameter: ELogType type
		// Parameter: bool bPrefix1
		// Parameter: bool bPrefix2
		// Parameter: const string & format
		// Parameter: ...
		//************************************
		static void Write_2_File(ELogType type, bool bPrefix1, bool bPrefix2,
			const string& strFunctionName, const string& strFilePath, int nRowNo,
			const char* format, ...);

		//************************************
		// Method:    Reg Log Console Callback
		// Parameter: LogConsoleCallback callback
		//************************************
		static void RegLogConsoleCallback(LogConsoleCallback callback);

		//************************************
		// Method:    Reg Log File Callback
		// Parameter: LogFileCallback callback
		//************************************
		static void RegLogFileCallback(LogFileCallback callback);

		//************************************
		// Method:    Get Log Type Str
		// Parameter: ELogType type
		//************************************
		static string GetLogTypeStr(ELogType type);

		//************************************
		// Method:    Add Custom Log Type
		// Parameter: int type
		// Parameter: const string & strType
		//************************************
		static bool AddCustomLogType(int type, const string& strType);
	};


	// Write to Console
	// Parameter: ELogType type
	// Parameter: const string & format
	// Parameter: ...
#define Write2Console(type, strFunctionName, strFilePath, nRowNo, format, ...)				Log::Write_2_Console(type, true, strFunctionName, strFilePath, nRowNo, format, __VA_ARGS__)

	// Write to File
	// Parameter: ELogType type
	// Parameter: const string & format
	// Parameter: ...
#define Write2File(type, strFunctionName, strFilePath, nRowNo, format, ...)					Log::Write_2_File(type, true, true, strFunctionName, strFilePath, nRowNo, format, __VA_ARGS__)

}