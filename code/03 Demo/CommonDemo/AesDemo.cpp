#include "stdafx.h"
#include "AesDemo.h"

#include "com/AesHelper.h"
#include "com/BufferTool.h"
using namespace com;


AesDemo::AesDemo()
{

}

void AesDemo::Test1()
{
	string clearText = "hello world";
	string key = "1234567890123456";

	printf("clearText	: %s \n", clearText.c_str());
	printf("key		: %s \n", key.c_str());


	BYTE buf1[1024] = { 0 };
	int len1 = AesHelper::Encrypt(buf1, clearText, key);
	string str1 = BufferTool::Join(buf1, len1, ", ", "0x%x");

	printf("Buf		: %s \n", str1.c_str());

	string str = AesHelper::Decrypt(buf1, len1, key);

	printf("clearText	: %s \n", str.c_str());
}

void AesDemo::Test2()
{
	string clearText = "hello world";
	string key = "1234567890123456";

	printf("clearText	: %s \n", clearText.c_str());
	printf("key		: %s \n", key.c_str());

	string str1 = AesHelper::Encrypt_2_Base64(clearText, key);
	printf("Base64		: %s \n", str1.c_str());

	string str2 = AesHelper::Decrypt_from_Base64(str1, key);
	printf("clearText	: %s \n", str2.c_str());
}