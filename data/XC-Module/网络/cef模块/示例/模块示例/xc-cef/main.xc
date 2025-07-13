#外部宏  SW_HIDE
#外部宏  CEF_REQUIRE_UI_THREAD

#智能指针  CefRefPtr<CBrowserView>  CBrowserViewPtr
#智能指针  CefRefPtr<CefBrowser>  CefBrowserPtr
#智能指针  CefRefPtr<CefBrowserHost>  CefBrowserHostPtr
#智能指针  CefRefPtr<CefLoadHandler>  CefLoadHandlerPtr
#智能指针  CefRefPtr<CefDisplayHandler>  CefDisplayHandlerPtr
#智能指针  CefRefPtr<CefLifeSpanHandler>  CefLifeSpanHandlerPtr

类  CBrowserView 继承  CBrowserViewBase
	函数  BOOL Create(int x, int y, int cx, int cy, HWINDOW hWindow, const wchar_t* pUrl)
		m_hWindow = hWindow
		m_bShow = TRUE
		this->AddRef()
		CefWindowInfo window_info
		RECT rcChild = { x, y, 0, 0 }
		rcChild.right = rcChild.left + cx
		rcChild.bottom = rcChild.top + cy

		window_info.SetAsChild(XWnd_GetHWND(hWindow), rcChild)
		CefBrowserSettings browser_settings
		browser_settings.background_color = RGB(255, 0, 0)
		CefBrowserHost::CreateBrowser(window_info, this, pUrl, browser_settings, NULL)
		返回 TRUE
	
	函数  void Show(BOOL bShow)
		如果 m_bShow == bShow
			返回
		m_bShow = bShow
		如果 m_browser.get()
			CefBrowserHostPtr host = m_browser->GetHost()
			HWND hWnd = host->GetWindowHandle()
			如果 m_bShow
				ShowWindow(hWnd, SW_SHOW);
			否则
				ShowWindow(hWnd, SW_HIDE);

	函数 虚函数 CefDisplayHandlerPtr GetDisplayHandler()重写
		调试输出(__函数名__, " ", U2W(__文件__), " ", __行号__)
		返回 this
	
	函数 虚函数 CefLifeSpanHandlerPtr GetLifeSpanHandler()重写
		调试输出(__函数名__, " ", U2W(__文件__), "  ", __行号__)
		返回 this
	
	函数 虚函数 CefLoadHandlerPtr   GetLoadHandler()重写
		调试输出(__函数名__, " ", U2W(__文件__), " ", __行号__)
		返回 this
		
	函数 虚函数 void OnTitleChange(CefBrowserPtr browser, const CefString& title)重写
		调试输出(__函数名__, " ", U2W(__文件__), " ", __行号__)
		调试输出(title)
		
	函数 void OnAfterCreated(CefBrowserPtr browser)重写
		CEF_REQUIRE_UI_THREAD()
		如果 m_browser.get()
			返回
		m_browser = browser
	
	函数 虚函数 void OnBeforeClose(CefBrowserPtr browser)重写
		调试输出(__函数名__, " ", U2W(__文件__), " ", __行号__)
		CEF_REQUIRE_UI_THREAD()
		如果 FALSE == m_browser->IsSame(browser)
			返回
		m_browser = NULL
		CefQuitMessageLoop()
		this->Release()
	
	函数 虚函数 void AddRef()const 重写
		ref_count_.AddRef()
	
	函数 虚函数 bool Release()const 重写
		如果 ref_count_.Release()
			delete this
			返回 TRUE
		返回  FALSE
	
	函数 虚函数 bool HasOneRef()const 重写
		返回 ref_count_.HasOneRef()
	
	CefBrowserPtr   m_browser //CefBrowser*
	CefRefCount   ref_count_
	HWINDOW m_hWindow
	逻辑型   m_bShow

类 CMainFrame
	HWINDOW     m_hWindow
	CBrowserViewPtr   m_BrowserView //CBrowserView*

	函数  逻辑型 Run()
		m_hWindow = XWnd_Create(0, 0, 1024 + 40, 800, "炫彩界面库-窗口")
		如果 m_hWindow
			HELE hButton = XBtn_Create(1024 - 80, 0, 60, 25, "关闭", m_hWindow)//创建按钮
			XObj_SetTypeEx(hButton, button_type_close)

			m_BrowserView = new CBrowserView
			m_BrowserView->Create(20, 30, 1024, 800 - 50, m_hWindow, "http://www.baidu.com")
			
			XWnd_ShowWindow(m_hWindow, SW_SHOW)//显示窗口
			返回 TRUE
		返回 FALSE

	函数 空类型 Exit()
		m_BrowserView = NULL
	
函数 整型 入口函数_窗口()//窗口程序入口
	调试输出("你好")
	调试输出(A"你好")
	CefMainArgs main_args(模块句柄)
	整型 exit_code = CefExecuteProcess(main_args, NULL, NULL)
	如果 exit_code >= 0
		返回 exit_code
		
	XInitXCGUI(真)//初始化
	
	CefSettings settings
	settings.no_sandbox = TRUE
	settings.single_process = FALSE
	
	CefInitialize(main_args, settings, NULL, NULL)
	
	CMainFrame  mainFrame
	mainFrame.Run()

	CefRunMessageLoop()
	XRunXCGUI()//运行
	CefShutdown()
	XExitXCGUI()//释放资源
	返回 0

