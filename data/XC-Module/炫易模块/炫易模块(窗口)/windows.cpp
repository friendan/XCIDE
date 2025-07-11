//
// Created by Huiyi on 2021/5/26.
// update By hxznhf on 2024/12/13.
//
#include "module_e_windows.h"
#include <tlhelp32.h>

POINT GetPOINT() {
    POINT r;
    GetCursorPos(&r);
    return r;
}

HWND X_Wnd_Find(CXText className, CXText title)
{
    return FindWindowW(
        wcscmp(className.getPtr(), L"") == 0 ? NULL : className.getPtr(),
        wcscmp(title.getPtr(), L"") == 0 ? NULL : title.getPtr());
}

HWND X_Wnd_FindChild(CXText className, CXText title, HWND hWndChildAfter, HWND phWnd)
{
    return FindWindowExW(phWnd, hWndChildAfter,
        lstrcmpW(className.getPtr(), L"") == 0 ? NULL : className.getPtr(),
        lstrcmpW(title.getPtr(), L"") == 0 ? NULL : title.getPtr());
}



//窗口_按类名枚举W
int X_Wnd_EnumByClass(CXText className, CXVector<HWND>& rList) {
    rList.clear();
    HWND hwnd = FindWindowExW(0, 0, className, 0);
    while (hwnd!=0) {
        rList.add(hwnd);
        hwnd = FindWindowExW(0, hwnd, className, 0);
    }
    return rList.size();
}
//窗口_按类名枚举A
int X_Wnd_EnumByClassA(CXTextA className, CXVector<HWND>& rList) {
    rList.clear();
    HWND hwnd = FindWindowExA(0, 0, className, 0);
    while (hwnd != 0) {
        rList.add(hwnd);
        hwnd = FindWindowExA(0, hwnd, className, 0);
    }
    return rList.size();
}

BOOL CALLBACK Enum_WNDENUMPROC(HWND hwnd, LPARAM lParam) {
    CXVector<X_FORM_WINININFO>* rList = (CXVector<X_FORM_WINININFO>*)lParam;
    X_FORM_WINININFO l={0};
    l.hWnd = hwnd;
    l.ProcessID=X_Wnd_HWNDGetProcessID(hwnd);
    l.ThreadID = X_Wnd_HWNDGetThreadID(hwnd);
    l.wTitle = X_Wnd_GetTitle(hwnd);
    l.wClass = X_Wnd_GetClass(hwnd);
    rList->add(l);
    return 1;
}
//窗口_枚举
int X_Wnd_Enum(CXVector<X_FORM_WINININFO>& rList) {
    rList.clear();
    EnumWindows(&Enum_WNDENUMPROC,(LPARAM)((LPVOID) & rList));
    return rList.size();
}
BOOL CALLBACK Enum_WNDENUMPROCA(HWND hwnd, LPARAM lParam) {
    CXVector<X_FORM_WINININFOA>* rList = (CXVector<X_FORM_WINININFOA>*)lParam;
    X_FORM_WINININFOA l = { 0 };
    l.hWnd = hwnd;
    l.ProcessID = X_Wnd_HWNDGetProcessID(hwnd);
    l.ThreadID = X_Wnd_HWNDGetThreadID(hwnd);
    l.wTitle = X_Wnd_GetTitleA(hwnd);
    l.wClass = X_Wnd_GetClassA(hwnd);
    rList->add(l);
    return 1;
}
//窗口_枚举A
int X_Wnd_EnumA(CXVector<X_FORM_WINININFOA>& rList) {
    rList.clear();
    EnumWindows(&Enum_WNDENUMPROCA, (LPARAM)((LPVOID)&rList));
    return rList.size();
}

//窗口_取标题W
CXText X_Wnd_GetTitle(HWND hWnd) {
    int dwSize = GetWindowTextLengthW(hWnd);
    if (dwSize <= 0) { return L""; }
    dwSize++;
    wchar_t* szTitle = new wchar_t[dwSize];
    GetWindowTextW(hWnd, szTitle, dwSize);
    CXText r = szTitle;
    delete szTitle;
    return r;
}
//窗口_取标题A
CXTextA X_Wnd_GetTitleA(HWND hWnd) {
    int dwSize = GetWindowTextLengthA(hWnd);
    if (dwSize <= 0) { return ""; }
    dwSize++;
    char* szTitle = new char[dwSize];
    GetWindowTextA(hWnd, szTitle, dwSize);
    CXTextA r = szTitle;
    delete szTitle;
    return r;
}

//窗口_取类名W
CXText X_Wnd_GetClass(HWND hWnd) {
    DWORD dwClassName = _MAX_PATH+1;
    wchar_t* szClassName = new wchar_t[dwClassName];
    GetClassNameW(hWnd, szClassName, dwClassName);
    CXText r = szClassName;
    delete szClassName;
    return r;
}
//窗口_取类名A
CXTextA X_Wnd_GetClassA(HWND hWnd) {
    DWORD dwClassName = _MAX_PATH + 1;
    char* szClassName = new char[dwClassName];
    GetClassNameA(hWnd, szClassName, dwClassName);
    CXTextA r = szClassName;
    delete szClassName;
    return r;
}

//窗口_按钮解除禁止
BOOL X_Wnd_ButtonProhibited(HWND hObj,BOOL bEnabled) {
    return EnableWindow(hObj, bEnabled)>0;
}

//窗口_撤销窗口热键
BOOL X_Wnd_RevokeHotKey(HWND hWnd,int keyCode) {
    HANDLE hProc = GetPropA(hWnd, "Comet_HotKeyProc");
    if (hWnd == NULL || keyCode == NULL) { return false; }
    SetWindowLongA(hWnd, -4, (vint)hProc);
    char VirtKey[10]={'\0'};
    _itoa_s(keyCode, VirtKey,10,10);
    CXTextA PropName ="HotKey" + keyCode;
    RemovePropA(hWnd, PropName +"_Mod");
    RemovePropA(hWnd, PropName +"_VirtKey");
    RemovePropA(hWnd, PropName +"_Proc");
    RemovePropA(hWnd, PropName +"_Type");
    RemovePropA(hWnd, PropName +"_Char");
    RemovePropA(hWnd, "Comet_HotKeyProc");
    return true;
}

//窗口_是否存在W
HWND X_Wnd_WindowExists(CXText win) {
    HWND hwnd = (HWND)_wtoi64(win);
    WINDOWINFO info;
    info.cbSize=sizeof(WINDOWINFO);
    if (GetWindowInfo(hwnd, &info) > 0) {
        return hwnd;
    }
    else {
        CXVector<X_FORM_WINININFO> wins;
        int n = X_Wnd_Enum(wins);
        for (int i = 0; i < n; i++) {
            if (wins[i].wTitle.find(win)!=-1) {
                hwnd = wins[i].hWnd;
                break;
            }
        }
    }
    return hwnd;
}
//窗口_是否存在A
HWND X_Wnd_WindowExistsA(CXTextA win) {
    HWND hwnd = (HWND)_atoi64(win);
    WINDOWINFO info;
    info.cbSize = sizeof(WINDOWINFO);
    if (GetWindowInfo(hwnd, &info) > 0) {
        return hwnd;
    }
    else {
        CXVector<X_FORM_WINININFOA> wins;
        int n = X_Wnd_EnumA(wins);
        for (int i = 0; i < n; i++) {
            if (wins[i].wTitle.find(win) != -1) {
                hwnd = wins[i].hWnd;
                break;
            }
        }
    }
    return hwnd;
}

