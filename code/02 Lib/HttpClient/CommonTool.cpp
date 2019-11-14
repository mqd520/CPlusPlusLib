#include "stdafx.h"
#include "CommonTool.h"

namespace hc
{
	CommonTool::CommonTool()
	{

	}

	void CommonTool::Split(const string& strSrc, vector<string>& vec, const string& strFind)
	{
		string::size_type pos1, pos2;
		pos2 = strSrc.find(strFind);
		pos1 = 0;

		while (string::npos != pos2)
		{
			vec.push_back(strSrc.substr(pos1, pos2 - pos1));

			pos1 = pos2 + strFind.size();
			pos2 = strSrc.find(strFind, pos1);
		}

		if (pos1 != strSrc.length())
		{
			vec.push_back(strSrc.substr(pos1));
		}
	}

	string CommonTool::UTF16_2_GB2312(wchar_t* pStr)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, pStr, -1, NULL, 0, NULL, NULL);
		char* aStr = new char[len];
		WideCharToMultiByte(CP_ACP, 0, pStr, -1, aStr, len, NULL, NULL);

		return aStr;
	}

	wstring CommonTool::GB2312_2_UTF16(char* pStr)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, pStr, -1, NULL, 0);
		wchar_t* wStr = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, pStr, -1, wStr, len);

		return wStr;
	}
}