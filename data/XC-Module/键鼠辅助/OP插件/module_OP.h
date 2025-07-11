#pragma once

//@模块名称	OP插件
//@版本  1.2.2  
//@日期  2021-04-24
//@作者  DeepFire-炫彩模块封装：zgr
//@QQ    154460336
//@模块备注 封装自开源OP项目0.3.9(https://gitee.com/wallbreaker2/op 项目中难免存在BUG,如有问题请及时反馈修复) 
//类似大漠插件 ，Windows消息模拟,gdi,dx,opengl截图，找图,找字(OCR),其他实用算法 
//说明：本模块只用作技术研究，不针对任何使用场景，用本模块制作的任何软件和本人无关，请遵守OP项目原版相关声明。 
//@依赖  module_base.h

//@隐藏{
#include <iostream>
#include <string>
#include<vector>

using bytearray = std::vector<unsigned char>;
using namespace std;
#define OP_API __declspec(dllimport)

class WinApi;
class bkbase;
class ImageProc;

//@隐藏}
#undef FindWindow
#undef FindWindowEx

#ifdef  _WIN64
//@lib "op_x64.lib"
//@复制文件 @当前模块路径 "op_x64.dll"
#else
//@lib "op_x86.lib"
//@复制文件 @当前模块路径 "op_x86.dll"
#endif


//@备注 使用前必须先创建OP对象 例 创建OP对象 OP1
//@别名  创建OP对象
class __declspec(dllimport)  libop {

public:
	libop();
	~libop();

private:
	//一些共用变量

	//1. Windows API
	WinApi* _winapi;
	// background module
	bkbase* _bkproc;
	//image process
	ImageProc* _image_proc;
	// work path
	std::wstring _curr_path;

	std::map<std::wstring, long> _vkmap;
	bytearray _screenData;
	bytearray _screenDataBmp;
	std::wstring m_opPath;

public:
	//@备注 获取OP版本信息
	//@参数 ret  wstring类型变量	返回版本信息
	//@别名  取版本()
	long Ver(wstring& ret);

	//@备注 设置全局路径,设置了此路径后,所有接口调用中,相关的文件都相对于此路径. 比如图片,字库等.
	//@参数 path  wstring类型变量	设置路径,可以是相对路径,也可以是绝对路径
	//@参数 ret  long类型变量 返回值 0: 失败，1: 成功
	//@别名  置目录();
	long SetPath(const wchar_t* path, long* ret);

	//@备注 获取全局路径.(可用于调试)
	//@参数 path  wstring类型变量 返回以字符串的形式返回当前设置的全局路径
	//@别名  取目录()
	long GetPath(wstring& path);

	//@备注 获取注册在系统中的op.dll的路径
	//@参数 path  wstring类型变量 返回op.dll所在路径
	//@别名  取插件目录()
	long GetBasePath(wstring& path);

	//@备注 返回当前对象的ID值，这个值对于每个对象是唯一存在的。可以用来判定两个对象是否一致
	//@参数 ret  long类型变量 返回当前对象的ID值
	//@别名  取当前对象ID()
	long GetID(long* ret);

	//@备注	获取插件命令的最后错误,值的具体信息看文档
	//@参数 ret  long类型变量 返回值表示错误值。 0表示无错误.
	//@别名  取最后错误()
	long GetLastError(long* ret);

	//@备注	设置是否弹出错误信息,默认是打开 0:关闭，1:显示为信息框，2:保存到文件,3:输出到标准输出
	//@参数 show_type  long类型变量	设置0表示不打开,1表示打开，2表示将错误信息写入文件
	//@参数 ret  long类型变量 返回值 0: 失败，1: 成功
	//@别名  置是否弹出错误信息()
	long SetShowErrorMsg(long show_type, long* ret);


	//@备注	Sleep睡眠 有问题未公开
	//@参数 millseconds  long类型变量	设置睡眠时间以毫秒为单位 1000毫秒=1秒
	//@参数 ret  long类型变量 返回值 0: 失败，1: 成功
	//@别名  睡眠()
	long Sleep(long millseconds, long* ret);


	//@备注	Process inject dll  有问题未公开
	//@参数 process_name  wchar_t类型变量	进程名字
	//@参数 dll_name  wchar_t类型变量	dll名字 
	//@参数 ret  long类型变量 返回值 0: 失败，1: 成功
	//@别名  提权()
	long InjectDll(const wchar_t* process_name, const wchar_t* dll_name, long* ret);


	//@备注 设置是否开启或者关闭插件内部的图片缓存机制	
	//@参数 enable   long类型变量	设置0 : 关闭,1 : 打开
	//@参数 ret   long类型变量	 返回值 0: 失败，1: 成功
	//@别名  开启图片缓存()
	long EnablePicCache(long enable, long* ret);

