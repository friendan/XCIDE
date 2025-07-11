#pragma once
// Created by Huiyi on 2021/4/20.
//
//@模块名称 炫易模块(窗口)
//@版本   1.4.1
//@日期   2024-12-13
//@作者   Huiyi
//@模块备注 
// 封装窗口相关处理函数
// 更新 By hxznhf on 2024/12/13.
// 增加 窗口_查找  窗口_查找子 命令
// 修复 窗口_取句柄 找不到的BUG
// 优化 去掉之前依赖的两个炫易模块
//
// 下面是原作者Huiyi留下的注释
// 大部分代码已经历过粗略测试,如发现BUG可提交issues
// https://gitee.com/LoveA/XL_XExpand/issues   https://gitee.com/LoveA/XL_XExpand/tree/master/易炫彩窗口库
// 反馈QQ群:594165459

//@依赖  module_base.h, module_e_ProcessThread.h, module_e_System.h

#ifndef XL_XEXPAND_WINDOW_H
//@隐藏{
#define XL_XEXPAND_WINDOW_H    //防止复用


#include "module_base.h"
// #include "module_e_System.h"
// #include "module_e_ProcessThread.h"



#include <wtsapi32.h>
#include <psapi.h>
#include <Shlobj.h>

#pragma comment (lib,"Wtsapi32.lib")
#pragma comment (lib,"Psapi.lib")

//@隐藏}

//@src  "windows.cpp"

// TODO: 窗口句柄
//@分组{  窗口操作


//@别名 窗口_查找(类名,标题)
//@返回   窗口句柄
//@参数   窗口的类名
//@参数   窗口的标题
//@备注   检索顶级窗口的句柄，该窗口的类名称和窗口名称与指定的字符串匹配。 此函数不搜索子窗口。 此函数不执行区分大小写的搜索。

HWND X_Wnd_Find(CXText className = L"", CXText title= L"");

//@别名 窗口_查找子(类名,标题,Z轴子窗口句柄,父窗口句柄)
//@返回   窗口句柄
//@参数   窗口的类名
//@参数   窗口的标题
//@参数   从指定Z轴子窗口下面开始查找，如果为NULL则查找所有子窗口
//@参数   指定父窗口的句柄，如果为NULL则查找所有顶层窗口（桌面）
//@备注   查找指定父窗口的子窗口，该窗口的类名称和窗口名称与指定的字符串匹配。 此函数不搜索子窗口。 此函数不执行区分大小写的搜索。

HWND X_Wnd_FindChild( CXText sClassName= L"", CXText sTitle = L"", HWND hWndChildAfter = NULL,HWND phWnd = NULL);


//@别名   窗口_按类名枚举(类名,返回列表)
int X_Wnd_EnumByClass(CXText className, CXVector<HWND>& rList);
//@别名   窗口_按类名枚举A(类名,返回列表)
int X_Wnd_EnumByClassA(CXTextA className, CXVector<HWND>& rList);

//@备注   可以激活一些被禁止的按钮
//@返回   成功返回真；失败返回假
//@参数   控件句柄 指定的按钮等控件句柄
//@参数   类型 真=解除禁止,假=禁止
//@别名   窗口_按钮解除禁止(控件句柄,类型)
BOOL X_Wnd_ButtonProhibited(HWND hObj, BOOL bEnabled);

//@备注   InvalidateRect
//@别名   窗口_重画(窗口句柄,擦除背景)
BOOL X_Wnd_Repaint(HWND hWnd, BOOL EraseBg);

//@备注   顶级窗口,会在任务条里显示一个按钮.通过本功能可以将其隐藏
//@别名   窗口_隐藏任务按钮(窗口句柄)
void X_Wnd_HideTaskButton(HWND hWnd);

//@别名   窗口_是否响应(窗口句柄)
BOOL X_Wnd_IfNormal(HWND hWnd);

//@别名   窗口_取光标坐标()
BOOL X_Wnd_GetCaretPos(POINT& Pos);

//@别名   窗口_取桌面句柄A()
HWND X_Wnd_GetDesktopHWndA();

//@别名   窗口_取桌面句柄W()
HWND X_Wnd_GetDesktopHWndW();

//@别名   窗口_嵌入桌面(窗口句柄)
HWND X_Wnd_EmbedOnDesktop(HWND hWnd);

//@备注   指定一个窗口的新父(返回  前一个父窗口的句柄)
//@别名   窗口_置父(子窗口句柄,父窗口句柄)
HWND X_Wnd_SetParent(HWND hWndChild, HWND hWndParent);

