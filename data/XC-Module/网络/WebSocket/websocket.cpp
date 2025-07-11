//#include "common__.h"
//#include "WebSocket__.h"
#include "module_websocket.h"


#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<Windows.h>
#include<winsock2.h>
#include<WS2tcpip.h>
#include<cstdint>
#include<thread>

#pragma comment(lib, "ws2_32.lib")
#include<windows.h>
#include<vector>
#include<string>
#include<iostream>
#include<sstream>
#include<regex>


using namespace std;


namespace XCWebSocket {


vector<int> X; //8*64=512，每个下标存放8位
int W[80]; //32位为一组
int A, B, C, D, E;
int A1, B1, C1, D1, E1; //缓冲区寄存器,产生最后结果
int Turn; //加密分组数量
void printX() {//输出填充后的文本
	for (int i = 0; i < X.size(); i++) {
		printf("%02x", X[i]);
		if ((i + 1) % 4 == 0)
			printf(" ");
		if ((i + 1) % 16 == 0)
			printf("\n");
	}
}
int S(unsigned int x, int n) {//循环左移
	return x >> (32 - n) | (x << n);
}
void append(string m) {//文本的填充处理
	Turn = (m.size() + 8) / 64 + 1;
	X.resize(Turn * 64);
	int i = 0;
	for (; i < m.size(); i++) {
		X[i] = m[i];
	}
	X[i++] = 0x80;
	while (i < X.size() - 8) {
		X[i] = 0;
		i++;
	}
	long long int a = m.size() * 8;
	for (i = X.size() - 1; i >= X.size() - 8; i--) {
		X[i] = a % 256;
		a /= 256;
	}
}
void setW(vector<int> m, int n) {//W数组的生成
	n *= 64;
	for (int i = 0; i < 16; i++) {
		W[i] = (m[n + 4 * i] << 24) + (m[n + 4 * i + 1] << 16)
			+ (m[n + 4 * i + 2] << 8) + m[n + 4 * i + 3];
	}
	for (int i = 16; i < 80; i++) {
		W[i] = S(W[i - 16] ^ W[i - 14] ^ W[i - 8] ^ W[i - 3], 1);
	}
}
int ft(int t) {//ft(B,C,D)函数
	if (t < 20)
		return (B & C) | ((~B) & D);
	else if (t < 40)
		return B ^ C ^ D;
	else if (t < 60)
		return (B & C) | (B & D) | (C & D);
	else
		return B ^ C ^ D;
}
int Kt(int t) {//常量K
	if (t < 20)
		return 0x5a827999;
	else if (t < 40)
		return 0x6ed9eba1;
	else if (t < 60)
		return 0x8f1bbcdc;
	else
		return 0xca62c1d6;
}
std::string sha1(string text) {
	A1 = A = 0x67452301;
	B1 = B = 0xefcdab89;
	C1 = C = 0x98badcfe;
	D1 = D = 0x10325476;
	E1 = E = 0xc3d2e1f0;
	append(text);
	//printX();
	for (int i = 0; i < Turn; i++) {
		setW(X, i);
		for (int t = 0; t < 80; t++) {
			int temp = E + ft(t) + S(A, 5) + W[t] + Kt(t);
			E = D;
			D = C;
			C = S(B, 30);
			B = A;
			A = temp;
		}
		A1 = A = A + A1;
		B1 = B = B + B1;
		C1 = C = C + C1;
		D1 = D = D + D1;
		E1 = E = E + E1;
	}



	printf("%08x%08x%08x%08x%08x\n\n", A1, B1, C1, D1, E1);

	std::stringstream ss;
	ss << std::hex << A1 << std::hex << B1 << std::hex << C1 << std::hex << D1 << std::hex << E1;

	std::string hexText = ss.str();

	return hexText;


}




const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
std::string base64_encode(string str) { // const std::vector<uint8_t>& data) {

	std::vector<uint8_t> data;

	for (char c : str) {
		data.push_back(static_cast<uint8_t>(c));
	}

	std::string encoded;
	int i = 0, j = 0;
	uint8_t byte3[3] = { 0 };
	uint8_t byte4[4] = { 0 };
	for (uint8_t byte : data) {
		byte3[i++] = byte;
		if (i == 3) {
			byte4[0] = (byte3[0] & 0xfc) >> 2;
			byte4[1] = ((byte3[0] & 0x03) << 4) | ((byte3[1] & 0xf0) >> 4);
			byte4[2] = ((byte3[1] & 0x0f) << 2) | ((byte3[2] & 0xc0) >> 6);
			byte4[3] = byte3[2] & 0x3f;
			for (i = 0; i < 4; i++) {
				encoded += base64_chars[byte4[i]];
			}
			i = 0;
		}
	}
	if (i != 0) {
		for (int k = i; k < 3; k++) {
			byte3[k] = 0;
		}
		byte4[0] = (byte3[0] & 0xfc) >> 2;
		byte4[1] = ((byte3[0] & 0x03) << 4) | ((byte3[1] & 0xf0) >> 4);
		byte4[2] = ((byte3[1] & 0x0f) << 2) | ((byte3[2] & 0xc0) >> 6);
		for (int k = 0; k < i + 1; k++) {
			encoded += base64_chars[byte4[k]];
		}
		while (i++ < 3) {
			encoded += '=';
		}
	}
	return encoded;
}



std::string base64_sha1(string text) {
	A1 = A = 0x67452301;
	B1 = B = 0xefcdab89;
	C1 = C = 0x98badcfe;
	D1 = D = 0x10325476;
	E1 = E = 0xc3d2e1f0;
	append(text);
	//printX();
	for (int i = 0; i < Turn; i++) {
		setW(X, i);
		for (int t = 0; t < 80; t++) {
			int temp = E + ft(t) + S(A, 5) + W[t] + Kt(t);
			E = D;
			D = C;
			C = S(B, 30);
			B = A;
			A = temp;
		}
		A1 = A = A + A1;
		B1 = B = B + B1;
		C1 = C = C + C1;
		D1 = D = D + D1;
		E1 = E = E + E1;
	}


	std::stringstream ss;
	ss << std::hex << A1 << std::hex << B1 << std::hex << C1 << std::hex << D1 << std::hex << E1;
	std::string hexText = ss.str();
	//std::cout << "=="<<hexText<<"\n";
	   // std::cout <<"==" << to_string(A1) + to_string(B1) + to_string(C1) + to_string(D1) + to_string(E1) << "\n";

	   // return base64_encode(to_string(A1)+ to_string(B1)+ to_string(C1)+ to_string(D1)+ to_string(E1));

	std::uint8_t byteArray[sizeof(int) * 5]{}; // 创建一个大小为int类型的字节数组
	std::vector<int> array;
	array.push_back(A1);
	array.push_back(B1);
	array.push_back(C1);
	array.push_back(D1);
	array.push_back(E1);
	int n = 0;
	for (int i : array) {
		byteArray[n] = static_cast<std::uint8_t>(i >> 24);
		byteArray[n + 1] = static_cast<std::uint8_t>(i >> 16);
		byteArray[n + 2] = static_cast<std::uint8_t>(i >> 8);
		byteArray[n + 3] = static_cast<std::uint8_t>(i);
		n = n + 4;
	}


	std::string encoded;
	int i = 0, j = 0;
	uint8_t byte3[3] = { 0 };
	uint8_t byte4[4] = { 0 };
	for (uint8_t byte : byteArray) {
		byte3[i++] = byte;
		if (i == 3) {
			byte4[0] = (byte3[0] & 0xfc) >> 2;
			byte4[1] = ((byte3[0] & 0x03) << 4) | ((byte3[1] & 0xf0) >> 4);
			byte4[2] = ((byte3[1] & 0x0f) << 2) | ((byte3[2] & 0xc0) >> 6);
			byte4[3] = byte3[2] & 0x3f;
			for (i = 0; i < 4; i++) {
				encoded += base64_chars[byte4[i]];
			}
			i = 0;
		}
	}
	if (i != 0) {
		for (int k = i; k < 3; k++) {
			byte3[k] = 0;
		}
		byte4[0] = (byte3[0] & 0xfc) >> 2;
		byte4[1] = ((byte3[0] & 0x03) << 4) | ((byte3[1] & 0xf0) >> 4);
		byte4[2] = ((byte3[1] & 0x0f) << 2) | ((byte3[2] & 0xc0) >> 6);
		for (int k = 0; k < i + 1; k++) {
			encoded += base64_chars[byte4[k]];
		}
		while (i++ < 3) {
			encoded += '=';
		}
	}
	return encoded;

}
CXTextA BASE64_SHA1(CXTextA& data)
{
	CXTextA ret;
	std::string _data(data.getPtr());
	ret.append(base64_sha1(_data).c_str());
	return ret;
}
std::vector<std::wstring> 分割文本W(const wchar_t* in, const wchar_t* delim) {
	std::wregex re{ delim };
	return std::vector<std::wstring>{
		std::wcregex_token_iterator(in, in + wcslen(in), re, -1),
			std::wcregex_token_iterator()
	};
}

std::vector<std::string> 分割文本A(const char* in, const char* delim) {
	std::regex re{ delim };
	return std::vector<std::string>{
		std::cregex_token_iterator(in, in + strlen(in), re, -1),
			std::cregex_token_iterator()
	};
}

std::string 文本删首位空A(std::string wstr) {
	wstr.erase(0, wstr.find_first_not_of(" "));
	wstr.erase(wstr.find_last_not_of(" ") + 1);
	return wstr;
}

BOOL WS服务端::启动(int 端口)
{
	SOCKET s = 0;


	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		return false;
	}