	//@备注	抓取上次操作的图色区域，保存为file(32位位图) 注意，要开启此函数，必须先调用EnableDisplayDebug 任何图色或者文字识别函数，都可以通过这个来截取
	//@参数 file_name  wstring类型变量	设置保存路径,可以是相对路径,也可以是绝对路径
	//@参数 ret  long类型变量 返回值 0: 失败，1: 成功
	//@别名  抓取上次图色区域();
	long CapturePre(const wchar_t* file_name, long* ret);

	
	//@备注	 根据A星算法，获取地图上从源坐标到目的坐标的一条最短路径
	//@参数 mapWidth  long类型变量	区域的左上X坐标
	//@参数 mapHeight  long类型变量	区域的左上Y坐标
	//@参数 disable_points  wchar_t类型变量	不可通行的坐标，以"|"分割，例如:"10,15|20,30"
	//@参数 beginX  long类型变量	源坐标X
	//@参数 beginY  long类型变量	源坐标Y
	//@参数 endX  long类型变量	目的坐标X
	//@参数 endY  long类型变量 目的坐标Y
	//@参数 path  wstring类型变量	返回计算的路径
	//@别名  A星算法();
	long AStarFindPath(long mapWidth, long mapHeight, const wchar_t* disable_points, long beginX, long beginY, long endX, long endY, wstring& path);


	//@备注	根据指定条件,枚举系统中符合条件的窗口
	//@参数 parent  long类型变量	获得的窗口句柄是该窗口的子窗口的窗口句柄,取0时为获得桌面句柄
	//@参数 title  wchar_t类型变量	窗口标题. 此参数是模糊匹配.
	//@参数 class_name  wchar_t类型变量	窗口类名. 此参数是模糊匹配.
	//@参数 filter  long类型变量	取值类型1标题，2类名，4匹配指定父窗口的第一层孩子窗口，8匹配所有者窗口为0的窗口,即顶级窗口，16 : 匹配可见的窗口，32 : 匹配出的窗口按照窗口打开顺序依次排列，这些值可以相加,比如4+8+16就是类似于任务管理器中的窗口列表
	//@参数 retstr  wchar_t类型变量	返回所有匹配的窗口句柄字符串,格式"hwnd1,hwnd2,hwnd3"
	//@别名	枚举窗口()
	long EnumWindow(long parent, const wchar_t* title, const wchar_t* class_name, long filter, wstring& retstr);
	
	
	//@备注	根据指定进程以及其它条件,枚举系统中符合条件的窗口
	//@参数 process_name  wchar_t类型变量	进程映像名.比如(svchost.exe). 此参数是精确匹配,但不区分大小写
	//@参数 title  wchar_t类型变量	窗口标题. 此参数是模糊匹配.
	//@参数 class_name  wchar_t类型变量	窗口类名. 此参数是模糊匹配.
	//@参数 filter  long类型变量	取值类型1标题，2类名，4匹配指定父窗口的第一层孩子窗口，8匹配所有者窗口为0的窗口,即顶级窗口，16 : 匹配可见的窗口，32 : 匹配出的窗口按照窗口打开顺序依次排列，这些值可以相加,比如4+8+16就是类似于任务管理器中的窗口列表
	//@参数 retstr  wchar_t类型变量	返回所有匹配的窗口句柄字符串,格式"hwnd1,hwnd2,hwnd3"
	//@别名	枚举进程()
	long EnumWindowByProcess(const wchar_t* process_name, const wchar_t* title, const wchar_t* class_name, long filter, wstring& retstring);
	
	
	//@备注	根据指定进程名,枚举系统中符合条件的进程PID
	//@参数 name  wchar_t类型变量	进程名,比如qq.exe
	//@参数 retstring  wchar_t类型变量	返返回所有匹配的进程PID,并按打开顺序排序,格式"pid1,pid2,pid3"
	//@别名	枚举进程PID()
	long EnumProcess(const wchar_t* name, wstring& retstring);
	
	
	//@备注	把窗口坐标转换为屏幕坐标
	//@参数 ClientToScreen  long类型变量	指定的窗口句柄
	//@参数 x  long类型变量	窗口X坐标
	//@参数 y  long类型变量	窗口Y坐标
	//@参数 bret  long类型变量 返回值 0: 失败，1: 成功
	//@别名	窗口坐标转屏幕坐标()
	long ClientToScreen(long ClientToScreen, long* x, long* y, long* bret);
	
	//@备注	查找符合类名或者标题名的顶层可见窗口
	//@参数 class_name  wchar_t类型变量	窗口类名，如果为空，则匹配所有. 这里的匹配是模糊匹配
	//@参数 title  wchar_t类型变量	窗口标题,如果为空，则匹配所有.这里的匹配是模糊匹配
	//@参数 rethwnd  long类型变量	返回整形数表示的窗口句柄，没找到返回0
	//@别名	查找窗口1()
	long FindWindow(const wchar_t* class_name, const wchar_t* title, long* rethwnd);

	//@备注	根据指定的进程名字，来查找可见窗口
	//@参数 process_name  wchar_t类型变量	进程名. 比如(notepad.exe).这里是精确匹配,但不区分大小写
	//@参数 class_name  wchar_t类型变量	窗口类名，如果为空，则匹配所有. 这里的匹配是模糊匹配
	//@参数 title  wchar_t类型变量	窗口标题,如果为空，则匹配所有.这里的匹配是模糊匹配
	//@参数 rethwnd  long类型变量	返回整形数表示的窗口句柄，没找到返回0
	//@别名	根据进程查找窗口()
	long FindWindowByProcess(const wchar_t* process_name, const wchar_t* class_name, const wchar_t* title, long* rethwnd);
	
