#pragma once
#include <shlwapi.h>
#pragma  comment(lib, "Shlwapi.lib")
#include <shlobj.h>
#include <commoncontrols.h>
#pragma  comment(lib, "Shell32.lib")
#pragma comment(lib, "urlmon.lib")
#include <commdlg.h>
#pragma comment(lib, "Comdlg32.lib")

//@模块名称  系统API(前缀分类法)
//@版本  1.0  
//@日期  2025-01-21
//@作者  XCGUI  
//@QQ  154460336
//@模块备注  windows-API
// 此模块 按照 <前缀分类命名法> 规范, 例如: A线程_创建() 命名为 A线程_创建();
// 前缀添加 "A" 目的是避免与其他模块名称产生冲突, "A" 代表 "系统API模块"
// 若是旧项目不想升级到此模块, 可使用旧版的 <系统API> 模块
// https://learn.microsoft.com/zh-cn/windows/win32/api/
// 关于同步 https://docs.microsoft.com/en-us/windows/win32/sync/about-synchronization

//@依赖  module_base.h


/*@声明
//@分组{   路径
//@备注 用于创建一个新目录
//@参数 目录路径
//@参数 安全属性指针（可选）
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A目录_创建()
BOOL CreateDirectory(LPCTSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

//@备注 用于删除一个空目录
//@参数 目录路径
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A目录_删除()
BOOL RemoveDirectory(LPCTSTR lpPathName);

//@备注 用于获取当前工作目录
//@参数 输出当前目录路径
//@参数 缓冲区大小
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A目录_取当前目录()
DWORD GetCurrentDirectory(DWORD nBufferLength, LPTSTR lpBuffer);

//@备注 用于设置当前工作目录
//@参数 目标目录路径
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A目录_置当前目录()
BOOL SetCurrentDirectory(LPCTSTR lpPathName);

//@参数 pszDest 缓冲区指针 当此函数成功返回时，该缓冲区接收组合的路径字符串。必须将此缓冲区的大小设置为MAX_PATH，以确保其大小足以容纳返回的字符串
//@参数 pszDir 欲要合并的路径1 指向包含第一个路径的最大长度MAX_PATH以 null 结尾的字符串的指针。此值可以为 NULL
//@参数 pszFile 欲要合并的路径2 指向包含第二个路径的最大长度MAX_PATH以 null 结尾的字符串的指针。 此值可以为 NULL
//@返回 指向缓冲区的指针，当此函数成功返回时，该缓冲区接收串联的路径字符串。如果此函数未成功返回，则此值为 NULL
//@别名 A路径_合并(缓冲区指针,欲要合并的路径1,欲要合并的路径2)
wchar_t* PathCombine(wchar_t*  pszDest, const wchar_t* pszDir, const wchar_t* pszFile);

//@备注 创建从一个文件或文件夹到另一个文件或文件夹的相对路径
//@参数 pszPath 缓冲区指针 指向接收相对路径的字符串的指针。 此缓冲区的大小必须至少为MAX_PATH个字符
//@参数 pszFrom 该字符串包含定义相对路径的开头的路径
//@参数	dwAttrFrom pszFrom的文件属性。如果此值包含 FILE_ATTRIBUTE_DIRECTORY，则假定 pszFrom 是一个目录；否则，假定 pszFrom 是一个文件
//@参数 pszTo 该字符串包含定义相对路径的终结点的路径
//@参数 dwAttrTo pszTo的文件属性。如果此值包含 FILE_ATTRIBUTE_DIRECTORY，则 假定 pszTo 为 directory;否则，假定 pszTo 为文件
//@返回 如果成功返回TRUE，否则返回false
//@别名 A路径_到相对路径(缓冲区指针,文件路径)
BOOL PathRelativePathTo(wchar_t*  pszPath, const wchar_t* pszFrom, DWORD dwAttrFrom, const wchar_t* pszTo, DWORD dwAttrTo);

//@备注 一个有效的扩展名是不包括空格的。
//@参数 pszPath 欲要查找的文件路径,指向以0结尾，最大长度为MAX_PATH文件路径字符串指针。
//@返回 如果扩展名找到则返回pszPath字符串中“.”所在地址，否则返回空字符结尾地址。
//@别名 A路径_取后缀名(欲要查找的文件路径)
const wchar_t* PathFindExtension(const wchar_t* pszPath);

//@备注 从路径中删除文件扩展名
//@参数 pszPath 文件路径,
//@返回 移除后的文件路径,不包含扩展名
//@别名 A路径_删除后缀名(文件路径)
void PathRemoveExtension(wchar_t* pszPath);

//@备注 用于从路径字符串中提取文件名部分
//@参数 pszPath 欲要查找的文件路径
//@返回 函数返回指向文件名的指针（如果找到的话），否则返回指向路径开头的指针。
//@别名 A路径_取文件名(欲要查找的文件路径)
const wchar_t* PathFindFileName(const wchar_t* pszPath);

//@备注 尤其是在需要分离路径和文件名的场景中。使用时需要注意路径格式和返回值可能为空的情况
//@参数 pszPath 欲要检查的文件路径 该字符串包含要验证的对象的完整路径
//@返回 如果该文件存在返回TRUE，否则返回false
//@别名 A路径_文件是否存在(欲要检查的文件路径)
BOOL PathFileExists(const wchar_t* pszPath);

//@备注 删除路径字符串中的最后一个元素，无论该元素是文件名还是目录名称。元素的前导反斜杠也会被删除
//@参数 pszPath 文件路径,指向长度为MAX_PATH的空终止字符串的指针，该字符串包含要从中删除文件名的路径。
//@返回 如果已删除某些内容，则返回非零值；否则返回零。
//@别名 A路径_删除最后元素(文件路径)
BOOL PathRemoveFileSpec(wchar_t* pszPath);

//@分组}


//@分组{  窗口

#ifndef SW_HIDE
    #define SW_HIDE             0   //@别名 窗口显示标识_隐藏
    #define SW_SHOWNORMAL       1   //@别名 窗口显示标识_显示并激活还原
    #define SW_SHOWMINIMIZED    2	//@别名 窗口显示标识_显示并最小化
    #define SW_SHOWMAXIMIZED    3	//@别名 窗口显示标识_显示并最大化
    #define SW_SHOWNOACTIVATE   4	//@别名 窗口显示标识_显示不激活
    #define SW_SHOW             5	//@别名 窗口显示标识_显示
    #define SW_MINIMIZE         6	//@别名 窗口显示标识_最小化
    #define SW_SHOWMINNOACTIVE  7	//@别名 窗口显示标识_最小化不激活
    #define SW_SHOWNA           8	//@别名 窗口显示标识_显示不激活2
    #define SW_RESTORE          9	//@别名 窗口显示标识_还原
    #define SW_SHOWDEFAULT      10	//@别名 窗口显示标识_启动初始值
    #define SW_FORCEMINIMIZE    11	//@别名 窗口显示标识_强制最小化
#endif

//@备注 用于使指定矩形区域无效（需要重绘）
//@参数 窗口句柄
//@参数 矩形区域指针
//@参数 是否擦除背景
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_无效矩形()
BOOL InvalidateRect(HWND hWnd,const RECT *lpRect,BOOL bErase);

//@备注 用于将指定的数据（通常是一个句柄或指针）与窗口关联起来
//@参数 窗口句柄
//@参数 属性名称（字符串或原子）
//@参数 要关联的数据（句柄或指针）
//@返回 如果函数成功，返回值为非零值（TRUE）。如果函数失败，返回值为零（FALSE）
//@别名 A窗口_置属性()
BOOL WINAPI SetProp(HWND hWnd,LPCWSTR lpString, HANDLE hData);

//@备注 用于从指定窗口中检索之前通过 SetProp 函数设置的属性值
//@参数 窗口句柄
//@参数 属性名称（字符串或原子）
//@返回 如果找到属性，返回与之关联的数据（通常是一个句柄或指针） 如果未找到属性，返回 NULL
//@别名 A窗口_取属性()
HANDLE WINAPI GetProp(HWND hWnd,LPCWSTR lpString);

//@备注 用于设置窗口的区域（Region）。窗口区域定义了窗口的可视部分，只有区域内的部分才会显示
// 区域外的部分会被裁剪掉。通过设置窗口区域，可以实现非矩形窗口（如圆形、椭圆形或不规则形状的窗口）
//@参数 窗口句柄
//@参数 区域句柄
//@参数 是否重绘窗口
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_置区域()
int WINAPI SetWindowRgn(HWND hWnd,HRGN hRgn, BOOL bRedraw);

//@备注 用于获取窗口的区域信息。这个区域可以是矩形、椭圆形、多边形或复杂的自定义形状，它定义了窗口的可见部分。
//@参数 窗口句柄
//@参数 区域句柄
//@返回 区域句柄
//@别名 A窗口_取区域()
int WINAPI GetWindowRgn( __in HWND hWnd,  __in HRGN hRgn);

//@备注 最小化窗口 (但不销毁指定窗口)
//@别名 A窗口_关闭(窗口句柄)
BOOL CloseWindow(HWND hWnd);

//@别名 A窗口_更新()
BOOL UpdateWindow(HWND hWnd);

//@备注 用于创建一个重叠窗口、弹出窗口或子窗口
//@参数 窗口类名
//@参数 窗口标题
//@参数 窗口风格
//@参数 左边
//@参数 顶边
//@参数 宽度
//@参数 高度
//@参数 父窗口句柄
//@参数 菜单句柄
//@参数 模块句柄
//@参数 附加值
//@返回 如果函数成功，返回值为新窗口的句柄 如果函数失败，返回值为NULL
//@别名 A窗口_创建(窗口类名,窗口标题,窗口风格,左边,顶边,宽度,高度,父窗口句柄,菜单句柄,模块句柄,附加值)
HWND CreateWindow(
    LPCTSTR lpClassName,
    LPCTSTR lpWindowName,
    DWORD dwStyle,
    int x,
    int y,
    int nWidth,
    int nHeight,
    HWND hWndParent,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam
);

//@备注 用于更新指定窗口的指定区域或全部区域
//@参数 窗口句柄
//@参数 更新区域矩形指针（可选）
//@参数 更新区域句柄（可选）
//@参数 重画标志
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_重画()
BOOL RedrawWindow(
    HWND hWnd,
    const RECT *lprcUpdate,
    HRGN hrgnUpdate,
    UINT flags
);

//@备注 用于创建一个具有扩展风格的窗口
//@参数 扩展窗口风格
//@参数 窗口类名
//@参数 窗口标题
//@参数 窗口风格
//@参数 左边
//@参数 顶边
//@参数 宽度
//@参数 高度
//@参数 父窗口句柄
//@参数 菜单句柄
//@参数 模块句柄
//@参数 附加值
//@返回 如果函数成功，返回值为新窗口的句柄 如果函数失败，返回值为NULL
//@别名 A窗口_创建窗口扩展()
HWND CreateWindowEx(
    DWORD dwExStyle,
    LPCWSTR lpClassName,
    LPCWSTR lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam
);

//@备注 用于更新多个窗口的位置和大小
//@参数 多窗口位置信息句柄
//@参数 窗口句柄
//@参数 插入位置窗口句柄
//@参数 左边
//@参数 顶边
//@参数 宽度
//@参数 高度
//@参数 标志
//@返回 如果函数成功，返回值为更新后的多窗口位置信息句柄 如果函数失败，返回值为NULL
//@别名 A窗口_更新多窗口位置()
HDWP DeferWindowPos(
  HDWP hWinPosInfo,
  HWND hWnd,
  HWND hWndInsertAfter,
  int  x,
  int  y,
  int  cx,
  int  cy,
  UINT uFlags
);

//@备注 用于完成多个窗口的位置和大小更新
//@参数 多窗口位置信息句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_更新多窗口位置结束()
BOOL EndDeferWindowPos(
  HDWP hWinPosInfo
);

//@备注 用于销毁指定窗口及其子窗口
//@参数 窗口句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_销毁()
BOOL DestroyWindow(HWND hWnd);

//@备注 用于处理窗口的默认消息
//@参数 窗口句柄
//@参数 消息
//@参数 消息参数1
//@参数 消息参数2
//@返回 消息处理结果
//@别名 A窗口_调用默认窗口过程()
LRESULT DefWindowProc(
  HWND   hWnd,
  UINT   Msg,
  WPARAM wParam,
  LPARAM lParam
);

//@备注 用于枚举指定窗口的所有子窗口
//@参数 父窗口句柄
//@参数 枚举回调函数
//@参数 附加参数
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_枚举子窗口()
BOOL EnumChildWindows(
  HWND        hWndParent,
  WNDENUMPROC lpEnumFunc,
  LPARAM      lParam
);

//@备注 用于查找具有指定类名和窗口标题的顶级窗口
//@参数 窗口类名
//@参数 窗口标题
//@返回 如果找到窗口，返回值为窗口句柄 如果未找到，返回值为NULL
//@别名 A窗口_查找()
HWND FindWindow(
  LPCWSTR lpClassName,
  LPCWSTR lpWindowName
);
//@备注 用于查找具有指定类名和窗口标题的子窗口
//@参数 窗口类名
//@参数 父窗口句柄
//@参数 子窗口句柄
//@参数 窗口标题
//@返回 如果找到窗口，返回值为窗口句柄 如果未找到，返回值为NULL
//@别名 A窗口_查找扩展()
HWND FindWindowEx(
  HWND    hWndParent,
  HWND    hWndChildAfter,
  LPCWSTR lpszClass,
  LPCWSTR lpszWindow
);
//@备注 用于获取指定窗口类的信息
//@参数 模块句柄
//@参数 窗口类名
//@参数 窗口类结构指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_取窗口类信息()
BOOL GetClassInfo(
  HINSTANCE   hInstance,
  LPCWSTR     lpClassName,
  LPWNDCLASSW lpWndClass
);

//@别名 A窗口_置窗口类数值Ptr()
ULONG_PTR SetClassLongPtr(
  HWND     hWnd,
  int      nIndex,
  LONG_PTR dwNewLong
);

//@备注 用于获取指定窗口的类名
//@参数 窗口句柄
//@参数 接收类名的缓冲区
//@参数 缓冲区大小
//@返回 复制的字符数
//@别名 A窗口_取窗口类名()
int GetClassName(
  HWND   hWnd,
  LPTSTR lpClassName,
  int    nMaxCount
);

//@备注 用于获取桌面窗口的句柄
//@返回 桌面窗口的句柄
//@别名 A窗口_取桌面窗口()
HWND GetDesktopWindow();

//@别名 A窗口_激活前台窗口()
BOOL SetForegroundWindow(HWND hWnd);

//@备注 返回值是前台窗口的句柄。在某些情况下，前台窗口可以为 NULL ，例如，当窗口失去激活时
//@返回 前台窗口的句柄
//@别名 A窗口_取前台窗口()
HWND GetForegroundWindow();

//@备注 用于锁定或解锁前台窗口
//@参数 锁定代码
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_置前台窗口锁定()
BOOL LockSetForegroundWindow(UINT uLockCode);

//@备注 用于获取指定线程的界面信息
//@参数 线程ID
//@参数 界面线程信息结构指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_取界面线程信息()
BOOL GetGUIThreadInfo(DWORD idThread, PGUITHREADINFO pgui);

//@备注 用于获取指定窗口的下一个窗口
//@参数 窗口句柄
//@参数 查找命令
//@返回 下一个窗口的句柄
//@别名 A窗口_取下一个()
HWND GetNextWindow(HWND hWnd, UINT wCmd);

//@备注 用于获取指定窗口的顶级窗口
//@参数 窗口句柄
//@返回 顶级窗口的句柄
//@别名 A窗口_取顶级窗口()
HWND GetTopWindow(HWND hWnd);

//@备注 用于获取与指定窗口有特定关系的窗口
//@参数 窗口句柄
//@参数 查找命令
//@返回 目标窗口的句柄
//@别名 A窗口_取窗口()
HWND GetWindow(HWND hWnd, UINT uCmd);

//@备注 用于获取指定窗口的父窗口
//@参数 窗口句柄
//@返回 父窗口的句柄
//@别名 A窗口_取父()
HWND GetParent(HWND hWnd);

//@备注 用于设置指定窗口的父窗口
//@参数 hWndChild 子窗口句柄
//@参数 hWndNewParent 新的父窗口句柄
//@返回 如果函数成功，返回值为之前的父窗口句柄；如果函数失败，返回值为NULL
//@别名 A窗口_置父()
HWND SetParent(
  HWND hWndChild,
  HWND hWndNewParent
);

//@备注 用于获取Shell桌面窗口的句柄
//@返回 Shell桌面窗口的句柄
//@别名 A窗口_取Shell窗口()
HWND GetShellWindow();

//@备注 用于获取窗口的额外信息
//@参数 窗口句柄
//@参数 索引
//@返回 指定偏移处的值
//@别名 A窗口_取数值()
LONG GetWindowLong(
  HWND hWnd,
  int  nIndex
);

//@备注 用于获取窗口的额外信息（64位兼容）
//@参数 窗口句柄
//@参数 索引
//@返回 指定偏移处的值
//@别名 A窗口_取数值Ptr()
LONG_PTR GetWindowLongPtr(HWND hWnd, int nIndex);

//@备注 用于设置窗口的额外信息（64位兼容）
//@参数 hWnd 窗口句柄
//@参数 nIndex 指定要设置的值的偏移量
//@参数 dwNewLong 要设置的新值
//@返回 如果函数成功，返回值为之前的值；如果函数失败，返回值为0
//@别名 A窗口_置数值Ptr()
LONG_PTR SetWindowLongPtr(HWND hWnd, int  nIndex, LONG_PTR dwNewLong);

//@备注 用于设置窗口的额外信息
//@参数 hWnd 窗口句柄
//@参数 nIndex 指定要设置的值的偏移量
//@参数 dwNewLong 要设置的新值
//@返回 如果函数成功，返回值为之前的值；如果函数失败，返回值为0
//@别名 A窗口_置数值()
LONG SetWindowLong(HWND hWnd, int  nIndex, LONG dwNewLong);

//@备注 用于获取与指定窗口关联的模块文件名
//@参数 窗口句柄
//@参数 接收文件名的缓冲区
//@参数 缓冲区大小
//@返回 复制的字符数
//@别名 A窗口_取所属模块文件名()
UINT GetWindowModuleFileName(
  HWND   hwnd,
  LPWSTR pszFileName,
  UINT   cchFileNameMax
);

//@备注 该函数返回指定窗口的显示状态以及被恢复的、最大化的和最小化的窗口位置
//@参数 窗口句柄
//@参数 窗口位置结构指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_取位置信息()
BOOL GetWindowPlacement(HWND hWnd, WINDOWPLACEMENT *lpwndpl);

@备注 设置指定窗口的显示状态和还原、最小化和最大化的位置
@别名 A窗口_置位置信息()
BOOL SetWindowPlacement(HWND  hWnd, const WINDOWPLACEMENT *lpwndpl);

//@备注 用于获取指定窗口的标题
//@参数 窗口句柄
//@参数 接收文本的缓冲区
//@参数 缓冲区大小
//@返回 复制的字符数
//@别名 A窗口_取标题()
int GetWindowText(
  HWND   hWnd,
  LPWSTR lpString,
  int    nMaxCount
);

//@备注 用于设置指定窗口的标题
//@参数 窗口句柄
//@参数 要设置的文本
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_置标题()
BOOL SetWindowText(
    HWND hWnd,
    LPCWSTR lpString
);

//@备注 用于获取指定窗口标题的长度
//@参数 窗口句柄
//@返回 窗口标题的长度
//@别名 A窗口_取文本长度()
int GetWindowTextLength(HWND hWnd);

//@备注 用于获取创建指定窗口的线程和进程的ID
//@参数 窗口句柄
//@参数 进程ID指针
//@返回 线程ID
//@别名 A窗口_取窗口线程进程ID()
DWORD GetWindowThreadProcessId(HWND hWnd, LPDWORD lpdwProcessId);

//@备注 用于判断指定窗口是否为另一个窗口的子窗口
//@参数 父窗口句柄
//@参数 窗口句柄
//@返回 如果窗口是子窗口，返回值为非零值 否则返回值为零
//@别名 A窗口_是否子窗口()
BOOL IsChild(HWND hWndParent, HWND hWnd);

//@备注 用于判断调用线程是否为界面线程
//@参数 是否转换为界面线程
//@返回 如果调用线程是界面线程，返回值为非零值 否则返回值为零
//@别名 A窗口_是否界面线程()
BOOL IsGUIThread(BOOL bConvert);

//@备注 用于判断指定窗口是否是最小化的
//@参数 窗口句柄
//@返回 如果窗口是最小化的，返回值为非零值 否则返回值为零
//@别名 A窗口_是否最小化()
BOOL IsIconic(HWND hWnd);

//@备注 用于判断指定窗口是否是最大化的
//@参数 窗口句柄
//@返回 如果窗口是最大化的，返回值为非零值 否则返回值为零
//@别名 A窗口_是否最大化()
BOOL IsZoomed(HWND hWnd);

//@备注 用于判断指定句柄是否为窗口句柄
//@参数 窗口句柄
//@返回 如果句柄是窗口句柄，返回值为非零值 否则返回值为零
//@别名 A窗口_是否窗口()
BOOL IsWindow(HWND hWnd);

//@备注 用于判断指定窗口是否为Unicode窗口
//@参数 窗口句柄
//@返回 如果窗口是Unicode窗口，返回值为非零值 否则返回值为零
//@别名 A窗口_是否Unicode窗口()
BOOL IsWindowUnicode(HWND hWnd);

//@备注 用于判断指定窗口是否可见
//@参数 窗口句柄
//@返回 如果窗口是可见的，返回值为非零值 否则返回值为零
//@别名 A窗口_是否显示()
BOOL IsWindowVisible(HWND hWnd);

//@别名 A窗口_置定时器()
UINT_PTR SetTimer(
  HWND      hWnd,
  UINT_PTR  nIDEvent,
  UINT      uElapse,
  TIMERPROC lpTimerFunc
);

//@备注 用于关闭指定定时器
//@参数 窗口句柄
//@参数 定时器ID
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_关闭定时器()
BOOL KillTimer(HWND hWnd, UINT_PTR uIDEvent);

//@备注 用于移动或调整窗口大小
//@参数 窗口句柄
//@参数 左边
//@参数 顶边
//@参数 宽度
//@参数 高度
//@参数 是否重绘
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_移动()
BOOL MoveWindow(
  HWND hWnd,
  int  X,
  int  Y,
  int  nWidth,
  int  nHeight,
  BOOL bRepaint
);

//@备注 用于获取指定窗口的基础类名
//@参数 窗口句柄
//@参数 接收类名的缓冲区
//@参数 缓冲区大小
//@返回 复制的字符数
//@别名 A窗口_取真实类名()
UINT RealGetWindowClass(HWND hwnd, LPWSTR ptszClassName, UINT cchClassNameMax);

//@备注 用于注册窗口类
//@参数 窗口类结构指针
//@返回 如果函数成功，返回值为窗口类原子 如果函数失败，返回值为零
//@别名 A窗口_注册窗口类()
ATOM RegisterClass(const WNDCLASSW *lpWndClass);

//@备注 用于注册扩展窗口类
//@参数 窗口类扩展结构指针
//@返回 如果函数成功，返回值为窗口类原子 如果函数失败，返回值为零
//@别名 A窗口_注册窗口类扩展()
ATOM RegisterClassEx(const WNDCLASSEXW *Arg1);

//@备注 用于取消注册指定的窗口类
//@参数 窗口类名
//@参数 模块句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_取消注册窗口类()
BOOL UnregisterClass(
    LPCWSTR lpClassName,
    HINSTANCE hInstance
);

//@别名 A窗口_置窗口类数值()
DWORD SetClassLong(
  HWND hWnd,
  int  nIndex,
  LONG dwNewLong
);

//@备注 用于获取窗口类的额外信息
//@参数 窗口句柄
//@参数 索引
//@返回 指定偏移处的值
//@别名 A窗口_取窗口类数值()
ULONG_PTR GetClassLongPtr(HWND hWnd, int  nIndex);

//@别名 A窗口_置分层属性()
BOOL SetLayeredWindowAttributes(
  HWND     hwnd,
  COLORREF crKey,
  BYTE     bAlpha,
  DWORD    dwFlags
);

//@别名 A窗口_置焦点()
HWND WINAPI SetFocus(HWND hWnd);

//@别名 A窗口_取焦点()
HWND WINAPI GetFocus();

//@别名 A窗口_取活动窗口()
HWND WINAPI GetActiveWindow();

//@备注 显示或隐藏指定窗口拥有的所有弹出窗口
//@参数 窗口句柄
//@参数 是否显示
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_显示拥有的所有弹出窗口()
BOOL ShowOwnedPopups(
    HWND hWnd,
    BOOL fShow
);

//@备注 用于设置窗口的显示状态
//@参数 窗口句柄
//@参数 显示命令
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_显示()
BOOL ShowWindow(
    HWND hWnd,
    int nCmdShow
);

//@备注 设置窗口的显示状态，而无需等待操作完成
//@参数 窗口句柄
//@参数 显示命令
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_显示窗口异步()
BOOL ShowWindowAsync(
    HWND hWnd,
    int nCmdShow
);

//@备注 用于平铺指定父窗口的子窗口
//@参数 父窗口句柄
//@参数 平铺方式
//@参数 平铺区域矩形指针（可选）
//@参数 子窗口数量
//@参数 子窗口句柄数组（可选）
//@返回 平铺成功的子窗口数量
//@别名 A窗口_平铺子窗口()
WORD TileWindows(
  HWND       hwndParent,
  UINT       wHow,
  const RECT *lpRect,
  UINT       cKids,
  const HWND *lpKids
);

//@备注 用于更新分层窗口的位置、大小、形状和内容
//@参数 窗口句柄
//@参数 目标设备上下文句柄（可选）
//@参数 目标位置指针（可选）
//@参数 窗口大小指针（可选）
//@参数 源设备上下文句柄（可选）
//@参数 源位置指针（可选）
//@参数 透明颜色
//@参数 混合函数指针
//@参数 更新标志
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A窗口_更新分层窗口()
BOOL UpdateLayeredWindow(
  HWND          hWnd,
  HDC           hdcDst,
  POINT         *pptDst,
  SIZE          *psize,
  HDC           hdcSrc,
  POINT         *pptSrc,
  COLORREF      crKey,
  BLENDFUNCTION *pblend,
  DWORD         dwFlags
);

//@分组}  //窗口管理



//@分组{  窗口消息

//@备注 用于向指定窗口发送消息
//@参数 窗口句柄
//@参数 消息
//@参数 消息参数1
//@参数 消息参数2
//@返回 消息处理结果
//@别名 A消息_发送()
LRESULT SendMessage(
  HWND   hWnd,
  UINT   Msg,
  WPARAM wParam,
  LPARAM lParam
);

//@备注 用于将消息投递到指定窗口的消息队列
//@参数 窗口句柄
//@参数 消息
//@参数 消息参数1
//@参数 消息参数2
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A消息_投递()
BOOL PostMessage(
  HWND   hWnd,
  UINT   Msg,
  WPARAM wParam,
  LPARAM lParam
);

//@备注 用于向线程的消息队列投递退出消息
//@参数 退出代码
//@返回 无返回值
//@别名 A消息_投递退出消息()
void PostQuitMessage(int nExitCode);

//@备注 用于向指定线程的消息队列投递消息
//@参数 线程ID
//@参数 消息
//@参数 消息参数1
//@参数 消息参数2
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A消息_投递线程消息()
BOOL PostThreadMessage(
  DWORD  idThread,
  UINT   Msg,
  WPARAM wParam,
  LPARAM lParam
);
//@备注 用于异步发送消息并在消息处理完成后调用回调函数
//@参数 窗口句柄
//@参数 消息
//@参数 消息参数1
//@参数 消息参数2
//@参数 回调函数
//@参数 附加数据
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A消息_发送回调()
BOOL SendMessageCallback(
  HWND          hWnd,
  UINT          Msg,
  WPARAM        wParam,
  LPARAM        lParam,
  SENDASYNCPROC lpResultCallBack,
  ULONG_PTR     dwData
);

//@备注 用于在指定时间内发送消息并等待结果
//@参数 窗口句柄
//@参数 消息
//@参数 消息参数1
//@参数 消息参数2
//@参数 标志
//@参数 超时时间
//@参数 结果指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A消息_发送超时()
LRESULT SendMessageTimeout(
  HWND       hWnd,
  UINT       Msg,
  WPARAM     wParam,
  LPARAM     lParam,
  UINT       fuFlags,
  UINT       uTimeout,
  PDWORD_PTR lpdwResult
);

//@备注 用于向指定窗口发送通告消息
//@参数 窗口句柄
//@参数 消息
//@参数 消息参数1
//@参数 消息参数2
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A消息_发送通知消息()
BOOL SendNotifyMessage(
  HWND   hWnd,
  UINT   Msg,
  WPARAM wParam,
  LPARAM lParam
);

//@备注 用于从调用线程的消息队列中获取消息
//@参数 消息结构指针
//@参数 窗口句柄
//@参数 消息过滤最小值
//@参数 消息过滤最大值
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A消息_取窗口消息()
BOOL GetMessage(
  LPMSG lpMsg,
  HWND  hWnd,
  UINT  wMsgFilterMin,
  UINT  wMsgFilterMax
);

//@备注 用于将虚拟键消息转换为字符消息
//@参数 消息结构指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A消息_翻译()
BOOL TranslateMessage(
    const MSG *lpMsg
);

//@备注 用于将消息分发到窗口过程
//@参数 消息结构指针
//@返回 消息处理结果
//@别名 A消息_分发()
LRESULT DispatchMessage(const MSG *lpMsg);

//@备注 用于挂起当前线程，直到线程的消息队列中有消息
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A消息_等待()
BOOL WaitMessage();

//@备注 用于检查线程的消息队列中是否有消息
//@参数 消息结构指针
//@参数 窗口句柄
//@参数 消息过滤最小值
//@参数 消息过滤最大值
//@参数 移除消息标志
//@返回 如果存在消息，返回值为非零值 否则返回值为零
//@别名 A消息_检查队列()
BOOL PeekMessage(
  LPMSG lpMsg,
  HWND  hWnd,
  UINT  wMsgFilterMin,
  UINT  wMsgFilterMax,
  UINT  wRemoveMsg
);

//@分组}  //窗口消息


//@分组{  对话框

//@备注 用于创建并显示一个模态对话框
//@参数 模块句柄
//@参数 对话框模板名称
//@参数 父窗口句柄
//@参数 对话框过程函数指针
//@返回 无返回值
//@别名 A对话框_创建模态对话框()
void DialogBox(
  __in  HINSTANCE hInstance,
  __in  LPCTSTR lpTemplate,
  __in  HWND hWndParent,
  __in  DLGPROC lpDialogFunc
);

//@备注 用于销毁一个模态对话框
//@参数 对话框句柄
//@参数 结果值
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A对话框_关闭()
BOOL EndDialog(
  __in HWND    hDlg,
  __in INT_PTR nResult
);

//@备注 用于创建并显示一个非模态对话框
//@参数 模块句柄
//@参数 对话框模板名称
//@参数 父窗口句柄
//@参数 对话框过程函数指针
//@返回 无返回值
//@别名 A对话框_创建()
void CreateDialog(
  __in HINSTANCE hInstance,
  __in  LPCTSTR  lpName,
  __in  HWND hWndParent,
  __in  DLGPROC lpDialogFunc
);
//@备注 用于处理对话框的默认消息
//@参数 对话框句柄
//@参数 消息
//@参数 消息参数1
//@参数 消息参数2
//@返回 消息处理结果
//@别名 A对话框_调用默认对话框过程()
LRESULT DefDlgProc(
  __in HWND   hDlg,
  __in UINT   Msg,
  __in WPARAM wParam,
  __in LPARAM lParam
);

//@备注 用于获取对话框中指定控件的文本
//@参数 对话框句柄
//@参数 控件ID
//@参数 接收文本的缓冲区
//@参数 缓冲区大小
//@返回 复制的字符数
//@别名 A对话框_取标题()
UINT GetDlgItemText(
  __in  HWND   hDlg,
  __in  int    nIDDlgItem,
  __out LPWSTR lpString,
  __in  int    cchMax
);

//@备注 用于设置对话框中指定控件的文本
//@参数 对话框句柄
//@参数 控件ID
//@参数 要设置的文本
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A对话框_置控件标题()
BOOL SetDlgItemText(
  __in HWND    hDlg,
  __in int     nIDDlgItem,
  __in LPCWSTR lpString
);

//@备注 用于创建模态对话框并传递初始化参数
//@参数 模块句柄
//@参数 对话框模板指针
//@参数 父窗口句柄
//@参数 对话框过程函数指针
//@参数 初始化参数
//@返回 对话框的返回值
//@别名 A对话框_创建间接参数()
INT_PTR WINAPI DialogBoxIndirectParam(
    HINSTANCE hInstance,
    LPCDLGTEMPLATEW hDialogTemplate,
    HWND hWndParent,
    DLGPROC lpDialogFunc,
    LPARAM dwInitParam
);


//@分组}



//@分组{  文件拖放

//@备注 使用 fAccept 参数设置为 TRUE 调用 DragAcceptFiles 的应用程序已将自身标识为能够处理文件管理器中的WM_DROPFILES消息
//@参数 窗口句柄
//@参数 是否接受拖放文件
//@返回 无返回值
//@别名 A文件拖放_允许()
void DragAcceptFiles(HWND hWnd,  BOOL fAccept);

@备注 释放系统分配用于将文件名传输到应用程序的内存。
@参数 hDrop 描述已删除文件的结构的标识符。 此句柄是从WM_DROPFILES消息的 wParam 参数中检索的。
@别名 A文件拖放_完成()
void DragFinish( HDROP hDrop);

@备注  检索成功拖放操作导致的已删除文件的名称
@参数  hDrop 包含已删除文件的文件名的结构的标识符。
@参数  iFile 要查询的文件的索引。 如果此参数的值0xFFFFFFFF， DragQueryFile 将返回删除的文件计数。 如果此参数的值介于零和删除的文件总数之间， DragQueryFile 会将具有相应值的文件名复制到 lpszFile 参数指向的缓冲区。
@参数  lpszFile 当函数返回时接收已删除文件的文件名的缓冲区的地址。 此文件名是一个以 null 结尾的字符串。 如果此参数为 NULL， DragQueryFile 将返回此缓冲区的所需大小（以字符为单位）。
@参数  cch 缓冲区的大小（以字符为单位）。
@返回  非零值指示成功调用。
@别名  A文件拖放_取拖放文件()
UINT DragQueryFile(__in HDROP  hDrop, __in UINT iFile, __out LPWSTR lpszFile, UINT cch);

@备注  检索在拖放操作期间删除文件时鼠标指针的位置。
@参数  hDrop 描述已删除文件的放置结构的句柄。
@参数  ppt 指向 POINT 结构的指针，当此函数成功返回时，该结构接收删除文件时鼠标指针的坐标。
@返回  如果删除发生在窗口的工作区中，则为 TRUE;否则为 FALSE。
@ 返回坐标的窗口是接收 WM_DROPFILES 消息的窗口。
@别名  A文件拖放_取拖放文件鼠标位置()
BOOL DragQueryPoint(__in HDROP hDrop, __out POINT *ppt);

//@分组}


//------------坐标操作-----------------------------------------------------------------

//@分组{  坐标

//@备注 用于获取指定窗口的屏幕坐标矩形
//@参数 窗口句柄
//@参数 返回矩形指针 该结构接收窗口左上角和右下角的屏幕坐标
//@返回 如果该函数成功，则返回值为非零值。如果函数失败，则返回值为零
//@别名 A坐标_取窗口矩形(窗口句柄,返回矩形指针)
BOOL GetWindowRect(
    HWND hWnd,
    LPRECT lpRect
);

//@备注 用于获取指定窗口客户区的坐标矩形
//@参数 窗口句柄
//@参数 返回矩形指针 该结构接收窗口客户区的坐标
//@返回 如果该函数成功，则返回值为非零值。如果函数失败，则返回值为零
//@别名 A坐标_取客户区矩形(窗口句柄,返回矩形指针)
BOOL GetClientRect(
    HWND hWnd,
    LPRECT lpRect
);

//@备注 用于将客户区坐标转换为屏幕坐标
//@参数 窗口句柄
//@参数 转换坐标指针 该结构包含要转换的客户区坐标
//@返回 如果该函数成功，则返回值为非零值。如果函数失败，则返回值为零
//@别名 A坐标_客户区坐标到屏幕(窗口句柄,转换坐标指针)
BOOL ClientToScreen(
    HWND hWnd,
    LPPOINT lpPoint
);

//@备注 用于将屏幕坐标转换为客户区坐标
//@参数 窗口句柄
//@参数 转换坐标指针 该结构包含要转换的屏幕坐标
//@返回 如果该函数成功，则返回值为非零值。如果函数失败，则返回值为零
//@别名 A坐标_屏幕坐标到客户区(窗口句柄,转换坐标指针)
BOOL ScreenToClient(
    HWND hWnd,
    LPPOINT lpPoint
);

//@备注 用于判断指定点是否在矩形内
//@参数 矩形指针 指向要检查的矩形
//@参数 坐标 要检查的点
//@返回 如果该函数成功，则返回值为非零值。如果函数失败，则返回值为零
//@别名 A坐标_坐标是否在矩形内(矩形指针,坐标)
BOOL PtInRect(
    const RECT *lprc,
    POINT pt
);

//@备注 用于获取包含指定屏幕坐标的窗口句柄
//@参数 坐标点
//@返回 包含指定坐标的窗口句柄
//@别名 A坐标_取坐标所在窗口()
HWND WindowFromPoint(
    POINT Point
);

//@备注 用于设置窗口的位置和大小
//@参数 hWnd 窗口句柄
//@参数 hWndInsertAfter 指定窗口的Z顺序（即窗口的显示顺序）
//@参数 X 窗口的新X坐标
//@参数 Y 窗口的新Y坐标
//@参数 cx 窗口的新宽度
//@参数 cy 窗口的新高度
//@参数 uFlags 窗口位置和大小的调整标志
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A坐标_置窗口位置()
BOOL SetWindowPos(
  HWND hWnd,
  HWND hWndInsertAfter,
  int  X,
  int  Y,
  int  cx,
  int  cy,
  UINT uFlags
);

//@备注 用于将逻辑坐标转换为物理坐标
//@参数 窗口句柄
//@参数 坐标指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A坐标_逻辑坐标点到物理()
BOOL LogicalToPhysicalPoint(HWND hWnd, LPPOINT lpPoint);

//@分组}


//@分组{ HOOK

#define WH_MSGFILTER        (-1)
#define WH_JOURNALRECORD    0
#define WH_JOURNALPLAYBACK  1
@备注 安装用于监视击键消息的挂钩过程。
#define WH_KEYBOARD         2
#define WH_GETMESSAGE       3
@备注 安装一个挂钩过程，用于在系统将消息发送到目标窗口过程之前监视消息。
#define WH_CALLWNDPROC      4
#define WH_CBT              5
#define WH_SYSMSGFILTER     6
@备注 安装监视鼠标消息的挂钩过程。 
#define WH_MOUSE            7

#define WH_DEBUG            9
@备注 安装一个挂钩过程，用于接收对 shell 应用程序有用的通知。 
#define WH_SHELL           10
#define WH_FOREGROUNDIDLE  11

@备注 安装一个挂钩过程，该过程在目标窗口过程处理消息后监视消息。 
#define WH_CALLWNDPROCRET  12

@备注 安装用于监视低级别键盘输入事件的挂钩过程。
#define WH_KEYBOARD_LL     13
@备注 安装用于监视低级别鼠标输入事件的挂钩过程。 
#define WH_MOUSE_LL        14

/// Hook Codes

#define HC_ACTION           0
#define HC_GETNEXT          1
#define HC_SKIP             2
#define HC_NOREMOVE         3
#define HC_NOREM            HC_NOREMOVE
#define HC_SYSMODALON       4
#define HC_SYSMODALOFF      5

DECLARE_HANDLEX(HHOOK);

//@参数 钩子代码
//@参数 消息参数1
//@参数 消息参数2
//@返回 钩子处理结构
//@别名 钩子过程的回调函数类型()
typedef LRESULT (CALLBACK* HOOKPROC)(int code, WPARAM wParam, LPARAM lParam);

//@备注 调用下一个钩子过程
//@参数 钩子句柄
//@参数 钩子代码
//@参数 消息参数1
//@参数 消息参数2
//@返回 钩子处理结果
//@别名 调用下一个钩子过程()
LRESULT WINAPI CallNextHookEx(
    _In_opt_ HHOOK hhk,
    _In_ int nCode,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);


//@参数 钩子类型, WH_ 开头的常量
//@参数 钩子过程
//@参数 模块句柄
//@参数 线程标识符
//@返回 如果函数成功，返回值为钩子句柄 如果函数失败，返回值为NULL
//@别名 安装钩子过程()
HHOOK SetWindowsHookEx(
  int       idHook,
  HOOKPROC  lpfn,
  HINSTANCE hmod = NULL,
  DWORD     dwThreadId = NULL
);

//@备注 用于卸载指定的钩子过程
//@参数 钩子句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 卸载钩子过程()
BOOL UnhookWindowsHookEx(
    HHOOK hhk
);

//@分组}  //HOOK


//-------------文件管理-----------------------------------------------------------------

//@分组{  文件管理

#define GENERIC_READ                     0x80000000
#define GENERIC_WRITE                    0x40000000
#define GENERIC_EXECUTE                  0x20000000
#define GENERIC_ALL                      0x10000000

#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5

//@备注 用于创建或打开一个文件
//@参数 文件名
//@参数 访问模式（如 GENERIC_READ, GENERIC_WRITE）
//@参数 共享模式（如 FILE_SHARE_READ, FILE_SHARE_WRITE）
//@参数 安全属性指针（可选）
//@参数 创建方式（如 CREATE_NEW, OPEN_EXISTING）
//@参数 文件属性和标志（如 FILE_ATTRIBUTE_NORMAL, FILE_FLAG_OVERLAPPED）
//@参数 模板文件句柄（可选）
//@返回 返回文件句柄
//@别名 A文件_创建()
HANDLE WINAPI CreateFile(
  __in          LPCTSTR lpFileName,
  __in          DWORD dwDesiredAccess,
  __in          DWORD dwShareMode,
  __in          LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  __in          DWORD dwCreationDisposition,
  __in          DWORD dwFlagsAndAttributes,
  __in          HANDLE hTemplateFile
);

//@备注 用于复制文件
//@参数 源文件名
//@参数 目标文件名
//@参数 如果目标文件存在是否失败
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_复制()
BOOL WINAPI CopyFile(
  __in          LPCTSTR lpExistingFileName,
  __in          LPCTSTR lpNewFileName,
  __in          BOOL bFailIfExists
);

//@备注 用于复制文件，支持进度回调和取消操作功能
//进度回调函数是一个自定义的函数，CopyFileEx 会在复制过程中定期调用它，以报告复制的进度
//你可以利用这个功能显示进度条或执行其他操作。
//@参数 源文件名
//@参数 目标文件名
//@参数 进度回调函数（可选）
//@参数 传递给回调函数的数据（可选）
//@参数 取消标志（可选）
//@参数 复制选项
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_复制扩展()
BOOL WINAPI CopyFileEx(
  __in      LPCTSTR lpExistingFileName,
  __in      LPCTSTR lpNewFileName,
  __in_opt  LPPROGRESS_ROUTINE lpProgressRoutine,
  __in_opt  LPVOID lpData,
  __in_opt  LPBOOL pbCancel,
  __in      DWORD dwCopyFlags
);

//@备注 用于删除指定文件
//@参数 文件名
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_删除()
BOOL WINAPI DeleteFile(__in LPCTSTR lpFileName);

//@备注 用于获取文件的大小
//@参数 文件句柄
//@参数 输出文件大小的高位部分
//@返回 返回文件大小的低位部分
//@别名 A文件_取大小()
DWORD WINAPI GetFileSize(__in HANDLE hFile, __out LPDWORD lpFileSizeHigh);

//@备注 用于获取文件的大小（支持大文件）
//@参数 文件句柄
//@参数 输出文件大小结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_取大小扩展()
BOOL WINAPI GetFileSizeEx(__in HANDLE hFile, __out LARGE_INTEGER* lpFileSize);

//@备注 用于获取文件的类型
//@参数 文件句柄
//@返回 返回文件类型（如 FILE_TYPE_DISK, FILE_TYPE_PIPE）
//@别名 A文件_取类型()
DWORD WINAPI GetFileType(__in HANDLE hFile);

//@备注 用于移动或重命名文件
//@参数 源文件名
//@参数 目标文件名
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_移动()
BOOL WINAPI MoveFile(__in LPCTSTR lpExistingFileName, __in LPCTSTR lpNewFileName);

//@备注 用于移动或重命名文件，支持更多选项
//@参数 源文件名
//@参数 目标文件名
//@参数 移动标志（如 MOVEFILE_REPLACE_EXISTING, MOVEFILE_COPY_ALLOWED）
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_移动扩展()
BOOL WINAPI MoveFileEx(__in LPCTSTR lpExistingFileName, __in LPCTSTR lpNewFileName, __in DWORD dwFlags);

//@备注 用于打开一个文件
//@参数 文件名
//@参数 输出重新打开缓冲区
//@参数 打开方式（如 OF_READ, OF_WRITE）
//@返回 返回文件句柄
//@别名 A文件_打开()
HFILE WINAPI OpenFile(__in LPCSTR lpFileName, __out LPOFSTRUCT lpReOpenBuff, __in UINT uStyle);

//@备注 用于锁定文件的指定区域
//@参数 文件句柄
//@参数 文件偏移的低位部分
//@参数 文件偏移的高位部分
//@参数 锁定字节数的低位部分
//@参数 锁定字节数的高位部分
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_锁定()
BOOL WINAPI LockFile(
  __in          HANDLE hFile,
  __in          DWORD dwFileOffsetLow,
  __in          DWORD dwFileOffsetHigh,
  __in          DWORD nNumberOfBytesToLockLow,
  __in          DWORD nNumberOfBytesToLockHigh
);

//@备注 用于锁定文件的指定区域，支持更多选项
//@参数 文件句柄
//@参数 锁定标志（如 LOCKFILE_EXCLUSIVE_LOCK, LOCKFILE_FAIL_IMMEDIATELY）
//@参数 保留参数
//@参数 锁定字节数的低位部分
//@参数 锁定字节数的高位部分
//@参数 重叠结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_锁定扩展()
BOOL WINAPI LockFileEx(
  __in          HANDLE hFile,
  __in          DWORD dwFlags,
  DWORD dwReserved,
  __in          DWORD nNumberOfBytesToLockLow,
  __in          DWORD nNumberOfBytesToLockHigh,
  __in          LPOVERLAPPED lpOverlapped
);

//@备注 用于从文件中读取数据
//@参数 文件句柄
//@参数 输出缓冲区指针
//@参数 要读取的字节数
//@参数 输出实际读取的字节数
//@参数 重叠结构体指针（可选）
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_读取()
BOOL WINAPI ReadFile(
  __in          HANDLE hFile,
  __out         LPVOID lpBuffer,
  __in          DWORD nNumberOfBytesToRead,
  __out         LPDWORD lpNumberOfBytesRead,
  __in          LPOVERLAPPED lpOverlapped
);

//@备注 用于从文件中异步读取数据
//@参数 文件句柄
//@参数 输出缓冲区指针
//@参数 要读取的字节数
//@参数 重叠结构体指针
//@参数 完成例程指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_读取扩展()
BOOL WINAPI ReadFileEx(
  __in          HANDLE hFile,
  __out         LPVOID lpBuffer,
  __in          DWORD nNumberOfBytesToRead,
  __in          LPOVERLAPPED lpOverlapped,
  __in          LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

//@备注 用于向文件中写入数据
//@参数 文件句柄
//@参数 输入缓冲区指针
//@参数 要写入的字节数
//@参数 输出实际写入的字节数
//@参数 重叠结构体指针（可选）
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_写入()
BOOL WINAPI WriteFile(
  __in          HANDLE hFile,
  __in          LPCVOID lpBuffer,
  __in          DWORD nNumberOfBytesToWrite,
  __out         LPDWORD lpNumberOfBytesWritten,
  __in          LPOVERLAPPED lpOverlapped
);

//@备注 用于向文件中异步写入数据
//@参数 文件句柄
//@参数 输入缓冲区指针
//@参数 要写入的字节数
//@参数 重叠结构体指针
//@参数 完成例程指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_写入扩展()
BOOL WINAPI WriteFileEx(
  __in          HANDLE hFile,
  __in          LPCVOID lpBuffer,
  __in          DWORD nNumberOfBytesToWrite,
  __in          LPOVERLAPPED lpOverlapped,
  __in          LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

//@备注 用于解锁文件的指定区域
//@参数 文件句柄
//@参数 文件偏移的低位部分
//@参数 文件偏移的高位部分
//@参数 解锁字节数的低位部分
//@参数 解锁字节数的高位部分
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A文件_解锁()
BOOL WINAPI UnlockFile(
  __in          HANDLE hFile,
  __in          DWORD dwFileOffsetLow,
  __in          DWORD dwFileOffsetHigh,
  __in          DWORD nNumberOfBytesToUnlockLow,
  __in          DWORD nNumberOfBytesToUnlockHigh
);
//@分组}


//---------------内存管理----------------------------------------------------------------------
//@分组{   内存管理

//@返回 如果函数成功，并且至少读取了一个字节的数据，返回值为TRUE；如果函数失败，返回值为FALSE。可以通过调用GetLastError函数来获取错误信息。
//@参数 hProcess 要读取其内存的进程的句柄。句柄必须具有PROCESS_VM_READ权限。
//@参数 lpBaseAddress 要从中读取的远程进程内存地址。
//@参数 lpBuffer 接收从远程进程内存读取的数据的缓冲区。
//@参数 nSize 要从远程进程内存读取的字节数。
//@参数 lpNumberOfBytesRead 指向变量的指针，该变量接收实际读取的字节数。如果此参数为NULL，则不返回实际读取的字节数。
//@别名 读进程内存()
BOOL ReadProcessMemory(
    __in      HANDLE hProcess,
    __in      LPCVOID lpBaseAddress,
    __out    LPVOID lpBuffer,
    __in      SIZE_T nSize,
    __out_opt SIZE_T * lpNumberOfBytesRead
    );

//@备注 用于将数据写入指定进程的内存空间
//@参数 hProcess 目标进程的句柄
//@参数 lpBaseAddress 目标进程中的内存地址
//@参数 lpBuffer 要写入的数据缓冲区
//@参数 nSize 要写入的数据大小（以字节为单位）
//@参数 lpNumberOfBytesWritten 返回实际写入的字节数（可选）
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 写进程内存()
BOOL WriteProcessMemory(
    __in      HANDLE hProcess,
    __in      LPVOID lpBaseAddress,
    __in      LPCVOID lpBuffer,
    __in      SIZE_T nSize,
    __out_opt SIZE_T * lpNumberOfBytesWritten
    );


//@备注 该函数的功能是在调用进程的虚地址空间,预定或者提交一部分页，如果用于内存分配的话,并且分配类型未指定
//@参数 lpAddress 指定需要保留或提交的地址空间的位置,可以使用NULL(函数自行在某个最方便的位置保留地址范围)
//@参数 dwSize 指定要保留或提交的地址大小(0~2GB)
//@参数 flAllocationType 指定地址如何分配
//@参数 flProtect 指定保护的类型
//@别名  A虚拟内存_分配()
LPVOID WINAPI VirtualAlloc(
  __in          LPVOID lpAddress,
  __in          SIZE_T dwSize,
  __in          DWORD flAllocationType,
  __in          DWORD flProtect
);

//@备注 用于在指定进程的虚拟地址空间中分配内存
//@参数 hProcess 目标进程句柄
//@参数 lpAddress 内存地址（可选）
//@参数 dwSize 内存大小（以字节为单位）
//@参数 flAllocationType 内存分配类型
//@参数 flProtect 内存保护属性
//@返回 如果函数成功，返回值为分配的内存地址；如果函数失败，返回值为NULL
//@别名 A虚拟内存_分配扩展()
LPVOID WINAPI VirtualAllocEx(
  __in          HANDLE hProcess,
  __in          LPVOID lpAddress,
  __in          SIZE_T dwSize,
  __in          DWORD flAllocationType,
  __in          DWORD flProtect
);
@参数 hProcess 目标进程的句柄
@参数 lpAddress 要分配的内存区域的地址
@参数 dwSize 指定的地址大小(0~2GB)
@参数 flAllocationType 指定地址如何分配
@参数 flProtect 指定保护的类型
@参数 nndPreferred 物理内存应驻留的 NUMA 节点
@别名 A虚拟内存_分配扩展NUMA()
LPVOID WINAPI VirtualAllocExNuma(
  __in          HANDLE hProcess,
  __in_opt      LPVOID lpAddress,
  __in          SIZE_T dwSize,
  __in          DWORD flAllocationType,
  __in          DWORD flProtect,
  __in          DWORD nndPreferred
);

//@备注 用于释放当前进程中的虚拟内存
//@参数 lpAddress 内存地址
//@参数 dwSize 内存大小（以字节为单位）
//@参数 dwFreeType 释放类型
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A虚拟内存_释放()
BOOL WINAPI VirtualFree(
  __in          LPVOID lpAddress,
  __in          SIZE_T dwSize,
  __in          DWORD dwFreeType
);

//@备注 用于释放指定进程中的虚拟内存
//@参数 hProcess 目标进程句柄
//@参数 lpAddress 内存地址
//@参数 dwSize 内存大小（以字节为单位）
//@参数 dwFreeType 释放类型
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A虚拟内存_释放扩展()
BOOL WINAPI VirtualFreeEx(
  __in          HANDLE hProcess,
  __in          LPVOID lpAddress,
  __in          SIZE_T dwSize,
  __in          DWORD dwFreeType
);

@备注 该函数要求系统总是将指定的内存页保留在物理内存中,不许将它交换到磁盘页文件中,可以提高访问的速度
@参数 lpAddress 指定地址空间的位置
@参数 dwSize 指定的地址大小(0~2GB)
@别名 A虚拟内存_锁定()
BOOL WINAPI VirtualLock(
  __in          LPVOID lpAddress,
  __in          SIZE_T dwSize
);
@参数 lpAddress 指定地址空间的位置
@参数 dwSize 指定的地址大小(0~2GB)
@参数 flNewProtect 指定改变的属性保护的类型
@参数 lpflOldProtect 指向一个双字的指针,返回原来的保护方式
@别名 A虚拟内存_保护设置()
BOOL WINAPI VirtualProtect(
  __in          LPVOID lpAddress,
  __in          SIZE_T dwSize,
  __in          DWORD flNewProtect,
  __out         PDWORD lpflOldProtect
);

@参数 hProcess 目标进程的句柄
@参数 lpAddress 指定地址空间的位置
@参数 dwSize 指定的地址大小(0~2GB)
@参数 flNewProtect 指定改变的属性保护的类型
@参数 lpflOldProtect 指向一个双字的指针,返回原来的保护方式
@别名 A虚拟内存_保护设置扩展()
BOOL WINAPI VirtualProtectEx(
  __in          HANDLE hProcess,
  __in          LPVOID lpAddress,
  __in          SIZE_T dwSize,
  __in          DWORD flNewProtect,
  __out         PDWORD lpflOldProtect
);

@备注 获取一段虚拟地址空间或虚拟页的属性或状态．成功返回缓冲区的实数数组．否则返回0
@参数 lpAddress 指定地址空间的位置
@参数 lpBuffer 指向一个MEMORY_BASIC_INFORMATION 结构，用来存取虚拟页属性或状态
@参数 dwLength 指定lpBuffer缓冲区的大小
@别名 A虚拟内存_查询()
SIZE_T WINAPI VirtualQuery(
  __in          LPCVOID lpAddress,
  __out         PMEMORY_BASIC_INFORMATION lpBuffer,
  __in          SIZE_T dwLength
);
@备注 获取一段虚拟地址空间或虚拟页的属性或状态．成功返回缓冲区的实数数组．否则返回0
@参数 lpAddress 指定地址空间的位置
@参数 lpBuffer 指向一个MEMORY_BASIC_INFORMATION 结构，用来存取虚拟页属性或状态
@参数 dwLength 指定lpBuffer缓冲区的大小
@别名 A虚拟内存_查询扩展()
SIZE_T WINAPI VirtualQueryEx(
  __in          HANDLE hProcess,
  __in          LPCVOID lpAddress,
  __out         PMEMORY_BASIC_INFORMATION lpBuffer,
  __in          SIZE_T dwLength
);
@备注 该函数要求系统解锁指定保留在物理内存中的内存页,允许将它交换到磁盘页文件中
@参数 lpAddress 指定地址空间的位置
@参数 dwSize 指定的地址大小(0~2GB)
@别名 A虚拟内存_解锁()
BOOL WINAPI VirtualUnlock(
  __in          LPVOID lpAddress,
  __in          SIZE_T dwSize
);


@备注  从全局堆中分配出内存供程序使用
@别名  A全局内存_分配()
HGLOBAL WINAPI GlobalAlloc(
  __in          UINT uFlags,
  __in          SIZE_T dwBytes
);
@备注 它只移走对象的内容,而保持其句柄有效,用户在需要时,还可以使用此内存句柄用LocalReAlloc函数重新分配一块内存
@别名  A全局内存_删除(内存块句柄)
HGLOBAL WINAPI GlobalDiscard(
  __in                 HGLOBAL hMem
);
@备注 获取内存块当前的当前属性，主要用来获取可移动内存块当前的锁定计数，也可以用来检测可丢弃内存块是否已经被丢弃
@别名 A全局内存_取标识(内存块句柄)
UINT WINAPI GlobalFlags(
  __in          HGLOBAL hMem
);
@别名 A全局内存_释放(内存块指针)
HGLOBAL WINAPI GlobalFree(
  __in          HGLOBAL hMem
);
@备注 获得GlobalLock函数锁定内存的句柄
@参数 pMem 指向一个先前用GlobalLock函数锁定内存块指针，此指针一般由GlobalLock函数返回
@别名 A全局内存_取句柄(内存块指针)
HGLOBAL WINAPI GlobalHandle(
  __in          LPCVOID pMem
);
@别名  A全局内存_锁定(内存块指针)
LPVOID WINAPI GlobalLock(
  __in          HGLOBAL hMem
);
@别名 A全局内存_重置(内存块指针,内存块大小,标识)
HGLOBAL WINAPI GlobalReAlloc(
  __in          HGLOBAL hMem,
  __in          SIZE_T dwBytes,
  __in          UINT uFlags
);
@备注 修改先前申请到的固定内存块的大小/属性，成功返回新的内存块的句柄或指针,否则返回0
@参数 hMem 内存块指针 指向一个内存块的指针,一般是先前用GlobalAlloc函数申请到的内存块
@参数 uBytes 内存块大小 新内存块的大小。uflags参数被设置为GMEM_MODIFY时，此参数会被忽略
@参数 uFlags 标识
@别名  A全局内存_取大小(内存块指针)
SIZE_T WINAPI GlobalSize(
  __in          HGLOBAL hMem
);
@别名 A全局内存_解锁(内存块指针)
BOOL WINAPI GlobalUnlock(
  __in          HGLOBAL hMem
);


@备注 从局部堆中分配内存供程序使用
@别名 A本地内存_分配()
HLOCAL WINAPI LocalAlloc(
  __in          UINT uFlags,
  __in          SIZE_T uBytes
);
@备注 它只移走对象的内容,而保持其句柄有效,用户在需要时,还可以使用此内存句柄用LocalReAlloc函数重新分配一块内存
@别名 A本地内存_删除(内存块句柄)
HLOCAL WINAPI LocalDiscard(
 __in                HLOCAL hlocMem
);
@备注 获取内存块当前的当前属性，主要用来获取可移动内存块当前的锁定计数，也可以用来检测可丢弃内存块是否已经被丢弃
@别名 A本地内存_取标识(内存块句柄)
UINT WINAPI LocalFlags(
  __in          HLOCAL hMem
);
@别名 A本地内存_释放(内存块指针)
HLOCAL WINAPI LocalFree(
  __in          HLOCAL hMem
);

@备注 获得LocalLock函数锁定内存的句柄
@参数 pMem 指向一个先前用LocalLock函数锁定内存块指针，此指针一般由LocalLock函数返回
@别名 A本地内存_取句柄(内存块指针)
HLOCAL WINAPI LocalHandle(
  __in          LPCVOID pMem
);
@别名 本地内存_锁定(内存块指针)
LPVOID WINAPI LocalLock(
  __in          HLOCAL hMem
);
@备注 修改先前申请到的固定内存块的大小/属性，成功返回新的内存块的句柄或指针,否则返回0
@参数 hMem 内存块指针 指向一个内存块的指针,一般是先前用LocalAlloc函数申请到的内存块
@参数 uBytes 内存块大小 新内存块的大小。uflags参数被设置为GMEM_MODIFY时，此参数会被忽略
@参数 uFlags 标识
@别名 A本地内存_重置(内存块指针,内存块大小,标识)
HLOCAL WINAPI LocalReAlloc(
  __in          HLOCAL hMem,
  __in          SIZE_T uBytes,
  __in          UINT uFlags
);

@别名 A本地内存_取大小(内存块指针)
UINT WINAPI LocalSize(
  __in          HLOCAL hMem
);
@别名 A本地内存_解锁(内存块指针)
BOOL WINAPI LocalUnlock(
  __in          HLOCAL hMem
);

//@备注  分配固定内存。 返回值为指针。
#define GMEM_FIXED          0x0000

//@备注  分配可移动内存。 内存块永远不会在物理内存中移动，但它们可以在默认堆内移动。
//      返回值是内存对象的句柄。 若要将句柄转换为指针，请使用 GlobalLock 函数。
//      此值不能与 GMEM_FIXED结合使用。
#define GMEM_MOVEABLE       0x0002

//@备注  将内存内容初始化为零。
#define GMEM_ZEROINIT       0x0040

//@分组}


//---------------资源管理------------------------------------------------------------------
//@分组{   资源管理

//@备注 用于在模块中查找指定名称和类型的资源
//@参数 模块句柄
//@参数 资源名称
//@参数 资源类型
//@返回 返回资源信息句柄
//@别名 A资源_查找()
HRSRC FindResource(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType);

//@备注 用于在模块中查找指定名称、类型和语言的资源
//@参数 模块句柄
//@参数 资源类型
//@参数 资源名称
//@参数 语言标识符
//@返回 返回资源信息句柄
//@别名 A资源_查找扩展()
HRSRC FindResourceEx(HMODULE hModule, LPCTSTR lpType, LPCTSTR lpName, WORD wLanguage);

//@备注 用于加载指定资源
//@参数 模块句柄
//@参数 资源信息句柄
//@返回 返回资源数据句柄
//@别名 A资源_加载()
HGLOBAL LoadResource(HMODULE hModule, HRSRC hResInfo);

//@备注 用于锁定资源数据并返回其指针
//@参数 资源数据句柄
//@返回 返回资源数据的指针
//@别名 A资源_锁定()
LPVOID LockResource(HGLOBAL hResData);

//@备注 用于获取指定资源的大小
//@参数 模块句柄
//@参数 资源信息句柄
//@返回 返回资源的大小（以字节为单位）
//@别名 A资源_取大小()
DWORD SizeofResource(HMODULE hModule, HRSRC hResInfo);

//@备注 用于释放资源数据
//@参数 资源数据句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A资源_释放()
BOOL FreeResource(HGLOBAL hglbResource);

//@备注 用于更新可执行文件中的资源
//@参数 更新资源句柄
//@参数 资源类型
//@参数 资源名称
//@参数 语言ID
//@参数 资源数据指针
//@参数 资源数据大小
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A资源_更新()
BOOL UpdateResource(
    HANDLE hUpdate,
    LPCWSTR lpType,
    LPCWSTR lpName,
    WORD wLanguage,
    LPVOID lpData,
    DWORD cb
);

//@备注 用于开始更新可执行文件中的资源
//@参数 文件名
//@参数 是否删除现有资源
//@返回 如果函数成功，返回值为更新资源句柄 如果函数失败，返回值为NULL
//@别名 A资源_开始更新()
HANDLE BeginUpdateResource(
    LPCWSTR pFileName,
    BOOL bDeleteExistingResources
);

//@备注 用于结束更新可执行文件中的资源
//@参数 更新资源句柄
//@参数 是否放弃更改
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A资源_结束更新()
BOOL EndUpdateResource(
    HANDLE hUpdate,
    BOOL fDiscard
);

//@备注 用于解锁指定的资源数据
//@参数 资源数据句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A资源_解锁()
BOOL UnlockResource(
    HGLOBAL hResData
);

//@备注 用于枚举指定模块中的资源名称
//@参数 模块句柄
//@参数 资源类型
//@参数 枚举回调函数
//@参数 附加参数
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A资源_枚举资源名称()
BOOL EnumResourceNames(
    HMODULE hModule,
    LPCWSTR lpType,
    ENUMRESNAMEPROCW lpEnumFunc,
    LONG_PTR lParam
);

//@备注 用于加载图像（位图、图标、光标等）
//@参数 实例句柄
//@参数 图像名称或路径
//@参数 图像类型（如 IMAGE_BITMAP, IMAGE_ICON, IMAGE_CURSOR）
//@参数 期望的图像宽度
//@参数 期望的图像高度
//@参数 加载标志
//@返回 返回加载的图像句柄
//@别名 加载图像()
HANDLE LoadImage(HINSTANCE hinst, LPCTSTR lpszName, UINT uType, int cxDesired, int cyDesired, UINT fuLoad);

//@分组}


//@分组{  插入符-光标-图标

//--------------插入符--------------------------------------
//@备注 用于为指定窗口创建一个插入符
//@参数 窗口句柄
//@参数 位图句柄（可选）
//@参数 插入符宽度
//@参数 插入符高度
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A插入符_创建()
BOOL CreateCaret(HWND hWnd, HBITMAP hBitmap, int nWidth, int nHeight);

//@备注 用于销毁当前插入符
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A插入符_销毁()
BOOL DestroyCaret();

//@备注 用于获取插入符的闪烁时间
//@返回 返回插入符的闪烁时间（以毫秒为单位）
//@别名 A插入符_取闪烁时间()
UINT GetCaretBlinkTime();

//@备注 用于获取插入符的位置
//@参数 点结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A插入符_取位置()
BOOL GetCaretPos(LPPOINT lpPoint);

//@备注 用于隐藏指定窗口的插入符
//@参数 窗口句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A插入符_隐藏()
BOOL HideCaret(HWND hWnd);

//@备注 用于设置插入符的闪烁时间
//@参数 闪烁时间（以毫秒为单位）
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A插入符_置闪烁时间()
BOOL SetCaretBlinkTime(UINT uMSeconds);

//@备注 用于设置插入符的位置
//@参数 插入符的X坐标
//@参数 插入符的Y坐标
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A插入符_置位置()
BOOL SetCaretPos(int X, int Y);

//@备注 用于显示指定窗口的插入符
//@参数 窗口句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A插入符_显示()
BOOL ShowCaret(HWND hWnd);


//@备注 用于将鼠标限制在指定的矩形区域内
//@参数 矩形区域指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A光标_限制区域()
BOOL ClipCursor(const RECT *lpRect);

//@备注 用于复制一个光标
//@参数 光标句柄
//@返回 返回复制的光标句柄
//@别名 A光标_复制()
HCURSOR CopyCursor(HCURSOR pcur);

//@备注 创建一个指定大小、位模式和热点的光标
//@参数 hInst 创建光标的应用程序的当前事例句柄
//@参数 xHotSpot 指定光标热点的水平位置
//@参数 yHotSpot 指定光标热点的垂直位置
//@参数 nWidth 以像素为单位指定光标的宽度
//@参数 nHeight 以像素为单位指定光标的高度
//@参数 pvANDPlane 指向一个字节数组的指针，该数组包含光标AND掩码的位值，就象设备相关的单色位图一样
//@参数 pvXORPlane 指向一个字节数组的指针，该数组包含光标XOR掩码的位值，就象设备相关的单色位图一样
//@返回 返回创建的光标句柄
//@别名 A光标_创建()
HCURSOR CreateCursor(
    HINSTANCE hInst,
    int xHotSpot,
    int yHotSpot,
    int nWidth,
    int nHeight,
    const VOID *pvANDPlane,
    const VOID *pvXORPlane
);

//@备注 用于销毁一个光标
//@参数 光标句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A光标_销毁()
BOOL DestroyCursor(HCURSOR hCursor);

//@备注 用于获取鼠标限制的矩形区域
//@参数 矩形区域指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A光标_取限制区域()
BOOL GetClipCursor(LPRECT lpRect);

//@备注 用于获取当前光标的句柄
//@返回 返回当前光标的句柄
//@别名 A光标_取句柄()
HCURSOR GetCursor();

//@备注 用于获取当前光标的信息
//@参数 光标信息结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A光标_取信息()
BOOL GetCursorInfo(PCURSORINFO pci);

//@备注 用于获取当前鼠标的位置
//@参数 点结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A光标_取位置()
BOOL GetCursorPos(LPPOINT lpPoint);

//@备注 用于获取当前鼠标的物理位置
//@参数 点结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A光标_取物理位置()
BOOL GetPhysicalCursorPos(LPPOINT lpPoint);

//@备注 用于从资源中加载一个光标
//@参数 实例句柄
//@参数 光标名称
//@返回 返回加载的光标句柄
//@别名 A光标_加载()
HCURSOR LoadCursor(HINSTANCE hInstance, LPCTSTR lpCursorName);

//@备注 用于从文件中加载一个光标
//@参数 文件路径
//@返回 返回加载的光标句柄
//@别名 A光标_加载从文件()
HCURSOR LoadCursorFromFile(LPCTSTR lpFileName);

//@备注 用于设置当前光标
//@参数 光标句柄
//@返回 返回之前的光标句柄
//@别名 A光标_置句柄()
HCURSOR SetCursor(HCURSOR hCursor);

//@备注 用于设置鼠标的位置
//@参数 鼠标位置的X坐标
//@参数 鼠标位置的Y坐标
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A光标_置位置()
BOOL SetCursorPos(int X, int Y);

//@备注 用于设置鼠标的物理位置
//@参数 鼠标位置的X坐标
//@参数 鼠标位置的Y坐标
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A光标_置物理位置()
BOOL SetPhysicalCursorPos(int X, int Y);

//@备注 用于设置系统光标
//@参数 光标句柄
//@参数 系统光标标识符
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A光标_置系统光标()
BOOL SetSystemCursor(HCURSOR hcur, DWORD id);

//@备注 用于显示或隐藏光标
//@参数 是否显示光标
//@返回 返回光标的显示计数
//@别名 A光标_显示()
int ShowCursor(BOOL bShow);

//-----------ICON 图标--------------------------------------
//@备注 用于复制一个图标
//@参数 图标句柄
//@返回 返回复制的图标句柄
//@别名 A图标_复制()
HICON CopyIcon(HICON hIcon);

//@备注 用于创建一个图标
//@参数 实例句柄
//@参数 图标宽度
//@参数 图标高度
//@参数 颜色平面数
//@参数 每像素位数
//@参数 AND掩码位图数据
//@参数 XOR掩码位图数据
//@返回 返回创建的图标句柄
//@别名 A图标_创建()
HICON CreateIcon(
    HINSTANCE hInstance,
    int nWidth,
    int nHeight,
    BYTE cPlanes,
    BYTE cBitsPixel,
    const BYTE *lpbANDbits,
    const BYTE *lpbXORbits
);

//@备注 用于从资源数据中创建一个图标
//@参数 资源数据指针
//@参数 资源数据大小
//@参数 是否为图标
//@参数 资源版本
//@返回 返回创建的图标句柄
//@别名 A图标_创建从资源()
HICON CreateIconFromResource(
    PBYTE presbits,
    DWORD dwResSize,
    BOOL fIcon,
    DWORD dwVer
);

//@备注 用于从资源数据中创建一个指定尺寸的图标
//@参数 图标数据指针
//@参数 图标数据大小
//@参数 是否为图标
//@参数 资源版本
//@参数 期望的图标宽度
//@参数 期望的图标高度
//@参数 创建标志
//@返回 返回创建的图标句柄
//@别名 A图标_创建从资源扩展()
HICON CreateIconFromResourceEx(
    PBYTE pbIconBits,
    DWORD cbIconBits,
    BOOL fIcon,
    DWORD dwVersion,
    int cxDesired,
    int cyDesired,
    UINT uFlags
);

//@备注 用于根据图标信息结构体创建一个图标
//@参数 图标信息结构体指针
//@返回 返回创建的图标句柄
//@别名 A图标_创建从结构()
HICON CreateIconIndirect(PICONINFO piconinfo);

//@备注 用于销毁一个图标
//@参数 图标句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A图标_销毁()
BOOL DestroyIcon(HICON hIcon);

//@备注 用于创建一个指定图标的副本
//@参数 实例句柄
//@参数 图标句柄
//@返回 返回复制的图标句柄
//@别名 A图标_创建副本()
HICON DuplicateIcon(HINSTANCE hInst, HICON hIcon);

//@备注 用于获取图标的信息
//@参数 图标句柄
//@参数 图标信息结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A图标_取信息()
BOOL GetIconInfo(HICON hIcon, PICONINFO piconinfo);

//@备注 用于获取图标的扩展信息
//@参数 图标句柄
//@参数 扩展图标信息结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A图标_取信息扩展()
BOOL GetIconInfoEx(HICON hIcon, PICONINFOEX piconinfoex);

//@备注 用于从资源中加载一个图标
//@参数 实例句柄
//@参数 图标名称
//@返回 返回加载的图标句柄
//@别名 A图标_加载()
HICON LoadIcon(HINSTANCE hInstance, LPCTSTR lpIconName);

//@备注 用于从可执行文件中提取指定索引的图标
//@参数 实例句柄
//@参数 可执行文件路径
//@参数 图标索引
//@返回 返回提取的图标句柄
//@别名 A图标_取执行文件图标()
HICON ExtractIcon(HINSTANCE hInst, LPCTSTR lpszExeFileName, UINT nIconIndex);

//@备注 用于从可执行文件中提取多个图标
//@参数 文件路径
//@参数 图标索引
//@参数 输出大图标句柄数组
//@参数 输出小图标句柄数组
//@参数 提取的图标数量
//@返回 返回实际提取的图标数量
//@别名 A图标_取执行文件图标扩展()
UINT ExtractIconEx(LPCTSTR lpszFile, int nIconIndex, HICON *phiconLarge, HICON *phiconSmall, UINT nIcons);

//@备注 获取存储为文件中资源或存储在文件的关联可执行文件中的图标的句柄
//@参数 实例句柄
//@参数 图标路径
//@参数 图标索引指针
//@返回 返回提取的图标句柄
//@别名 A图标_取关联执行文件图标()
HICON ExtractAssociatedIcon(HINSTANCE hInst, LPTSTR lpIconPath, LPWORD lpiIcon);

//@备注 用于从可执行文件中提取多个图标，支持更多选项
//@参数 文件路径
//@参数 图标索引
//@参数 图标宽度
//@参数 图标高度
//@参数 输出图标句柄数组
//@参数 输出图标ID数组
//@参数 提取的图标数量
//@参数 提取标志
//@返回 返回实际提取的图标数量
//@别名 A图标_取私有文件全部图标()
UINT PrivateExtractIcons(
    LPCTSTR lpszFile,
    int nIconIndex,
    int cxIcon,
    int cyIcon,
    HICON *phicon,
    UINT *piconid,
    UINT nIcons,
    UINT flags
);

//@分组}


//---------------内核对象----------------------------------------------

//-----------临界区-----------------------------------------------
//@分组{   临界区

//@备注 用于初始化临界区对象
//@参数 lpCriticalSection 临界区结构指针
//@别名 A临界区_初始化()
void InitializeCriticalSection(
    CRITICAL_SECTION* lpCriticalSection  // 临界区结构指针
);

//@备注 用于进入临界区，如果临界区已被其他线程占用，则当前线程会阻塞
//@参数 lpCriticalSection 临界区结构指针
//@别名 A临界区_进入()
void EnterCriticalSection(
    CRITICAL_SECTION* lpCriticalSection  // 临界区结构指针
);

//@备注 用于离开临界区，允许其他线程进入
//@参数 lpCriticalSection 临界区结构指针
//@别名 A临界区_离开()
void LeaveCriticalSection(
    CRITICAL_SECTION* lpCriticalSection  // 临界区结构指针
);

//@备注 尝试在不阻塞的情况下进入关键部分。如果调用成功，则调用线程将取得关键部分的所有权
//@参数 lpCriticalSection 临界区结构指针
//@返回 如果成功进入临界区，返回值为非零值；如果临界区已被占用，返回值为零
//@别名 A临界区_尝试进入()
BOOL TryEnterCriticalSection(
    CRITICAL_SECTION* lpCriticalSection  // 临界区结构指针
);

//@备注 用于删除临界区对象，释放相关资源
//@参数 lpCriticalSection 临界区结构指针
//@别名 A临界区_删除()
void DeleteCriticalSection(
    CRITICAL_SECTION* lpCriticalSection  // 临界区结构指针
);

//@分组}

//----------互斥对象--------------------------

//@分组{   互斥对象

//@备注  创建或打开已命名或未命名的互斥体对象。
//@参数  lpMutexAttributes   [可选] 指向SECURITY_ATTRIBUTES结构的指针。如果此参数为 NULL，则子进程无法继承句柄
//@参数  bInitialOwner       如果此值为 TRUE 并且调用方创建了互斥体，则调用线程将获得互斥对象的初始所有权。否则，调用线程不会获得互斥锁的所有权。若要确定调用方是否创建了互斥锁，请参阅“返回值”部分。
//@参数  lpName              [可选]互斥对象的名称。该名称限制为MAX_PATH个字符。名称比较区分大小写。
//@返回     如果函数成功，则返回值是新创建的互斥对象的句柄
//          如果函数失败，则返回值为 NULL。若要获取扩展的错误信息，请调用 GetLastError。
//          如果互斥体是命名互斥体，并且该对象在此函数调用之前存在，则返回值是现有对象的句柄，并且 GetLastError 函数返回ERROR_ALREADY_EXISTS。
//@别名  A互斥对象_创建扩展(安全属性, 初始所有权, 互斥对象名称)
HANDLE CreateMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName);

//@备注  创建或打开已命名或未命名的互斥对象，并返回该对象的句柄。
//@参数 lpMutexAttributes  [可选] 指向SECURITY_ATTRIBUTES结构的指针。如果此参数为 NULL，则子进程无法继承互斥句柄。
//       结构的 lpSecurityDescriptor 成员为新互斥体指定安全描述符。如果 lpMutexAttributes 为 NULL，则互斥体将获得默认的安全描述符。互斥体的默认安全描述符中的 ACL 来自创建者的主令牌或模拟令牌。有关更多信息，请参见同步对象安全性和访问权限。
//@参数 lpName  [可选]  互斥对象的名称。该名称限制为MAX_PATH个字符。名称比较区分大小写。
//       如果 lpName 为 NULL，则创建互斥对象时不带名称。
//@参数 dwFlags  此参数可以是 0 或以下值。
//      CREATE_MUTEX_INITIAL_OWNER=1  对象创建者是互斥锁的初始所有者。
//@参数 dwDesiredAccess  互斥对象的访问掩码。有关访问权限的列表，请参阅同步对象安全性和访问权限。
//@返回 如果函数成功，则返回值是新创建的互斥对象的句柄
//@别名  A互斥对象_创建扩展2(安全属性, 互斥对象名称, 标识, 访问掩码)
HANDLE CreateMutexEx(LPSECURITY_ATTRIBUTES lpMutexAttributes, LPCWSTR lpName, DWORD dwFlags, DWORD dwDesiredAccess);
*/

