#include "stdafx.h"
#include "DataRowCollection.h"


namespace MyAdo
{
	void DataRowCollection::Add(DataRow& dr)
	{
		vecDR.push_back(dr);
	}

	DataRow* DataRowCollection::operator[](int nIndex)
	{
		for (int i = 0; i < (int)vecDR.size(); i++)
		{
			if (i == nIndex)
			{
				return &vecDR[i];
			}
		}

		return nullptr;
	}

	int DataRowCollection::Count()
	{
		return (int)vecDR.size();
	}
}