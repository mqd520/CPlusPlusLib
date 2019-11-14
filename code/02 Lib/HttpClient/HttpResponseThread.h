#pragma once

#include "Thread.h"

namespace hc
{
	// http response process thread
	class HttpResponseThread : public Thread
	{
	public:
		HttpResponseThread();
		~HttpResponseThread();

	public:
		void OnExecute() override;
	};
}