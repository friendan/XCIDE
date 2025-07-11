#pragma once
//@隐藏{
#ifndef module_zy_zip_utils_h__
#define module_zy_zip_utils_h__
//@隐藏}

#include <windows.h>

#include "zip_utils_src/zip.h"
#include "zip_utils_src/unzip.h"

#include "module_base.h"

//@模块名称 zyZIP实用工具
//@版本  1.0
//@日期  2022-08-18
//@作者  kyozy
//@QQ  75602718
//@模块备注  接口简单的ZIP压缩解压类

//@预处理宏 _CRT_SECURE_NO_WARNINGS
//@依赖  module_base.h
//@src  "zip_utils_src/zip.cpp"
//@src  "zip_utils_src/unzip.cpp"


//@分组{ 枚举
/*@声明

@别名 ZR_成功
#define ZR_OK         0x00000000

@别名 ZR_近似
#define ZR_RECENT     0x00000001     // 永远不会返回的伪错误代码

@别名 ZR_生成掩码
#define ZR_GENMASK    0x0000FF00

@别名 ZR_无法复制
#define ZR_NODUPH     0x00000100     // 无法复制句柄

@别名 ZR_无文件
#define ZR_NOFILE     0x00000200     // 无法创建/打开文件

@别名 ZR_无法分配
#define ZR_NOALLOC    0x00000300     // 未能分配一些资源

@别名 ZR_写入
#define ZR_WRITE      0x00000400     // 写入文件的一般错误 

@别名 ZR_未找到
#define ZR_NOTFOUND   0x00000500     // 在 zip 中找不到该文件 

@别名 ZR_更多
#define ZR_MORE       0x00000600     // 还有更多数据需要解压 

@别名 ZR_损坏
#define ZR_CORRUPT    0x00000700     // zip文件 已损坏或不是 zip文件

@别名 ZR_读取
#define ZR_READ       0x00000800     // 读取文件的一般错误 

// 以下来自调用者的错误

@别名 ZR_调用掩码
#define ZR_CALLERMASK 0x00FF0000

@别名 ZR_参数
#define ZR_ARGS       0x00010000     // 参数的一般错误

@别名 ZR_非映射文件
#define ZR_NOTMMAP    0x00020000     // 尝试使用 ZipGetMemory，但这仅适用于 mmap zipfile，而您的则不是 

@别名 ZR_内存大小
#define ZR_MEMSIZE    0x00030000     // 内存太小

@别名 ZR_失败
#define ZR_FAILED     0x00040000     // 当你调用这个函数时，事情已经失败了

@别名 ZR_关闭
#define ZR_ENDED      0x00050000     // zip创建已关闭 

@别名 ZR_错误大小
#define ZR_MISSIZE    0x00060000     // 指示的输入文件大小结果是错误的 

@别名 ZR_部分解压
#define ZR_PARTIALUNZ 0x00070000     // 该文件已经部分解压

@别名 ZR_模式
#define ZR_ZMODE      0x00080000     // 尝试混合 创建/打开 zip 

// 以下来自 zip 库本身的错误

@别名 ZR_BUG掩码
#define ZR_BUGMASK    0xFF000000

@别名 ZR_无法初始化
#define ZR_NOTINITED  0x01000000     // 初始化不起作用

@别名 ZR_寻找
#define ZR_SEEK       0x02000000     // 试图在一个不可搜索的文件中寻找

@别名 ZR_不能改变
#define ZR_NOCHANGE   0x04000000     // 在存储上改变了主意，但不允许

@别名 ZR_内部
#define ZR_FLATE      0x05000000     // de/inflation 代码中的内部错误 

*/
//@分组} 枚举


//@分组{ 核心


//@别名 zyZIP项目信息
class zyZipEntry :public ZIPENTRY
{
public:
	//@隐藏{
	zyZipEntry(){
		ZeroMemory(this, sizeof(ZIPENTRY));
		this->index = -1;
	}
	//@隐藏}

	//@别名 取索引()
	int GetIndex() const {
		return this->index;
	}

	//@别名 取名称()
	TCHAR* GetName() const {
		return (TCHAR*)this->name;
	}

	//@别名 取文件属性()
	DWORD GetAttr() const {
		return this->attr;
	}
	
