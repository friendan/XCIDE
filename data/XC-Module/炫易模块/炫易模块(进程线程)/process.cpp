//
// Created by Huiyi on 2022/10/01.
//
#include "module_e_ProcessThread.h"
#include <ShlObj.h>
#pragma  comment(lib, "psapi.lib")

///---------------------------

//进程_ID取进程名W
CXText X_Process_GetNameByIDW(DWORD PID) {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	CXText r;
	if (hProcessSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32W pe32={0};
		pe32.dwSize = sizeof(pe32);
		BOOL b = Process32NextW(hProcessSnap, &pe32);
		while (b>0) {
			if (pe32.th32ProcessID == PID) {
				r = pe32.szExeFile;
				break;
			}
			b = Process32NextW(hProcessSnap, &pe32);
		}
		CloseHandle(hProcessSnap);
	}
	return r;
}

//进程_ID取进程名A
CXTextA X_Process_GetNameByIDA(DWORD PID) {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	CXTextA r;
	if (hProcessSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 pe32 = { 0 };
		pe32.dwSize = sizeof(pe32);
		BOOL b = Process32Next(hProcessSnap, &pe32);
		while (b > 0) {
			if (pe32.th32ProcessID == PID) {
				r = W2A(pe32.szExeFile);
				break;
			}
			b = Process32NextW(hProcessSnap, &pe32);
		}
		CloseHandle(hProcessSnap);
	}
	return r;
}

//进程_DEP保护
BOOL X_Program_DEPProtect(DWORD dwFlags) {
	if (GetSystemDEPPolicy() < DEP_SYSTEM_POLICY_TYPE::DEPPolicyOptIn) {
		return false;
	}
	return SetProcessDEPPolicy(dwFlags);
}

//进程_DLL取自身信息A
X_Process_ModuleInfoA X_Program_GetModuleInfoA() {
	LPCSTR lpModuleName=NULL;
	HMODULE hModule=NULL;
	X_Process_ModuleInfoA r;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, lpModuleName, &hModule);
	if (!hModule) {
		auto hProcess = GetCurrentProcess();
		char szBaseName [_MAX_PATH] = {0};
		auto dwSize = GetModuleBaseNameA(hProcess, hModule, szBaseName, _MAX_PATH);
		if (dwSize>0) {
			r.BaseName = szBaseName;
		}
		char szFileName[_MAX_PATH] = {0};
		dwSize = GetModuleFileNameA(hModule, szFileName, _MAX_PATH);
		if (dwSize>0) {
			r.FileName = szFileName;
		}
		r.hModule = hModule;
	}
	return r;
}
//进程_DLL取自身信息W
X_Process_ModuleInfoW X_Program_GetModuleInfoW() {
	LPWSTR lpModuleName = NULL;
	HMODULE hModule = NULL;
	X_Process_ModuleInfoW r;
	BOOL err = GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, lpModuleName, &hModule);
	if (!hModule) {
		auto hProcess = GetCurrentProcess();
		wchar_t szBaseName[_MAX_PATH] = { 0 };
		auto dwSize = GetModuleBaseNameW(hProcess, hModule, szBaseName, _MAX_PATH);
		if (dwSize > 0) {
			r.BaseName = szBaseName;
		}
		wchar_t szFileName[_MAX_PATH] = { 0 };
		dwSize = GetModuleFileNameW(hModule, szFileName, _MAX_PATH);
		if (dwSize > 0) {
			r.FileName = szFileName;
		}
		r.hModule = hModule;
	}
	return r;
}

X_Process_ModuleInfoA X_Program_GetModuleInfoExA(const char* ModuleName) {
	X_Process_ModuleInfoA ModuleInfo;
	auto hProcess = GetCurrentProcess();
	auto hModule = (strcmp(ModuleName, "") == 0) ? GetModuleHandleA(NULL): GetModuleHandleA(ModuleName);
	if (!hModule) {
		return ModuleInfo;
	};
	MEMORY_BASIC_INFORMATION mbi;
	if (!VirtualQueryEx(hProcess, hModule, &mbi, sizeof(mbi))) { 
		return ModuleInfo; 
	};
	char szBaseName[_MAX_PATH] = { 0 };
	DWORD dwSize = GetModuleBaseNameA(hProcess, (HMODULE)mbi.AllocationBase, szBaseName, _MAX_PATH);
	if (dwSize>0) {
		ModuleInfo.BaseName = szBaseName;
	}
	char szFileName[_MAX_PATH] = { 0 };
	dwSize = GetModuleFileNameA(hModule, szFileName, _MAX_PATH);
	if (dwSize>0) {
		ModuleInfo.FileName = szFileName;
	}
	ModuleInfo.hModule = (HMODULE)mbi.AllocationBase;
	return ModuleInfo;
}
X_Process_ModuleInfoW X_Program_GetModuleInfoExW(const wchar_t* ModuleName) {
	X_Process_ModuleInfoW ModuleInfo;
	auto hProcess = GetCurrentProcess();
	auto hModule = (wcscmp(ModuleName, L"") == 0) ? GetModuleHandleW(NULL) : GetModuleHandleW(ModuleName);
	if (!hModule) {
		return ModuleInfo;
	};
	MEMORY_BASIC_INFORMATION mbi;
	if (!VirtualQueryEx(hProcess, hModule, &mbi, sizeof(mbi))) {
		return ModuleInfo;
	};
	wchar_t szBaseName[_MAX_PATH] = { 0 };
	DWORD dwSize = GetModuleBaseNameW(hProcess, (HMODULE)mbi.AllocationBase, szBaseName, _MAX_PATH);
	if (dwSize > 0) {
		ModuleInfo.BaseName = szBaseName;
	}
	wchar_t szFileName[_MAX_PATH] = { 0 };
	dwSize = GetModuleFileNameW(hModule, szFileName, _MAX_PATH);
	if (dwSize > 0) {
		ModuleInfo.BaseName = szFileName;
	}
	ModuleInfo.hModule = (HMODULE)mbi.AllocationBase;
	return ModuleInfo;
}