//@备注  创建或打开已命名或未命名的互斥体对象。 省略参数
//@参数  bInitialOwner    如果此值为 TRUE 并且调用方创建了互斥体，则调用线程将获得互斥对象的初始所有权。否则，调用线程不会获得互斥锁的所有权。若要确定调用方是否创建了互斥锁，请参阅“返回值”部分。
//@参数  lpName           [可选]互斥对象的名称。该名称限制为MAX_PATH个字符。名称比较区分大小写。
//@返回    如果函数成功，则返回值是新创建的互斥对象的句柄
//         如果函数失败，则返回值为 NULL。若要获取扩展的错误信息，请调用 GetLastError。
//         如果互斥体是命名互斥体，并且该对象在此函数调用之前存在，则返回值是现有对象的句柄，并且 GetLastError 函数返回ERROR_ALREADY_EXISTS。
//@别名  A互斥对象_创建(初始所有权, 互斥对象名称)
static HANDLE xcl_CreateMutex(BOOL bInitialOwner, LPCWSTR lpName)
{
	return CreateMutex(NULL, bInitialOwner, lpName);
}

/*@声明

//@备注 打开现有的命名事件对象
//@参数 dwDesiredAccess 对事件对象的访问。如果指定对象的安全描述符不允许对调用进程进行请求的访问，则该函数将失败。有关访问权限的列表，请参阅同步对象安全性和访问权限。
//@参数 bInheritHandle  如果此值为 TRUE，则此进程创建的进程将继承句柄。否则，进程不会继承此句柄。
//@参数 lpName          要打开的事件的名称。名称比较区分大小写
//@返回 如果函数成功，则返回值是事件对象的句柄。
//      如果函数失败，则返回值为 NULL。若要获取扩展的错误信息，请调用 GetLastError。
//@别名  A互斥对象_打开()
HANDLE OpenMutex(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCWSTR lpName);

//@备注  释放指定互斥对象的所有权
//@返回  如果函数成功，则返回值为非零值
//       如果函数失败，则返回值为零。若要获取扩展的错误信息，请调用 GetLastError。
//@别名  A互斥对象_释放所有权(互斥对象句柄)
BOOL ReleaseMutex(HANDLE hMutex);

//@分组}


//@分组{   等待操作

//@备注 如果函数成功，返回值为TRUE；如果失败，返回值为FALSE。可以通过调用GetLastError函数来获取错误信息。
//@备注  https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-registerwaitforsingleobject
//@参数 phNewWaitObject 指向变量的指针，该变量接收新注册等待对象的句柄。
//@参数 hObject 要等待的内核对象句柄。该对象可以是事件、作业、I/O完成端口、互斥量、信号量或定时器。
//@参数 Callback 当指定的对象被信号通知时调用的回调函数。
//@参数 Context 传递给回调函数的用户定义的值。
//@参数 dwMilliseconds 注册等待对象等待(hObject)信号的时间（以毫秒为单位）。如果这个参数为INFINITE，则等待对象将无限期等待。
//@参数 dwFlags 控制等待行为的标志。可以是0或者以下值的组合：REGISTER_WAITFORSINGLEOBJECT_VALID_FLAGS。
//@别名  A等待_注册单信号对象()
BOOL RegisterWaitForSingleObject(
  PHANDLE             phNewWaitObject,
  HANDLE              hObject,
  WAITORTIMERCALLBACK Callback,
  PVOID               Context,
  ULONG               dwMilliseconds,
  ULONG               dwFlags
);

//@备注 如果函数成功，返回值是一个指示事件发生的索引值，或者是特定状态值；如果失败，返回值为WAIT_FAILED。可以通过调用GetLastError函数来获取错误信息。
//@参数 nCount pHandles数组中句柄的数量。
//@参数 pHandles 指向要等待的句柄数组的指针。
//@参数 fWaitAll 指定等待选项。如果为TRUE，函数返回时所有对象都已被信号通知；如果为FALSE，函数在任一对象被信号通知时返回。
//@参数 dwMilliseconds 指定等待的毫秒数。如果这个参数为INFINITE，则函数将无限期等待。
//@参数 dwWakeMask 指定导致函数返回的输入消息类型。这个参数可以是0，或者是下列值的组合：QS_ALLEVENTS、QS_ALLINPUT、QS_ALLPOSTMESSAGE、QS_HOTKEY、QS_INPUT、QS_KEY、QS_MOUSE、QS_MOUSEMOVE、QS_PAINT、QS_POSTMESSAGE、QS_RAWINPUT、QS_SENDMESSAGE、QS_TIMER。
//@别名 A等待_消息从多对象()
DWORD MsgWaitForMultipleObjects(
  DWORD        nCount,
  const HANDLE *pHandles,
  BOOL         fWaitAll,
  DWORD        dwMilliseconds,
  DWORD        dwWakeMask
);

//@备注 如果函数成功，返回值是一个指示事件发生的索引值，或者是特定状态值；如果失败，返回值为WAIT_FAILED。可以通过调用GetLastError函数来获取错误信息。
//@备注 这个函数是MsgWaitForMultipleObjects的扩展版本，它提供了额外的功能。nCount参数指定了pHandles数组中句柄的数量。pHandles是一个指向句柄数组的指针，这些句柄可以是事件、互斥量、信号量等。
//@参数 nCount pHandles数组中句柄的数量。
//@参数 pHandles 指向要等待的句柄数组的指针。
//@参数 dwMilliseconds 指定等待的毫秒数。如果这个参数为INFINITE，则函数将无限期等待。
//@参数 dwWakeMask 指定导致函数返回的输入消息类型。这个参数可以是0，或者是下列值的组合：QS_ALLEVENTS、QS_ALLINPUT、QS_ALLPOSTMESSAGE、QS_HOTKEY、QS_INPUT、QS_KEY、QS_MOUSE、QS_MOUSEMOVE、QS_PAINT、QS_POSTMESSAGE、QS_RAWINPUT、QS_SENDMESSAGE、QS_TIMER。
//@参数 dwFlags 指定额外的等待选项。这个参数可以是0，或者是下列值的组合：MWMO_INPUTAVAILABLE、MWMO_WAITALL、MWMO_ALERTABLE。
//@别名 A等待_消息从多对象扩展()
DWORD MsgWaitForMultipleObjectsEx(
  DWORD        nCount,
  const HANDLE *pHandles,
  DWORD        dwMilliseconds,
  DWORD        dwWakeMask,
  DWORD        dwFlags
);

//@备注 取消由 RegisterWaitForSingleObject 函数发出的已注册等待操作。
//@别名 A等待_取消注册()
BOOL UnregisterWait(
  HANDLE WaitHandle
);
//@备注 取消由 RegisterWaitForSingleObject 函数发出的已注册等待操作。
//@别名 A等待_取消注册扩展()
BOOL WINAPI UnregisterWaitEx(
  _In_     HANDLE WaitHandle,
  _In_opt_ HANDLE CompletionEvent
);

//@备注  指定的对象是一个互斥对象，在拥有该对象的线程终止之前，该对象不是由拥有该互斥对象的线程释放的。互斥对象的所有权授予调用线程，互斥锁状态设置为无签名。
//如果互斥锁正在保护持久性状态信息，则应检查其一致性。
//@别名  等待_废弃
#define  WAIT_ABANDONED

//@备注  将发出指定对象的状态信号。
//@别名  等待_成功
#define  WAIT_OBJECT_0

//@备注  超时间隔已过，并且对象的状态为无信号。
//@别名  等待_超时
#define WAIT_TIMEOUT

//@备注  该函数已失败。若要获取扩展的错误信息，请调用 GetLastError。
//@别名  等待_失败
#define WAIT_FAILED

//@别名  无限等待
#define INFINITE

//@备注 等待指定的对象处于信号状态或超时间隔过去
//WaitForSingleObject 函数可以等待以下对象
//变更通知
//控制台输入
//事件
//内存资源通知
//互斥
//过程
//信号量
//线程
//可等待计时器
@参数  对象的句柄
@参数  超时间隔，以毫秒为单位。如果指定了非零值，则该函数将一直等到对象发出信号或间隔过去。如果 dw 毫秒为零，则当对象未发出信号时，函数不会进入等待状态;它总是立即返回。如果 dwMilliseconds 是 INFINITE，则仅当对象发出信号时，该函数才会返回
//@别名 A等待_单对象(对象句柄, 超时间隔)
DWORD WINAPI WaitForSingleObject(
	__in HANDLE hHandle,
	__in DWORD dwMilliseconds
	);

//@别名 A等待_单对象扩展()
DWORD WaitForSingleObjectEx(
  HANDLE hHandle,
  DWORD  dwMilliseconds,
  BOOL   bAlertable
);

//@备注 等待一个或所有指定的对象处于信号状态、I/O 完成例程或异步过程调用 （APC） 排队到线程，或者超时间隔过去
//@别名 A等待_多对象()
DWORD WaitForMultipleObjects(
  DWORD        nCount,
  const HANDLE *lpHandles,
  BOOL         bWaitAll,
  DWORD        dwMilliseconds
);

//@备注 首先，它会向一个对象（如信号量、互斥体、事件等）发送信号，通知其他等待该对象的线程或进程该对象的状态已经发生了改变
// 然后，该函数会使调用它的线程进入等待状态，等待另一个对象的信号。这一操作可以在原子操作中完成，以避免信号丢失或竞争条件
//@参数 hObjectToSignal 要发出信号的内核对象的句柄。
//@参数 hObjectToWaitOn 要等待的内核对象的句柄。
//@参数 dwMilliseconds 指定等待的时间，以毫秒为单位。如果设置为INFINITE，则函数将无限期等待。
//@参数 bAlertable 指定等待是否可以被异步过程调用（APC）中断。如果设置为TRUE，等待可以被APC中断；如果设置为FALSE，则不可以。
//@备注 如果函数成功，它将返回一个指示等待结果的值，例如 WAIT_OBJECT_0、WAIT_TIMEOUT 等。如果函数失败，它将返回 WAIT_FAILED。
//@别名 A等待_发送信号并等待()
DWORD SignalObjectAndWait(
  HANDLE hObjectToSignal,
  HANDLE hObjectToWaitOn,
  DWORD  dwMilliseconds,
  BOOL   bAlertable
);

//@备注 监视指定的内存地址，直到该地址的值发生变化或者等待超时。这个函数通常用于同步操作，允许线程在没有其他通知机制的情况下等待某个条件成立。
//@参数 Address 要监视其变化的内存地址。
//@参数 CompareAddress 要与之比较的内存地址。如果Address指向的内存与CompareAddress指向的内存相同，则函数继续等待。
//@参数 AddressSize 要比较的内存区域的大小，以字节为单位。
//@参数 dwMilliseconds 等待的时间，以毫秒为单位。如果设置为INFINITE，则函数将无限期等待。
//@返回 如果函数成功，返回值为TRUE；如果函数在指定的时间内没有观察到地址的变化，返回值为FALSE。如果发生错误，例如无效的参数，函数返回FALSE，并且可以通过调用GetLastError函数来获取错误信息。
//@别名 A等待_指定地址处值改变()
BOOL WaitOnAddress(
 VOID *Address,
  PVOID         CompareAddress,
  SIZE_T        AddressSize,
  DWORD         dwMilliseconds
);

//@备注 使用该函数用于唤醒所有正在等待指定内存地址变化的线程。这个函数通常与 WaitOnAddress 函数一起使用，用于实现线程同步。
//@参数 Address 需要唤醒的线程正在等待的内存地址。指向一个内存地址的指针，该地址是之前通过 WaitOnAddress 函数设置并正在被一个或多个线程监视的。
//@别名 唤醒等待地址值更改的所有线程()
void WakeByAddressAll(PVOID Address);

//@备注 唤醒单个正在等待指定内存地址变化的线程。与 WakeByAddressAll 不同的是，WakeByAddressSingle 只唤醒一个线程，而不是所有等待的线程。
//@参数 Address 指向一个内存地址的指针，该地址是之前通过 WaitOnAddress 函数设置并正在被一个或多个线程监视的。
//@别名 唤醒等待地址值更改的线程()
void WakeByAddressSingle(PVOID Address);

//@分组}


//----信号量功能------------------------------------
//@分组{  信号量功能

@备注 创建或打开已命名或未命名的信号量对象
@参数 lpSemaphoreAttributes [可选] 指向SECURITY_ATTRIBUTES结构的指针。如果此参数为 NULL，则子进程无法继承句柄
@参数 lInitialCount         信号量对象的初始计数。此值必须大于或等于零，并且小于或等于 lMaximumCount。信号量的状态在计数大于零时发出信号，当其计数为零时发出无信号量。每当等待函数释放正在等待信号量的线程时，计数就会减少 1。通过调用 ReleaseSemaphore 函数，计数将增加指定的量。
@参数 lMaximumCount         信号量对象的最大计数。此值必须大于零。
@参数 lpName                [可选]  信号量对象的名称。该名称限制为MAX_PATH个字符。名称比较区分大小写。
@     如果 lpName 与现有命名信号量对象的名称匹配，则此函数请求SEMAPHORE_ALL_ACCESS访问权限。在这种情况下，将忽略 lInitialCount 和 lMaximumCount 参数，因为它们已由创建过程设置。如果 lpSemaphoreAttributes 参数不是 NULL，它将确定句柄是否可以继承，但会忽略其安全描述符成员
@     如果 lpName 为 NULL，则创建不带名称的信号量对象
@返回 如果函数成功，则返回值是信号量对象的句柄。如果在函数调用之前存在命名的信号量对象，则该函数将返回现有对象的句柄，GetLastError 将返回ERROR_ALREADY_EXISTS
@     如果函数失败，则返回值为 NULL。若要获取扩展的错误信息，请调用 GetLastError。
@别名 A信号量_创建扩展(安全属性, 初始计数, 最大计数, 信号量对象的名称)
HANDLE CreateSemaphore(
  LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  LONG                  lInitialCount,
  LONG                  lMaximumCount,
  LPCWSTR               lpName
);

*/

