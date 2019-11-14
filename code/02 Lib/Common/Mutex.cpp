#include "stdafx.h"
#include "Include/com/Mutex.h"

namespace com
{
	Mutex::Mutex() :
		hMutex(NULL)
	{

	}

	Mutex::~Mutex()
	{
		if (hMutex)
		{
			::CloseHandle(hMutex);
			hMutex = NULL;
		}
	}

	HANDLE Mutex::GetHandle() const
	{
		return hMutex;
	}

	bool Mutex::Create(BOOL bInitialOwner, LPCTSTR lpName)
	{
		hMutex = ::CreateMutex(NULL, bInitialOwner, lpName);
		DWORD dwResult = ::GetLastError();
		if (hMutex)
		{
			if (dwResult == ERROR_ALREADY_EXISTS)
			{
				::CloseHandle(hMutex);
				hMutex = NULL;

				return false;
			}

			return true;
		}

		return false;
	}

	DWORD Mutex::WaitForSingal(DWORD timeout /*= INFINITE*/)
	{
		if (hMutex)
		{
			return ::WaitForSingleObject(hMutex, timeout);
		}

		return 0xFF;
	}

	BOOL Mutex::Release()
	{
		if (hMutex)
		{
			return ::ReleaseMutex(hMutex);
		}

		return FALSE;
	}
}