//@参数   欲设置的窗口句柄
//@参数   窗口新的左边位置,留空或者为NULL/0则不变
//@参数   窗口新的顶边位置,留空或者为NULL/0则不变
//@参数   窗口的新宽度,留空或者为NULL/0则不变
//@参数   窗口的新高度,留空或者为NULL/0则不变
//@别名   窗口_置位置和大小(窗口句柄,左边位置,顶边位置,新宽度,新高度)
BOOL X_Wnd_SetPosAndSize(HWND hWnd, int Left = 0, int Top = 0, int NewWidth = 0, int NewHigh = 0);

//@别名   窗口_撤销窗口热键(窗口句柄,键代码)
BOOL X_Wnd_RevokeHotKey(HWND hWnd, int keyCode);

//@别名   窗口_窗口信息
struct X_FORM_WINININFO {
    //@别名   窗口句柄
    HWND hWnd;
    //@别名   线程ID
    DWORD ThreadID;
    //@别名   进程ID
    DWORD ProcessID;
    //@别名   窗口标题
    CXText wTitle;
    //@别名   窗口类名
    CXText wClass;
};

//@别名   窗口_窗口信息A
struct X_FORM_WINININFOA {
    //@别名   窗口句柄
    HWND hWnd;
    //@别名   线程ID
    DWORD ThreadID;
    //@别名   进程ID
    DWORD ProcessID;
    //@别名   窗口标题
    CXTextA wTitle;
    //@别名   窗口类名
    CXTextA wClass;
};

//@备注   枚举所有窗口
//@返回   窗口句柄数目,失败返回0
//@别名   窗口_枚举(返回数组)
int X_Wnd_Enum(CXVector<X_FORM_WINININFO>& rList);
//@备注   枚举所有窗口
//@返回   窗口句柄数目,失败返回0
//@别名   窗口_枚举A(返回数组)
int X_Wnd_EnumA(CXVector<X_FORM_WINININFOA>& rList);

//@备注   获取指定窗口句柄的标题
//@别名   窗口_取标题(窗口句柄)
CXText X_Wnd_GetTitle(HWND hWnd);
//@备注   获取指定窗口句柄的标题
//@别名   窗口_取标题A(窗口句柄)
CXTextA X_Wnd_GetTitleA(HWND hWnd);

//@返回   返回进程ID
//@别名   窗口_句柄取进程ID(窗口句柄)
DWORD X_Wnd_HWNDGetProcessID(HWND hWnd);

//@返回   成功返回指定窗口的线程ID
//@别名   窗口_窗口句柄取线程ID(窗口句柄)
DWORD X_Wnd_HWNDGetThreadID(HWND hWnd);

//@别名   窗口_取类名(窗口句柄)
CXText X_Wnd_GetClass(HWND hWnd);
//@别名   窗口_取类名A(窗口句柄)
CXTextA X_Wnd_GetClassA(HWND hWnd);

//@备注   根据指定窗口句柄或窗口标题，查询一个窗口是否存在
//@返回   成功返回窗口句柄，否则返回0
//@别名   窗口_是否存在(句柄或标题)
HWND X_Wnd_WindowExists(CXText win);
//@备注   根据指定窗口句柄或窗口标题，查询一个窗口是否存在
//@返回   成功返回窗口句柄，否则返回0
//@别名   窗口_是否存在A(句柄或标题)
HWND X_Wnd_WindowExistsA(CXTextA win);

//@备注   查询一个窗口句柄是否有效
//@别名   窗口_是否存在_句柄(窗口句柄)
BOOL X_Wnd_WindowExistsHWND(HWND hWnd);

//@备注   枚举指定句柄的下一级子窗口
//@返回   返回子窗口句柄数目,失败或无子返回0
//@参数   父窗口句柄   指定父窗口句柄  可空:为桌面.找顶级窗口
//@参数   子窗口数组   返回的所有符合条件的子窗口句柄
//@参数   类名  指定子窗口类名
//@别名   窗口_枚举子窗口(父窗口句柄,子窗口数组,类名)
int X_Wnd_EnumSon(HWND hWnd, CXVector<HWND>& rList, CXText sClassName = L"");
//@备注   枚举指定句柄的下一级子窗口
//@返回   返回子窗口句柄数目,失败或无子返回0
//@参数   父窗口句柄   指定父窗口句柄  可空:为桌面.找顶级窗口
//@参数   子窗口数组   返回的所有符合条件的子窗口句柄
//@参数   类名  指定子窗口类名
//@别名   窗口_枚举子窗口A(父窗口句柄,子窗口数组,类名)
int X_Wnd_EnumSonA(HWND hWnd, CXVector<HWND>& rList, CXTextA sClassName = "");

