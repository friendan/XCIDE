#include "module_winhttp.h"

HANDLE w_DefaultHeap = 0;

CXWinHttp::CXWinHttp() {
	__Init();
	if (!w_DefaultHeap) {
		w_DefaultHeap = GetProcessHeap();
	}
	__Create();
	__InitOptions();
}

CXWinHttp::CXWinHttp(CXText url) {
	__Init();
	if (!w_DefaultHeap) {
		w_DefaultHeap = GetProcessHeap();
	}
	__Create();
	__InitOptions();
	Open(url);
}

CXWinHttp::CXWinHttp(CXText url, CXText Method) {
	__Init();
	if (!w_DefaultHeap) {
		w_DefaultHeap = GetProcessHeap();
	}
	__Create();
	__InitOptions();
	Open(url, Method);
}

CXWinHttp::~CXWinHttp() { __Close(); }

void CXWinHttp::__Init()
{
	_hSession = NULL;
	_hRequest = NULL;
	_hConnect = NULL;
	_Dataptr = NULL;

	_Port = 0;
	_Scheme = 0;
	_ResponseBodylen = 0;
	_ContentLength = 0;
	_AutoCookies = 0;
	_Cookieslen = 0;
	_RedirectIndex = 0;
}

void CXWinHttp::__Create() {
	//初始化Winhttp
	_hSession = WinHttpOpen(L"Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2)",
		WINHTTP_ACCESS_TYPE_NO_PROXY, WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, NULL);
	//申请缓冲区
	_Dataptr = HeapAlloc(w_DefaultHeap, NULL, HTTP_BUFFER_LEN);
}

void CXWinHttp::__Create(CXText User_Agent) {
	//初始化Winhttp
	_hSession = WinHttpOpen(User_Agent.get(), WINHTTP_ACCESS_TYPE_NO_PROXY,
		WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, NULL);
	//申请缓冲区
	_Dataptr = HeapAlloc(w_DefaultHeap, NULL, HTTP_BUFFER_LEN);
}

void CXWinHttp::__Close() {
	//关闭CXWinHttp各句柄
	if (!_hRequest) {
		WinHttpCloseHandle(_hRequest);
		_hRequest = NULL;
	}
	if (!_hConnect) {
		WinHttpCloseHandle(_hConnect);
		_hConnect = NULL;
	}
	if (!_hSession) {
		WinHttpCloseHandle(_hSession);
		_hSession = NULL;
	}

	//释放缓冲区
	if (!_Dataptr) {
		HeapFree(w_DefaultHeap, NULL, _Dataptr);
	}
	//初始化各状态
	_Dataptr = NULL;
	_hRequest = _hConnect = _hSession = NULL;
	_ResponseBodylen = _ContentLength = _Port = NULL;
	_NeverRedirect = _SetProxyInfo = FALSE;
	_ResponseHeaders = L"";
	_SetProxyUser = L"";
	_SetProxyPass = L"";
	_HostName = L"";
	_UrlW = L"";
}

void CXWinHttp::__InitOptions() {
	_Auto = TRUE;
	_AutoCookies = 0;
	_IsIgnoreError = TRUE;  // 自动忽略错误
	_Cookies = L"; ";
	_Cookieslen = 2;
	// 设置默认超时 能有效避免Send失败
	WinHttpSetTimeouts(_hSession, 10000, 15000, 120000, 300000);
}

void CXWinHttp::__UpCookies1(BOOL NopNullCookieName) {
	size_t i = _ResponseHeaders.find(L"Set-Cookie:");
	size_t ii = 0;
	BOOL vbool;
	while (i != std::wstring::npos && ii != std::wstring::npos) {
		i += 11;
		ii = _ResponseHeaders.find(L";", i);
		if (ii != std::wstring::npos) {
			std::wstring cookie = _ResponseHeaders.substr(i, ii - i+1);
			lTrim(cookie);
			size_t iii = cookie.find(L"=");
			std::wstring Value;
			if (iii != std::wstring::npos) {
				// cookies计算
				std::wstring name = cookie.substr(0, iii+1);
				size_t OI = _Cookies.find(L"; " + name);  // Cookie名区分大小写emmm
				if (OI != std::wstring::npos) {
					size_t OII = cookie.size();
					if (NopNullCookieName && OII - 1 == iii) {
						i = _ResponseHeaders.find(L"Set-Cookie:", ii);
						continue;
					}
					OI += 2;
					OII = _Cookies.find(L"; ", name.size());
					if (OII != std::wstring::npos) {
						Value = cookie.substr(cookie.size() - 9, cookie.size());
						if (Value == L"=deleted;" || Value == L"=DELETED;" || Value == L"=Deleted;") {  //判断是否是删除标记
							if (NopNullCookieName) {
								i = _ResponseHeaders.find(L"Set-Cookie:", ii);
								continue;
							}
							cookie = L"";
							OI -= 1;
						}
						_Cookies.replace(OI, OII - OI + 1, cookie);
						vbool = TRUE;
					}
				} else {
					Value = cookie.substr(cookie.size() - 9, cookie.size());
					if (Value != L"=deleted;" && Value != L"=DELETED;" && Value != L"=Deleted;") {  //判断是否是删除标记
						_Cookies = _Cookies + cookie + L" ";
						vbool = TRUE;
					}
				}
			}
		}
		i = _ResponseHeaders.find(L"Set-Cookie:", ii);
	}
	if (vbool) {
		_Cookieslen = (int)_Cookies.size();
	}
}

