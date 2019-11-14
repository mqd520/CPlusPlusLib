#pragma once

#include <vector>
using namespace std;

#include "DataTable.h"


namespace MyAdo
{
	// DataTableCollection
	class DataTableCollection
	{
	protected:
		vector<DataTable> vecTables;	// DataTable list

	public:
		//************************************
		// Method:    Add
		// Parameter: DataTable & table
		//************************************
		void Add(DataTable& table);

		//************************************
		// Method:    Table Count
		//************************************
		int Count();

		//************************************
		// Method:    Read DataTable
		// Parameter: int nIndex
		//************************************
		DataTable* operator[](int nIndex);
	};
}