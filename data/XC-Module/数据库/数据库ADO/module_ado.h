#pragma once
#include <iostream>
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename ("EOF", "adoEOF")
#include <atlbase.h>
//extern _variant_t vtMissing;

//@模块名称  数据库ADO
//@版本  1.0  
//@日期  2022-01-26
//@作者  XCGUI  
//@QQ    154460336
//@模块备注 https://docs.microsoft.com/zh-cn/office/client-developer/access/desktop-database-reference/ado-objects-and-interfaces
// 引用本模块的项目使用的位数（x86 / x64）需要与系统已安装的Ado驱动位数一致
//@依赖  module_base.h, module_com.h

/*@声明
@分组{  枚举
enum CursorTypeEnum 
{
	adOpenUnspecified = -1,
	adOpenForwardOnly = 0,
	adOpenKeyset = 1,
	adOpenDynamic = 2,
	adOpenStatic = 3
};

enum LockTypeEnum
{
	adLockUnspecified = -1,
	adLockReadOnly = 1,
	adLockPessimistic = 2,
	adLockOptimistic = 3,
	adLockBatchOptimistic = 4
};

enum CommandTypeEnum
{
	adCmdUnspecified = -1,
	adCmdUnknown = 8,
	adCmdText = 1,
	adCmdTable = 2,
	adCmdStoredProc = 4,
	adCmdFile = 256,
	adCmdTableDirect = 512
};

enum MarshalOptionsEnum
{
	adMarshalAll = 0,
	adMarshalModifiedOnly = 1
};

enum SearchDirectionEnum
{
	adSearchForward = 1,
	adSearchBackward = -1
};

enum CursorLocationEnum
{
	adUseNone = 1,
	adUseServer = 2,
	adUseClient = 3,
	adUseClientBatch = 3
};

enum ConnectModeEnum
{
	adModeUnknown = 0,
	adModeRead = 1,
	adModeWrite = 2,
	adModeReadWrite = 3,
	adModeShareDenyRead = 4,
	adModeShareDenyWrite = 8,
	adModeShareExclusive = 12,
	adModeShareDenyNone = 16,
	adModeRecursive = 4194304
};

enum EditModeEnum
{
	adEditNone = 0,
	adEditInProgress = 1,
	adEditAdd = 2,
	adEditDelete = 4
};

enum PositionEnum
{
	adPosUnknown = -1,
	adPosBOF = -2,
	adPosEOF = -3
};

enum ResyncEnum
{
	adResyncUnderlyingValues = 1,
	adResyncAllValues = 2
};

enum SchemaEnum
{
	adSchemaProviderSpecific = -1,
	adSchemaAsserts = 0,
	adSchemaCatalogs = 1,
	adSchemaCharacterSets = 2,
	adSchemaCollations = 3,
	adSchemaColumns = 4,
	adSchemaCheckConstraints = 5,
	adSchemaConstraintColumnUsage = 6,
	adSchemaConstraintTableUsage = 7,
	adSchemaKeyColumnUsage = 8,
	adSchemaReferentialContraints = 9,
	adSchemaReferentialConstraints = 9,
	adSchemaTableConstraints = 10,
	adSchemaColumnsDomainUsage = 11,
	adSchemaIndexes = 12,
	adSchemaColumnPrivileges = 13,
	adSchemaTablePrivileges = 14,
	adSchemaUsagePrivileges = 15,
	adSchemaProcedures = 16,
	adSchemaSchemata = 17,
	adSchemaSQLLanguages = 18,
	adSchemaStatistics = 19,
	adSchemaTables = 20,
	adSchemaTranslations = 21,
	adSchemaProviderTypes = 22,
	adSchemaViews = 23,
	adSchemaViewColumnUsage = 24,
	adSchemaViewTableUsage = 25,
	adSchemaProcedureParameters = 26,
	adSchemaForeignKeys = 27,
	adSchemaPrimaryKeys = 28,
	adSchemaProcedureColumns = 29,
	adSchemaDBInfoKeywords = 30,
	adSchemaDBInfoLiterals = 31,
	adSchemaCubes = 32,
	adSchemaDimensions = 33,
	adSchemaHierarchies = 34,
	adSchemaLevels = 35,
	adSchemaMeasures = 36,
	adSchemaProperties = 37,
	adSchemaMembers = 38,
	adSchemaTrustees = 39,
	adSchemaFunctions = 40,
	adSchemaActions = 41,
	adSchemaCommands = 42,
	adSchemaSets = 43
};

@分组}

*/

//@别名 ADO错误类
class CAdoError
{
public:
	CAdoError(ErrorPtr err) {
		m_error = err;
	}
	//@隐藏{
	ErrorPtr  m_error;
	//@隐藏}
};

//@别名 ADO错误集合类
class CAdoErrors
{
public:
	CAdoErrors(ErrorsPtr err) {
		m_error = err;
	}
	//@隐藏{
	ErrorsPtr  m_error;
	//@隐藏}
};

//@备注  表示指向数据源的打开的连接。
//https://docs.microsoft.com/zh-cn/office/client-developer/access/desktop-database-reference/connection-properties-methods-and-events-ado
//@别名 ADO数据库类
class CAdoConnect
{
public:
//@隐藏{
	_ConnectionPtr  m_pConnection;
	CAdoConnect()
	{
		CoInitialize(NULL);
		HRESULT hr = m_pConnection.CreateInstance(__uuidof(Connection));
	}
	~CAdoConnect() {
		if (m_pConnection)
			m_pConnection.Release();
	}
//@隐藏}