//@备注 创建或打开已命名或未命名的信号量对象
//@参数 lInitialCount         信号量对象的初始计数。此值必须大于或等于零，并且小于或等于 lMaximumCount。信号量的状态在计数大于零时发出信号，当其计数为零时发出无信号量。每当等待函数释放正在等待信号量的线程时，计数就会减少 1。通过调用 ReleaseSemaphore 函数，计数将增加指定的量。
//@参数 lMaximumCount         信号量对象的最大计数。此值必须大于零。
//@参数 lpName                [可选]  信号量对象的名称。该名称限制为MAX_PATH个字符。名称比较区分大小写。
//      如果 lpName 与现有命名信号量对象的名称匹配，则此函数请求SEMAPHORE_ALL_ACCESS访问权限。在这种情况下，将忽略 lInitialCount 和 lMaximumCount 参数，因为它们已由创建过程设置。如果 lpSemaphoreAttributes 参数不是 NULL，它将确定句柄是否可以继承，但会忽略其安全描述符成员
//      如果 lpName 为 NULL，则创建不带名称的信号量对象
//@返回 如果函数成功，则返回值是信号量对象的句柄。如果在函数调用之前存在命名的信号量对象，则该函数将返回现有对象的句柄，GetLastError 将返回ERROR_ALREADY_EXISTS
//      如果函数失败，则返回值为 NULL。若要获取扩展的错误信息，请调用 GetLastError。
//@别名 A信号量_创建(初始计数, 最大计数, 信号量对象的名称)
static HANDLE xcl_CreateSemaphore(LONG lInitialCount,  LONG lMaximumCount, LPCWSTR lpName)
{
	return CreateSemaphore(NULL, lInitialCount,  lMaximumCount, lpName);
}


