#pragma once

#include <string>
using namespace std;

#include "Def.h"
#include "MSAdo.h"
#include "AdoParam.h"
#include "AdoResult.h"


namespace MyAdo
{
	// Ado
	class Ado
	{
	public:
		Ado();
		Ado(const string& strconn, EDbType type = EDbType::MSSQLSERVER);
		Ado(const string& strAddr, const string& strUsername, const string& strPwd, const string& strDbName = "", EDbType type = EDbType::MSSQLSERVER);

	protected:
		char chErrorInfo[MyAdo_Max_ErrorInfo];			// Last error info
		string strConn;					// Conn db string
		EDbType dbType;					// Db type
		EDbDRMode dbDRMode;				// Db read and write mode
		int nConnTimeout;				// Connect timeout(s)
		int nCmdTimeout;				// Exec cmd timeout(s)

	protected:
		_ConnectionPtr pConnection;		// connection obj
		_CommandPtr pCommand;			// command obj
		_RecordsetPtr pRst;				// recordset obj

	protected:
		//************************************
		// Method:    Process Error
		// Parameter: string strErrorInfo
		// Parameter: const string & strFunctionName
		// Parameter: bool bWriteConsole
		// Parameter: bool bWriteFile
		// Parameter: const string & strFilePath
		// Parameter: int nRowNo
		//************************************
		void ProcessError(string strErrorInfo, const string& strFunctionName, bool bWriteConsole = true, bool bWriteFile = true, const string& strFilePath = __FILE__, int nRowNo = __LINE__);

		//************************************
		// Method:    Format Com Error
		// Parameter: _com_error & e
		//************************************
		string FormatComError(_com_error &e);

		//************************************
		// Method:    GenerateConnStr
		// Parameter: EDbType type
		// Parameter: const string & strHost
		// Parameter: const string & strUsername
		// Parameter: const string & strPwd
		// Parameter: const string & dbName
		//************************************
		string GenerateConnStr(EDbType type, const string& strAddr, const string& strUsername, const string& strPwd, const string& strDbName = "");

		//************************************
		// Method:    Filter Conn Str
		// Parameter: string strconn
		//************************************
		string FilterConnStr(string strconn);

	public:
		//************************************
		// Method:    Reset Conn Str
		// Parameter: const string & connstr
		// Parameter: EDbType type
		//************************************
		void ResetConnStr(const string& connstr, EDbType type = EDbType::MSSQLSERVER);

		//************************************
		// Method:    Reset Conn Str
		// Parameter: const string & strHost
		// Parameter: const string & strUsername
		// Parameter: const string & strPwd
		// Parameter: const string & dbName
		// Parameter: EDbType type
		//************************************
		void ResetConnStr(const string& strAddr, const string& strUsername, const string& strPwd, const string& strDbName = "", EDbType type = EDbType::MSSQLSERVER);

		//************************************
		// Method:    Reset DRMode
		// Parameter: EDbDRMode mode
		//************************************
		void ResetDRMode(EDbDRMode model);

		//************************************
		// Method:    Reset Connect Timeout
		// Parameter: int timeout
		//************************************
		void ResetConnTimeout(int timeout);

		//************************************
		// Method:    ResetCmdTimeout
		// Parameter: int timeout
		//************************************
		void ResetCmdTimeout(int timeout);

		//************************************
		// Method:    GetConnStr
		// Returns:   std::string
		//************************************
		string GetConnStr();

		//************************************
		// Method:    GetDbType
		// Returns:   MyAdo::EDbType
		//************************************
		EDbType GetDbType();

		//************************************
		// Method:    Get DbDRMode
		//************************************
		EDbDRMode GetDbDRMode();

	protected:
		//************************************
		// Method:    CreateCommand
		// Parameter: _ConnectionPtr conn
		// Parameter: string sql
		// Parameter: ECmdType type
		// Parameter: AdoParam & param
		//************************************
		_CommandPtr CreateCommand(_ConnectionPtr conn, string sql, ECmdType type, AdoParam& param);

		//************************************
		// Method:    Set Output Param
		// Parameter: AdoParam & src
		// Parameter: AdoParam & dest
		// Parameter: _CommandPtr cmd
		//************************************
		void SetOutputParam(AdoParam& src, AdoParam& dest, _CommandPtr cmd);

		//************************************
		// Method:    RecordSqlLog
		// Parameter: string sql
		// Parameter: AdoParam param
		//************************************
		void RecordSqlLog(string sql, AdoParam param);

	public:
		//************************************
		// Method:    Get Last Error Info
		//************************************
		string GetLastErrorInfo();

		//************************************
		// Method:    Is Connection Opened
		//************************************
		bool IsConnectionOpened();

		//************************************
		// Method:    Connect
		//************************************
		bool Connect();

		//************************************
		// Method:    Close Connect
		//************************************
		void CloseConnection();

		//************************************
		// Method:    Close
		//************************************
		void Close();

		//************************************
		// Method:    Test Connect
		//************************************
		bool TestConnect();

		//************************************
		// Method:    ExecuteNonQuery
		// Parameter: string sql
		// Parameter: AdoParam param
		// Parameter: ECmdType type
		//************************************
		AdoResult ExecuteNonQuery(string sql, AdoParam param = AdoParam(), ECmdType type = ECmdType::Text);

		//************************************
		// Method:    Read DataSet
		// Parameter: string sql
		// Parameter: AdoParam param
		// Parameter: ECmdType type
		//************************************
		AdoResult ReadDataSet(string sql, AdoParam param = AdoParam(), ECmdType type = ECmdType::Text);
	};
}