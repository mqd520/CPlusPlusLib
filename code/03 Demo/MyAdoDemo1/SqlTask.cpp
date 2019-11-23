#include "stdafx.h"
#include "SqlTask.h"

#include "com/CommonTool.h"
#include "com/StringTool.h"
#include "com/TimeTool.h"
#include "com/Log.h"
using namespace com;

#include "Config.h"
#include "AdoConnection.h"


SqlTask _sqltask;

void SqlTask::Process()
{
	vector<XmlSqlInfo> vec = _cfg.List();
	int size = (int)vec.size();
	if (size > 0)
	{
		int rand = CommonTool::Rand() % size;
		XmlSqlInfo info = vec[rand];


		string log = StringTool::Format("\n Sql: %s, count: %d, type: %d", info.strSql.c_str(), info.nCount, info.nType);
		Log::Write_2_Console(ELogType::Info, log, false, __FUNCTION__, __FILE__, __LINE__);
		Log::Write_2_Console(ELogType::Info, "Start ...", false, __FUNCTION__, __FILE__, __LINE__);

		time_t timestamp1 = TimeTool::GetCurTimeStamp();
		for (int i = 0; i < info.nCount; i++)
		{
			AdoConnection::default.ReadDataSet(info.strSql, AdoParam());
		}
		time_t timestamp2 = TimeTool::GetCurTimeStamp();

		string sql = "insert into Logs (SqlStatement, Count, Time, Type, ThreadCount) values(?, ?, ?, ?, ?)";
		AdoParam param;
		param.CreatePara("@SqlStatement", adVarChar, adParamInput, 255, _variant_t(info.strSql.c_str()));
		param.CreatePara("@Count", adInteger, adParamInput, sizeof(int), _variant_t(info.nCount));
		param.CreatePara("@Time", adInteger, adParamInput, sizeof(int), _variant_t(timestamp2 - timestamp1));
		param.CreatePara("@Type", adInteger, adParamInput, sizeof(int), _variant_t(info.nType));
		param.CreatePara("@ThreadCount", adInteger, adParamInput, sizeof(int), _variant_t(_cfg.bMultiThread ? _cfg.adoThreadInfo.nCount : 1));
		AdoConnection::default.ExecuteNonQuery(sql, param);

		Log::Write_2_Console(ELogType::Info, "End ... \n", false, __FUNCTION__, __FILE__, __LINE__);
	}
}