HWND X_Program_FindHWNDByIDA(DWORD pid,const char* title,const char* className,DWORD timeOut,bool isVisual) {
	LONGLONG dwStartTime = GetTickCount64();
	DWORD dwEndTime = timeOut <= 0 ? 31536000 : timeOut;
	HWND hWnd = NULL;
	DWORD dwProcessId=0;
	while (GetTickCount64() - dwStartTime < dwEndTime) {
		hWnd = FindWindowExA(NULL, hWnd, NULL, NULL);
		if (!hWnd) {
			break;
		}
		if (isVisual) {
			if (!IsWindowVisible(hWnd)) {
				continue;
			}
		}
		GetWindowThreadProcessId(hWnd, &dwProcessId);
		if (dwProcessId == pid && GetParent(hWnd) == NULL) {
			char tpClass[_MAX_PATH] = {0};
			std::string szClass;
			std::string szTitle;
			DWORD dwTitle;
			GetClassNameA(hWnd, tpClass, _MAX_PATH);
			szClass = tpClass;
			dwTitle = GetWindowTextLengthA(hWnd);
			if (dwTitle>0) {
				char* tpTitle = new char[dwTitle+1];
				memset(tpTitle,0, dwTitle + 1);
				GetWindowTextA(hWnd, tpTitle, dwTitle);
				szTitle = tpTitle;
				delete[] tpTitle;
			}
			
			if (strcmp(title,"")==0 && strcmp(className,"")==0) {
				return hWnd;
			}
			else if (strcmp(title, "") == 0) {
				if (szClass.find(className)!=std::string::npos) {
					return hWnd;
				}
			}
			else if (strcmp(className, "") == 0) {
				if (szTitle.find(title) != std::string::npos) {
					return hWnd;
				}
			}
			else {
				return hWnd;
			}
		}
		xcl_doMessage();
	}
	return NULL;
}
HWND X_Program_FindHWNDByIDW(DWORD pid, const wchar_t* title, const wchar_t* className, DWORD timeOut, bool isVisual) {
	LONGLONG dwStartTime = GetTickCount64();
	DWORD dwEndTime = timeOut <= 0 ? 31536000 : timeOut;
	HWND hWnd = NULL;
	DWORD dwProcessId = 0;
	while (GetTickCount64() - dwStartTime < dwEndTime) {
		hWnd = FindWindowExA(NULL, hWnd, NULL, NULL);
		if (!hWnd) {
			break;
		}
		if (isVisual) {
			if (!IsWindowVisible(hWnd)) {
				continue;
			}
		}
		GetWindowThreadProcessId(hWnd, &dwProcessId);
		if (dwProcessId == pid && GetParent(hWnd) == NULL) {
			wchar_t tpClass[_MAX_PATH] = { 0 };
			std::wstring szClass;
			std::wstring szTitle;
			DWORD dwTitle;
			GetClassNameW(hWnd, tpClass, _MAX_PATH);
			szClass = tpClass;
			dwTitle = GetWindowTextLengthW(hWnd);
			if (dwTitle > 0) {
				wchar_t* tpTitle = new wchar_t[dwTitle + 1];
				memset(tpTitle, 0, dwTitle + 1);
				GetWindowTextW(hWnd, tpTitle, dwTitle);
				szTitle = tpTitle;
				delete[] tpTitle;
			}

			if (wcscmp(title, L"") == 0 && wcscmp(className, L"") == 0) {
				return hWnd;
			}
			else if (wcscmp(title, L"") == 0) {
				if (szClass.find(className) != std::wstring::npos) {
					return hWnd;
				}
			}
			else if (wcscmp(className, L"") == 0) {
				if (szTitle.find(title) != std::wstring::npos) {
					return hWnd;
				}
			}
			else {
				return hWnd;
			}
		}
		xcl_doMessage();
	}
	return NULL;
}

CXTextA X_Program_GetProcessNameByIDExA(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (hProcess == NULL) {
		// 打开进程失败
		return "";
	}
	CXTextA r;
	// 获取进程的可执行文件名
	char szProcessName[_MAX_PATH] = "";
	if (GetModuleFileNameExA(hProcess, NULL, szProcessName, _MAX_PATH)) {
		std::string lStr = szProcessName;
		auto index = lStr.rfind("\\");
		r = (index != -1) ? lStr.substr(index + 1, lStr.length() - index - 1) : lStr;
	}
	else {
		// 获取进程名失败
		r = "";
	}
	// 关闭进程句柄
	CloseHandle(hProcess);
	return r;
}
CXText X_Program_GetProcessNameByIDExW(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (hProcess == NULL) {
		// 打开进程失败
		return L"";
	}
	CXText r;
	// 获取进程的可执行文件名
	wchar_t szProcessName[_MAX_PATH] = L"";
	if (GetModuleFileNameExW(hProcess, NULL, szProcessName, _MAX_PATH)) {
		std::wstring lStr = szProcessName;
		auto index = lStr.rfind(L"\\");
		r = (index != -1)? lStr.substr(index+1, lStr.length()- index-1): lStr;
	}
	else {
		// 获取进程名失败
		r = L"";
	}
	// 关闭进程句柄
	CloseHandle(hProcess);
	return r;
}

HMODULE m_hKernel32LibA = nullptr;
UINT X_Program_GetModuleListByIdA(DWORD pid,CXVector<tagMODULEENTRY32>&ret) {
	ret.clear();
	auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (handle== INVALID_HANDLE_VALUE) {
		return 0;
	}
	//别问我为什么要这怎么写,你自己试试就知道了
	m_hKernel32LibA = m_hKernel32LibA==nullptr?LoadLibraryA("Kernel32.dll"): m_hKernel32LibA;
	if (m_hKernel32LibA == nullptr) {
		return 0;
	}
	typedef BOOL (WINAPI *Module32FirstAFUNC)(HANDLE, tagMODULEENTRY32*);
	typedef BOOL (WINAPI *Module32NextAFUNC)(HANDLE, tagMODULEENTRY32*);
	Module32FirstAFUNC pfnMF = (Module32FirstAFUNC)GetProcAddress(m_hKernel32LibA, "Module32First");
	Module32FirstAFUNC pfnMN = (Module32FirstAFUNC)GetProcAddress(m_hKernel32LibA, "Module32Next");
	if (pfnMF==NULL || pfnMN== NULL) {
		return 0;
	}
	tagMODULEENTRY32 modleInfo;
	modleInfo.dwSize = sizeof(modleInfo);
	auto phandle = pfnMF(handle,&modleInfo);
	while (phandle)
	{
		ret.add(modleInfo);
		phandle = pfnMN(handle,&modleInfo);
	}
	CloseHandle(handle);
	return ret.size();
}
UINT X_Program_GetModuleListByIdW(DWORD pid, CXVector<tagMODULEENTRY32W>& ret) {
	ret.clear();
	auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (handle == INVALID_HANDLE_VALUE) {
		return 0;
	}
	tagMODULEENTRY32W modleInfo;
	modleInfo.dwSize = sizeof(modleInfo);
	auto phandle = Module32FirstW(handle, &modleInfo);
	while (phandle)
	{
		ret.add(modleInfo);
		phandle = Module32NextW(handle, &modleInfo);
	}
	CloseHandle(handle);
	return ret.size();
}

