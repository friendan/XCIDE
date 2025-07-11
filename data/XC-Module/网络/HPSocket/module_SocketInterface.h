//@模块名称  HPSocket  
//@版本  5.8.6  
//@日期  2022-02-14
//@作者  XCGUI, 易团雪
//@QQ   154460336
//@模块备注  HPSocket
//HP - Socket 是一套通用的高性能 TCP / UDP / HTTP 通信框架，包含服务端组件、客户端组件和Agent组件，
//广泛适用于各种不同应用场景的 TCP / UDP / HTTP 通信系统，
//HP - Socket 对通信层实现完全封装，应用程序不必关注通信层的任何细节；
//HP - Socket 提供基于事件通知模型的 API 接口，能非常简单高效地整合到新旧应用程序中。

//@依赖  module_base.h

#ifdef  XC_MODULE
#include "module_base.h"
#endif
/*
 * Copyright: JessMA Open Source (ldcsaa@gmail.com)
 *
 * Author	: Bruce Liang
 * Website	: https://github.com/ldcsaa
 * Project	: https://github.com/ldcsaa/HP-Socket
 * Blog		: http://www.cnblogs.com/ldcsaa
 * Wiki		: http://www.oschina.net/p/hp-socket
 * QQ Group	: 44636872, 75375912
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#pragma once

#include <winsock2.h>

#define _HTTP_SUPPORT
#define _UDP_SUPPORT
//@启用枚举前缀

#ifdef _WIN64
//@复制文件 @当前模块路径 "x64\HPSocket_U.dll"
//@lib "x64\HPSocket_U.lib"
#else
//@复制文件 @当前模块路径 "x86\HPSocket_U.dll"
//@lib "x86\HPSocket_U.lib"
#endif

/*@声明
//模拟HP双接口继承;  typedef DualInterface<IHttpRequester, ITcpClient> IHttpClient;
//@分组{ HTTP
//@别名 HP_HTTP客户端
class IHttpClient : public IHttpRequester,  ITcpClient
{
};
//@别名 HP_HTTP服务器
class IHttpServer : public IComplexHttpResponder,  ITcpServer
{
};

class ITcpPackServer : public IPackSocket,  ITcpServer
{
};

class ITcpPackAgent : public IPackSocket,  ITcpAgent
{
};

class ITcpPackClient : public IPackSocket,  ITcpClient
{
};

//------------

class ITcpPullServer : public IPullSocket,  ITcpServer
{
};

class ITcpPullAgent : public IPullSocket,  ITcpAgent
{
};

class ITcpPullClient : public IPullClient,  ITcpClient
{
};



//@分组{ 对象创建API

//@备注 创建 ITcpServer 对象
ITcpServer* HP_Create_TcpServer(ITcpServerListener* pListener);
//@备注 创建 ITcpAgent 对象
ITcpAgent* HP_Create_TcpAgent(ITcpAgentListener* pListener);
//@备注 创建 ITcpClient 对象
ITcpClient* HP_Create_TcpClient(ITcpClientListener* pListener);
//@备注 创建 ITcpPullServer 对象
ITcpPullServer* HP_Create_TcpPullServer(ITcpServerListener* pListener);
//@备注 创建 ITcpPullAgent 对象
ITcpPullAgent* HP_Create_TcpPullAgent(ITcpAgentListener* pListener);
//@备注 创建 ITcpPullClient 对象
ITcpPullClient* HP_Create_TcpPullClient(ITcpClientListener* pListener);
//@备注 创建 ITcpPackServer 对象
ITcpPackServer* HP_Create_TcpPackServer(ITcpServerListener* pListener);
//@备注 创建 ITcpPackAgent 对象
ITcpPackAgent* HP_Create_TcpPackAgent(ITcpAgentListener* pListener);
//@备注 创建 ITcpPackClient 对象
ITcpPackClient* HP_Create_TcpPackClient(ITcpClientListener* pListener);

//@备注 销毁 ITcpServer 对象
void HP_Destroy_TcpServer(ITcpServer* pServer);
//@备注 销毁 ITcpAgent 对象
void HP_Destroy_TcpAgent(ITcpAgent* pAgent);
//@备注 销毁 ITcpClient 对象
void HP_Destroy_TcpClient(ITcpClient* pClient);
//@备注 销毁 ITcpPullServer 对象
void HP_Destroy_TcpPullServer(ITcpPullServer* pServer);
//@备注 销毁 ITcpPullAgent 对象
void HP_Destroy_TcpPullAgent(ITcpPullAgent* pAgent);
//@备注 销毁 ITcpPullClient 对象
void HP_Destroy_TcpPullClient(ITcpPullClient* pClient);
//@备注 销毁 ITcpPackServer 对象
void HP_Destroy_TcpPackServer(ITcpPackServer* pServer);
//@备注 销毁 ITcpPackAgent 对象
void HP_Destroy_TcpPackAgent(ITcpPackAgent* pAgent);
//@备注 销毁 ITcpPackClient 对象
void HP_Destroy_TcpPackClient(ITcpPackClient* pClient);


//@备注 创建 IUdpServer 对象
IUdpServer* HP_Create_UdpServer(IUdpServerListener* pListener);
//@备注 创建 IUdpClient 对象
IUdpClient* HP_Create_UdpClient(IUdpClientListener* pListener);
//@备注 创建 IUdpCast 对象
IUdpCast* HP_Create_UdpCast(IUdpCastListener* pListener);
//@备注 创建 IUdpNode 对象
IUdpNode* HP_Create_UdpNode(IUdpNodeListener* pListener);
//@备注 创建 IUdpArqServer 对象
IUdpArqServer* HP_Create_UdpArqServer(IUdpServerListener* pListener);
//@备注 创建 IUdpArqClient 对象
IUdpArqClient* HP_Create_UdpArqClient(IUdpClientListener* pListener);

//@备注 销毁 IUdpServer 对象
void HP_Destroy_UdpServer(IUdpServer* pServer);
//@备注 销毁 IUdpClient 对象
void HP_Destroy_UdpClient(IUdpClient* pClient);
//@备注 销毁 IUdpCast 对象
void HP_Destroy_UdpCast(IUdpCast* pCast);
//@备注 销毁 IUdpNode 对象
void HP_Destroy_UdpNode(IUdpNode* pNode);
//@备注 销毁 IUdpArqServer 对象
void HP_Destroy_UdpArqServer(IUdpArqServer* pServer);
//@备注 销毁 IUdpArqClient 对象
void HP_Destroy_UdpArqClient(IUdpArqClient* pClient);

//@备注 创建 IHttpServer 对象
IHttpServer* HP_Create_HttpServer(IHttpServerListener* pListener);
//@备注 创建 IHttpAgent 对象
IHttpAgent* HP_Create_HttpAgent(IHttpAgentListener* pListener);
//@备注 创建 IHttpClient 对象
IHttpClient* HP_Create_HttpClient(IHttpClientListener* pListener);
//@备注 创建 IHttpSyncClient 对象
IHttpSyncClient* HP_Create_HttpSyncClient(IHttpClientListener* pListener = nullptr);

//@备注 销毁 IHttpServer 对象
void HP_Destroy_HttpServer(IHttpServer* pServer);
//@备注 销毁 IHttpAgent 对象
void HP_Destroy_HttpAgent(IHttpAgent* pAgent);
//@备注 销毁 IHttpClient 对象
void HP_Destroy_HttpClient(IHttpClient* pClient);
//@备注 销毁 IHttpSyncClient 对象
void HP_Destroy_HttpSyncClient(IHttpSyncClient* pClient);

//@分组}

//@分组}
*/

//#include "HPTypeDef.h" 将内容复制过来, 以便炫彩解析类型

/* HP-Socket 版本号 */
//@备注 HP-Socket 版本号
//@别名 HP主版本号
#define HP_VERSION_MAJOR		5	// 主版本号
//@别名 HP子版本号
#define HP_VERSION_MINOR		8	// 子版本号
//@别名 HP修正版本号
#define HP_VERSION_REVISE		6	// 修正版本号
//@别名 HP构建编号
#define HP_VERSION_BUILD		3	// 构建编号

//#define _UDP_DISABLED				// 禁用 UDP
//#define _SSL_DISABLED				// 禁用 SSL
//#define _HTTP_DISABLED			// 禁用 HTTP
//#define _ZLIB_DISABLED			// 禁用 ZLIB
//#define _BROTLI_DISABLED			// 禁用 BROTLI

/* 是否启用 UDP，如果定义了 _UDP_DISABLED 则禁用（默认：启用） */
#if !defined(_UDP_DISABLED)
#ifndef _UDP_SUPPORT
#define _UDP_SUPPORT
#endif
#endif

/* 是否启用 SSL，如果定义了 _SSL_DISABLED 则禁用（默认：启用） */
#if !defined(_SSL_DISABLED)
#ifndef _SSL_SUPPORT
#define _SSL_SUPPORT
#endif
#endif

/* 是否启用 HTTP，如果定义了 _HTTP_DISABLED 则禁用（默认：启用） */
#if !defined(_HTTP_DISABLED)
#ifndef _HTTP_SUPPORT
#define _HTTP_SUPPORT
#endif
#endif

/* 是否启用 ZLIB，如果定义了 _ZLIB_DISABLED 则禁用（默认：启用） */
#if !defined(_ZLIB_DISABLED)
#ifndef _ZLIB_SUPPORT
#define _ZLIB_SUPPORT
#endif
#endif

/* 是否启用 BROTLI，如果定义了 _BROTLI_DISABLED 则禁用（默认：启用） */
#if !defined(_BROTLI_DISABLED)
#ifndef _BROTLI_SUPPORT
#define _BROTLI_SUPPORT
#endif
#endif

/**************************************************/
/********** imports / exports HPSocket4C **********/

#ifdef HPSOCKET_STATIC_LIB
#define HPSOCKET_API		EXTERN_C
#else
#ifdef HPSOCKET_EXPORTS
#define HPSOCKET_API	EXTERN_C __declspec(dllexport)
#else
#define HPSOCKET_API	EXTERN_C __declspec(dllimport)
#endif
#endif

#define __HP_CALL				__stdcall

/*****************************************************************************************************************************************************/
/**************************************************************** Base Type Definitions **************************************************************/
/*****************************************************************************************************************************************************/

typedef const BYTE* LPCBYTE, PCBYTE;
typedef ULONG_PTR		TID, THR_ID, NTHR_ID, PID, PRO_ID;

/************************************************************************
名称：连接 ID 数据类型
描述：应用程序可以把 CONNID 定义为自身需要的类型（如：ULONG / ULONGLONG）
************************************************************************/
typedef ULONG_PTR		CONNID, HP_CONNID;

/************************************************************************
名称：通信组件服务状态
描述：应用程序可以通过通信组件的 GetState() 方法获取组件当前服务状态
************************************************************************/
//@别名 HP服务状态
typedef enum EnServiceState
{
	//@别名 正在启动
	SS_STARTING = 0,	// 正在启动
	//@别名 已经启动
	SS_STARTED = 1,	// 已经启动
	//@别名 正在停止
	SS_STOPPING = 2,	// 正在停止
	//@别名 已经停止
	SS_STOPPED = 3,	// 已经停止
} En_HP_ServiceState;

/************************************************************************
名称：Socket 操作类型
描述：应用程序的 OnClose() 事件中通过该参数标识是哪种操作导致的错误
************************************************************************/
//@别名 HP操作类型
typedef enum EnSocketOperation
{
	//@别名 未知操作
	SO_UNKNOWN = 0,	// Unknown
	//@别名 接受请求
	SO_ACCEPT = 1,	// Acccept
	//@别名 连接请求
	SO_CONNECT = 2,	// Connect
	//@别名 发送请求
	SO_SEND = 3,	// Send
	//@别名 接收请求
	SO_RECEIVE = 4,	// Receive
	//@别名 主动断开
	SO_CLOSE = 5,	// Close
} En_HP_SocketOperation;

/************************************************************************
名称：事件处理结果
描述：事件的返回值，不同的返回值会影响通信组件的后续行为
************************************************************************/
//@别名 HP事件处理结果
typedef enum EnHandleResult
{
	//@别名  成功
	HR_OK = 0,	// 成功
	//@别名  忽略
	HR_IGNORE = 1,	// 忽略
	//@别名  错误
	HR_ERROR = 2,	// 错误
} En_HP_HandleResult;

/************************************************************************
名称：数据抓取结果
描述：数据抓取操作的返回值
************************************************************************/
//@别名 HP数据抓取结果
typedef enum EnFetchResult
{
	//@别名 成功
	FR_OK = 0,	// 成功
	//@别名 长度过大
	FR_LENGTH_TOO_LONG = 1,	// 抓取长度过大
	//@别名 找不到
	FR_DATA_NOT_FOUND = 2,	// 找不到 ConnID 对应的数据
} En_HP_FetchResult;

/************************************************************************
名称：数据发送策略
描述：Server 组件和 Agent 组件的数据发送策略

* 打包发送策略（默认）	：尽量把多个发送操作的数据组合在一起发送，增加传输效率
* 安全发送策略			：尽量把多个发送操作的数据组合在一起发送，并控制传输速度，避免缓冲区溢出
* 直接发送策略			：对每一个发送操作都直接投递，适用于负载不高但要求实时性较高的场合
************************************************************************/
//@别名 HP数据发送策略
typedef enum EnSendPolicy
{
	//@别名 打包模式
	SP_PACK = 0,	// 打包模式（默认）
	//@别名 安全模式
	SP_SAFE = 1,	// 安全模式
	//@别名 直接模式
	SP_DIRECT = 2,	// 直接模式
} En_HP_SendPolicy;

/************************************************************************
名称：OnSend 事件同步策略
描述：Server 组件和 Agent 组件的 OnSend 事件同步策略

* 不同步（默认）	：不同步 OnSend 事件，可能同时触发 OnReceive 和 OnClose 事件
* 同步 OnClose	：只同步 OnClose 事件，可能同时触发 OnReceive 事件
* 同步 OnReceive	：（只用于 TCP 组件）同步 OnReceive 和 OnClose 事件，不可能同时触发 OnReceive 或 OnClose 事件
************************************************************************/
//@别名 HP发送事件同步策略
typedef enum EnOnSendSyncPolicy
{
	//@别名 不同步
	OSSP_NONE = 0,	// 不同步（默认）
	//@别名 同步关闭
	OSSP_CLOSE = 1,	// 同步 OnClose
	//@别名 同步接收
	OSSP_RECEIVE = 2,	// 同步 OnReceive（只用于 TCP 组件）	
} En_HP_OnSendSyncPolicy;

/************************************************************************
名称：地址重用选项
描述：通信组件底层 socket 的地址重用选项
************************************************************************/
//@别名 HP地址重用选项
typedef enum EnReuseAddressPolicy
{
	//@别名 不
	RAP_NONE = 0,	// 不重用
	//@别名 仅地址
	RAP_ADDR_ONLY = 1,	// 仅重用地址
	//@别名 地址和端口
	RAP_ADDR_AND_PORT = 2,	// 重用地址和端口
} En_HP_ReuseAddressPolicy;

/************************************************************************
名称：操作结果代码
描述：组件 Start() / Stop() 方法执行失败时，可通过 GetLastError() 获取错误代码
************************************************************************/
//@别名 HP操作代码
typedef enum EnSocketError
{
	//@别名 成功
	SE_OK = NO_ERROR,	// 成功
	//@别名 当前状态不允许操作
	SE_ILLEGAL_STATE = 1,		// 当前状态不允许操作
	//@别名 非法参数
	SE_INVALID_PARAM = 2,		// 非法参数
	//@别名 创建SOCKET失败
	SE_SOCKET_CREATE = 3,		// 创建 SOCKET 失败
	//@别名 绑定SOCKET失败
	SE_SOCKET_BIND = 4,		// 绑定 SOCKET 失败
	//@别名 设置SOCKET失败
	SE_SOCKET_PREPARE = 5,		// 设置 SOCKET 失败
	//@别名 监听SOCKET失败
	SE_SOCKET_LISTEN = 6,		// 监听 SOCKET 失败
	//@别名 创建完成端口失败
	SE_CP_CREATE = 7,		// 创建完成端口失败
	//@别名 创建工作线程失败
	SE_WORKER_THREAD_CREATE = 8,		// 创建工作线程失败
	//@别名 创建监测线程失败
	SE_DETECT_THREAD_CREATE = 9,		// 创建监测线程失败
	//@别名 绑定完成端口失败
	SE_SOCKE_ATTACH_TO_CP = 10,		// 绑定完成端口失败
	//@别名 连接服务器失败
	SE_CONNECT_SERVER = 11,		// 连接服务器失败
	//@别名 网络错误
	SE_NETWORK = 12,		// 网络错误
	//@别名 数据处理错误
	SE_DATA_PROC = 13,		// 数据处理错误
	//@别名 数据发送失败
	SE_DATA_SEND = 14,		// 数据发送失败

	/***** SSL Socket 扩展操作结果代码 *****/
	//@别名 环境未就绪
	SE_SSL_ENV_NOT_READY = 101,		// SSL 环境未就绪
} En_HP_SocketError;

/************************************************************************
名称：播送模式
描述：UDP 组件的播送模式（组播或广播）
************************************************************************/
//@别名 HPUDP播送模式
typedef enum EnCastMode
{
	//@别名 单播
	CM_UNICAST = -1,	// 单播
	//@别名 组播
	CM_MULTICAST = 0,	// 组播
	//@别名 广播
	CM_BROADCAST = 1,	// 广播
} En_HP_CastMode;

/************************************************************************
名称：IP 地址类型
描述：IP 地址类型枚举值
************************************************************************/
//@别名 HPIP地址类型
typedef enum EnIPAddrType
{
	//@别名 所有
	IPT_ALL = 0,		// 所有
	//@别名 IPv4
	IPT_IPV4 = 1,		// IPv4
	//@别名 IPv6
	IPT_IPV6 = 2,		// IPv6
} En_HP_IPAddrType;

/************************************************************************
名称：IP 地址条目结构体
描述：IP 地址的地址簇/地址值结构体
************************************************************************/
//@别名 HP_IP地址结构
typedef struct TIPAddr
{
	//@别名 IP地址类型
	En_HP_IPAddrType type;
	//@别名 添加值
	LPCTSTR			 address;
} *LPTIPAddr, HP_TIPAddr, * HP_LPTIPAddr;

/************************************************************************
名称：拒绝策略
描述：调用被拒绝后的处理策略
************************************************************************/
//@别名 HP拒绝策略
typedef enum EnRejectedPolicy
{
	//@别名 失败
	TRP_CALL_FAIL = 0,	// 立刻返回失败
	//@别名 等待
	TRP_WAIT_FOR = 1,	// 等待（直到成功、超时或线程池关闭等原因导致失败）
	//@别名 执行
	TRP_CALLER_RUN = 2,	// 调用者线程直接执行
} En_HP_RejectedPolicy;

/************************************************************************
名称：任务缓冲区类型
描述：TSockeTask 对象创建和销毁时，根据不同类型的缓冲区类型作不同的处理
************************************************************************/
//@别名 HP任务缓冲区类型
typedef enum EnTaskBufferType
{
	//@别名 深拷贝
	TBT_COPY = 0,	// 深拷贝
	//@别名 浅拷贝
	TBT_REFER = 1,	// 浅拷贝
	//@别名 附属
	TBT_ATTACH = 2,	// 附属（不负责创建，但负责销毁）
} En_HP_TaskBufferType;

/************************************************************************
名称：任务处理函数
描述：任务处理入口函数
参数：pvArg -- 自定义参数
返回值：（无）
************************************************************************/
//@备注 任务处理入口函数
//@参数 pTask -- 自定义参数
//@别名 HP任务处理函数(自定义参数)
typedef VOID(__HP_CALL* Fn_TaskProc)(PVOID pvArg);
typedef Fn_TaskProc	HP_Fn_TaskProc;

struct TSocketTask;

/************************************************************************
名称：Socket 任务处理函数
描述：Socket 任务处理入口函数
参数：pTask -- Socket 任务结构体指针
返回值：（无）
************************************************************************/
//@备注 Socket 任务处理入口函数
//@参数 pTask -- HP任务结构体指针
//@别名 HP_Socket任务处理函数(HP任务结构指针)
typedef VOID(__HP_CALL* Fn_SocketTaskProc)(struct TSocketTask* pTask);
typedef Fn_SocketTaskProc	HP_Fn_SocketTaskProc;

/************************************************************************
名称：Socket 任务结构体
描述：封装 Socket 任务相关数据结构
************************************************************************/
//@别名 HP任务结构
typedef struct TSocketTask
{
	//@别名 任务处理函数
	HP_Fn_SocketTaskProc	fn;			// 任务处理函数
	//@别名 发起对象
	PVOID					sender;		// 发起对象
	//@别名 连接ID
	CONNID					connID;		// 连接 ID
	//@别名 数据缓冲区
	LPCBYTE					buf;		// 数据缓冲区
	//@别名 数据缓冲区长度
	INT						bufLen;		// 数据缓冲区长度
	//@别名 缓冲区类型
	En_HP_TaskBufferType	bufType;	// 缓冲区类型
	//@别名 自定义参数1
	WPARAM					wparam;		// 自定义参数
	//@别名 自定义参数2
	LPARAM					lparam;		// 自定义参数
} *LPTSocketTask, HP_TSocketTask, * HP_LPTSocketTask;

/************************************************************************
名称：获取 HPSocket 版本号
描述：版本号（4 个字节分别为：主版本号，子版本号，修正版本号，构建编号）
************************************************************************/
//@备注 版本号（4 个字节分别为：主版本号，子版本号，修正版本号，构建编号）
//@别名 HP取版本号()
inline DWORD GetHPSocketVersion()
{
	return (HP_VERSION_MAJOR << 24) | (HP_VERSION_MINOR << 16) | (HP_VERSION_REVISE << 8) | HP_VERSION_BUILD;
}

/*****************************************************************************************************************************************************/
/**************************************************************** SSL Type Definitions ***************************************************************/
/*****************************************************************************************************************************************************/

#ifdef _SSL_SUPPORT

/************************************************************************
名称：SSL 工作模式
描述：标识 SSL 的工作模式，客户端模式或服务端模式
************************************************************************/
//@别名 HPSSL工作模式
typedef enum EnSSLSessionMode
{
	//@别名 客户端
	SSL_SM_CLIENT = 0,	// 客户端模式
	//@别名 服务端
	SSL_SM_SERVER = 1,	// 服务端模式
} En_HP_SSLSessionMode;

/************************************************************************
名称：SSL 验证模式
描述：SSL 验证模式选项，SSL_VM_PEER 可以和后面两个选项组合一起
************************************************************************/
//@别名 HPSSL验证模式
typedef enum EnSSLVerifyMode
{
	//@别名 无
	SSL_VM_NONE = 0x00,	// SSL_VERIFY_NONE
	//@别名 单项
	SSL_VM_PEER = 0x01,	// SSL_VERIFY_PEER
	//@别名 双向
	SSL_VM_FAIL_IF_NO_PEER_CERT = 0x02,	// SSL_VERIFY_FAIL_IF_NO_PEER_CERT
	//@别名 单次
	SSL_VM_CLIENT_ONCE = 0x04,	// SSL_VERIFY_CLIENT_ONCE
} En_HP_SSLVerifyMode;

