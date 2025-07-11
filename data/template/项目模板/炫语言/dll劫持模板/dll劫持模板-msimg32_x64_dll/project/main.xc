

// 这是对 64 位的 msimg32.dll 的劫持源码  南小鱼 QQ128492656

#嵌入代码
#include <windows.h>
#include <Shlwapi.h>
#pragma comment( lib, "Shlwapi.lib")

#pragma comment(linker, "/EXPORT:vSetDdrawflag=AheadLib_vSetDdrawflag,@1")
#pragma comment(linker, "/EXPORT:AlphaBlend=AheadLib_AlphaBlend,@2")
#pragma comment(linker, "/EXPORT:DllInitialize=AheadLib_DllInitialize,@3")
#pragma comment(linker, "/EXPORT:GradientFill=AheadLib_GradientFill,@4")
#pragma comment(linker, "/EXPORT:TransparentBlt=AheadLib_TransparentBlt,@5")


extern "C" {
	PVOID pfnAheadLib_vSetDdrawflag;
	PVOID pfnAheadLib_AlphaBlend;
	PVOID pfnAheadLib_DllInitialize;
	PVOID pfnAheadLib_GradientFill;
	PVOID pfnAheadLib_TransparentBlt;
	void AheadLib_vSetDdrawflag(void);
	void AheadLib_AlphaBlend(void);
	void AheadLib_DllInitialize(void);
	void AheadLib_GradientFill(void);
	void AheadLib_TransparentBlt(void);
}

static HMODULE	g_OldModule = NULL;

// 加载原始模块
__inline BOOL WINAPI Load()
{
	TCHAR tzPath[MAX_PATH];
	TCHAR tzTemp[MAX_PATH * 2];


	GetSystemDirectory(tzPath, MAX_PATH) ; // 这里是否从系统目录加载或者当前目录，自行修改
	lstrcat(tzPath, TEXT("\\msimg32.dll"));

	g_OldModule = LoadLibrary(tzPath);
	if (g_OldModule == NULL)
	{
		wsprintf(tzTemp, TEXT("无法找到模块 %s,程序无法正常运行"), tzPath);
		MessageBox(NULL, tzTemp, TEXT("AheadLib"), MB_ICONSTOP);
		}

	return (g_OldModule != NULL);
}

// 释放原始模块
__inline VOID WINAPI Free()
{
	if (g_OldModule)
	{
		FreeLibrary(g_OldModule);
		}
}
// 获取原始函数地址
FARPROC WINAPI GetAddress(PCSTR pszProcName)
{
	FARPROC fpAddress;
	CHAR szProcName[128];
	TCHAR tzTemp[MAX_PATH];

	fpAddress = GetProcAddress(g_OldModule, pszProcName);
	if (fpAddress == NULL)
	{
		if (HIWORD(pszProcName) == 0)
		{
			wsprintfA(szProcName, "%d", pszProcName);
			pszProcName = szProcName;
		}
		wsprintf(tzTemp, TEXT("无法找到函数 %S,程序无法正常运行"), pszProcName);
		//MessageBox(NULL, tzTemp, TEXT("AheadLib"), MB_ICONSTOP);
		ExitProcess(-2);
		}
	return fpAddress;
}

// 初始化获取原函数地址
BOOL WINAPI Init()
{
	if(NULL == (pfnAheadLib_vSetDdrawflag = GetAddress("vSetDdrawflag")))
		return FALSE;
	if(NULL == (pfnAheadLib_AlphaBlend = GetAddress("AlphaBlend")))
		return FALSE;
	if(NULL == (pfnAheadLib_DllInitialize = GetAddress("DllInitialize")))
		return FALSE;
	if(NULL == (pfnAheadLib_GradientFill = GetAddress("GradientFill")))
		return FALSE;
	if(NULL == (pfnAheadLib_TransparentBlt = GetAddress("TransparentBlt")))
		return FALSE;
	return TRUE;
}

#嵌入代码_结束

函数 整型 函数名(整型 参数A, 整型 参数B)
	调试输出(123)
	如果 1 > 0
		调试输出(23)





函数 整型 入口函数_动态库()

	如果(DLL_进程附加 == 被调用原因)
		#嵌入代码
		// 这是对 64 位的 msimg32.dll 的劫持源码  南小鱼 QQ128492656
		DisableThreadLibraryCalls(模块句柄);
		Load() && Init();
		#嵌入代码_结束
		//这里就可以判断进程名,并启动线程处理自己的代码
	否则 DLL_线程附加 == 被调用原因
		调试输出("DLL_线程附加")
	否则 DLL_线程分离 == 被调用原因
		调试输出("DLL_线程分离")
	否则 DLL_进程分离 == 被调用原因
		#嵌入代码
		// 这是对 64 位的 msimg32.dll 的劫持源码  南小鱼 QQ128492656
		Free();
		#嵌入代码_结束

	返回 真 //成功返回真