//@备注   等待指定窗口出现，本命令类似于AU3脚本中WinWait命令
//@返回   成功返回窗口句柄，失败返回0
//@参数   标题 支持模糊标题
//@参数   内容 如果窗口标题相同，可以比较窗口内文本，支持模糊内容
//@参数   超时时间 单位为毫秒,超过此时间等待还没结果则返回0,留空或为0则一直等待
//@别名   窗口_等待出现(标题,内容,超时时间)
HWND X_Wnd_WaitAppear(CXText title, CXText str = L"", int timeout = 0);
//@备注   等待指定窗口出现，本命令类似于AU3脚本中WinWait命令
//@返回   成功返回窗口句柄，失败返回0
//@参数   标题 支持模糊标题
//@参数   内容 如果窗口标题相同，可以比较窗口内文本，支持模糊内容
//@参数   超时时间 单位为毫秒,超过此时间等待还没结果则返回0,留空或为0则一直等待
//@别名   窗口_等待出现A(标题,内容,超时时间)
HWND X_Wnd_WaitAppearA(CXTextA title, CXTextA str = "", int timeout = 0);

//@返回   成功返回控件的句柄，失败返回0
//@参数   父窗口句柄 如果是取顶级的窗口句柄请留空或NULL
//@参数   子窗口句柄 如果是取顶级的窗口句柄请留空或NULL
//@参数   窗口类名 窗口的类名
//@参数   窗口标题 窗口的标题
//@别名   窗口_取句柄(父窗口句柄,子窗口句柄,窗口类名,窗口标题)
HWND X_Wnd_GetHWND(HWND hWndf = NULL, HWND hWnds = NULL, CXText sClassName = L"", CXText sTitle = L"");
//@返回   成功返回控件的句柄，失败返回0
//@参数   父窗口句柄 如果是取顶级的窗口句柄请留空或NULL
//@参数   子窗口句柄 如果是取顶级的窗口句柄请留空或NULL
//@参数   窗口类名 窗口的类名
//@参数   窗口标题 窗口的标题
//@别名   窗口_取句柄A(父窗口句柄,子窗口句柄,窗口类名,窗口标题)
HWND X_Wnd_GetHWNDA(HWND hWndf = NULL, HWND hWnds = NULL, CXTextA sClassName = "", CXTextA sTitle = "");

//@备注   向指定窗口发送拖拽消息_该函数为ANSIC文件名使用；不支持拖放对象
//@参数   窗口句柄    接受拖拽消息的句柄
//@参数   路径  需要拖放的文件路径
//@别名   窗口_发送拖放消息A(窗口句柄,路径)
BOOL X_Wnd_SendFileDragDropMessageA(HWND hWnd, CXTextA strFilePath);
//@备注   向指定窗口发送拖拽消息_该函数为ANSIC文件名使用；不支持拖放对象
//@参数   窗口句柄    接受拖拽消息的句柄
//@参数   路径  需要拖放的文件路径
//@别名   窗口_发送拖放消息(窗口句柄,路径)
BOOL X_Wnd_SendFileDragDropMessage(HWND hWnd, CXText strFilePath);

//@备注   程序发送此消息给一个编辑框或combobox来复制当前选择的文本到剪贴板
//@别名   窗口_复制到剪贴板(窗口句柄)
BOOL X_Wnd_SendCopyMessage(HWND hWnd);

//@备注   修改窗口的鼠标指针
//@参数   窗口句柄
//@参数   光标路径 后缀名为:ani\cur的鼠标指针文件路径
//@参数   光标指针 #鼠标指针_
//@别名   窗口_更换鼠标指针(窗口句柄,光标路径,光标指针)
BOOL X_Wnd_ReplaceMousePointer(HWND hWnd, CXText sCurPath = L"", LPWSTR iPointer = 0);
//@备注   修改窗口的鼠标指针
//@参数   窗口句柄
//@参数   光标路径 后缀名为:ani\cur的鼠标指针文件路径
//@参数   光标指针 #鼠标指针_
//@别名   窗口_更换鼠标指针A(窗口句柄,光标路径,光标指针)
BOOL X_Wnd_ReplaceMousePointerA(HWND hWnd, CXTextA sCurPath = "", LPWSTR iPointer = 0);

//@返回   成功返回挂起计数，失败返回-1
//@参数   窗口句柄
//@参数   是否挂起 默认真
//@别名   窗口_挂起(窗口句柄,是否挂起)
DWORD X_Wnd_Suspend(HWND hWnd, BOOL bSuspend = true);

//@别名   窗口_关闭HWND(窗口句柄)
void X_Wnd_Close(HWND hWnd);

