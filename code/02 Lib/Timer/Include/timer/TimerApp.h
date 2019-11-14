#pragma once

namespace timer
{
	// Timer App
	class TimerApp
	{
	private:
		TimerApp();

	public:
		//************************************
		// Method:    Init
		//************************************
		static void Init();

		//************************************
		// Method:    Exit
		// Parameter: int timeout
		//************************************
		static void Exit(int timeout = 2 * 1000);
	};
}