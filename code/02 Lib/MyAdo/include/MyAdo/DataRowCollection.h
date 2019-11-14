#pragma once

#include <vector>
using namespace std;

#include "DataRow.h"


namespace MyAdo
{
	// DataRowCollection
	class DataRowCollection
	{
	protected:
		vector<DataRow> vecDR;		// DataRow list

	public:
		//************************************
		// Method:    Add
		// Parameter: DataRow & dr
		//************************************
		void Add(DataRow& dr);

		//************************************
		// Method:    Row Count
		//************************************
		int Count();

		//************************************
		// Method:    Read DataRow
		// Parameter: int nIndex
		//************************************
		DataRow* operator[](int nIndex);
	};
}