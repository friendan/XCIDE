#include "module_threadpool.h"

ThreadPoolPro::~ThreadPoolPro()
{
	// 销毁线程池
	DestroyThreadPool(FALSE, 2000);
}

BOOL ThreadPoolPro::CreateThreadPool(int32_t Capacity)
{
    // 线程池已创建则直接返回真,其他情况返回假
	if (m_ThreadPool)
		return (m_ThreadPool->state >= ThreadPoolState_Normal) ? TRUE : FALSE;
	m_ThreadPool.reset(new THREADPOOL_INFO());
	if (!m_ThreadPool)
		return FALSE;
	if (!m_ThreadPool->hCompletionPort || !m_ThreadPool->hResumeSemaphore || !m_ThreadPool->hExitSemaphore)
	{
		m_ThreadPool.reset();
		return FALSE;
	}
	m_ThreadPool->state = ThreadPoolState_Starting;
	m_ThreadPool->Capacity = (Capacity <= 0) ? GetProcessorsCount() + 1 : Capacity;
	// 创建线程
	for (int32_t i = 0; i < m_ThreadPool->Capacity; i++)
	{
		std::thread(&ThreadPoolWorkerThread, &m_ThreadPool).detach();
		m_ThreadPool->ThreadsCount++;
	}
	//Sleep(1000);
	// 所有线程创建失败时退出
// 	if (m_ThreadPool->ThreadsCount == 0)
// 	{
// 		OutputDebugStringW(L"所有线程创建失败时退出\n");
// 		m_ThreadPool.reset();
// 		return FALSE;
// 	}
	// 创建成功,状态设置为正常工作
	m_ThreadPool->state = ThreadPoolState_Normal;
	return TRUE;
}

BOOL ThreadPoolPro::DestroyThreadPool(BOOL ForceDestroy, int32_t WaitTime)
{
	if (!m_ThreadPool)
		return TRUE;
	// 如果当前为暂停状态,转为强制销毁
	ForceDestroy = (m_ThreadPool->state == ThreadPoolState_Suspend) ? TRUE : ForceDestroy;
	// 如果正在销毁返回假
	if (m_ThreadPool->state == ThreadPoolState_Closing)
		return FALSE;
	m_ThreadPool->state = ThreadPoolState_Closing;
	// 非强制模式时限时等待队列的任务执行完成
	if (!ForceDestroy)
	{
		WaitTime = max(WaitTime, -1);
		std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
		// 循环到线程都退出或超时
		while (m_ThreadPool->ThreadsCount > 0)
		{
			// 超时退出循环,将强制销毁线程池
			if (WaitTime >= 0)
			{
				if (std::chrono::steady_clock::now() - startTime >= std::chrono::milliseconds(WaitTime))
					break;
			}
			Sleep(50);
			ProcessMessage(); // UI线程下自动处理事件,防止窗口卡死
		}
	}
	m_ThreadPool->Capacity = 0;
	int32_t ThreadsCount = m_ThreadPool->ThreadsCount;
	::ReleaseSemaphore(m_ThreadPool->hResumeSemaphore, static_cast<LONG>(ThreadsCount), NULL);
	::ReleaseSemaphore(m_ThreadPool->hExitSemaphore, static_cast<LONG>(ThreadsCount), NULL);
	// 通知IOCP结束所有线程
	for (int32_t i = 0; i < ThreadsCount; i++)
	{
		::PostQueuedCompletionStatus(m_ThreadPool->hCompletionPort, 10086, 0, NULL);
	}
	// 清空所有任务
	if (m_ThreadPool->QueueTask > 0)
	{
		std::thread(&ThreadPoolClearTask, &m_ThreadPool).join();
	}
	m_ThreadPool.reset();
	return TRUE;
}

BOOL ThreadPoolPro::SuspendThreadPool()
{
	if (!m_ThreadPool || m_ThreadPool->state != ThreadPoolState_Normal)
		return FALSE;
	ReSetSemaphore(m_ThreadPool->hResumeSemaphore);
	m_ThreadPool->state = ThreadPoolState_Suspend;
	return TRUE;
}