	sockaddr_in6 address{};
	address.sin6_family = AF_INET;
	address.sin6_port = htons(端口);
	/*address.sin_family = PF_INET;
	address.sin_port = htons(端口);*/

	//如果需要IPV6则使用inet_pton   inet_addr只支持IPV4


	inet_pton(AF_INET, "0.0.0.0", &address.sin6_addr);


	if (::bind(s, (SOCKADDR*)&address, sizeof(sockaddr_in6)) == SOCKET_ERROR)
	{

		closesocket(s);
		return false;
	}

	if (listen(s, 0) == SOCKET_ERROR) {

		closesocket(s);
		return false;
	}

	u_long iMode = 1;

	ioctlsocket(s, FIONBIO, &iMode);

	s_server = s;

	线程参数 cs;
	cs.server = this;
	cs.s = s;

	std::thread t(接收连接, &cs);
	std::thread t1(接收数据, &cs);
	t.detach();
	t1.detach();
	t = std::thread();
	t1 = std::thread();



	return true;
}
void WS服务端::停止()
{
	closesocket(s_server);
	s_server = 0;

	while (true) {
		if (接收连接线程停止 && 接收数据线程停止) {
			break;
		}
		Sleep(2);
	}
}
BOOL WS服务端::发送文本(客户& 客户, const CXTextA& 文本)
{
	CXBytes bin;
	数据帧编码(文本.getPtr(), 文本.getSize(), bin, 1);
	//WS客户端::数据帧编码(文本.getPtr(), 文本.getSize(), bin, 1, true, false);

	send(客户.s, bin.getTextPtrA(), bin.getSize(), 0);
	return true;
}
BOOL WS服务端::发送字节集(客户& 客户, const CXBytes& 数据)
{
	CXBytes bin;
	数据帧编码(数据.getTextPtrA(), 数据.getSize(), bin, 2);
	WS客户端::数据帧编码(数据.getTextPtrA(), 数据.getSize(), bin, 2, true, false);


	send(客户.s, bin.getTextPtrA(), bin.getSize(), 0);
	return true;
}
int WS服务端::取客户数()
{
	int 客户数;
	EnterCriticalSection(&许可证_客户列表);
	客户数 = Clients.getSize();
	LeaveCriticalSection((&许可证_客户列表));
	return 客户数;
}
int WS服务端::取客户列表(CXVector<客户*>& 客户列表)
{
	客户列表.clear();
	for (int i = 0; i < Clients.getSize(); i++)
	{
		客户列表.add(Clients[i]);
	}
	return 客户列表.getSize();
}
CXTextA WS服务端::取客户IP(客户* _客户)
{
	return _客户->IP地址;
}
BOOL WS服务端::PING(客户* 客户)
{
	char buffer[]="\0";
	CXBytes bin;
	数据帧编码(buffer, 0, bin, 9);
	return send(客户->s, bin.getTextPtrA(), bin.getSize(), 0)!=SOCKET_ERROR;

}
BOOL WS服务端::PONG(客户* 客户)
{
	char buffer[] = "\0";
	CXBytes bin;
	数据帧编码(buffer, 0, bin, 10);
	return send(客户->s, bin.getTextPtrA(), bin.getSize(), 0) != SOCKET_ERROR;
	
}
WS服务端::WS服务端()
{
	InitializeCriticalSection(&许可证_客户列表);
	
	if(WSA初始化计数器==0)
	{
		WSA初始化计数器++;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsadata);// != NO_ERROR
	}
	else {
		WSA初始化计数器++;
	}
	


	/*客户* client = new 客户{};
	Clients.add(client);*/
}
WS服务端::~WS服务端()
{
	DeleteCriticalSection(&许可证_客户列表);

	if (WSA初始化计数器 == 1) {
		WSACleanup();
		WSA初始化计数器 = 0;
	}else {
		WSA初始化计数器--;
	}

	
}
void WS服务端::接收连接(线程参数* cs)
{
	WS服务端* server = cs->server;
	SOCKET s = cs->s;
	SOCKET s_client;

	int len = sizeof(sockaddr_in6);
	while (true)
	{
		sockaddr_in6 addr{};
		s_client = accept(s, (SOCKADDR*)&addr, &len);
		if (s_client != INVALID_SOCKET)
		{

			客户* client = new 客户{};
			client->buffer.resize(0);
			client->bin_buffer.resize(0);
			client->s = s_client;
			char Address_buffer[100];
			memset(Address_buffer, 0, 100);
			inet_ntop(addr.sin6_family, &addr.sin6_flowinfo, Address_buffer, 100);


			client->IP地址.append2(Address_buffer, strlen(Address_buffer));

			EnterCriticalSection(&(server->许可证_客户列表));

			server->Clients.add(client);

			for (int i = server->Clients.size() - 1; i >= 0; i--)
			{
				if (server->Clients[i]->s == 0) {
					server->Clients.erase(i);
				}
			}

			LeaveCriticalSection(&(server->许可证_客户列表));

		}
		if (server->s_server == 0)
		{
			break;
		}
		Sleep(2);
	}
	server->接收连接线程停止 = true;
}
void WS服务端::接收数据(线程参数* cs)
{
	WS服务端* server = cs->server;
	SOCKET s = cs->s;
	客户* client = new 客户();
	int len = 0;
	char buffer[4096];
	包信息 data;
	memset(buffer, 0, 4096);
	char* content = 0;
	int packetLen = 0;
	int contentLen = 0;
	//WS帧类型
	int opcode = 0;
	bool endFrame = false;

	while (true)
	{
		LeaveCriticalSection(&(server->许可证_客户列表));
		Sleep(2);
		EnterCriticalSection(&(server->许可证_客户列表));
		for (int i = 0; i < server->Clients.getSize(); i++)
		{
			if (server->Clients[i]->s == 0) { continue; }
			client = server->Clients[i];
			len = recv(server->Clients[i]->s, buffer, 4096, 0);

			if (len == SOCKET_ERROR) {
				int error = WSAGetLastError();
				if (error == WSAENETRESET || error == WSAESHUTDOWN || error == WSAETIMEDOUT || error == WSAECONNRESET) {
					//连接已中断/套接字已关闭/因为网络故障或对等系统无法响应，已经丢弃了连接。
					closesocket(client->s);
					client->s = 0;
					if (server->事件_客户退出 != 0) {
						((WS服务端事件_客户退出) server->事件_客户退出)(*client);
					}
					continue;
				}

			}
			if (len <= 0) { continue; }

			if (client->握手 == false)
			{
				client->握手 = server->确认握手请求(client->s, buffer, len);

				if (client->握手) {
					if (server->事件_客户进入 != 0) { ((WS服务端事件_客户进入)server->事件_客户进入)(*client); }

				}
				else {
					//握手失败直接断开连接
					client->bin_buffer.resize(0);
					closesocket(client->s);
					client->s = 0;
				}
			}
			else
			{
				client->bin_buffer.append2(buffer, len);

				while (true)
				{
					opcode = server->数据帧解码(&data, client->bin_buffer, &content, &contentLen, &endFrame, &packetLen);
					if (data.opcode == WS_CLOSING_FRAME)
					{
						client->bin_buffer.erase(0, client->bin_buffer.getSize());
						client->buffer.erase(0, client->buffer.getSize());
						closesocket(client->s);
						client->s = 0;
						break;
					}
					else if ((opcode == -1))
					{
						client->bin_buffer.erase(0, client->bin_buffer.getSize());
						client->buffer.erase(0, client->buffer.getSize());
						break;
					}
					else if ((opcode == 0))
					{
						break;
					}

					else
					{
						client->buffer.erase(0, client->buffer.getSize());
						client->buffer.append2(content, contentLen);
						delete[]content;
						if (endFrame)
						{
							CXBytes bin;
							bin.add((void*)client->buffer.getPtr(), client->buffer.size());
							if (server->事件_数据到达 != 0) {
								((WS服务端事件_收到数据) server->事件_数据到达)(*client, bin);
							}
							client->buffer.erase(0, client->buffer.getSize());
						}

						client->bin_buffer.erase(0, packetLen);
						if (client->bin_buffer.getSize() > packetLen) {
							//存在粘包情况
							continue;
						}
						//否则退出解析包循环
						break;

					}
				}
			}
		}
		if (server->s_server == 0)
		{
			break;
		}
	}
	server->接收数据线程停止 = true;
}