	//@别名 取访问时间()
	tm GetATime() const
	{
		SYSTEMTIME sysTime;
		FILETIME localTime;
		tm ct;
		FileTimeToLocalFileTime(&this->atime, &localTime);
		FileTimeToSystemTime(&localTime, &sysTime);
		ct.tm_sec = sysTime.wSecond;         // Second
		ct.tm_min = sysTime.wMinute;         // Minute
		ct.tm_hour = sysTime.wHour;          // Hour
		ct.tm_mday = sysTime.wDay;           // Day
		ct.tm_mon = sysTime.wMonth - 1;       // Month
		ct.tm_year = sysTime.wYear - 1900;   // Year
		ct.tm_wday = sysTime.wDayOfWeek;     // Day of week
		return ct;
	}
	//@别名 取创建时间()
	tm GetCTime() const
	{
		SYSTEMTIME sysTime;
		FILETIME localTime;
		tm ct;
		FileTimeToLocalFileTime(&this->ctime, &localTime);
		FileTimeToSystemTime(&localTime, &sysTime);
		ct.tm_sec = sysTime.wSecond;         // Second
		ct.tm_min = sysTime.wMinute;         // Minute
		ct.tm_hour = sysTime.wHour;          // Hour
		ct.tm_mday = sysTime.wDay;           // Day
		ct.tm_mon = sysTime.wMonth - 1;       // Month
		ct.tm_year = sysTime.wYear - 1900;   // Year
		ct.tm_wday = sysTime.wDayOfWeek;     // Day of week
		return ct;
	}
	//@别名 取修改时间()
	tm GetMTime() const
	{
		SYSTEMTIME sysTime;
		FILETIME localTime;
		tm ct;
		FileTimeToLocalFileTime(&this->mtime, &localTime);
		FileTimeToSystemTime(&localTime, &sysTime);
		ct.tm_sec = sysTime.wSecond;         // Second
		ct.tm_min = sysTime.wMinute;         // Minute
		ct.tm_hour = sysTime.wHour;          // Hour
		ct.tm_mday = sysTime.wDay;           // Day
		ct.tm_mon = sysTime.wMonth - 1;       // Month
		ct.tm_year = sysTime.wYear - 1900;   // Year
		ct.tm_wday = sysTime.wDayOfWeek;     // Day of week
		return ct;
	}
	//@别名 取压缩尺寸()
	long GetCompSize() const
	{
		return this->comp_size;
	}
	//@别名 取解压尺寸()
	long GetUnCompSize() const
	{
		return this->unc_size;
	}

};

//@别名 zyZIP压缩
class zyZip
{
	//@隐藏{
public:
	HZIP m_hZip;
	zyZip():m_hZip(nullptr){}
	~zyZip(){
		if (m_hZip)
		{
			CloseZip(m_hZip);
		}
	}
	zyZip(zyZip&& other){
		HZIP temp = other.m_hZip;
		other.m_hZip = m_hZip;
		m_hZip = temp;
	}
	zyZip& operator=(zyZip&& other) noexcept{
		if (this != &other)
		{
			if (m_hZip)
			{
				CloseZip(m_hZip);
				m_hZip = nullptr;
			}
		}
		m_hZip = other.m_hZip;
		other.m_hZip = nullptr;
	}

	zyZip(const zyZip&) = delete;
	zyZip& operator=(const zyZip&) = delete;
	//@隐藏}

	// @备注 从文件创建
	// @参数 文件名
	// @参数 密码
	// @返回 成功返回真,失败返回假
	// @别名 创建自文件(文件名,密码)
	bool CreateFromFile(const TCHAR* fn, const char* password = nullptr){
		if (m_hZip)
		{
			CloseZip(m_hZip);
		}
		m_hZip = ::CreateZip(fn, password);
		return m_hZip != nullptr;
	}

	// @备注 从内存创建
	// @参数 内存地址 为空指针
	// @参数 长度 内存长度
	// @参数 密码
	// @返回 成功返回真,失败返回假
	// @别名 创建自内存(内存地址,长度,密码)
	bool CreateFromMemory(void* buf, unsigned int len, const char* password = nullptr){
		if (m_hZip)
		{
			CloseZip(m_hZip);
		}
		m_hZip = ::CreateZip(buf, len, password);
		return m_hZip != nullptr;
	}

	// @备注 从字节集创建
	// @参数 字节集
	// @参数 密码
	// @返回 成功返回真,失败返回假
	// @别名 创建自字节集(字节集,密码)
	bool CreateFromBtytes(CXBytes& bytes, const char* password = nullptr) {
		if (m_hZip)
		{
			CloseZip(m_hZip);
		}
		m_hZip = ::CreateZip((void*)bytes.get(), (unsigned int)bytes.size(), password);
		return m_hZip != nullptr;
	}

	// @备注 从内存创建
	// @参数 句柄 文件句柄或管道句柄。
	// @参数 密码 压缩包密码。
	// @返回 成功返回真,失败返回假
	// @别名 创建自句柄(句柄,密码)
	bool CreateFromHandle(HANDLE h, const char* password = nullptr) {
		if (m_hZip)
		{
			CloseZip(m_hZip);
		}
		m_hZip = ::CreateZipHandle(h, password);
		return m_hZip != nullptr;
	}

