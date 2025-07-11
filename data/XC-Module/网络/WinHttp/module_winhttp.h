#ifndef XC_WINHTTP_H
#define XC_WINHTTP_H

//@模块名称  WinHttp
//@版本  1.0 
//@日期  2020-06-13
//@作者  回忆(huiyi)
//@模块备注  WinHttp的封装,基本上全兼容鱼刺WinHTTP写法
// 轻量级http响应库的封装
// 单元测试覆盖率接近100%！
// 支持自管理Cookies(增/删/改/查)
// 无需附加任何dll即可支持ssl(系统需要win7 sp1以上)
//@依赖  module_base.h
//@QQ  154460336

#ifdef XC_MODULE
#include "module_base.h"
#endif

//#pragma comment(lib, "Kernel32.lib")
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
#include "haper.h"


//@src  "winhttp.cpp"
//@src  "haper.cpp"


//@隐藏{
#define HTTP_BUFFER_LEN 10240
#define DwSize 4
#define WINHTTP_DEFAULT_VERSION 0
#define HTTP_BUFFER_LENMAX 1048576
//@隐藏}

//@分组{   WINHTTP认证常量
/*@声明
//@别名 WINHTTP_AUTH_认证目标_网站服务器
#define WINHTTP_AUTH_TARGET_SERVER      0       //验证目标：网站服务器。
//@别名 WINHTTP_AUTH_认证目标_代理服务器
#define WINHTTP_AUTH_TARGET_PROXY       1       //验证目标：代理服务器。
//@别名 WINHTTP_AUTH_认证方式_基本认证_BASE64加密
#define WINHTTP_AUTH_SCHEME_BASIC       1       //基本认证方式(BASE64加密)。
//@别名 WINHTTP_AUTH_认证方式_NTLM认证
#define WINHTTP_AUTH_SCHEME_NTLM        2       //NTLM认证方式。
//@别名 WINHTTP_AUTH_认证方式_PASSPORT认证
#define WINHTTP_AUTH_SCHEME_PASSPORT    4       //PASSPORT认证方式。
//@别名 WINHTTP_AUTH_认证方式_DIGEST认证
#define WINHTTP_AUTH_SCHEME_DIGEST      8       //DIGEST认证方式。
//@别名 WINHTTP_AUTH_认证方式_NTLM_KERBEROS_中间认证
#define WINHTTP_AUTH_SCHEME_NEGOTIATE   16      //NTLM和Kerberos之间的认证方式。
*/
//@分组}

//@分组{   WINHTTP_ADDREQ_FLAG
/*@声明
//@别名 WINHTTP_ADDREQ_FLAG_添加
#define WINHTTP_ADDREQ_FLAG_ADD      536870912       //添加一个协议头，如果协议头已存在则被新值替换，与 WINHTTP_ADDREQ_FLAG_替换 标志一起使用。

//@别名 WINHTTP_ADDREQ_FLAG_新建
#define WINHTTP_ADDREQ_FLAG_ADD_IF_NEW 268435456    //只有不存在的时候才添加

//@别名 WINHTTP_ADDREQ_FLAG_合并
#define WINHTTP_ADDREQ_FLAG_COALESCE    1073741824  //合并相同的名称

//@别名 WINHTTP_ADDREQ_FLAG_合并标记逗号
#define WINHTTP_ADDREQ_FLAG_COALESCE_WITH_COMMA    1073741824  //合并相同的名称使用逗号

//@别名 WINHTTP_ADDREQ_FLAG_合并标记分号
#define WINHTTP_ADDREQ_FLAG_COALESCE_WITH_SEMICOLON    16777216  //合并相同的名称使用分号

//@别名 WINHTTP_ADDREQ_FLAG_替换
#define WINHTTP_ADDREQ_FLAG_REPLACE  2147483648
*/
//@分组}

//@别名 CXWinHttp
class CXWinHttp
{
private:
	std::wstring  _HostName;  //域名
	int     _Port;         //端口
	std::wstring  _UrlW;      //本次访问的Url （存储用于302解析）
	int     _Scheme;       //连接类型 http or https （存储用于302解析）
	BOOL    _IsPOST;

	LPVOID  _Dataptr;       //数据指针/缓冲区
	int     _ResponseBodylen;  //返回数据长度
	int     _ContentLength;    //返回数据预计长度

	std::wstring  _ResponseHeaders;  //返回协议头

	BOOL   _Auto;        //自动模式
	int    _AutoCookies;  // Cookies自动模式
	std::wstring  _Cookies;   //模式1内部Cookies
	int    _Cookieslen;   //整数型

