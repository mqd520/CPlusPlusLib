#include "stdafx.h"
#include "Ado.h"

#include "com/Log.h"
#include "com/StringTool.h"
using namespace com;

#include "DataSet.h"
#include "MyAdoApp.h"


namespace MyAdo
{
	Ado::Ado()
		: strConn("")
		, dbType(EDbType::MSSQLSERVER)
		, dbDRMode(EDbDRMode::ReadWrite)
		, nConnTimeout(MyAdo_Max_Connect_Timeout)
		, nCmdTimeout(MyAdo_Max_Command_Timeout)
	{
		ZeroMemory(chErrorInfo, MyAdo_Max_ErrorInfo);
	}

	Ado::Ado(const string& strconn, EDbType type /*= EDbType::MSSQLSERVER*/)
		: dbDRMode(EDbDRMode::ReadWrite)
		, nConnTimeout(MyAdo_Max_Connect_Timeout)
		, nCmdTimeout(MyAdo_Max_Command_Timeout)
	{
		ZeroMemory(chErrorInfo, MyAdo_Max_ErrorInfo);
		strConn = strconn;
		dbType = type;
	}

	Ado::Ado(const string& strAddr, const string& strUsername, const string& strPwd, const string& strDbName /*= ""*/, EDbType type /*= EDbType::MSSQLSERVER*/)
		: dbDRMode(EDbDRMode::ReadWrite)
		, nConnTimeout(MyAdo_Max_Connect_Timeout)
		, nCmdTimeout(MyAdo_Max_Command_Timeout)
	{
		ZeroMemory(chErrorInfo, MyAdo_Max_ErrorInfo);
		dbType = type;
		strConn = GenerateConnStr(type, strAddr, strUsername, strPwd, strDbName);
	}

	string Ado::GenerateConnStr(EDbType type, const string& strAddr, const string& strUsername, const string& strPwd, const string& strDbName /*= ""*/)
	{
		char ch[256] = { 0 };

		if (type == EDbType::ADO)
		{
			sprintf_s(ch, "Provider=SQLOLEDB.1;Persist Security Info=False;User ID=%s;Password=%s;Initial Catalog=%s;",
				strUsername.c_str(), strPwd.c_str(), strAddr.c_str());
		}
		else if (type == EDbType::ODBC)
		{
			sprintf_s(ch, "Provider=MSDASQL;DSN=%s;UID=%s;PWD=%s;",
				strAddr.c_str(), strUsername.c_str(), strPwd.c_str());
		}
		else if (type == EDbType::Oracle)
		{
			sprintf_s(ch, "Provider=MSDAORA;Data Source=%s;User ID=%s; Password=%s;",
				strAddr.c_str(), strUsername.c_str(), strPwd.c_str());
		}
		else if (type == EDbType::MSSQLSERVER)
		{
			sprintf_s(ch, "Provider=SQLOLEDB;Data Source=%s;Initial Catalog=%s;User ID=%s;Password=%s;",
				strAddr.c_str(), strDbName.c_str(), strUsername.c_str(), strPwd.c_str());
		}
		else if (type == EDbType::Access)
		{
			sprintf_s(ch, "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;User ID=%s;Password=%s;",
				strAddr.c_str(), strUsername.c_str(), strPwd.c_str());
		}

		return ch;
	}

	string Ado::FilterConnStr(string strconn)
	{
		string str = "";

		vector<string> vec = StringTool::Split(strconn, ";");
		for (auto & it : vec)
		{
			if (StringTool::StartWith(it, "pwd") || StringTool::StartWith(it, "password"))
			{
				// do nothing
			}
			else
			{
				str += it + ";";
			}
		}

		return str;
	}

	void Ado::ResetConnStr(const string& connstr, EDbType type /*= EDbType::MSSQLSERVER*/)
	{
		dbType = type;
		strConn = connstr;
	}

	void Ado::ResetConnStr(const string& strAddr, const string& strUsername, const string& strPwd, const string& strDbName /*= ""*/, EDbType type /*= EDbType::MSSQLSERVER*/)
	{
		dbType = type;
		strConn = GenerateConnStr(type, strAddr, strUsername, strPwd, strDbName);
	}

	void Ado::ResetDRMode(EDbDRMode model)
	{
		dbDRMode = model;
	}

	void Ado::ResetConnTimeout(int timeout)
	{
		nConnTimeout = timeout;
	}

	void Ado::ResetCmdTimeout(int timeout)
	{
		nCmdTimeout = timeout;
	}

