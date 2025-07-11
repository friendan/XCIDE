类 CTCP服务端监听器类  继承 HP_TCP服务器监听器_实现
	TCP服务端_智能指针    _TCP服务
	函数 逻辑型 开始()
		_TCP服务.附加(HP_Create_TcpServer(this))
		如果  _TCP服务->启动("0.0.0.0", 80)
			调试输出("启动")
		否则
			调试输出("失败: ", _TCP服务->取错误代码(), _TCP服务->取错误描述())
		返回 真
	函数 停止()
		调试输出("停止")
		_TCP服务->关闭()

	函数 虚函数 HP事件处理结果 准备监听通知(HP_TCP服务器* pSender, SOCKET soListen) 重写 //OnPrepareListen()
		字符型 szAddress[100]  //地址
		整型   iAddressLen =100 //数组大小
		正短整型 usPort  //端口
		pSender->取监听地址信息(szAddress, iAddressLen, usPort)
		控制台格式输出("%s() %s:%d\n", __函数名__, szAddress, usPort)
		返回 HP事件处理结果_忽略

	函数 虚函数 HP事件处理结果 接收连接通知(HP_TCP服务器* pSender, CONNID dwConnID, UINT_PTR soClient) 重写 //OnAccept()
		字符型 szAddress[100]  //地址
		整型   iAddressLen =100 //数组大小
		正短整型 usPort  //端口
		pSender->取远程地址信息(dwConnID, szAddress, iAddressLen, usPort)
		控制台格式输出("%s() 链接ID:%d, %s:%d\n", __函数名__, dwConnID, szAddress, usPort)
		返回 HP事件处理结果_忽略

	函数 虚函数 HP事件处理结果 握手完成通知(HP_TCP服务器* pSender, CONNID dwConnID) 重写  //OnHandShake
		控制台格式输出("%s\n", __函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 HP事件处理结果 数据到达通知(HP_TCP服务器* pSender, CONNID dwConnID, 常量 字节型* pData, 整型 iLength) 重写  //OnReceive
		控制台格式输出("%s\n", __函数名__)
		文本型A   数据
		数据.添加2((常量 字符型A*)pData, iLength)
		控制台格式输出A(A"接收数据:%s\n", 数据.取地址())
		返回 HP事件处理结果_忽略

	函数 虚函数 HP事件处理结果 数据到达通知(HP_TCP服务器* pSender, CONNID dwConnID, 整型 iLength)  重写  //OnReceive
		控制台格式输出("%s\n", __函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 HP事件处理结果 已发送数据通知(HP_TCP服务器* pSender, CONNID dwConnID, 常量 字节型* pData, 整型 iLength) 重写
		控制台格式输出("%s\n", __函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 HP事件处理结果 关闭通信组件通知(HP_TCP服务器* pSender) 重写
		控制台格式输出("%s\n", __函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 HP事件处理结果 关闭通知(HP_TCP服务器* pSender, CONNID dwConnID, HP操作类型 enOperation, 整型 iErrorCode)  重写  //OnClose
		控制台格式输出("%s\n", __函数名__); 返回 HP事件处理结果_忽略

