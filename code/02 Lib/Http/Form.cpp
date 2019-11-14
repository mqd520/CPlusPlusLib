#include "stdafx.h"
#include "Include/http/Form.h"

#include "com/StringTool.h"
using namespace com;


namespace http
{
	Form::Form() :
		nLen(0)
	{

	}

	bool Form::AddItem(const string& key, const BYTE& val)
	{
		char ch[20] = { 0 };
		sprintf_s(ch, "%d", val);

		pair<string, string> item = { key, ch };
		vecParams.emplace_back(item);

		return true;
	}

	bool Form::AddItem(const string& key, const INT16& val)
	{
		char ch[20] = { 0 };
		sprintf_s(ch, "%d", val);

		pair<string, string> item = { key, ch };
		vecParams.emplace_back(item);

		return true;
	}

	bool Form::AddItem(const string& key, const UINT16& val)
	{
		char ch[20] = { 0 };
		sprintf_s(ch, "%d", val);

		pair<string, string> item = { key, ch };
		vecParams.emplace_back(item);

		return true;
	}

	bool Form::AddItem(const string& key, const INT32& val)
	{
		char ch[20] = { 0 };
		sprintf_s(ch, "%d", val);

		pair<string, string> item = { key, ch };
		vecParams.emplace_back(item);

		return true;
	}

	bool Form::AddItem(const string& key, const UINT32& val)
	{
		char ch[20] = { 0 };
		sprintf_s(ch, "%d", val);

		pair<string, string> item = { key, ch };
		vecParams.emplace_back(item);

		return true;
	}

	bool Form::AddItem(const string& key, const INT64& val)
	{
		char ch[20] = { 0 };
		sprintf_s(ch, "%d", val);

		pair<string, string> item = { key, ch };
		vecParams.emplace_back(item);

		return true;
	}

	bool Form::AddItem(const string& key, const UINT64& val)
	{
		char ch[20] = { 0 };
		sprintf_s(ch, "%d", val);

		pair<string, string> item = { key, ch };
		vecParams.emplace_back(item);

		return true;
	}

	bool Form::AddItem(const string& key, const FLOAT& val, const int& f /*= 2*/)
	{
		char ch1[20] = { 0 };
		_itoa_s(f, ch1, 10);
		string format = "%.";
		format += ch1;
		format += "f";

		char ch[20] = { 0 };
		sprintf_s(ch, format.c_str(), val);

		pair<string, string> item = { key, ch };
		vecParams.emplace_back(item);

		return true;
	}

	bool Form::AddItem(const string& key, const double& val, const int& f /*= 2*/)
	{
		char ch1[20] = { 0 };
		_itoa_s(f, ch1, 10);
		string format = "%.";
		format += ch1;
		format += "f";

		char ch[20] = { 0 };
		sprintf_s(ch, format.c_str(), val);

		pair<string, string> item = { key, ch };
		vecParams.emplace_back(item);

		return true;
	}

	bool Form::AddItem(const string& key, const string& val)
	{
		pair<string, string> item = { key, val };
		vecParams.emplace_back(item);

		return true;
	}

	bool Form::AddItem(const string& key, const bool& val, const string& trueVal, const string& falseVal)
	{
		pair<string, string> item = { key, val == true ? trueVal : falseVal };
		vecParams.emplace_back(item);

		return true;
	}

	bool Form::IsExistKey(const string& key)
	{
		bool b = false;

		for (auto & vecParam : vecParams)
		{
			if (vecParam.first == key)
			{
				b = true;
				break;
			}
		}

		return b;
	}

	bool Form::RemoveItem(const string& key)
	{
		bool b = false;

		for (vector<pair<string, string>>::iterator it = vecParams.begin(); it != vecParams.end(); it++)
		{
			if (it->first == key)
			{
				vecParams.erase(it);
				b = true;
				break;
			}
		}

		return b;
	}

	void Form::Clear()
	{
		vecParams.clear();
		pBuf = "";
		nLen = 0;
	}

	string Form::Join()
	{
		string result = "";

		for (vector<pair<string, string>>::iterator it = vecParams.begin(); it != vecParams.end(); it++)
		{
			if (it == vecParams.begin())
			{
				result += it->first + "=" + it->second;
			}
			else
			{
				result += "&" + it->first + "=" + it->second;
			}
		}

		return result;
	}

	bool Form::HasFormData()
	{
		return !vecParams.empty();
	}

	vector<pair<string, string>> Form::GetParamList()
	{
		return vecParams;
	}

	void Form::ParseFormText(const string& text)
	{
		vector<string> vec1 = StringTool::Split(text, "&");
		for (auto & it1 : vec1)
		{
			if (!it1.empty())
			{
				if ((int)it1.find("=") > -1)
				{
					vector<string> vec2 = StringTool::Split(it1, "=");
					if (vec2.size() == 2)
					{
						pair<string, string> item = { vec2[0], vec2[1] };
						vecParams.emplace_back(item);
					}
					else
					{
						pair<string, string> item = { vec2[0], "" };
						vecParams.emplace_back(item);
					}
				}
			}
		}
	}
}