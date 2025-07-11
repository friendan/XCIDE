函数 test()
	文本型 path = "C:\\windows\\explorer.exe"
	文本型 ver = 文件_取文件版本(path)
	调试输出(ver)
	返回

函数 test2()
	文本型  path = "C:\\Windows"
	文本型  new_path = 目录_处理(path)
	调试输出(new_path)
	返回

函数 test3()
	逻辑型 ret = 目录_创建("C:\\1\\2\\3")
	调试输出(ret)
	返回

函数 test4()
	逻辑型 ret = 目录_是否存在("C:\\Windows\\")
	逻辑型 ret2 = 目录_是否存在("C:\\Windows")
	调试输出(ret)
	调试输出(ret2)
	返回

函数 test5()
	逻辑型 ret = 目录_复制("D:\\1\\3\\4", "D:\\1\\2\\4")
	调试输出(ret)
	返回

函数 test6()
	逻辑型 ret = 目录_定位("d:\\1.txt")
	调试输出(ret)
	返回

函数 test7()
	逻辑型 ret = 目录_改名("d:\\1", "d:\\2")
	调试输出(ret)
	返回

函数 test8()
	目录_更新("d:\\1", "d:\\2")
	返回

函数 test9()
	文本型 ret = 目录_获取完整路径名称("1.txt")
	调试输出(ret)
	返回

函数 test10()
	逻辑型 ret = 目录_检查系统属性("C:\\Windows")
	调试输出(ret)
	返回

函数 test11()
	整型 cslid = 23
	文本型 ret = 目录_检索文件的显示名称(cslid)
	调试输出(ret)
	返回

函数 test12()
	目录_浏览()
	返回

函数 test13()
	CXVector<CXText> retList
	整型 ret = 目录_枚举子目录("C:\\", retList, 真)

	变量循环 文本型 item : retList
		调试输出(item)

	返回

函数 test14()
	逻辑型 ret = 目录_是否符合规范("c:\\Windows")
	调试输出(ret)
	返回 

函数 test15()
	逻辑型 ret = 目录_删除目录("D:\\1")
	调试输出(ret)
	返回

函数 test16()
	目录_清空("d:\\2")
	返回

函数 test17()
	文本型 ret = 目录_取system32目录()
	调试输出(ret)

	ret = 目录_取Windows目录()
	调试输出(ret)

	ret = 目录_取x86系统目录()
	调试输出(ret)
	返回

函数 test18()
	CSysDateTime ret = 目录_取创建时间("c:\\windows")
	
	调试输出(到文本(ret.取年()))
	返回

函数 test19()
	int ret = 目录_取大小("D:\\2")
	调试输出(到文本(ret))
	返回

函数 test20()
	文本型 ret = 目录_取当前目录()
	调试输出(ret)
	返回

函数 test21()
	文本型 ret = 目录_取父路径("c:\\windows\\")
	调试输出(ret)
	返回

函数 test22()
	文本型 ret = 目录_取临时目录()
	调试输出(ret)

	返回

函数 test23()
	文本型 ret = 目录_取尾部目录名或文件名("c:\\windows")
	调试输出(ret)
	返回


函数 test24()
	int ret = 目录_取文件数("C:\\windows")
	调试输出(到文本(ret))
	返回

函数 test25()
	文本型 ret = 目录_取桌面目录()
	调试输出(ret)
	返回

函数 test26()
	int ret = 目录_取子目录数("C:\\windows")
	调试输出(到文本(ret))
	返回

函数 test27()
	逻辑型 ret = 目录_是否为空("C:\\windows")
	调试输出(ret)
	返回

函数 test28()
	目录_同步更新("D:\\2", "D:\\1")
	返回

函数 test29()
	文件_定位("D:\\2\\444.txt")
	返回

函数 test30()
	文件_改名("D:\\2\\444.txt", "D:\\2\\433.txt")
	返回

函数 test31()
	文件_复制("D:\\2\\433.txt", "D:\\1\\443.txt")
	返回

函数 test32()
	文件_删除到回收站("D:\\1\\443.txt")
	返回

函数 test33()
	文本型 ret = 文件_取扩展名("D:\\2\\433.txt")
	调试输出(ret)
	返回

函数 test34()
	逻辑型 ret = 文件_是否存在("D:\\2\\433.txt")
	调试输出(ret)
	返回

函数 test35()
	CXBytes fileByte
	int ret = 文件_读入文件("D:\\2\\433.txt", fileByte)
	调试输出(到文本(ret))
	返回

函数 test36()
	CXVector<CXText> rExportFuncList
	int ret = 文件_遍历PE导出表(A"C:\\Windows\\twain_32.dll", rExportFuncList)
	调试输出(到文本(ret))
	变量循环 文本型 item : rExportFuncList
		调试输出(item)

	返回

函数 test37()
	CXVector<CXText> rExportFuncList
	int ret = 文件_遍历PE导入表("C:\\Windows\\twain_32.dll", rExportFuncList)
	调试输出(到文本(ret))
	变量循环 文本型 item : rExportFuncList
		调试输出(item)
	返回

函数 test38()
	bool ret = ("C:\\Windows\\")
	调试输出(ret)
	返回

函数 test39()
	文本型 ret = 文件_取目录("C:\\Windows\\twain_32.dll")
	调试输出(ret)
	返回