void CXWinHttp::__UpCookies2(BOOL NopNullCookieName) {
	size_t i = _ResponseHeaders.find(L"Set-Cookie:");
	size_t ii = 0;
	while (i == std::wstring::npos && ii == std::wstring::npos) {
		i += 11;
		ii = _ResponseHeaders.find(L";", i);
		if (ii != std::wstring::npos) {
			ii++;
			std::wstring cookie = _ResponseHeaders.substr(i, ii - i);
			lTrim(cookie);
			size_t iii = cookie.find(L"=");
			if (iii != std::wstring::npos) {
				std::wstring name = cookie.substr(0, iii - 1);
				std::wstring Value = cookie.substr(cookie.size() - 9, cookie.size());
				BOOL del = Value == L"=deleted;" || Value == L"=DELETED;" ||
					Value == L"=Deleted;";
				if (del) {
					if (NopNullCookieName) {
						i = _ResponseHeaders.find(L"Set-Cookie:", ii);
						continue;
					}
					Value = L"";
				} else {
					iii += 1;
					Value = cookie.substr(iii, cookie.size() - iii);
					std::wstring tx = Value;
					lTrim(tx);
					if (NopNullCookieName && tx == L"") {
						i = _ResponseHeaders.find(L"Set-Cookie:", ii);
						continue;
					}
				}
				InternetSetCookieW(_UrlW.c_str(), name.c_str(), Value.c_str());
			}
			i = _ResponseHeaders.find(L"Set-Cookie:", ii);
		}
	}
}

BOOL CXWinHttp::__SetCookies2(CXText Cookie) {
	if (Cookie == L"") {
		return FALSE;
	}
	BOOL vbool;
	std::vector<std::wstring> strs = split(Cookie, L';');
	for (size_t i = 0; i < strs.size(); i++) {
		lTrim(strs[i]);
		size_t ii = strs[i].find(L"=");
		if (ii != std::wstring::npos) {
			std::wstring name = strs[i].substr(0, ii - 1);
			std::wstring value = strs[i].substr(strs[i].size() - (strs[i].size() - ii),
				strs[i].size());
			InternetSetCookieW(_UrlW.c_str(), name.c_str(), value.c_str());
			vbool = TRUE;
		}
	}
	return vbool;
}

BOOL CXWinHttp::__LoadCookies1() {
	std::wstring HeaderW = L"Cookie:" + _Cookies.substr(2, _Cookieslen - 4);
	return WinHttpAddRequestHeaders(
		_hRequest, HeaderW.c_str(), HeaderW.size(),
		WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE) > 0;
}

BOOL CXWinHttp::__LoadCookies2() {
	DWORD len = 0;
	wchar_t* cookies;
	InternetGetCookieW(_UrlW.c_str(), L"", NULL, &len);
	if (!len) {
		return FALSE;
	}
	cookies = new wchar_t[len];
	InternetGetCookieW(_UrlW.c_str(), L"", cookies, &len);
	std::wstring HeaderW = L"Cookie:";
	HeaderW += cookies;
	delete cookies;
	return WinHttpAddRequestHeaders(
		_hRequest, HeaderW.c_str(), HeaderW.size(),
		WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE) > 0;
}

void CXWinHttp::__SetRequestHeaders(BOOL IsData) {
	WinHttpAddRequestHeaders(_hRequest, L"Accept:*/*", 10,
		WINHTTP_ADDREQ_FLAG_ADD_IF_NEW);
	WinHttpAddRequestHeaders(_hRequest, L"Accept-Language:zh-cn", 21,
		WINHTTP_ADDREQ_FLAG_ADD_IF_NEW);
	WinHttpAddRequestHeaders(_hRequest, L"Cache-Control:no-cache", 22,
		WINHTTP_ADDREQ_FLAG_ADD_IF_NEW);
	if (_IsPOST || IsData) {
		WinHttpAddRequestHeaders(_hRequest,
			L"Content-Type:application/x-www-form-urlencoded",
			46, WINHTTP_ADDREQ_FLAG_ADD_IF_NEW);
	}
}