/*@声明

//@备注 CreateSemaphoreEx 函数创建一个新的信号量对象，并返回一个句柄，该句柄可用于后续的信号量操作。
//@参数 lpSemaphoreAttributes 一个指向SECURITY_ATTRIBUTES结构的指针，该结构指定新信号量的安全描述符，并确定子进程是否可以继承返回的句柄。如果此参数为NULL，则信号量将获得一个默认的安全描述符，并且句柄不能被继承。
//@参数 lInitialCount 信号量的初始计数。这个值必须大于或等于0且小于或等于lMaximumCount。
//@参数 lMaximumCount 信号量的最大计数。这个值必须大于0。
//@参数 lpName 信号量的名称。如果该参数为NULL，则信号量没有名称。如果名称与一个现有的信号量名称相同，则函数将使用现有的信号量，而不是创建一个新的信号量。名称的最大长度由MAX_PATH定义。
//@参数 dwFlags 控制信号量的行为。这个参数可以是0，或者是一个或多个以下值的组合：
//    SEMAPHORE_ALL_ACCESS: 允许完全访问信号量。
//    SEMAPHORE_MODIFY_STATE: 允许使用ReleaseSemaphore函数修改信号量的状态。
//@参数 dwDesiredAccess 指定请求的访问权限。这个参数可以是以下值的组合：
//    SEMAPHORE_MODIFY_STATE: 允许使用ReleaseSemaphore函数修改信号量的状态。
//    SEMAPHORE_QUERY_STATE: 允许使用QuerySemaphore函数查询信号量的状态。
//@别名 A信号量_创建扩展2(安全属性)
HANDLE CreateSemaphoreEx(
  LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
  LONG                  lInitialCount,
  LONG                  lMaximumCount,
  LPCSTR                lpName,
  DWORD                 dwFlags,
  DWORD                 dwDesiredAccess
);

//@备注 OpenSemaphore 允许一个进程访问另一个进程创建的信号量，前提是提供了正确的信号量名称和所需的访问权限。
//  如果信号量已经存在，并且调用进程有足够的权限，那么该函数将返回信号量的句柄，该句柄可以用于信号量的同步操作。
//@参数 dwDesiredAccess 指定请求的访问权限。这个参数可以是以下值的组合：
//    SEMAPHORE_MODIFY_STATE: 允许使用 ReleaseSemaphore 函数修改信号量的状态。
//    SEMAPHORE_QUERY_STATE: 允许使用 QuerySemaphore 函数查询信号量的状态。
//@参数 bInheritHandle 指定返回的句柄是否可以被新创建的进程继承。如果此参数为 TRUE，则句柄可以继承；如果为 FALSE，则不能继承。
//@参数 lpName 指定要打开的信号量的名称。如果名称为 NULL，或者指定了一个不存在的信号量名称，则函数调用将失败。
//@别名 A信号量_打开()
HANDLE OpenSemaphore(
  DWORD   dwDesiredAccess,
  BOOL    bInheritHandle,
  LPCWSTR lpName
);

@备注  将指定的信号量对象的计数增加指定的量
@参数  hSemaphore     信号量对象的句柄。CreateSemaphore 或 OpenSemaphore 函数返回此句柄。
@参数  lReleaseCount  信号量对象的当前计数要增加的量。该值必须大于零。如果指定的量会导致信号量的计数超过创建信号量时指定的最大计数，则不会更改计数，并且该函数返回 FALSE。
@参数  lpPreviousCount [可选] 指向变量的指针，用于接收信号量的上一个计数。如果不需要上一个计数，则此参数可以为 NULL
@返回  如果函数成功，则返回值为非零值
@      如果函数失败，则返回值为零。若要获取扩展的错误信息，请调用 GetLastError。
@别名  A信号量_释放(信号量对象的句柄, 当前计数要增加的量, 接收信号量的上一个计数)
BOOL ReleaseSemaphore(
  HANDLE hSemaphore,
  LONG   lReleaseCount,
  LPLONG lpPreviousCount
);

//@分组}

//----------事件对象-------------------------------------------------

//@分组{  事件对象

//@备注 创建或打开已命名或未命名的事件对象
//@参数 lpEventAttributes  [可选] 指向SECURITY_ATTRIBUTES结构的指针。如果此参数为 NULL，则子进程无法继承句柄。
// 结构的 lpSecurityDescriptor 成员为新事件指定安全描述符。如果 lpEventAttributes 为 NULL，则该事件将获得默认安全描述符。事件的默认安全描述符中的 ACL 来自创建者的主令牌或模拟令牌。
//@参数  bManualReset  如果此参数为 TRUE，则该函数将创建一个手动重置事件对象，该对象需要使用 ResetEvent 函数将事件状态设置为无签名。如果此参数为 FALSE，则该函数将创建一个自动复位事件对象，并在释放单个等待线程后，系统自动将事件状态重置为非信号。
//@参数  bInitialState  如果此参数为 TRUE，则向事件对象发出初始状态信号;否则，它是无信号的。
//@参数  lpName   [可选] 事件对象的名称。该名称限制为MAX_PATH个字符。名称比较区分大小写。
//@别名  A事件对象_创建扩展(安全属性, 手动重置, 初始状态, 事件对象名称)
HANDLE CreateEvent(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  BOOL                  bManualReset,
  BOOL                  bInitialState,
  LPCWSTR               lpName
);
*/