UINT X_Program_GetModuleHandleListById(DWORD pid, CXVector<HMODULE>& ret) {
	ret.clear();
	HANDLE hProcess = pid == NULL? GetCurrentProcess(): OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, 0, pid);
	if (hProcess==NULL) {
		return NULL;
	}
	DWORD dwSize;
	EnumProcessModulesEx(hProcess, NULL, 0, &dwSize, LIST_MODULES_ALL);
	if (dwSize==NULL) {
		CloseHandle(hProcess);
		return NULL;
	}
	auto len = dwSize / sizeof(HMODULE);
	ret.getVector()->reserve(len);
	ret.getVector()->resize(len);
	EnumProcessModulesEx(hProcess, &ret[0], len, &dwSize, LIST_MODULES_ALL);
	ret.getVector()->erase(ret.getVector()->begin());
	CloseHandle(hProcess);
	return ret.size();
}

bool X_Program_ProcessExist(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
	if (hProcess == NULL) {
		return false;
	}
	CloseHandle(hProcess);
	return true;
}

UINT X_Program_GetPortByID(DWORD pid){
	DWORD r = 0;
	DWORD dwSize;
	//检索tcp
	GetExtendedTcpTable(NULL, &dwSize, TRUE, AF_INET, TCP_TABLE_CLASS::TCP_TABLE_OWNER_PID_ALL, 0);
	if (!dwSize) {
		return 0;
	}
	PMIB_TCPTABLE_OWNER_PID pTable = (PMIB_TCPTABLE_OWNER_PID)LocalAlloc(LMEM_ZEROINIT, dwSize);
	DWORD dwRet = GetExtendedTcpTable(pTable, &dwSize, TRUE, AF_INET, TCP_TABLE_CLASS::TCP_TABLE_OWNER_PID_ALL, 0);
	if (dwRet== NO_ERROR && pTable!=nullptr) {
		for (DWORD i = 0; i < pTable->dwNumEntries;i++) {
			if (pid== pTable->table[i].dwOwningPid) {
				r = ntohs((short)pTable->table[i].dwLocalPort); break;
			}
		}

	}
	LocalFree((HLOCAL)pTable);
	if (r!=NULL) {
		return r;
	}
	//检索udp
	dwSize = 0;
	GetExtendedUdpTable(NULL, &dwSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0);
	if (dwSize==0) {
		return 0;
	}
	pTable = NULL;
	pTable = (PMIB_TCPTABLE_OWNER_PID)LocalAlloc(LMEM_ZEROINIT, dwSize);
	dwRet = GetExtendedUdpTable(pTable, &dwSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0);
	if (dwRet == NO_ERROR && pTable != nullptr) {
		for (DWORD i = 0; i < pTable->dwNumEntries; i++) {
			if (pid == pTable->table[i].dwOwningPid) {
				r = ntohs((short)pTable->table[i].dwLocalPort); break;
			}
		}
	}
	LocalFree((HLOCAL)pTable);
	return r;
}
UINT X_Program_GetIDByPort(DWORD port) {
	DWORD r = 0;
	DWORD dwSize;
	//检索tcp
	GetExtendedTcpTable(NULL, &dwSize, TRUE, AF_INET, TCP_TABLE_CLASS::TCP_TABLE_OWNER_PID_ALL, 0);
	if (!dwSize) {
		return 0;
	}
	PMIB_TCPTABLE_OWNER_PID pTable = (PMIB_TCPTABLE_OWNER_PID)LocalAlloc(LMEM_ZEROINIT, dwSize);
	DWORD dwRet = GetExtendedTcpTable(pTable, &dwSize, TRUE, AF_INET, TCP_TABLE_CLASS::TCP_TABLE_OWNER_PID_ALL, 0);
	if (dwRet == NO_ERROR && pTable != nullptr) {
		for (DWORD i = 0; i < pTable->dwNumEntries; i++) {
			if (port == ntohs((short)pTable->table[i].dwLocalPort)) {
				r = pTable->table[i].dwOwningPid; break;
			}
		}

	}
	LocalFree((HLOCAL)pTable);
	if (r != NULL) {
		return r;
	}
	//检索udp
	dwSize = 0;
	GetExtendedUdpTable(NULL, &dwSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0);
	if (dwSize == 0) {
		return 0;
	}
	pTable = NULL;
	pTable = (PMIB_TCPTABLE_OWNER_PID)LocalAlloc(LMEM_ZEROINIT, dwSize);
	dwRet = GetExtendedUdpTable(pTable, &dwSize, TRUE, AF_INET, UDP_TABLE_CLASS::UDP_TABLE_OWNER_PID, 0);
	if (dwRet == NO_ERROR && pTable != nullptr) {
		for (DWORD i = 0; i < pTable->dwNumEntries; i++) {
			if (port == ntohs( (short) pTable->table[i].dwLocalPort)) {
				r = pTable->table[i].dwOwningPid; break;
			}
		}
	}
	LocalFree((HLOCAL)pTable);
	return r;
}

CXText X_Program_GetPathByIDW(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (hProcess == NULL)
	{
		std::cout << "Failed to open process: " << GetLastError() << std::endl;
		xcl_log("Failed to open process: ", GetLastError());
		return L"";
	}
	// 缓冲区
	wchar_t buffer[_MAX_PATH];
	// 获取进程的可执行文件的全路径
	if (GetModuleFileNameExW(hProcess, NULL, buffer, _MAX_PATH) == 0)
	{
		std::cout << "Failed to get module file name: " << GetLastError() << std::endl;
		xcl_log("Failed to get module file name: ", GetLastError());
		return L"";
	}
	CloseHandle(hProcess);
	return buffer;
}
CXTextA X_Program_GetPathByIDA(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (hProcess == NULL)
	{
		std::cout << "Failed to open process: " << GetLastError() << std::endl;
		xcl_log("Failed to open process: ", GetLastError());
		return "";
	}
	// 缓冲区
	char buffer[_MAX_PATH];
	// 获取进程的可执行文件的全路径
	if (GetModuleFileNameExA(hProcess, NULL, buffer, _MAX_PATH) == 0)
	{
		std::cout << "Failed to get module file name: " << GetLastError() << std::endl;
		xcl_log("Failed to get module file name: ", GetLastError());
		return "";
	}
	CloseHandle(hProcess);
	return buffer;
}

