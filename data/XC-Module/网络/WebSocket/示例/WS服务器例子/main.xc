﻿

WebSocket服务端 WS

函数 事件_客户进入(客户 _客户)
	调试输出("客户进入")

函数 事件_客户退出(客户 _客户)
	调试输出("客户退出")

函数 事件_收到数据(客户 _客户, 字节集 数据)

	调试输出("收到数据")
	调试输出(到文本A(数据))




函数 整型 入口函数() //控制台程序入口函数, 程序启动优先进入此函数
	调试输出("控制台程序")


	WS.事件_客户进入 = 事件_客户进入
	WS.事件_客户退出 = 事件_客户退出
	WS.事件_数据到达 = 事件_收到数据

	WS.启动(8080)
	


	控制台_暂停()
	


	返回 0