//@备注  创建或打开已命名或未命名的事件对象
//@参数  bManualReset       如果此参数为 TRUE，则该函数将创建一个手动重置事件对象，该对象需要使用 ResetEvent 函数将事件状态设置为无签名。如果此参数为 FALSE，则该函数将创建一个自动复位事件对象，并在释放单个等待线程后，系统自动将事件状态重置为非信号。
//@参数  bInitialState      如果此参数为 TRUE，则向事件对象发出初始状态信号;否则，它是无信号的。
//@参数  lpName             [可选] 事件对象的名称。该名称限制为MAX_PATH个字符。名称比较区分大小写。
//@别名  A事件对象_创建(手动重置, 初始状态, 事件对象名称)
static HANDLE xcl_CreateEvent(BOOL bManualReset, BOOL bInitialState, LPCWSTR lpName)
{
	return CreateEvent(NULL, bManualReset, bInitialState, lpName);
}

/*@声明

//@备注 创建一个事件对象，该对象可以用于同步线程或进程之间的操作。事件对象有两种状态：信号状态和非信号状态。
//线程可以等待事件变为信号状态，或者设置事件的状态。
//根据 dwFlags 参数的不同，事件可以是自动重置的（当线程等待后自动变为非信号状态）或手动重置的（需要显式调用 ResetEvent 函数来重置状态）。
//@参数 lpEventAttributes 一个指向SECURITY_ATTRIBUTES结构的指针，该结构指定新事件对象的安全描述符，并确定子进程是否可以继承返回的句柄。
//  如果此参数为NULL，则事件对象将获得一个默认的安全描述符，并且句柄不能被继承。
//@参数 lpName 指定事件对象的名称。如果此参数为NULL，则创建一个未命名的事件对象。如果名称与现有的事件对象相同，则函数将失败，除非dwFlags参数中包含了CREATE_ALWAYS标志。
//@参数 dwFlags 指定如何创建事件。可以是以下值的组合：
//    CREATE_EVENT_MANUAL_RESET: 创建一个手动重置事件。必须使用ResetEvent函数手动将事件状态重置为非信号状态。
//    CREATE_EVENT_INITIAL_SET: 创建时将事件状态设置为信号状态。
//    CREATE_ALWAYS: 如果事件已经存在，则忽略lpName参数，并创建一个新的事件对象。
//@参数 dwDesiredAccess 指定请求的访问权限。可以是以下值的组合：
//    EVENT_MODIFY_STATE: 允许使用SetEvent和ResetEvent函数修改事件的状态。
//    EVENT_ALL_ACCESS: 允许完全访问权限。
//@别名  A事件对象_创建扩展2()
HANDLE CreateEventEx(
  LPSECURITY_ATTRIBUTES lpEventAttributes,
  LPCWSTR               lpName,
  DWORD                 dwFlags,
  DWORD                 dwDesiredAccess
);

//@备注 OpenEvent 函数允许一个进程访问另一个进程创建的命名事件对象。
//如果事件对象已经存在，并且调用进程有足够的权限，那么该函数将返回事件对象的句柄，该句柄可以用于事件同步操作。
//如果事件名称是 NULL，或者没有指定正确的权限，或者事件不存在，函数将失败。
//@参数 dwDesiredAccess 指定请求的访问权限。这个参数可以是以下值的组合：
//    EVENT_MODIFY_STATE: 允许使用 SetEvent 和 ResetEvent 函数修改事件的状态。
//    EVENT_ALL_ACCESS: 允许完全访问权限。
//@参数 bInheritHandle 指定返回的句柄是否可以被新创建的进程继承。如果为 TRUE，则子进程可以继承该句柄。
//@参数 lpName 指定要打开的事件对象的名称。如果事件是系统事件，则可以是系统定义的事件名称。
//@别名  A事件对象_打开()
HANDLE WINAPI OpenEvent(
  __in          DWORD dwDesiredAccess,
  __in          BOOL bInheritHandle,
  __in          LPCTSTR lpName
);

//@备注 ResetEvent 函数仅对手动重置事件有效。对于自动重置事件，它们在释放一个等待线程后自动重置，因此不需要调用 ResetEvent 来手动重置。
//  手动重置事件在释放所有等待线程后不会自动重置，需要显式调用 ResetEvent 来将其状态设置为非信号状态。
//  使用 ResetEvent 可以在事件已经被设置（变为信号状态）后，将其重新设置为非信号状态，以便再次使用该事件进行同步操作。如果传递给 ResetEvent 的句柄无效，或者句柄不是事件句柄，函数将失败。
//@参数 hEvent 指定要重置的事件的句柄。这个句柄是通过 CreateEvent 或 OpenEvent 函数获取的。
//@别名 A事件对象_重置无信号(事件对象句柄)
BOOL ResetEvent(HANDLE hEvent);

//@备注 SetEvent 函数的作用是将事件的状态设置为信号状态，这会唤醒所有正在等待该事件的线程（对于手动重置事件）或一个等待线程（对于自动重置事件）。以下是关于 SetEvent 函数的一些详细信息：
//  对于手动重置事件，一旦事件被设置为信号状态，它会保持这种状态直到 ResetEvent 函数被调用或者 CloseHandle 函数关闭了事件句柄。
//  对于自动重置事件，一旦事件被设置为信号状态，它会唤醒一个等待的线程，然后自动回到非信号状态。
//  如果传递给 SetEvent 的句柄无效，或者句柄不是事件句柄，函数将失败。
//  SetEvent 通常用于线程同步，允许一个线程通知一个或多个其他线程某个条件已经满足。
//  如果函数成功，返回值为非零（TRUE）。
//  如果函数失败，返回值为零（FALSE）。要获取错误信息，可以调用 GetLastError 函数。
//  SetEvent 通常用于线程同步，允许一个线程通知一个或多个其他线程某个条件已经满足。
//@参数 hEvent 指定要设置的事件的句柄。这个句柄是通过 CreateEvent 或 OpenEvent 函数获取的。
//@返回 成功返回值为非零（TRUE），失败返回值为零（FALSE）
//@别名 A事件对象_置有信号(事件对象句柄)
BOOL SetEvent(HANDLE hEvent);

//@分组}

//-------------通信管道---------------------------

//@分组{  通信管道

//@备注 创建匿名管道，并将句柄返回到管道的读取端和写端
// 匿名管道是使用具有唯一名称的命名管道实现的。因此，通常可以将匿名管道的句柄传递给需要命名管道句柄的函数
//@参数 输出读取端句柄
//@参数 输出写入端句柄
//@参数 安全属性指针（可选）
//@参数 管道缓冲区大小
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_创建匿名管道()
BOOL CreatePipe(
  PHANDLE               hReadPipe,
  PHANDLE               hWritePipe,
  LPSECURITY_ATTRIBUTES lpPipeAttributes,
  DWORD                 nSize
);

//@备注 创建命名管道的实例，并返回后续管道操作的句柄。命名管道服务器进程使用此函数创建特定命名管道的第一个实例并建立其基本属性，或者创建现有命名管道的新实例。
//@参数 管道名称
//@参数 打开模式（如 PIPE_ACCESS_DUPLEX, PIPE_ACCESS_INBOUND）
//@参数 管道模式（如 PIPE_TYPE_BYTE, PIPE_TYPE_MESSAGE）
//@参数 最大实例数
//@参数 输出缓冲区大小
//@参数 输入缓冲区大小
//@参数 默认超时时间
//@参数 安全属性指针（可选）
//@返回 返回命名管道的句柄
//@别名 A通信管道_创建命名管道()
HANDLE WINAPI CreateNamedPipe(
  __in          LPCTSTR lpName,
  __in          DWORD dwOpenMode,
  __in          DWORD dwPipeMode,
  __in          DWORD nMaxInstances,
  __in          DWORD nOutBufferSize,
  __in          DWORD nInBufferSize,
  __in          DWORD nDefaultTimeOut,
  __in          LPSECURITY_ATTRIBUTES lpSecurityAttributes
);

//@备注 连接到消息类型管道（如果管道的某个实例不可用，则等待），写入管道并从中读取，然后关闭管道。
//@参数 命名管道名称
//@参数 输入缓冲区指针
//@参数 输入缓冲区大小
//@参数 输出缓冲区指针
//@参数 输出缓冲区大小
//@参数 输出实际读取的字节数
//@参数 超时时间
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_调用()
BOOL WINAPI CallNamedPipe(
  __in          LPCTSTR lpNamedPipeName,
  __in          LPVOID lpInBuffer,
  __in          DWORD nInBufferSize,
  __out         LPVOID lpOutBuffer,
  __in          DWORD nOutBufferSize,
  __out         LPDWORD lpBytesRead,
  __in          DWORD nTimeOut
);

//@备注 使命名管道服务器进程能够等待客户端进程连接到命名管道的实例。客户端进程通过调用 CreateFile 或 CallNamedPipe 函数进行连接。
//@参数 命名管道句柄
//@参数 重叠结构体指针（可选）
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_链接()
BOOL ConnectNamedPipe(
  HANDLE       hNamedPipe,
  LPOVERLAPPED lpOverlapped
);

//@备注 断开命名管道实例的服务器端与客户端进程的连接
//@参数 命名管道句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_断开()
BOOL DisconnectNamedPipe(
  HANDLE hNamedPipe
);

//@备注 检索指定命名管道的客户端计算机名称
//@参数 命名管道句柄
//@参数 输出客户端计算机名称
//@参数 客户端计算机名称长度
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_取客户端计算机名称()
BOOL WINAPI GetNamedPipeClientComputerName(
  __in          HANDLE Pipe,
  __out         LPTSTR ClientComputerName,
  __in          ULONG ClientComputerNameLength
);

//@备注 检索指定命名管道的客户端进程标识符
//@参数 命名管道句柄
//@参数 输出客户端进程ID
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_取客户端进程ID()
BOOL GetNamedPipeClientProcessId(
  HANDLE Pipe,
  PULONG ClientProcessId
);

//@备注 检索指定命名管道的客户端会话标识符。
//@参数 命名管道句柄
//@参数 输出客户端会话ID
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_取客户端会话ID()
BOOL GetNamedPipeClientSessionId(
  HANDLE Pipe,
  PULONG ClientSessionId
);

//@备注 检索有关指定命名管道的信息。在命名管道实例的生存期内，返回的信息可能会有所不同
//@参数 命名管道句柄
//@参数 输出管道状态
//@参数 输出当前实例数
//@参数 输出最大收集计数
//@参数 输出收集数据超时时间
//@参数 输出用户名
//@参数 用户名最大长度
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_取状态()
BOOL WINAPI GetNamedPipeHandleState(
  __in          HANDLE hNamedPipe,
  __out         LPDWORD lpState,
  __out         LPDWORD lpCurInstances,
  __out         LPDWORD lpMaxCollectionCount,
  __out         LPDWORD lpCollectDataTimeout,
  __out         LPTSTR lpUserName,
  __in          DWORD nMaxUserNameSize
);

//@备注 检索有关指定命名管道的信息。
//@参数 命名管道句柄
//@参数 输出管道标志
//@参数 输出输出缓冲区大小
//@参数 输出输入缓冲区大小
//@参数 输出最大实例数
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_取信息()
BOOL GetNamedPipeInfo(
  HANDLE  hNamedPipe,
  LPDWORD lpFlags,
  LPDWORD lpOutBufferSize,
  LPDWORD lpInBufferSize,
  LPDWORD lpMaxInstances
);

//@备注 检索指定命名管道的服务器进程标识符
//@参数 命名管道句柄
//@参数 输出服务器进程ID
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_取服务端进程ID()
BOOL GetNamedPipeServerProcessId(
  HANDLE Pipe,
  PULONG ServerProcessId
);

//@备注 检索指定命名管道的服务器会话标识符
//@参数 命名管道句柄
//@参数 输出服务器会话ID
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_取服务端会话ID()
BOOL GetNamedPipeServerSessionId(
  HANDLE Pipe,
  PULONG ServerSessionId
);

//@备注 模拟命名管道客户端函数模拟命名管道客户端应用程序
//@参数 命名管道句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_模拟客户端()
BOOL ImpersonateNamedPipeClient(HANDLE hNamedPipe);

//@备注 将数据从命名或匿名管道复制到缓冲区中，而不将其从管道中删除。它还返回有关管道中数据的信息
//@参数 命名管道句柄
//@参数 输出缓冲区指针
//@参数 缓冲区大小
//@参数 输出实际读取的字节数
//@参数 输出总可用字节数
//@参数 输出当前消息剩余字节数
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_窥视()
BOOL PeekNamedPipe(
  HANDLE  hNamedPipe,
  LPVOID  lpBuffer,
  DWORD   nBufferSize,
  LPDWORD lpBytesRead,
  LPDWORD lpTotalBytesAvail,
  LPDWORD lpBytesLeftThisMessage
);

//@备注 等待，直到超时间隔过去或指定命名管道的实例可用于连接（即，管道的服务器进程在管道上具有挂起的 ConnectNamedPipe 操作）
//@参数 命名管道名称
//@参数 超时时间
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_等待()
BOOL WINAPI WaitNamedPipe(
  __in          LPCTSTR lpNamedPipeName,
  __in          DWORD nTimeOut
);

//@备注 设置指定命名管道的读取模式和阻塞模式。如果指定的句柄位于命名管道的客户端，并且命名管道服务器进程位于远程计算机上，则该函数还可用于控制本地缓冲。
//@参数 命名管道句柄
//@参数 管道模式指针
//@参数 最大收集计数指针
//@参数 收集数据超时时间指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_置状态()
BOOL SetNamedPipeHandleState(
  HANDLE  hNamedPipe,
  LPDWORD lpMode,
  LPDWORD lpMaxCollectionCount,
  LPDWORD lpCollectDataTimeout
);

//@备注 将消息写入指定命名管道和从指定命名管道读取消息的函数合并到单个网络操作中
//@参数 命名管道句柄
//@参数 输入缓冲区指针
//@参数 输入缓冲区大小
//@参数 输出缓冲区指针
//@参数 输出缓冲区大小
//@参数 输出实际读取的字节数
//@参数 重叠结构体指针（可选）
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A通信管道_事务()
BOOL TransactNamedPipe(
  HANDLE       hNamedPipe,
  LPVOID       lpInBuffer,
  DWORD        nInBufferSize,
  LPVOID       lpOutBuffer,
  DWORD        nOutBufferSize,
  LPDWORD      lpBytesRead,
  LPOVERLAPPED lpOverlapped
);

//@分组}
*/


//------------线程-------------------------------------------------------
//@分组{  线程

//@备注 回调函数格式: DWORD WINAPI 线程函数格式(空类型* 用户数据);
// #外部类型 DWORD
//@参数 用户指定的线程运行函数, 回调函数
//@参数 用户数据, 传递给线程函数
//@参数 接收返回的线程ID
//@返回 线程句柄
//@别名 A线程_创建(回调函数, 用户数据, 返回线程ID)
static HANDLE xcl_CreateThread(LPTHREAD_START_ROUTINE ThreadProc, void* pParameter=NULL, UINT* pThreadId=NULL)
{
	DWORD threadID = 0;
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, pParameter, 0, &threadID);
	if (pThreadId)
		*pThreadId = threadID;
	return hThread;
}

