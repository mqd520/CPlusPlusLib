#pragma once

#include <minwindef.h>
#include <string>
#include <vector>
using namespace std;

#include "com/MemoryStream.h"
using namespace com;


namespace ws
{
	struct wsheader_type
	{
		unsigned header_size;
		bool fin;
		bool mask;
		enum opcode_type
		{
			CONTINUATION = 0x0,
			TEXT_FRAME = 0x1,
			BINARY_FRAME = 0x2,
			CLOSE = 8,
			PING = 9,
			PONG = 0xa,
		} opcode;
		int N0;
		unsigned __int64 N;
		BYTE masking_key[4];
	};


	// WebSocket protocol handle
	class WSProtocolHandle
	{
	public:
		//************************************
		// Method:    Constructor
		// Parameter: int Id:	
		//************************************
		WSProtocolHandle(int Id);

	private:
		int Id;					// Id
		bool bSuccessed;		// whether handshake complete
		string strKey;			// ws key
		string strProtocol;		// ws protocol
		string strVersion;		// ws version
		com::MemoryStream ms;		// ms

	private:
		int ParseSinglePacket(BYTE* pBuf, int len, BYTE** ppBuf, int* len1);

	public:
		//************************************
		// Method:    Get Id
		//************************************
		int GetId();

		//************************************
		// Method:    Get Key
		//************************************
		string GetKey();

		//************************************
		// Method:    Get Protocol
		//************************************
		string GetProtocol();

		//************************************
		// Method:    Get Version
		//************************************
		string GetVersion();

		//************************************
		// Method:    Is handshake completed
		//************************************
		bool IsHandShakeComplete();

		//************************************
		// Method:    HandShake Complete
		//************************************
		void HandShakeComplete();

		//************************************
		// Method:    HandShake
		// Returns:   build buf actual length
		// Parameter: pBuf:		recv buf 
		// Parameter: len:		recv buf length
		// Parameter: pBuf1:	build buf
		// Parameter: build:	build buf length
		//************************************
		int HandShake(BYTE* pBuf, int len, BYTE* pBuf1, int len1);

		//************************************
		// Method:    HandShake
		// Returns:   build buf
		// Parameter: pBuf:		recv buf 
		// Parameter: len:		recv buf length
		//************************************
		string HandShake(BYTE* pBuf, int len);

		//************************************
		// Method:    Parse recv buf
		// Returns:   build buf
		// Parameter: pBuf:		recv buf 
		// Parameter: len:		recv buf length
		// Parameter: len1:	build buf actual length
		//************************************
		BYTE* ParsePacket(BYTE* pBuf, int len, int* len1);

		//************************************
		// Method:    Build ws packet
		// Returns:   build buf
		// Parameter: type:		opcode_type 
		// Parameter: pBuf:		recv buf 
		// Parameter: len:		recv buf length
		// Parameter: bMask:	mask
		// Parameter: len1:		build buf actual length
		//************************************
		BYTE* BuildPacket(wsheader_type::opcode_type type, BYTE* pBuf, int len, bool bMask, int* len1);
	};
}