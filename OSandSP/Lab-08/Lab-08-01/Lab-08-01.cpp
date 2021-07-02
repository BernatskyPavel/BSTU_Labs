#include<stdio.h>
#include<conio.h>
#include<time.h>
#include <tchar.h>

int _tmain()
{
	time_t ti;
	ti = time(NULL);
	struct tm tm;
	localtime_s(&tm, &ti);
	_tprintf_s(_T("Current Date: %02d.%02d.%02d %02d:%02d:%02d"), tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}