	//@备注	根据指定的进程Id，来查找可见窗口
	//@参数 process_id  long类型变量	进程id
	//@参数 class_name  wchar_t类型变量	窗口类名，如果为空，则匹配所有. 这里的匹配是模糊匹配
	//@参数 title  wchar_t类型变量	窗口标题,如果为空，则匹配所有.这里的匹配是模糊匹配
	//@参数 rethwnd  long类型变量	返回整形数表示的窗口句柄，没找到返回0
	//@别名	根据进程查找窗口()
	long FindWindowByProcessId(long process_id, const wchar_t* class_name, const wchar_t* title, long* rethwnd);

	//@备注	查找符合类名或者标题名的顶层可见窗口,如果指定了parent,则在parent的第一层子窗口中查找
	//@参数 parent  long类型变量	父窗口句柄，如果为空，则匹配所有顶层窗口
	//@参数 class_name  wchar_t类型变量	窗口类名，如果为空，则匹配所有. 这里的匹配是模糊匹配
	//@参数 title  wchar_t类型变量	窗口标题,如果为空，则匹配所有.这里的匹配是模糊匹配
	//@参数 rethwnd  long类型变量	返回整形数表示的窗口句柄，没找到返回0
	//@别名	查找窗口2()
	long FindWindowEx(long parent, const wchar_t* class_name, const wchar_t* title, long* rethwnd);

	//@备注	取窗口客户区域在屏幕上的位置
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 x1  long类型变量	返回窗口客户区左上角X坐标
	//@参数 y1  long类型变量	返回窗口客户区左上角Y坐标
	//@参数 x2  long类型变量	返回窗口客户区右下角X坐标
	//@参数 y2  long类型变量	返回窗口客户区右下角Y坐标
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@别名	取客户区在屏幕上的位置()
	long GetClientRect(long hwnd, long* x1, long* y1, long* x2, long* y2, long* nret);
	
	//@备注	取窗口客户区域的宽度和高度
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 width  long类型变量	宽度
	//@参数 height  long类型变量	高度
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 取窗口客户区宽高()
	long GetClientSize(long hwnd, long* width, long* height, long* nret);
	
	//@备注	取顶层活动窗口中具有输入焦点的窗口句柄
	//@参数 rethwnd  long类型变量	返回整型表示的窗口句柄
	//@别名	取顶层活动窗口1()
	long GetForegroundFocus(long* rethwnd);
	
	//@备注	取顶层活动窗口,可以获取到按键自带插件无法获取到的句柄
	//@参数 rethwnd  long类型变量	返回整型表示的窗口句柄
	//@别名 取顶层活动窗口2()
	long GetForegroundWindow(long* rethwnd);
	
	//@备注	取鼠标指向的可见窗口句柄
	//@参数 rethwnd  long类型变量	返回整型表示的窗口句柄
	//@别名 取鼠标指向窗口句柄()
	long GetMousePointWindow(long* rethwnd);
	
	//@备注	取给定坐标的可见窗口句柄
	//@参数 x  long类型变量	屏幕X坐标
	//@参数 y  long类型变量	屏幕Y坐标
	//@参数 rethwnd  long类型变量	返回整型表示的窗口句柄
	//@别名 取坐标可见窗口句柄()
	long GetPointWindow(long x, long y, long* rethwnd);
	
	//@备注	根据指定的pid获取进程详细信息
	//@参数 pid  long类型变量	进程pid
	//@参数 retstring  wchar_t类型变量	格式"进程名|进程路径|cpu|内存"
	//@别名  取指定进程信息()
	long GetProcessInfo(long pid, wstring& retstring);
	
	//@备注	取特殊窗口  flag: 0获取桌面窗口 1获取任务栏窗口  
	//@参数 rethwnd  long类型变量	返回整型表示的窗口句柄
	//@别名	取特殊窗口()
	long GetSpecialWindow(long flag, long* rethwnd);
	
	//@备注	取给定窗口相关的窗口句柄 flag:0获取父窗口,1获取第一个儿子窗口,2获取First 窗口,3获取Last窗口,4获取下一个窗口, 5获取上一个窗口,6获取拥有者窗口,7获取顶层窗口
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 flag  long类型变量	指定获取flag
	//@参数 nret  long类型变量	返回整型表示的窗口句柄
	//@别名	取给定窗口相关的窗口句柄()
	long GetWindow(long hwnd, long flag, long* nret);
	
	//@备注	取窗口的类名
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 retstring  wchar_t类型变量	返回窗口的类名
	//@别名	取窗口的类名()
	long GetWindowClass(long hwnd, wstring& retstring);

	//@备注	取指定窗口所在的进程ID
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 nretpid  long类型变量	返回整型表示的是进程ID
	//@别名  取指定窗口进程ID()
	long GetWindowProcessId(long hwnd, long* nretpid);
	
	//@备注	取指定窗口所在的进程的exe文件全路径
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 retstring  wchar_t类型变量	返回字符串表示的是exe全路径名
	//@别名	取指定窗口进程文件路径()
	long GetWindowProcessPath(long hwnd, wstring& retstring);
	
	//@备注	取窗口在屏幕上的位置
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 x1  long类型变量	返回窗口左上角X坐标
	//@参数 y1  long类型变量	返回窗口左上角Y坐标
	//@参数 x2  long类型变量	返回窗口右下角X坐标
	//@参数 y2  long类型变量	返回窗口右下角Y坐标
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 取窗口在屏幕位置()
	long GetWindowRect(long hwnd, long* x1, long* y1, long* x2, long* y2, long* nret);
	