//窗口_是否存在_句柄
BOOL X_Wnd_WindowExistsHWND(HWND hWnd) {
    WINDOWINFO info;
    info.cbSize = sizeof(WINDOWINFO);
    return GetWindowInfo(hWnd, &info) > 0?true:false;
}

//窗口_重画
BOOL X_Wnd_Repaint(HWND hWnd,BOOL EraseBg){
    return InvalidateRect(hWnd,NULL,EraseBg)>0;
}

//窗口_隐藏任务按钮
void X_Wnd_HideTaskButton(HWND hWnd){
    SetWindowLongW(hWnd,-8,(vint)GetDesktopWindow());
}

//窗口_是否响应
BOOL X_Wnd_IfNormal(HWND hWnd){
    return SendMessageTimeoutW(hWnd,0,0,0,SMTO_ABORTIFHUNG,128,0)>0;
}

//窗口_取光标坐标
BOOL X_Wnd_GetCaretPos (POINT& Pos) {
    return GetCaretPos(&Pos)>0;
}

//窗口_取桌面句柄A
HWND X_Wnd_GetDesktopHWndA() {
    return FindWindowA("Progman", "Program Manager");
}

//窗口_取桌面句柄W
HWND X_Wnd_GetDesktopHWndW() {
    return FindWindowW(L"Progman", L"Program Manager");
}

//窗口_置父
HWND X_Wnd_SetParent(HWND hWndChild,HWND hWndParent){
    return SetParent(hWndChild,hWndParent);
}

//窗口_置位置和大小
BOOL X_Wnd_SetPosAndSize(HWND hWnd,int Left,int Top,int NewWidth,int NewHigh){
    RECT lpRect;
    GetWindowRect (hWnd, &lpRect);
    if (Left==0){
        Left = lpRect.left;
    }
    if (Top == 0){
        Top = lpRect.top;
    }
    if (NewWidth == 0){
        NewWidth = lpRect.right - lpRect.left;
    }
    if (NewHigh == 0){
        NewHigh = lpRect.bottom - lpRect.top;
    }
    return MoveWindow(hWnd,Left,Top,NewWidth,NewHigh,true)==TRUE;
}

BOOL EnumWindowsProc (HWND hwnd,void*  lParam){
    HWND defview = FindWindowExA (hwnd, NULL, "SHELLDLL_DefView", NULL);
    if(!defview){
        (*(HWND*)lParam) = FindWindowExA (NULL, hwnd, "WorkerW", NULL);
    }
    return true;
}

HWND GetWorkerW(){
    PDWORD_PTR result=0;
    HWND lParam=0;
    HWND hDistop = FindWindowA("Progman", "\0");
    SendMessageTimeoutA (hDistop, 1324, 0, 0, SMTO_NORMAL, 1000, result);
    EnumWindows ((WNDENUMPROC)EnumWindowsProc, (vint)&lParam);
    ShowWindow (lParam, SW_HIDE);
    return hDistop;
}

//窗口_嵌入桌面
HWND X_Wnd_EmbedOnDesktop (HWND hWnd){
    HWND newwnd = SetParent(hWnd,GetWorkerW());
    X_Wnd_SetPosAndSize(hWnd);
    return newwnd;
}

//窗口_窗口句柄取进程ID
DWORD X_Wnd_HWNDGetProcessID(HWND hWnd) {
    DWORD dwProcessId;
    GetWindowThreadProcessId(hWnd, &dwProcessId);
    return dwProcessId;
}

//窗口_窗口句柄取线程ID
DWORD X_Wnd_HWNDGetThreadID(HWND hWnd) {
    DWORD dwProcessId;
    return GetWindowThreadProcessId(hWnd, &dwProcessId);
}

//窗口_枚举子窗口W
int X_Wnd_EnumSon(HWND hWnd,CXVector<HWND>&rList,CXText sClassName) {
    const wchar_t* c = lstrcmpW(sClassName.get(),L"")==0?NULL: sClassName;
    rList.clear();
    HWND lh = FindWindowExW(hWnd, 0, c, 0);
    while (lh!=NULL) {
        rList.add(lh);
        lh = FindWindowExW(hWnd, lh, c, 0);
    }
    return rList.size();
}
//窗口_枚举子窗口A
int X_Wnd_EnumSonA(HWND hWnd, CXVector<HWND>& rList, CXTextA sClassName) {
    const char* c = strcmp(sClassName.get(), "") == 0 ? NULL : sClassName;
    rList.clear();
    HWND lh = FindWindowExA(hWnd, 0, c, 0);
    while (lh != NULL) {
        rList.add(lh);
        lh = FindWindowExA(hWnd, lh, c, 0);
    }
    return rList.size();
}

//窗口_等待出现
HWND X_Wnd_WaitAppear(CXText title, CXText str, int timeout) {
    HWND rh = 0;
    DWORD ltim = timeout>0? timeout: 1000000 * 1000;
    DWORD tc=GetTickCount();
    while (GetTickCount()-tc< ltim) {
        HWND hwnd = X_Wnd_WindowExists(title);
        if (hwnd!=0) {
            if (str.size()>0) {
                CXVector<HWND> cl;
                int cnum=X_Wnd_EnumSon(hwnd,cl);
                for (int i = 0; i < cnum; i++) {
                    CXText lst = X_Wnd_GetTitle(cl[i]);
                    if (lst.find(str) != std::wstring::npos) {
                        rh = cl[i];
                        break;
                    }
                }
            }
            else {
                rh = hwnd;
            }
			xcl_doMessage();
            //X_System_DoEvents();
        }
        if (rh!=NULL) {
            break;
        }
        Sleep(250);
    }
    return rh;
}
//窗口_等待出现A
HWND X_Wnd_WaitAppearA(CXTextA title, CXTextA str, int timeout) {
    HWND rh = 0;
    DWORD ltim = timeout > 0 ? timeout : 1000000 * 1000;
    DWORD tc = GetTickCount();
    while (GetTickCount() - tc < ltim) {
        HWND hwnd = X_Wnd_WindowExistsA(title);
        if (hwnd != 0) {
            if (str.size() > 0) {
                CXVector<HWND> cl;
                int cnum = X_Wnd_EnumSonA(hwnd, cl);
                for (int i = 0; i < cnum; i++) {
                    CXTextA lst = X_Wnd_GetTitleA(cl[i]);
                    if (lst.find(str) != std::string::npos) {
                        rh = cl[i];
                        break;
                    }
                }
            }
            else {
                rh = hwnd;
            }
			xcl_doMessage(); //X_System_DoEvents();
        }
        if (rh != NULL) {
            break;
        }
		Sleep(250);
    }
    return rh;
}

