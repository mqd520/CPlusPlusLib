#include "stdafx.h"
#include "MainService.h"

#include "Config.h"
#include "SqlTaskThread.h"


MainService _mainSrv;
SqlTaskThread _thd;

void MainService::Init()
{
	_thd.Run();
}

void MainService::Exit()
{
	_thd.Exit(10 * 1000);
}