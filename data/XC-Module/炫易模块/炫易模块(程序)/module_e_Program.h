// Created by Huiyi on 2021/4/20.
//
//@模块名称 炫易模块(程序)
//@版本   1.3
//@日期   2022-10-05
//@作者   Huiyi
//@模块备注 封装程序相关函数
//项目gitee地址 https://gitee.com/LoveA/XL_XExpand
//大部分代码已经历过粗略测试
//如发现BUG可提交issues
//https://gitee.com/LoveA/XL_XExpand/issues
//反馈QQ群:594165459

//@依赖   module_base.h

#pragma once

#ifndef XL_XEXPAND_PROGRAM_H
//@隐藏{
#define XL_XEXPAND_PROGRAM_H    //防止复用

#if XC_MODULE
#include "module_base.h"
#endif
//@隐藏}

//@src  "program.cpp"


//@分组{  程序

//@备注   不占用cpu，窗口不卡死，不影响其它代码执行
//@参数   延时时间 1000毫秒 = 1秒  留空为无限等待
//@参数   延时单位 默认为毫秒  0=毫秒  1=秒  2=分钟  3=小时
//@别名   程序_延时(延时时间,延时单位)
void X_Program_Sleep(long time = 0, int unit = 0);

//@备注   仅对编译环境有效
//@别名   程序_是否64位()
BOOL X_Program_If64();


//@别名   程序_COM生成GUID (GUID)
CXText X_Program_CreateGUID(__out GUID &guid_);



CXText 程序_取cmd路径();


//@备注 内存中运行EXE, 翻译自精易模块
//@参数 欲执行的程序，不支持某些加了壳的程序，请自行测试
//@参数 为程序提供的命令行参数，不需要请留空。
//@参数 外壳程序的路径(如果用系统程序做外壳，如cmd.exe、svchost.exe，可以实现穿防火墙，呵呵)，不支持某些程序，请自行测试；不在当前目录下要提供绝对路径；留空默认为cmd.exe，如果无法运行，请换用不同的程序尝试。
//@参数 默认为假，即不等待
//@参数 1#隐藏窗口； 2#普通激活； 3#最小化激活； 4#最大化激活； 5#普通不激活； 6#最小化不激活。如果省略本参数，默认为“普通激活”方式。
//@参数 用来接收在内存中执行的exe的运行信息(进程、主线程的句柄和ID)。不需要可留空。当不使用时需要关闭进程和线程句柄
//@返回 成功返回真, 失败返回假
BOOL 程序_内存中运行EXE(const CXBytes& 欲执行的程序, const wchar_t* 命令行 = 0, const wchar_t* 外壳程序路径 = 0,
	BOOL 等待程序运行完毕 = FALSE, int 窗口显示方式 = 0, __out PROCESS_INFORMATION* 进程信息 = 0);


//@备注 内存中运行EXE, 来源于网络
//@参数 欲执行的程序，不支持某些加了壳的程序，请自行测试
//@参数 为程序提供的命令行参数，不需要请留空。
//@参数 外壳程序的路径(如果用系统程序做外壳，如cmd.exe、svchost.exe，可以实现穿防火墙，呵呵)，不支持某些程序，请自行测试；不在当前目录下要提供绝对路径；留空默认为cmd.exe，如果无法运行，请换用不同的程序尝试。
//@参数 默认为假，即不等待
//@参数 ShowWindow() API 对应参数, 例如: SW_SHOW, SW_HIDE
//@参数 用来接收在内存中执行的exe的运行信息(进程、主线程的句柄和ID)。不需要可留空。当不使用时需要关闭进程和线程句柄
//@别名 程序_内存中运行EXE2(欲执行的程序, 命令行, 外壳程序路径, 等待程序运行完毕, 窗口显示方式, 进程信息)
//@返回 成功返回真, 失败返回假
BOOL 程序_内存中运行EXE2(const CXBytes& data_, const wchar_t* pCmdLine, const wchar_t* pShellProgram = 0,
	BOOL bWait = FALSE, int showWindow = 0, __out PROCESS_INFORMATION* pProcessInfo = 0);


//@备注 内存中运行EXE, 以线程方式运行, 当目标线程退出时, 当前进程退出
//@返回 成功返回真, 失败返回假
void 程序_内存中运行EXE线程方式(const CXBytes& data_);


//@备注 把指定的程序添加到不允许运行的应用程序列表中。
//     注册表路径:Software\Microsoft\Windows\CurrentVersion\Policies\Explorer
//@参数 程序名称, 例如: abc.exe
//@返回 成功返回真, 失败返回假
BOOL 程序_禁止运行(const wchar_t* pFileName);


//@备注 把指定的程序从不允许运行的应用程序列表中删除。
//     注册表路径:Software\Microsoft\Windows\CurrentVersion\Policies\Explorer
//@参数 程序名称, 例如: abc.exe
//@返回 成功返回真, 失败返回假
BOOL 程序_允许运行(const wchar_t* pFileName);


//@备注  禁止当前程序多开运行
//@参数  指定互斥对象的名称, 该名称限制为 MAX_PATH 个字符, 反斜杠字符除外
//@返回  如果程序重复运行返回真, 否则返回假
BOOL 程序_禁止重复运行(const wchar_t *pName);


//@参数 程序名称, 例如: abc.exe
//@返回 成功返回目录，以“\”结尾。失败返回空文本。
CXText 程序_取安装目录(const wchar_t* pFileName);



//@分组}  程序

#endif //XL_XEXPAND_PROGRAM_H
