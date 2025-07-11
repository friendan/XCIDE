//
// Created by Huiyi on 2021/4/25.
//
#include "module_e_System.h"

//系统_是否64
bool X_System_SysIs64()
{
    SYSTEM_INFO info;
    GetNativeSystemInfo(&info);
    if(info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64
    || info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
    {
        return true;
    }
    return false;
}

//取系统类型
int X_System_WIsOs ()
{
#if defined I_OS_MAC
    return X_OS_MACOS;
#elif defined I_OS_ANDROID
    return X_OS_ANDROID;
#elif defined I_OS_WIN
    return X_OS_WINDOWS;
//#elif _WIN32
//    return X_OS_WINDOWS32;
#elif defined I_OS_CYGWIN
    return X_OS_CYGWIN;
#elif defined I_OS_SOLARIS
    return X_OS_SUNOS;
#elif defined I_OS_LINUX
    return X_OS_LINUX;
#elif defined I_OS_FREEBSD
    return X_OS_FREEBSD;
#elif defined I_OS_OPENBSD
    return X_OS_OPENBSD;
#elif defined I_OS_AIX
    return X_OS_AIX;
#else
    return X_OS_NULL;
#endif
    return X_OS_NULL;
}

//取DOS执行结果A
CXTextA X_System_RunCmd (CXTextA cmd,void*func)
{
    FILE* pipe;
    std::string rets;
    rets.reserve(1024* 4);//初始化定义存放结果的字符串变量
    char buffer [128]; //定义缓冲区
    pipe = _popen ("ipconfig", "r"); //打开管道，并执行命令
    if (!pipe)
    {
        return rets;
    }
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe)){ //将管道输出到result中
            if (func != NULL && func != nullptr){
                X_System_RunCmd_res fCmd = (X_System_RunCmd_res)func;
                if(fCmd (buffer)){
                    break;
                }
            }
            rets.append(buffer);
        }
    }
    _pclose(pipe);
    return rets;
}


CXText GetLastErrorStr() {
    auto e = GetLastError();
    DWORD dwlen = AMGetErrorTextW(e,0,0);
    if (dwlen < 1) { 
        wchar_t wrs[100];
        wsprintfW(wrs, L"未知错误:%d", e);
        return wrs;
    }
    LPWSTR str = new wchar_t[dwlen];
    memset(str,0, dwlen);
    AMGetErrorTextW(e, str, dwlen);
    CXText r= str;
    delete str;
    return r;
}

//@别名   系统_取屏幕宽度()
int X_System_ScreenWidth() {
    return GetSystemMetrics(SM_CXSCREEN);
    
}
//@别名   系统_取屏幕高度()
int X_System_ScreenHeight() {
    return GetSystemMetrics(SM_CYSCREEN);
}

//系统_置屏幕分辨率
DWORD X_System_SetScreenResolution(WORD dmBitsPerPel, WORD dmPelsWidth, WORD dmPelsHeight,WORD dmDisplayFrequency,int model,DWORD iModeNum) {
    DISPLAY_DEVICE Device;
    DEVMODE	 DeviceMode;
    DWORD dwFlags = 0;
    LONG iDisp = 0;
    Device.cb = sizeof(DISPLAY_DEVICE);
    DeviceMode.dmSize = sizeof(DEVMODE);
    DeviceMode.dmDriverExtra = 0;
    if (!EnumDisplayDevicesW(NULL, 0, &Device, 0)){return 0;}
    if (EnumDisplaySettingsExW(Device.DeviceName, ENUM_CURRENT_SETTINGS, &DeviceMode, 0))
    {
        if (dmBitsPerPel > 0) {
            DeviceMode.dmBitsPerPel = dmBitsPerPel;
        }
        if (dmPelsWidth > 0) {
            DeviceMode.dmPelsWidth = dmPelsWidth;
        }
        if (dmPelsHeight > 0) {
            DeviceMode.dmPelsHeight = dmPelsHeight;
        }
        if (dmDisplayFrequency > 0) {
            DeviceMode.dmDisplayFrequency = dmDisplayFrequency;
        }
        if (model == 1) {
            dwFlags = CDS_FULLSCREEN;
        }
        else {
            dwFlags = CDS_GLOBAL | CDS_UPDATEREGISTRY;
        }
        iDisp = ChangeDisplaySettingsExW(Device.DeviceName, &DeviceMode,0,dwFlags,0) == DISP_CHANGE_SUCCESSFUL;
    }
    return iDisp;
}