BOOL ThreadPoolPro::ResumeThreadPool()
{
	if (!m_ThreadPool || m_ThreadPool->state != ThreadPoolState_Suspend)
		return FALSE;
	// 发信号让等待事件结束
	::ReleaseSemaphore(m_ThreadPool->hResumeSemaphore, static_cast<LONG>(m_ThreadPool->ThreadsCount), NULL);
	m_ThreadPool->state = ThreadPoolState_Normal;
	return TRUE;
}

BOOL ThreadPoolPro::ClearTask()
{
	if (!m_ThreadPool)
		return FALSE;
	if (m_ThreadPool->QueueTask <= 0)
		return TRUE;
	if (m_ThreadPool->state == ThreadPoolState_Suspend)
	{
		std::thread(&ThreadPoolClearTask, &m_ThreadPool).join();
		return TRUE;
	}
	if (m_ThreadPool->state != ThreadPoolState_Normal)
		return FALSE;
	m_ThreadPool->state = ThreadPoolState_Clear;
	return TRUE;
}

BOOL ThreadPoolPro::SetThreadPoolCapacity(int32_t nNewThreadNum)
{
	// 非正常状态时返回假
	if (!m_ThreadPool || m_ThreadPool->state < ThreadPoolState_Normal)
		return FALSE;
	nNewThreadNum = (nNewThreadNum <= 0) ? m_Processors + 1 : nNewThreadNum;
	// 新旧线程数量一样时直接返回真
	m_ThreadPool->Capacity = nNewThreadNum;
	if (m_ThreadPool->ThreadsCount == nNewThreadNum)
	{
		return TRUE;
	}
	if (m_ThreadPool->ThreadsCount < nNewThreadNum)
	{
		for (int32_t i = m_ThreadPool->ThreadsCount; i < nNewThreadNum; i++)
			std::thread(&ThreadPoolWorkerThread, &m_ThreadPool).detach();
	} else
	{
		m_ThreadPool->state = ThreadPoolState_Adjust;
		for (int32_t i = m_ThreadPool->ThreadsCount - nNewThreadNum; i > 0; i--)
			::PostQueuedCompletionStatus(m_ThreadPool->hCompletionPort, 0, 0, nullptr);
	}
	return TRUE;
}

int32_t ThreadPoolPro::GetProcessorsCount()
{
	if (m_Processors <= 0)
	{
		SYSTEM_INFO stSysInfo;
		::GetSystemInfo(&stSysInfo);
		m_Processors = static_cast<int32_t>(stSysInfo.dwNumberOfProcessors);
	}
	return (m_Processors <= 0) ? 1 : m_Processors;
}

int32_t ThreadPoolPro::GetThreadsCount() const
{
	return (!m_ThreadPool) ? 0 : m_ThreadPool->ThreadsCount.load();
}

int32_t ThreadPoolPro::GetThreadsCapacity() const
{
	return (!m_ThreadPool) ? 0 : m_ThreadPool->Capacity.load();
}

int32_t ThreadPoolPro::GetWorkerTaskCount() const
{
	return (!m_ThreadPool) ? 0 : m_ThreadPool->WorkerTask.load();
}

int64_t ThreadPoolPro::GetQueueTaskCount() const
{
	return (!m_ThreadPool) ? 0 : m_ThreadPool->QueueTask.load();
}

int64_t ThreadPoolPro::GetComplateTaskCount() const
{
	return (!m_ThreadPool) ? 0 : m_ThreadPool->ComplateTask.load();
}

int32_t ThreadPoolPro::GetFreeThreadsCount() const
{
	return (!m_ThreadPool) ? 0 : (m_ThreadPool->ThreadsCount.load() - m_ThreadPool->WorkerTask.load());
}

int32_t ThreadPoolPro::GetThreadPoolState() const
{
	return (!m_ThreadPool) ? 0 : static_cast<int32_t>(m_ThreadPool->state.load());
}

BOOL ThreadPoolPro::ThreadPoolIsFree() const
{
	return (!m_ThreadPool) ? TRUE : (m_ThreadPool->QueueTask.load() == 0 && m_ThreadPool->WorkerTask.load() == 0);
}

BOOL ThreadPoolPro::IsNeedExit(int32_t nMillseconds)
{
	if (m_ThreadPool)
		return (::WaitForSingleObject(m_ThreadPool->hExitSemaphore, static_cast<DWORD>(nMillseconds)) == WAIT_OBJECT_0);
	return TRUE;
}

