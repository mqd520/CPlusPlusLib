#pragma once
#include <string>
using namespace std;

namespace com
{
	// simple shell
	class ShellService
	{
	private:
		ShellService();

	private:
		static void ShowHelp();

		static bool OnScanCpl(string& result);

		static bool OnHelp();

		static bool OnQuit();

		static bool OnCleanScreen();

		static bool OnUndefined();

	public:
		static void ReadLine();
	};
}