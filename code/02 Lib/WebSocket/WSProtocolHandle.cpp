#include "stdafx.h"
#include "Include//ws/WSProtocolHandle.h"
#include "Include/ws/WSException.h"

#include <vector>
using namespace std;

#include "com/HttpRequest.h"
#include "com/HttpResponse.h"
#include "com/sha1.h"
#include "com/Base64.h"
using namespace com;


#pragma warning (push)
#pragma warning (disable: 4244)
#pragma warning (disable: 4293)


// ParseDataInfo
typedef struct tagParseDataInfo
{
	BYTE* buf;
	int len;
}ParseDataInfo;


#define Max_WsPacketData_Len		(8096)			// max ws packet data length


namespace ws
{
	WSProtocolHandle::WSProtocolHandle(int Id) :
		Id(Id),
		bSuccessed(false),
		strKey(""),
		strProtocol(""),
		strVersion("")
	{

	}

	int WSProtocolHandle::GetId()
	{
		return Id;
	}

	string WSProtocolHandle::GetKey()
	{
		return strKey;
	}

	string WSProtocolHandle::GetProtocol()
	{
		return strProtocol;
	}

	string WSProtocolHandle::GetVersion()
	{
		return strVersion;
	}

	bool WSProtocolHandle::IsHandShakeComplete()
	{
		return bSuccessed;
	}

	int WSProtocolHandle::HandShake(BYTE* pBuf, int len, BYTE* pBuf1, int len1)
	{
		int n = 0;

		HttpRequest req;
		HttpRequest::Parse(req, pBuf, len);

		if (req.bSuccess)
		{
			if (req.method == "GET")
			{
				strKey = req.GetReqHeaderValue("Sec-WebSocket-Key");
				strProtocol = req.GetReqHeaderValue("Sec-WebSocket-Protocol");
				strVersion = req.GetReqHeaderValue("Sec-WebSocket-Version");

				if (!strKey.empty())
				{
					string str = strKey + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

					char hash[32] = { 0 };
					char bhash[128] = { 0 };

					SHA1_CTX ctx;
					SHA1_Init(&ctx);
					SHA1_Update(&ctx, (const unsigned char*)str.c_str(), str.size());
					SHA1_Final((unsigned char*)hash, &ctx);
					Base64encode(bhash, hash, 20);

					HttpResponse response(101, "Switching Protocols");
					response.RemoveResponseHeader();
					response.SetResponseHeader("Upgrade", "WebSocket");
					response.SetResponseHeader("Connection", "Upgrade");
					response.SetResponseHeader("Sec-WebSocket-Accept", bhash);

					if (!strProtocol.empty())
					{
						response.SetResponseHeader("Sec-WebSocket-Protocol", strProtocol);
					}

					n = response.BuildBuf(pBuf1, len1, false, false);
				}
				else
				{
					throw WSException(EWSExceptionCode::KeyEmpty);
				}
			}
			else
			{
				throw WSException(EWSExceptionCode::DenyGet);
			}
		}
		else
		{
			throw WSException(EWSExceptionCode::HttpError);
		}

		return n;
	}

	string WSProtocolHandle::HandShake(BYTE* pBuf, int len)
	{
		string str;
		BYTE buf[1024] = { 0 };
		HandShake(pBuf, len, buf, 1024);
		str = (char*)buf;

		return str;
	}

	void WSProtocolHandle::HandShakeComplete()
	{
		bSuccessed = true;
	}