	//@备注	取指定窗口的一些属性 flage  0判断窗口是否存在,1判断窗口是否处于激活,2判断窗口是否可见,3判断窗口是否最小化,4判断窗口是否最大化,5判断窗口是否置顶,6判断窗口是否无响应,7判断窗口是否可用(灰色为不可用),8另外的方式判断窗口是否无响应,如果6无效可以尝试这个
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 flag  long类型变量	指定判断条件
	//@参数 nret  long类型变量	返回值 0: 不满足条件，1: 满足条件
	//@别名	取指定窗口属性()
	long GetWindowState(long hwnd, long flag, long* rethwnd);


	//@别名  取窗口标题()
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 retstring  wchar_t类型变量	返回窗口的标题
	//@备注	取窗口标题()
	long GetWindowTitle(long hwnd, wstring& rettitle);


	//@备注	移动指定窗口到指定位置
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 x  long类型变量	X坐标
	//@参数 y  long类型变量	Y坐标
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@别名	移动窗口到指定位置()
	long MoveWindow(long hwnd, long x, long y, long* nret);
	
	//@备注	把屏幕坐标转换为窗口坐标
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 x  long类型变量	屏幕X坐标
	//@参数 y  long类型变量	屏幕Y坐标
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@别名	屏幕坐标转窗口坐标()
	long ScreenToClient(long hwnd, long* x, long* y, long* nret);
	
	//@备注	向指定窗口发送粘贴命令
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@别名	向指定窗口发送粘贴命令()
	long SendPaste(long hwnd, long* nret);
	
	//@备注	设置窗口客户区域的宽度和高度
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 width  long类型变量	宽度
	//@参数 height  long类型变量	高度
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@别名  置窗口客户区域宽高()
	long SetClientSize(long hwnd, long width, long hight, long* nret);
	
	//@备注	设置窗口的状态 0关闭,1激活,2最小化窗口不激活,3最小化窗口激活,4最大化激活,5恢复窗口不激活，6隐藏,7显示,8置顶,9取消置顶,10禁止,11取消禁止,12恢复并激活,13强制结束,14闪烁,15窗口获取输入焦点
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 flag  long类型变量	设置窗口状态flag
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@别名  置窗口状态()
	long SetWindowState(long hwnd, long flag, long* nret);

	//@别名  置窗口大小()
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 width  long类型变量	宽度
	//@参数 height  long类型变量	高度
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@备注	设置窗口的大小
	long SetWindowSize(long hwnd, long width, long height, long* nret);

	//@别名  置窗口标题()
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 retstring  wchar_t类型变量	设置修改的窗口标题
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@备注	设置窗口的标题
	long SetWindowText(long hwnd, const wchar_t* title, long* nret);


	//@备注	设置窗口的透明度 透明度取值(0-255) 越小透明度越大 0为完全透明(不可见) 255为完全显示(不透明)
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 trans  long类型变量	设置窗口透明度
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@别名  置窗口的透明度()
	long SetWindowTransparent(long hwnd, long trans, long* nret);
	
	//@备注	向指定窗口发送文本数据
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 retstring  wchar_t类型变量	设置修改的窗口标题
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 向指定窗口发送文本()
	long SendString(long hwnd, const wchar_t* str, long* ret);
	
	//@备注	向指定窗口发送文本数据-输入法 必须配合绑定dx.public.input.ime属性
	//@参数 hwnd  long类型变量	指定的窗口句柄
	//@参数 retstring  wchar_t类型变量	设置修改的窗口标题
	//@参数 nret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 向指定窗口发送文本2()
	long SendStringIme(long hwnd, const wchar_t* str, long* ret);
	
	//@备注	运行可执行文件,可指定模式 0普通模式  1加强模式
	//@参数 cmdline  wchar_t类型变量	指定的可执行程序全路径.
	//@参数 mode  long类型变量	0普通模式  1加强模式
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 运行可执行文件()
	long RunApp(const wchar_t* cmdline, long mode, long* ret);
	
	//@备注	运行可执行文件，可指定显示模式  0 : 隐藏  1 : 用最近的大小和位置显示, 激活
	//@参数 cmdline  wchar_t类型变量	指定的可执行程序全路径.
	//@参数 cmdshow  long类型变量	 0 : 隐藏  1 : 用最近的大小和位置显示, 激活
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 运行可执行文件2()
	long WinExec(const wchar_t* cmdline, long cmdshow, long* ret);

	//@备注	运行命令行并返回结果 cmdline 字符串: 指定的可执行程序全路径 millseconds 整形数: 等待的时间(毫秒) retstr字符串:  返回cmd输出的字符
	//@参数 cmdline  wchar_t类型变量	指定的可执行程序全路径.
	//@参数 millseconds  long类型变量	 等待的时间(毫秒)
	//@参数 ret  wchar_t类型变量	返回cmd输出的字符
	//@别名 运行可执行文件3()
	long GetCmdStr(const wchar_t* cmd, long millseconds, wstring& retstr);

	//--------------------Background -----------------------
	//@备注	bind window and beign capture screen
	//@别名 BindWindow()
	long BindWindow(long hwnd, const wchar_t* display, const wchar_t* mouse, const wchar_t* keypad, long mode, long* ret);
	

