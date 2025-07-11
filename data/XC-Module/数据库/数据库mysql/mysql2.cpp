#include "module_mysql2.h"

CMySql数据库类::CMySql数据库类()
{
	m_data = NULL;
}
CMySql数据库类::~CMySql数据库类()
{
	if (m_data!= NULL )
	{
		mysql_close(m_data);
		m_data= NULL ;
		resPtr= NULL ;
	}
}
BOOL CMySql数据库类::连接(CXText 地址, CXText 用户名, CXText 密码, CXText 数据库名, int 端口, CXText 套接字, int 配置位)
{
	if (m_data == NULL)
	{
		m_data = mysql_init(NULL);
	}
	if (m_data!= NULL )
	{
		if (mysql_real_connect(m_data, W2A(地址), W2A(用户名), W2A(密码), W2A(数据库名), 端口, W2A(套接字), 配置位)> 0 )
		{
			return TRUE ;
		}
	}
	return FALSE ;
}
CXText CMySql数据库类::取客户端版本名()
{
	CXTextA 版本号= mysql_get_client_info();
	return A2W(版本号);
		;
}
UINT64 CMySql数据库类::取客户端版本号()
{
	return mysql_get_client_version();
}
int CMySql数据库类::线程安全()
{
	return mysql_thread_safe();
}
void CMySql数据库类::置连接超时(int 超时)
{
	if (m_data!= NULL )
	{
		mysql_options(m_data, MYSQL_OPT_CONNECT_TIMEOUT, &超时);
	}
}
int CMySql数据库类::取连接超时()
{
	int 超时= - 1 ;
	if (m_data!= NULL )
	{
		mysql_get_option(m_data, MYSQL_OPT_CONNECT_TIMEOUT, &超时);
	}
	return 超时;
}
void CMySql数据库类::置读取超时(int 超时)
{
	if (m_data!= NULL )
	{
		mysql_options(m_data, MYSQL_OPT_READ_TIMEOUT, &超时);
	}
	return ;
}
int CMySql数据库类::取读取超时()
{
	int 超时= -1 ;
	if (m_data!= NULL )
	{
		mysql_get_option(m_data, MYSQL_OPT_READ_TIMEOUT, &超时);
	}
	return 超时;
}
void CMySql数据库类::置写入超时(int 超时)
{
	if (m_data!= NULL )
	{
		mysql_options(m_data, MYSQL_OPT_WRITE_TIMEOUT, &超时);
	}
}
int CMySql数据库类::取写入超时()
{
	int 超时= -1 ;
	if (m_data!= NULL )
	{
		mysql_get_option(m_data, MYSQL_OPT_WRITE_TIMEOUT, &超时);
	}
	return 超时;
}
int CMySql数据库类::置通报数据截断错误(BOOL 启用)
{
	if (m_data!= NULL )
	{
		return mysql_options(m_data, MYSQL_REPORT_DATA_TRUNCATION, &启用);
	}
	return - 1 ;
}
BOOL CMySql数据库类::取通报数据截断错误()
{
	BOOL 启用;
	if (m_data!= NULL )
	{
		mysql_get_option(m_data, MYSQL_REPORT_DATA_TRUNCATION, &启用);
	}
	return 启用;
}
void CMySql数据库类::置自动提交事务(BOOL 启用)
{
	if (m_data!= NULL )
	{
		mysql_autocommit(m_data, (char)启用);
	}
}
void CMySql数据库类::置自动重连(BOOL 启用)
{
	if (m_data!= NULL )
	{
		mysql_options(m_data, MYSQL_OPT_RECONNECT, &启用);
	}
}
BOOL CMySql数据库类::取自动重连()
{
	BOOL value= 0 ;
	if (m_data!= NULL )
	{
		mysql_get_option(m_data, MYSQL_OPT_RECONNECT, &value);
	}
	return value;
}
void CMySql数据库类::置连接后命令(CXText 命令内容)
{
	if (m_data!= NULL )
	{
		mysql_options(m_data, MYSQL_INIT_COMMAND, W2A(命令内容).get());
	}
}
void CMySql数据库类::置命名选项文件(CXText 文件)
{
	if (m_data!= NULL )
	{
		mysql_options(m_data, MYSQL_READ_DEFAULT_FILE, W2A(文件).get());
	}
}
void CMySql数据库类::置命名选项组(CXText 命名组)
{
	if (m_data!= NULL )
	{
		mysql_options(m_data, MYSQL_READ_DEFAULT_GROUP, W2A(命名组).get());
	}
}
void CMySql数据库类::置字符集定义文件(CXText 文件)
{
	if (m_data!= NULL )
	{
		mysql_options(m_data, MYSQL_SET_CHARSET_DIR, W2A(文件).get());
	}
}
void CMySql数据库类::置协议类型(int 类型)
{
	if (m_data!= NULL )
	{
		mysql_protocol_type type= MYSQL_PROTOCOL_DEFAULT;
		switch (类型)
		{
			case 1 :
			{
				type= MYSQL_PROTOCOL_TCP;
			}break;
			case 2 :
			{
				type= MYSQL_PROTOCOL_SOCKET;
			}break;
			case 3 :
			{
				type= MYSQL_PROTOCOL_PIPE;
			}break;
			case 4 :
			{
				type= MYSQL_PROTOCOL_MEMORY;
			}break;
			default :
			{
				type= MYSQL_PROTOCOL_DEFAULT;
			}
		}
		mysql_options(m_data, MYSQL_OPT_PROTOCOL, &type);
	}
}
void CMySql数据库类::置共享内存对象名称(CXText 名称)
{
	if (m_data!= NULL )
	{
		mysql_options(m_data, MYSQL_SHARED_MEMORY_BASE_NAME, W2A(名称).get());
	}
}
BOOL CMySql数据库类::多个查询结果()
{
	if (m_data!= NULL )
	{
		return (BOOL)mysql_more_results(m_data);
	}
	return FALSE ;
}
int CMySql数据库类::启用SSL(CXText 私钥文件, CXText 证书文件, CXText 授权文件, CXText 目录名称, CXText 允许密码列表)
{
	if (m_data!= NULL )
	{
		return mysql_ssl_set(m_data, W2A(私钥文件).get(), W2A(证书文件).get(), W2A(授权文件).get(), W2A(目录名称).get(), W2A(允许密码列表).get());
	}
	return - 1 ;
}
CXText CMySql数据库类::取SSL允许密码列表()
{
	if (m_data!= NULL )
	{
		const char* str= mysql_get_ssl_cipher(m_data);
		if (str!= NULL )
		{
			return A2W(str);
		}
	}
	return L"" ;
}
BOOL CMySql数据库类::修改用户(CXText 数据库名, CXText 用户名, CXText 密码)
{
	if (m_data!= NULL )
	{
		return ! (BOOL)mysql_change_user(m_data, W2A(用户名).get(), W2A(密码).get(), W2A(数据库名).get());
	}
	return FALSE ;
}
BOOL CMySql数据库类::选择库(CXText 数据库名)
{
	if (m_data!= NULL )
	{
		return ! (BOOL)mysql_select_db(m_data, W2A(数据库名).get());
	}
	return FALSE ;
}
BOOL CMySql数据库类::执行SQL语句(CXText 语句内容)
{
	if (m_data!= NULL )
	{
		return ! (BOOL)mysql_query(m_data, W2A(语句内容).get());
	}
	return FALSE ;
}
BOOL CMySql数据库类::执行SQL语句_二进制(CXBytes 语句内容)
{
	if (m_data!= NULL )
	{
		return ! (BOOL)mysql_real_query(m_data, (char*)语句内容.getTextPtrA(), (UINT64)(int)语句内容.size());
	}
	return FALSE ;
}
int CMySql数据库类::到下一个记录集()
{
	if (m_data!= NULL )
	{
		return mysql_next_result(m_data);
	}
	return - 1 ;
}
BOOL CMySql数据库类::取记录集(CMySql记录集类* 记录集)
{
	if (m_data!= NULL )
	{
		resPtr= mysql_store_result(m_data);
		if (resPtr!= 0 )
		{
			记录集->SetData(resPtr);
			return TRUE ;
		}
		else 
		{
			return FALSE ;
		}
	}
	return FALSE ;
}
BOOL CMySql数据库类::取临时记录集(CMySql记录集类* 记录集)
{
	if (m_data!= NULL )
	{
		resPtr= mysql_use_result(m_data);
		if (resPtr!= 0 )
		{
			记录集->SetData(resPtr);
			return TRUE ;
		}
		else 
		{
			return FALSE ;
		}
	}
	return FALSE ;
}
BOOL CMySql数据库类::取所有库(CMySql记录集类* 记录集, CXText 通配符)
{
	if (m_data!= NULL )
	{
		CXTextA 临时值= W2A(通配符);
		if (通配符.empty())
		{
			临时值= "";
		}
		resPtr= mysql_list_dbs(m_data, 临时值);
		if (resPtr!= 0 )
		{
			记录集->SetData(resPtr);
			return TRUE ;
		}
		else 
		{
			return FALSE ;
		}
	}
	return FALSE ;
}
BOOL CMySql数据库类::置当前字符集(CXText 字符集)
{
	if (m_data!= NULL )
	{
		if(0 == mysql_set_character_set(m_data, W2A(字符集)))
			return TRUE;
	}
	return FALSE ;
}
BOOL CMySql数据库类::写入调试日志()
{
	if (m_data!= NULL )
	{
		return mysql_dump_debug_info(m_data)== 0 ;
	}
	return FALSE ;
}
BOOL CMySql数据库类::刷新(int 配置位)
{
	if (m_data!= NULL )
	{
		return mysql_refresh(m_data, 配置位)== 0 ;
	}
	return FALSE ;
}
BOOL CMySql数据库类::关闭线程(int 线程ID)
{
	if (m_data!= NULL )
	{
		return mysql_kill(m_data, 线程ID)== 0 ;
	}
	return FALSE ;
}
BOOL CMySql数据库类::检测连接状态(int 线程ID)
{
	if (m_data!= NULL )
	{
		return mysql_ping(m_data);
	}
	return FALSE ;
}
BOOL CMySql数据库类::重置当前连接(int 线程ID)
{
	if (m_data!= NULL )
	{
		return mysql_reset_connection(m_data)== 0 ;
	}
	return FALSE ;
}
BOOL CMySql数据库类::开始提交事务()
{
	if (m_data!= NULL )
	{
		return ! (BOOL)mysql_commit(m_data);
	}
	return FALSE ;
}
BOOL CMySql数据库类::回滚事务()
{
	if (m_data!= NULL )
	{
		return ! (BOOL)mysql_rollback(m_data);
	}
	return FALSE ;
}
void CMySql数据库类::关闭()
{
	if (m_data!= NULL )
	{
		mysql_close(m_data);
		m_data= NULL ;
		resPtr= NULL ;
	}
}
CXTextA CMySql数据库类::取错误信息()
{
	if (m_data!= NULL )
	{
		return mysql_error(m_data);
	}
    return "";
}
void CMySql记录集类::SetData(MYSQL_RES* ptr)
{
	if (m_data!= NULL )
	{
		mysql_free_result(m_data);
		m_data= NULL ;
	}
	m_data= ptr;
}
CMySql记录集类::CMySql记录集类()
{
	m_data= NULL ;
}
CMySql记录集类::~CMySql记录集类()
{
	if (m_data!= NULL )
	{
		mysql_free_result(m_data);
		m_data= NULL ;
	}
}
void CMySql记录集类::关闭()
{
	if (m_data!= NULL )
	{
		mysql_free_result(m_data);
		m_data= NULL ;
	}
}
BOOL CMySql记录集类::是否有效()
{
	return m_data!= NULL ;
}
INT64 CMySql记录集类::取行数()
{
	if (m_data!= NULL )
	{
		return (INT64)mysql_num_rows(m_data);
	}
	return 0 ;
}
int CMySql记录集类::取列数()
{
	if (m_data!= NULL )
	{
		return mysql_num_fields(m_data);
	}
	return 0 ;
}
int CMySql记录集类::取列长度()
{
	if (m_data!= NULL )
	{
		u_long* len= mysql_fetch_lengths(m_data);
		return (int)* len;
	}
	return 0 ;
}
BOOL CMySql记录集类::取字段列表(CXVector<MYSQL_FIELD*>* 结果数据)
{
	if (m_data!= NULL )
	{
		MYSQL_FIELD* fields= mysql_fetch_fields(m_data);
		if ((fields!= NULL ))
		{
			for (UINT i= 0 ; i< mysql_num_fields(m_data); i++ )
			{
				结果数据->add((MYSQL_FIELD*)(& fields[i]));
			}
			return TRUE ;
		}
	}
	return FALSE ;
}
BOOL CMySql记录集类::取当前行数据(CXVector<CXBytes>* 结果数据)
{
	CXBytes 空字节集;
	if (m_data!= NULL )
	{
		char** current_row= m_data->current_row;
		u_long* lengths= mysql_fetch_lengths(m_data);
		if (current_row&& lengths)
		{
			for (int i= 0 ; i< ( int) mysql_num_fields(m_data); i++ )
			{
				if (current_row[i]== NULL )
				{
					空字节集.clear();
					结果数据->add(空字节集);
				}
				else 
				{
					空字节集.clear();
					空字节集.add(current_row[i], lengths[i]);
					结果数据->add(空字节集);
				}
			}
			return TRUE ;
		}
	}
	return FALSE ;
}
BOOL CMySql记录集类::取当前行文本数据(CXVector<CXText>* 结果数据)
{
	CXText 内容;
	if (m_data!= NULL )
	{
		char** current_row= m_data->current_row;
		if (current_row)
		{
			for (int i= 0 ; i< ( int) mysql_num_fields(m_data); i++ )
			{
				if (current_row[i]== NULL )
				{
					内容.resize(0 );
					结果数据->add(内容);
				}
				else 
				{
					内容.resize(0 );
					内容.append(A2W(current_row[i]));
					结果数据->add(内容);
				}
			}
			return TRUE ;
		}
	}
	return FALSE ;
}
BOOL CMySql记录集类::取当前行整数数据(CXVector<int>* 结果数据)
{
	int 内容;
	if (m_data!= NULL )
	{
		char** current_row= m_data->current_row;
		if (current_row)
		{
			for (int i= 0 ; i< ( int) mysql_num_fields(m_data); i++ )
			{
				if (current_row[i]== NULL )
				{
					结果数据->add(0 );
				}
				else 
				{
					内容= (atoi(current_row[i]));
					结果数据->add(内容);
				}
			}
			return TRUE ;
		}
	}
	return FALSE ;
}
BOOL CMySql记录集类::到下一行()
{
	if (m_data!= NULL )
	{
		return (mysql_fetch_row(m_data)!= NULL );
	}
	return FALSE ;
}
BOOL CMySql记录集类::到指定行(INT64 行)
{
	if (行> 取行数())
	{
		return FALSE ;
	}
	if (m_data!= NULL )
	{
		mysql_data_seek(m_data, 行);
		return TRUE ;
	}
	return FALSE ;
}
BOOL CMySql记录集类::读字节集数据(CXText 字段名, CXBytes* 返回数据)
{
	if (m_data!= NULL )
	{
		MYSQL_ROW current_row= m_data->current_row;
		MYSQL_FIELD* fields= m_data->fields;
		u_long* lengths= mysql_fetch_lengths(m_data);
		if (fields)
		{
			CXBytes memBuf;
			CXTextA 临时= W2A(字段名);
			char* fieldName= (char*)临时.get();
			int fields_count= mysql_num_fields(m_data);
			for (int i= 0 ; i< fields_count; i++ )
			{
				int 比较值= strcmp(fieldName, fields[i].name);
				if (比较值== 0 )
				{
					返回数据->add(current_row[i], lengths[i]);
					return TRUE ;
				}
			}
		}
	}
	return FALSE ;
}
BOOL CMySql记录集类::读索引字节集数据(UINT 字段索引, CXBytes* 返回数据)
{
	if (m_data&& 字段索引< mysql_num_fields(m_data))
	{
		char** current_row= m_data->current_row;
		u_long* lengths= mysql_fetch_lengths(m_data);
		if ((current_row&& lengths))
		{
			返回数据->add(current_row[字段索引], (int)lengths[字段索引]);
		}
		return TRUE ;
	}
	return FALSE ;
}
CXText CMySql记录集类::读文本数据(CXText 字段名)
{
	CXBytes 结果;
	读字节集数据(字段名, &结果);
	return (A2W(结果.getTextPtrA()));
}
CXText CMySql记录集类::读索引文本数据(int 字段索引)
{
	CXBytes 结果;
	读索引字节集数据(字段索引, &结果);
	return (A2W(结果.getTextPtrA()));
}
int CMySql记录集类::读整数数据(CXText 字段名)
{
	CXBytes 结果;
	读字节集数据(字段名, &结果);
	return 结果.getInt();
}
int CMySql记录集类::读索引整数数据(int 字段索引)
{
	CXBytes 结果;
	读索引字节集数据(字段索引, &结果);
	return 结果.getInt();
}
short CMySql记录集类::读短整数数据(CXText 字段名)
{
	CXBytes 结果;
	读字节集数据(字段名, &结果);
	return 结果.getShort();
}
short CMySql记录集类::读索引短整数数据(int 字段索引)
{
	CXBytes 结果;
	读索引字节集数据(字段索引, &结果);
	return 结果.getShort();
}
INT64 CMySql记录集类::读长整数数据(CXText 字段名)
{
	CXBytes 结果;
	读字节集数据(字段名, &结果);
	return 结果.getInt64();
}
INT64 CMySql记录集类::读索引长整数数据(int 字段索引)
{
	CXBytes 结果;
	读索引字节集数据(字段索引, &结果);
	return 结果.getInt64();
}
BOOL CMySql记录集类::读逻辑型数据(CXText 字段名)
{
	CXBytes 结果;
	读字节集数据(字段名, &结果);
	return (BOOL)结果.getUShort();
}
BOOL CMySql记录集类::读索引逻辑型数据(int 字段索引)
{
	CXBytes 结果;
	读索引字节集数据(字段索引, &结果);
	return (BOOL)结果.getUShort();
}
BYTE CMySql记录集类::读字节数据(CXText 字段名)
{
	CXBytes 结果;
	读字节集数据(字段名, &结果);
	return 结果.getByte();
}
BYTE CMySql记录集类::读索引字节数据(int 字段索引)
{
	CXBytes 结果;
	读索引字节集数据(字段索引, &结果);
	return 结果.getByte();
}
wchar_t CMySql记录集类::读字符数据(CXText 字段名)
{
	CXBytes 结果;
	读字节集数据(字段名, &结果);
	return 结果.getWchar();
}
wchar_t CMySql记录集类::读索引字符数据(int 字段索引)
{
	CXBytes 结果;
	读索引字节集数据(字段索引, &结果);
	return 结果.getWchar();
}
float CMySql记录集类::读浮点型数据(CXText 字段名)
{
	CXBytes 结果;
	读字节集数据(字段名, &结果);
	return 结果.getFloat();
}
float CMySql记录集类::读索引浮点型数据(int 字段索引)
{
	CXBytes 结果;
	读索引字节集数据(字段索引, &结果);
	return 结果.getFloat();
}
double CMySql记录集类::读双浮点型数据(CXText 字段名)
{
	CXBytes 结果;
	读字节集数据(字段名, &结果);
	return 结果.getDouble();
}
double CMySql记录集类::读索引双浮点型数据(int 字段索引)
{
	CXBytes 结果;
	读索引字节集数据(字段索引, &结果);
	return 结果.getDouble();
}
