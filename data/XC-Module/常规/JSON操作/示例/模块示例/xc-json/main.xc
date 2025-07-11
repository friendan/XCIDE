//当数组成员为对象时
函数 访问数组成员()
	单文本型  rawJson = AR"({"a":[{"b":"34"}]})"
	JSON值类   root
	JSON读取类  reader //读取解析JSON
	如果 !reader.解析(rawJson, root)
		返回

	//方式1 通过取成员操作
	JSON值类 array_ = root.取对象(A"a")
	整型  count = array_.取成员数()
	计次循环 整型 i = 0; count //遍历数组成员
		JSON值类 obj = array_[i].取对象(A"b") //数组成员是对象
		调试输出(obj.到文本()) //转换为文本值

	//方式2 通过数组下标操作
	调试输出(array_[0][A"b"].到文本())
	
	//方式3 通过多级下标操作
	调试输出(root[A"a"][0][A"b"].到文本())
	调试输出("================")
	占位

函数 整型 入口函数_窗口()   //窗口程序入口
	访问数组成员()

	//单文本型 rawJson =A"{\"Age\": 20, \"Name\": \"colin\", \"obj\":{\"a\":1, \"b\":2}}"
	单文本型 rawJson = AR"({"Age": 20, "Name": "colin", "obj":{"a":1, "b":2}, "array":[1,2,3]})"
	//根节点
	JSON值类   root
	JSON读取类  reader //读取解析JSON
	如果 !reader.解析(rawJson, root)
		返回 0

	单文本型  ret_name = root.取文本(A"Name")
	单文本型  ret_age = root.取文本(A"Age")
	调试输出(ret_name)
	调试输出(ret_age)
	
	JSON值类 obj = root.取对象(A"obj")
	整型 a = obj.取整型(A"a")
	整型 b = obj.取整型(A"b")
	调试输出(a)
	调试输出(b)
	
	//直接访问数组成员
	JSON值类  array_1 = root[A"array"][1] 
	单文本型  ret_array_1 = array_1.到文本()
	调试输出(ret_array_1)

	//访问数组成员
	JSON值类  array_ = root.取对象(A"array")
	整型  count = array_.取成员数()
	计次循环 整型 i = 0; count
		调试输出(array_[i].到文本())

	返回 0
