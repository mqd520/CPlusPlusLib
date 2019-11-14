#pragma once

#include <string>
#include <vector>
using namespace std;

namespace hc
{
	// common tool
	class CommonTool final
	{
	private:
		CommonTool();

	public:
		static void Split(const string& strSrc, vector<string>& vec, const string& strFind);

		static string UTF16_2_GB2312(wchar_t* pStr);

		static wstring GB2312_2_UTF16(char* pStr);
	};
}