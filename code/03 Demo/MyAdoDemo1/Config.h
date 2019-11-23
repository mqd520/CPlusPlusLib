#pragma once

#include <vector>
using namespace std;

#include "Def.h"


// Config
class Config
{
public:
	Config();

protected:
	vector<XmlSqlInfo> vecSqlInfos;		// Sql info list

public:
	bool			bMultiThread;		// Whether multi thread
	int				nSqlTaskThreadTime;	// Sql task thread time
	AdoThreadInfo	adoThreadInfo;		// Ado Thread Info
	string			strDbConnection;	// Db connection

public:
	//************************************
	// Method:    Init
	//************************************
	void Init();

	//************************************
	// Method:    List
	//************************************
	vector<XmlSqlInfo>& List();
};

extern Config _cfg;	// the only Config object