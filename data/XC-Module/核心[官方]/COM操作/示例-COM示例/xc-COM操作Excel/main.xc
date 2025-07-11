类 COM事件Excel 继承 COM事件类
	函数 虚函数 void 事件响应(整型 dispIdMember, COM变体型* pArrayParams, COM变体型& retResult)
		调试输出(dispIdMember, 取名称(dispIdMember))

//打开已存在的Excel文件
函数 打开Excel文件(COM对象类& Excel对象, COM对象类& 工作簿集, 文本型 文件名)
	工作簿集.方法("Open", 文件名)
	COM对象类  行列对象 = Excel对象.取属性("ActiveCell")
	占位

//COM变体型 演示
函数  演示COM变体型(COM对象类& 工作簿对象)
	//方式1 已知结果为字符串
	文本型  工作簿名称 = 工作簿对象.取属性("Name")
	调试输出(工作簿名称)

	//方式2 判断结果是否为OLE字符串
	COM变体型  结果 = 工作簿对象.取属性("Name")
	如果 COM数据类型_OLE字符串 == 结果.取类型()
		工作簿名称 = 结果.取文本指针()
		调试输出(工作簿名称)
	占位

函数 整型 入口函数_窗口()
	COM初始化(NULL)
	COM对象类   Excel对象
	如果 FALSE == Excel对象.创建("Excel.Application")
		返回 0

	//错误码使用演示
	COM返回值  错误码 = Excel对象.取错误码()
	如果 !COM是否成功(错误码)
		返回 0
	如果 COM是否失败(错误码)
		返回 0
	COM智能指针<COM事件Excel> Excel事件 = new COM事件Excel
	Excel事件->挂接(Excel对象, "{00024413-0000-0000-C000-000000000046}")

	如果 FALSE == Excel对象.置属性("Visible", (bool)TRUE)
		返回 0

	COM对象类  工作簿集 = Excel对象.取属性("Workbooks")
	//打开Excel文件(Excel对象, 工作簿集, "C:\\Users\\ABC\\Desktop\\Book1.xlsx")

	COM对象类  工作簿对象(工作簿集.方法("Add"))
	演示COM变体型(工作簿对象)

	COM对象类  行列对象 = Excel对象.取属性("ActiveCell")
	行列对象.置属性("FormulaR1C1", "123456")

	Excel对象.方法("Quit")
	Excel事件->清理()
	COM清理()
	返回 0