	BYTE* WSProtocolHandle::ParsePacket(BYTE* pBuf, int len, int* len1)
	{
		BYTE* pResult = NULL;
		if (len1 != NULL)
		{
			*len1 = 0;
		}

		ms.Write(pBuf, len);
		BYTE* pBuf2 = ms.GetBuf();
		int len2 = ms.AvaliableReadLen();

		vector<ParseDataInfo> vec;
		int nParsedLen = 0;		// parsed buf length: pBuf2(ms)
		while (true)
		{
			int bufLen = len2 - nParsedLen;
			BYTE* pBuf3 = pBuf2 + nParsedLen;

			if (bufLen <= 0)
			{
				break;
			}

			BYTE* p = NULL;
			int len3 = 0;
			int n = ParseSinglePacket(pBuf3, bufLen, &p, &len3);
			nParsedLen += n;

			if (p && len3 > 0)
			{
				vec.push_back({ p, len3 });
			}
			else
			{
				break;
			}
		}

		if (nParsedLen > 0)
		{
			ms.Read(nParsedLen);	// read ms
		}

		if (ms.AvaliableReadLen() >= Max_WsPacketData_Len)	// over max packet data length
		{
			ms.Clear();

			for (vector<ParseDataInfo>::iterator it = vec.begin(); it != vec.end(); it++)
			{
				delete it->buf;
			}

			throw WSException(EWSExceptionCode::OutBuf);
		}
		else
		{
			int lenTotal = 0;
			for (vector<ParseDataInfo>::iterator it = vec.begin(); it != vec.end(); it++)
			{
				lenTotal += it->len;
			}

			if (lenTotal > 0)
			{
				pResult = new BYTE[lenTotal];
				int index = 0;
				for (vector<ParseDataInfo>::iterator it = vec.begin(); it != vec.end(); it++)
				{
					memcpy(pResult + index, it->buf, it->len);
					index += it->len;

					delete it->buf;
				}
			}

			if (len1 != NULL)
			{
				*len1 = lenTotal;
			}
		}

		return pResult;
	}

	int WSProtocolHandle::ParseSinglePacket(BYTE* pBuf, int len, BYTE** ppBuf, int* len1)
	{
		BYTE* pResult = NULL;
		int dataLen = 0;

		if (len1 != NULL)
		{
			*len1 = dataLen;
		}

		if (ppBuf != NULL)
		{
			*ppBuf = pResult;
		}

		vector<BYTE> receivedData;
		vector<BYTE> rxbuf;

		for (int i = 0; i < len; i++)
		{
			rxbuf.push_back(pBuf[i]);
		}

		const BYTE* data = (BYTE*)&rxbuf[0];	// peek, but don't consume

		wsheader_type ws;
		ws.fin = (data[0] & 0x80) == 0x80;
		ws.opcode = (wsheader_type::opcode_type) (data[0] & 0x0f);
		ws.mask = (data[1] & 0x80) == 0x80;
		ws.N0 = (data[1] & 0x7f);
		ws.header_size = 2 + (ws.N0 == 126 ? 2 : 0) + (ws.N0 == 127 ? 8 : 0) + (ws.mask ? 4 : 0);

		if ((int)rxbuf.size() < ws.header_size)
		{
			return 0; /* Need: ws.header_size - rxbuf.size() */
		}

		int i;
		if (ws.N0 < 126) {
			ws.N = ws.N0;
			i = 2;
		}
		else if (ws.N0 == 126) {
			ws.N = 0;
			ws.N |= ((unsigned __int64)data[2]) << 8;
			ws.N |= ((unsigned __int64)data[3]) << 0;
			i = 4;
		}
		else if (ws.N0 == 127) {
			ws.N = 0;
			ws.N |= ((unsigned __int64)data[2]) << 56;
			ws.N |= ((unsigned __int64)data[3]) << 48;
			ws.N |= ((unsigned __int64)data[4]) << 40;
			ws.N |= ((unsigned __int64)data[5]) << 32;
			ws.N |= ((unsigned __int64)data[6]) << 24;
			ws.N |= ((unsigned __int64)data[7]) << 16;
			ws.N |= ((unsigned __int64)data[8]) << 8;
			ws.N |= ((unsigned __int64)data[9]) << 0;
			i = 10;
		}
		if (ws.mask) {
			ws.masking_key[0] = ((BYTE)data[i + 0]) << 0;
			ws.masking_key[1] = ((BYTE)data[i + 1]) << 0;
			ws.masking_key[2] = ((BYTE)data[i + 2]) << 0;
			ws.masking_key[3] = ((BYTE)data[i + 3]) << 0;
		}
		else {
			ws.masking_key[0] = 0;
			ws.masking_key[1] = 0;
			ws.masking_key[2] = 0;
			ws.masking_key[3] = 0;
		}

		if (rxbuf.size() < ws.header_size + ws.N)
		{
			return 0; /* Need: ws.header_size+ws.N - rxbuf.size() */
		}

		// We got a whole message, now do something with it:
		if (ws.opcode == wsheader_type::TEXT_FRAME ||
			ws.opcode == wsheader_type::BINARY_FRAME ||
			ws.opcode == wsheader_type::CONTINUATION
			)
		{
			if (ws.mask)
			{
				for (size_t i = 0; i != ws.N; ++i)
				{
					rxbuf[i + ws.header_size] ^= ws.masking_key[i & 0x3];
				}
			}

			receivedData.insert(receivedData.end(), rxbuf.begin() + ws.header_size, rxbuf.begin() + ws.header_size + (size_t)ws.N);	// just feed
			if (ws.fin) {

				dataLen = (int)receivedData.size();
				pResult = new BYTE[dataLen];
				int index = 0;
				for (vector<BYTE>::iterator it = receivedData.begin(); it != receivedData.end(); it++)
				{
					pResult[index++] = *it;
				}

				if (len1 != NULL)
				{
					*len1 = dataLen;
				}

				if (ppBuf != NULL)
				{
					*ppBuf = pResult;
				}
			}
		}
		else if (ws.opcode == wsheader_type::PING){}
		else if (ws.opcode == wsheader_type::PONG) {}
		else if (ws.opcode == wsheader_type::CLOSE) {}
		else {}

		return ws.header_size + ws.N;
	}

