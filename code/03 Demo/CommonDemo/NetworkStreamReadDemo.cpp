#include "stdafx.h"
#include "NetworkStreamReadDemo.h"
#include "com/BufferTool.h"
#include "com/StringTool.h"


void NetworkStreamReadDemo::Init()
{

}

void NetworkStreamReadDemo::Test1()
{
	BYTE buf1[] = { 1, 2, 3, 4, 5 };
	NetworkStreamRead ns1(buf1, sizeof(buf1) / sizeof(BYTE), EEndian::big);
	int n1 = ns1.ReadInt16();
	printf("n1: %d \n", n1);

	BYTE buf2[] = { 1, 2, 3, 4, 5 };
	NetworkStreamRead ns2(buf2, sizeof(buf2) / sizeof(BYTE), EEndian::little);
	int n2 = ns2.ReadInt16();
	printf("n2: %d \n", n2);
}

void NetworkStreamReadDemo::Test2()
{
	BYTE buf1[] = { 186, 186, 215, 214, 65, 66, 67, 97, 98, 99, 49, 50, 51, 33, 64, 35 };					// "ºº×ÖABCabc123!@#"		GB2312
	NetworkStreamRead ns1(buf1, sizeof(buf1) / sizeof(BYTE), EEndian::big);
	string str1 = ns1.ReadGB2312Str(sizeof(buf1) / sizeof(BYTE));
	printf("str1: %s \n", str1.c_str());


	BYTE buf2[] = { 17, 0, 0, 0, 186, 186, 215, 214, 65, 66, 67, 97, 98, 99, 49, 50, 51, 33, 64, 35, 0 };	// "ºº×ÖABCabc123!@#"		GB2312
	NetworkStreamRead ns2(buf2, sizeof(buf2) / sizeof(BYTE), EEndian::little);
	string str2 = ns2.ReadGB2312Str();
	printf("str2: %s \n", str2.c_str());


	BYTE buf3[] = { 0, 0, 0, 17, 186, 186, 215, 214, 65, 66, 67, 97, 98, 99, 49, 50, 51, 33, 64, 35, 0 };	// "ºº×ÖABCabc123!@#"		GB2312
	NetworkStreamRead ns3(buf3, sizeof(buf3) / sizeof(BYTE), EEndian::big);
	string str3 = ns3.ReadGB2312Str();
	printf("str3: %s \n", str3.c_str());
}

void NetworkStreamReadDemo::Test3()
{
	BYTE buf1[] = { 73, 108, 87, 91, 65, 0, 66, 0, 67, 0, 97, 0, 98, 0, 99, 0, 49, 0, 50, 0, 51, 0, 33, 0, 64, 0, 35, 0 };			// "ºº×ÖABCabc123!@#"		UTF-16, Ð¡¶Ë
	NetworkStreamRead ns1(buf1, sizeof(buf1) / sizeof(BYTE), EEndian::little);
	wstring str1 = ns1.ReadUTF16Str(sizeof(buf1) / sizeof(BYTE));
	wprintf(L"str1: %s \n", str1.c_str());


	BYTE buf2[] = { 108, 73, 91, 87, 0, 65, 0, 66, 0, 67, 0, 97, 0, 98, 0, 99, 0, 49, 0, 50, 0, 51, 0, 33, 0, 64, 0, 35 };			// "ºº×ÖABCabc123!@#"		UTF-16, ´ó¶Ë
	NetworkStreamRead ns2(buf2, sizeof(buf2) / sizeof(BYTE), EEndian::big);
	wstring str2 = ns2.ReadUTF16Str(sizeof(buf2) / sizeof(BYTE));
	wprintf(L"str2: %s \n", str2.c_str());
}

void NetworkStreamReadDemo::Test4()
{
	BYTE buf1[] = { 230, 177, 137, 229, 173, 151, 65, 66, 67, 97, 98, 99, 49, 50, 51, 33, 64, 35 };			// "ºº×ÖABCabc123!@#"		UTF-8
	NetworkStreamRead ns1(buf1, sizeof(buf1) / sizeof(BYTE), EEndian::little);
	string str1 = ns1.ReadUTF8Str(sizeof(buf1) / sizeof(BYTE));
	printf("str1: %s \n", str1.c_str());
}