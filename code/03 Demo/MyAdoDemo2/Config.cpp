#include "stdafx.h"
#include "Config.h"

#include "tinyxml.h"

#include "com/CommonTool.h"
#include "com/StringTool.h"
#include "com/Log.h"
using namespace com;


Config _cfg;

Config::Config()
	: strDbConnection("")
	, nAdoCount(0)
	, nTaskSleepTime(0)
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

		TiXmlElement* dbConnElement = root->FirstChildElement("DbConnection");
		this->strDbConnection = dbConnElement->GetText();

		TiXmlElement* adoCountElement = root->FirstChildElement("AdoCount");
		this->nAdoCount = StringTool::To_Int32(adoCountElement->GetText());

		TiXmlElement* taskSleepTimeElement = root->FirstChildElement("TaskSleepTime");
		this->nTaskSleepTime = StringTool::To_Int32(taskSleepTimeElement->GetText());
	}
	else
	{
		string log = StringTool::Format("Open Config.xml fail, msg: %s, path: %s", doc.ErrorDesc(), path.c_str());
		Log::Write_2_Console(ELogType::Error, log, true, __FUNCTION__, __FILE__, __LINE__);
	}
}