	//@别名 关闭()
	void Close(){
		if (m_hZip)
		{
			CloseZip(m_hZip);
			m_hZip = nullptr;
		}
	}

	// @备注 从文件名加入项目到压缩包
	// @参数 项目名 压缩包中的项目名称
	// @参数 文件名 磁盘文件名路径
	// @返回 ZR_ 开头常量
	// @别名 添加文件(项目名,文件名)
	ZRESULT AddFile(const TCHAR* dstzn, const TCHAR* fn){
		return ::ZipAdd(m_hZip, dstzn, fn);
	}

	// @备注 从内存加入项目到压缩包
	// @参数 项目名 压缩包中的项目名称
	// @参数 内存地址 包含数据的内存地址
	// @参数 内存长度 内存数据的大小
	// @返回 ZR_ 开头常量
	// @别名 添加内存(项目名, 内存地址, 内存长度)
	ZRESULT AddMemory(const TCHAR* dstzn, void* src, unsigned int len) {
		return ::ZipAdd(m_hZip, dstzn, src, len);
	}

	// @备注 从文件名加入项目到压缩包
	// @参数 项目名 压缩包中的项目名称
	// @参数 字节集 字节集数据
	// @返回 ZR_ 开头常量
	// @别名 添加字节集(项目名, 字节集)
	ZRESULT AddBytes(const TCHAR* dstzn, const CXBytes& src) {
		return ::ZipAdd(m_hZip, dstzn, (void*)src.get(), src.size());
	}

	// @备注 从句柄中加入项目到压缩包
	// @参数 项目名 压缩包中的项目名称
	// @参数 句柄 文件或管道句柄
	// @返回 ZR_ 开头常量
	// @别名 添加句柄(项目名, 句柄)
	ZRESULT AddHandle(const TCHAR* dstzn, HANDLE h){
		return ::ZipAddHandle(m_hZip, dstzn, h);
	}

	// @备注 从句柄中加入项目到压缩包
	// @参数 项目名 压缩包中的项目名称
	// @参数 句柄 文件或管道句柄
	// @参数 长度 数据长度
	// @返回 ZR_ 开头常量
	// @别名 添加句柄(项目名, 句柄, 长度)
	ZRESULT AddHandle(const TCHAR* dstzn, HANDLE h, unsigned int len){
		return ::ZipAddHandle(m_hZip, dstzn, h, len);
	}
	
	// @备注 向压缩包添加一个空目录
	// @参数 目录 项目名称
	// @返回 ZR_ 开头常量
	// @别名 添加目录(目录)
	ZRESULT AddFolder(const TCHAR* dstzn){
		return ::ZipAddFolder(m_hZip, dstzn);
	}

	// @备注 当你使用 创建(0,长度) 时, 可以获取其内存地址 和 长度. 注意: 一旦调用将不能添加项目
	// @参数 内存地址 接收内存地址的指针
	// @参数 长度 接收内存长度的指针
	// @返回 ZR_ 开头常量
	// @别名 取内存(内存地址, 长度)
	ZRESULT GetMemory(void** buf, unsigned long* len){
		return ::ZipGetMemory(m_hZip, buf, len);
	}

};


//@别名 zyZIP解压
class zyUnZip
{
	//@隐藏{
public:
	HZIP m_hZip;
	zyUnZip() :m_hZip(nullptr) {}
	~zyUnZip() {
		if (m_hZip)
		{
			CloseZip(m_hZip);
		}
	}
	zyUnZip(zyUnZip&& other) noexcept {
		HZIP temp = other.m_hZip;
		other.m_hZip = m_hZip;
		m_hZip = temp;
	}
	zyUnZip& operator=(zyUnZip&& other) noexcept {
		if (this != &other)
		{
			if (m_hZip)
			{
				CloseZip(m_hZip);
				m_hZip = nullptr;
			}
		}
		m_hZip = other.m_hZip;
		other.m_hZip = nullptr;
	}

	zyUnZip(const zyUnZip&) = delete;
	zyUnZip& operator=(const zyUnZip&) = delete;
	//@隐藏}

	// @备注 从文件打开一个ZIP压缩包
	// @参数 文件名 压缩包文件名
	// @参数 密码 压缩包密码
	// @返回 成功返回 真
	// @别名 打开自文件(文件名, 密码)
	bool OpenFromFile(const TCHAR* fn, const char* password = nullptr){
		m_hZip = ::OpenZip(fn, password);
		return m_hZip != nullptr;
	}

