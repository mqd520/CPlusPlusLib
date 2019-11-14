#pragma once

#include <string>
using namespace std;


namespace http
{
	// HttpHeader Define
	class HttpHeaderDef final
	{
	private:
		HttpHeaderDef();

	public:

		// Common ------------------------------------------------------
		static const string ContentType;
		static const string ContentLength;
		static const string Cookie;
		static const string CacheControl;
		static const string Connection;
		// Common ------------------------------------------------------



		// Request -----------------------------------------------------
		static const string UserAgent;
		static const string Host;
		static const string Accept;
		static const string AcceptEncoding;
		static const string AcceptLanguage;
		// Request -----------------------------------------------------



		// Response ----------------------------------------------------
		static const string Server;
		static const string Date;
		// Response ----------------------------------------------------
	};
}