//================================================
//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG
//
//
//
//================================================
//
// Created by Huiyi on 2022/10/28.
//
//@模块名称 易炫彩APIHOOK支持库
//@版本   1.1
//@日期   2022-10-28
//@作者   Huiyi
//@模块备注 mhook的封装版本,支持x86/64,内置反汇编引擎,能根据系统自动调整钩子方式


#pragma once

#ifndef XL_XAPIHOOK_H
//@隐藏{
#define XL_XAPIHOOK_H    //防止复用

#if XC_MOUDLE
#endif
//@隐藏}
#include <windows.h>
#include "mhook-lib\mhook.h"
//@src "hook.cpp"
//@src "mhook-lib\mhook.cpp"
//@src "disasm-lib\cpu.c"
//@src "disasm-lib\disasm.c"
//@src "disasm-lib\disasm_x86.c"
//@src "disasm-lib\misc.c"

//@备注 HOOK某函数
//@参数 被hook的地址 被hook的原始地址
//@参数 预转向的地址 HOOK的新地址
//@别名 HOOK_装载HOOK(被hook的函数地址,预转向的地址)
BOOL XHOOK_SetHook(PVOID* ppSystemFunction, PVOID pHookFunction);

//@备注 卸载被HOOK的函数
//@参数 预转向的地址 与 HOOK_装载HOOK() 中的 预转向的地址 是相同地址
//@别名 HOOK_卸载HOOK(被hook的函数地址)
BOOL XHOOK_Unhook(PVOID* ppHookedFunction);





#endif //XL_XAPIHOOK_H
