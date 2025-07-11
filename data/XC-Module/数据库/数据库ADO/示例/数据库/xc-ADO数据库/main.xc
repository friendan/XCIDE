#外部宏 LONG
函数 整型 入口函数_窗口()
	调试输出("控制台程序")
	COM初始化(NULL)
	
	ADO数据库类   ADO数据库
	ADO记录集类   ADO记录集
	如果 FALSE == ADO数据库.打开("Provider=Microsoft.ACE.OLEDB.12.0; Data Source=mydb.accdb", "", "", 0)
		返回 0
	
	如果 (FALSE == ADO记录集.打开("SELECT * FROM  table1", &ADO数据库, adOpenDynamic, adLockOptimistic, adCmdText))
		return 0;

	调试输出("-------------打印字段名:-------------")
	ADO字段集类 ADO字段集 = ADO记录集.取字段集()
	整型  字段数量 = ADO字段集.取成员数量()
	计次循环 LONG i = 0; 字段数量
		调试输出(ADO字段集.取成员(COM变体型(i)))
	
	调试输出("-------------打印数据:-------------")
	循环 FALSE == ADO记录集.是否尾记录之后()
		计次循环 LONG i = 0; 字段数量
			调试输出(ADO记录集.取列值(COM变体型(i)))
		ADO记录集.到下一个()
	
	ADO记录集.关闭()
	ADO数据库.关闭()
	COM清理()
	返回 0