void CXWinHttp::__SetInternetInfo() {
	DWORD i = 0;
	if (_SetProxyInfo) {
		// CXWinHttp的设置代理信息 必须使用请求句柄来设置 而且设置后是一直有效的
		// 真搞不懂
		//  为啥不能直接用会话句柄去设置呢？CXWinHttp的设置代理信息
		//  必须使用请求句柄来设置 而且设置后是一直有效的 真搞不懂
		//  为啥不能直接用会话句柄去设置呢？ 为什么不用 WinHttpSetCredentials
		//  呢？ 因为 WinHttpSetCredentials 没有 WinHttpSetOption 快 已测试
		WinHttpSetOption(_hRequest, WINHTTP_OPTION_PROXY_USERNAME,
			(void*)_SetProxyUser.c_str(), _SetProxyUser.size());
		WinHttpSetOption(_hRequest, WINHTTP_OPTION_PROXY_PASSWORD,
			(void*)_SetProxyPass.c_str(), _SetProxyPass.size());
		_SetProxyInfo = FALSE;
		_SetProxyUser = L"";
		_SetProxyPass = L"";
	}
	if (_NeverRedirect ||
		_AutoCookies >
		NULL) {  //禁止重定向 这个设置后是本次有效的 所以必须每次都设置一次
  // WinHttpSetOption (_hRequest, #WINHTTP_OPTION_REDIRECT_POLICY,
  // #WINHTTP_OPTION_REDIRECT_POLICY_NEVER, 4) ’这俩都是禁止重定向
  // 好像用哪个都一样
		i = WINHTTP_DISABLE_REDIRECTS;
		WinHttpSetOption(_hRequest, WINHTTP_OPTION_DISABLE_FEATURE, &i, DwSize);
	}

	if (_IsIgnoreError) {  //设置一次自动忽略错误/证书错误 设置一次就一直有效
	  //而且暂时没找到如何取消的标志
		i = 13056;
		WinHttpSetOption(_hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &i, DwSize);
		_IsIgnoreError = FALSE;
	}
	if (_AutoCookies != NULL) {
		i = WINHTTP_DISABLE_COOKIES;
		WinHttpSetOption(_hRequest, WINHTTP_OPTION_DISABLE_FEATURE, &i,
			DwSize);  //设置禁止Winhttp内部自动处理Cookies
		if (_AutoCookies == 1) {
			__LoadCookies1();
		}
		if (_AutoCookies == 2) {
			__LoadCookies2();
		}
	}
}

BOOL CXWinHttp::__GetQueryHeadersInfo(BOOL NopNullCookieName) {
	DWORD len = 0;
	WinHttpQueryHeaders(_hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, NULL, NULL,
		&len,
		NULL);  //先获取长度
	if (len < 1) {
		_ContentLength = -1;
		return FALSE;
	}
	wchar_t* Bin = new wchar_t[len];
	if (!WinHttpQueryHeaders(_hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, NULL, Bin,
		&len, NULL)) {
		_ContentLength = -1;
		delete Bin;
		return FALSE;
	}
	_ResponseHeaders = Bin;
	delete Bin;
	//为了更好且更快的读取数据 这里提前获取了Content-Length信息来得到要读取的长度
	size_t i = _ResponseHeaders.find(L"Content-Length:");
	if (i == std::wstring::npos) {
		_ContentLength = -1;  // 如果获取失败
	} else {
		i += 15;  // 加上 Content-Length:  的长度
		size_t len = _ResponseHeaders.find(L"\n", i);
		if (len != std::wstring::npos) {
			_ContentLength = _wtoi(_ResponseHeaders.substr(i, len - i).c_str());
		} else {
			len = _ResponseHeaders.size();  //万一没换行符
			_ContentLength = _wtoi(_ResponseHeaders.substr(_ResponseHeaders.size() - 5,
				_ResponseHeaders.size()).c_str());
		}
	}
	//处理并更新Cookies
	if (_AutoCookies) {
		switch (_AutoCookies) {
		case 1:
			__UpCookies1(NopNullCookieName);
			break;
		case 2:
			__UpCookies2(NopNullCookieName);
			break;
		}
	}
	return FALSE;
}

void CXWinHttp::__Redirect(BOOL NopNullCookieName, int SendRetryCount) {
	if (!_AutoCookies || _NeverRedirect) {  //模式0或者禁止重定向
		return;
	}
	std::wstring url = GetResponseLocation();
	if (url == L"") {
		_RedirectIndex = NULL;
		return;
	}
	_RedirectIndex++;
	if (_RedirectIndex > 20) {  //单次访问 最多20次重定向跳转
		_RedirectIndex = NULL;
		return;
	}
	Open(url);
	Send(0, 0, NopNullCookieName, SendRetryCount);
}

// === 公开集

void CXWinHttp::Auto(BOOL IsAuto) { _Auto = IsAuto; }

void CXWinHttp::AutoCookies(int Index) {
	_AutoCookies = Index > 2 || Index < 0 ? 0 : Index;
}

void CXWinHttp::Rest(CXText User_Agent) {
	__Close();
	if (User_Agent == L"") {
		__Create();
	} else {
		__Create(User_Agent);
	}
	__InitOptions();
}

