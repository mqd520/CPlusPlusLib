#include "stdafx.h"
#include "Config.h"

#include "tinyxml.h"

#include "com/Log.h"
#include "com/CommonTool.h"
#include "com/StringTool.h"
using namespace com;


Config _cfg;

Config::Config()
	: strDbServiceAddr("")
	, taskSleepTime(0)
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

		TiXmlElement* libcurlElement = root->FirstChildElement("LibcurlHttp");
		this->libcurlHttp.nThreadCount = StringTool::To_Int32(libcurlElement->FirstChildElement("ThreadCount")->GetText());
		this->libcurlHttp.nSleepTime = StringTool::To_Int32(libcurlElement->FirstChildElement("ThreadSleepTime")->GetText());
		this->libcurlHttp.bProxy = StringTool::To_Int32(libcurlElement->FirstChildElement("Proxy")->GetText()) == 1;
		this->libcurlHttp.strProxyAddr = libcurlElement->FirstChildElement("ProxyAddr")->GetText();

		TiXmlElement* httpsElement = root->FirstChildElement("https");
		for (TiXmlElement* httpElement = httpsElement->FirstChildElement("http");
			httpElement != NULL;
			httpElement = httpElement->NextSiblingElement())
		{
			string url = httpElement->GetText();
			int count = StringTool::To_Int32(httpElement->Attribute("count"));
			string method = httpElement->Attribute("method");
			string data = httpElement->Attribute("data");
			string contentType = httpElement->Attribute("contentType");

			vecHttps.push_back({ url, count, method, data, contentType });
		}

		//TiXmlElement* dbConnectionElement = root->FirstChildElement("DbConnection");
		//this->dbConnection = dbConnectionElement->GetText();

		TiXmlElement* taskElement = root->FirstChildElement("TaskSleepTime");
		this->taskSleepTime = StringTool::To_Int32(taskElement->GetText());

		TiXmlElement* dbServiceAddrElement = root->FirstChildElement("DbServiceAddr");
		this->strDbServiceAddr = dbServiceAddrElement->GetText();
	}
	else
	{
		string log = StringTool::Format("Open Config.xml fail, msg: %s, path: %s", doc.ErrorDesc(), path.c_str());
		Log::Write_2_Console(ELogType::Error, log, true, __FUNCTION__, __FILE__, __LINE__);
	}
}