#pragma once
#include <string>
using namespace std;

namespace com
{
	// common tool
	class CommonTool final
	{
	private:
		CommonTool();

	public:
		//************************************
		// Method:    Convert ip(string) to ip(int)
		// Parameter: const string & ip
		//************************************
		static UINT32 ConvertIp(const string& ip);

		//************************************
		// Method:    Convert ip(int) to ip(string)
		// Parameter: const UINT32& ip
		//************************************
		static string ConvertIp(const UINT32& ip);

		//************************************
		// Method:    Get Current Exe dir
		//************************************
		static string GetCurrentExeDir();

		//************************************
		// Method:    Get Current Exe path
		//************************************
		static string GetCurrentExePath();

		//************************************
		// Method:    Create a guid string
		//************************************
		static string CreateGuid();

		//************************************
		// Method:    Format a guid string
		//************************************
		static string FormatGuid(string guid);

		//************************************
		// Method:    Create and Format a guid string
		//************************************
		static string FormatGuid();

		//************************************
		// Method:    Rand
		//************************************
		static int Rand();
	};
}