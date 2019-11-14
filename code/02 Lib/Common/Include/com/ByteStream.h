#pragma once

namespace com
{
	// Byte Stream
	class ByteStream
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: BYTE * pBuf
		// Parameter: int len
		// Parameter: bool copy:	whether create buf clone
		//************************************
		ByteStream(BYTE* pBuf, int len, bool copy = false);

		virtual ~ByteStream();

	protected:
		BYTE* pBuf;		// buf
		int nLen;		// buf len
		bool bCopy;		// whether copy buf

	protected:
		//************************************
		// Method:    Free buf
		//************************************
		void FreeBuf();

	public:
		//************************************
		// Method:    Get buf
		//************************************
		BYTE* GetBuf() const;

		//************************************
		// Method:    Get buf length
		//************************************
		int GetBufLen() const;

		//************************************
		// Method:    Reset buf
		// Parameter: BYTE * pBuf
		// Parameter: int len
		// Parameter: bool copy:	whether create buf clone
		//************************************
		void ResetBuf(BYTE* pBuf, int len, bool copy = false);

		//************************************
		// Method:    Copy buf to specify buf
		// Parameter: BYTE * pDest
		// Parameter: int len
		// Parameter: int start
		//************************************
		void Copy(BYTE* pDest, int len, int start = 0);

		//************************************
		// Method:    Read buf
		// Parameter: int len
		// Parameter: BYTE * buf
		//************************************
		void Read(int len, BYTE* buf = nullptr);

		//************************************
		// Method:    Write buf
		// Parameter: int len
		// Parameter: BYTE * buf
		//************************************
		void Write(BYTE* buf, int len);
	};
}