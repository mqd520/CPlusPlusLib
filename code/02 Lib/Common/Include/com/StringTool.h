#pragma once

#include <string>
#include <vector>
using namespace std;


#define GB2312EndCharByteLen	(1)		// length of GB2312 end char 
#define UTF16EndCharByteLen		(2)		// length of UTF16 end char 
#define UTF8EndCharByteLen		(1)		// length of UTF8 end char 


namespace com
{
	// string tool
	class StringTool final
	{
	private:
		StringTool();

	public:
		//************************************
		// Method:    UTF16 to GB2312
		// Parameter: wchar_t * pStr
		//************************************
		static string UTF16_2_GB2312(wchar_t* pStr);

		//************************************
		// Method:    UTF16 to UTF8
		// Parameter: wchar_t * pStr
		//************************************
		static string UTF16_2_UTF8(wchar_t* pStr);

		//************************************
		// Method:    GB2312 to UTF16
		// Parameter: char * pStr
		//************************************
		static wstring GB2312_2_UTF16(char* pStr);

		//************************************
		// Method:    GB2312 to UTF8
		// Parameter: char * pStr
		//************************************
		static string GB2312_2_UTF8(char* pStr);

		//************************************
		// Method:    UTF8 to UTF16
		// Parameter: char * pStr
		//************************************
		static wstring UTF8_2_UTF16(char* pStr);

		//************************************
		// Method:    UTF8 to GB2312
		// Parameter: char * pStr
		//************************************
		static string UTF8_2_GB2312(char* pStr);

		//************************************
		// Method:    Get GB2312 String char length and byte length
		// Parameter: char * pStr
		// Parameter: int * charLen
		// Parameter: int * byteLen
		//************************************
		static void GetGB2312StrLen(char* pStr, int* charLen = nullptr, int* byteLen = nullptr);

		//************************************
		// Method:    Get UTF16 String char length and byte length
		// Parameter: wchar_t * pStr
		// Parameter: int * charLen
		// Parameter: int * byteLen
		//************************************
		static void GetUTF16StrLen(wchar_t* pStr, int* charLen = nullptr, int* byteLen = nullptr);

		//************************************
		// Method:    Get UTF8 String char length and byte length
		// Parameter: char * pStr
		// Parameter: int * charLen
		// Parameter: int * byteLen
		//************************************
		static void GetUTF8StrLen(char* pStr, int* charLen = nullptr, int* byteLen = nullptr);

		//************************************
		// Method:    To Int16
		// Parameter: const string & str
		// Parameter: const int& radix = 10
		// Parameter: const INT16& def = 0, default value
		//************************************
		static INT16 To_Int16(const string& str, const int& radix = 10, const INT16& def = 0);

		//************************************
		// Method:    To UINT16
		// Parameter: const string & str
		// Parameter: const int& radix = 10
		// Parameter: const UINT16& def = 0, default value
		//************************************
		static UINT16 To_UInt16(const string& str, const int& radix = 10, const UINT16& def = 0);

		//************************************
		// Method:    To INT32
		// Parameter: const string & str
		// Parameter: const int& radix = 10
		// Parameter: const INT32& def = 0, default value
		//************************************
		static INT32 To_Int32(const string& str, const int& radix = 10, const INT32& def = 0);

		//************************************
		// Method:    To UINT32
		// Parameter: const string & str
		// Parameter: const int& radix = 10
		// Parameter: const UINT32& def = 0, default value
		//************************************
		static UINT32 To_UInt32(const string& str, const int& radix = 10, const UINT32& def = 0);

		//************************************
		// Method:    To INT64
		// Parameter: const string & str
		// Parameter: const int& radix = 10
		// Parameter: const INT64& def = 0, default value
		//************************************
		static INT64 To_Int64(const string& str, const int& radix = 10, const INT64& def = 0);

		//************************************
		// Method:    To UINT64
		// Parameter: const string & str
		// Parameter: const int& radix = 10
		// Parameter: const UINT64& def = 0, default value
		//************************************
		static UINT64 To_UInt64(const string& str, const int& radix = 10, const UINT64& def = 0);

		//************************************
		// Method:    To FLOAT
		// Parameter: const string & str
		// Parameter: const int& decimalLen = 2
		// Parameter: const FLOAT& def = 0, default value
		//************************************
		static FLOAT To_Float(const string& str, const FLOAT& def = 0);

		//************************************
		// Method:    To double
		// Parameter: const string & str
		// Parameter: const int& decimalLen = 2
		// Parameter: const double& def = 0, default value
		//************************************
		static double To_Double(const string& str, const double& def = 0);

		//************************************
		// Method:    Split
		// Parameter: const string & strSrc
		// Parameter: const string & strFind
		//************************************
		static vector<string> Split(const string& strSrc, const string& strFind);

		//************************************
		// Method:    To Lower String
		// Parameter: string & str
		//************************************
		static string ToLower(const string& str);

		//************************************
		// Method:    To Upper String
		// Parameter: string & str
		//************************************
		static string ToUpper(const string& str);

		//************************************
		// Method:    Trim left
		// Parameter: string & str
		//************************************
		static string TrimLeft(const string& str);

		//************************************
		// Method:    Trim right
		// Parameter: string & str
		//************************************
		static string TrimRight(const string& str);

		//************************************
		// Method:    Trim
		// Parameter: string & str
		//************************************
		static string Trim(const string& str);

		//************************************
		// Method:    Is Src Start With str
		// Returns:   bool
		// Parameter: const string & src
		// Parameter: const string & str
		// Parameter: bool icase
		//************************************
		static bool StartWith(const string& src, const string& str, bool icase = true);

		//************************************
		// Method:    Is Src End With str
		// Returns:   bool
		// Parameter: const string & src
		// Parameter: const string & str
		// Parameter: bool icase
		//************************************
		static bool EndWith(const string& src, const string& str, bool icase = true);

		//************************************
		// Method:    Replace
		// Parameter: const string & src
		// Parameter: const string & search
		// Parameter: const string & val
		//************************************
		static string Replace(const string& src, const string& search, const string& val, const bool& iCase = false);

		//************************************
		// Method:    Format
		// Parameter: const string & format
		// Parameter: ...
		//************************************
		static string Format(char* format, ...);

		//************************************
		// Method:    FillIn String
		// Parameter: const string & src
		// Parameter: const int & max: max char length
		// Parameter: const string & str
		// Parameter: const bool& b = true, whether fill in from the left
		//************************************
		static string FillIn(const string& src, const int& max = 10, const string& str = "0", const bool& b = true);

		//************************************
		// Method:    Url Encode
		// Parameter: const string & str
		//************************************
		static string UrlEncode(const string& str);
	};
}