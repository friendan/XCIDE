//================================================
//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG
//
//
//
//================================================
//
// Created by Huiyi on 2022/10/28.
//
//@模块名称 易炫彩Miniblink支持库
//@版本   1.1
//@日期   2022-10-28
//@作者   Huiyi
//@模块备注 Miniblink支持库的封装版本,基于 miniblink-2022.4.5


#pragma once

#ifndef XL_XMINIBLINK_H
//@隐藏{
#define XL_XMINIBLINK_H    //防止复用

#if XC_MOUDLE

#endif
//@隐藏}

#include "wke.h"

#ifdef  _WIN64
//@复制文件 @当前模块路径 "x86\node.dll"
#else
//@复制文件 @当前模块路径 "x64\node.dll"
#endif



//@分组{ 枚举类型

/*@声明

//@别名 WKE代理类型
typedef enum wkeProxyType {
    //@别名 WKE代理_无
    WKE_PROXY_NONE,
    //@别名 WKE代理_HTTP
    WKE_PROXY_HTTP,
    //@别名 WKE代理_SOCKS4
    WKE_PROXY_SOCKS4,
    //@别名 WKE代理_SOCKS4A
    WKE_PROXY_SOCKS4A,
    //@别名 WKE代理_SOCKS5
    WKE_PROXY_SOCKS5,
    //@别名 WKE代理_SOCKS5HOSTNAME
    WKE_PROXY_SOCKS5HOSTNAME
} _wkeProxyType;

//@别名 WKE菜单项ID
typedef enum wkeMenuItemId {
    //@别名 WKE菜单项_全选
    kWkeMenuSelectedAllId = 1 << 1,
    //@别名 WKE菜单项_选择文本
    kWkeMenuSelectedTextId = 1 << 2,
    //@别名 WKE菜单项_撤销
    kWkeMenuUndoId = 1 << 3,
    //@别名 WKE菜单项_复制图像
    kWkeMenuCopyImageId = 1 << 4,
    //@别名 WKE菜单项_审查元素
    kWkeMenuInspectElementAtId = 1 << 5,
    //@别名 WKE菜单项_剪切
    kWkeMenuCutId = 1 << 6,
    //@别名 WKE菜单项_粘贴
    kWkeMenuPasteId = 1 << 7,
    //@别名 WKE菜单项_打印
    kWkeMenuPrintId = 1 << 8,
    //@别名 WKE菜单项_前进
    kWkeMenuGoForwardId = 1 << 9,
    //@别名 WKE菜单项_返回
    kWkeMenuGoBackId = 1 << 10,
    //@别名 WKE菜单项_刷新
    kWkeMenuReloadId = 1 << 11,
    //@别名 WKE菜单项_保存图像
    kWkeMenuSaveImageId = 1 << 12,
} _wkeMenuItemId ;

//@别名 WKECookie命令
typedef enum wkeCookieCommand {
    //@别名 WKECookie命令_清除所有Cookie
    wkeCookieCommandClearAllCookies,
    //@别名 WKECookie命令_清除会话Cookie
    wkeCookieCommandClearSessionCookies,
    //@别名 WKECookie命令_Cookie刷新到文件
    wkeCookieCommandFlushCookiesToFile,
    //@别名 WKECookie命令_从文件重新加载Cookie
    wkeCookieCommandReloadCookiesFromFile,
} _wkeCookieCommand;

//@别名 WKE鼠标消息
typedef enum wkeMouseMsg {
    //@别名 WKE鼠标消息_移动
    WKE_MSG_MOUSEMOVE = 0x0200,
    //@别名 WKE鼠标消息_左键按下
    WKE_MSG_LBUTTONDOWN = 0x0201,
    //@别名 WKE鼠标消息_左键放开
    WKE_MSG_LBUTTONUP = 0x0202,
    //@别名 WKE鼠标消息_左键双击
    WKE_MSG_LBUTTONDBLCLK = 0x0203,
    //@别名 WKE鼠标消息_右键按下
    WKE_MSG_RBUTTONDOWN = 0x0204,
    //@别名 WKE鼠标消息_右键放开
    WKE_MSG_RBUTTONUP = 0x0205,
    //@别名 WKE鼠标消息_右键双击
    WKE_MSG_RBUTTONDBLCLK = 0x0206,
    //@别名 WKE鼠标消息_中键按下
    WKE_MSG_MBUTTONDOWN = 0x0207,
    //@别名 WKE鼠标消息_中键放开
    WKE_MSG_MBUTTONUP = 0x0208,
    //@别名 WKE鼠标消息_中键双击
    WKE_MSG_MBUTTONDBLCLK = 0x0209,
    //@别名 WKE鼠标消息_滚动事件
    WKE_MSG_MOUSEWHEEL = 0x020A,
} _wkeMouseMsg;

//@别名 WKE鼠标标志
typedef enum wkeMouseFlags {
    //@别名 WKE鼠标标志_左键
    WKE_LBUTTON = 0x01,
    //@别名 WKE鼠标标志_右键
    WKE_RBUTTON = 0x02,
    //@别名 WKE鼠标标志_SHIFT
    WKE_SHIFT = 0x04,
    //@别名 WKE鼠标标志_CTRL
    WKE_CONTROL = 0x08,
    //@别名 WKE鼠标标志_中间
    WKE_MBUTTON = 0x10,
} _wkeMouseFlags;

//@别名 WKE控制台输出等级
typedef enum wkeConsoleLevel {
    //@别名 WKE控制台等级_调试
    wkeLevelDebug = 4,
    //@别名 WKE控制台等级_日志
    wkeLevelLog = 1,
    //@别名 WKE控制台等级_信息
    wkeLevelInfo = 5,
    //@别名 WKE控制台等级_警告
    wkeLevelWarning = 2,
    //@别名 WKE控制台等级_错误
    wkeLevelError = 3,
    //@别名 WKE控制台等级_取消的错误
    wkeLevelRevokedError = 6,
    //@别名 WKE控制台等级_Last
    wkeLevelLast = wkeLevelInfo
} _wkeConsoleLevel;

//@别名 WKE导航类型
typedef enum wkeNavigationType {
    //@别名 WKE导航_点击链接
    WKE_NAVIGATION_TYPE_LINKCLICK,
    //@别名 WKE导航_提交表单
    WKE_NAVIGATION_TYPE_FORMSUBMITTE,
    //@别名 WKE导航_返回
    WKE_NAVIGATION_TYPE_BACKFORWARD,
    //@别名 WKE导航_刷新
    WKE_NAVIGATION_TYPE_RELOAD,
    //@别名 WKE导航_重新提交表单
    WKE_NAVIGATION_TYPE_FORMRESUBMITT,
    //@别名 WKE导航_其他
    WKE_NAVIGATION_TYPE_OTHER
} _wkeNavigationType;

//@别名 WKE加载结果
typedef enum wkeLoadingResult {
    //@别名 WKE加载结果_完成
    WKE_LOADING_SUCCEEDED,
    //@别名 WKE加载结果_失败
    WKE_LOADING_FAILED,
    //@别名 WKE加载结果_取消
    WKE_LOADING_CANCELED
} _wkeLoadingResult;

//@别名 WKE下载状态
typedef enum wkeDownloadOpt {
    //@别名 WKE下载状态_取消
    kWkeDownloadOptCancel,
    //@别名 WKE下载状态_缓存数据
    kWkeDownloadOptCacheData,
} _wkeDownloadOpt;

//@别名 WKE请求类型
typedef enum _wkeRequestType {
    //@别名 WKE请求类型_无效
    kWkeRequestTypeInvalidation,
    //@别名 WKE请求类型_GET
    kWkeRequestTypeGet,
    //@别名 WKE请求类型_POST
    kWkeRequestTypePost,
    //@别名 WKE请求类型_PUT
    kWkeRequestTypePut,
} wkeRequestType;

typedef enum wkeOnContextMenuItemClickType {
    kWkeContextMenuItemClickTypePrint = 0x01,
} _wkeOnContextMenuItemClickType;

typedef enum wkeOnContextMenuItemClickStep {
    kWkeContextMenuItemClickStepShow = 0x01,
    kWkeContextMenuItemClickStepClick = 0x02,
} _wkeOnContextMenuItemClickStep;

//@别名 WKEBody结构数据类型
typedef enum wkeHttBodyElementType {
    //@别名 WKEBody结构数据类型_字节数据
    wkeHttBodyElementTypeData,
    //@别名 WKEBody结构数据类型_文件
    wkeHttBodyElementTypeFile,
} _wkeHttBodyElementType;

//@别名 WKE窗口类型
typedef enum wkeWindowType {
    //@别名 WKE窗口类型_普通窗口
    WKE_WINDOW_TYPE_POPUP,
    //@别名 WKE窗口类型_透明窗口
    WKE_WINDOW_TYPE_TRANSPARENT,
    //@别名 WKE窗口类型_子窗口
    WKE_WINDOW_TYPE_CONTROL
} _wkeWindowType;

//@别名 WKEJS变量类型
typedef enum jsType {
    //@别名 WKEJS变量类型_数字型
    JSTYPE_NUMBER,
    //@别名 WKEJS变量类型_文本型
    JSTYPE_STRING,
    //@别名 WKEJS变量类型_逻辑型
    JSTYPE_BOOLEAN,
    //@别名 WKEJS变量类型_对象
    JSTYPE_OBJECT,
    //@别名 WKEJS变量类型_函数
    JSTYPE_FUNCTION,
    //@别名 WKEJS变量类型_未定义
    JSTYPE_UNDEFINED,
    //@别名 WKEJS变量类型_数组
    JSTYPE_ARRAY,
    //@别名 WKEJS变量类型_NULL
    JSTYPE_NULL,
} _jsType;

*/

//@分组}
//@分组{ 数据类型

