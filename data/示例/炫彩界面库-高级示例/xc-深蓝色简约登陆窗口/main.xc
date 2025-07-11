窗口类  主窗口
元素句柄   hLayoutContent = 0  //布局内容
元素句柄   hCurPanel = 0    //当前面板

函数 空类型 SwitchTab(文本型 strTy)
	如果 (hCurPanel)
		元素_销毁(hCurPanel)
	如果 ("登陆" == strTy)
		hCurPanel = (元素句柄)炫彩_加载布局文件("panel-login.xml", hLayoutContent)
		元素_置文本颜色((元素句柄)炫彩_取对象从名称("登陆"), 0xFFFFFFFF)
		元素_置文本颜色((元素句柄)炫彩_取对象从名称("注册"), 0xFF000000)
	否则
		hCurPanel = (元素句柄)炫彩_加载布局文件("panel-reg.xml", hLayoutContent)
		元素_置文本颜色((元素句柄)炫彩_取对象从名称("登陆"), 0xFF000000)
		元素_置文本颜色((元素句柄)炫彩_取对象从名称("注册"), 0xFFFFFFFF)
	主窗口.调整布局()
	//主窗口.重绘()

函数 整型 WINAPI OnBtnCheck_login(整型 bCheck, 逻辑型 *是否拦截)
	如果 (bCheck)
		调试输出("按钮-登陆")
		SwitchTab("登陆")
	返回 0

函数 整型 WINAPI OnBtnCheck_register(整型 bCheck, 逻辑型 *是否拦截)
	如果 (bCheck)
		调试输出("按钮-注册")
		SwitchTab("注册")
	返回 0

函数 整型 入口函数_窗口()   //窗口程序入口
	炫彩_初始化(真)       //初始化界面库
	炫彩_启用自动重绘UI(真)
	#加载资源文件

	主窗口._句柄 = (窗口句柄)炫彩_加载布局文件("main.xml", 0)
	如果 (主窗口._句柄)
		hLayoutContent = (元素句柄)炫彩_取对象从名称("content")
		SwitchTab("登陆")
		元素_注册事件C((元素句柄)炫彩_取对象从名称("登陆"), 元素事件_按钮选中, OnBtnCheck_login)
		元素_注册事件C((元素句柄)炫彩_取对象从名称("注册"), 元素事件_按钮选中, OnBtnCheck_register)
		
		主窗口.调整布局() //调整布局
		主窗口.显示(SW_SHOW) //显示窗口
		炫彩_运行()
	炫彩_退出()
	返回 0
