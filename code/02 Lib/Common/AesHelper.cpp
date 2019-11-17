#include "stdafx.h"
#include "AesHelper.h"

#include "Base64.h"

#pragma warning(disable: 4996)


namespace com
{
	AesHelper::AesHelper()
	{

	}

	int AesHelper::Encrypt(BYTE buf[], const string& clearText, const string& key, int mode /*= AES::ECB*/, const string& iv /*= ""*/)
	{
		int result = 0;

		size_t length = clearText.length();
		int block_num = length / BLOCK_SIZE + 1;

		// 明文
		char* szDataIn = new char[block_num * BLOCK_SIZE + 1];
		memset(szDataIn, 0x00, block_num * BLOCK_SIZE + 1);
		strcpy(szDataIn, clearText.c_str());

		// 进行PKCS7Padding填充。
		int k = length % BLOCK_SIZE;
		int j = length / BLOCK_SIZE;
		int padding = BLOCK_SIZE - k;
		for (int i = 0; i < padding; i++)
		{
			szDataIn[j * BLOCK_SIZE + k + i] = padding;
		}
		szDataIn[block_num * BLOCK_SIZE] = '\0';

		// 加密后的密文
		char *szDataOut = new char[block_num * BLOCK_SIZE + 1];
		memset(szDataOut, 0, block_num * BLOCK_SIZE + 1);

		AES aes;
		aes.MakeKey(key.c_str(), iv.c_str(), 16, 16);
		aes.Encrypt(szDataIn, szDataOut, block_num * BLOCK_SIZE, mode);

		result = block_num * BLOCK_SIZE;
		memcpy(buf, szDataOut, result);

		delete[] szDataIn;
		delete[] szDataOut;

		return result;
	}

	string AesHelper::Encrypt(const string& clearText, const string& key, int mode /*= AES::ECB*/, const string& iv /*= ""*/)
	{
		BYTE buf[1024] = { 0 };
		int len = Encrypt(buf, clearText, key, mode, iv);

		return (char*)buf;
	}

	string AesHelper::Encrypt_2_Base64(const string& clearText, const string& key, int mode /*= AES::ECB*/, const string& iv /*= ""*/)
	{
		BYTE buf[2048] = { 0 };
		int len = Encrypt(buf, clearText, key, mode, iv);

		return base64_encode(buf, len);
	}

	string AesHelper::Decrypt(BYTE* buf, int len, const string& key, int mode /*= AES::ECB*/, const string& iv /*= ""*/)
	{
		size_t length = len;

		// 密文
		char *szDataIn = new char[length + 1];
		memset(szDataIn, 0, length + 1);
		memcpy(szDataIn, buf, length);

		// 明文
		char *szDataOut = new char[length + 1];
		memset(szDataOut, 0, length + 1);
		memcpy(szDataOut, buf, length);

		AES aes;
		aes.MakeKey(key.c_str(), iv.c_str(), 16, 16);
		aes.Decrypt(szDataIn, szDataOut, length, mode);

		// 去除PKCS7Padding填充
		if (0x00 < szDataOut[length - 1] && szDataOut[length - 1] <= 0x16)
		{
			int tmp = szDataOut[length - 1];
			for (int i = length - 1; i >= (int)length - tmp; i--)
			{
				if (szDataOut[i] != tmp)
				{
					memset(szDataOut, 0, length);
					break;
				}
				else
					szDataOut[i] = 0;
			}
		}

		string result = string(szDataOut);

		delete[] szDataIn;
		delete[] szDataOut;

		return result;
	}

	string AesHelper::Decrypt_from_Base64(const string& cipherText, const string& key, int mode /*= AES::ECB*/, const string& iv /*= ""*/)
	{
		string str = base64_decode(cipherText);

		return Decrypt((BYTE*)str.c_str(), str.length(), key, mode, iv);
	}
}