#pragma once

#include <vector>
using namespace std;

#include "Def.h"


namespace MyAdo
{
	// Field Collection
	class FieldCollection
	{
	protected:
		vector<FieldInfo> vecFields;	// FieldInfo list

	public:
		//************************************
		// Method:    Add
		//************************************
		void Add(FieldInfo fi);

		//************************************
		// Method:    Count
		//************************************
		int Count();

		//************************************
		// Method:    operator[]
		// Parameter: int nIndex
		//************************************
		FieldInfo operator[](int nIndex);

		//************************************
		// Method:    operator[]
		// Parameter: const string & fieldName
		//************************************
		FieldInfo operator[](const string& fieldName);
	};
}