//@参数   窗口句柄 要画矩形的窗口的句柄
//@参数   矩形粗细 默认为3
//@参数   矩形颜色 默认为红色
//@参数   是否闪烁 默认假
//@别名   窗口_画矩形(窗口句柄,矩形粗细,矩形颜色,是否闪烁)
void X_Wnd_DrawRectangle(HWND hWnd, int iThickness = 3, DWORD rColor = 0xed0f28, BOOL bTwinkle = false);

//@返回   若函数调用成功，则返回原先活动窗口的句柄。若函数调用失败，则返回值为NULL
//@别名   窗口_激活(窗口句柄)
HWND X_Wnd_Activation(HWND hWnd);

//@备注   键状态用于判断是否是扩展按键，Ctrl、Alt、Enter等。通过检查该标志，你可以确定是否为扩展键,意义不大，目前只能检测到Alt键，原因不明
//@参数   回调函数 如: 函数 回调事件(整型 键代码,整型 键状态,逻辑型 是否按下),
//@别名   窗口_监视热键_注册(回调函数)
void X_Wnd_WindowHotkeys_register(LPVOID callback);

//@备注   卸载键盘HOOK
//@别名   窗口_监视热键_卸载(回调函数)
void X_Wnd_WindowHotkeys_uninstall();

//@备注   注册指定的窗口以接收会话更改通知
//@参数   窗口句柄 接收的窗口
//@参数   响应监视事件 如: 函数 回调事件(逻辑型 是锁屏)
//@别名   窗口_监视锁屏_注册(窗口句柄,响应监视事件)
BOOL X_Wnd_MonitoringLockScreen_register(HWND hWnd, LPVOID callback);
//@别名   窗口_监视锁屏_卸载(窗口句柄)
BOOL X_Wnd_MonitoringLockScreen_uninstall(HWND hWnd);

//@备注   将焦点切换到指定的窗口
//@别名   窗口_将焦点切换到指定的窗口(要激活的窗口句柄,是否使最小化的窗口还原)
void X_Wnd_SwitchToThisWindow(HWND hwnd, BOOL fUnknown = false);

//@备注   控制窗口关闭按钮,(允许/禁止)关闭窗口
//@返回   成功返回真,失败返回假
//@参数   窗口句柄    欲禁止或解除禁止的窗口句柄
//@参数   禁止关闭    默认为真,禁止关闭； 假:允许关闭； 真:禁止关闭；
//@别名   窗口_禁止关闭(窗口句柄,禁止关闭)
BOOL X_Wnd_WindowBanClose(HWND hwnd, BOOL bBanClose = true);

//@备注   保护自己的屏幕窗口内容不被捕获或复制
//@别名   窗口_禁止截图(窗口句柄,是否禁止)
BOOL X_Wnd_WindowBanScreen(HWND hwnd, BOOL bBan = true);

//@备注   根据指定窗口句柄获取程序的文件路径
//@别名   窗口_句柄取进程路径(窗口句柄)
CXText X_Wnd_HandleGetProcessPath(HWND hwnd = NULL);
//@备注   根据指定窗口句柄获取程序的文件路径
//@别名   窗口_句柄取进程路径A(窗口句柄)
CXTextA X_Wnd_HandleGetProcessPathA(HWND hwnd = NULL);

//@别名   窗口_句柄取进程名(窗口句柄)
CXText X_Wnd_GetProcessByHWND(HWND hwnd);
//@别名   窗口_句柄取进程名A(窗口句柄)
CXTextA X_Wnd_GetProcessByHWNDA(HWND hwnd);

//@别名   窗口_句柄取线程ID(窗口句柄)
DWORD X_Wnd_GetProcessIdByHWND(HWND hwnd);

//@别名   窗口_句柄取线程句柄(窗口句柄)
HANDLE X_Wnd_GetThreadHandleByHWND(HWND hwnd);

//@别名   窗口_句柄是否有效(窗口句柄)
BOOL X_Wnd_HWNDIsValid(HWND hwnd);

//@备注   根据控件ID取出窗口句柄
//@参数   父窗口句柄 上一级的窗口句柄
//@参数   控件ID 控件ID用 "窗口_取控件ID()/X_Wnd_GetControlID()"命令取回
//@别名   窗口_控件ID取句柄(父窗口句柄,控件ID)
HWND X_Wnd_GetControlHWNDByID(HWND hWnd, int nIDDlgItem);

//@备注   根据窗口句柄取出窗口控件的ID
//@返回   顶级窗口将返回0
//@别名   窗口_取控件ID(子窗口句柄)
int X_Wnd_GetControlID(HWND chWnd);