	string Ado::GetConnStr()
	{
		return strConn;
	}

	EDbType Ado::GetDbType()
	{
		return dbType;
	}

	EDbDRMode Ado::GetDbDRMode()
	{
		return dbDRMode;
	}

	_CommandPtr Ado::CreateCommand(_ConnectionPtr conn, string sql, ECmdType type, AdoParam& param)
	{
		_CommandPtr cmd = NULL;
		cmd.CreateInstance(__uuidof(Command));
		cmd->CommandText = sql.c_str();
		cmd->ActiveConnection = conn;
		cmd->CommandTimeout = nCmdTimeout;
		cmd->CommandType = type == ECmdType::Text ? adCmdText : adCmdStoredProc;

		if (!param.IsEmpty())
		{
			vector<AdoParamInfo>& vec = param.GetParams();
			for (auto & it : vec)
			{
				_ParameterPtr para = cmd->CreateParameter(it.strParaName.c_str(), it.nDataType, it.nParaDirect, it.nParaSize);
				if (it.nParaDirect == adParamInput || it.nParaDirect == adParamInputOutput)
				{
					if (it.nDataType == adVarBinary || it.nDataType == adBinary)
					{
						para->AppendChunk(it.vtParaValue);
					}
					else
					{
						para->Value = it.vtParaValue;
					}
				}
				cmd->Parameters->Append(para);
			}
		}

		return cmd;
	}

	void Ado::SetOutputParam(AdoParam& src, AdoParam& dest, _CommandPtr cmd)
	{
		if (!src.IsEmpty())
		{
			vector<AdoParamInfo>& vec = src.GetParams();
			for (auto & it : vec)
			{
				if (it.nParaDirect == adParamInputOutput || it.nParaDirect == adParamOutput || it.nParaDirect == adParamReturnValue)
				{
					_ParameterPtr para = cmd->Parameters->GetItem(it.strParaName.c_str());
					_variant_t var = para->GetValue();
					dest.CreatePara(it.strParaName, it.nDataType, it.nParaDirect, it.nParaSize, var);
				}
			}
		}
	}

	void Ado::RecordSqlLog(string sql, AdoParam param)
	{
		if (MyAdoApp::bEnableAutoSqlLog)
		{
			Write2File(ELogType::Sql, __FUNCDNAME__, __FILE__, __LINE__, "Sql: %s, param: %s", sql.c_str(), "");
		}
	}

	string Ado::GetLastErrorInfo()
	{
		return chErrorInfo;
	}

	void Ado::ProcessError(string strErrorInfo, bool bWriteConsole /*= true*/, bool bWriteFile /*= true*/)
	{
		ZeroMemory(chErrorInfo, 1024);

		sprintf_s(chErrorInfo, "%s", strErrorInfo.c_str());

		if (bWriteConsole)
		{
			Log::Write_2_Console(ELogType::Error, chErrorInfo, bWriteFile, __FUNCDNAME__);
		}
		else
		{
			if (bWriteFile)
			{
				Log::Write_2_File(ELogType::Error, chErrorInfo, true, true, __FUNCDNAME__);
			}
		}
	}

	string Ado::FormatComError(_com_error &e)
	{
		char ch[1024] = { 0 };

		sprintf_s(ch, "Ado Error, Des: %s, Code: %d, Source: %s, ErrorMessage: %s",
			(char*)e.Description(),
			e.WCode(),
			(char*)e.Source(),
			StringTool::UTF16_2_GB2312((wchar_t*)e.ErrorMessage()).c_str());

		return ch;
	}

	bool Ado::IsConnectionOpened()
	{
		return pConnection != nullptr && pConnection->State == adStateOpen;
	}

	bool Ado::Connect()
	{
		if (IsConnectionOpened())
		{
			return true;
		}

		try
		{
			pConnection.CreateInstance(__uuidof(Connection));
			pConnection->ConnectionTimeout = nConnTimeout;
			pConnection->CommandTimeout = nCmdTimeout;

			if (dbDRMode == EDbDRMode::Read)
			{
				pConnection->Mode = adModeRead;
			}
			else if (dbDRMode == EDbDRMode::Write)
			{
				pConnection->Mode = adModeWrite;
			}
			else if (dbDRMode == EDbDRMode::ReadWrite)
			{
				pConnection->Mode = adModeReadWrite;
			}

			HRESULT hr = pConnection->Open(_bstr_t(strConn.c_str()), "", "", adConnectUnspecified);

			if (FAILED(hr))
			{
				char ch[1024] = { 0 };
				sprintf_s(ch, "Conn db fail, conn string: %s, msg: HRESULT Invalid", FilterConnStr(strConn).c_str());
				ProcessError(ch);

				return false;
			}
		}
		catch (_com_error &e)
		{
			string str = FormatComError(e);

			char ch[1024] = { 0 };
			sprintf_s(ch, "Conn db fail, conn string: %s, %s", FilterConnStr(strConn).c_str(), str.c_str());

			ProcessError(ch);

			return false;
		}

		return true;
	}

