#include "haper.h"
#include <algorithm>

std::wstring lTrim(std::wstring&str)
{
    int i, len;

    len = str.size();
    for (i = 0; i < len; i++)
    {
        if (str[i] != L' ')
            break;
    }
    str = str.substr(i, len - i);
    return str;
}

std::wstring rTrim(std::wstring&str)
{
    int i, len;

    len = str.size();
    for (i = len - 1; i >= 0; i--)
    {
        if (str[i] != L' ')
            break;
    }
    str = str.substr(0, i);
    return str;
}

std::wstring Trim(std::wstring&str)
{
    lTrim(str);
    rTrim(str);
    return str;
}

DWORD rFind(std::wstring&str, const wchar_t *_Ptr, size_t _Off)
{
	return str.rfind(_Ptr);
    //std::wstring s = str.c_str();
   // return s.rfind(_Ptr);
}

std::vector<std::wstring> split(const wchar_t* pString, wchar_t c)
{
	std::wstring s;
	if (pString && *pString)
		s = pString;

    s += c;
    std::vector<std::wstring> ret;
	std::wstring t;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == c)
            ret.push_back(t), t = L"";
        else
            t += s[i];
    }
    return ret;
}

void w_toupper(std::wstring&wcstr)
{
    //std::wstring wstr = wcstr.get();
    transform(wcstr.begin(), wcstr.end(), wcstr.begin(), toupper);
}

void w_tolower(std::wstring&wcstr)
{
    //std::wstring wstr = wcstr.get();
    transform(wcstr.begin(), wcstr.end(), wcstr.begin(), tolower);
}

HMODULE WininetDLL = NULL;

bool initNetLib()
{
    if (!WininetDLL)
    {
        WininetDLL = LoadLibraryW(L"Wininet.dll");
    }
    return WininetDLL != NULL;
}

typedef bool (*InternetSetCookie)(_In_ LPCWSTR lpszUrl,
                                  _In_opt_ LPCWSTR lpszCookieName,
                                  _In_ LPCWSTR lpszCookieData);
typedef bool (*InternetGetCookie)(
    _In_ LPCWSTR lpszUrl,
    _In_opt_ LPCWSTR lpszCookieName,
    _Out_writes_opt_(*lpdwSize) LPWSTR lpszCookieData,
    _Inout_ LPDWORD lpdwSize);

bool InternetSetCookieW(_In_ LPCWSTR lpszUrl,
                        _In_opt_ LPCWSTR lpszCookieName,
                        _In_ LPCWSTR lpszCookieData)
{
    if (initNetLib())
    {
        return false;
    }
    InternetSetCookie fun = (InternetSetCookie)GetProcAddress(WininetDLL, "InternetSetCookieW");
    return fun(lpszUrl, lpszCookieName, lpszCookieData);
}

bool InternetGetCookieW(
    _In_ LPCWSTR lpszUrl,
    _In_opt_ LPCWSTR lpszCookieName,
    _Out_writes_opt_(*lpdwSize) LPWSTR lpszCookieData,
    _Inout_ LPDWORD lpdwSize)
{
    if (initNetLib())
    {
        return false;
    }
    InternetGetCookie fun = (InternetGetCookie)GetProcAddress(WininetDLL, "InternetSetCookieW");
    return fun(lpszUrl, lpszCookieName, lpszCookieData, lpdwSize);
}

//Utf8转Gbk
//std::string W_Coding_Utf82Gbk(CXTextA& utf8)
//{
//    int len = MultiByteToWideChar(CP_UTF8, 0, utf8.get(), -1, NULL, 0);
//    wchar_t* wstr = new wchar_t [len+1];
//    memset(wstr, 0, len+1);
//    MultiByteToWideChar(CP_UTF8, 0, utf8.get(), -1, wstr, len);
//    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
//    char* str = (char*)malloc(len+1);
//    memset(str, 0, len+1);
//    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
//    if(wstr) { delete [] wstr; }
//	std::string rets = str;
//    free (str);
//    return rets;
//}