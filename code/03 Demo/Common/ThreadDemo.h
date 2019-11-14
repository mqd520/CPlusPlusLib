#pragma once

#include "Thread1.h"


// ThreadDemo
class ThreadDemo
{
private:
	static Thread1 thd1;

public:
	static void Init();

	static void Exit();

	static void Test1();
};