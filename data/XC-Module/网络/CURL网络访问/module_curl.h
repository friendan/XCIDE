#pragma once
//@模块名称  CURL网络访问 
//@版本  1.2.2
//@日期  2021-04-29
//@作者  zgr封装  
//@模块备注 封装自开源CURL项目
// CURL网络访问:https://github.com/curl/curl 目前只封装了http和https的网络请求，支持GET和POST提交数据
// https://curl.se/libcurl/c/
//@依赖  module_base.h
//@QQ  154460336

#include <iostream>
#include "lib/include/curl.h"

#if XC_MODULE
#include "module_base.h"
#endif

#ifdef  _WIN64
//@lib  "x64\libcurl.lib"
//@复制文件 @当前模块路径 "x64\libcurl.dll"
//@复制文件 @当前模块路径 "x64\libssh2.dll"
//@复制文件 @当前模块路径 "x64\libssl-1_1-x64.dll"
//@复制文件 @当前模块路径 "x64\libcrypto-1_1-x64.dll"
#else
//@lib  "x86\libcurl.lib"
//@复制文件 @当前模块路径 "x86\libcurl.dll"
//@复制文件 @当前模块路径 "x86\libssh2.dll"
//@复制文件 @当前模块路径 "x86\libssl-1_1.dll"
//@复制文件 @当前模块路径 "x86\libcrypto-1_1.dll"
#endif

typedef void CURL;

//@src "module_curl.cpp"

struct MemoryStruct {
	char* memory;
	size_t size;
};

//@备注 CURL网络传输类 目前只封装了http和https的网络请求，支持GET和POST提交数据
class CURL网络传输类
{
public:
	CURL网络传输类();
private:
	MemoryStruct m_ResponsBody; 
	MemoryStruct m_ResponsHead;	
	struct curl_slist* m_RequstHeaderList; 
	struct curl_httppost* m_form;
	char	m_szErrorBuffer[CURL_ERROR_SIZE];
	char    m_lpszCookies[1024];
	CURL*   m_curl;
private:
	static  size_t write_data(void* contents, size_t size, size_t nmemb, void* userp);

	static size_t write_head(char* buffer, size_t size, size_t nitems, void* userp);

public:
	//@备注 全局初始化CURL 返回0为正常完成初始化，其它数字都是错误值，具体见官网文档。
	//调用 初始化CURL句柄() 会自动调用此函数, 但是非线程安全, 如果多线程需要手动调用此函数,再调用 初始化CURL句柄()
	//@返回 执行是否成功的状态码，0为成功。
	int	全局初始化CURL();  

	//@备注 取CURL版本信息。
	//@返回 CURL版本信息。
	char* 取版本();
	
	//@备注 初始化curl的实例句柄
	//@返回	CURL的实例句柄
	CURL* 初始化CURL句柄(); 

	//@备注 置访问的HTTP地址链接
	//@参数 url	  例如：A"http://www.baidu.com"
	void 置地址(LPCSTR url);

	//@参数 data  例如: A"Field=1&Field=2&Field=3"
	void 置POST数据(const char* data, long length);
	void 置文件(LPCSTR name,LPCSTR file);

	//@备注 必须完成各项置后，才可执行发起HTTP的请求数据
	//@返回	True或False确认执行状态
	BOOL 执行访问();

	//@备注 执行CURL请求后进行清理，释放连接
	void 清理(); 

	//@备注 置访问的UserAgent,例如："Mozilla / 5.0 (Windows NT 10.0; Win64; x64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 79.0.3945.88 Safari / 537.36"
	//@参数 m_UserAgent  具体UserAgent
	void 置UserAgent(LPCSTR m_UserAgent);

	//@备注 置访问的Encoding,例如："gzip, deflate"
	//@参数 m_Encoding  具体Encoding
	void 置Encoding(LPCSTR m_Encoding);

	//@备注 置访问的Referer
	//@参数 m_Referer  具体Referer
	void 置Referer(LPCSTR m_Referer);

	//@备注 置连接超时 毫秒
	//@参数 m_TimeOut  具体时间
	void 置TimeOut(INT m_TimeOut); 

	//@备注 置不需要页面内容
	void 置Nobody(); 
	
	//@备注 置请求头格式： A"Upgrade: WebSocket"  每次只能置一个参数 将作为POST的数据以表单形式提交
	//@参数 Header  置Header
	void 置请求头(LPCSTR header);

	void 清空请求头();

	//@备注 置请求方式POST或GET方式
	//@参数 m_Methed  具体方法暂时只接受POST或GET
	void 置请求方式(LPCSTR m_Methed); 

	//@备注 置最大重定向次数
	//@参数 m_MaxRederects  置最大重定向次数
	void 置重定向次数(INT m_MaxRederects);

	//@备注 启用Cookie记录
	//@参数 m_FilePath  启用Cookie记录文件的具体路径
	void 启用Cookie记录(LPCSTR m_FilePath);

	//@备注 置Cookie记录
	//@参数 m_Cookie  置Cookie
	void 置Cookie(LPCSTR m_Cookie);

	//@备注 置SSLCert
	void 置SSLCert(const char* m_CertFile, const char* m_KeyFile, const char* m_KeyPassword);

	//@备注 置SSLCertMem
	void 置SSLCertMem(void* lpCerFileData, int CerFileDataLen, const char* lpszCertType,
		void* lpKeyFileData, int nKeyFileDataLen, const char* lpszKeyFileType, const char* lpKeyPassword);

	//@备注 置SSLVerifyPeer
	void 置SSLVerifyPeer(BOOL bVerify);

	//@备注 置SSLVerifyHost
	void 置SSLVerifyHost(BOOL bVerify);

	//@备注 取对端的URL地址
	const char* 取Url();

	//@备注 取远端IP
	const char* 取远端IP();

	//@备注 取远端端口
	INT 取远端端口();

	//@备注 取状态码
	INT 取状态码();

	//@备注 取错误信息
	const char* 取错误信息();

	//@备注 取响应头
	const char* 取响应头();

	//@备注 取响应内容
	const char* 取响应内容();

	//@备注 取响应内容长度
	size_t 取响应内容长度();

	//@备注 取重定向跳转地址
	LPCSTR 取跳转地址();

	//@备注 取原始Cookie
	LPCSTR 取OriginalCookie();

	//@备注 取当前Cookie
	LPCSTR 取Cookies();

	//@备注 取当前数据返回所耗时间
	__int64 取下载时间();

	//@备注 取数据返回的速率
	__int64 取下载速率();
};
