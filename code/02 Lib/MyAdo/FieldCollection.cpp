#include "stdafx.h"
#include "FieldCollection.h"


namespace MyAdo
{
	void FieldCollection::Add(FieldInfo fi)
	{
		vecFields.push_back(fi);
	}

	int FieldCollection::Count()
	{
		return (int)vecFields.size();
	}

	FieldInfo FieldCollection::operator[](int nIndex)
	{
		FieldInfo info;

		for (int i = 0; i < (int)vecFields.size(); i++)
		{
			if (i == nIndex)
			{
				info = vecFields[i];
				break;
			}
		}

		return info;
	}

	FieldInfo FieldCollection::operator[](const string& fieldName)
	{
		FieldInfo info;

		for (auto & it : vecFields)
		{
			if (it.strFieldName == fieldName)
			{
				info = it;
				break;
			}
		}

		return info;
	}
}