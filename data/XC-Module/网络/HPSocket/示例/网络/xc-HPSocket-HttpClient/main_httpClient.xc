类 CHTTP客户端监听类 继承  HP_HTTP客户端监听器_实现
	HTTP客户端_智能指针   _客户端 
	函数 逻辑型 开始()
		_客户端.附加(HP_Create_HttpClient(this))
		如果 _客户端->启动("127.0.0.1", 80, FALSE)
			文本型A buf = A"123456"
			如果 _客户端->发送数据((字节型*)buf.取地址(), buf.取大小(), 0)
				调试输出("---Send---")
			延迟(1000)
			_客户端->关闭()
		否则
			调试输出("失败: ", _客户端->取错误代码(), _客户端->取错误描述())
		返回 真

	函数 虚函数 HP事件处理结果 准备连接通知(HP_TCP客户端* pSender, CONNID dwConnID, SOCKET socket)重写
		调试输出("OnPrepareConnect()")
		返回 HP事件处理结果_成功
	函数 虚函数 HP事件处理结果 连接完成通知(HP_TCP客户端* pSender, CONNID dwConnID)重写
		调试输出("OnConnect()")
		返回 HP事件处理结果_成功
	函数 虚函数 HP事件处理结果 握手完成通知(HP_TCP客户端* pSender, CONNID dwConnID)重写
		调试输出("OnHandShake()")
		返回 HP事件处理结果_成功
	函数 虚函数 HP事件处理结果 已发送数据通知(HP_TCP客户端* pSender, CONNID dwConnID, const BYTE* pData, int iLength)重写
		调试输出("OnSend() iLength:", iLength)
		返回 HP事件处理结果_成功
	函数 虚函数 HPHTTP解析结果 开始解析通知(HP_HTTP客户端* pSender, CONNID dwConnID)重写
		调试输出("OnMessageBegin()")
		返回 HPHTTP解析结果_成功
	函数 虚函数 HPHTTP解析结果 请求行解析完成通知(HP_HTTP客户端* pSender, CONNID dwConnID, const char* lpszMethod, const char* lpszUrl)重写
		返回 HPHTTP解析结果_成功
	函数 虚函数 HPHTTP解析结果 状态行解析完成通知(HP_HTTP客户端* pSender, CONNID dwConnID, USHORT usStatusCode, const char* lpszDesc)重写
		调试输出("OnStatusLine()")
		返回 HPHTTP解析结果_成功
	函数 虚函数 HPHTTP解析结果 请求头通知(HP_HTTP客户端* pSender, CONNID dwConnID, const char* lpszName, const char* lpszValue)重写
		调试输出(A"OnHeader()   ", lpszName, lpszValue)
		返回 HPHTTP解析结果_成功
	函数 虚函数 HPHTTP解析结果 Chunked报文头通知(HP_HTTP客户端* pSender, CONNID dwConnID, int iLength)重写
		返回 HPHTTP解析结果_成功
	函数 虚函数 HPHTTP解析结果 Chunked报文结束通知(HP_HTTP客户端* pSender, CONNID dwConnID)重写
		返回 HPHTTP解析结果_成功
	函数 虚函数 HPHTTP解析结果 升级协议通知(HP_HTTP客户端* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)重写
		返回 HPHTTP解析结果_成功
	函数 虚函数 HPHTTP解析结果 解析错误通知(HP_HTTP客户端* pSender, CONNID dwConnID, int iErrorCode, const char* lpszErrorDesc)重写
		返回 HPHTTP解析结果_成功
	函数 虚函数 HPHTTP解析结果 请求头完成通知(HP_HTTP客户端* pSender, CONNID dwConnID)重写
		返回 HPHTTP解析结果_成功
	函数 虚函数 HPHTTP解析结果 BODY报文通知(HP_HTTP客户端* pSender, CONNID dwConnID, const BYTE* pData, int iLength)重写
		调试输出("OnBody() iLength:", iLength)
		char buf[20480] = {0};
		memcpy(buf, pData, iLength);
		buf[iLength] = 0;
		调试输出(A"OnBody():  ", buf)
		返回 HPHTTP解析结果_成功
	函数 虚函数 HPHTTP解析结果 完成解析通知(HP_HTTP客户端* pSender, CONNID dwConnID)重写
		返回 HPHTTP解析结果_成功
	函数 虚函数 HP事件处理结果 Web数据包体通知(HP_HTTP客户端* pSender, CONNID dwConnID, const BYTE* pData, int iLength)重写
		返回 HP事件处理结果_忽略
	函数 虚函数 HP事件处理结果 Web数据包完成通知(HP_HTTP客户端* pSender, CONNID dwConnID)重写
		返回 HP事件处理结果_忽略
	函数 虚函数 HP事件处理结果 关闭通知(HP_TCP客户端* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)重写
		调试输出("OnClose()")
		返回 HP事件处理结果_忽略