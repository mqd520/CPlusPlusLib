#pragma once

#include <minwinbase.h>

namespace com
{
	// Lock
	class Lock
	{
	public:
		Lock();

		~Lock();

	protected:
		bool bDisabled;

	protected:
		CRITICAL_SECTION crSection;
		bool bLeaved;

	public:
		void Enter();

		void Leave();

		void Disable(bool disable = true);
	};
}