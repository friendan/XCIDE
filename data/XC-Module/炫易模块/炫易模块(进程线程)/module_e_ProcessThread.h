// Created by Huiyi on 2021/4/20.
//
//@模块名称  炫易模块(进程线程)
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

#ifndef XL_XEXPAND_PROCESS_THREAD_H
//@隐藏{
#define XL_XEXPAND_PROCESS_THREAD_H    //防止复用

#if XC_MODULE
#include "module_base.h"
#endif

#include <psapi.h>
#include <iphlpapi.h>
#include <tlhelp32.h>
#include <AclAPI.h>
#include <dbghelp.h>
#include <WinSock.h>

#pragma  comment(lib, "Dbghelp.lib")
#pragma  comment(lib, "Iphlpapi.lib")
#pragma  comment(lib, "Ws2_32.lib")
//@隐藏}


//@src  "process.cpp"
//@src  "thread.cpp"



//@分组{	进程操作

//@别名 进程_模块信息A
struct X_Process_ModuleInfoA {
	//@别名 模块句柄
	HMODULE hModule=nullptr;
	//@别名 模块文件名
	CXTextA BaseName;
	//@别名 模块完整路径
	CXTextA FileName;
};
//@别名 进程_模块信息W
struct X_Process_ModuleInfoW {
	//@别名 模块句柄
	HMODULE hModule = nullptr;
	//@别名 模块文件名
	CXText BaseName;
	//@别名 模块完整路径
	CXText FileName;
};

/*@声明
//@别名 进程_内存模块信息A
struct tagMODULEENTRY32 {
	//@别名 结构体尺寸
	DWORD   dwSize;
	//@别名 模块ID
	DWORD   th32ModuleID;
	//@别名 进程ID
	DWORD   th32ProcessID;
	//@别名 全局引用数
	DWORD   GlblcntUsage;
	//@别名 引用数
	DWORD   ProccntUsage;
	//@别名 模块基址
	BYTE  * modBaseAddr;
	//@别名 模块大小
	DWORD   modBaseSize;
	//@别名 模块句柄
	HMODULE hModule;
	//@别名 模块名
	char    szModule[256];
	//@别名 模块路径
	char    szExePath[MAX_PATH];
};
//@别名 进程_内存模块信息W
struct tagMODULEENTRY32W
{
	//@别名 结构体尺寸
	DWORD   dwSize;
	//@别名 模块ID
	DWORD   th32ModuleID;
	//@别名 进程ID
	DWORD   th32ProcessID;
	//@别名 全局引用数
	DWORD   GlblcntUsage;
	//@别名 引用数
	DWORD   ProccntUsage;
	//@别名 模块基址
	BYTE  * modBaseAddr;
	//@别名 模块大小
	DWORD   modBaseSize;
	//@别名 模块句柄
	HMODULE hModule;
	//@别名 模块名
	WCHAR   szModule[256];
	//@别名 模块路径
	WCHAR   szExePath[MAX_PATH];
};

//@别名 进程_进程结构
struct PROCESS_INFORMATION {
	//@别名 进程句柄
	HANDLE hProcess;
	//@别名 线程句柄
	HANDLE hThread;
	//@别名 进程标识符
	DWORD dwProcessId;
	//@别名 线程标识符
	DWORD dwThreadId;
};

*/


//@别名   进程_ID取进程名W(进程ID)
CXText X_Process_GetNameByIDW(DWORD PID);
//@别名   进程_ID取进程名A(进程ID)
CXTextA X_Process_GetNameByIDA(DWORD PID);
//@别名   进程_ID取进程名ExA(进程ID)
CXTextA X_Program_GetProcessNameByIDExA(DWORD pid);
//@别名   进程_ID取进程名ExW(进程ID)
CXText X_Program_GetProcessNameByIDExW(DWORD pid);

//@备注   数据执行保护开关; 成功返回真, 失败返回假
//@参数   dwFlags 常量_进程_DEP_\X_DEFINE_PROCESS_DEP_
//@别名   进程_DEP保护(标志)
BOOL X_Program_DEPProtect(DWORD dwFlags=0);

