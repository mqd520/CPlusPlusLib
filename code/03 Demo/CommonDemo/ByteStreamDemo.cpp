#include "stdafx.h"
#include "ByteStreamDemo.h"

#include "com/ByteStream.h"
using namespace com;


void ByteStreamDemo::Test1()
{


	BYTE buf[128] = { 0 };
	buf[0] = 0;
	buf[1] = 1;
	buf[2] = 2;
	buf[127] = 127;

	ByteStream bs1(buf, 128);
	printf("bs1.len = %d \n", bs1.GetBufLen());

	BYTE* pBuf1 = bs1.GetBuf();
}