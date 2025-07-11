
#pragma once

//@模块名称  数据库mysql类
//@版本  1.0
//@日期  2023-05-28
//@作者  qq128492656
//@模块备注  MYSQL数据库二次封装,方便使用, mysql版本 5.7.16
//@依赖  module_mysql.h
//@src "mysql2.cpp"  

#ifdef  XC_MODULE
#include "module_mysql.h"
#endif

class CMySql记录集类
{

private:
	MYSQL_RES* m_data;
public:
	void  SetData(MYSQL_RES* ptr);
	CMySql记录集类();
	~CMySql记录集类();
	void  关闭();
	BOOL  是否有效();
	INT64  取行数();
	int  取列数();
	int  取列长度();
	BOOL  取字段列表(CXVector<MYSQL_FIELD*>* 结果数据);
	BOOL  取当前行数据(CXVector<CXBytes>* 结果数据);
	BOOL  取当前行文本数据(CXVector<CXText>* 结果数据);
	BOOL  取当前行整数数据(CXVector<int>* 结果数据);
	BOOL  到下一行();
	BOOL  到指定行(INT64 行);
	BOOL  读字节集数据(CXText 字段名, CXBytes* 返回数据);
	BOOL  读索引字节集数据(UINT 字段索引, CXBytes* 返回数据);
	CXText  读文本数据(CXText 字段名);
	CXText  读索引文本数据(int 字段索引);
	int  读整数数据(CXText 字段名);
	int  读索引整数数据(int 字段索引);
	short  读短整数数据(CXText 字段名);
	short  读索引短整数数据(int 字段索引);
	INT64  读长整数数据(CXText 字段名);
	INT64  读索引长整数数据(int 字段索引);
	BOOL  读逻辑型数据(CXText 字段名);
	BOOL  读索引逻辑型数据(int 字段索引);
	BYTE  读字节数据(CXText 字段名);
	BYTE  读索引字节数据(int 字段索引);
	wchar_t  读字符数据(CXText 字段名);
	wchar_t  读索引字符数据(int 字段索引);
	float  读浮点型数据(CXText 字段名);
	float  读索引浮点型数据(int 字段索引);
	double  读双浮点型数据(CXText 字段名);
	double  读索引双浮点型数据(int 字段索引);
};



class CMySql数据库类
{

private:
	MYSQL* m_data;
public:
	MYSQL_RES* resPtr;
	CMySql数据库类();
	~CMySql数据库类();
	BOOL  连接(CXText 地址=L"127.0.0.1" , CXText 用户名=L"root" , CXText 密码=L"haosql" , CXText 数据库名=L"test" , int 端口=3306 , CXText 套接字=NULL, int 配置位=0 );
	CXText  取客户端版本名();
	UINT64  取客户端版本号();
	int  线程安全();
	void  置连接超时(int 超时);
	int  取连接超时();
	void  置读取超时(int 超时);
	int  取读取超时();
	void  置写入超时(int 超时);
	int  取写入超时();
	int  置通报数据截断错误(BOOL 启用);
	BOOL  取通报数据截断错误();
	void  置自动提交事务(BOOL 启用);
	void  置自动重连(BOOL 启用);
	BOOL  取自动重连();
	void  置连接后命令(CXText 命令内容);
	void  置命名选项文件(CXText 文件);
	void  置命名选项组(CXText 命名组);
	void  置字符集定义文件(CXText 文件);
	void  置协议类型(int 类型);
	void  置共享内存对象名称(CXText 名称);
	BOOL  多个查询结果();
	int  启用SSL(CXText 私钥文件, CXText 证书文件, CXText 授权文件, CXText 目录名称, CXText 允许密码列表);
	CXText  取SSL允许密码列表();
	BOOL  修改用户(CXText 数据库名, CXText 用户名, CXText 密码);
	BOOL  选择库(CXText 数据库名);
	BOOL  执行SQL语句(CXText 语句内容);
	BOOL  执行SQL语句_二进制(CXBytes 语句内容);
	int  到下一个记录集();
	BOOL  取记录集(CMySql记录集类 * 记录集);
	//@备注 mysql_use_result 函数不会将整个结果集存储在客户端内存中，而是逐行从服务器读取数据
	// 这种方式适用于处理大型结果集，因为它可以节省内存
	// 使用 mysql_use_result 后，必须逐行读取数据（通过 mysql_fetch_row），直到返回 nullptr
	// 使用完结果集后，必须调用 mysql_free_result 释放资源
	// 在使用 mysql_use_result 时，连接不能执行其他查询，直到结果集完全读取并释放
	BOOL  取临时记录集(CMySql记录集类 * 记录集);
	//@备注 mysql_list_dbs 函数用于列出 MySQL 服务器上的所有数据库。它返回一个结果集，其中包含数据库名称
	// 使用 mysql_list_dbs 后，必须通过 mysql_fetch_row （遍历结果集）逐行读取结果集，直到返回 nullptr
	// 使用完结果集后，必须调用 mysql_free_result 释放资源
	// 通配符支持 %（匹配任意字符序列）和 _（匹配单个字符）
	BOOL  取所有库(CMySql记录集类 * 记录集, CXText 通配符);
	BOOL  置当前字符集(CXText 字符集);
	BOOL  写入调试日志();
	BOOL  刷新(int 配置位);
	BOOL  关闭线程(int 线程ID);
	BOOL  检测连接状态(int 线程ID);
	BOOL  重置当前连接(int 线程ID);
	BOOL  开始提交事务();
	BOOL  回滚事务();
	void  关闭();
	CXTextA  取错误信息();
};