//@备注   编译成DLL后被其他程序加载时用于查看自身模块信息
//@别名   进程_DLL取自身信息A()
X_Process_ModuleInfoA X_Program_GetModuleInfoA();
//@备注   编译成DLL后被其他程序加载时用于查看自身模块信息
//@别名   进程_DLL取自身信息W()
X_Process_ModuleInfoW X_Program_GetModuleInfoW();

//@备注   编译成DLL后被其他程序加载时用于查看自身模块信息
//@别名   进程_DLL取自身信息ExA(模块名)
X_Process_ModuleInfoA X_Program_GetModuleInfoExA(const char* ModuleName="");
//@备注   编译成DLL后被其他程序加载时用于查看自身模块信息
//@别名   进程_DLL取自身信息ExW(模块名)
X_Process_ModuleInfoW X_Program_GetModuleInfoExW(const wchar_t* ModuleName = L"");

//@备注   通过进程ID取得该进程的窗口句柄,超时则返回零.
//@返回   返回的句柄不一定是祖句柄,只要满足条件就返回
//@参数   进程ID 该进程的ID
//@参数   窗口标题 模糊参数 如果为空,忽略此参数
//@参数   窗口类名 模糊参数 如果为空,忽略此参数
//@参数   超时 为空则无限循环
//@参数   是否可见 可空 默认为真,只查找可见的窗口;为假则查找包括不可见的窗口
//@别名   进程_ID取窗口句柄A(进程ID,窗口标题,窗口类名,超时,是否可见)
HWND X_Program_FindHWNDByIDA(DWORD pid, const char* title="", const char* className = "", DWORD timeOut = 0, bool isVisual = true);
//@备注   通过进程ID取得该进程的窗口句柄,超时则返回零.
//@返回   返回的句柄不一定是祖句柄,只要满足条件就返回
//@参数   进程ID 该进程的ID
//@参数   窗口标题 模糊参数 如果为空,忽略此参数
//@参数   窗口类名 模糊参数 如果为空,忽略此参数
//@参数   超时 为空则无限循环
//@参数   是否可见 可空 默认为真,只查找可见的窗口;为假则查找包括不可见的窗口
//@别名   进程_ID取窗口句柄W(进程ID,窗口标题,窗口类名,超时,是否可见)
HWND X_Program_FindHWNDByIDW(DWORD pid, const wchar_t* title=L"", const wchar_t* className = L"", DWORD timeOut=0, bool isVisual = true);

//@返回   失败为0，成功返回模块数量
//@别名   进程_ID取模块A(进程ID,模块信息数组)
UINT X_Program_GetModuleListByIdA(DWORD pid, CXVector<tagMODULEENTRY32>& ret);
//@返回   失败为0，成功返回模块数量
//@别名   进程_ID取模块W(进程ID,模块信息数组)
UINT X_Program_GetModuleListByIdW(DWORD pid, CXVector<tagMODULEENTRY32W>& ret);

//@备注   检索指定进程中满足指定过滤条件的每个模块的句柄。
//@别名   进程_ID取模块句柄列表(进程ID,模块句柄数组)
UINT X_Program_GetModuleHandleListById(DWORD pid, CXVector<HMODULE>& ret);

//@别名   进程_ID是否有效(进程ID)
bool X_Program_ProcessExist(DWORD pid);

//@备注   通过进程PID取出本地端口
//@别名   进程_ID取端口(进程ID)
UINT X_Program_GetPortByID(DWORD pid);
//@备注   通过本地端口取出进程PID
//@别名   进程_端口取ID(本地端口)
UINT X_Program_GetIDByPort(DWORD port);

//@别名   进程_ID取路径A(进程ID)
CXTextA X_Program_GetPathByIDA(DWORD pid);
//@别名   进程_ID取路径W(进程ID)
CXText X_Program_GetPathByIDW(DWORD pid);

//@备注   枚举在不同用户上下文中运行的进程
//@别名   进程_按用户名枚举进程A(用户名,返回ID数组)
UINT X_Program_EnumProcessByUserNameA(CXTextA UserName,CXVector<DWORD>&ret);
//@备注   枚举在不同用户上下文中运行的进程
//@别名   进程_按用户名枚举进程W(用户名,返回ID数组)
UINT X_Program_EnumProcessByUserNameW(CXText UserName, CXVector<DWORD>& ret);