BOOL CXWinHttp::Open(CXText Url, CXText Method) {  //打开一个HTTP连接
	if (_hSession == NULL) {
		return FALSE;
	}
	// 处理CrackUrl
	// WinHttpCrackUrl无法处理带有协议头的Url,需要自行处理
	_UrlW = Url;
	//w_tolower(_UrlW);
    if (_UrlW.substr(0, 7) != L"http://" && _UrlW.substr(0, 8) != L"https://") {
		_UrlW = L"http://" + _UrlW;
	}
	int nPort = 0;
	std::wstring HostNameW;
	_UrlW.substr(0, 7) == L"http://" ? nPort = INTERNET_DEFAULT_HTTP_PORT: nPort = INTERNET_DEFAULT_HTTPS_PORT;
	int pos = (int)_UrlW.find(L"://");
	if(pos != std::wstring::npos){
		int pos2 = (int)_UrlW.find(L"/", pos + 3);
		if (pos2 != std::wstring::npos) {
			HostNameW = _UrlW.substr(pos + 3, pos2 - (pos + 3));
	} else {
			HostNameW = _UrlW.substr(pos + 3);
		}
	}
	pos = HostNameW.find(L":");
	if(pos != std::wstring::npos) {
		nPort = std::stoi(HostNameW.substr(pos + 1));
		HostNameW = HostNameW.substr(0, pos);
	}
	URL_COMPONENTS urlComp;
	// Initialize the URL_COMPONENTS structure.
	ZeroMemory(&urlComp, sizeof(urlComp));
	urlComp.dwStructSize = sizeof(urlComp);
	// Set required component lengths to non-zero
	// so that they are cracked.
	urlComp.dwSchemeLength = (DWORD)-1;
	urlComp.dwHostNameLength = (DWORD)-1;
	urlComp.dwUrlPathLength = (DWORD)-1;
	urlComp.dwExtraInfoLength = (DWORD)-1;

	LPCWSTR pwszUrl = _UrlW.c_str();
	if (!WinHttpCrackUrl(pwszUrl, (DWORD)wcslen(pwszUrl), 0, &urlComp)) {
		return FALSE;
	}
	//初始化状态
	_ResponseBodylen = _ContentLength = NULL;
	_ResponseHeaders = L"";
	//处理Connect
	if (_hRequest) {
		WinHttpCloseHandle(_hRequest);
	}


	if (!_hConnect || _HostName != HostNameW || nPort != _Port) {  //如果还是上次的域名与端口就直接复用Connect
		if (_hConnect) {
			WinHttpCloseHandle(_hConnect);
		}
		_hConnect = WinHttpConnect(_hSession, HostNameW.c_str(), nPort, NULL);
		if (!_hConnect) {
			_hRequest = NULL;
			return FALSE;
		}
		_HostName = HostNameW;
		_Port = nPort;
	}
	//处理 Request
	std::wstring str;
	std::wstring MethodW;
	if (Method == L"") {
		MethodW = L"GET";
	} else {
		str = Method;
		w_toupper(str);
		if (_Auto) {
			_IsPOST = str == L"POST";
			MethodW = str;
		} else {
			MethodW = str;
		}
	}
	std::wstring UrlPathW;
	if (urlComp.dwUrlPathLength < 1) {  //访问路径如果为空 自动使用斜杠
		UrlPathW = L"/";
	} else {
		UrlPathW = urlComp.lpszUrlPath;
	}
	DWORD dwFlags = 0;
	if (urlComp.nScheme == INTERNET_SCHEME_HTTPS) {  //判断是否为HTTPS
		dwFlags = WINHTTP_FLAG_SECURE;
	}
	//部署状态
	_Scheme = urlComp.nScheme;  //保存协议 解析302
	_hRequest = WinHttpOpenRequest(_hConnect, MethodW.c_str(), UrlPathW.c_str(),
		WINHTTP_DEFAULT_VERSION, WINHTTP_NO_REFERER,
		WINHTTP_DEFAULT_ACCEPT_TYPES, dwFlags);
	return _hRequest != NULL;
}

BOOL CXWinHttp::SendText(CXText data_, BOOL NopNullCookieName, int SendRetryCount) {

	int length = data_.getSize() * 2;
	return Send((const BYTE*)data_.get(), length, NopNullCookieName, SendRetryCount);
}
BOOL CXWinHttp::SendTextA(CXTextA data_, BOOL NopNullCookieName, int SendRetryCount) {

	return Send((const BYTE*)data_.get(), data_.getSize(), NopNullCookieName, SendRetryCount);
}
BOOL CXWinHttp::SendBytes(CXBytes data_, BOOL NopNullCookieName, int SendRetryCount) {

	int length = data_.getSize();
	return Send(data_.get(), length, NopNullCookieName, SendRetryCount);
}

