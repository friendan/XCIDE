#include "module_e_Web.h"
#include <objbase.h>
#include <Shlobj.h>
#pragma comment(lib, "urlmon.lib")
#include <fstream>

//系统_创建快捷方式
BOOL System_CreateFileShortcut(CXText lpszTargetFilePath, CXText lpszLnkPath, CXText IconPath, CXText lpszDescription, WORD wHotkey) {
	if (lpszTargetFilePath == L"" || lpszLnkPath == L"") {
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
	pLink->SetIconLocation(IconPath, 0);
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

//网页_访问
CXBytes X_NetWork_Visit(CXText Url, int Method, CXBytes* PostData,
	CXText* SendCookies , CXText* RespCookies ,
	CXText* SendHeader , CXText* RespHeader ,
	bool bBanRedirect , CXText* agentHost, CXText* agentName , CXText* agentPasswd, 
	bool completionHeader , bool standardHeaders,
	int* rStatusCode, CXText* rStatusStr) {
	CXBytes rb;
	CXWinHttp http;
	CXBytes lPostData; if (PostData != nullptr) { lPostData = *PostData; }
	CXText lSendCookies; if (SendCookies != nullptr) { lSendCookies = *SendCookies; }
	//CXText lRespCookies; if (RespCookies != nullptr) { lRespCookies = *RespCookies; }
	CXText lSendHeader; if (SendHeader != nullptr) { lSendHeader = *SendHeader; }
	//CXText lRespHeader; if (RespHeader != nullptr) { lRespHeader = *RespHeader; }
	CXText lagentHost; if (agentHost != nullptr) { lagentHost = *agentHost; }
	CXText lagentName; if (agentName != nullptr) { lagentName = *agentName; }
	CXText lagentPasswd; if (agentPasswd != nullptr) { lagentPasswd = *agentPasswd; }
	std::vector<const wchar_t*> ml = { L"GET" ,L"POST",L"HEAD" ,L"PUT"  ,L"OPTIONS" ,L"DELETE"  ,L"TRACE"  , L"CONNECT" };
	if (!http.Open(Url,
	(Method<0 || Method>((int)ml.size())-1)? ml[0]:ml[Method]
	)) {
		if (rStatusStr != nullptr) {
			*rStatusStr = L"打开链接失败";
		}
		return rb;
	}
	http.SetRedirect(bBanRedirect);
	if (lstrcmpW(lagentHost, L"")!=0) {
		if (!http.SetProxy(lagentHost, lagentName, lagentPasswd)) {
			if (rStatusStr != nullptr) {
				*rStatusStr = L"设置代理失败";
			}
			return rb;
		}
	}
	std::wstring headerStr = X_String_ToLower(lSendHeader).get();
	if (lSendHeader.size()>0) {
		if (lSendHeader[lSendHeader.size() - 1] != '\n') {
			lSendHeader += L"\n";
		}
	}
	if (completionHeader) {
		if (headerStr.find(L"user-agent: ") == -1) {
			lSendHeader += L"User-Agent: Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)\n";
		}
		if (headerStr.find(L"accept: ") == -1) {
			lSendHeader += L"Accept: text/html, application/xhtml+xml, */*\n";
		}
		if (headerStr.find(L"accept-encoding: ") == -1) {
			lSendHeader += L"Accept-Encoding: identity\n";
		}
		if (headerStr.find(L"accept-language: ") == -1) {
			lSendHeader += L"Accept-Language: zh-cn\n";
		}
		if (Method==1) {
			if (headerStr.find(L"content-type: ") == -1) {
				lSendHeader += L"Content-Type: application/x-www-form-urlencoded\n";
			}
		}
		if (headerStr.find(L"cache-control: ") == -1) {
			lSendHeader += L"Cache-Control: no-cache\n";
		}
	}
	if (completionHeader) {
		lSendHeader = X_NetWork_CompletionHeaders(lSendHeader);
	}
	if(headerStr.find(L"cookie:")==-1) {
		if (lSendCookies.size() > 0) {
			if (X_String_ToLower(lSendCookies).find(L"cookie:")==-1) {
				lSendHeader += L"\nCookie: "+ lSendCookies + L"\n";
			}
			else {
				lSendHeader += L"\n" + lSendCookies+L"\n";
			}
		}
	}
	http.SetRequestHeaders(lSendHeader);
	if (lPostData.size()>0) {
		if (!http.SendBytes(lPostData)) {
			if (rStatusStr != nullptr) {
				*rStatusStr = L"发送请求失败";
			}
			return rb;
		}
	}
	else {
		if (!http.Send()) {
			if (rStatusStr != nullptr) {
				*rStatusStr = L"发送请求失败";
			}
			return rb;
		}
	}
	http.GetResponseBody(rb);
	if (!rb.size()) {
		rb = {0,0};
	}
	if (RespCookies != nullptr) { 
		CXText rc = http.GetAllResponseCookies();
		rc =X_String_Subreplace(rc, L"Set-Cookie: ", L"Cookie: ");
		*RespCookies = rc;
	}
	if (RespHeader != nullptr) {
		*RespHeader = L"";
		CXText rh = http.GetAllResponseHeaders();
		auto hl = X_String_SplitWithStl(rh,L"\n");
		for (int hi = 0; hi<(int)hl.size();hi++) {
			if (hl[hi].size()<2) {
				continue;
			}
			auto ls=X_String_ToLower(hl[hi].substr(0, 10));
			if (lstrcmpW(ls,L"set-cookie")==0) {
				continue;
			}
			RespHeader->append(hl[hi]);
			RespHeader->append(L"\n");
		}
	}
	if (rStatusCode != nullptr) {
		*rStatusCode = http.GetStatus();
	}
	//std::wcout << http.GetAllResponseCookies().get();
	return rb;
}

//网页_处理协议头
CXText X_NetWork_CompletionHeaders(CXText header) {
	CXText rh = L"";
	auto arr = X_String_SplitWithStl(header, L"\n");
	for (int i = 0; i < (int)arr.size(); i++) {
		UINT l_colonIndex = arr[i].find(L":");
		if (l_colonIndex == -1) { continue; }
		CXText l_KeyName = arr[i].substr(0, l_colonIndex);
		if (l_KeyName.find(L"-") != -1) {
			CXText l_KeyAdd;
			auto l_KeyArr = X_String_SplitWithStl(l_KeyName, L"-");
			for (int ka = 0; ka < (int)l_KeyArr.size(); ka++) {
				l_KeyAdd += (ka == (l_KeyArr.size() - 1) ? L"-" : L"");
				l_KeyAdd += X_String_LastToUpper(l_KeyArr[ka]);
			}
			l_KeyName = l_KeyAdd;
		}
		else {
			l_KeyName = X_String_LastToUpper(l_KeyName);
		}
		CXText l_v = arr[i].substr(l_colonIndex, arr[i].size() - l_colonIndex);
		rh += l_KeyName + l_v + "\n";
	}
	return rh;

	//CXText rh=L"";
	//auto arr=X_String_SplitWithStl(header,L"\n");
	//for (int i = 0; i < arr.size();i++) {
	//	UINT l_colonIndex = arr[i].find(L":");
	//	if (l_colonIndex==-1) { continue; }
	//	CXText l_KeyName = arr[i].substr(0, l_colonIndex);
	//	if (l_KeyName.find(L"-")!=-1) {
	//		CXText l_KeyAdd;
	//		auto l_KeyArr= X_String_SplitWithStl(arr[i], L"-");
	//		for (int ka = 0; ka < l_KeyArr.size();ka++) {
	//			l_KeyAdd += (ka == (l_KeyArr.size() - 1) ? L"-" : L"");
	//			l_KeyAdd+=X_String_LastToUpper(l_KeyArr[ka]);
	//		}
	//		l_KeyName = l_KeyAdd;
	//	}
	//	else {
	//		l_KeyName = X_String_LastToUpper(l_KeyName);
	//	}
	//	CXText l_v = arr[i].substr(l_colonIndex, arr[i].size() - l_colonIndex);
	//	rh += l_KeyName+ l_v+"\n";
	//}
	//return rh;
}
//网页_处理协议头A
CXTextA X_NetWork_CompletionHeadersA(CXTextA header) {
	CXTextA rh = "";
	auto arr = X_String_SplitWithStlA(header, "\n");
	for (int i = 0; i < (int)arr.size(); i++) {
		UINT l_colonIndex = arr[i].find(":");
		if (l_colonIndex == -1) { continue; }
		CXTextA l_KeyName = arr[i].substr(0, l_colonIndex);
		if (l_KeyName.find("-") != -1) {
			CXTextA l_KeyAdd;
			auto l_KeyArr = X_String_SplitWithStlA(arr[i], "-");
			for (int ka = 0; ka < (int)l_KeyArr.size(); ka++) {
				l_KeyAdd += X_String_LastToUpperA(l_KeyArr[ka]);
				l_KeyAdd += (ka == (l_KeyArr.size() - 1) ? "-" : "");
			}
			l_KeyName = l_KeyAdd;
		}
		else {
			l_KeyName = X_String_LastToUpperA(l_KeyName);
		}
		CXTextA l_v = arr[i].substr(l_colonIndex + 1, arr[i].size() - l_colonIndex);
		rh += l_KeyName + l_v + "\n";
	}
	return rh;
}

//网页_取网络文件尺寸
ULONGLONG X_NetWork_GetNetFileSize(CXText Url) {
	CXWinHttp h;
	if (!h.Open(Url)) { return -1; }
	if (!h.Send()) { return -1; }
	CXText size=h.GetResponseHeader(L"Content-Length");
	size = X_String_Trim(size);
	if(lstrcmpW(size,L"")==0) { return -1; }
	return std::stoull(size.get());
}
//网页_取网络文件尺寸A
ULONGLONG X_NetWork_GetNetFileSizeA(CXTextA Url) {
	CXWinHttp h;
	if (!h.Open(A2W(Url))) { return -1; }
	if (!h.Send()) { return -1; }
	CXText size = h.GetResponseHeader(L"Content-Length");
	size = X_String_Trim(size);
	if (lstrcmpW(size, L"") == 0) { return -1; }
	return std::stoull(size.get());
}

//网页_IE浏览器网页跳转静音
void X_NetWork_IESkipMute(bool IsMute){
	CoInternetSetFeatureEnabled(FEATURE_DISABLE_NAVIGATION_SOUNDS, SET_FEATURE_ON_PROCESS, IsMute);
}

typedef struct _INTERNET_CACHE_ENTRY_INFOW {
	DWORD dwStructSize;         // version of cache system.
	LPWSTR  lpszSourceUrlName;    // embedded pointer to the URL name string.
	LPWSTR  lpszLocalFileName;  // embedded pointer to the local file name.
	DWORD CacheEntryType;       // cache type bit mask.
	DWORD dwUseCount;           // current users count of the cache entry.
	DWORD dwHitRate;            // num of times the cache entry was retrieved.
	DWORD dwSizeLow;            // low DWORD of the file size.
	DWORD dwSizeHigh;           // high DWORD of the file size.
	FILETIME LastModifiedTime;  // last modified time of the file in GMT format.
	FILETIME ExpireTime;        // expire time of the file in GMT format
	FILETIME LastAccessTime;    // last accessed time in GMT format
	FILETIME LastSyncTime;      // last time the URL was synchronized
	// with the source
	LPWSTR  lpHeaderInfo;        // embedded pointer to the header info.
	DWORD dwHeaderInfoSize;     // size of the above header.
	LPWSTR  lpszFileExtension;  // File extension used to retrive the urldata as a file.
	union {                     // Exemption delta from last access time.
		DWORD dwReserved;
		DWORD dwExemptDelta;
	};                          // Exemption delta from last access
} INTERNET_CACHE_ENTRY_INFOW, * LPINTERNET_CACHE_ENTRY_INFOW;
typedef BOOLAPI GetUrlCacheEntryInfoW(
	_In_ LPCWSTR lpszUrlName,
	_Inout_updates_bytes_opt_(*lpcbCacheEntryInfo) LPINTERNET_CACHE_ENTRY_INFOW lpCacheEntryInfo,
	_Inout_opt_ LPDWORD lpcbCacheEntryInfo
);
HMODULE WininetMODE = nullptr;
//网页_URL取本地地址
CXText X_NetWork_UrlGetLocalPath(CXText Url){
	DWORD dwbuffer;
	if (WininetMODE == nullptr) {
		WininetMODE = LoadLibraryW(L"Wininet.dll");
	}
	if (!WininetMODE) { return L""; }
	auto f=(GetUrlCacheEntryInfoW*)GetProcAddress(WininetMODE,"GetUrlCacheEntryInfoW");
	if (f == nullptr) {
		return L"";
	}
	f(Url, 0, &dwbuffer);
	if(GetLastError() == 2){
		xcl_log(L"指定的缓存条目在缓存中没有找到。");
		return L"";
	}
	if(GetLastError() == 122){
		INTERNET_CACHE_ENTRY_INFOW info={0};
		f(Url, &info, &dwbuffer);
		return info.lpszLocalFileName;
	}
	return L"";
}
//文件_写到文件
bool _X_File_WriteFile(CXText fileName, CXBytes& filebytes) {
	std::ofstream wf;
	wf.open(fileName, std::ios::out | std::ios::binary);
	if (!wf.is_open()) { return false; }
	int index = 0;
	int addnum = filebytes.size();
	int iBuffLen = addnum < 2048 ? addnum : 2048;
	while (addnum > 0) {
		char* buff = new char[addnum];
		CXBytes b = filebytes.getMid(index, iBuffLen);
		wf.write((char*)b.get(), b.size());
		index = (index + iBuffLen) > (int)filebytes.size() ? filebytes.size() : index + iBuffLen;
		addnum = (filebytes.size() - index) > 2048 ? 2048 : filebytes.size() - index;
		delete buff;
	}
	wf.close();
	return true;
}

//系统_创建快捷方式A
BOOL System_CreateFileShortcutA(CXTextA lpszTargetFilePath, CXTextA lpszLnkPath, CXTextA IconPath, CXTextA lpszDescription, WORD wHotkey) {
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

//网页_创建快捷方式
BOOL X_NetWork_CreateShortcut(CXText FileName, CXText Url, CXText IconPath, WORD HotKey) {
	CXText fn = FileName;
	if (fn.size()<4) {
		fn += L".url";
	}
	fn = fn.substr(fn.size() - 4, 4);
	fn = X_String_ToLower(fn);
	fn = (lstrcmpW(fn, L".url") == 0) ? FileName: FileName+L".url";
	BOOL r = System_CreateFileShortcut(L"C:\\", fn, IconPath, L"", HotKey);
	if (r<1) {
		return r;
	}
	const wchar_t * tmp = L"[{000214A0-0000-0000-C000-000000000046}]\n"
		"Prop3=19,2\n"
		"[InternetShortcut]\n"
		"IDList=\n"
		"IconIndex=0\n"
		"HotKey=%d\n"
		"URL=%s\n"
		"IconFile=%s\n";
	DWORD len = lstrlenW(tmp)+ FileName.size()+ Url.size()+ IconPath.size()+20;
	WCHAR* buffer= new WCHAR[len];
	memset(buffer,0, len);
	swprintf_s (buffer, len, tmp, HotKey, Url.get(), IconPath.get());
	CXBytes data; data.addText(buffer);
	delete buffer;
	return _X_File_WriteFile(fn, data);
}
//文件_写到文件A
bool _X_File_WriteFileA(CXTextA fileName, CXBytes& filebytes) {
	std::ofstream wf;
	wf.open(fileName, std::ios::out | std::ios::binary);
	if (!wf.is_open()) { return false; }
	int index = 0;
	int addnum = filebytes.size();
	int iBuffLen = addnum < 2048 ? addnum : 2048;
	while (addnum > 0) {
		char* buff = new char[addnum];
		CXBytes b = filebytes.getMid(index, iBuffLen);
		wf.write((char*)b.get(), b.size());
		index = (index + iBuffLen) > (int)filebytes.size() ? filebytes.size() : index + iBuffLen;
		addnum = (filebytes.size() - index) > 2048 ? 2048 : filebytes.size() - index;
		delete buff;
	}
	wf.close();
	return true;
}
//网页_创建快捷方式A
BOOL X_NetWork_CreateShortcutA(CXTextA FileName, CXTextA Url, CXTextA IconPath, WORD HotKey) {
	CXTextA fn = FileName;
	if (fn.size() < 4) {
		fn += ".url";
	}
	fn = fn.substr(fn.size() - 4, 4);
	fn = X_String_ToLowerA(fn);
	fn = (strcmp(fn, ".url") == 0) ? FileName : FileName + ".url";
	BOOL r = System_CreateFileShortcutA("C:\\", fn, IconPath, "", HotKey);
	if (r < 1) {
		return r;
	}
	const char* tmp = "[{000214A0-0000-0000-C000-000000000046}]\n"
		"Prop3=19,2\n"
		"[InternetShortcut]\n"
		"IDList=\n"
		"IconIndex=0\n"
		"HotKey=%d\n"
		"URL=%s\n"
		"IconFile=%s\n";
	DWORD len = strlen(tmp) + FileName.size() + Url.size() + IconPath.size()  + 20;
	CHAR* buffer = new CHAR[len];
	memset(buffer, 0, len);
	sprintf_s(buffer, len, tmp, HotKey, Url.get(), IconPath.get());
	CXBytes data; data.addTextA(buffer);
	delete buffer;
	return _X_File_WriteFileA(fn, data);
}

//网页_打开指定网址
void X_NetWork_OpenUrl(CXText url) {
	ShellExecuteW(0,L"open", url,NULL,NULL,1);
}
//网页_打开指定网址A
void X_NetWork_OpenUrlA(CXTextA url) {
	ShellExecuteA(0, "open", url, NULL, NULL, 1);
}
//窗口_查找网页句柄
void X_NetWork_FindNetWorkHwnd(HWND hWnd, HWND &hwndSDV, HWND &hwndIES) {
	HWND h = FindWindowExW(hWnd, 0, 0, 0);
	while (h) {
		wchar_t szClassName[MAX_PATH + 1] = {0};
		GetClassNameW(h, szClassName, MAX_PATH);
		if (!lstrcmpW(L"Shell DocObject View", szClassName)) {
			hwndSDV = h;
			break;
		}
		else {
			X_NetWork_FindNetWorkHwnd(h, hwndSDV, hwndIES);
		}
		h = FindWindowExW(hWnd, h, 0,0);
	}
	if (hwndSDV) {
		wchar_t szClassName[MAX_PATH + 1] = { 0 };
		GetClassNameW(h, szClassName, MAX_PATH);
		if (!lstrcmpW(szClassName,L"Shell DocObject View")) {
			hwndIES = FindWindowExW(hwndSDV, 0, 0, 0);
		}
	}
}
void X_NetWork_SendMessage(HWND hWnd,int cType,int id) {
	HWND hwndSDV=0, hwndIES=0;
	X_NetWork_FindNetWorkHwnd(hWnd,hwndSDV, hwndIES);
	if (hwndSDV != 0 && hwndIES!=0) {
		if (cType == 1) {
			SendMessageW(hwndIES, 273, id, 0);
		}
		else {
			SendMessageW(hwndSDV, 273, id, 0);
		}
	}
}

//网页_保存
void X_NetWork_Save(HWND hWnd) {
	X_NetWork_SendMessage(hWnd,0, 258);
}

//网页_保存html
void X_NetWork_SaveHTML(HWND hWnd) {
	X_NetWork_SendMessage(hWnd,0, 71);
}

//网页_查看网页属性
void X_NetWork_ViewProperties(HWND hWnd) {
	X_NetWork_SendMessage(hWnd, 0, 28);
}

//网页_查找关键字
void X_NetWork_FindKeyword(HWND hWnd) {
	X_NetWork_SendMessage(hWnd, 0, 67);
}

//网页_打印
void X_NetWork_Print(HWND hWnd) {
	X_NetWork_SendMessage(hWnd, 0, 260);
}

//网页_打印预览
void X_NetWork_PrintView(HWND hWnd) {
	X_NetWork_SendMessage(hWnd, 0, 93);
}

CXText _X_Coding_AToW(const char* c, size_t m_encode)
{
	int len = MultiByteToWideChar(m_encode, 0, c, strlen(c), NULL, 0);
	wchar_t* l_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(m_encode, 0, c, strlen(c), l_wchar, len);
	l_wchar[len] = '\0';
	CXText rets = l_wchar;
	delete[] l_wchar;
	return rets;
}
//网页_取IP地址A
X_IPAscriptionA X_NetWork_GetIPAscriptionA(CXTextA IP) {
	CXText rip = L"https://ip.taobao.com/outGetIpInfo?ip="; ;
	rip += (strcmp(IP, "") != 0) ? A2W(IP) : L"myip";
	rip += L"&accessKey=alibaba-inc";
	CXWinHttp h(rip);
	h.Send();
	X_IPAscriptionA r;
	CXTextA rdata;
	h.GetResponseBodyText_Utf8ToA(rdata);
	r.IP = X_String_GetMiddleTextA(rdata,"\"ip\":","\",");
	r.IP = r.IP.substr(1, r.IP.size()-1);
	r.Country= X_String_GetMiddleTextA(rdata, "\"country\":", "\",");
	r.Country = r.Country.substr(1, r.Country.size() - 1);
	r.Region = X_String_GetMiddleTextA(rdata, "\"region\":", "\",");
	r.Region = r.Region.substr(1, r.Region.size() - 1);
	r.City = X_String_GetMiddleTextA(rdata, "\"city\":", "\",");
	r.City = r.City.substr(1, r.City.size() - 1);
	r.Isp = X_String_GetMiddleTextA(rdata, "\"isp\":", "\",");
	r.Isp = r.Isp.substr(1, r.Isp.size() - 1);
	return r;
}
//网页_取IP地址
X_IPAscription X_NetWork_GetIPAscription(CXText IP) {
	CXText rip = L"https://ip.taobao.com/outGetIpInfo?ip="; ;
	rip += (lstrcmpW(IP, L"") != 0)? IP: L"myip";
	rip += L"&accessKey=alibaba-inc";
	CXWinHttp h(rip);
	h.Send();
	X_IPAscription r;
	CXTextA rdataraw;
	h.GetResponseBodyText_Utf8ToA(rdataraw);
	CXText rdata = _X_Coding_AToW(rdataraw,CP_ACP);
	r.IP = (X_String_GetMiddleText(rdata, L"\"ip\":", L"\","));
	r.IP = r.IP.substr(1, r.IP.size() - 1);
	r.Country = (X_String_GetMiddleText(rdata, L"\"country\":", L"\","));
	r.Country = r.Country.substr(1, r.Country.size() - 1);
	r.Region = (X_String_GetMiddleText(rdata, L"\"region\":", L"\","));
	r.Region = r.Region.substr(1, r.Region.size() - 1);
	r.City = (X_String_GetMiddleText(rdata, L"\"city\":", L"\","));
	r.City = r.City.substr(1, r.City.size() - 1);
	r.Isp = (X_String_GetMiddleText(rdata, L"\"isp\":", L"\","));
	r.Isp = r.Isp.substr(1, r.Isp.size() - 1);
	return r;
}

//网页_取编码
CXText X_NetWork_GetHtmlCodeing(CXText url) {
	CXBytes data = X_NetWork_Visit(url);
	CXTextA tmp = data.getMid(0,1024).getTextPtrA();
	X_String_RegexA reg("<meta.+?charset=[^\\w]?([-\\w]+)", tmp);
	CXTextA u = reg.SearchSub(0,0);
	return A2W(u);
}
//网页_取编码A
CXTextA X_NetWork_GetHtmlCodeingA(CXTextA url) {
	CXBytes data = X_NetWork_Visit(A2W(url));
	CXTextA tmp = data.getMid(0, 1024).getTextPtrA();
	X_String_RegexA reg("<meta.+?charset=[^\\w]?([-\\w]+)", tmp);
	return reg.SearchSub(0, 0);
}

CXText _X_NetWork_GetCookie(CXText cookie, CXText cookieName) {
	CXVector<CXText>cookies=X_String_SplitWithStl(cookie,L";");
	CXText r;
	for (int i = 0; i < (int)cookies.size();i++) {
		CXText name = X_String_Trim(X_String_GetLeft(cookies[i],L"="));
		if(!_wcsicmp(name, cookieName)) {
			CXText t = X_String_Trim(cookies[i]);
			if(t.find(L":")!=-1) {
				r = X_String_GetMiddleText(t,L"=",L":"); break;
			}
			r = X_String_GetRight(t,L"="); break;
		}
	}
	return r;
}
CXTextA _X_NetWork_GetCookieA(CXTextA cookie, CXTextA cookieName) {
	CXVector<CXTextA>cookies = X_String_SplitWithStlA(cookie, ";");
	CXTextA r;
	for (int i = 0; i < (int)cookies.size(); i++) {
		CXTextA name = X_String_TrimA(X_String_GetLeftA(cookies[i], "="));
		if (!_stricmp(name, cookieName)) {
			CXTextA t = X_String_TrimA(cookies[i]);
			if (t.find(":") != -1) {
				r = X_String_GetMiddleTextA(t, "=", ":"); break;
			}
			r = X_String_GetRightA(t, "="); break;
		}
	}
	return r;
}

//网页_取单条Cookie
CXText X_NetWork_GetCookie(CXText cookie, CXText Name,bool NoName) {
	cookie = X_String_Trim(cookie);
	if (cookie.size() < 1) { return L""; }
	if(cookie[cookie.size()-1]==L';') {
		cookie += L";";
	}
	CXText t = _X_NetWork_GetCookie(cookie, Name);
	if (NoName || t == L"") {
		return t;
	}
	return Name+L"="+ t;
}
//网页_取单条CookieA
CXTextA X_NetWork_GetCookieA(CXTextA cookie, CXTextA Name, bool NoName) {
	cookie = X_String_TrimA(cookie);
	if (cookie.size() < 1) { return ""; }
	if (cookie[cookie.size() - 1] == ';') {
		cookie += ";";
	}
	CXTextA t = _X_NetWork_GetCookieA(cookie, Name);
	if (NoName || t == "") {
		return t;
	}
	return Name + "=" + t;
}

//网页_取端口
UINT X_NetWork_GetPort(CXText url) {
	CXText p = X_NetWork_GetHost(url,false,true);
	p = X_String_GetRight(p,L":");
	int port = X_String_TextToInt(p);
	if (port>0) {
		return port;
	}
	if (!_wcsicmp(url.substr(0, 5),L"https")) {
		return 443;
	}
	return 80;
}
//网页_取端口
UINT X_NetWork_GetPortA(CXTextA url) {
	CXTextA p = X_NetWork_GetHostA(url, false, true);
	p = X_String_GetRightA(p, ":");
	int port = X_String_TextToIntA(p);
	if (port > 0) {
		return port;
	}
	if (!_stricmp(url.substr(0, 5), "https")) {
		return 443;
	}
	return 80;
}

//网页_取域名
CXText X_NetWork_GetHost(CXText url,bool delSL,bool addPort,int suffixNum) {
	if (url.size() < 1) { return L""; }
	if(suffixNum<1){
		if (url[url.size()-1]!=L'/') {
			url += L"/";
		}
		if (_wcsicmp(L"https://", url.substr(0,8))) {
			if (_wcsicmp(L"http://", url.substr(0, 7))) {
				url = L"http://" + url;
			}
			url = X_String_GetMiddleText(url,L"http://",L"/");
		}
		else {
			url = X_String_GetMiddleText(url, L"https://", L"/");
		}
		if (delSL) {
			CXVector<CXText> two = X_String_SplitWithStl(url,L".");
			int index = two.size();
			if (index>1) {
				//域名 ＝ 二级 [位置 － 1] ＋ “.” ＋ 二级 [位置]
				url = two[index - 2] + L"." + two[index - 1];
			}
		}
	}
	else {
		url = X_String_Subreplace(url,L"http://",L"");
		url = X_String_Subreplace(url,L"https://",L"");
		std::wstring wsurl = url.get();
		UINT index = wsurl.find(L'/');
		if (index!=-1) {
			wsurl = wsurl.substr(0, index);
		}
		UINT urlLen, doLast,doLeft=0; urlLen = doLast = wsurl.length();
		for (int i = 0; i < suffixNum;i++) {
			doLast = wsurl.rfind(L".", doLast-1);
		}
		doLeft = wsurl.rfind(L".", doLast-1);
		if (delSL) {
			wsurl = wsurl.substr(doLeft+1, urlLen - doLeft);
		}
		else {
			if(doLeft !=-1){
				UINT LeftOpen = wsurl.rfind(L'.', doLeft -1);
				if (LeftOpen!=-1) {
					//域名 ＝ 取文本右边 (域名, 域名长度 － 前点开始)
					wsurl = wsurl.substr(LeftOpen+1, urlLen - LeftOpen);
				}
			}
		}
		url = wsurl;
	}
	if(addPort) {
		return url;
	}
	else {
		UINT index= url.find(L":");
		if (index!=-1) {
			return url.substr(0, index);
		}
		else {
			return url;
		}
	}
	return L"";
}
//网页_取域名A
CXTextA X_NetWork_GetHostA(CXTextA url, bool delSL, bool addPort, int suffixNum) {
	if (url.size() < 1) { return ""; }
	if (suffixNum < 1) {
		if (url[url.size() - 1] != '/') {
			url += "/";
		}
		if (_stricmp("https://", url.substr(0, 8))) {
			if (_stricmp("http://", url.substr(0, 7))) {
				url = "http://" + url;
			}
			url = X_String_GetMiddleTextA(url, "http://", "/");
		}
		else {
			url = X_String_GetMiddleTextA(url, "https://", "/");
		}
		if (delSL) {
			CXVector<CXTextA> two = X_String_SplitWithStlA(url, ".");
			int index = two.size();
			if (index > 1) {
				//域名 ＝ 二级 [位置 － 1] ＋ “.” ＋ 二级 [位置]
				url = two[index - 2] + L"." + two[index - 1];
			}
		}
	}
	else {
		url = X_String_SubreplaceA(url, "http://", "");
		url = X_String_SubreplaceA(url, "https://", "");
		std::string wsurl = url.get();
		UINT index = wsurl.find('/');
		if (index != -1) {
			wsurl = wsurl.substr(0, index);
		}
		UINT urlLen, doLast, doLeft = 0; urlLen = doLast = wsurl.length();
		for (int i = 0; i < suffixNum; i++) {
			doLast = wsurl.rfind(".", doLast - 1);
		}
		doLeft = wsurl.rfind(".", doLast - 1);
		if (delSL) {
			wsurl = wsurl.substr(doLeft + 1, urlLen - doLeft);
		}
		else {
			if (doLeft != -1) {
				UINT LeftOpen = wsurl.rfind(".", doLeft - 1);
				if (LeftOpen != -1) {
					//域名 ＝ 取文本右边 (域名, 域名长度 － 前点开始)
					wsurl = wsurl.substr(LeftOpen + 1, urlLen - LeftOpen);
				}
			}
		}
		url = wsurl;
	}
	if (addPort) {
		return url;
	}
	else {
		UINT index = url.find(":");
		if (index != -1) {
			return url.substr(0, index);
		}
		else {
			return url;
		}
	}
	return "";
}

//网页_取快捷方式地址
CXText X_NetWork_GetShortcut(CXText path,DWORD buffSize) {
	if (buffSize <= 0) {
		buffSize = 2048;
	}
	wchar_t* lpReturnedString=new wchar_t[buffSize];
	GetPrivateProfileStringW(L"InternetShortcut", L"URL", NULL, lpReturnedString, buffSize, path);
	CXText r = lpReturnedString;
	delete[]lpReturnedString;
	return r;
}
//网页_取快捷方式地址A
CXTextA X_NetWork_GetShortcutA(CXTextA path, DWORD buffSize) {
	if (buffSize <= 0) {
		buffSize = 2048;
	}
	char* lpReturnedString = new char[buffSize];
	GetPrivateProfileStringA("InternetShortcut", "URL", NULL, lpReturnedString, buffSize, path);
	CXTextA r = lpReturnedString;
	delete[]lpReturnedString;
	return r;
}

//网页_取网络文件名
CXText X_NetWork_GetFileName(CXText url) {
	CXWinHttp h;
	if (!h.Open(url)) { return L""; }
	if (!h.Send()) { return  L""; }
	CXText hs = h.GetAllResponseHeaders();
	return X_String_GetMiddleText(hs, L"filename=\"", L"\"");
}
//网页_取网络文件名A
CXTextA X_NetWork_GetFileNameA(CXTextA url) {
	CXWinHttp h;
	if (!h.Open(A2W(url))) { return ""; }
	if (!h.Send()) { return  ""; }
	CXText hs = h.GetAllResponseHeaders();
	return W2A(X_String_GetMiddleText(hs, L"filename=\"", L"\""));
}

// 网页_取网址文件名
CXText X_NetWork_GetUrlName(CXText url) {
	std::wstring* rs=url.getString();
	UINT index=rs->rfind(L"/");
	return index == -1 ? L"" : rs->substr(index + 1, rs->length()- index -1);
}
// 网页_取网址文件名A
CXTextA X_NetWork_GetUrlNameA(CXTextA url) {
	std::string* rs = url.getString();
	UINT index = rs->rfind("/");
	return index == -1 ? "" : rs->substr(index + 1, rs->length() - index - 1);
}

//网页_取页面地址
CXText X_NetWork_GetPath(CXText url) {
	std::wstring* wu = url.getString();
	UINT index = wu->find(L"//");
	index = (index == -1) ? 0 : index+2;
	index=wu->find(L"/", index);
	if (index == -1) {return L"/";}
	CXText r = wu->substr(index + 1, wu->length() - index);
	if (lstrcmpW(r, L"") == 0) { return L"/"; }
	return r;
}
//网页_取页面地址
CXTextA X_NetWork_GetPathA(CXTextA url) {
	std::string* wu = url.getString();
	UINT index = wu->find("//");
	index = (index == -1) ? 0 : index + 2;
	index = wu->find("/", index);
	if (index == -1) { return "/"; }
	CXTextA r = wu->substr(index + 1, wu->length() - index);
	if (strcmp(r, "") == 0) { return "/"; }
	return r;
}

//网页_全选
void X_NetWork_SelectAll(HWND hWnd) {
	X_NetWork_SendMessage(hWnd, 0, 31);
}

//网页_设置网页字体
void X_NetWork_SetPageFonts(HWND hWnd) {
	X_NetWork_SendMessage(hWnd, 0, 90); 
}

//网页_网络文件是否存在
bool X_NetWork_FileIfExistence(CXText url) {
	CXWinHttp w(url);
	w.SetRedirect(true);
	w.Send();
	return (w.GetStatus() == 200);
}
//网页_网络文件是否存在
bool X_NetWork_FileIfExistenceA(CXTextA url) {
	CXWinHttp w(A2W(url));
	w.SetRedirect(true);
	w.Send();
	return (w.GetStatus() == 200);
}

//网页_取协议头信息
CXText X_NetWork_GetHeaderInfo(CXText Headers,CXText Key) {
	auto arr = X_String_SplitWithStl(Headers,L"\n");
	UINT lk = Key.size();
	CXText r;
	for (int i = 0; i < (int)arr.size();i++) {
		if (_wcsicmp(arr[i].substr(0, lk), Key) == 0) {
			r = arr[i].substr(lk+1, arr[i].size()- lk);
			r = X_String_Trim(r);
			break;
		}
	}
	return r;
}
//网页_取协议头信息A
CXTextA X_NetWork_GetHeaderInfoA(CXTextA Headers, CXTextA Key) {
	auto arr = X_String_SplitWithStlA(Headers, "\n");
	UINT lk = Key.size();
	CXTextA r;
	for (int i = 0; i < (int)arr.size(); i++) {
		if (_stricmp(arr[i].substr(0, lk), Key) == 0) {
			r = arr[i].substr(lk + 1, arr[i].size() - lk);
			r = X_String_TrimA(r);
			break;
		}
	}
	return r;
}

//网页_置浏览器UA
bool X_NetWork_SetBrowserUA(CXText UserAgent) {
	return UrlMkSetSessionOption(URLMON_OPTION_USERAGENT, (LPVOID)UserAgent.get(), UserAgent.size()+2, 0) == 0;
}
//网页_置浏览器UAA
bool X_NetWork_SetBrowserUAA(CXTextA UserAgent) {
	return UrlMkSetSessionOption(URLMON_OPTION_USERAGENT, (LPVOID)UserAgent.get(), UserAgent.size() + 1, 0) == 0;
}

//网址_取所有参数
int X_NetWork_GetAllParameter(CXText Url,CXMap<CXText,CXText>& ret) {
	ret.clear();
	UINT p = Url.find(L"?");
	if (p==-1) {
		return 0;
	}
	p++;
	std::wstring sp = Url.substr(p, Url.size()-p).get();
	auto arr=X_String_SplitWithStl(sp,L"&");
	for (int i = 0; i < (int)arr.size();i++) {
		UINT wi = arr[i].find(L"=");
		ret[arr[i].substr(0, wi)]= arr[i].substr(wi + 1, arr[i].size() - wi);
	}
	return ret.size();
}
//网址_取所有参数A
int X_NetWork_GetAllParameterA(CXTextA Url, CXMap<CXTextA, CXTextA>& ret) {
	ret.clear();
	UINT p = Url.find("?");
	if (p == -1) {
		return 0;
	}
	p++;
	std::string sp = Url.substr(p, Url.size() - p).get();
	auto arr = X_String_SplitWithStlA(sp, "&");
	for (int i = 0; i < (int)arr.size(); i++) {
		UINT wi = arr[i].find("=");
		ret[arr[i].substr(0, wi)] = arr[i].substr(wi + 1, arr[i].size() - wi);
	}
	return ret.size();
}