//@别名   窗口_毛玻璃特效(子窗口句柄)
BOOL X_Wnd_Aero(HWND chWnd);

//@参数   回调接口 例如：函数 回调事件(HWND 窗口接口,LPARAM lParam)
//@别名   窗口_枚举接口(回调接口)
void X_Wnd_EnumInterface(LPVOID pCallBack);

//
//@返回   返回满足条件的第一个窗口的句柄
//@参数   父窗口句柄 为空，则为桌面句柄
//@参数   要找的窗口类名
//@参数   要找的窗口标题
//@参数   结果句柄数组指针 原型为 动态数组<HWND>/CXVector<HWND> ,例如:窗口_模糊遍历窗口(0,"","",&返回数组)
//@别名   窗口_模糊遍历窗口(父窗口句柄,要找的窗口类名,要找的窗口标题,结果句柄数组指针)
HWND X_Wnd_VagueEnumWindow(HWND fhWnd = NULL, CXText sWClass = L"", CXText title = L"", LPVOID rLIst = NULL);

//@备注   对窗口进行置顶、激活等操作（注：非强制显示隐藏窗口）
//@别名   窗口_强制显示(窗口句柄,总在最前)
BOOL X_Wnd_ForceDisplay(HWND hWnd, BOOL bTopping = false);

//@备注  判断窗口是否为置顶的窗口
//@别名  窗口_是否置顶(窗口句柄)
BOOL XC_Wnd_IsTopmost(HWND hWnd);

//@别名   窗口_取边框宽度(窗口句柄)
UINT X_Wnd_GetWindFrameWidth(HWND hWnd);
//@别名   窗口_取边框高度(窗口句柄)
UINT X_Wnd_GetWindFrameHeight(HWND hWnd);

//@别名   窗口_取窗口属性(窗口句柄,类型)
LONG X_Wnd_GetWindAttribute(HWND hWnd, int type);

//@别名   窗口_取点标题(水平位置,垂直位置)
CXText X_Wnd_GetPOINTTitle(LONG x = -1, LONG y = -1);
//@别名   窗口_取点标题A(水平位置,垂直位置)
CXTextA X_Wnd_GetPOINTTitleA(LONG x = -1, LONG y = -1);

//@返回   成功返回路径，失败返回空文本
//@别名   窗口_取顶端文件夹路径()
CXText X_Wnd_GetTopFolderPath();
//@返回   成功返回路径，失败返回空文本
//@别名   窗口_取顶端文件夹路径A()
CXTextA X_Wnd_GetTopFolderPathA();

//@返回   成功返回控件的句柄，失败返回0
//@别名   窗口_取句柄_递归(句柄,指定类名)
HWND X_Wnd_RecursionGetHWND(HWND hWnd, CXText sClass);
//@返回   成功返回控件的句柄，失败返回0
//@别名   窗口_取句柄_递归A(句柄,指定类名)
HWND X_Wnd_RecursionGetHWNDA(HWND hWnd, CXTextA sClass);

//@备注   注意!.使用该命令时,需要保证被取光标位置的编辑框 [拥有输入焦点] 否则命令将会失败
//@参数   窗口句柄 如果是自身，请直接输入0或忽略
//@别名   窗口_取光标位置(窗口句柄)
RECT X_Wnd_GetCursorPoint(HWND hWnd = 0);

//@别名   窗口_取光标位置1(线程ID)
POINT X_Wnd_GetCursorPoint1(HANDLE dwThreadID = 0);

//@别名   窗口_取滚动条位置(控件句柄)
POINT X_Wnd_GetScrollBarPoint(HWND hWnd);

//@备注   取焦点句柄;获得自身拥有输入焦点的窗口句柄
//@别名   窗口_取焦点句柄()
HWND X_Wnd_GetFocusHwnd();

//@备注   返回指定窗口的矩形信息
//@别名   窗口_取矩形(窗口句柄)
RECT X_Wnd_GetRECT(HWND hWnd);

//@别名   窗口_取客户区矩形(窗口句柄)
RECT X_Wnd_GetClientRECT(HWND hWnd);

//@备注   获取一个控件的大小（宽度和高度）
//@返回   x为宽,y为高
//@别名   窗口_取控件大小(窗口句柄,返回结构)
BOOL X_Wnd_GetControlSize(HWND hWnd, POINT& rpoint);

//@备注   取指定窗口的标题
//@返回   成功返回窗口标题，失败返回空
//@别名   窗口_取控件内容(控件句柄)
CXText X_Wnd_GetControlContent(HWND hWnd);
//@备注   取指定窗口的标题
//@返回   成功返回窗口标题，失败返回空
//@别名   窗口_取控件内容A(控件句柄)
CXTextA X_Wnd_GetControlContentA(HWND hWnd);