	//@别名 UnBindWindow()
	long UnBindWindow(long* ret);
	//--------------------mouse & keyboard------------------

	//@备注	取鼠标位置.
	//@参数 x  long类型变量	X坐标
	//@参数 y  long类型变量	Y坐标
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 取鼠标位置()
	long GetCursorPos(long* x, long* y, long* ret);
	
	//@备注	鼠标相对于上次的位置移动rx,ry.
	//@参数 x  long类型变量	相对于上次的X偏移
	//@参数 y  long类型变量	相对于上次的Y偏移
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 鼠标相对上次位置移动至()
	long MoveR(long x, long y, long* ret);
	
	//@备注	把鼠标移动到目的点(x,y)
	//@参数 x  long类型变量	X坐标
	//@参数 y  long类型变量	Y坐标
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 鼠标移动到目的点()
	long MoveTo(long x, long y, long* ret);
	
	//@备注	此函数的意思是移动鼠标到指定的范围(x,y,x+w,y+h)内的任意随机一点
	//@参数 x  long类型变量	X坐标
	//@参数 y  long类型变量	Y坐标
	//@参数 w  long类型变量	宽度(从x计算起)
	//@参数 h  long类型变量	高度(从y计算起)
	//@参数 ret  long类型变量	返回要移动到的目标点. 格式为x,y.  比如MoveToEx 100,100,10,10,返回值可能是101,102
	//@别名 鼠标移动到任意点()
	long MoveToEx(long x, long y, long w, long h, long* ret);
	
	//@备注	按下鼠标左键
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 按下鼠标左键()
	long LeftClick(long* ret);
	
	//@备注	双击鼠标左键
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 双击鼠标左键()
	long LeftDoubleClick(long* ret);
	
	//@备注	按住鼠标左键
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 按住鼠标左键()
	long LeftDown(long* ret);
	
	//@备注	弹起鼠标左键
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 弹起鼠标左键()
	long LeftUp(long* ret);
	
	//@备注	按下鼠标中键
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 按下鼠标中键()
	long MiddleClick(long* ret);
	
	//@备注	按住鼠标中键
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 按住鼠标中键()
	long MiddleDown(long* ret);
	
	//@备注	弹起鼠标中键
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 弹起鼠标中键()
	long MiddleUp(long* ret);
	
	//@备注	按下鼠标右键
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 按下鼠标右键()
	long RightClick(long* ret);
	
	//@备注	按住鼠标右键
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 按住鼠标右键()
	long RightDown(long* ret);
	
	//@备注	弹起鼠标右键
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 弹起鼠标右键()
	long RightUp(long* ret);
	
	//@备注	滚轮向下滚
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 滚轮向下滚()
	long WheelDown(long* ret);
	
	//@备注	滚轮向上滚
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 滚轮向上滚()
	long WheelUp(long* ret);
	
	//@备注	取指定的按键状态.(前台信息,不是后台)
	//@参数 vk_code  long类型变量	虚拟按键码
	//@参数 ret  long类型变量	返回值 0: 弹起，1: 按下
	//@别名 取指定按键状态()
	long GetKeyState(long vk_code, long* ret);
	
	//@备注	按住指定的虚拟键码 按键对应的asin码
	//@参数 vk_code  long类型变量	虚拟按键码
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 按住虚拟键1()
	long KeyDown(long vk_code, long* ret);
	
	//@备注	按住指定的虚拟键  非asin是具体的按键吗字符串比如"1"
	//@参数 vk_code  wchar_t类型变量	虚拟按键字符串
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 按住虚拟键2()
	long KeyDownChar(const wchar_t* vk_code, long* ret);
	
	//@备注	弹起来虚拟键	按键对应的asin键码
	//@参数 vk_code  long类型变量	虚拟按键码
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 弹起虚拟键1()
	long KeyUp(long vk_code, long* ret);
	
	//@备注	弹起来虚拟键   非asin 是具体的按键吗字符串比如"1"
	//@参数 vk_code  wchar_t类型变量	虚拟按键字符串
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 弹起虚拟键2()
	long KeyUpChar(const wchar_t* vk_code, long* ret);
	
	//@备注	等待指定的按键按下 (前台,不是后台)
	//@参数 vk_code  long类型变量	虚拟按键码,当此值为0，表示等待任意按键。 鼠标左键是1,鼠标右键时2,鼠标中键是4
	//@参数 time_out  long类型变量	等待多久,单位毫秒. 如果是0，表示一直等待
	//@参数 ret  long类型变量	返回值 0:超时  1:指定的按键按下 (当vk_code不为0时)  按下的按键码:(当vk_code为0时)
	//@别名 等待指定的按键按下()
	long WaitKey(long vk_code, long time_out, long* ret);
	
	
	//@备注	下指定的虚拟键码 按键对应的asin码
	//@参数 vk_code  long类型变量	虚拟按键码
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 按下虚拟键1()
	long KeyPress(long vk_code, long* ret);

	//@备注 按下指定的虚拟键码 非asin 是具体的按键吗字符串比如"1"
	//@参数 vk_code  wchar_t类型变量	虚拟按键字符串
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 按下虚拟键2()
	long KeyPressChar(const wchar_t* vk_code, long* ret);