UINT X_Program_EnumProcessByUserNameA(CXTextA UserName, CXVector<DWORD>& ret) {
	ret.clear();
	// 获取系统中所有进程的 PID
	DWORD pids[2048];
	DWORD bytesReturned;
	if (!EnumProcesses(pids, sizeof(pids), &bytesReturned)) {
		return 0;
	}
	// 计算返回的进程数量
	int numProcesses = bytesReturned / sizeof(DWORD);
	// 遍历所有进程
	for (int i = 0; i < numProcesses; i++)
	{
		// 打开进程
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pids[i]);
		if (hProcess == NULL)
		{
			continue;
		}
		// 获取进程令牌
		HANDLE hToken;
		if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
		{
			CloseHandle(hProcess);
			continue;
		}
		// 获取令牌用户信息
		DWORD cbSize;
		GetTokenInformation(hToken, TokenUser, NULL, 0, &cbSize);
		PTOKEN_USER pTokenUser = (PTOKEN_USER)GlobalAlloc(GPTR, cbSize);
		if (pTokenUser != NULL)
		{
			if (GetTokenInformation(hToken, TokenUser, pTokenUser, cbSize, &cbSize))
			{
				// 获取用户名
				char szUserName[_MAX_PATH];
				DWORD cchUserName = _MAX_PATH;
				char szADName[_MAX_PATH];
				DWORD cchADName = _MAX_PATH;
				SID_NAME_USE snu;
				if (LookupAccountSidA(NULL, pTokenUser->User.Sid, szUserName, &cchUserName, szADName, &cchADName, &snu))
				{
					// 比较用户名是否匹配
					if (strcmp(szUserName, UserName) == 0)
					{
						ret.add(pids[i]);
					}
				}
			}
			GlobalFree(pTokenUser);
		}
		// 关闭句柄
		CloseHandle(hToken);
		CloseHandle(hProcess);
	}
	return ret.size();
}
UINT X_Program_EnumProcessByUserNameW(CXText UserName, CXVector<DWORD>& ret) {
	ret.clear();
	// 获取系统中所有进程的 PID
	DWORD pids[2048];
	DWORD bytesReturned;
	if (!EnumProcesses(pids, sizeof(pids), &bytesReturned)) {
		//_tprintf(_T("EnumProcesses failed (%d)\n"), GetLastError());
		//return 1;
		return 0;
	}
	// 计算返回的进程数量
	int numProcesses = bytesReturned / sizeof(DWORD);
	// 遍历所有进程
	for (int i = 0; i < numProcesses; i++)
	{
		// 打开进程
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pids[i]);
		if (hProcess == NULL)
		{
			continue;
		}
		// 获取进程令牌
		HANDLE hToken;
		if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
		{
			CloseHandle(hProcess);
			continue;
		}
		// 获取令牌用户信息
		DWORD cbSize;
		GetTokenInformation(hToken, TokenUser, NULL, 0, &cbSize);
		PTOKEN_USER pTokenUser = (PTOKEN_USER)GlobalAlloc(GPTR, cbSize);
		if (pTokenUser != NULL)
		{
			if (GetTokenInformation(hToken, TokenUser, pTokenUser, cbSize, &cbSize))
			{
				// 获取用户名
				wchar_t szUserName[_MAX_PATH];
				DWORD cchUserName = _MAX_PATH;
				wchar_t szADName[_MAX_PATH];
				DWORD cchADName = _MAX_PATH;
				SID_NAME_USE snu;
				if (LookupAccountSidW(NULL, pTokenUser->User.Sid, szUserName, &cchUserName, szADName, &cchADName, &snu))
				{
					// 比较用户名是否匹配
					if (wcscmp(szUserName, UserName) == 0)
					{
						//// 输出进程信息
						//char szProcessName[_MAX_PATH];
						//if (GetModuleBaseNameA(hProcess, NULL, szProcessName, _MAX_PATH))
						//{
						//	//_tprintf(_T("Process: %s (PID: %d)\n"), szProcessName, pids[i]);
						//	//printf_s("Process: %s (PID: %d)\n", szProcessName, pids[i]);
						//	std::cout << szUserName << std::endl;
						//}
						ret.add(pids[i]);
					}
				}
			}
			GlobalFree(pTokenUser);
		}
		// 关闭句柄
		CloseHandle(hToken);
		CloseHandle(hProcess);
	}
	return ret.size();
}

DWORD X_Program_ProcessCreateA(CXTextA ExePath, CXTextA cmd, CXTextA RunPath, PROCESS_INFORMATION* Info) {
	if (!strcmp(RunPath,"")) {
		RunPath = ExePath.substr(0, ExePath.getString()->rfind("\\"));
	}
	STARTUPINFOA info = {0};
	PROCESS_INFORMATION pInfo = { 0 };
	CreateProcessA(ExePath, (LPSTR)cmd.get(), NULL, NULL, false, NULL, NULL, RunPath, &info, &pInfo);
	if (Info != nullptr) {
		memcpy_s(Info,sizeof(PROCESS_INFORMATION),&pInfo,sizeof(pInfo));
	}
	CloseHandle(pInfo.hProcess);
	CloseHandle(pInfo.hThread);
	return pInfo.dwProcessId;
}
DWORD X_Program_ProcessCreateW(CXText ExePath, CXText cmd, CXText RunPath, PROCESS_INFORMATION* Info) {
	if (!wcscmp(RunPath, L"")) {
		RunPath = ExePath.substr(0, ExePath.getString()->rfind(L"\\"));
	}
	STARTUPINFOW info = { 0 };
	PROCESS_INFORMATION pInfo = { 0 };
	CreateProcessW(ExePath, (LPWSTR)cmd.get(), NULL, NULL, false, NULL, NULL, RunPath, &info, &pInfo);
	if (Info != nullptr) {
		memcpy_s(Info, sizeof(PROCESS_INFORMATION), &pInfo, sizeof(pInfo));
	}
	CloseHandle(pInfo.hProcess);
	CloseHandle(pInfo.hThread);
	return pInfo.dwProcessId;
}

DWORD X_Program_ProcessCreateExA(CXTextA ExePath, CXTextA cmd, bool wait, int ExplicitMode, CXTextA RunPath, PROCESS_INFORMATION* Info) {
	STARTUPINFOA wInfo = { 0 };
	wInfo.cb = sizeof(wInfo);
	wInfo.dwFlags = ExplicitMode == SW_SHOWNORMAL ?0 :1 ;
	wInfo.wShowWindow = ExplicitMode;
	PROCESS_INFORMATION pInfo = { 0 };
	CreateProcessA(ExePath, (LPSTR)cmd.get(), NULL, NULL, false, NULL, NULL, RunPath, &wInfo, &pInfo);
	if (Info != nullptr) {
		memcpy_s(Info, sizeof(PROCESS_INFORMATION), &pInfo, sizeof(pInfo));
	}
	CloseHandle(pInfo.hProcess);
	CloseHandle(pInfo.hThread);
	return pInfo.dwProcessId;
}
DWORD X_Program_ProcessCreateExW(CXText ExePath, CXText cmd, bool wait, int ExplicitMode, CXText RunPath, PROCESS_INFORMATION* Info) {
	STARTUPINFOW wInfo = { 0 };
	wInfo.cb = sizeof(wInfo);
	wInfo.dwFlags = ExplicitMode == SW_SHOWNORMAL ? 0 : 1;
	wInfo.wShowWindow = ExplicitMode;
	PROCESS_INFORMATION pInfo = { 0 };
	CreateProcessW(ExePath, (LPWSTR)cmd.get(), NULL, NULL, false, NULL, NULL, RunPath, &wInfo, &pInfo);
	if (Info != nullptr) {
		memcpy_s(Info, sizeof(PROCESS_INFORMATION), &pInfo, sizeof(pInfo));
	}
	CloseHandle(pInfo.hProcess);
	CloseHandle(pInfo.hThread);
	return pInfo.dwProcessId;
}