static CXVector<CXTextA> ws_String_SplitWithStlA(CXTextA str, CXTextA pattern)
{
	CXVector<CXTextA> rets;
	if ("" == str.get())
	{
		return rets;
	}
	std::string strs;
	strs.append(str.get()).append(pattern.get());
	size_t pos = strs.find(pattern);
	size_t size = strs.size();
	while (pos != std::string::npos)
	{
		CXTextA x = strs.substr(0, pos);
		rets.add(x);
		strs = strs.substr(pos + pattern.size(), size);
		pos = strs.find(pattern);
	}
	return rets;
}


bool WS服务端::确认握手请求(SOCKET s, const char* buffer, int len)
{
	CXTextA 数据;
	数据.append2(buffer, len);

	CXVector<CXTextA>  请求 = ws_String_SplitWithStlA(数据, "\r\n");
	for (int i = 0; i < 请求.getSize(); i++)
	{
		if (请求[i].substr(0, 18) == CXTextA("Sec-WebSocket-Key:"))
		{
			CXTextA key = 请求[i].substr(18, 请求[i].getSize() - 18);
			key.replaceSub(" ", "");
			key = key + CXTextA("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
			key = BASE64_SHA1(key);
			CXTextA 回复("HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: ");
			回复 = 回复 + CXTextA(key) + CXTextA("\r\n\r\n");
			SendText(s, 回复);
			return true;
		}
	}
	return false;
}
int WS服务端::数据帧解码(包信息* outdata, CXTextA buffer, char** lp_outMessage, int* packet_len, bool* end, int* endlen)
{
	const char* frameData = buffer.getPtr();
	int len = buffer.size();
	int ret = -1; //WS_ERROR_FRAME
	*endlen = 0;
	*end = false;
	const int frameLength = len;
	if (frameLength < 2) {
		return ret;
	}
	// 检查扩展位并忽略
	if ((frameData[0] & 0x70) != 0x0) {
		return ret;
	}
	// fin位: 为1表示已接收完整报文, 为0表示继续监听后续报文
	*end = (frameData[0] & 0x80);

	if ((frameData[0] & 0x80) != 0x80) {
		return ret;
	}
	// mask位, 为1表示数据被加密
	if ((frameData[1] & 0x80) != 0x80) {
		return ret;
	}
	// 操作码
	uint16_t payloadLength = 0;
	uint8_t payloadFieldExtraBytes = 0;
	uint8_t opcode = static_cast<uint8_t>(frameData[0] & 0x0f);

	/*	std::cout << std::endl;
		std::cout << "mask:" << ((frameData[1] &0x80) != 0x80) << std::endl;
		std::cout << "frameLength: " << frameLength << std::endl;
		std::cout << "payloadLength: " << payloadLength << std::endl;
		std::cout << "payloadFieldExtraBytes: " << payloadFieldExtraBytes << std::endl;
		std::cout << "opcode: " << (int)opcode << std::endl;*/


	outdata->opcode = opcode;

	if (opcode == WS_TEXT_FRAME)
	{
		// 处理utf-8编码的文本帧
		ret = WS_TEXT_FRAME;
		payloadLength = static_cast<uint16_t>(frameData[1] & 0x7f);
		if (payloadLength == 0x7e)
		{
			uint16_t payloadLength16b = 0;
			payloadFieldExtraBytes = 2;
			memcpy(&payloadLength16b, &frameData[2], payloadFieldExtraBytes);
			payloadLength = ntohs(payloadLength16b);
		}
		else if (payloadLength == 0x7f)
		{
			// 数据过长,暂不支持
			ret = -1; //WS_ERROR_FRAME
		}
	}
	else if (opcode == WS_BINARY_FRAME || opcode == WS_PING_FRAME || opcode == WS_PONG_FRAME)
	{
		// 二进制/ping/pong帧暂不处理
	}
	else //其他类型如 WS_CLOSING_FRAME等全部识别为断开连接
	{
		ret = -1;
		return ret;
	}


	// 数据解码
	if ((ret != -1) && (payloadLength > 0)) //WS_ERROR_FRAME
	{

		if (2 + payloadFieldExtraBytes + 4 + payloadLength > len) {
			ret = 0;
			return ret;
		}

		// header: 2字节, masking key: 4字节
		const char* maskingKey = &frameData[2 + payloadFieldExtraBytes];
		char* payloadData = new char[payloadLength + 1];
		memset(payloadData, 0, payloadLength + 1);
		memcpy(payloadData, &frameData[2 + payloadFieldExtraBytes + 4], payloadLength);
		for (int i = 0; i < payloadLength; i++)
		{
			payloadData[i] = payloadData[i] ^ maskingKey[i % 4];
		}

		*lp_outMessage = payloadData;
		int totLen = payloadLength;
		*packet_len = totLen;
		*endlen = 2 + payloadFieldExtraBytes + 4 + totLen;
		payloadData[totLen] = 0x00;
		//memcpy(outMessage, payloadData, totLen);
		//**lp_outMessage[totLen] = 0x00;
		//delete[] payloadData;
		ret = 1;
	}
	return ret;
}


int WS服务端::数据帧编码(const char* 数据, int 长度, CXBytes& bin, int frameType)
{
	int ret = 0x0F;

	const uint32_t messageLength = 长度;

	if (messageLength > 32767)
	{
		// 暂不支持这么长的数据
		return -1; //WS_ERROR_FRAME
	}

	uint8_t payloadFieldExtraBytes = (messageLength <= 0x7d) ? 0 : 2;
	// header: 2字节, mask位设置为0(不加密), 则后面的masking key无须填写, 省略4字节
	uint8_t frameHeaderSize = 2 + payloadFieldExtraBytes;
	uint8_t* frameHeader = new uint8_t[frameHeaderSize];
	memset(frameHeader, 0, frameHeaderSize);
	// fin位为1, 扩展位为0, 操作位为frameType
	frameHeader[0] = static_cast<uint8_t>(0x80 | frameType);

	// 填充数据长度
	if (messageLength <= 0x7d)
	{
		//头1个字节+ 1个字节长度 + 0x0000
		frameHeader[1] = static_cast<uint8_t>(messageLength);
	}
	else
	{
		//头1个字节+ 0x7e +2个字节长度
		frameHeader[1] = 0x7e;
		uint16_t len = htons(messageLength);
		memcpy(&frameHeader[2], &len, payloadFieldExtraBytes);
	}

	// 填充数据
	uint32_t frameSize = frameHeaderSize + messageLength;
	char* frame = new char[frameSize + 1];
	memcpy(frame, frameHeader, frameHeaderSize);
	memcpy(frame + frameHeaderSize, 数据, messageLength);
	frame[frameSize] = '\0';


	//outFrame = frame;
	//memcpy(outFrame, frame, frameSize);
	//outFrame[frameSize] = 0x00;
	bin.add(frame, frameSize);

	delete[]frame;
	delete[]frameHeader;

	return ret;
}
bool WS服务端::SendText(SOCKET s, CXTextA& 文本)
{
	send(s, 文本.getPtr(), 文本.getSize(), 0);
	return true;
}





//============ WS客户端::==========================


// 函数用于拆分WS连接地址  
bool splitWSAddress(CXTextA& wsAddress, CXTextA& host, int& port) {
	std::size_t pos = wsAddress.find("://");
	if (pos == std::string::npos) {
		// 找不到协议部分  
		return false;
	}




	// 跳过协议部分  
	CXTextA remaining = wsAddress.substr(pos + 3, wsAddress.size() - pos - 3);
	pos = remaining.find("/");
	if (pos != std::string::npos) {
		remaining = remaining.substr(0, pos);
	}


	// 查找端口号前的冒号  
	pos = remaining.find(":");
	if (pos == std::string::npos) {
		// 没有找到端口号  
		port = 80;
		// 提取主机名和端口号  
		host = remaining;

	}
	else {

		// 提取主机名和端口号  
		host = remaining.substr(0, pos);

		// 提取端口号并转换为整数  
		CXTextA portStr = remaining.substr(pos + 1, wsAddress.size() - pos - 1);
		std::istringstream iss(portStr.getPtr());
		if (!(iss >> port) || !(iss >> std::ws).eof()) {
			// 转换失败或端口号后还有字符  
			return false;
		}


	}



	return true;
}

//int main() {
//	std::string wsAddress = "ws://example.com:8080/path";
//	std::string host;
//	int port;
//
//	if (splitWSAddress(wsAddress, host, port)) {
//		std::cout << "Host: " << host << ", Port: " << port << std::endl;
//	}
//	else {
//		std::cout << "Invalid WS address format." << std::endl;
//	}
//
//	return 0;
//}


WS客户端::WS客户端() {
	WSADATA wsadata{};
	/*if (WSAStartup(MAKEWORD(2, 2), &wsadata) != NO_ERROR) {
	}*/
	
	if (WSA初始化计数器 == 0)
	{
		WSA初始化计数器++;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsadata);// != NO_ERROR
	}
	else {
		WSA初始化计数器++;
	}

	
	status = WS连接状态_未连接;
}

