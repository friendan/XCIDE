//================================================
//
// Created by Huiyi on 2021/4/20.
//
//@模块名称 易炫彩时间库
//@依赖   module_base.h
//@版本   1.3
//@日期   2022-10-05
//@作者   Huiyi
//@模块备注 封装时间相关处理函数
//项目gitee地址 https://gitee.com/LoveA/XL_XExpand
//大部分代码已经历过粗略测试
//如发现BUG可提交issues
//https://gitee.com/LoveA/XL_XExpand/issues
//反馈QQ群:594165459

#pragma once

#ifndef XL_XEXPAND_TIMES_H
//@隐藏{
#define XL_XEXPAND_TIMES_H    //防止复用

#if XC_MOUDLE
#include "module_base.h"
#endif
//@隐藏}

//@src  "times.cpp"

// TODO: 时间分组
//@分组{  时间

/*@声明
//@别名 系统时间型
struct SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
};
*/

//@别名   时间_系统时间转炫彩时间(要转换的时间,接收的时间变量)
void X_Time_SystemToCSysDateTime(SYSTEMTIME& st, CDateTimeTM& rt);

//@别名   时间_炫彩时间转系统时间(要转换的时间,接收的时间变量)
void X_Time_CSysDateTimeToSystem(CDateTimeTM& rt, SYSTEMTIME& st);

//@参数   需要格式化的时间 用于格式化的时间
//@参数   时间格式 可空 %d 日期,%f 小数形式的秒,%H 小时,%j 算出某一天是该年的第几天,%m 月份,%M 分钟,%s 从1970年1月1日到现在的秒数%S 秒,%w 星期,%W 算出某一天属于该年的第几周,%Y 年,%% 百分号
//@别名   时间_格式化(需要格式化的时间,时间格式)
CXText X_Time_Format(CDateTimeTM& rt,CXText formatStr=L"%Y.%m.%d %H:%M:%S");
//@参数   需要格式化的时间 用于格式化的时间
//@参数   时间格式 可空 %d 日期,%f 小数形式的秒,%H 小时,%j 算出某一天是该年的第几天,%m 月份,%M 分钟,%s 从1970年1月1日到现在的秒数%S 秒,%w 星期,%W 算出某一天属于该年的第几周,%Y 年,%% 百分号
//@别名   时间_格式化A(需要格式化的时间,时间格式)
CXTextA X_Time_FormatA(CDateTimeTM& rt, CXTextA formatStr = "%Y.%m.%d %H:%M:%S");
//@隐藏{

void X_Time_TimetToFileTime(time_t t, LPFILETIME pft);

//@隐藏}

//@分组}  时间

#endif //XL_XEXPAND_TIMES_H
