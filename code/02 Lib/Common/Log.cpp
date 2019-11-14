#include "stdafx.h"
#include "Include/com/Log.h"

#include "Include/com/TimeTool.h"


#define Log_MaxLogLength		(1024)		// max log string length


namespace com
{
	vector<LogCallback> Log::callbacks;


	Log::Log()
	{

	}

	string Log::GetLogTypeStr(ELogType type)
	{
		char ch[10] = { 0 };

		if (type == ELogType::Info)
		{
			sprintf_s(ch, "%s", "[Info ]");
		}
		else if (type == ELogType::Debug)
		{
			sprintf_s(ch, "%s", "[Debug]");
		}
		else if (type == ELogType::Warn)
		{
			sprintf_s(ch, "%s", "[Warn ]");
		}
		else if (type == ELogType::Error)
		{
			sprintf_s(ch, "%s", "[Error]");
		}
		else if (type == ELogType::Fatal)
		{
			sprintf_s(ch, "%s", "[Fatal]");
		}
		else if (type == ELogType::Sql)
		{
			sprintf_s(ch, "%s", "[SQL]");
		}
		else if (type == ELogType::Http)
		{
			sprintf_s(ch, "%s", "[Http]");
		}

		return ch;
	}

	void Log::Write_2_Console(ELogType type, const string& log, bool bWrite2File, bool bPrefix1, bool bPrefix2, bool bColor)
	{
		string log1;
		string prefix = "";

		if (bPrefix1)
		{
			prefix += GetLogTypeStr(type) + " ";
		}


		if (bPrefix2)
		{
			//string str = TimeTool::GetCurrentTimeStr();
			//prefix += "[" + str + "] ";
		}

		log1 = prefix + log;


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
				color = FOREGROUND_RED;
			}
			else if (type == ELogType::Fatal)
			{
				color = FOREGROUND_RED | FOREGROUND_INTENSITY;
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
			printf("%s \n", log1.c_str());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else
		{
			printf("%s \n", log1.c_str());
		}


		if (bWrite2File)
		{
			Write_2_File(type, log1);
		}
	}

	void Log::Write_2_Console(ELogType type, const string& log, bool bWrite2File)
	{
		Write_2_Console(type, log, bWrite2File, true, true, true);
	}

	void Log::Write_2_Console(ELogType type, bool bWrite2File, bool bPrefix1, bool bPrefix2, bool bColor, const char* format, ...)
	{
		char ch[Log_MaxLogLength] = { 0 };
		va_list argPtr;
		va_start(argPtr, format);
		vsprintf_s(ch, Log_MaxLogLength - 1, format, argPtr);
		va_end(argPtr);

		Write_2_Console(type, ch, bWrite2File, bPrefix1, bPrefix2, bColor);
	}

	void Log::Write_2_Console(ELogType type, bool bWrite2File, const char* format, ...)
	{
		char ch[Log_MaxLogLength] = { 0 };
		va_list argPtr;
		va_start(argPtr, format);
		vsprintf_s(ch, Log_MaxLogLength - 1, format, argPtr);
		va_end(argPtr);

		Write_2_Console(type, ch, bWrite2File, true, true, true);
	}

	void Log::Write_2_File(ELogType type, const string& log)
	{
		for (auto & it : callbacks)
		{
			if (!it._Empty())
			{
				it(type, (string&)log);
			}
		}
	}

	void Log::Write_2_File(ELogType type, const string& log, bool bPrefix1, bool bPrefix2)
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

		Write_2_File(type, log1);
	}

	void Log::Write_2_File(ELogType type, bool bPrefix1, bool bPrefix2, const char* format, ...)
	{
		char ch[Log_MaxLogLength] = { 0 };
		va_list argPtr;
		va_start(argPtr, format);
		vsprintf_s(ch, Log_MaxLogLength - 1, format, argPtr);
		va_end(argPtr);

		Write_2_File(type, ch, bPrefix1, bPrefix2);
	}

	void Log::RegLogCallback(LogCallback callback)
	{
		callbacks.emplace_back(callback);
	}
}