WS客户端::~WS客户端() {

	status = WS连接状态_未连接;
	//WSACleanup();
	if (WSA初始化计数器 == 1) {
		WSACleanup();
		WSA初始化计数器 = 0;
	}
	else {
		WSA初始化计数器--;
	}


}

BOOL WS客户端::连接(CXTextA Url, BOOL 异步) {


	CXTextA host;
	int port;
	splitWSAddress(Url, host, port);
	线程退出 = false;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		status = WS连接状态_未连接;
		return false;
	}

	sockaddr_in address{};
	address.sin_family = PF_INET;
	address.sin_port = htons(port);

	PADDRINFOA addrinfo{};

	GetAddrInfoA(host.getPtr(), std::to_string(port).c_str(), nullptr, &addrinfo);

	if (connect(s, addrinfo->ai_addr, addrinfo->ai_addrlen) == SOCKET_ERROR) {
		closesocket(s);
		status = WS连接状态_未连接;
		return false;
	}
	//如果需要IPV6则使用inet_pton   inet_addr只支持IPV4
	//	address.sin_addr.s_addr = inet_addr("124.222.224.186");
	//inet_pton(AF_INET, host.getPtr(), &address.sin_addr.s_addr);


	/*if (connect(s, (SOCKADDR*)&address, sizeof(address)) == SOCKET_ERROR) {
		closesocket(s);
		status = WS连接状态_未连接;
		return false;
	}*/
	ULONG mode = 0;
	ioctlsocket(s, FIONBIO, &mode);
	//setsockopt(s,)

	std::thread t = std::thread(接受数据, this);
	t.detach();
	t = std::thread();

	CXTextA request = "GET [地址] HTTP/1.1\r\n"\
		"Host: [主机]\r\n"\
		"Connection: Upgrade\r\n"\
		"Pragma: no-cache\r\n"\
		"Cache-Control: no-cache\r\n"\
		"User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)\r\n"\
		"Upgrade: websocket\r\n"\
		"Origin: [来源]\r\n"\
		"Sec-WebSocket-Version: 13\r\n"\
		"Accept-Encoding: gzip, deflate, br\r\n"\
		"Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6\r\n"\
		"Sec-WebSocket-Key: [KEY]\r\n"\
		"Sec-WebSocket-Extensions: permessage-deflate; client_max_window_bits\r\n\r\n";
	request.replaceSub("[主机]", host);
	request.replaceSub("[地址]", Url);
	request.replaceSub("[来源]", Url);
	request.replaceSub("[KEY]", "dGhlIHNhbXBsZSBub25jZQ==");


	if (send(s, request, request.size(), 0) == SOCKET_ERROR) {
		status = WS连接状态_未连接;
		return false;
	}

	if (异步) {
		status = WS连接状态_正在连接;
		return true;
	}

	while (!handshake) {
		Sleep(2);
	}
	status = WS连接状态_已连接;
	handshake = true;
	if (事件_连接成功) {
		((WS客户端事件_连接成功)事件_连接成功)();
	}
	return true;

}


