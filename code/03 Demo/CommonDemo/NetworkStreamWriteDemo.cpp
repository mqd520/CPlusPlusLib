#include "stdafx.h"
#include "NetworkStreamWriteDemo.h"
#include "com/BufferTool.h"
#include "com/StringTool.h"


void NetworkStreamWriteDemo::Init()
{

}

void NetworkStreamWriteDemo::Test1()
{
	BYTE buf1[128] = { 0 };
	NetworkStreamWrite ns1(buf1, sizeof(buf1) / sizeof(BYTE), EEndian::little);
	INT16 val1 = 16;
	int len1 = ns1.WriteInt16(val1);
	INT32 val2 = 1;
	int len2 = ns1.WriteInt32(val2);
	string str1 = BufferTool::Join(buf1, len1 + len2, ", ", "%02d");
	printf("buf1: %s \n", str1.c_str());


	BYTE buf2[128] = { 0 };
	NetworkStreamWrite ns2(buf2, sizeof(buf2) / sizeof(BYTE), EEndian::big);
	INT16 val3 = 16;
	int len3 = ns2.WriteInt16(val3);
	INT32 val4 = 1;
	int len4 = ns2.WriteInt32(val4);
	string str2 = BufferTool::Join(buf2, len3 + len4, ", ", "%02d");
	printf("buf2: %s \n", str2.c_str());
}

void NetworkStreamWriteDemo::Test2()
{
	BYTE buf1[128] = { 0 };
	NetworkStreamWrite ns1(buf1, sizeof(buf1) / sizeof(BYTE));
	int len1 = ns1.WriteGB2312Str("ºº×ÖABCabc123!@#", false);
	string str1 = BufferTool::Join(buf1, len1, ", ", "%02d");
	printf("buf1: %s \n", str1.c_str());


	BYTE buf2[128] = { 0 };
	NetworkStreamWrite ns2(buf2, sizeof(buf2) / sizeof(BYTE));
	int len2 = ns2.WriteGB2312Str("ºº×ÖABCabc123!@#");
	string str2 = BufferTool::Join(buf2, len2, ", ", "%02d");
	printf("buf2: %s \n", str2.c_str());
}

void NetworkStreamWriteDemo::Test3()
{
	BYTE buf1[128] = { 0 };
	NetworkStreamWrite ns1(buf1, sizeof(buf1) / sizeof(BYTE), EEndian::little);
	int len1 = ns1.WriteUTF16Str(L"ºº×ÖABCabc123!@#", false);
	string str1 = BufferTool::Join(buf1, len1, ", ", "%02d");
	printf("buf1: %s \n", str1.c_str());


	BYTE buf2[128] = { 0 };
	NetworkStreamWrite ns2(buf2, sizeof(buf2) / sizeof(BYTE), EEndian::little);
	int len2 = ns2.WriteUTF16Str(L"ºº×ÖABCabc123!@#");
	string str2 = BufferTool::Join(buf2, len2, ", ", "%02d");
	printf("buf2: %s \n", str2.c_str());


	BYTE buf3[128] = { 0 };
	NetworkStreamWrite ns3(buf3, sizeof(buf3) / sizeof(BYTE), EEndian::big);
	int len3 = ns3.WriteUTF16Str(L"ºº×ÖABCabc123!@#", false);
	string str3 = BufferTool::Join(buf3, len3, ", ", "%02d");
	printf("buf3: %s \n", str3.c_str());


	BYTE buf4[128] = { 0 };
	NetworkStreamWrite ns4(buf4, sizeof(buf4) / sizeof(BYTE), EEndian::big);
	int len4 = ns4.WriteUTF16Str(L"ºº×ÖABCabc123!@#");
	string str4 = BufferTool::Join(buf4, len4, ", ", "%02d");
	printf("buf4: %s \n", str4.c_str());
}

void NetworkStreamWriteDemo::Test4()
{
	string strUTF8 = StringTool::GB2312_2_UTF8("ºº×ÖABCabc123!@#");

	BYTE buf1[128] = { 0 };
	NetworkStreamWrite ns1(buf1, sizeof(buf1) / sizeof(BYTE));
	int len1 = ns1.WriteUTF8Str(strUTF8, false);
	string str1 = BufferTool::Join(buf1, len1, ", ", "%02d");
	printf("buf1: %s \n", str1.c_str());


	BYTE buf2[128] = { 0 };
	NetworkStreamWrite ns2(buf2, sizeof(buf2) / sizeof(BYTE));
	int len2 = ns2.WriteUTF8Str(strUTF8);
	string str2 = BufferTool::Join(buf2, len2, ", ", "%02d");
	printf("buf2: %s \n", str2.c_str());
}