HANDLE X_Program_ProcessOpen(DWORD hWndOrPid) {
	DWORD dwProcessID;
	if (IsWindow((HWND)hWndOrPid)) {
		GetWindowThreadProcessId((HWND)hWndOrPid, &dwProcessID);
	}
	return OpenProcess(PROCESS_ALL_ACCESS, 0, dwProcessID);
}

//文件_定位W
bool Files_FileLocation(CXText fileName, bool editMode) {
	if (!PathFileExistsW(fileName)) {
		return false;
	}
	PIDLIST_ABSOLUTE pidl = ILCreateFromPathW(fileName);
	if (pidl == NULL) {
		return false;
	}
	HRESULT hr = SHOpenFolderAndSelectItems(pidl, NULL, NULL, editMode ? OFASI_EDIT : NULL);
	ILFree(pidl);
	return hr == S_OK;
}

bool X_Program_FileLocation(DWORD pid){

	return Files_FileLocation(X_Program_GetPathByIDW(pid),FALSE);
}

BOOL X_Program_Close(HANDLE pid) { return CloseHandle(pid); }

BOOL X_Program_ShutDown(DWORD pid) {
	HANDLE hProcess = pid==NULL? GetCurrentProcess(): OpenProcess(PROCESS_TERMINATE, 0, pid);
	if (hProcess==NULL) {
		return false;
	}
	BOOL bRet = TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);
	return bRet;
}

bool X_Program_DonotOpen(){
	ACL Acl = {0};
	if(!InitializeAcl(&Acl, sizeof(Acl), 2)){
		return false;
	}
	return SetSecurityInfo((HANDLE)-1, SE_OBJECT_TYPE::SE_KERNEL_OBJECT, 2147483652, 0, 0, &Acl, 0)!=0;
}

DWORD X_Program_GetIDByHandle(HANDLE pid) {
	return GetProcessId(pid);
}

UINT X_Program_ProcessEnumA(CXMap<DWORD, CXTextA>& ret) {
	ret.clear();
	HANDLE sp = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if (sp == INVALID_HANDLE_VALUE) {
		return 0;
	}
	m_hKernel32LibA = m_hKernel32LibA == nullptr ? LoadLibraryA("Kernel32.dll") : m_hKernel32LibA;
	if (m_hKernel32LibA == nullptr) {
		return 0;
	}
	typedef BOOL(WINAPI* Process32FirstAFUNC)(HANDLE hSnapshot, tagPROCESSENTRY32* lppe);
	typedef BOOL(WINAPI* Process32NextAFUNC)(HANDLE hSnapshot, tagPROCESSENTRY32* lppe);
	Process32FirstAFUNC pfnMF = (Process32FirstAFUNC)GetProcAddress(m_hKernel32LibA, "Process32First");
	Process32NextAFUNC pfnMN = (Process32NextAFUNC)GetProcAddress(m_hKernel32LibA, "Process32Next");
	if (pfnMF == NULL || pfnMN == NULL) {
		return 0;
	}
	tagPROCESSENTRY32 modleInfo = {0};
	modleInfo.dwSize = sizeof(modleInfo);
	BOOL next = pfnMF(sp,&modleInfo);
	while (next) {
		ret[modleInfo.th32ProcessID]= modleInfo.szExeFile;
		next = pfnMN(sp, &modleInfo);
	}
	CloseHandle(sp);
	return ret.size();
}
UINT X_Program_ProcessEnumW(CXMap<DWORD, CXText>& ret) {
	ret.clear();
	HANDLE sp = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if (sp == INVALID_HANDLE_VALUE) {
		return 0;
	}
	tagPROCESSENTRY32W modleInfo = { 0 };
	modleInfo.dwSize = sizeof(modleInfo);
	BOOL next = Process32FirstW(sp, &modleInfo);
	while (next) {
		ret[modleInfo.th32ProcessID] = modleInfo.szExeFile;
		next = Process32NextW(sp, &modleInfo);
	}
	CloseHandle(sp);
	return ret.size();
}

DWORD X_Program_GetIDByNameA(CXTextA name,bool isCase){
	HANDLE sp = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if (sp == INVALID_HANDLE_VALUE) {
		return 0;
	}
	m_hKernel32LibA = m_hKernel32LibA == nullptr ? LoadLibraryA("Kernel32.dll") : m_hKernel32LibA;
	if (m_hKernel32LibA == nullptr) {
		return 0;
	}
	typedef BOOL(WINAPI* Process32FirstAFUNC)(HANDLE hSnapshot, tagPROCESSENTRY32* lppe);
	typedef BOOL(WINAPI* Process32NextAFUNC)(HANDLE hSnapshot, tagPROCESSENTRY32* lppe);
	Process32FirstAFUNC pfnMF = (Process32FirstAFUNC)GetProcAddress(m_hKernel32LibA, "Process32First");
	Process32NextAFUNC pfnMN = (Process32NextAFUNC)GetProcAddress(m_hKernel32LibA, "Process32Next");
	if (pfnMF == NULL || pfnMN == NULL) {
		return 0;
	}
	tagPROCESSENTRY32 modleInfo = { 0 };
	modleInfo.dwSize = sizeof(modleInfo);
	BOOL next = pfnMF(sp, &modleInfo);
	while (next) {
		//ret[modleInfo.th32ProcessID] = modleInfo.szExeFile;
		if (!(isCase ? 
			_stricmp(name, modleInfo.szExeFile): 
			strcmp(name, modleInfo.szExeFile))) {
			CloseHandle(sp);
			return modleInfo.th32ProcessID;
		}
		next = pfnMN(sp, &modleInfo);
	}
	CloseHandle(sp);
	return 0;
}
DWORD X_Program_GetIDByNameW(CXText name, bool isCase) {
	HANDLE sp = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if (sp == INVALID_HANDLE_VALUE) {
		return 0;
	}
	tagPROCESSENTRY32W modleInfo = { 0 };
	modleInfo.dwSize = sizeof(modleInfo);
	BOOL next = Process32FirstW(sp, &modleInfo);
	while (next) {
		if (!(isCase ?
			_wcsicmp(name, modleInfo.szExeFile) :
			wcscmp(name, modleInfo.szExeFile))) {
			CloseHandle(sp);
			return modleInfo.th32ProcessID;
		}
		next = Process32NextW(sp, &modleInfo);
	}
	CloseHandle(sp);
	return 0;
}