//@备注   取指定窗口(左上角\顶点)在屏幕中的位置
//@别名   窗口_取控件坐标(控件句柄)
POINT X_Wnd_GetControlPoint(HWND hWnd = NULL);

//@别名   窗口_取扩展样式(窗口句柄)
DWORD X_Wnd_GetWindowExStyle(HWND hWnd);

//@备注   取任务栏句柄
//@别名   窗口_取任务栏句柄()
HWND X_Wnd_GetTrayWnd();

//@备注   取鼠标处窗口句柄
//@返回   成功返回句柄，失败返回0
//@别名   窗口_取鼠标处窗口句柄()
HWND X_Wnd_GetMousePointHwnd();

//@别名   窗口_取鼠标处控件标题()
CXText X_Wnd_GetMousePointControl(LONG x = 0, LONG y = 0);
//@别名   窗口_取鼠标处控件标题A()
CXTextA X_Wnd_GetMousePointControlA(LONG x = 0, LONG y = 0);

//@备注   成功返回窗口的透明度，失败返回-1
//@别名   窗口_取透明度(窗口句柄)
DWORD X_Wnd_GetTransparency(HWND hWnd);

//@备注   取消 [窗口_限制尺寸] 的限制
//@别名   窗口_取消尺寸限制(窗口句柄,是否取消限制)
BOOL  X_Wnd_CancelSizeLimit(HWND hWnd, BOOL cancel);

//@返回   返回指定窗口的窗口样式
//@别名   窗口_取样式(窗口句柄)
DWORD X_Wnd_GetWindowStyle(HWND hWnd);

//@别名   窗口_取字符串宽度(窗口句柄,字符串)
DWORD X_Wnd_GetStrWidth(HWND hWnd, CXText str);
//@别名   窗口_取字符串宽度A(窗口句柄,字符串)
DWORD X_Wnd_GetStrWidthA(HWND hWnd, CXTextA str);

//@备注   取一个窗口的顶级句柄，如果提供的句柄已是顶级句柄，将直接返回
//@别名   窗口_取祖句柄(窗口句柄)
HWND X_Wnd_GetAncestorsHwnd(HWND hWnd);

//@备注   返回两坐标点之间的距离
//@别名   窗口_取坐标距离(坐标1,坐标2)
double X_Wnd_GetPointsDistance(POINT a, POINT b);

//@参数   取父窗口中包含了指定坐标的第一个子窗口句柄(与其它取窗口句柄不同的是:可取出不可视或透明的窗口)
//@别名   窗口_取坐标子句柄(父窗口句柄,坐标)
HWND X_Wnd_GetChildWindowFromPoint(HWND hWnd, POINT p);

//@备注   闪烁指定窗口，可选闪烁标题、任务栏、次数、速度
//@返回   成功返回真，失败返回假。
//@备注   窗口句柄 指定闪动的窗口句柄 
//@备注   闪烁类型 默认为标题闪烁,可选参数(多个值可相加);0=停止;1=标题;2=任务栏;3=标题与任务栏;4=连续
//@备注   闪烁次数 可为空,默认即1次.
//@备注   闪烁速度 可为空,即默认速度.单位为"毫秒"
//@别名   窗口_闪动Ex(窗口句柄,闪烁类型,闪烁次数,闪烁速度)
BOOL X_Wnd_FlashWindowEx(HWND hWnd, UINT type = 1, UINT num = 1, UINT speed = 0);

//@备注   设置窗口为无焦点窗口（类似输入法窗口不会获取焦点）
//@别名   窗口_设为无焦点(窗口句柄)
LONG X_Wnd_SetWindowToNoFocus(HWND hWnd);

//@备注   判断指定窗口是否激活状态
//@返回   激活状态则返回真，否则返回假
//@别名   窗口_是否激活(窗口句柄)
BOOL  X_Wnd_IsActivation(HWND hWnd);

//@备注   判断指定窗口的是否被禁止
//@返回   如果禁止返回真,否则返回假
//@别名   窗口_是否禁止(窗口句柄)
BOOL  X_Wnd_IsProhibit(HWND hWnd);

//@别名   窗口_是否全屏(窗口句柄)
BOOL X_Wnd_IsFullScreen(HWND hWnd);

//@备注   判断某个窗口下是否有子级窗口控件
//@别名   窗口_是否有子窗口(窗口句柄)
BOOL X_Wnd_HavingChildren(HWND hWnd);

