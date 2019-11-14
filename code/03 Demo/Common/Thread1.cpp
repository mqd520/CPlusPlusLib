#include "stdafx.h"
#include "Thread1.h"


Thread1::Thread1() :
Thread(1500, "Thread1")
{
	
}

void Thread1::OnStart()
{
	printf("Thread1.OnStart \n");

	__super::OnStart();
}

void Thread1::OnExit()
{
	printf("Thread1.OnExit \n");

	__super::OnExit();
}

void Thread1::OnWhile()
{
	printf("Thread1.OnWhileInner \n");

	__super::OnWhile();
}