/*@声明


//@备注 用于在指定进程中创建一个远程线程
//@参数 hProcess 目标进程句柄
//@参数 lpThreadAttributes 线程安全属性（可选）
//@参数 dwStackSize 堆栈大小（可选）
//@参数 lpStartAddress 线程起始地址
//@参数 lpParameter 线程参数
//@参数 dwCreationFlags 创建标志
//@参数 lpThreadId 返回的线程ID（可选）
//@返回 如果函数成功，返回值为线程句柄；如果函数失败，返回值为NULL
//@别名 A线程_创建远程线程()
HANDLE CreateRemoteThread(
  HANDLE                 hProcess,
  LPSECURITY_ATTRIBUTES  lpThreadAttributes,
  SIZE_T                 dwStackSize,
  LPTHREAD_START_ROUTINE lpStartAddress,
  LPVOID                 lpParameter,
  DWORD                  dwCreationFlags,
  LPDWORD                lpThreadId
);

//@备注 用于在指定进程中创建一个远程线程，并支持线程属性列表
//@参数 hProcess 目标进程句柄
//@参数 lpThreadAttributes 线程安全属性（可选）
//@参数 dwStackSize 堆栈大小（可选）
//@参数 lpStartAddress 线程起始地址
//@参数 lpParameter 线程参数
//@参数 dwCreationFlags 创建标志
//@参数 lpAttributeList 线程属性列表（可选）
//@参数 lpThreadId 返回的线程ID（可选）
//@返回 如果函数成功，返回值为线程句柄；如果函数失败，返回值为NULL
//@别名 A线程_创建远程线程扩展()
HANDLE CreateRemoteThreadEx(
  HANDLE                       hProcess,
  LPSECURITY_ATTRIBUTES        lpThreadAttributes,
  SIZE_T                       dwStackSize,
  LPTHREAD_START_ROUTINE       lpStartAddress,
  LPVOID                       lpParameter,
  DWORD                        dwCreationFlags,
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
  LPDWORD                      lpThreadId
);

@备注 创建要在调用进程的虚拟地址空间中执行的线程
@ 若要创建在另一个进程的虚拟地址空间中运行的线程，请使用 CreateRemoteThread 函数
@参数 lpThreadAttributes [可选] 指向SECURITY_ATTRIBUTES结构的指针，该结构确定子进程是否可以继承返回的句柄。如果 lpThreadAttributes 为 NULL，则句柄不能被继承。
@参数 dwStackSize        堆栈的初始大小，以字节为单位。系统将此值舍入到最接近的页面。如果此参数为零，则新线程将使用可执行文件的默认大小。有关更多信息，请参见线程堆栈大小。
@参数 lpStartAddress     指向要由线程执行的应用程序定义函数的指针。此指针表示线程的起始地址。有关线程函数的详细信息，请参阅线程过程。
@参数 lpParameter        [可选] 指向要传递给线程的变量的指针。
@参数 dwCreationFlags    控制线程创建的标志。 0:线程在创建后立即运行。 
@                        CREATE_SUSPENDED=0x04:线程是在挂起状态下创建的，并且在调用 ResumeThread 函数之前不会运行 
@                        STACK_SIZE_PARAM_IS_A_RESERVATION=0x00010000: dwStackSize 参数指定堆栈的初始保留大小。如果未指定此标志，则 dwStackSize 指定提交大小。
@参数 lpThreadId         [可选] 指向接收线程标识符的变量的指针。如果此参数为 NULL，则不返回线程标识符。
@返回 如果函数成功，则返回值是新线程的句柄
@      如果函数失败，则返回值为 NULL。若要获取扩展的错误信息，请调用 GetLastError。
@别名  A线程_创建线程扩展(安全属性, 堆栈的初始大小, 线程函数, 传递给线程的数据指针, 控制线程创建的标志, 接收线程ID)
HANDLE CreateThread(
  LPSECURITY_ATTRIBUTES   lpThreadAttributes,
  SIZE_T                  dwStackSize,
  LPTHREAD_START_ROUTINE  lpStartAddress,
  LPVOID                  lpParameter,
  DWORD                   dwCreationFlags,
  LPDWORD                 lpThreadId
);

//@备注 用于终止当前线程的执行，并返回退出码
//@参数 dwExitCode 线程退出码
//@别名 A线程_退出()
void ExitThread(DWORD dwExitCode);

//@备注 用于强制终止指定线程的执行
//@参数 hThread 线程句柄
//@参数 dwExitCode 线程退出码
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A线程_终止(线程句柄, 线程退出码)
BOOL TerminateThread(
    HANDLE hThread,  // 线程句柄
    DWORD dwExitCode // 线程退出码
);

//@备注 用于获取当前线程的伪句柄
//@返回 当前线程的伪句柄
//@别名 A线程_取当前线程()
HANDLE GetCurrentThread();

//@备注 用于获取当前线程的线程ID
//@返回 当前线程的线程ID
//@别名 A线程_取当前线程ID()
DWORD GetCurrentThreadId();

//@备注 用于获取当前线程的访问令牌句柄
//@返回 当前线程的访问令牌句柄
//@别名 A线程_取当前线程令牌()
HANDLE GetCurrentThreadToken();

//@备注 用于获取指定线程的退出码
//@参数 hThread 线程句柄
//@参数 lpExitCode 返回的线程退出码
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A线程_取退出码()
BOOL GetExitCodeThread(
  HANDLE  hThread,
  LPDWORD lpExitCode
);

//@备注 用于获取指定线程的上下文（如寄存器状态）
//@参数 hThread 线程句柄
//@参数 lpContext 线程上下文结构指针
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A线程_取上下文()
BOOL GetThreadContext(
    HANDLE hThread,  // 线程句柄
    LPCONTEXT lpContext // 线程上下文结构指针
);

//@备注 检索通过调用 SetThreadDescription 分配给线程的说明
//@参数 hThread 线程句柄
//@参数 ppszThreadDescription 返回的线程描述字符串
//@返回 如果函数成功，返回值为 S_OK；如果函数失败，返回错误代码
//@别名  A线程_取描述()
HRESULT GetThreadDescription(HANDLE hThread, PWSTR  *ppszThreadDescription);

//@备注 用于获取指定线程的线程ID
//@参数 Thread 线程句柄
//@返回 线程ID
//@别名 A线程_取ID()
DWORD GetThreadId(
    HANDLE Thread  // 线程句柄
);

//@备注 用于获取指定线程的特定信息（如优先级、亲和性等）
//@参数 hThread 线程句柄
//@参数 ThreadInformationClass 线程信息类别
//@参数 ThreadInformation 线程信息结构指针
//@参数 ThreadInformationSize 线程信息结构大小
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A线程_取信息()
BOOL GetThreadInformation(
  HANDLE                   hThread,
  THREAD_INFORMATION_CLASS ThreadInformationClass,
  LPVOID                   ThreadInformation,
  DWORD                    ThreadInformationSize
);

//@备注 检索指定线程的时间信息
//@参数 hThread 线程句柄
//@参数 lpCreationTime 返回的线程创建时间
//@参数 lpExitTime 返回的线程退出时间
//@参数 lpKernelTime 返回的线程内核模式时间
//@参数 lpUserTime 返回的线程用户模式时间
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A线程_取时间信息()
BOOL GetThreadTimes(
  HANDLE     hThread,
  LPFILETIME lpCreationTime,
  LPFILETIME lpExitTime,
  LPFILETIME lpKernelTime,
  LPFILETIME lpUserTime
);

//@备注 用于打开指定线程的句柄
//@参数 dwDesiredAccess 访问权限
//@参数 bInheritHandle 是否继承句柄
//@参数 dwThreadId 线程ID
//@返回 如果函数成功，返回值为线程句柄；如果函数失败，返回值为NULL
//@别名 A线程_打开()
HANDLE OpenThread(
  DWORD dwDesiredAccess,
  BOOL  bInheritHandle,
  DWORD dwThreadId
);

//@参数 ThreadHandle 线程的句柄。这个句柄必须具有THREAD_QUERY_INFORMATION、THREAD_SET_INFORMATION或THREAD_IMPERSONATE访问权限。如果设置为NULL，则函数尝试打开调用线程的令牌。
//@参数 DWORD DesiredAccess：
@                              指定你希望对令牌进行的操作类型。这个参数可以是以下一个或多个访问权限标志的组合：
@                              TOKEN_ASSIGN_PRIMARY：指定赋予令牌的主要权限。
@                              TOKEN_DUPLICATE：指定复制令牌的权限。
@                              TOKEN_IMPERSONATE：指定模拟令牌的权限。
@                              TOKEN_QUERY：指定查询令牌的权限。
@                              TOKEN_QUERY_SOURCE：指定查询令牌源的权限。
@                              TOKEN_ADJUST_PRIVILEGES：指定调整令牌权限的权限。
@                              TOKEN_ADJUST_GROUPS：指定调整令牌组的权限。
@                              TOKEN_ADJUST_DEFAULT：指定调整令牌默认所有者、主组、DACL和SACL的权限。
//@参数 OpenAsSelf 指示函数是否应该以调用者的名义打开线程的令牌。如果设置为TRUE，函数将尝试打开调用者线程的令牌；如果设置为FALSE，函数将尝试打开由ThreadHandle指定的线程的令牌。
//@参数 TokenHandle 指向一个变量的指针，该变量接收打开的访问令牌的句柄。如果函数成功，该句柄将具有DesiredAccess参数中指定的访问权限。如果函数失败，该句柄将无效。
//@返回 如果函数成功，返回值为TRUE；如果失败，返回值为FALSE。可以通过调用GetLastError函数来获取错误信息。
//@别名 A线程_打开令牌()
BOOL OpenThreadToken(
  HANDLE  ThreadHandle,
  DWORD   DesiredAccess,
  BOOL    OpenAsSelf,
  PHANDLE TokenHandle
);

//@参数 hThread 要恢复的线程的句柄。句柄必须具有THREAD_SUSPEND_RESUME访问权限。
//@返回 如果函数成功，返回值为线程的之前挂起计数；如果失败，返回值为(DWORD)-1。可以通过调用GetLastError函数来获取错误信息。
//@别名 A线程_恢复()
DWORD ResumeThread(
  HANDLE hThread
);

//@备注 用于设置指定线程的上下文（如寄存器状态）
//@参数 hThread 目标线程的句柄
//@参数 lpContext 线程上下文结构指针
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A线程_置上下文()
BOOL SetThreadContext(HANDLE hThread, const CONTEXT *lpContext);

//@备注 用于设置指定线程的描述信息（调试或诊断用途）
//@参数 hThread 目标线程的句柄
//@参数 lpThreadDescription 线程描述字符串
//@返回 如果函数成功，返回值为 S_OK；如果函数失败，返回错误代码
//@别名 A线程_置描述()
HRESULT SetThreadDescription(HANDLE hThread, PCWSTR lpThreadDescription);

//@备注 用于设置指定线程的令牌（安全上下文）
//@参数 Thread 目标线程的句柄
//@参数 Token 要设置的令牌句柄
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A线程_置令牌()
BOOL SetThreadToken(PHANDLE Thread, HANDLE  Token);

//@备注 用于设置指定线程的特定信息（如优先级、亲和性等）
//@参数 hThread 目标线程的句柄
//@参数 ThreadInformationClass 线程信息类别
//@参数 ThreadInformation 线程信息结构指针
//@参数 ThreadInformationSize 线程信息结构大小
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A线程_置信息()
BOOL SetThreadInformation(
  HANDLE                   hThread,
  THREAD_INFORMATION_CLASS ThreadInformationClass,
  LPVOID                   ThreadInformation,
  DWORD                    ThreadInformationSize
);

//@别名 A线程_暂停()
DWORD SuspendThread(HANDLE hThread);

//@备注 使调用线程将执行权交给另一个准备在当前处理器上运行的线程。操作系统选择要执行的下一个线程
//@别名 A线程_切换() 
BOOL SwitchToThread();
	
//@分组}


//@分组{  进程

//@备注 用于创建一个新进程及其主线程
//@参数 lpApplicationName 应用程序名称（完整路径）
//@参数 lpCommandLine 命令行参数
//@参数 lpProcessAttributes 进程安全属性（可选）
//@参数 lpThreadAttributes 线程安全属性（可选）
//@参数 bInheritHandles 是否继承句柄
//@参数 dwCreationFlags 创建标志
//@参数 lpEnvironment 环境变量（可选）
//@参数 lpCurrentDirectory 当前目录（可选）
//@参数 lpStartupInfo 启动信息结构指针
//@参数 lpProcessInformation 进程信息结构指针
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A进程_创建()
BOOL CreateProcess(
  LPCWSTR               lpApplicationName,
  LPWSTR                lpCommandLine,
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL                  bInheritHandles,
  DWORD                 dwCreationFlags,
  LPVOID                lpEnvironment,
  LPCWSTR               lpCurrentDirectory,
  LPSTARTUPINFOW        lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
);

//@备注 如果函数成功，返回值为TRUE；如果失败，返回值为FALSE。可以通过调用GetLastError函数来获取错误信息。
//@参数 hProcess 要终止的进程的句柄。句柄必须具有PROCESS_TERMINATE权限。
//@参数 uExitCode 进程及其所有线程的终止状态码。
//@别名 A进程_终止()
BOOL TerminateProcess(HANDLE hProcess, UINT   uExitCode);

//@备注 用于打开指定进程的句柄
//@参数 dwDesiredAccess 访问权限
//@参数 bInheritHandle 是否继承句柄
//@参数 dwProcessId 进程ID
//@返回 如果函数成功，返回值为进程句柄；如果函数失败，返回值为NULL
//@别名 A进程_打开()
HANDLE OpenProcess(
  DWORD dwDesiredAccess,
  BOOL  bInheritHandle,
  DWORD dwProcessId
);

//@备注 OpenProcessToken 函数打开与进程关联的访问令牌
//@参数 ProcessHandle 进程句柄
//@参数 DesiredAccess 访问权限
//@参数 TokenHandle 返回的令牌句柄
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A进程_打开令牌()
BOOL OpenProcessToken(
  HANDLE  ProcessHandle,
  DWORD   DesiredAccess,
  PHANDLE TokenHandle
);

//@备注 检索指定进程的优先级类。此值与进程的每个线程的优先级值一起确定每个线程的基本优先级
//@参数 hProcess 进程句柄
//@返回 进程的优先级类
//@别名 A进程_取优先级()
DWORD GetPriorityClass(
  HANDLE hProcess
);

//@备注 检索属于指定进程的打开句柄数
//@参数 hProcess 进程句柄
//@参数 pdwHandleCount 返回的句柄数量
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A进程_取句柄数量()
BOOL GetProcessHandleCount(
  HANDLE hProcess,
  PDWORD pdwHandleCount
);

//@备注 用于获取指定进程的进程ID
//@参数 Process 进程句柄
//@返回 进程ID
//@别名 A进程_取ID()
DWORD GetProcessId(
  HANDLE Process
);

//@备注 检索与指定线程关联的进程的进程标识符
//@参数 Thread 线程句柄
//@返回 线程所属进程的进程ID
//@别名 A进程_取指定线程进程ID()
DWORD GetProcessIdOfThread(
  HANDLE Thread
);
//@备注 检索有关指定进程的信息
//@参数 hProcess 进程句柄
//@参数 ProcessInformationClass 进程信息类别
//@参数 ProcessInformation 进程信息结构指针
//@参数 ProcessInformationSize 进程信息结构大小
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A进程_取信息()
BOOL GetProcessInformation(
  HANDLE                    hProcess,
  PROCESS_INFORMATION_CLASS ProcessInformationClass,
  LPVOID                    ProcessInformation,
  DWORD                     ProcessInformationSize
);

//@备注 检索当前调用进程的关机参数
//@参数 lpdwLevel 返回的关机级别
//@参数 lpdwFlags 返回的关机标志
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A进程_取关机参数()
BOOL GetProcessShutdownParameters(
  LPDWORD lpdwLevel,
  LPDWORD lpdwFlags
);

//@备注 检索指定进程的时间信息
//@参数 hProcess 进程句柄
//@参数 lpCreationTime 返回的进程创建时间
//@参数 lpExitTime 返回的进程退出时间
//@参数 lpKernelTime 返回的进程内核模式时间
//@参数 lpUserTime 返回的进程用户模式时间
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A进程_取时间信息()
BOOL GetProcessTimes(
  HANDLE     hProcess,
  LPFILETIME lpCreationTime,
  LPFILETIME lpExitTime,
  LPFILETIME lpKernelTime,
  LPFILETIME lpUserTime
);

//@备注 检索指定进程预期在其上运行的系统的主要和次要版本号
//@参数 ProcessId 进程ID
//@返回 进程预期运行的系统版本号
//@别名 A进程_取版本()
DWORD GetProcessVersion(
    DWORD ProcessId
);

//@备注 检索创建调用进程时指定的 STARTUPINFO 结构的内容
//@参数 lpStartupInfo 启动信息结构指针
//@别名 A进程_取启动信息()
void GetStartupInfo(
    LPSTARTUPINFOW lpStartupInfo  // 启动信息结构指针
);

//@备注 用于获取指定进程的退出码
//@参数 hProcess 进程句柄
//@参数 lpExitCode 返回的进程退出码
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 A进程_取退出码()
BOOL GetExitCodeProcess(
  HANDLE  hProcess,
  LPDWORD lpExitCode
);

//@备注 用于终止当前进程
//@参数 退出代码
//@返回 无
//@别名 A进程_退出()
void ExitProcess(
  UINT uExitCode
);
//@备注 用于获取当前进程的伪句柄
//@返回 当前进程的伪句柄
//@别名 A进程_取当前进程()
HANDLE GetCurrentProcess();

//@备注 用于获取当前进程的进程ID
//@返回 当前进程的进程ID
//@别名 A进程_取当前进程ID()
DWORD GetCurrentProcessId();

//@备注 检索一个伪句柄，您可以使用该句柄作为速记方式来引用与进程关联的访问令牌
//@返回 当前进程的访问令牌句柄
//@别名 A进程_取当前进程令牌()
HANDLE GetCurrentProcessToken();

//@分组}



//@分组{ 外壳程序

@备注 对指定文件执行操作
@  https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shellexecutew
@别名 执行文件()
HINSTANCE ShellExecute(__in_opt HWND hwnd, __in_opt LPCWSTR lpOperation,  __in LPCWSTR lpFile, __in_opt LPCWSTR lpParameters, __in_opt LPCWSTR lpDirectory, __in INT nShowCmd);


@备注  检索文件系统中有关对象的信息，例如文件、文件夹、目录或驱动器根目录。
@别名 取文件信息()
DWORD_PTR SHGetFileInfo(
  __in      LPCWSTR     pszPath,
			DWORD       dwFileAttributes,
  __in_out SHFILEINFOW *psfi,
			UINT        cbFileInfo,
			UINT        uFlags
);

//@备注 检索图像列表。
//@备注 用于获取系统图像列表的接口指针
//@ https://learn.microsoft.com/zh-cn/windows/win32/api/commoncontrols/nn-commoncontrols-iimagelist
//@参数 iImageList 图像列表类型
//@参数 riid 接口的唯一标识符 (IID)
//@参数 ppvObj 返回的图像列表接口指针
//@返回 如果成功，返回 S_OK；如果失败，返回错误代码
//@别名 取图像列表()
DWORD_PTR SHGetImageList( __in  int    iImageList, __in  REFIID riid, __out void   **ppvObj);

//指定要检索的文件信息的标志。 此参数可以是以下值的组合。
#define SHGFI_ICON              0x000000100     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_DISPLAYNAME       0x000000200     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_TYPENAME          0x000000400     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_ATTRIBUTES        0x000000800     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_ICONLOCATION      0x000001000     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_EXETYPE           0x000002000     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_SYSICONINDEX      0x000004000     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_LINKOVERLAY       0x000008000     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_SELECTED          0x000010000     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_ATTR_SPECIFIED    0x000020000     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_LARGEICON         0x000000000     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_SMALLICON         0x000000001     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_OPENICON          0x000000002     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_SHELLICONSIZE     0x000000004     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_PIDL              0x000000008     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_USEFILEATTRIBUTES 0x000000010     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa

#define SHGFI_ADDOVERLAYS       0x000000020     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa
#define SHGFI_OVERLAYINDEX      0x000000040     //@备注 参加MSDN: https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/nf-shellapi-shgetfileinfoa

@备注  32*32图标, 但是，如果“使用大图标”选项是从“显示属性”选项卡的“效果”部分选择的，则图像为 48x48 像素。
@别名  图标类型32
#define SHIL_LARGE          0   // normally 32x32

@备注  16*16图标, 但大小可由用户自定义。
@别名  图标类型16
#define SHIL_SMALL          1   // normally 16x16

@备注  48*48图标, 但大小可由用户自定义。
@别名  图标类型48
#define SHIL_EXTRALARGE     2

@备注  这些映像是由使用 SM_CXSMICON 调用的 GetSystemMetrics 指定的大小，使用 SM_CYSMICON 调用 GetSystemMetrics。
@别名  图标类型系统16
#define SHIL_SYSSMALL       3   // like SHIL_SMALL, but tracks system small icon metric correctly

@备注  256*256图标
@别名  图标类型256
#define SHIL_JUMBO          4   // normally 256x256

extern "C" const IID IID_IImageList;

//@别名  图像列表
struct IImageList : public IUnknown
{
	  //@备注 用于向图像列表中添加一个图像
	  //@参数 图像位图句柄
	  //@参数 掩码位图句柄（可选）
	  //@参数 输出图像的索引
	  //@返回 如果函数成功，返回值为 S_OK
	  //@别名 添加()
	  virtual HRESULT __stdcall  Add(
	__in  HBITMAP hbmImage,
	__in_opt  HBITMAP hbmMask,
	__out  int* pi) = 0;

	  //@备注 用于用图标替换图像列表中的指定图像
	  //@参数 替换位置的索引
	  //@参数 图标句柄
	  //@参数 输出新图像的索引
	  //@返回 如果函数成功，返回值为 S_OK
	  //@别名 替换图标()
	virtual HRESULT __stdcall ReplaceIcon(
		int i,
		__in  HICON hicon,
	    __out  int* pi) = 0;

      //@备注 用于设置覆盖图像
      //@参数 图像索引
      //@参数 覆盖图像索引
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 设置覆盖图像()
    virtual HRESULT __stdcall SetOverlayImage(
	    int iImage,
	    int iOverlay) = 0;

      //@备注 用于替换图像列表中的指定图像
      //@参数 替换位置的索引
      //@参数 图像位图句柄
      //@参数 掩码位图句柄（可选）
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 替换()
    virtual HRESULT __stdcall Replace(
	    int i,
	    __in  HBITMAP hbmImage,
	    __in_opt  HBITMAP hbmMask) = 0;

      //@备注 用于向图像列表中添加一个带有掩码的图像
      //@参数 图像位图句柄
      //@参数 掩码颜色
      //@参数 输出图像的索引
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 加掩码图像()
    virtual HRESULT __stdcall AddMasked(
	    __in  HBITMAP hbmImage,
	    COLORREF crMask,
	    __out  int* pi) = 0;

      //@备注 用于绘制图像列表中的图像
      //@参数 图像绘制参数结构体指针
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 绘制()
    virtual HRESULT __stdcall Draw(
	    __in  IMAGELISTDRAWPARAMS* pimldp) = 0;

      //@备注 用于移除图像列表中的指定图像
      //@参数 要移除的图像索引
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 移除()
    virtual HRESULT __stdcall Remove(
	    int i) = 0;

      //@备注 用于从图像列表中获取指定图像的图标
      //@参数 图像索引
      //@参数 图标标志
      //@参数 输出图标句柄
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 取图标()
    virtual HRESULT __stdcall GetIcon(
	    int i,
	    UINT flags,
	    __out  HICON* picon) = 0;

      //@备注 用于获取图像列表中指定图像的信息
      //@参数 图像索引
      //@参数 输出图像信息结构体指针
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 取图像信息()
    virtual HRESULT __stdcall GetImageInfo(
	    int i,
	    __out  IMAGEINFO* pImageInfo) = 0;

      //@备注 用于复制图像列表中的图像
      //@参数 目标图像索引
      //@参数 源图像列表接口指针
      //@参数 源图像索引
      //@参数 复制标志
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 复制()
    virtual HRESULT __stdcall Copy(
	    int iDst,
	    __in  IUnknown* punkSrc,
	    int iSrc,
	    UINT uFlags) = 0;

      //@备注 用于合并两个图像列表中的图像
      //@参数 目标图像索引
      //@参数 源图像列表接口指针
      //@参数 源图像索引
      //@参数 水平偏移
      //@参数 垂直偏移
      //@参数 接口标识符
      //@参数 输出合并后的图像列表接口指针
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 合并()
    virtual HRESULT __stdcall Merge(
	    int i1,
	    __in  IUnknown* punk2,
	    int i2,
	    int dx,
	    int dy,
	    REFIID riid,
	    __out  void** ppv) = 0;

      //@备注 用于克隆图像列表
      //@参数 接口标识符
      //@参数 输出克隆的图像列表接口指针
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 克隆()
    virtual HRESULT __stdcall Clone(
	    REFIID riid,
	    __out  void** ppv) = 0;

      //@备注 用于获取图像列表中指定图像的矩形区域
      //@参数 图像索引
      //@参数 输出图像矩形区域
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 取图像矩形()
    virtual HRESULT __stdcall GetImageRect(
	    int i,
	    __out  RECT* prc) = 0;

      //@备注 用于获取图像列表中图标的尺寸
      //@参数 输出图标的宽度
      //@参数 输出图标的高度
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 取图标尺寸()
    virtual HRESULT __stdcall GetIconSize(
	    __out  int* cx,
	    __out  int* cy) = 0;

      //@备注 用于设置图像列表中图标的尺寸
      //@参数 图标的宽度
      //@参数 图标的高度
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 设置图标尺寸()
    virtual HRESULT __stdcall SetIconSize(
	    int cx,
	    int cy) = 0;

      //@备注 用于获取图像列表中的图像数量
      //@参数 输出图像数量
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 取图像数量()
    virtual HRESULT __stdcall GetImageCount(
	    __out  int* pi) = 0;

      //@备注 用于设置图像列表中的图像数量
      //@参数 新的图像数量
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 设置图像数量()
    virtual HRESULT __stdcall SetImageCount(
	    UINT uNewCount) = 0;

      //@备注 用于设置图像列表的背景颜色
      //@参数 背景颜色
      //@参数 输出之前的背景颜色
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 设置背景颜色()
    virtual HRESULT __stdcall SetBkColor(
	    COLORREF clrBk,
	    __out  COLORREF* pclr) = 0;

      //@备注 用于获取图像列表的背景颜色
      //@参数 输出背景颜色
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 取背景颜色()
    virtual HRESULT __stdcall GetBkColor(
	    __out  COLORREF* pclr) = 0;

      //@备注 用于开始拖拽图像
      //@参数 拖拽图像的索引
      //@参数 热点的水平偏移
      //@参数 热点的垂直偏移
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 开始拖拽()
    virtual HRESULT __stdcall BeginDrag(
	    int iTrack,
	    int dxHotspot,
	    int dyHotspot) = 0;

      //@备注 用于结束拖拽图像
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 结束拖拽()
    virtual HRESULT __stdcall EndDrag(void) = 0;

      //@备注 用于进入拖拽状态
      //@参数 锁定窗口句柄（可选）
      //@参数 拖拽位置的X坐标
      //@参数 拖拽位置的Y坐标
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 进入拖拽()
    virtual HRESULT __stdcall DragEnter(
	    __in_opt  HWND hwndLock,
	    int x,
	    int y) = 0;

      //@备注 用于离开拖拽状态
      //@参数 锁定窗口句柄（可选）
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 离开拖拽()
    virtual HRESULT __stdcall DragLeave(
	    __in_opt  HWND hwndLock) = 0;

      //@备注 用于移动拖拽图像
      //@参数 拖拽位置的X坐标
      //@参数 拖拽位置的Y坐标
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 移动拖拽()
    virtual HRESULT __stdcall DragMove(
	    int x,
	    int y) = 0;

      //@备注 用于设置拖拽光标图像
      //@参数 拖拽图像列表接口指针
      //@参数 拖拽图像的索引
      //@参数 热点的水平偏移
      //@参数 热点的垂直偏移
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 设置拖拽光标图像()
    virtual HRESULT __stdcall SetDragCursorImage(
	    __in  IUnknown* punk,
	    int iDrag,
	    int dxHotspot,
	    int dyHotspot) = 0;

      //@备注 用于显示或隐藏拖拽图像
      //@参数 是否显示拖拽图像
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 显示拖拽图像()
    virtual HRESULT __stdcall DragShowNolock(
	    BOOL fShow) = 0;

      //@备注 用于获取拖拽图像
      //@参数 输出拖拽图像的位置
      //@参数 输出热点的位置
      //@参数 接口标识符
      //@参数 输出拖拽图像列表接口指针
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 取拖拽图像()
    virtual HRESULT __stdcall GetDragImage(
	    __out_opt  POINT* ppt,
	    __out_opt  POINT* pptHotspot,
	    REFIID riid,
	    __out  void** ppv) = 0;

      //@备注 用于获取图像列表中指定图像的标志
      //@参数 图像索引
      //@参数 输出图像标志
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 取图像标志()
      virtual HRESULT __stdcall GetItemFlags(
        int i,
        __out  DWORD* dwFlags) = 0;

      //@备注 用于获取覆盖图像的索引
      //@参数 覆盖图像索引
      //@参数 输出图像索引
      //@返回 如果函数成功，返回值为 S_OK
      //@别名 取覆盖图像()
    virtual HRESULT __stdcall GetOverlayImage(
	    int iOverlay,
	    __out  int* piIndex) = 0;   
};

//图片列表绘制标识
#define ILD_NORMAL              0x00000000  //@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_TRANSPARENT         0x00000001	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_MASK                0x00000010	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_IMAGE               0x00000020	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_ROP                 0x00000040	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_BLEND25             0x00000002	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_BLEND50             0x00000004	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_OVERLAYMASK         0x00000F00	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define INDEXTOOVERLAYMASK(i)   ((i) << 8)	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_PRESERVEALPHA       0x00001000  //@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_SCALE               0x00002000  //@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_DPISCALE            0x00004000	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_ASYNC               0x00008000	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
											
#define ILD_SELECTED            ILD_BLEND50	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_FOCUS               ILD_BLEND25	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILD_BLEND               ILD_BLEND50	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define CLR_HILIGHT             CLR_DEFAULT	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags

#define ILS_NORMAL              0x00000000	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILS_GLOW                0x00000001	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILS_SHADOW              0x00000002	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILS_SATURATE            0x00000004	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILS_ALPHA               0x00000008	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags

#define ILGT_NORMAL             0x00000000	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags
#define ILGT_ASYNC              0x00000001	//@备注  图片列表绘制标识, 参见: https://learn.microsoft.com/zh-cn/windows/win32/controls/imagelistdrawflags

//@分组}


//@分组{ GDI绘图

//@备注 用于获取窗口的设备上下文句柄
//@参数 窗口句柄
//@返回 返回窗口的设备上下文句柄
//@别名 AGDI_取窗口DC()
HDC GetDC(HWND hWnd);

//@备注 用于释放窗口的设备上下文句柄
//@参数 窗口句柄
//@参数 设备上下文句柄
//@返回 如果函数成功，返回值为1 如果函数失败，返回值为0
//@别名 AGDI_释放窗口DC()
int WINAPI ReleaseDC(HWND hWnd, HDC hDC);

//@备注 用于删除设备上下文
//@参数 设备上下文句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_删除DC()
BOOL DeleteDC(__in HDC hdc);

//@备注 用于执行透明混合操作
//@参数 目标设备上下文句柄
//@参数 目标矩形左上角X坐标
//@参数 目标矩形左上角Y坐标
//@参数 目标矩形宽度
//@参数 目标矩形高度
//@参数 源设备上下文句柄
//@参数 源矩形左上角X坐标
//@参数 源矩形左上角Y坐标
//@参数 源矩形宽度
//@参数 源矩形高度
//@参数 混合函数结构体
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_透明混合()
BOOL WINAPI AlphaBlend(
    __in HDC hdcDest,
    __in int xoriginDest,
    __in int yoriginDest,
    __in int wDest,
    __in int hDest,
    __in HDC hdcSrc,
    __in int xoriginSrc,
    __in int yoriginSrc,
    __in int wSrc,
    __in int hSrc,
    __in BLENDFUNCTION ftn);

//@备注 用于执行透明位图传输
//@参数 目标设备上下文句柄
//@参数 目标矩形左上角X坐标
//@参数 目标矩形左上角Y坐标
//@参数 目标矩形宽度
//@参数 目标矩形高度
//@参数 源设备上下文句柄
//@参数 源矩形左上角X坐标
//@参数 源矩形左上角Y坐标
//@参数 源矩形宽度
//@参数 源矩形高度
//@参数 透明颜色
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_透明位图传输()
BOOL WINAPI TransparentBlt(
    __in HDC hdcDest,
    __in int xoriginDest,
    __in int yoriginDest,
    __in int wDest,
    __in int hDest,
    __in HDC hdcSrc,
    __in int xoriginSrc,
    __in int yoriginSrc,
    __in int wSrc,
    __in int hSrc,
    __in UINT crTransparent);

//@备注 用于删除AGDI_对象
//@参数 AGDI_对象句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_删除对象()
BOOL DeleteObject(__in HGDIOBJ ho);

//@备注 用于创建一个画笔
//@参数 画笔样式
//@参数 画笔宽度
//@参数 画笔颜色
//@返回 返回创建的画笔句柄
//@别名 AGDI_创建画笔()
HPEN CreatePen(
  __in int      iStyle,
  __in int      cWidth,
  __in COLORREF color
);

//@备注 用于创建一个阴影画刷
//@参数 阴影样式
//@参数 阴影颜色
//@返回 返回创建的阴影画刷句柄
//@别名 AGDI_创建阴影画刷()
HBRUSH  WINAPI CreateHatchBrush( __in int iHatch, __in COLORREF color);

//@备注 用于创建一个与指定设备上下文兼容的内存设备上下文
//@参数 设备上下文句柄
//@返回 返回创建的兼容设备上下文句柄
//@别名 AGDI_创建兼容DC()
HDC CreateCompatibleDC( __in HDC hdc);

//@备注 用于创建一个字体
//@参数 字体高度
//@参数 字体宽度
//@参数 字体倾斜角度
//@参数 字体方向
//@参数 字体粗细
//@参数 是否斜体
//@参数 是否下划线
//@参数 是否删除线
//@参数 字符集
//@参数 输出精度
//@参数 裁剪精度
//@参数 输出质量
//@参数 字体间距和族
//@参数 字体名称
//@返回 返回创建的字体句柄
//@别名 AGDI_创建字体()
HFONT CreateFont(int cHeight, int cWidth, int cEscapement,int cOrientation,int cWeight,DWORD bItalic,DWORD bUnderline,DWORD bStrikeOut,DWORD iCharSet,DWORD   iOutPrecision,DWORD iClipPrecision,DWORD iQuality,DWORD iPitchAndFamily,LPCWSTR pszFaceName);

//@备注 用于执行位图复制
//@参数 目标设备上下文句柄
//@参数 目标矩形左上角X坐标
//@参数 目标矩形左上角Y坐标
//@参数 目标矩形宽度
//@参数 目标矩形高度
//@参数 源设备上下文句柄
//@参数 源矩形左上角X坐标
//@参数 源矩形左上角Y坐标
//@参数 光栅操作码
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_位图复制()
BOOL  WINAPI BitBlt( __in HDC hdc, __in int x, __in int y, __in int cx, __in int cy, __in HDC hdcSrc, __in int x1, __in int y1, __in DWORD rop);

//@备注 用于设置指定像素点的颜色
//@参数 设备上下文句柄
//@参数 像素点的X坐标
//@参数 像素点的Y坐标
//@参数 像素点的颜色
//@返回 返回实际设置的颜色值
//@别名 AGDI_设置像素点()
COLORREF WINAPI SetPixel(__in HDC hdc, __in int x, __in int y, __in COLORREF color);

//@备注 用于设置指定像素点的颜色（更快但不返回实际颜色）
//@参数 设备上下文句柄
//@参数 像素点的X坐标
//@参数 像素点的Y坐标
//@参数 像素点的颜色
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_设置像素点V()
BOOL  WINAPI SetPixelV(__in HDC hdc, __in int x, __in int y, __in COLORREF color);

//@备注 用于设置设备上下文的像素格式
//@参数 设备上下文句柄
//@参数 像素格式
//@参数 像素格式描述符
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_设置像素格式()
BOOL  WINAPI SetPixelFormat(__in HDC hdc, __in int format, __in const PIXELFORMATDESCRIPTOR * ppfd);

//@备注 用于设置多边形的填充模式
//@参数 设备上下文句柄
//@参数 多边形填充模式
//@返回 返回之前的填充模式
//@别名 AGDI_设置多边形填充模式()
int   WINAPI SetPolyFillMode(__in HDC hdc, __in int mode);

//@备注 用于执行拉伸位图复制
//@参数 目标设备上下文句柄
//@参数 目标矩形左上角X坐标
//@参数 目标矩形左上角Y坐标
//@参数 目标矩形宽度
//@参数 目标矩形高度
//@参数 源设备上下文句柄
//@参数 源矩形左上角X坐标
//@参数 源矩形左上角Y坐标
//@参数 源矩形宽度
//@参数 源矩形高度
//@参数 光栅操作码
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_位图复制拉伸()
BOOL  WINAPI StretchBlt(__in HDC hdcDest, __in int xDest, __in int yDest, __in int wDest, __in int hDest, __in HDC hdcSrc, __in int xSrc, __in int ySrc, __in int wSrc, __in int hSrc, __in DWORD rop);

//@备注 用于绘制一条从当前位置到指定点的线条
//@参数 设备上下文句柄
//@参数 线条终点的X坐标
//@参数 线条终点的Y坐标
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_画线到()
BOOL WINAPI LineTo( __in HDC hdc, __in int x, __in int y);

//@备注 用于将AGDI_对象选入设备上下文
//@参数 设备上下文句柄
//@参数 AGDI_对象句柄
//@返回 返回之前选中的AGDI_对象句柄
//@别名 AGDI_选择对象()
HGDIOBJ SelectObject(HDC hdc,HGDIOBJ h);

//@备注 用于获取指定像素点的颜色
//@参数 设备上下文句柄
//@参数 像素点的X坐标
//@参数 像素点的Y坐标
//@返回 返回指定像素点的颜色值
//@别名 AGDI_取像素点()
COLORREF WINAPI GetPixel( __in HDC hdc, __in int x, __in int y);

//@备注 用于创建一个实心画刷
//@参数 画刷颜色
//@返回 返回创建的实心画刷句柄
//@别名 AGDI_创建实心画刷()
HBRUSH CreateSolidBrush(COLORREF color);

//@备注 用于绘制一个椭圆
//@参数 设备上下文句柄
//@参数 椭圆外接矩形左上角X坐标
//@参数 椭圆外接矩形左上角Y坐标
//@参数 椭圆外接矩形右下角X坐标
//@参数 椭圆外接矩形右下角Y坐标
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_画椭圆()
BOOL WINAPI Ellipse( __in HDC hdc, __in int left, __in int top,  __in int right, __in int bottom);

//@备注 用于在指定位置输出文本
//@参数 设备上下文句柄
//@参数 文本起始X坐标
//@参数 文本起始Y坐标
//@参数 文本字符串
//@参数 文本长度
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_输出文本()
BOOL TextOut(HDC hdc,int x,int y,LPCWSTR lpString,int c);

//@备注 用于移动当前位置到指定点
//@参数 设备上下文句柄
//@参数 新位置的X坐标
//@参数 新位置的Y坐标
//@参数 旧位置指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_移动到()
BOOL  WINAPI MoveToEx( __in HDC hdc, __in int x, __in int y, __out LPPOINT lppt);

//@备注 用于在指定矩形区域内绘制文本
//@参数 设备上下文句柄
//@参数 文本字符串
//@参数 文本长度
//@参数 矩形区域指针
//@参数 文本格式
//@返回 返回文本的高度
//@别名 AGDI_绘制文本()
int DrawText(HDC hdc,LPCTSTR lpchText,int cchText,LPRECT lprc,UINT format);

//@备注 用于创建一个位图
//@参数 位图宽度
//@参数 位图高度
//@参数 颜色平面数
//@参数 每像素位数
//@参数 位图数据指针
//@返回 返回创建的位图句柄
//@别名 AGDI_创建位图()
HBITMAP WINAPI CreateBitmap( __in int nWidth, __in int nHeight, __in UINT nPlanes, __in UINT nBitCount, __in const VOID *lpBits);

//@备注 用于开始绘制窗口
//@参数 窗口句柄
//@参数 绘图结构体指针
//@返回 返回设备上下文句柄
//@别名 AGDI_开始绘制()
HDC BeginPaint(HWND hWnd,LPPAINTSTRUCT lpPaint);

//@备注 用于设置文本颜色
//@参数 设备上下文句柄
//@参数 文本颜色
//@返回 返回之前的文本颜色
//@别名 AGDI_设置文本颜色()
COLORREF WINAPI SetTextColor(__in HDC hdc, __in COLORREF color);

//@备注 用于设置文本对齐方式
//@参数 设备上下文句柄
//@参数 文本对齐方式
//@返回 返回之前的文本对齐方式
//@别名 AGDI_设置文本对齐()
UINT  WINAPI SetTextAlign(__in HDC hdc, __in UINT align);

//@备注 用于获取文本对齐方式
//@参数 设备上下文句柄
//@返回 返回当前的文本对齐方式
//@别名 AGDI_取文本对齐()
UINT WINAPI GetTextAlign(__in HDC hdc);

//@备注 用于获取文本颜色
//@参数 设备上下文句柄
//@返回 返回当前的文本颜色
//@别名 AGDI_取文本颜色()
COLORREF WINAPI GetTextColor(__in HDC hdc);

//@备注 用于结束绘制窗口
//@参数 窗口句柄
//@参数 绘图结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_结束绘制()
BOOL EndPaint(HWND hWnd,const PAINTSTRUCT *lpPaint);

//@备注 用于设置背景颜色
//@参数 设备上下文句柄
//@参数 背景颜色
//@返回 返回之前的背景颜色
//@别名 AGDI_设置背景颜色()
COLORREF WINAPI SetBkColor(__in HDC hdc, __in COLORREF color);

//@备注 用于绘制一个圆角矩形
//@参数 设备上下文句柄
//@参数 圆角矩形左上角X坐标
//@参数 圆角矩形左上角Y坐标
//@参数 圆角矩形右下角X坐标
//@参数 圆角矩形右下角Y坐标
//@参数 圆角宽度
//@参数 圆角高度
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_画圆角矩形()
BOOL  WINAPI RoundRect(__in HDC hdc, __in int left, __in int top, __in int right, __in int bottom, __in int width, __in int height);

//@备注 用于绘制矩形边框
//@参数 设备上下文句柄
//@参数 矩形区域指针
//@参数 画刷句柄
//@返回 返回填充的矩形数量
//@别名 AGDI_画矩形边框()
int FrameRect(HDC hDC,const RECT *lprc,HBRUSH hbr);

//@备注 用于绘制一个矩形
//@参数 设备上下文句柄
//@参数 矩形左上角X坐标
//@参数 矩形左上角Y坐标
//@参数 矩形右下角X坐标
//@参数 矩形右下角Y坐标
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_画矩形()
BOOL WINAPI Rectangle(__in HDC hdc, __in int left, __in int top, __in int right, __in int bottom);

//@备注 用于填充当前路径
//@参数 设备上下文句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_填充路径()
BOOL WINAPI FillPath(__in HDC hdc);

//@备注 用于填充指定矩形区域
//@参数 设备上下文句柄
//@参数 矩形区域指针
//@参数 画刷句柄
//@返回 返回填充的矩形数量
//@别名 AGDI_填充矩形()
int FillRect(__in HDC hDC, __in const RECT *lprc, __in HBRUSH hbr);

//@备注 用于获取背景颜色
//@参数 设备上下文句柄
//@返回 返回当前的背景颜色
//@别名 AGDI_取背景颜色()
COLORREF WINAPI GetBkColor( __in HDC hdc);

//@备注 用于填充指定区域
//@参数 设备上下文句柄
//@参数 区域句柄
//@参数 画刷句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_填充区域()
BOOL WINAPI FillRgn( __in HDC hdc, __in HRGN hrgn, __in HBRUSH hbr);

//@备注 用于获取背景模式
//@参数 设备上下文句柄
//@返回 返回当前的背景模式
//@别名 AGDI_取背景模式()
int WINAPI GetBkMode(__in HDC hdc);

//@备注 用于设置背景模式
//@参数 设备上下文句柄
//@参数 背景模式
//@返回 返回之前的背景模式
//@别名 AGDI_设置背景模式()
int   WINAPI SetBkMode(__in HDC hdc, __in int mode);

//@备注 用于绘制一个多边形
//@参数 设备上下文句柄
//@参数 点数组指针
//@参数 点的数量
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_画多边形()
BOOL  WINAPI Polygon(__in HDC hdc, __in const POINT *apt, __in int cpt);

//@备注 用于绘制多条连接线
//@参数 设备上下文句柄
//@参数 点数组指针
//@参数 点的数量
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_画多线()
BOOL  WINAPI Polyline(__in HDC hdc, __in const POINT *apt, __in int cpt);

//@备注 用于绘制一个饼图
//@参数 设备上下文句柄
//@参数 椭圆外接矩形左上角X坐标
//@参数 椭圆外接矩形左上角Y坐标
//@参数 椭圆外接矩形右下角X坐标
//@参数 椭圆外接矩形右下角Y坐标
//@参数 起始点的X坐标
//@参数 起始点的Y坐标
//@参数 结束点的X坐标
//@参数 结束点的Y坐标
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_画饼图()
BOOL WINAPI Pie(__in HDC hdc, __in int left, __in int top, __in int right, __in int bottom, __in int xr1, __in int yr1, __in int xr2, __in int yr2);

//@备注 用于绘制多条贝塞尔曲线
//@参数 设备上下文句柄
//@参数 点数组指针
//@参数 点的数量
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_画贝塞尔曲线()
BOOL  WINAPI PolyBezier(__in HDC hdc, __in const POINT * apt, __in DWORD cpt);

//@备注 用于绘制多条贝塞尔曲线（从当前位置开始）
//@参数 设备上下文句柄
//@参数 点数组指针
//@参数 点的数量
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_画贝塞尔曲线到()
BOOL  WINAPI PolyBezierTo(__in HDC hdc, __in const POINT * apt, __in DWORD cpt);

//@备注 用于绘制多条连接线（从当前位置开始）
//@参数 设备上下文句柄
//@参数 点数组指针
//@参数 点的数量
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_画多线到()
BOOL  WINAPI PolylineTo(__in HDC hdc, __in const POINT * apt, __in DWORD cpt);

//@备注 用于创建一个图案画刷
//@参数 位图句柄
//@返回 返回创建的图案画刷句柄
//@别名 AGDI_创建图案画刷()
HBRUSH  WINAPI CreatePatternBrush( __in HBITMAP hbm);

//@备注 用于绘制一条弧线
//@参数 设备上下文句柄
//@参数 弧线外接矩形左上角X坐标
//@参数 弧线外接矩形左上角Y坐标
//@参数 弧线外接矩形右下角X坐标
//@参数 弧线外接矩形右下角Y坐标
//@参数 起始点的X坐标
//@参数 起始点的Y坐标
//@参数 结束点的X坐标
//@参数 结束点的Y坐标
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_画弧线()
BOOL  WINAPI Arc( __in HDC hdc, __in int x1, __in int y1, __in int x2, __in int y2, __in int x3, __in int y3, __in int x4, __in int y4);

//@备注 用于创建一个与指定设备上下文兼容的位图
//@参数 设备上下文句柄
//@参数 位图宽度
//@参数 位图高度
//@返回 返回创建的兼容位图句柄
//@别名 AGDI_创建兼容位图()
HBITMAP WINAPI CreateCompatibleBitmap( __in HDC hdc, __in int cx, __in int cy);

//@备注 用于创建一个可丢弃的位图
//@参数 设备上下文句柄
//@参数 位图宽度
//@参数 位图高度
//@返回 返回创建的可丢弃位图句柄
//@别名 AGDI_创建可丢弃位图()
HBITMAP WINAPI CreateDiscardableBitmap( __in HDC hdc, __in int cx, __in int cy);

//@备注 用于设置字符间距
//@参数 设备上下文句柄
//@参数 字符间距
//@返回 返回之前的字符间距
//@别名 AGDI_设置字符间距()
int   WINAPI SetTextCharacterExtra(__in HDC hdc, __in int extra);

//@备注 用于根据字体结构体创建一个字体
//@参数 字体结构体指针
//@返回 返回创建的字体句柄
//@别名 AGDI_创建字体间接()
HFONT   WINAPI CreateFontIndirect( __in const LOGFONTW *lplf);

//@备注 用于在指定位置绘制一个图标
//@参数 设备上下文句柄
//@参数 绘制位置的X坐标
//@参数 绘制位置的Y坐标
//@参数 图标句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_绘制图标()
BOOL DrawIcon(HDC hDC, int X, int Y, HICON hIcon);

//@备注 用于在指定位置绘制一个图标，支持更多选项
//@参数 设备上下文句柄
//@参数 绘制位置的X坐标
//@参数 绘制位置的Y坐标
//@参数 图标句柄
//@参数 图标的宽度
//@参数 图标的高度
//@参数 动画光标步进
//@参数 闪烁消除画刷句柄
//@参数 绘制标志
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 AGDI_绘制图标扩展()
BOOL DrawIconEx(
    HDC hdc,
    int xLeft,
    int yTop,
    HICON hIcon,
    int cxWidth,
    int cyWidth,
    UINT istepIfAniCur,
    HBRUSH hbrFlickerFreeDraw,
    UINT diFlags
);
//@分组}


//@分组{ 菜单

//@备注 用于从资源文件中加载菜单
//@参数 模块句柄
//@参数 菜单名称
//@返回 返回加载的菜单句柄
//@别名 A菜单_加载(模块句柄,菜单名称)
HMENU WINAPI LoadMenu(HINSTANCE hlnstance, LPCTSTR lpMenuName);

//@备注 用于在菜单末尾添加新菜单项
//@参数 菜单句柄
//@参数 菜单项标志
//@参数 新菜单项ID
//@参数 新菜单项文本
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_添加项()
BOOL WINAPI AppendMenu(HMENU hMenu,UINT uFlags,UINT_PTR uIDNewItem,LPCWSTR lpNewItem);

//@备注 用于创建一个空的弹出菜单
//@参数 无
//@返回 返回新创建的弹出菜单句柄
//@别名 A菜单_创建弹出菜单()
HMENU WINAPI CreatePopupMenu();

//@备注 用于创建一个空的菜单
//@参数 无
//@返回 返回新创建的菜单句柄
//@别名 A菜单_创建()
HMENU WINAPI CreateMenu();

//@备注 用于获取菜单中指定位置的子菜单句柄
//@参数 菜单句柄
//@参数 子菜单位置
//@返回 返回指定位置的子菜单句柄
//@别名 A菜单_取子菜单()
HMENU WINAPI GetSubMenu(HMENU hMenu,int nPos);

//@备注 用于获取菜单项的详细信息
//@参数 菜单句柄
//@参数 菜单项ID或位置
//@参数 是否按位置获取
//@参数 菜单项信息结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_取项信息()
BOOL WINAPI GetMenuItemInfo(HMENU hmenu, UINT item,BOOL fByPosition,LPMENUITEMINFOW lpmii);

//@备注 用于设置菜单项的详细信息
//@参数 菜单句柄
//@参数 菜单项ID或位置
//@参数 是否按位置设置
//@参数 菜单项信息结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_置项信息()
BOOL WINAPI SetMenuItemInfo(HMENU hmenu, UINT item, BOOL fByPositon,LPCMENUITEMINFOW lpmii);

//@备注 用于选中或取消选中菜单项
//@参数 菜单句柄
//@参数 菜单项ID
//@参数 选中标志
//@返回 返回菜单项之前的状态
//@别名 A菜单_选中项()
DWORD WINAPI CheckMenuItem(HMENU hMenu,UINT uIDCheckItem,UINT uCheck);

//@备注 用于启用或禁用菜单项
//@参数 菜单句柄
//@参数 菜单项ID
//@参数 启用标志
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_禁止项()
BOOL WINAPI EnableMenuItem(HMENU hMenu,UINT uIDEnableItem,UINT uEnable);

//@备注 用于删除菜单中的指定菜单项
//@参数 菜单句柄
//@参数 菜单项位置
//@参数 菜单标志
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_删除项()
BOOL WINAPI DeleteMenu(HMENU hMenu,UINT uPosition,UINT uFlags);

//@备注 用于结束当前活动的菜单
//@参数 无
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_关闭()
BOOL WINAPI EndMenu();

//@备注 用于高亮或取消高亮菜单项
//@参数 窗口句柄
//@参数 菜单句柄
//@参数 要高亮的菜单项ID
//@参数 高亮标志
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_项高亮()
BOOL WINAPI HiliteMenuItem(
    __in HWND hWnd,
    __in HMENU hMenu,
    __in UINT uIDHiliteItem,
    __in UINT uHilite);

//@备注 用于修改菜单项
//@参数 菜单句柄
//@参数 菜单命令
//@参数 新菜单项文本
//@参数 插入位置
//@参数 菜单标志
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_修改()
BOOL WINAPI ChangeMenu(
    __in HMENU hMenu,
    __in UINT cmd,
    __in_opt LPCWSTR lpszNewItem,
    __in UINT cmdInsert,
    __in UINT flags);

//@备注 用于获取菜单项的文本
//@参数 菜单句柄
//@参数 菜单项ID
//@参数 输出字符串缓冲区
//@参数 缓冲区大小
//@参数 菜单标志
//@返回 返回实际拷贝到缓冲区的字符数
//@别名 A菜单_取项文本()
int WINAPI GetMenuString(
    __in HMENU hMenu,
    __in UINT uIDItem,
    __out LPWSTR lpString,
    __in int cchMax,
    __in UINT flags);

//@备注 用于获取菜单项的状态（如选中、禁用等）
//@参数 菜单句柄
//@参数 菜单项ID
//@参数 菜单标志
//@返回 返回菜单项的状态
//@别名 A菜单_取项状态()
UINT WINAPI GetMenuState(
    __in HMENU hMenu,
    __in UINT uId,
    __in UINT uFlags);

//@备注 用于获取窗口的菜单句柄
//@参数 窗口句柄
//@返回 返回窗口的菜单句柄
//@别名 A菜单_取句柄()
HMENU WINAPI GetMenu(
    __in HWND hWnd);
//@备注 用于重绘窗口的菜单栏
//@参数 窗口句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_重绘菜单条()
BOOL WINAPI DrawMenuBar(__in HWND hWnd);

//@备注 用于销毁指定的菜单
//@参数 菜单句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_销毁()
BOOL WINAPI DestroyMenu( __in HMENU hMenu);

//@备注 用于获取窗口的系统菜单句柄
//@参数 窗口句柄
//@参数 是否恢复系统菜单
//@返回 返回系统菜单的句柄
//@别名 A菜单_取系统菜单句柄()
HMENU WINAPI GetSystemMenu(
    __in HWND hWnd,
    __in BOOL bRevert);

//@备注 用于获取指定位置的菜单项ID
//@参数 菜单句柄
//@参数 菜单项位置
//@返回 返回菜单项的ID
//@别名 A菜单_取项ID()
UINT WINAPI GetMenuItemID(
    __in HMENU hMenu,
    __in int nPos);

//@备注 用于获取菜单项的个数
//@参数 菜单句柄
//@返回 返回菜单项的个数
//@别名 A菜单_取项数量()
int WINAPI GetMenuItemCount(
    __in HMENU hMenu);

//@备注 用于在菜单中插入新菜单项
//@参数 菜单句柄
//@参数 插入位置
//@参数 菜单标志
//@参数 新菜单项ID
//@参数 新菜单项文本
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_插入项()
BOOL WINAPI InsertMenu(
    __in HMENU hMenu,
    __in UINT uPosition,
    __in UINT uFlags,
    __in UINT_PTR uIDNewItem,
    __in LPCWSTR lpNewItem);	

//@备注 用于设置窗口的菜单
//@参数 窗口句柄
//@参数 菜单句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_置窗口菜单()
BOOL SetMenu(HWND hWnd, HMENU hMenu);

//@备注 用于移除菜单中的指定菜单项
//@参数 菜单句柄
//@参数 菜单项位置
//@参数 菜单标志
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_移除项()
BOOL WINAPI RemoveMenu(
    __in HMENU hMenu,
    __in UINT uPosition,
    __in UINT uFlags);

//@备注 用于设置菜单项的选中和未选中位图
//@参数 菜单句柄
//@参数 菜单项位置
//@参数 菜单标志
//@参数 未选中时的位图句柄
//@参数 选中时的位图句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_置项位图()
BOOL WINAPI SetMenuItemBitmaps(
    __in HMENU hMenu,
    __in UINT uPosition,
    __in UINT uFlags,
    __in_opt HBITMAP hBitmapUnchecked,
    __in_opt HBITMAP hBitmapChecked);

//@备注 用于获取菜单选中标记的尺寸
//@参数 无
//@返回 返回菜单选中标记的尺寸
//@别名 A菜单_取选中标记尺寸()
LONG WINAPI GetMenuCheckMarkDimensions(VOID);

//@备注 用于在指定位置显示弹出菜单
//@参数 菜单句柄
//@参数 弹出菜单标志
//@参数 弹出菜单的X坐标
//@参数 弹出菜单的Y坐标
//@参数 保留参数
//@参数 窗口句柄
//@参数 弹出菜单的约束矩形
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_弹出()
BOOL WINAPI TrackPopupMenu(
    __in HMENU hMenu,
    __in UINT uFlags,
    __in int x,
    __in int y,
    __in int nReserved,
    __in HWND hWnd,
    __in const RECT *prcRect);

//@备注 用于获取菜单的信息
//@参数 菜单句柄
//@参数 菜单信息结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_取信息()
BOOL WINAPI GetMenuInfo(
    __in HMENU unnamedParam1,
    __out LPMENUINFO unnamedParam2);

//@备注 用于设置菜单的信息
//@参数 菜单句柄
//@参数 菜单信息结构体指针
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A菜单_置信息()
BOOL WINAPI SetMenuInfo(
    __in HMENU,
    __in LPCMENUINFO);

//@分组}

//@分组{   结构体

//@别名 绘图_结构体
struct PAINTSTRUCT {
  HDC  hdc;           // 设备上下文句柄
  BOOL fErase;        // 是否擦除背景
  RECT rcPaint;       // 需要绘制的矩形区域
  BOOL fRestore;      // 保留字段
  BOOL fIncUpdate;    // 保留字段
  BYTE rgbReserved[32]; // 保留字段
};

//@别名 混合_结构体
struct BLENDFUNCTION
{
    BYTE   BlendOp;             // 混合操作
    BYTE   BlendFlags;          // 混合标志
    BYTE   SourceConstantAlpha; // 源透明度
    BYTE   AlphaFormat;         // 透明度格式
};

//@别名 字体_结构体
struct LOGFONTW
{
    LONG      lfHeight;         // 字体高度
    LONG      lfWidth;          // 字体宽度
    LONG      lfEscapement;     // 字体倾斜角度
    LONG      lfOrientation;    // 字体方向
    LONG      lfWeight;         // 字体粗细
    BYTE      lfItalic;         // 是否斜体
    BYTE      lfUnderline;      // 是否下划线
    BYTE      lfStrikeOut;      // 是否删除线
    BYTE      lfCharSet;        // 字符集
    BYTE      lfOutPrecision;   // 输出精度
    BYTE      lfClipPrecision;  // 裁剪精度
    BYTE      lfQuality;        // 输出质量
    BYTE      lfPitchAndFamily; // 字体间距和族
    WCHAR     lfFaceName[LF_FACESIZE]; // 字体名称
};

@别名 文件信息_结构
struct SHFILEINFO
{
    HICON       hIcon;                    //@备注  out: 图标
    int         iIcon;                    //@备注  out: 图标索引
    DWORD       dwAttributes;             //@备注  out: 属性标识  SFGAO_ flags
    WCHAR       szDisplayName[MAX_PATH];  //@备注  out: 显示名称或路径  display name (or path)
    WCHAR       szTypeName[80];           //@备注  out: 类型名
};

//@备注 用于定义临界区对象的结构体
//@别名 临界区结构
struct CRITICAL_SECTION {};

//@别名 菜单_项目结构
struct MENUITEMINFOW
{
    UINT     cbSize;         //@备注 结构体大小
    UINT     fMask;          //@备注 标志位，指定哪些字段有效
    UINT     fType;          //@备注 菜单项类型（如MFT_STRING）
    UINT     fState;         //@备注 菜单项状态（如MFS_CHECKED）
    UINT     wID;            //@备注 菜单项ID
    HMENU    hSubMenu;       //@备注 子菜单句柄
    HBITMAP  hbmpChecked;    //@备注 选中时的位图句柄
    HBITMAP  hbmpUnchecked;  //@备注 未选中时的位图句柄
    ULONG_PTR dwItemData;    //@备注 菜单项数据
    LPWSTR   dwTypeData;     //@备注 菜单项文本
    UINT     cch;            //@备注 菜单项文本长度
    HBITMAP  hbmpItem;       //@备注 菜单项位图
};

struct MSG{
  HWND   hwnd;
  UINT   message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD  time;
  POINT  pt;
  DWORD  lPrivate;
};

//@备注 WH_MOUSE_结构
struct MOUSEHOOKSTRUCT {
    POINT     pt;           //@备注 鼠标事件的屏幕坐标
    HWND      hwnd;         //@备注 接收鼠标事件的窗口句柄
    UINT      wHitTestCode; //@备注 命中测试代码
    ULONG_PTR dwExtraInfo;  //@备注 额外信息
};

//@备注 WH_MOUSE_LL_结构
struct MSLLHOOKSTRUCT {
    POINT     pt;           //@备注 鼠标事件的屏幕坐标
    DWORD     mouseData;    //@备注 鼠标事件的附加数据
    DWORD     flags;        //@备注 事件标志
    DWORD     time;         //@备注 事件时间戳
    ULONG_PTR dwExtraInfo;  //@备注 额外信息
};

//@备注 WH_KEYBOARD_LL_结构
struct KBDLLHOOKSTRUCT {
    DWORD   vkCode;         //@备注 虚拟键码
    DWORD   scanCode;       //@备注 扫描码
    DWORD   flags;          //@备注 事件标志
    DWORD   time;           //@备注 事件时间戳
    ULONG_PTR dwExtraInfo;  //@备注 额外信息
};

struct OPENFILENAMEW {
    DWORD        lStructSize;
    HWND         hwndOwner;
    HINSTANCE    hInstance;
    LPCWSTR      lpstrFilter;
    LPWSTR       lpstrCustomFilter;
    DWORD        nMaxCustFilter;
    DWORD        nFilterIndex;
    LPWSTR       lpstrFile;
    DWORD        nMaxFile;
    LPWSTR       lpstrFileTitle;
    DWORD        nMaxFileTitle;
    LPCWSTR      lpstrInitialDir;
    LPCWSTR      lpstrTitle;
    DWORD        Flags;
    WORD         nFileOffset;
    WORD         nFileExtension;
    LPCWSTR      lpstrDefExt;
    LPARAM       lCustData;
    LPOFNHOOKPROC lpfnHook;
    LPCWSTR      lpTemplateName;
    void* pvReserved;
    DWORD        dwReserved;
    DWORD        FlagsEx;
};
struct WNDCLASSEX {
    UINT      cbSize;
    UINT      style;
    WNDPROC   lpfnWndProc;
    int       cbClsExtra;
    int       cbWndExtra;
    HINSTANCE hInstance;
    HICON     hIcon;
    HCURSOR   hCursor;
    HBRUSH    hbrBackground;
    LPCSTR    lpszMenuName;
    LPCSTR    lpszClassName;
    HICON     hIconSm;
};

struct DLGTEMPLATE {
    DWORD style;
    DWORD dwExtendedStyle;
    WORD cdit;
    short x;
    short y;
    short cx;
    short cy;
};
typedef DLGTEMPLATE* LPDLGTEMPLATEA;
typedef DLGTEMPLATE* LPDLGTEMPLATEW;
//@分组}   //结构体
*/


