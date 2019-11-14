#include "stdafx.h"
#include "Include/com/Semaphore.h"

namespace com
{
	Semaphore::Semaphore(LONG lInitialCount, LONG lMaximumCount /*= 4096*/, LPCTSTR lpName /*= NULL*/)
	{
		hSema = ::CreateSemaphore(NULL, lInitialCount, lMaximumCount, lpName);
	}

	HANDLE Semaphore::GetHandle() const
	{
		return hSema;
	}

	DWORD Semaphore::WaitForSingal(int timeout /*= INFINITE*/)
	{
		DWORD dwResult = ::WaitForSingleObject(hSema, timeout);

		return dwResult;
	}

	BOOL Semaphore::ReleaseSingal(int count /*= 1*/)
	{
		return ::ReleaseSemaphore(hSema, count, nullptr);
	}
}