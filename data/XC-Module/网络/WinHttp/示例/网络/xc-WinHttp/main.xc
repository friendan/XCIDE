函数 GET测试()
	打印("--GET测试--")
	//WinHttp h("http://www.xcgui.com")
	CXWinHttp h("https://www.baidu.com")
	如果 !h.发送请求()
		打印("发送请求失败")
		返回
	文本型A 返回数据
	打印(h.取状态码文本())
	打印(h.取所有协议头())
	打印(h.取协议头("Content-Type"))
	调试输出(h.取响应文本_自动Utf8转A(返回数据))
	//打印(返回数据)

函数 Cookies测试()
	打印("--Cookies测试--")
	CXWinHttp h("https://www.baidu.com")
	如果 !h.发送请求()
		打印("发送请求失败")
		返回
	打印(h.取所有COOKIES())
	打印(h.取指定COOKIES("BAIDUID"))
	打印(h.Cookies("Cookie: BIDUPSID=AC5721E5E4597209CD26AAE65272D605; PSTM=1650174139;"))
	打印(h.Cookies())
	打印(h.获取Cookies("PSTM"))
	h.删除Cookie("PSTM=233333")
	打印(h.Cookies())
	h.添加Cookie("PSTM=233333")
	打印(h.Cookies())

函数 跳转测试()
	打印("--跳转测试--")
	CXWinHttp h
	如果 !h.打开("https://link.mcmod.cn/target/aHR0cHM6Ly93d3cubWNiYnMubmV0L3RocmVhZC05MzI5MTEtMS0xLmh0bWw=")
		打印("打开链接失败")
		返回
	h.置允许重定向(假)
	如果 !h.发送请求()
		打印("发送请求失败")
		返回
	文本型 返回数据
	调试输出(h.取响应文本_自动Utf8转W(返回数据))
	打印(返回数据)
	打印(h.取重定向地址())

函数 代理测试(整型 type)
	打印("--代理测试--")
	CXWinHttp h
	如果 !h.打开("https://github.com/")
		打印("打开链接失败")
		返回
	如果 type == 1
		如果 !h.置代理("https=127.0.0.1:20812", "admin", "admin")	//有代理自己修改测试
			打印("置代理失败")
			返回
	如果 type == 2
		如果 !h.置代理("https=127.0.0.1:20812")	//有代理自己修改测试
			打印("置代理失败")
			返回
		h.置身份验证凭据("admin", "admin", WINHTTP_AUTH_认证目标_代理服务器, WINHTTP_AUTH_认证方式_基本认证_BASE64加密)
	如果 !h.发送请求()
		打印("发送请求失败")
		返回
	文本型A 返回数据
	打印(h.取状态码文本())
	调试输出(h.取响应文本_自动Utf8转A(返回数据))
	打印A(返回数据)

函数 请求头测试()
	打印("--请求头测试--")
	CXWinHttp h("https://littleskin.cn/")
	如果 !h.发送请求()
		打印("发送请求失败")
		返回
	文本型A 返回数据
	调试输出(h.取响应文本_自动Utf8转A(返回数据))
	//打印(返回数据)
	h.置UA信息("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36 Edg/102.0.1245.39")
	如果 !h.发送请求()
		打印("发送请求失败")
		返回
	调试输出(h.取响应文本_自动Utf8转A(返回数据))
	//打印(返回数据)

函数 IP测试()
	打印("--IP测试--")
	CXWinHttp h("http://4.ipw.cn/")
	如果 !h.发送请求()
		打印("发送请求失败")
		返回
	文本型A 返回数据
	调试输出(h.取响应文本_自动Utf8转A(返回数据))
	打印A(返回数据)
	如果 !h.置FakeIP("127.0.0.1")
		打印("FakeIP设置失败")
		返回
	如果 !h.发送请求()
		打印("发送请求失败")
		返回

函数 整型 入口函数()
	GET测试()
	Cookies测试()
	跳转测试()
	//代理测试(1)
	//代理测试(2)
	请求头测试()
	IP测试()
	控制台暂停()
	返回 0

函数 打印A(文本型A str)
	#嵌入代码
	printf("%s\n", str.get());
	#嵌入代码_结束
	调试输出(str)

函数 打印(文本型 str)
	#嵌入代码
	printf("%s\n", W2A(str.get()).get());
	#嵌入代码_结束
	调试输出(str)