	void Ado::CloseConnection()
	{
		if (pConnection)
		{
			if (IsConnectionOpened())
			{
				pConnection->Close();
			}

			pConnection = nullptr;
		}
	}

	void Ado::Close()
	{
		CloseConnection();
	}

	bool Ado::TestConnect()
	{
		bool b = Connect();
		if (b)
		{
			CloseConnection();
		}

		return b;
	}

	AdoResult Ado::ExecuteNonQuery(string sql, AdoParam param, ECmdType type /*= ESqlCmdType::Text*/)
	{
		RecordSqlLog(sql, param);

		AdoResult result(this);

		bool b1 = Connect();
		if (b1)
		{
			try
			{
				_CommandPtr cmd = CreateCommand(pConnection, sql, type, param);

				_variant_t varAffected;
				cmd->Execute(&varAffected, NULL, cmd->GetCommandType());
				result.nRecordsAffected = varAffected.intVal;

				SetOutputParam(param, result.param, cmd);
			}
			catch (_com_error &e)
			{
				result.strErrorInfo = FormatComError(e);
				result.bError = true;
				ProcessError(result.strErrorInfo);
			}
		}
		else
		{
			result.bError = true;
			result.strErrorInfo = chErrorInfo;
		}

		return result;
	}

	AdoResult Ado::ReadDataSet(string sql, AdoParam param, ECmdType type /*= ECmdType::Text*/)
	{
		RecordSqlLog(sql, param);

		AdoResult result(this);

		bool b1 = Connect();
		if (b1)
		{
			try
			{
				_CommandPtr cmd = CreateCommand(pConnection, sql, type, param);

				_RecordsetPtr rs;
				rs.CreateInstance(__uuidof(Recordset));

				_variant_t varAffected;
				rs = cmd->Execute(NULL, NULL, cmd->GetCommandType());
				result.nRecordsAffected = varAffected.intVal;

				SetOutputParam(param, result.param, cmd);

				DataSet ds;

				while (true)
				{
					Fields* pFields = nullptr;
					rs->get_Fields(&pFields);
					int nFieldCount = pFields->Count;

					DataTable dt;

					for (int i = 0; i < nFieldCount; i++)
					{
						FieldPtr field = pFields->GetItem((_variant_t)(long)i);
						_bstr_t fieldName = field->GetName();

						string strFieldName = "";
#if _UNICODE
						wchar_t* str1 = fieldName.GetBSTR();
						strFieldName = StringTool::UTF16_2_GB2312(str1);
#else
						char* str1 = fieldName.GetBSTR();
						strFieldName = str1;
#endif

						dt.fields.Add({ strFieldName, 0 });
					}

					while (!rs->adoEOF)
					{
						vector<DataRowMetaInfo> vec;

						for (int i = 0; i < nFieldCount; i++)
						{
							FieldPtr field = pFields->GetItem((_variant_t)(long)i);
							_bstr_t fieldName = field->GetName();
							_variant_t fieldValue = rs->GetCollect(fieldName);

							string strFieldName = "";
#if _UNICODE
							wchar_t* str1 = fieldName.GetBSTR();
							strFieldName = StringTool::UTF16_2_GB2312(str1);
#else
							char* str1 = fieldName.GetBSTR();
							strFieldName = str1;
#endif

							vec.push_back({ i, strFieldName, fieldValue });
						}

						dt.rows.Add(DataRow(vec));

						rs->MoveNext();
					}

					ds.tables.Add(dt);


					rs = rs->NextRecordset((VARIANT *)(long)0);
					if (rs == NULL)
					{
						break;
					}
				}

				result.ds = ds;
			}
			catch (_com_error &e)
			{
				result.strErrorInfo = FormatComError(e);
				result.bError = true;
				ProcessError(result.strErrorInfo);
			}
		}
		else
		{
			result.bError = true;
			result.strErrorInfo = chErrorInfo;
		}

		return result;
	}
}