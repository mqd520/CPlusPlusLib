#pragma once

#include <vector>
using namespace std;

#include "WSProtocolHandle.h"


namespace ws
{

	// ws protocool handle mgr
	class WSProtocolHandleMgr
	{
	public:
		WSProtocolHandleMgr();

	private:
		vector<WSProtocolHandle*> vec;		// WSProtocolHandle list

	public:
		//************************************
		// Method:    Create a WSProtocolHandle obj
		// Parameter: int Id
		//************************************
		WSProtocolHandle* Create(int Id);

		//************************************
		// Method:    Get a WSProtocolHandle obj
		// Parameter: int Id
		//************************************
		WSProtocolHandle* Get(int Id);

		//************************************
		// Method:    Remove a WSProtocolHandle obj
		// Parameter: int Id
		//************************************
		WSProtocolHandle* Remove(int Id);

		//************************************
		// Method:    Clear
		//************************************
		void Clear();
	};
}