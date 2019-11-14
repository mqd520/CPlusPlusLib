#pragma once

#include <string>
using namespace std;


namespace http
{
	// Regex Tool
	class RegexTool final
	{
	private:
		RegexTool();

	public:
		//************************************
		// Method:    Whether Ip
		// Parameter: string val
		//************************************
		static bool IsIp(string val);
	};
}