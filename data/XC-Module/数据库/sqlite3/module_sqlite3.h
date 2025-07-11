#ifndef  XC_SQLITE3_H
#define  XC_SQLITE3_H

//@模块名称  sqlite3
//@版本  1.0  
//@日期  2021-03-08
//@作者  XCGUI  
//@模块备注 官方文档:https://www.sqlite.org/docs.html



#ifdef  _WIN64
//@lib "x64\sqlite3.lib"
//@复制文件 @当前模块路径 "x64\sqlite3.dll"
#else
//@lib "x86\sqlite3.lib"
//@复制文件 @当前模块路径 "x86\sqlite3.dll"
#endif

#include "module_base.h"

//@隐藏{
//#ifdef __cplusplus
extern "C" {
//#endif
//@隐藏}
	typedef struct sqlite3 sqlite3;
	typedef struct sqlite3_stmt  sqlite3_stmt;
//@分组{  SQLite3记录集
	//@别名 记录集3_取当前记录列数()
	int sqlite3_data_count(sqlite3_stmt *pStmt);
	//@别名 记录集3_取参数数量()
	int sqlite3_bind_parameter_count(sqlite3_stmt *pStmt);
	//@别名 记录集3_取列数()
	int sqlite3_column_count(sqlite3_stmt *pStmt);
	//@别名 记录集3_取指定参数名()
	const char *sqlite3_bind_parameter_name(sqlite3_stmt*, int id);
	//@别名 记录集3_取指定参数索引()
	int sqlite3_bind_parameter_index(sqlite3_stmt*, const char *zName);
	//@别名 记录集3_置所有参数为空()
	int sqlite3_clear_bindings(sqlite3_stmt*);
	//@参数 [in]数据库连接句柄
	//@参数 [in]编译的语句，编码为UTF-8
	//@参数 [in]如果为nbytes参数小于零，则szSql将读取到第一个零终止符。如果为nbytes为非负数，则为从szSql读取的最大字节数。当为nbytes为非负值时，szSql字符串以第一个“\\ 000”或“\\ u0000”字符或第nB字节结尾，以先到者为准。如果调用者知道提供的字符串是非终止的，那么通过传递等于输入字符串中包含nul-terminator字节的字节数的为nbytes参数可以获得较小的性能优势，因为这样保存SQLite不必制作输入字符串的副本。
	//@参数 [inout]ppStmt指向可以使用sqlite3_step执行的编译准备语句。如果有错误，ppStmt设置为NULL。如果输入文本不包含SQL（如果输入是空字符串或注释），则ppStmt设置为NULL。调用过程在完成之后负责使用sqlite3_finalize删除编译的SQL语句。ppStmt可能不为空
	//@参数 [in]如果pzTail不为空，则指向szSql中第一个SQL语句结尾的第一个字节。这些函数只能编译szSql中的第一个语句，所以pzTail指向未编译的内容。
	//@返回 如果成功返回SQLITE_OK，否则返回错误代码。
	//@备注 要执行SQL查询，必须首先使用其中一个准备函数将其编译成字节码程序。
	//@别名 记录集3_取记录集(数据库连接句柄, sq语句, 长度, 语句句柄, 返回下一条语句)
	int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nByte, sqlite3_stmt **ppStmt, const char **pzTail);

	//@参数 [in]数据库连接句柄
	//@参数 [in]要编译的语句，编码为UTF-16。
	//@参数 [in]如果为nbytes参数小于零，则szSql读取到第一个零终止符。如果为nbytes为非负数，则为从szSql读取的最大字节数。当为nbytes为非负数时，szSql字符串以第一个“\\ 000”或“\\ u0000”字符或第nB字节结尾，以先到者为准。如果调用者知道提供的字符串是非终止的，那么通过传递等于输入字符串中包含Nul-Terminator字节的字节数的为nbytes参数可以获得较小的性能优势，因为这样保存SQLite不必制作输入字符串的副本。
	//@参数 [inout]ppStmt指向可以使用sqlite3_step执行的编译准备语句。如果有错误，ppStmt设置为NULL。如果输入文本不包含SQL（如果输入是空字符串或注释），则ppStmt设置为NULL。调用过程完成后，负责使用sqlite3_finalize删除编译的SQL语句。ppStmt可能不为空。
	//@参数 [in]如果pzTail不为NULL，则指向szSql中第一个SQL语句结尾的第一个字节。这些函数只编译在szSql中的第一个语句，所以pzTail指向什么仍然未编译。
	//@返回 如果成功返回SQLITE_OK，否则返回错误代码
	//@备注 要执行SQL查询，必须首先使用其中一个准备函数将其编译成字节码程序。
	//@别名 记录集3_语句准备16()
	int sqlite3_prepare16_v2(sqlite3 *db, const void *zSql, int nByte, sqlite3_stmt **ppStmt, const void **pzTail);

	//@别名 记录集3_执行语句()
	int sqlite3_step(sqlite3_stmt*);

	//@别名 记录集3_重置()
	int sqlite3_reset(sqlite3_stmt *pStmt);

	//@别名 记录集3_释放()
	int sqlite3_finalize(sqlite3_stmt *pStmt);
	//@别名 记录集3_取列小数(语句, 列索引_1开始)
	double sqlite3_column_double(sqlite3_stmt*, int iCol);
	//@别名 记录集3_取列整型(语句, 列索引_1开始)
	int sqlite3_column_int(sqlite3_stmt*, int iCol);

	//@别名 记录集3_取列整型64(语句, 列索引_1开始)
	__int64 sqlite3_column_int64(sqlite3_stmt*, int iCol);
	
	//@别名 记录集3_取列文本(语句, 列索引_1开始)
	const char *sqlite3_column_text(sqlite3_stmt*, int iCol);

	//@别名 记录集3_取列文本16(语句, 列索引_1开始)
	const wchar_t *sqlite3_column_text16(sqlite3_stmt*, int iCol);

	//@别名 记录集3_取列字节(语句, 列索引_1开始)
	int sqlite3_column_bytes(sqlite3_stmt*, int iCol);

	//@别名 记录集3_取列双字节(语句, 列索引_1开始)
	int sqlite3_column_bytes16(sqlite3_stmt*, int iCol);

	//@别名 记录集3_取列类型(语句, 列索引_1开始)
	int sqlite3_column_type(sqlite3_stmt*, int iCol);

	//@别名 记录集3_取列名称(语句, 列索引_1开始)
	const char *sqlite3_column_name(sqlite3_stmt*, int N);

	//@别名 记录集3_取列名称16(语句, 列索引_1开始)
	const wchar_t *sqlite3_column_name16(sqlite3_stmt*, int N);
	
	//@别名 记录集3_取字节集数据(语句, 列索引_1开始)
	const void *sqlite3_column_blob(sqlite3_stmt*, int iCol);
	//@别名 记录集3_取指定列原始名(语句, 列索引_1开始)
	const char *sqlite3_column_origin_name(sqlite3_stmt*,int);
	//@别名 记录集3_取指定列所处库名(语句, 列索引_1开始)
	const char *sqlite3_column_database_name(sqlite3_stmt*,int);
	//@别名 记录集3_取指定列所处表名(语句, 列索引_1开始)
	const char *sqlite3_column_table_name(sqlite3_stmt*,int);
	//@别名 记录集3_取指定列类型名称(语句, 列索引_1开始)
	const char *sqlite3_column_decltype(sqlite3_stmt*,int);
	//@别名 记录集3_置双精度浮点型(语句, 索引_1开始, 值)
	int sqlite3_bind_double(sqlite3_stmt*, int, double);

	//@别名 记录集3_置整型(语句, 索引_1开始, 值)
	int sqlite3_bind_int(sqlite3_stmt*, int, int);

	//@别名 记录集3_置长整型(语句, 索引_1开始, 值)
	int sqlite3_bind_int64(sqlite3_stmt*, int, __int64);

	//@别名 记录集3_置空(语句, 索引_1开始)
	int sqlite3_bind_null(sqlite3_stmt*, int);

	//@别名 记录集3_置文本(语句, 索引_1开始, 字符串, 字符串长度, 回调函数)
	int sqlite3_bind_text(sqlite3_stmt*, int, const char*, int, void(*)(void*));

	//@别名 记录集3_置文本16(语句, 索引_1开始, 字符串, 字符串长度, 回调函数)
	int sqlite3_bind_text16(sqlite3_stmt*, int, const wchar_t*, int, void(*)(void*));

	//@别名 记录集3_置文本64(语句, 索引_1开始, 字符串, 字符串长度, 回调函数)
	int sqlite3_bind_text64(sqlite3_stmt*, int, const char*, unsigned __int64, void(*)(void*), unsigned char encoding);
	//@别名 记录集3_置字节集(语句, 索引_1开始, 字节指针, 字符串长度)
	int sqlite3_bind_blob(sqlite3_stmt*, int, const void*, int n, void(*)(void*));
