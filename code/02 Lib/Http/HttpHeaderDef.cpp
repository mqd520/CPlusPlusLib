#include "stdafx.h"
#include "Include/http/HttpHeaderDef.h"


namespace http
{
	// Common -------------------------------------------------------------------------------
	const string HttpHeaderDef::ContentType = "Content-Type";
	const string HttpHeaderDef::ContentLength = "Content-Length";
	const string HttpHeaderDef::Cookie = "Cookie";
	const string HttpHeaderDef::CacheControl = "Cache-Control";
	const string HttpHeaderDef::Connection = "Connection";
	// Common -------------------------------------------------------------------------------


	// Request ------------------------------------------------------------------------------
	const string HttpHeaderDef::UserAgent = "User-Agent";
	const string HttpHeaderDef::Host = "Host";
	const string HttpHeaderDef::Accept = "Accept";
	const string HttpHeaderDef::AcceptEncoding = "Accept-Encoding";
	const string HttpHeaderDef::AcceptLanguage = "Accept-Language";
	
	// Request ------------------------------------------------------------------------------


	// Response -----------------------------------------------------------------------------
	const string HttpHeaderDef::Server = "Server";
	const string HttpHeaderDef::Date = "Date";
	// Response -----------------------------------------------------------------------------



	HttpHeaderDef::HttpHeaderDef()
	{

	}
}