#include "stdafx.h"
#include "Task.h"

#include "libcurlHttp/AsyncHttp.h"
using namespace libcurlHttp;

#include "com/CommonTool.h"
#include "com/TimeTool.h"
#include "com/StringTool.h"
#include "com/Log.h"
#include "com/Event.h"
using namespace com;

#include "Config.h"


void OnHttpResult(LibcurlHttpResult& http);

Task _task;
int	_nCount = 0;
int _nCompleteCount = 0;

Event		_evt("TaskEvent1");
time_t		_tStart;
time_t		_tEnd;

void Task::Process()
{
	_nCompleteCount = 0;
	_evt.Reset();

	int size = (int)_cfg.vecHttps.size();
	if (size > 0)
	{
		int rand = CommonTool::Rand() % size;
		ConfigHttpsInfo item = _cfg.vecHttps[rand];

		string log = StringTool::Format("Http url: %s, count: %d, method: %s", item.url.c_str(), item.count, item.method.c_str());
		Log::Write_2_Console(ELogType::Info, log, false, __FUNCTION__);
		Log::Write_2_Console(ELogType::Info, "Start ...", false, __FUNCTION__);

		_nCount = item.count;
		_tStart = TimeTool::GetCurTimeStamp();

		for (int i = 0; i < item.count; i++)
		{
			AsyncHttpReq req;
			req.bRecvHeader = false;
			req.bRecvResponse = false;
			req.contentType = item.contentType;
			req.url = item.url;
			req.method = item.method;
			req.callback = std::bind(OnHttpResult, _1);

			_asyncHttp.PushHttpReq(req);
		}

		_evt.WaitForSingal();

		Log::Write_2_Console(ELogType::Info, "End ... \n", false, __FUNCTION__);

		//string sql = "insert into Logs(Url, Method, Data, ContentType, Count, Start, End) values(?, ?, ?, ?, ?, ?, ?)";
		//AdoParam param;
		//param.CreatePara("@Url", adVarChar, adParamInput, 255, _variant_t(item.url.c_str()));
		//param.CreatePara("@Method", adVarChar, adParamInput, 10, _variant_t(item.method.c_str()));
		//param.CreatePara("@Data", adVarChar, adParamInput, 255, _variant_t(item.data.c_str()));
		//param.CreatePara("@ContentType", adVarChar, adParamInput, 128, _variant_t(item.contentType.c_str()));
		//param.CreatePara("@Count", adInteger, adParamInput, 11, _variant_t(item.count));
		//param.CreatePara("@Start", adInteger, adParamInput, 11, _variant_t((__int64)_tStart));
		//param.CreatePara("@End", adInteger, adParamInput, 11, _variant_t((__int64)_tEnd));
		//AdoConnection::default.ExecuteNonQuery(sql, param);

		LibcurlHttp http;
		http.SetFormItem("url", item.url);
		http.SetFormItem("method", item.method);
		http.SetFormItem("data", item.data);
		http.SetFormItem("contentType", item.contentType);
		http.SetFormItem("count", item.count);
		http.SetFormItem("time", _tEnd - _tStart);
		http.SetFormItem("recordTime", TimeTool::Format());
		http.Post(_cfg.strDbServiceAddr);
	}
}

void OnHttpResult(LibcurlHttpResult& http)
{
	_nCompleteCount++;

	if (_nCompleteCount == _nCount)
	{
		_tEnd = TimeTool::GetCurTimeStamp();
		_evt.Active();
	}
}