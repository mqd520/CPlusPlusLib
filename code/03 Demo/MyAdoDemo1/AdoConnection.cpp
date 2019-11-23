#include "stdafx.h"
#include "AdoConnection.h"

#include "Config.h"


Ado AdoConnection::default;

void AdoConnection::Init()
{
	default.ResetDRMode(EDbDRMode::ReadWrite);
	default.ResetConnStr(_cfg.strDbConnection, EDbType::MySQL);
}

void AdoConnection::Exit()
{
	default.CloseConnection();
}