函数 test40()
	bool ret = 文件_创建("D:\\2.txt", 10)
	调试输出(ret)
	返回

函数 test41()
	bool ret = 文件_创建文件目录("D:\\1\\2\\3")
	调试输出(ret)
	返回

函数 test42()
	文本型 ret = 文件_到短文件名("C:\\Program Files\\Windows Defender\\ConfigSecurityPolicy.exe")
	调试输出(ret)
	//C:\PROGRA~1\WINDOW~1\ConfigSecurityPolicy.exe
	返回

函数 test43()
	CXVector<CXText> fileList = {"C:\\Program Files\\Windows Defender\\ConfigSecurityPolicy.exe"}
	调试输出(到文本(fileList.取大小()))
	bool ret = 文件_定位多个("C:\\Program Files\\Windows Defender", fileList)
	调试输出(ret)
	返回

函数 test44()
	bool ret = 文件_改扩展名("D:\\1.txt", ".rar")
	调试输出(ret)
	返回

函数 test45()
	bool ret = 文件_合并("D:\\1.txt", "D:\\2.txt")

	调试输出(ret)
	返回

函数 test46()
	文本型 ret = 文件_取MIME类型("D:\\1.txt")
	调试输出(ret)
	返回

函数 test47()
	文本型 ret = 文件_取尺寸("D:\\1.txt", 真)
	调试输出(ret)
	返回

函数 test48()
	字节集 bts
	int len = 文件_读入文件("D:\\1.zip", bts)
	文本型 lx
	int ret = 文件_取格式(bts, lx)
	调试输出(lx)
	返回

函数 test49()
	文本型 ret = 文件_取关联("*.txt")
	调试输出(ret)
	// %SystemRoot%\system32\NOTEPAD.EXE %1
	返回 

函数 test50()
	文本型 ret = 文件_取类型("C:\\Windows\\regedit.exe")
	调试输出(ret)
	返回 

函数 test51()
	文本型 ret = 文件_取路径盘符("c:\\windows")
	调试输出(ret)
	返回

函数 test52()
	正长整型 ret = 文件_取真实尺寸("D:\\1.zip")
	调试输出(到文本(ret))
	返回

函数 test53()
	文本型 ret = 文件_取文件名("D:\\1.zip", 真)
	调试输出(ret)
	返回

函数 test54()
	bool ret = 文件_去扩展名("1.zip")
	调试输出(ret)
	返回

函数 test55()
	int ret = 文件_删除某类文件("D:\\1", "*.txt")
	调试输出(到文本(ret))
	返回

函数 test56()
	bool ret = 文件_是否被占用("D:\\1.zip")
	调试输出(ret)
	返回

函数 test57()
	bool ret = 文件_是否为64位("D:\\regedit.exe")
	调试输出(ret)
	返回

函数 test58()
	bool ret = 文件_执行("regedit.exe")
	调试输出(ret)
	返回

函数 整型 入口函数()
	空类型 *ptr = 空
	COM初始化(ptr)
	调试输出("控制台程序")
	//test()
	//test2()
	//test3()
	//test4()
	//test5()
	//test6()
	//test7()
	//test8()
	//test9()
	//test10()
	//test11()
	//test12()
	//test13()
	//test14()
	//test15()
	//test16()
	//test17()
	//test18()
	//test19()
	//test20()
	//test21()
	//test22()
	//test23()
	//test24()
	//test25()
	//test26()
	//test27()
	//test28()
	//test29()
	//test30()
	//test31()
	//test32()
	//test33()
	//test34()
	//test35()
	//test36()
	//test37()
	//test38()
	//test39()
	//test40()
	//test41()
	//test42()
	//test43()
	//test44()
	//test45()
	//test46()
	//test47()
	//test48()
	//test49()
	//test50()
	//test51()
	//test52()
	//test53()
	//test54()
	//test55()

	//test56()
	//test57()
	test58()

	COM清理()

	返回 0



// [文档]<炫语言> 在线手册: http://www.xcgui.com/doc
// [视频]<炫语言> 入门教程: https://www.bilibili.com/video/BV1KM411h7KK
//
// [文档]<炫彩界面库> 最新在线文档: http://www.xcgui.com/doc-ui
// [视频]<炫彩界面库> 之火山PC: https://www.bilibili.com/video/BV15a411s7hK
// [视频]<炫彩界面库> 通用教程: https://www.bilibili.com/video/BV1kA411A71p/
//
// [商城]炫彩资源商城: http://mall.xcgui.com
//
// *新手尽量不要使用指针, 例如: 字符串使用"文本型", 函数参数若要返回值使用引用 "函数名(整型 &输入输出参数)",
//  内存使用"字节集"
//
//  文本型   双字节字符串  =  炫语言默认字符串类型  =  "字符串W"
//  文本型A  单字节字符串  =  易语言字符串类型     =  A"字符串A"
//  utf8字符串  = U"UTF8字符串"
//  A2W()   单字节字符串 转 双字节字符串
//  W2A()   双字节字符串 转 单字节字符串
//  A =  char    =  单字节
//  w =  wchar_t = 双字节 = UNICODE
//  两个文件中结构体类型互相包含导致冲突, 请将结构体定义移动到一个独立文件中
