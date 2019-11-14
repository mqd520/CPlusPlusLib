#pragma once

#include "DataTableCollection.h"
#include "MSAdo.h"


namespace MyAdo
{
	// DataSet
	class DataSet
	{
	public:
		DataSet();

	public:
		DataTableCollection tables;		// DataTableCollection
	};
}