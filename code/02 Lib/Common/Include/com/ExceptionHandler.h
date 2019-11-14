#pragma once
#include <string>
using namespace std;

namespace com
{
	//************************************
	// Method:    异常回调函数指针
	// Parameter: pParam1:	附加参数1
	// Parameter: pParam1:	附加参数2
	//************************************
	typedef void(*LPExceptionCallback)(void* pParam1, void* pParam2);

	// 异常处理类
	class ExceptionHandler
	{
	private:
		ExceptionHandler();

	public:
		//************************************
		// Method:    初始化
		//************************************
		static void Init();

		//************************************
		// Method:    设置文件名
		// Parameter: strFilename:	文件名
		//************************************
		static void SetFileName(string strFilename);

		//************************************
		// Method:    设置异常处理回调函数
		// Parameter: lpfnCallback:	回调函数指针
		// Parameter: pParam1:	附加参数1
		// Parameter: pParam1:	附加参数2
		//************************************
		static void SetCallback(LPExceptionCallback lpfnCallback, void* pParam1 = NULL, void* pParam2 = NULL);
	};
}