	BOOL         _SetProxyInfo;  //标记=真 会在Send前设置下代理信息
	std::wstring _SetProxyUser;
	std::wstring _SetProxyPass;

	BOOL   _IsIgnoreError;

	BOOL   _NeverRedirect;  //是否禁止自动重定向
	int    _RedirectIndex;

	void __Init();
	void __Create();

	void __Create(CXText User_Agent);

	void __Close();

	void __InitOptions();  //初始化一些默认配置选项
	void __UpCookies1(BOOL NopNullCookieName = FALSE);  //处理并更新内部Cookies 1
	void __UpCookies2(
		BOOL NopNullCookieName = FALSE);  //处理并更新本地IESCookies 2
	BOOL __SetCookies2(CXText Cookie);    // SetCookieIES
	BOOL __LoadCookies1();                //加载并设置内部Cookies 1
	BOOL __LoadCookies2();                //加载并设置本地IESCookies 2
	void __SetRequestHeaders(BOOL IsData);  // Send前自动处理补全必须协议头
	void __SetInternetInfo();               // Send前自动处理相关信息
	BOOL __GetQueryHeadersInfo(
		BOOL NopNullCookieName);  // Send后自动获取Headers信息并处理
	void __Redirect(BOOL NopNullCookieName,
		int SendRetryCount);  // AutoCookie自动递归处理重定向

public:
	HINTERNET _hSession;  // 会话句柄
	HINTERNET _hRequest;  //请求句柄
	HINTERNET _hConnect;  //链接句柄

	CXWinHttp();
	CXWinHttp(CXText url);
	CXWinHttp(CXText url, CXText Method);
	~CXWinHttp();

	//@备注  打开一个HTTP连接
	//@别名  打开(请求地址, 请求类型)
	//@参数  Url  请求地址,例如:http://www.xcgui.com
	//@参数  Method  请求类型,例如:POST,GET,HEAD,默认GET
	BOOL Open(CXText Url, CXText Method = L"");

	//@备注  设置自动补全模式,此模式开启后会自动帮你补全必要的协议头
	//@别名  置自动补全模式(自动补全)
	//@参数  IsAuto  默认真,真=开启自动协议头补全 假=关闭自动协议头补全
	void Auto(BOOL IsAuto = TRUE);

	//@备注  设置Cookies自动管理模式
	//@别名  置Cookies管理模式(模式)
	//@参数  Index 0=Winhttp内部自动处理Cookies,1=类内部自动合并更新Cookies(此模式下可以配合独有方法Cookies CookieAdd CookieSet CookieDel 来取/设/添加/设置/删除),2=缓存到本地(支持IES控件继承 注意:模式2不兼容多线程)
	void AutoCookies(int Index = 1);

	//@别名  重置(UA)
	//@参数  User_Agent 自定义用户浏览器协议头信息 User_Agent 留空则使用默认的浏览器信息
	//@备注  重置(初始化)CXWinHttp 释放所有数据 包括之前所有设置和Cookies
	void Rest(CXText User_Agent = L"");

	//@备注  发送HTTP请求, 文本内容
	//@参数  提交文本数据,可以为空
	//@参数  默认=假, 自动更新Cookies时忽略掉Cookie键值为空的Cookie（必须在'非AutoCookies模式0'下使用）
	//@参数  默认=0, 执行Send或Recv失败后 自动重试最大次数 0=关闭Send失败重试
	//@别名  发送请求文本(提交数据,自动处理空Cookits,最大重试次数)
	BOOL SendText(CXText data_ = L"", BOOL NopNullCookieName = FALSE, int SendRetryCount = 0);

	//@备注  发送HTTP请求, 文本内容A
	//@参数  提交文本A数据,可以为空
	//@参数  默认=假, 自动更新Cookies时忽略掉Cookie键值为空的Cookie（必须在'非AutoCookies模式0'下使用）
	//@参数  默认=0, 执行Send或Recv失败后 自动重试最大次数 0=关闭Send失败重试
	//@别名  发送请求文本A(提交数据,自动处理空Cookits,最大重试次数)
	BOOL SendTextA(CXTextA data_ = "", BOOL NopNullCookieName = FALSE, int SendRetryCount = 0);

	//@备注  发送HTTP请求, 字节集内容
	//@参数  提交字节集数据,可以为空
	//@参数  默认=假, 自动更新Cookies时忽略掉Cookie键值为空的Cookie (必须在'非AutoCookies模式0'下使用)
	//@参数  默认=0, 执行Send或Recv失败后 自动重试最大次数 0=关闭Send失败重试
	//@别名  发送请求字节集(提交数据,自动处理空Cookits,最大重试次数)
	BOOL SendBytes(CXBytes data_ = "", BOOL NopNullCookieName = FALSE, int SendRetryCount = 0);

