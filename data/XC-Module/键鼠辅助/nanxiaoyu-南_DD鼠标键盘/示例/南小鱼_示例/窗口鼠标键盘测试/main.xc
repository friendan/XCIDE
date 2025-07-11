

DD鼠标键盘类 dd 

类 我的主窗口类 继承 窗口类 
	[绑定信息] //IDE生成的UI绑定信息(UI变量,事件), 支持手动修改, 可收缩隐藏
		[按钮类, _Button, "Button"]
			[XE_BNCLICK, 事件_点击_Button, 0]
		[按钮类, _BUTTON2, "BUTTON2"]
			[XE_BNCLICK, 事件_点击_BUTTON2, 0]
		[按钮类, _button3, "button3"]
			[XE_BNCLICK, 事件_点击_button3, 0]
		[按钮类, _button4, "button4"]
			[XE_BNCLICK, 事件_点击_button4, 0]
		[按钮类, _button5, "button5"]
			[XE_BNCLICK, 事件_点击_button5, 0]
		
	//窗口类初始化, 自动处理关联的布局文件及绑定变量和注册事件
	函数 整型 运行(文本型 窗口布局文件 = "main.xml", 炫彩句柄 父句柄=0)
		显示(TRUE)
		返回 0
	函数 整型  事件_点击_Button(逻辑型* 是否拦截)
		
		dd.DD_movR(-10,0) //相对移动
		dd.DD鼠标绝对移动(100, 100)//绝对移动
		整型 DDCODE = dd.DD_VK键值转DD键值(91)
		调试输出(DDCODE)


		
		
		返回 0
	函数 整型  事件_点击_BUTTON2(逻辑型* 是否拦截)
		// << "ctrl+alt+del";
		
		dd.DD_key(600, 1)//;  //600 == L.CTRL down
		dd.DD_key(602, 1)//;  //602 == L.ALT   down
		dd.DD_key(706, 1)//;  //706 == DEL   down
		dd.DD_key(706, 2)//;
		dd.DD_key(602, 2)//; 	 //up
		dd.DD_key(600, 2)//;

		返回 0
	函数 整型  事件_点击_button3(逻辑型* 是否拦截)
		//  "Keyboard L.win";
		int ddcode = 601//;		//Left.win == 601 in ddcode	   
		ddcode = dd.DD_todc(91)//;
		dd.DD_key(ddcode, 1)//;
		Sleep(1)//;					//may, delay 50ms
		dd.DD_key(ddcode, 2)//;

		返回 0
	函数 整型  事件_点击_button4(逻辑型* 是否拦截)
		
		dd.DD鼠标绝对移动(300, 300)//绝对移动
		dd.DD鼠标按键(1)
		dd.DD鼠标按键(2)
		dd.DD_str(A"MyEmail@aa.bb.cc !@#$")

		返回 0
	函数 整型  事件_点击_button5(逻辑型* 是否拦截)
		dd.DD鼠标相对移动(-300, -330)//
		
		dd.DD鼠标按键(1)
		Sleep(50)//;					//may, delay 50ms
		dd.DD鼠标按键(2)
		Sleep(100)//;
		计次循环 整型 i = 0; 10
			dd.DD_whl(2)

			Sleep(10)//;
			//dd.DD_whl(2)
			占位

		计次循环 整型 i = 0; 10
			dd.DD_whl(1)
			Sleep(10)//;
			//dd.DD_whl(2)
			占位
		

		返回 0
	
	
	

函数 整型 入口函数_窗口()
	炫彩_初始化(TRUE)
	炫彩_加载资源文件("resource.res")
	文本型 路径 = 取运行目录() 
	我的主窗口类  我的主窗口
	我的主窗口.运行()
	文本型 test
	计次循环 整型 i = 0; 50
		test = test+文本取随机字符(6) +"\n"
		

		占位
	
	
	//元素句柄 元素句柄_
	
	//元素句柄_ = (HELE)XC_GetObjectByName("编辑框1")
	//编辑框_添加文本(元素句柄_, test + "\n")
	//我的主窗口._编辑框1.置文本(test + "\n")

	//{启动时初始化虚拟键鼠功能
	#嵌入代码
	#ifdef _WIN64
	路径 = 路径 + L"\\dd32695.x64.dll";  //L"\\DD94687.64.dll"
	#else
	路径 = 路径 + L"\\dd32695.x32.dll";
	#endif
	#嵌入代码_结束
	调试输出(路径)

	整型 st = dd.DD初始化(路径)
	调试输出(st)


	如果 st != 1
		消息框("虚拟鼠标键盘初始化失败,虚拟键鼠功能无法使用")
		占位
	//}启动时初始化虚拟键鼠功能

	炫彩_运行()
	炫彩_退出()
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