//@备注 SSL Session 信息类型
//描述：用于 GetSSLSessionInfo()，标识输出的 Session 信息类型
//@别名 HPSSL信息类型
typedef enum EnSSLSessionInfo
{
	SSL_SSI_MIN = 0,	// 
	SSL_SSI_CTX = 0,	// SSL CTX				（输出类型：SSL_CTX*）
	SSL_SSI_CTX_METHOD = 1,	// SSL CTX Mehtod		（输出类型：SSL_METHOD*）
	SSL_SSI_CTX_CIPHERS = 2,	// SSL CTX Ciphers		（输出类型：STACK_OF(SSL_CIPHER)*）
	SSL_SSI_CTX_CERT_STORE = 3,	// SSL CTX Cert Store	（输出类型：X509_STORE*）
	SSL_SSI_SERVER_NAME_TYPE = 4,	// Server Name Type		（输出类型：int）
	SSL_SSI_SERVER_NAME = 5,	// Server Name			（输出类型：LPCSTR）
	SSL_SSI_VERSION = 6,	// SSL Version			（输出类型：LPCSTR）
	SSL_SSI_METHOD = 7,	// SSL Method			（输出类型：SSL_METHOD*）
	SSL_SSI_CERT = 8,	// SSL Cert				（输出类型：X509*）
	SSL_SSI_PKEY = 9,	// SSL Private Key		（输出类型：EVP_PKEY*）
	SSL_SSI_CURRENT_CIPHER = 10,	// SSL Current Cipher	（输出类型：SSL_CIPHER*）
	SSL_SSI_CIPHERS = 11,	// SSL Available Ciphers（输出类型：STACK_OF(SSL_CIPHER)*）
	SSL_SSI_CLIENT_CIPHERS = 12,	// SSL Client Ciphers	（输出类型：STACK_OF(SSL_CIPHER)*）
	SSL_SSI_PEER_CERT = 13,	// SSL Peer Cert		（输出类型：X509*）
	SSL_SSI_PEER_CERT_CHAIN = 14,	// SSL Peer Cert Chain	（输出类型：STACK_OF(X509)*）
	SSL_SSI_VERIFIED_CHAIN = 15,	// SSL Verified Chain	（输出类型：STACK_OF(X509)*）
	SSL_SSI_MAX = 15,	// 
} En_HP_SSLSessionInfo;

/*@声明
@别名 HP_SNI服务名称回调函数(服务器名称,回调上下文)
@备注 根据服务器名称选择 SSL 证书
@参数	lpszServerName -- 服务器名称（域名）
@参数	pContext -- 回调上下文
@返回	0	 -- 成功，使用默认 SSL 证书索引
//		正数	 -- 成功，使用返回值对应的 SNI 主机证书索引
//		负数	 -- 失败，中断 SSL 握手

*/
typedef int (__HP_CALL* Fn_SNI_ServerNameCallback)(LPCTSTR lpszServerName, PVOID pContext);
typedef Fn_SNI_ServerNameCallback	HP_Fn_SNI_ServerNameCallback;

#endif

/*****************************************************************************************************************************************************/
/**************************************************************** HTTP Type Definitions **************************************************************/
/*****************************************************************************************************************************************************/

#ifdef _HTTP_SUPPORT

/************************************************************************
名称：HTTP 版本
描述：低字节：主版本号，高字节：次版本号
************************************************************************/
//@别名 HPHTTP协议版本
typedef enum EnHttpVersion
{
	//@别名 HTTP1_0
	HV_1_0 = MAKEWORD(1, 0),	// HTTP/1.0
	//@别名 HTTP1_1
	HV_1_1 = MAKEWORD(1, 1)	// HTTP/1.1
} En_HP_HttpVersion;

/************************************************************************
名称：URL 域
描述：HTTP 请求行中 URL 段位的域定义
************************************************************************/
//@别名 HPURL字段
typedef enum EnHttpUrlField
{
	//@别名 概要
	HUF_SCHEMA = 0,	// Schema
	//@别名 主机
	HUF_HOST = 1,	// Host
	//@别名 端口
	HUF_PORT = 2,	// Port
	//@别名 路径
	HUF_PATH = 3,	// Path
	//@别名 查询
	HUF_QUERY = 4,	// Query String
	//@别名 片段
	HUF_FRAGMENT = 5,	// Fragment
	//@别名 用户信息
	HUF_USERINFO = 6,	// User Info
	//@别名 字段数量
	HUF_MAX = 7,	// (Field Count)
} En_HP_HttpUrlField;

/************************************************************************
名称：HTTP 解析结果标识
描述：指示 HTTP 解析器是否继续执行解析操作
************************************************************************/
//@别名 HPHTTP解析结果
typedef enum EnHttpParseResult
{
	//@别名 成功
	HPR_OK = 0,	// 解析成功
	//@别名 跳过当前请求
	HPR_SKIP_BODY = 1,	// 跳过当前请求 BODY（仅用于 OnHeadersComplete 事件）
	//@别名 升级协议
	HPR_UPGRADE = 2,	// 升级协议（仅用于 OnHeadersComplete 事件）
	//@别名 错误
	HPR_ERROR = -1,	// 解析错误，终止解析，断开连接
} En_HP_HttpParseResult;

//@备注 HTTP 协议升级类型
//描述：标识 HTTP 升级为哪种协议
//@别名 HPHTTP协议类型
typedef enum EnHttpUpgradeType
{
	//@别名 没有升级
	HUT_NONE = 0,	// 没有升级
	//@别名 WebSocket
	HUT_WEB_SOCKET = 1,	// WebSocket
	//@别名 HTTP隧道
	HUT_HTTP_TUNNEL = 2,	// HTTP 隧道
	//@别名 未知类型
	HUT_UNKNOWN = -1,	// 未知类型
} En_HP_HttpUpgradeType;

/************************************************************************
名称：HTTP 状态码
描述：HTTP 标准状态码
************************************************************************/
//@别名 HPHTTP状态码
typedef enum EnHttpStatusCode
{
	//@别名 继续
	HSC_CONTINUE = 100,
	//@别名 交换协议
	HSC_SWITCHING_PROTOCOLS = 101,
	//@别名 正在处理
	HSC_PROCESSING = 102,

	//@别名 成功
	HSC_OK = 200,
	//@别名 已创建
	HSC_CREATED = 201,
	//@别名 已同意
	HSC_ACCEPTED = 202,
	//@别名 非权威信息
	HSC_NON_AUTHORITATIVE_INFORMATION = 203,
	//@别名 空内容
	HSC_NO_CONTENT = 204,
	//@别名 重置内容
	HSC_RESET_CONTENT = 205,
	//@别名 分块内容
	HSC_PARTIAL_CONTENT = 206,
	//@别名 多状态
	HSC_MULTI_STATUS = 207,
	//@别名 已报告
	HSC_ALREADY_REPORTED = 208,
	//@别名 已响应
	HSC_IM_USED = 226,

	//@别名 多重选择
	HSC_MULTIPLE_CHOICES = 300,
	//@别名 永久重定向
	HSC_MOVED_PERMANENTLY = 301,
	//@别名 临时重定向
	HSC_MOVED_TEMPORARILY = 302,
	//@别名 重定向
	HSC_SEE_OTHER = 303,
	//@别名 缓存
	HSC_NOT_MODIFIED = 304,
	//@别名 使用代理
	HSC_USE_PROXY = 305,
	//@别名 选择代理
	HSC_SWITCH_PROXY = 306,
	//@别名 临时重定向_
	HSC_TEMPORARY_REDIRECT = 307,
	//@别名 永久重定向_
	HSC_PERMANENT_REDIRECT = 308,

	//@别名 请求无效
	HSC_BAD_REQUEST = 400,
	//@别名 未授权
	HSC_UNAUTHORIZED = 401,
	//@别名 需要付款
	HSC_PAYMENT_REQUIRED = 402,
	//@别名 拒绝访问
	HSC_FORBIDDEN = 403,
	//@别名 未找到资源
	HSC_NOT_FOUND = 404,
	//@别名 不允许的请求方法
	HSC_METHOD_NOT_ALLOWED = 405,
	//@别名 不允许的请求
	HSC_NOT_ACCEPTABLE = 406,
	//@别名 需要代理服务器认证身份
	HSC_PROXY_AUTHENTICATION_REQUIRED = 407,
	//@别名 请求超时
	HSC_REQUEST_TIMEOUT = 408,
	//@别名 资源状态冲突
	HSC_CONFLICT = 409,
	//@别名 资源过期
	HSC_GONE = 410,
	//@别名 需要表明长度
	HSC_LENGTH_REQUIRED = 411,
	//@别名 未满足先决条件
	HSC_PRECONDITION_FAILED = 412,
	//@别名 请求体太大
	HSC_REQUEST_ENTITY_TOO_LARGE = 413,
	//@别名 请求域太长
	HSC_REQUEST_URI_TOO_LONG = 414,
	//@别名 不支持的媒体类型
	HSC_UNSUPPORTED_MEDIA_TYPE = 415,
	//@别名 不满足请求范围
	HSC_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
	//@别名 预期结果失败
	HSC_EXPECTATION_FAILED = 417,
	//@别名 错误的请求
	HSC_MISDIRECTED_REQUEST = 421,
	//@别名 无法遵循的语义错误
	HSC_UNPROCESSABLE_ENTITY = 422,
	//@别名 已锁定
	HSC_LOCKED = 423,
	//@别名 失败的依赖项
	HSC_FAILED_DEPENDENCY = 424,
	//@别名 无序收集
	HSC_UNORDERED_COLLECTION = 425,
	//@别名 需要升级协议
	HSC_UPGRADE_REQUIRED = 426,
	//@别名 需要条件请求
	HSC_PRECONDITION_REQUIRED = 428,
	//@别名 请求过多
	HSC_TOO_MANY_REQUESTS = 429,
	//@别名 请求头过大
	HSC_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
	//@别名 因法律不可用
	HSC_UNAVAILABLE_FOR_LEGAL_REASONS = 451,
	//@别名 使用重试
	HSC_RETRY_WITH = 449,

	//@别名 服务器内部错误
	HSC_INTERNAL_SERVER_ERROR = 500,
	//@别名 尚未实现
	HSC_NOT_IMPLEMENTED = 501,
	//@别名 错误网关
	HSC_BAD_GATEWAY = 502,
	//@别名 服务不可用
	HSC_SERVICE_UNAVAILABLE = 503,
	//@别名 网关超时
	HSC_GATEWAY_TIMEOUT = 504,
	//@别名 HTTP版本不支持
	HSC_HTTP_VERSION_NOT_SUPPORTED = 505,
	//@别名 服务器存在内部配置错误
	HSC_VARIANT_ALSO_NEGOTIATES = 506,
	//@别名 服务器无法存储
	HSC_INSUFFICIENT_STORAGE = 507,
	//@别名 发现无穷循环
	HSC_LOOP_DETECTED = 508,
	//@别名 流量超限
	HSC_BANDWIDTH_LIMIT_EXCEEDED = 509,
	//@别名 未扩展
	HSC_NOT_EXTENDED = 510,
	//@别名 需要网络验证
	HSC_NETWORK_AUTHENTICATION_REQUIRED = 511,

	//@别名 无法解析响应头
	HSC_UNPARSEABLE_RESPONSE_HEADERS = 600
} En_HP_HttpStatusCode;

/************************************************************************
名称：Name/Value 结构体
描述：字符串名值对结构体
************************************************************************/
//@别名 HP请求头结构
typedef struct TNVPair
{
	//@别名 名称
	LPCSTR name;
	//@别名 值
	LPCSTR value;
}	HP_TNVPair,
TParam, HP_TParam, * LPPARAM, * HP_LPPARAM,
THeader, HP_THeader, * LPHEADER, * HP_LPHEADER,
TCookie, HP_TCookie, * LPCOOKIE, * HP_LPCOOKIE;

#endif

/*@声明
@备注 回调处理过程中产生的数据输出
@参数 pData		-- 数据缓冲区
@参数 iLength		-- 数据长度
@参数 pContext	-- 回调上下文

@返回	TRUE	-- 成功
//		FALSE	-- 失败
@别名 HP数据回调函数(数据缓冲区,数据长度,回调上下文)
*/
typedef BOOL(__HP_CALL* Fn_DataCallback)(const BYTE* pData, int iLength, PVOID pContext);
typedef Fn_DataCallback	Fn_CompressDataCallback;
typedef Fn_DataCallback	Fn_DecompressDataCallback;
typedef Fn_DataCallback	HP_Fn_DataCallback;
typedef Fn_DataCallback	HP_Fn_CompressDataCallback;
typedef Fn_DataCallback	HP_Fn_DecompressDataCallback;

//---------------end HPTypeDef.h--------------------------------------------

/*****************************************************************************************************************************************************/
/***************************************************************** TCP/UDP Interfaces ****************************************************************/
/*****************************************************************************************************************************************************/

/************************************************************************
名称：双接口模版类
描述：定义双接口转换方法
************************************************************************/
//@隐藏{

#if FALSE

#define __DUAL_VPTR_GAP__	sizeof(PVOID)

class __IFakeDualInterface__
{
public:
	virtual ~__IFakeDualInterface__() {}
};

template<class F, class S> class DualInterface : public F, private __IFakeDualInterface__, public S

#else

#define __DUAL_VPTR_GAP__	0

template<class F, class S> class DualInterface : public F, public S

#endif

{
public:

	/* this 转换为 F* */
	inline static F* ToF(DualInterface* pThis)
	{
		return (F*)(pThis);
	}

	/* F* 转换为 this */
	inline static DualInterface* FromF(F* pF)
	{
		return (DualInterface*)(pF);
	}

	/* this 转换为 S* */
	inline static S* ToS(DualInterface* pThis)
	{
		return (S*)(F2S(ToF(pThis)));
	}

	/* S* 转换为 this */
	inline static DualInterface* FromS(S* pS)
	{
		return FromF(S2F(pS));
	}

	/* S* 转换为 F* */
	inline static F* S2F(S* pS)
	{
		return (F*)((char*)pS - (sizeof(F) + __DUAL_VPTR_GAP__));
	}

	/* F* 转换为 S* */
	inline static S* F2S(F* pF)
	{
		return (S*)((char*)pF + (sizeof(F) + __DUAL_VPTR_GAP__));
	}

public:
	virtual ~DualInterface() {}
};

//@隐藏}

