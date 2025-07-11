#pragma once

//@模块名称  WebSocket
//@版本  1.1 
//@日期  2024-09-10
//@作者  hxznhf
//@QQ   568415950
//@模块备注  提供WebSocket服务端和客户端基础支持（暂不支持WSS）
// 2025-01-10 完善了些细节
// 2024-09-10 更新：修复客户端不能正常使用的bug
//@依赖  module_base.h

//@src "websocket.cpp"
#include "module_base.h"
#include "xc_mkStr.h"


//@隐藏{
//#ifndef XC_WEBSOCKET_H
//#define XC_WEBSOCKET_H
//
//#ifndef HEAD_C965C7E5_C527_413a_BFB4_D0BC1BC42FEB
//#define HEAD_C965C7E5_C527_413a_BFB4_D0BC1BC42FEB
//@隐藏}

//@别名 WebSocket
namespace WebSocket {

// @分组{ 常量定义
//@别名 WS帧类型_连续
#define  WS_OPENING_FRAME  0
//@别名 WS帧类型_错误
#define  WS_ERROR_FRAME  -1
//@别名 WS帧类型_文本
#define  WS_TEXT_FRAME  1
//@别名 WS帧类型_二进制
#define  WS_BINARY_FRAME  2
//@别名 WS帧类型_关闭
#define  WS_CLOSING_FRAME  0x8
//@别名 WS帧类型_PING
#define  WS_PING_FRAME  0x9
//@别名 WS帧类型_PONG
#define  WS_PONG_FRAME  0xA

//@别名 WS连接状态_未连接
#define  WS_STATUS_DISCONNECTED  0
//@别名 WS连接状态_正在连接
#define  WS_STATUS_CONNECTING  1
//@别名 WS连接状态_已连接
#define  WS_STATUS_CONNECTED  2

//@分组}

//@隐藏{
struct 客户;
struct 线程参数;
struct 包信息;
class WS服务端;


static int WSA初始化计数器= 0;
//@隐藏}

// @分组{ 数据类型
struct 客户
{
	//@隐藏{
	SOCKET s;

	bool 握手= false;
	CXTextA buffer{};
	CXTextA bin_buffer{};
	//@隐藏}
	CXTextA IP地址;
	
};
struct WS帧 {

	//@备注 常量 WS帧类型_
	int 类型= 0;
	CXBytes 数据;
};
// @分组}

//@隐藏{
struct 线程参数
{
	WS服务端* server;
	SOCKET s;
};


struct 包信息
{
	int type= 0;
	int ret= 0;
	int opcode;
};
//@隐藏}

//@分组{ 事件定义
typedef void (*WS服务端事件_客户进入)(客户& cilent);
typedef void (*WS服务端事件_客户退出)(客户& cilent);
typedef void (*WS服务端事件_收到数据)(客户& cilent, CXBytes& 数据);
typedef void (*WS服务端事件_收到帧)(客户& cilent, WS帧& 帧);


typedef void (*WS客户端事件_连接成功)();
typedef void (*WS客户端事件_连接断开)();
typedef void (*WS客户端事件_收到数据)(CXBytes& 数据);
typedef void (*WS客户端事件_收到帧)(WS帧& 帧);

//@分组}

// @分组{ WebSocket
//@别名 WebSocket服务端
//@备注 WebSocket服务端（暂不支持WSS）
class WS服务端
{
public:
public:
	void* 事件_客户进入 = 0;
	void* 事件_客户退出 = 0;
	void* 事件_数据到达 = 0;


	//@别名 启动(端口)
	//@备注 启用WebSocket服务端
	//@参数 端口
	BOOL  启动(int 端口);

	//@别名 停止()
	//@备注 关闭WebSocket服务端
	void  停止();

	//@别名 发送文本(客户,文本)
	//@备注 发送文本到指定客户
	//@参数 客户对象
	//@参数 文本数据
	BOOL  发送文本(客户& 客户,const CXTextA& 文本);

	//@别名 发送字节集(客户,字节集)
	//@备注 发送字节集到指定客户
	//@参数 客户对象
	//@参数 字节集数据
	BOOL  发送字节集(客户& 客户,const CXBytes& 数据);

	//@别名 取客户数()
	//@备注 取已连接的客户数
	int  取客户数();

	//@别名 取客户列表(客户列表)
	//@备注 取出已连接的客户对象列表
	int  取客户列表(CXVector<客户*>& 客户列表);

