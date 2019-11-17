#pragma once

#include <string>
using namespace std;


namespace com
{
	// Url Tool
	class UrlTool final
	{
	private:
		UrlTool();

	public:
		//************************************
		// Method:    Encode
		// Parameter: const string & str
		//************************************
		static string Encode(const string& str, bool bUpperCase = true);

		static string Decode(const string& str);
	};
}