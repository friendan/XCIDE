
函数 测试函数1()
	机读文本类 机读文本
	调试输出(A"S")
	机读文本.初始化()
	//机读文本.置音库("Microsoft Zira Desktop - English (United States)")
	机读文本.置音库("Microsoft Huihui Desktop - Chinese (Simplified)")

	//机读文本.置语速(5)
	//机读文本.置音量(200)
	//文本型  ret = 机读文本.置声调("你好,我是语音朗读机器人!", 0)
	//机读文本.朗读(ret)
	//机读文本.朗读("你好,我是语音朗读机器人!")
	机读文本.朗读("Hello, how are you?")

//	调试输出(机读文本.取数量())
	机读文本.销毁()
	调试输出(A"N")


函数 整型 入口函数_窗口()
	测试函数1()
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
