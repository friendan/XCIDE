函数 整型  入口函数_窗口()
	//CDoc  doc
	XML文档类  文档
	//文本型   str =  "<root name=\"abc\" >123</root>"
	//xml_parse_result result = doc.load_buffer(str, str.大小())
	//xml_parse_result result = doc.load_file("test.xml");

	XML解析结果类  XML解析结果 = 文档.载入文件("test.xml")
	如果 空 != XML解析结果.状态
		调试输出("失败")
		返回 0

	XML节点类 根节点 = 文档.第一个子节点()
	如果 空 == 根节点
		返回 0

	XML属性类 属性 = 根节点.属性("name")
	如果 空 == 属性
		返回 0

	常量 wchar_t*  p = 属性.值()
	调试输出(p)
	
	XML节点类 子节点 = 根节点.第一个子节点()
	循环 子节点
		p = 子节点.名称()
		调试输出(p)
		
		属性 = 子节点.属性("name")
		如果 属性
			p = 属性.值()
			调试输出(p)
			
		XML文本类  文本类 = 子节点.文本()
		如果 文本类
			p = 文本类.获取()
			调试输出(p)
		
		子节点 = 子节点.下一个()
	返回 0