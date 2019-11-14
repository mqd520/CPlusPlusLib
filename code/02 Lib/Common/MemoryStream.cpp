#include "stdafx.h"
#include "Include/com/MemoryStream.h"
#include <assert.h>

namespace com
{
	MemoryStream::MemoryStream(int len, int max /*= 1024 * 1024*/) :
		nBufLen(len),
		nMaxLen(max),
		pBuf(nullptr),
		nDataStartIndex(-1),
		nDataEndIndex(-1)
	{
		assert(len > 0);
		assert(max > 0 && max >= len);
		assert(max > len);

		pBuf = new BYTE[len];
		memset(pBuf, 0, len);
	}

	MemoryStream::~MemoryStream()
	{
		if (pBuf)
		{
			delete pBuf;
			pBuf = nullptr;
		}
	}

	bool MemoryStream::ReAssignBuf(int len)
	{
		if (len <= nMaxLen)
		{
			BYTE* pTmp = new BYTE[len];
			memset(pTmp, 0, len);

			int len1 = AvaliableReadLen();
			if (len1 > 0 && nDataStartIndex >= 0)
			{
				memcpy(pTmp, pBuf + nDataStartIndex, len1);
			}
			delete pBuf;
			pBuf = pTmp;

			if (len1 > 0 && nDataStartIndex >= 0)
			{
				nDataStartIndex = 0;
				nDataEndIndex = len1 - 1;
			}
			else
			{
				nDataStartIndex = -1;
				nDataEndIndex = -1;
			}

			return true;
		}
		else
		{
			for (vector<MSOverMaxBufLenCallback>::iterator it = vecFns.begin(); it != vecFns.end(); it++)
			{
				if (!it->_Empty())
				{
					(*it)(this, nMaxLen);
				}
			}

			return false;
		}
	}

	int MemoryStream::PanLeft(int index, int len, int panLen)
	{
		int len1 = 0;

		BYTE* pTmp = new BYTE[len];
		memcpy(pTmp, pBuf + index, len);

		len1 = panLen > index ? index : panLen;

		int index1 = index - len1;
		if (index1 < 0)
		{
			index1 = 0;
		}

		memcpy(pBuf + index1, pTmp, len);
		delete pTmp;

		return len1;
	}

	void MemoryStream::DataPanLeft(int len)
	{
		int len1 = PanLeft(nDataStartIndex, AvaliableReadLen(), len);

		nDataStartIndex -= len1;
		if (nDataStartIndex < 0)
		{
			nDataStartIndex = 0;
		}

		nDataEndIndex -= len1;
		if (nDataEndIndex < 0)
		{
			nDataEndIndex = 0;
		}
	}

	int MemoryStream::GetMaxLen() const
	{
		return nMaxLen;
	}

	BYTE* MemoryStream::GetBuf() const
	{
		return pBuf;
	}

	int MemoryStream::GetTotalLen() const
	{
		return nBufLen;
	}

	int MemoryStream::AvaliableReadLen()
	{
		if (nDataStartIndex == -1 && nDataEndIndex == -1)
		{
			return 0;
		}
		else
		{
			if (nDataEndIndex >= nDataStartIndex)
			{
				return nDataEndIndex - nDataStartIndex + 1;
			}
			else
			{
				return 0;
			}
		}
	}

	int MemoryStream::AvaliableWriteLen()
	{
		if (nDataStartIndex == -1 && nDataEndIndex == -1)
		{
			return  nBufLen;
		}
		else
		{
			return nBufLen - AvaliableReadLen();
		}
	}

	int MemoryStream::AvaliableRightWriteLen()
	{
		if (nDataStartIndex == -1 && nDataEndIndex == -1)
		{
			return nBufLen;
		}
		else
		{
			return nBufLen - nDataEndIndex - 1;
		}
	}

	int MemoryStream::Copy(int len, BYTE* buf /*= nullptr*/)
	{
		int len1 = 0;

		if (buf && len > 0)
		{
			len1 = len <= AvaliableReadLen() ? len : AvaliableReadLen();
			memcpy(buf, pBuf + nDataStartIndex, len1);
		}

		return len1;
	}

	int MemoryStream::Read(int len, BYTE* buf /*= nullptr*/)
	{
		int len1 = 0;

		if (len > 0)
		{
			len1 = len <= AvaliableReadLen() ? len : AvaliableReadLen();

			if (buf)
			{
				memcpy(buf, pBuf + nDataStartIndex, len1);
			}

			nDataStartIndex += len1;
		}

		return len1;
	}

	bool MemoryStream::Write(BYTE* buf, int len)
	{
		int len1 = AvaliableWriteLen();
		int len2 = AvaliableReadLen();
		int len3 = AvaliableRightWriteLen();

		if (len > len3)
		{
			if (len > len1)
			{
				bool b = ReAssignBuf(len + AvaliableReadLen());
				if (!b)
				{
					return false;
				}
			}
			else
			{
				DataPanLeft(nDataStartIndex);
			}
		}

		memcpy(pBuf + nDataEndIndex + 1, buf, len);
		nDataEndIndex += len;
		if (nDataStartIndex == -1)
		{
			nDataStartIndex = 0;
		}

		return true;
	}

	void MemoryStream::Clear()
	{
		memset(pBuf, 0, nBufLen);
		nDataStartIndex = -1;
		nDataEndIndex = -1;
	}

	void MemoryStream::RegCallback(MSOverMaxBufLenCallback callback)
	{
		vecFns.push_back(callback);
	}
}