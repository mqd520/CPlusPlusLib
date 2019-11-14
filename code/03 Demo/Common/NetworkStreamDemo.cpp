#include "stdafx.h"
#include "NetworkStreamDemo.h"

void NetStreamDemo::Init()
{

}

void NetStreamDemo::Test1()
{
	BYTE buf1[] = { 1, 2, 3, 4, 5 };
	NetworkStream ns1(buf1, sizeof(buf1) / sizeof(BYTE));
	BYTE* p1 = ns1.GetBuf();
	int len1 = ns1.GetBufLen();
	EEndian bo1 = ns1.GetByteOrder();
}