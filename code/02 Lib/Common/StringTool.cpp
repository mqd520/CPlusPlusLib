#include "stdafx.h"
#include "Include/com/StringTool.h"

#include <regex>
#include <iostream>
#include <sstream>
using namespace std;

#include "Include/com/BufferTool.h"



namespace com
{
	StringTool::StringTool()
	{

	}

	string StringTool::UTF16_2_GB2312(wchar_t* pStr)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, pStr, -1, NULL, 0, NULL, NULL);
		char* aStr = new char[len];
		WideCharToMultiByte(CP_ACP, 0, pStr, -1, aStr, len, NULL, NULL);

		string result = aStr;
		delete aStr;

		return result;
	}

	string StringTool::UTF16_2_UTF8(wchar_t* pStr)
	{
		int len = WideCharToMultiByte(CP_UTF8, 0, pStr, -1, NULL, 0, NULL, NULL);
		char* aStr = new char[len];
		WideCharToMultiByte(CP_UTF8, 0, pStr, -1, aStr, len, NULL, NULL);

		string result = aStr;
		delete aStr;

		return result;
	}

	wstring StringTool::GB2312_2_UTF16(char* pStr)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, pStr, -1, NULL, 0);
		wchar_t* wStr = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, pStr, -1, wStr, len);

		wstring result = wStr;
		delete wStr;

		return result;
	}

	string StringTool::GB2312_2_UTF8(char* pStr)
	{
		wstring wStr = GB2312_2_UTF16(pStr);
		return UTF16_2_UTF8((wchar_t*)wStr.c_str());
	}

	wstring StringTool::UTF8_2_UTF16(char* pStr)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, pStr, -1, NULL, 0);
		wchar_t* wStr = new WCHAR[len];
		MultiByteToWideChar(CP_UTF8, 0, pStr, -1, wStr, len);

		wstring result = wStr;
		delete wStr;

		return result;
	}

	string StringTool::UTF8_2_GB2312(char* pStr)
	{
		wstring wStr = UTF8_2_UTF16(pStr);
		return UTF16_2_GB2312((wchar_t*)wStr.c_str());
	}

	void StringTool::GetGB2312StrLen(char* pStr, int* charLen /*= nullptr*/, int* byteLen /*= nullptr*/)
	{
		if (charLen)
		{
			wstring utf16Str = GB2312_2_UTF16(pStr);
			GetUTF16StrLen((wchar_t*)utf16Str.c_str(), charLen, nullptr);
		}

		if (byteLen)
		{
			*byteLen = strlen(pStr);
		}
	}

	void StringTool::GetUTF16StrLen(wchar_t* pStr, int* charLen /*= nullptr*/, int* byteLen /*= nullptr*/)
	{
		if (charLen)
		{
			*charLen = wcslen(pStr);
		}

		if (byteLen)
		{
			*byteLen = wcslen(pStr) * 2;
		}
	}

	void StringTool::GetUTF8StrLen(char* pStr, int* charLen /*= nullptr*/, int* byteLen /*= nullptr*/)
	{
		if (charLen)
		{
			wstring utf16Str = UTF8_2_UTF16(pStr);
			GetUTF16StrLen((wchar_t*)utf16Str.c_str(), charLen, nullptr);
		}

		if (byteLen)
		{
			*byteLen = strlen(pStr);
		}
	}

	INT16 StringTool::To_Int16(const string& str, const int& radix /*= 10*/, const INT16& def /*= 0*/)
	{
		INT16 result = def;

		string format = "%d";
		if (radix == 8)
		{
			format = "%o";
		}
		else if (radix == 16)
		{
			format = "%x";
		}
		int n = 0;
		sscanf_s(str.c_str(), format.c_str(), &n);
		result = n;

		return result;
	}

	UINT16 StringTool::To_UInt16(const string& str, const int& radix /*= 10*/, const UINT16& def /*= 0*/)
	{
		UINT16 result = def;

		string format = "%u";
		if (radix == 8)
		{
			format = "%o";
		}
		else if (radix == 16)
		{
			format = "%x";
		}
		int n = 0;
		sscanf_s(str.c_str(), format.c_str(), &n);
		result = n;

		return result;
	}

	INT32 StringTool::To_Int32(const string& str, const int& radix /*= 10*/, const INT32& def /*= 0*/)
	{
		INT32 result = def;

		string format = "%d";
		if (radix == 8)
		{
			format = "%o";
		}
		else if (radix == 16)
		{
			format = "%x";
		}
		sscanf_s(str.c_str(), format.c_str(), &result);

		return result;
	}

	UINT32 StringTool::To_UInt32(const string& str, const int& radix /*= 10*/, const UINT32& def /*= 0*/)
	{
		UINT32 result = def;

		string format = "%u";
		if (radix == 8)
		{
			format = "%o";
		}
		else if (radix == 16)
		{
			format = "%x";
		}
		sscanf_s(str.c_str(), format.c_str(), &result);

		return result;
	}

	INT64 StringTool::To_Int64(const string& str, const int& radix /*= 10*/, const INT64& def /*= 0*/)
	{
		INT64 result = def;

		string format = "%lld";
		if (radix == 8)
		{
			format = "%llo";
		}
		else if (radix == 16)
		{
			format = "%llx";
		}
		sscanf_s(str.c_str(), format.c_str(), &result);

		return result;
	}

	UINT64 StringTool::To_UInt64(const string& str, const int& radix /*= 10*/, const UINT64& def /*= 0*/)
	{
		UINT64 result = def;

		string format = "%llu";
		if (radix == 8)
		{
			format = "%llo";
		}
		else if (radix == 16)
		{
			format = "%llx";
		}
		sscanf_s(str.c_str(), format.c_str(), &result);

		return result;
	}

	FLOAT StringTool::To_Float(const string& str, const FLOAT& def /*= 0*/)
	{
		FLOAT result = def;

		sscanf_s(str.c_str(), "%f", &result);

		return result;
	}

	double StringTool::To_Double(const string& str, const double& def /*= 0*/)
	{
		double result = def;

		sscanf_s(str.c_str(), "%lf", &result);

		return result;
	}

	vector<string> StringTool::Split(const string& strSrc, const string& strFind)
	{
		vector<string> vec;

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

		return vec;
	}

	string StringTool::ToLower(const string& str)
	{
		string result = str;

		int len = result.size();
		for (int i = 0; i < len; i++)
		{
			if (result[i] >= 'A' && result[i] <= 'Z')
			{
				result[i] += 32;
			}
		}

		return result;
	}

	string StringTool::ToUpper(const string& str)
	{
		string result = str;

		int len = result.size();
		for (int i = 0; i < len; i++)
		{
			if (result[i] >= 'a' && result[i] <= 'z')
			{
				result[i] -= 32;
			}
		}

		return result;
	}

	string StringTool::TrimLeft(const string& str)
	{
		string result = str;

		if (str.empty())
		{
			return result;
		}

		int n1 = result.find_first_not_of(" ");
		if (n1 > 0)
		{
			result.erase(0, n1);
		}

		return result;
	}

	string StringTool::TrimRight(const string& str)
	{
		string result = str;

		if (str.empty())
		{
			return result;
		}

		int n2 = result.find_last_not_of(" ");
		if (n2 < (int)result.size() - 1)
		{
			result.erase(n2 + 1);
		}

		return result;
	}

	string StringTool::Trim(const string& str)
	{
		string result = str;

		if (str.empty())
		{
			return result;
		}

		int n1 = result.find_first_not_of(" ");
		if (n1 > 0)
		{
			result.erase(0, n1);
		}

		int n2 = result.find_last_not_of(" ");
		if (n2 < (int)result.size() - 1)
		{
			result.erase(n2 + 1);
		}

		return result;
	}

	bool StringTool::StartWith(const string& src, const string& str, bool icase /*= true*/)
	{
		bool result = false;

		if (!src.empty() && !str.empty() && (int)src.size() >= (int)str.size())
		{
			string src1, str1;
			if (icase)
			{
				src1 = StringTool::ToLower(src);
				str1 = StringTool::ToLower(str);
			}
			else
			{
				src1 = src;
				str1 = str;
			}

			if (src1.find(str1) == 0)
			{
				result = true;
			}
		}

		return result;
	}

	bool StringTool::EndWith(const string& src, const string& str, bool icase /*= true*/)
	{
		bool result = false;

		if (!src.empty() && !str.empty() && (int)src.size() >= (int)str.size())
		{
			string src1, str1;
			if (icase)
			{
				src1 = StringTool::ToLower(src);
				str1 = StringTool::ToLower(str);
			}
			else
			{
				src1 = src;
				str1 = str;
			}

			int len = (int)src1.size() - (int)str1.size();
			string str2 = src1.substr(len);
			if (str2 == str1)
			{
				result = true;
			}
		}

		return result;
	}

	string StringTool::Replace(const string& src, const string& search, const string& val, const bool& iCase /*= false*/)
	{
		string result = src;

		if (!src.empty() && !search.empty())
		{
			if (iCase)
			{
				regex pattern(StringTool::ToLower(search));
				result = regex_replace(StringTool::ToLower(src), pattern, val);
			}
			else
			{
				regex pattern(search);
				result = regex_replace(src, pattern, val);
			}
		}

		return result;
	}

	string StringTool::Format(char* format, ...)
	{
		char ch[1024] = { 0 };
		va_list argPtr;
		va_start(argPtr, format);
		vsprintf_s(ch, 1024 - 1, format, argPtr);
		va_end(argPtr);

		return ch;
	}

	string StringTool::FillIn(const string& src, const int& max /*= 10*/, const string& str /*= "0"*/, const bool& b /*= true*/)
	{
		string result = src;

		if (max > 0 && !str.empty())
		{
			wstring str1 = GB2312_2_UTF16((char*)str.c_str());
			wstring result1 = GB2312_2_UTF16((char*)result.c_str());
			int len1 = 0;
			GetUTF16StrLen((wchar_t*)result1.c_str(), &len1);

			int max2 = max - len1;
			if (max2 > 0)
			{
				wstring str2;
				int len2 = 0;
				while (max2 > len2)
				{
					str2 += str1;
					GetUTF16StrLen((wchar_t*)str2.c_str(), &len2);
				}

				if (len2 > max2)
				{
					str2 = str2.substr(0, max2);
				}

				if (b)
				{
					result1 = str2 + result1;
				}
				else
				{
					result1 = result1 + str2;
				}

				result = UTF16_2_GB2312((wchar_t*)result1.c_str());
			}
		}

		return result;
	}

	string StringTool::UrlEncode(const string& str)
	{
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++)
		{
			if (isalnum((unsigned char)str[i]) ||
				(str[i] == '-') ||
				(str[i] == '_') ||
				(str[i] == '.') ||
				(str[i] == '~'))
				strTemp += str[i];
			else if (str[i] == ' ')
				strTemp += "+";
			else
			{
				strTemp += '%';
				strTemp += BufferTool::ToHex((unsigned char)str[i] >> 4);
				strTemp += BufferTool::ToHex((unsigned char)str[i] % 16);
			}
		}
		return strTemp;
	}
}