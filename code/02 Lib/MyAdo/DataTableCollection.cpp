#include "stdafx.h"
#include "DataTableCollection.h"


namespace MyAdo
{
	void DataTableCollection::Add(DataTable& table)
	{
		vecTables.push_back(table);
	}

	int DataTableCollection::Count()
	{
		return (int)vecTables.size();
	}

	DataTable* DataTableCollection::operator[](int nIndex)
	{
		for (int i = 0; i < (int)vecTables.size(); i++)
		{
			if (i == nIndex)
			{
				return &vecTables[i];
			}
		}

		return nullptr;
	}
}