	//@别名 取客户IP(客户)
	//@备注 取出客户IP地址
	//@参数 客户对象
	CXTextA  取客户IP(客户* _客户);


	//@别名 PING(客户)
	//@备注 发送PING给指定客户(心跳请求包)
	//@参数 客户对象
	BOOL  PING(客户* 客户);

	//@别名 PONG(客户)
	//@备注 发送PONG给指定客户(心跳回复包)
	//@参数 客户对象
	BOOL  PONG(客户* 客户);


//@隐藏{
private:
	WSAData wsadata;
	CXVector<客户*>  Clients;
	SOCKET s_server;
	bool 接收连接线程停止= false;
	bool 接收数据线程停止= false;
	CRITICAL_SECTION 许可证_客户列表;
public:
	WS服务端();
	~WS服务端();
private:
	static void  接收连接(线程参数* cs);
	static void  接收数据(线程参数* cs);
	bool  确认握手请求(SOCKET s, const char* buffer, int);
	int  数据帧解码(包信息* outdata, CXTextA buffer, char** lp_outMessage, int* packet_len, bool* end, int* endlen);
	//CXBytes  WS协议_服务器组包(BOOL IsEOf, int Type, BOOL hasMAsk, const char* inMessage, int key);
	int  数据帧编码(const char* 数据, int 长度, CXBytes& bin, int frameType);
	bool  SendText(SOCKET s, CXTextA& 文本);
	//@隐藏}
};



//@隐藏{
CXTextA BASE64_SHA1(CXTextA& data);
//@隐藏}





//@别名 WebSocket客户端
//@备注 WebSocket客户端（暂不支持WSS）
class WS客户端 {
	//@隐藏{
private:
	SOCKET s = 0;
	bool 线程退出 = false;
	CXText 错误信息;
	//连接状态
	int status = WS连接状态_未连接;
	//握手
	bool handshake = false;
	//@隐藏}



public:

	//@备注 回调函数：事件_连接成功()
	void* 事件_连接成功;
	//@备注 回调函数：事件_连接断开()
	void* 事件_连接断开;
	//@备注 回调函数：事件_收到数据(字节集& 消息)
	void* 事件_收到数据;

	//@备注 回调函数：事件_收到帧(WS帧& 帧)
	void* 事件_收到帧;

	//@隐藏{
	WS客户端();
	~WS客户端();
	//@隐藏}

	//@别名 连接(服务地址,异步)
	//@备注 连接到WebSocket服务端（失败返回假,用取错误信息获取失败原因,如果是异步模式,会立即返回真,但不表示连接成功）
	//@备注 异步模式请稍后使用【取连接状态（）】判断连接是否成功
	//@参数 WS服务器地址
	//@参数 使用异步连接模式（返回值无效）
	BOOL 连接(CXTextA 服务地址,BOOL 异步 = FALSE);

	//@别名 断开()
	//@备注 关闭与服务器连接
	void 断开();

	//@别名 发送文本(文本内容)
	//@备注 发送文本到到服务端（失败返回假,用取错误信息获取失败原因）
	//@参数 文本内容
	BOOL 发送文本(CXTextA);

	//@别名 发送字节集(字节集内容)
	//@备注 发送文本到到服务端（失败返回假,用取错误信息获取失败原因）
	//@参数 字节集数据
	BOOL 发送字节集(CXBytes);

	//@别名 取连接状态()
	//@备注 判断连接状态（常量: WS连接状态_）
	int 取连接状态();

	//@别名 取错误信息()
	//@备注 【本命令暂不可用】当执行命令失败时，用此方法获取错误原因
	CXText 取错误信息();

	//@别名 PING()
	//@备注 发送PING数据包到服务端（心跳请求包）
	BOOL PING();

	//@别名 PONG()
	//@备注 发送PONG数据包到服务端（心跳回复包）
	BOOL PONG();


	//@隐藏{
	static int 数据帧编码(const char* 数据, int 长度, CXBytes& bin, int frameType, bool IsEof, bool hasMask);

	static int 数据帧解码(包信息* outdata, const char* frameData, int len, char** lp_outMessage, int* packet_len, bool* end, int* endlen);

	
	static void  接受数据(WS客户端*);
	//@隐藏}


};


//@分组}

}



//#endif
//#endif