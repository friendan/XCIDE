//以下示例使用 信号灯对象 来限制可执行特定任务的线程数。 
//首先，它使用 CreateSemaphore 函数创建信号灯并指定初始计数和最大计数，然后使用 CreateThread 函数创建线程。

//在线程尝试执行任务之前，它使用 WaitForSingleObject 函数来确定信号灯的当前计数是否允许它执行此操作。 
//wait 函数的超时参数设置为零，因此当信号灯处于非对齐状态时，函数会立即返回。 WaitForSingleObject 将信号灯的计数递减一。

//当线程完成任务时，它使用 ReleaseSemaphore 函数递增信号灯的计数，从而允许另一个等待线程执行该任务。
//https://docs.microsoft.com/zh-cn/windows/win32/sync/using-semaphore-objects

#外部类型 DWORD
句柄型 ghSemaphore
函数 DWORD WINAPI 线程函数(空类型 *用户数据)
	DWORD dwWaitResult
	循环 1
		延时(10)
		dwWaitResult = A等待_单对象(ghSemaphore, 0)
		如果 等待_成功 == dwWaitResult
			调试输出("线程", A线程_取当前线程ID(), "等待成功 ok")
			A信号量_释放(ghSemaphore, 1, NULL)
			跳出
		否则 等待_超时 == dwWaitResult
			调试输出("线程", A线程_取当前线程ID(), "等待超时")
	返回 0

//测试多线程 未加数据保护
函数 整型 入口函数_窗口()
	ghSemaphore = A信号量_创建(2, 2, NULL)
	句柄型  hThreads[10]
	计次循环 整型 i = 0; 10
		hThreads[i] = A线程_创建(线程函数, 0, 0)

	A等待_多对象(10, hThreads, 真, 无限等待)//等待线程退出

	计次循环 整型 i = 0; 10
		关闭句柄(hThreads[i])
	关闭句柄(ghSemaphore)
	返回 0