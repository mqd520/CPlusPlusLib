#pragma once

#include <string>
using namespace std;


namespace com
{
	// Number Tool
	class NumberTool final
	{
	private:
		NumberTool();

	public:
		//************************************
		// Method:    To String
		// Parameter: const BYTE & val
		// Parameter: const int& radix = 10
		// Parameter: const int & max: max char length
		// Parameter: const string & str
		// Parameter: const bool& b = true, whether fill in from the left
		//************************************
		static string ToString(const BYTE& val, const int& radix = 10, const int& max = 0, const string& str = "0", const bool& b = true);

		//************************************
		// Method:    To String
		// Parameter: const INT16 & val
		// Parameter: const int& radix = 10
		// Parameter: const int & max: max char length
		// Parameter: const string & str
		// Parameter: const bool& b = true, whether fill in from the left
		//************************************
		static string ToString(const INT16& val, const int& radix = 10, const int& max = 0, const string& str = "0", const bool& b = true);

		//************************************
		// Method:    To String
		// Parameter: const UINT16 & val
		// Parameter: const int& radix = 10
		// Parameter: const int & max: max char length
		// Parameter: const string & str
		// Parameter: const bool& b = true, whether fill in from the left
		//************************************
		static string ToString(const UINT16& val, const int& radix = 10, const int& max = 0, const string& str = "0", const bool& b = true);

		//************************************
		// Method:    To String
		// Parameter: const INT32 & val
		// Parameter: const int& radix = 10
		// Parameter: const int & max: max char length
		// Parameter: const string & str
		// Parameter: const bool& b = true, whether fill in from the left
		//************************************
		static string ToString(const INT32& val, const int& radix = 10, const int& max = 0, const string& str = "0", const bool& b = true);

		//************************************
		// Method:    To String
		// Parameter: const UINT32 & val
		// Parameter: const int& radix = 10
		// Parameter: const int & max: max char length
		// Parameter: const string & str
		// Parameter: const bool& b = true, whether fill in from the left
		//************************************
		static string ToString(const UINT32& val, const int& radix = 10, const int& max = 0, const string& str = "0", const bool& b = true);

		//************************************
		// Method:    To String
		// Parameter: const INT32 & val
		// Parameter: const int& radix = 10
		// Parameter: const int & max: max char length
		// Parameter: const string & str
		// Parameter: const bool& b = true, whether fill in from the left
		//************************************
		static string ToString(const INT64& val, const int& radix = 10, const int& max = 0, const string& str = "0", const bool& b = true);

		//************************************
		// Method:    To String
		// Parameter: const UINT64 & val
		// Parameter: const int& radix = 10
		// Parameter: const int & max: max char length
		// Parameter: const string & str
		// Parameter: const bool& b = true, whether fill in from the left
		//************************************
		static string ToString(const UINT64& val, const int& radix = 10, const int& max = 0, const string& str = "0", const bool& b = true);

		//************************************
		// Method:    To String
		// Parameter: const FLOAT & val
		// Parameter: const int& decimal = 2
		//************************************
		static string ToString(const FLOAT& val, const int& decimal = 2);

		//************************************
		// Method:    To String
		// Parameter: const double & val
		// Parameter: const int& decimal = 2
		//************************************
		static string ToString(const double& val, const int& decimal = 2);
	};
}