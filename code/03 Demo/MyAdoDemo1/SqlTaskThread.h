#pragma once

#include "com/Thread.h"
using namespace com;


// SqlTaskThread
class SqlTaskThread : public Thread
{
public:
	SqlTaskThread();

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