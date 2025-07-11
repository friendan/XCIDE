类 CMainFrame
	//定义类成员变量
	HWINDOW 窗口句柄
	文本型 城市   //成员变量用来存储需要查询天气的城市
	逻辑型 是否定时发送 = 假   
	CURL网络传输类 获取天气  //实例化CURL对象
	创建OP对象 OP  //使用前必须实例化OP对象
	
	函数 整型 Run()
		逻辑型 bRes = 炫彩_加载资源文件("resource.res")   //加载资源文件
		窗口句柄 = (HWINDOW)炫彩_加载布局文件("main.xml", 0)   //加载布局文件
		HELE 下拉列表 = (HELE)炫彩_取对象从名称("list1")   //获取下拉列表元素
		组合框_创建数据适配器(下拉列表)
		组合框_添加项文本(下拉列表, "北京")
		组合框_添加项文本(下拉列表, "上海")
		组合框_置选择项(下拉列表, 0)
		//编辑框_添加文本((HELE) XC_GetObjectByName("list1"),"123456")
		
		元素_注册事件CPP(炫彩_取对象从名称("list1"), XE_COMBOBOX_SELECT, &CMainFrame::OnComboBoxSelect) //下拉列表框选择事件绑定
		元素_注册事件CPP(炫彩_取对象从名称("btn1"), XE_BNCLICK, &CMainFrame::OnBtnClick) //按钮单击事件绑定
		元素_注册事件CPP(炫彩_取对象从名称("btn2"), XE_BNCLICK, &CMainFrame::OnBtnClick2) //按钮单击事件绑定
		窗口_注册事件CPP(窗口句柄, XWM_XC_TIMER, &CMainFrame::OnWndXCTimer)    //窗口定时器事件绑定
		
		窗口_启用允许最大化(窗口句柄, 假)  //禁止窗口最大化
		编辑框_启用自动换行((HELE)XC_GetObjectByName("return1"), 真)  
		整型 状态 = 获取天气.全局初始化CURL()   //必须全局初始化 且返回0代表初始化成功
		调试输出(状态)
		
		wchar_t   temp[256] = {0}   //定义临时变量
		编辑框_取文本((HELE)XC_GetObjectByName("bjk1"), temp, 1024)  //取编辑框内容放入变量
		城市 = (CXText)temp + "101010100.html"   //强转为文本类型
		调试输出(城市)
		
		//EVENT
		窗口_调整布局(窗口句柄)   //窗口调整布局
		窗口_显示(窗口句柄, SW_SHOW)
		返回 0 
		
	函数 int  OnComboBoxSelect(int iItem, BOOL* pbHandled)   //下拉列表框的选择事件触发的函数
		调试输出(组合框_取项文本((HELE)XC_GetObjectByName("list1"), iItem, 0))
		wchar_t   temp[256] = {0}
		如果 iItem == 0
			编辑框_取文本((HELE)XC_GetObjectByName("bjk1"), temp, 1024)
			调试输出(temp)
			城市 = (CXText)temp + "101010100.html"
			调试输出(城市)
		如果 iItem == 1		
			编辑框_取文本((HELE)XC_GetObjectByName("bjk1"), temp, 1024)
			调试输出(temp)
			城市 = (CXText)temp + "101020100.html"
			调试输出(城市)
		返回 0
	
	函数 int  OnBtnClick(BOOL* pbHandled)  //采集一次按钮单击事件确认是执行采集天气还是采集天气发送qq都执行
		如果 按钮_是否选中((HELE)XC_GetObjectByName("sky"))&&按钮_是否选中((HELE)XC_GetObjectByName("sendqq")) == 假
			天气()
			
		如果 按钮_是否选中((HELE)XC_GetObjectByName("sky"))&&按钮_是否选中((HELE)XC_GetObjectByName("sendqq"))
			天气qq()
		返回 0
	
	函数 int  OnBtnClick2(BOOL* pbHandled) //定时发送按钮单击事件确认是执行采集天气还是采集天气发送qq都执行
		如果 是否定时发送 == 假
			窗口_置炫彩定时器(窗口句柄, 123321, 5000)  //测试5秒一发送1000毫秒=1秒，可自行修改
			是否定时发送 = 真
		否则
			窗口_关闭炫彩定时器(窗口句柄, 123321)
			是否定时发送 = 假	
		返回 0
	
	函数 int  OnWndXCTimer(UINT nTimerID, BOOL* pbHandled)   // //窗口定时器事件绑定函数
		如果 nTimerID == 123321
			调试输出("time")
			天气qq()
		返回 0

	函数  void  天气()   //获取天气的方法
		CURL* curl句柄 = 获取天气.初始化CURL句柄()
		调试输出(curl句柄)
		调试输出(城市)
		获取天气.置地址(W2A(城市))
		逻辑型 访问是否成功 = 获取天气.执行访问()
		调试输出(访问是否成功)
		调试输出(获取天气.取响应内容())
		文本型 结果 = U2W(获取天气.取响应内容())
		编辑框_删除行((HELE)XC_GetObjectByName("return1"), 0)
		编辑框_插入文本((HELE)XC_GetObjectByName("return1"), 0, 0, 结果)
		//XEle_RedrawEle((HELE)XC_GetObjectByName("return1"))
		元素_重绘((HELE)XC_GetObjectByName("return1"))	
		编辑框_置选择((HELE)XC_GetObjectByName("return1"), 0, 0, 0, 编辑框_取内容长度((HELE)XC_GetObjectByName("return1")))
		编辑框_剪贴板复制((HELE)XC_GetObjectByName("return1"))
		获取天气.清理()	
		
	函数 void 天气qq()   //获取天气并发送QQ的方法
		CURL* curl句柄 = 获取天气.初始化CURL句柄()
		调试输出(curl句柄)
		调试输出(城市)
		获取天气.置地址(W2A(城市))
		逻辑型 访问是否成功 = 获取天气.执行访问()
		调试输出(访问是否成功)
		文本型 结果 = U2W(获取天气.取响应内容())
		调试输出(结果)
		编辑框_删除行((HELE)XC_GetObjectByName("return1"), 0)
		编辑框_插入文本((HELE)XC_GetObjectByName("return1"), 0, 0, 结果)
		//XEle_RedrawEle((HELE)XC_GetObjectByName("return1"))
		元素_重绘((HELE)XC_GetObjectByName("return1"))	
		编辑框_置选择((HELE)XC_GetObjectByName("return1"), 0, 0, 0, 编辑框_取内容长度((HELE)XC_GetObjectByName("return1")))
		编辑框_剪贴板复制((HELE)XC_GetObjectByName("return1"))
		获取天气.清理()
				
		//下面将天气信息发送到指定QQ
		long  句柄 //定义long类型的变量  存放窗口句柄 ，注意OP的整形都是long类型的。
		OP.查找窗口1("", "我的Android手机", &句柄) //调用OP的查找窗口方法，并传入刚才定义的句柄变量的地址，会将结果记录在此变量中。单独打开需要转发的QQ窗口，查找此窗口的标题
		调试输出("获取的窗口句柄：")
		调试输出(句柄)
		long  结果1	//定义long类型的变量  存放设置窗口状态方法是否成功返回的结果 ，注意OP的整形都是long类型的。
		OP.置窗口状态(句柄, 12, &结果1)//调用OP的设置窗口状态　12恢复并激活　详细看模块备注，并传入刚才定义的变量地址，会将结果记录在此变量中
		OP.睡眠(500, &结果1)  //睡眠0.5秒
		OP.按住虚拟键2("ctrl", &结果1)
		OP.按下虚拟键2("v", &结果1)
		OP.弹起虚拟键2("ctrl", &结果1)
		OP.弹起虚拟键2("v", &结果1)
		OP.睡眠(500, &结果1)  //睡眠0.5秒
		OP.按住虚拟键2("ctrl", &结果1)
		OP.按下虚拟键2("enter", &结果1)
		OP.弹起虚拟键2("ctrl", &结果1)
		OP.弹起虚拟键2("enter", &结果1)
		OP.睡眠(1000, &结果1)  //睡眠1秒
		OP.置窗口状态(句柄, 2, &结果1)//调用OP的设置窗口状态　2最小化　详细看模块备注，并传入刚才定义的变量地址，会将结果记录在此变量中	

函数 整型  入口函数_窗口()   //程序运行的入口函数
	炫彩_初始化(真)
	CMainFrame  我的程序实例
	我的程序实例.Run()
	炫彩_运行()
	炫彩_退出()
	返回 0
