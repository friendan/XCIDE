#pragma once
//@隐藏{
#ifndef FiddlerXPL_H
#define FiddlerXPL_H
#include <windows.h>
#include <tchar.h>
#include <functional>
#include <string>
#include <memory>
#define ENABLE_FIDDLERCWRAP_EXTEND  
#include "FiddlerXPL_Typedef.h"
#include "FiddlerCWrap.hpp"

#ifndef  XC_MOUDLE
//#include "C:\Users\Jin\Desktop\炫彩IDE-3.3.5-(2022-07-16)\data\XC-Module\核心模块\基础模块\module_base.h"
#endif

//@隐藏}

//@模块名称 FiddlerXPL
//@版本  0.2.0
//@日期  2022-07-18
//@作者  欧阳逸洛
//@QQ   欧阳逸洛
//@模块备注  FiddlerCore包装; http中间人代理, 读写流过的数据
//项目地址：https://gitee.com/ouyang-yiluo/xpl-fiddler-xpl
//@依赖  module_base.h


#ifdef  _WIN64
//@复制文件 "data\XC-Module\常规\FiddlerXPL\x64\FiddlerCWrap_Extend.dll"
#else
//@复制文件 "data\XC-Module\常规\FiddlerXPL\x86\FiddlerCWrap_Extend.dll"
#endif


/*@声明

*/

//@隐藏{
namespace FiddlerXPL {
	using namespace FiddlerCWrap;

#if _UNICODE
	constexpr auto currentWrapStrEncoding{ WrapStrEncoding::UTF16 };
#else
	constexpr auto currentWrapStrEncoding{ WrapStrEncoding::ANSI };
#endif

	inline CXBytes WrapBytesPtrToCXBytes(WrapBytesPtr wbp) {
		CXBytes bytes;
		if (wbp) {
			bytes.set(const_cast<uint8_t*>(wbp->p), wbp->len);
		}
		return bytes;
	}
	inline WrapBytes CXBytesToWrapBytes(CXBytes& bytes) {
		return { reinterpret_cast<const uint8_t*>(bytes.get()), (ptrdiff_t)bytes.size()};
	}
//@隐藏}
	
	//@别名 FD_加载DLL(dll路径)
	static BOOL FD_Dll_Load(const TCHAR* path) {
		
		try {
			FiddlerCWrap::dll_load(path);
		}
		catch (...) {
			return false;
		}
		return true;
	}

	//@别名 FD_卸载DLL()
	static BOOL FD_Dll_Free() {
		FiddlerCWrap::dll_free();
	}

	//@别名 FD_会话_标志
	class FD_Session_Flags {
		
	public:
		//@隐藏{
		FD_Session_Flags(FD_SessionHandle h)
			:m_handle(h)
		{}
		//@隐藏}


		//@别名 取值(标志)
		const TCHAR* Get_Item(const TCHAR* key) {
			return Fiddler_Session_Flags_Get_Item(m_handle, key);
		}

		//@别名 置值(标志, 值)
		void Set_Item(const TCHAR* key, const TCHAR* value) {
			Fiddler_Session_Flags_Set_Item(m_handle, key, value);
		}

		//@别名 移除(标志)
		const void Remove(const TCHAR* key) {
			Fiddler_Session_Flags_Remove(m_handle, key);
		}

		//@别名 包含(标志)
		const BOOL ContainsKey(const TCHAR* key) {
			return Fiddler_Session_Flags_ContainsKey(m_handle, key);
		}

		//@别名 清空()
		const void Clear() {
			Fiddler_Session_Flags_Clear(m_handle);
		}
	private:
		FD_SessionHandle m_handle;
	};

	//@别名 FD_HTTP头
	class FD_HTTPHeaders {
		friend class FD_Utilities;
	public:
		//@隐藏{
		FD_HTTPHeaders(FD_HTTPHeadersHandle h)
			:m_handle(h) 
		{}
		//@隐藏}
		// 
		//@别名 到文本()
		const TCHAR* ToString() {
			return Fiddler_HTTPHeaders_ToString(m_handle);
		}
		//@别名 从文本赋值(文本)
		BOOL AssignFromString(const TCHAR* value) {
			return Fiddler_HTTPHeaders_AssignFromString(m_handle, value);
		}

		//@别名 取值(键)
		const TCHAR* Get_Item(const TCHAR* name) {
			return Fiddler_HTTPHeaders_Get_Item(m_handle, name);
		}

		//@别名 置值(键, 值)
		void Set_Item(const TCHAR* name, const TCHAR* value) {
			Fiddler_HTTPHeaders_Set_Item(m_handle, name, value);
		}

		//@别名 移除(键)
		void Remove(const TCHAR* name) {
			Fiddler_HTTPHeaders_Remove(m_handle, name);
		}

		//@备注 如果存在指定的键（不区分大小写）,则返回true。
		//@别名 存在(键)
		BOOL Exists(const TCHAR* name) {
			Fiddler_HTTPHeaders_Exists(m_handle, name);
		}

		//@备注 如果存在指定的键（不区分大小写）,并且值（不区分大小写）包含，则返回true。
		//@别名 存在并包含(键, 值)
		BOOL ExistsAndContains(const TCHAR* name, const TCHAR* value) {
			Fiddler_HTTPHeaders_ExistsAndContains(m_handle, name, value);
		}

		//@备注 如果存在指定的键（不区分大小写）,并且值（不区分大小写）相等，则返回true。
		//@别名 存在并相等(键, 值)
		BOOL ExistsAndEquals(const TCHAR* name, const TCHAR* value) {
			Fiddler_HTTPHeaders_ExistsAndEquals(m_handle, name, value);
		}