BOOL CXWinHttp::Send(const BYTE* data_, int length, BOOL NopNullCookieName, int SendRetryCount)
{
	if (!_hRequest) {
		return FALSE;
	}
	//附加选项和加载Cookies
	__SetInternetInfo();
	//提交数据
	if (_Auto) {  //处理Auto自动补全协议头
		__SetRequestHeaders(length == 0);
	}
	BOOL vbool;
	for (int i = 0; i < SendRetryCount + 1; i++) {
		vbool = WinHttpSendRequest(_hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, NULL, (LPVOID)data_, length, length, NULL) > 0;
		int error = 0;
		if (!vbool) {
			error = GetLastError();
			if (error != ERROR_WINHTTP_CANNOT_CONNECT &&
				error != ERROR_WINHTTP_CONNECTION_ERROR) {
				return FALSE;
			}
			continue;
		}
		vbool = WinHttpReceiveResponse(_hRequest, NULL) > 0;
		if (vbool) {
			break;
		}
		error = GetLastError();
		if (error != ERROR_WINHTTP_CANNOT_CONNECT &&
			error != ERROR_WINHTTP_CONNECTION_ERROR) {
			return FALSE;
		}
	}
	if (!vbool) {
		return FALSE;
	}

	//处理协议头和Cookies
	__GetQueryHeadersInfo(NopNullCookieName);

	//处理重定向
	__Redirect(NopNullCookieName, SendRetryCount);
	return TRUE;
}

DWORD CXWinHttp::GetResponseBody(CXBytes& req) {
	if (_hRequest == 0 || _ContentLength == 0) {
		return {};
	}
	DWORD Ptri;
	if (_ResponseBodylen != NULL) {
		req = "";
		return 0;
	}
	//接收数据
	Ptri = 0;
	DWORD dwSize;
	LPSTR pszOutBuffer;
	DWORD dwDownloaded = 0;
	do {
		// 检查可用数据
		dwSize = 0;
		if (!WinHttpQueryDataAvailable(_hRequest, &dwSize)) {
			xcl_log(L"Error ", GetLastError(), L" in WinHttpQueryDataAvailable.\n");
			break;
		}
		// 没有更多的可用数据
		if (!dwSize) {
			break;
		}
		//为缓冲区分配空间
		pszOutBuffer = new char[dwSize + 1];
		if (!pszOutBuffer) {
			xcl_log(L"Out of memory\n");
			break;
		}
		// 读入数据开始.
		ZeroMemory(pszOutBuffer, dwSize + 1);
		if (!WinHttpReadData(_hRequest, (LPVOID)pszOutBuffer, dwSize,
			&dwDownloaded)) {
			xcl_log(L"Error ", GetLastError(), L" in WinHttpReadData.\n");
		} else {
			req.add(pszOutBuffer, dwSize);
		}
		// 释放分配给缓冲区的内存空间.
		delete[] pszOutBuffer;
		// This condition should never be reached since WinHttpQueryDataAvailable
		// reported that there are bits to read.
		if (!dwDownloaded) {
			break;
		}
	} while (dwSize > 0);
	return req.size();
}

DWORD CXWinHttp::GetResponseBodyText_Utf8ToW(CXText& req) {
	CXTextA txt;
	GetResponseBodyText_Utf8ToA(txt);
	req = A2W(txt.get());
	return req.size();
}

DWORD CXWinHttp::GetResponseBodyTextUTF8(CXTextA& req) {
	if (_hRequest == 0 || _ContentLength == 0) {
		return {};
	}
	DWORD Ptri;
	if (_ResponseBodylen != NULL) {
		req = "";
		return 0;
	}
	//接收数据
	Ptri = 0;
	DWORD dwSize;
	LPSTR pszOutBuffer;
	DWORD dwDownloaded = 0;
	do {
		// 检查可用数据
		dwSize = 0;
		if (!WinHttpQueryDataAvailable(_hRequest, &dwSize)) {
			xcl_log(L"Error ", GetLastError(), L" in WinHttpQueryDataAvailable.\n");
			break;
		}
		// 没有更多的可用数据
		if (!dwSize) {
			break;
		}
		//为缓冲区分配空间
		pszOutBuffer = new char[dwSize + 1];
		if (!pszOutBuffer) {
			xcl_log(L"Out of memory\n");
			break;
		}
		// 读入数据开始.
		ZeroMemory(pszOutBuffer, dwSize + 1);
		if (!WinHttpReadData(_hRequest, (LPVOID)pszOutBuffer, dwSize,
			&dwDownloaded)) {
			xcl_log(L"Error ", GetLastError(), L" in WinHttpReadData.\n");
		} else {
			req+=pszOutBuffer;
		}
		// 释放分配给缓冲区的内存空间.
		delete[] pszOutBuffer;
		// This condition should never be reached since WinHttpQueryDataAvailable
		// reported that there are bits to read.
		if (!dwDownloaded) {
			break;
		}
	} while (dwSize > 0);
	return req.size();
}

DWORD CXWinHttp::GetResponseBodyText_Utf8ToA(CXTextA& req) {
	GetResponseBodyTextUTF8(req);
	req = U2A(req.get(), req.size());
	//req = W_Coding_Utf82Gbk(req);
	return req.size();
}

int CXWinHttp::GetStatus() { return _wtoi(GetStatusText()); }

