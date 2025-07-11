#ifndef HEAD_51117D62_6C61_4c9d_AA93_C6252A6197EE
#define HEAD_51117D62_6C61_4c9d_AA93_C6252A6197EE
class 我的主窗口类;
class 我的主窗口类  :  public  CXWindow
{
public:
	CXButton _按钮1;
	CXEdit _编辑框1;
	CXText _布局文件= L"main.xml" ;
	int  运行();
	int  事件_按钮1_点击(BOOL* 是否拦截);
};
int WINAPI wWinMain(HINSTANCE 模块句柄, HINSTANCE 先前句柄, wchar_t* 命令行, int 窗口显示标识);
#endif