		//@别名 修改键名(键名, 新键名)
		BOOL RenameHeaderItems(const TCHAR* oldName, const TCHAR* newName) {
			Fiddler_HTTPHeaders_RenameHeaderItems(m_handle, oldName, newName);
		}
	protected:
		FD_HTTPHeadersHandle m_handle = nullptr;
	};

	//@别名 FD_HTTP请求头
	class FD_HTTPRequestHeaders : public FD_HTTPHeaders {
		using FD_HTTPHeaders::FD_HTTPHeaders;
	public:
	
		const TCHAR* Get_UriScheme() {
			return Fiddler_HTTPRequestHeaders_Get_UriScheme(m_handle);
		}

		void Set_UriScheme(const TCHAR* uriScheme) {
			Fiddler_HTTPRequestHeaders_Set_UriScheme(m_handle, uriScheme);
		}
	};

	//@别名 FD_HTTP响应头
	class FD_HTTPResponseHeaders : public FD_HTTPHeaders {
		using FD_HTTPHeaders::FD_HTTPHeaders;
	public:

		//@别名 置状态(状态码, 描述)
		void Set_Status(int32_t code, const TCHAR* description) {
			Fiddler_HTTPResponseHeaders_Set_Status(m_handle, code, description);
		}
	};

	class FD_WebSocket {
	public:
		//@隐藏{
		FD_WebSocket(FD_WebSocketHandle hanlde)
			:m_handle(hanlde)
		{}
		//@隐藏}
		//@备注 此 WebSocket 是否已打开/已连接？
		//@别名 已打开()
		BOOL IsOpen()
		{
			return Fiddler_WebSocket_IsOpen(m_handle);
		}

#ifdef ENABLE_FIDDLERCWRAP_EXTEND
		BOOL SendClientTextMessage(const TCHAR* strPayload)
		{
			return Fiddler_WebSocket_SendClientTextMessage(m_handle, strPayload);
		}

		BOOL SendClientBinaryMessage(CXBytes& bytesPayload)
		{
			auto wb = CXBytesToWrapBytes(bytesPayload);
			return Fiddler_WebSocket_SendClientBinaryMessage(m_handle, &wb);
		}

		BOOL SendServerTextMessage(const TCHAR* strPayload)
		{
			return Fiddler_WebSocket_SendServerTextMessage(m_handle, strPayload);
		}

		BOOL SendServerBinaryMessage(CXBytes& bytesPayload)
		{
			auto wb = CXBytesToWrapBytes(bytesPayload);
			return Fiddler_WebSocket_SendServerBinaryMessage(m_handle, &wb);
		}
#endif //ENABLE_FIDDLERCWRAP_EXTEND
	private:
		FD_WebSocketHandle m_handle;
	};

	//@别名 FD_会话
	class FD_Session {
		friend class FD_SessionList;
	public:
		//@隐藏{
		FD_Session(FD_SessionHandle sessionHandle)
			: m_handle(sessionHandle)
		{}
		//@隐藏}
		// 
		//备注 返回此会话的序号。请注意，默认情况下，当会话列表被清除时，编号会从零重新开始。
		int32_t ID() {
			return Fiddler_Session_ID(m_handle);
		}

		//@备注 常见查询会话属性的位标志
		//@别名 位标志()
		FD_SessionBitFlags BitFlags() {
			return static_cast<FD_SessionBitFlags>(Fiddler_Session_Get_BitFlags(m_handle));
		}

		//备注 如果此会话状态 > ReadingResponse 且 oResponse 不为空，则返回 TRUE。
		//@别名 有响应()
		BOOL HasResponse() {
			return Fiddler_Session_Get_HasResponse(m_handle);
		}

		//备注 检查这是否是 WebSocket，如果是，它是否记录了任何已解析的消息。
		//@别名 有WebSocket消息()
		BOOL HasWebSocketMessages() {
			return Fiddler_Session_Get_HasWebSocketMessages(m_handle);
		}

		//@别名 取缓冲响应()
		BOOL Get_BufferResponse() {
			return Fiddler_Session_Get_BufferResponse(m_handle);
		}

		//@别名 置缓冲响应(值)
		void Set_BufferResponse(BOOL value) {
			Fiddler_Session_Set_BufferResponse(m_handle, value);
		}

		//@备注 在 OnBeforeRequest 内部调用以创建响应对象并绕过服务器
		//@别名 创建响应对象并绕过服务器()
		void CreateResponseAndBypassServer() {
			Fiddler_Session_CreateResponseAndBypassServer(m_handle);
		}

		//@别名 标志()
		FD_Session_Flags Flags() {
			return { m_handle };
		}
		
		//@备注 设置此 Session 的 SessionFlags.Ignore 位，隐藏它并忽略它的流量。
		//@别名 忽略()
		virtual const void Ignore() {
			Fiddler_Session_Ignore(m_handle);
		}

		//@别名 取URL()
		const TCHAR* Get_URL() {
			return Fiddler_Session_Get_Url(m_handle);
		}

		//@别名 置URL(值)
		void Set_URL(const TCHAR* value) {
			Fiddler_Session_Set_Url(m_handle, value);
		}

		//@别名 取完整URL()
		const TCHAR* Get_FullURL() {
			return Fiddler_Session_Get_FullUrl(m_handle);
		}

		//@别名 置完整URL(值)
		void Set_FullURL(const TCHAR* value) {
			Fiddler_Session_Set_FullUrl(m_handle, value);
		}

		//@别名 取主机()
		const TCHAR* Get_Host() {
			return Fiddler_Session_Get_Host(m_handle);
		}