//@返回   返回值是指定的32位整数的原来的值。如果函数失败，返回值为0。若想获得更多错误信息，请调用GetLastError函数
//@别名   窗口_剔除风格(句柄,待剔除风格)
LONG X_Wnd_CullStyle(HWND hWnd, DWORD dwStyle);
//@返回   返回值是指定的32位整数的原来的值。如果函数失败，返回值为0。若想获得更多错误信息，请调用GetLastError函数
//@别名   窗口_剔除扩展风格(句柄,待剔除风格)
LONG X_Wnd_CullStyleEx(HWND hWnd, DWORD dwStyle);

//@别名   窗口_限制运行次数(标题,类名,限制次数)
BOOL X_Wnd_RestrictedOperationNum(CXText title, CXText sClassName, int num = 1);
//@别名   窗口_限制运行次数A(标题,类名,限制次数)
BOOL X_Wnd_RestrictedOperationNumA(CXTextA title, CXTextA sClassName, int num = 1);

//@备注   循环关闭一个窗口
//@别名   窗口_循环关闭(窗口类名,窗口标题)
void X_Wnd_CycleClose(CXText sClassName, CXText title);
//@备注   循环关闭一个窗口
//@别名   窗口_循环关闭A(窗口类名,窗口标题)
void X_Wnd_CycleCloseA(CXTextA sClassName, CXTextA title);

//@备注   隐藏标题左上角的小图标
//@别名   窗口_隐藏小图标(窗口句柄)
void X_Wnd_HideSmallIcon(HWND hWnd);

//@备注   改指定窗口句柄的窗口标题
//@别名   窗口_置标题(窗口句柄,标题)
BOOL X_Wnd_SetTitle(HWND hWnd, CXText title);
//@备注   改指定窗口句柄的窗口标题
//@别名   窗口_置标题A(窗口句柄,标题)
BOOL X_Wnd_SetTitleA(HWND hWnd, CXTextA title);

//@别名   窗口_置穿透(窗口句柄,是否穿透)
BOOL X_Wnd_SetPenetrate(HWND hWnd, BOOL bPenetrate = false);

//@备注   将指定窗口窗口化.通常用于游戏中
//@参数   句柄 欲窗口化的窗口句柄(通常有这一个参数就可以了,其它可以不设定)
//@参数   新宽度 窗口化后的窗口宽度 可空:800
//@参数   新高度 窗口化后的窗口高度 可空:600
//@参数   窗口标题 窗口化后的窗口标题 可空:不修改原窗口标题(有的游戏修改标题后会自动退出)
//@参数   是否带边框 可空:无边框窗口 真:带标题栏(有的游戏屏蔽了边框的修改,可通过其它方法来实现)
//@参数   分辨率_宽 可空:不修改分辨率(有的游戏全屏时修改了其分辨率,需改回去..)
//@参数   分辨率_高 可空:不修改分辨率
//@别名   窗口_置窗口化(窗口句柄,新宽度,新高度,窗口标题,是否带边框,分辨率_宽,分辨率_高)
void X_Wnd_SetWindowing(HWND hWnd, int NewWidth = 800, int NewHeight = 600, CXText title = L"", BOOL addFrame = false, int rpWidth = 0, int rpHeight = 0);

//@备注   置滚动条到指定位置
//@别名   窗口_置滚动条位置(控件句柄,坐标)
void X_Wnd_SetScrollBarPosition(HWND hWnd, POINT pPosition);

//@备注   该函数对指定的窗口设置键盘焦点
//@返回   失败返回0
//@别名   窗口_置控件焦点(控件句柄)
HWND X_Wnd_SetControlFocus(HWND hWnd);

//@备注   往指定的编辑框内置指定的内容
//@别名   窗口_置控件内容(控件句柄,欲写入的内容)
void X_Wnd_SetControlContent(HWND hWnd, CXText str);
//@备注   往指定的编辑框内置指定的内容
//@别名   窗口_置控件内容A(控件句柄,欲写入的内容)
void X_Wnd_SetControlContentA(HWND hWnd, CXTextA str);

//@备注   隐藏或显示控件
//@参数   窗口句柄
//@参数   显示隐藏 真 = 显示；假 = 隐藏
//@别名   窗口_置控件状态(窗口句柄,显示隐藏)
BOOL X_Wnd_SetScrollBar(HWND hWnd, BOOL show);

//@别名   窗口_总在最前(窗口句柄,是否总在最前)
BOOL X_Wnd_AlwaysTop(HWND hWnd, BOOL bATop);

//@别名   窗口_最大化(窗口句柄,无边框)
void X_Wnd_Maximize(HWND hWnd, BOOL bNoFrame = false);

