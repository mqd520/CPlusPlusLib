#pragma once

#include <string>
using namespace std;


namespace com
{
	// Event
	class Event
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: bool bManualReset = true
		// Parameter: bool bInitialState = false
		//************************************
		Event(const string name = "", bool bManualReset = true, bool bInitialSingal = false);

		~Event();

	protected:
		HANDLE hEvt;
		//string strName;

	public:
		HANDLE GetHandle() const;

		DWORD WaitForSingal(int timeout = INFINITE);

		BOOL Active();

		BOOL Reset();

		//string Name();
	};
}