		//@别名 置主机(值)
		void Set_Host(const TCHAR* value) {
			Fiddler_Session_Set_Host(m_handle, value);
		}

		//@别名 取主机名()
		const TCHAR* Get_HostName() {
			return Fiddler_Session_Get_HostName(m_handle);
 		}

		//@别名 置主机名(值)
		void Set_HostName(const TCHAR* value) {
			Fiddler_Session_Set_HostName(m_handle, value);
		}

		//@别名 取主机端口()
		const int32_t Get_HostPort() {
			return Fiddler_Session_Get_HostPort(m_handle);
		}

		//@别名 置主机端口(值)
		void Set_HostPort(int32_t port) {
			Fiddler_Session_Set_HostPort(m_handle, static_cast<int32_t>(port));
		}

		//@别名 取主机IP()
		const TCHAR* Get_HostIP() {
			return Fiddler_Session_Get_HostIP(m_handle);
		}

		//@别名 置主机IP(值)
		void Set_HostIP(const TCHAR* value) {
			Fiddler_Session_Set_HostIP(m_handle, value);
		}

		//@别名 取客户端IP()
		const TCHAR* Get_ClientIP() {
			return Fiddler_Session_Get_ClientIP(m_handle);
		}

		//@别名 置客户端IP()
		const uint16_t Get_ClientPort() {
			return Fiddler_Session_Get_ClientPort(m_handle);
		}

		//@别名 取请求方法()
		const TCHAR* Get_RequestMethod() {
			return Fiddler_Session_Get_RequestMethod(m_handle);
		}

		//@别名 置请求方法(值)
		void Set_RequestMethod(const TCHAR* value) {
			Fiddler_Session_Set_RequestMethod(m_handle, value);
		}

		//@别名 请求头()
		FD_HTTPRequestHeaders RequestHeaders() {
			return { Fiddler_Session_RequestHeaders(m_handle) };
		}

		//@隐藏{
		////@别名 取请求头文本()
		//const TCHAR* Get_RequestHeadersString() {
		//	return Fiddler_Session_Get_RequestHeadersString(m_handle);
		//}

		////@别名 置请求头文本()
		//void Set_RequestHeadersString(const TCHAR* value) {
		//	Fiddler_Session_Set_RequestHeadersString(m_handle, value);
		//}
		//@隐藏}

		//@别名 取请求体文本()
		const TCHAR* Get_RequestBodyString() {
			return Fiddler_Session_Get_RequestBodyString(m_handle);
		}

		//@别名 置请求体文本(值)
		void Set_RequestBodyString(const TCHAR* value) {
			Fiddler_Session_Set_RequestBodyString(m_handle, value);
		}

		//@备注 从请求中删除分块和 HTTP 压缩。添加或更新 Content-Length 标头。
		//@别名 解码请求()
		void DecodeRequest() {
			Fiddler_Session_DecodeRequest(m_handle);
		}

		//@别名 取请求体()
		CXBytes Get_RequestBody() {
			return WrapBytesPtrToCXBytes(Fiddler_Session_Get_RequestBody(m_handle));
		}

		//@别名 置请求体(值)
		void Set_RequestBody(CXBytes& value) {
			auto wb = CXBytesToWrapBytes(value);
			Fiddler_Session_Set_RequestBody(m_handle, &wb);
		}

		//@别名 响应头()
		FD_HTTPResponseHeaders ResponseHeaders() {
			return { Fiddler_Session_ResponseHeaders(m_handle) };
		}

		//@隐藏{
		//const TCHAR* Get_ResponseHeadersString() {
		//	return Fiddler_Session_Get_ResponseHeadersString(m_handle);
		//}


		//void Set_ResponseHeadersString(const TCHAR* value) {
		//	Fiddler_Session_Set_ResponseHeadersString(m_handle, value);
		//}
		//@隐藏}

		//@别名 取响应体文本()
		const TCHAR* Get_ResponseBodyString() {
			return Fiddler_Session_Get_ResponseBodyString(m_handle);
		}

		//@别名 置响应体文本(值)
		void Set_ResponseBodyString(const TCHAR* value) {
			Fiddler_Session_Set_ResponseBodyString(m_handle, value);
		}

		//@备注 从响应中删除分块和 HTTP 压缩。添加或更新 Content-Length 标头。
		//@别名 解码响应()
		void DecodeResponse() {
			Fiddler_Session_DecodeResponse(m_handle);
		}

		//@别名 取响应体()
		CXBytes Get_ResponseBody() {
			return WrapBytesPtrToCXBytes(Fiddler_Session_Get_ResponseBody(m_handle));
		}

		//@别名 置响应体(值)
		void Set_ResponseBody(CXBytes& value) {
			auto wb = CXBytesToWrapBytes(value);
			Fiddler_Session_Set_ResponseBody(m_handle, &wb);
		}

		//@别名 取响应代码()
		const int32_t Get_ResponseCode() {
			return Fiddler_Session_Get_ResponseCode(m_handle);
		}

		//@别名 置响应代码(响应代码)
		void Set_ResponseCode(const int32_t value) {
			Fiddler_Session_Set_ResponseCode(m_handle, value);
		}

		//@别名 到文本(只有HTTP头)
		const TCHAR* ToString(BOOL headersOnly) {
			return Fiddler_Session_ToString(m_handle, headersOnly);
		}

		//@别名 取请求体编码()
		const TCHAR* Get_RequestBodyEncoding() {
			return Fiddler_Session_Get_RequestBodyEncoding(m_handle);
		}