	//@备注  发送HTTP请求, 字节数据
	//@参数  提交数据, 可以为空
	//@参数  数据长度, 字节为单位
	//@参数  默认=假, 自动更新Cookies时忽略掉Cookie键值为空的Cookie (必须在'非AutoCookies模式0'下使用)
	//@参数  默认=0, 执行Send或Recv失败后 自动重试最大次数 0=关闭Send失败重试
	//@别名  发送请求(提交数据,自动处理空Cookits,最大重试次数)
	BOOL Send(const BYTE* data_=0, int length=0, BOOL NopNullCookieName = FALSE, int SendRetryCount = 0);

	//@备注  取返回字节集 （必须在Send后使用）
	//@别名  取响应数据(返回数据)
	DWORD GetResponseBody(CXBytes& req);

	//@备注  取返回文本 （自动Utf8转Ansi） （必须在Send后使用）
	//@别名  取响应文本_自动Utf8转W(返回数据)
	DWORD GetResponseBodyText_Utf8ToW(CXText& req);

	//@备注  取返回文本UTF8 （必须在Send后使用）
	//@别名  取响应文本UTF8(返回数据)
	DWORD GetResponseBodyTextUTF8(CXTextA& req);

	//@备注  取返回文本A （自动Utf8转Ansi） （必须在Send后使用）
	//@别名  取响应文本_自动Utf8转A(返回数据)
	DWORD GetResponseBodyText_Utf8ToA(CXTextA& req);

	//@备注  取状态码 （必须在Send后使用）
	//@别名  取状态码()
	int GetStatus();
	//@备注  取文本状态码 （必须在Send后使用）
	//@别名  取状态码文本()
	CXText GetStatusText();

	//@备注  取得所有HTTP返回协议头 （必须在Send后使用）
	//@别名  取所有协议头()
	CXText GetAllResponseHeaders();
	//@备注  取得HTTP返回协议头 （必须在Send后使用）
	//@别名  取协议头(协议头)
	CXText GetResponseHeader(CXText Header);

	//@备注  取得HTTP返回协议头中所有COOKIES （必须在Send后使用）
	//@别名  取所有COOKIES()
	CXText GetAllResponseCookies();
	//@备注  取得HTTP返回协议头中指定Cookie键的值 （必须在Send后使用）
	//@别名  取指定COOKIES(键名)
	//@参数  Name         Cookie键名
	CXText GetResponseCookie(CXText Name);

	//@备注  取得HTTP返回协议头中的302重定向地址 （必须在Send后使用）
	//@别名  取重定向地址(自动补全Url)
	//@参数  autobUrl     智能判断并补全url(协议头+域名+端口+路径）
	CXText GetResponseLocation(BOOL autobUrl = FALSE);

	//@备注  指定超时设置 （设置后一直有效） （要想本次访问就生效 请在Open前调用）
	//@别名  置超时(解析超时,连接超时,发送超时,接收超时)
	//@参数  ResolveTimeout     解析超时，单位毫秒 留空=10000(10秒)
	//@参数  ConnectTimeout     连接超时，单位毫秒 留空=15000(15秒)
	//@参数  SendTimeout        发送超时，单位毫秒 留空=120000(120秒/2分钟)
	//@参数  ReceiveTimeout     接收超时，单位毫秒 留空=300000(300秒/5分钟) （注意：经测试 接收超时也会影响到POST上传超时）
	BOOL SetTimeouts(int ResolveTimeout = 10000, int ConnectTimeout = 15000, int SendTimeout = 120000, int ReceiveTimeout = 300000);

	//@备注  设置或取消代理 （设置后一直有效）
	//@别名  置代理(代理地址,代理帐号,代理密码)
	//@参数  Proxy    空=取消代理  HTTP代理="http=127.0.0.1:8080"  HTTPS代理=“127.0.0.1:8080”
	//@参数  User     代理帐号
	//@参数  Pass     代理密码
	BOOL SetProxy(CXText Proxy = L"", CXText User = L"", CXText Pass = L"");

	//@备注  指定身份验证凭据 （设置后一直有效） （必须在Open后使用）
	//@别名  置身份验证凭据(用户名,密码,认证目标,认证方式)
	//@参数  UserName     用户名
	//@参数  Password     密码
	//@参数  AuthTargets  认证目标：留空=0  0=设置登录帐号密码 1=设置代理帐号密码  常量：WINHTTP_AUTH_认证目标_
	//@参数  AuthScheme   认证方式：留空=1  常量：WINHTTP_AUTH_认证方式_
	BOOL SetCredentials(CXText UserName, CXText Password,
		int AuthTargets = WINHTTP_AUTH_TARGET_SERVER,
		int AuthScheme = WINHTTP_AUTH_SCHEME_BASIC);