	//@备注 打开与数据源的连接
	//"Driver=SQL Server;Database=test;Server=127.0.0.1;UID=sa;PWD=123;" //连接SQL SERVER
	//"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=mydb.mdb";  //access 2013
	//"Provider=Microsoft.ACE.OLEDB.12.0; Data Source=mydb.accdb"; //access 2017
	//@参数 pConnectionString 可选。 一个包含连接信息的 字符串 值。 有关有效设置的详细信息，请参阅 ConnectionString 属性。
	//@参数 pUserID 可选。 一个 字符串 值，该值包含建立连接时要使用的用户名。
	//@参数 pPassword 可选。 一个 字符串 值，该值包含建立连接时要使用的密码。
	//@参数 Options 可选。 一个 ConnectOptionEnum 值，该值确定此方法是在 (同步之后) 还是在建立连接 (异步) 之前返回。
	//@返回值 执行成功返回真,否则返回假
	//@别名 打开(链接字符串, 用户名, 密码, 选项)
	BOOL Open(const wchar_t* pConnectionString, const wchar_t* pUserID, const wchar_t* pPassword, long Options)
	{
		//"Driver=SQL Server;Database=test;Server=127.0.0.1;UID=sa;PWD=123;" //连接SQL SERVER
		//"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=mydb.mdb";  //access 2013
		//"Provider=Microsoft.ACE.OLEDB.12.0; Data Source=mydb.accdb"; //access 2017
		try
		{
			HRESULT hr = m_pConnection->Open(pConnectionString, pUserID, pPassword, adModeUnknown);
		} catch (...) // (_com_error &e)
		{
			return FALSE;
		}
		return TRUE;
	}
	//@备注 关闭打开的对象和所有依赖对象
	//@返回值 执行成功返回真,否则返回假
	//@别名 关闭()
	BOOL Close()
	{
		HRESULT hr = m_pConnection->Close();
		if (SUCCEEDED(hr))
			return TRUE;
		return FALSE;
	} 
	//@备注 指示用于与数据源建立连接的信息
	//@别名 置链接字符串()
	void PutConnectionString(const wchar_t* pConnectionString)
	{
		m_pConnection->PutConnectionString(pConnectionString);
	}
	//@备注 指示用于与数据源建立连接的信息
	//@别名 取链接字符串()
	const wchar_t* GetConnectionString(const wchar_t* pConnectionString)
	{
		return m_pConnection->GetConnectionString();
	}
	//@备注 获取版本信息
	//@别名 取版本信息()
	const wchar_t* GetVersion()
	{
		return m_pConnection->GetVersion();
	}
	//@备注 指示在执行命令时在终止尝试并生成错误之前等待的时间
	// 设置或返回 一个 Long 值，该值指示等待命令执行多久（以秒表示）。 默认值为 30。
	//@别名 置执行超时值(超时值)
	void PutCommandTimeout(long timeOut)
	{
		m_pConnection->PutCommandTimeout(timeOut);
	}

	//@备注 指示在执行命令时在终止尝试并生成错误之前等待的时间
	//设置或返回 一个 Long 值，该值指示等待命令执行多久（以秒表示）。 默认值为 30。
	//@别名 取执行超时值()
	long GetCommandTimeout()
	{
		return m_pConnection->GetCommandTimeout();
	}
	//@备注 指示在终止尝试并生成错误之前建立连接时等待的时间
	// 设置或返回一个 长整型 值，该值指示等待连接打开的时间（以秒为单位）。 默认为 15.
	//@别名 置执链接超时值(超时值)
	void PutConnectionTimeout(long timeOut)
	{
		m_pConnection->PutConnectionTimeout(timeOut);
	}

	//@备注 指示在终止尝试并生成错误之前建立连接时等待的时间
	// 设置或返回一个 长整型 值，该值指示等待连接打开的时间（以秒为单位）。 默认为 15.
	//@别名 取执链接超时值()
	long GetConnectionTimeout()
	{
		return m_pConnection->GetConnectionTimeout();
	}
	//@备注 指示对象的状态是打开还是关闭，适用于所有适用对象。 如果对象正在执行异步方法，则 指示对象的当前状态是正在连接、执行还是正在检索。
	//@返回值 返回 一个 Long 值，该值可以是 ObjectStateEnum 值。 默认值为 adStateClosed。
	//@别名 取状态()
	long GetState()
	{
		return m_pConnection->GetState();
	}
	//@备注 指示 连接 对象的访问接口的名称
	// 设置或返回一个指示提供程序名称的 字符串 值。
	//@别名 置提供者名称(供者名称)
	void PutProvider(const wchar_t* pProvider)
	{
		m_pConnection->PutProvider(pProvider);
	}
	