		//@别名 取响应体编码()
		const TCHAR* Get_ResponseBodyEncoding() {
			return Fiddler_Session_Get_ResponseBodyEncoding(m_handle);
		}

		//@别名 取本地进程()
		const TCHAR* Get_LocalProcess() {
			return Fiddler_Session_Get_LocalProcess(m_handle);
		}

		//@别名 取本地进程ID()
		const int32_t Get_LocalProcessID() {
			return Fiddler_Session_Get_LocalProcessID(m_handle);
		}

		//@别名 取标志(键)
		const TCHAR* Get_Flag(const TCHAR* name) {
			return Fiddler_Session_Get_Flag(m_handle,name);
		}

		//@别名 置标志(键,值)
		void Set_Flag(const TCHAR* name,const TCHAR* value) {
			Fiddler_Session_Set_Flag(m_handle, name, value);
		}

		//@别名 隧道为WebSocket()
		FD_WebSocket TunnelAsWebSocket() {
			return { Fiddler_Session_TunnelAsWebSocket(m_handle) };
		}

		//@别名 Uri包含(欲寻找文本)
		BOOL UriContains(const TCHAR* lookfor) {
			return Fiddler_Session_UriContains(m_handle, lookfor);
		}

		//@别名 中止()
		void Abort() {
			Fiddler_Session_Abort(m_handle);
		}

		//@备注 区分大小写，在请求正文（不是 URL！）上执行区分大小写的字符串替换。更新 Content-Length 标头。如果发生替换，则返回 TRUE。
		//@别名 替换请求(欲搜索文本，欲替换文本)
		BOOL ReplaceInRequest(const TCHAR* sSearchFor, const TCHAR* sReplaceWith) {
			return Fiddler_Session_ReplaceInRequest(m_handle, sSearchFor, sReplaceWith);
		}

		//@备注 区分大小写，对响应正文执行区分大小写的字符串替换。更新 Content-Length 标头。请注意，您应该先调用 utilDecodeResponse！如果发生替换，则返回 TRUE。
		//@别名 替换响应(欲搜索文本，欲替换文本)
		BOOL ReplaceInResponse(const TCHAR* sSearchFor, const TCHAR* sReplaceWith) {
			return Fiddler_Session_ReplaceInResponse(m_handle, sSearchFor, sReplaceWith);
		}

		//@备注 区分大小写，在响应正文上执行单个区分大小写的字符串替换。更新 Content-Length 标头。请注意，您应该先调用 utilDecodeResponse！如果发生替换，则返回 TRUE。
		//@别名 替换一次响应(欲搜索文本，欲替换文本,区分大小写)
		BOOL ReplaceOnceInResponse(const TCHAR* sSearchFor, const TCHAR* sReplaceWith, BOOL bCaseSensitive) {
			return Fiddler_Session_ReplaceOnceInResponse(m_handle, sSearchFor, sReplaceWith, bCaseSensitive);
		}
		
		//@备注 对响应正文执行基于正则表达式的替换。 通过领先的内联标志指定正则表达式选项，例如 (?im) 用于不区分大小写的多行。 更新 Content-Length 标头。 请注意，您应该先调用 utilDecodeResponse！ 如果发生替换，则返回 TRUE。
		//@别名 替换响应(用于搜索正文的正则表达式，用于替换的文本或表达式)
		BOOL ReplaceRegexInResponse(const TCHAR* sSearchForRegEx, const TCHAR* sReplaceWithExpression) {
			return Fiddler_Session_ReplaceRegexInResponse(m_handle, sSearchForRegEx, sReplaceWithExpression);
		}

	private:
		FD_SessionHandle m_handle;
	};

	//@别名 FD_WebSocket消息
	class FD_WebSocketMessage {
	public:
		//@隐藏{
		FD_WebSocketMessage(FD_WebSocketMessageHandle webSocketMessagHandlee)
			:m_handle(webSocketMessagHandlee)
		{}
		//@隐藏}


		int32_t ID() {
			return Fiddler_WebSocketMessage_ID(m_handle);
		}

		//@别名 中止()
		void Abort() {
			Fiddler_WebSocketMessage_Abort(m_handle);
		}

		//@备注 如果这是一个 Client->Server 消息，则返回 true，如果这是来自 Server->Client 的消息，则返回 false。
		//@别名 为出站()
		BOOL IsOutbound() {
			return Fiddler_WebSocketMessage_IsOutbound(m_handle);
		}

		//@别名 为最终帧()
		BOOL IsFinalFrame() {
			return Fiddler_WebSocketMessage_IsFinalFrame(m_handle);
		}

		//@别名 帧类型()
		FD_WebSocketFrameTypes FrameType() {
			return static_cast<FD_WebSocketFrameTypes>(Fiddler_WebSocketMessage_FrameType(m_handle));
		}

		//@别名 取有效载荷文本()
		const TCHAR* Get_PayloadString() {
			return Fiddler_WebSocketMessage_Get_PayloadString(m_handle);
		}

		//@别名 置有效载荷文本()
		void Set_PayloadString(const TCHAR* value) {
			Fiddler_WebSocketMessage_Set_PayloadString(m_handle, value);
		}

		//@别名 取有效载荷()
		CXBytes Get_Payload()
		{
			return WrapBytesPtrToCXBytes(Fiddler_WebSocketMessage_Get_Payload(m_handle));
		}

		//@别名 置有效载荷(值)
		void Set_Payload(CXBytes& value) {
			auto wb = CXBytesToWrapBytes(value);
			Fiddler_WebSocketMessage_Set_Payload(m_handle, &wb);
		}
	private:
		FD_WebSocketMessageHandle m_handle;
	};

