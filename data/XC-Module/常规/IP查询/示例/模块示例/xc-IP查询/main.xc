

函数 整型 入口函数()
	Xdb xdb
	如果 xdb.载入_从文件(取运行目录() + "//ip2region.xdb")
		单文本型 regionA = xdb.搜索A(A"1.2.3.4")
		调试输出(regionA)
		文本型 region = xdb.搜索("1.2.3.4")
		调试输出(region)

	返回 0