//@备注   把窗口或控件的四个直角设置成圆角
//@别名   控件_圆角化(窗口句柄,圆角宽,圆角高)
void X_Wnd_ControlRounding(HWND hWnd, int Width, int height);


/*@声明

//@参数   强制立即更新窗口，窗口中以前屏蔽的所有区域都会重画
//@别名   窗口_更新窗口(窗口句柄)
BOOL UpdateWindow(HWND hWnd);

//@备注   恢复一个最小化的程序，并将其激活
//@返回   成功把回真，失败返回假
//@别名   窗口_还原(窗口句柄)
BOOL OpenIcon(HWND hWnd);

//@返回   成功返回一个最顶端窗口的句柄
//@别名   窗口_取顶端窗口句柄()
HWND GetForegroundWindow ();

//@备注   判断一个窗口是否有父窗口，如有直接返回该窗口的像窗口句柄，否则返回0
//@参数   窗口句柄 欲取父窗口的窗口句柄
//@别名   窗口_取父句柄(窗口句柄)
HWND GetParent(HWND hWnd);

//@备注   取激活的窗口句柄
//@别名   窗口_取激活句柄()
HWND GetActiveWindow();

//@别名   窗口_取屏幕句柄()
HWND GetDesktopWindow();

//@别名   窗口_取指定坐标处句柄(坐标)
HWND WindowFromPoint(POINT p);

//@别名   窗口_闪动(窗口句柄,是否闪动)
BOOL FlashWindow(HWND hWnd,BOOL flash);

//@返回   返回真为可见，否则为不可见
//@别名   窗口_是否可见(窗口句柄)
BOOL IsWindowVisible(HWND hWnd);

//@备注   判断一个窗口和另一窗口是否为父子关系
//@别名   窗口_是否子窗口(父窗口的句柄,欲判断的窗口句柄)
BOOL IsChild(HWND hWndParent, HWND hWnd);

//@备注   已最大化返回真；否则返回假
//@别名   窗口_是否最大化(窗口句柄)
BOOL IsZoomed(HWND hWnd);

//@备注   已最小化返回真；否则返回假
//@别名   窗口_是否最小化(窗口句柄)
BOOL IsIconic(HWND hWnd);

//@备注   在指定的窗口里允许或禁止所有鼠标及键盘输入
//@参数   窗口句柄 要锁住或解锁的窗口句柄
//@参数   是否解锁 真 = 解锁；假 = 锁住；
//@别名   窗口_锁住解锁(窗口句柄,是否解锁)
BOOL EnableWindow(HWND hWnd, BOOL bEnable);

//@备注   窗口显示或隐藏
//@参数   窗口句柄 欲操作的窗口句柄
//@参数   显示隐藏 真 = 显示；假 = 隐藏
//@别名   窗口_显示隐藏(窗口句柄,显示隐藏)
BOOL ShowWindowAsync(HWND hWnd, int nCmdShow);

//@返回   如果函数成功，返回值是指定的32位整数的原来的值。如果函数失败，返回值为0。若想获得更多错误信息，请调用GetLastError函数。
//@参数   窗口句柄 设置指定的窗口风格属性，如将有边框窗口设置为无边框窗口
//@参数   属性 参考常量GWL相关
//@参数   新样式 调用 窗口_取窗口属性 获取对应属性值并设置对应属性值
//@别名   窗口_置窗口属性(窗口句柄,属性,新样式)
LONG_PTR SetWindowLongPtrA( HWND hWnd, int nIndex, LONG_PTR dwNewLong);

//@返回   成功返回真，失败返回假
//@参数   窗口句柄 欲设置状态的窗口句柄
//@参数   状态类型 0 隐藏取消激活 1 还原激活 2 最小化激活 3 最大化激活 4 还原 6 最小化取消激活 7 最小化 9 还原激活
//@别名   窗口_置状态(窗口句柄,状态类型)
BOOL ShowWindow(HWND hWnd, int nCmdShow);

//@别名   窗口_最小化(窗口句柄)
BOOL CloseWindow(HWND hWnd);


*/


//@分组}  窗口句柄
//@分组{  常量

//@别名   常量_状态键_Shift键
#define X_STATUSKEY_SHIFT 16
//@别名   常量_状态键_Ctrl键
#define X_STATUSKEY_CTRL 17
//@别名   常量_状态键_Alt键
#define X_STATUSKEY_ALT 18
//@别名   常量_状态键_Win键
#define X_STATUSKEY_WIN 91
//@分组}  常量


#endif //XL_XEXPAND_WINDOW_H
