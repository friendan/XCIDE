﻿窗口类  主窗口
函数 整型 WINAPI OnPopupModalWindow(逻辑型 *是否拦截)
	模态窗口类 模态窗口(200, 200, "模态窗口", 主窗口.取HWND())

	整型 nResult = 模态窗口.启动()
	调试输出("退出模态窗口:", nResult)
	返回 0

函数 整型 入口函数_窗口() 
	炫彩_初始化(真)       //初始化界面库
	主窗口.创建(0, 0, 300, 300, "xcgui-window", NULL, 炫彩窗口样式_默认)//创建窗口
	
	如果 主窗口._句柄
		按钮类 按钮2(20, 50, 80, 22, "模态窗口", 主窗口._句柄) //点击弹出模态窗口
		按钮2.注册事件C(元素事件_按钮点击, OnPopupModalWindow)
		
		主窗口.调整布局() //调整布局
		主窗口.显示(SW_SHOW)  //显示窗口
		炫彩_运行()
	炫彩_退出()
	返回 0