//窗口_取句柄W
HWND X_Wnd_GetHWND(HWND hWndf,HWND hWnds,CXText sClassName, CXText sTitle){
    return FindWindowExW(hWndf, hWnds,
        wcscmp(sClassName.getPtr(), L"") == 0 ? NULL : sClassName.getPtr(),
        wcscmp(sTitle.getPtr(), L"") == 0 ? NULL : sTitle.getPtr());
}
//窗口_取句柄A
HWND X_Wnd_GetHWNDA(HWND hWndf, HWND hWnds, CXTextA sClassName, CXTextA sTitle) {
    return FindWindowExA(hWndf, hWnds,
        strcmp(sClassName.getPtr(), "") == 0 ? NULL : sClassName.getPtr(),
        strcmp(sTitle.getPtr(), "") == 0 ? NULL : sTitle.getPtr());
}

//窗口_发送拖放消息
BOOL X_Wnd_SendFileDragDropMessageA(HWND hWnd, CXTextA strFilePath) {
    if (hWnd==NULL
        || strFilePath.size() < 1 ){
        return false;
    }
    DWORD dwBufSize = sizeof(DROPFILES) + strFilePath.size() + 1;
    BYTE *pBuf = new BYTE[dwBufSize];
    if (pBuf==0) { return false; }
    memset(pBuf, 0, dwBufSize);
    DROPFILES* pDrop = (DROPFILES*)pBuf;
    pDrop->pFiles = sizeof(DROPFILES);
    strcpy_s((char*)(pBuf + sizeof(DROPFILES)), strFilePath.size()+1, strFilePath);
    DWORD dwProcessId;
    GetWindowThreadProcessId(hWnd, &dwProcessId);
    if (dwProcessId == NULL) { delete[] pBuf; return false; }
    HANDLE hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, dwProcessId);
    if (hProcess == NULL) { delete[] pBuf; return false; }
    LPSTR pszRemote = (LPSTR)VirtualAllocEx(hProcess, NULL, dwBufSize, MEM_COMMIT, PAGE_READWRITE);
    if (pszRemote == NULL) { delete[] pBuf; return false; }
    if (WriteProcessMemory(hProcess, pszRemote, pBuf, dwBufSize, 0)) {
        SendMessageA(hWnd, WM_DROPFILES, (WPARAM)pszRemote, NULL);
    }
    if(pszRemote){ VirtualFreeEx(hProcess, pszRemote, 0, MEM_RELEASE); }
    if(hProcess){ CloseHandle(hProcess); }
    if (pBuf) { delete[] pBuf; }
    return true;
}
//窗口_发送拖放消息
BOOL X_Wnd_SendFileDragDropMessage(HWND hWnd, CXText strFilePath) {
    return X_Wnd_SendFileDragDropMessageA(hWnd,W2A(strFilePath));
}

//窗口_复制到剪贴板
BOOL X_Wnd_SendCopyMessage(HWND hWnd) {
    return SendMessageA(hWnd, WM_COPY, 0, 0)>0;
}

//窗口_更换鼠标指针W
BOOL X_Wnd_ReplaceMousePointer(HWND hWnd,CXText sCurPath, LPWSTR iPointer) {
    if (!hWnd) { return FALSE; }
    HCURSOR lcur;
    if(lstrcmpW(sCurPath,L"")!=0 ) {
        lcur = LoadCursorFromFileW(sCurPath);
    }
    else {
        lcur = LoadCursorW(0, (LPCWSTR)iPointer);
    }
    CXVector<HWND> sons;
    X_Wnd_EnumSon(hWnd, sons);
    for (int i = 0; i < sons.size(); i++) {
        SetClassLongPtrW(sons[i], -12, (vint)lcur);
    }
    return SetClassLongPtrW(hWnd, -12, (vint)lcur);
}
//窗口_更换鼠标指针A
BOOL X_Wnd_ReplaceMousePointerA(HWND hWnd, CXTextA sCurPath, LPWSTR iPointer) {
    if (!hWnd) { return FALSE; }
    HCURSOR lcur;
    if (strcmp(sCurPath, "") != 0) {
        lcur = LoadCursorFromFileA(sCurPath);
    }
    else {
        lcur = LoadCursorW(0, (LPCWSTR)iPointer);
    }
    CXVector<HWND> sons;
    X_Wnd_EnumSon(hWnd, sons);
    for (int i = 0; i < sons.size(); i++) {
        SetClassLongPtrW(sons[i], -12, (vint)lcur);
    }
    return SetClassLongPtrW(hWnd, -12, (vint)lcur);
}

//窗口_挂起
DWORD X_Wnd_Suspend(HWND hWnd,BOOL bSuspend) {
    DWORD Tid = GetWindowThreadProcessId(hWnd, 0);
    if (Tid != NULL) {
        HANDLE hThread = OpenThread(2032639, 0, Tid);
        if (hThread) {
            DWORD bresult;
            if(bSuspend){
                bresult = SuspendThread(hThread);
            }
            else {
                bresult = ResumeThread(hThread);
            }
            CloseHandle(hThread);
            return bresult;
        }
    }
    return -1;
}

//窗口_关闭
void X_Wnd_Close(HWND hWnd) {
    PostMessageW(hWnd, WM_CLOSE, NULL, NULL); 
}

//@别名   窗口_画矩形(窗口句柄,矩形粗细,矩形颜色,是否闪烁)
void X_Wnd_DrawRectangle(HWND hWnd, int iThickness, DWORD rColor , BOOL bTwinkle ) {
    HWND hScreen = GetDesktopWindow();  // 取得桌面句柄
    HDC hWindowDC = GetWindowDC(hScreen);  // 取得桌面设备场景
    int oldModel = SetROP2(hWindowDC, 10);  // 10:R2_NOTXORPEN
    RECT hRect;
    GetWindowRect(hWnd, &hRect);  // 获得窗口矩形
    hRect.left = hRect.left<0?0: hRect.left;
    hRect.top = hRect.top <0?0: hRect.top;
    HPEN hPen = CreatePen(0, iThickness, rColor);  // 建立新画笔,载入DeskDC。取颜色值 (237, 15, 40)
    HGDIOBJ oldPen = SelectObject(hWindowDC, hPen);
    Rectangle(hWindowDC, hRect.left, hRect.top, hRect.right, hRect.bottom);  // 在窗口周围画矩形
    if (bTwinkle) {
		Sleep(100);
        Rectangle(hWindowDC, hRect.left, hRect.top, hRect.right, hRect.bottom);  // 刷新画矩形
        SetROP2(hWindowDC, oldModel);
    }
    SelectObject(hWindowDC, oldPen);
    DeleteObject(hPen);
    ReleaseDC(hScreen, hWindowDC);
}

//窗口_激活
HWND X_Wnd_Activation(HWND hWnd) {
    DWORD tid = GetCurrentThreadId();
    DWORD tpid = GetWindowThreadProcessId(hWnd, 0);
    AttachThreadInput(tpid, tid, true);
    HWND rust = SetActiveWindow(hWnd);
    AttachThreadInput(tpid, tid, false);
    return rust;
}