	//@备注  设置CXWinHttp属性选项
	//@别名  置属性设置(属性类型,属性标志,属性指针,属性长度)
	//@参数  Type         属性类型  0=会话句柄 1=连接句柄 2=请求句柄
	//@参数  Option       属性标志
	//@参数  ValueBuffer  属性指针
	//@参数  属性长度     属性长度  sizeof(type)
	BOOL SetOption(int Type, int Option, LPVOID ValueBuffer, int BufferLength);

	//@备注  是否允许自动重定向 （设置后一直有效）
	//@别名  置允许重定向(是否允许重定向)
	void SetRedirect(BOOL IsRedirect = TRUE);

	//@备注  添加或替换HTTP协议头 （本次访问有效） （必须在Open后使用）
	//@别名  置协议头(协议头名称,协议头值,标志)
	//@参数  Header       协议头名称
	//@参数  Value        协议头值 空文本为删除此协议头
	//@参数  Modifiers    标志 常量：WINHTTP_ADDREQ_FLAG_
	BOOL SetRequestHeader(CXText Header, CXText Value, int Modifiers = WINHTTP_ADDREQ_FLAG_ADD | WINHTTP_ADDREQ_FLAG_REPLACE);

	//@备注  删除HTTP协议头 （本次访问有效） （必须在Open后使用）
	//@别名  删除协议头(协议头名称)
	BOOL DelRequestHeader(CXText Header);

	//@备注  快速设置Cookie信息 （AutoCookies模式0下 必须在Open后使用）
	//@别名  置Cookie信息(Cookie)
	BOOL SetCookie(CXText Cookie);

	//@备注  快速设置User-Agent浏览器信息 （必须在Open后使用）
	//@别名  置UA信息(UA)
	BOOL SetUserAgent(CXText UserAgentValue = L"Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2) ");

	//@备注  快速设置Referer来路信息 （必须在Open后使用）
	//@别名  置Referer信息(Url)
	BOOL SetReferer(CXText RefererValue = L"");

	//@备注  快速设置Accept信息 （必须在Open后使用）
	//@别名  置Accept信息(Accept)
	BOOL SetAccept(CXText AcceptValue = L"*/*");

	//@备注  快速设置SetAccept-Language信息 （必须在Open后使用）
	//@别名  置AcceptLanguage信息(AcceptLanguageValue)
	BOOL SetAcceptLanguage(CXText AcceptLanguageValue = L"zh-cn");

	//@备注  快速设置Content-Type信息 （必须在Open后使用）
	//@别名  置ContentType信息(ContentType)
	BOOL SetContentType(CXText ContentTypeValue = L"application/x-www-form-urlencoded");

	//@备注  快速设置x-requested-with 为 XMLHttpRequest （必须在Open后使用）
	//@别名  置XMLHttpRequest()
	BOOL SetXMLHttpRequest();

	//@备注  快速设置多重伪造IP协议头（包括：X-Forwarded-For,CLIENT_IP,VIA,REMOTE_ADDR） （必须在Open后使用
	//@别名  置FakeIP(IP)
	BOOL SetFakeIP(CXText FakeIP);

	//@别名  置协议头文本(协议头文本)
	void SetRequestHeaders(CXText Headers);

	//@备注  取/设内部Cookies （AutoCookies模式1下有效）
	//@别名  Cookies(Cookies)
	CXText Cookies(CXText NewCookies = L"");

	//@备注  获取内部Cookies中的某个Cookie （AutoCookies模式1下有效）
	//@别名  获取Cookies(键名,是否附带名称)
	CXText CookieGet(CXText Name, BOOL AddName = FALSE);

	//@备注  添加或替换Cookie到内部Cookies （AutoCookies模式1下有效）
	//@别名  添加Cookie(Cookie)
	BOOL CookieAdd(CXText Cookie);

	//@备注  删除内部Cookies中的Cookie （AutoCookies模式1下有效）
	//@别名  删除Cookie(Cookie)
	//@参数  Cookie 单个或多个Cookie或Cookie名称 （例如：abc 或是 abc=123 或是 或是 abc; def;g 或是 abc=123; def=456;g=nima;id）
	BOOL CookieDel(CXText Cookie);
};


#endif  // XC_WINHTTP_H