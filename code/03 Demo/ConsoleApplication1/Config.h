#pragma once

#include <vector>
using namespace std;


// Config
class Config
{
public:
	Config();

public:
	string			strDbConnection;	// Db connection

public:
	//************************************
	// Method:    Init
	//************************************
	void Init();
};

extern Config _cfg;	// the only Config object