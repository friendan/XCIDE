﻿窗口类  主窗口
函数 空类型 创建列表树()
	列表树类  列表树(20, 40, 260, 240, 主窗口._句柄)
	列表树.创建数据适配器()
	列表树.启用展开(真)
	
	计次循环 整型 i = 0; 5
		列表树.插入项文本(文本组合("item-", i))
	列表树.插入项文本("item1-child", 1)
	列表树.插入项文本("item2-child", 2)
	
函数 整型 入口函数_窗口() 
	炫彩_初始化(真)     //初始化界面库
	主窗口.创建(0, 0, 300, 300, "xcgui-window", NULL, 炫彩窗口样式_默认)//创建窗口

	如果 主窗口._句柄
		创建列表树()
		
		主窗口.调整布局() //调整布局
		主窗口.显示(SW_SHOW)  //显示窗口
		炫彩_运行()
	炫彩_退出()
	返回 0