void WS客户端::断开() {

	线程退出 = false;
	closesocket(s);
	while (true)
	{
		if (线程退出) {
			break;
		}
	}
	status = WS连接状态_未连接;
}


BOOL WS客户端::发送文本(CXTextA 文本)
{
	if (!handshake) { return false; }
	CXBytes buffer;
	数据帧编码(文本.getPtr(), 文本.size(), buffer, 1, true, true);
	return send(s, buffer.getTextPtrA(), buffer.size(), 0) != SOCKET_ERROR;
}

BOOL WS客户端::发送字节集(CXBytes 数据)
{
	if (!handshake) { return false; }

	CXBytes buffer;
	数据帧编码(数据.getTextPtrA(), 数据.size(), buffer, 2, true, true);
	return send(s, buffer.getTextPtrA(), buffer.size(), 0) != SOCKET_ERROR;

}

int WS客户端::取连接状态()
{
	return status;
}

CXText WS客户端::取错误信息()
{

	return 错误信息;
}

BOOL WS客户端::PING()
{
	if (!handshake) { return false; }

	CXBytes buffer;
	数据帧编码(nullptr, 0, buffer, 9, true, false);
	return send(s, buffer.getTextPtrA(), buffer.size(), 0) != SOCKET_ERROR;

}

BOOL WS客户端::PONG() {
	if (!handshake) { return false; }
	CXBytes buffer;
	数据帧编码(nullptr, 0, buffer, 10, true, false);
	return send(s, buffer.getTextPtrA(), buffer.size(), 0) != SOCKET_ERROR;

}



