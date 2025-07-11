#include "module_curl.h"

CURL网络传输类::CURL网络传输类()
{
	m_RequstHeaderList = NULL;
	m_curl = NULL;
	m_form = NULL;
}

size_t CURL网络传输类::write_data(void* contents, size_t size, size_t nmemb, void* userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)userp;

	char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if (ptr == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}


size_t CURL网络传输类::write_head(char* buffer, size_t size, size_t nitems, void* userp)
{
	size_t realsize = size * nitems;
	struct MemoryStruct* mem = (struct MemoryStruct*)userp;

	char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if (ptr == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), buffer, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}


int CURL网络传输类::全局初始化CURL() {
	CURLcode	ret=curl_global_init(CURL_GLOBAL_ALL);
	return (vint)ret;
}

char* CURL网络传输类::取版本() {
	char* ver=curl_version();
	return ver;
}

CURL* CURL网络传输类::初始化CURL句柄() {
	ZeroMemory(m_szErrorBuffer, sizeof(m_szErrorBuffer));
	m_curl = curl_easy_init();
	m_ResponsBody.memory = (char*)malloc(1);
	if (m_ResponsBody.memory != NULL) m_ResponsBody.memory[0] = (char)0;
	m_ResponsBody.size = 0;
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void*)&m_ResponsBody);
	m_ResponsHead.memory = (char*)malloc(1);
	if (m_ResponsHead.memory != NULL) m_ResponsHead.memory[0] = (char)0;
	m_ResponsHead.size = 0;
	curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, write_head);
	curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, (void*)&m_ResponsHead);
	m_RequstHeaderList = NULL;
	curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, m_szErrorBuffer);
	return m_curl;
}

void CURL网络传输类::置地址(LPCSTR url) {
	curl_easy_setopt(m_curl, CURLOPT_URL,url);
}

void CURL网络传输类::置文件(LPCSTR name,LPCSTR file) {
	struct curl_httppost* lastptr = NULL;
	curl_formadd(&m_form, &lastptr,
                     CURLFORM_COPYNAME, name,
                     CURLFORM_FILE, file,
                     CURLFORM_END);
	curl_easy_setopt(m_curl, CURLOPT_HTTPPOST, m_form);
}
void CURL网络传输类::置POST数据(const char* data, long length)
{
	curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data);
	curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, length);
}

BOOL CURL网络传输类::执行访问()
{
	if (m_RequstHeaderList != NULL) {
		curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_RequstHeaderList);
	}
	if (m_ResponsHead.memory != NULL)
	{
		free(m_ResponsHead.memory);
	}
	if (m_ResponsBody.memory != NULL)
	{
		free(m_ResponsBody.memory);
	}

	m_ResponsBody.memory = (char*)malloc(1);
	if (m_ResponsBody.memory != NULL) m_ResponsBody.memory[0] = (char)0;
	m_ResponsBody.size = 0;

	m_ResponsHead.memory = (char*)malloc(1);
	if (m_ResponsHead.memory != NULL) m_ResponsHead.memory[0] = (char)0;
	m_ResponsHead.size = 0;

	BOOL res = (curl_easy_perform(m_curl) == CURLE_OK) ? TRUE : FALSE;
	return res;
}

void CURL网络传输类::清理() {
	curl_easy_cleanup(m_curl);
	curl_formfree(m_form);
	if (m_ResponsHead.memory != NULL) 
	{
		free(m_ResponsHead.memory);
	}
	if (m_ResponsBody.memory != NULL)  
	{
		free(m_ResponsBody.memory);
	}
}

void CURL网络传输类::置UserAgent(LPCSTR m_UserAgent)
{
	if (m_curl == NULL) {
		return;
	}
	curl_easy_setopt(m_curl, CURLOPT_USERAGENT, m_UserAgent);
}

void CURL网络传输类::置Encoding(LPCSTR m_Encoding)
{
	if (m_curl == NULL) {
		return;
	}
	curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, m_Encoding);
}

