
//#include "StdAfx.h"
//#include "common__.h"
#include "HttpClient.h"
#include"AES_Base64.h"
#include <time.h> 
#include <stdlib.h>
//#include "yazuoLog.h"

#define  BUFFER_SIZE       1024

#define  NORMAL_CONNECT             INTERNET_FLAG_KEEP_CONNECTION
#define  SECURE_CONNECT                NORMAL_CONNECT | INTERNET_FLAG_SECURE
#define  NORMAL_REQUEST             INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE 
#define  SECURE_REQUEST             NORMAL_REQUEST | INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID

CHttpClient::CHttpClient(const char* strAgent)
{
//	m_pSession = new CInternetSession(strAgent);
//	m_pConnection = NULL;
//	m_pFile = NULL;
//	m_pCurl.置SSLVerifyPeer(FALSE);
//	m_pCurl.置SSLVerifyHost(FALSE);

	m_curl.全局初始化CURL();
	m_curl.初始化CURL句柄();
}

CHttpClient::~CHttpClient(void)
{
	Clear();
//	if (NULL != m_pSession)
	{
	//	m_pSession->Close();
	//	delete m_pSession;
	//	m_pSession = NULL;
	}
}

void CHttpClient::Clear()
{
	m_curl.清理();
// 	if (NULL != m_pFile)
// 	{
// 		m_pFile->Close();
// 		delete m_pFile;
// 		m_pFile = NULL;
// 	}

// 	if (NULL != m_pConnection)
// 	{
// 		m_pConnection->Close();
// 		delete m_pConnection;
// 		m_pConnection = NULL;
// 	}
}

int CHttpClient::ExecuteRequest(const char* strMethod, const char* strUrl, const char* strPostData, string &strResponse)
{
	char* ver= m_curl.取版本();

	m_curl.置请求方式(strMethod);
	m_curl.置POST数据(strPostData, (long)strlen(strPostData));

	m_curl.置请求头(IE_AGENT);
	m_curl.置请求头("Accept: *,*/*");
	m_curl.置请求头("Accept-Language: zh-cn");
	m_curl.置请求头("ontent-Type: application/x-www-form-urlencoded");

	m_curl.置地址(strUrl);
	BOOL 访问是否成功 = m_curl.执行访问();
	int err = 0;
	if (0 == 访问是否成功)
	{
		err = m_curl.取状态码();
		return 0;
	}
	strResponse = m_curl.取响应内容();

#if 0
	std::string strServer;
	std::string strObject;
	DWORD dwServiceType;
	INTERNET_PORT nPort;
	strResponse = "";

	//AfxParseURL(strUrl, dwServiceType, strServer, strObject, nPort);

	if (AFX_INET_SERVICE_HTTP != dwServiceType && AFX_INET_SERVICE_HTTPS != dwServiceType)
	{
		return FAILURE;
	}

	try
	{
		m_pConnection = m_pSession->GetHttpConnection(strServer,
			dwServiceType == AFX_INET_SERVICE_HTTP ? NORMAL_CONNECT : SECURE_CONNECT,
			nPort);
		m_pFile = m_pConnection->OpenRequest(strMethod, strObject,
			NULL, 1, NULL, NULL,
			(dwServiceType == AFX_INET_SERVICE_HTTP ? NORMAL_REQUEST : SECURE_REQUEST));

		//DWORD dwFlags;
		//m_pFile->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, dwFlags);
		//dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
		////set web server option
		//m_pFile->SetOption(INTERNET_OPTION_SECURITY_FLAGS, dwFlags);

		m_pFile->AddRequestHeaders(L"Accept: *,*/*");
		m_pFile->AddRequestHeaders(L"Accept-Language: zh-cn");
		m_pFile->AddRequestHeaders(L"Content-Type: application/x-www-form-urlencoded");
		//m_pFile->AddRequestHeaders("Accept-Encoding: gzip, deflate");		// 返回乱码 请注释

		m_pFile->SendRequest(NULL, 0, (LPVOID)(LPCTSTR)strPostData, strPostData == NULL ? 0 : _tcslen(strPostData));

		char szChars[BUFFER_SIZE + 1] = { 0 };
		string strRawResponse = "";
		UINT nReaded = 0;
		while ((nReaded = m_pFile->Read((void*)szChars, BUFFER_SIZE)) > 0)
		{
			szChars[nReaded] = '\0';
			strRawResponse += szChars;
			memset(szChars, 0, BUFFER_SIZE + 1);
		}

		int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, strRawResponse.c_str(), -1, NULL, 0);
		WCHAR *pUnicode = new WCHAR[unicodeLen + 1];
		memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));

		MultiByteToWideChar(CP_UTF8, 0, strRawResponse.c_str(), -1, pUnicode, unicodeLen);
		CString cs(pUnicode);
		delete[]pUnicode;
		pUnicode = NULL;

		strResponse = cs;

		Clear();
	}
	catch (CInternetException* e)
	{
		Clear();
		DWORD dwErrorCode = e->m_dwError;


		DWORD dwError = GetLastError();

		//		PRINT_LOG("dwError = %d", dwError, 0);

		if (ERROR_INTERNET_TIMEOUT == dwErrorCode)
		{
			//throw;
			e->Delete();
			return OUTTIME;
		}
		else
		{
			//throw;
			e->Delete();
			return FAILURE;

		}
	}

