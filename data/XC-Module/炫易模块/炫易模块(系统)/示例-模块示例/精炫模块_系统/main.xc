
函数 test1()
	如果 系统_是否64位() == 真
		调试输出("64位系统")
		返回
	调试输出("32位系统")
	返回

函数 test2()
	如果 系统_取系统类型() == 常量_系统类型_Windows
		调试输出("windows")
	返回


函数 test3()
	int x = 0
	int y = 0
	x = 系统_取屏幕宽度()
	y = 系统_取屏幕高度()

	调试输出("x=" + 到文本(x) + " y=" + 到文本(y))
	//[线程:15304] x=1920 y=1080
	返回

函数 bool cmd_callback(const char *cmd)
	调试输出(cmd)
	返回 真

函数 test4()
	//CMD todo
	返回

函数 test5()
	注册表操作类 reg_class
	CXVector<CXText> ItemList
	int ret = reg_class.枚举子项("HKEY_CURRENT_USER\\Control Panel", ItemList)
	调试输出(到文本(ret))
	for CXText item : ItemList
		调试输出(item)
	返回

函数 test6()
	注册表操作类 reg_class
	CXVector<StructRegKey>List
	整型 ret = reg_class.枚举键名("HKEY_CURRENT_USER\\Control Panel\\Appearance", List)
	调试输出(到文本(ret))
	for StructRegKey item : List
		调试输出("键名:" + item.键名 + " 值:" + item.值 + " 类型:" + 到文本(item.类型))
	返回

函数 test7()
	注册表操作类 reg_class
	整型 ret = reg_class.取键名类型("HKEY_CURRENT_USER\\Environment", "OneDrive")

	调试输出(到文本(ret))
	如果 ret == 常量_注册表键类型_字符串值
		调试输出("字符串")
	返回

函数 test8()
	注册表操作类 reg_class
	逻辑型c ret = reg_class.是否存在("HKEY_CURRENT_USER\\Environment", "OneDrive")
	
	调试输出(到文本(ret))
	如果 ret
		调试输出("存在")
	返回

函数 test9()
	字节集 a
	字节型 b = 1
	a.置数据(&b, 1)

	注册表操作类 reg_class
	逻辑型c ret = reg_class.写入字节集("HKEY_CURRENT_USER\\XYYX\\KOOK", "isAutoRun", a, X_REG_BINARY)

	调试输出(到文本(ret))
	如果 ret
		调试输出("写入成功")
	返回

函数 test10()
	整型 type = 0
	注册表操作类 reg_class
	字节集 a = reg_class.取字节集("HKEY_CURRENT_USER\\XYYX\\KOOK", "isAutoRun", type)

	调试输出(到文本(a))
	调试输出(到文本(type))
	返回

函数 test11()
	整型 value = 3
	注册表操作类 reg_class
	逻辑型c a = reg_class.WriteDWORD("HKEY_CURRENT_USER\\SOFTWARE\\360\\360se6", "UsageStatsInSample", value)
	调试输出(到文本(a))
	返回

函数 test12()
	整型 value = 3
	注册表操作类 reg_class
	value = reg_class.取DWORD值("HKEY_CURRENT_USER\\SOFTWARE\\360\\360se6", "UsageStatsInSample")
	调试输出(到文本(value))
	返回

函数 test13()

	注册表操作类 reg_class
	逻辑型 ret = reg_class.写文本值("HKEY_CURRENT_USER\\SOFTWARE\\360", "app_tray_devicesid", "test")
	调试输出(到文本(ret))
	返回

函数 test14()
	注册表操作类 reg_class
	文本型 ret = reg_class.取文本值("HKEY_CURRENT_USER\\SOFTWARE\\360", "app_tray_devicesid")
	调试输出(ret)
	返回

函数 test15()
	注册表操作类 reg_class
	文本型 ret = reg_class.删除键("HKEY_CURRENT_USER\\XYYX\\KOOK", "isAutoRun")
	调试输出(ret)
	返回

函数 test16()
	void *ptr = 空
	COM初始化(ptr)
	系统_创建快捷方式("E:\\db.json", "C:\\Users\\peerless\\Desktop\\db.lnk")
	COM清理()
	返回

函数 整型 入口函数()
	//test1()
	//test2()
	//test3()
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
	test16()
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
