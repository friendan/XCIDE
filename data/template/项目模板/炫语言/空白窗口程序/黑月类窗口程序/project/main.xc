﻿应用程序类 App
窗口类 主窗口

函数 整型 主窗口_创建完毕事件(HWND hWnd)
	//在这里创建控件或其他操作
	返回 0
函数 整型 入口函数_窗口() //窗口程序入口函数, 程序启动优先进入此函数
	App.初始化(模块句柄)

	主窗口.事件_创建完毕(注册事件C_取地址(主窗口_创建完毕事件))
	主窗口.创建(, "炫语言黑月界面窗口",, 黑月坐标(800, 600), 窗口风格_默认)

	App.运行(主窗口)
	返回 0

// [文档]<炫语言> 在线手册: http://www.xcgui.com/doc
// [视频]<炫语言> 入门教程: https://www.bilibili.com/video/BV1KM411h7KK
//
// [文档]<炫彩界面库> 最新在线文档: http://www.xcgui.com/doc-ui
// [视频]<炫彩界面库> 通用教程: https://www.bilibili.com/video/BV1kA411A71p/
//
// [商城]炫彩资源商城: http://mall.xcgui.com
//
// *新手尽量不要使用指针, 例如: 字符串使用"文本型", 函数参数若要返回值使用引用 "函数名(整型 &输入输出参数)",
//  内存使用"字节集"
//
//  文本型   双字节字符串  =  炫语言默认字符串类型  =  "字符串W"
//  文本型A  单字节字符串  =  易语言字符串类型     =  A"字符串A"
//  utf8字符串  = U"UTF8字符串"
//  A2W()   单字节字符串 转 双字节字符串
//  W2A()   双字节字符串 转 单字节字符串
//  A =  char    =  单字节
//  w =  wchar_t = 双字节 = UNICODE
//  两个文件中结构体类型互相包含导致冲突, 请将结构体定义移动到一个独立文件中
