﻿函数 整型 入口函数_窗口() 
	炫彩_初始化(真)       //初始化界面库
	窗口类 主窗口(0, 0, 300, 300, "xcgui-window", NULL, 炫彩窗口样式_默认)//创建窗口
	如果 主窗口._句柄
		基础元素类  基础元素(20, 50, 100, 100, 主窗口._句柄) //点击弹出模态窗口
		
		主窗口.调整布局() //调整布局
		主窗口.显示(SW_SHOW)  //显示窗口
		炫彩_运行()
	炫彩_退出()
	返回 0