	//@备注 指示 连接 对象的访问接口的名称
	// 设置或返回一个指示提供程序名称的 字符串 值。
	//@别名 取提供者名称()
	const wchar_t* GetProvider()
	{
		return m_pConnection->GetProvider();
	}
	//@备注 指示游标服务的位置
	// 设置或返回一个可以设置为 CursorLocationEnum值之一的 Long 值。
	//@别名 置游标位置(游标位置)
	void PutCursorLocation(CursorLocationEnum plCursorLoc)
	{
		m_pConnection->PutCursorLocation(plCursorLoc);
	}
	//@备注 指示游标服务的位置
	// 设置或返回一个可以设置为 CursorLocationEnum值之一的 Long 值。
	//@别名 取游标位置()
	CursorLocationEnum GetCursorLocation()
	{
		return m_pConnection->GetCursorLocation();
	}
	//@备注 指示 连接 对象的默认数据库
	//设置或返回一个 字符串 值，该值的计算结果为提供程序提供的数据库的名称
	//使用 DefaultDatabase 属性可以设置或返回特定 连接 对象上默认数据库的名称
	//@别名 置默认数据库(库名)
	void PutDefaultDatabase(const wchar_t* pDefaultDatabase)
	{
		m_pConnection->PutDefaultDatabase(pDefaultDatabase);
	}
	//@备注 指示 连接 对象的默认数据库
	// 设置或返回一个 字符串 值，该值的计算结果为提供程序提供的数据库的名称
	// 使用 DefaultDatabase 属性可以设置或返回特定 连接 对象上默认数据库的名称
	//@别名 取默认数据库()
	const wchar_t* GetDefaultDatabase(const wchar_t* pDefaultDatabase){
		return m_pConnection->GetDefaultDatabase();
	}
	//@备注 指示 连接 对象的隔离级别
	// 设置一个 IsolationLevelEnum 值。 默认值为 adXactReadCommitted
	//@别名 置隔离级别(级别)
	void PutIsolationLevel(IsolationLevelEnum Level)
	{
		m_pConnection->PutIsolationLevel(Level);
	}
	//@备注 指示 连接 对象的隔离级别
	// 返回一个 IsolationLevelEnum 值。 默认值为 adXactReadCommitted
	//@别名 取隔离级别()
	IsolationLevelEnum GetIsolationLevel(IsolationLevelEnum Level)
	{
		return m_pConnection->GetIsolationLevel();
	}
	//@备注 指示用于修改 连接、 记录或 流 对象中的数据的可用权限。
	//@别名 置权限模式(权限模式)
	void PutMode(ConnectModeEnum Mode)
	{
		m_pConnection->PutMode(Mode);
	}
	//@备注 指示用于修改 连接、 记录或 流 对象中的数据的可用权限。
	//@别名 取权限模式()
	ConnectModeEnum GetMode()
	{
		return m_pConnection->GetMode();
	}
	//@返回值  ADO错误集合对象
	//@别名 取错误集合()
	CAdoErrors GetErrors(){
		return m_pConnection->GetErrors();
	}
	//@备注 指示对象的一个或多个特征
	//@别名 置属性值(属性值)
	long PutAttributes(long attr){
		m_pConnection->PutAttributes(attr);
	}
	//@备注 指示对象的一个或多个特征
	//@别名 取属性值()
	long GetAttributes(){
		return m_pConnection->GetAttributes();
	}
	//@备注 从提供程序中获取数据库架构信息。
	// 表示要运行的架构查询类型的任何 SchemaEnum 值。
	//@返回值 ADO记录集类, 返回一个包含架构信息的 记录集 对象。 记录集 将作为只读静态游标打开。 QueryType 确定在 记录集中 显示的列。
	//@别名 取结构信息(查询类型)
	_RecordsetPtr OpenSchema(enum SchemaEnum Schema,const _variant_t& Restrictions = vtMissing,	const _variant_t& SchemaID = vtMissing)
	{
		return m_pConnection->OpenSchema(Schema, Restrictions, SchemaID);
	}
	//@备注 取消执行挂起的异步方法调用
	//Cancel 方法用于终止异步方法调用（即用 adAsyncConnect、adAsyncExecute 或 adAsyncFetch 选项调用的方法）的执行。
	//@返回值 执行成功返回真,否则返回假
	//@别名  取消()
	BOOL Cancel()
	{
		return SUCCEEDED(m_pConnection->Cancel())? TRUE :FALSE;
	}
	//@备注 执行指定的SQL语句
	//@参数 pCommandText 提供所欲执行的SQL语句
	//@参数 pRecordsAffected 可选, 提供程序向其返回操作所影响的记录数
	//@参数 Options 可选, 用于指示提供程序评估 CommandText 参数的方式。 该参数可以是一个或多个 CommandTypeEnum 或 ExecuteOptionEnum 值的位掩码。
	//@返回 返回记录集类
	//@别名 执行SQL(SQL语句, 接收影响行数, 选项)
	_RecordsetPtr Execute(const wchar_t* pCommandText,long* pRecordsAffected, long Options)
	{
		_variant_t  RecordsAffected_(0);
		_RecordsetPtr pRecordset = m_pConnection->Execute(pCommandText, &RecordsAffected_, Options);
		if(pRecordsAffected)
			*pRecordsAffected = (long)RecordsAffected_;
		return pRecordset;
	}
};