/*@声明
@别名 HP_复合模型
@备注 定义复合 Socket 组件的所有操作方法和属性访问方法，复合 Socket 组件同时管理多个 Socket 连接
*/
class IComplexSocket
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 关闭()
	@备注 关闭通信组件，关闭完成后断开所有连接并释放所有资源
				
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Stop	()																		= 0;

	/*@声明
	@别名 发送数据(连接ID,发送缓冲区,发送缓冲区长度,发送缓冲区指针偏移量)
	@备注 向指定连接发送数据
		
	@参数		dwConnID	-- 连接 ID
	@参数		pBuffer		-- 发送缓冲区
	@参数		iLength		-- 发送缓冲区长度
	@参数		iOffset		-- 发送缓冲区指针偏移量
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Send	(CONNID dwConnID, const BYTE* pBuffer, int iLength, int iOffset = 0)	= 0;

	/*@声明
	@别名 发送数据组(连接ID,发送缓冲区数组,发送缓冲区数目)
	@备注 向指定连接发送多组数据
	//		TCP - 顺序发送所有数据包 
	//		UDP - 把所有数据包组合成一个数据包发送（数据包的总长度不能大于设置的 UDP 包最大长度） 
		
	@参数		dwConnID	-- 连接 ID
	@参数		pBuffers	-- 发送缓冲区数组
	@参数		iCount		-- 发送缓冲区数目
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendPackets(CONNID dwConnID, const WSABUF pBuffers[], int iCount)	= 0;

	/*@声明
	@别名 置暂停接收(连接ID,是否暂停)
	@备注 暂停/恢复某个连接的数据接收工作
		
	@参数		dwConnID	-- 连接 ID
	@参数		bPause		-- TRUE - 暂停, FALSE - 恢复
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败
	*/
	virtual BOOL PauseReceive(CONNID dwConnID, BOOL bPause = TRUE)					= 0;

	/*@声明
	@别名 断开连接(连接ID,是否断开)
	@备注 断开某个连接
		
	@参数		dwConnID	-- 连接 ID
	@参数		bForce		-- 是否强制断开连接
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败
	*/
	virtual BOOL Disconnect(CONNID dwConnID, BOOL bForce = TRUE)					= 0;

	/*@声明
	@别名 断开超时连接(时长,是否断开)
	@备注 断开超过指定时长的连接
	
	@参数		dwPeriod	-- 时长（毫秒）
	@参数		bForce		-- 是否强制断开连接
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败
	*/
	virtual BOOL DisconnectLongConnections(DWORD dwPeriod, BOOL bForce = TRUE)		= 0;

	/*@声明
	@别名 断开静默连接(时长,是否断开)
	@备注 断开超过指定时长的静默连接
	
	@参数		dwPeriod	-- 时长（毫秒）
	@参数		bForce		-- 是否强制断开连接
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败
	*/
	virtual BOOL DisconnectSilenceConnections(DWORD dwPeriod, BOOL bForce = TRUE)	= 0;

	/*@声明
	@别名 等待(超时时间)
	@备注 等待通信组件停止运行

	@参数		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Wait(DWORD dwMilliseconds = INFINITE)								= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/*@声明
	@别名 置附加数据(连接ID,数据)
	@备注 是否为连接绑定附加数据或者绑定什么样的数据，均由应用程序自身决定

	@参数		dwConnID	-- 连接 ID
	@参数		pv			-- 数据
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败（无效的连接 ID）
	*/
	virtual BOOL SetConnectionExtra		(CONNID dwConnID, PVOID pExtra)			= 0;

	/*@声明
	@别名 取附加数据(连接ID,数据指针)
	@备注 是否为连接绑定附加数据或者绑定什么样的数据，均由应用程序自身决定

	@参数		dwConnID	-- 连接 ID
	@参数		ppv			-- 数据指针
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败（无效的连接 ID）
	*/
	virtual BOOL GetConnectionExtra		(CONNID dwConnID, PVOID* ppExtra)		= 0;

	/* 检测是否为安全连接（SSL/HTTPS） */
	//@别名 是否为安全连接()
	virtual BOOL IsSecure				()										= 0;
	/* 检查通信组件是否已启动 */
	//@别名 是否启动()
	virtual BOOL HasStarted				()										= 0;
	/* 查看通信组件当前状态 */
	//@别名 当前状态()
	virtual EnServiceState GetState		()										= 0;
	/* 获取连接数 */
	//@别名 取连接数()
	virtual DWORD GetConnectionCount	()										= 0;
	/* 获取所有连接的 CONNID */
	//@别名 取连接CONNID()
	virtual BOOL GetAllConnectionIDs	(CONNID pIDs[], DWORD& dwCount)			= 0;
	/* 获取某个连接时长（毫秒） */
	//@别名 取连接时长()
	virtual BOOL GetConnectPeriod		(CONNID dwConnID, DWORD& dwPeriod)		= 0;
	/* 获取某个连接静默时间（毫秒） */
	//@别名 取静默时间()
	virtual BOOL GetSilencePeriod		(CONNID dwConnID, DWORD& dwPeriod)		= 0;
	/* 获取某个连接的本地地址信息 */
	//@别名 取本地地址信息()
	virtual BOOL GetLocalAddress		(CONNID dwConnID, TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
	/* 获取某个连接的远程地址信息 */
	//@别名 取远程地址信息()
	virtual BOOL GetRemoteAddress		(CONNID dwConnID, TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
	/* 获取最近一次失败操作的错误代码 */
	//@别名 取错误代码()
	virtual EnSocketError GetLastError	()										= 0;
	/* 获取最近一次失败操作的错误描述 */
	//@别名 取错误描述()
	virtual LPCTSTR GetLastErrorDesc	()										= 0;
	/* 获取连接中未发出数据的长度 */
	//@别名 取未发出数据长度()
	virtual BOOL GetPendingDataLength	(CONNID dwConnID, int& iPending)		= 0;
	/* 获取连接的数据接收状态 */
	//@别名 取数据接收状态()
	virtual BOOL IsPauseReceive			(CONNID dwConnID, BOOL& bPaused)		= 0;
	/* 检测是否有效连接 */
	//@别名 是否有效连接()
	virtual BOOL IsConnected			(CONNID dwConnID)						= 0;

	/* 设置地址重用选项 */
	//@别名 置地址重用选项(选项)
	virtual void SetReuseAddressPolicy(EnReuseAddressPolicy enReusePolicy)		= 0;
	/* 设置数据发送策略 */
	//@别名 置数据发送策略(发送策略)
	virtual void SetSendPolicy				(EnSendPolicy enSendPolicy)			= 0;
	//@备注 设置 OnSend 事件同步策略（默认：OSSP_NONE，不同步） 
	//@别名 置发送事件同步策略(策略)
	virtual void SetOnSendSyncPolicy		(EnOnSendSyncPolicy enSyncPolicy)	= 0;
	//@备注 设置最大连接数（组件会根据设置值预分配内存，因此需要根据实际情况设置，不宜过大）
	//@别名 置最大连接数(数量)
	virtual void SetMaxConnectionCount		(DWORD dwMaxConnectionCount)		= 0;
	//@备注 设置 Socket 缓存对象锁定时间（毫秒，在锁定期间该 Socket 缓存对象不能被获取使用） 
	//@别名 置缓存对象锁定时间(时间)
	virtual void SetFreeSocketObjLockTime	(DWORD dwFreeSocketObjLockTime)		= 0;
	//@备注 设置 Socket 缓存池大小（通常设置为平均并发连接数的 1/3 - 1/2） 
	//@别名 置缓存池大小(大小)
	virtual void SetFreeSocketObjPool		(DWORD dwFreeSocketObjPool)			= 0;
	//@备注 设置内存块缓存池大小（通常设置为 Socket 缓存池大小的 2 - 3 倍） 
	//@别名 置内存块缓存池大小(大小)
	virtual void SetFreeBufferObjPool		(DWORD dwFreeBufferObjPool)			= 0;
	//@备注 设置 Socket 缓存池回收阀值（通常设置为 Socket 缓存池大小的 3 倍） 
	//@别名 置缓存池回收阀值(阀值)
	virtual void SetFreeSocketObjHold		(DWORD dwFreeSocketObjHold)			= 0;
	//@备注 设置内存块缓存池回收阀值 
	//@别名 置内存块缓存池回收阀值(阀值)
	virtual void SetFreeBufferObjHold		(DWORD dwFreeBufferObjHold)			= 0;
	//@备注 设置工作线程数量（通常设置为 2 * CPU + 2） 
	//@别名 置工作线程数量(数量)
	virtual void SetWorkerThreadCount		(DWORD dwWorkerThreadCount)			= 0;
	//@备注 设置是否标记静默时间（设置为 TRUE 时 DisconnectSilenceConnections() 和 GetSilencePeriod() 才有效，默认：TRUE） 
	//@别名 置是否标记静默时间(是否标记)
	virtual void SetMarkSilence				(BOOL bMarkSilence)					= 0;

	/* 获取地址重用选项 */
	//@别名 取地址重用选项()
	virtual EnReuseAddressPolicy GetReuseAddressPolicy	()	= 0;
	/* 获取数据发送策略 */
	//@别名 取数据发送策略()
	virtual EnSendPolicy GetSendPolicy					()	= 0;
	/* 获取 OnSend 事件同步策略 */
	//@别名 取发送事件同步策略()
	virtual EnOnSendSyncPolicy GetOnSendSyncPolicy		()	= 0;
	/* 获取最大连接数 */
	//@别名 取最大连接数()
	virtual DWORD GetMaxConnectionCount					()	= 0;
	/* 获取 Socket 缓存对象锁定时间 */
	//@别名 取缓存对象锁定时间()
	virtual DWORD GetFreeSocketObjLockTime				()	= 0;
	/* 获取 Socket 缓存池大小 */
	//@别名 取缓存池大小()
	virtual DWORD GetFreeSocketObjPool					()	= 0;
	/* 获取内存块缓存池大小 */
	//@别名 取内存块缓存池大小()
	virtual DWORD GetFreeBufferObjPool					()	= 0;
	/* 获取 Socket 缓存池回收阀值 */
	//@别名 取缓存池回收阀值()
	virtual DWORD GetFreeSocketObjHold					()	= 0;
	/* 获取内存块缓存池回收阀值 */
	//@别名 取内存块缓存池回收阀值()
	virtual DWORD GetFreeBufferObjHold					()	= 0;
	/* 获取工作线程数量 */
	//@别名 取工作线程数量()
	virtual DWORD GetWorkerThreadCount					()	= 0;
	/* 检测是否标记静默时间 */
	//@别名 是否标记静默时间()
	virtual BOOL IsMarkSilence							()	= 0;

public:
	virtual ~IComplexSocket() {}
};

/************************************************************************
名称：通信服务端组件接口
描述：定义通信服务端组件的所有操作方法和属性访问方法
************************************************************************/
//@分组{ HP辅助类
//@别名 HP服务器
class IServer : public IComplexSocket
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 启动(监听地址,监听端口)
	@备注 启动服务端通信组件，启动完成后可开始接收客户端连接并收发数据

	@参数		lpszBindAddress	-- 监听地址
	@参数		usPort			-- 监听端口
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Start	(LPCTSTR lpszBindAddress, USHORT usPort)							= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 获取监听 Socket 的地址信息 */
	//@别名 取监听地址信息()
	virtual BOOL GetListenAddress(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
};
//@分组}
/************************************************************************
名称：TCP 通信服务端组件接口
描述：定义 TCP 通信服务端组件的所有操作方法和属性访问方法
************************************************************************/
//@分组{ HP服务端
//@别名 HP_TCP服务器
class ITcpServer : public IServer
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 发送小文件(连接ID,文件路径,头部附加数据,尾部附加数据)
	@备注 向指定连接发送 4096 KB 以下的小文件

	@参数		dwConnID		-- 连接 ID
	@参数		lpszFileName	-- 文件路径
	@参数		pHead			-- 头部附加数据
	@参数		pTail			-- 尾部附加数据
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendSmallFile(CONNID dwConnID, LPCTSTR lpszFileName, const LPWSABUF pHead = nullptr, const LPWSABUF pTail = nullptr)	= 0;

#ifdef _SSL_SUPPORT
	/*@声明
	@别名 初始化SSL环境(验证模式,证书文件,私钥文件,私钥密码,CA证书,回调函数指针)
	@备注 SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败

	@参数		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	@参数		lpszPemCertFile			-- 证书文件
	@参数		lpszPemKeyFile			-- 私钥文件
	@参数		lpszKeyPassword			-- 私钥密码（没有密码则为空）
	@参数		lpszCAPemCertFileOrPath	-- CA 证书文件或目录（单向验证或客户端可选）
	@参数		fnServerNameCallback	-- SNI 回调函数指针（可选，如果为 nullptr 则使用 SNI 默认回调函数）

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL SetupSSLContext(int iVerifyMode = SSL_VM_NONE, LPCTSTR lpszPemCertFile = nullptr, LPCTSTR lpszPemKeyFile = nullptr, LPCTSTR lpszKeyPassword = nullptr, LPCTSTR lpszCAPemCertFileOrPath = nullptr, Fn_SNI_ServerNameCallback fnServerNameCallback = nullptr)	= 0;

	/*@声明
	@别名 初始化SSL环境_内存(验证模式,证书内容,私钥内容,私钥密码,CA证书,回调函数指针)
	@备注 SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败

	@参数		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	@参数		lpszPemCert				-- 证书内容
	@参数		lpszPemKey				-- 私钥内容
	@参数		lpszKeyPassword			-- 私钥密码（没有密码则为空）
	@参数		lpszCAPemCert			-- CA 证书内容（单向验证或客户端可选）
	@参数		fnServerNameCallback	-- SNI 回调函数指针（可选，如果为 nullptr 则使用 SNI 默认回调函数）

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL SetupSSLContextByMemory(int iVerifyMode = SSL_VM_NONE, LPCSTR lpszPemCert = nullptr, LPCSTR lpszPemKey = nullptr, LPCSTR lpszKeyPassword = nullptr, LPCSTR lpszCAPemCert = nullptr, Fn_SNI_ServerNameCallback fnServerNameCallback = nullptr)				= 0;

	/*@声明
	@别名 添加SNI主机证书(验证模式,证书文件,私钥文件,私钥密码,CA证书)
	@备注 SSL 服务端在 SetupSSLContext() 成功后可以调用本方法增加多个 SNI 主机证书

	@参数		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	@参数		lpszPemCertFile			-- 证书文件
	@参数		lpszPemKeyFile			-- 私钥文件
	@参数		lpszKeyPassword			-- 私钥密码（没有密码则为空）
	@参数		lpszCAPemCertFileOrPath	-- CA 证书文件或目录（单向验证可选）

	@返回	正数		-- 成功，并返回 SNI 主机证书对应的索引，该索引用于在 SNI 回调函数中定位 SNI 主机
	//		负数		-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual int AddSSLContext(int iVerifyMode = SSL_VM_NONE, LPCTSTR lpszPemCertFile = nullptr, LPCTSTR lpszPemKeyFile = nullptr, LPCTSTR lpszKeyPassword = nullptr, LPCTSTR lpszCAPemCertFileOrPath = nullptr)																= 0;

	/*@声明
	@别名 添加SNI主机证书_内存(验证模式,证书内容,私钥内容,私钥密码,CA证书)
	@备注 SSL 服务端在 SetupSSLContext() 成功后可以调用本方法增加多个 SNI 主机证书

	@参数		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	@参数		lpszPemCert				-- 证书内容
	@参数		lpszPemKey				-- 私钥内容
	@参数		lpszKeyPassword			-- 私钥密码（没有密码则为空）
	@参数		lpszCAPemCert			-- CA 证书内容（单向验证可选）

	@返回	正数		-- 成功，并返回 SNI 主机证书对应的索引，该索引用于在 SNI 回调函数中定位 SNI 主机
	//		负数		-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual int AddSSLContextByMemory(int iVerifyMode = SSL_VM_NONE, LPCSTR lpszPemCert = nullptr, LPCSTR lpszPemKey = nullptr, LPCSTR lpszKeyPassword = nullptr, LPCSTR lpszCAPemCert = nullptr)																			= 0;

	/*@声明
	@别名 绑定SNI主机域名(主机域名,SNI证书)
	@备注 SSL 服务端在 AddSSLContext() 成功后可以调用本方法绑定主机域名到 SNI 主机证书

	@参数		lpszServerName		-- 主机域名
	@参数		iContextIndex		-- SNI 主机证书对应的索引

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL BindSSLServerName(LPCTSTR lpszServerName, int iContextIndex)	= 0;

	/*@声明
	@别名 清理SSL环境()
	@备注 清理通信组件 SSL 运行环境，回收 SSL 相关内存
	//		1、通信组件析构时会自动调用本方法
	//		2、当要重新设置通信组件 SSL 环境参数时，需要先调用本方法清理原先的环境参数

	@参数	无

	@返回 无
	*/
	virtual void CleanupSSLContext()											= 0;

	/*@声明
	@别名 启动SSL握手()
	@备注 当通信组件设置为非自动握手时，需要调用本方法启动 SSL 握手

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL StartSSLHandShake(CONNID dwConnID)						= 0;

#endif

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置 Accept 预投递数量（根据负载调整设置，Accept 预投递数量越大则支持的并发连接请求越多）
	//@别名 置预投递数量(数量)
	//@参数 dwAcceptSocketCount  --数量
	virtual void SetAcceptSocketCount	(DWORD dwAcceptSocketCount)		= 0;
	//@备注 设置通信数据缓冲区大小（根据平均通信数据包大小调整设置，通常设置为 1024 的倍数）
	//@别名 置通信数据缓冲区尺寸(尺寸)
	//@参数 dwSocketBufferSize  --尺寸
	virtual void SetSocketBufferSize	(DWORD dwSocketBufferSize)		= 0;
	//@备注 设置监听 Socket 的等候队列大小（根据并发连接数量调整设置）
	//@别名 置监听等候队列大小(大小)
	//@参数 dwSocketListenQueue  --大小
	virtual void SetSocketListenQueue	(DWORD dwSocketListenQueue)		= 0;
	//@备注 设置正常心跳包间隔（毫秒，0 则不发送心跳包，默认：60 * 1000）
	//@别名 置正常心跳包间隔(间隔)
	//@参数 dwKeepAliveTime  --间隔
	virtual void SetKeepAliveTime		(DWORD dwKeepAliveTime)			= 0;
	//@备注 设置异常心跳包间隔（毫秒，0 不发送心跳包，，默认：20 * 1000，如果超过若干次 [默认：WinXP 5 次, Win7 10 次] 检测不到心跳确认包则认为已断线）
	//@别名 置异常心跳包间隔(间隔)
	//@参数 dwKeepAliveInterval  --间隔
	virtual void SetKeepAliveInterval	(DWORD dwKeepAliveInterval)		= 0;
	//@备注 设置是否开启 nodelay 模式（默认：FALSE，不开启）
	//@别名 置是否开启(是否开启)
	//@参数 bNoDelay  --是否开启
	virtual void SetNoDelay				(BOOL bNoDelay)					= 0;

	/* 获取 Accept 预投递数量 */
	//@别名 取预投递数量()
	virtual DWORD GetAcceptSocketCount	()	= 0;
	/* 获取通信数据缓冲区大小 */
	//@别名 取通信数据缓冲区尺寸()
	virtual DWORD GetSocketBufferSize	()	= 0;
	/* 获取监听 Socket 的等候队列大小 */
	//@别名 取监听等候队列大小()
	virtual DWORD GetSocketListenQueue	()	= 0;
	/* 获取正常心跳包间隔 */
	//@别名 取正常心跳包间隔()
	virtual DWORD GetKeepAliveTime		()	= 0;
	/* 获取异常心跳包间隔 */
	//@别名 取异常心跳包间隔()
	virtual DWORD GetKeepAliveInterval	()	= 0;
	/* 检查是否开启 nodelay 模式 */
	//@别名 取是否开启()
	//@返回 开启=真,否则=假
	virtual BOOL IsNoDelay				()	= 0;
	
#ifdef _SSL_SUPPORT
	//@备注 设置通信组件握手方式（默认：TRUE，自动握手） */
	//@别名 置握手方式(方式)
	//@参数 bAutoHandShake  --方式
	virtual void SetSSLAutoHandShake(BOOL bAutoHandShake)				= 0;
	/* 获取通信组件握手方式 */
	//@别名 取握手方式()
	//@返回 是否握手
	virtual BOOL IsSSLAutoHandShake()									= 0;

	/* 设置 SSL 加密算法列表 */
	//@别名 置加密算法列表(算法列表)
	//@参数 lpszCipherList  --算法列表
	virtual void SetSSLCipherList(LPCTSTR lpszCipherList)				= 0;
	/* 获取 SSL 加密算法列表 */
	//@别名 取加密算法列表()
	//@返回 算法列表
	virtual LPCTSTR GetSSLCipherList()									= 0;

	/*@声明
	@别名 取SSL信息()
	@备注 获取指定类型的 SSL Session 信息（输出类型参考：EnSSLSessionInfo）

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL GetSSLSessionInfo(CONNID dwConnID, EnSSLSessionInfo enInfo, LPVOID* lppInfo)	= 0;
#endif

};
//@分组}
#ifdef _UDP_SUPPORT
//@分组{ UDP
/************************************************************************
名称：UDP 通信服务端组件接口
描述：定义 UDP 通信服务端组件的所有操作方法和属性访问方法
************************************************************************/
//@别名 HP_UDP服务器
class IUdpServer : public IServer
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节） 
	//@别名 置数据报文最大长度(最大长度)
	virtual void SetMaxDatagramSize		(DWORD dwMaxDatagramSize)	= 0;
	/* 获取数据报文最大长度 */
	//@别名 取数据报文最大长度()
	virtual DWORD GetMaxDatagramSize	()							= 0;

	//@备注 设置 Receive 预投递数量（根据负载调整设置，Receive 预投递数量越大则丢包概率越小） 
	//@别名 置预投递数量(数量)
	virtual void SetPostReceiveCount	(DWORD dwPostReceiveCount)	= 0;
	/* 获取 Receive 预投递数量 */
	//@别名 取预投递数量()
	virtual DWORD GetPostReceiveCount	()							= 0;

	//@备注 设置监测包尝试次数（0 则不发送监测跳包，如果超过最大尝试次数则认为已断线） 
	//@别名 置监测包尝试次数(次数)
	virtual void SetDetectAttempts		(DWORD dwDetectAttempts)	= 0;
	//@备注 设置监测包发送间隔（毫秒，0 不发送监测包） 
	//@别名 置监测包发送间隔(间隔)
	virtual void SetDetectInterval		(DWORD dwDetectInterval)	= 0;
	/* 获取心跳检查次数 */
	//@别名 取心跳次数()
	virtual DWORD GetDetectAttempts		()							= 0;
	/* 获取心跳检查间隔 */
	//@别名 取心跳间隔()
	virtual DWORD GetDetectInterval		()							= 0;
};

/************************************************************************
名称：Server/Agent ARQ 模型组件接口
描述：定义 Server/Agent 组件的 ARQ 模型组件的所有操作方法
************************************************************************/
//@别名 HP_ARQ模型
class IArqSocket
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置是否开启 nodelay 模式（默认：FALSE，不开启）
	//@别名 置是否开启模式(是否开启)
	virtual void SetNoDelay				(BOOL bNoDelay)				= 0;
	//@备注 设置是否关闭拥塞控制（默认：FALSE，不关闭）
	//@别名 置是否关闭拥塞控制(是否关闭)
	virtual void SetTurnoffCongestCtrl	(BOOL bTurnOff)				= 0;
	//@备注 设置数据刷新间隔（毫秒，默认：60）
	//@别名 置数据刷新间隔(间隔)
	virtual void SetFlushInterval		(DWORD dwFlushInterval)		= 0;
	//@备注 设置快速重传 ACK 跨越次数（默认：0，关闭快速重传）
	//@别名 置快速重传跨越次数(次数)
	virtual void SetResendByAcks		(DWORD dwResendByAcks)		= 0;
	//@备注 设置发送窗口大小（数据包数量，默认：128）
	//@别名 置发送窗口大小(大小)
	virtual void SetSendWndSize			(DWORD dwSendWndSize)		= 0;
	//@备注 设置接收窗口大小（数据包数量，默认：512）
	//@别名 置接收窗口大小(大小)
	virtual void SetRecvWndSize			(DWORD dwRecvWndSize)		= 0;
	//@备注 设置最小重传超时时间（毫秒，默认：30）
	//@别名 置最小重传超时时间(时间)
	virtual void SetMinRto				(DWORD dwMinRto)			= 0;
	//@备注 设置快速握手次数限制（默认：5，如果为 0 则不限制）
	//@别名 置快速握手次数限制(次数限制)
	virtual void SetFastLimit			(DWORD dwFastLimit)			= 0;
	//@备注 设置最大传输单元（默认：0，与 SetMaxDatagramSize() 一致）
	//@别名 置最大传输单元(传输单元)
	virtual void SetMaxTransUnit		(DWORD dwMaxTransUnit)		= 0;
	//@备注 设置最大数据包大小（默认：4096）
	//@别名 置最大数据包大小(大小)
	virtual void SetMaxMessageSize		(DWORD dwMaxMessageSize)	= 0;
	//@备注 设置握手超时时间（毫秒，默认：5000）
	//@别名 置握手超时时间(时间)
	virtual void SetHandShakeTimeout	(DWORD dwHandShakeTimeout)	= 0;

	//@备注 检测是否开启 nodelay 模式
	//@别名 是否开启模式()
	virtual BOOL IsNoDelay				()							= 0;
	/* 检测是否关闭拥塞控制 */
	//@别名 是否关闭拥塞控制()
	virtual BOOL IsTurnoffCongestCtrl	()							= 0;
	/* 获取数据刷新间隔 */
	//@别名 取数据刷新间隔()
	virtual DWORD GetFlushInterval		()							= 0;
	/* 获取快速重传 ACK 跨越次数 */
	//@别名 取快速重传跨越次数()
	virtual DWORD GetResendByAcks		()							= 0;
	/* 获取发送窗口大小 */
	//@别名 取发送窗口大小()
	virtual DWORD GetSendWndSize		()							= 0;
	/* 获取接收窗口大小 */
	//@别名 取接收窗口大小()
	virtual DWORD GetRecvWndSize		()							= 0;
	/* 获取最小重传超时时间 */
	//@别名 取最小重传超时时间()
	virtual DWORD GetMinRto				()							= 0;
	/* 获取快速握手次数限制 */
	//@别名 取快速握手次数限制()
	virtual DWORD GetFastLimit			()							= 0;
	/* 获取最大传输单元 */
	//@别名 取最大传输单元()
	virtual DWORD GetMaxTransUnit		()							= 0;
	/* 获取最大数据包大小 */
	//@别名 取最大数据包大小()
	virtual DWORD GetMaxMessageSize		()							= 0;
	/* 获取握手超时时间 */
	//@别名 取握手超时时间()
	virtual DWORD GetHandShakeTimeout	()							= 0;

	/* 获取等待发送包数量 */
	//@别名 取等待发送包数量()
	virtual BOOL GetWaitingSendMessageCount	(CONNID dwConnID, int& iCount)	= 0;

public:
	virtual ~IArqSocket() {}
};

/************************************************************************
名称：UDP ARQ 通信服务端组件接口
描述：继承了 ARQ 和 Server 接口
************************************************************************/
typedef	DualInterface<IArqSocket, IUdpServer>	IUdpArqServer;
//@分组}
#endif

//@分组{ HP辅助类
//@备注 通信代理组件接口
//		描述：定义通信代理组件的所有操作方法和属性访问方法，代理组件本质是一个同时连接多个服务器的客户端组件
//@别名 HP代理
class IAgent : public IComplexSocket
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 启动(绑定地址,是否采用异步)
	@备注 启动通信代理组件，启动完成后可开始连接远程服务器

	@参数		lpszBindAddress	-- 绑定地址（默认：nullptr，绑定任意地址）
	@参数		bAsyncConnect	-- 是否采用异步 Connect
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Start	(LPCTSTR lpszBindAddress = nullptr, BOOL bAsyncConnect = TRUE)				= 0;

	/*@声明
	@别名 连接服务器(服务端地址,服务端端口,连接ID,连接附加数据,本地端口,本地地址)
	@备注 连接服务器，连接成功后 IAgentListener 会接收到 OnConnect() / OnHandShake() 事件

	@参数		lpszRemoteAddress	-- 服务端地址
	@参数		usPort				-- 服务端端口
	@参数		pdwConnID			-- 连接 ID（默认：nullptr，不获取连接 ID）
	@参数		pExtra				-- 连接附加数据（默认：nullptr）
	@参数		usLocalPort			-- 本地端口（默认：0）
	@参数		lpszLocalAddress	-- 本地地址（默认：nullptr，使用 Start() 方法中绑定的地址）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Connect(LPCTSTR lpszRemoteAddress, USHORT usPort, CONNID* pdwConnID = nullptr, PVOID pExtra = nullptr, USHORT usLocalPort = 0, LPCTSTR lpszLocalAddress = nullptr)	= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 获取某个连接的远程主机信息 */
	//@别名 取远程主机信息()
	virtual BOOL GetRemoteHost	(CONNID dwConnID, TCHAR lpszHost[], int& iHostLen, USHORT& usPort)	= 0;

};

/************************************************************************
名称：TCP 通信代理组件接口
描述：定义 TCP 通信代理组件的所有操作方法和属性访问方法
************************************************************************/
//@别名 HP_TCP代理
class ITcpAgent : public IAgent
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 发送小文件(连接ID,文件路径,头部附加数据,尾部附加数据)
	@备注 向指定连接发送 4096 KB 以下的小文件

	@参数		dwConnID		-- 连接 ID
	@参数		lpszFileName	-- 文件路径
	@参数		pHead			-- 头部附加数据
	@参数		pTail			-- 尾部附加数据
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendSmallFile(CONNID dwConnID, LPCTSTR lpszFileName, const LPWSABUF pHead = nullptr, const LPWSABUF pTail = nullptr)	= 0;

#ifdef _SSL_SUPPORT
	/*@声明
	@别名 初始化SSL环境(验证模式,证书文件,私钥文件,私钥密码,CA证书)
	@备注 SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败

	@参数		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	@参数		lpszPemCertFile			-- 证书文件（客户端可选）
	@参数		lpszPemKeyFile			-- 私钥文件（客户端可选）
	@参数		lpszKeyPassword			-- 私钥密码（没有密码则为空）
	@参数		lpszCAPemCertFileOrPath	-- CA 证书文件或目录（单向验证或客户端可选）

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL SetupSSLContext(int iVerifyMode = SSL_VM_NONE, LPCTSTR lpszPemCertFile = nullptr, LPCTSTR lpszPemKeyFile = nullptr, LPCTSTR lpszKeyPassword = nullptr, LPCTSTR lpszCAPemCertFileOrPath = nullptr)	= 0;

	/*@声明
	@别名 初始化SSL环境_内存(验证模式,证书内容,私钥内容,私钥密码,CA证书)
	@备注 SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败

	@参数		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	@参数		lpszPemCert				-- 证书内容
	@参数		lpszPemKey				-- 私钥内容
	@参数		lpszKeyPassword			-- 私钥密码（没有密码则为空）
	@参数		lpszCAPemCert			-- CA 证书内容（单向验证或客户端可选）

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL SetupSSLContextByMemory(int iVerifyMode = SSL_VM_NONE, LPCSTR lpszPemCert = nullptr, LPCSTR lpszPemKey = nullptr, LPCSTR lpszKeyPassword = nullptr, LPCSTR lpszCAPemCert = nullptr)					= 0;

	/*@声明
	@别名 清理SSL环境()
	@备注 清理通信组件 SSL 运行环境，回收 SSL 相关内存
	//		1、通信组件析构时会自动调用本方法
	//		2、当要重新设置通信组件 SSL 环境参数时，需要先调用本方法清理原先的环境参数

	@参数	无
	
	@返回 无
	*/
	virtual void CleanupSSLContext()									= 0;

	/*@声明
	@别名 启动SSL握手()
	@备注 当通信组件设置为非自动握手时，需要调用本方法启动 SSL 握手

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL StartSSLHandShake(CONNID dwConnID)						= 0;

#endif

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置通信数据缓冲区大小（根据平均通信数据包大小调整设置，通常设置为 1024 的倍数）
	//@别名 置通信数据缓冲区大小(大小)
	virtual void SetSocketBufferSize	(DWORD dwSocketBufferSize)		= 0;
	//@备注 设置正常心跳包间隔（毫秒，0 则不发送心跳包，默认：60 * 1000）
	//@别名 置正常心跳包间隔(间隔)
	virtual void SetKeepAliveTime		(DWORD dwKeepAliveTime)			= 0;
	//@备注 设置异常心跳包间隔（毫秒，0 不发送心跳包，，默认：20 * 1000，如果超过若干次 [默认：WinXP 5 次, Win7 10 次] 检测不到心跳确认包则认为已断线）
	//@别名 置异常心跳包间隔(间隔)
	virtual void SetKeepAliveInterval	(DWORD dwKeepAliveInterval)		= 0;
	//@备注 设置是否开启 nodelay 模式（默认：FALSE，不开启）
	//@别名 置是否开启模式(模式)
	virtual void SetNoDelay				(BOOL bNoDelay)					= 0;

	/* 获取通信数据缓冲区大小 */
	//@别名 取通信数据缓冲区大小()
	virtual DWORD GetSocketBufferSize	()	= 0;
	/* 获取正常心跳包间隔 */
	//@别名 取正常心跳包间隔()
	virtual DWORD GetKeepAliveTime		()	= 0;
	/* 获取异常心跳包间隔 */
	//@别名 取异常心跳包间隔()
	virtual DWORD GetKeepAliveInterval	()	= 0;
	/* 检查是否开启 nodelay 模式 */
	//@别名 是否开启模式()
	virtual BOOL IsNoDelay				()	= 0;

