#include "stdafx.h"
#include "DataRow.h"

#include "VariantHelper.h"


namespace MyAdo
{
	DataRow::DataRow(vector<DataRowMetaInfo>& drmi)
	{
		vecMetaInfos = drmi;
	}

	int DataRow::GetFieldCount()
	{
		return (int)vecMetaInfos.size();
	}

	_variant_t DataRow::GetValue(const int& nIndex)
	{
		_variant_t result = vtMissing;

		for (int i = 0; i < (int)vecMetaInfos.size(); i++)
		{
			if (nIndex == i)
			{
				result = vecMetaInfos[i].fieldValue;
				break;
			}
		}

		return result;
	}

	_variant_t DataRow::GetValue(const string& strFieldName)
	{
		_variant_t result = vtMissing;

		for (int i = 0; i < (int)vecMetaInfos.size(); i++)
		{
			if (vecMetaInfos[i].strFieldName == strFieldName)
			{
				result = vecMetaInfos[i].fieldValue;
				break;
			}
		}

		return result;
	}

	int DataRow::GetInt(const int& nIndex)
	{
		_variant_t var = GetValue(nIndex);
		if (var != vtMissing)
		{
			return var.intVal;
		}

		return INFINITE;
	}

	int DataRow::GetInt(const string& strFieldName)
	{
		_variant_t var = GetValue(strFieldName);
		if (var != vtMissing)
		{
			return var.intVal;
		}

		return INFINITE;
	}

	string DataRow::GetString(const int& nIndex)
	{
		_variant_t var = GetValue(nIndex);
		if (var != vtMissing)
		{
			return (VariantHelper(var)).String();
		}

		return "";
	}

	string DataRow::GetString(const string& strFieldName)
	{
		_variant_t var = GetValue(strFieldName);
		if (var != vtMissing)
		{
			return (VariantHelper(var)).String();
		}

		return "";
	}
}