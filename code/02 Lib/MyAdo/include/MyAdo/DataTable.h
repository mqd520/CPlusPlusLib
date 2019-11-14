#pragma once

#include "DataRowCollection.h"
#include "FieldCollection.h"


namespace MyAdo
{
	// DataTable
	class DataTable
	{
	public:
		DataTable();

	public:
		DataRowCollection rows;		// DataRowCollection object
		FieldCollection fields;		// FieldCollection object
	};
}