#ifdef _SSL_SUPPORT
	//@备注 设置通信组件握手方式（默认：TRUE，自动握手）
	//@别名 置通信组件握手方式(握手方式)
	virtual void SetSSLAutoHandShake(BOOL bAutoHandShake)				= 0;
	/* 获取通信组件握手方式 */
	//@别名 取通信组件握手方式()
	virtual BOOL IsSSLAutoHandShake()									= 0;

	/* 设置 SSL 加密算法列表 */
	//@别名 置加密算法列表(算法列表)
	virtual void SetSSLCipherList(LPCTSTR lpszCipherList)				= 0;
	/* 获取 SSL 加密算法列表 */
	//@别名 取加密算法列表()
	virtual LPCTSTR GetSSLCipherList()									= 0;

	/*@声明
	@别名 取SSL信息()
	@备注 获取指定类型的 SSL Session 信息（输出类型参考：EnSSLSessionInfo）

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL GetSSLSessionInfo(CONNID dwConnID, EnSSLSessionInfo enInfo, LPVOID* lppInfo)	= 0;
#endif

};
//@分组}
//@分组{ HP客户端
//@备注 名称：通信客户端组件接口
//描述：定义通信客户端组件的所有操作方法和属性访问方法
//@别名 HP客户端
class IClient
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@备注 启动客户端通信组件并连接服务端，启动完成后可开始收发数据
			
	@参数		lpszRemoteAddress	-- 服务端地址
	@参数		usPort				-- 服务端端口
	@参数		bAsyncConnect		-- 是否采用异步 Connect
	@参数		lpszBindAddress		-- 绑定地址（默认：nullptr，TcpClient/UdpClient -> 不执行绑定操作，UdpCast 绑定 -> 任意地址）
	@参数		usLocalPort			-- 本地端口（默认：0）
	@返回 	TRUE	-- 成功
	//			FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	@别名 启动(服务端地址, 服务端端口, 是否采用异步, 绑定地址, 本地端口)
	*/
	virtual BOOL Start(LPCTSTR lpszRemoteAddress, USHORT usPort, BOOL bAsyncConnect = TRUE, LPCTSTR lpszBindAddress = nullptr, USHORT usLocalPort = 0)	= 0;

	/*@声明
	@备注 名称：关闭通信组件
	//描述：关闭客户端通信组件，关闭完成后断开与服务端的连接并释放所有资源

	@返回	TRUE	-- 成功
	//			FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	@别名  关闭()
	*/
	virtual BOOL Stop()																		= 0;

	/*@声明
	@备注 名称：发送数据
	//描述：向服务端发送数据
		
	@参数		pBuffer		-- 发送缓冲区
	@参数		iLength		-- 发送缓冲区长度
	@参数		iOffset		-- 发送缓冲区指针偏移量
	@返回	TRUE	-- 成功
	//			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	@别名  发送数据(发送缓冲区, 发送缓冲区长度, 发送缓冲区指针偏移量)
	*/
	virtual BOOL Send	(const BYTE* pBuffer, int iLength, int iOffset = 0)						= 0;

	/*@声明
	@备注 向服务端发送多组数据
	//		TCP - 顺序发送所有数据包 
	//		UDP - 把所有数据包组合成一个数据包发送（数据包的总长度不能大于设置的 UDP 包最大长度） 
			
	@参数		pBuffers	-- 发送缓冲区数组
	@参数		iCount		-- 发送缓冲区数目
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	@别名  发送数据组(发送缓冲区数组, 发送缓冲区数目)
	*/
	virtual BOOL SendPackets(const WSABUF pBuffers[], int iCount)								= 0;

	/*@声明
	@备注 暂停/恢复某个连接的数据接收工作		
	@参数		bPause	-- 是否暂停（默认：真，提供真则暂停数据接收,提供假则恢复该连接的数据接收）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败
	@别名  置暂停接收(是否暂停)
	*/
	virtual BOOL PauseReceive(BOOL bPause = TRUE)												= 0;

	/*@声明
	@备注 等待通信组件停止运行

	@参数		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
	@返回	TRUE	-- 成功
	//			FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	@别名  等待(超时时间)
	*/
	virtual BOOL Wait(DWORD dwMilliseconds = INFINITE)											= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置连接的附加数据
	//@参数 pExtra --数据
	//@别名 置附加数据(数据)
	virtual void SetExtra					(PVOID pExtra)										= 0;

	//@备注 获取连接的附加数据
	//@返回 数据
	//@别名 取附加数据()
	virtual PVOID GetExtra					()													= 0;
	//@备注 检测当前是否为安全连接(SSL/HTTPS)
	//@返回 为安全连接返回真,反之假.
	//@别名 是否为安全连接()
	virtual BOOL IsSecure					()													= 0;
	//@备注 检查通信组件是否已启动
	//@返回 已成功启动返回真,反之假.
	//@别名 是否已启动()
	virtual BOOL HasStarted					()													= 0;
	//@备注 查看通信组件当前状态
	//@返回 EnServiceState相关常量
	//@别名 取当前状态()
	virtual EnServiceState	GetState		()													= 0;
	//@备注 获取最近一次失败操作的错误代码
	//@返回 EnSocketError相关常量
	//@别名 取错误代码()
	virtual EnSocketError	GetLastError	()													= 0;
	//@备注 获取最近一次失败操作的错误描述
	//@返回 当前错误描述文本
	//@别名 取错误描述()
	virtual LPCTSTR			GetLastErrorDesc()													= 0;
	//@备注 获取该组件对象的连接ID
	//@返回 ID
	//@别名 取连接ID()
	virtual CONNID			GetConnectionID	()													= 0;
	//@备注 获取 Client Socket 的地址信息
	//@参数 TCHAR --缓冲区
	//@参数 int --长度
	//@参数 USHORT --地址(返回)
	//@返回 返回真则表示成功,反之假
	//@别名 取本地地址(缓冲区,长度,地址)
		virtual BOOL GetLocalAddress		(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
	//@备注 获取连接的远程主机信息
	//@参数 TCHAR --缓冲区
	//@参数 int --长度
	//@参数 USHORT --地址(返回)
	//@返回 返回真则表示成功,反之假
	//@别名 取远程地址(缓冲区,长度,地址)
	virtual BOOL GetRemoteHost			(TCHAR lpszHost[], int& iHostLen, USHORT& usPort)		= 0;
	//@备注 获取连接中未发出数据的长度
	//@参数 int --长度(返回)
	//@返回 返回真则表示正在接收,反之假
	//@别名 取未发出数据长度(长度)
	virtual BOOL GetPendingDataLength	(int& iPending)											= 0;
	//@备注 获取连接的数据接收状态
	//@参数 BOOL --是否接收(返回)
	//@返回 返回真则表示正在接收,反之假
	//@别名 取接收状态(是否接收)
	virtual BOOL IsPauseReceive			(BOOL& bPaused)											= 0;
	//@备注 检测是否有效连接
	//@返回 有效返回真,反之假
	//@别名 取连接状态()
	virtual BOOL IsConnected			()														= 0;

	//@备注 设置地址重用选项
	//@参数 enReusePolicy --HP地址重用选项
	//@别名 置地址重用策略(HP地址重用选项)
	virtual void SetReuseAddressPolicy(EnReuseAddressPolicy enReusePolicy)						= 0;
	//@备注 设置内存块缓存池大小
	//	请注意,本属性值不宜过大,请参考以下通信模型缓存池尺寸:
	// 普通 5  - 10.
	// PULL 10 - 20.
	//@参数 dwFreeBufferPoolSize --尺寸
	//@别名 置内存缓存池尺寸()
	virtual void SetFreeBufferPoolSize		(DWORD dwFreeBufferPoolSize)						= 0;
	//@备注 设置内存块缓存池回收阀值
	//	请注意,本值不宜过大,否则将会造成过大的内存占用,一般可设置为"内存缓存池尺寸"的3倍
	//@参数 dwFreeBufferPoolHold --阀值
	//@别名 置内存池回收阈值()
	virtual void SetFreeBufferPoolHold		(DWORD dwFreeBufferPoolHold)						= 0;

	//@备注 获取地址重用选项
	//@返回 EnReuseAddressPolicy --HP地址重用选项 常量
	//@别名 取地址重用策略()
	virtual EnReuseAddressPolicy GetReuseAddressPolicy	()										= 0;
	//@备注 取得当前客户端内存缓存池尺寸
	//@返回 尺寸大小
	//@别名 取内存缓存池尺寸()
	virtual DWORD GetFreeBufferPoolSize					()										= 0;
	//@备注 获取内存块缓存池回收阀值
	//@返回 阈值
	//@别名 取内存池回收阈值()
	virtual DWORD GetFreeBufferPoolHold					()										= 0;

public:
	virtual ~IClient() {}
};

//@备注 名称：通信客户端组件接口
//描述：定义 TCP 通信客户端组件的所有操作方法和属性访问方法
//@别名 HP_TCP客户端
class ITcpClient : public IClient
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@备注 向服务端发送 4096 KB 以下的小文件	
	@参数	lpszFileName	-- 文件路径
	@参数	pHead			-- 头部附加数据
	@参数	pTail			-- 尾部附加数据
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	@别名 发送小文件(文件路径, 头部附加数据, 尾部附加数据)
	*/
	virtual BOOL SendSmallFile(LPCTSTR lpszFileName, const LPWSABUF pHead = nullptr, const LPWSABUF pTail = nullptr)	= 0;

#ifdef _SSL_SUPPORT
	/*@声明
	@备注 名称：初始化通信组件 SSL 环境参数
	//	SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败
	@参数		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	@参数		lpszPemCertFile			-- 证书文件（客户端可选）
	@参数		lpszPemKeyFile			-- 私钥文件（客户端可选）
	@参数		lpszKeyPassword			-- 私钥密码（没有密码则为空）
	@参数		lpszCAPemCertFileOrPath	-- CA 证书文件或目录（单向验证或客户端可选）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	@别名 初始化SSL环境(验证模式, 证书文件, 私钥文件,私钥密码,CA证书)
	*/
	virtual BOOL SetupSSLContext(int iVerifyMode = SSL_VM_NONE, LPCTSTR lpszPemCertFile = nullptr, LPCTSTR lpszPemKeyFile = nullptr, LPCTSTR lpszKeyPassword = nullptr, LPCTSTR lpszCAPemCertFileOrPath = nullptr)	= 0;

	/*@声明
	@备注 名称：初始化通信组件 SSL 环境参数（通过内存加载证书）
	// SSL 环境参数必须在 SSL 通信组件启动前完成初始化，否则启动失败
	@参数		iVerifyMode				-- SSL 验证模式（参考 EnSSLVerifyMode）
	@参数		lpszPemCert				-- 证书内容
	@参数		lpszPemKey				-- 私钥内容
	@参数		lpszKeyPassword			-- 私钥密码（没有密码则为空）
	@参数		lpszCAPemCert			-- CA 证书内容（单向验证或客户端可选）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	@别名 初始化SSL环境_内存(验证模式, 证书文件, 私钥文件,私钥密码,CA证书)
	*/
	virtual BOOL SetupSSLContextByMemory(int iVerifyMode = SSL_VM_NONE, LPCSTR lpszPemCert = nullptr, LPCSTR lpszPemKey = nullptr, LPCSTR lpszKeyPassword = nullptr, LPCSTR lpszCAPemCert = nullptr)					= 0;

	/*@声明
	@备注 清理通信组件 SSL 运行环境
	// 清理通信组件 SSL 运行环境，回收 SSL 相关内存
	//	1、通信组件析构时会自动调用本方法
	//	2、当要重新设置通信组件 SSL 环境参数时，需要先调用本方法清理原先的环境参数

	@参数	无
	
	@返回 无
	@别名 清理SSL环境()
	*/
	virtual void CleanupSSLContext()					= 0;

	/*@声明
	@备注 启动 SSL 握手
	// 当通信组件设置为非自动握手时，需要调用本方法启动 SSL 握手

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	@别名 启动SSL握手()
	*/
	virtual BOOL StartSSLHandShake()					= 0;

#endif

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置通信数据缓冲区大小（根据平均通信数据包大小调整设置，通常设置为：(N * 1024) - sizeof(TBufferObj)）
	//@参数 dwSocketBufferSize  --尺寸
	//@别名 置通信数据缓冲区尺寸(尺寸)
	virtual void SetSocketBufferSize	(DWORD dwSocketBufferSize)	= 0;
	//@备注 设置正常心跳包间隔（毫秒，0 则不发送心跳包，默认：60 * 1000）
	//@参数 dwKeepAliveTime  --间隔(单位:毫秒,0则不发送心跳包)
	//@别名 置正常心跳包间隔(间隔)
	virtual void SetKeepAliveTime		(DWORD dwKeepAliveTime)		= 0;
	//@备注 设置异常心跳包间隔（毫秒，0 不发送心跳包，，默认：20 * 1000，如果超过若干次 [默认：WinXP 5 次, Win7 10 次] 检测不到心跳确认包则认为已断线）
	//@参数 dwKeepAliveInterval  --间隔
	//@别名 置异常心跳包间隔(间隔)
	virtual void SetKeepAliveInterval	(DWORD dwKeepAliveInterval)	= 0;
	//@备注 设置是否开启 nodelay 模式（默认：FALSE，不开启）
	//@参数 bNoDelay  --是否开启
	//@别名 置是否开启(是否开启)
	virtual void SetNoDelay				(BOOL bNoDelay)				= 0;

	/* 获取通信数据缓冲区大小 */
	//@别名 取通信数据缓冲区尺寸()
	virtual DWORD GetSocketBufferSize	()	= 0;
	/* 获取正常心跳包间隔 */
	//@别名 取正常心跳包间隔()
	virtual DWORD GetKeepAliveTime		()	= 0;
	/* 获取异常心跳包间隔 */
	//@别名 取异常心跳包间隔()
	virtual DWORD GetKeepAliveInterval	()	= 0;
	/* 检查是否开启 nodelay 模式 */
	//@别名 取是否开启()
	virtual BOOL IsNoDelay				()	= 0;

#ifdef _SSL_SUPPORT
	//@备注 设置通信组件握手方式（默认：TRUE，自动握手）
	//@参数 bAutoHandShake  --方式
	//@别名 置通信组件握手方式(方式)
	virtual void SetSSLAutoHandShake(BOOL bAutoHandShake)	= 0;
	/* 获取通信组件握手方式 */
	//@别名 取通信组件握手方式()
	virtual BOOL IsSSLAutoHandShake()						= 0;

	/* 设置 SSL 加密算法列表 */
	//@参数 lpszCipherList  --列表
	//@别名 置SSL加密算法列表(列表)
	virtual void SetSSLCipherList(LPCTSTR lpszCipherList)	= 0;
	/* 获取 SSL 加密算法列表 */
	//@别名 取SSL加密算法列表()
	virtual LPCTSTR GetSSLCipherList()						= 0;

	/*@声明
	@备注获取 SSL Session 信息
	// 获取指定类型的 SSL Session 信息（输出类型参考：EnSSLSessionInfo）
	//@参数 enInfo  --输出类型参考	
	//@参数 lppInfo  --信息	
	//@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	//@别名 取SSL信息()
	*/
	virtual BOOL GetSSLSessionInfo(EnSSLSessionInfo enInfo, LPVOID* lppInfo)	= 0;
#endif

};
//@分组}
#ifdef _UDP_SUPPORT
//@分组{ UDP
/************************************************************************
名称：UDP 通信客户端组件接口
描述：定义 UDP 通信客户端组件的所有操作方法和属性访问方法
************************************************************************/
//@别名 HP_UDP客户端
class IUdpClient : public IClient
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节）
	//@别名 置数据报文最大长度(长度)
	virtual void SetMaxDatagramSize	(DWORD dwMaxDatagramSize)	= 0;
	//@备注 获取数据报文最大长度
	//@别名 取数据报文最大长度(长度)
	virtual DWORD GetMaxDatagramSize()							= 0;

	//@备注 设置监测包尝试次数（0 则不发送监测跳包，如果超过最大尝试次数则认为已断线）
	//@别名 置监测包尝试次数(次数)
	virtual void SetDetectAttempts	(DWORD dwDetectAttempts)	= 0;
	//@备注 设置监测包发送间隔（毫秒，0 不发送监测包）
	//@别名 置监测包发送间隔(间隔)
	virtual void SetDetectInterval	(DWORD dwDetectInterval)	= 0;
	//@备注 获取心跳检查次数
	//@别名 取心跳次数()
	virtual DWORD GetDetectAttempts	()							= 0;
	//@备注 获取心跳检查间隔
	//@别名 取心跳间隔()
	virtual DWORD GetDetectInterval	()							= 0;
};

/************************************************************************
名称：UDP 传播组件接口
描述：定义 UDP 传播（组播或广播）组件的所有操作方法和属性访问方法
************************************************************************/
//@别名 HP_UDP传播
class IUdpCast : public IClient
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节）
	//@别名 置数据报文最大长度(长度)
	virtual void SetMaxDatagramSize	(DWORD dwMaxDatagramSize)		= 0;
	/* 获取数据报文最大长度 */
	//@别名 取数据报文最大长度()
	virtual DWORD GetMaxDatagramSize()								= 0;

	//@备注 设置传播模式（组播或广播）
	//@别名 置传播模式()
	virtual void SetCastMode		(EnCastMode enCastMode)			= 0;
	/* 获取传播模式 */
	//@别名 取传播模式()
	virtual EnCastMode GetCastMode	()								= 0;

	//@备注 设置组播报文的 TTL（0 - 255）
	//@别名 置组播报文的TTL()
	virtual void SetMultiCastTtl	(int iMCTtl)					= 0;
	/* 获取组播报文的 TTL */
	//@别名 取组播报文的TTL()
	virtual int GetMultiCastTtl		()								= 0;

	//@备注 设置是否启用组播环路（TRUE or FALSE）
	//@别名 置是否启用组播环路(是否启用)
	virtual void SetMultiCastLoop	(BOOL bMCLoop)					= 0;
	/* 检测是否启用组播环路 */
	//@别名 取是否启用组播环路()
	virtual BOOL IsMultiCastLoop	()								= 0;

	//@备注 获取当前数据报的远程地址信息（通常在 OnReceive 事件中调用）
	//@别名 取远程地址信息()
	virtual BOOL GetRemoteAddress	(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
};

/************************************************************************
名称：UDP 节点组件接口
描述：定义 UDP 节点组件的所有操作方法和属性访问方法
************************************************************************/
//@别名 HP_UDP节点
class IUdpNode
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 启动(绑定地址,本地端口,传播模式,传播地址)
	@备注 启动 UDP 节点通信组件，启动完成后可开始收发数据

	@参数		lpszBindAddress		-- 绑定地址（默认：nullptr，绑定任意地址）
	@参数		usPort				-- 本地端口（默认：0）
	@参数		enCastMode			-- 传播模式（默认：CM_UNICAST）
	@参数		lpszCastAddress		-- 传播地址（默认：nullptr，当 enCaseMode 为 CM_MULTICAST 或 CM_BROADCAST 时有效）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Start(LPCTSTR lpszBindAddress = nullptr, USHORT usPort = 0, EnCastMode enCastMode = CM_UNICAST, LPCTSTR lpszCastAddress = nullptr)	= 0;

	/*@声明
	@别名 关闭()
	@备注 描述：关闭 UDP 节点通信组件，关闭完成后释放所有资源

	@参数	
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 GetLastError() 获取错误代码
	*/
	virtual BOOL Stop()																										= 0;

	/*@声明
	@别名 发送数据_指定(远程地址,远程端口,发送缓冲区,发送缓冲区长度,发送缓冲区指针偏移量)
	@备注 描述：向指定地址发送数据

	@参数		lpszRemoteAddress	-- 远程地址
	@参数		usRemotePort		-- 远程端口
	@参数		pBuffer				-- 发送缓冲区
	@参数		iLength				-- 发送缓冲区长度
	@参数		iOffset				-- 发送缓冲区指针偏移量
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Send(LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pBuffer, int iLength, int iOffset = 0)	= 0;

	/*@声明
	@别名 发送数据组_指定(远程地址,远程端口,发送缓冲区数组,发送缓冲区数目)
	@备注 描述：向指定地址发送多组数据，把所有数据包组合成一个数据包发送（数据包的总长度不能大于设置的 UDP 包最大长度） 

	@参数		lpszRemoteAddress	-- 远程地址
	@参数		usRemotePort		-- 远程端口
	@参数		pBuffers			-- 发送缓冲区数组
	@参数		iCount				-- 发送缓冲区数目
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendPackets(LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const WSABUF pBuffers[], int iCount)			= 0;

	/*@声明
	@别名 发送数据(发送缓冲区,发送缓冲区长度,发送缓冲区指针偏移量)
	@备注 描述：向传播地址发送数据

	@参数		pBuffer		-- 发送缓冲区
	@参数		iLength		-- 发送缓冲区长度
	@参数		iOffset		-- 发送缓冲区指针偏移量
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendCast(const BYTE* pBuffer, int iLength, int iOffset = 0)												= 0;

	/*@声明
	@别名 发送数据组(发送缓冲区数组,发送缓冲区数目)
	@备注 描述：向传播地址发送多组数据，把所有数据包组合成一个数据包发送（数据包的总长度不能大于设置的 UDP 包最大长度） 

	@参数		pBuffers	-- 发送缓冲区数组
	@参数		iCount		-- 发送缓冲区数目
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL SendCastPackets(const WSABUF pBuffers[], int iCount)														= 0;

	/*@声明
	@别名 等待()
	@备注 描述：等待通信组件停止运行

	@参数		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Wait(DWORD dwMilliseconds = INFINITE)																		= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置附加数据 */
	//@别名 置附加数据()
	virtual void SetExtra					(PVOID pExtra)										= 0;

	/* 获取附加数据 */
	//@别名 取附加数据()
	virtual PVOID GetExtra					()													= 0;

	/* 检查通信组件是否已启动 */
	//@别名 是否已启动()
	virtual BOOL HasStarted					()													= 0;
	/* 查看通信组件当前状态 */
	//@别名 取当前状态()
	virtual EnServiceState GetState			()													= 0;
	/* 获取最近一次失败操作的错误代码 */
	//@别名 取错误代码()
	virtual EnSocketError GetLastError		()													= 0;
	/* 获取最近一次失败操作的错误描述 */
	//@别名 取错误描述()
	virtual LPCTSTR GetLastErrorDesc		()													= 0;
	/* 获取本节点地址 */
	//@别名 取本节点地址()
	virtual BOOL GetLocalAddress		(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
	/* 获取本节点传播地址 */
	//@别名 取本节点传播地址()
	virtual BOOL GetCastAddress			(TCHAR lpszAddress[], int& iAddressLen, USHORT& usPort)	= 0;
	/* 获取传播模式 */
	//@别名 取传播模式()
	virtual EnCastMode GetCastMode		()														= 0;
	/* 获取未发出数据的长度 */
	//@别名 取未发出数据长度()
	virtual BOOL GetPendingDataLength	(int& iPending)											= 0;

	//@备注 设置数据报文最大长度（建议在局域网环境下不超过 1432 字节，在广域网环境下不超过 548 字节） 
	//@别名 置数据报文最大长度(长度)
	virtual void SetMaxDatagramSize	(DWORD dwMaxDatagramSize)	= 0;
	/* 获取数据报文最大长度 */
	//@别名 取数据报文最大长度()
	virtual DWORD GetMaxDatagramSize()							= 0;

	//@备注 设置组播报文的 TTL（0 - 255） 
	//@别名 置组播报文的TTL()
	virtual void SetMultiCastTtl	(int iMCTtl)				= 0;
	/* 获取组播报文的 TTL */
	//@别名 取组播报文的TTL()
	virtual int GetMultiCastTtl		()							= 0;

	//@备注 设置是否启用组播环路（TRUE or FALSE） 
	//@别名 置是否启用组播环路()
	virtual void SetMultiCastLoop	(BOOL bMCLoop)				= 0;
	/* 检测是否启用组播环路 */
	//@别名 是否启用组播环路()
	virtual BOOL IsMultiCastLoop	()							= 0;

	/* 设置地址重用选项 */
	//@别名 置地址重用选项(选项)
	virtual void SetReuseAddressPolicy(EnReuseAddressPolicy enReusePolicy)	= 0;
	//@备注 设置工作线程数量（通常设置为 2 * CPU + 2） 
	//@别名 置工作线程数量(数量)
	virtual void SetWorkerThreadCount	(DWORD dwWorkerThreadCount)			= 0;
	//@备注 设置 Receive 预投递数量（根据负载调整设置，Receive 预投递数量越大则丢包概率越小） 
	//@别名 置预投递数量(数量)
	virtual void SetPostReceiveCount	(DWORD dwPostReceiveCount)			= 0;
	/* 设置内存块缓存池大小 */
	//@别名 置内存块缓存池大小(大小)
	virtual void SetFreeBufferPoolSize	(DWORD dwFreeBufferPoolSize)		= 0;
	/* 设置内存块缓存池回收阀值 */
	//@别名 置内存块缓存池回收阀值(阀值)
	virtual void SetFreeBufferPoolHold	(DWORD dwFreeBufferPoolHold)		= 0;

	/* 获取地址重用选项 */
	//@别名 取地址重用选项()
	virtual EnReuseAddressPolicy GetReuseAddressPolicy()					= 0;
	/* 获取工作线程数量 */
	//@别名 取工作线程数量()
	virtual DWORD GetWorkerThreadCount	()									= 0;
	/* 获取 Receive 预投递数量 */
	//@别名 取预投递数量()
	virtual DWORD GetPostReceiveCount	()									= 0;
	/* 获取内存块缓存池大小 */
	//@别名 取内存块缓存池大小()
	virtual DWORD GetFreeBufferPoolSize	()									= 0;
	/* 获取内存块缓存池回收阀值 */
	//@别名 取内存块缓存池回收阀值()
	virtual DWORD GetFreeBufferPoolHold	()									= 0;

public:
	virtual ~IUdpNode() {}
};