	//@别名 FD_代理设置
	class FD_ProxySettings {
		friend class FD_StartupSettingsBuilder;
	public:
		//@隐藏{
		FD_ProxySettings() :m_handle(nullptr) {
			m_handle = Fiddler_ProxySettings_New();
		}
		~FD_ProxySettings() {
			if (m_handle) {

				Fiddler_ProxySettings_Del(m_handle);
				m_handle = nullptr;
			}
		}
		


		bool notNull() const noexcept {
			return m_handle;
		}
		//@隐藏}

		//@别名 置Web代理自动发现(值)
		auto& Set_UseWebProxyAutoDiscovery(BOOL v)
		{
			Fiddler_ProxySettings_Set_UseWebProxyAutoDiscovery(m_handle, static_cast<BOOL>(v));
			return *this;
		}

		//@别名 置代理自动配置启用(值)
		auto& Set_ProxyAutoConfigEnabled(BOOL v)
		{
			Fiddler_ProxySettings_Set_ProxyAutoConfigEnabled(m_handle, static_cast<BOOL>(v));
			return *this;
		}

		//@别名 置自动配置Url(值)
		auto& Set_ProxyAutoConfigUrl(TCHAR* v)
		{
			Fiddler_ProxySettings_Set_ProxyAutoConfigUrl(m_handle, v);
			return *this;
		}

		//@别名 置绕过主机(值)
		auto& Set_BypassHosts(const TCHAR* v)
		{
			Fiddler_ProxySettings_Set_BypassHosts(m_handle, v);
			return *this;
		}

		//@别名 置HTTP代理启用(值)
		auto& Set_HttpProxyEnabled(BOOL v)
		{
			Fiddler_ProxySettings_Set_HttpProxyEnabled(m_handle, static_cast<BOOL>(v));
			return *this;
		}

		//@别名 置HTTP代理主机(值)
		auto& Set_HttpProxyHost(const TCHAR* v)
		{
			Fiddler_ProxySettings_Set_HttpProxyHost(m_handle, v);
			return *this;
		}

		//@别名 置HTTP代理端口(值)
		auto& Set_HttpProxyPort(int v)
		{
			Fiddler_ProxySettings_Set_HttpProxyPort(m_handle, v);
			return *this;
		}

		//@别名 置HTTPS代理启用(值)
		auto& Set_HttpsProxyEnabled(BOOL v)
		{
			Fiddler_ProxySettings_Set_HttpsProxyEnabled(m_handle, v);
			return *this;
		}

		//@别名 置HTTPS代理主机(值)
		auto& Set_HttpsProxyHost(const TCHAR* v)
		{
			Fiddler_ProxySettings_Set_HttpsProxyHost(m_handle, v);
			return *this;
		}

		//@别名 置HTTPS代理端口(值)
		auto& Set_HttpsProxyPort(int v)
		{
			Fiddler_ProxySettings_Set_HttpsProxyPort(m_handle, v);
			return *this;
		}

		//@别名 置FTP代理启用(值)
		auto& Set_FtpProxyEnabled(BOOL v)
		{
			Fiddler_ProxySettings_Set_FtpProxyEnabled(m_handle, v);
			return *this;
		}

		//@别名 置FTP代理主机(值)
		auto& Set_FtpProxyHost(const TCHAR* v)
		{
			Fiddler_ProxySettings_Set_FtpProxyHost(m_handle, v);
			return *this;
		}

		//@别名 置FTP代理端口(值)
		auto& Set_FtpProxyPort(int v)
		{
			Fiddler_ProxySettings_Set_FtpProxyPort(m_handle, v);
			return *this;
		}

		//@别名 置Socks代理启用(值)
		auto& Set_SocksProxyEnabled(BOOL v)
		{
			Fiddler_ProxySettings_Set_SocksProxyEnabled(m_handle, static_cast<BOOL>(v));
			return *this;
		}

		//@别名 置Socks代理主机(值)
		auto& Set_SocksProxyHost(const TCHAR* v)
		{
			Fiddler_ProxySettings_Set_SocksProxyHost(m_handle, v);
			return *this;
		}

		//@别名 置Socks代理端口(值)
		auto& Set_SocksProxyPort(int v)
		{
			Fiddler_ProxySettings_Set_SocksProxyPort(m_handle, v);
			return *this;
		}
		//@别名 取Web代理自动发现()
		BOOL Get_UseWebProxyAutoDiscovery()
		{
			return Fiddler_ProxySettings_Get_UseWebProxyAutoDiscovery(m_handle);
		}

		//@别名 取代理自动配置启用()
		BOOL Get_ProxyAutoConfigEnabled()
		{
			return Fiddler_ProxySettings_Get_ProxyAutoConfigEnabled(m_handle);
		}

		//@别名 取自动配置Url()
		const TCHAR* Get_ProxyAutoConfigUrl()
		{
			return Fiddler_ProxySettings_Get_ProxyAutoConfigUrl(m_handle);
		}

		//@别名 取绕过主机()
		const TCHAR* Get_BypassHosts()
		{
			return Fiddler_ProxySettings_Get_BypassHosts(m_handle);
		}

		//@别名 取HTTP代理启用()
		BOOL Get_HttpProxyEnabled()
		{
			return Fiddler_ProxySettings_Get_HttpProxyEnabled(m_handle);
		}

		//@别名 取HTTP代理主机()
		const TCHAR* Get_HttpProxyHost()
		{
			return Fiddler_ProxySettings_Get_HttpProxyHost(m_handle);
		}

