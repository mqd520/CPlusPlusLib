#include "stdafx.h"
#include "Task.h"

#include "com/StringTool.h"
#include "com/Log.h"
using namespace com;

#include "Config.h"

#import "c:\\program files\\common files\\system\\ado\\msado15.dll" no_namespace rename("EOF","adoEOF") rename("BOF", "adoBOF")


string FormatComError(_com_error &e);

Task _task;

void Task::Execute()
{
	Log::Write_2_Console(ELogType::Info, "Start...", false, __FUNCTION__);

	int count = 0;
	while (count < _cfg.nAdoCount)
	{
		_ConnectionPtr pConnection;
		pConnection.CreateInstance(__uuidof(Connection));
		pConnection->Mode = adModeReadWrite;

		HRESULT hr = pConnection->Open(_bstr_t(_cfg.strDbConnection.c_str()), "", "", adConnectUnspecified);
		if (FAILED(hr))
		{
			char ch[1024] = { 0 };
			sprintf_s(ch, "Conn db fail, conn string: %s, msg: HRESULT Invalid", _cfg.strDbConnection.c_str());

			Log::Write_2_Console(ELogType::Error, ch, true, __FUNCTION__);
		}
		else
		{
			try
			{
				_CommandPtr cmd = NULL;
				cmd.CreateInstance(__uuidof(Command));
				cmd->CommandText = "select * from logs limit 0, 10";
				cmd->ActiveConnection = pConnection;
				cmd->CommandType = adCmdText;

				_RecordsetPtr rs;
				rs.CreateInstance(__uuidof(Recordset));
				rs = cmd->Execute(NULL, NULL, cmd->GetCommandType());
			}
			catch (_com_error &e)
			{
				string log = FormatComError(e);

				Log::Write_2_Console(ELogType::Error, log, true, __FUNCTION__);
			}
		}


		count++;
	}

	Log::Write_2_Console(ELogType::Info, "End... \n", false, __FUNCTION__);
}

string FormatComError(_com_error &e)
{
	char ch[1024] = { 0 };

	sprintf_s(ch, "Ado Error, Des: %s, Code: %d, Source: %s, ErrorMessage: %s",
		(char*)e.Description(),
		e.WCode(),
		(char*)e.Source(),
		StringTool::UTF16_2_GB2312((wchar_t*)e.ErrorMessage()).c_str());

	return ch;
}