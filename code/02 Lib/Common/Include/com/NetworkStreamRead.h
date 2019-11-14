#pragma once

#include <string>
using namespace std;
#include "NetworkStream.h"


namespace com
{
	// NetStream readonly
	class NetworkStreamRead final : public NetworkStream
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: BYTE * buf
		// Parameter: int len
		// Parameter: EByteOrder bo:	byte order
		//************************************
		NetworkStreamRead(BYTE* buf, int len, EEndian bo = EEndian::big);

	protected:
		//************************************
		// Method:    Read Data
		// Parameter: void * pDest
		// Parameter: int len
		//************************************
		bool ReadData(void* pDest, int len);

		//************************************
		// Method:    Read String Prefix Value
		// Parameter: EStringPrefixByteLen len
		// Parameter: bool * result
		//************************************
		int ReadStrPrefixVal(EStringPrefixByteLen len, bool* result = nullptr);

	public:
		//************************************
		// Method:    Read Buf data
		// Parameter: int len
		// Parameter: BYTE * buf
		// Parameter: bool * result
		//************************************
		int ReadBuf(int len, BYTE* buf = nullptr, bool* result = nullptr);

		//************************************
		// Method:    Read Byte data
		// Parameter: bool * result
		//************************************
		BYTE ReadByte(bool* result = nullptr);

		//************************************
		// Method:    Read SHORT data
		// Parameter: bool * result
		//************************************
		SHORT ReadShort(bool* result = nullptr);

		//************************************
		// Method:    Read USHORT data
		// Parameter: bool * result
		//************************************
		USHORT ReadUShort(bool* result = nullptr);

		//************************************
		// Method:    Read INT16 data
		// Parameter: bool * result
		//************************************
		INT16 ReadInt16(bool* result = nullptr);

		//************************************
		// Method:    Read UINT16 data
		// Parameter: bool * result
		//************************************
		UINT16 ReadUInt16(bool* result = nullptr);

		//************************************
		// Method:    Read INT32 data
		// Parameter: bool * result
		//************************************
		INT32 ReadInt32(bool* result = nullptr);

		//************************************
		// Method:    Read UINT32 data
		// Parameter: bool * result
		//************************************
		UINT32 ReadUInt32(bool* result = nullptr);

		//************************************
		// Method:    Read INT64 data
		// Parameter: bool * result
		//************************************
		INT64 ReadInt64(bool* result = nullptr);

		//************************************
		// Method:    Read UINT64 data
		// Parameter: bool * result
		//************************************
		UINT64 ReadUInt64(bool* result = nullptr);

		//************************************
		// Method:    Read FLOAT data
		// Parameter: bool * result
		//************************************
		FLOAT ReadFloat(bool* result = nullptr);

		//************************************
		// Method:    Read double data
		// Parameter: bool * result
		//************************************
		double ReadDouble(bool* result = nullptr);

		//************************************
		// Method:    Read GB2312 string
		// Parameter: int len
		// Parameter: bool * result
		//************************************
		string ReadGB2312Str(int len, bool* result = nullptr);

		//************************************
		// Method:    Read GB2312 string
		// Parameter: EStringPrefixByteLen prefixLen
		// Parameter: bool hasEndChar: is endchar included by buf
		// Parameter: bool isPrefixContainEndChar
		// Parameter: bool * result
		//************************************
		string ReadGB2312Str(EStringPrefixByteLen prefixLen = EStringPrefixByteLen::Int32,
			bool hasEndChar = true, bool isPrefixContainEndChar = true, bool* result = nullptr);

		//************************************
		// Method:    Read UTF-16 string
		// Parameter: int len
		// Parameter: bool * result
		//************************************
		wstring ReadUTF16Str(int len, bool* result = nullptr);

		//************************************
		// Method:    Read UTF-16 string
		// Parameter: EStringPrefixByteLen prefixLen
		// Parameter: bool hasEndChar: is endchar included by buf
		// Parameter: bool isPrefixContainEndChar
		// Parameter: bool * result
		//************************************
		wstring ReadUTF16Str(EStringPrefixByteLen prefixLen = EStringPrefixByteLen::Int32,
			bool hasEndChar = true, bool isPrefixContainEndChar = true, bool* result = nullptr);

		//************************************
		// Method:    Read UTF-8 string
		// Parameter: int len
		// Parameter: bool * result
		//************************************
		string ReadUTF8Str(int len, bool* result = nullptr);

		//************************************
		// Method:    Read UTF-8 string
		// Parameter: EStringPrefixByteLen prefixLen
		// Parameter: bool hasEndChar: is endchar included by buf
		// Parameter: bool isPrefixContainEndChar
		// Parameter: bool * result
		//************************************
		string ReadUTF8Str(EStringPrefixByteLen prefixLen = EStringPrefixByteLen::Int32,
			bool hasEndChar = true, bool isPrefixContainEndChar = true, bool* result = nullptr);
	};
}