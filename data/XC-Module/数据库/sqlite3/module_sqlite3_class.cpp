#include "module_sqlite3_class.h"


//----------------------------
CXSqlite3Err::CXSqlite3Err()
{
	m_errA = 0;
	m_err = 0;
}

CXSqlite3Err::~CXSqlite3Err()
{
	if (m_errA) sqlite3_free((void*)m_errA);
	if (m_err) sqlite3_free((void*)m_err);
}

void  CXSqlite3Err::close()
{
	if (m_errA) sqlite3_free((void*)m_errA);
	if (m_err) sqlite3_free((void*)m_err);
	m_errA = 0;
	m_err = 0;
}

//--------------------------------
CXSqlite3::CXSqlite3()
{
	m_db = 0;
}
CXSqlite3::~CXSqlite3()
{
	if (m_db)
	{
		sqlite3_close(m_db);
		m_db = NULL;
	}
}
int CXSqlite3::openA(const char *filename)
{
	return sqlite3_open(filename, &m_db);
}

int CXSqlite3::open(const wchar_t *filename)
{
	return sqlite3_open16(filename, &m_db);
}

int CXSqlite3::close()
{
	if (m_db)
	{
		int ret = sqlite3_close(m_db);
		m_db = 0;
		return ret;
	}
	return SQLITE_OK;
}

int CXSqlite3::exec(const char* sql, int(*callback)(void *, int, char **, char **), void *userData, CXSqlite3Err &err)
{
	err.close();
	return sqlite3_exec(m_db, sql, callback, userData, (char**)&err.m_errA);
}

const char* CXSqlite3::errMsgA()
{
	return sqlite3_errmsg(m_db);
}

const wchar_t* CXSqlite3::errMsg()
{
	return sqlite3_errmsg16(m_db);
}
int CXSqlite3::SetMaindbName(const char * pName)
{
	return sqlite3_db_config(m_db, 1000, pName, NULL);//SQLITE_DBCONFIG_MAINDBNAME
}

int CXSqlite3::EnableFkey(BOOL Enable){
	return sqlite3_db_config(m_db, 1002, (int)Enable, NULL);//SQLITE_DBCONFIG_ENABLE_FKEY
}
//-------------------------------------
CXStmt::CXStmt()
{
	m_stmt = NULL;
}

CXStmt::~CXStmt()
{
	if (m_stmt)
	{
		sqlite3_finalize(m_stmt);
		m_stmt = NULL;
	}
}

int CXStmt::prepareA(CXSqlite3 & db, const char * zSql, int nByte, const char ** pzTail)
{
	return sqlite3_prepare_v2(db.m_db, zSql, nByte, &m_stmt, pzTail);
}

int CXStmt::prepare(CXSqlite3 & db, const wchar_t* zSql, int nByte, const wchar_t** pzTail)
{
	return sqlite3_prepare16_v2(db.m_db, zSql, nByte, &m_stmt,(const void**)pzTail);
}

int CXStmt::step()
{
	return sqlite3_step(m_stmt);
}

int CXStmt::reset()
{
	return sqlite3_reset(m_stmt);
}

int CXStmt::close()
{
	if (m_stmt)
	{
		int ret= sqlite3_finalize(m_stmt);
		m_stmt = 0;
		return ret;
	}
	return SQLITE_OK;
}

double CXStmt::column_double(int nCol)
{
	return sqlite3_column_double(m_stmt, nCol);
}
int CXStmt::column_int(int nCol)
{
	return sqlite3_column_int(m_stmt, nCol);
}

__int64 CXStmt::column_int64(int nCol)
{
	return sqlite3_column_int64(m_stmt, nCol);
}

const char *CXStmt::column_textA(int nCol)
{
	return (const char*)sqlite3_column_text(m_stmt, nCol);
}

const wchar_t *CXStmt::column_text(int nCol)
{
	return (const wchar_t*)sqlite3_column_text16(m_stmt, nCol);
}

int CXStmt::column_bytes(int nCol)
{
	return sqlite3_column_type(m_stmt, nCol);
}

int CXStmt::column_bytes16(int nCol)
{
	return sqlite3_column_bytes16(m_stmt, nCol);
}

int CXStmt::column_type(int nCol)
{
	return sqlite3_column_type(m_stmt, nCol);
}

const char *CXStmt::column_nameA(int nCol)
{
	return sqlite3_column_name(m_stmt, nCol);
}

const wchar_t *CXStmt::column_name(int nCol)
{
	return (const wchar_t*)sqlite3_column_name16(m_stmt, nCol);
}

//---------------------------------
int CXStmt::bind_double(int nCol, double fValue)
{
	return sqlite3_bind_double(m_stmt, nCol, fValue);
}

int CXStmt::bind_int(int nCol, int nValue)
{
	return sqlite3_bind_int(m_stmt, nCol, nValue);
}

int CXStmt::bind_int64(int nCol, __int64 nValue)
{
	return sqlite3_bind_int64(m_stmt, nCol, nValue);
}

int CXStmt::bind_null(int nCol)
{
	return sqlite3_bind_null(m_stmt, nCol);
}

int CXStmt::bind_textA(int nCol, const char* text, int textLength, void(*f)(void *))
{
	return sqlite3_bind_text(m_stmt, nCol, text, textLength, f);
}

int CXStmt::bind_text(int nCol, const wchar_t* text, int textLength, void(*f)(void *))
{
	return sqlite3_bind_text16(m_stmt, nCol, text, textLength, f);
}

int CXStmt::bind_text64(int nCol, const char* text, unsigned __int64 textLength, void(*f)(void *), unsigned char encoding)
{
	return sqlite3_bind_text64(m_stmt, nCol, text, textLength, f, encoding);
}

