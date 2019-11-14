#include "stdafx.h"
#include "Include/http/HttpTool.h"

#include "com/StringTool.h"
using namespace com;


namespace http
{
	HttpTool::HttpTool()
	{

	}

	bool HttpTool::IsTextType(const string& contentType)
	{
		bool result = false;

		if (contentType.empty())
		{
			return true;
		}
		else
		{
			string contentType1 = StringTool::Trim(StringTool::ToLower(contentType));
			vector<string> vec = StringTool::Split(contentType1, "/");
			if (vec.size() == 2)
			{
				if (vec[0] == "application")
				{
					if (vec[1] == "x-www-form-urlencoded" ||
						vec[1] == "xhtml+xml" ||
						vec[1] == "atom+xml" ||
						vec[1] == "json")
					{
						result = true;
					}
				}
				else if (vec[0] == "text")
				{
					result = true;
				}
			}
		}

		return result;
	}
}