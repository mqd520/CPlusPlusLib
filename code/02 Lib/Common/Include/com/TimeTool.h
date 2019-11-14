#pragma once

#include <time.h>
#include <minwinbase.h>

#include <string>
using namespace std;


namespace com
{
	// Time zone
	enum class ETimeZone
	{
		GMT = 1,		// GMT
		CST = 2			// CST(Bei jing)
	};


	// Time Tool
	class TimeTool final
	{
	private:
		TimeTool();

	public:
		//************************************
		// Method:    Get TimeStamp(ms)
		//************************************
		static time_t GetCurTimeStamp();

		//************************************
		// Method:    time_t to tm
		// Parameter: const time_t & t
		// Parameter: bool bMillSec
		// Parameter: ETimeZone tz
		//************************************
		static struct tm TIME_T_2_TM(const time_t& t, bool bMillSec = false, ETimeZone tz = ETimeZone::GMT);

		//************************************
		// Method:    time_t to SYSTEMTIME
		// Parameter: const time_t & t
		// Parameter: bool bMillSec
		// Parameter: ETimeZone tz
		//************************************
		static SYSTEMTIME TIME_T_2_SYSTEMTIME(const time_t& t, bool bMillSec = false, ETimeZone tz = ETimeZone::GMT);

		//************************************
		// Method:    SYSTEMTIME to time_t
		// Parameter: const SYSTEMTIME & t
		// Parameter: bool bMillSec
		// Parameter: ETimeZone tz
		//************************************
		static time_t SYSTEMTIME_2_TIME_T(const SYSTEMTIME& t, ETimeZone tz = ETimeZone::GMT, bool bMillSec = false);

		//************************************
		// Method:    SYSTEMTIME to tm
		// Parameter: const SYSTEMTIME & t
		// Parameter: ETimeZone tz
		//************************************
		static struct tm SYSTEMTIME_2_TM(const SYSTEMTIME& t);

		//************************************
		// Method:    tm to time_t
		// Parameter: const struct tm & t
		// Parameter: bool bMillSec
		//************************************
		static time_t TM_2_TIME_T(const struct tm& t, ETimeZone tz = ETimeZone::GMT, bool bMillSec = false);

		//************************************
		// Method:    tm to SYSTEMTIME
		// Parameter: const struct tm & t
		//************************************
		static SYSTEMTIME TM_2_SYSTEMTIME(const struct tm& t);

		//************************************
		// Method:    GMT to CST
		// Parameter: const tm & t1
		//************************************
		static struct tm GMT_2_CST(const struct tm& t);

		//************************************
		// Method:    GMT to CST
		// Parameter: const SYSTEMTIME & t
		//************************************
		static SYSTEMTIME GMT_2_CST(const SYSTEMTIME& t);

		//************************************
		// Method:    GMT to CST
		// Parameter: const tm & t
		//************************************
		static SYSTEMTIME GMT_2_CST_1(const struct tm& t);

		//************************************
		// Method:    GMT to CST
		// Parameter: const SYSTEMTIME & t
		//************************************
		static struct tm GMT_2_CST_1(const SYSTEMTIME& t);

		//************************************
		// Method:    CST to GMT
		// Parameter: const struct tm & t
		//************************************
		static struct tm CST_2_GMT(const struct tm& t);

		//************************************
		// Method:    CST to GMT
		// Parameter: const SYSTEMTIME t
		//************************************
		static SYSTEMTIME CST_2_GMT(const SYSTEMTIME t);

		//************************************
		// Method:    CST to GMT
		// Parameter: const struct tm & t
		//************************************
		static SYSTEMTIME CST_2_GMT_1(const struct tm& t);

		//************************************
		// Method:    CST to GMT
		// Parameter: const SYSTEMTIME t
		//************************************
		static struct tm CST_2_GMT_1(const SYSTEMTIME t);

		//************************************
		// Method:    Get Current Time tm
		// Parameter: ETimeZone tz
		//************************************
		static struct tm GetCurTM(ETimeZone tz = ETimeZone::CST);

		//************************************
		// Method:    Format
		// Parameter: const SYSTEMTIME & t
		// Parameter: const string & format
		//************************************
		static string Format(const SYSTEMTIME& t, const string& format = "yyyy-mm-dd HH:MM:ss");

		//************************************
		// Method:    Format
		// Parameter: const tm & t
		// Parameter: const string & format
		//************************************
		static string Format(const tm& t, const string& format = "yyyy-mm-dd HH:MM:ss");

		//************************************
		// Method:    Format
		// Parameter: const time_t & t
		// Parameter: bool bMillSec
		// Parameter: const string & format
		// Parameter: ETimeZone tz
		//************************************
		static string Format(const time_t& t, bool bMillSec = false, const string& format = "yyyy-mm-dd HH:MM:ss", ETimeZone tz = ETimeZone::CST);

		//************************************
		// Method:    Format
		// Parameter: const string & format
		// Parameter: ETimeZone tz
		//************************************
		static string Format(const string& format = "yyyy-mm-dd HH:MM:ss", ETimeZone tz = ETimeZone::CST);
	};
}