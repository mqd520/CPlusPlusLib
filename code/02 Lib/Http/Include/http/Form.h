#pragma once

#include <minwindef.h>
#include <string>
#include <vector>
using namespace std;


namespace http
{
	// Form
	class Form
	{
	public:
		Form();

	protected:
		vector<pair<string, string>> vecParams;		// text param list
		string pBuf;
		int nLen;

	public:
		//************************************
		// Method:    Add Form Item Data
		// Parameter: const string & key
		// Parameter: const BYTE & val
		//************************************
		bool AddItem(const string& key, const BYTE& val);

		//************************************
		// Method:    Add Form Item Data
		// Parameter: const string & key
		// Parameter: const BYTE & val
		//************************************
		bool AddItem(const string& key, const INT16& val);

		//************************************
		// Method:    Add Form Item Data
		// Parameter: const string & key
		// Parameter: const BYTE & val
		//************************************
		bool AddItem(const string& key, const UINT16& val);

		//************************************
		// Method:    Add Form Item Data
		// Parameter: const string & key
		// Parameter: const BYTE & val
		//************************************
		bool AddItem(const string& key, const INT32& val);

		//************************************
		// Method:    Add Form Item Data
		// Parameter: const string & key
		// Parameter: const BYTE & val
		//************************************
		bool AddItem(const string& key, const UINT32& val);

		//************************************
		// Method:    Add Form Item Data
		// Parameter: const string & key
		// Parameter: const BYTE & val
		//************************************
		bool AddItem(const string& key, const INT64& val);

		//************************************
		// Method:    Add Form Item Data
		// Parameter: const string & key
		// Parameter: const BYTE & val
		//************************************
		bool AddItem(const string& key, const UINT64& val);

		//************************************
		// Method:    Add Form Item Data
		// Parameter: const string & key
		// Parameter: const BYTE & val
		// Parameter: const int& f = 2
		//************************************
		bool AddItem(const string& key, const FLOAT& val, const int& f = 2);

		//************************************
		// Method:    Add Form Item Data
		// Parameter: const string & key
		// Parameter: const BYTE & val
		// Parameter: const int& f = 2
		//************************************
		bool AddItem(const string& key, const double& val, const int& f = 2);

		//************************************
		// Method:    Add Form Item Data
		// Parameter: const string & key
		// Parameter: const BYTE & val
		//************************************
		bool AddItem(const string& key, const string& val);

		//************************************
		// Method:    Add Form Item Data
		// Parameter: const string & key
		// Parameter: const bool & val
		// Parameter: const string & trueVal
		// Parameter: const string & falseVal
		//************************************
		bool AddItem(const string& key, const bool& val, const string& trueVal, const string& falseVal);

		//************************************
		// Method:    Whether form key exist
		// Parameter: const string & key
		//************************************
		bool IsExistKey(const string& key);

		//************************************
		// Method:    Remove Form Item Data
		// Parameter: const string & key
		//************************************
		bool RemoveItem(const string& key);

		//************************************
		// Method:    Join Form Item Data
		//************************************
		string Join();

		//************************************
		// Method:    Has Form Data
		//************************************
		bool HasFormData();

		//************************************
		// Method:    Get Form Data List
		//************************************
		vector<pair<string, string>> GetParamList();

		//************************************
		// Method:    Parse Form Text
		// Parameter: const string & text
		//************************************
		void ParseFormText(const string& text);

		//************************************
		// Method:    Clear Form Data
		//************************************
		void Clear();
	};
}