		//@别名 取HTTP代理端口()
		int Get_HttpProxyPort()
		{
			return Fiddler_ProxySettings_Get_HttpProxyPort(m_handle);
		}

		//@别名 取HTTPS代理启用()
		BOOL Get_HttpsProxyEnabled()
		{
			return Fiddler_ProxySettings_Get_HttpsProxyEnabled(m_handle);
		}

		//@别名 取HTTPS代理主机()
		const TCHAR* Get_HttpsProxyHost()
		{
			return Fiddler_ProxySettings_Get_HttpsProxyHost(m_handle);
		}

		//@别名 取HTTPS代理端口()
		int Get_HttpsProxyPort()
		{
			return Fiddler_ProxySettings_Get_HttpsProxyPort(m_handle);
		}

		//@别名 取FTP代理启用()
		BOOL Get_FtpProxyEnabled()
		{
			return Fiddler_ProxySettings_Get_FtpProxyEnabled(m_handle);
		}

		//@别名 取FTP代理主机()
		const TCHAR* Get_FtpProxyHost()
		{
			return Fiddler_ProxySettings_Get_FtpProxyHost(m_handle);
		}

		//@别名 取FTP代理端口()
		int Get_FtpProxyPort()
		{
			return Fiddler_ProxySettings_Get_FtpProxyPort(m_handle);
		}

		//@别名 取Socks代理启用()
		BOOL Get_SocksProxyEnabled()
		{
			return Fiddler_ProxySettings_Get_SocksProxyEnabled(m_handle);
		}

		//@别名 取Socks代理主机()
		const TCHAR* Get_SocksProxyHost()
		{
			return Fiddler_ProxySettings_Get_SocksProxyHost(m_handle);
		}

		//@别名 取Socks代理端口()
		int Get_SocksProxyPort()
		{
			return Fiddler_ProxySettings_Get_SocksProxyPort(m_handle);
		}

	protected:
		void* m_handle;
	};

	//@别名 FD_启动配置构建
	class FD_StartupSettingsBuilder {
	public:
		//@隐藏{
		FD_StartupSettingsBuilder():m_handle(nullptr) {
			m_handle = Fiddler_StartupSettingsBuilder_New();
		}
		~FD_StartupSettingsBuilder() {
			if (m_handle) {
				Fiddler_StartupSettingsBuilder_Del(m_handle);
				m_handle = nullptr;
			}
		}
		
		bool notNull() const noexcept {
			return m_handle;
		}
		//@隐藏}
		
		//@备注 当参数传入0时，将使用随机端口。
		//@别名 监听端口(值)
		FD_StartupSettingsBuilder& ListenOnPort(int port) {
			Fiddler_StartupSettingsBuilder_ListenOnPort(m_handle, port);
			return *this;
		}

		//@别名 注册为系统代理()
		FD_StartupSettingsBuilder& RegisterAsSystemProxy() {
			Fiddler_StartupSettingsBuilder_RegisterAsSystemProxy(m_handle);
			return *this;
		}

		//@别名 解密SSL()
		FD_StartupSettingsBuilder& DecryptSSL() {
			Fiddler_StartupSettingsBuilder_DecryptSSL(m_handle);
			return *this;
		}

		//@别名 允许远程客户端()
		FD_StartupSettingsBuilder& AllowRemoteClients() {
			Fiddler_StartupSettingsBuilder_AllowRemoteClients(m_handle);
			return *this;
		}

		//@别名 链上游网关()
		FD_StartupSettingsBuilder& ChainToUpstreamGateway() {
			Fiddler_StartupSettingsBuilder_ChainToUpstreamGateway(m_handle);
			return *this;
		}

		//@别名 监控所有连接()
		FD_StartupSettingsBuilder& MonitorAllConnections() {
			Fiddler_StartupSettingsBuilder_MonitorAllConnections(m_handle);
			return *this;
		}

		//@别名 使用PAC文件挂钩()
		FD_StartupSettingsBuilder& HookUsingPACFile() {
			Fiddler_StartupSettingsBuilder_HookUsingPACFile(m_handle);
			return *this;
		}

		//@别名 捕获本地主机流量()
		FD_StartupSettingsBuilder& CaptureLocalhostTraffic() {
			Fiddler_StartupSettingsBuilder_CaptureLocalhostTraffic(m_handle);
			return *this;
		}

		//@别名 捕获FTP()
		FD_StartupSettingsBuilder& CaptureFTP() {
			Fiddler_StartupSettingsBuilder_CaptureFTP(m_handle);
			return *this;
		}

		//@别名 优化线程池()
		FD_StartupSettingsBuilder& OptimizeThreadPool() {
			Fiddler_StartupSettingsBuilder_OptimizeThreadPool(m_handle);
			return *this;
		}

		//@别名 置上游网关(上游网关, 绕过主机列表)
		FD_StartupSettingsBuilder& SetUpstreamGatewayTo(const TCHAR* upstreamGateway, const TCHAR* bypassList) {
			Fiddler_StartupSettingsBuilder_SetUpstreamGatewayTo(m_handle, upstreamGateway, bypassList);
			return *this;
		}

		//@别名 置上游代理设置(代理设置)
		FD_StartupSettingsBuilder& SetUpstreamProxySettingsTo(FD_ProxySettings proxySettings) {
			Fiddler_StartupSettingsBuilder_SetUpstreamProxySettingsTo(m_handle, proxySettings.m_handle);
			return *this;
		}

		//@别名 构建()
		FD_StartupSettingsHandle Build() {
			return reinterpret_cast<FD_StartupSettingsHandle>(Fiddler_StartupSettingsBuilder_Build(m_handle));
		}


