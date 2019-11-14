#pragma once

#include <vector>
#include <minwindef.h>
#include <minwindef.h>
#include <functional>
using namespace std;
using namespace std::placeholders;


namespace com
{

	class MemoryStream;


	// over max buf length
	// MemoryStream*:	MemoryStream pointer 
	// int:				max buf length
	using MSOverMaxBufLenCallback = std::function < void(MemoryStream*, int) > ;


	// MemoryStream
	class MemoryStream
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: int len
		//************************************
		MemoryStream(int len = 4096, int max = 1024 * 1024);

		~MemoryStream();

	protected:
		BYTE* pBuf;				// buf
		int nBufLen;			// buf length
		int nMaxLen;			// max buf length
		int nDataStartIndex;	// data buf start index
		int nDataEndIndex;		// data buf end index
		vector<MSOverMaxBufLenCallback> vecFns;

	protected:
		//************************************
		// Method:    Reassign buf
		// Parameter: int len
		//************************************
		bool ReAssignBuf(int len);

		//************************************
		// Method:    PanLeft
		// Rerurns:	  actual pan length
		// Parameter: int index
		// Parameter: int len
		// Parameter: int panLen
		//************************************
		int PanLeft(int index, int len, int panLen);

		//************************************
		// Method:    Data PanLeft
		// Parameter: int len
		//************************************
		void DataPanLeft(int len);

	public:
		//************************************
		// Method:    Get max buf length
		//************************************
		int GetMaxLen() const;

		//************************************
		// Method:    Get buf
		//************************************
		BYTE* GetBuf() const;

		//************************************
		// Method:    Get total length
		//************************************
		int GetTotalLen() const;

		//************************************
		// Method:    Get readable buf length
		//************************************
		int AvaliableReadLen();

		//************************************
		// Method:    Get writable buf length
		//************************************
		int AvaliableWriteLen();

		//************************************
		// Method:    Get writable right buf length
		//************************************
		int AvaliableRightWriteLen();

		//************************************
		// Method:    Copy buf to dest buf
		// Returns:   actual copy length 
		// Parameter: int len
		// Parameter: BYTE * buf
		//************************************
		int Copy(int len, BYTE* buf = nullptr);

		//************************************
		// Method:    Read buf
		// Parameter: int len
		// Parameter: BYTE * buf
		//************************************
		int Read(int len, BYTE* buf = nullptr);
		
		//************************************
		// Method:    Write
		// Parameter: BYTE * buf
		// Parameter: int len
		//************************************
		bool Write(BYTE* buf, int len);

		//************************************
		// Method:    Clear
		//************************************
		void Clear();

		//************************************
		// Method:    Reg Callback
		// Parameter: MSOverMaxBufLenCallback callback
		//************************************
		void RegCallback(MSOverMaxBufLenCallback callback);
	};
}