//@备注 表示从基表得到的整个记录集，或执行命令的结果。在任何时候，Recordset 对象只引用该集合中的单个记录作为当前记录。
// https://docs.microsoft.com/zh-cn/office/client-developer/access/desktop-database-reference/recordset-object-ado
//@别名 ADO记录集类
class CAdoRecordset
{
//@隐藏{
	_RecordsetPtr     m_pRecordset;
//@隐藏}
public:
//@隐藏{
	CAdoRecordset() { 
		CoInitialize(NULL);
		HRESULT hr = m_pRecordset.CreateInstance(__uuidof(Recordset));
	}
	CAdoRecordset(_RecordsetPtr pRecordset)
	{
		m_pRecordset = pRecordset;
	}
	~CAdoRecordset()
	{
		if(m_pRecordset)
			m_pRecordset.Release();
	}
//@隐藏}
	void operator =(_RecordsetPtr pRecordset) {
		m_pRecordset = pRecordset;
	}
	//@备注 用于打开与数据源的连接
	//@参数 SQL语句
	//@参数 ADO数据库类指针
	//@参数 可选。 一个 CursorTypeEnum 值，确定提供程序在打开 记录集 时应使用的游标类型。 默认值为 adOpenForwardOnly。
	//@参数 可选。 LockTypeEnum值，用于确定提供程序在打开 记录集 时应使用的 (并发) 类型。 默认值为 adLockReadOnly。
	//@参数 可选。 一个 长整型 值，该值指示当提供程序表示某个 命令 对象以外的内容时，该提供程序应如何计算 Source 参数，或者应从以前保存该记录集的文件还原该 记录集。 可以是一个或多个 CommandTypeEnum 或 ExecuteOptionEnum 值，可以与按位 or 运算符组合。
	//@返回值 执行成功返回真,否则返回假
	//@别名 打开(SQL语句, ADO数据库类指针, 游标类型, 锁类型, 选项)
	BOOL Open(const wchar_t* Source, CAdoConnect*  pConnect, enum CursorTypeEnum CursorType, enum LockTypeEnum LockType, long Options)
	{
		try
		{
			HRESULT hr = m_pRecordset->Open(Source, pConnect->m_pConnection.GetInterfacePtr(), CursorType, LockType, Options);
			if (SUCCEEDED(hr))
				return TRUE;
		} catch (...) //(_com_error& e)
		{
			return FALSE;
		}
		return FALSE;
	}
	//@备注 指示由多少记录构成 Recordset 中的一页。
	// 设置或返回一个 Long 值，指示页上的记录数。默认值为 10。
	//@别名 置页大小(页大小)
	void PutPageSize(long size){
		m_pRecordset->PutPageSize(size);
	}
	//@备注 指示由多少记录构成 Recordset 中的一页。
	// 设置或返回一个 Long 值，指示页上的记录数。默认值为 10。
	//@别名 取页大小()
	long GetPageSize(){
		return m_pRecordset->GetPageSize();
	}
	//@备注 指示 Recordset 对象包含的数据页数
	//@别名 取页数()
	long GetPageCount()
	{
		return m_pRecordset->GetPageCount();
	}
	//@备注 指示游标服务的位置。
	// 设置或返回一个 Long 值，该值可以设置为 CursorLocationEnum 值之一
	//@别名 置游标服位置(位置)
	void PutCursorLocation(CursorLocationEnum plCursorLoc){
		m_pRecordset->PutCursorLocation(plCursorLoc);
	}
	//@备注 指示游标服务的位置。
	// 设置或返回一个 Long 值，该值可以设置为 CursorLocationEnum 值之一
	//@别名 取游标服位置(位置)
	CursorLocationEnum GetCursorLocation(){
		return m_pRecordset->GetCursorLocation();
	}
	//@备注 指示哪些记录要封送回服务器。
	//设置或返回一个 MarshalOptionsEnum 值。默认值是 adMarshalAll。
	//@别名 置数据封送选项()
	void PutMarshalOptions(MarshalOptionsEnum peMarshal)
	{
		m_pRecordset->PutMarshalOptions(peMarshal);
	}
	//@备注 指示哪些记录要封送回服务器。
	//设置或返回一个 MarshalOptionsEnum 值。默认值是 adMarshalAll。
	//@别名 取数据封送选项()
	MarshalOptionsEnum GetMarshalOptions()
	{
		return m_pRecordset->GetMarshalOptions();
	}
	//@参数 字段名称或序号
	//@返回值 COM变体型, 返回字段值
	//@别名 取列值()
	CXComVariant GetCollect(const CComVariant& index)
	{
		CXComVariant s = m_pRecordset->GetCollect(index);
		return s;
	}
	//@备注 指示与批更新或其他批量操作相关的当前记录的状态
	//@别名 取状态()
	long GetStatus()
	{
		return m_pRecordset->GetStatus();
	}
	//@备注 指示 Recordset 中数据的筛选条件
	//设置或返回一个 Variant 值，该值可包含以下内容之一：
	//1 条件字符串  由一个或多个用 AND 或 OR 运算符连接的子句组成的字符串。
	//2 书签数组  指向 Recordset 对象中的记录的唯一书签值数组。
	//3 一个 FilterGroupEnum 值。
	//@别名 置筛选(筛选条件)
	void PutFilter(CComVariant& Criteria)
	{
		m_pRecordset->PutFilter(Criteria);
	}
	//@备注 指示 Recordset 中数据的筛选条件
	//@别名 取筛选()
	CComVariant GetFilter()
	{
		return m_pRecordset->GetFilter();
	}
	//@备注 指示一个或多个作为 Recordset 的排序依据的字段名称，并指定是按升序还是降序对字段进行排序。
	//@别名 置排序(排序规则)
	void PutSort(const wchar_t* pCriteria)
	{
		m_pRecordset->PutSort(pCriteria);
	}
	//@备注 指示一个或多个作为 Recordset 的排序依据的字段名称，并指定是按升序还是降序对字段进行排序。
	// 设置或返回一个 String 值，指示作为 Recordset 的排序依据的字段名称。每个名称由逗号分隔，可以选择后跟空格和关键字 ASC（以升序对字段进行排序）或 DESC（以降序对字段进行排序）。默认情况下，如果未指定关键字，则以升序对字段进行排序。
	//@别名 取排序()
	const wchar_t* GetSort()
	{
		return m_pRecordset->GetSort();
	}
	//@备注 指示 Recordset 对象的当前记录的序号位置
	// 设置或返回一个 Long 值，该值的范围为 1 到 Recordset 对象中的记录数 (RecordCount)；或返回 PositionEnum 值之一。
	//@别名 置当前位置(位置)
	void PutAbsolutePosition(PositionEnum pl)
	{
		m_pRecordset->PutAbsolutePosition(pl);
	}
	//@备注 指示 Recordset 对象的当前记录的序号位置
	//@别名 取当前位置()
	PositionEnum GetAbsolutePosition()
	{
		return m_pRecordset->GetAbsolutePosition();
	}
	//@备注 指示指定的 Command、Recordset 或 Record 对象当前属于哪个 Connection 对象。
	//如果某个连接处于关闭状态，则设置或返回一个 String 值，其中包含该连接的定义；如果某个连接处于打开状态，则设置或返回一个 Variant ，其中包含当前的 Connection 对象。默认值为一个空对象引用。请参阅 ConnectionString 属性。
	//@别名 置当前链接对象()
	void PutActiveConnection(CComVariant& pvar)
	{
		m_pRecordset->PutActiveConnection(pvar);
	}
	//@备注 指示指定的 Command、Recordset 或 Record 对象当前属于哪个 Connection 对象。
	//@别名 取当前链接对象()
	CComVariant GetActiveConnection()
	{
		return m_pRecordset->GetActiveConnection();
	}
	//@备注  指示当前记录位置在 Recordset 对象中的第一条记录之前
	//@返回值 执行成功返回真,否则返回假
	//@别名  是否首记录之前()
	BOOL IsBOF()
	{
		return 0==m_pRecordset->GetBOF() ? TRUE : FALSE;
	}
	//@备注 指示在 Recordset 对象中唯一标识当前记录的书签，或者将 Recordset 对象中的当前记录设置为有效书签标识的记录。
	//设置或返回一个 Variant 表达式，该表达式的计算结果为一个有效书签。
	//@别名 置书签(书签)
	void PutBookmark(CComVariant &pvBookmark)
	{
		m_pRecordset->PutBookmark(pvBookmark);
	}
	//@备注  指示在 Recordset 对象中唯一标识当前记录的书签，或者将 Recordset 对象中的当前记录设置为有效书签标识的记录。
	//@别名  取书签()
	CComVariant GetBookmark()
	{
		return m_pRecordset->GetBookmark();
	}
	//@备注 指示本地缓存在内存中的 Recordset 对象的记录数
	//设置或返回一个必须大于 0 的 Long 值。默认值为 1。
	//@别名 置缓存大小(缓存大小)
	void PutCacheSize(long cacheSize)
	{
		m_pRecordset->PutCacheSize(cacheSize);
	}
	//@备注 指示本地缓存在内存中的 Recordset 对象的记录数
	//@别名 取缓存大小()
	long GetCacheSize()
	{
		return m_pRecordset->GetCacheSize();
	}
	//@备注 指示在 Recordset 对象中使用的游标类型
	// 设置或返回 CursorTypeEnum 值。默认值为 adOpenForwardOnly
	//@别名 置游标类型(游标类型)
	void PutCursorType(CursorTypeEnum plCursorType)
	{
		m_pRecordset->PutCursorType(plCursorType);
	}
	//@备注 指示在 Recordset 对象中使用的游标类型
	//@别名 取游标类型()
	CursorTypeEnum GetCursorType()
	{
		return m_pRecordset->GetCursorType();
	}
	//@备注 指示当前记录位置在 Recordset 对象中的最后一条记录之后。
	//@返回值 执行成功返回真,否则返回假
	//@别名 是否尾记录之后()
	BOOL IsEOF()
	{
		return m_pRecordset->GetadoEOF() ? TRUE : FALSE;
	}
	//@返回值 ADO字段集类
	//@别名 取字段集()
	FieldsPtr GetFields()
	{
		return m_pRecordset->GetFields();
	}