CXText CXWinHttp::GetStatusText() {
	if (!_hRequest) {
		return L"0";
	}
	DWORD len;
	WinHttpQueryHeaders(_hRequest, WINHTTP_QUERY_STATUS_CODE, NULL, NULL, &len,
		NULL);
	wchar_t* bin = new wchar_t[len];
	if (WinHttpQueryHeaders(_hRequest, WINHTTP_QUERY_STATUS_CODE, NULL, bin, &len,
		NULL) <= 0) {
		delete bin;
		return 0;
	}
	CXText r = bin;
	delete bin;
	return r;
}

CXText CXWinHttp::GetAllResponseHeaders() { return _ResponseHeaders; }

CXText CXWinHttp::GetResponseHeader(CXText Header) {
	if (_ResponseHeaders == L"") {
		return L"";
	}
	std::wstring str = L"\n";
	str += Header + ":";
	std::wstring ret;
	size_t i = _ResponseHeaders.find(str);
	if (i != std::wstring::npos) {
		i += str.size();
		size_t ii = _ResponseHeaders.find(L"\n", i);
		if (i != std::wstring::npos) {
			ret = _ResponseHeaders.substr(i, ii - i);
			lTrim(ret);
		}
	}
	return ret;
}

CXText CXWinHttp::GetAllResponseCookies() {
	if (_ResponseHeaders == L"") {
		return L"";
	}
	std::wstring cookie, Cookies;
	size_t i = _ResponseHeaders.find(L"Set-Cookie:");
	size_t ii = 0;
	while (i != std::wstring::npos && ii != std::wstring::npos) {
		if (i > _ResponseHeaders.size()) {  // 64位情况下可能会出现溢出导致无限循环,所以手动跳出
			break;
		}
		ii = _ResponseHeaders.find(L";", i);
		if (ii != std::wstring::npos) {
			ii++;
			cookie = _ResponseHeaders.substr(i, ii - i);
			lTrim(cookie);
			std::wstring Value = cookie.substr(cookie.size() - 9, cookie.size());
			BOOL del = Value == L"=deleted;" || Value == L"=DELETED;" ||
				Value == L"=Deleted;";  // 判断是否是删除标记
			if (!del) {
				Cookies = Cookies + cookie + L" ";
			}
			i = _ResponseHeaders.find(L"Set-Cookie:", ii);
		}
	}
	if (Cookies != L"") {
		Cookies = Cookies.substr(0, Cookies.size() - 2);
	}
	return Cookies;
}

CXText CXWinHttp::GetResponseCookie(CXText Name) {
	if (_ResponseHeaders == L"") {
		return L"";
	}
	std::wstring str = L"Set-Cookie: " + Name + L"=", ret;
	size_t i = _ResponseHeaders.find(str);
	if (i != std::wstring::npos) {
		i += str.size();
		size_t ii = _ResponseHeaders.find(L";", i);
		if (ii != std::wstring::npos) {
			ret = _ResponseHeaders.substr(i, ii - i);
		} else {
			str = L"Set-Cookie: " + Name + "=";
			i = _ResponseHeaders.find(str);
			if (i != std::wstring::npos) {
				i += str.size();
				ii = _ResponseHeaders.find(L";", i);
				if (ii != std::wstring::npos) {
					ret = _ResponseHeaders.substr(i, ii - i);
				}
			}
		}
	}
	return ret;
}

CXText CXWinHttp::GetResponseLocation(BOOL autobUrl) {
	std::wstring ret;
	if (_ResponseHeaders == L"") {
		return L"";
	}
	size_t i = _ResponseHeaders.find(L"Location:");
	if (i != std::wstring::npos) {
		i += 9;
		size_t ii = _ResponseHeaders.find(L"\n", i);
		if (ii != std::wstring::npos) {
			ret = _ResponseHeaders.substr(i, ii - i);
			Trim(ret);
			if (ret != L"") {
				if (autobUrl) {
					std::wstring str = ret;
					w_tolower(str);
					if (ret.substr(0, 1) == L"/") {  //比如 /demo/index.html
						std::wstring l = _Scheme == 2 ? L"https://" : L"http://";
						l += _HostName;
						l += L":";
						wchar_t str[40];
						_itow_s(_Port, str, 40);
						l += str;
						ret = l + ret;
					}
					if (str.substr(0, 7) != L"http://" &&
						str.substr(0, 8) != L"https://")  // 比如index2.html
					{
						i = rFind(_UrlW, L"/");
						if (i == std::wstring::npos) {
							ret = _UrlW + L"/" + ret;
						} else {
							ret = _UrlW.substr(0, i) + _UrlW;
						}
					}
				}
			}
		}
	}
	return ret;
}

BOOL CXWinHttp::SetTimeouts(int ResolveTimeout, int ConnectTimeout,
	int SendTimeout, int ReceiveTimeout) {
	if (!_hSession) {
		return FALSE;
	}
	return WinHttpSetTimeouts(_hSession, ResolveTimeout, ConnectTimeout,
		SendTimeout, ReceiveTimeout) > 0;
}

