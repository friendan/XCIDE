
函数 整型 callback(空类型* NotUsed, 整型 argc, 字符型A**argv, 字符型A**azColName)
	计次循环 整型 i = 0; argc
		如果 argv[i]
			调试输出(azColName[i], ":", argv[i])
		否则
			调试输出(azColName[i], ":NULL")
	返回 0
	
函数 空类型 测试_exec()
	sqlite3 *db
	整型 ret = 数据库3_打开16("test.db", &db)
	如果 SQLITE_OK != ret
		调试输出("不能打开数据库:", 数据库3_取错误信息(db))
		数据库3_关闭(db)
		返回
	//创建表
	字符型A *zErrMsg = 0
	ret = 数据库3_执行SQL(db, A"CREATE TABLE IF NOT EXISTS xcgui(id integer PRIMARY KEY AUTOINCREMENT, name text NOT NULL,age integer NOT NULL)", callback, 0, &zErrMsg)
	如果 (ret != SQLITE_OK)
		调试输出("SQL error:", zErrMsg)
		数据库3_内存释放(zErrMsg)
		数据库3_关闭(db)
		返回
	//插入
	ret = 数据库3_执行SQL(db, A"INSERT INTO xcgui(name, age) VALUES ('大明', 22)", callback, 0, &zErrMsg)
	如果 (ret != SQLITE_OK)
		调试输出("SQL error:", zErrMsg)
		数据库3_内存释放(zErrMsg)
		数据库3_关闭(db)
		返回
	//查询
	ret = 数据库3_执行SQL(db, A"SELECT * FROM xcgui", callback, 0, &zErrMsg)
	如果 (ret != SQLITE_OK)
		调试输出("SQL error:", zErrMsg)
		数据库3_内存释放(zErrMsg)
		数据库3_关闭(db)
		返回
	数据库3_关闭(db)
	
函数 空类型 测试_语句()
	sqlite3 *db
	整型 ret = 数据库3_打开16("test.db", &db)
	如果 SQLITE_OK != ret
		调试输出("不能打开数据库:", 数据库3_取错误信息(db))
		数据库3_关闭(db)
		返回	
	//准备语句
	sqlite3_stmt * stmt
	ret = 记录集3_语句准备16(db, "SELECT * FROM xcgui", -1, &stmt, NULL)
	如果 (SQLITE_OK != ret)
		调试输出("SQL error:", 数据库3_取错误信息16(db))
		记录集3_释放(stmt)
		数据库3_关闭(db)
		返回

	//执行语句
	循环 (SQLITE_ROW == 记录集3_执行语句(stmt))
		调试输出(记录集3_取列名称16(stmt, 0), ":", 记录集3_取列文本16(stmt, 0))
		调试输出(记录集3_取列名称16(stmt, 1), ":", 记录集3_取列文本16(stmt, 1))
		调试输出(记录集3_取列名称16(stmt, 2), ":", 记录集3_取列文本16(stmt, 2))
	//ret = sqlite3_语句重置(stmt)  调用[重置语句]后可再次循环 [语句单步]
	sqlite3_finalize(stmt)
	sqlite3_close(db)

函数  空类型 测试_绑定()
	sqlite3 *db
	整型 ret = 数据库3_打开16("test.db", &db)
	如果 SQLITE_OK != ret
		调试输出("不能打开数据库:", 数据库3_取错误信息(db))
		数据库3_关闭(db)
		返回
	
	测试_删除(db)
	测试_查询(db)
	
	//准备语句
	sqlite3_stmt * stmt
	ret = 记录集3_语句准备16(db, "INSERT INTO xcgui(name, age) VALUES (?, ?)", -1, &stmt, NULL)
	如果 (SQLITE_OK != ret)
		调试输出("SQL error:", 数据库3_取错误信息(db))
		记录集3_释放(stmt)
		数据库3_关闭(db)
		返回
	
	记录集3_置文本16(stmt, 1, "小白1", -1, NULL)
	记录集3_置整型(stmt, 2, 20)
	记录集3_执行语句(stmt)
	
	记录集3_重置(stmt)

	记录集3_置文本16(stmt, 1, "小白2", -1, NULL)
	记录集3_置整型(stmt, 2, 22)
	记录集3_执行语句(stmt)

	记录集3_释放(stmt)
	
	测试_查询(db)
	数据库3_关闭(db)
	
函数  空类型 测试_查询(sqlite3* db)	
	//准备语句
	sqlite3_stmt * stmt
	整型 ret = 记录集3_语句准备16(db, "SELECT * FROM xcgui", -1, &stmt, NULL)
	如果 (SQLITE_OK != ret)
		调试输出("SQL error:", 数据库3_取错误信息(db))
		记录集3_释放(stmt)
		返回
	//执行语句
	循环 (SQLITE_ROW == 记录集3_执行语句(stmt))
		调试输出(记录集3_取列名称16(stmt, 0), ":", 记录集3_取列文本16(stmt, 0))
		调试输出(记录集3_取列名称16(stmt, 1), ":", 记录集3_取列文本16(stmt, 1))
		调试输出(记录集3_取列名称16(stmt, 2), ":", 记录集3_取列文本16(stmt, 2))
	记录集3_释放(stmt)

函数  空类型 测试_删除(sqlite3* db)
	//准备语句
	sqlite3_stmt * stmt
	整型 ret = 记录集3_语句准备16(db, "DELETE FROM xcgui", -1, &stmt, NULL)
	如果 (SQLITE_OK != ret)
		调试输出("SQL error:", 数据库3_取错误信息(db))
		记录集3_释放(stmt)
		return
	ret = 记录集3_执行语句(stmt)
	如果 (SQLITE_DONE != ret)
		调试输出("SQL error:", 数据库3_取错误信息(db))
	ret = 记录集3_释放(stmt)	

函数 整型 入口函数_窗口()
	//测试_exec()
	//测试_语句()
	测试_绑定()
	返回 0