//@备注   创建一个程序进程
//@参数   程序路径 欲创建进程的执行路径
//@参数   命令行 附加上程序路径后的命令行参数
//@参数   运行目录 程序的运行目录
//@参数   进程结构 接收进程结构信息的变量,如果不为空，句柄用CloseHandle函数释放
//@返回   成功返回进程ID,失败返回0
//@别名   进程_创建A(程序路径,命令行,运行目录,进程结构)
DWORD X_Program_ProcessCreateA(CXTextA ExePath, CXTextA cmd="", CXTextA RunPath = "", PROCESS_INFORMATION* Info=NULL);
//@备注   创建一个程序进程
//@参数   程序路径 欲创建进程的执行路径
//@参数   命令行 附加上程序路径后的命令行参数
//@参数   运行目录 程序的运行目录
//@参数   进程结构 接收进程结构信息的变量,如果不为空，句柄用CloseHandle函数释放
//@返回   成功返回进程ID,失败返回0
//@别名   进程_创建W(程序路径,命令行,运行目录,进程结构)
DWORD X_Program_ProcessCreateW(CXText ExePath, CXText cmd=L"", CXText RunPath = L"", PROCESS_INFORMATION* Info=NULL);

//@备注   创建一个程序进程
//@参数   程序路径 欲创建进程的执行路径
//@参数   命令行 附加上程序路径后的命令行参数
//@参数   是否等待 是否等待程序运行完毕
//@参数   显式方式 参见常量:常量_进程_显示方式_,或者任意 SW_ 常量
//@参数   运行目录 程序的运行目录
//@参数   进程结构 接收进程结构信息的变量,如果不为空，句柄用CloseHandle函数释放
//@返回   成功返回进程ID,失败返回0
//@别名   进程_创建ExA(程序路径,命令行,是否等待,显式方式,运行目录,进程结构)
DWORD X_Program_ProcessCreateExA(CXTextA ExePath, CXTextA cmd = "",bool wait=false,int ExplicitMode=SW_SHOWNORMAL, CXTextA RunPath = "", PROCESS_INFORMATION* Info = NULL);

//@备注   通过目标窗口句柄或进程ID取进程句柄，成功返回进程句柄
//@参数   窗口句柄或进程ID
//@别名   进程_打开(窗口句柄或pid)
HANDLE X_Program_ProcessOpen(DWORD hWndOrPid);

//@备注   通过进程PID定位进程(失败需要自行初始化com)
//@别名   进程_定位(进程ID)
bool X_Program_FileLocation(DWORD pid);

//@备注   关闭已经打开的操作句柄
//@别名   进程_关闭(进程ID)
BOOL X_Program_Close(HANDLE pid);

//@别名   进程_结束(进程ID)
BOOL X_Program_ShutDown(DWORD pid=NULL);

//@别名   进程_禁止被打开()
bool X_Program_DonotOpen();

//@备注   成功则返回值是进程标识符。失败返回值为NULL！
//@参数   进程句柄 进程的句柄。句柄必须具有 PROCESS_QUERY_INFORMATION 或 PROCESS_QUERY_LIMITED_INFORMATION 访问权限。
//@别名   进程_句柄取进程ID(进程句柄)
DWORD X_Program_GetIDByHandle(HANDLE handle);

//@备注   失败返回0，成功返回进程数量
//@参数   字典结构为<进程PID,进程名>
//@别名   进程_枚举A(返回数据)
UINT X_Program_ProcessEnumA(CXMap<DWORD,CXTextA>&ret);
//@备注   失败返回0，成功返回进程数量
//@参数   字典结构为<进程PID,进程名>
//@别名   进程_枚举W(返回数据)
UINT X_Program_ProcessEnumW(CXMap<DWORD,CXText>&ret);

//@备注   通过进程名取进程ID.失败返回0
//@参数   进程名 取要进程ID的进程名
//@参数   是否区分大小写 默认为不区分,真=区分
//@别名   进程_名取IDA(进程名,是否区分大小写)
DWORD X_Program_GetIDByNameA(CXTextA name, bool isCase=false);
//@备注   通过进程名取进程ID.失败返回0
//@参数   进程名 取要进程ID的进程名
//@参数   是否区分大小写 默认为不区分,真=区分
//@别名   进程_名取IDW(进程名,是否区分大小写)
DWORD X_Program_GetIDByNameW(CXText name, bool isCase = false);

