#pragma once


// MainService
class MainService
{
public:
	//************************************
	// Method:    Init
	//************************************
	void Init();

	//************************************
	// Method:    Exit
	//************************************
	void Exit();
};

extern MainService _mainSrv;	// the only MainService object