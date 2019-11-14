#include "stdafx.h"
#include "Include/com/ByteStream.h"

namespace com
{
	ByteStream::ByteStream(BYTE* pBuf, int len, bool copy /*= false*/) :
		pBuf(pBuf),
		nLen(len),
		bCopy(copy)
	{
		if (this->bCopy && this->nLen > 0)
		{
			this->pBuf = new BYTE[nLen];
			memcpy(this->pBuf, pBuf, len);
		}
	}

	ByteStream::~ByteStream()
	{
		FreeBuf();
	}

	void ByteStream::FreeBuf()
	{
		if (bCopy)
		{
			if (pBuf)
			{
				delete pBuf;
				pBuf = nullptr;
			}
		}
	}

	BYTE* ByteStream::GetBuf() const
	{
		return pBuf;
	}

	int ByteStream::GetBufLen() const
	{
		return nLen;
	}

	void ByteStream::ResetBuf(BYTE* pBuf, int len, bool copy /*= false*/)
	{
		FreeBuf();

		this->pBuf = pBuf;
		this->nLen = len;
		this->bCopy = copy;

		if (this->bCopy && this->nLen > 0)
		{
			this->pBuf = new BYTE[nLen];
			memcpy(this->pBuf, pBuf, len);
		}
	}

	void ByteStream::Copy(BYTE* pDest, int len, int start /*= 0*/)
	{
		int start1 = start <= nLen - 1 ? start : nLen - 1;
		int len1 = nLen - start1;

		memcpy(pDest, pBuf + start1, len1);
	}

	void ByteStream::Read(int len, BYTE* buf /*= nullptr*/)
	{
		if (buf)
		{
			int len1 = len <= nLen ? len : nLen;
			memcpy(buf, this->pBuf, len1);
		}

		BYTE* pTmp = nullptr;
		if (nLen > 0)
		{
			pTmp = new BYTE[nLen];
			memcpy(pTmp, this->pBuf, nLen);
		}

		FreeBuf();

		int len1 = len <= nLen ? len : nLen;

		if (len1 == nLen)
		{
			this->pBuf = nullptr;
			this->nLen = 0;
		}
		else
		{
			nLen = nLen - len1;

			if (this->pBuf)
			{
				this->pBuf = this->pBuf + len1 - 1;
			}
			else
			{
				this->pBuf = new BYTE[nLen];
				memcpy(this->pBuf, pTmp + len1, nLen);
			}
		}
	}

	void ByteStream::Write(BYTE* buf, int len)
	{

	}
}