	private:
		void* m_handle;
	};
	
	//@别名 FD_实用程序
	class FD_Utilities {
	public:
		//@隐藏{
		static void WrapManage_Free() { Fiddler_Utilities_WrapManage_Free(); }
		//@隐藏}

		//@别名 删除_Sec_WebSocket_Extensions_扩展_Permessage_Deflate(HTTP头)
		static void Remove_Sec_WebSocket_Extensions_Permessage_Deflate(FD_HTTPHeaders headers) { Fiddler_Utilities_Remove_Sec_WebSocket_Extensions_Permessage_Deflate(headers.m_handle); }
		
		//@别名 此程序集版本()
		static const TCHAR* ThisAssemblyVersion() { return Fiddler_Utilities_ThisAssemblyVersion(); }
		
		//@别名 恢复内存()
		static void RecoverMemory() { Fiddler_Utilities_RecoverMemory(); }
	};

	//@别名 FD_会话列表
	class FD_SessionList {
	public:
		//@隐藏{
		FD_SessionList(FD_SessionListHandle handle) :m_handle(handle) {}
		FD_SessionList() :m_handle(Fiddler_SessionList_New()) {}
		~FD_SessionList() {
			if (m_handle) {
				Fiddler_SessionList_Del(m_handle);
				m_handle = nullptr;
			}
		 }
		

		bool notNull() const noexcept {
			return m_handle;
		}
		//@隐藏}

		//@别名 计数()
		int Count() {
			return Fiddler_SessionList_Count(m_handle);
		}

		//@别名 添加(会话)
		BOOL Add(FD_Session s) {
			return Fiddler_SessionList_Add(m_handle, s.m_handle);
		}

		//@别名 添加_从句柄(会话句柄)
		BOOL Add_From_Handle(FD_SessionHandle handle) {
			return Fiddler_SessionList_Add(m_handle, handle);
		}

		//@别名 清空()
		BOOL Clear() {
			return Fiddler_SessionList_Clear(m_handle);
		}

		//@别名 移除(会话)
		BOOL Remove(FD_Session s) {
			return Fiddler_SessionList_Remove(m_handle, s.m_handle);
		}

		//@别名 移除_从索引(索引)
		BOOL RemoveAt(int32_t index) {
			return Fiddler_SessionList_RemoveAt(m_handle, index);
		}
	protected:
		FD_SessionListHandle m_handle;
	};
//@隐藏{
#ifdef ENABLE_FIDDLERCWRAP_EXTEND
//@隐藏}
	//@别名 FD_WebSocket管理
	class FD_WebSocketManage : public FD_SessionList {
	public:
	//@隐藏{
		FD_WebSocketManage() : FD_SessionList (Fiddler_WebSocketManage_New()) {

		}
		~FD_WebSocketManage() {
			if (m_handle) {

				Fiddler_WebSocketManage_Del(m_handle);
				m_handle = nullptr;
			}
		}
	//@隐藏}

		//@别名 移除所有已关闭()
		int32_t RemoveAllClosed() {
			return Fiddler_WebSocketManage_RemoveAllClosed(m_handle);
		}

		//@别名 发送客户端文本消息(文本)
		BOOL SendClientTextMessage(const TCHAR* strPayload) {
			return Fiddler_WebSocketManage_SendClientTextMessage(m_handle, strPayload);
		}

		//@别名 发送客户端二进制消息(数据)
		BOOL SendClientBinaryMessage(CXBytes& wrapBytesPayload) {
			auto wb = CXBytesToWrapBytes(wrapBytesPayload);
			return Fiddler_WebSocketManage_SendClientBinaryMessage(m_handle, &wb);
		}

		//@别名 发送服务器文本消息(文本)
		BOOL SendServerTextMessage(const TCHAR* strPayload) {
			return Fiddler_WebSocketManage_SendServerTextMessage(m_handle, strPayload);
		}
		
		//@别名 发送服务器二进制消息(数据)
		BOOL SendServerBinaryMessage(CXBytes& wrapBytesPayload)	{
			auto wb = CXBytesToWrapBytes(wrapBytesPayload);
			return Fiddler_WebSocketManage_SendServerBinaryMessage(m_handle, &wb);
		}
	};
//@隐藏{
#endif //ENABLE_FIDDLERCWRAP_EXTEND
//@隐藏}

	//@隐藏{
	using SessionStateHandler = void(*)(FD_Session&, void*, void*);
	using WebSocketMessageEvent = void(*)(FD_Session&, FD_WebSocketMessage&, void*, void*);
	using WebSocketConnectionEvent = void(*)(FD_Session&, FD_WebSocket&, void*, void*);
	//@隐藏}

	//@别名 FD_应用
	class FD_Application {
	public:
		//@别名 事件_请求头可用(回调, 上下文1, 上下文2)
		static void Attach_OnRequestHeadersAvailable(SessionStateHandler callback, void* arg1, void* arg2) {
			static decltype(callback) func = callback;
			struct Internal {
				static void WINAPI Proc(FD_SessionHandle hS, void* a1, void* a2) {
					FD_Session oS(hS);
					func(oS, a1, a2);
				}
			} ;
			Fiddler_Application_Attach_OnRequestHeadersAvailable(Internal::Proc, arg1, arg2);
		}

		//@别名 事件_响应头可用(回调, 上下文1, 上下文2)
		static void WINAPI Attach_OnResponseHeadersAvailable(SessionStateHandler callback, void* arg1, void* arg2) {
			static decltype(callback) func = callback;
			struct Internal {
				static void WINAPI Proc(FD_SessionHandle hS, void* a1, void* a2) {
					FD_Session oS(hS);
					func(oS, a1, a2);
				}
			};
			Fiddler_Application_Attach_OnResponseHeadersAvailable(Internal::Proc, arg1, arg2);
		}

