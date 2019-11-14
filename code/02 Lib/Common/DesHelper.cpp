#include "stdafx.h"
#include "Include/com/DesHelper.h"


namespace com
{
	DesHelper::DesHelper()
	{

	}

	void DesHelper::Encrypt(unsigned char* outbuf, unsigned char * inbuf, int inlen, int* outLen, unsigned char * key, unsigned char * iv)
	{
		//BIO *bio, *mbio, *cbio;
		//unsigned char *dst;

		//mbio = BIO_new(BIO_s_mem());
		//cbio = BIO_new(BIO_f_cipher());
		//BIO_set_cipher(cbio, EVP_des_ecb(), key, iv, 1);

		//bio = BIO_push(cbio, mbio);
		//BIO_write(bio, inbuf, inlen);
		//BIO_flush(bio);

		//*outLen = BIO_get_mem_data(mbio, (unsigned char **)& dst);
		////unsigned char * outbuf = (unsigned char *)malloc(*outLen);

		//memcpy(outbuf, dst, *outLen);
		//BIO_free_all(bio);
	}
}