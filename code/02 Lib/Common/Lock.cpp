#include "stdafx.h"
#include "Include/com/Lock.h"

namespace com
{
	Lock::Lock()
		: bLeaved(true)
		, bDisabled(false)
	{
		InitializeCriticalSection(&crSection);
	}

	Lock::~Lock()
	{
		Leave();

		DeleteCriticalSection(&crSection);
	}

	void Lock::Enter()
	{
		if (!bDisabled)
		{
			bLeaved = false;
			EnterCriticalSection(&crSection);
		}
	}

	void Lock::Leave()
	{
		if (!bDisabled)
		{
			if (!bLeaved)
			{
				bLeaved = true;
				LeaveCriticalSection(&crSection);
			}
		}
	}

	void Lock::Disable(bool disable /*= true*/)
	{
		if (disable)
		{
			Leave();
		}

		bDisabled = disable;
	}
}