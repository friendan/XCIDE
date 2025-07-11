// 这是对 64 位的 version.dll 的劫持源码  南小鱼 QQ128492656

#嵌入代码


#include <windows.h>
#include <Shlwapi.h>
#pragma comment( lib, "Shlwapi.lib")

#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=AheadLib_GetFileVersionInfoA,@1")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=AheadLib_GetFileVersionInfoByHandle,@2")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=AheadLib_GetFileVersionInfoExA,@3")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=AheadLib_GetFileVersionInfoExW,@4")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=AheadLib_GetFileVersionInfoSizeA,@5")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=AheadLib_GetFileVersionInfoSizeExA,@6")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=AheadLib_GetFileVersionInfoSizeExW,@7")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=AheadLib_GetFileVersionInfoSizeW,@8")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=AheadLib_GetFileVersionInfoW,@9")
#pragma comment(linker, "/EXPORT:VerFindFileA=AheadLib_VerFindFileA,@10")
#pragma comment(linker, "/EXPORT:VerFindFileW=AheadLib_VerFindFileW,@11")
#pragma comment(linker, "/EXPORT:VerInstallFileA=AheadLib_VerInstallFileA,@12")
#pragma comment(linker, "/EXPORT:VerInstallFileW=AheadLib_VerInstallFileW,@13")
#pragma comment(linker, "/EXPORT:VerLanguageNameA=KERNEL32.VerLanguageNameA,@14")
#pragma comment(linker, "/EXPORT:VerLanguageNameW=KERNEL32.VerLanguageNameW,@15")
#pragma comment(linker, "/EXPORT:VerQueryValueA=AheadLib_VerQueryValueA,@16")
#pragma comment(linker, "/EXPORT:VerQueryValueW=AheadLib_VerQueryValueW,@17")


extern "C" {
 PVOID pfnAheadLib_GetFileVersionInfoA;
 PVOID pfnAheadLib_GetFileVersionInfoByHandle;
 PVOID pfnAheadLib_GetFileVersionInfoExA;
 PVOID pfnAheadLib_GetFileVersionInfoExW;
 PVOID pfnAheadLib_GetFileVersionInfoSizeA;
 PVOID pfnAheadLib_GetFileVersionInfoSizeExA;
 PVOID pfnAheadLib_GetFileVersionInfoSizeExW;
 PVOID pfnAheadLib_GetFileVersionInfoSizeW;
 PVOID pfnAheadLib_GetFileVersionInfoW;
 PVOID pfnAheadLib_VerFindFileA;
 PVOID pfnAheadLib_VerFindFileW;
 PVOID pfnAheadLib_VerInstallFileA;
 PVOID pfnAheadLib_VerInstallFileW;
 PVOID pfnAheadLib_VerQueryValueA;
 PVOID pfnAheadLib_VerQueryValueW;
 void AheadLib_GetFileVersionInfoA(void);
 void AheadLib_GetFileVersionInfoByHandle(void);
 void AheadLib_GetFileVersionInfoExA(void);
 void AheadLib_GetFileVersionInfoExW(void);
 void AheadLib_GetFileVersionInfoSizeA(void);
 void AheadLib_GetFileVersionInfoSizeExA(void);
 void AheadLib_GetFileVersionInfoSizeExW(void);
 void AheadLib_GetFileVersionInfoSizeW(void);
 void AheadLib_GetFileVersionInfoW(void);
 void AheadLib_VerFindFileA(void);
 void AheadLib_VerFindFileW(void);
 void AheadLib_VerInstallFileA(void);
 void AheadLib_VerInstallFileW(void);
 void AheadLib_VerQueryValueA(void);
 void AheadLib_VerQueryValueW(void);
};

static HMODULE	g_OldModule = NULL;

// 加载原始模块
__inline BOOL WINAPI Load()
{
	TCHAR tzPath[MAX_PATH];
	TCHAR tzTemp[MAX_PATH * 2];
	lstrcat(tzPath,TEXT(".\\version_ORG.dll")); // 先判断是否存在"dll名称+_ORG.dll"
	if (-1 == GetFileAttributes(tzPath))
	{
	GetSystemDirectory(tzPath, MAX_PATH); // 这里是否从系统目录加载或者当前目录，自行修改
	lstrcat(tzPath, TEXT("\\version.dll"));
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
	if(NULL == (pfnAheadLib_GetFileVersionInfoA = GetAddress("GetFileVersionInfoA")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoByHandle = GetAddress("GetFileVersionInfoByHandle")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoExA = GetAddress("GetFileVersionInfoExA")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoExW = GetAddress("GetFileVersionInfoExW")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoSizeA = GetAddress("GetFileVersionInfoSizeA")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoSizeExA = GetAddress("GetFileVersionInfoSizeExA")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoSizeExW = GetAddress("GetFileVersionInfoSizeExW")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoSizeW = GetAddress("GetFileVersionInfoSizeW")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoW = GetAddress("GetFileVersionInfoW")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerFindFileA = GetAddress("VerFindFileA")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerFindFileW = GetAddress("VerFindFileW")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerInstallFileA = GetAddress("VerInstallFileA")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerInstallFileW = GetAddress("VerInstallFileW")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerQueryValueA = GetAddress("VerQueryValueA")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerQueryValueW = GetAddress("VerQueryValueW")))
		return FALSE;
	return TRUE;
}






#嵌入代码_结束

函数 整型 入口函数_动态库()

	如果 DLL_进程附加 == 被调用原因
		#嵌入代码
		// 这是对 64 位的 version.dll 的劫持源码  南小鱼 QQ128492656
		DisableThreadLibraryCalls(模块句柄);
		Load() && Init();
		#嵌入代码_结束
		//这里就可以判断进程名,并启动线程处理自己的代码了

	否则 DLL_线程附加 == 被调用原因
		调试输出("DLL_线程附加")
	否则 DLL_线程分离 == 被调用原因
		调试输出("DLL_线程分离")
	否则 DLL_进程分离 == 被调用原因
		#嵌入代码
		// 这是对 64 位的 version.dll 的劫持源码  南小鱼 QQ128492656
		Free();
		#嵌入代码_结束

	返回 真 //成功返回真


