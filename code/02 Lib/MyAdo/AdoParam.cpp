#include "stdafx.h"
#include "AdoParam.h"


namespace MyAdo
{
	AdoParam::AdoParam()
	{

	}

	void AdoParam::CreatePara(const string& strParaName, DataTypeEnum paraType, ParameterDirectionEnum paraDirection, long paraSize, _variant_t vtParaValue /*= vtMissing*/)
	{
		AdoParamInfo para;
		para.strParaName = strParaName;
		para.vtParaValue = vtParaValue;
		para.nDataType = paraType;
		para.nParaDirect = paraDirection;
		para.nParaSize = paraSize;

		vecParas.push_back(para);
	}

	void AdoParam::CreateBinaryParam(const string& strParaName, DataTypeEnum paraType, ParameterDirectionEnum paraDirection, long paraSize, _variant_t vtParaValue /*= vtMissing*/)
	{
		//SAFEARRAYBOUND bound[1];
		//bound[0].lLbound = 0;
		//bound[0].cElements = nParaSize;
		//SAFEARRAY* psa = SafeArrayCreate(VT_UI1, 1, bound);
		//for (int i = 0; i < nParaSize; i++)
		//{
		//	SafeArrayPutElement(psa, (LONG*)&i, pParaValue++);
		//}

		//_variant_t vt;
		//vt.vt = VT_ARRAY | VT_UI1;
		//vt.parray = psa;

		//CreatePara(strParaName, vt, adVarBinary, (ParameterDirectionEnum)nParaDirect, nParaSize);
	}

	void AdoParam::CreateReturnValueParam()
	{
		CreatePara(MyAdo_ReturnValue_ParamName, adInteger, adParamReturnValue, sizeof(int));
	}

	vector<AdoParamInfo>& AdoParam::GetParams()
	{
		return vecParas;
	}

	_variant_t AdoParam::GetParamValue(int index)
	{
		_variant_t result = vtMissing;

		if (index < (int)vecParas.size())
		{
			result = vecParas[index].vtParaValue;
		}

		return result;
	}

	_variant_t AdoParam::GetParamValue(const string& strParamName)
	{
		_variant_t result = vtMissing;

		for (auto & it : vecParas)
		{
			if (it.strParaName == strParamName)
			{
				result = it.vtParaValue;
				break;
			}
		}

		return result;
	}

	int AdoParam::GetReturnValue()
	{
		int result = INFINITE;

		_variant_t var = GetParamValue(MyAdo_ReturnValue_ParamName);
		if (var != vtMissing)
		{
			result = var.intVal;
		}

		return result;
	}

	bool AdoParam::IsEmpty()
	{
		return (int)vecParas.size() == 0;
	}

	bool AdoParam::HasReturnValue()
	{
		bool result = false;

		for (auto & it : vecParas)
		{
			if (it.strParaName == MyAdo_ReturnValue_ParamName)
			{
				result = true;
				break;
			}
		}

		return result;
	}
}