	//--------------------image and color-----------------------
	//@备注	抓取指定区域(x1, y1, x2, y2)的图像, 保存为file
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 file_name  wchar_t类型变量	保存的文件名,保存的地方一般为SetPath中设置的目录,也可以指定全路径名
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 抓取指定区域图像()
	long Capture(long x1, long y1, long x2, long y2, const wchar_t* file_name, long* ret);
	
	//@备注	比较指定坐标点(x,y)的颜色  注意，这里只支持RGB颜色.
	//@参数 x1  long类型变量	X坐标
	//@参数 y1  long类型变量	Y坐标
	//@参数 color  wchar_t类型变量 颜色字符串,可以支持偏色,多色,例如 "ffffff-202020|000000-000000" 这个表示白色偏色为202020,和黑色偏色为000000.颜色最多支持10种颜色组合.
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 ret  long类型变量	返回值 0: 颜色匹配,1: 颜色不匹配
	//@别名 比较坐标点颜色()
	long CmpColor(long x, long y, const wchar_t* color, double sim, long* ret);
	
	//@备注	查找指定区域内的颜色 这里只支持RGB颜色
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 color  wchar_t类型变量 格式为"RRGGBB-DRDGDB",比如"123456-000000|aabbcc-202020"
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 dir  long类型变量 查找顺序 0左右上下，1左右下上，2右左上下,3右左下上,4中心往外,5上下左右,6下上左右,7下上左右,8下上右左
	//@参数 x  long类型变量	返回X坐标
	//@参数 y  long类型变量	返回Y坐标
	//@参数 ret  long类型变量	返回结果 0: 没找到,1:找到
	//@别名 查找指定区域颜色()
	long FindColor(long x1, long y1, long x2, long y2, const wchar_t* color, double sim, long dir, long* x, long* y, long* ret);
	
	//@备注	查找指定区域内的所有颜色,颜色格式"RRGGBB-DRDGDB",注意,和按键的颜色格式相反
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 color  wchar_t类型变量 格式为"RRGGBB-DRDGDB",比如"123456-000000|aabbcc-202020"
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 dir  long类型变量 查找顺序 0左右上下，1左右下上，2右左上下,3右左下上,4中心往外,5上下左右,6下上左右,7下上左右,8下上右左
	//@参数 retstr  wchar_t类型变量 返回所有颜色信息的坐标值,然后通过GetResultCount等接口来解析 (由于内存限制,返回的颜色数量最多为1800个左右)
	//@别名 查找指定区域所有颜色()
	long FindColorEx(long x1, long y1, long x2, long y2, const wchar_t* color, double sim, long dir, wstring& retstr);
	
	//@备注	根据指定的多点查找颜色坐标
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 first_color  wchar_t类型变量 颜色格式为"RRGGBB-DRDGDB|RRGGBB-DRDGDB|…………",比如"123456-000000"
	//@参数 offset_color  wchar_t类型变量 比如"1|3|aabbcc|aaffaa-101010,-5|-3|123456-000000|454545-303030|565656"等任意组合都可以，支持偏色
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 dir  long类型变量 查找顺序0: 从左到右,从上到下 1: 从左到右,从下到上 2: 从右到左,从上到下 3: 从右到左, 从下到上
	//@参数 x  long类型变量	返回X坐标(坐标为first_color所在坐标)
	//@参数 y  long类型变量	返回Y坐标(坐标为first_color所在坐标)
	//@参数 ret  long类型变量	返回结果 0: 没找到,1:找到
	//@别名 查找颜色坐标()
	long FindMultiColor(long x1, long y1, long x2, long y2, const wchar_t* first_color, const wchar_t* offset_color, double sim, long dir, long* x, long* y, long* ret);
	
	//@备注	根据指定的多点查找所有颜色坐标
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 first_color  wchar_t类型变量 颜色格式为"RRGGBB-DRDGDB|RRGGBB-DRDGDB|…………",比如"123456-000000"
	//@参数 offset_color  wchar_t类型变量 比如"1|3|aabbcc|aaffaa-101010,-5|-3|123456-000000|454545-303030|565656"等任意组合都可以，支持偏色
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 dir  long类型变量 查找顺序0: 从左到右,从上到下 1: 从左到右,从下到上 2: 从右到左,从上到下 3: 从右到左, 从下到上
	//@参数 retstr  wchar_t类型变量 返回所有颜色信息的坐标值,然后通过GetResultCount等接口来解析(由于内存限制,返回的坐标数量最多为1800个左右)坐标是first_color所在的坐标
	//@别名 查找所有颜色坐标()
	long FindMultiColorEx(long x1, long y1, long x2, long y2, const wchar_t* first_color, const wchar_t* offset_color, double sim, long dir, wstring& retstr);
	
	//@备注	查找指定区域内的图片
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 files  wchar_t类型变量 图片名,可以是多个图片,比如"test.bmp|test2.bmp|test3.bmp"
	//@参数 delta_color  wchar_t类型变量 颜色色偏比如"203040" 表示RGB的色偏分别是20 30 40 (这里是16进制表示)
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 dir  long类型变量 查找顺序0: 从左到右,从上到下 1: 从左到右,从下到上 2: 从右到左,从上到下 3: 从右到左, 从下到上
	//@参数 x  long类型变量	返回X坐标(坐标为first_color所在坐标)
	//@参数 y  long类型变量	返回Y坐标(坐标为first_color所在坐标)
	//@参数 ret  long类型变量	返回结果 0: 没找到,1:找到
	//@别名	查找指定区域图片()
	long FindPic(long x1, long y1, long x2, long y2, const wchar_t* files, const wchar_t* delta_color, double sim, long dir, long* x, long* y, long* ret);
	
