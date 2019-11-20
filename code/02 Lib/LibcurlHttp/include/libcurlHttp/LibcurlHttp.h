#pragma once

#include <string>
#include <map>
#include <vector>
using namespace std;

#include <curl/curl.h>


namespace libcurlHttp
{
	// LibcurlHttpResult
	typedef struct tagLibcurlHttpResult
	{
		bool bSuccess;
		CURLcode code;
		vector<pair<string, string>> vecHeaders;
		string response;
		int nHttpStatus;
	}LibcurlHttpResult;


	// Libcurl Http
	class LibcurlHttp
	{
	protected:
		map<string, string> mapHeaders;		// Header map
		map<string, string> mapFormItems;	// Form Item map
		string strBodyData;					// Body data
		bool bIsFormData;					// Whether form data

	protected:
		//************************************
		// Method:    SetHeadersOpt
		// Parameter: CURL * pCurl
		//************************************
		void SetHeadersOpt(CURL* pCurl);

		//************************************
		// Method:    Set Body Opt
		// Parameter: CURL * pCurl
		// Parameter: string method
		//************************************
		void SetBodyOpt(CURL* pCurl, const string& method);

		//************************************
		// Method:    IsFormData
		//************************************
		bool IsFormData();

		//************************************
		// Method:    Init
		//************************************
		CURL* Init();

		//************************************
		// Method:    Execute
		// Parameter: const string & strUrl
		// Parameter: string method
		// Parameter: LibcurlHttpResult * pResult
		// Parameter: bool bRecvResponse
		// Parameter: bool bRecvHeader
		//************************************
		void Execute(const string& strUrl, string method, LibcurlHttpResult* pResult,
			bool bRecvResponse = false, bool bRecvHeader = false);

	public:
		//************************************
		// Method:    Is Exit Header
		// Parameter: const string & header
		//************************************
		bool IsExitHeader(const string& header);

		//************************************
		// Method:    Get Header
		// Parameter: const string & header
		//************************************
		string GetHeader(const string& header);

		//************************************
		// Method:    Set Header
		// Parameter: const string & header
		// Parameter: const string & val
		//************************************
		void SetHeader(const string& header, const string& val);

		//************************************
		// Method:    Set Form Item
		// Parameter: const string & item
		// Parameter: const string & val
		//************************************
		void SetFormItem(const string& item, const string& val);

		//************************************
		// Method:    Set Form Item
		// Parameter: const string & item
		// Parameter: const wstring & val
		//************************************
		void SetFormItem(const string& item, const wstring& val);

		//************************************
		// Method:    Set Form Item
		// Parameter: const string & item
		// Parameter: const BYTE & val
		//************************************
		void SetFormItem(const string& item, const BYTE& val);

		//************************************
		// Method:    Set Form Item
		// Parameter: const string & item
		// Parameter: const INT16 & val
		//************************************
		void SetFormItem(const string& item, const INT16& val);

		//************************************
		// Method:    Set Form Item
		// Parameter: const string & item
		// Parameter: const UINT16 & val
		//************************************
		void SetFormItem(const string& item, const UINT16& val);

		//************************************
		// Method:    Set Form Item
		// Parameter: const string & item
		// Parameter: const INT32 & val
		//************************************
		void SetFormItem(const string& item, const INT32& val);

		//************************************
		// Method:    Set Form Item
		// Parameter: const string & item
		// Parameter: const UINT32 & val
		//************************************
		void SetFormItem(const string& item, const UINT32& val);

		//************************************
		// Method:    Set Form Item
		// Parameter: const string & item
		// Parameter: const INT64 & val
		//************************************
		void SetFormItem(const string& item, const INT64& val);

		//************************************
		// Method:    Set Form Item
		// Parameter: const string & item
		// Parameter: const UINT64 & val
		//************************************
		void SetFormItem(const string& item, const UINT64& val);

		//************************************
		// Method:    Set Form Item
		// Parameter: const string & item
		// Parameter: const float & val
		// Parameter: const int & decimal
		//************************************
		void SetFormItem(const string& item, const float& val, const int& decimal = 2);

		//************************************
		// Method:    Set Form Item
		// Parameter: const string & item
		// Parameter: const double & val
		// Parameter: const int & decimal
		//************************************
		void SetFormItem(const string& item, const double& val, const int& decimal = 2);

		//************************************
		// Method:    Set Body Data
		// Parameter: string & data
		//************************************
		void SetBodyData(string& data);

	public:
		//************************************
		// Method:    Post
		// Parameter: const string & strUrl
		// Parameter: const string & contentType
		//************************************
		LibcurlHttpResult Post(const string& strUrl, bool bRecvResponse = false, bool bRecvHeader = false,
			const string& contentType = "application/x-www-form-urlencoded");

		//************************************
		// Method:    Get
		// Parameter: const string & strUrl
		// Parameter: bool bRecvResponse
		// Parameter: bool bRecvHeader
		//************************************
		LibcurlHttpResult Get(const string& strUrl, bool bRecvResponse = false, bool bRecvHeader = false, 
			const string& contentType = "application/x-www-form-urlencoded");
	};
}