//应用程序可以在很多情况下使用 事件对象 来通知等待线程发生事件。 
//例如，对文件、命名管道和通信设备的重叠 I/O 操作使用事件对象来指示其完成情况。 
//有关在重叠 I/O 操作中使用事件对象的详细信息，请参阅 同步和重叠输入和输出

//以下示例使用事件对象防止在主线程写入该缓冲区时从共享内存缓冲区读取多个线程。 
//首先，主线程使用 CreateEvent 函数创建一个手动重置事件对象，其初始状态为非对齐状态。 
//然后，它会创建多个读取器线程。 主线程执行写入操作，然后在写入完成后将事件对象设置为信号状态。

//在开始读取操作之前，每个读取器线程都使用 WaitForSingleObject 等待手动重置事件对象发出信号。 
//WaitForSingleObject 返回时，这表示主线程已准备好开始其读取操作。

#外部类型 DWORD

HANDLE  ghWriteEvent = 0
函数 DWORD WINAPI 线程函数1(空类型 *用户数据)
	调试输出2("线程1运行, 参数: ", (整型)用户数据)

	DWORD dwWaitResult = A等待_单对象(ghWriteEvent, 无限等待)
	如果 等待_成功 == dwWaitResult
		调试输出2("线程1 读取数据")
	
	调试输出2("线程1 退出", dwWaitResult)
	返回 0

函数 DWORD WINAPI 线程函数2(空类型 *用户数据)
	调试输出2("线程2运行, 参数: ", (整型)用户数据)

	DWORD dwWaitResult = A等待_单对象(ghWriteEvent, 无限等待)
	如果 等待_成功 == dwWaitResult
		调试输出2("线程2 读取数据")

	调试输出2("线程2 退出", dwWaitResult)
	返回 0

函数 空类型 主线程写入数据()
	调试输出("主线程写入数据")
	如果 FALSE == A事件对象_置有信号(ghWriteEvent)
		调试输出("WriteToBuffer() 失败")
	//事件对象_置有信号(ghWriteEvent)

//测试多线程 未加数据保护
函数 整型 入口函数_窗口()
	ghWriteEvent = A事件对象_创建(真, FALSE, "WriteEvent")
	如果 NULL == ghWriteEvent
		返回 0

	整型    data = 100;
	句柄型  hThread1 = A线程_创建(线程函数1, (空类型*)data, 0)

	整型    data2 = 200;
	句柄型  hThread2 = A线程_创建(线程函数2, (空类型*)data2, 0)
	
	延时(2000)
	主线程写入数据()
	延时(1000)

	//等待线程退出
	A等待_单对象(hThread1, 无限等待)
	A等待_单对象(hThread2, 无限等待)

	关闭句柄(hThread1)
	关闭句柄(hThread2)
	关闭句柄(ghWriteEvent)
	返回 0