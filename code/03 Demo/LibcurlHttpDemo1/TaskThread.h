#pragma once

#include "com/Thread.h"
using namespace com;


// TaskThread
class TaskThread : public Thread
{
public:
	TaskThread();

protected:
	//************************************
	// Method:    Thread start evt handler
	//************************************
	void OnStart() override;

	//************************************
	// Method:    Thread while evt handler
	//************************************
	void OnWhile() override;

	//************************************
	// Method:    Thread exit evt handler
	//************************************
	void OnExit() override;
};