	//@备注 指示编辑过程中为记录设置的锁定类型。
	// 设置或返回一个 LockTypeEnum 值。默认值为 adLockReadOnly 。
	//@别名 置锁类型(锁类型)
	void PutLockType(LockTypeEnum plLockType)
	{
		m_pRecordset->PutLockType(plLockType);
	}
	//@备注 指示编辑过程中为记录设置的锁定类型。
	//@别名 取锁类型()
	LockTypeEnum GetLockType()
	{
		return m_pRecordset->GetLockType();
	}
	//@备注 指示通过查询返回到 Recordset 的最大记录数
	// 设置或返回一个 Long 值，指示要返回的最大记录数。默认值为 0（没有限制）。
	//@别名 置最大记录数(最大记录数) 
	void PutMaxRecords(long plMaxRecords)
	{
		m_pRecordset->PutMaxRecords(plMaxRecords);
	}
	//@备注 指示通过查询返回到 Recordset 的最大记录数
	//@别名 取最大记录数()
	long GetMaxRecords()
	{
		return m_pRecordset->GetMaxRecords();
	}
	//@备注 指示 Recordset 对象中的记录数。
	//返回一个 Long 值，指示 Recordset 中的记录数。
	//@别名 取记录数()
	long GetRecordCount()
	{
		return m_pRecordset->GetRecordCount();
	}