void CURL网络传输类::置Referer(LPCSTR m_Referer)
{
	if (m_curl == NULL) {
		return;
	}
	curl_easy_setopt(m_curl, CURLOPT_REFERER, m_Referer);
}


void CURL网络传输类::置TimeOut(INT m_TimeOut)
{
	if (m_curl == NULL) {
		return;
	}
	curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, true); //libcurl支持毫秒, 用户反馈需要开启这个才支持毫秒
	curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT_MS, m_TimeOut);
}

void CURL网络传输类::置Nobody()
{
	curl_easy_setopt(m_curl, CURLOPT_NOBODY);
}

void CURL网络传输类::置请求头(LPCSTR header) 
{
	m_RequstHeaderList = curl_slist_append(m_RequstHeaderList, header);
}

void CURL网络传输类::清空请求头()
{
	curl_slist_free_all(m_RequstHeaderList);
	m_RequstHeaderList = NULL;
}

void CURL网络传输类::置请求方式(LPCSTR m_Methed) {
	if (lstrcmpA(m_Methed, "GET") == 0)
	{
		curl_easy_setopt(m_curl, CURLOPT_HTTPGET, 1L);
	}
	else if (lstrcmpA(m_Methed, "POST") == 0)
	{
		curl_easy_setopt(m_curl, CURLOPT_POST, 1L);
	}
}

VOID CURL网络传输类::置重定向次数(INT m_MaxRederects) 
{
	if (m_MaxRederects > 0)
	{
		curl_easy_setopt(m_curl, CURLOPT_MAXREDIRS, m_MaxRederects);
		curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
	}
	else
	{
		curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 0);
	}
}

void CURL网络传输类::启用Cookie记录(LPCSTR m_FilePath)
{
	if (m_curl == NULL) {
		return;
	}
	curl_easy_setopt(m_curl, CURLOPT_COOKIEFILE, m_FilePath);
	curl_easy_setopt(m_curl, CURLOPT_COOKIEJAR, m_FilePath);
}


void CURL网络传输类::置Cookie(LPCSTR m_Cookie)
{
	if (m_curl == NULL) {
		return;
	}
	curl_easy_setopt(m_curl, CURLOPT_COOKIE, m_Cookie);
}


void CURL网络传输类::置SSLCert(const char* m_CertFile, const char* m_KeyFile, const char* m_KeyPassword)
{
	curl_easy_setopt(m_curl, CURLOPT_SSLCERT, m_CertFile);
	curl_easy_setopt(m_curl, CURLOPT_SSLKEY, m_KeyFile);
	curl_easy_setopt(m_curl, CURLOPT_KEYPASSWD, m_KeyPassword);
}

void CURL网络传输类::置SSLCertMem(void* lpCerFileData, int CerFileDataLen, const char* lpszCertType,
	void* lpKeyFileData, int nKeyFileDataLen, const char* lpszKeyFileType, const char* lpKeyPassword)
{
	struct curl_blob stblob;
	stblob.data = lpCerFileData;
	stblob.len = CerFileDataLen;
	stblob.flags = CURL_BLOB_COPY;
	curl_easy_setopt(m_curl, CURLOPT_SSLCERT_BLOB, &stblob);
	curl_easy_setopt(m_curl, CURLOPT_SSLCERTTYPE, lpszCertType);

	struct curl_blob blob;
	blob.data = lpKeyFileData;
	blob.len = nKeyFileDataLen;
	blob.flags = CURL_BLOB_COPY;
	curl_easy_setopt(m_curl, CURLOPT_SSLKEY_BLOB, &blob);
	curl_easy_setopt(m_curl, CURLOPT_SSLKEYTYPE, lpszKeyFileType);

	curl_easy_setopt(m_curl, CURLOPT_KEYPASSWD, lpKeyPassword);
}

void CURL网络传输类::置SSLVerifyPeer(BOOL bVerify)
{
	curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, bVerify);
}

