#include "stdafx.h"
#include "Include/com/TimeTool.h"

#include <sys/timeb.h>

#include "Include/com/StringTool.h"
#include "Include/com/NumberTool.h"


int GetMonthDayCount(int year, int month);
int GetDayCount(int year, int month, int day);


namespace com
{
	TimeTool::TimeTool()
	{

	}

	time_t TimeTool::GetCurTimeStamp()
	{
		struct timeb tb;

		ftime(&tb);

		return (time_t)((INT64)tb.millitm + tb.time * 1000);
	}

	struct tm TimeTool::TIME_T_2_TM(const time_t& t, bool bMillSec /*= false*/, ETimeZone tz /*= ETimeZone::GMT*/)
	{
		struct tm t1;
		time_t t2 = t;

		if (bMillSec)
		{
			t2 = t2 / 1000;
		}

		if (tz == ETimeZone::CST)
		{
			t2 += 8 * 60 * 60;
		}

		gmtime_s(&t1, &t2);

		return t1;
	}

	SYSTEMTIME TimeTool::TIME_T_2_SYSTEMTIME(const time_t& t, bool bMillSec /*= false*/, ETimeZone tz /*= ETimeZone::GMT*/)
	{
		struct tm t1 = TIME_T_2_TM(t, bMillSec, tz);

		WORD nMillSec = bMillSec ? (WORD)(t - ((t / 1000) * 1000)) : 0;

		SYSTEMTIME t2 = {
			1900 + t1.tm_year,
			1 + t1.tm_mon,
			t1.tm_wday,
			t1.tm_mday,
			t1.tm_hour,
			t1.tm_min,
			t1.tm_sec,
			nMillSec
		};

		return t2;
	}

	time_t TimeTool::SYSTEMTIME_2_TIME_T(const SYSTEMTIME& t, ETimeZone tz /*= ETimeZone::GMT*/, bool bMillSec /*= false*/)
	{
		struct tm t1 = SYSTEMTIME_2_TM(t);

		time_t t2 = TM_2_TIME_T(t1, tz, bMillSec);

		if (bMillSec)
		{
			t2 += t.wMilliseconds;
		}

		return t2;
	}

	struct tm TimeTool::SYSTEMTIME_2_TM(const SYSTEMTIME& t)
	{
		struct tm t1 = {
			t.wSecond,
			t.wMinute,
			t.wHour,
			t.wDay,
			t.wMonth - 1,
			t.wYear - 1900,
			t.wDayOfWeek,
			GetDayCount(t.wYear, t.wMonth, t.wDay) - 1,
			0
		};

		return t1;
	}

	time_t TimeTool::TM_2_TIME_T(const struct tm& t, ETimeZone tz /*= ETimeZone::GMT*/, bool bMillSec /*= false*/)
	{
		struct tm t1 = t;

		time_t t2 = mktime(&t1);
		if (tz == ETimeZone::GMT)
		{
			t2 += 8 * 60 * 60;
		}

		if (bMillSec)
		{
			t2 *= 1000;
		}

		return t2;
	}

	SYSTEMTIME TimeTool::TM_2_SYSTEMTIME(const struct tm& t)
	{
		SYSTEMTIME t1 = {
			t.tm_year + 1900,
			t.tm_mon + 1,
			t.tm_wday,
			t.tm_mday,
			t.tm_hour,
			t.tm_min,
			t.tm_sec,
			0
		};

		return t1;
	}

	struct tm TimeTool::GMT_2_CST(const struct tm& t)
	{
		time_t t1 = TM_2_TIME_T(t, ETimeZone::GMT);

		return TIME_T_2_TM(t1, false, ETimeZone::CST);
	}

	SYSTEMTIME TimeTool::GMT_2_CST(const SYSTEMTIME& t)
	{
		time_t t1 = SYSTEMTIME_2_TIME_T(t, ETimeZone::GMT, true);

		return TIME_T_2_SYSTEMTIME(t1, true, ETimeZone::CST);
	}

	SYSTEMTIME TimeTool::GMT_2_CST_1(const struct tm& t)
	{
		time_t t1 = TM_2_TIME_T(t, ETimeZone::GMT);

		return TIME_T_2_SYSTEMTIME(t1, false, ETimeZone::CST);
	}

	struct tm TimeTool::GMT_2_CST_1(const SYSTEMTIME& t)
	{
		time_t t1 = SYSTEMTIME_2_TIME_T(t, ETimeZone::GMT);

		return TIME_T_2_TM(t1, false, ETimeZone::CST);
	}

	struct tm TimeTool::CST_2_GMT(const struct tm& t)
	{
		time_t t1 = TimeTool::TM_2_TIME_T(t, ETimeZone::CST);

		return TIME_T_2_TM(t1, false, ETimeZone::GMT);
	}

