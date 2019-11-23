#include "stdafx.h"
#include "InitService.h"

#include <fstream>
using namespace std;

#include "com/Log.h"
#include "com/CommonTool.h"
#include "com/StringTool.h"
#include "com/TimeTool.h"
#include "com/ExceptionHandler.h"
using namespace com;

#include "MyAdo/MyAdoApp.h"
#include "MyAdo/Ado.h"
using namespace MyAdo;

#include "Config.h"
#include "AdoConnection.h"
#include "MainService.h"


void OnLog(ELogType type, string& log, ExtraLogInfo& info);
void OnException(void* lpParam1, void* lpParam2);

InitService::InitService()
{

}

void InitService::Init()
{
	Log::RegLogFileCallback(std::bind(OnLog, _1, _2, _3));

	ExceptionHandler::Init();
	ExceptionHandler::SetFileName($ProjectName);
	ExceptionHandler::SetCallback(OnException);

	_cfg.Init();

	MyAdoApp::Init(_cfg.adoThreadInfo.nCount, _cfg.adoThreadInfo.nTime);

	AdoConnection::Init();

	_mainSrv.Init();
}

void InitService::Exit()
{
	MyAdoApp::Exit(10 * 10000);

	AdoConnection::Exit();

	_mainSrv.Exit();
}

void OnLog(ELogType type, string& log, ExtraLogInfo& info)
{
	string path = CommonTool::GetCurrentExeDir() + TimeTool::Format("yyyy-mm-dd") + ".log";

	char ch[1024] = { 0 };
	sprintf_s(ch, "[%s] [%s] [0x%04x] [%s:%s:%d] %s \n\n",
		TimeTool::Format(info.time, true, "yyyy-mm-dd HH:MM:ss.ff").c_str(),
		Log::GetLogTypeStr(type).c_str(),
		info.nThreadId,
		info.strFileName.c_str(),
		info.strFunctionName.c_str(),
		info.nRowNo,
		log.c_str());

	fstream fs;
	fs.open(path, ios::app);
	fs << ch;
	fs.close();
}

void OnException(void* lpParam1, void* lpParam2)
{
	InitService::Exit();
}