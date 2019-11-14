#include "stdafx.h"
#include "Include/com/StreamTool.h"

namespace com
{

	bool				StreamTool::bInited = false;
	EEndian			StreamTool::endian = EEndian::little;


	StreamTool::StreamTool()
	{

	}

	void StreamTool::Init()
	{
		if (!bInited)
		{
			endian = CalcLocalhostEndian();

			bInited = true;
		}
	}

	EEndian StreamTool::CalcLocalhostEndian()
	{
		// MyUnion
		union MyUnion
		{
			int n;
			char ch;
		};

		MyUnion u1;
		u1.n = 67305985;

		if (u1.ch == 1)
		{
			return EEndian::little;
		}

		return EEndian::big;
	}

	EEndian StreamTool::GetLocalHostEndian()
	{
		Init();

		return endian;
	}
}