#pragma once
// Created by Huiyi on 2021/4/20.
//
//@模块名称 炫易模块(网页)
//@版本   1.3
//@日期   2022-11-14
//@作者   Huiyi
//@模块备注 封装常用网络操作指令
//项目gitee地址 https://gitee.com/LoveA/XL_XExpand
//大部分代码已经历过粗略测试
//如发现BUG可提交issues
//https://gitee.com/LoveA/XL_XExpand/issues
//反馈QQ群:594165459

//@依赖  module_base.h, module_yyy.h, module_winhttp.h

#ifndef XL_XEXPAND_NETWORK_H
//@隐藏{
#define XL_XEXPAND_NETWORK_H    //防止复用


#ifdef XC_MODULE
#include "module_base.h"
#include "module_yyy.h"
#include "module_winhttp.h"
#endif
//@隐藏}

//@src "web.cpp"


//@分组{	网页功能

//@备注 使用WinHttp的 API方式访问网页
//@参数 网址 完整的网页地址,必须包含http://或者https://
//@参数 请求方式  0=GET 1=POST 2=HEAD  3=PUT  4=OPTIONS  5=DELETE  6=TRACE  7=CONNECT
//@参数 提交信息 POST专用
//@参数 提交Cookies 设置提交时的cookie
//@参数 返回Cookies 返回的Cookie
//@参数 附加协议头 一行一个请用换行符隔开,建议填写常量值或文本值,防止因传参引发错误
//@参数 返回协议头 返回的协议头
//@参数 禁止重定向 默认不禁止网页重定向
//@参数 代理地址  代理地址，格式为 http=8.8.8.8:88
//@参数 代理账号 代理的验证账号
//@参数 代理密码 代理的验证密码
//@参数 是否补全必要协议头 当附件协议头为空时自动添加必要的UA协议头 默认为真，假将不再添加非传入协议头
//@参数 是否处理协议头大小写 将协议头中的键名首字母处理为大写  默认为真
//@参数 返回状态码 返回网页状态码,一般成功为200
//@参数 返回状态文本 错误状态文本
//@别名 网页_访问(网址,请求方式,提交信息,提交Cookies,返回Cookies,附加协议头,返回协议头,禁止重定向,代理地址,代理账号,代理密码,是否补全必要协议头,是否处理协议头大小写,返回状态码,返回状态码文本)
CXBytes X_NetWork_Visit(CXText Url, int Method=0,CXBytes* PostData=NULL,
    CXText* SendCookies=NULL, CXText* RespCookies = NULL,
    CXText* SendHeader = NULL, CXText* RespHeader = NULL,
    bool bBanRedirect=false, CXText* agentHost=NULL, CXText* agentName = NULL, CXText* agentPasswd = NULL,
    bool completionHeader=true,bool standardHeaders=true,
    int* rStatusCode = NULL, CXText* rStatusStr = NULL);

//@备注 将协议头中的键名首字母处理为大写
//@别名 网页_处理协议头(原始协议头)
CXText X_NetWork_CompletionHeaders(CXText header);
//@备注 将协议头中的键名首字母处理为大写
//@别名 网页_处理协议头A(原始协议头)
CXTextA X_NetWork_CompletionHeadersA(CXTextA header);

//@返回 成功返回文件尺寸,失败返回-1
//@别名 网页_取网络文件尺寸(欲取网络文件地址)
ULONGLONG X_NetWork_GetNetFileSize(CXText Url);
//@返回 成功返回文件尺寸,失败返回-1
//@别名 网页_取网络文件尺寸A(欲取网络文件地址)
ULONGLONG X_NetWork_GetNetFileSizeA(CXTextA Url);

//@别名 网页_IE浏览器网页跳转静音(是否静音)
void X_NetWork_IESkipMute(bool IsMute=true);

//@别名 网页_URL取本地地址(地址)
CXText X_NetWork_UrlGetLocalPath(CXText Url);

//@备注 创建网页快捷方式
//@参数 快捷方式文件名 扩展名为.url全路径
//@参数 网页地址
//@参数 ico图标
//@参数 快捷键 快捷键键代码
//@别名 网页_创建快捷方式(快捷方式文件名,网页地址,ico图标,快捷键)
BOOL X_NetWork_CreateShortcut(CXText FileName, CXText Url,CXText IconPath=L"", WORD HotKey = 0);
//@备注 创建网页快捷方式
//@参数 快捷方式文件名 扩展名为.url全路径
//@参数 网页地址
//@参数 ico图标
//@参数 快捷键 快捷键键代码
//@别名 网页_创建快捷方式A(快捷方式文件名,网页地址,ico图标,快捷键)
BOOL X_NetWork_CreateShortcutA(CXTextA FileName, CXTextA Url, CXTextA IconPath="", WORD HotKey=0);

