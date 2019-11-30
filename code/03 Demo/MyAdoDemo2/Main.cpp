// MyAdoDemo2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <fstream>
using namespace std;

#include "com/Log.h"
#include "com/ExceptionHandler.h"
#include "com/CommonTool.h"
#include "com/TimeTool.h"
using namespace com;

#include "Thread1.h"
#include "Config.h"


#define  ProjectName		("MyAdoDemo2.exe")				// MyAdoDemo2.exe


void OnLog(ELogType type, string& log, ExtraLogInfo& info);
void OnException(void* lpParam1, void* lpParam2);

int _tmain(int argc, _TCHAR* argv[])
{
	Log::RegLogFileCallback(std::bind(OnLog, _1, _2, _3));

	ExceptionHandler::Init();
	ExceptionHandler::SetFileName(ProjectName);
	ExceptionHandler::SetCallback(OnException);

	_cfg.Init();

	Thread1 thd;
	thd.Run();
	thd.SetSleepTime(_cfg.nTaskSleepTime);


	char chLine[1024] = { 0 };
	while (true)
	{
		string cmd = gets_s(chLine);
		if (cmd == "exit")
		{
			break;
		}
	}

	thd.Exit(10 * 1000);

	return 0;
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
	string log = ProjectName;
	log += "crashed!";

	Log::Write_2_File(ELogType::Fatal, log, __FUNCTION__);
}