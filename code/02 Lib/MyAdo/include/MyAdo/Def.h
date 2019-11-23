#pragma once

#include <string>
#include <functional>
using namespace std;
using namespace std::placeholders;

#include "MSAdo.h"


#define		MyAdo_ReturnValue_ParamName			("@RETURN_VALUE")		// return value param name
#define		MyAdo_Max_Connect_Timeout			(90)					// max connect time
#define		MyAdo_Max_Command_Timeout			(90)					// max command time
#define		MyAdo_Max_ErrorInfo					(1024)					// max error info


namespace MyAdo
{
	// Db Type
	enum class EDbType : int
	{
		MSSQLSERVER = 1,		// Ms SQLSERVER

		MySQL = 2,				// Mysql

		Oracle = 3,				// Oracle

		Access = 4,				// Ms Access

		ODBC = 5,				// ODBC

		ADO = 6,				// ADO

		None = 99				// None
	};


	// Db read and write mode
	enum class EDbDRMode
	{
		Read = 1,				// read-only

		ReadWrite = 2,			// read and write

		Write = 3				// write-only
	};


	// Sql Cmd Type
	enum class ECmdType
	{
		Text = 1,				// SQL Text
		Procedure = 2			// Procedure
	};


	// DbRequst Type
	enum class EDbRequstType
	{
		NonQuery = 1,			// None query

		Query = 2				// Query
	};


	// Ado param info
	typedef struct tagAdoParamInfo
	{
		string strParaName;					// Name
		_variant_t vtParaValue;				// Value
		ParameterDirectionEnum nParaDirect;	// direction
		long nParaSize;						// size
		DataTypeEnum nDataType;				// data type
	}AdoParamInfo;


	// DataRow Meta Info
	struct DataRowMetaInfo
	{
	public:
		int nIndex;				// Index
		string strFieldName;	// File Name
		_variant_t fieldValue;	// Field value

	public:
		DataRowMetaInfo(int index, string name, _variant_t value)
			: nIndex(index)
			, strFieldName(name)
			, fieldValue(value)
		{

		};
	};


	// FieldInfo
	struct FieldInfo
	{
		string strFieldName;
		int nFieldType;
	};
}