	//@备注 指示由 Record 表示的数据源或对象
	//@别名 置引用数据源()
	void PutRefSource(IDispatch* pvSource)
	{
		m_pRecordset->PutRefSource(pvSource);
	}
	//@备注 指示 Recordset 对象的数据源
	//设置一个 String 值或 Command 对象引用；仅返回一个 String 值，该值指示 Recordset 的数据源
	//@别名 置数据源(数据源)
	void PutSource(const wchar_t* pvSource)
	{
		m_pRecordset->PutSource(pvSource);
	}
	//@备注 指示 Recordset 对象的数据源
	//@别名 取数据源()
	CComVariant GetSource()
	{
		m_pRecordset->GetSource();
	}
	//@备注 用于为可更新的 Recordset 对象创建新记录。
	//@参数 可选。单个名称，或新记录中字段名称或序号位置的数组。
	//@参数 可选。 单个值，或新记录中字段值的数组。 如果 Fieldlist 为数组，则 Values 也必须是具有相同成员数的数组，否则将发生错误。 在每个数组中，字段名称的次序必须与字段值的次序匹配。
	//@返回值 执行成功返回真,否则返回假
	//@别名 添加新记录(字段列表, 置列表)
	BOOL AddNew(const CComVariant  &FieldList, const CComVariant &Values)
	{
		return SUCCEEDED( m_pRecordset->AddNew(FieldList, Values))? TRUE : FALSE;
	}
	//@备注 在调用 Update 方法之前，取消对 Recordset 对象的当前行或新行，或对 Record 对象的 Fields 集合所做的任何更改。
	//@返回值 执行成功返回真,否则返回假
	//@别名 取消更新()
	BOOL CancelUpdate()
	{
		return SUCCEEDED(m_pRecordset->CancelUpdate()) ? TRUE : FALSE;
	}
	//@备注 用于关闭打开的对象和任何相关的对象。
	//@返回值 执行成功返回真,否则返回假
	//@别名 关闭()
	BOOL Close()
	{
		if(SUCCEEDED(m_pRecordset->Close()))
			return TRUE;
		return FALSE;
	}
	//@备注 用于删除当前记录或一组记录
	//@参数 AffectEnum 值，可确定 Delete 方法将影响的记录数。默认值为 adAffectCurrent 。
	//@返回值 执行成功返回真,否则返回假
	//@别名 删除(选项)
	BOOL Delete(AffectEnum AffectRecords)
	{
		return SUCCEEDED(m_pRecordset->Delete(AffectRecords)) ? TRUE : FALSE;
	}
	//@备注 用于将 Recordset 对象的多个记录检索到数组中
	//@参数 可选。GetRowsOptionEnum 值，指示要检索的记录数。默认值为 adGetRowsRest 。
	//@参数 可选。 字符串型 值或 变量 ，变量计算得出的值为应从该处开始 GetRows 操作的记录的书签。也可以使用 BookmarkEnum 值。
	//@参数 可选。 变量 ，代表单个字段名或序号位置，或一个含一些字段名或序号位置编号的数组。ADO 仅返回这些字段中的数据。
	//@返回值 返回一个 变量，其值是二维数组。
	//@别名 取多行记录(行数, 开始位置, 字段列表)
	CComVariant GetRows(long Rows, const CComVariant& Start = vtMissing, const CComVariant& Fields = vtMissing)
	{
		return m_pRecordset->GetRows(Rows, Start, Fields);
	}
	//@备注 用于移动 Recordset 对象中当前记录的位置
	//@参数 有符号的 长整型 表达式，指定当前记录位置移动的记录数。
	//@参数 可选。 字符串型 值或值为书签的 变量型 值。也可以使用 BookmarkEnum 值。
	//@返回值 执行成功返回真,否则返回假
	//@别名 移动位置(移动的记录数, 开始位置)
	BOOL Move(long NumRecords, const CComVariant& Start = vtMissing)
	{
		return SUCCEEDED(m_pRecordset->Move(NumRecords, Start)) ? TRUE : FALSE;
	}
	//@备注 用于移动到指定的 Recordset 对象中的第一个、最后一个、下一个或上一个记录，并使该记录成为当前记录。
	//@返回值 执行成功返回真,否则返回假
	//@别名 到下一个()
	BOOL MoveNext()
	{
		if (SUCCEEDED(m_pRecordset->MoveNext()))
			return TRUE;
		return FALSE;
	}
	//@返回值 执行成功返回真,否则返回假
    //@别名 到上一个()
	BOOL MovePrevious()
	{
		return SUCCEEDED(m_pRecordset->MovePrevious()) ? TRUE : FALSE;
	}
	//@返回值 执行成功返回真,否则返回假
	//@别名 到第一个()
	BOOL MoveFirst()
	{
		return SUCCEEDED(m_pRecordset->MoveFirst()) ? TRUE : FALSE;
	}
	//@返回值 执行成功返回真,否则返回假
	//@别名 到最后一个()
	BOOL MoveLast()
	{
		return SUCCEEDED(m_pRecordset->MoveLast()) ? TRUE : FALSE;
	}
	//@备注 通过重新执行对象所基于的查询，更新 Recordset 对象中的数据。
	//@参数 可选。包含影响此操作的 ExecuteOptionEnum 和 CommandTypeEnum 值的位掩码。
	//@返回值 执行成功返回真,否则返回假
	//@别名 重新查询(选项)
	BOOL Requery(long Options)
	{
		return SUCCEEDED(m_pRecordset->Requery(Options)) ? TRUE : FALSE;
	}
	//@备注 用于从基础数据库刷新当前 Recordset 对象中的数据或刷新 Record 对象的 Fields 集合中的数据
	//@参数 可选。AffectEnum 值，用于确定 Resync 方法将影响的记录数。默认值为 adAffectAll 。对于 Record 对象的 Fields 集合的 Resync 方法，此值不可用。
	//@参数 可选。ResyncEnum 值，用于指定是否覆盖基础值。默认值为 adResyncAllValues 。
	//@返回值 执行成功返回真,否则返回假
	//@别名 垂直同步(影响记录数, 值选项)
	BOOL Resync(AffectEnum AffectRecords, ResyncEnum ResyncValues)
	{
		return SUCCEEDED(m_pRecordset->Resync(AffectRecords, ResyncValues)) ? TRUE : FALSE;
	}
	//@备注 可保存对 Recordset 对象的当前行或 Record 对象的 Fields 集合所做的任何更改。
	//@参数 可选。一个表示单个名称的 Variant ，或表示要修改的字段的名称或序号位置的 Variant 数组。
	//@参数 可选。一个表示单个名称的 Variant ，或表示新记录中字段值的 Variant 数组。
	//@返回值 执行成功返回真,否则返回假
	//@别名 更新(字段, 值数)
	BOOL Update(const CComVariant& Fields = vtMissing, const CComVariant& Values = vtMissing)
	{
		return SUCCEEDED(m_pRecordset->Update(Fields, Values)) ? TRUE : FALSE;
	}
	//@备注 指示当前记录驻留在哪一页。
	//设置或返回 一个 Long 值，该值从 1 到 PageCount (中的页数) 或 返回 PositionEnum 值之一
	//@别名 置当前页(当前页)
	void PutAbsolutePage(enum PositionEnum pl)
	{
		m_pRecordset->PutAbsolutePage(pl);
	}
	//@备注 指示当前记录驻留在哪一页。
	//@别名 取当前页()
	enum PositionEnum GetAbsolutePage()
	{
		return m_pRecordset->GetAbsolutePage();
	}
	//@备注 指示当前记录的编辑状态。
	//@别名 取编辑状态()
	enum EditModeEnum GetEditMode()
	{
		return m_pRecordset->GetEditMode();
	}
	//@备注 用于从现有 Recordset 对象创建重复的 Recordset 对象。还可以指定克隆为只读状态。
	//@参数 可选。LockTypeEnum 值，用于指定原始 Recordset 或只读 Recordset 的锁类型。有效值为 adLockUnspecified 或 adLockReadOnly 。
	//@别名 克隆(锁类型)
	_RecordsetPtr Clone(enum LockTypeEnum LockType)
	{
		return m_pRecordset->Clone(LockType);
	}
	//@备注 用于将所有挂起的批更新写入磁盘
	//可选。AffectEnum 值，指示 UpdateBatch 方法将影响的记录数。
	//@别名  批更新(影响记录数)
	HRESULT UpdateBatch(enum AffectEnum AffectRecords)
	{
		return SUCCEEDED(m_pRecordset->UpdateBatch(AffectRecords)) ? TRUE : FALSE;
	}
	//@备注 用于取消挂起的批更新。
	//@参数 可选。AffectEnum 值，用于指示 CancelBatch 方法将影响的记录数。
	//@别名 取消批更新(影响记录数)
	HRESULT CancelBatch(enum AffectEnum AffectRecords)
	{
		m_pRecordset->CancelBatch(AffectRecords);
	}
	//@备注 用于通过执行一系列命令，清除当前 Recordset 对象并返回下一个 Recordset。
	//@参数 可选。 长整型 变量，提供程序将受当前操作影响的记录数返回到该变量
	//@别名 到下一个记录集(接收返回影响记录数)
	_RecordsetPtr NextRecordset(CComVariant* RecordsAffected)
	{
		return m_pRecordset->NextRecordset(RecordsAffected);
	}
	//@备注 用于确定指定的 Recordset 对象是否支持特定类型的功能
	//@返回值 返回 Boolean 值，指示提供程序是否支持 CursorOptions 参数所标识的所有功能
	//@别名  是否支持指定功能(功能选项)
	BOOL Supports(enum CursorOptionEnum CursorOptions)
	{
		return m_pRecordset->Supports(CursorOptions);
	}
	//@备注 用于在 Recordset 中搜索满足指定条件的行。可以选择性地指定搜索方向、起始行和与起始行的偏移量。如果满足条件，当前行位置将设置为找到的记录位置；否则，该位置设置为 Recordset 的末尾（或开头）
	//@参数 Criteria 字符串型 值，包含用于指定在搜索中使用的列名、比较运算符和值的语句。
	//@参数 SkipRecords 可选。 长整型 值，默认值为零，用于指定与当前行的行偏移量或 开始 书签，以开始搜索。 默认情况下，搜索将从当前行开始。
	//@参数 SearchDirection 可选。 SearchDirectionEnum 值，指定搜索应从当前行开始还是从搜索方向上的下一个可用行开始。 如果该值为 adSearchForward ，则不成功的搜索在 Recordset 的末尾停止。 如果该值为 adSearchBackward ，则不成功的搜索在 Recordset 的开头停止
	//@参数 Start 可选。 变量型 书签，充当搜索的开始位置。
	//@返回值 执行成功返回真,否则返回假
	//@别名 查找(搜索语句, 开始偏移位置, 方向, 开始书签位置)
	HRESULT Find(const wchar_t* pCriteria,	long SkipRecords,enum SearchDirectionEnum SearchDirection,	const _variant_t& Start = vtMissing)
	{
		return SUCCEEDED(m_pRecordset->Find(pCriteria, SkipRecords, SearchDirection, Start)) ? TRUE : FALSE;
	}
};

