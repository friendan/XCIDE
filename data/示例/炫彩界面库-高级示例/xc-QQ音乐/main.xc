﻿类 我的主窗口类 继承 窗口类
	文本型  _布局文件= "main.xml"
	函数 整型 运行()
		置拖动边框大小(3,3,3,3)
		调整布局()
		显示(真)
		返回 0

函数 整型 入口函数_窗口()
	炫彩_初始化(真)
	#加载资源文件

	我的主窗口类  我的主窗口
	我的主窗口.运行()

	炫彩_运行()
	炫彩_退出()
	返回 0