/************************************************************************
名称：Client ARQ 模型组件接口
描述：定义 Client 组件的 ARQ 模型组件的所有操作方法
************************************************************************/
//@别名 HP_ARQ客户端
class IArqClient
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置是否开启 nodelay 模式（默认：FALSE，不开启）
	//@别名 置是否开启模式(模式)
	virtual void SetNoDelay				(BOOL bNoDelay)				= 0;
	//@备注 设置是否关闭拥塞控制（默认：FALSE，不关闭）
	//@别名 置是否关闭拥塞控制(是否关闭)
	virtual void SetTurnoffCongestCtrl	(BOOL bTurnOff)				= 0;
	//@备注 设置数据刷新间隔（毫秒，默认：60）
	//@别名 置数据刷新间隔(间隔)
	virtual void SetFlushInterval		(DWORD dwFlushInterval)		= 0;
	//@备注 设置快速重传 ACK 跨越次数（默认：0，关闭快速重传）
	//@别名 置快速重传跨越次数(次数)
	virtual void SetResendByAcks		(DWORD dwResendByAcks)		= 0;
	//@备注 设置发送窗口大小（数据包数量，默认：128）
	//@别名 置发送窗口大小(大小)
	virtual void SetSendWndSize			(DWORD dwSendWndSize)		= 0;
	//@备注 设置接收窗口大小（数据包数量，默认：512）
	//@别名 置接收窗口大小(大小)
	virtual void SetRecvWndSize			(DWORD dwRecvWndSize)		= 0;
	//@备注 设置最小重传超时时间（毫秒，默认：30）
	//@别名 置最小重传超时时间(时间)
	virtual void SetMinRto				(DWORD dwMinRto)			= 0;
	//@备注 设置快速握手次数限制（默认：5，如果为 0 则不限制）
	//@别名 置快速握手次数限制(次数)
	virtual void SetFastLimit			(DWORD dwFastLimit)			= 0;
	//@备注 设置最大传输单元（默认：0，与 SetMaxDatagramSize() 一致）
	//@别名 置最大传输单元(单元)
	virtual void SetMaxTransUnit		(DWORD dwMaxTransUnit)		= 0;
	//@备注 设置最大数据包大小（默认：4096）
	//@别名 置最大数据包大小(大小)
	virtual void SetMaxMessageSize		(DWORD dwMaxMessageSize)	= 0;
	//@备注 设置握手超时时间（毫秒，默认：5000）
	//@别名 置握手超时时间(时间)
	virtual void SetHandShakeTimeout	(DWORD dwHandShakeTimeout)	= 0;

	//@备注 检测是否开启 nodelay 模式
	//@别名 是否开启模式()
	virtual BOOL IsNoDelay				()							= 0;
	/* 检测是否关闭拥塞控制 */
	//@别名 是否关闭拥塞控制()
	virtual BOOL IsTurnoffCongestCtrl	()							= 0;
	/* 获取数据刷新间隔 */
	//@别名 取数据刷新间隔()
	virtual DWORD GetFlushInterval		()							= 0;
	/* 获取快速重传 ACK 跨越次数 */
	//@别名 取快速重传跨越次数()
	virtual DWORD GetResendByAcks		()							= 0;
	/* 获取发送窗口大小 */
	//@别名 取发送窗口大小()
	virtual DWORD GetSendWndSize		()							= 0;
	/* 获取接收窗口大小 */
	//@别名 取接收窗口大小()
	virtual DWORD GetRecvWndSize		()							= 0;
	/* 获取最小重传超时时间 */
	//@别名 取最小重传超时时间()
	virtual DWORD GetMinRto				()							= 0;
	/* 获取快速握手次数限制 */
	//@别名 取快速握手次数限制()
	virtual DWORD GetFastLimit			()							= 0;
	/* 获取最大传输单元 */
	//@别名 取最大传输单元()
	virtual DWORD GetMaxTransUnit		()							= 0;
	/* 获取最大数据包大小 */
	//@别名 取最大数据包大小()
	virtual DWORD GetMaxMessageSize		()							= 0;
	/* 获取握手超时时间 */
	//@别名 取握手超时时间()
	virtual DWORD GetHandShakeTimeout	()							= 0;

	/* 获取等待发送包数量 */
	//@别名 取等待发送包数量()
	virtual BOOL GetWaitingSendMessageCount	(int& iCount)			= 0;

public:
	virtual ~IArqClient() {}
};

/************************************************************************
名称：UDP ARQ 通信客户端组件接口
描述：继承了 ARQ 和 Client 接口
************************************************************************/
typedef	DualInterface<IArqClient, IUdpClient>	IUdpArqClient;
//@分组}
#endif

//@备注 Server/Agent PULL 模型组件接口
//描述：定义 Server/Agent 组件的 PULL 模型组件的所有操作方法
//@别名 HP_PULL模型
class IPullSocket
{
public:

	/*@声明
	@别名 抓取数据(连接ID,抓取缓冲区,数据长度)
	@备注 用户通过该方法从 Socket 组件中抓取数据

	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 抓取缓冲区
	@参数		iLength		-- 抓取数据长度
	@返回	EnFetchResult
	*/
	virtual EnFetchResult Fetch	(CONNID dwConnID, BYTE* pData, int iLength)	= 0;

	/*@声明
	@别名 窥探数据(连接ID,窥探缓冲区,数据长度)
	@备注 用户通过该方法从 Socket 组件中窥探数据(不会移除缓冲区数据)

	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 窥探缓冲区
	@参数		iLength		-- 窥探数据长度
	@返回	EnFetchResult
	*/
	virtual EnFetchResult Peek	(CONNID dwConnID, BYTE* pData, int iLength)	= 0;

public:
	virtual ~IPullSocket() {}
};

/************************************************************************
名称：Client PULL 模型组件接口
描述：定义 Client 组件的 PULL 模型组件的所有操作方法
************************************************************************/
//@别名 HP_PULL客户端
class IPullClient
{
public:

	/*@声明
	@别名 抓取数据(抓取缓冲区,数据长度)
	@备注 用户通过该方法从 Socket 组件中抓取数据

	@参数		pData		-- 抓取缓冲区
	@参数		iLength		-- 抓取数据长度
	@返回	EnFetchResult
	*/
	virtual EnFetchResult Fetch	(BYTE* pData, int iLength)	= 0;

	/*@声明
	@别名 窥探数据(窥探缓冲区,数据长度)
	@备注 用户通过该方法从 Socket 组件中窥探数据（不会移除缓冲区数据）

	@参数		pData		-- 窥探缓冲区
	@参数		iLength		-- 窥探数据长度
	@返回	EnFetchResult
	*/
	virtual EnFetchResult Peek	(BYTE* pData, int iLength)	= 0;

public:
	virtual ~IPullClient() {}
};

/************************************************************************
名称：TCP PULL 模型组件接口
描述：继承了 PULL 和 Socket 接口
************************************************************************/
//@隐藏{
typedef	DualInterface<IPullSocket, ITcpServer>	ITcpPullServer;
typedef	DualInterface<IPullSocket, ITcpAgent>	ITcpPullAgent;
typedef	DualInterface<IPullClient, ITcpClient>	ITcpPullClient;
//@隐藏}
/************************************************************************
名称：Server/Agent PACK 模型组件接口
描述：定义 Server/Agent 组件的 PACK 模型组件的所有操作方法
************************************************************************/
//@别名 HP_PACK模型
class IPackSocket
{
public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置数据包最大长度（有效数据包最大长度不能超过 4194303/0x3FFFFF 字节，默认：262144/0x40000） */
	//@参数 dwMaxPackSize --长度
	//@别名 置数据包最大长度(长度)
	virtual void SetMaxPackSize		(DWORD dwMaxPackSize)			= 0;
	//@备注 设置包头标识（有效包头标识取值范围 0 ~ 1023/0x3FF，当包头标识为 0 时不校验包头，默认：0） 
	//@参数 usPackHeaderFlag --标识
	//@别名 置包头标识(标识)
	virtual void SetPackHeaderFlag	(USHORT usPackHeaderFlag)		= 0;

	/* 获取数据包最大长度 */
	//@ 别名 取数据包最大长度()
	virtual DWORD GetMaxPackSize	()								= 0;
	/* 获取包头标识 */
	//@ 别名 取包头标识()
	virtual USHORT GetPackHeaderFlag()								= 0;

public:
	virtual ~IPackSocket() {}
};

/************************************************************************
名称：Client PACK 模型组件接口
描述：定义 Client 组件的 PACK 模型组件的所有操作方法
************************************************************************/
//@别名 HP_PACK客户端
class IPackClient
{
public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置数据包最大长度（有效数据包最大长度不能超过 4194303/0x3FFFFF 字节，默认：262144/0x40000） 
	//@参数 dwMaxPackSize --长度
	//@别名 置数据包最大长度(长度)
	virtual void SetMaxPackSize		(DWORD dwMaxPackSize)			= 0;
	//@备注 设置包头标识（有效包头标识取值范围 0 ~ 1023/0x3FF，当包头标识为 0 时不校验包头，默认：0） 
	//@参数 usPackHeaderFlag --标识
	//@别名 置包头标识(标识)
	virtual void SetPackHeaderFlag	(USHORT usPackHeaderFlag)		= 0;

	/* 获取数据包最大长度 */
	//@别名 取数据包最大长度()
	virtual DWORD GetMaxPackSize	()								= 0;
	/* 获取包头标识 */
	//@别名 取包头标识()
	virtual USHORT GetPackHeaderFlag()								= 0;

public:
	virtual ~IPackClient() {}
};

/************************************************************************
名称：TCP PACK 模型组件接口
描述：继承了 PACK 和 Socket 接口
************************************************************************/
//@隐藏{
typedef	DualInterface<IPackSocket, ITcpServer>	ITcpPackServer;
typedef	DualInterface<IPackSocket, ITcpAgent>	ITcpPackAgent;
typedef	DualInterface<IPackClient, ITcpClient>	ITcpPackClient;
//@隐藏}

/************************************************************************
名称：Socket 监听器基接口
描述：定义组件监听器的公共方法
************************************************************************/
template<class T> class ISocketListenerT
{
public:

	/*@声明
	@别名 握手完成通知()
	@备注 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始数据收发操作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnHandShake(T* pSender, CONNID dwConnID)												= 0;

	/*@声明
	@别名 已发送数据通知(事件源对象,连接ID,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已发送数据缓冲区
	@参数		iLength		-- 已发送数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
	virtual EnHandleResult OnSend(T* pSender, CONNID dwConnID, const BYTE* pData, int iLength)					= 0;

	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据缓冲区,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已接收数据缓冲区
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnReceive(T* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				= 0;

	/*@声明
	@别名  数据到达通知(事件源对象, 连接ID, 数据长度)
	@备注 描述：对于 PULL 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回值	    HR_OK / HR_IGNORE	-- 继续执行
	//			HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnReceive(T* pSender, CONNID dwConnID, int iLength)									= 0;

	/*@声明
	@别名 关闭通知(事件源对象,连接ID,操作类型,错误代码)
	@备注 描述：通信发生错误后，Socket 监听器将收到该通知，并关闭连接

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		enOperation	-- Socket 操作类型
	@参数		iErrorCode	-- 错误代码
	@返回	忽略返回值
	*/
	virtual EnHandleResult OnClose(T* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)	= 0;

public:
	virtual ~ISocketListenerT() {}
};

template<class T> class IComplexSocketListenerT : public ISocketListenerT<T>
{
public:

	/*@声明
	@别名 关闭通信组件通知(事件源对象)
	@备注 描述：通信组件关闭时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@返回	忽略返回值
	*/
	virtual EnHandleResult OnShutdown(T* pSender)																= 0;

};

/************************************************************************
名称：服务端 Socket 监听器接口
描述：定义服务端 Socket 监听器的所有事件
************************************************************************/
template<class T> class IServerListenerT : public IComplexSocketListenerT<T>
{
public:

	/*@声明
	@别名 准备监听通知(事件源对象,监听Socket)
	@备注 描述：通信服务端组件启动时，在监听 Socket 创建完成并开始执行监听前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		soListen	-- 监听 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信服务组件
	*/
	virtual EnHandleResult OnPrepareListen(T* pSender, SOCKET soListen)						= 0;

	/*@声明
	@别名 接收连接通知(事件源对象,连接ID,soClient)
	@备注 描述：接收到客户端连接请求时，Socket 监听器将收到该通知，监听器可以在通知处理方
	//		法中执行 Socket 选项设置或拒绝客户端连接等额外工作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		soClient	-- TCP: 客户端 Socket 句柄，UDP: 客户端 Socket SOCKADDR 指针
	@返回	HR_OK / HR_IGNORE	-- 接受连接
	//		HR_ERROR			-- 拒绝连接
	*/
	virtual EnHandleResult OnAccept(T* pSender, CONNID dwConnID, UINT_PTR soClient)			= 0;
};

/************************************************************************
名称：TCP 服务端 Socket 监听器接口
描述：定义 TCP 服务端 Socket 监听器的所有事件
************************************************************************/
//@分组{ HP服务端
//@别名 HP_TCP服务器监听器
class ITcpServerListener : public IServerListenerT< ITcpServer >
{
public:

};

/************************************************************************
名称：PUSH 模型服务端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_TCP服务器监听器_实现
class CTcpServerListener : public ITcpServerListener
{
public:
	/*@声明
	@别名 准备监听通知(事件源对象,监听Socket)
	@备注 描述：通信服务端组件启动时，在监听 Socket 创建完成并开始执行监听前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		soListen	-- 监听 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信服务组件
	*/
	事件定义 virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen)							{return HR_IGNORE;}
	/*@声明
	@别名 接收连接通知(事件源对象,连接ID,soClient)
	@备注 描述：接收到客户端连接请求时，Socket 监听器将收到该通知，监听器可以在通知处理方
	//		法中执行 Socket 选项设置或拒绝客户端连接等额外工作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		soClient	-- TCP: 客户端 Socket 句柄，UDP: 客户端 Socket SOCKADDR 指针
	@返回	HR_OK / HR_IGNORE	-- 接受连接
	//		HR_ERROR			-- 拒绝连接
	*/
	事件定义 virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)				{return HR_IGNORE;}
	/*@声明
	@别名 握手完成通知()
	@备注 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始数据收发操作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID)								{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength)						{return HR_IGNORE;}
	/*@声明
	@别名 已发送数据通知(事件源对象,连接ID,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已发送数据缓冲区
	@参数		iLength		-- 已发送数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
	事件定义 virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	/*@声明
	@别名 关闭通信组件通知(事件源对象)
	@备注 描述：通信组件关闭时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnShutdown(ITcpServer* pSender)													{return HR_IGNORE;}
	/*@声明
	@别名 关闭通知(事件源对象,连接ID,操作类型,错误代码)
	@备注 描述：通信发生错误后，Socket 监听器将收到该通知，并关闭连接

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		enOperation	-- Socket 操作类型
	@参数		iErrorCode	-- 错误代码
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) = 0;

};

/************************************************************************
名称：PULL 模型服务端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_TCP_PULL服务器监听器_实现
class CTcpPullServerListener : public CTcpServerListener
{
public:
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength)						= 0;
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据缓冲区,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已接收数据缓冲区
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}

	/*@声明
	@别名 关闭通知(事件源对象,连接ID,操作类型,错误代码)
	@备注 描述：通信发生错误后，Socket 监听器将收到该通知，并关闭连接

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		enOperation	-- Socket 操作类型
	@参数		iErrorCode	-- 错误代码
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) = 0;

};
//@分组}
#ifdef _UDP_SUPPORT
//@分组{ UDP
/************************************************************************
名称：UDP 服务端 Socket 监听器接口
描述：定义 UDP 服务端 Socket 监听器的所有事件
************************************************************************/
//@别名 HP_UDP服务器监听器
class IUdpServerListener : public IServerListenerT<IUdpServer>
{
public:

};

/************************************************************************
名称：UDP 服务端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_UDP服务器监听器_实现
class CUdpServerListener : public IUdpServerListener
{
public:
	/*@声明
	@别名 准备监听通知(事件源对象,监听Socket)
	@备注 描述：通信服务端组件启动时，在监听 Socket 创建完成并开始执行监听前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		soListen	-- 监听 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信服务组件
	*/
	事件定义 virtual EnHandleResult OnPrepareListen(IUdpServer* pSender, SOCKET soListen)						{return HR_IGNORE;}
	/*@声明
	@别名 接收连接通知(事件源对象,连接ID,soClient)
	@备注 描述：接收到客户端连接请求时，Socket 监听器将收到该通知，监听器可以在通知处理方
	//		法中执行 Socket 选项设置或拒绝客户端连接等额外工作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		soClient	-- TCP: 客户端 Socket 句柄，UDP: 客户端 Socket SOCKADDR 指针
	@返回	HR_OK / HR_IGNORE	-- 接受连接
	//		HR_ERROR			-- 拒绝连接
	*/
	事件定义 virtual EnHandleResult OnAccept(IUdpServer* pSender, CONNID dwConnID, UINT_PTR pSockAddr)			{return HR_IGNORE;}
	/*@声明
	@别名 握手完成通知()
	@备注 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始数据收发操作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnHandShake(IUdpServer* pSender, CONNID dwConnID)							{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(IUdpServer* pSender, CONNID dwConnID, int iLength)					{return HR_IGNORE;}
	/*@声明
	@别名 已发送数据通知(事件源对象,连接ID,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已发送数据缓冲区
	@参数		iLength		-- 已发送数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
	事件定义 virtual EnHandleResult OnSend(IUdpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
	/*@声明
	@别名 关闭通信组件通知(事件源对象)
	@备注 描述：通信组件关闭时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnShutdown(IUdpServer* pSender)												{return HR_IGNORE;}
	
	
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据缓冲区,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已接收数据缓冲区
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(IUdpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)	 {return HR_IGNORE;}
	
	/*@声明
	@别名 关闭通知(事件源对象,连接ID,操作类型,错误代码)
	@备注 描述：通信发生错误后，Socket 监听器将收到该通知，并关闭连接

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		enOperation	-- Socket 操作类型
	@参数		iErrorCode	-- 错误代码
	@返回	忽略返回值
	*/
	virtual EnHandleResult OnClose(IUdpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)  {return HR_IGNORE;}
};
//@分组}
#endif

/************************************************************************
名称：通信代理 Socket 监听器接口
描述：定义 通信代理 Socket 监听器的所有事件
************************************************************************/
template<class T> class IAgentListenerT : public IComplexSocketListenerT<T>
{
public:

	/*
	* 名称：准备连接通知
	* 描述：通信客户端组件启动时，在客户端 Socket 创建完成并开始执行连接前，Socket 监听
	*		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	*			socket		-- 客户端 Socket
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 终止启动通信客户端组件
	*/
	virtual EnHandleResult OnPrepareConnect(T* pSender, CONNID dwConnID, SOCKET socket)		= 0;

	/*
	* 名称：连接完成通知
	* 描述：与服务端成功建立连接时，Socket 监听器将收到该通知
	*		
	* 参数：		pSender		-- 事件源对象
	*			dwConnID	-- 连接 ID
	* 返回值：	HR_OK / HR_IGNORE	-- 继续执行
	*			HR_ERROR			-- 同步连接：终止启动通信客户端组件
	*								   异步连接：关闭连接
	*/
	virtual EnHandleResult OnConnect(T* pSender, CONNID dwConnID)							= 0;
};

/************************************************************************
名称：TCP 通信代理 Socket 监听器接口
描述：定义 TCP 通信代理 Socket 监听器的所有事件
************************************************************************/
//@别名 HP_TCP代理监听器
class ITcpAgentListener : public IAgentListenerT<ITcpAgent>
{
public:

};

