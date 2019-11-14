#include "stdafx.h"
#include "Include/com/NetworkStreamRead.h"

#include "Include/com/StreamTool.h"
#include "Include/com/BufferTool.h"
#include "Include/com/StringTool.h"


namespace com
{
	NetworkStreamRead::NetworkStreamRead(BYTE* buf, int len, EEndian bo /*= EByteOrder::big*/) :
		NetworkStream(buf, len, bo)
	{

	}

	bool NetworkStreamRead::ReadData(void* pDest, int len)
	{
		bool result = false;

		if (len <= AvaliableByteCount())
		{
			memcpy(pDest, pBuf + nDataIndex, len);

			if (len > 1 && bo != StreamTool::GetLocalHostEndian())
			{
				BufferTool::Reverse((BYTE*)pDest, len);
			}

			nDataIndex += len;

			result = true;
		}

		return result;
	}

	int NetworkStreamRead::ReadStrPrefixVal(EStringPrefixByteLen len, bool* result /*= nullptr*/)
	{
		int len1 = 0;

		if (len == EStringPrefixByteLen::Byte)
		{
			len1 = ReadByte(result);
		}
		else if (len == EStringPrefixByteLen::Int16)
		{
			len1 = ReadInt16(result);
		}
		else if (len == EStringPrefixByteLen::Int32)
		{
			len1 = ReadInt32(result);
		}

		return len1;
	}

	int NetworkStreamRead::ReadBuf(int len, BYTE* buf /*= nullptr*/, bool* result /*= nullptr*/)
	{
		bool b = false;
		int len1 = len <= AvaliableByteCount() ? len : AvaliableByteCount();

		if (len1 > 0)
		{
			if (buf)
			{
				memcpy(buf, pBuf + nDataIndex, len1);
			}

			nDataIndex += len1;

			b = true;
		}

		if (result)
		{
			*result = b;
		}

		return len1;
	}

	BYTE NetworkStreamRead::ReadByte(bool* result /*= nullptr*/)
	{
		BYTE val = 0;

		bool b = ReadData(&val, sizeof(BYTE));

		if (result)
		{
			*result = b;
		}

		return val;
	}

	SHORT NetworkStreamRead::ReadShort(bool* result /*= nullptr*/)
	{
		SHORT val = 0;

		bool b = ReadData(&val, sizeof(SHORT));

		if (result)
		{
			*result = b;
		}

		return val;
	}

	USHORT NetworkStreamRead::ReadUShort(bool* result /*= nullptr*/)
	{
		USHORT val = 0;

		bool b = ReadData(&val, sizeof(USHORT));

		if (result)
		{
			*result = b;
		}

		return val;
	}

	INT16 NetworkStreamRead::ReadInt16(bool* result /*= nullptr*/)
	{
		INT16 val = 0;

		bool b = ReadData(&val, sizeof(INT16));

		if (result)
		{
			*result = b;
		}

		return val;
	}

	UINT16 NetworkStreamRead::ReadUInt16(bool* result /*= nullptr*/)
	{
		UINT16 val = 0;

		bool b = ReadData(&val, sizeof(UINT16));

		if (result)
		{
			*result = b;
		}

		return val;
	}

	INT32 NetworkStreamRead::ReadInt32(bool* result /*= nullptr*/)
	{
		INT32 val = 0;

		bool b = ReadData(&val, sizeof(INT32));

		if (result)
		{
			*result = b;
		}

		return val;
	}

	UINT32 NetworkStreamRead::ReadUInt32(bool* result /*= nullptr*/)
	{
		UINT32 val = 0;

		bool b = ReadData(&val, sizeof(UINT32));

		if (result)
		{
			*result = b;
		}

		return val;
	}

	INT64 NetworkStreamRead::ReadInt64(bool* result /*= nullptr*/)
	{
		INT64 val = 0;

		bool b = ReadData(&val, sizeof(INT64));

		if (result)
		{
			*result = b;
		}

		return val;
	}

	UINT64 NetworkStreamRead::ReadUInt64(bool* result /*= nullptr*/)
	{
		UINT64 val = 0;

		bool b = ReadData(&val, sizeof(UINT64));

		if (result)
		{
			*result = b;
		}

		return val;
	}

	FLOAT NetworkStreamRead::ReadFloat(bool* result /*= nullptr*/)
	{
		FLOAT val = 0;

		bool b = ReadData(&val, sizeof(FLOAT));

		if (result)
		{
			*result = b;
		}

		return val;
	}

	double NetworkStreamRead::ReadDouble(bool* result /*= nullptr*/)
	{
		double val = 0;

		bool b = ReadData(&val, sizeof(double));

		if (result)
		{
			*result = b;
		}

		return val;
	}

