类 CTCP客户端监听类 继承  HP_TCP客户端监听器_实现
	TCP客户端_智能指针   _TCP客户端 
	函数 逻辑型 开始()
		_TCP客户端.附加(HP_Create_TcpClient(this))
		如果 _TCP客户端->启动("127.0.0.1", 80, FALSE)
			文本型A buf = A"123456"
			如果 _TCP客户端->发送数据((字节型*)buf.取地址(), buf.取大小(), 0)
				调试输出("---Send---")
				延迟(1000)
			_TCP客户端->关闭()
		否则
			调试输出("失败: ", _TCP客户端->取错误代码(), _TCP客户端->取错误描述())
		返回 真

	函数 事件 虚函数 HP事件处理结果 准备连接通知(HP_TCP客户端* pSender, CONNID dwConnID, SOCKET socket)  重写
		控制台格式输出("%s\n", __函数名__); 返回 HP事件处理结果_忽略
	函数 事件 虚函数 HP事件处理结果 连接完成通知(HP_TCP客户端* pSender, CONNID dwConnID) 重写
		控制台格式输出("%s\n", __函数名__); 返回 HP事件处理结果_忽略
	函数 事件 虚函数 HP事件处理结果 握手完成通知(HP_TCP客户端* pSender, CONNID dwConnID) 重写
		控制台格式输出("%s\n", __函数名__); 返回 HP事件处理结果_忽略
	函数 事件 虚函数 HP事件处理结果 数据到达通知(HP_TCP客户端* pSender, CONNID dwConnID, 整型 iLength) 重写
		控制台格式输出("%s\n", __函数名__); 返回 HP事件处理结果_忽略
	函数 事件 虚函数 HP事件处理结果 已发送数据通知(HP_TCP客户端* pSender, CONNID dwConnID, 常量 字节型* pData, 整型 iLength)  重写
		调试输出("OnSend() iLength:", iLength)
		字节集   数据
		数据.置数据(pData, iLength)
		调试输出(A"OnBody():  ", 数据.取文本指针A())
		返回 HP事件处理结果_忽略
	函数 事件 虚函数 HP事件处理结果 数据到达通知(HP_TCP客户端* pSender, CONNID dwConnID, 常量 字节型* pData, 整型 iLength) 重写
		控制台格式输出("%s\n", __函数名__); 返回 HP事件处理结果_忽略
	函数 事件 虚函数 HP事件处理结果 关闭通知(HP_TCP客户端* pSender, CONNID dwConnID, EnSocketOperation enOperation, 整型 iErrorCode) 重写
		控制台格式输出("%s\n", __函数名__); 返回 HP事件处理结果_忽略