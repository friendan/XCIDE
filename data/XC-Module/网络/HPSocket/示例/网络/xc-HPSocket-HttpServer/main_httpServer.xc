类 CHTTP服务端监听器类  继承 HP_HTTP服务器监听器_实现
	TCP服务端_智能指针    _TCP服务
	函数 逻辑型 开始()
		_TCP服务.附加(HP_Create_HttpServer(this))
		如果  _TCP服务->启动("0.0.0.0", 80)
			调试输出("启动")
		否则
			调试输出("失败: ", _TCP服务->取错误代码(), _TCP服务->取错误描述())
		返回 真
	函数 停止()
		调试输出("停止")
		_TCP服务->关闭()

	函数 虚函数 EnHandleResult 准备监听通知(HP_TCP服务器* pSender, SOCKET soListen) 重写
		调试输出(__函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 EnHandleResult 接收连接通知(HP_TCP服务器* pSender, CONNID dwConnID, UINT_PTR soClient)  重写
		调试输出(__函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 EnHandleResult 握手完成通知(HP_TCP服务器* pSender, CONNID dwConnID) 重写
		调试输出(__函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 EnHandleResult 数据到达通知(HP_TCP服务器* pSender, CONNID dwConnID, int iLength) 重写
		调试输出(__函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 EnHandleResult 数据到达通知(HP_TCP服务器* pSender, CONNID dwConnID, const BYTE* pData, int iLength) 重写
		调试输出(__函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 EnHandleResult 已发送数据通知(HP_TCP服务器* pSender, CONNID dwConnID, const BYTE* pData, int iLength) 重写
		调试输出(__函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 EnHandleResult 关闭通信组件通知(HP_TCP服务器* pSender)
		调试输出(__函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 EnHandleResult 关闭通知(HP_TCP服务器* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) 重写
		调试输出(__函数名__); 返回 HP事件处理结果_忽略
	
	函数 虚函数 EnHttpParseResult 开始解析通知(HP_HTTP服务器* pSender, CONNID dwConnID) 重写
		调试输出(__函数名__); 返回 HPHTTP解析结果_成功
	函数 虚函数 EnHttpParseResult 请求行解析完成通知(HP_HTTP服务器* pSender, CONNID dwConnID, const char* lpszMethod,  const char* lpszUrl) 重写
		调试输出(__函数名__); 返回 HPHTTP解析结果_成功
	函数 虚函数 EnHttpParseResult 状态行解析完成通知(HP_HTTP服务器* pSender, CONNID dwConnID, USHORT usStatusCode,  const char* lpszDesc) 重写
		调试输出(__函数名__); 返回 HPHTTP解析结果_成功
	函数 虚函数 EnHttpParseResult 请求头通知(HP_HTTP服务器* pSender, CONNID dwConnID,  const char* lpszName,  const char* lpszValue) 重写
		调试输出(__函数名__); 返回 HPHTTP解析结果_成功
	函数 虚函数 EnHttpParseResult Chunked报文头通知(HP_HTTP服务器* pSender, CONNID dwConnID, int iLength) 重写
		调试输出(__函数名__); 返回 HPHTTP解析结果_成功
	函数 虚函数 EnHttpParseResult Chunked报文结束通知(HP_HTTP服务器* pSender, CONNID dwConnID) 重写
		调试输出(__函数名__); 返回 HPHTTP解析结果_成功
	函数 虚函数 EnHttpParseResult 升级协议通知(HP_HTTP服务器* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType) 重写
		调试输出(__函数名__); 返回 HPHTTP解析结果_成功

	函数 虚函数 EnHandleResult Web数据包体通知(HP_HTTP服务器* pSender, CONNID dwConnID, const BYTE* pData, int iLength) 重写
		调试输出(__函数名__); 返回 HP事件处理结果_忽略
	函数 虚函数 EnHandleResult Web数据包完成通知(HP_HTTP服务器* pSender, CONNID dwConnID) 重写
		调试输出(__函数名__); 返回 HP事件处理结果_忽略
	
	函数 虚函数 EnHttpParseResult 请求头完成通知(HP_HTTP服务器* pSender, CONNID dwConnID) 重写
		调试输出(__函数名__); 返回 HPHTTP解析结果_成功
	函数 虚函数 EnHttpParseResult 完成解析通知(HP_HTTP服务器* pSender, CONNID dwConnID) 重写
		调试输出(__函数名__); 返回 HPHTTP解析结果_成功
	函数 虚函数 EnHttpParseResult 解析错误通知(HP_HTTP服务器* pSender, CONNID dwConnID, int iErrorCode, const  char*  lpszErrorDesc) 重写
		调试输出(__函数名__); 返回 HPHTTP解析结果_成功
	函数 虚函数 EnHttpParseResult BODY报文通知(HP_HTTP服务器* pSender, CONNID dwConnID, const BYTE* pData, int iLength) 重写
		调试输出(__函数名__); 返回 HPHTTP解析结果_成功