HWND X_Program_GetHWNDByProcessNameA(CXTextA name) {
	DWORD pid = X_Program_GetIDByNameA(name);
	if(pid!=NULL){
		return X_Program_FindHWNDByIDA(pid,"","",100);
	}
	return (HWND)-1;
}
HWND X_Program_GetHWNDByProcessNameW(CXText name) {
	DWORD pid = X_Program_GetIDByNameW(name);
	if (pid != NULL) {
		return X_Program_FindHWNDByIDW(pid, L"", L"", 100);
	}
	return (HWND)-1;
}

LONGLONG X_Program_GetProcessMemoryInfo(DWORD pid, int Company) {
	auto ProcessId = pid==NULL?GetCurrentProcessId(): pid;
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessId);
	if (hProcess == NULL) {
		return 0;
	} 
	PERFORMANCE_INFORMATION performanceInfo;
	GetPerformanceInfo(&performanceInfo, sizeof(performanceInfo));
	PROCESS_MEMORY_COUNTERS pmc;
	if (!GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
		return 0;
	}
	CloseHandle(hProcess);
	return (LONGLONG)(pmc.WorkingSetSize/pow(1024, Company));
}

LONGLONG X_Program_GetIOReadOperationCount(DWORD pid) {
	auto hProcess = pid == NULL ? GetCurrentProcess() : OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	IO_COUNTERS lpIoCounters = { 0 };
	auto pio = GetProcessIoCounters(hProcess, &lpIoCounters);
	CloseHandle(hProcess);
	return pio==FALSE?-1:lpIoCounters.ReadOperationCount;
}
LONGLONG X_Program_GetIOReadTransferCount(DWORD pid) {
	auto hProcess = pid == NULL ? GetCurrentProcess() : OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	IO_COUNTERS lpIoCounters = { 0 };
	auto pio = GetProcessIoCounters(hProcess, &lpIoCounters);
	CloseHandle(hProcess);
	return pio == FALSE ? -1 : lpIoCounters.ReadTransferCount;
}
LONGLONG X_Program_GetIOOtherOperationCount(DWORD pid) {
	auto hProcess = pid == NULL ? GetCurrentProcess() : OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	IO_COUNTERS lpIoCounters = { 0 };
	auto pio = GetProcessIoCounters(hProcess, &lpIoCounters);
	CloseHandle(hProcess);
	return pio == FALSE ? -1 : lpIoCounters.OtherOperationCount;
}
LONGLONG X_Program_GetIOOtherTransferCount(DWORD pid) {
	auto hProcess = pid == NULL ? GetCurrentProcess() : OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	IO_COUNTERS lpIoCounters = { 0 };
	auto pio = GetProcessIoCounters(hProcess, &lpIoCounters);
	CloseHandle(hProcess);
	return pio == FALSE ? -1 : lpIoCounters.OtherTransferCount;
}
LONGLONG X_Program_GetIOWriteOperationCount(DWORD pid) {
	auto hProcess = pid == NULL ? GetCurrentProcess() : OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	IO_COUNTERS lpIoCounters = { 0 };
	auto pio = GetProcessIoCounters(hProcess, &lpIoCounters);
	CloseHandle(hProcess);
	return pio == FALSE ? -1 : lpIoCounters.WriteOperationCount;
}
LONGLONG X_Program_GetIOWriteTransferCount(DWORD pid) {
	auto hProcess = pid == NULL ? GetCurrentProcess() : OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	IO_COUNTERS lpIoCounters = { 0 };
	auto pio = GetProcessIoCounters(hProcess, &lpIoCounters);
	CloseHandle(hProcess);
	return pio == FALSE ? -1 : lpIoCounters.WriteTransferCount;
}

DWORD X_Program_GetParentProcessId(DWORD pid) {
	DWORD retID = 0;
	DWORD currentProcessId = pid==NULL? GetCurrentProcessId(): pid;
	HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshotHandle == INVALID_HANDLE_VALUE) {
		return NULL;
	}
	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(snapshotHandle, &processEntry)) {
		do
		{
			if (processEntry.th32ProcessID == currentProcessId)
			{
				retID = processEntry.th32ParentProcessID;
				break;
			}
		} while (Process32Next(snapshotHandle, &processEntry));
	}
	CloseHandle(snapshotHandle);
	return retID;
}
DWORD X_Program_GetHandleCount(DWORD pid) {
	auto hProcess = pid == NULL ? GetCurrentProcess() : OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	DWORD Count;
	Count = GetProcessHandleCount(hProcess, &Count) ? Count : -1;
	CloseHandle(hProcess);
	return Count;
}

CXTextA X_Program_GetCommandByIDA(DWORD pid, DWORD predistribution) {
	CXTextA cmd;
	HANDLE sp = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if (sp == INVALID_HANDLE_VALUE) {
		return 0;
	}
	m_hKernel32LibA = m_hKernel32LibA == nullptr ? LoadLibraryA("Kernel32.dll") : m_hKernel32LibA;
	if (m_hKernel32LibA == nullptr) {
		return 0;
	}
	typedef BOOL(WINAPI* Process32FirstAFUNC)(HANDLE hSnapshot, tagPROCESSENTRY32* lppe);
	typedef BOOL(WINAPI* Process32NextAFUNC)(HANDLE hSnapshot, tagPROCESSENTRY32* lppe);
	Process32FirstAFUNC pfnMF = (Process32FirstAFUNC)GetProcAddress(m_hKernel32LibA, "Process32First");
	Process32NextAFUNC pfnMN = (Process32NextAFUNC)GetProcAddress(m_hKernel32LibA, "Process32Next");
	if (pfnMF == NULL || pfnMN == NULL) {
		return 0;
	}
	tagPROCESSENTRY32 modleInfo = { 0 };
	modleInfo.dwSize = sizeof(modleInfo);
	BOOL next = pfnMF(sp, &modleInfo);
	while (next) {
		// 根据 PID 获取进程的命令行
		if (pid!= modleInfo.th32ProcessID) {
			next = pfnMN(sp, &modleInfo);
			continue;
		}
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, modleInfo.th32ProcessID);
		if (hProcess) {
			if (predistribution>0) {
				char* szExeFile = new char[predistribution];
				if (szExeFile!=nullptr) {
					GetModuleFileNameExA(hProcess, NULL, szExeFile, predistribution);
					cmd = szExeFile;
				}
				delete[]szExeFile;
			}
			CloseHandle(hProcess);
		}
		next = pfnMN(sp, &modleInfo);
	}
	CloseHandle(sp);
	return cmd;
}

HMODULE X_Program_GetModelHandleA(CXTextA name) {
	return GetModuleHandleA(name);
}
HMODULE X_Program_GetModelHandleW(CXText name) {
	return GetModuleHandleW(name);
}

CXTextA X_Program_GetCommandLineA() {
	return GetCommandLineA();
}
CXText X_Program_GetCommandLineW() {
	return GetCommandLineW();
}

