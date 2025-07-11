#pragma once

#define WIN32_LEAN_AND_MEAN    // 从 Windows 头文件中排除极少使用的内容

#include <stdio.h>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include <time.h>
using namespace std;

#ifdef  XC_MODULE
#include "module_base.h"
#endif

#include "include\mysql.h"
//#pragma comment(lib,"lib/libmysql.lib")  
//@lib "x64\libmysql.lib"
//@复制文件 @当前模块路径 "x64\libmysql.dll"

#ifdef _WIN64

//@lib "x64\libmysql.lib"
//@复制文件 @当前模块路径 "x64\libmysql.dll"
#else

//@lib "win32\libmysql.lib"
//@复制文件 @当前模块路径 "win32\libmysql.dll"
#endif


//@模块名称  数据库mysql
//@版本  1.0  
//@日期  2020-11-20
//@作者  XCGUI  
//@模块备注 数据库mysql, mysql版本 5.7.16
//@依赖  module_base.h
//@QQ    154460336

/*@声明


#define packet_error (~(unsigned long) 0)
// For backward compatibility  
@分组{ Mysql字段类型

	#define CLIENT_MULTI_QUERIES    CLIENT_MULTI_STATEMENTS    
	@别名 Mysql字段类型_未压缩浮点数型
	#define FIELD_TYPE_DECIMAL     MYSQL_TYPE_DECIMAL
	#define FIELD_TYPE_NEWDECIMAL  MYSQL_TYPE_NEWDECIMAL
	@别名 Mysql字段类型_短整型
	#define FIELD_TYPE_TINY        MYSQL_TYPE_TINY
	@别名 Mysql字段类型_短整数型
	#define FIELD_TYPE_SHORT       MYSQL_TYPE_SHORT
	@别名 Mysql字段类型_长整型
	#define FIELD_TYPE_LONG        MYSQL_TYPE_LONG
	@别名 Mysql字段类型_小数型
	#define FIELD_TYPE_FLOAT       MYSQL_TYPE_FLOAT
	@别名 Mysql字段类型_双精度小数型
	#define FIELD_TYPE_DOUBLE      MYSQL_TYPE_DOUBLE
	@别名 Mysql字段类型_空值
	#define FIELD_TYPE_NULL        MYSQL_TYPE_NULL
	@别名 Mysql字段类型_时间戳型
	#define FIELD_TYPE_TIMESTAMP   MYSQL_TYPE_TIMESTAMP
	@别名 Mysql字段类型_长整数型
	#define FIELD_TYPE_LONGLONG    MYSQL_TYPE_LONGLONG
	@别名 Mysql字段类型_整数型_24位
	#define FIELD_TYPE_INT24       MYSQL_TYPE_INT24
	@别名 Mysql字段类型_日期型
	#define FIELD_TYPE_DATE        MYSQL_TYPE_DATE
	@别名 Mysql字段类型_时间型
	#define FIELD_TYPE_TIME        MYSQL_TYPE_TIME
	@别名 Mysql字段类型_日期时间型
	#define FIELD_TYPE_DATETIME    MYSQL_TYPE_DATETIME
	@别名 Mysql字段类型_年份型
	#define FIELD_TYPE_YEAR        MYSQL_TYPE_YEAR
	@别名 Mysql字段类型_新日期型
	#define FIELD_TYPE_NEWDATE     MYSQL_TYPE_NEWDATE
	@别名 Mysql字段类型_枚举型
	#define FIELD_TYPE_ENUM        MYSQL_TYPE_ENUM
	@别名 Mysql字段类型_集合型
	#define FIELD_TYPE_SET         MYSQL_TYPE_SET
	@别名 Mysql字段类型_字节型
	#define FIELD_TYPE_TINY_BLOB   MYSQL_TYPE_TINY_BLOB
	@别名 Mysql字段类型_短字节型
	#define FIELD_TYPE_MEDIUM_BLOB MYSQL_TYPE_MEDIUM_BLOB
	@别名 Mysql字段类型_长字节型
	#define FIELD_TYPE_LONG_BLOB   MYSQL_TYPE_LONG_BLOB

	#define FIELD_TYPE_BLOB        MYSQL_TYPE_BLOB
	#define FIELD_TYPE_VAR_STRING  MYSQL_TYPE_VAR_STRING
	#define FIELD_TYPE_STRING      MYSQL_TYPE_STRING
	#define FIELD_TYPE_CHAR        MYSQL_TYPE_TINY
	#define FIELD_TYPE_INTERVAL    MYSQL_TYPE_ENUM
	#define FIELD_TYPE_GEOMETRY    MYSQL_TYPE_GEOMETRY
	#define FIELD_TYPE_BIT         MYSQL_TYPE_BIT
@分组}  //Mysql字段类型



struct MYSQL{};
typedef char my_bool;

typedef char **MYSQL_ROW;

typedef unsigned long u_long;

typedef struct st_mysql_res {
  my_ulonglong  row_count;
  MYSQL_FIELD	*fields;
  MYSQL_DATA	*data;
  MYSQL_ROWS	*data_cursor;
  unsigned long *lengths;		
  MYSQL		*handle;		
  const struct st_mysql_methods *methods;
  MYSQL_ROW	row;			
  MYSQL_ROW	current_row;		
  MEM_ROOT	field_alloc;
  unsigned int	field_count ;
  unsigned int current_field;
  my_bool	eof;			
  
  my_bool       unbuffered_fetch_cancelled;
  void *extension;
} MYSQL_RES;


@别名 Mysql字段信息
struct MYSQL_FIELD {
  @别名 名称
  @备注 字段的名称
  char *name;
  @别名 原始名称
  @备注 字段的原始名称（未经过别名处理）
  char *org_name;
  @别名 表名
  @备注 字段所属的表名
  char *table;
  @别名 原始表名
  @备注 字段所属的原始表名（未经过别名处理）
  char *org_table;
  @别名 库名
  @备注 字段所属的数据库名称
  char *db;
  @别名 目录名
  @备注 字段所属的目录名称（通常为数据库名称）
  char *catalog;
  @别名 默认值
  @备注 字段的默认值（如果存在）
  char *def;
  @别名 长度
  @备注 字段的长度（以字节为单位）
  unsigned long length;
  @别名 最大长度
  @备注 字段的最大长度（以字节为单位）
  unsigned long max_length;
  @别名 名称长度
  @备注 字段名称的长度（以字节为单位）
  unsigned int name_length;
  @别名 原始名称长度
  @备注 字段原始名称的长度（以字节为单位）
  unsigned int org_name_length;
  @别名 表名长度
  @备注 表名的长度（以字节为单位）
  unsigned int table_length;
  @别名 原始表名长度
  @备注 原始表名的长度（以字节为单位）
  unsigned int org_table_length;
  @别名 库名长度
  @备注 数据库名称的长度（以字节为单位）
  unsigned int db_length;
  @别名 目录长度
  @备注 目录名称的长度（以字节为单位）
  unsigned int catalog_length;
  @别名 默认长度
  @备注 默认值的长度（以字节为单位）
  unsigned int def_length;
  @别名 DIV标志位
  @备注 字段的标志位，用于表示字段的属性（如是否为主键、是否允许 NULL 等）
  unsigned int flags;
  @别名 小数位数
  @备注 字段的小数位数（适用于数值类型）
  unsigned int decimals;
  @别名 字符集索引
  @备注 字段的字符集编号
  unsigned int charsetnr;
  @别名 类型
  @备注 字段的数据类型（如整数、字符串、日期等）
  enum enum_field_types type;
  @别名 扩展内容
  @备注 扩展字段，用于未来扩展或自定义数据
  void *extension;
};


@分组{ 全局函数
MYSQL_PARAMETERS *WINAPI mysql_get_parameters(void);
int WINAPI mysql_server_init(int argc, char **argv, char **groups);
void WINAPI mysql_server_end(void);
my_bool WINAPI mysql_thread_init(void);
void WINAPI mysql_thread_end(void);

my_ulonglong WINAPI mysql_num_rows(MYSQL_RES *res);
unsigned int WINAPI mysql_num_fields(MYSQL_RES *res);
my_bool WINAPI mysql_eof(MYSQL_RES *res);
MYSQL_FIELD *WINAPI mysql_fetch_field_direct(MYSQL_RES *res, unsigned int fieldnr);
MYSQL_FIELD * WINAPI mysql_fetch_fields(MYSQL_RES *res);
MYSQL_ROW_OFFSET WINAPI mysql_row_tell(MYSQL_RES *res);
MYSQL_FIELD_OFFSET WINAPI mysql_field_tell(MYSQL_RES *res);

unsigned int WINAPI mysql_field_count(MYSQL *mysql);
my_ulonglong WINAPI mysql_affected_rows(MYSQL *mysql);
my_ulonglong WINAPI mysql_insert_id(MYSQL *mysql);
unsigned int WINAPI mysql_errno(MYSQL *mysql);
const char * WINAPI mysql_error(MYSQL *mysql);
const char *WINAPI mysql_sqlstate(MYSQL *mysql);
unsigned int WINAPI mysql_warning_count(MYSQL *mysql);
const char * WINAPI mysql_info(MYSQL *mysql);
unsigned long WINAPI mysql_thread_id(MYSQL *mysql);
const char * WINAPI mysql_character_set_name(MYSQL *mysql);
int          WINAPI mysql_set_character_set(MYSQL *mysql, const char *csname);

MYSQL *		WINAPI mysql_init(MYSQL *mysql);
my_bool		WINAPI mysql_ssl_set(MYSQL *mysql, const char *key, const char *cert, const char *ca, const char *capath, const char *cipher);
const char *    WINAPI mysql_get_ssl_cipher(MYSQL *mysql);
my_bool		WINAPI mysql_change_user(MYSQL *mysql, const char *user, const char *passwd, const char *db);
MYSQL *		WINAPI mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long clientflag);
int		WINAPI mysql_select_db(MYSQL *mysql, const char *db);
int		WINAPI mysql_query(MYSQL *mysql, const char *q);
int		WINAPI mysql_send_query(MYSQL *mysql, const char *q, unsigned long length);
int		WINAPI mysql_real_query(MYSQL *mysql, const char *q, unsigned long length);
MYSQL_RES *     WINAPI mysql_store_result(MYSQL *mysql);
MYSQL_RES *     WINAPI mysql_use_result(MYSQL *mysql);

void  WINAPI mysql_get_character_set_info(MYSQL *mysql, MY_CHARSET_INFO *charset);

int WINAPI mysql_session_track_get_first(MYSQL *mysql, enum enum_session_state_type type, const char **data, size_t *length);
int WINAPI mysql_session_track_get_next(MYSQL *mysql, enum enum_session_state_type type, const char **data, size_t *length);

//void mysql_set_local_infile_handler(MYSQL *mysql, int (*local_infile_init)(void **, const char *, void *),    int (*local_infile_read)(void *, char *, unsigned int),  void (*local_infile_end)(void *), int (*local_infile_error)(void *, char*, unsigned int), void *);

void mysql_set_local_infile_default(MYSQL *mysql);

int		WINAPI mysql_shutdown(MYSQL *mysql, enum mysql_enum_shutdown_level  shutdown_level);
int		WINAPI mysql_dump_debug_info(MYSQL *mysql);
int		WINAPI mysql_refresh(MYSQL *mysql, unsigned int refresh_options);
int		WINAPI mysql_kill(MYSQL *mysql,unsigned long pid);
int		WINAPI mysql_set_server_option(MYSQL *mysql, enum enum_mysql_set_option option);
int		WINAPI mysql_ping(MYSQL *mysql);
const char *	WINAPI mysql_stat(MYSQL *mysql);
const char *	WINAPI mysql_get_server_info(MYSQL *mysql);
const char *	WINAPI mysql_get_client_info(void);
unsigned long	WINAPI mysql_get_client_version(void);
const char *	WINAPI mysql_get_host_info(MYSQL *mysql);
unsigned long	WINAPI mysql_get_server_version(MYSQL *mysql);
unsigned int	WINAPI mysql_get_proto_info(MYSQL *mysql);
MYSQL_RES *	WINAPI mysql_list_dbs(MYSQL *mysql,const char *wild);
MYSQL_RES *	WINAPI mysql_list_tables(MYSQL *mysql,const char *wild);
MYSQL_RES *	WINAPI mysql_list_processes(MYSQL *mysql);
int		WINAPI mysql_options(MYSQL *mysql,enum mysql_option option,const void *arg);
int		WINAPI mysql_options4(MYSQL *mysql,enum mysql_option option, const void *arg1, const void *arg2);
int             WINAPI mysql_get_option(MYSQL *mysql, enum mysql_option option, const void *arg);
void		WINAPI mysql_free_result(MYSQL_RES *result);
void		WINAPI mysql_data_seek(MYSQL_RES *result, my_ulonglong offset);
MYSQL_ROW_OFFSET WINAPI mysql_row_seek(MYSQL_RES *result,	MYSQL_ROW_OFFSET offset);
MYSQL_FIELD_OFFSET WINAPI mysql_field_seek(MYSQL_RES *result, MYSQL_FIELD_OFFSET offset);
MYSQL_ROW	WINAPI mysql_fetch_row(MYSQL_RES *result);
unsigned long * WINAPI mysql_fetch_lengths(MYSQL_RES *result);
MYSQL_FIELD *	WINAPI mysql_fetch_field(MYSQL_RES *result);
MYSQL_RES *     WINAPI mysql_list_fields(MYSQL *mysql, const char *table, const char *wild);
unsigned long	WINAPI mysql_escape_string(char *to,const char *from, unsigned long from_length);
unsigned long	WINAPI mysql_hex_string(char *to,const char *from, unsigned long from_length);
unsigned long WINAPI mysql_real_escape_string(MYSQL *mysql, char *to,const char *from,unsigned long length);
unsigned long WINAPI mysql_real_escape_string_quote(MYSQL *mysql, char *to, const char *from, unsigned long length, char quote);
void          WINAPI mysql_debug(const char *debug);
void          WINAPI myodbc_remove_escape(MYSQL *mysql,char *name);
unsigned int  WINAPI mysql_thread_safe(void);
my_bool       WINAPI mysql_embedded(void);
my_bool       WINAPI mysql_read_query_result(MYSQL *mysql);
int           WINAPI mysql_reset_connection(MYSQL *mysql);

//-----------------------------
MYSQL_STMT * WINAPI mysql_stmt_init(MYSQL *mysql);
int WINAPI mysql_stmt_prepare(MYSQL_STMT *stmt, const char *query,unsigned long length);
int WINAPI mysql_stmt_execute(MYSQL_STMT *stmt);
int WINAPI mysql_stmt_fetch(MYSQL_STMT *stmt);
int WINAPI mysql_stmt_fetch_column(MYSQL_STMT *stmt, MYSQL_BIND *bind_arg, unsigned int column, unsigned long offset);
int WINAPI mysql_stmt_store_result(MYSQL_STMT *stmt);
unsigned long WINAPI mysql_stmt_param_count(MYSQL_STMT * stmt);
my_bool WINAPI mysql_stmt_attr_set(MYSQL_STMT *stmt, enum enum_stmt_attr_type attr_type, const void *attr);
my_bool WINAPI mysql_stmt_attr_get(MYSQL_STMT *stmt, enum enum_stmt_attr_type attr_type, void *attr);
my_bool WINAPI mysql_stmt_bind_param(MYSQL_STMT * stmt, MYSQL_BIND * bnd);
my_bool WINAPI mysql_stmt_bind_result(MYSQL_STMT * stmt, MYSQL_BIND * bnd);
my_bool WINAPI mysql_stmt_close(MYSQL_STMT * stmt);
my_bool WINAPI mysql_stmt_reset(MYSQL_STMT * stmt);
my_bool WINAPI mysql_stmt_free_result(MYSQL_STMT *stmt);
my_bool WINAPI mysql_stmt_send_long_data(MYSQL_STMT *stmt, unsigned int param_number, const char *data, unsigned long length);
MYSQL_RES *WINAPI mysql_stmt_result_metadata(MYSQL_STMT *stmt);
MYSQL_RES *WINAPI mysql_stmt_param_metadata(MYSQL_STMT *stmt);
unsigned int WINAPI mysql_stmt_errno(MYSQL_STMT * stmt);
const char *WINAPI mysql_stmt_error(MYSQL_STMT * stmt);
const char *WINAPI mysql_stmt_sqlstate(MYSQL_STMT * stmt);
MYSQL_ROW_OFFSET WINAPI mysql_stmt_row_seek(MYSQL_STMT *stmt, MYSQL_ROW_OFFSET offset);
MYSQL_ROW_OFFSET WINAPI mysql_stmt_row_tell(MYSQL_STMT *stmt);
void WINAPI mysql_stmt_data_seek(MYSQL_STMT *stmt, my_ulonglong offset);
my_ulonglong WINAPI mysql_stmt_num_rows(MYSQL_STMT *stmt);
my_ulonglong WINAPI mysql_stmt_affected_rows(MYSQL_STMT *stmt);
my_ulonglong WINAPI mysql_stmt_insert_id(MYSQL_STMT *stmt);
unsigned int WINAPI mysql_stmt_field_count(MYSQL_STMT *stmt);

my_bool WINAPI mysql_commit(MYSQL * mysql);
my_bool WINAPI mysql_rollback(MYSQL * mysql);
my_bool WINAPI mysql_autocommit(MYSQL * mysql, my_bool auto_mode);
my_bool WINAPI mysql_more_results(MYSQL *mysql);
int WINAPI mysql_next_result(MYSQL *mysql);
int WINAPI mysql_stmt_next_result(MYSQL_STMT *stmt);
void WINAPI mysql_close(MYSQL *sock);
//@分组}

*/


