#include "stdafx.h"
#include "Include/com/Log.h"

#include "Include/com/TimeTool.h"


#define Log_MaxLogLength		(1024)		// max log string length


string GetPathFile(const string& path);

namespace com
{
	vector<LogConsoleCallback>	Log::vecConsoleCallbacks;
	vector<LogFileCallback>		Log::vecFileCallbacks;
	vector<CustomLogTypeInfo>	Log::vecCustomTypes;


	Log::Log()
	{

	}

	void Log::WriteConsole(ELogType type, const string& log, bool bPrefix1, bool bPrefix2, bool bColor, ExtraLogInfo& info)
	{
		string prefix = "";

		if (bPrefix2)
		{
			prefix += "[" + TimeTool::Format(info.time, true, "yyyy-mm-dd HH:MM:ss.ff") + "] ";
		}

		if (bPrefix1)
		{
			prefix += "[" + GetLogTypeStr(type) + "] ";
		}

		string log1 = prefix + log;

		if (bColor)
		{
			WORD color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			if (type == ELogType::Debug)
			{
				color = FOREGROUND_BLUE | FOREGROUND_GREEN;
			}
			else if (type == ELogType::Warn)
			{
				color = FOREGROUND_RED | FOREGROUND_GREEN;
			}
			else if (type == ELogType::Error)
			{
				color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | FOREGROUND_INTENSITY;
			}
			else if (type == ELogType::Fatal)
			{
				color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | FOREGROUND_INTENSITY;
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
			printf("%s \n", log1.c_str());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else
		{
			printf("%s \n", log1.c_str());
		}
	}

	void Log::Write_2_Console(ELogType type, const string& log, bool bWrite2File, bool bPrefix1, bool bPrefix2, bool bColor,
		const string& strFunctionName, const string& strFilePath /*= __FILE__*/, int nRowNo /*= __LINE__*/)
	{
		ExtraLogInfo info = { GetPathFile(strFilePath), strFunctionName, nRowNo, 1, TimeTool::GetCurTimeStamp() };

		if (vecConsoleCallbacks.empty())
		{
			WriteConsole(type, log, bPrefix1, bPrefix2, bColor, info);
		}
		else
		{
			for (auto & it : vecConsoleCallbacks)
			{
				if (!it._Empty())
				{
					it(type, (string&)log, info);
				}
			}
		}

		if (bWrite2File)
		{
			for (auto & it : vecFileCallbacks)
			{
				if (!it._Empty())
				{
					it(type, (string&)log, info);
				}
			}
		}
	}

	void Log::Write_2_Console(ELogType type, const string& log, bool bWrite2File,
		const string& strFunctionName, const string& strFilePath /*= __FILE__*/, int nRowNo /*= __LINE__*/)
	{
		Write_2_Console(type, log, bWrite2File, true, true, true, strFunctionName, strFilePath, nRowNo);
	}

	void Log::Write_2_Console(ELogType type, bool bWrite2File, bool bPrefix1, bool bPrefix2, bool bColor,
		const string& strFunctionName, const string& strFilePath, int nRowNo,
		const char* format, ...)
	{
		char ch[Log_MaxLogLength] = { 0 };
		va_list argPtr;
		va_start(argPtr, format);
		vsprintf_s(ch, Log_MaxLogLength - 1, format, argPtr);
		va_end(argPtr);

		Write_2_Console(type, ch, bWrite2File, bPrefix1, bPrefix2, bColor, strFunctionName, strFilePath, nRowNo);
	}

	void Log::Write_2_Console(ELogType type, bool bWrite2File,
		const string& strFunctionName, const string& strFilePath, int nRowNo,
		const char* format, ...)
	{
		char ch[Log_MaxLogLength] = { 0 };
		va_list argPtr;
		va_start(argPtr, format);
		vsprintf_s(ch, Log_MaxLogLength - 1, format, argPtr);
		va_end(argPtr);

		Write_2_Console(type, ch, bWrite2File, true, true, true, strFunctionName, strFilePath, nRowNo);
	}

	void Log::Write_2_File(ELogType type, const string& log,
		const string& strFunctionName, const string& strFilePath /*= __FILE__*/, int nRowNo /*= __LINE__*/)
	{
		ExtraLogInfo info = { GetPathFile(strFilePath), strFunctionName, nRowNo, 1, TimeTool::GetCurTimeStamp() };

		for (auto & it : vecFileCallbacks)
		{
			if (!it._Empty())
			{
				it(type, (string&)log, info);
			}
		}
	}

	void Log::Write_2_File(ELogType type, const string& log, bool bPrefix1, bool bPrefix2,
		const string& strFunctionName, const string& strFilePath /*= __FILE__*/, int nRowNo /*= __LINE__*/)
	{
		string log1;
		string prefix = "";

		if (bPrefix1)
		{
			prefix += GetLogTypeStr(type) + " ";
		}

		if (bPrefix2)
		{
			string str = TimeTool::Format();
			prefix += "[" + str + "] ";
		}

		log1 = prefix + log;

		Write_2_File(type, log1, strFunctionName, strFilePath, nRowNo);
	}

	void Log::Write_2_File(ELogType type, bool bPrefix1, bool bPrefix2,
		const string& strFunctionName, const string& strFilePath, int nRowNo,
		const char* format, ...)
	{
		char ch[Log_MaxLogLength] = { 0 };
		va_list argPtr;
		va_start(argPtr, format);
		vsprintf_s(ch, Log_MaxLogLength - 1, format, argPtr);
		va_end(argPtr);

		Write_2_File(type, ch, bPrefix1, bPrefix2, strFunctionName, strFilePath, nRowNo);
	}

	void Log::RegLogConsoleCallback(LogConsoleCallback callback)
	{
		vecConsoleCallbacks.emplace_back(callback);
	}

	void Log::RegLogFileCallback(LogFileCallback callback)
	{
		vecFileCallbacks.emplace_back(callback);
	}

	string Log::GetLogTypeStr(ELogType type)
	{
		char ch[10] = { 0 };

		if (type == ELogType::Info)
		{
			sprintf_s(ch, "%s", "Info");
		}
		else if (type == ELogType::Debug)
		{
			sprintf_s(ch, "%s", "Debug");
		}
		else if (type == ELogType::Warn)
		{
			sprintf_s(ch, "%s", "Warn");
		}
		else if (type == ELogType::Error)
		{
			sprintf_s(ch, "%s", "Error");
		}
		else if (type == ELogType::Fatal)
		{
			sprintf_s(ch, "%s", "Fatal");
		}
		else if (type == ELogType::Sql)
		{
			sprintf_s(ch, "%s", "SQL");
		}
		else if (type == ELogType::Http)
		{
			sprintf_s(ch, "%s", "Http");
		}

		return ch;
	}

	bool Log::AddCustomLogType(int type, const string& strType)
	{
		bool result = false;

		for (auto & it : vecCustomTypes)
		{
			if (it.type == type)
			{
				break;
			}
		}

		if (!result)
		{
			vecCustomTypes.push_back({ type, strType });
		}

		return result;
	}
}

string GetPathFile(const string& path)
{
	string::size_type index = path.find_last_of("/");
	if (index != string::npos)
	{
		return path.substr(index + 1);
	}

	return "";
}