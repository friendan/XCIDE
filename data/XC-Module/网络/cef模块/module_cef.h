#ifndef  MODULE_CEF_H
#define  MODULE_CEF_H

#include "include/cef_client.h"
#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/cef_parser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

#pragma comment(lib, "libcef.lib")

#ifdef   _DEBUG
#pragma comment(lib, "libcef_dll_wrapperd.lib")
#else
#pragma comment(lib, "libcef_dll_wrapper.lib")
#endif

//@模块名称  cef模块
//@版本  1.0  
//@日期  2020-11-17
//@作者  XCGUI  
//@模块备注  cef,  
//由于此模块包含文件比较大,所以需单独下载
//@依赖  module_base.h

class  CBrowserViewBase : public  CefClient , public CefDisplayHandler , public CefLifeSpanHandler , public CefLoadHandler
{
public:
/*@声明
	void AddRef();
	bool Release();
*/
};

/*@声明

class CefRefPtr
{
	const static short _a =10;
};

class CefString
{
	const wchar_t* c_str();
};

class CefBrowser
{
	CefBrowserHostPtr GetHost();
	 virtual bool IsSame(CefBrowserPtr that);
};
class CefLoadHandler
{
};

class CefBrowserHost
{
	bool CreateBrowser(...);
	 virtual HWND GetWindowHandle();
};

class CefWindowInfo
{
	void SetAsChild(HWND parent, RECT windowRect);
};
class CefBrowserSettings
{
	UINT background_color;
};

class CefMainArgs
{
};

class CefRefCount
{
	void AddRef() ;
	bool Release();
	bool HasOneRef();
};

struct CefSettings
{
	int single_process;
	int no_sandbox;
};

class CefClient
{
};

class CefDisplayHandler
{
};

class CefLifeSpanHandler
{
};

int CefExecuteProcess(...);
bool CefInitialize(...);
void CefRunMessageLoop();
void CefQuitMessageLoop();
void CefShutdown();


*/

#endif