//@备注 使用系统默认的浏览器打开一个网址
//@别名 网页_打开指定网址(网页地址)
void X_NetWork_OpenUrl(CXText url);
//@备注 使用系统默认的浏览器打开一个网址
//@别名 网页_打开指定网址A(网页地址)
void X_NetWork_OpenUrlA(CXTextA url);

//@备注 保存网页
//@别名 网页_保存(浏览器句柄)
void X_NetWork_Save(HWND hWnd);

//@备注 保存html文档
//@别名 网页_保存html文档(浏览器句柄)
void X_NetWork_SaveHTML(HWND hWnd);

//@别名 网页_查看网页属性(浏览器句柄)
void X_NetWork_ViewProperties(HWND hWnd);

//@别名 网页_查找关键字(浏览器句柄)
void X_NetWork_FindKeyword(HWND hWnd);

//@别名 网页_打印(浏览器句柄)
void X_NetWork_Print(HWND hWnd);

//@别名 网页_打印预览(浏览器句柄)
void X_NetWork_PrintView(HWND hWnd);

//@别名 IP归属地_易炫彩
struct X_IPAscription {
    //@别名 IP
    CXText IP;
    //@别名 国家
    CXText Country;
    //@别名 省份
    CXText Region;
    //@别名 城市
    CXText City;
    //@别名 运营商
    CXText Isp;
};
//@别名 IP归属地A_易炫彩
struct X_IPAscriptionA {
    //@别名 IP
    CXTextA IP;
    //@别名 国家
    CXTextA Country;
    //@别名 省份
    CXTextA Region;
    //@别名 城市
    CXTextA City;
    //@别名 运营商
    CXTextA Isp;
};
//@参数 查询IP 可空
//@别名 网页_取IP归属地(查询IP)
X_IPAscription X_NetWork_GetIPAscription(CXText IP=L"");
//@参数 查询IP 可空
//@别名 网页_取IP归属地A(查询IP)
X_IPAscriptionA X_NetWork_GetIPAscriptionA(CXTextA IP = "");

//@别名 网页_取编码(网页地址)
CXText X_NetWork_GetHtmlCodeing(CXText url);
//@别名 网页_取编码A(网页地址)
CXTextA X_NetWork_GetHtmlCodeingA(CXTextA url);

//@备注 从左往右获取
//@别名 网页_取单条Cookie(Cookie,名称,不附带名称)
CXText X_NetWork_GetCookie(CXText cookie, CXText Name, bool NoName = true);
//@备注 从左往右获取
//@别名 网页_取单条CookieA(Cookie,名称,不附带名称)
CXTextA X_NetWork_GetCookieA(CXTextA cookie, CXTextA Name, bool NoName = true);

//@备注 取出网站服务器的默认端口
//@别名 网页_取端口(网址)
UINT X_NetWork_GetPort(CXText url);
//@备注 取出网站服务器的默认端口
//@别名 网页_取端口A(网址)
UINT X_NetWork_GetPortA(CXTextA url);

//@备注 通过“/”或者“.”来获取网址中的域名，默认使用“/”方式
//@参数 网址
//@参数 去除二级域名
//@参数 不过滤端口
//@参数 后缀点数量 不留空表示通过“.”的方式取域名 。如：.com后缀点数量为1 ,.com.cn后缀点数量为2
//@别名 网页_取域名(网址,去除二级域名,不过滤端口,后缀点数量)
CXText X_NetWork_GetHost(CXText url, bool delSL=false, bool addPort=true, int suffixNum=0);
//@备注 通过“/”或者“.”来获取网址中的域名，默认使用“/”方式
//@参数 网址
//@参数 去除二级域名
//@参数 不过滤端口
//@参数 后缀点数量 不留空表示通过“.”的方式取域名 。如：.com后缀点数量为1 ,.com.cn后缀点数量为2
//@别名 网页_取域名A(网址,去除二级域名,不过滤端口,后缀点数量)
CXTextA X_NetWork_GetHostA(CXTextA url, bool delSL = false, bool addPort = false, int suffixNum = 0);