/*@声明

//@别名 WKEWeb框架句柄
typedef void* wkeWebFrameHandle;
//@备注 详情参见 https://miniblink.net/views/doc/APIDocument/API/index.html
//@别名 WKEJS执行信息
struct JsExecStateInfo;
//@备注 详情参见 https://miniblink.net/views/doc/APIDocument/API/index.html
//@别名 WKEJS执行状态
typedef JsExecStateInfo* jsExecState;
//@别名 WKE字符串
typedef wke::CString* wkeString;
typedef char utf8;
typedef __int64 jsValue;
//@别名 WKEV8隔离环境
typedef void* v8Isolate;
//@别名 WKE网络任务
typedef void* wkeNetJob;
//@别名 WKEBlink网络请求
typedef blink::WebURLRequest* blinkWebURLRequestPtr;
//@别名 WKE网络请求
typedef struct wkeWebUrlRequest* wkeWebUrlRequestPtr;
//@别名 WKE网络响应
typedef struct wkeWebUrlResponse* wkeWebUrlResponsePtr;
//@别名 WKEV8上下文
typedef void* v8ContextPtr;
//@别名 WKE网络任务数据绑定
typedef struct wkeNetJobDataBind {
    //@别名 参数
    void* param;
    //@别名 接收回调
    wkeNetJobDataRecvCallback recvCallback;
    //@别名 完成回调
    wkeNetJobDataFinishCallback finishCallback;
} _wkeNetJobDataBind;

//@别名 WKE代理设置
typedef struct wkeProxy {
    //@备注 WKE_代理类型_
    //@别名 WKE代理类型
    wkeProxyType type;
    //@别名 主机
    char hostname[100];
    //@别名 端口
    unsigned short port;
    //@别名 用户名
    char username[50];
    //@别名 密码
    char password[50];
} _wkeProxy;

//@别名 WKE设置
typedef struct wkeSettings {
    //@别名 WKE代理
    wkeProxy proxy;
    unsigned int mask;
    const char* extension;
} _wkeSettings;

//@别名 WKE_WebView设置
typedef struct wkeViewSettings {
    int size;
    //@别名 背景颜色
    unsigned int bgColor;
} _wkeViewSettings;

//@别名 WKE_客户端处理
typedef struct wkeClientHandler {
    //@备注 void(*ON_TITLE_CHANGED) (const struct _wkeClientHandler* clientHandler, const wkeString title);
    ON_TITLE_CHANGED onTitleChanged;
    //@备注 void(*ON_URL_CHANGED) (const struct _wkeClientHandler* clientHandler, const wkeString url)
    ON_URL_CHANGED onURLChanged;
} _wkeClientHandler;

//@别名 WKE_内存块
typedef struct wkeMemBuf {
    int unuse;
    void* data;
    size_t length;
} _wkeMemBuf;


//@参数 作用路径 如果|path|为非空，则只有位于或低于该路径的URL才会获取cookie值。
//@参数 安全保护 如果|secure|为true，则仅针对HTTPS请求发送cookie。
//@参数 仅HTTP 如果|httponly|为true，则仅针对HTTP请求发送cookie。
//@参数 过期 只有当|expires|为true时，cookie过期日期才有效。
//@别名 WKE_Cookie访问器(参数,名称,值,作用域,作用路径,安全保护,仅HTTP,过期)
typedef bool(*wkeCookieVisitor)(
    void* params,
    const char* name,
    const char* value,
    const char* domain,
    const char* path, // If |path| is non-empty only URLs at or below the path will get the cookie value.
    int secure, // If |secure| is true the cookie will only be sent for HTTPS requests.
    int httpOnly, // If |httponly| is true the cookie will only be sent for HTTP requests.
    int* expires // The cookie expiration date is only valid if |has_expires| is true.
    );

//@备注 WKE区域
typedef struct wkeRect {
    int x;
    int y;
    int w;
    int h;
} _wkeRect;

//@别名 WKE窗口设置
typedef struct wkeWindowFeatures {
    int x;
    int y;
    //@别名 宽度
    int width;
    //@别名 高度
    int height;
    //@别名 菜单栏可视
    bool menuBarVisible;
    //@别名 状态栏可视
    bool statusBarVisible;
    //@别名 工具栏可视
    bool toolBarVisible;
    //@别名 位置栏可视
    bool locationBarVisible;
    //@别名 滚动条可视
    bool scrollbarsVisible;
    //@别名 可调整尺寸
    bool resizable;
    //@别名 全屏
    bool fullscreen;
} _wkeWindowFeatures;

//@别名 WKE拖拽区域
struct wkeDraggableRegion {
    RECT bounds;
    bool draggable;
};

//@别名 WKE链表
typedef struct wkeSlist {
    char* data;
    struct _wkeSlist* next;
} _wkeSlist;

//@别名 WKE网络请求回调体
typedef struct wkeUrlRequestCallbacks {
    //@备注 参见 WKE_回调类型_网络请求_链接重定向
    //@别名 链接重定向回调
    wkeOnUrlRequestWillRedirectCallback willRedirectCallback;
    //@备注 参见 WKE_回调类型_网络请求_收到回应
    //@别名 收到回应回调
    wkeOnUrlRequestDidReceiveResponseCallback didReceiveResponseCallback;
    //@备注 参见 WKE_回调类型_网络请求_收到数据
    //@别名 收到数据回调
    wkeOnUrlRequestDidReceiveDataCallback didReceiveDataCallback;
    //@备注 参见 WKE_回调类型_网络请求_请求失败
    //@别名 请求失败回调
    wkeOnUrlRequestDidFailCallback didFailCallback;
    //@备注 参见 WKE_回调类型_网络请求_完成加载
    //@别名 完成加载回调
    wkeOnUrlRequestDidFinishLoadingCallback didFinishLoadingCallback;
} _wkeUrlRequestCallbacks;

//@别名 WKEPOST数据结构
typedef struct wkePostBodyElement {
    //@别名 大小
    int size;
    //@别名 结构数据类型
    wkeHttBodyElementType type;
    //@别名 数据内存块
    wkeMemBuf* data;
    //@别名 文件路径
    wkeString filePath;
    //@别名 文件起始索引
    __int64 fileStart;
    //@备注 -1 代表文件结束
    //@别名 文件结束索引
    __int64 fileLength;
} _wkePostBodyElement;
//@别名 WKEPOST数据包结构
typedef struct wkePostBodyElements {
    //@别名 大小
    int size;
    //@别名 Post数据数组指针
    wkePostBodyElement** element;
    //@别名 主体结构数组成员数
    size_t elementSize;
    bool isDirty;
} _wkePostBodyElements ;

//@别名 WKE窗口信息
typedef struct wkeWindowCreateInfo {
    //@别名 结构体大小
    int size;
    //@别名 父窗口
    HWND parent;
    //@别名 窗口风格
    DWORD style;
    //@别名 窗口附加风格
    DWORD styleEx;
    //@别名 横坐标
    int x;
    //@别名 纵坐标
    int y;
    //@别名 宽度
    int width;
    //@别名 高度
    int height;
    //@别名 颜色
    COLORREF color;
} _wkeWindowCreateInfo;

//@别名 WKE输出设置
typedef struct wkePrintSettings {
    //@别名 结构体尺寸
    int structSize;
    int dpi;
    //@别名 宽度
    int width; // in px
    //@别名 高度
    int height;
    //@别名 顶部边距
    int marginTop;
    //@别名 底部边距
    int marginBottom;
    //@别名 左边边距
    int marginLeft;
    //@别名 右边边距 
    int marginRight;
    //@别名 打印页眉和页脚
    BOOL isPrintPageHeadAndFooter;
    //@别名 打印背景
    BOOL isPrintBackgroud;
    //@别名 横向
    BOOL isLandscape;
} _wkePrintSettings;

//@别名 WKEPDF数据
typedef struct wkePdfDatas {
    int count;
    size_t* sizes;
    const void** datas;
} _wkePdfDatas;

//@别名 WKE图片设置
typedef struct wkeScreenshotSettings {
    int structSize;
    int width;
    int height;
} _wkeScreenshotSettings;

//@别名 WKEJS数据
typedef struct jsData {
    //@别名 名称
    char typeName[100];
    //@别名 获取属性回调
    jsGetPropertyCallback propertyGet;
    //@别名 变更属性回调
    jsSetPropertyCallback propertySet;
    //@别名 完成回调
    jsFinalizeCallback finalize;
    //@别名 调用函数回调
    jsCallAsFunctionCallback callAsFunction;
} tagjsData;

//@别名 WKEJSKeys
typedef struct jsKeys {
    //@别名 数组大小
    unsigned int length;
    //@别名 名称数组
    const char** keys;
    //@隐藏{
    ~_jsKeys();
    //@隐藏}
} _jsKeys;

//@别名 WKEJS异常信息
typedef struct jsExceptionInfo {
    //@别名 信息
    const utf8* message;
    //@别名 来源代码行
    const utf8* sourceLine;
    //@别名 来源脚本名
    const utf8* scriptResourceName;
    //@别名 行号
    int lineNumber;
    //@别名 开始位置
    int startPosition;
    //@别名 结束位置
    int endPosition;
    //@别名 开始列
    int startColumn;
    //@别名 结束列
    int endColumn;
    //@别名 调用堆栈字符串
    const utf8* callstackString;
} _jsExceptionInfo;

*/

//@分组}
//@分组{ 回调原型声明
/*@声明

//@别名 WKE_回调类型_开发者调试(webView,参数)
typedef void(*wkeOnShowDevtoolsCallback)(wkeWebView webView, void* param);
//@别名 WKE_回调类型_文本(webView,参数,传入文本)
typedef void(*wkeTitleChangedCallback)(wkeWebView webView, void* param, const wkeString str);
//@别名 WKE_回调类型_文本2(webView,参数,框架句柄,传入文本)
typedef void(*wkeURLChangedCallback2)(wkeWebView webView, void* param, wkeWebFrameHandle frameId, const wkeString url);
//@别名 WKE_回调类型_DC绘制事件(webView,参数,HDC,横坐标,纵坐标,长度,高度)
typedef void(*wkePaintUpdatedCallback)(wkeWebView webView, void* param, const HDC hdc, int x, int y, int cx, int cy);
//@别名 WKE_回调类型_像素绘制事件(webView,参数,像素缓冲区,横坐标,纵坐标,长度,高度)
typedef void(*wkePaintBitUpdatedCallback)(wkWebView webView, void* param, const void* buffer, const wkeRect* r, int width, int height);
//@别名 WKE_回调类型_信息框(webView,参数,文本)
typedef void(*wkeAlertBoxCallback)(wkeWebView webView, void* param, const wkeString msg);
//@别名 WKE_回调类型_确认框(webView,参数,文本)
typedef bool(*wkeConfirmBoxCallback)(wkeWebView webView, void* param, const wkeString msg);
//@别名 WKE_回调类型_输入框(webView,参数,文本信息,默认返回文本,返回文本)
typedef bool(*wkePromptBoxCallback)(wkeWebView webView, void* param, const wkeString msg, const wkeString defaultResult, wkeString result);
//@参数 日志等级 参见 WKE控制台输出等级
//@参数 来源行数 来自于网页源码的行数
//@别名 WKE_回调类型_控制台输出(webView,参数,日志等级,日志信息,来源名称,来源行数,跟踪堆栈)
typedef void(*wkeConsoleCallback)(wkeWebView webView,
    void* param,
    wkeConsoleLevel level,
    const wkeString message,
    const wkeString sourceName,
    unsigned sourceLine,
    const wkeString stackTrace
);

//@参数 导航类型 参见枚举值 WKE导航类型
//@别名 WKE_回调类型_页面导航(webView,参数,导航类型,传入链接)
typedef bool(*wkeNavigationCallback)(wkeWebView webView, void* param, wkeNavigationType navigationType, wkeString url);

//@参数 导航类型 参见枚举值 WKE导航类型
//@别名 WKE_回调类型_创建WebView(webView,参数,导航类型,传入URL,WKE窗口设置)
typedef wkeWebView(*wkeCreateViewCallback)(wkeWebView webView,
    void* param,
    wkeNavigationType navigationType,
    const wkeString url,
    const wkeWindowFeatures* windowFeatures);

//@别名 WKE_回调类型_文档加载完成(webView,参数)
typedef void(*wkeDocumentReadyCallback)(wkeWebView webView, void* param);

//@别名 WKE_回调类型_文档加载完成2(webView,参数,框架句柄)
typedef void(*wkeDocumentReady2Callback)(wkeWebView webView, void* param, wkeWebFrameHandle frameId);

//@别名 WKE_回调类型_页面加载完成(webView,参数,传入URL,WKE加载结果,失败原因)
typedef void(*wkeLoadingFinishCallback)(wkeWebView webView, void* param, const wkeString url, wkeLoadingResult result, const wkeString failedReason);

//@别名 WKE_回调类型_下载文件(webView,参数,下载链接)
typedef bool(*wkeDownloadCallback)(wkeWebView webView, void* param, const char* url);

//@别名 WKE_回调类型_网络任务数据绑定_接收回调(指针,任务,数据,数据长度)
typedef void(*wkeNetJobDataRecvCallback)(void* ptr, wkeNetJob job, const char* data, int length);
//@别名 WKE_回调类型_网络任务数据绑定_完成回调(指针,任务,任务状态,WKE下载状态)
typedef void(*wkeNetJobDataFinishCallback)(void* ptr, wkeNetJob job, wkeLoadingResult result);
//@别名 WKE_回调类型_下载文件2(webView,参数,预期尺寸,下载链接,文件MINE,文件Disposition,任务,数据绑定回调)
typedef wkeDownloadOpt(*wkeDownload2Callback)(
   wkeWebView webView,
   void* param,
   size_t expectedContentLength,
   const char* url,
   const char* mime,
   const char* disposition,
   wkeNetJob job,
   wkeNetJobDataBind* dataBind
);

//@别名 WKE_回调类型_UI函数回调(webView,参数)
typedef void(*wkeOnCallUiThread)(wkeWebView webView, void* paramOnInThread);

//@别名 WKE_回调类型_UI线程回调(webView,UI函数回调,参数)
typedef void(*wkeCallUiThread)(wkeWebView webView, wkeOnCallUiThread func, void* param);

//@别名 WKE_回调类型_网络请求开始(webView,参数,链接,任务)
typedef bool(*wkeLoadUrlBeginCallback)(wkeWebView webView, void* param, const utf8* url, wkeNetJob job);

//@别名 WKE_回调类型_网络请求结束(webView,参数,链接,任务,数据,数据长度)
typedef void(*wkeLoadUrlEndCallback)(wkeWebView webView, void* param, const utf8* url, wkeNetJob job, void* buf, int len);

//@别名 WKE_回调类型_网页加载失败(webView,参数,链接,任务)
typedef void(* wkeLoadUrlFailCallback)(wkeWebView webView, void* param, const utf8* url, wkeNetJob job);

//@别名 WKE_回调类型_收到返回信息(webView,参数,链接,任务)
typedef bool(*wkeNetResponseCallback)(wkeWebView webView, void* param, const utf8* url, wkeNetJob job);

//@别名 WKE_回调类型_准备执行JS(webView,参数,框架句柄,上下文,extensionGroup,worldId)
typedef void(*wkeDidCreateScriptContextCallback)(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId);

//@别名 WKE_回调类型_执行JS完成(webView,参数,框架句柄,上下文,worldId)
typedef void(*wkeWillReleaseScriptContextCallback)(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int worldId);

//@返回 返回false拒绝关闭窗口
//@别名 WKE_回调类型_窗口将被关闭(webView,参数)
typedef bool(*wkeWindowClosingCallback)(wkeWebView webWindow, void* param);

//@别名 WKE_回调类型_窗口将被销毁(webView,参数)
typedef void(*wkeWindowDestroyCallback)(wkeWebView webWindow, void* param);

//@别名 WKE_回调类型_拖拽区域被改变(webView,参数,拖拽区域设置,区域尺寸)
typedef void(*wkeDraggableRegionsChangedCallback)(wkeWebView webView, void* param, const wkeDraggableRegion* rects, int rectCount);

//@别名 WKE_回调类型_截图事件(webView,参数,截图数据,尺寸)
typedef void(*wkeOnScreenshot)(wkeWebView webView, void* param, const char* data, size_t size);

//@别名 WKE_回调类型_菜单项被点击(webView,参数,点击类型,W,框架句柄,信息)
typedef bool(* wkeOnContextMenuItemClickCallback)(
    wkeWebView webView,
    void* param,
    wkeOnContextMenuItemClickType type,
    wkeOnContextMenuItemClickStep step,
    wkeWebFrameHandle frameId,
    void* info
);

//@别名 WKE_回调类型_获取图标(webView,参数,链接,数据)
typedef void(*wkeOnNetGetFaviconCallback)(wkeWebView webView, void* param, const utf8* url, wkeMemBuf* buf);

//@别名 WKE_回调类型_网络请求_链接重定向(webView,参数,旧请求,新请求,重定向返回请求)
typedef void(* wkeOnUrlRequestWillRedirectCallback)(wkeWebView webView, void* param, wkeWebUrlRequestPtr oldRequest, wkeWebUrlRequestPtr request, wkeWebUrlResponsePtr redirectResponse);
//@别名 WKE_回调类型_网络请求_收到回应(webView,参数,网络请求,返回响应)
typedef void(* wkeOnUrlRequestDidReceiveResponseCallback)(wkeWebView webView, void* param, wkeWebUrlRequestPtr request, wkeWebUrlResponsePtr response);
//@别名 WKE_回调类型_网络请求_收到数据(webView,参数,网络请求,接收数据,数据长度)
typedef void(* wkeOnUrlRequestDidReceiveDataCallback)(wkeWebView webView, void* param, wkeWebUrlRequestPtr request, const char* data, int dataLength);
//@别名 WKE_回调类型_网络请求_请求失败(webView,参数,网络请求,错误信息)
typedef void(* wkeOnUrlRequestDidFailCallback)(wkeWebView webView, void* param, wkeWebUrlRequestPtr request, const utf8* error);
//@别名 WKE_回调类型_网络请求_完成加载(webView,参数,网络请求,完成时间)
typedef void(* wkeOnUrlRequestDidFinishLoadingCallback)(wkeWebView webView, void* param, wkeWebUrlRequestPtr request, double finishTime);

//@别名 WKE_回调类型_创建node(webView,参数,应用路径,参数,窗口属性)
typedef void(*wkeNodeOnCreateProcessCallback)(wkeWebView webView, void* param, const WCHAR* applicationPath, const WCHAR* arguments, STARTUPINFOW* startup);

//@别名 WKE_回调类型_查找插件(webView,参数,MIME,初始化函数,入口点函数,结束函数)
typedef void(*wkeOnPluginFindCallback)(wkeWebView webView, void* param, const utf8* mime, void* initializeFunc, void* getEntryPointsFunc, void* shutdownFunc);

//@备注 注意：JS函数调用约定为 (__fastcall) ！！！
//@别名 WKE_回调类型_JS函数源(es)
typedef jsValue(* jsNativeFunction) (jsExecState es);

//@别名 WKE_回调类型_JS函数源C(es,附加参数)
typedef jsValue(* wkeJsNativeFunction) (jsExecState es, void* param);

//@别名 WKE_回调类型_JS数据_获取属性回调(es,对象,属性名称)
typedef jsValue(*jsGetPropertyCallback)(jsExecState es, jsValue object, const char* propertyName);
//@别名 WKE_回调类型_JS数据_变更属性回调(es,对象,属性名称,值)
typedef bool(*jsSetPropertyCallback)(jsExecState es, jsValue object, const char* propertyName, jsValue value);
//@别名 WKE_回调类型_JS数据_完成回调(es,对象,参数数组,参数数量)
typedef jsValue(*jsCallAsFunctionCallback)(jsExecState es, jsValue object, jsValue* args, int argCount);
//@别名 WKE_回调类型_JS数据_调用函数回调(data)
typedef void(*jsFinalizeCallback)(struct tagjsData* data);

*/

