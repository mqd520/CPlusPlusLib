#pragma once

#include "Thread.h"

namespace hc
{
	// http request thread
	class HttpRequestThread : public Thread
	{
	public:
		HttpRequestThread();
		~HttpRequestThread();

	public:
		void OnExecute() override;
	};
}