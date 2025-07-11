#外部类型 DWORD_PTR

类 我的主窗口类 继承 窗口类
	[绑定信息] //IDE生成的UI绑定信息(UI变量,事件), 支持手动修改, 可收缩隐藏
		[布局类, _布局, "布局"]
	文本型  _布局文件= "main.xml"
	//窗口类初始化函数, 自动处理关联的窗口布局文件和绑定的变量
	函数 整型 运行()
		//从RC资源中获取图标
		HXCGUI hPic = 形状图片_创建(0,0,256,256,_布局._句柄)
		HICON  hIco = RC资源查找图标("IDI_ICON1")
		形状图片_置图片(hPic, 图片_加载从HICON(hIco))

		hIco = RC资源查找图标2("IDI_ICON2", 256, 256)
		hPic = 形状图片_创建(0,0,256,256,_布局._句柄)
		形状图片_置图片(hPic, 图片_加载从HICON(hIco))

		hPic = 形状图片_创建(0,0,256,256,_布局._句柄)
		hIco = RC资源查找图标2("IDI_ICON3", 256, 256)
		形状图片_置图片(hPic, 图片_加载从HICON(hIco))

		//从RC资源中获取图片文件
		UINT  dwSize
		void *data = RC资源查找文件("IDR_PNG3", &dwSize, NULL, "PNG")
		HIMAGE hImage = 图片_加载从内存(data, dwSize)
		hPic = 形状图片_创建(0,0,256,256,_布局._句柄)
		形状图片_置图片(hPic, hImage)

		//从exe文件中提取图标,不同大小图标
		显示文件图标("C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQ.exe", 图标类型32, 256,256);
		显示文件图标("C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQ.exe", 图标类型16, 256, 256);
		显示文件图标("C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQ.exe", 图标类型48, 256, 256);
		显示文件图标("C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQ.exe", 图标类型系统16, 256, 256);
		显示文件图标("C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQ.exe", 图标类型256, 256, 256);

		窗口_显示(_句柄, TRUE)
		返回 0

	函数  显示文件图标(文本型 文件名, 整型 类型, 整型 宽度,  整型  高度)
		HICON hIcon = 0
		SHFILEINFO sfi = {0}
		DWORD_PTR hr = SHGetFileInfo(文件名.取地址(), 0, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX)
		如果  hr>0
			IImageList* imageList = 空
			HRESULT hResult = SHGetImageList(类型, IID_IImageList, (void**)&imageList);
			if (hResult == S_OK)
				hResult = ((IImageList *)imageList)->GetIcon(sfi.iIcon, ILD_TRANSPARENT, &hIcon);
		HXCGUI  hPic = 形状图片_创建(20, 20, 宽度, 高度, _布局._句柄);
		形状图片_置图片(hPic, 图片_加载从HICON(hIcon));
		返回

函数 整型 入口函数_窗口()
	炫彩_初始化(真)
	炫彩_显示布局边界(真)
	炫彩_启用自动重绘UI(真)
	#加载资源文件

	我的主窗口类  我的主窗口
	我的主窗口.运行()
	
	炫彩_运行()
	炫彩_退出()
	返回 0