/************************************************************************
名称：PUSH 模型通信代理 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_TCP代理监听器_实现
class CTcpAgentListener : public ITcpAgentListener
{
public:
	/*@声明
	@别名 准备连接通知(事件源对象,连接ID,Socket)
	@备注 描述：通信客户端组件启动时，在客户端 Socket 创建完成并开始执行连接前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		socket		-- 客户端 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信客户端组件
	*/
	事件定义 virtual EnHandleResult OnPrepareConnect(ITcpAgent* pSender, CONNID dwConnID, SOCKET socket)				{return HR_IGNORE;}
	/*@声明
	@别名 连接完成通知(事件源对象,连接ID)
	@备注 描述：与服务端成功建立连接时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 同步连接：终止启动通信客户端组件
	//							   异步连接：关闭连接
	*/
	事件定义 virtual EnHandleResult OnConnect(ITcpAgent* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	/*@声明
	@别名 握手完成通知()
	@备注 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始数据收发操作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnHandShake(ITcpAgent* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpAgent* pSender, CONNID dwConnID, int iLength)						{return HR_IGNORE;}
	/*@声明
	@别名 已发送数据通知(事件源对象,连接ID,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已发送数据缓冲区
	@参数		iLength		-- 已发送数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
	事件定义 virtual EnHandleResult OnSend(ITcpAgent* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	/*@声明
	@别名 关闭通信组件通知(事件源对象)
	@备注 描述：通信组件关闭时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnShutdown(ITcpAgent* pSender)													{return HR_IGNORE;}
};

/************************************************************************
名称：PULL 通信代理 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_TCP_PULL代理监听器_实现
class CTcpPullAgentListener : public CTcpAgentListener
{
public:
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpAgent* pSender, CONNID dwConnID, int iLength)						= 0;
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据缓冲区,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已接收数据缓冲区
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpAgent* pSender, CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
};

/************************************************************************
名称：客户端 Socket 监听器接口
描述：定义客户端 Socket 监听器的所有事件
************************************************************************/

template<class T> class IClientListenerT : public ISocketListenerT<T>
{
public:
	
	/*@声明
	@别名 准备连接通知(事件源对象,连接ID,Socket)
	@备注 描述：通信客户端组件启动时，在客户端 Socket 创建完成并开始执行连接前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		socket		-- 客户端 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信客户端组件
	*/
	virtual EnHandleResult OnPrepareConnect(T* pSender, CONNID dwConnID, SOCKET socket)						= 0;

	/*@声明
	@别名 连接完成通知(事件源对象,连接ID)
	@备注 描述：与服务端成功建立连接时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 同步连接：终止启动通信客户端组件
	//							   异步连接：关闭连接
	*/
	virtual EnHandleResult OnConnect(T* pSender, CONNID dwConnID)											= 0;
};
//@分组{ HP客户端
/************************************************************************
名称：TCP 客户端 Socket 监听器接口
描述：定义 TCP 客户端 Socket 监听器的所有事件
************************************************************************/
//@别名 HP_TCP客户端监听器
class ITcpClientListener : public IClientListenerT<ITcpClient>
{
public:

};

/************************************************************************
名称：PUSH 模型客户端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_TCP客户端监听器_实现
class CTcpClientListener : public ITcpClientListener
{
public:
	/*@声明
	@别名 准备连接通知(事件源对象,连接ID,Socket)
	@备注 描述：通信客户端组件启动时，在客户端 Socket 创建完成并开始执行连接前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		socket		-- 客户端 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信客户端组件
	*/
事件定义 virtual EnHandleResult OnPrepareConnect(ITcpClient* pSender, CONNID dwConnID, SOCKET socket)			{return HR_IGNORE;}
	/*@声明
	@别名 连接完成通知(事件源对象,连接ID)
	@备注 描述：与服务端成功建立连接时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 同步连接：终止启动通信客户端组件
	//							   异步连接：关闭连接
	*/
事件定义	virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	/*@声明
	@别名 握手完成通知()
	@备注 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始数据收发操作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
事件定义	virtual EnHandleResult OnHandShake(ITcpClient* pSender, CONNID dwConnID)								{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
事件定义	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength)						{return HR_IGNORE;}
	/*@声明
	@别名 已发送数据通知(事件源对象,连接ID,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已发送数据缓冲区
	@参数		iLength		-- 已发送数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
事件定义	virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	/*@声明
	@别名 关闭通知(事件源对象,连接ID,操作类型,错误代码)
	@备注 描述：通信发生错误后，Socket 监听器将收到该通知，并关闭连接

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		enOperation	-- Socket 操作类型
	@参数		iErrorCode	-- 错误代码
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) = 0;

};

/************************************************************************
名称：PULL 客户端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_TCP_PULL客户端监听器_实现
class CTcpPullClientListener : public CTcpClientListener
{
public:
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength)						= 0;
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据缓冲区,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已接收数据缓冲区
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
};
//@分组}
#ifdef _UDP_SUPPORT
//@分组{ UDP
/************************************************************************
名称：UDP 客户端 Socket 监听器接口
描述：定义 UDP 客户端 Socket 监听器的所有事件
************************************************************************/
//@别名 HP_UDP客户端监听器
class IUdpClientListener : public IClientListenerT<IUdpClient>
{
public:

};

/************************************************************************
名称：UDP 客户端 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_UDP客户端监听器_实现
class CUdpClientListener : public IUdpClientListener
{
public:
	/*@声明
	@别名 准备连接通知(事件源对象,连接ID,Socket)
	@备注 描述：通信客户端组件启动时，在客户端 Socket 创建完成并开始执行连接前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		socket		-- 客户端 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信客户端组件
	*/
	事件定义 virtual EnHandleResult OnPrepareConnect(IUdpClient* pSender, CONNID dwConnID, SOCKET socket)			{return HR_IGNORE;}
	/*@声明
	@别名 连接完成通知(事件源对象,连接ID)
	@备注 描述：与服务端成功建立连接时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 同步连接：终止启动通信客户端组件
	//							   异步连接：关闭连接
	*/
	事件定义 virtual EnHandleResult OnConnect(IUdpClient* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	/*@声明
	@别名 握手完成通知()
	@备注 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始数据收发操作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnHandShake(IUdpClient* pSender, CONNID dwConnID)								{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(IUdpClient* pSender, CONNID dwConnID, int iLength)						{return HR_IGNORE;}
	/*@声明
	@别名 已发送数据通知(事件源对象,连接ID,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已发送数据缓冲区
	@参数		iLength		-- 已发送数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
	事件定义 virtual EnHandleResult OnSend(IUdpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	
	
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据缓冲区,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已接收数据缓冲区
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(IUdpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
	
	
	/*@声明
	@别名 关闭通知(事件源对象,连接ID,操作类型,错误代码)
	@备注 描述：通信发生错误后，Socket 监听器将收到该通知，并关闭连接

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		enOperation	-- Socket 操作类型
	@参数		iErrorCode	-- 错误代码
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnClose(IUdpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) {return HR_IGNORE;}
};

/************************************************************************
名称：UDP 传播 Socket 监听器接口
描述：定义 UDP 传播 Socket 监听器的所有事件
************************************************************************/
//@别名 HP_UDP传播监听器
class IUdpCastListener : public IClientListenerT<IUdpCast>
{
public:

};

/************************************************************************
名称：UDP 传播 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_UDP传播监听器_实现
class CUdpCastListener : public IUdpCastListener
{
public:
	/*@声明
	@别名 准备连接通知(事件源对象,连接ID,Socket)
	@备注 描述：通信客户端组件启动时，在客户端 Socket 创建完成并开始执行连接前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		socket		-- 客户端 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信客户端组件
	*/
	事件定义 virtual EnHandleResult OnPrepareConnect(IUdpCast* pSender, CONNID dwConnID, SOCKET socket)				{return HR_IGNORE;}
	/*@声明
	@别名 连接完成通知(事件源对象,连接ID)
	@备注 描述：与服务端成功建立连接时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 同步连接：终止启动通信客户端组件
	//							   异步连接：关闭连接
	*/
	事件定义 virtual EnHandleResult OnConnect(IUdpCast* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	/*@声明
	@别名 握手完成通知()
	@备注 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始数据收发操作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnHandShake(IUdpCast* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(IUdpCast* pSender, CONNID dwConnID, int iLength)						{return HR_IGNORE;}
	/*@声明
	@别名 已发送数据通知(事件源对象,连接ID,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已发送数据缓冲区
	@参数		iLength		-- 已发送数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
	事件定义 virtual EnHandleResult OnSend(IUdpCast* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
};

/************************************************************************
名称：UDP 节点 Socket 监听器接口
描述：定义 UDP 节点 Socket 监听器的所有事件
************************************************************************/
//@别名 HP_UDP节点监听器
class IUdpNodeListener
{
public:

	/*@声明
	@别名 准备监听通知(事件源对象,监听Socket)
	@备注 描述：通信服务端组件启动时，在监听 Socket 创建完成并开始执行监听前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		soListen	-- 监听 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信服务组件
	*/
	virtual EnHandleResult OnPrepareListen(IUdpNode* pSender, SOCKET soListen)															= 0;

	/*@声明
	@别名 已发送数据通知(事件源对象,远程地址,远程端口,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender				-- 事件源对象
	@参数		lpszRemoteAddress	-- 远程地址
	@参数		usRemotePort		-- 远程端口
	@参数		pData				-- 已发送数据缓冲区
	@参数		iLength				-- 已发送数据长度
	@返回	忽略返回值
	*/
	virtual EnHandleResult OnSend(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)	= 0;

	/*@声明
	@别名 数据到达通知(事件源对象,远程地址,远程端口,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功接收数据后，Socket 监听器将收到该通知（PUSH 模型）

	@参数		pSender				-- 事件源对象
	@参数		lpszRemoteAddress	-- 远程地址
	@参数		usRemotePort		-- 远程端口
	@参数		pData				-- 已发送数据缓冲区
	@参数		iLength				-- 已发送数据长度
	@返回	忽略返回值
	*/
	virtual EnHandleResult OnReceive(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)	= 0;

	/*@声明
	@别名 通信错误通知(事件源对象,远程地址,远程端口,操作类型,错误代码,本次事件关联的数据缓冲区,本次事件关联的数据长度)
	@备注 描述：通信发生错误后，Socket 监听器将收到该通知

	@参数		pSender				-- 事件源对象
	@参数		lpszRemoteAddress	-- 远程地址
	@参数		usRemotePort		-- 远程端口
	@参数		enOperation			-- Socket 操作类型
	@参数		iErrorCode			-- 错误代码
	@参数		pData				-- 本次事件关联的数据缓冲区
	@参数		iLength				-- 本次事件关联的数据长度
	@返回	忽略返回值
	*/
	virtual EnHandleResult OnError(IUdpNode* pSender, EnSocketOperation enOperation, int iErrorCode, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)	= 0;

	/*@声明
	@别名 关闭通信组件通知(事件源对象)
	@备注 描述：通信组件关闭时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@返回	忽略返回值
	*/
	virtual EnHandleResult OnShutdown(IUdpNode* pSender)																				= 0;

public:
	virtual ~IUdpNodeListener() {}
};

/************************************************************************
名称：UDP 节点 Socket 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_UDP节点监听器_实现
class CUdpNodeListener : public IUdpNodeListener
{
public:
	/*@声明
	@别名 准备监听通知(事件源对象,监听Socket)
	@备注 描述：通信服务端组件启动时，在监听 Socket 创建完成并开始执行监听前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		soListen	-- 监听 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信服务组件
	*/
	事件定义 virtual EnHandleResult OnPrepareListen(IUdpNode* pSender, SOCKET soListen)															{return HR_IGNORE;}
	/*@声明
	@别名 已发送数据通知(事件源对象,连接ID,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已发送数据缓冲区
	@参数		iLength		-- 已发送数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
	事件定义 virtual EnHandleResult OnSend(IUdpNode* pSender, LPCTSTR lpszRemoteAddress, USHORT usRemotePort, const BYTE* pData, int iLength)	{return HR_IGNORE;}
	/*@声明
	@别名 关闭通信组件通知(事件源对象)
	@备注 描述：通信组件关闭时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnShutdown(IUdpNode* pSender)																				{return HR_IGNORE;}
};
//@分组}
#endif

/*****************************************************************************************************************************************************/
/****************************************************************** HTTP Interfaces ******************************************************************/
/*****************************************************************************************************************************************************/

#ifdef _HTTP_SUPPORT
//@分组{ HTTP
/************************************************************************
名称：复合 Http 组件接口
描述：定义复合 Http 组件的所有操作方法和属性访问方法，复合 Http 组件同时管理多个 Http 连接
************************************************************************/
//@别名 HP复合HTTP
class IComplexHttp
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 启动HTTP通信(连接ID)
	@备注 当通信组件设置为非自动启动 HTTP 通信时，需要调用本方法启动 HTTP 通信

	@参数		dwConnID		-- 连接 ID
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL StartHttp(CONNID dwConnID)												= 0;

	/*@声明
	@别名 发送数据分片(连接ID,数据分片,长度,扩展属性)
	@备注 向对端发送 Chunked 数据分片

	@参数		dwConnID		-- 连接 ID
	@参数		pData			-- Chunked 数据分片
	@参数		iLength			-- 数据分片长度（为 0 表示结束分片）
	@参数		lpszExtensions	-- 扩展属性（默认：nullptr）
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL SendChunkData(CONNID dwConnID, const BYTE* pData = nullptr, int iLength = 0, LPCSTR lpszExtensions = nullptr)	= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置本地协议版本 */
	//@别名 置本地协议版本(版本)
	virtual void SetLocalVersion(EnHttpVersion usVersion)								= 0;
	/* 获取本地协议版本 */
	//@别名 取本地协议版本()
	virtual EnHttpVersion GetLocalVersion()												= 0;

	/* 检查是否升级协议 */
	//@别名 是否升级协议(连接ID)
	virtual BOOL IsUpgrade(CONNID dwConnID)												= 0;
	//@备注 检查是否有 Keep-Alive 标识 
	//@别名 是否有标识(连接ID)
	virtual BOOL IsKeepAlive(CONNID dwConnID)											= 0;
	/* 获取协议版本 */
	//@别名 取协议版本(连接ID)
	virtual USHORT GetVersion(CONNID dwConnID)											= 0;
	/* 获取内容长度 */
	//@别名 取内容长度(连接ID)
	virtual ULONGLONG GetContentLength(CONNID dwConnID)									= 0;
	/* 获取内容类型 */
	//@别名 取内容类型(连接ID)
	virtual LPCSTR GetContentType(CONNID dwConnID)										= 0;
	/* 获取内容编码 */
	//@别名 取内容编码(连接ID)
	virtual LPCSTR GetContentEncoding(CONNID dwConnID)									= 0;
	/* 获取传输编码 */
	//@别名 取传输编码(连接ID)
	virtual LPCSTR GetTransferEncoding(CONNID dwConnID)									= 0;
	/* 获取协议升级类型 */
	//@别名 取协议升级类型(连接ID)
	virtual EnHttpUpgradeType GetUpgradeType(CONNID dwConnID)							= 0;
	/* 获取解析错误代码 */
	//@别名 取解析错误代码()
	virtual USHORT GetParseErrorCode(CONNID dwConnID, LPCSTR* lpszErrorDesc = nullptr)	= 0;

	/* 获取某个请求头（单值） */
	//@别名 取某个请求头_单值()
	virtual BOOL GetHeader(CONNID dwConnID, LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	//@备注 获取某个请求头（多值）
	//@别名 取某个请求头_多值()
	virtual BOOL GetHeaders(CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue[], DWORD& dwCount)	= 0;
	/* 获取所有请求头 */
	//@别名 取所有请求头()
	virtual BOOL GetAllHeaders(CONNID dwConnID, THeader lpHeaders[], DWORD& dwCount)				= 0;
	/* 获取所有请求头名称 */
	//@别名 取所有请求头名称()
	virtual BOOL GetAllHeaderNames(CONNID dwConnID, LPCSTR lpszName[], DWORD& dwCount)				= 0;

	/* 获取 Cookie */
	//@别名 取Cookie()
	virtual BOOL GetCookie(CONNID dwConnID, LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	/* 获取所有 Cookie */
	//@别名 取所有Cookie()
	virtual BOOL GetAllCookies(CONNID dwConnID, TCookie lpCookies[], DWORD& dwCount)				= 0;

	/*
	// !! maybe implemented in future !! //

	virtual BOOL GetParam(CONNID dwConnID, LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	virtual BOOL GetParams(CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue[], DWORD& dwCount)	= 0;
	virtual BOOL GetAllParams(CONNID dwConnID, LPPARAM lpszParam[], DWORD& dwCount)					= 0;
	virtual BOOL GetAllParamNames(CONNID dwConnID, LPCSTR lpszName[], DWORD& dwCount)				= 0;
	*/

	//@备注 获取当前 WebSocket 消息状态，传入 nullptr 则不获取相应字段
	//@别名 取当前Web消息状态()
	virtual BOOL GetWSMessageState(CONNID dwConnID, BOOL* lpbFinal, BYTE* lpiReserved, BYTE* lpiOperationCode, LPCBYTE* lpszMask, ULONGLONG* lpullBodyLen, ULONGLONG* lpullBodyRemain)	= 0;

	//@备注 设置 HTTP 启动方式（默认：TRUE，自动启动）
	//@别名 置启动方式(方式)
	virtual void SetHttpAutoStart(BOOL bAutoStart)													= 0;
	/* 获取 HTTP 启动方式 */
	//@别名 取启动方式()
	virtual BOOL IsHttpAutoStart()																	= 0;

public:
	virtual ~IComplexHttp() {}
};

/************************************************************************
名称：复合 Http 请求者组件接口
描述：定义复合 Http 请求者组件的所有操作方法和属性访问方法
************************************************************************/
//@别名 HP复合HTTP请求
class IComplexHttpRequester : public IComplexHttp
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 发送Web消息(连接ID,是否结束帧,RSV,操作码,掩码,消息体数据缓冲区,消息体数据长度,消息总长度)
	@备注 描述：向对端端发送 WebSocket 消息

	@参数		dwConnID		-- 连接 ID
	@参数		bFinal			-- 是否结束帧
	@参数		iReserved		-- RSV1/RSV2/RSV3 各 1 位
	@参数		iOperationCode	-- 操作码：0x0 - 0xF
	@参数		lpszMask		-- 掩码（nullptr 或 4 字节掩码，如果为 nullptr 则没有掩码）
	@参数		pData			-- 消息体数据缓冲区
	@参数		iLength			-- 消息体数据长度
	@参数		ullBodyLen		-- 消息总长度
	//								ullBodyLen = 0		 -> 消息总长度为 iLength
	//								ullBodyLen = iLength -> 消息总长度为 ullBodyLen
	// 								ullBodyLen > iLength -> 消息总长度为 ullBodyLen，后续消息体长度为 ullBOdyLen - iLength，后续消息体通过底层方法 Send() / SendPackets() 发送
	//								ullBodyLen < iLength -> 错误参数，发送失败
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL SendWSMessage(CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], const BYTE* pData = nullptr, int iLength = 0, ULONGLONG ullBodyLen = 0)	= 0;

	/*@声明
	@别名 发送请求(连接ID,请求方法,请求路径,请求头,请求头数量,请求体,请求体长度)
	@备注 描述：向服务端发送 HTTP 请求

	@参数		dwConnID		-- 连接 ID
	@参数		lpszMethod		-- 请求方法
	@参数		lpszPath		-- 请求路径
	@参数		lpHeaders		-- 请求头
	@参数		iHeaderCount	-- 请求头数量
	@参数		pBody			-- 请求体
	@参数		iLength			-- 请求体长度
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL SendRequest(CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0, const BYTE* pBody = nullptr, int iLength = 0)				= 0;

	/*@声明
	@别名 发送本地文件(连接ID,文件路径,请求方法,请求路径,请求头,请求头数量)
	@备注 描述：向指定连接发送 4096 KB 以下的小文件

	@参数		dwConnID		-- 连接 ID
	@参数		lpszFileName	-- 文件路径
	@参数		lpszMethod		-- 请求方法
	@参数		lpszPath		-- 请求路径
	@参数		lpHeaders		-- 请求头
	@参数		iHeaderCount	-- 请求头数量
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL SendLocalFile(CONNID dwConnID, LPCSTR lpszFileName, LPCSTR lpszMethod, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)							= 0;

	/* 发送 POST 请求 */
	//@别名 发送POST请求()
	virtual BOOL SendPost(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)													= 0;
	/* 发送 PUT 请求 */
	//@别名 发送PUT请求()
	virtual BOOL SendPut(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)														= 0;
	/* 发送 PATCH 请求 */
	//@别名 发送PATCH请求()
	virtual BOOL SendPatch(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)													= 0;
	/* 发送 GET 请求 */
	//@别名 发送GET请求()
	virtual BOOL SendGet(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 DELETE 请求 */
	//@别名 发送DELETE请求()
	virtual BOOL SendDelete(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																	= 0;
	/* 发送 HEAD 请求 */
	//@别名 发送HEAD请求()
	virtual BOOL SendHead(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 TRACE 请求 */
	//@别名 发送TRACE请求()
	virtual BOOL SendTrace(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 OPTIONS 请求 */
	//@别名 发送OPTIONS请求()
	virtual BOOL SendOptions(CONNID dwConnID, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																	= 0;
	/* 发送 CONNECT 请求 */
	//@别名 发送CONNECT请求()
	virtual BOOL SendConnect(CONNID dwConnID, LPCSTR lpszHost, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																	= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 获取 HTTP 状态码 */
	//@别名 取HTTP状态码()
	virtual USHORT GetStatusCode(CONNID dwConnID)						= 0;

	/* 设置是否使用 Cookie（默认：TRUE） */
	//@别名 置是否使用Cookie()
	virtual void SetUseCookie(BOOL bUseCookie)							= 0;
	/* 检查是否使用 Cookie */
	//@别名 是否使用Cookie()
	virtual BOOL IsUseCookie()											= 0;
};

/************************************************************************
名称：复合 Http 响应者组件接口
描述：定义复合 Http 响应者组件的所有操作方法和属性访问方法
************************************************************************/
//@别名 HP复合HTTP响应
class IComplexHttpResponder : public IComplexHttp
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 发送Web消息(连接ID,是否结束帧,RSV,操作码,消息体数据缓冲区,消息体数据长度,消息总长度)
	@备注 描述：向对端端发送 WebSocket 消息

	@参数		dwConnID		-- 连接 ID
	@参数		bFinal			-- 是否结束帧
	@参数		iReserved		-- RSV1/RSV2/RSV3 各 1 位
	@参数		iOperationCode	-- 操作码：0x0 - 0xF
	@参数		pData			-- 消息体数据缓冲区
	@参数		iLength			-- 消息体数据长度
	@参数		ullBodyLen		-- 消息总长度
	// 								ullBodyLen = 0		 -> 消息总长度为 iLength
	//								ullBodyLen = iLength -> 消息总长度为 ullBodyLen
	//								ullBodyLen > iLength -> 消息总长度为 ullBodyLen，后续消息体长度为 ullBOdyLen - iLength，后续消息体通过底层方法 Send() / SendPackets() 发送
	//								ullBodyLen < iLength -> 错误参数，发送失败
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL SendWSMessage(CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE* pData = nullptr, int iLength = 0, ULONGLONG ullBodyLen = 0)	= 0;

	/*@声明
	@别名 回复请求(连接ID,状态码,状态描述,回复请求头,回复请求头数量,回复请求体,回复请求体长度)
	@备注 描述：向客户端回复 HTTP 请求

	@参数		dwConnID		-- 连接 ID
	@参数		usStatusCode	-- HTTP 状态码
	@参数		lpszDesc		-- HTTP 状态描述
	@参数		lpHeaders		-- 回复请求头
	@参数		iHeaderCount	-- 回复请求头数量
	@参数		pData			-- 回复请求体
	@参数		iLength			-- 回复请求体长度
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL SendResponse(CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc = nullptr, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0, const BYTE* pData = nullptr, int iLength = 0)	= 0;

	/*@声明
	@别名 发送本地文件(连接ID,文件路径,状态码,状态描述,回复请求头,回复请求头数量)
	@备注 描述：向指定连接发送 4096 KB 以下的小文件

	@参数		dwConnID		-- 连接 ID
	@参数		lpszFileName	-- 文件路径
	@参数		usStatusCode	-- HTTP 状态码
	@参数		lpszDesc		-- HTTP 状态描述
	@参数		lpHeaders		-- 回复请求头
	@参数		iHeaderCount	-- 回复请求头数量
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL SendLocalFile(CONNID dwConnID, LPCSTR lpszFileName, USHORT usStatusCode = HSC_OK, LPCSTR lpszDesc = nullptr, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)				= 0;

	/*@声明
	@别名 释放连接(连接ID)
	@备注 描述：把连接放入释放队列，等待某个时间（通过 SetReleaseDelay() 设置）关闭连接

	@参数		dwConnID		-- 连接 ID
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL Release(CONNID dwConnID)								= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 获取主机 */
	//@别名 取主机(连接ID)
	virtual LPCSTR GetHost(CONNID dwConnID)								= 0;

	/* 设置连接释放延时（默认：3000 毫秒） */
	//@别名 置连接释放延时(延时)
	virtual void SetReleaseDelay(DWORD dwReleaseDelay)					= 0;
	/* 获取连接释放延时 */
	//@别名 取连接释放延时()
	virtual DWORD GetReleaseDelay()										= 0;

	/* 获取请求行 URL 域掩码（URL 域参考：EnHttpUrlField） */
	//@别名 取请求行URL域掩码()
	virtual USHORT GetUrlFieldSet(CONNID dwConnID)						= 0;
	/* 获取某个 URL 域值 */
	//@别名 取某个URL域值()
	virtual LPCSTR GetUrlField(CONNID dwConnID, EnHttpUrlField enField)	= 0;
	/* 获取请求方法 */
	//@别名 取请求方法()
	virtual LPCSTR GetMethod(CONNID dwConnID)							= 0;
};

/************************************************************************
名称：简单 HTTP 组件接口
描述：定义 简单 HTTP 组件的所有操作方法和属性访问方法
************************************************************************/
//@别名 HP_HTTP
class IHttp
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 发送Web消息(是否结束帧,RSV,操作码,掩码,消息体数据缓冲区,消息体数据长度,消息总长度)
	@备注 描述：向对端端发送 WebSocket 消息

	@参数		bFinal			-- 是否结束帧
	@参数		iReserved		-- RSV1/RSV2/RSV3 各 1 位
	@参数		iOperationCode	-- 操作码：0x0 - 0xF
	@参数		lpszMask		-- 掩码（nullptr 或 4 字节掩码，如果为 nullptr 则没有掩码）
	@参数		pData			-- 消息体数据缓冲区
	@参数		iLength			-- 消息体数据长度
	@参数		ullBodyLen		-- 消息总长度
	// 								ullBodyLen = 0		 -> 消息总长度为 iLength
	//								ullBodyLen = iLength -> 消息总长度为 ullBodyLen
	//								ullBodyLen > iLength -> 消息总长度为 ullBodyLen，后续消息体长度为 ullBOdyLen - iLength，后续消息体通过底层方法 Send() / SendPackets() 发送
	//								ullBodyLen < iLength -> 错误参数，发送失败
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL SendWSMessage(BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], const BYTE* pData = nullptr, int iLength = 0, ULONGLONG ullBodyLen = 0)	= 0;

	/*@声明
	@别名 启动HTTP通信()
	@备注 描述：当通信组件设置为非自动启动 HTTP 通信时，需要调用本方法启动 HTTP 通信

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取失败原因
	*/
	virtual BOOL StartHttp()											= 0;

	/*@声明
	@别名 发送数据分片(数据分片,数据分片长度,扩展属性)
	@备注 描述：向对端发送 Chunked 数据分片

	@参数		pData			-- Chunked 数据分片
	@参数		iLength			-- 数据分片长度（为 0 表示结束分片）
	@参数		lpszExtensions	-- 扩展属性（默认：nullptr）
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL SendChunkData(const BYTE* pData = nullptr, int iLength = 0, LPCSTR lpszExtensions = nullptr)	= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置本地协议版本 */
	//@别名 置本地协议版本()
	virtual void SetLocalVersion(EnHttpVersion usVersion)				= 0;
	/* 获取本地协议版本 */
	//@别名 取本地协议版本()
	virtual EnHttpVersion GetLocalVersion()								= 0;

	/* 检查是否升级协议 */
	//@别名 是否升级协议()
	virtual BOOL IsUpgrade()											= 0;
	/* 检查是否有 Keep-Alive 标识 */
	//@别名 是否有KeepAlive标识()
	virtual BOOL IsKeepAlive()											= 0;
	/* 获取协议版本 */
	//@别名 取协议版本()
	virtual USHORT GetVersion()											= 0;
	/* 获取内容长度 */
	//@别名 取内容长度()
	virtual ULONGLONG GetContentLength()								= 0;
	/* 获取内容类型 */
	//@别名 取内容类型()
	virtual LPCSTR GetContentType()										= 0;
	/* 获取内容编码 */
	//@别名 取内容编码()
	virtual LPCSTR GetContentEncoding()									= 0;
	/* 获取传输编码 */
	//@别名 取传输编码()
	virtual LPCSTR GetTransferEncoding()								= 0;
	/* 获取协议升级类型 */
	//@别名 取协议升级类型()
	virtual EnHttpUpgradeType GetUpgradeType()							= 0;
	/* 获取解析错误代码 */
	//@别名 取解析错误代码()
	virtual USHORT GetParseErrorCode(LPCSTR* lpszErrorDesc = nullptr)	= 0;

	/* 获取 HTTP 状态码 */
	//@别名 取HTTP状态码()
	virtual USHORT GetStatusCode()										= 0;

	/* 获取某个请求头（单值） */
	//@别名 取某个请求头_单值()
	virtual BOOL GetHeader(LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	/* 获取某个请求头（多值） */
	//@别名 取某个请求头_多值()
	virtual BOOL GetHeaders(LPCSTR lpszName, LPCSTR lpszValue[], DWORD& dwCount)	= 0;
	/* 获取所有请求头 */
	//@别名 取所有请求头()
	virtual BOOL GetAllHeaders(THeader lpHeaders[], DWORD& dwCount)					= 0;
	/* 获取所有请求头名称 */
	//@别名 取所有请求头名称()
	virtual BOOL GetAllHeaderNames(LPCSTR lpszName[], DWORD& dwCount)				= 0;

	/* 获取 Cookie */
	//@别名 取Cookie()
	virtual BOOL GetCookie(LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	/* 获取所有 Cookie */
	//@别名 取所有Cookie()
	virtual BOOL GetAllCookies(TCookie lpCookies[], DWORD& dwCount)					= 0;

	/*
	// !! maybe implemented in future !! //

	virtual BOOL GetParam(LPCSTR lpszName, LPCSTR* lpszValue)						= 0;
	virtual BOOL GetParams(LPCSTR lpszName, LPCSTR lpszValue[], DWORD& dwCount)		= 0;
	virtual BOOL GetAllParams(LPPARAM lpszParam[], DWORD& dwCount)					= 0;
	virtual BOOL GetAllParamNames(LPCSTR lpszName[], DWORD& dwCount)				= 0;
	*/

	//@备注 获取当前 WebSocket 消息状态，传入 nullptr 则不获取相应字段
	//@别名 取当前Web消息状态()
	virtual BOOL GetWSMessageState(BOOL* lpbFinal, BYTE* lpiReserved, BYTE* lpiOperationCode, LPCBYTE* lpszMask, ULONGLONG* lpullBodyLen, ULONGLONG* lpullBodyRemain)	= 0;

	//@备注 设置 HTTP 启动方式（默认：TRUE，自动启动）
	//@别名 置启动方式(方式)
	virtual void SetHttpAutoStart(BOOL bAutoStart)									= 0;
	/* 获取 HTTP 启动方式 */
	//@别名 取启动方式()
	virtual BOOL IsHttpAutoStart()													= 0;

public:
	virtual ~IHttp() {}
};

/************************************************************************
名称：简单 Http 请求者组件接口
描述：定义简单 Http 请求者组件的所有操作方法和属性访问方法
************************************************************************/
//@别名 HP_HTTP请求
class IHttpRequester : public IHttp
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@备注 名称：发送请求
	// 描述：向服务端发送 HTTP 请求

	@参数		lpszMethod		-- 请求方法
	@参数		lpszPath		-- 请求路径
	@参数		lpHeaders		-- 请求头
	@参数		iHeaderCount	-- 请求头数量
	@参数		pBody			-- 请求体
	@参数		iLength			-- 请求体长度
	@返回	TRUE			-- 成功
	//			FALSE			-- 失败
	@别名  发送请求(请求方法, 请求路径, 请求头, 请求头数量, 请求体, 请求体长度)
	*/
	virtual BOOL SendRequest(LPCSTR lpszMethod, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0, const BYTE* pBody = nullptr, int iLength = 0)	= 0;

	/*@声明
	@别名 发送本地文件(连接ID,文件路径,请求方法,请求路径,请求头,请求头数量)
	@备注 描述：向指定连接发送 4096 KB 以下的小文件

	@参数		dwConnID		-- 连接 ID
	@参数		lpszFileName	-- 文件路径
	@参数		lpszMethod		-- 请求方法
	@参数		lpszPath		-- 请求路径
	@参数		lpHeaders		-- 请求头
	@参数		iHeaderCount	-- 请求头数量
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL SendLocalFile(LPCSTR lpszFileName, LPCSTR lpszMethod, LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)							= 0;

	/* 发送 POST 请求 */
	//@别名 发送POST请求()
	virtual BOOL SendPost(LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)														= 0;
	/* 发送 PUT 请求 */
	//@别名 发送PUT请求()
	virtual BOOL SendPut(LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)														= 0;
	/* 发送 PATCH 请求 */
	//@别名 发送PATCH请求()
	virtual BOOL SendPatch(LPCSTR lpszPath, const THeader lpHeaders[], int iHeaderCount, const BYTE* pBody, int iLength)													= 0;
	/* 发送 GET 请求 */
	//@别名 发送GET请求()
	virtual BOOL SendGet(LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 DELETE 请求 */
	//@别名 发送DELETE请求()
	virtual BOOL SendDelete(LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 HEAD 请求 */
	//@别名 发送HEAD请求()
	virtual BOOL SendHead(LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 TRACE 请求 */
	//@别名 发送TRACE请求()
	virtual BOOL SendTrace(LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																		= 0;
	/* 发送 OPTIONS 请求 */
	//@别名 发送OPTIONS请求()
	virtual BOOL SendOptions(LPCSTR lpszPath, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																	= 0;
	/* 发送 CONNECT 请求 */
	//@别名 发送CONNECT请求()
	virtual BOOL SendConnect(LPCSTR lpszHost, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0)																	= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 设置是否使用 Cookie（默认：TRUE） */
	//@别名 置是否使用Cookie(是否使用)
	virtual void SetUseCookie(BOOL bUseCookie)								= 0;
	/* 检查是否使用 Cookie */
	//@别名 是否使用Cookie()
	virtual BOOL IsUseCookie()												= 0;
};

/************************************************************************
名称：简单 Http 同步请求者组件接口
描述：定义简单 Http 同步请求者组件的所有操作方法和属性访问方法
************************************************************************/
//@别名 HP_HTTP同步请求
class IHttpSyncRequester : public IHttpRequester
{
public:

	/*@声明
	@别名 发送URL请求(请求方法,请求URL,请求头,请求头数量,请求体,请求体长度,强制重新连接)
	@备注 描述：向服务端发送 HTTP URL 请求

	@参数		lpszMethod		-- 请求方法
	@参数		lpszUrl			-- 请求 URL
	@参数		lpHeaders		-- 请求头
	@参数		iHeaderCount	-- 请求头数量
	@参数		pBody			-- 请求体
	@参数		iLength			-- 请求体长度
	@参数		bForceReconnect	-- 强制重新连接（默认：FALSE，当请求 URL 的主机和端口与现有连接一致时，重用现有连接）
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL OpenUrl(LPCSTR lpszMethod, LPCSTR lpszUrl, const THeader lpHeaders[] = nullptr, int iHeaderCount = 0, const BYTE* pBody = nullptr, int iLength = 0, BOOL bForceReconnect = FALSE)	= 0;

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 清除请求结果()
	@备注 描述：清除上一次请求的响应头和响应体等结果信息（该方法会在每次发送请求前自动调用）
	
	@参数		
	@返回	TRUE			-- 成功
	//		FALSE			-- 失败
	*/
	virtual BOOL CleanupRequestResult	()									= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 设置连接超时（毫秒，0：系统默认超时，默认：5000）
	//@别名 置连接超时(时间)
	virtual void SetConnectTimeout		(DWORD dwConnectTimeout)			= 0;
	//@备注 设置请求超时（毫秒，0：无限等待，默认：10000）
	//@别名 置请求超时(时间)
	virtual void SetRequestTimeout		(DWORD dwRequestTimeout)			= 0;

	/* 获取连接超时 */
	//@别名 取连接超时()
	virtual DWORD GetConnectTimeout		()									= 0;
	/* 获取请求超时 */
	//@别名 取请求超时()
	virtual DWORD GetRequestTimeout		()									= 0;

	/* 获取响应体 */
	//@别名 取响应体()
	virtual BOOL GetResponseBody		(LPCBYTE* lpszBody, int* iLength)	= 0;
};


/************************************************************************
名称：HTTP 组件接口
描述：继承了 HTTP 和 Socket 接口
************************************************************************/
//@隐藏{
typedef DualInterface<IComplexHttpResponder, ITcpServer>	IHttpServer;
typedef DualInterface<IComplexHttpRequester, ITcpAgent>		IHttpAgent;
typedef DualInterface<IHttpRequester, ITcpClient>			IHttpClient;
typedef DualInterface<IHttpSyncRequester, ITcpClient>		IHttpSyncClient;
//@隐藏}

/************************************************************************
名称：IComplexHttp 组件监听器基接口
描述：定义 IComplexHttp 组件监听器的所有事件
************************************************************************/

template<class T> class IHttpListenerT
{
public:

	/*@声明
	@别名 开始解析通知()
	@备注 描述：开始解析 HTTP 报文时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnMessageBegin(T* pSender, CONNID dwConnID)										= 0;

	/*@声明
	@别名 请求行解析完成通知(事件源对象,连接ID,请求方法名,URL域)
	@备注 描述：请求行解析完成后，向监听器发送该通知（仅用于 HTTP 服务端）

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		lpszMethod	-- 请求方法名
	@参数		lpszUrl		-- 请求行中的 URL 域
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnRequestLine(T* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)		= 0;

	/*@声明
	@别名 状态行解析完成通知(事件源对象,连接ID,状态码,状态描述)
	@备注 描述：状态行解析完成后，向监听器发送该通知（仅用于 HTTP 客户端）

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		usStatusCode	-- HTTP 状态码
	@参数		lpszDesc		-- 状态描述
	@返回	HPR_OK			-- 继续执行
	//		HPR_ERROR		-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnStatusLine(T* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc)	= 0;

	/*@声明
	@别名 请求头通知(事件源对象,连接ID,请求头名称,请求头值)
	@备注 描述：每当解析完成一个请求头后，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		lpszName	-- 请求头名称
	@参数		lpszValue	-- 请求头值
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnHeader(T* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)			= 0;

	/*@声明
	@别名 请求头完成通知()
	@备注 描述：解析完成所有请求头后，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@返回	HPR_OK			-- 继续执行
	//		HPR_SKIP_BODY	-- 跳过当前请求的 HTTP BODY
	//		HPR_UPGRADE		-- 升级协议
	//		HPR_ERROR		-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnHeadersComplete(T* pSender, CONNID dwConnID)									= 0;

	/*@声明
	@别名 BODY报文通知()
	@备注 描述：每当接收到 HTTP BODY 报文，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 数据缓冲区
	@参数		iLength		-- 数据长度
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnBody(T* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				= 0;

	/*@声明
	@别名 Chunked报文头通知(事件源对象,连接ID,报文体数据长度)
	@备注 描述：每当解析出一个 Chunked 报文头，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- Chunked 报文体数据长度
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnChunkHeader(T* pSender, CONNID dwConnID, int iLength)							= 0;

	/*@声明
	@别名 Chunked报文结束通知(事件源对象,连接ID)
	@备注 描述：每当解析完一个 Chunked 报文，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnChunkComplete(T* pSender, CONNID dwConnID)										= 0;

	/*@声明
	@别名 完成解析通知(事件源对象,连接ID)
	@备注 描述：每当解析完成一个完整 HTTP 报文，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnMessageComplete(T* pSender, CONNID dwConnID)									= 0;

	/*@声明
	@别名 升级协议通知(事件源对象,连接ID,协议类型)
	@备注 描述：当需要升级协议时，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		enUpgradeType	-- 协议类型
	@返回	HPR_OK			-- 继续执行
	//		HPR_ERROR		-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnUpgrade(T* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)			= 0;

	/*@声明
	@别名 解析错误通知(事件源对象,连接ID,错误代码,错误描述)
	@备注 描述：当解析 HTTP 报文错误时，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		iErrorCode		-- 错误代码
	@参数		lpszErrorDesc	-- 错误描述
	@返回	HPR_OK			-- 继续执行
	//		HPR_ERROR		-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHttpParseResult OnParseError(T* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc)	= 0;

	/*@声明
	@别名 Web数据包头通知(事件源对象,连接ID,是否结束帧,RSV,操作码,掩码,消息体长度)
	@备注 描述：当解析 WebSocket 数据包头时，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		bFinal			-- 是否结束帧
	@参数		iReserved		-- RSV1/RSV2/RSV3 各 1 位
	@参数		iOperationCode	-- 操作码：0x0 - 0xF
	@参数		lpszMask		-- 掩码（nullptr 或 4 字节掩码，如果为 nullptr 则没有掩码）
	@参数		ullBodyLen		-- 消息体长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnWSMessageHeader(T* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)	= 0;

	/*@声明
	@别名 Web数据包体通知(事件源对象,连接ID,消息体数据缓冲区,消息体数据长度)
	@备注 描述：当接收到 WebSocket 数据包体时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 消息体数据缓冲区
	@参数		iLength		-- 消息体数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnWSMessageBody(T* pSender, CONNID dwConnID, const BYTE* pData, int iLength)			= 0;

	/*@声明
	@别名 Web数据包完成通知(事件源对象,连接ID)
	@备注 描述：当完整接收一个 WebSocket 数据包时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	virtual EnHandleResult OnWSMessageComplete(T* pSender, CONNID dwConnID)										= 0;

public:
	virtual ~IHttpListenerT() {}
};

/************************************************************************
名称：IHttpServer 组件端监听器接口
描述：定义 IHttpServer 监听器的所有事件
************************************************************************/
//@别名 HP_HTTP服务器监听器
class IHttpServerListener : public IHttpListenerT<IHttpServer>, public ITcpServerListener
{
public:

};

/************************************************************************
名称：IHttpAgent 组件端监听器接口
描述：定义 IHttpAgent 监听器的所有事件
************************************************************************/
//@别名 HP_HTTP代理监听器
class IHttpAgentListener : public IHttpListenerT<IHttpAgent>, public ITcpAgentListener
{
public:

};

/************************************************************************
名称：IHttpClient 组件端监听器接口
描述：定义 IHttpClient 监听器的所有事件
************************************************************************/
//@别名 HP_HTTP客户端监听器
class IHttpClientListener : public IHttpListenerT<IHttpClient>, public ITcpClientListener
{
public:

};

/************************************************************************
名称：IHttpServerListener 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_HTTP服务器监听器_实现
class CHttpServerListener : public IHttpServerListener
{
public:
	/*@声明
	@别名 准备监听通知(事件源对象,监听Socket)
	@备注 描述：通信服务端组件启动时，在监听 Socket 创建完成并开始执行监听前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		soListen	-- 监听 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信服务组件
	*/
	事件定义 virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen)										{return HR_IGNORE;}
	/*@声明
	@别名 接收连接通知(事件源对象,连接ID,soClient)
	@备注 描述：接收到客户端连接请求时，Socket 监听器将收到该通知，监听器可以在通知处理方
	//		法中执行 Socket 选项设置或拒绝客户端连接等额外工作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		soClient	-- TCP: 客户端 Socket 句柄，UDP: 客户端 Socket SOCKADDR 指针
	@返回	HR_OK / HR_IGNORE	-- 接受连接
	//		HR_ERROR			-- 拒绝连接
	*/
	事件定义 virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, UINT_PTR soClient)							{return HR_IGNORE;}
	/*@声明
	@别名 握手完成通知()
	@备注 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始数据收发操作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnHandShake(ITcpServer* pSender, CONNID dwConnID)											{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength)									{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据缓冲区,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已接收数据缓冲区
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				{return HR_IGNORE;}
	/*@声明
	@别名 已发送数据通知(事件源对象,连接ID,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已发送数据缓冲区
	@参数		iLength		-- 已发送数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
	事件定义 virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)					{return HR_IGNORE;}
	/*@声明
	@别名 关闭通信组件通知(事件源对象)
	@备注 描述：通信组件关闭时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnShutdown(ITcpServer* pSender)																{return HR_IGNORE;}

	/*@声明
	@别名 开始解析通知(事件源对象,连接ID)
	@备注 描述：开始解析 HTTP 报文时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnMessageBegin(IHttpServer* pSender, CONNID dwConnID)										{return HPR_OK;}
	/*@声明
	@别名 请求行解析完成通知(事件源对象,连接ID,请求方法名,URL域)
	@备注 描述：请求行解析完成后，向监听器发送该通知（仅用于 HTTP 服务端）

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		lpszMethod	-- 请求方法名
	@参数		lpszUrl		-- 请求行中的 URL 域
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnRequestLine(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)	{return HPR_OK;}
	/*@声明
	@别名 状态行解析完成通知(事件源对象,连接ID,状态码,状态描述)
	@备注 描述：状态行解析完成后，向监听器发送该通知（仅用于 HTTP 客户端）

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		usStatusCode	-- HTTP 状态码
	@参数		lpszDesc		-- 状态描述
	@返回	HPR_OK			-- 继续执行
	//		HPR_ERROR		-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnStatusLine(IHttpServer* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc)	{return HPR_OK;}
	/*@声明
	@别名 请求头通知(事件源对象,连接ID,请求头名称,请求头值)
	@备注 描述：每当解析完成一个请求头后，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		lpszName	-- 请求头名称
	@参数		lpszValue	-- 请求头值
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnHeader(IHttpServer* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)		{return HPR_OK;}
	/*@声明
	@别名 Chunked报文头通知(事件源对象,连接ID,报文体数据长度)
	@备注 描述：每当解析出一个 Chunked 报文头，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- Chunked 报文体数据长度
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnChunkHeader(IHttpServer* pSender, CONNID dwConnID, int iLength)							{return HPR_OK;}
	/*@声明
	@别名 Chunked报文结束通知(事件源对象,连接ID)
	@备注 描述：每当解析完一个 Chunked 报文，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnChunkComplete(IHttpServer* pSender, CONNID dwConnID)									{return HPR_OK;}
	/*@声明
	@别名 升级协议通知(事件源对象,连接ID,协议类型)
	@备注 描述：当需要升级协议时，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		enUpgradeType	-- 协议类型
	@返回	HPR_OK			-- 继续执行
	//		HPR_ERROR		-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnUpgrade(IHttpServer* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)			{return HPR_OK;}

	/*@声明
	@别名 Web数据包头通知(事件源对象,连接ID,是否结束帧,RSV,操作码,掩码,消息体长度)
	@备注 描述：当解析 WebSocket 数据包头时，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		bFinal			-- 是否结束帧
	@参数		iReserved		-- RSV1/RSV2/RSV3 各 1 位
	@参数		iOperationCode	-- 操作码：0x0 - 0xF
	@参数		lpszMask		-- 掩码（nullptr 或 4 字节掩码，如果为 nullptr 则没有掩码）
	@参数		ullBodyLen		-- 消息体长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnWSMessageHeader(IHttpServer* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)	{return HR_IGNORE;}
	/*@声明
	@别名 Web数据包体通知(事件源对象,连接ID,消息体数据缓冲区,消息体数据长度)
	@备注 描述：当接收到 WebSocket 数据包体时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 消息体数据缓冲区
	@参数		iLength		-- 消息体数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnWSMessageBody(IHttpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	/*@声明
	@别名 Web数据包完成通知(事件源对象,连接ID)
	@备注 描述：当完整接收一个 WebSocket 数据包时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnWSMessageComplete(IHttpServer* pSender, CONNID dwConnID)									{return HR_IGNORE;}

	/*@声明
	@别名 关闭通知(事件源对象,连接ID,操作类型,错误代码)
	@备注 描述：通信发生错误后，Socket 监听器将收到该通知，并关闭连接

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		enOperation	-- Socket 操作类型
	@参数		iErrorCode	-- 错误代码
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnClose(IHttpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) { return HR_IGNORE; }
};

/************************************************************************
名称：IHttpAgentListener 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_HTTP代理监听器_实现
class CHttpAgentListener : public IHttpAgentListener
{
public:
	/*@声明
	@别名 准备连接通知(事件源对象,连接ID,Socket)
	@备注 描述：通信客户端组件启动时，在客户端 Socket 创建完成并开始执行连接前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		socket		-- 客户端 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信客户端组件
	*/
	事件定义 virtual EnHandleResult OnPrepareConnect(ITcpAgent* pSender, CONNID dwConnID, SOCKET socket)							{return HR_IGNORE;}
	/*@声明
	@别名 连接完成通知(事件源对象,连接ID)
	@备注 描述：与服务端成功建立连接时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 同步连接：终止启动通信客户端组件
	//							   异步连接：关闭连接
	*/
	事件定义 virtual EnHandleResult OnConnect(ITcpAgent* pSender, CONNID dwConnID)												{return HR_IGNORE;}
	/*@声明
	@别名 握手完成通知()
	@备注 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始数据收发操作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnHandShake(ITcpAgent* pSender, CONNID dwConnID)												{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpAgent* pSender, CONNID dwConnID, int iLength)									{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据缓冲区,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已接收数据缓冲区
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpAgent* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				{return HR_IGNORE;}
	/*@声明
	@别名 已发送数据通知(事件源对象,连接ID,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已发送数据缓冲区
	@参数		iLength		-- 已发送数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
	事件定义 virtual EnHandleResult OnSend(ITcpAgent* pSender, CONNID dwConnID, const BYTE* pData, int iLength)					{return HR_IGNORE;}
	/*@声明
	@别名 关闭通信组件通知(事件源对象)
	@备注 描述：通信组件关闭时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnShutdown(ITcpAgent* pSender)																{return HR_IGNORE;}

	/*@声明
	@别名 开始解析通知(事件源对象,连接ID)
	@备注 描述：开始解析 HTTP 报文时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnMessageBegin(IHttpAgent* pSender, CONNID dwConnID)										{return HPR_OK;}
	/*@声明
	@别名 请求行解析完成通知(事件源对象,连接ID,请求方法名,URL域)
	@备注 描述：请求行解析完成后，向监听器发送该通知（仅用于 HTTP 服务端）

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		lpszMethod	-- 请求方法名
	@参数		lpszUrl		-- 请求行中的 URL 域
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnRequestLine(IHttpAgent* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)	{return HPR_OK;}
	/*@声明
	@别名 状态行解析完成通知(事件源对象,连接ID,状态码,状态描述)
	@备注 描述：状态行解析完成后，向监听器发送该通知（仅用于 HTTP 客户端）

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		usStatusCode	-- HTTP 状态码
	@参数		lpszDesc		-- 状态描述
	@返回	HPR_OK			-- 继续执行
	//		HPR_ERROR		-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnStatusLine(IHttpAgent* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc)	{return HPR_OK;}
	/*@声明
	@别名 请求头通知(事件源对象,连接ID,请求头名称,请求头值)
	@备注 描述：每当解析完成一个请求头后，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		lpszName	-- 请求头名称
	@参数		lpszValue	-- 请求头值
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnHeader(IHttpAgent* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)			{return HPR_OK;}
	/*@声明
	@别名 Chunked报文头通知(事件源对象,连接ID,报文体数据长度)
	@备注 描述：每当解析出一个 Chunked 报文头，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- Chunked 报文体数据长度
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnChunkHeader(IHttpAgent* pSender, CONNID dwConnID, int iLength)							{return HPR_OK;}
	/*@声明
	@别名 Chunked报文结束通知(事件源对象,连接ID)
	@备注 描述：每当解析完一个 Chunked 报文，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnChunkComplete(IHttpAgent* pSender, CONNID dwConnID)										{return HPR_OK;}
	/*@声明
	@别名 升级协议通知(事件源对象,连接ID,协议类型)
	@备注 描述：当需要升级协议时，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		enUpgradeType	-- 协议类型
	@返回	HPR_OK			-- 继续执行
	//		HPR_ERROR		-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnUpgrade(IHttpAgent* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)			{return HPR_OK;}

	/*@声明
	@别名 Web数据包头通知(事件源对象,连接ID,是否结束帧,RSV,操作码,掩码,消息体长度)
	@备注 描述：当解析 WebSocket 数据包头时，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		bFinal			-- 是否结束帧
	@参数		iReserved		-- RSV1/RSV2/RSV3 各 1 位
	@参数		iOperationCode	-- 操作码：0x0 - 0xF
	@参数		lpszMask		-- 掩码（nullptr 或 4 字节掩码，如果为 nullptr 则没有掩码）
	@参数		ullBodyLen		-- 消息体长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnWSMessageHeader(IHttpAgent* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)	{return HR_IGNORE;}
	/*@声明
	@别名 Web数据包体通知(事件源对象,连接ID,消息体数据缓冲区,消息体数据长度)
	@备注 描述：当接收到 WebSocket 数据包体时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 消息体数据缓冲区
	@参数		iLength		-- 消息体数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnWSMessageBody(IHttpAgent* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	/*@声明
	@别名 Web数据包完成通知(事件源对象,连接ID)
	@备注 描述：当完整接收一个 WebSocket 数据包时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnWSMessageComplete(IHttpAgent* pSender, CONNID dwConnID)									{return HR_IGNORE;}
};

/************************************************************************
名称：IHttpClientListener 监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_HTTP客户端监听器_实现
class CHttpClientListener : public IHttpClientListener
{
public:
	/*@声明
	@别名 准备连接通知(事件源对象,连接ID,Socket)
	@备注 描述：通信客户端组件启动时，在客户端 Socket 创建完成并开始执行连接前，Socket 监听
	//		器将收到该通知，监听器可以在通知处理方法中执行 Socket 选项设置等额外工作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		socket		-- 客户端 Socket
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 终止启动通信客户端组件
	*/
	事件定义 virtual EnHandleResult OnPrepareConnect(ITcpClient* pSender, CONNID dwConnID, SOCKET socket)						{return HR_IGNORE;}
	/*@声明
	@别名 连接完成通知(事件源对象,连接ID)
	@备注 描述：与服务端成功建立连接时，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 同步连接：终止启动通信客户端组件
	//							   异步连接：关闭连接
	*/
	事件定义 virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID)												{return HR_IGNORE;}
	/*@声明
	@别名 握手完成通知()
	@备注 描述：连接完成握手时，Socket 监听器将收到该通知，监听器接收到该通知后才能开始数据收发操作

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnHandShake(ITcpClient* pSender, CONNID dwConnID)											{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength)									{return HR_IGNORE;}
	/*@声明
	@别名 数据到达通知(事件源对象,连接ID,已接收数据缓冲区,已接收数据长度)
	@备注 描述：对于 PUSH 模型的 Socket 通信组件，成功接收数据后将向 Socket 监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已接收数据缓冲区
	@参数		iLength		-- 已接收数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				{return HR_IGNORE;}
	/*@声明
	@别名 已发送数据通知(事件源对象,连接ID,已发送数据缓冲区,已发送数据长度)
	@备注 描述：成功发送数据后，Socket 监听器将收到该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 已发送数据缓冲区
	@参数		iLength		-- 已发送数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 该通知不允许返回 HR_ERROR（调试模式下引发断言错误）
	*/
	事件定义 virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)					{return HR_IGNORE;}

	/*@声明
	@别名 开始解析通知(事件源对象,连接ID)
	@备注 描述：开始解析 HTTP 报文时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnMessageBegin(IHttpClient* pSender, CONNID dwConnID)										{return HPR_OK;}
	/*@声明
	@别名 请求行解析完成通知(事件源对象,连接ID,请求方法名,URL域)
	@备注 描述：请求行解析完成后，向监听器发送该通知（仅用于 HTTP 服务端）

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		lpszMethod	-- 请求方法名
	@参数		lpszUrl		-- 请求行中的 URL 域
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnRequestLine(IHttpClient* pSender, CONNID dwConnID, LPCSTR lpszMethod, LPCSTR lpszUrl)	{return HPR_OK;}
	/*@声明
	@别名 状态行解析完成通知(事件源对象,连接ID,状态码,状态描述)
	@备注 描述：状态行解析完成后，向监听器发送该通知（仅用于 HTTP 客户端）

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		usStatusCode	-- HTTP 状态码
	@参数		lpszDesc		-- 状态描述
	@返回	HPR_OK			-- 继续执行
	//		HPR_ERROR		-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnStatusLine(IHttpClient* pSender, CONNID dwConnID, USHORT usStatusCode, LPCSTR lpszDesc)	{return HPR_OK;}
	/*@声明
	@别名 请求头通知(事件源对象,连接ID,请求头名称,请求头值)
	@备注 描述：每当解析完成一个请求头后，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		lpszName	-- 请求头名称
	@参数		lpszValue	-- 请求头值
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnHeader(IHttpClient* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)		{return HPR_OK;}
	/*@声明
	@别名 Chunked报文头通知(事件源对象,连接ID,报文体数据长度)
	@备注 描述：每当解析出一个 Chunked 报文头，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		iLength		-- Chunked 报文体数据长度
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnChunkHeader(IHttpClient* pSender, CONNID dwConnID, int iLength)							{return HPR_OK;}
	/*@声明
	@别名 Chunked报文结束通知(事件源对象,连接ID)
	@备注 描述：每当解析完一个 Chunked 报文，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnChunkComplete(IHttpClient* pSender, CONNID dwConnID)									{return HPR_OK;}
	/*@声明
	@别名 升级协议通知(事件源对象,连接ID,协议类型)
	@备注 描述：当需要升级协议时，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		enUpgradeType	-- 协议类型
	@返回	HPR_OK			-- 继续执行
	//		HPR_ERROR		-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnUpgrade(IHttpClient* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)			{return HPR_OK;}

	/*@声明
	@别名 Web数据包头通知(事件源对象,连接ID,是否结束帧,RSV,操作码,掩码,消息体长度)
	@备注 描述：当解析 WebSocket 数据包头时，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		bFinal			-- 是否结束帧
	@参数		iReserved		-- RSV1/RSV2/RSV3 各 1 位
	@参数		iOperationCode	-- 操作码：0x0 - 0xF
	@参数		lpszMask		-- 掩码（nullptr 或 4 字节掩码，如果为 nullptr 则没有掩码）
	@参数		ullBodyLen		-- 消息体长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnWSMessageHeader(IHttpClient* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)	{return HR_IGNORE;}
	/*@声明
	@别名 Web数据包体通知(事件源对象,连接ID,消息体数据缓冲区,消息体数据长度)
	@备注 描述：当接收到 WebSocket 数据包体时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 消息体数据缓冲区
	@参数		iLength		-- 消息体数据长度
	@返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnWSMessageBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)		{return HR_IGNORE;}
	/*@声明
	@别名 Web数据包完成通知(事件源对象,连接ID)
	@备注 描述：当完整接收一个 WebSocket 数据包时，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	#返回	HR_OK / HR_IGNORE	-- 继续执行
	//		HR_ERROR			-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHandleResult OnWSMessageComplete(IHttpClient* pSender, CONNID dwConnID)									{return HR_IGNORE;}
	/*@声明
	@别名 关闭通知(事件源对象,连接ID,操作类型,错误代码)
	@备注 描述：通信发生错误后，Socket 监听器将收到该通知，并关闭连接

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		enOperation	-- Socket 操作类型
	@参数		iErrorCode	-- 错误代码
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnClose(IHttpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) { return HR_IGNORE; }
};

/************************************************************************
名称：IHttpClientListener 监听器抽象基
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP_HTTP同步客户端监听器_实现
class CHttpSyncClientListener : public CHttpClientListener
{
public:
	/*@声明
	@别名 关闭通知(事件源对象,连接ID,操作类型,错误代码)
	@备注 描述：通信发生错误后，Socket 监听器将收到该通知，并关闭连接

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		enOperation	-- Socket 操作类型
	@参数		iErrorCode	-- 错误代码
	@返回	忽略返回值
	*/
	事件定义 virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)	{return HR_IGNORE;}

	/*@声明
	@别名 请求头完成通知()
	@备注 描述：解析完成所有请求头后，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@返回	HPR_OK			-- 继续执行
	//		HPR_SKIP_BODY	-- 跳过当前请求的 HTTP BODY
	//		HPR_UPGRADE		-- 升级协议
	//		HPR_ERROR		-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnHeadersComplete(IHttpClient* pSender, CONNID dwConnID)									{return HPR_OK;}
	/*@声明
	@别名 BODY报文通知(事件源对象,连接ID,数据缓冲区,数据长度)
	@备注 描述：每当接收到 HTTP BODY 报文，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@参数		pData		-- 数据缓冲区
	@参数		iLength		-- 数据长度
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)				{return HPR_OK;}
	/*@声明
	@别名 完成解析通知(事件源对象,连接ID)
	@备注 描述：每当解析完成一个完整 HTTP 报文，向监听器发送该通知

	@参数		pSender		-- 事件源对象
	@参数		dwConnID	-- 连接 ID
	@返回	HPR_OK		-- 继续执行
	//		HPR_ERROR	-- 引发 OnParserError() 和 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnMessageComplete(IHttpClient* pSender, CONNID dwConnID)									{return HPR_OK;}
	/*@声明
	@别名 解析错误通知(事件源对象,连接ID,错误代码,错误描述)
	@备注 描述：当解析 HTTP 报文错误时，向监听器发送该通知

	@参数		pSender			-- 事件源对象
	@参数		dwConnID		-- 连接 ID
	@参数		iErrorCode		-- 错误代码
	@参数		lpszErrorDesc	-- 错误描述
	@返回	HPR_OK			-- 继续执行
	//		HPR_ERROR		-- 引发 OnClose() 事件并关闭连接
	*/
	事件定义 virtual EnHttpParseResult OnParseError(IHttpClient* pSender, CONNID dwConnID, int iErrorCode, LPCSTR lpszErrorDesc)	{return HPR_OK;}

};
//@分组}
#endif

/*****************************************************************************************************************************************************/
/************************************************************** Thread Pool Interfaces ***************************************************************/
/*****************************************************************************************************************************************************/
//@分组{ HP线程池
/************************************************************************
名称：线程池组件接口
描述：定义线程池组件的所有操作方法和属性访问方法
************************************************************************/
//@别名 HP线程池
class IHPThreadPool
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 启动(线程数量,最大容量,处理策略,空间大小)
	@参数		dwThreadCount		-- 线程数量，（默认：0）
	//									>0 -> dwThreadCount
	//									=0 -> (CPU核数 * 2 + 2)
	//									<0 -> (CPU核数 * (-dwThreadCount))
	@参数		dwMaxQueueSize		-- 任务队列最大容量（默认：0，不限制）
	@参数		enRejectedPolicy	-- 任务拒绝处理策略
	//									TRP_CALL_FAIL（默认）	：立刻返回失败
	//									TRP_WAIT_FOR			：等待（直到成功、超时或线程池关闭等原因导致失败）
	//									TRP_CALLER_RUN			：调用者线程直接执行
	@参数		dwStackSize			-- 线程堆栈空间大小（默认：0 -> 操作系统默认）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Start	(DWORD dwThreadCount = 0, DWORD dwMaxQueueSize = 0, EnRejectedPolicy enRejectedPolicy = TRP_CALL_FAIL, DWORD dwStackSize = 0)	= 0;

	/*@声明
	@别名 关闭(时间)
	@备注 在规定时间内关闭线程池组件，如果工作线程在最大等待时间内未能正常关闭，会尝试强制关闭，这种情况下很可能会造成系统资源泄漏

	@参数		dwMaxWait	-- 最大等待时间（毫秒，默认：INFINITE，一直等待）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Stop	(DWORD dwMaxWait = INFINITE)										= 0;

	/*@声明
	@别名 提交任务(处理函数,任务参数,等待时间)
	@备注 向线程池提交异步任务

	@参数		fnTaskProc	-- 任务处理函数
	@参数		pvArg		-- 任务参数
	@参数		dwMaxWait	-- 任务提交最大等待时间（仅对 TRP_WAIT_FOR 类型线程池生效，默认：INFINITE，一直等待）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	//		其中，错误码 ERROR_DESTINATION_ELEMENT_FULL 表示任务队列已满
	*/
	virtual BOOL Submit	(Fn_TaskProc fnTaskProc, PVOID pvArg, DWORD dwMaxWait = INFINITE)	= 0;

	/*@声明
	@别名 提交Socket任务(任务参数,等待时间)
	@备注 向线程池提交异步 Socket 任务

	@参数		pTask		-- 任务参数
	@参数		dwMaxWait	-- 任务提交最大等待时间（仅对 TRP_WAIT_FOR 类型线程池生效，默认：INFINITE，一直等待）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	//		其中，错误码 ERROR_DESTINATION_ELEMENT_FULL 表示任务队列已满
	//		注意：如果提交失败，需要手工调用 Destroy_HP_SocketTaskObj() 销毁 TSocketTask 对象
	*/
	virtual BOOL Submit	(LPTSocketTask pTask, DWORD dwMaxWait = INFINITE)					= 0;

	/*@声明
	@别名 置线程数量(线程数量)
	@备注 增加或减少线程池的工作线程数量

	@参数		dwNewThreadCount	-- 线程数量
	//								>0 -> dwNewThreadCount
	//								=0 -> (CPU核数 * 2 + 2)
	//								<0 -> (CPU核数 * (-dwNewThreadCount))
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL AdjustThreadCount(DWORD dwNewThreadCount)									= 0;

	/*@声明
	@别名 等待(超时时间)
	@备注 等待线程池组件停止运行

	@参数		dwMilliseconds	-- 超时时间（毫秒，默认：-1，永不超时）
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Wait(DWORD dwMilliseconds = INFINITE)										= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	//@备注 检查线程池组件是否已启动 
	//@别名 是否启动()
	virtual BOOL HasStarted						()	= 0;
	//@备注 查看线程池组件当前状态
	//@别名 当前状态()
	virtual EnServiceState	GetState			()	= 0;
	//@备注 获取当前任务等待队列大小
	//@别名 取当前任务大小()
	virtual DWORD GetQueueSize					()	= 0;
	//@备注 获取当前正在执行的任务数量 
	//@别名 取当前任务数量()
	virtual DWORD GetTaskCount					()	= 0;
	//@备注 获取工作线程数量
	//@别名 取工作线程数量()
	virtual DWORD GetThreadCount				()	= 0;
	//@备注 获取任务队列最大容量 
	//@别名 取任务队列最大容量()
	virtual DWORD GetMaxQueueSize				()	= 0;
	//@备注 获取任务拒绝处理策略 
	//@别名 取任务拒绝处理策略()
	virtual EnRejectedPolicy GetRejectedPolicy	()	= 0;

public:
	virtual ~IHPThreadPool() {};
};

/************************************************************************
名称：线程池监听器接口
描述：定义线程池监听器的所有事件
************************************************************************/
//@别名 HP线程池监听器
class IHPThreadPoolListener
{
public:

	/*@声明
	@别名 线程池启动通知(线程池对象)
	@备注 线程池启动时监听器将收到该通知，监听器可以在通知处理方法中执行预处理工作

	@参数		pThreadPool		-- 线程池对象
	@返回	无
	*/
	virtual void OnStartup(IHPThreadPool* pThreadPool)								= 0;

	/*@声明
	@别名 线程池启动关闭通知(线程池对象)
	@备注 线程池关闭时监听器将收到该通知，监听器可以在通知处理方法中执行后处理工作

	@参数		pThreadPool		-- 线程池对象
	@返回	无
	*/
	virtual void OnShutdown(IHPThreadPool* pThreadPool)								= 0;

	/*@声明
	@别名 工作线程启动通知(线程池对象,工作线程ID)
	@备注 工作线程启动时监听器将收到该通知，监听器可以在通知处理方法中执行线程级别预处理工作

	@参数		pThreadPool		-- 线程池对象
	@参数		dwThreadID		-- 工作线程 ID
	@返回	无
	*/
	virtual void OnWorkerThreadStart(IHPThreadPool* pThreadPool, THR_ID dwThreadID)	= 0;

	/*@声明
	@别名 工作线程退出通知(线程池对象,工作线程ID)
	@备注 工作线程退出时监听器将收到该通知，监听器可以在通知处理方法中执行线程级别后处理工作

	@参数		pThreadPool		-- 线程池对象
	@参数		dwThreadID		-- 工作线程 ID
	@返回	无
	*/
	virtual void OnWorkerThreadEnd(IHPThreadPool* pThreadPool, THR_ID dwThreadID)	= 0;

public:
	virtual ~IHPThreadPoolListener() {};
};

/************************************************************************
名称：线程池监听器抽象基类
描述：定义某些事件的默认处理方法（忽略事件）
************************************************************************/
//@别名 HP线程池监听器_实现
class CHPThreadPoolListener : public IHPThreadPoolListener
{
public:
	//@别名 线程池启动通知(线程池对象)
	//@备注 线程池启动时监听器将收到该通知，监听器可以在通知处理方法中执行预处理工作
	//@参数		pThreadPool		-- 线程池对象
	事件定义 virtual void OnStartup(IHPThreadPool* pThreadPool)								{}
	//@别名 线程池启动关闭通知(线程池对象)
	//@备注 线程池关闭时监听器将收到该通知，监听器可以在通知处理方法中执行后处理工作
	//@参数		pThreadPool		-- 线程池对象
	事件定义 virtual void OnShutdown(IHPThreadPool* pThreadPool)								{}
	//@别名 工作线程启动通知(线程池对象,工作线程ID)
	//@备注 工作线程启动时监听器将收到该通知，监听器可以在通知处理方法中执行线程级别预处理工作		
	//@参数		pThreadPool		-- 线程池对象
	//@参数		dwThreadID		-- 工作线程 ID
	事件定义 virtual void OnWorkerThreadStart(IHPThreadPool* pThreadPool, THR_ID dwThreadID)	{}
	//@别名 工作线程退出通知(线程池对象,工作线程ID)
	//@备注 工作线程退出时监听器将收到该通知，监听器可以在通知处理方法中执行线程级别后处理工作		
	//@参数		pThreadPool		-- 线程池对象
	//@参数		dwThreadID		-- 工作线程 ID
	事件定义 virtual void OnWorkerThreadEnd(IHPThreadPool* pThreadPool, THR_ID dwThreadID)	{}
};
//@分组}
//@分组{ HP辅助类
/*@声明
@别名 HP压缩器
@备注 定义压缩器的所有操作方法和属性访问方法
*/
class IHPCompressor
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@别名 执行()
	@备注 可循环调用以压缩流式或分段数据

	@参数		pData		-- 待压缩数据缓冲区
	@参数		iLength		-- 待压缩数据长度
	@参数		pContext	-- 压缩回调函数 Fn_CompressDataCallback 的上下文参数

	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	*/
	virtual BOOL Process(const BYTE* pData, int iLength, BOOL bLast, PVOID pContext = nullptr)	= 0;

	//@别名 重置()
	virtual BOOL Reset()																		= 0;

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 检测压缩器是否可用 */
	//@别名 是否可用()
	virtual BOOL IsValid()																		= 0;

public:
	virtual ~IHPCompressor() {};
};

/*@声明
@别名 HP解压器
@备注 定义解压器的所有操作方法和属性访问方法
*/
class IHPDecompressor
{
public:

	/***********************************************************************/
	/***************************** 组件操作方法 *****************************/

	/*@声明
	@备注名称：执行解压
	// 可循环调用以解压流式或分段数据

	@参数		pData		-- 待解压数据缓冲区
	@参数		iLength		-- 待解压数据长度
	@参数		pContext	-- 解压回调函数 Fn_DecompressDataCallback 的上下文参数
	
	@返回	TRUE	-- 成功
	//		FALSE	-- 失败，可通过 SYS_GetLastError() 获取错误代码
	//@别名 执行(待解压数据缓冲区,待解压数据长度,解压回调函数)
	*/
	virtual BOOL Process(const BYTE* pData, int iLength, PVOID pContext = nullptr)	= 0;

	//@别名 重置()
	virtual BOOL Reset()															= 0;

public:

	/***********************************************************************/
	/***************************** 属性访问方法 *****************************/

	/* 检测解压器是否可用 */
	//@别名 是否可用()
	virtual BOOL IsValid()															= 0;

public:
	virtual ~IHPDecompressor() {};
};
//@分组}
#include "HPSocket.h"