HHOOK mHook=NULL;
LPVOID mHookBack = NULL;
typedef void (hookBackFunc)(int,int,BOOL);
LRESULT HotkeysCallback (int code, WPARAM wParam, LPARAM lParam) {

    if (code >= 0) {
        KBDLLHOOKSTRUCT* pKbStruct = (KBDLLHOOKSTRUCT*)lParam; //获取指针
        BOOL isExtendedKey = (pKbStruct->flags & LLKHF_EXTENDED) != 0;
        if ((wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) && mHookBack != nullptr)
        {
            ((hookBackFunc*)mHookBack)(pKbStruct->vkCode, isExtendedKey, TRUE);
        }
        else if (wParam == WM_KEYUP && mHookBack != nullptr)
        {
            ((hookBackFunc*)mHookBack)(pKbStruct->vkCode, isExtendedKey, FALSE);
        }
    }
    return CallNextHookEx(mHook, code, wParam, lParam);
}
//窗口_监视热键_注册
void X_Wnd_WindowHotkeys_register(LPVOID callback) {
    if (mHook) {  return; }
    mHookBack = callback;
    mHook = SetWindowsHookExA(13, (HOOKPROC)HotkeysCallback, GetModuleHandleA(0), 0);
}

//窗口_监视热键_卸载
void X_Wnd_WindowHotkeys_uninstall() {
    UnhookWindowsHookEx(mHook);
    mHook = NULL;
}

typedef void (HandleMsgProcBackFunc)(BOOL);
LPVOID m_HandleMsgProc;
WNDPROC m_oldMsgProc;
LRESULT HandleMsgProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam) {
    if(uMsg== WM_WTSSESSION_CHANGE){
        if(m_HandleMsgProc!=nullptr){
            if(wParam ==WTS_SESSION_LOCK){//锁屏
                ((HandleMsgProcBackFunc*)m_HandleMsgProc)(TRUE);
            }if (wParam == WTS_SESSION_UNLOCK) {//取消锁屏
                ((HandleMsgProcBackFunc*)m_HandleMsgProc)(FALSE);
            }
        }
    }
    return CallWindowProcA(m_oldMsgProc,hWnd, uMsg, wParam, lParam);
}
//@别名   窗口_监视锁屏_注册
BOOL X_Wnd_MonitoringLockScreen_register(HWND hWnd, LPVOID callback) {
    if (m_HandleMsgProc != nullptr) { return FALSE; }
    BOOL result = WTSRegisterSessionNotification(hWnd, NOTIFY_FOR_THIS_SESSION);
    if (result<1){
        xcl_log("安装通知失败");
    }
    else {
        m_HandleMsgProc = callback;
        m_oldMsgProc = (WNDPROC)SetWindowLongPtr(hWnd, -4, (vint)HandleMsgProc);
    }
    return result>0;
}
//@别名   窗口_监视锁屏_卸载()
BOOL X_Wnd_MonitoringLockScreen_uninstall(HWND hWnd) {
    SetWindowLongPtr(hWnd, -4, (vint)m_oldMsgProc);
    m_HandleMsgProc = NULL;
    return WTSUnRegisterSessionNotification(hWnd)>0;
}

//@别名   窗口_将焦点切换到指定的窗口(要激活的窗口句柄,是否使最小化的窗口还原)
void X_Wnd_SwitchToThisWindow(HWND hwnd, BOOL fUnknown) {
    SwitchToThisWindow(hwnd, fUnknown);
}

//窗口_禁止关闭
BOOL X_Wnd_WindowBanClose(HWND hwnd, BOOL bBanClose) {
    HMENU hSmu = GetSystemMenu(hwnd, 0);
    if (!hSmu) {
        return false;
    }
    if (bBanClose) {
        EnableMenuItem(hSmu, 6, 1025);  // 禁止关闭
    }
    else {
        EnableMenuItem(hSmu, 6, 1024);// 允许关闭
    }
    RECT wRect;
    if(!GetWindowRect(hwnd,&wRect)){
        return false;
    }
    return RedrawWindow(0, &wRect, 0, 1 | 128 | 256) > 0;
}

//窗口_禁止截图
BOOL X_Wnd_WindowBanScreen(HWND hwnd, BOOL bBan){
    DWORD dwAffinity = WDA_NONE;
    if (bBan) {
        dwAffinity = WDA_MONITOR;
    }
    return SetWindowDisplayAffinity(hwnd, dwAffinity)>0;
}

//窗口_句柄取进程路径W
CXText X_Wnd_HandleGetProcessPath(HWND hWnd){
    HANDLE hProcess;
    CXText r;
    if(hWnd !=0){
        DWORD dwProcessId;
        GetWindowThreadProcessId(hWnd, &dwProcessId);
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, 0, dwProcessId);
    }
    else {
        hProcess = GetCurrentProcess();
    }
    if (hProcess!=0) {
        wchar_t szPath[_MAX_PATH] = { 0 };
        DWORD dwSize = GetProcessImageFileNameW(hProcess, szPath, _MAX_PATH);
        CloseHandle(hProcess);
        r = szPath;
        CXText lPath = r.substr(0, dwSize+1);
        wchar_t szDrive[] = { L'@',L':' ,L'\0'};
        wchar_t szDevName[_MAX_PATH]={0};
        for (int i = 0; i < 26; i++) {
            szDrive[0]++;
            dwSize = QueryDosDeviceW(szDrive, szDevName, MAX_PATH);
            if (dwSize > 0) {
                if (lstrcmpW(r.substr(0, lstrlenW(szDevName)), szDevName) == 0) {
                    lPath = szDrive;
                    lPath+= L"\\";
                    UINT dn = lstrlenW(szDevName);
                    lPath += r.substr(dn+1, r.size()- dn);
                    r = lPath;
                    break;
                }
            }
            
        }
    }//\Device\HarddiskVolume8
    return r;
}
//窗口_句柄取进程路径A
CXTextA X_Wnd_HandleGetProcessPathA(HWND hWnd) {
    HANDLE hProcess;
    CXTextA r;
    if (hWnd != 0) {
        DWORD dwProcessId;
        GetWindowThreadProcessId(hWnd, &dwProcessId);
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, dwProcessId);
    }
    else {
        hProcess = GetCurrentProcess();
    }
    if (hProcess != 0) {
        char szPath[_MAX_PATH] = { 0 };
        DWORD dwSize = GetProcessImageFileNameA(hProcess, szPath, _MAX_PATH);
        CloseHandle(hProcess);
        r = szPath;
        CXTextA lPath = r.substr(0, dwSize + 1);
        char szDrive[] = { '@',':' ,'\0' };
        char szDevName[_MAX_PATH] = { 0 };
        for (int i = 0; i < 26; i++) {
            szDrive[0]++;
            dwSize = QueryDosDeviceA(szDrive, szDevName, MAX_PATH);
            if (dwSize > 0) {
                if (strcmp(r.substr(0, strlen(szDevName)), szDevName) == 0) {
                    lPath = szDrive;
                    lPath += "\\";
                    UINT dn = strlen(szDevName);
                    lPath += r.substr(dn + 1, r.size() - dn);
                    r = lPath;
                    break;
                }
            }

        }
    }//\Device\HarddiskVolume8
    return r;
}

