#pragma once

#include <string>
using namespace std;


namespace com
{
	// Md5
	class Md5 final
	{
	private:
		Md5();

	public:
		//************************************
		// Method:    Encrypt
		// Parameter: const string & src
		// Parameter: bool bCapital
		//************************************
		static string Encrypt(const string& src, bool bCapital = true);
	};
}