//@备注   通过进程名取对应的窗口句柄；成功返回窗口句柄，失败返回0，返回-1表示找不到进程。
//@参数   进程名 要取窗口句柄的进程名
//@别名   进程_名取句柄A(进程名)
HWND X_Program_GetHWNDByProcessNameA(CXTextA name);
//@备注   通过进程名取对应的窗口句柄；成功返回窗口句柄，失败返回0，返回-1表示找不到进程。
//@参数   进程名 要取窗口句柄的进程名
//@别名   进程_名取句柄W(进程名)
HWND X_Program_GetHWNDByProcessNameW(CXText name);

//@备注   查看指定进程ID的内存使用情况
//@参数   返回单位 0=Byte，1=KB，2=MB，3=GB，默认为1
//@别名   进程_内存使用(进程ID,返回单位)
LONGLONG X_Program_GetProcessMemoryInfo(DWORD pid=NULL,int Company=1);
//@备注   特殊进程需要特权，获取指定进程IO读取计数,与XP系统任务管理器功能一样，失败返回-1。
//@别名   进程_取IO读取计数(进程ID)
LONGLONG X_Program_GetIOReadOperationCount(DWORD pid=NULL);
//@备注   特殊进程需要特权，获取指定进程IO读取字节数,与XP系统任务管理器功能一样，失败返回-1。
//@别名   进程_取IO读取字节(进程ID)
LONGLONG X_Program_GetIOReadTransferCount(DWORD pid = NULL);
//@备注   特殊进程需要特权，获取指定进程IO其它计数,与XP系统任务管理器功能一样，失败返回-1。
//@别名   进程_取IO其它计数(进程ID)
LONGLONG X_Program_GetIOOtherOperationCount(DWORD pid = NULL);
//@备注   特殊进程需要特权，获取指定进程IO其它字节,与XP系统任务管理器功能一样，失败返回-1。
//@别名   进程_取IO其它字节(进程ID)
LONGLONG X_Program_GetIOOtherTransferCount(DWORD pid = NULL);
//@备注   特殊进程需要特权，获取指定进程IO写入计数,与XP系统任务管理器功能一样，失败返回-1。
//@别名   进程_取IO写入计数(进程ID)
LONGLONG X_Program_GetIOWriteOperationCount(DWORD pid = NULL);
//@备注   特殊进程需要特权，获取指定进程IO写入字节,与XP系统任务管理器功能一样，失败返回-1。
//@别名   进程_取IO写入字节(进程ID)
LONGLONG X_Program_GetIOWriteTransferCount(DWORD pid = NULL);

//@备注   根据进程名或进程ID取出进程父ID，失败返回-1。
//@别名   进程_取父ID(进程ID)
DWORD X_Program_GetParentProcessId(DWORD pid = NULL);

//@别名   进程_取句柄数(进程ID)
DWORD X_Program_GetHandleCount(DWORD pid = NULL);

//@别名   进程_取模块句柄A(模块名)
HMODULE X_Program_GetModelHandleA(CXTextA name);
//@别名   进程_取模块句柄W(模块名)
HMODULE X_Program_GetModelHandleW(CXText name);

//@备注   取当前进程的命令行
//@别名   进程_取启动参数A()
CXTextA X_Program_GetCommandLineA();
//@备注   取当前进程的命令行
//@别名   进程_取启动参数W()
CXText X_Program_GetCommandLineW();

//@备注   通过进程ID或进程名获取指定进程线程数。
//@别名   进程_取线程数(进程ID)
UINT  X_Program_GetThreadCount(DWORD pid=NULL);

//@备注   获取指定进程的用户名
//@别名   进程_取用户名A(进程ID)
CXTextA  X_Program_GetProcessUsernameA(DWORD pid = NULL);
//@备注   获取指定进程的用户名
//@别名   进程_取用户名W(进程ID)
CXText  X_Program_GetProcessUsernameW(DWORD pid = NULL);

//@别名 进程优先级
enum X_Program_Enum_ProcessPriority {
	//@别名 进程优先级_无权访问
	NoPermission=-1,
	//@别名 进程优先级_最高
	Highest=0,
	//@别名 进程优先级_高于标准
	AboveStandard,
	//@别名 进程优先级_实时
	RealTime,
	//@别名 进程优先级_标准
	Standard,
	//@别名 进程优先级_低于标准
	BelowStandard,
	//@别名 进程优先级_低
	Low,
};

