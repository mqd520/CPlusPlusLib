#include "stdafx.h"
#include "MainService.h"

#include "Config.h"
#include "TaskThread.h"


TaskThread		_taskThd;
MainService		_mainSrv;

void MainService::Init()
{
	_taskThd.SetSleepTime(_cfg.taskSleepTime);
	_taskThd.Run();
}

void MainService::Exit()
{
	_taskThd.Exit(2 * 1000);
}