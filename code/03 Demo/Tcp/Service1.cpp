#include "stdafx.h"
#include "Service1.h"


Service1::Service1()
{

}

void Service1::Init()
{

}

void Service1::Exit()
{
	server.Exit();
}

TcpServer* Service1::GetTcpServer()
{
	return &server;
}