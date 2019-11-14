#include "stdafx.h"
#include "Include/com/NetworkStream.h"
#include <assert.h>

namespace com
{
	NetworkStream::NetworkStream(BYTE* buf, int len, EEndian bo /*= EByteOrder::big*/) :
		pBuf(buf),
		nLen(len),
		bo(bo),
		nDataIndex(0)
	{
		assert(pBuf);
		assert(nLen > 0);
	}

	NetworkStream::~NetworkStream()
	{

	}

	BYTE* NetworkStream::GetBuf()
	{
		return pBuf;
	}

	int NetworkStream::GetBufLen()
	{
		return nLen;
	}

	EEndian NetworkStream::GetByteOrder()
	{
		return bo;
	}

	int NetworkStream::AvaliableByteCount()
	{
		int len = nLen - nDataIndex;
		if (len < 0)
		{
			len = 0;
		}

		return len;
	}

	int NetworkStream::UsedByteCount()
	{
		return nDataIndex < 0 ? 0 : nDataIndex;
	}
}