//窗口_句柄取进程名W
CXText X_Wnd_GetProcessByHWND(HWND hwnd) {
    DWORD ProcessId;
    GetWindowThreadProcessId(hwnd, &ProcessId);

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    CXText r;
    if (hProcessSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W pe32 = { 0 };
        pe32.dwSize = sizeof(pe32);
        BOOL b = Process32NextW(hProcessSnap, &pe32);
        while (b > 0) {
            if (pe32.th32ProcessID == ProcessId) {
                r = pe32.szExeFile;
                break;
            }
            b = Process32NextW(hProcessSnap, &pe32);
        }
        CloseHandle(hProcessSnap);
    }
    return r;


}
//窗口_句柄取进程名A
CXTextA X_Wnd_GetProcessByHWNDA(HWND hwnd) {
    DWORD ProcessId;
    GetWindowThreadProcessId(hwnd, &ProcessId);
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    CXTextA r;
    if (hProcessSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe32 = { 0 };
        pe32.dwSize = sizeof(pe32);
        BOOL b = Process32Next(hProcessSnap, &pe32);
        while (b > 0) {
            if (pe32.th32ProcessID == ProcessId) {
                r = W2A(pe32.szExeFile);
                break;
            }
            b = Process32NextW(hProcessSnap, &pe32);
        }
        CloseHandle(hProcessSnap);
    }
    return r;
    //return X_Process_GetNameByIDA(ProcessId);
}

//窗口_句柄取线程ID
DWORD X_Wnd_GetProcessIdByHWND(HWND hwnd) {
    DWORD ProcessId;
    return GetWindowThreadProcessId(hwnd, &ProcessId);
}

//窗口_句柄取线程句柄
HANDLE X_Wnd_GetThreadHandleByHWND(HWND hwnd) {
    return OpenThread(2032639, 0, GetWindowThreadProcessId(hwnd, NULL));
}

//窗口_句柄是否有效
BOOL X_Wnd_HWNDIsValid(HWND hwnd){
    return IsWindow(hwnd)>0;
}

//窗口_控件ID取句柄
HWND X_Wnd_GetControlHWNDByID(HWND hWnd,int nIDDlgItem) {
    return GetDlgItem(hWnd, nIDDlgItem);
}

//窗口_取控件ID
int X_Wnd_GetControlID(HWND chWnd) {
    return GetDlgCtrlID(chWnd);
}

struct ACCENTPOLICY
{
    int nAccentState;
    int nFlags;
    int nColor;
    int nAnimationId;
};
struct WINCOMPATTRDATA
{
    DWORD attribute; // the attribute to query, see below
    PVOID pData; // buffer to store the result
    ULONG dataSize; // size of the pData buffer
};
typedef BOOL(WINAPI* PtrSetWindowCompositionAttribute)(HWND hwnd, WINCOMPATTRDATA* pAttribute);
//窗口_毛玻璃特效
BOOL X_Wnd_Aero(HWND hWnd) {
    HMODULE hDll =LoadLibraryA("user32.dll");
    BOOL r=false;
    if (hDll != nullptr) {
        PtrSetWindowCompositionAttribute ptr = (PtrSetWindowCompositionAttribute)GetProcAddress(hDll, "SetWindowCompositionAttribute");
        if (ptr!=nullptr) {
            ACCENTPOLICY policy = { 3 , 0, 0, 0 }; // ACCENT_ENABLE_BLURBEHIND=3...
            WINCOMPATTRDATA data = { 19, &policy, sizeof(ACCENTPOLICY) }; // WCA_ACCENT_POLICY=19
            r=ptr(hWnd, &data)>0;
        }
        FreeLibrary(hDll);
    }
    return r;
}

//窗口_枚举接口
void X_Wnd_EnumInterface(LPVOID pCallBack) {
    EnumWindows((WNDENUMPROC)pCallBack,0);
}

//窗口_模糊遍历窗口W
HWND X_Wnd_VagueEnumWindow( HWND fhWnd , CXText sWClass, CXText title ,LPVOID rLIst) {
    //rLIst.clear();
    HWND r = NULL;
    HWND lfhWnd = fhWnd==NULL? GetDesktopWindow(): fhWnd;
    HWND lwnd = GetWindow(lfhWnd, 5);
    BOOL legi = false;
    while (lwnd!=NULL) {
        legi = true;
        if (lstrcmpW(sWClass,L"")!=0) {
            CXText ClassName=X_Wnd_GetClass(lwnd);
            if (text_lower2(ClassName).find(text_lower2(sWClass))==std::wstring::npos) {
                legi = false;
            }
			xcl_doMessage();//X_System_DoEvents();
        }
        if (lstrcmpW(title, L"") != 0) {
            CXText TitleName = X_Wnd_GetTitle(lwnd);
            if (text_lower2(TitleName).find(text_lower2(title)) == std::wstring::npos) {
                legi = false;
				xcl_doMessage();// X_System_DoEvents();
            }
        }
        if (legi) {
            if(rLIst==nullptr){
                r = lwnd;
                break;
            }
            CXVector<HWND>*lIst = (CXVector<HWND>*)rLIst;
            lIst->add(lwnd);
            if (lIst->size()==1) {
                r = lwnd;
            }
        }
        lwnd = GetWindow(lwnd, 2);
    }
    return r;
}