//' WS消息类型说明
//' 0x0表示附加数据帧
//' 0x1表示文本数据帧
//' 0x2表示二进制数据帧
//' 0x3-7暂时无定义，为以后的非控制帧保留
//' 0x8表示连接关闭
//' 0x9表示ping
//' 0xA表示pong
//' 0xB-F暂时无定义，为以后的控制帧保留




int WS客户端::数据帧编码(const char* 数据, int 长度, CXBytes& bin, int frameType, bool IsEof, bool hasMask)
{
	// header: 2字节, mask位若设置为0(不加密), 则后面的masking key无须填写, 省略4字节
	int ret = 0x0F;
	const uint32_t messageLength = 长度;
	//if (messageLength > 32767) { return -1; } //WS_ERROR_FRAME}// 暂不支持这么长的数据

	uint8_t payloadFieldExtraBytes = (messageLength <= 0x7d) ? 0 : 2;

	uint8_t frameHeaderSize = 2 + payloadFieldExtraBytes + 4;
	uint8_t* frameHeader = new uint8_t[frameHeaderSize];
	::memset(frameHeader, 0, frameHeaderSize);
	// fin位为1, 扩展位为0, 操作位为frameType
	frameHeader[0] = ((IsEof ? 1 : 0) << 7) | (frameType & 15); // static_cast<uint8_t>(0x80 | frameType);
	frameHeader[1] = (hasMask ? 1 : 0) << 7;

	// 填充数据长度
	if (messageLength >= 65536)
	{
		frameHeader[1] = frameHeader[1] | (127 & 127);//  static_cast<uint8_t>(messageLength);
		uint16_t len = htons(messageLength);
		memcpy(&frameHeader[2], &len, payloadFieldExtraBytes);
	}
	else if (messageLength >= 126)
	{
		frameHeader[1] = frameHeader[1] | (126 & 127);
		uint16_t len = htons(messageLength);
		memcpy(&frameHeader[2], &len, payloadFieldExtraBytes);
	}
	else
	{
		frameHeader[1] = frameHeader[1] | (messageLength & 127);

	}

	// 填充数据
	uint32_t frameSize = frameHeaderSize + messageLength;
	char* frame = new char[frameSize + 1];


	memcpy(frame, frameHeader, frameHeaderSize);
	memcpy(frame + frameHeaderSize, 数据, messageLength);
	frame[frameSize] = '\0';

	byte key[] = { 1,2,3,4 };
	memcpy(frame + frameHeaderSize - 4, key, 4);
	for (UINT i = frameHeaderSize; i < frameHeaderSize + messageLength; i++) {
		frame[i] = frame[i] ^ key[((i - 6) % 4)];
	}

	bin.add(frame, frameSize);
	//XCL_log(bin);
	delete[]frame;
	delete[]frameHeader;

	return ret;
}

