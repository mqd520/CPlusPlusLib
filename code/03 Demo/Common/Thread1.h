#pragma once

#include "com/Thread.h"
using namespace com;


// Thread1
class Thread1 : public Thread
{
public:
	Thread1();

protected:
	void OnStart() override;

	void OnExit() override;

	void OnWhile() override;
};