//@分组}

//@分组{ SQLite3数据库
	
	//@返回 成功返回SQLITE_OK,否则返回错误码
	//@别名 数据库3_打开A(文件名, 返回SQLite数据库句柄)
	int sqlite3_open(const char *filename, sqlite3 **ppDb);

	//@返回 成功返回SQLITE_OK,否则返回错误码
	//@别名  数据库3_打开16(文件名, 返回SQLite数据库句柄)
	int sqlite3_open16(const void *filename, sqlite3 **ppDb);

	//@参数  数据库连接句柄
	//@返回  如果sqlite3对象被成功销毁并且所有关联的资源被释放，SQLITE_OK。
	//@备注  关闭数据库连接
	//@别名  数据库3_关闭()
	int sqlite3_close(sqlite3*);

	//@参数 数据库连接句柄
	//@参数 一个或多个UTF-8编码，分号分隔的SQL语句。当运行sqlite3_exec时，应用程序不得修改传递给此参数的SQL语句文本。
	//@参数 指向回调函数的指针。如果不为NULL，则从评估的SQL语句中输出的每个结果行调用回调函数。如果为NULL，则不会调用回调，并忽略结果行。
	//@参数 一个可选值，被转发到每个回调调用的第一个参数
	//@参数 接收错误信息, 需要释放内存
	//@返回  如果成功返回SQLITE_OK，否则返回错误代码
	//@备注 执行指定的一条或多条SQL语句,多个SQL语句之间请以半角分号";"隔开
	//@别名 数据库3_执行SQL()
	int sqlite3_exec(sqlite3*, const char *sql, int(*callback)(void*, int, char**, char**), void *userData, char **errmsg);

	//@备注 不需要释放返回值
	//@别名 数据库3_取错误信息()
	const char *sqlite3_errmsg(sqlite3*);

	//@备注 不需要释放返回值
	//@别名  数据库3_取错误信息16()
	const wchar_t *sqlite3_errmsg16(sqlite3*);

	//@别名 数据库3_内存释放()
	void sqlite3_free(void*);
	//@别名 数据库3_取库版本号()
	int sqlite3_libversion_number(void);
	//@别名 数据库3_取库版本名称()
	const char *sqlite3_libversion(void);
	//@别名 数据库3_取库来源信息()
	const char *sqlite3_sourceid(void);
	//@别名 数据库3_是否线程安全()
	int sqlite3_threadsafe(void);
	//@别名 数据库3_置线程模式()
	int sqlite3_config(int);
	//@别名 数据库3_释放资源()
	int sqlite3_shutdown(void);
	//@别名 数据库3_检查语句是否完整()
	int sqlite3_complete(const char *sql);
	//@别名 数据库3_取已使用内存()
	vint sqlite3_memory_used(void);
	//@别名 数据库3_取指定错误描述()
	const char *sqlite3_errstr(int);

	
	//@返回 成功返回SQLITE_OK,否则返回错误码
	//@备注 初始化SQLite,分配一些必要的资源,数据结构等.
	//注意:本命令全局仅需执行一次,且在执行"打开"时会自动初始化.
	//@别名  数据库3_初始化()
	int sqlite3_initialize(void);


	//@参数 数据库连接句柄。必须是从sqlite3_open，sqlite3_open16或sqlite3_open_v2获取的NULL指针或sqlite3对象指针，而不是先前关闭。使用NULL指针参数调用sqlite3_close是无害的操作。
	//@返回 SQLITE_OK成功，失败时出现非零错误代码。
	//@备注 此函数返回由第一个参数指定的数据库连接上最近完成的SQL语句更改或插入或删除的数据库行数。
	//@别名 数据库3_取修改行数()
	int sqlite3_changes(sqlite3 *);

	//@参数 参数  数据库连接句柄
	//@参数 回调函数的地址。如果忙回调为NULL，则在遇到锁时立即返回SQLITE_BUSY或SQLITE_IOERR_BLOCKED。如果忙回调不为NULL，则可以使用两个参数调用回调。默认的busy回调为NULL。
	//@参数 一个可选值，被转发到每个回调调用的第一个参数。
	//@返回  SQLITE_OK成功，失败时出现非零错误代码。
	//@备注 此函数设置一个回调函数，只要尝试打开另一个线程或进程已锁定的数据库表时，该函数将被调用。
	//@别名  数据库3_注册繁忙回调(数据库连接句柄, 回调函数的地址, 自定义数据)
	int sqlite3_busy_handler(sqlite3*, int(*)(void*, int), void*);

	//@参数  数据库连接句柄
	//@参数  睡眠的毫秒数
	//@返回  SQLITE_OK成功，失败时出现非零错误代码。
	//@备注 此函数设置一个忙时处理程序，在处理表被锁定时睡眠一段指定的时间。处理程序将休眠多次，直到至少“ms”毫秒的睡眠已累积。在至少“ms”毫秒的睡眠后，处理程序返回0，这将导致sqlite3_step返回SQLITE_BUSY或SQLITE_IOERR_BLOCKED。
	//@别名 数据库3_置繁忙等待超时()
	int sqlite3_busy_timeout(sqlite3*, int ms);


	//@参数 数据库连接句柄。必须是从sqlite3_open，sqlite3_open16或sqlite3_open_v2获取的NULL指针或sqlite3对象指针，而不是先前关闭。使用NULL指针参数调用sqlite3_close是无害的操作。
	//@参数 配置动词 - 表示正在配置数据库连接的哪个方面的整数代码。后续参数因配置动词而异。
	//@返回 当且仅当该呼叫被认为是成功时，才会呼叫sqlite3_db_config返回SQLITE_OK
	//@备注 用于对数据库连接进行配置更改。该界面类似于sqlite3_config，只是更改适用于单个数据库连接（在第一个参数中指定）
	//@别名 数据库3_配置()
	int sqlite3_db_config(__in sqlite3*, __in int op, ...);

	//@参数 数据库连接句柄
	//@参数
	//@返回
	//@备注 此函数返回的文件名是VFS的xFullPathname方法的输出。换句话说，即使最初用于打开数据库的文件名是URI或相对路径名，文件名也将是绝对路径名
	//@别名 数据库3_取文件名()
	const char *sqlite3_db_filename(sqlite3 *db, const char *zDbName);


	//@参数 数据库连接句柄
	//@参数  数据库名称
	//@返回  如果指定的连接的指定数据库是只读的，则返回1，如果读/写则返回0，如果 不是指定连接上的数据库的名称，则返回-1。
	//@备注 如果指定的连接的指定数据库是只读的，则sqlite3_db_readonly函数返回1，如果读/写则为0，如果不是指定连接上的数据库的名称，则返回-1。
	//@别名 数据库3_是否只读()
	int sqlite3_db_readonly(sqlite3 *db, const char *zDbName);

	//@参数 据库连接句柄
	//@返回 字节数释放
	//@备注 尝试从指定的数据库连接释放尽可能多的堆内存。与sqlite3_release_memory不同，即使省略了SQLITE_ENABLE_MEMORY_MANAGEMENT编译时选项，此函数也会生效
	//@别名 数据库3_释放内存()
	int sqlite3_db_release_memory(sqlite3*);


	//@参数  要查询的数据库连接对象
	//@参数  一组整数常数，取自SQLITE_DBSTATUS选项集，用于确定要查询的参数。
	//SQLITE_DBSTATUS_LOOKASIDE_USED      = 0
	//SQLITE_DBSTATUS_CACHE_USED          = 1
	//SQLITE_DBSTATUS_SCHEMA_USED         = 2
	//SQLITE_DBSTATUS_STMT_USED           = 3
	//SQLITE_DBSTATUS_LOOKASIDE_HIT       = 4
	//SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE = 5
	//SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL = 6
	//SQLITE_DBSTATUS_CACHE_HIT           = 7
	//SQLITE_DBSTATUS_CACHE_MISS          = 8
	//SQLITE_DBSTATUS_CACHE_WRITE         = 9
	//@参数  请求参数的当前值
	//@参数  最高瞬时值
	//@参数  TRUE或FALSE。如果为真，那么最高瞬时值将被复位回当前值
	//@返回 SQLITE_OK成功，失败时出现非零错误代码
	//@备注  检索有关单个数据库连接的运行时状态信息
	//@别名  数据库3_取状态()
	int sqlite3_db_status(__in sqlite3*, __in int op, __out int *pCur, __out int *pHiwtr, __out int resetFlg);

	//@参数 数据库连接句柄
	//@返回 错误代码
	//@备注 返回与数据库连接相关联的最近失败的sqlite3_* API调用的数字结果代码。如果先前的API调用失败，但最近的API调用成功，则sqlite3_errcode的返回值未定义。
	//@别名 数据库3_取错误码()
	int sqlite3_errcode(sqlite3 *db);

	//@参数 数据库连接句柄
	//@返回 扩展错误代码
	//@备注 返回与数据库连接相关联的最近失败的sqlite3_* API调用的数字扩展结果代码。如果先前的API调用失败，但最近的API调用成功，则sqlite3_extended_errcode的返回值未定义。
	//@别名 数据库3_取错误码扩展()
	int sqlite3_extended_errcode(sqlite3 *db);

	//@参数 数据库连接句柄
	//@参数 TRUE或FALSE
	//@返回 SQLITE_OK
	//@备注 启用或禁用SQLite的扩展结果代码功能。默认情况下，扩展结果代码将被禁用以用于历史兼容性
	//@别名 数据库3_启用扩展结果代码()
	int sqlite3_extended_result_codes(sqlite3*, int onoff);

	//@参数 指向sqlite3_get_table函数返回的结果表的指针
	//@备注 释放sqlite3_get_table函数返回的结果表
	//@别名 数据库3_释放表()
	void sqlite3_free_table(char **result);

	//@参数 数据库连接句柄
	//@返回 如果给定的数据库连接处于或不处于自动提交模式，则分别返回非零或零
	//@备注 如果给定的数据库连接处于或不处于自动提交模式，则分别返回非零或零。默认情况下，自动提交模式是打开的。自动提交模式被BEGIN语句禁用。自动提交模式由COMMIT或ROLLBACK重新启用
	//@别名 数据库3_是否自动提交模式()
	int sqlite3_get_autocommit(sqlite3*);

	//@参数 数据库连接句柄
	//@参数 零终止的UTF-8字符串中的一个或多个分号分隔的SQL语句
	//@参数 接收指向结果表的指针的指针变量
	//@参数 指向一个LONG变量的指针，该变量接收结果集中的行数
	//@参数 指向一个LONG变量的指针，该变量接收结果集中的列数
	//@参数 如果不为NULL，任何错误消息都将写入从sqlite3_malloc获取并传回的内存中。为了避免内存泄漏，应用程序应该在不再需要错误消息字符串后调用sqlite3_free返回的错误消息字符串。如果此参数不为NULL并且没有发生错误，则sqlite3_get_table在返回前将该指针设置为NUL
	//@返回 如果成功返回SQLITE_OK，否则返回错误代码
	//@备注 这是一个旧接口，保留该接口是为了向后兼容。不建议使用此接口
	//@别名 数据库3_取表()
	int sqlite3_get_table(sqlite3 *db, const char *zSql, char ***pazResult, int *pnRow, int *pnColumn, char **pzErrmsg);

	//@参数 数据库连接句柄
	//@备注 此函数会导致任何挂起的数据库操作中止并尽早返回。响应于用户操作（例如按“取消”）或Ctrl-C，通常会调用此函数，用户希望长时间查询操作立即停止
	//@别名 数据库3_打断()
	void sqlite3_interrupt(sqlite3*);

	//@参数  数据库连接句柄
	//@返回
	//@备注 将第一个参数中数据库连接中最近成功插入的INSERT的rowid返回到数据库中
	//@别名 数据库3_取最后插入行号()
	__int64 sqlite3_last_insert_rowid(sqlite3*);

	//@参数 要限制其设置或查询的数据库连接
	//@参数 限制类别中定义一类要限制大小的构造之一
	//@参数 该结构的新限制,如果新限制为负数，则限制保持不变
	//@返回 上限值的限制
	//@备注 该函数允许通过连接基础在连接上限制各种构造的大小
	//@别名 数据库3_置运行时限制()
	int sqlite3_limit(sqlite3*, int id, int newVal);

	//@参数 数据库连接句柄
	//@参数 语句句柄
	//@返回 指向下一条语句的指针
	//@备注 该接口返回指向与数据库连接pDb关联的pStmt之后的下一个准备好的语句的指针。如果pStmt为NULL，则此接口返回指向与数据库连接pDb关联的第一个准备好的语句的指针。如果没有准备好的语句满足此例程的条件，则返回NULL。
	//该数据库连接到一个呼叫指针d sqlite3_next_stmt（d，S）必须是指开放式数据库连接，特别是不能是空指针
	//@别名 数据库3_下一个语句()
	sqlite3_stmt *sqlite3_next_stmt(sqlite3 *pDb, sqlite3_stmt *pStmt);

	//@参数 [in]连接句柄
	//@参数 [in]指向回调函数的指针
	//@参数 [in]一个可选值，它被转发到每个回调调用的第一个参数。
	//@返回 先前注册的跟踪回调的pData参数
	//@备注 注册了可用于跟踪和分析SQL语句执行的回调函数
	//@别名 数据库3_注册跟踪分析回调函数()
	void *sqlite3_profile(sqlite3*, void(*xProfile)(void*, const char*, unsigned __int64), void*);

	//@参数 [in]数据库连接句柄
	//@参数 [in]在回调X的连续调用之间评估的虚拟机指令数
	//@参数 [in]指向回调函数的指针
	//@参数 [in]作为唯一参数传递给回调函数的数据。
	//@备注 sqlite3_progress_handler（D，N，X，P）功能导致在长时间运行的数据库连接D sqlite3_exec，sqlite3_step和sqlite3_get_table期间定期调用回调函数X.此接口的一个示例使用是在大型查询期间保持GUI更新。
	//@别名 数据库3_注册查询进度回调()
	void sqlite3_progress_handler(sqlite3*, int, int(*)(void*), void*);

	//@参数 [in]数据库连接句柄
	//@参数 [in]指向回调函数的指针
	//@参数 [in]作为唯一参数传递给回调函数的数据
	//@返回 如果成功返回SQLITE_OK，否则返回错误代码
	//@备注 注册具有特定数据库连接的授权器回调
	//@别名  数据库3_注册授权回调()
	int sqlite3_set_authorizer(sqlite3*, int(*xAuth)(void*, int, const char*, const char*, const char*, const char*), void *pUserData);

	//@参数 [in]数据库连接句柄
	//@参数 [in]数据库的名称
	//@参数 [in]所需列的表名称。不能为空
	//@参数 [in]所需列的列名称。不能为空。
	//@参数 [out]指向接收指向声明类型的指针的变量的指针。可以为NULL
	//@参数 [out]指向接收指向排序规则序列名称的指针的变量的指针。可以为NULL。
	//@参数 [out]指向一个LONG变量的指针，如果NOT NULL约束存在则接收到TRUE。可以为NULL。
	//@参数 [out]如果列是主键的一部分，则指向一个LONG变量的指针，该变量接收到TRUE。可以为NULL。
	//@参数 [out]指向一个LONG变量的指针，如果列是自动递增的，则该变量接收到TRUE。可以为NULL。
	//@返回 如果成功返回SQLITE_OK，否则返回错误代码
	//@备注 此函数返回使用作为第一个函数参数传递的数据库连接句柄可访问的特定数据库表的特定列的元数据。
	//@别名 数据库3_取表列元数据()
	int sqlite3_table_column_metadata(sqlite3 *db, const char *zDbName, const char *zTableName, const char *zColumnName, char const **pzDataType, char const **pzCollSeq, int *pNotNull, int *pPrimaryKey, int *pAutoinc);

	//@参数 [in]数据库连接句柄
	//@返回 修改总行数
	//@备注 此函数返回自数据库连接打开以来由INSERT，UPDATE或DELETE语句引起的行更改数。
	//@别名 数据库3_取影响行数()
	int sqlite3_total_changes(sqlite3*);

	//@参数 [in]连接句柄
	//@参数 [in]指向回调函数的指针
	//@参数 [in]一个可选值，它被转发到每个回调调用的第一个参数。
	//@返回 先前注册的跟踪回调的pData参数
	//@备注 注册一个可用于跟踪执行SQL语句的回调函数。
	//@别名 数据库3_注册跟踪回调()
	void *sqlite3_trace(sqlite3*, void(*xTrace)(void*, const char*), void*);

	//@参数 [in]数据库连接句柄
	//@参数 [in]指向回调函数的指针
	//@参数 [in]将第二个参数传递给回调函数的数据
	//@返回 除非检测到死锁，sqlite3_unlock_notify总是返回SQLITE_OK
	//@备注 当以共享缓存模式运行时，如果无法获取共享缓存中的所需锁或共享缓存中的单独表，则数据库操作可能会失败并发生SQLITE_LOCKED错误。该API可以用于注册当连接当前持有所需的锁放弃它时SQLite将调用的回调。仅当使用定义了SQLITE_ENABLE_UNLOCK_NOTIFY C预处理器符号编译库时，此API才可用。
	//@别名 数据库3_注册解锁回调()
	int sqlite3_unlock_notify(sqlite3 *pBlocked, void(*xNotify)(void **apArg, int nArg), void *pNotifyArg);


	//@分组}