UINT  X_Program_GetThreadCount(DWORD pid){
	if (pid==NULL) {
		pid = GetCurrentProcessId();
	}
	// 创建进程快照
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		return 0;
	}
	// 遍历进程的线程
	THREADENTRY32 te;
	te.dwSize = sizeof(THREADENTRY32);
	if (!Thread32First(hSnapshot, &te)) {
		CloseHandle(hSnapshot);
		return 0;
	}
	int threadCount = 0;
	do
	{
		if (te.th32OwnerProcessID == pid)
		{
			// 统计线程数
			++threadCount;
		}
	} while (Thread32Next(hSnapshot, &te));
	CloseHandle(hSnapshot);
	return threadCount;
}

CXTextA X_Program_GetProcessUsernameA(DWORD pid) {
	if (pid == NULL) {
		pid = GetCurrentProcessId();
	}
	// 打开进程
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
	if (hProcess == NULL)
	{
		return "";
	}
	// 获取进程令牌
	HANDLE hToken;
	if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
	{
		CloseHandle(hProcess);
		return "";
	}
	// 获取令牌用户信息
	DWORD cbSize;
	GetTokenInformation(hToken, TokenUser, NULL, 0, &cbSize);
	PTOKEN_USER pTokenUser = (PTOKEN_USER)GlobalAlloc(GPTR, cbSize);
	if (pTokenUser != NULL) {
		if (GetTokenInformation(hToken, TokenUser, pTokenUser, cbSize, &cbSize)) {
			// 获取用户名
			char szUserName[_MAX_PATH];
			DWORD cchUserName = _MAX_PATH;
			char szADName[_MAX_PATH];
			DWORD cchADName = _MAX_PATH;
			SID_NAME_USE snu;
			if (LookupAccountSidA(NULL, pTokenUser->User.Sid, szUserName, &cchUserName, szADName, &cchADName, &snu))
			{
				GlobalFree(pTokenUser);
				CloseHandle(hToken);
				CloseHandle(hProcess);
				return szUserName;
			}
		}
	}
	GlobalFree(pTokenUser);
	CloseHandle(hToken);
	CloseHandle(hProcess);
	return "";
}
CXText X_Program_GetProcessUsernameW(DWORD pid) {
	if (pid == NULL) {
		pid = GetCurrentProcessId();
	}
	// 打开进程
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
	if (hProcess == NULL)
	{
		return L"";
	}
	// 获取进程令牌
	HANDLE hToken;
	if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
	{
		CloseHandle(hProcess);
		return L"";
	}
	// 获取令牌用户信息
	DWORD cbSize;
	GetTokenInformation(hToken, TokenUser, NULL, 0, &cbSize);
	PTOKEN_USER pTokenUser = (PTOKEN_USER)GlobalAlloc(GPTR, cbSize);
	if (pTokenUser != NULL) {
		if (GetTokenInformation(hToken, TokenUser, pTokenUser, cbSize, &cbSize)) {
			// 获取用户名
			wchar_t szUserName[_MAX_PATH];
			DWORD cchUserName = _MAX_PATH;
			wchar_t szADName[_MAX_PATH];
			DWORD cchADName = _MAX_PATH;
			SID_NAME_USE snu;
			if (LookupAccountSidW(NULL, pTokenUser->User.Sid, szUserName, &cchUserName, szADName, &cchADName, &snu))
			{
				GlobalFree(pTokenUser);
				CloseHandle(hToken);
				CloseHandle(hProcess);
				return szUserName;
			}
		}
	}
	GlobalFree(pTokenUser);
	CloseHandle(hToken);
	CloseHandle(hProcess);
	return L"";
}

X_Program_Enum_ProcessPriority X_Program_GetProcessPriority(DWORD pid) {
	auto hProcess = pid==NULL? GetCurrentProcess(): OpenProcess(1024, 0, pid);
	if (!hProcess) {
		return X_Program_Enum_ProcessPriority::NoPermission;
	}
	X_Program_Enum_ProcessPriority r;
	auto Class = GetPriorityClass(hProcess);
	switch (Class) {
	case REALTIME_PRIORITY_CLASS:
		r= X_Program_Enum_ProcessPriority::RealTime;
		break;
	case HIGH_PRIORITY_CLASS:
		r = X_Program_Enum_ProcessPriority::Highest;
		break;
	case ABOVE_NORMAL_PRIORITY_CLASS:
		r = X_Program_Enum_ProcessPriority::Highest;
		break;
	case NORMAL_PRIORITY_CLASS:
		r = X_Program_Enum_ProcessPriority::Standard;
		break;
	case BELOW_NORMAL_PRIORITY_CLASS:
		r = X_Program_Enum_ProcessPriority::BelowStandard;
		break;
	case IDLE_PRIORITY_CLASS:
		r = X_Program_Enum_ProcessPriority::Low;
		break;
	default:
		r = X_Program_Enum_ProcessPriority::Highest;
		break;
	}
	CloseHandle(hProcess);
	return r;
}

DWORD  X_Program_GetSessionIdByProcessId(DWORD pid) {
	DWORD dwSessionId;
	ProcessIdToSessionId(pid==NULL? GetCurrentProcessId():pid, &dwSessionId);
	return dwSessionId;
}

TOKEN_ELEVATION_TYPE X_Program_GetProcessUACLevel(DWORD pid) {
	// 获取进程的句柄
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
	if (hProcess == NULL) {
		return TOKEN_ELEVATION_TYPE::TokenElevationTypeDefault;
	}
	// 获取进程的令牌句柄
	HANDLE hToken;
	if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
	{
		return TOKEN_ELEVATION_TYPE::TokenElevationTypeDefault;
	}
	// 获取令牌的UAC执行权限级别
	TOKEN_ELEVATION_TYPE elevationType;
	DWORD dwSize;
	if (!GetTokenInformation(hToken, TokenElevationType, &elevationType, sizeof(elevationType), &dwSize)) {
		return TOKEN_ELEVATION_TYPE::TokenElevationTypeDefault;
	}
	return elevationType;
}

DWORD X_Program_GetSonProcessId(DWORD ParentPid) {
	DWORD retID = 0;
	DWORD currentProcessId = ParentPid == NULL ? GetCurrentProcessId() : ParentPid;
	HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshotHandle == INVALID_HANDLE_VALUE) {
		return NULL;
	}
	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(snapshotHandle, &processEntry)) {
		do
		{
			if (processEntry.th32ParentProcessID == currentProcessId)
			{
				retID = processEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(snapshotHandle, &processEntry));
	}
	CloseHandle(snapshotHandle);
	return retID;
}

