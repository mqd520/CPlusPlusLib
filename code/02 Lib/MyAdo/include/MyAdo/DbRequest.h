#pragma once

#include <string>
#include <functional>
using namespace std;
using namespace std::placeholders;

#include "Def.h"
#include "AdoParam.h"
#include "Ado.h"


namespace MyAdo
{
	// DbRequest Callback
	// AdoResult: Ado result
	// lpParam1:  param1
	// lpParam2:  param2
	using DbRequestCallback = std::function < void(AdoResult& result, void* lpParam1, void* lpParam2) > ;


	// DbRequest
	struct DbRequest
	{
	public:
		EDbRequstType type;		// DbRequstType
		string sql;				// Sql
		AdoParam param;			// Param
		ECmdType cmdType;		// Cmd type
		Ado* pAdo;				// Ado pointer

		DbRequestCallback callback;	// DbRequest Callback
		void* lpParam1;			// Additional param1
		void* lpParam2;			// Additional param2

	public:
		DbRequest()
			: sql("")
			, lpParam1(nullptr)
			, lpParam2(nullptr)
		{

		}
	};
}