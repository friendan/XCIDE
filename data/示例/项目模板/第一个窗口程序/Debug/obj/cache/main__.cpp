#include "common__.h"
#include "main__.h"
extern 我的主窗口类 我的主窗口;
int 我的主窗口类::运行()
{
	{
	HMODULE __hModule = GetModuleHandle(NULL);
	UINT __size = 0;
	void* __data = rc_findFileByID(IDR_UI_ZIP, &__size, __hModule);
	if (__data) {
		m_hWindow = (HWINDOW)XC_LoadLayoutZipMemEx(__data, __size, _布局文件, NULL, NULL, NULL, NULL, NULL);
	}
#ifdef _DEBUG
	if(NULL==m_hWindow) {MessageBox(NULL, L"句柄为空:\"m_hWindow\"", L"提示", 0); return 0;}
#endif
	_按钮1.m_hEle = (HELE)XC_GetObjectByName(L"按钮1");
	_编辑框1.m_hEle = (HELE)XC_GetObjectByName(L"编辑框1");
#ifdef _DEBUG
if(NULL==_按钮1.m_hEle) {MessageBox(NULL, L"绑定变量句柄为空:\"_按钮1\"", L"提示", 0); return 0;}
if(NULL==_编辑框1.m_hEle) {MessageBox(NULL, L"绑定变量句柄为空:\"_编辑框1\"", L"提示", 0); return 0;}
#endif
	XEle_RegEventCPP(_按钮1.m_hEle, XE_BNCLICK, &我的主窗口类::事件_按钮1_点击);
	}
	Show(TRUE) ;
	return 0;
}
int 我的主窗口类::事件_按钮1_点击(BOOL* 是否拦截)
{
	xcl_log2(L"按钮点击 编辑框内容:", _编辑框1.GetText());
	return 0;
}
我的主窗口类 我的主窗口;
int WINAPI wWinMain(HINSTANCE 模块句柄, HINSTANCE 先前句柄, wchar_t* 命令行, int 窗口显示标识)
{
	XInitXCGUI(TRUE) ;
	XC_EnableAutoRedrawUI(TRUE) ;
	HMODULE __hModule = GetModuleHandle(NULL);
	UINT __size = 0;
	void* __data = rc_findFileByID(IDR_UI_ZIP, &__size, __hModule);
	BOOL __bRetRes = XC_LoadResourceZipMem(__data, __size, LR"--(resource.res)--");
	if(0==__bRetRes) xcl_log(L"*加载资源文件失败: resource.res");
	我的主窗口.运行() ;
	XRunXCGUI() ;
	XExitXCGUI() ;
	return 0;
}
