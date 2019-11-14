#pragma once

#include <string>
using namespace std;


namespace http
{
	// Http Tool
	class HttpTool final
	{
	private:
		HttpTool();

	public:
		//************************************
		// Method:    Is Text Type(Content-Type)
		// Returns:   bool
		// Parameter: const string & contentType
		//************************************
		static bool IsTextType(const string& contentType);
	};
}