	SYSTEMTIME TimeTool::CST_2_GMT(const SYSTEMTIME t)
	{
		time_t t1 = TimeTool::SYSTEMTIME_2_TIME_T(t, ETimeZone::CST, true);

		return TIME_T_2_SYSTEMTIME(t1, true, ETimeZone::GMT);
	}

	SYSTEMTIME TimeTool::CST_2_GMT_1(const struct tm& t)
	{
		time_t t1 = TM_2_TIME_T(t, ETimeZone::CST);

		return TIME_T_2_SYSTEMTIME(t1, false, ETimeZone::GMT);
	}

	struct tm TimeTool::CST_2_GMT_1(const SYSTEMTIME t)
	{
		time_t t1 = SYSTEMTIME_2_TIME_T(t, ETimeZone::CST);

		return TIME_T_2_TM(t1, false, ETimeZone::GMT);
	}

	struct tm TimeTool::GetCurTM(ETimeZone tz /*= ETimeZone::CST*/)
	{
		SYSTEMTIME t;
		if (tz == ETimeZone::CST)
		{
			GetLocalTime(&t);
		}
		else if (tz == ETimeZone::GMT)
		{
			GetSystemTime(&t);
		}

		return SYSTEMTIME_2_TM(t);
	}

	string TimeTool::Format(const SYSTEMTIME& t, const string& format /*= "yyyy-mm-dd HH:MM:ss"*/)
	{
		string result = format;

		if (!result.empty())
		{
			if (format.find("yyyy") >= 0)
			{
				result = StringTool::Replace(result, "yyyy", StringTool::Format("%d", t.wYear).c_str());
			}
			else if (format.find("yy") >= 0)
			{
				result = StringTool::Replace(result, "yy", StringTool::Format("%d", t.wYear).substr(0, 2).c_str());
			}

			if (format.find("mm") >= 0)
			{
				result = StringTool::Replace(result, "mm", StringTool::Format("%02d", t.wMonth).c_str());
			}
			else if (format.find("m") >= 0)
			{
				result = StringTool::Replace(result, "m", StringTool::Format("%d", t.wMonth).c_str());
			}

			if (format.find("dd") >= 0)
			{
				result = StringTool::Replace(result, "dd", StringTool::Format("%02d", t.wDay).c_str());
			}
			else if (format.find("d") >= 0)
			{
				result = StringTool::Replace(result, "d", StringTool::Format("%d", t.wDay));
			}

			if (format.find("HH") >= 0)
			{
				result = StringTool::Replace(result, "HH", StringTool::Format("%02d", t.wHour));
			}
			else if (format.find("H") >= 0)
			{
				result = StringTool::Replace(result, "H", StringTool::Format("%d", t.wHour));
			}

			if (format.find("MM") >= 0)
			{
				result = StringTool::Replace(result, "MM", StringTool::Format("%02d", t.wMinute));
			}
			else if (format.find("M") >= 0)
			{
				result = StringTool::Replace(result, "M", StringTool::Format("%d", t.wMinute));
			}

			if (format.find("ss") >= 0)
			{
				result = StringTool::Replace(result, "ss", StringTool::Format("%02d", t.wSecond));
			}
			else if (format.find("s") >= 0)
			{
				result = StringTool::Replace(result, "s", StringTool::Format("%d", t.wSecond));
			}

			if (format.find("ff") >= 0)
			{
				result = StringTool::Replace(result, "ff", StringTool::Format("%03d", t.wMilliseconds));
			}
			else if (format.find("f") >= 0)
			{
				result = StringTool::Replace(result, "f", StringTool::Format("%d", t.wMilliseconds));
			}
		}

		return result;
	}

	string TimeTool::Format(const tm& t, const string& format /*= "yyyy-mm-dd HH:MM:ss"*/)
	{
		return Format(TM_2_SYSTEMTIME(t), format);
	}

	string TimeTool::Format(const time_t& t, bool bMillSec /*= false*/, const string& format /*= "yyyy-mm-dd HH:MM:ss"*/, ETimeZone tz /*= ETimeZone::CST*/)
	{
		return Format(TIME_T_2_SYSTEMTIME(t, bMillSec, tz), format);
	}

	string TimeTool::Format(const string& format /*= "yyyy-mm-dd HH:MM:ss"*/, ETimeZone tz /*= ETimeZone::CST*/)
	{
		time_t t1 = GetCurTimeStamp();

		return Format(t1, true, format, tz);
	}
}

int GetMonthDayCount(int year, int month)
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		return 31;
	}
	else
	{
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			return 30;
		}
		else
		{
			if (year % 4 == 0)
			{
				return 29;
			}
			else
			{
				return 28;
			}
		}
	}
}

int GetDayCount(int year, int month, int day)
{
	int sum = 0;

	for (int i = 1; i < month; i++)
	{
		sum += GetMonthDayCount(year, i);
	}

	sum += day;

	return sum;
}