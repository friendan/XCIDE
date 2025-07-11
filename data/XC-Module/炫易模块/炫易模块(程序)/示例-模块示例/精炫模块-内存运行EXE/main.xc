
函数 整型 入口函数_窗口() //窗口程序入口函数, 程序启动优先进入此函数

	文件类  file_
	file_.打开只读("ConsoleApplication1.exe");
	字节集 data = file_.readDataBytes()

	程序_内存中运行EXE(data, 0, 0, 真)
	//程序_内存中运行EXE2(data, 0, 0, 真)
	//程序_内存中运行EXE线程方式(data)
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
