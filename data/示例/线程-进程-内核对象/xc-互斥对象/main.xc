#外部类型 DWORD

HANDLE  ghMutex = 0
函数 DWORD WINAPI 线程函数1(空类型 *用户数据)
	计次循环 整型 i = 0; 100
		DWORD dwWaitResult = A等待_单对象(ghMutex, 无限等待)
		如果 等待_成功 == dwWaitResult
			调试输出2("线程1 写入数据")
			A互斥对象_释放所有权(ghMutex)
		否则
			跳出
	返回 0

函数 DWORD WINAPI 线程函数2(空类型 *用户数据)
	计次循环 整型 i = 0; 100
		DWORD dwWaitResult = A等待_单对象(ghMutex, 无限等待)
		如果 等待_成功 == dwWaitResult
			调试输出2("线程2 写入数据")
			A互斥对象_释放所有权(ghMutex)
		否则
			跳出
	返回 0

//可以使用 互斥体对象 来保护共享资源免受多个线程或进程的同时访问。 
//每个线程必须等待互斥体的所有权，然后才能执行访问共享资源的代码。 
//例如，如果多个线程共享对数据库的访问，则线程可以使用互斥对象一次只允许一个线程写入数据库。
函数 整型 入口函数_窗口()
	ghMutex = A互斥对象_创建(FALSE, 空)
	如果 NULL == ghMutex
		返回 0

	句柄型  hThread1 = A线程_创建(线程函数1, 0, 0)
	句柄型  hThread2 = A线程_创建(线程函数2, 0, 0)

	//等待线程退出
	A等待_单对象(hThread1, 无限等待)
	A等待_单对象(hThread2, 无限等待)

	关闭句柄(hThread1)
	关闭句柄(hThread2)
	关闭句柄(ghMutex)
	返回 0