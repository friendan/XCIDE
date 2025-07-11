函数 整型 入口函数()
	XL工作簿类 book
	book.新建文件(XL文件类型_XLSX)
	
	XL工作表类 sheet = book.添加工作表("测试考勤表")
	XL格式类 边框格式 = book.添加格式()
	边框格式.边框样式(XL边框样式_细线)
	sheet.置单元格格式("a2", "ai38", 边框格式)
	sheet.置列宽("a", 10.2)
	sheet.置列宽("b", 4.1)
	sheet.置列宽("c", "ag", 2.4)
	sheet.置列宽("ah", "ai", 9)
	sheet.置行高(0, 35)
	sheet.置行高(1, 34)
	sheet.置行高(2, 37, 16)

	sheet.置单元格合并("a1", "ai1")
	XL字体类 font = book.添加字体()
	XL格式类 format = book.添加格式()
	format.字体(font)
	font.加粗(真)
	font.尺寸(18)
	format.水平对齐(XL水平对齐_居中对齐)
	format.垂直对齐(XL垂直对齐_居中对齐)
	sheet.置单元格文本("a1", "考勤表名称", format)

	
	for int i = 1; i < 36; i += 4
		sheet.置单元格文本(i + 1, 1, "上午")
		sheet.置单元格文本(i + 2, 1, "中午")
		sheet.置单元格文本(i + 3, 1, "下午")
		sheet.置单元格文本(i + 4, 1, "晚上")
		sheet.置单元格合并(i + 1, i + 4, 0, 0)
		sheet.置单元格合并(i + 1, i + 4, 33, 33)
		sheet.置单元格合并(i + 1, i + 4, 34, 34)
	
	format = book.添加格式(边框格式)
	format.水平对齐(XL水平对齐_居中对齐)
	format.垂直对齐(XL垂直对齐_居中对齐)
	for int n = 1 ; n <= 31; n++
		sheet.置单元格数值(1, n + 1, n, format)
	sheet.置单元格文本("b2", "时间", format)
	sheet.置单元格文本("ah2", "天数", format)
	sheet.置单元格文本("ai2", "备注", format)
	format = book.添加格式(边框格式)
	format.自动换行(真)
	format.对角线边框(XL对角线边框_右斜)
	format.对角线边框样式(XL边框样式_细线)
	sheet.置单元格文本("a2", "            日期\r\n 姓名", format)
	sheet.置单元格文本("a39", " 填表：                                                   复核：                                                   审核：                                                   日期：")

	sheet.横向模式(真)
	sheet.置打印适合页面()
	
	book.保存文件("测试考勤表.xlsx")
	book.释放()
	
	调试输出("完成----")
	返回 0

//炫语言手册:   http://www.xcgui.com/doc/

//动态库入口函数参考: https://docs.microsoft.com/zh-cn/windows/win32/dlls/dllmain?redirectedfrom=MSDN

//调试快捷键:   F5: 编译和调试, F7: 编译, F9:下断点, F10: 单步, F11: 步入
//函数参数展开: Ctrl+回车: 展开收缩, 表格内回车:收缩, ESC: 取消展开
//TAB:          缩进
//TAB + SHIFT: 减少缩进
//"/":      注释/取消注释
//Ctrl + G: 跳转到指定行
//Ctrl + F: 搜索和替换
//F12:      跳转到定义
//Alt + ↑: 向上交换行
//Alt + ↓: 向下交换行
//home:     移到光标到行首
//end:      移动光标到行尾
//双击打开项目: 系统设置->关联炫彩文件类型

//关于文本编码
//  首先你确定他是一个字符串
//  如果你是二进制数据存在字节集里, 那么显示字符串是乱码的
//  取地址 是单字符型;
//  首先你要指定你字节集里存的是不是文本
//  是单字节 的 还是双字节的
//  文本文件 读到内存 都是单字节字符串 char*;
//  你需要把他转换为 unicode 双字节字符串 wchar_t*
//  调试输出A 是单字节文本
//  你用 单文本型
//  不然你要转换下
//  文本文件一般都是单字节
//  A 与 W 转换
//  ascii和unicode都不清楚的吗
//  A2W()
//  W2A()
//  我一般都用 双字节 字符处理, 比较简单
//  因为中文 如果单字节 会占多个字节
//  还得判断
//
//  文本型    双字节字符串  =  A2W_(data.取地址(),-1)
//  A2W() 就是把易那种字符串 转换为 unicode
//  分割文本, 你就用宽字符串  w wchar_t
//  
//  A =  char  =  单字节
//  w = wchar_t = 双字节 = UNICODE
//
//  你看系统API 都有两个版本
//  CreateWindowA()
//  CreateWindowW()
//  
//  炫语言代码文件是utf-8, 默认编译没有加utf-8选项, 所以ascii文本运行输入任然是ascii文本
//
//  两个文件中结构体类型互相包含导致冲突, 请将结构体定义移动到一个独立文件中
