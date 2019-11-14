#pragma once

#include <string>
using namespace std;

namespace com
{
	// INI Helper
	class IniHelper final
	{
	private:
		IniHelper();

	public:
		//************************************
		// Method:    读取int
		// Parameter: string section
		// Parameter: string key
		// Parameter: int iDefaultValue
		// Parameter: string strFilename
		//************************************
		static int ReadInt(string section, string key, int iDefaultValue, string strFilePath);

		//************************************
		// Method:    读取float
		// Parameter: string section
		// Parameter: string key
		// Parameter: int iDefaultValue
		// Parameter: string strFilename
		//************************************
		static float ReadFloat(string section, string key, float fltDefaultValue, string strFilePath);

		//************************************
		// Method:    读取double
		// Parameter: string section
		// Parameter: string key
		// Parameter: int iDefaultValue
		// Parameter: string strFilename
		//************************************
		static double ReadDouble(string section, string key, double douDefaultValue, string strFilePath);

		//************************************
		// Method:    读取bool
		// Parameter: string section
		// Parameter: string key
		// Parameter: int iDefaultValue
		// Parameter: string strFilename
		//************************************
		static bool ReadBool(string section, string key, bool bolDefaultValue, string strFilePath);

		//************************************
		// Method:    读取String
		// Parameter: string section
		// Parameter: string key
		// Parameter: int iDefaultValue
		// Parameter: string strFilename
		//************************************
		static string ReadString(string section, string key, string strDefaultValue, string strFilePath);
	};
}
