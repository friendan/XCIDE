//以下示例演示线程如何初始化、输入和释放 关键部分。 
//它使用 InitializeCriticalSectionAndSpinCount、EnterCriticalSection、LeaveCriticalSection 和 DeleteCriticalSection 函数。

#外部类型 DWORD

临界区结构  cs
整型    g_data = 0  //全局公共变量,临界区保护变量
函数 DWORD WINAPI ThreadProc1(空类型 *用户数据)
	计次循环 整型 i = 0; 100
		延时(10)
		A临界区_进入(&cs)
		//访问共享资源
		g_data++
		调试输出2("线程1 : ", g_data)
		A临界区_离开(&cs)
	返回 0

函数 DWORD WINAPI ThreadProc2(空类型 *用户数据)
	计次循环 整型 i = 0; 100
		延时(10)
		A临界区_进入(&cs)
		//访问共享资源
		g_data++
		调试输出2("线程2 : ", g_data)
		A临界区_离开(&cs)
	返回 0

函数 整型 入口函数_窗口()
	A临界区_初始化(&cs)

	句柄型 hThread1 = A线程_创建(ThreadProc1, 空, 空)
	句柄型 hThread2 = A线程_创建(ThreadProc2, 空, 空)

	A等待_单对象(hThread1, 无限等待)
	A等待_单对象(hThread2, 无限等待)

	关闭句柄(hThread1)
	关闭句柄(hThread2)
	A临界区_删除(&cs)
	返回 0