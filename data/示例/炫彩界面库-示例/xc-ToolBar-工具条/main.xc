﻿函数 整型 入口函数_窗口()
	炫彩_初始化(真)       //初始化界面库
	窗口类 主窗口(0, 0, 400, 300, "xcgui-window", NULL, 炫彩窗口样式_默认)//创建窗口
	如果 主窗口._句柄
		工具条类  工具条(20, 50, 320, 28, 主窗口._句柄)
		工具条.添加背景填充(RGB(200, 200, 200), 255)
		按钮类  按钮1(0, 0, 60, 20, "Button1")
		按钮类  按钮2(0, 0, 60, 20, "Button2")
		按钮类  按钮3(0, 0, 60, 20, "Button3")
		按钮类  按钮4(0, 0, 60, 20, "Button4")
		按钮类  按钮5(0, 0, 60, 20, "Button5")
		
		工具条.插入元素(按钮1._句柄)
		工具条.插入元素(按钮2._句柄)
		工具条.插入元素(按钮3._句柄)
		工具条.插入元素(按钮4._句柄)
		工具条.插入元素(按钮5._句柄)
		
		主窗口.调整布局() //调整布局
		主窗口.显示(SW_SHOW)  //显示窗口
		炫彩_运行()
	炫彩_退出()
	返回 0
	