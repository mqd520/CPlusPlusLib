#include "stdafx.h"
#include "UrlTool.h"


namespace com
{
	UrlTool::UrlTool()
	{

	}

	string UrlTool::Encode(const string& str, bool bUpperCase /*= true*/)
	{
		char pBuf[1024] = { 0 };
		int cbBufLen = 1024;

		size_t len_ascii = strlen(str.c_str());
		if (len_ascii == 0)
		{
			pBuf[0] = 0;

			return "";
		}

		//先转换到UTF-8
		char baseChar = bUpperCase ? 'A' : 'a';
		int cchWideChar = MultiByteToWideChar(CP_ACP, 0, str.c_str(), len_ascii, NULL, 0);
		LPWSTR pUnicode = (LPWSTR)malloc((cchWideChar + 1) * sizeof(WCHAR));
		if (pUnicode == NULL)
		{
			return "";
		}
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), len_ascii, pUnicode, cchWideChar + 1);

		int cbUTF8 = WideCharToMultiByte(CP_UTF8, 0, pUnicode, cchWideChar, NULL, 0, NULL, NULL);
		LPSTR pUTF8 = (LPSTR)malloc((cbUTF8 + 1) * sizeof(CHAR));
		if (pUTF8 == NULL)
		{
			free(pUnicode);
			return "";
		}
		WideCharToMultiByte(CP_UTF8, 0, pUnicode, cchWideChar, pUTF8, cbUTF8 + 1, NULL, NULL);
		pUTF8[cbUTF8] = '\0';

		unsigned char c;
		int cbDest = 0; //累加
		unsigned char *pSrc = (unsigned char*)pUTF8;
		unsigned char *pDest = (unsigned char*)pBuf;
		while (*pSrc && cbDest < cbBufLen - 1)
		{
			c = *pSrc;
			if (isalpha(c) || isdigit(c) || c == '-' || c == '.' || c == '~')
			{
				*pDest = c;
				++pDest;
				++cbDest;
			}
			else if (c == ' ')
			{
				*pDest = '+';
				++pDest;
				++cbDest;
			}
			else
			{
				if (cbDest + 3 > cbBufLen - 1)
				{
					break;
				}

				pDest[0] = '%';
				pDest[1] = (c >= 0xA0) ? ((c >> 4) - 10 + baseChar) : ((c >> 4) + '0');
				pDest[2] = ((c & 0xF) >= 0xA) ? ((c & 0xF) - 10 + baseChar) : ((c & 0xF) + '0');
				pDest += 3;
				cbDest += 3;
			}

			++pSrc;
		}

		*pDest = '\0';
		free(pUnicode);
		free(pUTF8);

		return pBuf;
	}

	string UrlTool::Decode(const string& str)
	{
		return str;
	}
}