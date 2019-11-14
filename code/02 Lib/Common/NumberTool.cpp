#include "stdafx.h"
#include "Include/com/NumberTool.h"

#include "Include/com/StringTool.h"


namespace com
{
	NumberTool::NumberTool()
	{

	}

	string NumberTool::ToString(const BYTE& val, const int& radix /*= 10*/, const int& max /*= 0*/, const string& str /*= "0"*/, const bool& b /*= true*/)
	{
		char ch[50] = { 0 };

		string format = "%u";
		if (radix == 8)
		{
			format = "%o";
		}
		else if (radix == 16)
		{
			format = "%x";
		}
		int n = sprintf_s(ch, format.c_str(), val);

		if (max > 0 && max > n)
		{
			return StringTool::FillIn(ch, max, str, b);
		}
		else
		{
			return ch;
		}
	}

	string NumberTool::ToString(const INT16& val, const int& radix /*= 10*/, const int& max /*= 0*/, const string& str /*= "0"*/, const bool& b /*= true*/)
	{
		char ch[50] = { 0 };

		string format = "%d";
		if (radix == 8)
		{
			format = "%o";
		}
		else if (radix == 16)
		{
			format = "%x";
		}
		int n = sprintf_s(ch, format.c_str(), val);

		if (max > 0 && max > n)
		{
			return StringTool::FillIn(ch, max, str, b);
		}
		else
		{
			return ch;
		}
	}

	string NumberTool::ToString(const UINT16& val, const int& radix /*= 10*/, const int& max /*= 0*/, const string& str /*= "0"*/, const bool& b /*= true*/)
	{
		char ch[50] = { 0 };

		string format = "%u";
		if (radix == 8)
		{
			format = "%o";
		}
		else if (radix == 16)
		{
			format = "%x";
		}
		int n = sprintf_s(ch, format.c_str(), val);

		if (max > 0 && max > n)
		{
			return StringTool::FillIn(ch, max, str, b);
		}
		else
		{
			return ch;
		}
	}

	string NumberTool::ToString(const INT32& val, const int& radix /*= 10*/, const int& max /*= 0*/, const string& str /*= "0"*/, const bool& b /*= true*/)
	{
		char ch[50] = { 0 };

		string format = "%d";
		if (radix == 8)
		{
			format = "%o";
		}
		else if (radix == 16)
		{
			format = "%x";
		}
		int n = sprintf_s(ch, format.c_str(), val);

		if (max > 0 && max > n)
		{
			return StringTool::FillIn(ch, max, str, b);
		}
		else
		{
			return ch;
		}
	}

	string NumberTool::ToString(const UINT32& val, const int& radix /*= 10*/, const int& max /*= 0*/, const string& str /*= "0"*/, const bool& b /*= true*/)
	{
		char ch[50] = { 0 };

		string format = "%u";
		if (radix == 8)
		{
			format = "%o";
		}
		else if (radix == 16)
		{
			format = "%x";
		}
		int n = sprintf_s(ch, format.c_str(), val);

		if (max > 0 && max > n)
		{
			return StringTool::FillIn(ch, max, str, b);
		}
		else
		{
			return ch;
		}
	}

	string NumberTool::ToString(const INT64& val, const int& radix /*= 10*/, const int& max /*= 0*/, const string& str /*= "0"*/, const bool& b /*= true*/)
	{
		char ch[50] = { 0 };

		string format = "%lld";
		if (radix == 8)
		{
			format = "%llo";
		}
		else if (radix == 16)
		{
			format = "%llx";
		}
		int n = sprintf_s(ch, format.c_str(), val);

		if (max > 0 && max > n)
		{
			return StringTool::FillIn(ch, max, str, b);
		}
		else
		{
			return ch;
		}
	}

	string NumberTool::ToString(const UINT64& val, const int& radix /*= 10*/, const int& max /*= 0*/, const string& str /*= "0"*/, const bool& b /*= true*/)
	{
		char ch[50] = { 0 };

		string format = "%llu";
		if (radix == 8)
		{
			format = "%o";
		}
		else if (radix == 16)
		{
			format = "%x";
		}
		int n = sprintf_s(ch, format.c_str(), val);

		if (max > 0 && max > n)
		{
			return StringTool::FillIn(ch, max, str, b);
		}
		else
		{
			return ch;
		}
	}

	string NumberTool::ToString(const FLOAT& val, const int& decimal /*= 2*/)
	{
		char ch[50] = { 0 };

		char ch1[5] = { 0 };
		sprintf_s(ch1, "%d", decimal);
		string format = "%." + string(ch1) + "f";
		sprintf_s(ch, format.c_str(), val);

		return ch;
	}

	string NumberTool::ToString(const double& val, const int& decimal /*= 2*/)
	{
		char ch[50] = { 0 };

		char ch1[5] = { 0 };
		sprintf_s(ch1, "%d", decimal);
		string format = "%." + string(ch1) + "lf";
		sprintf_s(ch, format.c_str(), val);

		return ch;
	}
}