DWORD X_Program_GetAllSonProcessId(DWORD ParentPid, CXVector<DWORD>& ret) {
	ret.clear();
	DWORD retID = 0;
	DWORD currentProcessId = ParentPid == NULL ? GetCurrentProcessId() : ParentPid;
	HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshotHandle == INVALID_HANDLE_VALUE) {
		return NULL;
	}
	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(snapshotHandle, &processEntry)) {
		do
		{
			if (processEntry.th32ParentProcessID == currentProcessId)
			{
				//retID = processEntry.th32ProcessID;
				ret.add(processEntry.th32ProcessID);
			}
		} while (Process32Next(snapshotHandle, &processEntry));
	}
	CloseHandle(snapshotHandle);
	return retID;
}

BOOL X_Program_CheckRemoteDebuggerPresent(HANDLE handle) {
	BOOL isDebug;
	CheckRemoteDebuggerPresent(handle, &isDebug);
	return isDebug;
}

BOOL X_Program_ProcessIfSuspend(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == NULL) {
		return FALSE;
	}
	// 获取进程的时间信息
	FILETIME ftCreationTime, ftExitTime, ftKernelTime, ftUserTime;
	if (!GetProcessTimes(hProcess, &ftCreationTime, &ftExitTime, &ftKernelTime, &ftUserTime)) {
		CloseHandle(hProcess);
		return FALSE;
	}
	if (ftCreationTime.dwLowDateTime == 0 && ftCreationTime.dwHighDateTime == 0) {
		CloseHandle(hProcess);
		return TRUE;
	}
	DWORD exitCode;
	if (GetExitCodeProcess(hProcess, &exitCode)) {
		if (exitCode == STILL_ACTIVE) {
			CloseHandle(hProcess);
			return FALSE;
		}
		else {
			CloseHandle(hProcess);
			return TRUE;
		}
	}
	return FALSE;
}
BOOL X_Program_ProcessIs64(DWORD pid) {
	auto hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, 0, pid == NULL ? GetCurrentProcessId() : pid);
	BOOL lRes=FALSE;
	if (hProcess) {
		BOOL isWow64;
		if (IsWow64Process(hProcess, &isWow64)&& isWow64==FALSE) {
			lRes = TRUE;
		}
		CloseHandle(hProcess);
	}
	return lRes;
}

BOOL X_Program_ProcessIsAdmin(DWORD pid){
	HANDLE                   hAccessToken;
	BYTE                     InfoBuffer[1024];
	PTOKEN_GROUPS            ptgGroups;
	DWORD                    dwInfoBufferSize;
	PSID                     psidAdministrators;
	SID_IDENTIFIER_AUTHORITY siaNtAuthority = SECURITY_NT_AUTHORITY;
	UINT                     i;
	BOOL                     bRet = FALSE;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hAccessToken)) {
		return bRet;
	}
	bRet = GetTokenInformation(hAccessToken, TokenGroups, InfoBuffer, 1024, &dwInfoBufferSize);
	CloseHandle(hAccessToken);
	if (!bRet){ return bRet; }
	if (!AllocateAndInitializeSid(&siaNtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&psidAdministrators)){
		return FALSE;
	}	
	bRet = FALSE;
	ptgGroups = (PTOKEN_GROUPS)InfoBuffer;
	for (i = 0; i < ptgGroups->GroupCount; i++){
		if (EqualSid(psidAdministrators, ptgGroups->Groups[i].Sid)) { 
			bRet = TRUE;
		}	
	}
	FreeSid(psidAdministrators);
	return bRet;
}

BOOL X_Program_ProcessPermissionPromotion(DWORD pid) {
	// 打开进程
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
	if (hProcess == NULL) {
		return FALSE;
	}
	// 打开访问令牌
	HANDLE hToken;
	if (!OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken)) {
		return FALSE;
	}
	// 关闭进程句柄
	CloseHandle(hProcess);
	// 查找LUID取得SeDebugPrivilege
	LUID luid;
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) {
		return FALSE;
	}
	// 启用权限
	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL)) {
		return FALSE;
	}
	CloseHandle(hToken);
	return TRUE;
}

HMODULE g_ntdllLib = nullptr;
void X_Program_ProcessSuspend(DWORD pid, bool state) {
	if (g_ntdllLib == nullptr) {
		g_ntdllLib = LoadLibraryW(L"ntdll.dll");
	}
	if (g_ntdllLib==nullptr) {
		return;
	}
	auto hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	if (state) {
		typedef DWORD(__stdcall* ZWSUSPENDPROCESS)(HANDLE ProcessHandle);
		ZWSUSPENDPROCESS ZwSuspendProcess = (ZWSUSPENDPROCESS)GetProcAddress(g_ntdllLib, "ZwSuspendProcess");
		if (ZwSuspendProcess!=nullptr) {
			ZwSuspendProcess(hProcess);
		}
	}
	else {
		typedef DWORD(__stdcall* ZWRESUMEPROCESS)(HANDLE ProcessHandle);
		ZWRESUMEPROCESS ZwResumeProcess = (ZWRESUMEPROCESS)GetProcAddress(g_ntdllLib, "ZwResumeProcess");
		if (ZwResumeProcess != nullptr) {
			ZwResumeProcess(hProcess);
		}
	}
	CloseHandle(hProcess);
}

BOOL X_Program_SetPriority(DWORD pid, X_Program_Enum_ProcessPriority Priority) {
	DWORD iPriority = 0;
	switch (Priority)
	{
	case X_Program_Enum_ProcessPriority::Highest:
		iPriority = HIGH_PRIORITY_CLASS;
		break;
	case X_Program_Enum_ProcessPriority::AboveStandard:
		iPriority = ABOVE_NORMAL_PRIORITY_CLASS;
		break;
	case X_Program_Enum_ProcessPriority::RealTime:
		iPriority = REALTIME_PRIORITY_CLASS;
		break;
	case X_Program_Enum_ProcessPriority::Standard:
		iPriority = NORMAL_PRIORITY_CLASS;
		break;
	case X_Program_Enum_ProcessPriority::BelowStandard:
		iPriority = BELOW_NORMAL_PRIORITY_CLASS;
		break;
	case X_Program_Enum_ProcessPriority::Low:
		iPriority = IDLE_PRIORITY_CLASS;
		break;
	default:
		iPriority = HIGH_PRIORITY_CLASS;
		break;
	}
	auto hProcess = pid == NULL ? GetCurrentProcess() : OpenProcess(PROCESS_SET_INFORMATION, 0, pid);
	if (hProcess==NULL) {
		return FALSE;
	}
	auto Bool = SetPriorityClass(hProcess, iPriority);
	CloseHandle(hProcess);
	return Bool;
}

BOOL X_Program_ProcessShutDown(DWORD pid){
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
	if (hProcess == NULL) {
		return FALSE;
	}
	if (!TerminateProcess(hProcess, 0)) {
		return FALSE;
	}
	CloseHandle(hProcess);
	return TRUE;
}
