#pragma once

#include "Aes.h"


namespace com
{
	// AesHelper
	class AesHelper final
	{
	private:
		AesHelper();

	public:
		//************************************
		// Method:    Encrypt (PKCS7Padding, 128bit)
		// Parameter: BYTE buf[]
		// Parameter: const string & clearText
		// Parameter: const string & key
		// Parameter: int mode
		// Parameter: const string & iv
		//************************************
		static int Encrypt(BYTE buf[], const string& clearText, const string& key, int mode = AES::ECB, const string& iv = "");

		//************************************
		// Method:    Encrypt (PKCS7Padding, 128bit)
		// Parameter: const string & clearText
		// Parameter: const string & key
		// Parameter: int mode
		// Parameter: const string & iv
		//************************************
		static string Encrypt(const string& clearText, const string& key, int mode = AES::ECB, const string& iv = "");

		//************************************
		// Method:    Encrypt (PKCS7Padding, 128bit)
		// Parameter: const string & clearText
		// Parameter: const string & key
		// Parameter: int mode
		// Parameter: const string & iv
		//************************************
		static string Encrypt_2_Base64(const string& clearText, const string& key, int mode = AES::ECB, const string& iv = "");

		//************************************
		// Method:    Decrypt (PKCS7Padding, 128bit)
		// Parameter: BYTE * buf
		// Parameter: int len
		// Parameter: const string & key
		// Parameter: int mode
		// Parameter: const string & iv
		//************************************
		static string Decrypt(BYTE* buf, int len, const string& key, int mode = AES::ECB, const string& iv = "");

		//************************************
		// Method:    Decrypt from Base64
		// Parameter: const string & cipherText
		// Parameter: const string & key
		// Parameter: int mode
		// Parameter: const string & iv
		//************************************
		static string Decrypt_from_Base64(const string& cipherText, const string& key, int mode = AES::ECB, const string& iv = "");
	};
}