	BYTE* WSProtocolHandle::BuildPacket(wsheader_type::opcode_type type, BYTE* pBuf, int len, bool bMask, int* len1)
	{
		BYTE* pResult = NULL;

		const BYTE masking_key[4] = { 0x12, 0x34, 0x56, 0x78 };

		std::vector<BYTE> header;
		header.assign(2 + (len >= 126 ? 2 : 0) + (len >= 65536 ? 6 : 0) + (bMask ? 4 : 0), 0);
		header[0] = 0x80 | type;

		if (false) {}
		else if (len < 126)
		{
			header[1] = (len & 0xff) | (bMask ? 0x80 : 0);
			if (bMask)
			{
				header[2] = masking_key[0];
				header[3] = masking_key[1];
				header[4] = masking_key[2];
				header[5] = masking_key[3];
			}
		}
		else if (len < 65536)
		{
			header[1] = 126 | (bMask ? 0x80 : 0);
			header[2] = (len >> 8) & 0xff;
			header[3] = (len >> 0) & 0xff;
			if (bMask)
			{
				header[4] = masking_key[0];
				header[5] = masking_key[1];
				header[6] = masking_key[2];
				header[7] = masking_key[3];
			}
		}
		else
		{
			// TODO: run coverage testing here
			header[1] = 127 | (bMask ? 0x80 : 0);
			header[2] = (len >> 56) & 0xff;
			header[3] = (len >> 48) & 0xff;
			header[4] = (len >> 40) & 0xff;
			header[5] = (len >> 32) & 0xff;
			header[6] = (len >> 24) & 0xff;
			header[7] = (len >> 16) & 0xff;
			header[8] = (len >> 8) & 0xff;
			header[9] = (len >> 0) & 0xff;
			if (bMask)
			{
				header[10] = masking_key[0];
				header[11] = masking_key[1];
				header[12] = masking_key[2];
				header[13] = masking_key[3];
			}
		}

		std::vector<BYTE> txbuf;
		// N.B. - txbuf will keep growing until it can be transmitted over the socket:
		txbuf.insert(txbuf.end(), header.begin(), header.end());
		for (int i = 0; i < len; i++)
		{
			txbuf.push_back((BYTE)pBuf[i]);
		}

		if (bMask)
		{
			for (size_t i = 0; i != len; ++i)
			{
				*(txbuf.end() - len + i) ^= masking_key[i & 0x3];
			}
		}

		pResult = new BYTE[(int)txbuf.size()];
		int index = 0;
		for (vector<BYTE>::iterator it = txbuf.begin(); it != txbuf.end(); it++)
		{
			pResult[index++] = *it;
		}

		if (len1 != NULL)
		{
			*len1 = (int)txbuf.size();
		}

		return pResult;
	}
}

#pragma warning (pop)