//
// Created by Huiyi on 2022/9/26.
//
#include "times.h"

//时间_系统时间转炫彩时间
void X_Time_SystemToCSysDateTime(SYSTEMTIME& st, CDateTimeTM& rt) {
    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);
    LONGLONG nLL;
    ULARGE_INTEGER ui;
    ui.LowPart = ft.dwLowDateTime;
    ui.HighPart = ft.dwHighDateTime;
    nLL = ((LONGLONG)(ft.dwHighDateTime) << 32) + ft.dwLowDateTime;
    time_t pt = (LONGLONG)((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
    localtime_s(&rt.m_tm,&pt);
}
//时间_炫彩时间转系统时间
void X_Time_CSysDateTimeToSystem(CDateTimeTM& rt,SYSTEMTIME& st) {
    //time_t转SYSTEMTIME
    time_t tt= mktime(&rt.m_tm);
    tm temptm;
    localtime_s(&temptm ,&tt);
    WORD l=NULL;
    SYSTEMTIME rst;
    rst.wYear= (WORD)(1900) + temptm.tm_year;
    rst.wMonth= (WORD)(1) + temptm.tm_mon;
    rst.wDayOfWeek= temptm.tm_wday;
    rst.wDay = temptm.tm_mday;
    rst.wHour = temptm.tm_hour;
    rst.wMinute = temptm.tm_min;
    rst.wSecond = temptm.tm_sec;
    rst.wMilliseconds= (WORD)(0);
    st = rst;
}
//时间_格式化W
CXText X_Time_Format(CDateTimeTM& rt, CXText formatStr) {
    char tmstr[100]={'\0'};
    rt.m_tm.tm_mday = rt.m_tm.tm_mday<1?1: rt.m_tm.tm_mday;
    strftime(tmstr, sizeof(tmstr), "%Y-%m-%d:%H:%M:%S", &rt.m_tm);
    return A2W(tmstr);
}
//时间_格式化A
CXTextA X_Time_FormatA(CDateTimeTM& rt, CXTextA formatStr) {
    char tmstr[100] = { '\0' };
    rt.m_tm.tm_mday = rt.m_tm.tm_mday < 1 ? 1 : rt.m_tm.tm_mday;
    strftime(tmstr, sizeof(tmstr), "%Y-%m-%d:%H:%M:%S", &rt.m_tm);
    return tmstr;
}

void X_Time_TimetToFileTime(time_t t, LPFILETIME pft) {
    ULARGE_INTEGER time_value;
    time_value.QuadPart = (t * 10000000LL) + 116444736000000000LL;
    pft->dwLowDateTime = time_value.LowPart;
    pft->dwHighDateTime = time_value.HighPart;
}