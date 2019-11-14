#pragma once

#include <minwindef.h>

namespace com
{
	// Semaphore
	class Semaphore
	{
	public:
		Semaphore(LONG lInitialCount, LONG lMaximumCount = 4096, LPCTSTR lpName = NULL);

		~Semaphore();

	protected:
		HANDLE hSema;

	public:
		HANDLE GetHandle() const;

		DWORD WaitForSingal(int timeout = INFINITE);

		BOOL ReleaseSingal(int count = 1);
	};
}