#pragma once

#include <string>
#include <vector>
using namespace std;

#include "Def.h"


namespace MyAdo
{
	// DataRow
	class DataRow
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: vector<DataRowMetaInfo> & drmi
		//************************************
		DataRow(vector<DataRowMetaInfo>& drmi);

	protected:
		vector<DataRowMetaInfo> vecMetaInfos;	// DataRowMetaInfo list

	public:
		//************************************
		// Method:    Get Field Count
		//************************************
		int GetFieldCount();

		//************************************
		// Method:    Get Value
		// Parameter: const int & nIndex
		//************************************
		_variant_t GetValue(const int& nIndex);

		//************************************
		// Method:    Get Value
		// Parameter: const string & strFieldName
		//************************************
		_variant_t GetValue(const string& strFieldName);

	public:
		//************************************
		// Method:    Get Int
		// Parameter: const int & nIndex
		//************************************
		int GetInt(const int& nIndex);

		//************************************
		// Method:    Get Int
		// Parameter: const string & strFieldName
		//************************************
		int GetInt(const string& strFieldName);

		//************************************
		// Method:    Get String
		// Parameter: const int & nIndex
		//************************************
		string GetString(const int& nIndex);

		//************************************
		// Method:    Get String
		// Parameter: const string & strFieldName
		//************************************
		string GetString(const string& strFieldName);
	};
}