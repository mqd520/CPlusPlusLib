#pragma once

#include <minwindef.h>
#include "StreamTool.h"

namespace com
{

	// String prefix byte length
	enum class EStringPrefixByteLen : int
	{
		Byte	= 1,		// 1 byte(BYTE)
		Int16	= 2,		// 2 byte(Int16)
		Int32	= 4			// 4 byte(Int32)
	};


	// NetworkStream
	class NetworkStream
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: BYTE * buf
		// Parameter: int len
		// Parameter: EByteOrder bo:	byte order
		//************************************
		NetworkStream(BYTE* buf, int len, EEndian bo = EEndian::big);

		virtual ~NetworkStream();

	protected:
		BYTE* pBuf;			// buf pointer
		int nLen;			// buf length
		EEndian bo;		// current byte order
		int nDataIndex;		// data pos index

	public:
		//************************************
		// Method:    Get Buf
		//************************************
		BYTE* GetBuf();

		//************************************
		// Method:    Get Buf length
		//************************************
		int GetBufLen();

		//************************************
		// Method:    Get current byte order
		//************************************
		EEndian GetByteOrder();

		//************************************
		// Method:    Get avaliable byte count
		//************************************
		int AvaliableByteCount();

		//************************************
		// Method:    Get used byte count
		//************************************
		int UsedByteCount();
	};
}