	// @备注 从内存打开一个ZIP压缩包
	// @参数 内存地址 压缩包内存地址
	// @参数 内存长度 压缩包长度
	// @参数 密码 压缩包密码
	// @返回 成功返回 真
	// @别名 打开自内存(内存地址, 内存长度, 密码)
	bool OpenFromMemory(void* z, unsigned int len, const char* password = nullptr) {
		m_hZip = ::OpenZip(z, len, password);
		return m_hZip != nullptr;
	}

	// @备注 从字节集打开一个ZIP压缩包
	// @参数 字节集 压缩包字节集数据
	// @参数 密码 压缩包密码
	// @返回 成功返回 真
	// @别名 打开自字节集(字节集, 密码)
	bool OpenFromBytes(const CXBytes& bytes, const char* password) {
		m_hZip = ::OpenZip((void*)bytes.get(), bytes.size(), password = nullptr);
		return m_hZip != nullptr;
	}

	// @备注 从句柄打开一个ZIP压缩包
	// @参数 句柄 文件句柄或管道句柄
	// @参数 密码 压缩包密码
	// @返回 成功返回 真
	// @别名 打开自句柄(文件名, 密码)
	bool OpenFromHandle(HANDLE h, const char* password = nullptr) {
		m_hZip = ::OpenZipHandle(h, password);
		return m_hZip != nullptr;
	}

	// @别名 取项目数()
	int GetItemCount() const{
		ZIPENTRY ze;
		ZRESULT zr = ::GetZipItem(m_hZip, -1, &ze);
		if (zr == ZR_OK)
		{
			return ze.index;
		}
		return 0;
	}


	// @备注 获取压缩包内的项目信息。
	// @参数 索引 压缩包项目索引, 索引从0开始。
	// @参数 信息 返回的项目信息
	// @返回 ZR_ 开头常量
	// @别名 取项目信息(索引, 信息)
	ZRESULT GetItemInfo(int index, ZIPENTRY* ze){
		return ::GetZipItem(m_hZip, index, ze);
	}

	// @备注 根据项目名寻找指定项目。
	// @参数 名称 要寻找的项目名。
	// @参数 忽略大小写 是否忽略大小写
	// @参数 信息 返回的项目信息
	// @返回 ZR_ 开头常量
	// @别名 寻找项目(名称,忽略大小写, 信息)
	ZRESULT FindItem(const TCHAR* name, bool ic, ZIPENTRY* ze){
		int index = -1;
		ze->index = -1;
		ZRESULT zr = ::FindZipItem(m_hZip, name, ic, &index, ze);
		ze->index = index;
		return zr;
	}

	// @备注 解压指定索引项目
	// @参数 索引 压缩包项目索引, 索引从0开始。
	// @参数 文件名 解压到的文件名。
	// @返回 ZR_ 开头常量
	// @别名 解压到文件(索引, 文件名)
	ZRESULT UnzipItem(int index, const TCHAR* fn){
		return ::UnzipItem(m_hZip, index, fn);
	}

	// @备注 解压指定索引项目到内存
	// @参数 索引 压缩包项目索引, 索引从0开始。
	// @参数 内存地址 解压到的此地址。
	// @参数 长度 内存长度。
	// @返回 ZR_ 开头常量
	// @别名 解压到内存(索引, 内存地址, 长度)
	ZRESULT UnzipItem(int index, void* z, unsigned int len) {
		return ::UnzipItem(m_hZip, index, z, len);
	}

	// @备注 解压指定索引项目
	// @参数 索引 压缩包项目索引, 索引从0开始。
	// @参数 字节集 解压到此字节集。
	// @返回 ZR_ 开头常量
	// @别名 解压到字节集(索引, 字节集)
	ZRESULT UnzipItem(int index, CXBytes& bytes) {
		ZIPENTRY ze;
		ZRESULT zr = ::GetZipItem(m_hZip, index, &ze);
		if (zr != ZR_OK)
		{
			return zr;
		}
		bytes.resize(ze.unc_size);
		return ::UnzipItem(m_hZip, index, (void*)bytes.get(), ze.unc_size);
	}

	// @备注 解压指定索引项目
	// @参数 索引 压缩包项目索引, 索引从0开始。
	// @参数 句柄 解压到的文件句柄或管道句柄
	// @返回 ZR_ 开头常量
	// @别名 解压到句柄(索引, 句柄)
	ZRESULT UnzipItemHandle(int index, HANDLE h) {
		return ::UnzipItemHandle(m_hZip, index, h);
	}

	// @备注 设置解压项目的根目录
	// @参数 解压根目录 解压的文件名相对于此目录。
	// @返回 ZR_ 开头常量
	// @别名 置解压根目录(解压根目录)
	ZRESULT SetUnzipBaseDir(const TCHAR* dir){
		return ::SetUnzipBaseDir(m_hZip, dir);
	}



};


//@分组}   核心



#endif // module_zy_zip_utils_h__