//@备注 取网页快捷方式的地址
//@参数 文件路径 快捷方式的地址
//@参数 缓冲区大小 返回缓冲区尺寸,默认2048,默认可空
//@别名 网页_取快捷方式地址(文件路径,缓冲区大小)
CXText X_NetWork_GetShortcut(CXText path,DWORD buffSize=2048);
//@备注 取网页快捷方式的地址
//@参数 文件路径 快捷方式的地址
//@参数 缓冲区大小 返回缓冲区尺寸,默认2048,默认可空
//@别名 网页_取快捷方式地址A(文件路径,缓冲区大小)
CXTextA X_NetWork_GetShortcutA(CXTextA path, DWORD buffSize = 2048);

//@备注 取特殊网络文件名
//@别名 网页_取网络文件名(网址)
CXText X_NetWork_GetFileName(CXText url);
//@备注 取特殊网络文件名
//@别名 网页_取网络文件名A(网址)
CXTextA X_NetWork_GetFileNameA(CXTextA url);

//@备注 取一个网站地址中的文件名
//@别名 网页_取网址文件名(网址)
CXText X_NetWork_GetUrlName(CXText url);
//@备注 取一个网站地址中的文件名
//@别名 网页_取网址文件名A(网址)
CXTextA X_NetWork_GetUrlNameA(CXTextA url);

//@备注 返回指定网址的页面地址
//@别名 网页_取页面地址(网址)
CXText X_NetWork_GetPath(CXText url);
//@备注 返回指定网址的页面地址
//@别名 网页_取页面地址A(网址)
CXTextA X_NetWork_GetPathA(CXTextA url);

//@别名 网页_全选(浏览器句柄)
void X_NetWork_SelectAll(HWND hWnd);

//@别名 网页_设置网页字体(浏览器句柄)
void X_NetWork_SetPageFonts(HWND hWnd);

//@别名 网页_网络文件是否存在(网络文件名)
bool X_NetWork_FileIfExistence(CXText url);
//@别名 网页_网络文件是否存在A(网络文件名)
bool X_NetWork_FileIfExistenceA(CXTextA url);

//@备注 取出协议头中的某个值 例如302跳转协议头中的 Location
//@参数 源协议头 协议头文本
//@参数 键名 例如：Location
//@别名 网页_取协议头信息(源协议头,键名)
CXText X_NetWork_GetHeaderInfo(CXText Headers, CXText Key);
//@备注 取出协议头中的某个值 例如302跳转协议头中的 Location
//@参数 源协议头 协议头文本
//@参数 键名 例如：Location
//@别名 网页_取协议头信息A(源协议头,键名)
CXTextA X_NetWork_GetHeaderInfoA(CXTextA Headers, CXTextA Key);

//@备注 设置当前程序中浏览器的UserAgent,不影响外部浏览器使用
//@别名 网页_置浏览器UA(UserAgent)
bool X_NetWork_SetBrowserUA(CXText UserAgent);
//@备注 设置当前程序中浏览器的UserAgent,不影响外部浏览器使用
//@别名 网页_置浏览器UAA(UserAgent)
bool X_NetWork_SetBrowserUAA(CXTextA UserAgent);

//@备注 取出指定网址中所有的键名和键值，返回取到的数量
//@返回 返回参数数量
//@参数 链接 带取参数的链接,必须是转码之后的链接
//@参数 返回数据 存储参数对的字典:map<Key,Value>
//@别名 网址_取所有参数(链接,返回数据)
int X_NetWork_GetAllParameter(CXText Url, CXMap<CXText, CXText>& ret);
//@备注 取出指定网址中所有的键名和键值，返回取到的数量
//@返回 返回参数数量
//@参数 链接 带取参数的链接,必须是转码之后的链接
//@参数 返回数据 存储参数对的字典:map<Key,Value>
//@别名 网址_取所有参数A(链接,返回数据)
int X_NetWork_GetAllParameterA(CXTextA Url, CXMap<CXTextA, CXTextA>& ret);

/*@声明

//@别名 网页_是否为网页(网页地址)
BOOL PathIsURLW(LPCWSTR pszPath);

*/

//@分组}	网页功能


//@隐藏{

//窗口_查找网页句柄
void X_NetWork_FindNetWorkHwnd(HWND hWnd, HWND& hwndSDV, HWND& hwndIES);
void X_NetWork_SendMessage(HWND hWnd, int cType, int id);
CXText _X_NetWork_GetCookie(CXText cookie, CXText cookieName);
CXTextA _X_NetWork_GetCookieA(CXTextA cookie, CXTextA cookieName);
//@隐藏}


#endif //XL_XEXPAND_NETWORK_H
