#pragma once

#include <string>
using namespace std;

#include "AdoParam.h"
#include "DataSet.h"


namespace MyAdo
{
	class Ado;

	// Ado Result
	typedef struct tagAdoResult
	{
	public:
		int nRecordsAffected;		// records affected number
		AdoParam param;				// ado param
		bool bError;				// whether error
		string strErrorInfo;		// error info
		DataSet ds;					// DataSet
		Ado* pAdo;					// ado pointer

	public:
		tagAdoResult(Ado* ado = nullptr)
			: nRecordsAffected(-1)
			, param(AdoParam())
			, bError(false)
			, strErrorInfo("")
			, pAdo(ado)
		{

		}

	}AdoResult;
}