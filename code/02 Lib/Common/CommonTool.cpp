#include "stdafx.h"
#include "Include/com/CommonTool.h"

#include "Include/com/StringTool.h"

#include <objbase.h>
#include <time.h>


namespace com
{
	CommonTool::CommonTool()
		= default;

	UINT32 CommonTool::ConvertIp(const string& ip)
	{
		UINT32 result = 0;

		vector<string> vec = StringTool::Split(ip, ".");
		if (vec.size() == 4 && !vec[0].empty() && !vec[1].empty() && !vec[2].empty() && !vec[3].empty())
		{
			int n1 = atoi(vec[0].c_str());
			int n2 = atoi(vec[1].c_str());
			int n3 = atoi(vec[2].c_str());
			int n4 = atoi(vec[3].c_str());

			result = (n1 << 24) | (n2 << 16) | (n3 << 8) | n4;
		}

		return result;
	}

	string CommonTool::ConvertIp(const UINT32& ip)
	{
		string result = "";

		BYTE n1 = ip >> 24;
		BYTE n2 = (ip << 8) >> 24;
		BYTE n3 = (ip << 16) >> 24;
		BYTE n4 = (ip << 24) >> 24;

		char ch[20] = { 0 };
		sprintf_s(ch, "%u.%u.%u.%u", n1, n2, n3, n4);

		result = ch;

		return result;
	}

	string CommonTool::GetCurrentExeDir()
	{
		string str = "";

		char chPath[MAX_PATH] = { 0 };
		GetModuleFileNameA(NULL, chPath, MAX_PATH);
		char* p = strrchr(chPath, '\\');
		if (p)
		{
			*(p + 1) = 0;
		}

		str = chPath;

		return str;
	}

	string CommonTool::GetCurrentExePath()
	{
		string str = "";

		char chPath[MAX_PATH] = { 0 };
		GetModuleFileNameA(NULL, chPath, MAX_PATH);

		str = chPath;

		return str;
	}

	string CommonTool::CreateGuid()
	{
		GUID guid;
		CoCreateGuid(&guid);
		char ch[64] = { 0 };

		sprintf_s(
			ch,
			sizeof(ch),
			"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1],
			guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);

		return ch;
	}

	string CommonTool::FormatGuid(string guid)
	{
		string str1 = StringTool::Replace(guid, "-", "");
		string str2 = StringTool::Replace(str1, "\\{", "");
		string str3 = StringTool::Replace(str2, "\\}", "");

		return str3;
	}

	string CommonTool::FormatGuid()
	{
		return FormatGuid(CreateGuid());
	}

	int CommonTool::Rand()
	{
		srand((unsigned int)time(NULL));

		return rand();
	}
}