int WS客户端::数据帧解码(包信息* outdata, const char* frameData, int len, char** lp_outMessage, int* packet_len, bool* end, int* endlen)
{
	int ret = -1; //WS_ERROR_FRAME

	const int frameLength = len;
	bool masked = false;
	if (frameLength < 2) {
		return ret;
	}
	// 检查扩展位并忽略
	if ((frameData[0] & 0x70) != 0x0) {
		return ret;
	}
	// fin位: 为1表示已接收完整报文, 为0表示继续监听后续报文
	*end = (frameData[0] & 0x80);

	if ((frameData[0] & 0x80) != 0x80) {
		return ret;
	}
	// mask位, 为1表示数据被加密
	if ((frameData[1] & 0x80) == 0x80) {
		masked = true;
	}
	// 操作码
	uint16_t payloadLength = 0;
	uint8_t payloadFieldExtraBytes = 0;
	uint8_t opcode = static_cast<uint8_t>(frameData[0] & 0x0f);

	/*std::cout << std::endl;
	std::cout << "mask:" << ((frameData[1] & 0x80) == 0x80) << std::endl;
	std::cout << "frameLength: " << frameLength << std::endl;
	std::cout << "payloadLength: " << payloadLength << std::endl;
	std::cout << "payloadFieldExtraBytes: " << payloadFieldExtraBytes << std::endl;
	std::cout << "opcode: " << (int)opcode << std::endl;*/


	outdata->opcode = opcode;

	if (opcode == WS_TEXT_FRAME)
	{
		// 处理utf-8编码的文本帧
		ret = WS_TEXT_FRAME;
		payloadLength = static_cast<uint16_t>(frameData[1] & 0x7f);
		if (payloadLength == 0x7e)
		{
			uint16_t payloadLength16b = 0;
			payloadFieldExtraBytes = 2;
			memcpy(&payloadLength16b, &frameData[2], payloadFieldExtraBytes);
			payloadLength = ntohs(payloadLength16b);
		}
		else if (payloadLength == 0x7f)
		{
			// 数据过长,暂不支持
			ret = -1; //WS_ERROR_FRAME
		}
	}
	else if (opcode == WS_BINARY_FRAME || opcode == WS_PING_FRAME || opcode == WS_PONG_FRAME)
	{
		// 二进制/ping/pong帧暂不处理
	}
	else //其他类型如 WS_CLOSING_FRAME等全部识别为断开连接
	{
		ret = -1;
		return ret;
	}
	//return ret;


	int masklen = masked ? 4 : 0;

	// header: 2字节, masking key: 4字节(如果有的话)
	if (2 + payloadFieldExtraBytes + masklen + payloadLength > len) {
		ret = 0;
		return ret;
	}
	const char* maskingKey = masked ? &frameData[2 + payloadFieldExtraBytes] : 0;

	char* payloadData = new char[payloadLength + 1];
	memset(payloadData, 0, payloadLength + 1);
	memcpy(payloadData, &frameData[2 + payloadFieldExtraBytes + masklen], payloadLength);
	if (masked) {
		for (int i = 0; i < payloadLength; i++)
		{
			payloadData[i] = (payloadData[i] ^ maskingKey[i % 4]);
		}
	}

	*lp_outMessage = payloadData;
	int totLen = payloadLength;
	*packet_len = totLen;
	*endlen = 2 + payloadFieldExtraBytes + 4 + totLen;
	payloadData[totLen] = 0x00;

	//std::cout << u8"payloadData" << std::endl;
	//std::cout << payloadData << std::endl;



	return opcode;


}


