#pragma once

#include <string>
using namespace std;
#include "NetworkStream.h"


namespace com
{
	// NetworkStream writeonly
	class NetworkStreamWrite final : public NetworkStream
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: BYTE * buf
		// Parameter: int len
		// Parameter: EByteOrder bo:	byte order
		//************************************
		NetworkStreamWrite(BYTE* buf, int len, EEndian bo = EEndian::big);

	protected:
		//************************************
		// Method:    Write Data
		// Parameter: void * pDest
		// Parameter: int len
		//************************************
		int WriteData(void* pDest, int len);

		//************************************
		// Method:    Write String Prefix Value
		// Parameter: EStringPrefixByteLen len
		//************************************
		int WriteStrPrefixVal(EStringPrefixByteLen len, int val);

	public:
		//************************************
		// Method:    Write Buf
		// Parameter: BYTE * buf
		// Parameter: int len
		//************************************
		int WriteBuf(BYTE* buf, int len);

		//************************************
		// Method:    Write Byte Data
		// Parameter: BYTE & val
		//************************************
		int WriteByte(BYTE& val);

		//************************************
		// Method:    Write SHORT Data
		// Parameter: SHORT & val
		//************************************
		int WriteShort(SHORT& val);

		//************************************
		// Method:    Write USHORT Data
		// Parameter: USHORT & val
		//************************************
		int WriteUShort(USHORT& val);

		//************************************
		// Method:    Write INT16 Data
		// Parameter: INT16 & val
		//************************************
		int WriteInt16(INT16& val);

		//************************************
		// Method:    Write UINT16 Data
		// Parameter: UINT16 & val
		//************************************
		int WriteUInt16(UINT16& val);

		//************************************
		// Method:    Write INT32 Data
		// Parameter: INT32 & val
		//************************************
		int WriteInt32(INT32& val);

		//************************************
		// Method:    Write UINT32 Data
		// Parameter: UINT32 & val
		//************************************
		int WriteUInt32(UINT32& val);

		//************************************
		// Method:    Write INT64 Data
		// Parameter: INT64 & val
		//************************************
		int WriteInt64(INT64& val);

		//************************************
		// Method:    Write UINT64 Data
		// Parameter: UINT64 & val
		//************************************
		int WriteUInt64(UINT64& val);

		//************************************
		// Method:    Write FLOAT Data
		// Parameter: FLOAT & val
		//************************************
		int WriteFloat(FLOAT& val);

		//************************************
		// Method:    Write double Data
		// Parameter: double & val
		//************************************
		int WriteDouble(double& val);

		//************************************
		// Method:    Write GB2312 string
		// Parameter: string str
		// Parameter: bool hasPrefix = true
		// Parameter: EStringPrefixByteLen prefixLen = EStringPrefixByteLen::Int32
		// Parameter: bool hasEndChar = true
		// Parameter: bool isPrefixContainEndChar = true
		//************************************
		int WriteGB2312Str(string str, bool hasPrefix = true, EStringPrefixByteLen prefixLen = EStringPrefixByteLen::Int32, 
			bool hasEndChar = true, bool isPrefixContainEndChar = true);

		//************************************
		// Method:    Write UTF-16 string
		// Parameter: wstring str
		// Parameter: bool hasPrefix = true
		// Parameter: EStringPrefixByteLen prefixLen = EStringPrefixByteLen::Int32
		// Parameter: bool hasEndChar = true
		// Parameter: bool isPrefixContainEndChar = true
		//************************************
		int WriteUTF16Str(wstring str, bool hasPrefix = true, EStringPrefixByteLen prefixLen = EStringPrefixByteLen::Int32,
			bool hasEndChar = true, bool isPrefixContainEndChar = true);

		//************************************
		// Method:    Write UTF-8 string
		// Parameter: string str(UTF-8 string)
		// Parameter: bool hasPrefix = true
		// Parameter: EStringPrefixByteLen prefixLen = EStringPrefixByteLen::Int32
		// Parameter: bool hasEndChar = true
		// Parameter: bool isPrefixContainEndChar = true
		//************************************
		int WriteUTF8Str(string str, bool hasPrefix = true, EStringPrefixByteLen prefixLen = EStringPrefixByteLen::Int32,
			bool hasEndChar = true, bool isPrefixContainEndChar = true);
	};
}