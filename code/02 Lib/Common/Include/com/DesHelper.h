#pragma once

#include <minwindef.h>

namespace com
{
	// Des Helper  
	class DesHelper final
	{
	private:
		DesHelper();

	public:
		static void Encrypt(unsigned char* outbuf, unsigned char * inbuf, int inlen, int* outLen, unsigned char * key, unsigned char * iv);
	};
}