	//@备注	查找多个图片
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 files  wchar_t类型变量 图片名,可以是多个图片,比如"test.bmp|test2.bmp|test3.bmp"
	//@参数 delta_color  wchar_t类型变量 颜色色偏比如"203040" 表示RGB的色偏分别是20 30 40 (这里是16进制表示)
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 dir  long类型变量 查找顺序0: 从左到右,从上到下 1: 从左到右,从下到上 2: 从右到左,从上到下 3: 从右到左, 从下到上
	//@参数 retstr  wchar_t类型变量 返回的是所有找到的坐标格式如下:"id,x,y|id,x,y..|id,x,y" (图片左上角的坐标)比如"0,100,20|2,30,40" 表示找到了两个,第一个,对应的图片是图像序号为0的图片,坐标是(100,20)
	//@别名	查找多个图片()
	long FindPicEx(long x1, long y1, long x2, long y2, const wchar_t* files, const wchar_t* delta_color, double sim, long dir, wstring& retstr);
	
	//@备注	取(x,y)的颜色
	//@参数 x  long类型变量	X坐标
	//@参数 y  long类型变量	Y坐标
	//@参数 ret  wstring类型变量	返回值颜色字符串(注意这里都是小写字符，和工具相匹配)
	//@别名	取坐标颜色()
	long GetColor(long x, long y, wstring& ret);
	
	//@备注	设定图色的获取方式，默认是显示器或者后台窗口(具体参考BindWindow)
	//@参数 mode  wstring类型变量  "screen"默认显示器或者后台窗口 "pic:file" 指定输入图片为文件，"mem:addr,size" 指定输入图片在内存当中
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名  置图像输入方式()
	long SetDisplayInput(const wchar_t* mode, long* ret);
	
	//@备注	预先加载指定的图片,这样在操作任何和图片相关的函数时,将省去了加载图片的时间。调用此函数后,没必要一定要调用FreePic,插件自己会自动释放.
	//@参数 file_name  wstring类型变量 文件名比如"1.bmp|2.bmp|3.bmp" 等,可以使用通配符"*.bmp" 这个对应了所有的bmp文件
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名	预加载指定的图片()
	long LoadPic(const wchar_t* file_name, long* ret);
	
	//@备注	释放指定的图片,此函数不必要调用,除非你想节省内存.
	//@参数 file_name  wstring类型变量 文件名比如"1.bmp|2.bmp|3.bmp" 等,可以使用通配符"*.bmp" 这个对应了所有的bmp文件
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名	释放指定图片()
	long FreePic(const wchar_t* file_name, long* ret);
	
	//@备注	获取指定区域的图像,用二进制数据的方式返回,（不适合按键使用）方便二次开发.
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 data  void**类型变量	返回图片的数据指针 
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名	抓取指定区域图像2()
	long GetScreenData(long x1, long y1, long x2, long y2, void** data, long* ret);
	
	//@备注	获取指定区域的图像,用24位位图的数据格式返回,方便二次开发.（或者可以配合SetDisplayInput的mem模式）
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 data  void**类型变量	返回图片的数据指针 
	//@参数 size  long类型变量	区域的右下Y坐标 
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名	抓取指定区域图像3()
	long GetScreenDataBmp(long x1, long y1, long x2, long y2, void** data, long* size, long* ret);
	
	//@别名	GetScreenFrameInfo()
	long GetScreenFrameInfo(long* frame_id, long* time);
	//----------------------ocr-------------------------
	//@备注	设置字库文件
	//@参数 idx  long类型变量	字库的序号,取值为0-19,目前最多支持20个字库 
	//@参数 file_name  wchar_t类型变量	字库文件名 
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名  置字库文件()
	long SetDict(long idx, const wchar_t* file_name, long* ret);
	
	//@备注	使用哪个字库文件进行识别
	//@参数 idx  long类型变量	字库编号(0-9)
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名	选择识别字库()
	long UseDict(long idx, long* ret);
	
	//@备注	识别屏幕范围(x1,y1,x2,y2)内符合color_format的字符串,并且相似度为sim,sim取值范围(0.1-1.0),
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 color  wchar_t类型变量 格式为"RRGGBB-DRDGDB",比如"123456-000000|aabbcc-202020"
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 ret_str  wchar_t类型变量 返回识别到的字符串
	//@别名	识别屏幕字符串1()
	long Ocr(long x1, long y1, long x2, long y2, const wchar_t* color, double sim, wstring& ret_str);
	
	//@备注	识别屏幕范围(x1,y1,x2,y2)内符合color_format的字符串,并且相似度为sim,sim取值范围(0.1-1.0),返回识别到的字符串 格式如  "字符0$x0$y0|…|字符n$xn$yn"
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 color  wchar_t类型变量 格式为"RRGGBB-DRDGDB",比如"123456-000000|aabbcc-202020"
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 ret_str  wchar_t类型变量 返回识别到的字符串
	//@别名 识别屏幕字符串2()
	long OcrEx(long x1, long y1, long x2, long y2, const wchar_t* color, double sim, wstring& ret_str);
	