#endif
	return SUCCESS;
}

int CHttpClient::HttpGet(const char* strUrl, const char* strPostData, std::string &strResponse)
{
	return ExecuteRequest("GET", strUrl, strPostData, strResponse);
}


inline BYTE toHex(const BYTE &x)
{
	return x > 9 ? x + 55 : x + 48;
}

std::string CHttpClient::UrlEncode(std::string sIn)
{
	std::string sOut;
	const int nLen = (int)sIn.size() + 1;
	//alloc out buffer
	char* pOutBuf =(char*)malloc(nLen * 3); // (LPBYTE)sOut.GetBuffer(nLen * 3 - 2);//new BYTE [nLen  * 3];
	if (pOutBuf)
	{
		register const char* pInTmp = sIn.c_str();
		register char* pOutTmp = pOutBuf;

		// do encoding
		while (*pInTmp)
		{
			if (isalnum(*pInTmp))
				*pOutTmp++ = *pInTmp;
			else
				if (isspace(*pInTmp))
					*pOutTmp++ = '+';
				else
				{
					*pOutTmp++ = '%';
					*pOutTmp++ = toHex(*pInTmp >> 4);
					*pOutTmp++ = toHex(*pInTmp % 16);
				}
			pInTmp++;
		}
		*pOutTmp = '\0';
		sOut =pOutBuf;
		free(pOutBuf);
	}
	return sOut;
}

int ReadNum()
{
	srand((unsigned)time(NULL));

	return rand();
}

int CHttpClient::HttpPost(const char* strUrl, const char* strPostData, std::string &strResponse)
{
	std::string Pass = "";
	std::string Data = strPostData;
	std::string Num= XCL_ToTextA(ReadNum());
	//Num.Format("%d", ReadNum());
	Num = "m" + Num;
	std::string EnData = "";

	//MessageBox(0, Num, "0", MB_OK);
	//appsafecode=安全防封包劫持，发送服务器原文返回，不是原文返回说明被劫持了
	Data = "<httpdatas>" + Data + "&appsafecode=" + Num + "</httpdatas>";
	//MessageBox(0, Data, "0", MB_OK);
	Data = EncryptionAES(Data.data()).c_str();
	Data = UrlEncode(Data);
	cout << Data << endl;
	Data = "&parameter=" + Data;
	//MessageBox(0, Data, "0", MB_OK);
	int Post = ExecuteRequest("POST", strUrl, Data.data(), Pass);
	EnData = DecryptionAES(Pass);
	cout << EnData << endl;
	//appsafecode=安全防封包劫持，发送服务器原文返回，不是原文返回说明被劫持了
	int a = (int)EnData.find("<appsafecode>");
	int b = (int)EnData.find("</appsafecode>");
	if (EnData.substr(a + 13, b - a - 13).c_str() == Num)
	{
		a = (int)EnData.find("<data>");
		b = (int)EnData.find("</data>");
		strResponse = EnData.substr(a + 6, b - a - 6).c_str();
	}else
	{
		MessageBox(0, L"非法数据", L"警告", MB_OK);
	}
	return 1;
}
