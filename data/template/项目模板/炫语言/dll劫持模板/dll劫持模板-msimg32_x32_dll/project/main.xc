
// 这是对 32 位的 msimg32.dll 的劫持源码  南小鱼 QQ128492656
#嵌入代码

#include <windows.h>
#include <Shlwapi.h>
#pragma comment( lib, "Shlwapi.lib")

#pragma comment(linker,"/SUBSYSTEM:windows")
//#pragma comment(linker,"/Opt:nowin98")

#pragma comment(linker, "/EXPORT:vSetDdrawflag=_AheadLib_vSetDdrawflag,@1")
#pragma comment(linker, "/EXPORT:AlphaBlend=_AheadLib_AlphaBlend,@2")
#pragma comment(linker, "/EXPORT:DllInitialize=_AheadLib_DllInitialize,@3")
#pragma comment(linker, "/EXPORT:GradientFill=_AheadLib_GradientFill,@4")
#pragma comment(linker, "/EXPORT:TransparentBlt=_AheadLib_TransparentBlt,@5")
PVOID pfnAheadLib_vSetDdrawflag;
PVOID pfnAheadLib_AlphaBlend;
PVOID pfnAheadLib_DllInitialize;
PVOID pfnAheadLib_GradientFill;
PVOID pfnAheadLib_TransparentBlt;




static HMODULE	g_OldModule = NULL;

// 加载原始模块
__inline BOOL WINAPI Load()
{
	TCHAR tzPath[MAX_PATH];
	TCHAR tzTemp[MAX_PATH * 2];
	lstrcat(tzPath,TEXT(".\\msimg32_ORG.dll")); // 先判断是否存在"dll名称+_ORG.dll"
	if (-1 == GetFileAttributes(tzPath))
	{
	GetSystemDirectory(tzPath, MAX_PATH); // 这里是否从系统目录加载或者当前目录，自行修改
	lstrcat(tzPath, TEXT("\\msimg32.dll"));
	}
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
		MessageBox(NULL, tzTemp, TEXT("AheadLib"), MB_ICONSTOP);
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




 // 导出函数
EXTERN_C __declspec(naked) void __cdecl AheadLib_vSetDdrawflag(void)
{
	__asm jmp pfnAheadLib_vSetDdrawflag;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_AlphaBlend(void)
{
	__asm jmp pfnAheadLib_AlphaBlend;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_DllInitialize(void)
{
	__asm jmp pfnAheadLib_DllInitialize;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_GradientFill(void)
{
	__asm jmp pfnAheadLib_GradientFill;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_TransparentBlt(void)
{
	__asm jmp pfnAheadLib_TransparentBlt;
}


#嵌入代码_结束

正整型  主线程id = 0


函数 整型 入口函数_动态库()

	如果 DLL_进程附加 == 被调用原因
		#嵌入代码
		// 这是对 32 位的 msimg32.dll 的劫持源码  南小鱼 QQ128492656
		DisableThreadLibraryCalls(模块句柄);
		Load() && Init();
		#嵌入代码_结束
		字节集 test = {0}//初始化字节集
		test += {1, 2, 3, 4}//连续增加字节集
		调试输出(test)

		
		//这里就可以判断进程名,并启动线程处理自己的代码了
		文本型 当前执行文件全路径 = 取执行文件名()
		文本型 当前执行文件名 = 文本_取右边(当前执行文件全路径, "\\")
		如果(当前执行文件名 == "NCTrainer2Plus.exe")
			线程_创建线程(&主线程函数, 0, 主线程id)
			


	
	否则 DLL_线程附加 == 被调用原因
		调试输出("DLL_线程附加")
	否则 DLL_线程分离 == 被调用原因
		调试输出("DLL_线程分离")
	否则 DLL_进程分离 == 被调用原因
		#嵌入代码
		// 这是对 32 位的 msimg32.dll 的劫持源码  南小鱼 QQ128492656
		Free();
		#嵌入代码_结束

	返回 真 //成功返回真

函数 空类型 主线程函数(整型 参数A)
	线程_初始化COM库()
	//-----------------------
	消息框("msimg32.dll劫持成功")


	//-----------------------
	线程_取消COM库()
	返回 



