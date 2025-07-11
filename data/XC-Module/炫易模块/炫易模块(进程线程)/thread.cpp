//
// Created by Huiyi on 2021/5/27.
//
#include "module_e_ProcessThread.h"

//创建线程
HANDLE X_Thread_CreateThread (LPVOID lpStartAddress,DWORD lpParameter,UINT& lpThreadId){
    DWORD resid = lpThreadId;
    HANDLE rehed =  CreateThread (NULL,NULL,(LPTHREAD_START_ROUTINE)lpStartAddress,(LPVOID)((vint)lpParameter),NULL,&resid);
    lpThreadId = resid;
    return rehed;
}

//线程关闭句柄
bool X_Thread_CloseHandle(HANDLE handle){
    return CloseHandle(handle)==TRUE;
}

//线程打开
HANDLE X_Thread_OpenThread(int ThreadId){
    return OpenThread (2032639, FALSE, ThreadId);
}

//取自线程ID
int X_Thread_GetCurrentThreadId(){
    return GetCurrentThreadId();
}

//线程_取自线程句柄
HANDLE X_Thread_GetCurrentThread(){
    return GetCurrentThread();
}

//线程_初始化COM库
void X_Thread_COMINIT(){
    CoInitialize(NULL);
}

//线程_取消COM库
void X_Thread_COMUNINIT(){
    CoUninitialize();
}

//线程_取ID
int X_Thread_GetID(HWND hwnd){
    return GetWindowThreadProcessId(hwnd,NULL);
}

//线程_销毁
bool X_Thread_Destroy (HANDLE handle){
    DWORD lpExitCode = 0;
    GetExitCodeThread(handle,&lpExitCode);
    return TerminateThread(handle,lpExitCode)==TRUE;
}

//线程_创建进入许可证
CRITICALSECTION X_Thread_CriticalSection (){
    CRITICALSECTION cs;
    InitializeCriticalSection(&cs);
    return cs;
}

//线程_删除许可证
void X_Thread_DelSection (CRITICALSECTION &SECTION){
    DeleteCriticalSection(&SECTION);
}

//线程_进入许可区
void X_Thread_EnterCriticalSection(CRITICALSECTION &SECTION){
    EnterCriticalSection(&SECTION);
}

//线程_退出许可区
void X_Thread_LeaveCriticalSection(CRITICALSECTION &SECTION){
    LeaveCriticalSection(&SECTION);
}