INT CALLBACK ThreadPoolPro::ThreadPoolWorkerThread(std::shared_ptr<THREADPOOL_INFO>* lpThreadPool)
{
	std::shared_ptr<THREADPOOL_INFO> ThreadPool = *lpThreadPool;
	//ThreadPool->ThreadsCount++;
	DWORD dwStatus = 0;
	ULONG_PTR CompletionKey = 0;
	std::packaged_task<void()>* task = nullptr; // 任务函数指针
	// 无限循环获取完成端口的状态(接收线程任务)
	while (::GetQueuedCompletionStatus(ThreadPool->hCompletionPort, &dwStatus, &CompletionKey, reinterpret_cast<LPOVERLAPPED*>(&task), INFINITE))
	{
		std::unique_ptr<std::packaged_task<void()>> WorkProc(task);
		if (dwStatus == 10086)
			break;
		else if (dwStatus == 1)
			ThreadPool->QueueTask--;
		switch (ThreadPool->state.load())
		{
		case ThreadPoolState_Suspend:
		{
			::WaitForSingleObject(ThreadPool->hResumeSemaphore, INFINITE);
			break;
		}
		case ThreadPoolState_Clear:
		{
			WorkProc.reset(nullptr);
			if (ThreadPool->QueueTask <= 0)
				ThreadPool->state = ThreadPoolState_Normal;
			break;
		}
		case ThreadPoolState_Adjust:
		{
			if (ThreadPool->ThreadsCount == ThreadPool->Capacity)
				ThreadPool->state = ThreadPoolState_Normal;
			break;
		}
		}
		if (WorkProc != nullptr && WorkProc->valid())
		{
			ThreadPool->WorkerTask++; // 原子锁递增执行任务数
			try
			{
				(*WorkProc)(); // 执行任务
			} catch (...)
			{
			}
			ThreadPool->ComplateTask++; // 原子锁递增已完成任务数
			ThreadPool->WorkerTask--;   // 原子锁递减执行任务数
		}
		if (ThreadPool->ThreadsCount != ThreadPool->Capacity)
		{
			std::lock_guard<std::mutex> lock_g(ThreadPool->lock);
			if (ThreadPool->ThreadsCount > ThreadPool->Capacity)
			{
				ThreadPool->ThreadsCount--;
				return (0);
			} else
			{
				std::thread(&ThreadPoolWorkerThread, &ThreadPool).detach();
			}
		}
	}
	ThreadPool->ThreadsCount--; // 原子锁递减线程数量
	return 0;
}

int32_t CALLBACK ThreadPoolPro::ThreadPoolClearTask(std::shared_ptr<THREADPOOL_INFO>* lpThreadPool)
{
	std::shared_ptr<THREADPOOL_INFO> ThreadPool = *lpThreadPool;
	DWORD dwStatus = 0;
	ULONG_PTR CompletionKey = 0;
	std::packaged_task<void()>* task = nullptr;
	while (::GetQueuedCompletionStatus(ThreadPool->hCompletionPort, &dwStatus,
		&CompletionKey, reinterpret_cast<LPOVERLAPPED*>(&task), 100))
	{
		ThreadPool->QueueTask--; // 原子锁递减队列任务数
		if (task != nullptr)
		{
			delete task; // 释放参数占用的内容
			task = nullptr;
		}
		if (ThreadPool->QueueTask <= 0)
			break;
	}
	ThreadPool->state = ThreadPoolState_Normal;
	return 0;
}

void ThreadPoolPro::ProcessMessage()
{
	MSG msg;
	while (::PeekMessageW(&msg, NULL, NULL, NULL, PM_NOREMOVE) && msg.message != WM_QUIT)
	{
		if (::GetMessageW(&msg, NULL, 0, 0) <= 0)
			break;
		::TranslateMessage(&msg);
		::DispatchMessageW(&msg);
	}
}

void ThreadPoolPro::ReSetSemaphore(HANDLE hSemaphore)
{
	if (hSemaphore)
	{
		while (::WaitForSingleObject(hSemaphore, 0) == WAIT_OBJECT_0)
			;
	}
}

