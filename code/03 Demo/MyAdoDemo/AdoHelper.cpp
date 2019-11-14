#include "stdafx.h"
#include "AdoHelper.h"


Ado AdoHelper::default;

void AdoHelper::Init()
{
	default.ResetDRMode(EDbDRMode::ReadWrite);
	default.ResetConnStr("127.0.0.1", "sa", "123456", "JinWinGame", EDbType::MSSQLSERVER);
}

void AdoHelper::Exit()
{
	default.CloseConnection();
}