//@分组}
//@分组{ WKE公开函数

/*@声明
//@别名 WKE_初始化()
void wkeInitialize();
//@别名 WKE_初始化Ex(WKE设置)
void wkeInitializeEx(const wkeSettings* settings);

//@备注 获取MB的内部版本号。
//@别名 WKE_取内部版本号()
UINT wkeGetVersion();
//@别名 WKE_取发行版本号()
const char* wkeGetVersionString();

//@备注 设置webView内置名称，基本没啥用
//@别名 WKE_置webView内置名称(webView,名称)
void wkeSetWebViewName(wkeWebView webView, const char* name);
//@备注 获取通过wkeSetWebViewName设置的webView的内置名称
//@别名 WKE_取webView内置名称(webView)
const char* wkeWebViewName(wkeWebView webView);
//@别名 WKE_取网页标题(webView)
const utf8* wkeGetTitle(wkeWebView webView);
//@别名 WKE_取网页标题W(webView)
const wchar_t* wkeGetTitleW(wkeWebView webView);

//@别名 WKE_文本_取文本数据(WKE文本)
const utf8* wkeGetString(const wkeString string);
//@别名 WKE_文本_取文本数据W(WKE文本)
const wchar_t* wkeGetStringW(const wkeString string);

//@别名 WKE_文本_置文本数据(WKE文本,文本数据,文本长度)
void wkeSetString(wkeString string, const utf8* str, size_t len);
//@别名 WKE_文本_置文本数据W(WKE文本,文本数据,文本长度)
void wkeSetStringW(wkeString string, const utf8* str, size_t len);

//@别名 WKE_文本_置文本数据_无结束符(WKE文本,文本数据,文本长度)
void wkeSetStringWithoutNullTermination(wkeString string, const utf8* str, size_t len);


//@别名 WKE_文本_创建文本(文本数据,文本长度)
wkeString wkeCreateString(const utf8* str, size_t len);
//@别名 WKE_文本_创建文本_无结束符(文本数据,文本长度)
wkeString wkeCreateStringWithoutNullTermination(const utf8* str, size_t len);
//@别名 WKE_文本_创建文本W(文本数据,文本长度)
wkeString wkeCreateStringW(const wchar_t* str, size_t len);

//@别名 WKE_文本_取文本长度(WKE文本)
size_t wkeGetStringLen(wkeString str);
//@备注 干掉wkeString字符串，释放其内存。
//@别名 WKE_文本_释放数据(WKE文本)
void wkeDeleteString(wkeString str);


//@备注 延迟让MB垃圾回收
//@别名 WKE_延迟GC(webView,延迟秒数)
void wkeGC(wkeWebView webView, long intervalSec);
//@备注 设置自动回收系统资源时间间隔,intervalSec：单位秒，默认300秒。
//@别名 WKE_置GC间隔(webView，间隔秒数)
void wkeSetResourceGc(wkeWebView webView, long intervalSec);

//@别名 WKE_全选(webView)
void wkeEditorSelectAll(wkeWebView webView);
//@别名 WKE_反选(webView)
void wkeEditorUnSelect(wkeWebView webView);
//@别名 WKE_复制(webView)
void wkeEditorCopy(wkeWebView webView);
//@别名 WKE_剪切(webView)
void wkeEditorCut(wkeWebView webView);
//@别名 WKE_粘贴(webView)
void wkeEditorPaste(wkeWebView webView);
//@别名 WKE_删除(webView)
void wkeEditorDelete(wkeWebView webView);
//@别名 WKE_撤销(webView)
void wkeEditorUndo(wkeWebView webView);
//@别名 WKE_重做(webView)
void wkeEditorRedo(wkeWebView webView);
//@别名 WKE_刷新()
void wkeUpdate();

//@别名 WKE_置配置项(配置信息)
void wkeConfigure(const wkeSettings* settings);

//@备注 强制停止MB，一般用于开发调试
//@别名 WKE_强行停止ForDebug()
void wkeShutdownForDebug();

//@别名 WKE_是否初始化()
BOOL wkeIsInitialize();

//@别名 WKE_置WebView设置(webView,webView设置)
void wkeSetViewSettings(wkeWebView webView, const wkeViewSettings* settings);

//@备注 试验性设置,暂时跳过封装
void wkeSetDebugConfig(wkeWebView webView, const char* debugString, const char* param);
//@备注 获取试验性设置,暂时跳过封装
void * wkeGetDebugConfig(wkeWebView webView, const char* debugString);

//@备注 在内存里创建一个webView对象，但不创建真窗口，一般用在离屏渲染里，如游戏等。
//@别名 WKE_创建WebView()
wkeWebView wkeCreateWebView();

//@备注 干掉webView，释放其内存。
//@别名 WKE_释放WebView(webView)
void wkeDestroyWebView(wkeWebView webView);

//@备注 设置是否开启内存缓存，默认开。开启后图片等都会放到内存缓存里，用于某些优化操作。关闭则会降低内存使用，但容易引起一些问题。
//@别名 WKE_置开启内存缓存(webView,是否开启)
void wkeSetMemoryCacheEnable(wkeWebView webView, bool b);

//@备注 设置是否允许鼠标，默认开。
//@别名 WKE_置是否允许鼠标(webView,是否允许鼠标)
void wkeSetMouseEnabled(wkeWebView webView, bool b);

//@备注 设置是否允许触屏，默认关。开启后，鼠标消息将自动转换成触屏消息。
//@别名 WKE_置是否允许触屏(webView,是否允许触屏)
void wkeSetTouchEnabled(wkeWebView webView, bool b);

//@备注 设置操作系统是否发送触屏消息，默认关。
//@别名 WKE_置操作系统是否发送触屏消息(webView,是否发送)
void wkeSetSystemTouchEnabled(wkeWebView webView, bool b);

//@备注 设置是否允许菜单，默认开。
//@别名 WKE_置是否允许菜单(webView,是否允许)
void wkeSetContextMenuEnabled(wkeWebView webView, bool b);

//@备注 当有新页面需要打开时（如标签），是否在新窗口打开，默认是当前窗口，如开启，则会触发wkeOnCreateView回调接口。
//@别名 WKE_置是否新窗口调整(webView,跳转是否新窗口)
void wkeSetNavigationToNewWindowEnable(wkeWebView webView, bool b);

//@备注 设置是否开启csp跨域检查，默认开。如需进行跨域操作，如跨域ajax，跨域设置iframe等，则需要先关闭此开关。
//@别名 WKE_置csp跨域检查(webView,是否检查跨域)
void wkeSetCspCheckEnable(wkeWebView webView, bool b);

//@备注 设置是否开启npapi插件，如flash等，默认开。
//@别名 WKE_置npapi插件状态(webView,开启状态)
void wkeSetNpapiPluginsEnabled(wkeWebView webView, bool b);

//@备注 开启无头模式，默认关。开启后页面不会被渲染上屏，直接内存运行，大幅提升性能。注意：目前很多网站对这种模式已经进行了识别和反制。
//@别名 WKE_置无头模式状态(webView,是否开启无头模式)
void wkeSetHeadlessEnabled(wkeWebView webView, bool b);

//@备注 设置是否支持拖拽文件到页面，默认开启。
//@别名 WKE_置是否支持拖拽文件(webView,是否开启拖拽)
void wkeSetDragEnable(wkeWebView webView, bool b);

//@备注 设置是否支持拖拽页面元素，默认开启。
//@别名 WKE_置是否支持拖拽页面元素(webView,是否开启拖拽)
void wkeSetDragDropEnable(wkeWebView webView, bool b);

//@备注 设置指定的菜单项是否显示。
//@别名 WKE_置菜单项可视(webView,WKE菜单项ID,可视状态)
void wkeSetContextMenuItemShow(wkeWebView webView, wkeMenuItemId item, bool isShow);

//@备注 设置其他语言，默认跟随系统设定。
//@别名 WKE_置语言(webView,语言)
void wkeSetLanguage(wkeWebView webView, const char* language);

//@备注 设置webView代理，全局生效。注意：标准版的代理是全局的。
//@别名 WKE_置代理(代理信息)
void wkeSetProxy(const wkeProxy* proxy);

//@备注 获取webWindow句柄
//@别名 WKE_取HWND(wkeWebView)
HWND wkeGetWindowHandle(wkeWebView webWindow);

//@备注 设置webView句柄
//@别名 WKE_置webView句柄(webView,ClientHandler)
void wkeSetClientHandler(wkeWebView webView, const wkeClientHandler* handler);

//@备注 获取webView句柄
//@别名 WKE_取webView句柄(webView)
const wkeClientHandler* wkeGetClientHandler(wkeWebView webView);

//@备注 设置wkeWebView对应的窗口句柄，用于无头模式，如果是wkeCreateWebWindow创建的webview，则已经自带窗口句柄了。
//@别名 WKE_webView绑定HWND(webView,窗口句柄)
void wkeSetHandle(wkeWebView webView, HWND wnd);

//@备注 设置无头模式下的绘制位置，在某些情况下绘制的地方不在真窗口的(0，0)处，就需要调用此接口。
//@别名 WKE_置绘制位置_无头模式(webView,X,Y)
void wkeSetHandleOffset(wkeWebView webView, int x, int y);

//@备注 判断窗口是否是透明模式。
//@别名 WKE_是否为透明模式(webView)
BOOL wkeIsTransparent(wkeWebView webView);

//@备注 设置是否开启透明模式，默认关。
//@别名 WKE_置透明模式(webView,是否透明)
void wkeSetTransparent(wkeWebView webView, bool transparent);

//@备注 获取网页H5源码。
//@别名 WKE_取网页源码(webView)
const utf8* wkeGetSource(wkeWebView webView);

//@备注 设置webview的UA，全局生效。注意：标准版接口的UA是全局的。
//@别名 WKE_置UserAgent(webView,userAgent)
void wkeSetUserAgent(wkeWebView webView, const utf8* userAgent);

//@备注 设置webview的UA，全局生效。注意：标准版接口的UA是全局的。
//@别名 WKE_置UserAgentW(webView,userAgent)
void wkeSetUserAgentW(wkeWebView webView, const wchar_t* userAgent);

//@备注 获取webview的UA。
//@别名 WKE_取UserAgent(webView,userAgent)
const char* wkeGetUserAgent(wkeWebView webView);

//@备注 加载网址。注意：建议写完整url，如：http://www.miniblink.net。
//@别名 WKE_加载URL(webView,URL)
void wkeLoadURL(wkeWebView webView, const utf8* url);

//@备注 加载网址。注意：建议写完整url，如：http://www.miniblink.net。
//@别名 WKE_加载URLW(webView,URL)
void wkeLoadURLW(wkeWebView webView, const wchar_t* url);

//@备注 POST网络请求。
//@别名 WKE_提交Post(wkeView,URL,提交数据,数据长度)
void wkePostURL(wkeWebView wkeView, const utf8* url, const char* postData, int postLen);

//@备注 POST网络请求。
//@别名 WKE_提交PostW(wkeView,URL,提交数据,数据长度)
void wkePostURLW(wkeWebView wkeView, const wchar_t* url, const char* postData, int postLen);

//@备注 加载一段H5代码。注意：如果代码里有相对路径的文件操作，则是当前目录。
//@别名 WKE_加载HTML(webView,HTML数据)
void wkeLoadHTML(wkeWebView webView, const utf8* html);

//@备注 加载一段H5代码。注意：如果代码里有相对路径的文件操作，则是当前目录。
//@别名 WKE_加载HTMLW(webView,HTML数据)
void wkeLoadHTMLW(wkeWebView webView, const wchar_t* html);

//@备注 加载H5代码文件。
//@别名 WKE_加载文件(webView,文件路径)
void wkeLoadFile(wkeWebView webView, const utf8* filename);

//@备注 加载H5代码文件。
//@别名 WKE_加载文件W(webView,文件路径)
void wkeLoadFileW(wkeWebView webView, const wchar_t* filename);

//@备注 获取主frame的URL。
//@别名 WKE_取URL(webView)
const utf8* wkeGetURL(wkeWebView webView);

//@备注 获取指定frame的url
//@别名 WKE_取框架URL(webView,框架ID)
const utf8* wkeGetFrameUrl(wkeWebView webView, wkeWebFrameHandle frameId);

//@备注 判断webView是否正在加载
//@别名 WKE_是否正在加载(webView)
BOOL wkeIsLoading(wkeWebView webView);

//@备注 判断webView是否加载失败。
//@别名 WKE_是否加载失败(webView)
BOOL wkeIsLoadingFailed(wkeWebView webView);

//@备注 判断webView是否加载完成。注意：由于现代网页大多采用动态加载，多frame框架等原因，本接口返回的加载完成并不等于“网页已全部加载完成”，只表示MB已接收了服务器本次传回的全部数据。
//@别名 WKE_是否加载完成(webView)
BOOL wkeIsLoadingCompleted(wkeWebView webView);

//@备注 DOM文档结构是否加载完成。注意：由于现代网页大多采用动态加载，多frame框架等原因，本接口返回的加载完成并不等于“网页已全部加载完成”，只表示MB已接收了服务器本次传回的全部数据。
//@别名 WKE_文档是否加载完成(webView)
BOOL wkeIsDocumentReady(wkeWebView webView);

//@备注 强制停止加载当前页面。
//@别名 WKE_强制停止加载(webView)
void wkeStopLoading(wkeWebView webView);

//@备注 重新加载当前页面，从服务器重新拉取内容而不仅仅是重新渲染，相当于按ctrl+F5强刷。
//@别名 WKE_强制刷新(webView)
void wkeReload(wkeWebView webView);

//@备注 移动到指定偏移位置，一般没啥用。
//@别名 WKE_移动视图到偏移(webView,偏移值)
void wkeGoToOffset(wkeWebView webView, int offset);

//@备注 移动到指定索引位置，一般没啥用。
//@别名 WKE_移动视图到索引(webView,索引值)
void wkeGoToIndex(wkeWebView webView, int index);

//@备注 获取完整的url。
//@别名 WKE_取完整URL(webView,框架ID,部分URL)
const utf8* wkeGetDocumentCompleteURL(wkeWebView webView, wkeWebFrameHandle frameId, const utf8* partialURL);

//@备注 new一块内存空间。
//@别名 WKE_申请内存(webView,缓存块,长度)
wkeMemBuf* wkeCreateMemBuf(wkeWebView webView, void* buf, size_t length);

//@备注 释放内存。
//@别名 WKE_是否内存(内存块指针)
void wkeFreeMemBuf(wkeMemBuf* buf);

//@备注 重新设置页面的像素宽高，如果webView是带窗口模式的，会设置实际窗口的宽高。
//@别名 WKE_置页面尺寸(webView,宽度,高度)
void wkeResize(wkeWebView webView, int w, int h);

//@备注 获取webView宽度像素，同wkeWidth。
//@别名 WKE_取页面宽度(webView)
int wkeGetWidth(wkeWebView webView);

//@备注 获取webView高度像素，同wkeHeight。
//@别名 WKE_取页面高度(webView)
int wkeGetHeight(wkeWebView webView);

//@备注 获取webView排版出来的内容区域宽度像素。
//@别名 WKE_取排版宽度(webView)
int wkeGetContentWidth(wkeWebView webView);

//@备注 获取webView排版出来的内容区域高度像素。
//@别名 WKE_取排版高度(webView)
int wkeGetContentHeight(wkeWebView webView);

//@备注 获取页面像素，一般给3D游戏使用。注意：频繁使用此接口并拷贝像素会有性能问题，建议先用wkeGetViewDC再去拷贝DC。
//@参数 webView
//@参数 buffer 传递给webView的buffer，大小是 bufWid * bufHei
//@参数 buf宽度 bits的宽
//@参数 buf高度 bits的高
//@参数 绘制区x 绘制到bits的哪个坐标
//@参数 绘制区y 绘制到bits的哪个坐标
//@参数 截取区宽度 webView需要取的画面的宽度
//@参数 截取区高度 webView需要取的画面的高度
//@参数 截取区x webView需要取的画面的起始x坐标
//@参数 截取区y webView需要取的画面的起始y坐标
//@参数 是否保留透明度 是否拷贝画面的透明度值
//@别名 WKE_取页面像素2(webView,buffer,buf宽度,buf高度,绘制区x,绘制区y,截取区宽度,截取区高度,截取区x,截取区y,是否保留透明度)
void wkePaint2(wkeWebView webView, void* bits, int bufWid, int bufHei, int xDst, int yDst, int w, int h, int xSrc, int ySrc, bool bCopyAlpha);

//@备注 获取页面像素的简化版
//@参数 webView
//@参数 buffer 传递给webView的buffer，大小是webview宽度 * 高度
//@参数 pitch 写0
//@别名 WKE_取页面像素(webView,buffer,pitch)
void wkePaint(wkeWebView webView, void* bits, int pitch);

//@备注 获取webview的DC
//@别名 WKE_取DC(webView)
HDC wkeGetViewDC(wkeWebView webView);

//@备注 解锁webview的DC
//@别名 WKE_DC解锁(webView)
void wkeUnlockViewDC(wkeWebView webView);

//@备注 判断页面是否可以后退
//@别名 WKE_页面是否能返回(webView)
BOOL wkeCanGoBack(wkeWebView webView);

//@备注 强制让页面后退
//@别名 WKE_强制页面返回(webView)
BOOL wkeGoBack(wkeWebView webView);

//@备注 判断页面是否可以前进
//@别名 WKE_页面是否能前进(webView)
BOOL wkeCanGoForward(wkeWebView webView);

//@备注 强制让页面前进
//@别名 WKE_强制页面前进(webView)
BOOL wkeGoForward(wkeWebView webView);

//@备注 是否启用cookie，默认开。
//@别名 WKE_是否启用Cookie(webView)
BOOL wkeCookieEnabled(wkeWebView webView);

//@备注 获取页面的cookie字符串
//@别名 WKE_取Cookie(webView)
const utf8* wkeGetCookie(wkeWebView webView);

//@备注 获取页面的cookie字符串
//@别名 WKE_取CookieW(webView)
const wchar_t* wkeGetCookieW(wkeWebView webView);

//@备注 设置页面的cookie，全局生效。注意：1、cookie必须符合curl的标准写法。如：PERSONALIZE=123;expires=Monday 13-Jun-2022 03:04:55 GMT; domain=.fidelity.com; path=/; secure 2、标准版的Cookie是全局的，而VIP版可以针对每个webView单独设置。
//@别名 WKE_置Cookie(webView,URL,Cookie文本)
void wkeSetCookie(wkeWebView webView, const utf8* url, const utf8* cookie);

//@备注 通过访问器visitor访问所有cookie
//@参数 webView
//@参数 附加参数 自定义参数，没有传NULL
//@参数 访问器回调 参见 WKE_Cookie访问器 ,传入函数指针
//@别名 WKE_取Cookie_访问器(webView,附加参数,访问器回调)
void wkeVisitAllCookie(wkeWebView webView, void* params, wkeCookieVisitor visitor);

//@备注 通过设置webView内置的curl来操作cookie，这个接口只是调用curl设置命令，并不会去修改js里的内容
//@参数 命令类型 参见枚举类型 WKECookie命令
//@别名 WKE_执行Cookie命令(webView,命令类型)
void wkePerformCookieCommand(wkeWebView webView, wkeCookieCommand command);

//@备注 开启或关闭cookie。注意：这个接口只是影响当前渲染的页面，并不会设置curl。所以还是会生成curl的cookie文件。
//@别名 WKE_置开启Cookie(webView,是否开启)
void wkeSetCookieEnabled(wkeWebView webView, bool enable);

//@备注 判断cookie是否开启
//@别名 WKE_Cookie是否开启(webView)
BOOL wkeIsCookieEnabled(wkeWebView webView);

//@备注 设置cookie文件的目录，默认是程序运行的当前目录，文件名为：cookie.dat。注意：path是文件目录路径，不包括文件名，不能自动新建不存在的目录
//@别名 WKE_置Cookie目录(webView,路径)
void wkeSetCookieJarPath(wkeWebView webView, const WCHAR* path);

//@备注 设置cookie文件的全路径，默认是程序运行的当前目录，默认文件名为cookie.dat。注意：是全路径，包括cookie文件名，不能自动新建不存在的目录。
//@别名 WKE_置Cookie位置(webView,Cookie文件完整路径)
void wkeSetCookieJarFullPath(wkeWebView webView, const WCHAR* path);

//@备注 清除cookie。注意：由于缓存等因素，直接删cookie.dat可能更有效。另外有的网站可能有服务端缓存，所以会存在清理无效的情况
//@别名 WKE_清除Cookie(webView)
void wkeClearCookie(wkeWebView webView);

//@备注 设置local storage的全路径。如c:\mb\LocalStorage\，必须且只能是目录，默认是当前目录。
//@别名 WKE_置本地存储路径(webView,目录地址)
void wkeSetLocalStorageFullPath(wkeWebView webView, const WCHAR* path);

//@备注 设置插件目录
//@别名 WKE_置插件目录(webView,目录地址)
void wkeAddPluginDirectory(wkeWebView webView, const WCHAR* path);

//@备注 获取音量，返回一个0到1的音量百分比。该接口可能尚未实现。
//@别名 WKE_取音量大小(webView)
float wkeGetMediaVolume(wkeWebView webView);

//@备注 设置音量，volume为0到1之间的小数。
//@别名 WKE_置音量大小(webView,音量大小)
void wkeSetMediaVolume(wkeWebView webView, float volume);

//@备注 触发一个鼠标事件。注意：x和y为相对窗口左上角的像素坐标。
//@参数 webView
//@参数 消息值 参见枚举值 WKE鼠标消息
//@参数 X 对窗口左上角的像素横坐标
//@参数 Y 对窗口左上角的像素纵坐标
//@参数 标志 参见枚举值 WKE鼠标标志
//@别名 WKE_发送鼠标事件(webView,消息值,x,y,标志)
BOOL wkeFireMouseEvent(wkeWebView webView, unsigned int message, int x, int y, unsigned int flags);

//@备注 向webView发送滚轮消息。
//@参数 标志 参见枚举值 WKE鼠标标志
//@别名 WKE_发送滚轮事件(webView,x,y,滚动值,标志)
BOOL wkeFireMouseWheelEvent(wkeWebView webView, int x, int y, int delta, unsigned int flags);

//@备注 向webView发送WM_KEYUP消息
//@别名 WKE_发送键盘消息_键放开(webView,键代码,标志,系统键)
BOOL wkeFireKeyUpEvent(wkeWebView webView, unsigned int virtualKeyCode, unsigned int flags, bool systemKey);

//@备注 向webView发送WM_KEYDOWN消息
//@别名 WKE_发送键盘消息_键按下(webView,键代码,标志,系统键)
BOOL wkeFireKeyDownEvent(wkeWebView webView, unsigned int virtualKeyCode, unsigned int flags, bool systemKey);

//@备注 向webView发送WM_KEYPRESS消息。
//@别名 WKE_发送键盘消息(webView,键代码,标志,系统键)
BOOL wkeFireKeyPressEvent(wkeWebView webView, unsigned int charCode, unsigned int flags, bool systemKey);

//@备注 向mb发送任意windows消息。注意：MB在无窗口模式下，要响应光标事件，需要通过本函数手动发送光标消息。
//@别名 WKE_发送消息(webView,窗口句柄,消息值,wParam,lParam,返回值)
BOOL wkeFireWindowsMessage(wkeWebView webView, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* result);

//@备注 设置webview获得焦点。注意：如果webveiw绑定了窗口，窗口也会获得焦点。
//@别名 WKE_获取焦点(webView)
void wkeSetFocus(wkeWebView webView);

//@备注 设置webview放弃焦点。
//@别名 WKE_取消焦点(webView)
void wkeKillFocus(wkeWebView webView);

//@备注 获取编辑框中光标的位置。
//@别名 WKE_取编辑框光标位置(webView)
wkeRect wkeGetCaretRect(wkeWebView webView);

//@备注 获取编辑框中光标的位置，不方便处理结构体数据类型的语言可使用本接口。
//@别名 WKE_取编辑框光标位置2(webView)
wkeRect* wkeGetCaretRect2(wkeWebView webView);

//@备注 执行一段js代码，由于js是弱类型语言，返回值统一用jsValue类型表示，jsValue其实是一个指向封装了v8内部各种类型的类指针），后面提供了一组用于具体类型转换的接口
//@别名 WKE_执行js代码(webView,JS代码)
jsValue wkeRunJS(wkeWebView webView, const utf8* script);
//@备注 执行一段js代码，由于js是弱类型语言，返回值统一用jsValue类型表示，jsValue其实是一个指向封装了v8内部各种类型的类指针），后面提供了一组用于具体类型转换的接口
//@别名 WKE_执行js代码W(webView,JS代码)
jsValue wkeRunJSW(wkeWebView webView, const wchar_t* script);

//@备注 获取页面主frame的jsExecState，jsExecState可以理解为一个句柄，js相关接口会频繁使用该句柄，使用完立刻就失效，再次使用需重新获取。
//@别名 WKE_取主框架JsExec(webView)
jsExecState wkeGlobalExec(wkeWebView webView);

//@备注 获取页面主frame的jsExecState，jsExecState可以理解为一个句柄，js相关接口会频繁使用该句柄，使用完立刻就失效，再次使用需重新获取。
//@别名 WKE_取框架JsExec(webView,框架ID)
jsExecState wkeGetGlobalExecByFrame(wkeWebView webView, wkeWebFrameHandle frameId);

//@备注 获取webView的id，基本没啥用。
//@别名 WKE_取WebviewID(webView)
int wkeGetWebviewId(wkeWebView webView);

//@别名 WKE_是否有效(webView)
BOOL wkeIsWebviewValid(wkeWebView webView);

//@备注 设置页面缩放系数，默认是1。
//@别名 WKE_置缩放系数(webView,缩放系数)
void wkeSetZoomFactor(wkeWebView webView, float factor);

//@备注 获取页面缩放系数。
//@别名 WKE_取缩放系数(webView)
float wkeGetZoomFactor(wkeWebView webView);

//@备注 开启高分屏支持。注意：本质是通过设置ZOOM并且关闭系统默认缩放来实现的，所以再使用wkeGetZoomFactor会发现值可能不为1。
//@别名 WKE_开启高分屏支持()
void wkeEnableHighDPISupport();

//@备注 获取当前线程环境内的webView
//@别名 WKE_取线程WebView()
wkeWebView wkeGetWebViewForCurrentContext();

//@备注 对webView设置一个kv键值对，本质是一个 字典<单文本,void*> 结构，可以认为这是一个MB内部的数据缓存区。
//@别名 WKE_设置用户缓存(webView,键名,值指针)
void wkeSetUserKeyValue(wkeWebView webView, const char* key, void* value);

//@备注 获取webView指定key对应的value。
//@别名 WKE_取用户缓存(webView,键名)
void* wkeGetUserKeyValue(wkeWebView webView, const char* key);

//@备注 获取当前光标类型。
//@别名 WKE_取当前光标类型(webView)
int wkeGetCursorInfoType(wkeWebView webView);

//@备注 设置当前光标类型，
//@参数 光标类型 参看Windows系统定义的光标枚举数据类型。
//@别名 WKE_置当前光标类型(webView,光标类型)
void wkeSetCursorInfoType(wkeWebView webView, int type);

//@备注 设置文件拖拽支持。
//@别名 WKE_置文件拖拽支持(webView,clintPos,screenPos,文件列表,文件列表宽度)
void wkeSetDragFiles(wkeWebView webView, const POINT* clintPos, const POINT* screenPos, wkeString files[], int filesCount);

//@备注 显示开发者调试工具，path为开发者工具的资源路径，如file:///c:/miniblink-release/front_end/inspector.html，必须是全路径，并且不能有中文。
//@参数 回调函数 参见 WKE_回调类型_开发者调试
//@别名 WKE_显示开发者调试工具(webView,路径,回调函数,自定义参数)
void wkeShowDevtools(wkeWebView webView, const wchar_t* path, wkeOnShowDevtoolsCallback callback, void* param);

//@备注 鼠标滑过url时触发此回调
//@参数 回调事件 参见 WKE_回调类型_文本
//@别名 WKE_回调事件_鼠标经过超链接(webView,文本更新回调,自定义参数)
void wkeOnMouseOverUrlChanged(wkeWebView webView, wkeTitleChangedCallback callback, void* callbackParam);

//@备注 标题改变时触发此回调
//@参数 回调事件 参见 WKE_回调类型_文本
//@别名 WKE_回调事件_标题被改变(webView,文本更新回调,自定义参数)
void wkeOnTitleChanged(wkeWebView webView, wkeTitleChangedCallback callback, void* callbackParam);

//@备注 url改变时触发此回调
//@参数 回调事件 参见 WKE_回调类型_文本
//@别名 WKE_回调事件_URL被改变(webView,文本更新回调,自定义参数)
void wkeOnURLChanged(wkeWebView webView, wkeURLChangedCallback callback, void* callbackParam);

//@备注 url改变时触发此回调
//@参数 回调事件 参见 WKE_回调类型_文本2
//@别名 WKE_回调事件_URL被改变2(webView,文本更新回调2,自定义参数)
void wkeOnURLChanged2(wkeWebView webView, wkeURLChangedCallback2 callback, void* callbackParam);

//@备注 页面任何区域刷新时触发此回调
//@参数 回调事件 参见 WKE_回调类型_DC绘制事件
//@别名 WKE_回调事件_区域被刷新_DC(webView,绘制事件回调,自定义参数)
void wkeOnPaintUpdated(wkeWebView webView, wkePaintUpdatedCallback callback, void* callbackParam);

//@备注 功能同wkeOnPaintUpdated，不同的是回调过来的是填充好像素的buffer，而不是DC。方便嵌入到游戏中做离屏渲染
//@参数 回调事件 参见 WKE_回调类型_像素绘制事件
//@别名 WKE_回调事件_区域被刷新_Bit(webView,绘制事件回调,自定义参数)
void wkeOnPaintBitUpdated(wkeWebView webView, wkePaintBitUpdatedCallback callback, void* callbackParam);

//@备注 网页弹出alert时触发此回调
//@参数 回调事件 参见 WKE_回调类型_信息框
//@别名 WKE_回调事件_网页弹窗(webView,弹窗事件回调,自定义参数)
void wkeOnAlertBox(wkeWebView webView, wkeAlertBoxCallback callback, void* callbackParam);

//@备注 网页弹出Confirm时触发此回调
//@参数 回调事件 参见 WKE_回调类型_确认框
//@别名 WKE_回调事件_网页弹窗_确认框(webView,弹窗事件回调,自定义参数)
void wkeOnConfirmBox(wkeWebView webView, wkeConfirmBoxCallback callback, void* callbackParam);

//@备注 网页弹出Prompt时触发此回调
//@参数 回调事件 参见 WKE_回调类型_输入框
//@别名 WKE_回调事件_网页弹窗_输入框(webView,弹窗事件回调,自定义参数)
void wkeOnPromptBox(wkeWebView webView, wkePromptBoxCallback callback, void* callbackParam);

//@备注 有Console输出时触发此回调
//@参数 回调事件 参见 WKE_回调类型_控制台输出
//@别名 WKE_回调事件_控制台输出(webView,回调事件,自定义参数)
void wkeOnConsole(wkeWebView webView, wkeConsoleCallback callback, void* param);

//@备注 页面导航时触发此回调
//@参数 回调事件 参见 WKE_回调类型_页面导航
//@别名 WKE_回调事件_页面导航(webView,回调事件,自定义参数)
void wkeOnNavigation(wkeWebView webView, wkeNavigationCallback callback, void* param);

//@备注 新建webView时触发此回调，一般配合wkeSetNavigationToNewWindowEnable开关使用
//@参数 回调事件 参见 WKE_回调类型_创建WebView
//@别名 WKE_回调事件_创建WebView(webView,回调事件,自定义参数)
void wkeOnCreateView(wkeWebView webView, wkeCreateViewCallback callback, void* param);

//@备注 网页Document数据结构生成完成时触发此回调。注意：由于现在网页多采用异步加载模式，Document数据结构生成完成 ≠ 网页加载完成，每个异步执行的加载动作完成时都可能会触发一次本回调，注意是可能，不是一定，另外页面中如有多个frame，每个frame加载完成时都会触发一次本回调，实践中可以采用wkeOnLoadingFinish接口，wkeOnTitleChanged接口，wkeOnURLChanged接口，以及检查页面中某个元素（如网站logo等）是否存在等方法来综合判断页面加载是否完成。
//@参数 回调事件 参见 WKE_回调类型_文档加载完成
//@别名 WKE_回调事件_文档加载完成(webView,回调事件,自定义参数)
void wkeOnDocumentReady(wkeWebView webView, wkeDocumentReadyCallback callback, void* param);

//@备注 网页Document数据结构生成完成时触发此回调。注意：由于现在网页多采用异步加载模式，Document数据结构生成完成 ≠ 网页加载完成，每个异步执行的加载动作完成时都可能会触发一次本回调，注意是可能，不是一定，另外页面中如有多个frame，每个frame加载完成时都会触发一次本回调，实践中可以采用wkeOnLoadingFinish接口，wkeOnTitleChanged接口，wkeOnURLChanged接口，以及检查页面中某个元素（如网站logo等）是否存在等方法来综合判断页面加载是否完成。
//@参数 回调事件 参见 WKE_回调类型_文档加载完成2
//@别名 WKE_回调事件_文档加载完成2(webView,回调事件,自定义参数)
void wkeOnDocumentReady2(wkeWebView webView, wkeDocumentReady2Callback callback, void* param);

//@备注 页面加载完成时触发此回调。注意：注意事项同wkeOnDocumentReady
//@参数 回调事件 参见 WKE_回调类型_页面加载完成
//@别名 WKE_回调事件_页面加载完成(webView,回调事件,自定义参数)
void wkeOnLoadingFinish(wkeWebView webView, wkeLoadingFinishCallback callback, void* param);

//@备注 有下载文件时触发此回调。注意：此接口尚未完善，回调中暂时只返回了下载URL，未带有身份认证信息，所以只适用于不需要身份认证的下载请求。
//@参数 回调事件 参见 WKE_回调类型_下载文件
//@别名 WKE_回调事件_下载文件(webView,回调事件,自定义参数)
void wkeOnDownload(wkeWebView webView, wkeDownloadCallback callback, void* param);

//@参数 回调事件 参见 WKE_回调类型_下载文件2
//@别名 WKE_回调事件_下载文件2(webView,回调事件,自定义参数)
void wkeOnDownload2(wkeWebView webView, wkeDownload2Callback callback, void* param);

//@备注 调用UI线程时，触发此回调
//@参数 回调事件 参见 WKE_回调类型_UI线程回调
//@别名 WKE_回调事件_设置UI线程回调(webView,回调函数,参数)
void wkeSetUIThreadCallback(wkeWebView webView, wkeCallUiThread callback, void* param);

//@备注 任何网络请求发起前会触发此回调
//@参数 回调事件 参见 WKE_回调类型_网络请求开始
//@别名 WKE_回调事件_网络请求开始(webView,回调函数,参数)
void wkeOnLoadUrlBegin(wkeWebView webView, wkeLoadUrlBeginCallback callback, void* callbackParam);

//@备注 网络请求结束时会触发此回调，只有设置了wkeNetSetData或wkeNetHookRequest才会触发该接口
//@参数 回调事件 参见 WKE_回调类型_网络请求结束
//@别名 WKE_回调事件_网络请求结束(webView,回调函数,参数)
void wkeOnLoadUrlEnd(wkeWebView webView, wkeLoadUrlEndCallback callback, void* callbackParam);

//@备注 网页加载失败时触发此回调
//@参数 回调事件 参见 WKE_回调类型_网页加载失败
//@别名 WKE_回调事件_网页加载失败(webView,回调函数,参数)
void wkeOnLoadUrlFail(wkeWebView webView, wkeLoadUrlFailCallback callback, void* callbackParam);

//@备注 网络请求发送后，收到服务器response时触发此回调
//@参数 回调事件 参见 WKE_回调类型_收到返回信息
//@别名 WKE_回调事件_收到返回信息(webView,回调函数,参数)
void wkeNetOnResponse(wkeWebView webView, wkeNetResponseCallback callback, void* param);

//@备注 执行js前触发此回调
//@参数 回调事件 参见 WKE_回调类型_准备执行JS
//@别名 WKE_回调事件_准备执行JS(webView,回调函数,参数)
void wkeOnDidCreateScriptContext(wkeWebView webView, wkeDidCreateScriptContextCallback callback, void* callbackParam);

//@备注 执行js前触发此回调
//@参数 回调事件 参见 WKE_回调类型_执行JS完成
//@别名 WKE_回调事件_执行JS完成(webView,回调函数,参数)
void wkeOnWillReleaseScriptContext(wkeWebView webView, wkeWillReleaseScriptContextCallback callback, void* callbackParam);

//@备注 wkeWebView如果是正常窗口模式，则在收到WM_CLODE消息时触发此回调接口，回调可返回false拒绝关闭窗口
//@参数 回调事件 参见 WKE_回调类型_窗口将被关闭
//@别名 WKE_回调事件_窗口将被关闭(webView,回调函数,参数)
void wkeOnWindowClosing(wkeWebView webWindow, wkeWindowClosingCallback callback, void* param);

//@备注 窗口即将被销毁时触发此回调。注意：与wkeOnWindowClosing不同，这个操作一旦开始则无法取消。
//@参数 回调事件 参见 WKE_回调类型_窗口将被销毁
//@别名 WKE_回调事件_窗口将被销毁(webView,回调函数,参数)
void wkeOnWindowDestroy(wkeWebView webWindow, wkeWindowDestroyCallback callback, void* param);

//@备注 拖拽区域改变时触发此回调
//@参数 回调事件 参见 WKE_回调类型_拖拽区域被改变
//@别名 WKE_回调事件_拖拽区域被改变(webView,回调函数,参数)
void wkeOnDraggableRegionsChanged(wkeWebView webView, wkeDraggableRegionsChangedCallback callback, void* param);

//@备注 截图时触发此回调
//@参数 回调事件 参见 WKE_回调类型_截图事件
//@别名 WKE_回调事件_截图事件(webView,回调函数,参数)
void wkeScreenshot(wkeWebView webView, const wkeScreenshotSettings* settings, wkeOnScreenshot callback, void* param);

//@备注 菜单中的某项被点击时触发此回调
//@参数 回调事件 参见 WKE_回调类型_菜单项被点击
//@别名 WKE_回调事件_菜单项被点击(webView,回调函数,参数)
void wkeOnContextMenuItemClick(wkeWebView webView, wkeOnContextMenuItemClickCallback callback, void* param);

//@备注 获取favicon图标，此接口需在wkeOnLoadingFinish回调里调用
//@参数 回调事件 参见 WKE_回调类型_获取图标
//@别名 WKE_回调事件_获取图标(webView,回调函数,参数)
int wkeNetGetFavicon(wkeWebView webView, wkeOnNetGetFaviconCallback callback, void* param);

//@备注 用于判断是否收到用户手势操作。
//@别名 WKE_是否收到手势操作(webView)
BOOL wkeIsProcessingUserGesture(wkeWebView webView);

//@备注 设置网络接口，一般用不到。
//@别名 WKE_设置网络接口(webView,网络接口)
void wkeSetViewNetInterface(wkeWebView webView, const char* netInterface);

//@备注 在wkeOnLoadUrlBegin回调里调用，设置http请求的MIME类型。
//@别名 WKE_置请求MIME(网络任务,MIME)
void wkeNetSetMIMEType(wkeNetJob jobPtr, const char* type);

//@备注 获取response的MIME类型。
//@别名 WKE_取返回MIME(网络任务,MIME)
const char* wkeNetGetMIMEType(wkeNetJob jobPtr, wkeString mime);

//@备注 在wkeOnLoadUrlBegin回调里调用，设置http请求（或者file:///协议）的http请求头。response一直要被设置成false。
//@别名 WKE_置HTTP请求头(网络任务,键名,值,返回)
void wkeNetSetHTTPHeaderField(wkeNetJob jobPtr, const wchar_t* key, const wchar_t* value, bool response);

//@备注 在wkeOnLoadUrlBegin回调里调用，获取HTTP请求头。
//@别名 WKE_取HTTP请求头(网络任务,键名)
const char* wkeNetGetHTTPHeaderField(wkeNetJob jobPtr, const char* key);

//@备注 获取HTTP响应头。
//@别名 WKE_取HTTP响应头(网络任务,键名)
const char* wkeNetGetHTTPHeaderFieldFromResponse(wkeNetJob jobPtr, const char* key);

//@备注 此接口一般在wkeOnLoadUrlBegin接口回调wkeLoadUrlBeginCallback中使用，在网络访问执行前，设置指定的数据到网络层，数据内容可以为js代码，图片，字符串，数据块等任意类型，设置此接口后会触发OnLoadUrlEnd事件。
//@别名 WKE_置网络数据(网络任务,数据内容,数据长度)
void wkeNetSetData(wkeNetJob jobPtr, void *buf, int len);

//@备注 拦截某次网络请求，此接口会在接受到真正网络数据后触发OnLoadUrlEnd事件，你可以在wkeLoadUrlEndCallback中修改接收到的数据。注意：此接口是在接收到实际的网络数据后进行拦截，而wkeNetSetData是在数据尚未发送前进行插入。
//@别名 WKE_拦截请求(网络任务)
void wkeNetHookRequest(wkeNetJob jobPtr);

//@备注 获取此请求的method类型
//@别名 WKE_取请求类型(网络任务)
wkeRequestType wkeNetGetRequestMethod(wkeNetJob jobPtr);

//@备注 继续某次异步网络请求，参考wkeNetHoldJobToAsynCommit。
//@别名 WKE_继续异步请求(网络任务)
void wkeNetContinueJob(wkeNetJob jobPtr);

//@备注 通过jobPtr获取当前请求的url。
//@别名 WKE_取请求Url(网络任务)
const char* wkeNetGetUrlByJob(wkeNetJob jobPtr);

//@备注 获取Raw格式的HTTP请求数据
//@别名 WKE_取原始HTTP请求数据(网络任务)
const wkeSlist* wkeNetGetRawHttpHead(wkeNetJob jobPtr);

//@备注 获取Raw格式的HTTP响应数据。
//@别名 WKE_取原始HTTP响应数据(网络任务)
const wkeSlist* wkeNetGetRawResponseHead(wkeNetJob jobPtr);

//@备注 取消本次网络请求，需要在wkeOnLoadUrlBegin里调用。
//@别名 WKE_取消请求(网络任务)
void wkeNetCancelRequest(wkeNetJob jobPtr);

//@备注 当在wkeOnLoadUrlBegin中里拦截到一个请求后需要进行一些耗时操作时，可以调用本接口，耗时操作完成后需要调用wkeNetContinueJob接口以通知MB让此次请求继续进行。注意：返回true代表成功，false代表调用失败，如失败则不能再调用wkeNetContinueJob。
//@别名 WKE_中断异步请求(网络任务)
BOOL wkeNetHoldJobToAsynCommit(wkeNetJob jobPtr);

//@备注 修改当前请求的url。
//@别名 WKE_置请求URL(网络任务,URL)
void wkeNetChangeRequestUrl(wkeNetJob jobPtr, const char* url);

//@别名 WKE_创建网络请求(链接,请求类型,MIME)
wkeWebUrlRequestPtr wkeNetCreateWebUrlRequest(const utf8* url, const utf8* method, const utf8* mime);

//@别名 WKE_创建网络请求Blink(Blink请求)
wkeWebUrlRequestPtr wkeNetCreateWebUrlRequest2(const blinkWebURLRequestPtr request);

//@备注 复制一个网络请求。
//@别名 WKE_复制网络请求(网络任务,需要额外数据)
blinkWebURLRequestPtr wkeNetCopyWebUrlRequest(wkeNetJob jobPtr, bool needExtraData);

//@备注 取消网络请求。
//@别名 WKE_取消Blink网络请求(网络请求)
void wkeNetDeleteBlinkWebURLRequestPtr(blinkWebURLRequestPtr request);

//@备注 在指定网络请求中插入一个请求头。
//@别名 WKE_网络请求添加请求头(网络请求)
void wkeNetAddHTTPHeaderFieldToUrlRequest(wkeWebUrlRequestPtr request, const utf8* name, const utf8* value);

//@备注 开始网络请求
//@别名 WKE_开始网络请求(webView,网络请求,参数,请求回调)
int wkeNetStartUrlRequest(wkeWebView webView, wkeWebUrlRequestPtr request, void* param, const wkeUrlRequestCallbacks* callbacks);

//@备注 获取HTTP响应状态码。
//@别名 WKE_取HTTP状态码(网络响应)
int wkeNetGetHttpStatusCode(wkeWebUrlResponsePtr response);

//@备注 获取响应数据大小。
//@别名 WKE_取响应数据尺寸(网络响应)
__int64 wkeNetGetExpectedContentLength(wkeWebUrlResponsePtr response);

//@备注 获取响应url。
//@别名 WKE_取响应URL(网络响应)
const utf8* wkeNetGetResponseUrl(wkeWebUrlResponsePtr response);

//@备注 取消网络请求。
//@别名 WKE_取消网络请求(请求ID)
void wkeNetCancelWebUrlRequest(int requestId);

//@备注 获取此请求中的post数据。注意：只有当请求是post时才可获取到。
//@别名 WKE_取POST请求数据(网络任务)
wkePostBodyElements* wkeNetGetPostBody(wkeNetJob jobPtr);

//@备注 创建post数据包。
//@别名 WKE_创建POST数据包(webView,数据包长度)
wkePostBodyElements* wkeNetCreatePostBodyElements(wkeWebView webView, size_t length);

//@备注 干掉post数据包，释放内存。
//@别名 WKE_释放POST数据包(POST数据包)
void wkeNetFreePostBodyElements(wkePostBodyElements* elements);

//@备注 创建post数据。
//@别名 WKE_创建POST数据(webView)
wkePostBodyElement* wkeNetCreatePostBodyElement(wkeWebView webView);

//@备注 干掉post数据，释放内存。
//@别名 WKE_释放POST数据(POST数据)
void wkeNetFreePostBodyElement(wkePostBodyElement* element);

//@备注 判断是否是主frame。
//@别名 WKE_是否为主框架(webView,框架句柄)
BOOL wkeIsMainFrame(wkeWebView webView, wkeWebFrameHandle frameId);

//@备注 判断是否是远程frame。
//@别名 WKE_是否为远程框架(webView,框架句柄)
BOOL wkeIsWebRemoteFrame(wkeWebView webView, wkeWebFrameHandle frameId);

//@备注 获取主frame。
//@别名 WKE_取主框架句柄(webView)
wkeWebFrameHandle wkeWebFrameGetMainFrame(wkeWebView webView);

//@备注 在指定frame中执行一段js代码，如果isInClosure为true，则MB会将这段js代码放到一个function(){ script }中执行，以避免变量名和页面中的js变量重名导致的错误。
//@别名 WKE_执行JS代码(webView,框架句柄,脚本内容,是否闭包)
jsValue wkeRunJsByFrame(wkeWebView webView, wkeWebFrameHandle frameId, const utf8* script, bool isInClosure);

//@备注 在指定frame中插入一段css。
//@别名 WKE_置入CSS(webView,框架句柄,CSS文本)
void wkeInsertCSSByFrame(wkeWebView webView, wkeWebFrameHandle frameId, const utf8* cssText);

//@备注 获取全局脚本上下文环境
//@别名 WKE_取V8上下文(webView,框架句柄,返回上下文)
void wkeWebFrameGetMainWorldScriptContext(wkeWebView webView, wkeWebFrameHandle webFrameId, v8ContextPtr contextOut);

//@备注 获取渲染主线程的隔离环境。
//@别名 WKE_取主线程隔离环境()
v8Isolate wkeGetBlinkMainThreadIsolate();

//@备注 创建一个带真实窗口的wkeWebView
//@别名 WKE_创建WebView_窗口(窗口类型,父窗口,横坐标,纵坐标,宽度,高度)
wkeWebView wkeCreateWebWindow(wkeWindowType type, HWND parent, int x, int y, int width, int height);

//@备注 创建一个带真实窗口的wkeWebView
//@别名 WKE_创建WebView_窗口Ex(窗口信息)
wkeWebView wkeCreateWebCustomWindow(const wkeWindowCreateInfo* info);

//@备注 干掉wkeWebView对应的所有资源，包括真实窗口等。
//@别名 WKE_释放WebView资源(WebView)
void wkeDestroyWebWindow(wkeWebView webWindow);

//@备注 设置是否显示窗口。。
//@别名 WKE_可视(WebView,是否可视)
void wkeShowWindow(wkeWebView webWindow, bool show);

//@备注 设置是否激活窗口。
//@别名 WKE_是否激活(WebView,是否激活)
void wkeEnableWindow(wkeWebView webWindow, bool enable);

//@备注 移动窗口，参数为从指定坐标移动指定的距离。
//@别名 WKE_移动窗口(WebView,横坐标,纵坐标,宽度,高度)
void wkeMoveWindow(wkeWebView webWindow, int x, int y, int width, int height);

//@备注 设置webView窗口在其父窗口或屏幕居中。
//@别名 WKE_置居中(WebView)
void wkeMoveToCenter(wkeWebView webWindow);

//@备注 获取MHTML代码。
//@别名 WKE_取MHTML代码(webView)
const utf8* wkeUtilSerializeToMHTML(wkeWebView webView);

//@备注 将页面输出为PDF格式
//@别名 WKE_网页保存为PDF(webView,框架句柄,输出设置)
const wkePdfDatas* wkeUtilPrintToPdf(wkeWebView webView, wkeWebFrameHandle frameId, const wkePrintSettings* settings);

//@备注 释放打印PDF数据。
//@别名 WKE_释放PDF数据(PDF数据指针)
void wkeUtilRelasePrintPdfDatas(const wkePdfDatas* datas);

//@备注 把页面输出为图片
//@别名 WKE_网页保存为图片(webView,框架句柄,图像输出设置)
const wkeMemBuf* wkePrintToBitmap(wkeWebView webView, wkeWebFrameHandle frameId, const wkeScreenshotSettings* settings);

//@备注 设置窗口标题。
//@别名 WKE_置窗口标题(webView,标题)
void wkeSetWindowTitle(wkeWebView webWindow, const utf8* title);

//@备注 设置窗口标题。
//@别名 WKE_置窗口标题W(webView,标题)
void wkeSetWindowTitleW(wkeWebView webWindow, const wchar_t* title);

//@备注 创建node时触发此回调
//@参数 回调事件 参见 WKE_回调类型_创建node
//@别名 WKE_回调事件_创建node(webView,回调函数,参数)
void wkeNodeOnCreateProcess(wkeWebView webView, wkeNodeOnCreateProcessCallback callback, void* param);

//@备注 查找插件时触发此回调
//@参数 回调事件 参见 WKE_回调类型_查找插件
//@别名 WKE_回调事件_查找插件(webView,回调函数,参数)
void wkeOnPluginFind(wkeWebView webView, const char* mime, wkeOnPluginFindCallback callback, void* param);

//@备注 添加Npapi插件。
//@别名 WKE_插件_添加Npapi(webView,初始化函数,入口点函数,结束函数)
void wkeAddNpapiPlugin(wkeWebView webView, void* initializeFunc, void* getEntryPointsFunc, void* shutdownFunc);

//@备注 往插件列表中添加插件。
//@别名 WKE_插件_添加插件(开发者,名称,描述,文件名)
void wkePluginListBuilderAddPlugin(void* builder, const utf8* name, const utf8* description, const utf8* fileName);

//@备注 往插件列表尾部添加多媒体插件。
//@别名 WKE_插件_多媒体插件(开发者,名称,描述)
void wkePluginListBuilderAddMediaTypeToLastPlugin(void* builder, const utf8* name, const utf8* description);

//@备注 往多媒体插件添加文件扩展信息。
//@别名 WKE_插件_多媒体插件添加扩展(开发者,扩展名)
void wkePluginListBuilderAddFileExtensionToLastMediaType(void* builder, const utf8* fileExtension);

//@备注 从ndata中获取webView。
//@别名 WKE_取WebView_Ndata(ndata)
wkeWebView wkeGetWebViewByNData(void* ndata);

//@备注 注册自定义元素。
//@别名 WKE_注册元素(webView,框架句柄,名称,设置,返回)
BOOL wkeRegisterEmbedderCustomElement(wkeWebView webView, wkeWebFrameHandle frameId, const char* name, void* options, void* outResult);

//@备注 获取标记内容。
//@别名 WKE_取标记内容(webView,框架句柄,返回长度)
const utf8* wkeGetContentAsMarkup(wkeWebView webView, wkeWebFrameHandle frame, size_t* size);

//@备注 URLEscape编码。
//@别名 WKE_编码_URL编码(url)
const utf8* wkeUtilEncodeURLEscape(const utf8* url);

//@备注 URLEscape解码。
//@别名 WKE_编码_URL解码(url)
const utf8* wkeUtilDecodeURLEscape(const utf8* url);

//@备注 base64编码。
//@别名 WKE_编码_Base64编码(数据)
const utf8* wkeUtilBase64Encode(const utf8* str);

//@备注 base64解码。
//@别名 WKE_编码_Base64解码(数据)
const utf8* wkeUtilBase64Decode(const utf8* str);

//@备注 创建V8内存快照
//@别名 WKE_创建V8内存快照(数据)
const wkeMemBuf* wkeUtilCreateV8Snapshot(const utf8* str);

//@备注 执行消息循环。
//@别名 WKE_消息循环()
void wkeRunMessageLoop();

//@备注 保存webView内存缓存。
//@别名 WKE_保存WebView缓存(webView)
void wkeSaveMemoryCache(wkeWebView webView);

//@备注 绑定一个全局函数到主frame上，name为js函数名称，当v8引擎执行到该函数时，会触发c中的fn函数，从而实现在js代码中调用c函数的功能
//·   注意：
//·   1、此接口只能绑定主frame。
//·   2、此接口是fastcall调用约定，但wkeJsBindFunction是__cdecl。
//·   3、此接口和wkeJsBindFunction必须在webview创建前调用。
//@别名 WKE_JS_绑定全局函数(JS函数名,本机函数,参数数量)
void jsBindFunction(const char* name, jsNativeFunction fn, unsigned int argCount);
//@备注 具体可参见 WKE_JS_绑定全局函数
//@别名 WKE_JS_绑定全局函数C(JS函数名,本机函数,附加参数,参数数量)
void wkeJsBindFunction(const char* name, wkeJsNativeFunction fn, void* param, unsigned int argCount);

//@备注 对js window绑定一个属性访问器，在js里windows.XXX这种形式调用时，会触发c++中的fn函数。
//@别名 WKE_JS_绑定Window访问器(名称,回调)
void jsBindGetter(const char* name, jsNativeFunction fn);
//@备注 对js window绑定一个属性访问器，在js里windows.XXX这种形式调用时，会触发c++中的fn函数。
//@别名 WKE_JS_绑定Window访问器C(名称,回调,附加参数)
void wkeJsBindGetter(const char* name, wkeJsNativeFunction fn, void* param);

//@备注 对js window绑定一个属性设置器。
//@别名 WKE_JS_绑定属性访问器(名称,回调)
void jsBindSetter(const char* name, jsNativeFunction fn);
//@备注 对js window绑定一个属性设置器。
//@别名 WKE_JS_绑定属性访问器C(名称,回调,附加参数)
void wkeJsBindSetter(const char* name, wkeJsNativeFunction fn, void* param);

//@备注 获取es里存的参数个数，一般是在绑定的js调用c回调里使用，判断js传递了多少个参数给c。
//@别名 WKE_JS_取参数个数(es)
int jsArgCount(jsExecState es);

//@备注 判断第argIdx个参数的参数类型。
//@别名 WKE_JS_取参数类型(es,参数索引)
jsType jsArgType(jsExecState es, int argIdx);

//@备注 获取第argIdx个参数的jsValue值。
//@别名 WKE_JS_取参数值(es,参数索引)
jsValue jsArg(jsExecState es, int argIdx);

//@备注 获取v的数据类型
//@别名 WKE_JS_取值类型(值指针)
jsType jsTypeOf(jsValue v);

//@备注 判断v是否为数字。
//@别名 WKE_JS_是否为数字(值指针)
BOOL jsIsNumber(jsValue v);

//@备注 判断v是否为字符串。
//@别名 WKE_JS_是否为文本(值指针)
BOOL jsIsString(jsValue v);

//@备注 判断v是否为bool值。
//@别名 WKE_JS_是否为逻辑型(值指针)
BOOL jsIsBoolean(jsValue v);

//@备注 判断v是否为Object对象。
//@别名 WKE_JS_是否为对象(值指针)
BOOL jsIsObject(jsValue v);

//@备注 判断v是否为函数。
//@别名 WKE_JS_是否为函数(值指针)
BOOL jsIsFunction(jsValue v);

//@备注 判断v是否为未定义。
//@别名 WKE_JS_是否为未定义(值指针)
BOOL jsIsUndefined(jsValue v);

//@备注 判断v是否为null。
//@别名 WKE_JS_是否为NULL(值指针)
BOOL jsIsNull(jsValue v);

//@备注 判断v是否为数组型。
//@别名 WKE_JS_是否为数组(值指针)
BOOL jsIsArray(jsValue v);

//@备注 如果v本身是个布尔值，返回对应的true或者false，如果是个对象（JSTYPE_OBJECT），返回false。
//@别名 WKE_JS_值是否为真(值指针)
BOOL jsIsTrue(jsValue v);

//@备注 等价于!jsIsTrue(v)。
//@别名 WKE_JS_值是否为假(值指针)
BOOL jsIsFalse(jsValue v);

//@备注 如果v是个整形则返回相应值，如果是浮点型则返回取整后的值，如果是其他类型则返回0。
//@别名 WKE_JS_值到整数(es,值指针)
int jsToInt(jsExecState es, jsValue v);

//@备注 如果v是个浮点型则返回相应值，如果是其他类型则返回0.0。
//@别名 WKE_JS_值到小数(es,值指针)
float jsToFloat(jsExecState es, jsValue v);

//@备注 如果v是个浮点型则返回相应值，如果是其他类型则返回0.0。
//@别名 WKE_JS_值到双精度小数(es,值指针)
double jsToDouble(jsExecState es, jsValue v);

//@备注 如果v是个DoubleString型则返回相应值，如果是其他类型则返回空字符串。
//@别名 WKE_JS_双文本到单字节(es,值指针)
const char* jsToDoubleString(jsExecState es, jsValue v);

//@备注 如果v是个bool型则返回相应值，如果是其他类型则返回FALSE。
//@别名 WKE_JS_值到逻辑型(es,值指针)
BOOL jsToBoolean(jsExecState es, jsValue v);

//@备注 如果v是个字符串则返回相应值，如果是其他类型则返回空字符串，注意：返回的字符串不需要外部释放，MB会在下一帧自动释放。
//@别名 WKE_JS_值到临时文本(es,值指针)
const utf8* jsToTempString(jsExecState es, jsValue v);

//@备注 宽字符版jsToTempString。
//@别名 WKE_JS_值到临时文本W(es,值指针)
const wchar_t* jsToTempStringW(jsExecState es, jsValue v);

//@备注 将v转成v8引擎中定义的数据类型，具体定义可参见v8::Persistentv8::Value*(给V8代码留的接口)。
//@别名 WKE_JS_值到V8类型(es,值指针)
void* jsToV8Value(jsExecState es, jsValue v);

//@备注 如果v是个字符串则返回相应值，如果是其他类型则返回空字符串。
//@别名 WKE_JS_值到文本(es,值指针)
const utf8* jsToString(jsExecState es, jsValue v);

//@备注 宽字符版jsToString。
//@别名 WKE_JS_值到文本W(es,值指针)
const wchar_t* jsToStringW(jsExecState es, jsValue v);

//@备注 将n转成int型的jsValue。
//@别名 WKE_JS_整型到Js值(值)
jsValue jsInt(int n);

//@备注 将f转成float型的jsValue。
//@别名 WKE_JS_小数型到Js值(值)
jsValue jsFloat(float f);

//@备注 将d转成double型的jsValue。
//@别名 WKE_JS_双精度小数型到Js值(值)
jsValue jsDouble(double d);

//@备注 将str转成doublestring型的jsValue。
//@别名 WKE_JS_单字节到Js双文本(值)
jsValue jsDoubleString(const char* str);

//@备注 将b转成bool型的jsValue。
//@别名 WKE_JS_逻辑型到Js值(值)
jsValue jsBoolean(bool b);

//@备注 将str转成string型的jsValue。
//@别名 WKE_JS_单文本到Js文本(es,值)
jsValue jsString(jsExecState es, const utf8* str);

//@备注 宽字符版jsString。
//@别名 WKE_JS_文本到Js文本(es,值)
jsValue jsStringW(jsExecState es, const wchar_t* str);

//@备注 创建一个表示js undefined的jsValue。
//@别名 WKE_JS_创建未定义()
jsValue jsUndefined();

//@备注 创建一个表示js null的jsValue。
//@别名 WKE_JS_创建NULL()
jsValue jsNull();

//@备注 创建一个表示js true的jsValue。
//@别名 WKE_JS_创建TRUE()
jsValue jsTrue();

//@备注 创建一个表示js false的jsValue。
//@别名 WKE_JS_创建FALSE()
jsValue jsFalse();

//@备注 创建一个表示js object的jsValue。
//@别名 WKE_JS_创建对象(es)
jsValue jsEmptyObject(jsExecState es);

//@备注 创建一个表示js array的jsValue。
//@别名 WKE_JS_创建数组(es)
jsValue jsEmptyArray(jsExecState es);

//@备注 将buffer中的数据转成jsValue型，主要用来处理一些二进制数据。
//@别名 WKE_JS_创建字节集(es,缓冲区,缓冲区长度)
jsValue jsArrayBuffer(jsExecState es, const char* buffer, size_t size);

//@备注 将value中的数据转成内存数据
//@别名 WKE_JS_取字节集(es,js值)
wkeMemBuf* jsGetArrayBuffer(jsExecState es, jsValue value);

//@备注 将value中的数据转成内存数据
//@别名 WKE_JS_C对象到JS对象(es,obj)
jsValue jsObject(jsExecState es, jsData* obj);

//@备注 将obj转成一个表示js function的jsValue。
//@别名 WKE_JS_C对象到JS函数(es,obj)
jsValue jsFunction(jsExecState es, jsData* obj);

//@备注 将exception转成一个表示js exception的jsValue。
//@别名 WKE_JS_到Exception(es,str)
jsValue jsThrowException(jsExecState es, const utf8* exception);

//@备注 获取jsObject或jsFunction创建的jsValue对应的jsData指针。
//@别名 WKE_JS_JS值指针到JS数据(es,obj)
jsData* jsGetData(jsExecState es, jsValue object);

//@备注 如果object是个js的object，则获取prop指定的属性。如果object不是js object类型，则返回jsUndefined。
//@别名 WKE_JS_取属性(es,obj,属性名称)
jsValue jsGet(jsExecState es, jsValue object, const char* prop);

//@备注 设置object的属性。
//@别名 WKE_JS_置属性(es,obj,属性名称,属性值)
void jsSet(jsExecState es, jsValue object, const char* prop, jsValue v);

//@备注 获取js arrary的第index个成员的值，object必须是js array才有用，否则会返回jsUndefined。
//@别名 WKE_JS_取数组成员值(es,数组指针,索引)
jsValue jsGetAt(jsExecState es, jsValue object, int index);

//@备注 设置js arrary的第index个成员的值，object必须是js array才有用。
//@别名 WKE_JS_置数组成员值(es,数组指针,索引,值)
void jsSetAt(jsExecState es, jsValue object, int index, jsValue v);

//@备注 设置js arrary的第index个成员的值，object必须是js array才有用。
//@别名 WKE_JS_取对象所有KEY(es,obj)
jsKeys* jsGetKeys(jsExecState es, jsValue object);

//@备注 判断object是否是无效值。
//@别名 WKE_JS_对象是否有效(es,obj)
BOOL jsIsJsValueValid(jsExecState es, jsValue object);

//@备注 判断es是否是无效状态。
//@别名 WKE_JS_Es是否有效(es)
BOOL jsIsValidExecState(jsExecState es);

//@备注 删除object中的指定prop属性。
//@别名 WKE_JS_对象删除prop属性(es,obj,prop名)
void jsDeleteObjectProp(jsExecState es, jsValue object, const char* prop);

//@备注 获取object长度。
//@别名 WKE_JS_取对象长度(es,obj)
int jsGetLength(jsExecState es, jsValue object);

//@备注 设置object长度。
//@别名 WKE_JS_置对象长度(es,obj,长度)
void jsSetLength(jsExecState es, jsValue object, int length);

//@备注 获取全局Object值。
//@别名 WKE_JS_取全局对象(es)
jsValue jsGlobalObject(jsExecState es);

//@备注 获取es对应的webview。
//@别名 WKE_JS_ES取Webview(es)
wkeWebView jsGetWebView(jsExecState es);

//@备注 执行一段js代码，代码会在MB内部自动被包裹在一个function(){}中，所以使用的变量会作为局部变量以避免同页面js代码中的其他变量重名导致运行出错，要获取返回值，请加return。
//@别名 WKE_JS_执行JS(es,js代码)
jsValue jsEval(jsExecState es, const utf8* str);

//@备注 执行一段js代码，代码会在MB内部自动被包裹在一个function(){}中，所以使用的变量会作为局部变量以避免同页面js代码中的其他变量重名导致运行出错，要获取返回值，请加return。
//@别名 WKE_JS_执行JSW(es,js代码)
jsValue jsEvalW(jsExecState es, const wchar_t* str);

//@备注 同jsEvalW，isInClosure设定是否闭包运行js。
//@别名 WKE_JS_执行JSExW(es,js代码,是否闭包)
jsValue jsEvalExW(jsExecState es, const wchar_t* str, bool isInClosure);

//@备注 执行页面中的js函数
//@别名 WKE_JS_执行函数(es,js函数名,父对象指针,参数列表,参数数量)
jsValue jsCall(jsExecState es, jsValue func, jsValue thisObject, jsValue* args, int argCount);

//@备注 调用window上的全局函数，参看jsCall。
//@别名 WKE_JS_执行Window函数(es,js函数名,参数列表,参数数量)
jsValue jsCallGlobal(jsExecState es, jsValue func, jsValue* args, int argCount);

//@备注 获取window上的属性。
//@别名 WKE_JS_取Window属性(es,属性名)
jsValue jsGetGlobal(jsExecState es, const char* prop);

//@备注 设置window上的属性。
//@别名 WKE_JS_置Window属性(es,属性名,属性值)
void jsSetGlobal(jsExecState es, const char* prop, jsValue v);

//@备注 强制js执行垃圾回收。
//@别名 WKE_JS_执行GC()
void jsGC();

//@备注 将val添加为js引用。
//@别名 WKE_JS_添加引用(es,val)
BOOL jsAddRef(jsExecState es, jsValue val);

//@备注 释放val引用。
//@别名 WKE_JS_释放引用(es,val)
BOOL jsReleaseRef(jsExecState es, jsValue val);

//@备注 释放val引用。
//@别名 WKE_JS_取异常信息(es)
jsExceptionInfo* jsGetLastErrorIfException(jsExecState es);

//@备注 返回js执行时的堆栈信息。
//@别名 WKE_JS_取执行堆栈信息(es)
const utf8* jsGetCallstack(jsExecState es);



*/

//@分组}






#endif //XL_XMINIBLINK_H
