#ifndef XCL_THREAD_POOL_H
#define XCL_THREAD_POOL_H

//@模块名称  线程池
//@版本  1.0  
//@日期  2023-08-27
//@作者  XCGUI  
//@QQ   154460336
//@模块备注  线程池模块, 示例->高级示例->线程池
//用法:
//函数  任务处理函数(整型  用户数据)
//**调试输出(用户数据)
//**
//函数 整型 入口函数_窗口()
//**线程池类  线程池
//**线程池.创建(10)
//**计次循环 整型 i = 0; 1000
//****线程池.投递任务(任务处理函数, i)


//@依赖  module_base.h

#if XC_MOUDLE
#include <windows.h>
#endif

#include <future>


//@src  "threadpool.cpp"


//@启用枚举前缀

//@别名  线程池状态
enum ThreadPoolState
{
	ThreadPoolState_Closed = 0,   //@别名 线程池已被关闭
	ThreadPoolState_Closing = 1,  //@别名 正在关闭线程池
	ThreadPoolState_Starting = 2, //@别名 正在创建线程池
	ThreadPoolState_Normal = 3,   //@别名 线程池正常工作
	ThreadPoolState_Adjust = 4,   //@别名 调整线程池容量
	ThreadPoolState_Suspend = 5,  //@别名 线程池暂停
	ThreadPoolState_Clear = 6     //@别名 正在清空任务
};

//@别名 线程池类
class ThreadPoolPro
{
protected:

    struct THREADPOOL_INFO // 线程池信息
    {
        HANDLE hCompletionPort = NULL;                               // IOCP完成端口
        HANDLE hResumeSemaphore = NULL;                              // 是否需要退出信号灯
        HANDLE hExitSemaphore = NULL;                                // 是否需要退出信号灯
        std::mutex lock;                                             // 互斥锁
        std::atomic<ThreadPoolState> state = ThreadPoolState_Closed; // 工作状态(ThreadPoolState)
        std::atomic<int32_t> ThreadsCount = 0;                       // 现行线程数
        std::atomic<int32_t> Capacity = 0;                           // 线程池容量
        std::atomic<int32_t> WorkerTask = 0;                         // 执行任务数
        std::atomic<int64_t> QueueTask = 0;                          // 队列任务数量
        std::atomic<int64_t> ComplateTask = 0;                       // 已完成任务数
        THREADPOOL_INFO()
        {
            hCompletionPort = ::CreateIoCompletionPort((HANDLE)-1, NULL, 0, 0);
            hResumeSemaphore = ::CreateSemaphoreW(NULL, 0, LONG_MAX, NULL);
            hExitSemaphore = ::CreateSemaphoreW(NULL, 0, LONG_MAX, NULL);
        }
        ~THREADPOOL_INFO()
        {
            if (hResumeSemaphore)
                ::CloseHandle(hResumeSemaphore);
            if (hExitSemaphore)
                ::CloseHandle(hExitSemaphore);
            if (hCompletionPort)
                ::CloseHandle(hCompletionPort);
        }
    };
    std::shared_ptr<THREADPOOL_INFO> m_ThreadPool{nullptr};
    int32_t m_Processors = 0; // CPU逻辑核心数

public:
	ThreadPoolPro() { }
	~ThreadPoolPro();

	//@别名  创建(线程数量)
	virtual BOOL CreateThreadPool(int32_t Capacity = 0);

	 //@别名  销毁(是否强制销毁, 最长等待时间)
	BOOL DestroyThreadPool(BOOL ForceDestroy = TRUE, int32_t WaitTime = -1);

	 //@别名  暂停()
	BOOL SuspendThreadPool();

	 //@别名  继续()
	BOOL ResumeThreadPool();



/*@声明
	//@参数  Fun 执行函数
	//@参数  args 参数列表, 不定参数数量及类型, 参数将传入执行函数
	//@别名  投递任务()
	BOOL PostTask(Fun &&fun, ...);

	//@备注  任务函数不带参数
	//@别名  投递任务2(执行函数)
	BOOL PostTask2(Fun &fun);
*/

//@隐藏{
    template <typename Fun, typename... Args>
    inline BOOL PostTask(Fun &&fun, Args &&...args)
    {
        if (!m_ThreadPool || m_ThreadPool->state < ThreadPoolState_Normal)
            return FALSE;
        std::packaged_task<void()> *task = new std::packaged_task<void()>(std::bind(std::forward<Fun>(fun), std::forward<Args>(args)...));
        m_ThreadPool->QueueTask++;
        return ::PostQueuedCompletionStatus(m_ThreadPool->hCompletionPort, 1, 0, reinterpret_cast<LPOVERLAPPED>(task));
    }
    template <typename Fun>
    inline BOOL PostTask2(Fun &fun)
    {
        if (!m_ThreadPool || m_ThreadPool->state < ThreadPoolState_Normal)
            return FALSE;
        std::packaged_task<void()> *task = new std::packaged_task<void()>(std::forward<Fun>(fun));
        m_ThreadPool->QueueTask++;
        return ::PostQueuedCompletionStatus(m_ThreadPool->hCompletionPort, 1, 0, reinterpret_cast<LPOVERLAPPED>(task));
    }
//@隐藏}

	 //@别名  清空任务()
	BOOL ClearTask();

	 //@别名  调整线程池(新线程数)
	BOOL SetThreadPoolCapacity(int32_t nNewThreadNum);

	 //@别名  取CPU核心数()
	int32_t GetProcessorsCount();

	 //@别名  取现行线程数()
	int32_t GetThreadsCount() const;

	 //@别名  取线程池容量()
	int32_t GetThreadsCapacity() const;

	 //@别名  取执行任务数()
	int32_t GetWorkerTaskCount() const;

	 //@别名  取队列任务数()
	int64_t GetQueueTaskCount() const;

	 //@别名  取已完成任务数()
	int64_t GetComplateTaskCount() const;

	 //@别名  取空闲线程数()
	int32_t GetFreeThreadsCount() const;

	 //@别名  取工作状态()
	int32_t GetThreadPoolState() const;

	 //@别名  是否空闲()
	BOOL ThreadPoolIsFree() const;

	 //@别名  是否需要退出(最大检查等待时间)
	BOOL IsNeedExit(int32_t nMillseconds = 0);

protected:
    /**
     * @brief (内部)工作线程
     * @param lpThreadPool 线程池参数
     * @return
     */
	static INT CALLBACK ThreadPoolWorkerThread(std::shared_ptr<THREADPOOL_INFO>* lpThreadPool);
    /**
     * @brief (内部)清空任务线程
     * @param lpThreadPool 线程池参数
     * @return
     */
	static int32_t CALLBACK ThreadPoolClearTask(std::shared_ptr<THREADPOOL_INFO>* lpThreadPool);
    /**
     * @brief (内部)UI线程下处理事件,防止窗口卡死
     */
	void ProcessMessage();
    /**
     * @brief (内部)重置信号灯
     * @param hSemaphore 信号灯句柄
     */
	static void ReSetSemaphore(HANDLE hSemaphore);
};

#endif
