#include "stdafx.h"
#include "Include/com/Event.h"


namespace com
{
	Event::Event(const string name /*= ""*/, bool bManualReset /*= true*/, bool bInitialSingal /*= false*/)
		//: strName(name)
	{
		hEvt = ::CreateEventA(NULL, bManualReset, bInitialSingal, name.empty() ? NULL : name.c_str());
	}

	Event::~Event()
	{
		if (hEvt)
		{
			::CloseHandle(hEvt);
			hEvt = NULL;
		}
	}

	HANDLE Event::GetHandle() const
	{
		return hEvt;
	}

	DWORD Event::WaitForSingal(int timeout /*= INFINITE*/)
	{
		DWORD result = ::WaitForSingleObject(hEvt, timeout);

		return result;
	}

	BOOL Event::Active()
	{
		return ::SetEvent(hEvt);
	}

	BOOL Event::Reset()
	{
		return ::ResetEvent(hEvt);
	}

	//string Event::Name()
	//{
	//	return strName;
	//}
}