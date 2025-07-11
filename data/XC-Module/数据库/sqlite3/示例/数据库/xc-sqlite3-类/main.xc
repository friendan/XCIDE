
函数 整型 callback(空类型* NotUsed, 整型 argc, 字符型A**argv, 字符型A**azColName)
	计次循环 整型 i = 0; argc
		如果 argv[i]
			调试输出(azColName[i], ":", argv[i])
		否则
			调试输出(azColName[i], ":NULL")
	返回 0
	
函数 空类型 测试_exec()
	Sqlite3数据库类  db
	整型 ret = db.打开("test.db")
	如果 SQLITE_OK != ret
		调试输出("不能打开数据库:", db.取错误信息())
		返回
	//创建表
	Sqlite3错误  err
	ret = db.执行SQL(A"CREATE TABLE IF NOT EXISTS xcgui(id integer PRIMARY KEY AUTOINCREMENT, name text NOT NULL,age integer NOT NULL)", callback, 0, err)
	如果 (ret != SQLITE_OK)
		调试输出("SQL error:", err)
		返回
	//插入
	ret = db.执行SQL(A"INSERT INTO xcgui(name, age) VALUES ('大明', 22)", callback, 0, err)
	如果 (ret != SQLITE_OK)
		调试输出("SQL error:", err)
		返回
	//查询
	ret = db.执行SQL(A"SELECT * FROM xcgui", callback, 0, err)
	如果 (ret != SQLITE_OK)
		调试输出("SQL error:", err)
		返回
	
函数 空类型 测试_语句()
	Sqlite3数据库类 db
	整型 ret = db.打开("test.db")
	如果 SQLITE_OK != ret
		调试输出("不能打开数据库:", db.取错误信息())
		返回	
	//准备语句
	Sqlite3记录集类  stmt
	ret = stmt.准备(db, "SELECT * FROM xcgui", - 1, NULL)
	如果 (SQLITE_OK != ret)
		调试输出("SQL error:", db.取错误信息())
		返回

	//执行语句
	循环(SQLITE_ROW == stmt.单步())
		调试输出(stmt.取列名(0), ":", stmt.取列文本(0))
		调试输出(stmt.取列名(1), ":", stmt.取列文本(1))
		调试输出(stmt.取列名(2), ":", stmt.取列文本(2))
	//ret = sqlite3_语句重置(stmt)  调用[重置语句]后可再次循环 [语句单步]
	
函数  空类型 测试_绑定()
	Sqlite3数据库类  db
	整型 ret = db.打开("test.db")
	如果 SQLITE_OK != ret
		调试输出("不能打开数据库:", db.取错误信息())
		返回
	
	测试_删除(db)
	测试_查询(db)
	
	//准备语句
	Sqlite3记录集类  stmt
	ret = stmt.准备(db, "INSERT INTO xcgui(name, age) VALUES (?, ?)", - 1, NULL)
	如果 (SQLITE_OK != ret)
		调试输出("SQL error:", db.取错误信息())
		返回

	stmt.绑定文本(1, "小白1", - 1, NULL)
	stmt.绑定整型(2, 20)
	stmt.单步()
	
	stmt.重置()

	stmt.绑定文本(1, "小白2", - 1, NULL)
	stmt.绑定整型(2, 22)
	stmt.单步()

	测试_查询(db)		
	
函数 空类型 测试_查询(Sqlite3数据库类 &db)	
	//准备语句
	Sqlite3记录集类 stmt
	整型 ret = stmt.准备(db, "SELECT * FROM xcgui", - 1, NULL)
	如果 (SQLITE_OK != ret)
		调试输出("SQL error:", db.取错误信息())
		返回
	//执行语句
	循环(SQLITE_ROW == stmt.单步())
		调试输出(stmt.取列名(0), ":", stmt.取列文本(0))
		调试输出(stmt.取列名(1), ":", stmt.取列文本(1))
		调试输出(stmt.取列名(2), ":", stmt.取列文本(2))

函数 空类型 测试_删除(Sqlite3数据库类 &db)
	//准备语句
	Sqlite3记录集类 stmt
	整型 ret = stmt.准备(db, "DELETE FROM xcgui", - 1, NULL)
	如果 (SQLITE_OK != ret)
		调试输出("SQL error:", db.取错误信息())
		返回
	ret = stmt.单步()
	如果 (SQLITE_DONE != ret)
		调试输出("SQL error: ", db.取错误信息())

函数 整型 入口函数_窗口()
	//测试_exec()
	//测试_语句()
	测试_绑定()
	返回 0