		//@别名 事件_请求前(回调, 上下文1, 上下文2)
		static void Attach_OnBeforeRequest(SessionStateHandler callback, void* arg1, void* arg2) {
			static decltype(callback) func = callback;
			struct Internal {
				static void WINAPI Proc(FD_SessionHandle hS, void* a1, void* a2) {
					FD_Session oS(hS);
					func(oS, a1, a2);
				}
			};
			Fiddler_Application_Attach_OnBeforeRequest(Internal::Proc, arg1, arg2);
		}

		//@别名 事件_响应前(回调, 上下文1, 上下文2)
		static void Attach_OnBeforeResponse(SessionStateHandler callback, void* arg1, void* arg2) {
			static decltype(callback) func = callback;
			struct Internal {
				static void WINAPI Proc(FD_SessionHandle hS, void* a1, void* a2) {
					FD_Session oS(hS);
					func(oS, a1, a2);
				}
			}; 
			Fiddler_Application_Attach_OnBeforeResponse(Internal::Proc, arg1, arg2);
		}

		//@别名 事件_WebSocket消息(回调, 上下文1, 上下文2)
		static void Attach_OnWebSocketMessage(WebSocketMessageEvent callback, void* arg1, void* arg2) {
			static decltype(callback) func = callback;
			struct Internal {
				static void WINAPI Proc(FD_SessionHandle hS, FD_WebSocketMessageHandle hWSM, void* a1, void* a2) {
					FD_Session oS(hS);
					FD_WebSocketMessage oWSM(hWSM);
					func(oS, oWSM, a1, a2);
				}
			};
			Fiddler_Application_Attach_OnWebSocketMessage(Internal::Proc, arg1, arg2);
		}
//@隐藏{
#ifdef ENABLE_FIDDLERCWRAP_EXTEND
//@隐藏}
		//@别名 事件_WebSocket创建后(回调, 上下文1, 上下文2)
		static void Attach_AfterWebSocketCreateComplete(WebSocketConnectionEvent callback, void* arg1, void* arg2) {
			static decltype(callback) func = callback;
			struct Internal {
				static void WINAPI Proc(FD_SessionHandle hS, FD_WebSocketHandle hWS, void* a1, void* a2) {
					FD_Session oS(hS);
					FD_WebSocket oWS(hWS);
					func(oS, oWS, a1, a2);
				}
			};
			Fiddler_Application_Attach_AfterWebSocketCreateComplete(Internal::Proc, arg1, arg2);
		}

		//@别名 事件_WebSocket关闭后(回调, 上下文1, 上下文2)
		static void Attach_AfterWebSocketCloseComplete(WebSocketConnectionEvent callback, void* arg1, void* arg2) {
			static decltype(callback) func = callback;
			struct Internal {
				static void WINAPI Proc(FD_SessionHandle hS, FD_WebSocketHandle hWS, void* a1, void* a2) {
					FD_Session oS(hS);
					FD_WebSocket oWS(hWS);
					func(oS, oWS, a1, a2);
				}
			};
			Fiddler_Application_Attach_AfterWebSocketCloseComplete(Internal::Proc, arg1, arg2);
		}
//@隐藏{
#endif //ENABLE_FIDDLERCWRAP_EXTEND
//@隐藏}
 
		//@别名 启用会话互斥体(值)
		static void EnableSessionsMutex(BOOL value) {
			Fiddler_Application_EnableSessionsMutex(static_cast<BOOL>(value));
		}

		//@别名 初始化()
		static BOOL Init() {
			BOOL result = Fiddler_Application_Init();
			if (result) {
				WrapManage_Set_CurrentWrapStrEncoding(currentWrapStrEncoding);
			}
			return result;
		}

		//@别名 启动()
		static BOOL Startup(FD_StartupSettingsHandle hStartupSetting) {
			return Fiddler_Application_Startup(hStartupSetting);
		}

		//@别名 关闭()
		static void Shutdown() {
			Fiddler_Application_Shutdown();
		}

		//@别名 根证书_安装默认证书()
		static BOOL RootCertificate_InstallDefault() {
			return Fiddler_Application_RootCertificate_InstallDefault();
		}

		//@别名 根证书_安装(证书, 密码)
		static BOOL RootCertificate_Install(CXBytes& data, const TCHAR* pPassword) {
			auto wb = CXBytesToWrapBytes(data);
			return Fiddler_Application_RootCertificate_Install(&wb, pPassword);
		}

		//@别名 WrapManage_释放()
		static void WrapManage_Free() {
			return Fiddler_Application_WrapManage_Free();
		}

		//@别名 版本文本()
		static const TCHAR* Get_VersionString() {
			return Fiddler_Application_Get_VersionString();
		}

		//@别名 已启动()
		static BOOL IsStarted() {
			return Fiddler_Application_IsStarted();
		}

		//@别名 为系统代理()
		static BOOL IsSystemProxy() {
			return Fiddler_Application_IsSystemProxy();
		}

		//@别名 代理_取监听端口()
		static int Proxy_Get_ListenPort() {
			return Fiddler_Application_Proxy_Get_ListenPort();
		}

		//@别名 代理_分离()
		static BOOL Proxy_Detach() {
			return Fiddler_Application_Proxy_Detach();
		}
	};

	//@隐藏{
}
using namespace FiddlerXPL;
//@隐藏}
//@隐藏{
#endif //FiddlerXPL_H
//@隐藏}