void CURL网络传输类::置SSLVerifyHost(BOOL bVerify)
{
	curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, bVerify);
}


const char* CURL网络传输类::取Url()
{
	char* url = NULL;
	curl_easy_getinfo(m_curl, CURLINFO_EFFECTIVE_URL, &url);
	if (url == NULL) {
		return "";
	}
	return url;
}

const char* CURL网络传输类::取远端IP()
{
	char* ip;
	curl_easy_getinfo(m_curl, CURLINFO_PRIMARY_IP, &ip);
	if (ip == NULL) {
		return "";
	}
	return ip;
}


INT CURL网络传输类::取远端端口()
{
	long port;
	curl_easy_getinfo(m_curl, CURLINFO_PRIMARY_PORT, &port);
	return port;
}

INT CURL网络传输类::取状态码()
{
	long nResponsCode;
	curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &nResponsCode);
	return nResponsCode;
}

const char* CURL网络传输类::取错误信息()
{
	return m_szErrorBuffer;
}

const char* CURL网络传输类::取响应头()
{
	return m_ResponsHead.memory;
}

const char* CURL网络传输类::取响应内容()
{
	return m_ResponsBody.memory;
}

size_t CURL网络传输类::取响应内容长度()
{
	return m_ResponsBody.size;
}

LPCSTR CURL网络传输类::取跳转地址()
{
	if (m_curl == NULL) {
		return 0;
	}
	char* url = NULL;
	curl_easy_getinfo(m_curl, CURLINFO_EFFECTIVE_URL, &url);
	return url;
}

LPCSTR CURL网络传输类::取OriginalCookie()
{
	if (m_curl == NULL) {
		return "";
	}
	ZeroMemory(m_lpszCookies, sizeof(m_lpszCookies));
	struct curl_slist* cookies = NULL;
	CURLcode res = curl_easy_getinfo(m_curl, CURLINFO_COOKIELIST, &cookies);

	if (!res && cookies) {
		struct curl_slist* each = cookies;
		while (each) {
			lstrcatA(m_lpszCookies, each->data);
			each = each->next;
		}
	}
	if (cookies) curl_slist_free_all(cookies);
	return m_lpszCookies;
}

LPCSTR CURL网络传输类::取Cookies()
{
	if (m_curl == NULL) {
		return "";
	}
	ZeroMemory(m_lpszCookies, sizeof(m_lpszCookies));

	struct curl_slist* cookies, * temp;
	curl_easy_getinfo(m_curl, CURLINFO_COOKIELIST, &cookies);

	temp = cookies;
	while (temp) {
		int	   nCount = 0;
		char* pOffset = temp->data;
		while (*pOffset != 0)
		{
			if (*pOffset == '\t') {
				nCount++;
				if (nCount == 5) break;
			}
			pOffset++;
		}

		pOffset++;


		std::string szKey, szValue;
		while (*pOffset != '\t')
		{
			szKey += *pOffset;
			pOffset++;
		}

		pOffset++;
		szValue = pOffset;


		lstrcatA(m_lpszCookies, szKey.c_str());
		lstrcatA(m_lpszCookies, "=");
		lstrcatA(m_lpszCookies, szValue.c_str());


		temp = temp->next;

		if (temp != NULL)
		{
			lstrcatA(m_lpszCookies, "; ");
		}

	}

	if (cookies)
		curl_slist_free_all(cookies);

	return m_lpszCookies;
}

__int64 CURL网络传输类::取下载时间()
{
	if (m_curl == NULL) {
		return 0;
	}
	curl_off_t val = 0;
	curl_easy_getinfo(m_curl, CURLINFO_TOTAL_TIME_T, &val);
	return val;
}


__int64 CURL网络传输类::取下载速率()
{
	if (m_curl == NULL) {
		return 0;
	}
	curl_off_t val = 0;
	curl_easy_getinfo(m_curl, CURLINFO_SPEED_DOWNLOAD_T, &val);
	return val;
}

