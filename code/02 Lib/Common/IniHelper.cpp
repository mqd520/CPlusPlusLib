#include "stdafx.h"
#include "Include/com/IniHelper.h"
#include <windows.h>

#define CharMaxLen		(255)		// char max len

namespace com
{
	IniHelper::IniHelper()
	{

	}

	int IniHelper::ReadInt(string section, string key, int iDefaultValue, string strFilePath)
	{
		return GetPrivateProfileIntA(section.c_str(), key.c_str(), iDefaultValue, strFilePath.c_str());
	}

	float IniHelper::ReadFloat(string section, string key, float fltDefaultValue, string strFilePath)
	{
		float fltResult;

		char chResult[CharMaxLen] = { 0 };
		char chDefault[CharMaxLen] = { 0 };
		sprintf_s(chDefault, CharMaxLen, "%f", fltDefaultValue);

		GetPrivateProfileStringA(section.c_str(), key.c_str(), chDefault, chResult, CharMaxLen, strFilePath.c_str());
		fltResult = (float)atof(chResult);

		return fltResult;
	}

	double IniHelper::ReadDouble(string section, string key, double douDefaultValue, string strFilePath)
	{
		double douResult;

		char chResult[CharMaxLen] = { 0 };
		char chDefault[CharMaxLen] = { 0 };
		sprintf_s(chDefault, CharMaxLen, "%f", douDefaultValue);

		GetPrivateProfileStringA(section.c_str(), key.c_str(), chDefault, chResult, CharMaxLen, strFilePath.c_str());
		douResult = (double)atof(chResult);

		return douResult;
	}

	bool IniHelper::ReadBool(string section, string key, bool bolDefaultValue, string strFilePath)
	{
		char chResult[CharMaxLen] = { 0 };
		char chDefault[CharMaxLen] = { 0 };
		sprintf_s(chDefault, CharMaxLen, "%f", bolDefaultValue);

		GetPrivateProfileStringA(section.c_str(), key.c_str(), chDefault, chResult, CharMaxLen, strFilePath.c_str());

		if (strcmp(chDefault, "True") == 0 || strcmp(chDefault, "true") == 0)
		{
			return true;
		}

		return false;
	}

	string IniHelper::ReadString(string section, string key, string strDefaultValue, string strFilePath)
	{
		char chResult[CharMaxLen] = { 0 };
		GetPrivateProfileStringA(section.c_str(), key.c_str(), strDefaultValue.c_str(), chResult, CharMaxLen, strFilePath.c_str());
		string str = chResult;

		return str;
	}
}