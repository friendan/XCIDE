﻿函数 整型 WINAPI OnCalendarChange(逻辑型 *是否拦截)
	调试输出("OnCalendarChange")
	返回 0

函数 整型 入口函数_窗口()
	炫彩_初始化(真)       //初始化界面库
	窗口类 主窗口(0, 0, 400, 300, "xcgui-   window", NULL, 炫彩窗口样式_默认)//创建窗口
	如果 主窗口._句柄
		月历卡片类  月历卡片(20,40,290,240, 主窗口._句柄)
		月历卡片.注册事件C(元素事件_月历改变, OnCalendarChange)
	
		主窗口.调整布局() //调整布局
		主窗口.显示(SW_SHOW)  //显示窗口
		炫彩_运行()
	炫彩_退出()
	返回 0