//@分组{  SQLite执行结果
//@别名 SQLite执行结果_成功
#define SQLITE_OK           0   /* Successful result */
/* beginning-of-error-codes */
//@别名 SQLite执行结果_错误
#define SQLITE_ERROR        1   /* Generic error */
//@别名 SQLite执行结果_内部错误
#define SQLITE_INTERNAL     2   /* Internal logic error in SQLite */
//@别名 SQLite执行结果_拒绝访问
#define SQLITE_PERM         3   /* Access permission denied */
//@别名 SQLite执行结果_回调中止
#define SQLITE_ABORT        4   /* Callback routine requested an abort */
//@别名 SQLite执行结果_库被锁定
#define SQLITE_BUSY         5   /* The database file is locked */
//@别名 SQLite执行结果_表被锁定
#define SQLITE_LOCKED       6   /* A table in the database is locked */
//@别名 SQLite执行结果_无内存
#define SQLITE_NOMEM        7   /* A malloc() failed */
//@别名 SQLite执行结果_只读错误
#define SQLITE_READONLY     8   /* Attempt to write a readonly database */
//@别名 SQLite执行结果_中止操作
#define SQLITE_INTERRUPT    9   /* Operation terminated by sqlite3_interrupt()*/
//@别名 SQLite执行结果_IO错误
#define SQLITE_IOERR       10   /* Some kind of disk I/O error occurred */
//@别名 SQLite执行结果_映像不正确
#define SQLITE_CORRUPT     11   /* The database disk image is malformed */
//@别名 SQLite执行结果_未知操作码
#define SQLITE_NOTFOUND    12   /* Unknown opcode in sqlite3_file_control() */
//@别名 SQLite执行结果_数据库已满
#define SQLITE_FULL        13   /* Insertion failed because database is full */
//@别名 SQLite执行结果_无法打开
#define SQLITE_CANTOPEN    14   /* Unable to open the database file */
//@别名 SQLite执行结果_锁定协议错误
#define SQLITE_PROTOCOL    15   /* Database lock protocol error */
//@别名 SQLite执行结果_仅供内部使用
#define SQLITE_EMPTY       16   /* Internal use only */
//@别名 SQLite执行结果_结构已更改
#define SQLITE_SCHEMA      17   /* The database schema changed */
//@别名 SQLite执行结果_数据量超限
#define SQLITE_TOOBIG      18   /* String or BLOB exceeds size limit */
//@别名 SQLite执行结果_违法约束
#define SQLITE_CONSTRAINT  19   /* Abort due to constraint violation */
//@别名 SQLite执行结果_类型不匹配
#define SQLITE_MISMATCH    20   /* Data type mismatch */
//@别名 SQLite执行结果_使用错误
#define SQLITE_MISUSE      21   /* Library used incorrectly */
//@别名 SQLite执行结果_主机不支持
#define SQLITE_NOLFS       22   /* Uses OS features not supported on host */
//@别名 SQLite执行结果_授权错误
#define SQLITE_AUTH        23   /* Authorization denied */
//@别名 SQLite执行结果_不使用
#define SQLITE_FORMAT      24   /* Not used */
//@别名 SQLite执行结果_超出范围
#define SQLITE_RANGE       25   /* 2nd parameter to sqlite3_bind out of range */
//@别名 SQLite执行结果_非数据库文件
#define SQLITE_NOTADB      26   /* File opened that is not a database file */
//@别名 SQLite执行结果_日志通知
#define SQLITE_NOTICE      27   /* Notifications from sqlite3_log() */
//@别名 SQLite执行结果_日志警告
#define SQLITE_WARNING     28   /* Warnings from sqlite3_log() */
//@别名 SQLite执行结果_下一行就绪
#define SQLITE_ROW         100  /* sqlite3_step() has another row ready */
//@别名 SQLite执行结果_已提交完毕
#define SQLITE_DONE        101  /* sqlite3_step() has finished executing */
/* end-of-error-codes */
//@分组}
//@分组{  SQLite打开方式
#define SQLITE_OPEN_DEFAULT  -1 //@别名 SQLite打开方式_默认
//@别名 SQLite打开方式_只读打开
#define SQLITE_OPEN_READONLY         0x00000001  /* Ok for sqlite3_open_v2() */
//@别名 SQLite打开方式_读写打开
#define SQLITE_OPEN_READWRITE        0x00000002  /* Ok for sqlite3_open_v2() */
//@别名 SQLite打开方式_新建打开
#define SQLITE_OPEN_CREATE           0x00000004  /* Ok for sqlite3_open_v2() */
//@别名 SQLite打开方式_资源标识符路径
#define SQLITE_OPEN_URI              0x00000040  /* Ok for sqlite3_open_v2() */
//@别名 SQLite打开方式_驻留内存
#define SQLITE_OPEN_MEMORY           0x00000080  /* Ok for sqlite3_open_v2() */
//@别名 SQLite打开方式_多线程模式
#define SQLITE_OPEN_NOMUTEX          0x00008000  /* Ok for sqlite3_open_v2() */
//@别名 SQLite打开方式_串行模式
#define SQLITE_OPEN_FULLMUTEX        0x00010000  /* Ok for sqlite3_open_v2() */
//@别名 SQLite打开方式_共享缓存模式
#define SQLITE_OPEN_SHAREDCACHE      0x00020000  /* Ok for sqlite3_open_v2() */
//@别名 SQLite打开方式_私有缓存模式
#define SQLITE_OPEN_PRIVATECACHE     0x00040000  /* Ok for sqlite3_open_v2() */
//@别名 SQLite打开方式_不允许符号连接
#define SQLITE_OPEN_NOFOLLOW         0x01000000  /* Ok for sqlite3_open_v2() */
//@分组}
//@隐藏{
//#ifdef __cplusplus
}
//#endif
//@隐藏}

#endif  //XC_SQLITE3_H