//系统_创建快捷方式
BOOL X_System_CreateFileShortcut(CXText lpszTargetFilePath, CXText lpszLnkPath, CXText IconPath, CXText lpszDescription, WORD wHotkey) {
	if (lpszTargetFilePath ==L"" || lpszLnkPath == L"") {
		return FALSE;
	}

	HRESULT hr;
	IShellLink* pLink;  // IShellLink对象指针    
	IPersistFile* ppf;    // IPersisFil对象指针 

	//::CoInitialize( NULL );

	// 创建IShellLink对象    
	hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void**)&pLink);
	if (FAILED(hr))
	{
		//::CoUninitialize()
		return FALSE;
	}

	// 从IShellLink对象中获取IPersistFile接口    
	hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
	if (FAILED(hr))
	{
		pLink->Release();
		//::CoUninitialize()
		return FALSE;
	}

	// 快捷方式指向的实际文件路径    
	if (lpszTargetFilePath != L"")
	{

		pLink->SetPath(lpszTargetFilePath);
		pLink->SetWorkingDirectory(lpszTargetFilePath.substr(0, text_getSubPosRight(lpszTargetFilePath, L"\\")));

		// 解决快捷图标不刷新、更改图标时找不到文件的问题
		// 快捷方式文件的图标就是其指向的exe文件的图标
		//pLink->SetIconLocation(lpszTargetFilePath, 0);

		IShellLinkDataList* pShellLinkDataList = NULL;
		hr = pLink->QueryInterface(IID_IShellLinkDataList, (void**)&pShellLinkDataList);
		if (FAILED(hr))
		{
			ppf->Release();
			pLink->Release();
			return FALSE;
		}

		DWORD dwFlags = SLDF_DEFAULT;
		pShellLinkDataList->GetFlags(&dwFlags);
		if ((dwFlags & SLDF_HAS_EXP_ICON_SZ) == SLDF_HAS_EXP_ICON_SZ)
		{
			pShellLinkDataList->SetFlags(SLDF_DEFAULT);
			pShellLinkDataList->RemoveDataBlock(EXP_SZ_ICON_SIG);
		}

		pShellLinkDataList->Release();
	}

	// 设置快捷键    
	if (wHotkey != 0)
	{
		pLink->SetHotkey(wHotkey);
	}
    pLink->SetIconLocation(IconPath,0);
	// 设置备注    
	if (lpszDescription != L"")
	{
		pLink->SetDescription(lpszDescription);
	}

	// 显示方式    
	pLink->SetShowCmd(0);

	// 保存快捷方式到指定目录下    
	// 要将路径字符串转化成宽字节字符串，COM接口ppf->Save要传入宽字符
	BOOL bUnicode = FALSE;


	hr = ppf->Save(lpszLnkPath, TRUE);

	ppf->Release();
	pLink->Release();


	//::CoUninitialize();

	return SUCCEEDED(hr);
}

//系统_创建快捷方式A
BOOL X_System_CreateFileShortcutA(CXTextA lpszTargetFilePath, CXTextA lpszLnkPath, CXTextA IconPath, CXTextA lpszDescription, WORD wHotkey) {
	if (lpszTargetFilePath == "" || lpszLnkPath == "") {
		return FALSE;
	}

	HRESULT hr;
	IShellLinkA* pLink;  // IShellLink对象指针    
	IPersistFile* ppf;    // IPersisFil对象指针 

	//::CoInitialize( NULL );

	// 创建IShellLink对象    
	hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkA, (void**)&pLink);
	if (FAILED(hr)) {
		//::CoUninitialize()
		return FALSE;
	}

	// 从IShellLink对象中获取IPersistFile接口    
	hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
	if (FAILED(hr)) {
		pLink->Release();
		//::CoUninitialize()
		return FALSE;
	}

	// 快捷方式指向的实际文件路径    
	if (lpszTargetFilePath != "") {
		pLink->SetPath(lpszTargetFilePath);
		pLink->SetWorkingDirectory(lpszTargetFilePath.substr(0, text_getSubPosRightA(lpszTargetFilePath, "\\")));

		// 解决快捷图标不刷新、更改图标时找不到文件的问题
		// 快捷方式文件的图标就是其指向的exe文件的图标
		//pLink->SetIconLocation(lpszTargetFilePath, 0);

		IShellLinkDataList* pShellLinkDataList = NULL;
		hr = pLink->QueryInterface(IID_IShellLinkDataList, (void**)&pShellLinkDataList);
		if (FAILED(hr))
		{
			ppf->Release();
			pLink->Release();
			return FALSE;
		}

		DWORD dwFlags = SLDF_DEFAULT;
		pShellLinkDataList->GetFlags(&dwFlags);
		if ((dwFlags & SLDF_HAS_EXP_ICON_SZ) == SLDF_HAS_EXP_ICON_SZ)
		{
			pShellLinkDataList->SetFlags(SLDF_DEFAULT);
			pShellLinkDataList->RemoveDataBlock(EXP_SZ_ICON_SIG);
		}

		pShellLinkDataList->Release();
	}

	// 设置快捷键    
	if (wHotkey != 0)
	{
		pLink->SetHotkey(wHotkey);
	}
	pLink->SetIconLocation(IconPath, 0);
	// 设置备注    
	if (lpszDescription != "")
	{
		pLink->SetDescription(lpszDescription);
	}

	// 显示方式    
	pLink->SetShowCmd(0);

	// 保存快捷方式到指定目录下    
	// 要将路径字符串转化成宽字节字符串，COM接口ppf->Save要传入宽字符
	BOOL bUnicode = FALSE;

	hr = ppf->Save(A2W(lpszLnkPath), TRUE);

	ppf->Release();
	pLink->Release();


	//::CoUninitialize();

	return SUCCEEDED(hr);
}