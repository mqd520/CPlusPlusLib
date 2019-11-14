#pragma once

#include "tcp/TcpServer.h"
using namespace tcp;


class Service1
{
public:
	Service1();

protected:
	TcpServer server;

public:
	void Init();

	void Exit();

	TcpServer* GetTcpServer();
};