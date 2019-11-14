#pragma once


#define Http_UserAgent			("User-Agent", "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36")	// User-Agent
#define Http_MaxFstLineLen		(1024 * 1)		// max first line byte length
#define Http_MaxHeaderLen		(1024 * 4)		// max header byte length
#define Http_MaxBodyLen			(1024 * 8)		// max body byte length


namespace http
{
	// Http type
	enum class EHttpType
	{
		Request = 1,

		Response = 2
	};
}