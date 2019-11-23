#include "stdafx.h"
#include "Config.h"

#include "tinyxml.h"

#include "com/CommonTool.h"
#include "com/StringTool.h"
#include "com/Log.h"
using namespace com;


Config _cfg;

Config::Config()
	: bMultiThread(false)
	, nSqlTaskThreadTime(2 * 1000)
	, adoThreadInfo({ 1, 50 })
	, strDbConnection("")
{

}

void Config::Init()
{
	string path = CommonTool::GetCurrentExeDir() + "Config.xml";
	TiXmlDocument doc(path.c_str());
	bool b = doc.LoadFile();
	if (b)
	{
		TiXmlElement* root = doc.RootElement();

		TiXmlElement* multiThreadElement = root->FirstChildElement("MultiThread");
		this->bMultiThread = multiThreadElement->GetText() == "1";

		TiXmlElement* sqlTaskElement = root->FirstChildElement("SqlTaskThreadTime");
		this->nSqlTaskThreadTime = StringTool::To_Int32(sqlTaskElement->GetText());

		TiXmlElement* adoElement = root->FirstChildElement("AdoThread");
		this->adoThreadInfo.nCount = StringTool::To_Int32(adoElement->FirstChildElement("count")->GetText());
		this->adoThreadInfo.nTime = StringTool::To_Int32(adoElement->FirstChildElement("time")->GetText());

		TiXmlElement* dbConnElement = root->FirstChildElement("DbConnection");
		this->strDbConnection = dbConnElement->GetText();

		TiXmlElement* items = root->FirstChildElement("sqls");
		TiXmlElement* item = NULL;
		for (item = items->FirstChildElement(); item != NULL; item = item->NextSiblingElement())
		{
			string sql = item->Attribute("sql");
			string type = item->Attribute("type");
			string count = item->Attribute("count");

			vecSqlInfos.push_back({ sql, StringTool::To_Int32(count), StringTool::To_Int32(type) });
		}
	}
	else
	{
		string log = StringTool::Format("Open Config.xml fail, msg: %s, path: %s", doc.ErrorDesc(), path.c_str());
		Log::Write_2_Console(ELogType::Error, log, true, __FUNCTION__, __FILE__, __LINE__);
	}
}

vector<XmlSqlInfo>& Config::List()
{
	return vecSqlInfos;
}