#include "stdafx.h"
#include "StringDemo.h"

void StringDemo::Init()
{
	setlocale(LC_ALL, "");
}

void StringDemo::Test1()
{
	wchar_t* strUTF16 = L"ºº×ÖabcABC123!@#";
	int clen1 = 0;
	int blen1 = 0;
	StringTool::GetUTF16StrLen(strUTF16, &clen1, &blen1);
	wprintf(L"strUTF16: %ls, char len: %d, byte len: %d \n", strUTF16, clen1, blen1);

	string strGB2312 = StringTool::UTF16_2_GB2312(strUTF16);
	int clen2 = 0;
	int blen2 = 0;
	StringTool::GetGB2312StrLen((char*)strGB2312.c_str(), &clen2, &blen2);
	printf("strGB2312: %s, char len: %d, byte len: %d \n", strGB2312.c_str(), clen2, blen2);

	string strUTF8 = StringTool::UTF16_2_UTF8(strUTF16);
	int clen3 = 0;
	int blen3 = 0;
	StringTool::GetUTF8StrLen((char*)strUTF8.c_str(), &clen3, &blen3);
	printf("strUTF8: %s, char len: %d, byte len: %d \n", strUTF8.c_str(), clen3, blen3);
}