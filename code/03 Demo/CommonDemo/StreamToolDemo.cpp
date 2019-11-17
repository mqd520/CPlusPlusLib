#include "stdafx.h"
#include "StreamToolDemo.h"

void StreamToolDemo::Test1()
{
	EEndian endian = StreamTool::GetLocalHostEndian();

	printf("Local host byte order: %d \n", endian);
}