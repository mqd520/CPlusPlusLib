#pragma once

#include "MyAdo/Ado.h"
using namespace MyAdo;


class AdoHelper
{
public:
	//************************************
	// Method:    Init
	//************************************
	static void Init();

	//************************************
	// Method:    Exit
	//************************************
	static void Exit();

public:
	static Ado default;		// read and write, main db
};