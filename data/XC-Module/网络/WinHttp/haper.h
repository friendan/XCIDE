#ifndef XC_WINHTTP_HAPER_H
#define XC_WINHTTP_HAPER_H

//#ifndef XC_WINHTTP_H_TEST
//#define XC_WINHTTP_H_TEST
//#include "D:\app\XCIDE\data\XC-Module\核心模块\基础模块\module_base.h"
//#include "D:\app\XCIDE\data\XC-Module\核心模块\系统API\module_windowsApi.h"
//#endif

#ifdef XC_MOUDLE
#include "module_base.h"
#endif


std::wstring lTrim(std::wstring&str);
std::wstring rTrim(std::wstring&str);
std::wstring Trim(std::wstring&str);
DWORD rFind(std::wstring&str, const wchar_t *_Ptr, size_t _Off = std::string::npos);

std::vector<std::wstring> split(const wchar_t* pString, wchar_t c = ' ');

void w_toupper(std::wstring&wstr);

void w_tolower(std::wstring&wstr);

bool InternetSetCookieW(
    _In_ LPCWSTR lpszUrl,
    _In_opt_ LPCWSTR lpszCookieName,
    _In_ LPCWSTR lpszCookieData);

bool InternetGetCookieW(
    _In_ LPCWSTR lpszUrl,
    _In_opt_ LPCWSTR lpszCookieName,
    _Out_writes_opt_(*lpdwSize) LPWSTR lpszCookieData,
    _Inout_ LPDWORD lpdwSize);

//CXTextA W_Coding_Utf82Gbk(CXTextA& utf8);

#endif // XC_WINHTTP_HAPER_H