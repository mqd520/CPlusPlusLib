#pragma once

#include <string>
using namespace std;


#define		$ProjectName				("MyAdoDemo1.exe")			// Project name


// XmlSqlInfo
typedef struct tagXmlSqlInfo
{
	string strSql;		// sql
	int nCount;			// Count
	int nType;			// Type
}XmlSqlInfo;	// XmlSqlInfo


//// Db Conn Info
//typedef struct tagDbConnInfo
//{
//	string	strAddr;			// Db Addr
//	string	strUID;				// Db uid
//	string	strPwd;				// Db pwd
//	string	strDbName;			// Db name
//}DbConnInfo;	// Db Conn Info


// Ado Thread Info
typedef struct tagAdoThreadInfo
{
	int		nCount;		// Thread count
	int		nTime;		// Sleep time(in ms)
}AdoThreadInfo;	// Ado Thread Info