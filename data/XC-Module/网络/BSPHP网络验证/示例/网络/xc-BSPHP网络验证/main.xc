﻿
类 我的主窗口类 继承 窗口类 
	[绑定信息] //IDE生成的UI绑定信息(UI变量,事件), 支持手动修改, 可收缩隐藏
		[窗口事件]
		[按钮类, _登入, "登入"]
			[XE_BNCLICK, 事件_登入_点击, 0]
		[按钮类, _注册, "注册"]
			[XE_BNCLICK, 事件_注册_点击, 0]
		[按钮类, _充值, "充值"]
			[XE_BNCLICK, 事件_充值_点击, 0]
		[形状文本类, _形状文本1, "形状文本1"]
	文本型   _账号 = "abctt666"
	文本型   _密码 = "ac586ss3"
	文本型  _布局文件= "main.xml"
	//窗口类初始化, 自动处理关联的布局文件及绑定变量和注册事件
	函数 整型 运行()
		BSPHP_置标记("123481251")  //绑定电脑标记
		文本型  公告 = BSPHP_取公告()
		_形状文本1.置文本(公告)
		显示(TRUE)
		返回 0
	函数 整型  事件_登入_点击(逻辑型* 是否拦截)
		调试输出(BSPHP_登录(_账号, _密码)) //登录
		返回 0
	函数 整型  事件_注册_点击(逻辑型* 是否拦截)
		调试输出(BSPHP_注册(_账号, _密码, "QQ1544"))//注册
		返回 0
	函数 整型  事件_充值_点击(逻辑型* 是否拦截)
		调试输出(BSPHP_充值(_账号, _密码, "卡号", "卡密"))  //充值续费
		返回 0

函数 整型 入口函数_窗口()
	BSPHP_SetServerUrl("http://app.bsphp.com/AppEn.php?appid=90001&m=f15a5c67a0c7cf6da3a1e5f50cb32325")
	BSPHP_SetMesKey("46ae5f5ca6c2d27fb6185c7590a15ae9")
	BSPHP_SetAesKey("suAuy0xHfXvDHFXs")

	if(!BSPHP_初始化())
		返回 0
	BSPHP_取session()

	炫彩_初始化(TRUE)
	我的主窗口类  主窗口
	主窗口.运行()
	炫彩_运行()
	炫彩_退出()
	返回 0