//@分组{   其他

//@备注  从指定URL地址读取内容并将读取到的内容保存到特定的文件里的实现方法。
//@参数  远程文件的URL, 例如: "http://www.example.com/file.txt"
//@参数  要保存到的本地文件路径,  例如: "C:\\Downloads\\file.txt"
//@返回  成功返回真, 失败返回假
//@别名  下载文件(远程文件的URL, 保存到的本地文件路径)
static BOOL xcl_URLDownloadToFile(const wchar_t* pFileURL, const wchar_t* pSaveFileName)
{
	HRESULT hr = URLDownloadToFile(NULL, pFileURL, pSaveFileName, 0, NULL);
	if (hr == S_OK)
	{
		return TRUE;
	}
	return FALSE;
}

/*@声明

//@备注 用于关闭一个内核对象句柄, https://learn.microsoft.com/zh-cn/windows/win32/api/handleapi/nf-handleapi-closehandle
//@参数 句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 关闭句柄()
BOOL CloseHandle(HANDLE hObject);

//@备注 用于创建加速键表
//@参数 加速键结构指针
//@参数 加速键数量
//@返回 如果函数成功，返回值为加速键表句柄 如果函数失败，返回值为NULL
//@别名 A加速键表_创建()
HACCEL WINAPI CreateAcceleratorTable(
    LPACCEL paccel,
    int cAccel
);

//@备注 用于加载指定的加速键表
//@参数 模块句柄
//@参数 加速键表名称
//@返回 如果函数成功，返回值为加速键表句柄 如果函数失败，返回值为NULL
//@别名 A加速键表_加载()
HACCEL WINAPI LoadAccelerators(
    HINSTANCE hInstance,
    LPCWSTR lpTableName
);

//@备注 用于销毁指定的加速键表
//@参数 加速键表句柄
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 A加速键表_销毁()
BOOL WINAPI DestroyAcceleratorTable(
    HACCEL hAccel
);

//@备注 用于将加速键消息转换为菜单命令
//@参数 窗口句柄
//@参数 加速键表句柄
//@参数 消息结构指针
//@返回 如果消息被转换，返回值为非零值 如果消息未被转换，返回值为零
//@别名 A加速键表_转换()
int WINAPI TranslateAccelerator(
    HWND hWnd,
    HACCEL hAccTable,
    LPMSG lpMsg
);

@备注 它允许程序注册一个热键组合，这样当用户按下该热键组合时，操作系统可以通知注册了该热键的窗口或者线程。
@参数 将接收热键生成的 WM_HOTKEY 消息的窗口句柄。 如果此参数 NULL，WM_HOTKEY 消息将发布到调用线程的消息队列，并且必须在消息循环中进行处理。
@参数 热键的标识符。 如果 hWnd 参数为 NULL，则热键与当前线程（而不是特定窗口）相关联。 如果热键已存在具有相同的 hWnd 和 id 参数，请参阅“备注”以获取所执行的操作。
@参数 必须与 vk 参数指定的键结合使用才能生成 WM_HOTKEY 消息， fsModifiers 参数可以是以下值的组合。
//MOD_ALT 0x0001	必须按住任一 ALT 键。
//MOD_CONTROL 0x0002	必须按住 Ctrl 键。
//MOD_NOREPEAT  0x4000 更改热键行为，使键盘自动重复不会生成多个热键通知。Windows Vista：不支持 此标志。
//MOD_SHIFT  0x0004	必须按住 Shift 键。
//MOD_WIN  0x0008	必须按住任一 WINDOWS 密钥。 这些键标有 Windows 徽标。 涉及 WINDOWS 键的键盘快捷方式保留供操作系统使用。
@参数 热键的虚拟键代码
@返回 如果函数成功，则返回值为非零。如果函数失败，则返回值为零。 若要获取扩展的错误信息，请调用 GetLastError。
@别名 注册热键()
BOOL RegisterHotKey(HWND hWnd, int id, UINT fsModifiers, UINT vk);

@备注 释放以前由调用线程注册的热键。
@参数 与要释放的热键关联的窗口的句柄。 如果热键与窗口不关联，则此参数应为 NULL
@参数 要释放的热键的标识符
@返回 如果该函数成功，则返回值为非零值。如果函数失败，则返回值为零。 要获得更多的错误信息，请调用 GetLastError。
@别名 取消注册热键()
BOOL UnregisterHotKey(HWND hWnd, int  id);

//@备注 用于获取指定设备上下文的能力信息
//@参数 设备上下文句柄
//@参数 索引
//@返回 指定设备能力的信息
//@别名 取设备能力()
int WINAPI GetDeviceCaps(
    HDC hdc,
    int index
);

//@备注 用于显示“打开文件”对话框并获取用户选择的文件名
//@参数 打开文件名结构指针
//@返回 如果用户选择了文件，返回值为非零值 如果用户取消操作，返回值为零
//@别名 取打开文件名()
BOOL GetOpenFileName(
    LPOPENFILENAMEW unnamedParam1
);

//@备注 用于获取指定字符串的长度
//@参数 字符串指针
//@返回 字符串的长度（以字符为单位）
//@别名 取字符串长度()
int lstrlen(
    LPCWSTR lpString
);

//@备注 为调用进程分配一个新的控制台
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 分配控制台()
BOOL WINAPI AllocConsole(void);

//@备注 将字符串写入控制台屏幕缓冲区
//@参数 控制台输出句柄
//@参数 缓冲区指针
//@参数 要写入的字符数
//@参数 实际写入的字符数指针
//@参数 保留参数
//@返回 如果函数成功，返回值为非零值 如果函数失败，返回值为零
//@别名 写入控制台()
BOOL WINAPI WriteConsole(
    HANDLE hConsoleOutput,
    const void *lpBuffer,
    DWORD nNumberOfCharsToWrite,
    LPDWORD lpNumberOfCharsWritten,
    LPVOID lpReserved
);

//@备注 获取指定标准设备的句柄（标准输入、标准输出或标准错误）
//@参数 标准设备类型,此参数的取值可为下列值之一:
//STD_INPUT_HANDLE((DWORD)-10)	标准输入设备。 最初，这是输入缓冲区 CONIN$ 的控制台。
//STD_OUTPUT_HANDLE((DWORD)-11)	标准输出设备。 最初，这是活动控制台屏幕缓冲区 CONOUT$。
//STD_ERROR_HANDLE((DWORD)-12)	标准错误设备。 最初，这是活动控制台屏幕缓冲区 CONOUT$。
//@返回 如果函数成功，返回值为标准设备句柄 如果函数失败，返回值为INVALID_HANDLE_VALUE
//@别名 取标准设备句柄()
HANDLE WINAPI GetStdHandle( DWORD nStdHandle);

//@备注 确定调用线程的消息队列中是否存在鼠标按钮或键盘消息
//@返回 如果存在鼠标按钮或键盘消息，返回值为非零值 否则返回值为零
//@别名 取输入状态()
BOOL GetInputState();

//@备注 检索在调用此函数期间运行当前线程的处理器的编号
//@返回 当前线程运行的处理器编号
//@别名 取当前处理器编号()
DWORD GetCurrentProcessorNumber();

//@备注 检索运行调用线程的逻辑处理器的处理器组和编号
//@参数 ProcNumber 处理器编号结构指针
//@别名 取当前处理器编号扩展()
void GetCurrentProcessorNumberEx(PPROCESSOR_NUMBER ProcNumber);

//@备注 检索系统计时信息。在多处理器系统上，返回的值是所有处理器上指定时间的总和
//@参数 lpIdleTime 返回的系统空闲时间
//@参数 lpKernelTime 返回的系统内核模式时间
//@参数 lpUserTime 返回的系统用户模式时间
//@返回 如果函数成功，返回值为非零值；如果函数失败，返回值为零
//@别名 取系统时间信息()
BOOL GetSystemTimes(PFILETIME lpIdleTime, PFILETIME lpKernelTime, PFILETIME lpUserTime);

//@备注 用于获取屏幕宽度、高度等系统指标
//@参数 索引
//@返回 指定系统指标的数值
//@别名 取系统度量信息()
int GetSystemMetrics(int nIndex);

//@备注 用于创建一个矩形区域
//@参数 矩形左上角X坐标
//@参数 矩形左上角Y坐标
//@参数 矩形右下角X坐标
//@参数 矩形右下角Y坐标
//@返回 返回创建的矩形区域句柄
//@别名 创建矩形区域()
HRGN CreateRectRgn(int x1, int y1, int x2, int y2);

//@备注 用于创建一个多边形区域
//@参数 点数组指针
//@参数 点的数量
//@参数 多边形填充模式
//@返回 返回创建的多边形区域句柄
//@别名 创建多边形区域()
HRGN WINAPI CreatePolygonRgn(__in const POINT *pptl, __in int cPoint, __in int iMode);


//@备注 检索调用线程的最后一个错误代码值。最后一个错误代码基于每个线程进行维护。多个线程不会覆盖彼此的最后一个错误代码。
//@返回 调用线程的最后一个错误代码值
//@别名 取系统API最后错误值()
DWORD WINAPI GetLastError();

*/

//@分组}