void  WS客户端::接受数据(WS客户端* client) {
	int len = 0, error = 0;
	CXTextA buffer;
	CXTextA buffer_all;
	CXBytes buffer_p;
	bool end = false;

	包信息 data;
	buffer.resize(1048576);
	while (true)
	{
		int len = recv(client->s, (char*)buffer.getPtr(), 1048576, 0);

		if (len == SOCKET_ERROR) {
			int error = WSAGetLastError();
			if (len<0 || error == WSAENETRESET || error == WSAESHUTDOWN || error == WSAETIMEDOUT || error == WSAECONNRESET) {
				//连接已中断/套接字已关闭/因为网络故障或对等系统无法响应，已经丢弃了连接。
				closesocket(client->s);

				client->s = 0;
				break;
			}

		}




		if (len >= 0) {
			buffer_all.append2(buffer, len);
			//std:cout << len;
		}
		if (buffer_all.size() == 0)
		{
			continue;
		}


		char* packet = 0;
		int endlen = 0;
		int packet_len = 0;
		int ret = 0;
		bool end = false;

		if (!client->handshake) {

			//printf(buffer_all.getPtr());
			//buffer_all.resize(0);
			if (buffer_all.substr(0, 12) == "HTTP/1.1 101") {
				client->handshake = true;
				client->status = WS连接状态_已连接;
				if (client->事件_连接成功 != 0) {
					((WS客户端事件_连接成功) client->事件_连接成功)();
				}
				buffer_all.resize(0);
			}
			else {
				closesocket(client->s);
				client->s = 0;
				break;
			}


		}
		else {
			while (true)
			{
				//从总缓冲区解码数据帧
				ret = 数据帧解码(&data, buffer_all.getPtr() + endlen, buffer_all.getSize() - endlen, &packet, &packet_len, &end, &endlen);

				if (ret != -1) {
					if (client-> 事件_收到帧) {
						WS帧 frame;
						frame.类型 = data.opcode;
						frame.数据.clear();
						frame.数据.add(packet, packet_len);
						((WS客户端事件_收到帧)client->事件_收到帧)(frame);
					}
				}


				if (data.opcode == WS_CLOSING_FRAME)
				{
					//遇到关闭帧则断开连接
					closesocket(client->s);
					client->s = 0;
					break;
				}
				else if ((ret == -1))
				{
					//遇到解析错误清空总缓冲区
					buffer_all.resize(0);
					break;
				}
				else if ((ret == 0))
				{
					//总缓冲区数据帧不完整，需要继续接收
					break;
				}
				else
				{
					//解析出完整数据帧
					buffer_p.resize(0);
					buffer_p.add(packet, packet_len);
					delete[]packet;
					if (end)
					{

						/*std::string utf8_str = u8"收到文本信息";
						std::cout << utf8_str<<std::endl;
						std::cout<<(buffer_p);*/
						if (client->事件_收到数据 != 0) {
							((WS客户端事件_收到数据) client->事件_收到数据)(buffer_p);
						}
					}
					if (endlen < buffer_all.getSize())
					{
						//总缓冲区有粘包数据，删除已解析部分
						buffer_all.erase(0, endlen);
					}
					else
					{
						//总缓冲区已解析完成，清空
						buffer_all.resize(0);
						break;
					}
				}
			}
		}


		if (client->s == 0)break;

		Sleep(2);

	}

	client->线程退出 = true;

	client->status = WS连接状态_未连接;
	if (client->事件_连接断开 != 0) {
		((WS客户端事件_连接断开)client->事件_连接断开)();
	}
}


}