BOOL CXWinHttp::SetProxy(CXText Proxy, CXText User, CXText Pass) {
	if (!_hSession) {
		return FALSE;
	}
	WINHTTP_PROXY_INFO op;
	if (Proxy == L"") {
		op.dwAccessType = WINHTTP_ACCESS_TYPE_NO_PROXY;
		op.lpszProxy = NULL;
		op.lpszProxyBypass = NULL;
		return WinHttpSetOption(_hSession, WINHTTP_OPTION_PROXY, &op, 12) > 0;
	}
	if (_hRequest) {  //如果是在Open之后调用 可直接设置代理信息
		WinHttpSetOption(_hRequest, WINHTTP_OPTION_PROXY_USERNAME, (void*)User.get(),
			User.size());
		WinHttpSetOption(_hRequest, WINHTTP_OPTION_PROXY_PASSWORD, (void*)Pass.get(),
			Pass.size());
	} else {
		_SetProxyInfo = TRUE;
		_SetProxyUser = User;
		_SetProxyPass = Pass;
	}
	op.dwAccessType = WINHTTP_ACCESS_TYPE_NAMED_PROXY;
	op.lpszProxy = (LPWSTR)Proxy.get();
	op.lpszProxyBypass = NULL;
	return WinHttpSetOption(_hSession, WINHTTP_OPTION_PROXY, &op,
		sizeof(WINHTTP_PROXY_INFO)) > 0;
}

BOOL CXWinHttp::SetCredentials(CXText UserName, CXText Password, int AuthTargets,
	int AuthScheme) {
	if (!_hRequest) {
		return FALSE;
	}
	return WinHttpSetCredentials(_hRequest, AuthTargets, AuthScheme, UserName,
		Password, NULL) > 0;
}

BOOL CXWinHttp::SetOption(int Type, int Option, LPVOID ValueBuffer,
	int BufferLength) {
	HINTERNET hInternet = 0;
	switch (Type) {
	case 1:
		hInternet = _hConnect;
		break;
	case 2:
		hInternet = _hRequest;
	case 3:
		hInternet = _hSession;
	default:
		hInternet = _hConnect;
		break;
	}
	return WinHttpSetOption(hInternet, Option, ValueBuffer, BufferLength) > 0;
}

void CXWinHttp::SetRedirect(BOOL IsRedirect) { _NeverRedirect = !IsRedirect; }

BOOL CXWinHttp::SetRequestHeader(CXText Header, CXText Value, int Modifiers) {
	if (!_hRequest || Header == L"") {
		return FALSE;
	}
	std::wstring t = Header;
	w_tolower(t);
	if (_AutoCookies && t == L"cookie") {
		DWORD cset = WINHTTP_DISABLE_COOKIES;
		WinHttpSetOption(_hRequest, WINHTTP_OPTION_DISABLE_FEATURE, &cset,
			sizeof(cset));  //设置禁止Winhttp内部自动处理Cookies
	}
	std::wstring HeaderW = Header + L":" + Value;
	return WinHttpAddRequestHeaders(_hRequest, HeaderW.c_str(), HeaderW.size(),
		Modifiers) > 0;
}

BOOL CXWinHttp::DelRequestHeader(CXText Header) {
	if (!_hRequest || Header == L"") {
		return FALSE;
	}
	std::wstring t = Header;
	w_tolower(t);
	if (_AutoCookies && t == L"cookie") {
		DWORD cset = WINHTTP_DISABLE_COOKIES;
		WinHttpSetOption(_hRequest, WINHTTP_OPTION_DISABLE_FEATURE, &cset,
			sizeof(cset));  //设置禁止Winhttp内部自动处理Cookies
	}
	std::wstring HeaderW = Header + L":";
	return WinHttpAddRequestHeaders(_hRequest, HeaderW.c_str(), HeaderW.size(),
		WINHTTP_ADDREQ_FLAG_REPLACE) > 0;
}

BOOL CXWinHttp::SetCookie(CXText Cookie) {
	if (_AutoCookies == 0) {
		if (!_hRequest) {
			return FALSE;
		}
		DWORD cset = WINHTTP_DISABLE_COOKIES;
		WinHttpSetOption(_hRequest, WINHTTP_OPTION_DISABLE_FEATURE, &cset,
			sizeof(cset));  //设置禁止Winhttp内部自动处理Cookies
		return SetRequestHeader(L"Cookie", Cookie);
	} else if (_AutoCookies == 1) {
		return CookieAdd(Cookie);
	} else if (_AutoCookies == 2) {
		return __SetCookies2(Cookie);  //处理更新到IES缓存
	}
	return FALSE;
}

BOOL CXWinHttp::SetUserAgent(CXText UserAgentValue) {
	return SetRequestHeader(L"User-Agent", UserAgentValue);
}

BOOL CXWinHttp::SetReferer(CXText RefererValue) {
	if (RefererValue == L"") {
		RefererValue = _UrlW;
	}
	return SetRequestHeader(L"Referer", RefererValue);
}

BOOL CXWinHttp::SetAccept(CXText AcceptValue) {
	return SetRequestHeader(L"Accept", AcceptValue);
}

BOOL CXWinHttp::SetAcceptLanguage(CXText AcceptLanguageValue) {
	return SetRequestHeader(L"Accept-Language", AcceptLanguageValue);
}