//@备注 包含 Recordset 或 Record 对象的所有 Field 对象
//https://docs.microsoft.com/zh-cn/office/client-developer/access/desktop-database-reference/fields-collection-properties-methods-and-events
//@别名 ADO字段集类
class CAdoFields
{
public:
//@隐藏{
	FieldsPtr  m_Fields;
	CAdoFields(FieldsPtr Fields)
	{
		m_Fields = Fields;
	}
//@隐藏}
	//@备注 指示集合中的对象数。
	//@别名 取成员数量()
	long  GetCount()
	{
		return m_Fields->GetCount();
	}
	//@备注  按名称或序号指示集合的特定成员。
	//@参数  一个 Variant 表达式，其值为集合中对象的名称或序号。
	//@别名  取成员()
	const wchar_t* GetItem(const CComVariant &index)
	{
		_bstr_t s = m_Fields->GetItem(index)->Name;
		return s;
	}
	//@备注  用于将对象追加到集合。如果集合为 Fields，则在将对象追加到集合之前，可能会创建新的 Field 对象。
	//@参数 Name	字符串 值，包含新的 Field 对象的名称，不能与 fields 中任何其他对象同名。
	//@参数 Type  DataTypeEnum 值，其默认值为 adEmpty ，用于指定新字段的数据类型。ADO 不支持以下数据类型，在将新字段追加到 Recordset 时不应当使用这些数据类型： adIDispatch 、 adIUnknown 、 adVariant 。
	//@参数 DefinedSize  可选。长整型 值，表示新字段的定义大小，以字符数或字节数计。此参数的默认值由 Type 决定。DefinedSize 大于 255 字节的字段将被视为可变长度列。（未指定默认 DefinedSize。）
	//@参数 Attrib  可选。FieldAttributeEnum 值，其默认值为 adFldDefault，用于指定新字段的属性。如果未指定此值，则字段所包含的属性由 Type 决定。
	//@参数 FieldValue 可选。 变量型 ，表示新字段的值。如果未指定此值，则为字段追加一个 Null 值。
	//@别名 追加()
	BOOL Append(_bstr_t Name, enum DataTypeEnum Type, long DefinedSize, enum FieldAttributeEnum Attrib, const _variant_t& FieldValue)
	{
		m_Fields->Append(Name, Type, DefinedSize, Attrib, FieldValue);
	}
	//@备注 更新集合中的对象，以反映提供程序特定的可用对象。
	//Refresh 方法用于完成各种不同的任务，具体取决于从中调用该方法的集合
	//@返回值 执行成功返回真,否则返回假
	//@别名 刷新()
	BOOL Refresh()
	{
		return SUCCEEDED(m_Fields->Refresh()) ? TRUE : FALSE;
	}
	//@备注 可保存对 Recordset 对象的当前行或 Record 对象的 Fields 集合所做的任何更改。
	//@返回值 执行成功返回真,否则返回假
	//@别名 更新()
	BOOL Update()
	{
		return SUCCEEDED(m_Fields->Update()) ? TRUE : FALSE;
	}
	//@备注 在调用 Update 方法之前，取消对 Recordset 对象的当前行或新行，或对 Record 对象的 Fields 集合所做的任何更改。
	//@返回值 执行成功返回真,否则返回假
	//@别名 取消更新()
	BOOL CancelUpdate()
	{
		m_Fields->CancelUpdate();
	}
	//@备注  用于从 Fields 集合中删除对象
	//@参数 变量型 ，指定要删除的 Field 对象。此参数可以是 Field 对象的名称，或 Field 对象自身的序号位置。
	//@返回值 执行成功返回真,否则返回假
	//@别名  删除(字段)
	BOOL Delete(const CComVariant& Index)
	{
		m_Fields->Delete(Index);
	}
	//@备注 用于从基础数据库刷新当前 Recordset 对象中的数据或刷新 Record 对象的 Fields 集合中的数据。
	//@参数 可选。ResyncEnum 值，用于指定是否覆盖基础值。默认值为 adResyncAllValues 。
	//@返回值 执行成功返回真,否则返回假
	//@别名 垂直同步(选项)
	BOOL Resync(enum ResyncEnum ResyncValues)
	{
		m_Fields->Resync(ResyncValues);
	}
};