	string NetworkStreamRead::ReadGB2312Str(int len, bool* result /*= nullptr*/)
	{
		bool b = false;
		string str = "";

		if (len <= AvaliableByteCount())
		{
			char* ch = new char[len + 1];
			memset(ch, 0, len + 1);
			memcpy(ch, pBuf + nDataIndex, len);
			str = ch;
			delete ch;
			nDataIndex += len;

			b = true;
		}

		if (result)
		{
			*result = b;
		}

		return str;
	}

	string NetworkStreamRead::ReadGB2312Str(EStringPrefixByteLen prefixLen /*= EStringPrefixByteLen::Int32*/,
		bool hasEndChar /*= true*/, bool isPrefixContainEndChar /*= true*/, bool* result /*= nullptr*/)
	{
		bool b = false;
		string str = "";

		int originalIndex = nDataIndex;

		int len = 0;	// read byte length
		len += ReadStrPrefixVal(prefixLen, &b);
		if (b)
		{
			if (hasEndChar && isPrefixContainEndChar == false)
			{
				len += GB2312EndCharByteLen;
			}

			if (len > 0)
			{
				str = ReadGB2312Str(len, &b);
				if (!b)
				{
					nDataIndex = originalIndex;	 // revert to original pos
				}
			}
			else
			{
				nDataIndex = originalIndex;	 // revert to original pos
			}
		}
		else
		{
			nDataIndex = originalIndex;	 // revert to original pos
		}

		if (result)
		{
			*result = b;
		}

		return str;
	}

	wstring NetworkStreamRead::ReadUTF16Str(int len, bool* result /*= nullptr*/)
	{
		bool b = false;
		wstring str = L"";

		if (len <= AvaliableByteCount())
		{
			wchar_t* ch = new wchar_t[(len / 2) + 1];
			memset(ch, 0, len + UTF16EndCharByteLen);

			if (bo == StreamTool::GetLocalHostEndian())
			{
				memcpy(ch, pBuf, len);
			}
			else
			{
				int n = 0;
				for (int i = 0; i < len; i += 2)
				{
					BYTE arr[2] = { 0 };
					arr[0] = pBuf[nDataIndex + i + 1];
					arr[1] = pBuf[nDataIndex + i];
					memcpy(ch + n, arr, 2);
					n++;
				}
			}

			str = ch;
			delete ch;

			nDataIndex += len;

			b = true;
		}

		if (result)
		{
			*result = b;
		}

		return str;
	}

	wstring NetworkStreamRead::ReadUTF16Str(EStringPrefixByteLen prefixLen /*= EStringPrefixByteLen::Int32*/,
		bool hasEndChar /*= true*/, bool isPrefixContainEndChar /*= true*/, bool* result /*= nullptr*/)
	{
		bool b = false;
		wstring str = L"";

		int originalIndex = nDataIndex;

		int len = 0;	// read byte length
		len += ReadStrPrefixVal(prefixLen, &b);
		if (b)
		{
			if (hasEndChar && isPrefixContainEndChar == false)
			{
				len += UTF16EndCharByteLen;
			}

			if (len > 0)
			{
				str = ReadUTF16Str(len, &b);
				if (!b)
				{
					nDataIndex = originalIndex;	 // revert to original pos
				}
			}
			else
			{
				nDataIndex = originalIndex;	 // revert to original pos
			}
		}
		else
		{
			nDataIndex = originalIndex;	 // revert to original pos
		}

		if (result)
		{
			*result = b;
		}

		return str;
	}

	string NetworkStreamRead::ReadUTF8Str(int len, bool* result /*= nullptr*/)
	{
		bool b = false;
		string str = "";

		if (len <= AvaliableByteCount())
		{
			char* ch = new char[len + 1];
			memset(ch, 0, len + 1);
			memcpy(ch, pBuf + nDataIndex, len);
			str = StringTool::UTF8_2_GB2312(ch);
			delete ch;

			nDataIndex += len;

			b = true;
		}

		if (result)
		{
			*result = b;
		}

		return str;
	}

	string NetworkStreamRead::ReadUTF8Str(EStringPrefixByteLen prefixLen /*= EStringPrefixByteLen::Int32*/,
		bool hasEndChar /*= true*/, bool isPrefixContainEndChar /*= true*/, bool* result /*= nullptr*/)
	{
		bool b = false;
		string str = "";

		int originalIndex = nDataIndex;

		int len = 0;	// read byte length
		len += ReadStrPrefixVal(prefixLen, &b);
		if (b)
		{
			if (hasEndChar && isPrefixContainEndChar == false)
			{
				len += UTF8EndCharByteLen;
			}

			if (len > 0)
			{
				str = ReadUTF8Str(len, &b);
				if (!b)
				{
					nDataIndex = originalIndex;	 // revert to original pos
				}
			}
			else
			{
				nDataIndex = originalIndex;	 // revert to original pos
			}
		}
		else
		{
			nDataIndex = originalIndex;	 // revert to original pos
		}

		if (result)
		{
			*result = b;
		}

		return str;
	}
}