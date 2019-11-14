#pragma once

namespace com
{

	// Endian
	enum class EEndian : int
	{
		little = 1,	// little endian

		big = 2		// big endian(network endian)
	};


	// Stream Tool
	class StreamTool final
	{
	private:
		StreamTool();

	private:
		static bool bInited;	// Whether inited

	private:
		static EEndian endian;	// localhost endian

	private:
		//************************************
		// Method:    Init
		//************************************
		static void Init();

		//************************************
		// Method:    Calc localhost endian
		//************************************
		static EEndian CalcLocalhostEndian();

	public:
		//************************************
		// Method:    Get localhost endian
		//************************************
		static EEndian GetLocalHostEndian();
	};
}