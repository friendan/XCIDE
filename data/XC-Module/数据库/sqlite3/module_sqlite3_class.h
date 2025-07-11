#ifndef  XC_SQLITE3_CLASS_H
#define  XC_SQLITE3_CLASS_H

//@模块名称  sqlite3-类
//@版本  1.0  
//@日期  2021-03-08
//@作者  XCGUI  
//@模块备注 官方文档:https://www.sqlite.org/docs.html
//@依赖  module_sqlite3.h


#ifdef XC_MOUDLE
#include "module_sqlite3.h"
#endif

//@src "module_sqlite3_class.cpp"


//@别名 Sqlite3错误
class CXSqlite3Err
{
public:
	CXSqlite3Err();
	~CXSqlite3Err();
	const char*    m_errA;
	const wchar_t* m_err;

	void  close();
};

//@别名  Sqlite3数据库类
class CXSqlite3
{
public:
	CXSqlite3();
	~CXSqlite3();
	sqlite3* m_db;

	//@别名 打开A(文件名)
	int openA(const char *filename);

	//@别名 打开(文件名)
	int open(const wchar_t *filename);

	//@别名 关闭()
	int close();
	
	//@别名 执行SQL(sql字符串, 回调函数, 自定义数据, 接收错误信息)
	//@参数 sql语句内容 提供所欲执行的SQL语句
	//@参数 自定义数据 可留空
	//@参数 回调函数 可留空
	//@参数 接收错误信息 可留空,如果本次执行出现错误,错误的具体内容将会写入至该变量.
	int exec(const char *sql, int(*callback)(void*, int, char**, char**), void *userData, CXSqlite3Err& err);

	//@备注 不需要释放返回值
	//@别名 取错误信息A()
	const char* errMsgA();

	//@备注 不需要释放返回值
	//@别名 取错误信息()
	const wchar_t* errMsg();
	
	//@返回 0表示执行成功,其他值请参考"SQLite执行结果"所提供的常量.
	//@备注 更改"main"数据库模式的名称
	//@别名 置主库名称()
	int SetMaindbName(const char * pName);
	
	//@返回 0表示执行成功,其他值请参考"SQLite执行结果"所提供的常量.
	//@备注 设置是否启用外键约束
	//@别名 启用外键约束()
	int EnableFkey(BOOL Enable);	
};

//@别名  Sqlite3记录集类
class CXStmt
{
public:
	CXStmt();
	~CXStmt();
	sqlite3_stmt* m_stmt;
	
	//@参数 返回下一条语句
	//@参数 内容偏移 指定所欲编译SQL语句内容的偏移位置,-1表示编译所有内容,>N表示编译从0至第N个字符,N必须大于0
	//@参数 sq语句 提供所欲编译的SQL语句,其中可包含参数所对应的变量名称.例如带参数插入数据:INSERT INTO 表名称 VALUES (?,?,...)
	//@参数 数据库连接句柄
	//@别名 准备A(数据库连接句柄, sq语句, 长度, 返回下一条语句)
	int prepareA(CXSqlite3 &db, const char *zSql, int nByte, const char **pzTail);
	//@参数 返回下一条语句
	//@参数 内容偏移 指定所欲编译SQL语句内容的偏移位置,-1表示编译所有内容,>N表示编译从0至第N个字符,N必须大于0
	//@参数 sq语句 提供所欲编译的SQL语句,其中可包含参数所对应的变量名称.例如带参数插入数据:INSERT INTO 表名称 VALUES (?,?,...)
	//@参数 数据库连接句柄	
	//@别名 准备(数据库连接句柄, sq语句, 长度, 返回下一条语句)
	int prepare(CXSqlite3 &db, const wchar_t *zSql, int nByte, const wchar_t **pzTail);
	
	//@别名 单步()
	int step();

	//@别名 重置()
	int reset();

	//@别名 释放()
	int close();
	//@参数 所欲读取值所处的列位置
	//@备注 读取当前行指定列索引的小数数据
	//@别名 取列小数(索引_1开始)
	double column_double(int nCol);
	//@参数 所欲读取值所处的列位置
	//@别名 取列整型(索引_1开始)
	int column_int(int nCol);
	//@参数 所欲读取值所处的列位置
	//@别名 取列整型64(索引_1开始)
	__int64 column_int64(int nCol);
	//@参数 所欲读取值所处的列位置
	//@别名 取列文本A(索引_1开始)
	const char *column_textA(int nCol);
	//@参数 所欲读取值所处的列位置
	//@别名 取列文本(索引_1开始)
	const wchar_t *column_text(int nCol);
	//@参数 所欲读取值所处的列位置
	//@别名 取列字节(索引_1开始)
	int column_bytes(int nCol);
	//@参数 所欲读取值所处的列位置
	//@别名 取列双字节(索引_1开始)
	int column_bytes16(int nCol);
	//@参数 所欲读取值所处的列位置
	//@别名 取列类型(索引_1开始)
	int column_type(int nCol);
	//@参数 所欲读取值所处的列位置
	//@别名 取列名A(索引_1开始)
	const char *column_nameA(int nCol);
	//@参数 所欲读取值所处的列位置
	//@别名 取列名(索引_1开始)
	const wchar_t *column_name(int nCol);
	//@参数 值 欲置入的值
	//@参数 索引_1开始 欲设置参数所处的索引位置,请注意参数索引从1开始
	//@别名 绑定双精度浮点型(索引_1开始, 值)
	int bind_double(int nCol, double fValue);
	//@参数 值 欲置入的值
	//@参数 索引_1开始 欲设置参数所处的索引位置,请注意参数索引从1开始
	//@别名 绑定整型(索引_1开始, 值)
	int bind_int(int nCol, int nValue);
	//@参数 值 欲置入的值
	//@参数 索引_1开始 欲设置参数所处的索引位置,请注意参数索引从1开始
	//@别名 绑定整型64(索引_1开始, 值)
	int bind_int64(int nCol, __int64 nValue);
	//@参数 值 欲置入的值
	//@参数 索引_1开始 欲设置参数所处的索引位置,请注意参数索引从1开始
	//@别名 绑定空(索引_1开始)
	int bind_null(int nCol);
	//@参数 回调函数 可留空
	//@参数 字符串长度 默认-1
	//@参数 值 欲置入的值
	//@参数 索引_1开始 欲设置参数所处的索引位置,请注意参数索引从1开始
	//@别名 绑定文本A(索引_1开始, 字符串, 字符串长度, 回调函数)
	int bind_textA(int nCol, const char* text, int textLength, void(*f)(void*));
	//@参数 回调函数 可留空
	//@参数 字符串长度 默认-1
	//@参数 值 欲置入的值
	//@参数 索引_1开始 欲设置参数所处的索引位置,请注意参数索引从1开始
	//@别名 绑定文本(索引_1开始, 字符串, 字符串长度, 回调函数)
	int bind_text(int nCol, const wchar_t* text, int textLength, void(*)(void*));
	//@参数 回调函数 可留空
	//@参数 字符串长度 默认-1
	//@参数 值 欲置入的值
	//@参数 索引_1开始 欲设置参数所处的索引位置,请注意参数索引从1开始
	//@别名 绑定文本64(索引_1开始, 字符串, 字符串长度, 回调函数)
	int bind_text64(int nCol, const char* text, unsigned __int64 textLength, void(*f)(void*), unsigned char encoding);
};

#endif  //XC_SQLITE3_CLASS_H