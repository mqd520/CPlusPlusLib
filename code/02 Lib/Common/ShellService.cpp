#include "stdafx.h"
#include "Include/com/ShellService.h"

namespace com
{
	ShellService::ShellService()
	{

	}

	void ShellService::ShowHelp()
	{
		printf("-------------------------------------------------------\n");
		printf("Server1.exe cmd:                               \n");
		printf("	help(-h): show help.                       \n");
		printf("	exit: exit the console.                    \n");
		printf("	quit(-q): exit the console.                \n");
		printf("	clear(-c): clear all the content on screen.\n");
		printf("-------------------------------------------------------\n\n");
	}

	void ShellService::ReadLine()
	{
		ShowHelp();

		char ch[1024] = { 0 };
		while (true)
		{
			string result = gets_s(ch);
			bool b = OnScanCpl(result);
			if (!b)
			{
				break;
			}

			Sleep(10);
		}
	}

	bool ShellService::OnScanCpl(string& result)
	{
		bool continue1 = false;		// is continue or not

		if (result == "help" || result == "-h")
		{
			continue1 = OnHelp();
		}
		else if (result == "exit" || result == "EXIT" || result == "quit" || result == "QUIT" || result == "-q")
		{
			continue1 = OnQuit();
		}
		else if (result == "clear" || result == "CLEAR" || result == "-c")
		{
			continue1 = OnCleanScreen();
		}
		else
		{
			continue1 = OnUndefined();
		}

		return continue1;
	}

	bool ShellService::OnHelp()
	{
		ShowHelp();

		return true;
	}

	bool ShellService::OnQuit()
	{
		return false;
	}

	bool ShellService::OnCleanScreen()
	{
		// ... clear screen

		return true;
	}

	bool ShellService::OnUndefined()
	{
		printf("undefined cmd. \n");

		return true;
	}
}