BOOL CXWinHttp::SetContentType(CXText ContentTypeValue) {
	return SetRequestHeader(L"Content-Type", ContentTypeValue);
}

BOOL CXWinHttp::SetXMLHttpRequest() {
	return SetRequestHeader(L"x-requested-with", L"XMLHttpRequest");
}

BOOL CXWinHttp::SetFakeIP(CXText FakeIP) {
	if (!_hRequest) {
		return FALSE;
	}
	std::wstring Header = L"X-Forwarded-For: " + FakeIP + L"\n";
	Header += L"CLIENT_IP: " + FakeIP + L"\n";
	Header += L"VIA: " + FakeIP + L"\n";
	Header += L"REMOTE_ADDR: " + FakeIP;
	return WinHttpAddRequestHeaders(
		_hRequest, Header.c_str(), Header.size(),
		WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE) > 0;
}

void CXWinHttp::SetRequestHeaders(CXText Headers) {
	//auto list = X_String_SplitWithStl(Headers, L"\n");
	CXVector<CXText> list_=text_splitChar(Headers.get(), '\n');
	for (int i = 0; i < (int)list_.size(); i++) {
		size_t index = list_[i].find(L":");
		if (index != -1) {
			SetRequestHeader(list_[i].substr(0, index), list_[i].substr(index + 1, list_[i].size() - index));
		}
	}
}
CXText CXWinHttp::Cookies(CXText NewCookies) {
	xcl_log(L"1");
	if (NewCookies == L"") {
		return _Cookies.size() < 7 ? _Cookies : _Cookies.substr(2, _Cookieslen - 3);
	}
	xcl_log(L"1");
	std::wstring str;
	if (NewCookies.substr(0, 2) != L"; ") {
		str = L"; " + NewCookies;
	} else {
		str = NewCookies;
	}
	xcl_log(L"2");
	if (str.substr(str.size() - 2, 2) != L"; ") {
		std::wstring text = str.substr(str.size() - 1, 1);
		if (text != L";") {
			str += L";";
		}
		if (text != L" ") {
			str += L" ";
		}
	}
	xcl_log(L"3");
	_Cookies = str;
	_Cookieslen = (int)_Cookies.size();
	return NewCookies;
}

CXText CXWinHttp::CookieGet(CXText Name, BOOL AddName) {
	std::wstring str;
	if (Name == L"") {
		return str;
	}
	// Cookie名 区分大小写
	size_t i = _Cookies.find(L"; " + Name);
	if (i != std::wstring::npos) {
		i += 2;
		int len = Name.size();
		size_t ii = _Cookies.find(L";", i + len);
		if (ii != std::wstring::npos) {
			if (!AddName) {
				i = i + len + 1;
			}
			str = _Cookies.substr(i, ii - i);
		}
	}
	return str;
}

BOOL CXWinHttp::CookieAdd(CXText Cookie) {
	if (Cookie == L"") {
		return FALSE;
	}
	std::vector<std::wstring> strs = split(Cookie, L';');
	size_t i = 0;
	BOOL vbool = FALSE;
	for (size_t jc = 0; jc < strs.size(); jc++) {
		lTrim(strs[jc]);
		i = strs[jc].find(L"=");
		if (i != std::wstring::npos) {
			std::wstring name = L"; " + strs[jc].substr(0, i - 1) + L"=";
			i = _Cookies.find(name);
			if (i != std::wstring::npos) {
				size_t ii = _Cookies.find(L"; ", i + name.size());
				if (ii != std::wstring::npos) {
					i += 2;
					_Cookies.replace(i, ii - i, strs[jc]);
				}
			} else {
				_Cookies += strs[jc] + L"; ";
				vbool = TRUE;
			}
		}
	}
	if (vbool) {
		_Cookieslen = _Cookies.size();
	}
	return vbool;
}

BOOL CXWinHttp::CookieDel(CXText Cookie) {
	if (Cookie == L"") {
		return FALSE;
	}
	BOOL vbool = FALSE;
	std::vector<std::wstring> strs = split(Cookie, L';');
	for (size_t jc = 0; jc < strs.size(); jc++) {
		lTrim(strs[jc]);
		size_t i = strs[jc].find(L"=");
		if (i != std::wstring::npos) {
			strs[jc] = strs[jc].substr(0, i);
		}
		i = _Cookies.find(strs[jc]);
		if (i != std::wstring::npos) {
			size_t ii = _Cookies.find(L"; ", i + strs[jc].size());
			if (ii != std::wstring::npos) {
				int n = ii - i;
				std::wstring t(_Cookies.c_str());
				t.replace(t.begin() + i, t.begin() + ii + 1, L"");
				_Cookies = t.c_str();
				//我超？？？迭代器报错？？日了g了c
				//_Cookies.replace(i, ii, L"");

				vbool = TRUE;
			}
		}
	}
	if (vbool) {
		_Cookieslen = _Cookies.size();
	}
	return vbool;
}
