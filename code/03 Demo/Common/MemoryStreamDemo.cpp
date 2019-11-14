#include "stdafx.h"
#include "MemoryStreamDemo.h"


void PrintfBuf(BYTE* buf, int len, string name);
void PrintMS(MemoryStream* ms, int len);
void OnOverMaxBufLen(MemoryStream* pMS, int len);


void MemoryStreamDemo::Init()
{

}

void MemoryStreamDemo::Test1()
{
	MemoryStream ms;

	BYTE buf1[] = { 1, 2, 3 };
	ms.Write(buf1, 3);
	PrintMS(&ms, 10);

	BYTE buf2[] = { 0, 0, 0 };
	ms.Read(1, buf2);
	PrintfBuf(buf2, 3, "buf2");

	BYTE buf3[] = { 0, 0, 0 };
	ms.Read(1, buf3);
	PrintfBuf(buf3, 3, "buf3");

	BYTE buf4[] = { 0, 0, 0 };
	ms.Read(1, buf4);
	PrintfBuf(buf4, 3, "buf4");

	BYTE buf5[] = { 0, 0, 0 };
	ms.Read(1, buf5);
	PrintfBuf(buf5, 3, "buf5");

	PrintMS(&ms, 10);
}

void MemoryStreamDemo::Test2()
{
	MemoryStream ms(10, 20);
	ms.RegCallback(std::bind(OnOverMaxBufLen, _1, _2));

	BYTE buf1[30] = { 0 };
	bool b = ms.Write(buf1, 30);
	printf("ms.Write: %d \n", b);
}

void MemoryStreamDemo::Test3()
{
	MemoryStream ms(10, 20);
	PrintMS(&ms, 10);

	BYTE buf1[5] = { 1, 2, 3, 4, 5 };
	ms.Write(buf1, 5);
	PrintMS(&ms, 10);

	ms.Read(2);
	PrintMS(&ms, 10);

	BYTE buf2[6] = { 6, 7, 8, 9, 10, 11 };
	ms.Write(buf2, 6);
	PrintMS(&ms, 10);
}

void OnOverMaxBufLen(MemoryStream* pMS, int len)
{
	printf("Over max buf length: %d \n", len);
}

void PrintfBuf(BYTE* buf, int len, string name)
{
	printf("%s: ", name.c_str());
	for (int i = 0; i < len; i++)
	{
		printf("%02X, ", buf[i]);
	}
	printf("\n");
}

void PrintMS(MemoryStream* pMS, int len)
{
	BYTE* buf = new BYTE[len];
	memset(buf, 0, len);

	pMS->Copy(len, buf);

	PrintfBuf(buf, len, "MemoryStream");

	delete buf;
}