//窗口_强制显示
BOOL X_Wnd_ForceDisplay(HWND hWnd, BOOL bTopping) {   
    return SetWindowPos(hWnd, bTopping ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
}

BOOL XC_Wnd_IsTopmost(HWND hWnd)
{
	// 判断窗口是否置顶
	BOOL isTopmost = ((GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0);
	return isTopmost;
}

//窗口_取边框宽度
UINT X_Wnd_GetWindFrameWidth(HWND hWnd){
    WINDOWINFO pwi;
    pwi.cbSize = sizeof(WINDOWINFO);
    GetWindowInfo(hWnd, &pwi);
    return pwi.cxWindowBorders;
}

//窗口_取边框高度
UINT X_Wnd_GetWindFrameHeight(HWND hWnd){
    WINDOWINFO pwi;
    pwi.cbSize = sizeof(WINDOWINFO);
    GetWindowInfo(hWnd, &pwi);
    return pwi.cyWindowBorders;
}

//窗口_取窗口属性
LONG X_Wnd_GetWindAttribute(HWND hWnd, int type) {
    return GetWindowLongA(hWnd, type);
}

//窗口_取点标题
CXText X_Wnd_GetPOINTTitle(LONG x, LONG y) {
    POINT pi = {x,y};
    if(x<=0 || y <= 0){
        pi = GetPOINT();
    }
    wchar_t t[256]={0};
    SendMessageW(WindowFromPoint(pi), 13, 256, (LPARAM)t);
    return t;
}
//窗口_取点标题
CXTextA X_Wnd_GetPOINTTitleA(LONG x, LONG y) {
    POINT pi = { x,y };
    if (x <= 0 || y <= 0) {
        pi = GetPOINT();
    }
    char t[256] = { 0 };
    SendMessageA(WindowFromPoint(pi), 13, 256, (LPARAM)t);
    return t;
}

//窗口_取句柄_递归
HWND X_Wnd_RecursionGetHWND(HWND hWnd, CXText sClass) {
    HWND lhWnd = FindWindowExW(hWnd, 0, 0, 0);
    while (lhWnd!=NULL) {
        CXText Class = X_Wnd_GetClass(lhWnd);
        if(lstrcmpW(sClass, Class)==0){
            break;
        }
        HWND phWnd = X_Wnd_RecursionGetHWND(lhWnd, sClass);
        if (phWnd != NULL) {
            break;
        }
        lhWnd = FindWindowExW(hWnd, lhWnd, 0, 0);
		xcl_doMessage(); //X_System_DoEvents();
    }
    return lhWnd;
}
//窗口_取句柄_递归
HWND X_Wnd_RecursionGetHWNDA(HWND hWnd, CXTextA sClass) {
    HWND lhWnd = FindWindowExA(hWnd, 0, 0, 0);
    while (lhWnd != NULL) {
        CXTextA Class = X_Wnd_GetClassA(lhWnd);
        if (strcmp(sClass, Class) == 0) {
            break;
        }
        HWND phWnd = X_Wnd_RecursionGetHWNDA(lhWnd, sClass);
        if (phWnd != NULL) {
            break;
        }
        lhWnd = FindWindowExA(hWnd, lhWnd, 0, 0);
		xcl_doMessage();//X_System_DoEvents();
    }
    return lhWnd;
}

//窗口_取顶端文件夹路径
CXText X_Wnd_GetTopFolderPath() {
    HWND hWnd = FindWindowW(L"CabinetWClass", NULL);
    CXText path;
    if (hWnd != NULL) {
        hWnd = X_Wnd_RecursionGetHWND(hWnd,L"Breadcrumb Parent");
        hWnd = FindWindowExW(hWnd, 0, L"ToolbarWindow32", 0);
        path = X_Wnd_GetTitle(hWnd);
        path = text_findRight(path,L"地址: ");
    }
    return path;
}
//窗口_取顶端文件夹路径
CXTextA X_Wnd_GetTopFolderPathA() {
    HWND hWnd = FindWindowA("CabinetWClass", NULL);
    CXTextA path;
    if (hWnd != NULL) {
        hWnd = X_Wnd_RecursionGetHWNDA(hWnd, "Breadcrumb Parent");
        hWnd = FindWindowExA(hWnd, 0, "ToolbarWindow32", 0);
        path = X_Wnd_GetTitleA(hWnd);
        path = text_findRightA(path, "地址: ");
    }
    return path;
}

//窗口_取光标位置
RECT X_Wnd_GetCursorPoint(HWND hWnd) {
    DWORD Threadid = (vint)hWnd == NULL ? GetCurrentThreadId() : GetWindowThreadProcessId(hWnd, NULL);
    GUITHREADINFO p;
    p.cbSize = sizeof(p);
    GetGUIThreadInfo(Threadid, &p);
    return p.rcCaret;
}

//窗口_取光标位置1
POINT X_Wnd_GetCursorPoint1(HANDLE dwThreadID) {
    HANDLE lthreadID = dwThreadID;
    if (dwThreadID==NULL) {
        lthreadID = GetCurrentThread();
    }
    GUITHREADINFO p;
    p.cbSize = sizeof(p);
    GetGUIThreadInfo((DWORD)((vint)lthreadID), &p);
    POINT r = { p.rcCaret.left,p.rcCaret.top};
    return r;
}

//窗口_取滚动条位置
POINT X_Wnd_GetScrollBarPoint(HWND hWnd) {
    POINT r;
    r.x = GetScrollPos(hWnd, SB_HORZ);
    r.y = GetScrollPos(hWnd, SB_VERT);
    return r;
}

//窗口_取焦点句柄
HWND X_Wnd_GetFocusHwnd() {
    HWND lqwnd = GetForegroundWindow();
    DWORD lmythID = GetCurrentThreadId();
    DWORD ltargetth = GetWindowThreadProcessId(lqwnd, 0);
    if (lmythID== ltargetth) {
        return GetFocus();
    }
    HWND r;
    AttachThreadInput(ltargetth, lmythID, true);
    r= GetFocus();
    AttachThreadInput(ltargetth, lmythID, true);
    return r;
}

//窗口_取矩形
RECT X_Wnd_GetRECT(HWND hWnd) {
    WINDOWINFO pwi = { 0 };
    pwi.cbSize = sizeof(pwi);
    GetWindowInfo(hWnd, &pwi);
    return pwi.rcWindow;
}

//窗口_取客户区矩形
RECT X_Wnd_GetClientRECT(HWND hWnd) {
    WINDOWINFO pwi={0};
    pwi.cbSize = sizeof(pwi);
    GetWindowInfo(hWnd, &pwi);
    return pwi.rcClient;
}

//窗口_取控件大小
BOOL X_Wnd_GetControlPoint(HWND hWnd,POINT &rpoint){
    RECT r;
    BOOL y = GetClientRect(hWnd, &r);
    rpoint.x = r.right- r.left;
    rpoint.y = r.bottom-r.top;
    return y;
}


//窗口_取控件内容
CXText X_Wnd_GetControlContent(HWND hWnd) {
    DWORD dwSize = SendMessageW(hWnd, 14, 0, 0) + 1;
    if (dwSize>50000) {
        DWORD lSize = 50000;
        wchar_t *lc = new wchar_t[lSize];
        memset(lc,0, lSize);
        SendMessageW(hWnd, 13, lSize, (LPARAM)lc);
        lc[lSize - 1] = L'\0';
        CXText r = lc;
        delete []lc;
        r += L"...后面略掉";
        r += std::to_wstring(dwSize - lSize).c_str();
        r += L"个字符...";
        return r;
    }
    else {
        wchar_t* lc = new wchar_t[dwSize];
        memset(lc, 0, dwSize);
        SendMessageW(hWnd, 13, dwSize, (LPARAM)lc);
        lc[dwSize - 1] = L'\0';
        CXText r = lc;
        delete[]lc;
        return r;
    }
}
//窗口_取控件内容A
CXTextA X_Wnd_GetControlContentA(HWND hWnd) {
    DWORD dwSize = SendMessageA(hWnd, 14, 0, 0) + 1;
    if (dwSize > 50000) {
        DWORD lSize = 50000;
        char* lc = new char[lSize];
        memset(lc, 0, lSize);
        SendMessageA(hWnd, 13, lSize, (LPARAM)lc);
        lc[lSize - 1] = '\0';
        CXTextA r = lc;
        delete[]lc;
        r += "...后面略掉";
        r += std::to_string(dwSize - lSize).c_str();
        r += "个字符...";
        return r;
    }
    else {
        char* lc = new char[dwSize];
        memset(lc, 0, dwSize);
        SendMessageA(hWnd, 13, dwSize, (LPARAM)lc);
        lc[dwSize - 1] = '\0';
        CXTextA r = lc;
        delete[]lc;
        return r;
    }
}

//窗口_取控件坐标
POINT X_Wnd_GetControlPoint(HWND hWnd) {
    HWND lwnd = hWnd==NULL? GetFocus() : hWnd;
    POINT r={0,0};
    ClientToScreen(lwnd, &r);
    return r;
}

//窗口_取扩展样式
DWORD X_Wnd_GetWindowExStyle(HWND hWnd){
    WINDOWINFO pwi;
    pwi.cbSize = sizeof(pwi);
    GetWindowInfo(hWnd, &pwi);
    return pwi.dwExStyle;
}

//窗口_取任务栏句柄
HWND X_Wnd_GetTrayWnd() {
    return FindWindowW(L"Shell_TrayWnd", NULL);
}

//窗口_取鼠标处窗口句柄
HWND X_Wnd_GetMousePointHwnd() {
    POINT mp= GetPOINT();
    return WindowFromPoint(mp);
}

//窗口_取鼠标处控件标题
CXText X_Wnd_GetMousePointControl(LONG x, LONG y) {
    POINT p = {x,y};
    if(!x || !y){
        GetCursorPos(&p);
    }
    wchar_t *str = new wchar_t[_MAX_PATH];
    SendMessageW(WindowFromPoint(p),13, _MAX_PATH,(LPARAM)str);
    CXText r = str;
    delete[]str;
    return r;
}
//窗口_取鼠标处控件标题A
CXTextA X_Wnd_GetMousePointControlA(LONG x, LONG y) {
    POINT p = { x,y };
    if (!x || !y) {
        GetCursorPos(&p);
    }
    char* str = new char[_MAX_PATH];
    SendMessageA(WindowFromPoint(p), 13, _MAX_PATH, (LPARAM)str);
    CXTextA r = str;
    delete[]str;
    return r;
}

//窗口_取透明度
DWORD X_Wnd_GetTransparency(HWND hWnd) {
    BYTE dwAlpha=0;
    DWORD dwStyle = GetWindowLongA(hWnd, GWL_EXSTYLE);
    if (dwStyle& WS_EX_LAYERED) {
        GetLayeredWindowAttributes(hWnd, NULL, &dwAlpha, NULL);
    }
    else {
        return - 1;
    }
    return dwAlpha;
}

//窗口_取消尺寸限制
BOOL  X_Wnd_CancelSizeLimit(HWND hWnd, BOOL cancel) {
    //SetPropA (窗口句柄, “Cancel the limit”, 选择 (是否取消限制, 1, 0))
    return SetPropA(hWnd,"Cancel the limit", cancel? (HANDLE)1: (HANDLE)0);
}

//窗口_取样式
DWORD X_Wnd_GetWindowStyle(HWND hWnd) {
    WINDOWINFO pwi;
    pwi.cbSize = sizeof(pwi);
    GetWindowInfo(hWnd, &pwi);
    return pwi.dwStyle;
}

//窗口_取字符串宽度
DWORD X_Wnd_GetStrWidth(HWND hWnd,CXText str) {
    RECT rect;
    GetWindowRect(hWnd, &rect);
    HDC dc = GetDC(hWnd);
    DrawTextW(dc, str, -1, &rect, 1024|32);
    ReleaseDC(0, dc);
    return rect.right-rect.left;
}
//窗口_取字符串宽度A
DWORD X_Wnd_GetStrWidthA(HWND hWnd, CXTextA str) {
    RECT rect;
    GetWindowRect(hWnd, &rect);
    HDC dc = GetDC(hWnd);
    DrawTextA(dc, str, -1, &rect, 1024 | 32);
    ReleaseDC(0, dc);
    return rect.right - rect.left;
}

//@别名   窗口_取祖句柄(窗口句柄)
HWND X_Wnd_GetAncestorsHwnd(HWND hWnd) {
    return GetAncestor(hWnd, GA_ROOTOWNER);
}

//窗口_取坐标距离
double X_Wnd_GetPointsDistance(POINT a, POINT b) {
    return fabs(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

//窗口_取坐标子句柄
HWND X_Wnd_GetChildWindowFromPoint(HWND hWnd, POINT p) {
    return ChildWindowFromPoint(hWnd, p); 
}

//窗口_闪动Ex
BOOL X_Wnd_FlashWindowEx(HWND hWnd, UINT type, UINT num, UINT speed) {
    FLASHWINFO pfwi;
    pfwi.cbSize = sizeof(pfwi);
    pfwi.hwnd = hWnd;
    pfwi.uCount = num==0?1: num;
    pfwi.dwFlags = type;
    pfwi.dwTimeout = speed;
    return FlashWindowEx(&pfwi);
}

//窗口_设为无焦点
LONG X_Wnd_SetWindowToNoFocus(HWND hWnd) {
    return SetWindowLongPtrA(hWnd, GWL_EXSTYLE, WS_EX_NOACTIVATE);
}

//窗口_是否激活
BOOL  X_Wnd_IsActivation(HWND hWnd) {
    WINDOWINFO pwi;
    pwi.cbSize = sizeof(pwi);
    GetWindowInfo(hWnd, &pwi);
    return pwi.dwWindowStatus == 1;
}

//窗口_是否禁止
BOOL  X_Wnd_IsProhibit(HWND hWnd) {
    return IsWindowEnabled(hWnd)==0;
}

//窗口_是否全屏
BOOL X_Wnd_IsFullScreen(HWND hWnd) {
    RECT rect;
    GetWindowRect(hWnd, &rect);
    LONG sw = (LONG)GetSystemMetrics(SM_CXSCREEN);
    LONG sh = (LONG)GetSystemMetrics(SM_CYSCREEN);
    LONG ww = sw - rect.left + rect.right - sw;
    LONG wh = sh - rect.top + rect.bottom - sh;
    return (ww > (sw - 50)) &&
        (wh > (sh - 50));
}

//窗口_是否有子窗口
BOOL X_Wnd_HavingChildren(HWND hWnd) {
    return !X_Wnd_GetHWND(hWnd) == NULL;
}

//窗口_是否置顶
BOOL X_Wnd_WhetherToTop(HWND hWnd) {
    auto p = GetWindowLongPtrA(hWnd, GWL_EXSTYLE);
    return (p& WS_EX_TOPMOST)== WS_EX_TOPMOST; 
}

//窗口_剔除风格
LONG X_Wnd_CullStyle(HWND hWnd,DWORD dwStyle) {
    DWORD dwlStyle = GetWindowLongPtrA(hWnd, GWL_STYLE);
    dwlStyle = dwlStyle & ~dwStyle;
    return SetWindowLongPtrA(hWnd, GWL_STYLE, dwlStyle);
}

//窗口_剔除扩展风格
LONG X_Wnd_CullStyleEx(HWND hWnd, DWORD dwStyle){
    DWORD dwlStyle = GetWindowLongPtrA(hWnd, GWL_EXSTYLE);
    dwlStyle = dwlStyle & ~dwStyle;
    return SetWindowLongPtrA(hWnd, GWL_EXSTYLE, dwlStyle); 
}

//窗口_限制运行次数
BOOL X_Wnd_RestrictedOperationNum(CXText title, CXText sClassName, int num) {
    int lnum = num <= 0?1: num;
    HWND hWnd = FindWindowExW(0, 0, sClassName, 0);
    int sn=0;
    while (hWnd!=NULL) {
        if(lstrcmpW(title,X_Wnd_GetTitle(hWnd))==0) {
            sn++;
        }
        hWnd = FindWindowExW(0, hWnd, sClassName, 0);
    }
    return sn> num;
}
//窗口_限制运行次数A
BOOL X_Wnd_RestrictedOperationNumA(CXTextA title, CXTextA sClassName, int num) {
    int lnum = num <= 0 ? 1 : num;
    HWND hWnd = FindWindowExA(0, 0, sClassName, 0);
    int sn = 0;
    while (hWnd != NULL) {
        if (strcmp(title, X_Wnd_GetTitleA(hWnd)) == 0) {
            sn++;
        }
        hWnd = FindWindowExA(0, hWnd, sClassName, 0);
    }
    return sn > num;
}

//窗口_循环关闭
void X_Wnd_CycleClose(CXText sClassName, CXText title) {
    HWND hWnd = NULL;
    hWnd = FindWindowW(sClassName,title);
    while (hWnd!=NULL) {
        PostMessageW(hWnd, 16, 0, 0);
        hWnd = FindWindowW(sClassName, title);
    }
}
//窗口_循环关闭A
void X_Wnd_CycleCloseA( CXTextA sClassName, CXTextA title) {
    HWND hWnd = NULL;
    hWnd = FindWindowA(sClassName, title);
    while (hWnd != NULL) {
        PostMessageA(hWnd, 16, 0, 0);
        hWnd = FindWindowA(sClassName, title);
    }
}

//窗口_隐藏小图标
void X_Wnd_HideSmallIcon(HWND hWnd) {
    SetWindowLongA(hWnd, GWL_EXSTYLE, 65793);
    SendMessageA(hWnd, WM_SETICON, 1, 0);
    SendMessageA(hWnd, WM_SETICON, 0, 0);
}

//窗口_置标题
BOOL X_Wnd_SetTitle(HWND hWnd, CXText title) {
    return SetWindowTextW(hWnd, title);
}
//窗口_置标题A
BOOL X_Wnd_SetTitleA(HWND hWnd, CXTextA title) {
    return SetWindowTextA(hWnd, title);
}

//窗口_置穿透
BOOL X_Wnd_SetPenetrate(HWND hWnd, BOOL bPenetrate) {
    DWORD dwStyleEx=0;
    if (!bPenetrate) {
        dwStyleEx = (DWORD)GetPropA(hWnd, "transparent_tmp");
        RemovePropA(hWnd, "transparent_tmp");  // 删除这个属性;
        SetWindowLongA(hWnd, GWL_EXSTYLE, dwStyleEx); // 重新取一下,看是否设置成功
        return dwStyleEx == GetWindowLongA(hWnd, GWL_EXSTYLE);// 重新取一下, 看是否设置成功
    }
    DWORD dwStyleExNew=0;
    dwStyleEx = GetWindowLongA(hWnd, GWL_EXSTYLE);
    if ((dwStyleExNew & WS_EX_TRANSPARENT)!= WS_EX_TRANSPARENT) {
        dwStyleExNew = dwStyleExNew| WS_EX_TRANSPARENT;
    }
    if ((dwStyleExNew & WS_EX_LAYERED)!= WS_EX_LAYERED) {
        dwStyleExNew = dwStyleExNew | WS_EX_LAYERED;
    }
    SetPropA(hWnd, "transparent_tmp", (HANDLE)dwStyleEx);
    SetWindowLongA(hWnd, GWL_EXSTYLE, dwStyleExNew);
    dwStyleEx = GetWindowLongA(hWnd, GWL_EXSTYLE); //重新取一下,看是否设置成功
    return ((dwStyleEx&WS_EX_TRANSPARENT) == WS_EX_TRANSPARENT) && ((dwStyleEx & WS_EX_LAYERED)== WS_EX_LAYERED);
}

//窗口_置窗口化
void X_Wnd_SetWindowing(HWND hWnd, int NewWidth, int NewHeight, CXText title, BOOL addFrame, int rpWidth, int rpHeight) {
    if (addFrame) { SetWindowLongA(hWnd, -16, 348913664); }
    if (lstrcmpW(title, L"") != 0) { SetWindowTextW(hWnd, title); }
    MoveWindow(hWnd, 0, 0, NewWidth, NewHeight, true);
    if (rpWidth != 0 && rpHeight != 0) {
        //X_System_SetScreenResolution(0, rpWidth, rpHeight);
        DISPLAY_DEVICE Device;
        DEVMODE	 DeviceMode;
        DWORD dwFlags = 0;
        LONG iDisp = 0;
        Device.cb = sizeof(DISPLAY_DEVICE);
        DeviceMode.dmSize = sizeof(DEVMODE);
        DeviceMode.dmDriverExtra = 0;
        if (!EnumDisplayDevicesW(NULL, 0, &Device, 0)) { return; }
        if (EnumDisplaySettingsExW(Device.DeviceName, ENUM_CURRENT_SETTINGS, &DeviceMode, 0))
        {

            DeviceMode.dmBitsPerPel = 0;
            DeviceMode.dmPelsWidth = rpWidth;
            DeviceMode.dmPelsHeight = rpHeight;
            DeviceMode.dmDisplayFrequency = 0;
            dwFlags = CDS_FULLSCREEN;
            iDisp = ChangeDisplaySettingsExW(Device.DeviceName, &DeviceMode, 0, dwFlags, 0) == DISP_CHANGE_SUCCESSFUL;
        }
    }
}

//窗口_置滚动条位置
void X_Wnd_SetScrollBarPosition(HWND hWnd, POINT pPosition) {
    SetScrollPos(hWnd, SB_HORZ, pPosition.x, true);
    SetScrollPos(hWnd, SB_VERT, pPosition.y, true);
    SendMessageA(hWnd, WM_HSCROLL, (((vint)pPosition.x<<16)|SB_THUMBPOSITION), 0);
    SendMessageA(hWnd, WM_VSCROLL, (((vint)pPosition.y<<16)|SB_THUMBPOSITION), 0);
}

//窗口_置控件焦点
HWND X_Wnd_SetControlFocus(HWND hWnd) {
    DWORD dwtid = GetCurrentThreadId();
    DWORD dwsuctid = GetWindowThreadProcessId(hWnd, 0);
    AttachThreadInput(dwsuctid, dwtid, true);
    HWND hsf = SetFocus(hWnd);
    AttachThreadInput(dwsuctid, dwtid, false);
    return hsf;
}

//窗口_置控件内容
void X_Wnd_SetControlContent(HWND hWnd, CXText str) {
    SendMessageW(hWnd, 12, 0, (LPARAM)str.get());
}
//窗口_置控件内容
void X_Wnd_SetControlContentA(HWND hWnd, CXTextA str) {
    SendMessageA(hWnd, 12, 0, (LPARAM)str.get());
}

//窗口_置控件状态
BOOL X_Wnd_SetScrollBar(HWND hWnd, BOOL show) {
    return ShowScrollBar(hWnd,2, show); 
}

//窗口_总在最前
BOOL X_Wnd_AlwaysTop(HWND hWnd, BOOL bATop) {
    if (bATop) {
        SetForegroundWindow(hWnd);
    }
    return SetWindowPos(hWnd, bATop?HWND_TOPMOST:HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
}

//@别名   窗口_最大化(窗口句柄,无边框)
void X_Wnd_Maximize(HWND hWnd, BOOL bNoFrame) {
    SetForegroundWindow(hWnd);
    if (bNoFrame) {
        X_Wnd_SetPosAndSize(hWnd,-2,-2, GetSystemMetrics(62), GetSystemMetrics(61));
    }
    else {
        PostMessageW(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    }
}

//控件_圆角化
void X_Wnd_ControlRounding(HWND hWnd, int Width, int height) {
    POINT sz;
    X_Wnd_GetControlSize(hWnd, sz);
    HRGN hRgn = CreateRoundRectRgn(0, 0, sz.x, sz.y, Width, height);
    SetWindowRgn(hWnd, hRgn, true);
    DeleteObject(hRgn);
}

//窗口_取控件大小
BOOL X_Wnd_GetControlSize(HWND hWnd, POINT& rpoint) {
    RECT r;
    BOOL b = GetClientRect(hWnd, &r);
    rpoint.x = r.right-r.left;
    rpoint.y = r.bottom-r.top;
    return b;
}