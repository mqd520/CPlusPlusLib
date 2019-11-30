#pragma once

#include "com/Thread.h"
using namespace com;


// Thread1
class Thread1 : public Thread
{
public:
	Thread1();

protected:
	bool bComInited;

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