函数 整型 WINAPI OnScrollViewScrollH(整型 pos, 逻辑型 *是否拦截)
	调试输出("OnScrollViewScrollH()", pos )
	返回 0

函数 整型 WINAPI OnScrollViewScrollV(整型 pos, 逻辑型 *是否拦截)
	调试输出("OnScrollViewScrollV()", pos )
	返回 0

函数 整型 入口函数_窗口()
	炫彩_初始化(真)       //初始化界面库
	窗口类 主窗口(0, 0, 300, 300, "xcgui-window", NULL, 炫彩窗口样式_默认)//创建窗口
	如果 主窗口._句柄
		滚动视图类  滚动视图(20,50, 200, 200, 主窗口._句柄)
		滚动视图.置视图大小(300,300)
		
		按钮类  按钮1(20,10, 100,20, "button1", 滚动视图._句柄)
		按钮类  按钮2(20,40, 100,20, "button2" ,滚动视图._句柄)
		按钮类  按钮3(20,70, 100,20, "button3", 滚动视图._句柄)
		
		滚动视图.注册事件C(元素事件_滚动视图水平滚动, OnScrollViewScrollH) //注册事件 水平滚动
		滚动视图.注册事件C(元素事件_滚动视图垂直滚动, OnScrollViewScrollV) //注册事件 垂直滚动
		
		主窗口.调整布局() //调整布局
		主窗口.显示(SW_SHOW)  //显示窗口
		炫彩_运行()
	炫彩_退出()
	返回 0

