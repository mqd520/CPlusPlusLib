#pragma once

#include <vector>
#include <string>
using namespace std;

#include "MSAdo.h"
#include "Def.h"


namespace MyAdo
{
	// Ado Param
	class AdoParam
	{
	public:
		AdoParam();

	private:
		vector<AdoParamInfo> vecParas;	// Ado Param list

	public:
		//************************************
		// Method:    Create Para
		// Parameter: const string & strParaName
		// Parameter: DataTypeEnum paraType
		// Parameter: ParameterDirectionEnum paraDirection
		// Parameter: long paraSize
		// Parameter: _variant_t vtParaValue
		//************************************
		void CreatePara(const string& strParaName, DataTypeEnum paraType, ParameterDirectionEnum paraDirection, long paraSize, _variant_t vtParaValue = vtMissing);

		//************************************
		// Method:    CreateBinaryParam
		// Parameter: const string & strParaName
		// Parameter: DataTypeEnum paraType
		// Parameter: ParameterDirectionEnum paraDirection
		// Parameter: long paraSize
		// Parameter: _variant_t vtParaValue
		//************************************
		void CreateBinaryParam(const string& strParaName, DataTypeEnum paraType, ParameterDirectionEnum paraDirection, long paraSize, _variant_t vtParaValue = vtMissing);

		//************************************
		// Method:    Create Return Value Param
		//************************************
		void CreateReturnValueParam();

		//************************************
		// Method:    Get Params
		//************************************
		vector<AdoParamInfo>& GetParams();

		//************************************
		// Method:    GetParamValue
		// Parameter: int index
		//************************************
		_variant_t GetParamValue(int index);

		//************************************
		// Method:    GetParamValue
		// Parameter: const string & strParamName
		//************************************
		_variant_t GetParamValue(const string& strParamName);

		//************************************
		// Method:    GetReturnValue
		//************************************
		int GetReturnValue();

		//************************************
		// Method:    IsEmpty
		//************************************
		bool IsEmpty();

		//************************************
		// Method:    HasReturnValue
		//************************************
		bool HasReturnValue();
	};
}