//@备注   特殊进程需要特权，检索指定的进程的优先级。
//@别名   进程_取优先级(进程ID)
X_Program_Enum_ProcessPriority X_Program_GetProcessPriority(DWORD pid = NULL);

//@备注   检索与指定进程关联的远程桌面服务会话
//@别名   进程_取远程会话ID(进程ID)
DWORD  X_Program_GetSessionIdByProcessId(DWORD pid = NULL);

/*@声明
//@别名 进程_权限等级
enum TOKEN_ELEVATION_TYPE {
	//@备注 默认权限,参见创建者。
	//@别名 进程_权限等级_默认
	TokenElevationTypeDefault = 1,
	//@备注 高权限。
	//@别名 进程_权限等级_已提升
	TokenElevationTypeFull,
	//@备注 高权限,但是权限有限。
	//@别名 进程_权限等级_已提升_受限
	TokenElevationTypeLimited,
};
*/

//@别名   进程_取执行权限级别(进程ID)
TOKEN_ELEVATION_TYPE X_Program_GetProcessUACLevel(DWORD pid = NULL);

//@备注   取指定进程ID为父进程的子进程ID
//@返回   返回子进程的ID
//@别名   进程_取子进程ID(父进程ID)
DWORD X_Program_GetSonProcessId(DWORD ParentPid);
//@备注   取指定进程ID为父进程的所有子进程ID
//@返回   返回数组数量
//@别名   进程_取所有子进程(父进程ID,返回数组)
DWORD X_Program_GetAllSonProcessId(DWORD ParentPid,CXVector<DWORD>&ret);

//@备注   判断指定的进程是否正在调试
//@参数   hProcess 被打开的进程句柄
//@别名   进程_是否被调试(进程句柄)
BOOL X_Program_CheckRemoteDebuggerPresent(HANDLE);

//@别名   进程_是否被挂起(进程ID)
BOOL X_Program_ProcessIfSuspend(DWORD pid = NULL);

//@别名   进程_是否为64位(进程ID)
BOOL X_Program_ProcessIs64(DWORD pid = NULL);

//@别名   进程_是否有管理员特权(进程ID)
BOOL X_Program_ProcessIsAdmin(DWORD pid = NULL);

//@备注   将进程权限提升至Debug
//@别名   进程_提升权限(进程ID)
BOOL X_Program_ProcessPermissionPromotion(DWORD pid);

//@备注   将指定进程暂停
//@参数   状态 可空为假:恢复进程   真:暂停进程
//@别名   进程_暂停(进程ID,状态)
void X_Program_ProcessSuspend(DWORD pid,bool state=false);

//@隐藏{
#define X_Program_Enum_ProcessPriority_Default X_Program_Enum_ProcessPriority::Highest
//@隐藏}

//@备注   特殊进程需要特权，设置一个进程的优先级别,成功返回真，失败返回假。
//@别名   进程_置优先级(进程ID,进程级别)
BOOL X_Program_SetPriority(DWORD pid, X_Program_Enum_ProcessPriority Priority = X_Program_Enum_ProcessPriority_Default);

//@别名   进程_终止进程(进程ID)
BOOL X_Program_ProcessShutDown(DWORD pid);



//@分组}	进程操作
//@分组{  进程常量

//@备注 在当前进程中永久启用 DEP。 通过设置 X_DEFINE_PROCESS_DEP_ENABLE 为进程启用 DEP 后，无法在进程生命周期内禁用它。
//@别名 常量_进程_DEP_永久启用
#define X_DEFINE_PROCESS_DEP_ENABLE PROCESS_DEP_ENABLE
//@备注 禁用当前进程的 DEP-ATL thunk 仿真，从而阻止系统截获源自活动模板库的 NX 故障， (ATL) thunk 层。 
// .有关详细信息，请参见“https://learn.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-setprocessdeppolicy”。
//@别名 常量_进程_DEP_禁用仿真
#define X_DEFINE_PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION

