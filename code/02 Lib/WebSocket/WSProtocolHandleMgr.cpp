#include "stdafx.h"
#include "Include/ws/WSProtocolHandleMgr.h"

namespace ws
{
	WSProtocolHandleMgr::WSProtocolHandleMgr()
	{

	}

	WSProtocolHandle* WSProtocolHandleMgr::Create(int Id)
	{
		WSProtocolHandle* p = NULL;

		bool b = false;
		for (vector<WSProtocolHandle*>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			if ((*it)->GetId() == Id)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			p = new WSProtocolHandle(Id);
			vec.push_back(p);
		}

		return p;
	}

	WSProtocolHandle* WSProtocolHandleMgr::Get(int Id)
	{
		WSProtocolHandle* p = NULL;

		for (vector<WSProtocolHandle*>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			if ((*it)->GetId() == Id)
			{
				p = *it;
				break;
			}
		}

		return p;
	}

	WSProtocolHandle* WSProtocolHandleMgr::Remove(int Id)
	{
		WSProtocolHandle* p = NULL;

		for (vector<WSProtocolHandle*>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			if ((*it)->GetId() == Id)
			{
				p = *it;
				vec.erase(it);
				break;
			}
		}

		return p;
	}

	void WSProtocolHandleMgr::Clear()
	{
		for (vector<WSProtocolHandle*>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			delete *it;
		}

		vec.clear();
	}
}