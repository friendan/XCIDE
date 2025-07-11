
函数 整型 入口函数_窗口()
	炫彩_初始化(真)       //初始化界面库
	窗口类 主窗口(0, 0, 400, 300, "xcgui-window", NULL, 炫彩窗口样式_默认)//创建窗口
	如果 主窗口._句柄
		日期时间类  日期时间(20, 50, 120, 26, 主窗口._句柄)
		日期时间.置样式(0)
		日期时间.注册事件C(元素事件_日期时间弹出月历, OnDateTimePopupMonthCal)
		日期时间.注册事件C(元素事件_日期时间退出月历, OnDateTimeExitMonthCal)
		日期时间.注册事件C(元素事件_日期时间改变, OnDateTimeChange)

		主窗口.调整布局() //调整布局
		主窗口.显示(SW_SHOW)  //显示窗口
		炫彩_运行()
	炫彩_退出()
	返回 0
函数 整型 WINAPI OnDateTimeChange(逻辑型 *是否拦截)
	调试输出("OnDateTimeChange()")
	返回 0
函数 整型 WINAPI OnDateTimeExitMonthCal(窗口句柄 hMonthCalWnd, 元素句柄 hMonthCal, 逻辑型 *是否拦截)
	调试输出("OnDateTimeExitMonthCal")
	返回 0
函数 整型 WINAPI OnDateTimePopupMonthCal(窗口句柄 hMonthCalWnd, 元素句柄 hMonthCal, 逻辑型 *是否拦截)
	调试输出("OnDateTimePopupMonthCal")
	返回 0