//@备注   隐藏窗口并激活另一个窗口
//@别名   常量_进程_显示方式_隐藏窗口
#define  X_DEFINE_PROCESS_SW_HIDE SW_HIDE
//@备注   激活并显示窗口。 如果窗口最小化或最大化，系统会将其还原到其原始大小和位置。 首次显示窗口时，应用程序应指定此标志。
//@别名   常量_进程_显示方式_普通激活
#define  X_DEFINE_PROCESS_SW_SHOWNORMAL SW_SHOWNORMAL
//@备注   激活窗口并将其显示为最小化窗口。
//@别名   常量_进程_显示方式_最小化激活
#define  X_DEFINE_PROCESS_SW_SHOWMINIMIZED SW_SHOWMINIMIZED
//@备注   激活窗口并显示最大化的窗口。
//@别名   常量_进程_显示方式_最大化激活
#define  X_DEFINE_PROCESS_SW_SHOWMAXIMIZED SW_SHOWMAXIMIZED
//@备注   在其最近的大小和位置显示一个窗口。 此值类似于 SW_SHOWNORMAL，但窗口未激活。
//@别名   常量_进程_显示方式_普通不激活
#define  X_DEFINE_PROCESS_SW_SHOWNOACTIVATE SW_SHOWNOACTIVATE
//@备注   最小化指定的窗口，并按 Z 顺序激活下一个顶级窗口。
//@别名   常量_进程_显示方式_最小化不激活
#define  X_DEFINE_PROCESS_SW_MINIMIZE SW_MINIMIZE


//@分组}



//@分组{  线程操作

//@别名   线程许可证
#define CRITICALSECTION CRITICAL_SECTION

//@别名   线程_创建线程(传入的子程序,传入的参数,线程ID)
HANDLE X_Thread_CreateThread (LPVOID lpStartAddress,DWORD lpParameter, UINT& lpThreadId);

//@别名   线程_关闭句柄(线程句柄)
bool X_Thread_CloseHandle(HANDLE handle);

//@别名   线程_打开(线程ID)
HANDLE X_Thread_OpenThread(int ThreadId);

//@备注   GetCurrentThreadId,获取当前线程一个唯一的线程标识符
//@别名   线程_取自线程ID()
int X_Thread_GetCurrentThreadId();

//@备注   GetCurrentThread,获取当前线程的一个伪句柄
//@别名   线程_取自线程句柄()
HANDLE X_Thread_GetCurrentThread();

//@备注   有时执行线程的时候，会自动关闭，此时，可以在多线程的程序里创建COM对象前先初始化，一个线程只能调用一次
//@别名   线程_初始化COM库()
void X_Thread_COMINIT();

//@备注   取消COM库的初始化，如果你在线程头部加入了 线程_初始化COM库 请在尾部加入此命令
//@别名   线程_取消COM库()
void X_Thread_COMUNINIT();

//@备注   成功返回指定窗口的线程ID
//@别名   线程_取ID()
int X_Thread_GetID(HWND hwnd);

//@备注   强制终止正在运行的线程,成功返回真,失败返回假.
//@别名   线程_销毁()
bool X_Thread_Destroy (HANDLE handle);

//@备注   创建并返回一个进入许可证数值，此许可证值用作进入程序中的指定许可代码区，以避免多线程冲突
//@别名   线程_创建进入许可证()
CRITICALSECTION X_Thread_CriticalSection ();

//@备注   删除由"创建进入许可证"命令所创建返回的进入许可证(该命令会在本类被销毁时自动被调用)
//@别名   线程_删除许可证()
void X_Thread_DelSection (CRITICALSECTION &SECTION);

//@备注   根据已经创建的许可证进入指定许可代码区，在此线程未退出之前，其它线程如要通过同一个进入许可证进入该许可代码区则必须先等待此线程退出许可代码区，从而保证了指定许可代码区在任何时候都只能有一条线程进入并执行
//@别名   线程_进入许可区()
void X_Thread_EnterCriticalSection(CRITICALSECTION &SECTION);

//@备注   指示当前线程将退出许可代码区，并允许其它使用同一进入许可证的线程进入此许可代码区
//@别名   线程_退出许可区()
void X_Thread_LeaveCriticalSection(CRITICALSECTION &SECTION);


//@分组}  线程操作


#endif //XL_XEXPAND_PROGRAM_H