	//@备注	在屏幕范围(x1,y1,x2,y2)内,查找string(可以是任意个字符串的组合),并返回符合color_format的坐标位置
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 strs  wchar_t类型变量 待查找的字符串,可以是字符串组合，比如"长安|洛阳|大雁塔",中间用"|"来分割字符串
	//@参数 color  wchar_t类型变量 颜色格式串, 可以包含换行分隔符,语法是","后加分割字符串","9f2e3f-000000"
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 retx  long类型变量 返回X坐标没找到返回-1
	//@参数 rety  long类型变量 返回Y坐标没找到返回-1	
	//@参数 ret  long类型变量	返回字符串的索引 没找到返回-1, 比如"长安|洛阳",若找到长安，则返回0
	//@别名	查找屏幕字符串1()
	long FindStr(long x1, long y1, long x2, long y2, const wchar_t* strs, const wchar_t* color, double sim, long* retx, long* rety, long* ret);
	
	//@备注	在屏幕范围(x1,y1,x2,y2)内,查找string(可以是任意个字符串的组合),并返回符合color_format的坐标位置
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 strs  wchar_t类型变量 待查找的字符串,可以是字符串组合，比如"长安|洛阳|大雁塔",中间用"|"来分割字符串
	//@参数 color  wchar_t类型变量 颜色格式串, 可以包含换行分隔符,语法是","后加分割字符串","9f2e3f-000000"
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 retstr  wchar_t类型变量	返回所有找到的坐标集合,格式如下:比如"0,100,20|2,30,40" 表示找到了两个,第一个,对应的是序号为0的字符串,坐标是(100,20),第二个是序号为2的字符串,坐标(30,40)
	//@别名 查找屏幕字符串2()
	long FindStrEx(long x1, long y1, long x2, long y2, const wchar_t* strs, const wchar_t* color, double sim, wstring& retstr);
	
	//@备注	识别屏幕范围(x1,y1,x2,y2)内的字符串,自动二值化，而无需指定颜色
	//@参数 x1  long类型变量	区域的左上X坐标
	//@参数 y1  long类型变量	区域的左上Y坐标
	//@参数 x2  long类型变量	区域的右下X坐标
	//@参数 y2  long类型变量	区域的右下Y坐标 
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 ret_str  wchar_t类型变量 返回识别到的字符串
	//@别名	识别屏幕字符串3()
	long OcrAuto(long x1, long y1, long x2, long y2, double sim, wstring& ret_str);
	
	//@备注	从文件中识别图片
	//@参数 file_name  wstring类型变量 文件名比如"1.bmp"
	//@参数 color  wchar_t类型变量 颜色格式串, 可以包含换行分隔符,语法是","后加分割字符串","9f2e3f-000000"
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 ret_str  wchar_t类型变量 返回识别到的字符串
	//@别名	识别文件图片字符串1()
	long OcrFromFile(const wchar_t* file_name, const wchar_t* color_format, double sim, wstring& retstr);
	
	//@备注	从文件中识别图片,无需指定颜色
	//@参数 file_name  wstring类型变量 文件名比如"1.bmp"
	//@参数 sim  double类型变量  双精度浮点数相似度(0.1-1.0)
	//@参数 ret_str  wchar_t类型变量 返回识别到的字符串
	//@别名 识别文件图片字符串2()
	long OcrAutoFromFile(const wchar_t* file_name, double sim, wstring& retstr);
	
	//@备注	查找屏幕中的直线
	//@别名 查找屏幕直线()
	long FindLine(long x1, long y1, long x2, long y2, const wchar_t* color, double sim, wstring& retstr);

	//@备注	向某进程写入数据
	//@参数 hwnd  long类型变量	指定搜索的窗口句柄或者进程ID.  默认是窗口句柄. 如果要指定为进程ID,需要调用SetMemoryHwndAsProcessId
	//@参数 address  wchar_t类型变量	用字符串来描述地址，类似于CE的地址描述"4DA678" ,"<360SE.exe>+DA678" ,"[4DA678]+3A"
	//@参数 data  wchar_t类型变量	二进制数据，以字符串形式描述，比如"12 34 56 78 90 ab cd"
	//@参数 size  long类型变量	二进制数据的长度
	//@参数 ret  long类型变量	返回值 0: 失败，1: 成功
	//@别名 写入进程数据()
	long WriteData(long hwnd, const wchar_t* address, const wchar_t* data, long size, long* ret);
	
	//@备注	读取指定地址的二进制数据
	//@参数 hwnd  long类型变量	指定搜索的窗口句柄或者进程ID.  默认是窗口句柄. 如果要指定为进程ID,需要调用SetMemoryHwndAsProcessId
	//@参数 address  wchar_t类型变量	用字符串来描述地址，类似于CE的地址描述"4DA678" ,"<360SE.exe>+DA678" ,"[4DA678]+3A"
	//@参数 size  long类型变量	二进制数据的长度
	//@参数 retstr  wstring类型变量	返回读取到的数值,以16进制表示的字符串 每个字节以空格相隔 比如"12 34 56 78 ab cd ef"
	//@别名	读取数据()
	long ReadData(long hwnd, const wchar_t* address, long size, wstring& retstr);
};

