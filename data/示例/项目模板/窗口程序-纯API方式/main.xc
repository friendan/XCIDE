类 我的主窗口
	窗口句柄  m_hWindow
	函数 整型 Run()
		逻辑型 bRes = 炫彩_加载资源文件("resource.res")
		m_hWindow = (窗口句柄)炫彩_加载布局文件("main.xml", 0)
		元素_注册事件CPP(炫彩_取对象从名称("button1"), 元素事件_按钮点击, &我的主窗口::OnBtnClick)
		
		窗口_调整布局(m_hWindow)
		窗口_显示(m_hWindow, 真)
		返回 0

	函数 整型 OnBtnClick(BOOL *是否拦截)
		返回 0

函数 整型  入口函数_窗口()
	炫彩_初始化(真)
	炫彩_启用自动重绘UI(真)
	我的主窗口  我的主窗口
	我的主窗口.Run()
	炫彩_运行()
	炫彩_退出()
	返回 0

// [文档]<炫语言> 在线手册: http://www.xcgui.com/doc
// [视频]<炫语言> 入门教程: https://www.bilibili.com/video/BV1KM411h7KK
//
// [文档]<炫彩界面库> 最新在线文档: http://www.xcgui.com/doc-ui
// [视频]<炫彩界面库> 通用教程: https://www.bilibili.com/video/BV1kA411A71p/
//
// [商城]炫彩资源商城: http://mall.xcgui.com
