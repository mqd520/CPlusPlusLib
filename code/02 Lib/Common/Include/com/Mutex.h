#pragma once

#include <minwindef.h>

namespace com
{
	// Mutex
	class Mutex
	{
	public:
		Mutex();

		~Mutex();

	protected:
		HANDLE hMutex;

	public:
		HANDLE GetHandle() const;

		bool Create(BOOL bInitialOwner, LPCTSTR lpName);

		DWORD WaitForSingal(DWORD timeout = INFINITE);

		BOOL Release();
	};
}