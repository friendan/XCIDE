
函数 LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	switch (Message)
		case WM_DESTROY
			//PostQuitMessage(0)//可以使GetMessage函数返回0,从而结束消息循环
			PostMessage(hwnd, WM_QUIT, 0, 0)//上面PostQuitMessage函数就是按这个投递的WM_QUIT=关闭消息循环
			break
		case WM_CREATE
			//可以在这里创建组件等
			break

	
	return DefWindowProc(hwnd, Message, wParam, lParam)

函数 整型 入口函数_窗口() //窗口程序入口函数, 程序启动优先进入此函数
	
	//注册窗口信息
	WNDCLASSEX wc = {0}//初始化结构赋值为0
	wc.cbSize = sizeof(WNDCLASSEX)
	wc.lpfnWndProc = WndProc
	wc.hInstance = 模块句柄
	wc.hCursor = LoadCursor(NULL, IDC_ARROW)//设置默认光标
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1)//设置背景颜色白色
	wc.lpszClassName = "WindowClass"
	HICON icon = RC资源查找图标("IDI_ICON")//取程序图标
	wc.hIcon = icon//状态栏图标
	wc.hIconSm = icon//窗口图标
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS//注意如果不加CS_DBLCLKS风格将不会接收鼠标双击消息
	if (!RegisterClassEx(&wc))
		MessageBox(NULL, "窗口注册失败!", "错误", MB_ICONEXCLAMATION | MB_OK)
		return 0
	// 计算屏幕宽度和高度
	int screenWidth = GetSystemMetrics(SM_CXSCREEN)
	int screenHeight = GetSystemMetrics(SM_CYSCREEN)
	// 计算窗口宽度和高度
	int nWidth = 500
	int nHeight = 400
	// 计算窗口左上角的位置
	int x = (screenWidth - nWidth) / 2
	int y = (screenHeight - nHeight) / 2
	HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_ACCEPTFILES, "WindowClass", "炫语言黑月界面", WS_OVERLAPPEDWINDOW, x, y, nWidth, nHeight, NULL, NULL, 模块句柄, NULL)
	if (hwnd == NULL)
		MessageBox(NULL, "创建窗口失败!", "错误", MB_ICONEXCLAMATION | MB_OK)
		return 0

	ShowWindow(hwnd, SW_SHOW)//显示窗口
	UpdateWindow(hwnd)//更新窗口
	//消息循环
	MSG Msg = {0}
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
		TranslateMessage(&Msg)//翻译消息,如:按键,不可见的不处理
		DispatchMessage(&Msg)//派发消息,将消息交给处理函数来处理
	return 0

// [文档]<炫语言> 在线手册: http://www.xcgui.com/doc
// [视频]<炫语言> 入门教程: https://www.bilibili.com/video/BV1KM411h7KK
//
// [文档]<炫彩界面库> 最新在线文档: http://www.xcgui.com/doc-ui
// [视频]<炫彩界面库> 通用教程: https://www.bilibili.com/video/BV1kA411A71p/
//
// [商城]炫彩资源商城: http://mall.xcgui.com
//
// *新手尽量不要使用指针, 例如: 字符串使用"文本型", 函数参数若要返回值使用引用 "函数名(整型 &输入输出参数)",
//  内存使用"字节集"
//
//  文本型   双字节字符串  =  炫语言默认字符串类型  =  "字符串W"
//  文本型A  单字节字符串  =  易语言字符串类型     =  A"字符串A"
//  utf8字符串  = U"UTF8字符串"
//  A2W()   单字节字符串 转 双字节字符串
//  W2A()   双字节字符串 转 单字节字符串
//  A =  char    =  单字节
//  w =  wchar_t = 双字节 = UNICODE
//  两个文件中结构体类型互相包含导致冲突, 请将结构体定义移动到一个独立文件中
