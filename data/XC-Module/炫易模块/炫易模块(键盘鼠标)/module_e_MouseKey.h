// Created by Huiyi on 2021/4/20.
//
//@模块名称 炫易模块(键盘鼠标)
//@版本   1.3
//@日期   2022-10-05
//@作者   Huiyi
//@模块备注 封装鼠标键盘操作函数
//项目gitee地址 https://gitee.com/LoveA/XL_XExpand
//大部分代码已经历过粗略测试
//如发现BUG可提交issues
//https://gitee.com/LoveA/XL_XExpand/issues
//反馈QQ群:594165459

//@依赖   module_base.h

#pragma once

#ifndef XL_XEXPAND_MOUSEKEY_H
//@隐藏{
#define XL_XEXPAND_MOUSEKEY_H    //防止复用

#if XC_MODULE
#include "module_base.h"
#endif
//@隐藏}

//@src  "Keyboard.cpp"
//@src  "mouse.cpp"

// TODO: 鼠标键盘分组
//@分组{  键盘操作

//@参数   键代码 可参考常量 键代码_
//@参数   1为按下,2为抬起,否则单击
//@别名   键盘_单击(键代码,状态)
void X_Keyboard_Onclick(BYTE key, int type = 0);

//@参数   键代码 可参考常量 键代码_
//@别名   键盘_键代码取键名(键代码)
CXText X_Keyboard_GetName(BYTE key);
//@参数   键代码 可参考常量 键代码_
//@别名   键盘_键代码取键名A(键代码)
CXTextA X_Keyboard_GetNameA(BYTE key);

//@参数   可空。真=锁全键盘(可空为假)，假=锁定功能键与Win键Esc键F4键Tab键Print键Soroll键Pause键
//@别名   键盘_锁定(状态)
void X_Keyboard_Lock(bool status = false);
//@备注   键盘解锁(键盘锁定后,用来恢复键盘的使用)
//@别名   键盘_解锁()
void X_Keyboard_UnLock();

//@备注   取当前键盘的大小写状态
//@返回   返回真为大写,返回假则为小写
//@别名   键盘_是否为大写()
bool X_Keyboard_IfisUppercase();

//@备注   取功能键状态对应的键名，1.Ctrl键，2.Shift键，4.Alt键，其他为组合
//@参数   功能键状态 如填1，将返回Ctrl键
//@别名   键盘_取功能键名(功能键状态)
CXText X_Keyboard_GetFkeysName(int fkeyStat);
//@备注   取功能键状态对应的键名，1.Ctrl键，2.Shift键，4.Alt键，其他为组合
//@参数   功能键状态 如填1，将返回Ctrl键
//@别名   键盘_取功能键名A(功能键状态)
CXTextA X_Keyboard_GetFkeysNameA(int fkeyStat);

//@备注   取键名的功能键组合，1.Ctrl键，2.Shift键，4.Alt键，其他为组合
//@参数   键名 键名,如填:Ctrl键,将返回1，字母不区分大小写
//@别名   键盘_取功能键状态(键名)
int X_Keyboard_GetFkeysStatus(CXText keyName);
//@备注   取键名的功能键组合，1.Ctrl键，2.Shift键，4.Alt键，其他为组合
//@参数   键名 键名,如填:Ctrl键,将返回1，字母不区分大小写
//@别名   键盘_取功能键状态A(键名)
int X_Keyboard_GetFkeysStatusA(CXTextA keyName);

//@备注   取当前键盘的小键盘开关状态
//@返回   返回真为开,返回假则为关
//@别名   键盘_取小键盘状态()
bool X_Keyboard_GetKeypadStatus();

//@备注   向指定窗口句柄的窗口中发送按键消息(无返回值)
//@参数   窗口句柄 接收消息的窗口句柄
//@参数   键代码 按键的键代码
//@参数   状态 可空。默认为1  1=输入字符 2=1(废弃)  3=按下，4=放开，5=单击
//@参数   是否功能键状态 可空。默认为假：普通键   真:功能键 (为功能键可用于热键技能不输入字符)
//@别名   键盘_消息(窗口句柄,键代码,状态,是否功能键)
void X_Keyboard_Message(HWND hWnd, UINT key, int status=1, bool isFunc=false);

//@备注	模拟一个组合按键；如:Ctrl+A
//@参数	键代码 键代码；如：A(65)
//@参数	功能键码1 功能键代码；如：ctrl(1) 
//@参数	功能键码2 功能键代码(可以留空)
//@参数	功能键码3 功能键代码(可以留空)
//@别名	键盘_组合按键(键代码,功能键码1,功能键码2,功能键码3)
void X_Keyboard_CombinaCheck(UINT key, UINT fKey1, UINT fKey2=0, UINT fKey3 = 0);

//@备注	阻塞键盘及鼠标事件到达应用程序
//@参数	状态 真=锁定
//@别名	键鼠_锁定(状态)
BOOL X_Keyboard_LockAll(bool status);

//@分组}  键盘操作

//@分组{  鼠标操作

//@备注   取鼠标在屏幕中的坐标位置
//@别名   鼠标_取位置()
POINT X_Mouse_GetPOINT();

//@备注	模拟鼠标按键(无返回值)
//@参数	键 可空:为左键  1 左键   2 右键   3 中键
//@参数	控制 可空:为单击  1 单击   2 双击   3 按下  4 放开
//@别名	鼠标_按键(键,控制)
void X_Mouse_CKey(UINT key = 0, UINT control = 0);

//@别名	鼠标_带轨迹移动(起点坐标,终点坐标,移动速度,窗口句柄)
void X_Mouse_VisualMove(POINT pStart, POINT pEnd, int speed = 1, HWND hWnd = 0);

//@别名	鼠标_相对移动(坐标)
void X_Mouse_RelativeMove(POINT p);

//@别名	设置鼠标坐标
//@参数	窗口句柄 可空:相对桌面移动鼠标  句柄有效则相对窗口中坐标移动
//@参数	坐标 终点坐标 
//@别名	鼠标_移动(窗口句柄,坐标)
void X_Mouse_Move(HWND hWnd, POINT p);

//@别名	鼠标_单击(窗口句柄)
void X_Mouse_Click(HWND hWnd, POINT p, int type = 1);

//@备注	只能改自身程序的鼠标指针
//@参数	hWnd 要改鼠标的窗口句柄
//@参数	光标路径 鼠标文件名路径；支持动态鼠标
//@参数	光标指针 鼠标指针_
//@别名	鼠标_改指针(窗口句柄,光标路径,光标指针)
void X_Mouse_SetCursor(HWND hWnd, CXText sCursorPath=L"",LPWSTR Cursor=NULL);

//@备注	只能改自身程序的鼠标指针
//@参数	hWnd 要改鼠标的窗口句柄
//@参数	光标路径 鼠标文件名路径；支持动态鼠标
//@参数	光标指针 鼠标指针_
//@别名	鼠标_改指针A(窗口句柄,光标路径,光标指针)
void X_Mouse_SetCursorA(HWND hWnd, CXTextA sCursorPath = "", LPWSTR Cursor = NULL);

//@备注	记录当前鼠标坐标
//@别名	鼠标_记位()
POINT X_Mouse_MemoryPOINT();

//@备注	恢复当前鼠标坐标到"鼠标_记位"的坐标点或移动鼠标到指定点(无返回值)
//@别名	鼠标_归位()
void X_Mouse_Reset();

//@备注	锁定鼠标键(锁定后,鼠标键无效)
//@参数	锁定鼠标键(真:完全锁定鼠标 (可空为假) 假:锁定鼠标左右键)
//@别名	鼠标_锁定(状态)
void X_Mouse_Lock(bool status = false);

//@备注	鼠标键解锁(锁定鼠标键锁定后,用来恢复鼠标的使用)
//@别名	鼠标_解锁()
void X_Mouse_UnLock();

//@返回	鼠标当前在某个窗口上的坐标
//@参数	如果提供窗口句柄，将返回鼠标在该窗口上的坐标；否则将取出屏幕中的坐标
//@别名	鼠标_取窗口坐标()
POINT X_Mouse_GetWindowPoint(HWND hWnd=NULL);

//@备注	检索当前鼠标速度
//@别名	鼠标_取指针移动速度()
int  X_Mouse_GetMotionSpeed();

//@备注	设置当前鼠标速度
//@备注	速度值 1（最慢）和20（最快）
//@别名	鼠标_设置指针移动速度(速度值)
BOOL  X_Mouse_SetMotionSpeed(UINT num = 1);

//@备注	限制鼠标的活动范围
//@参数	左边 可空，为0
//@参数	顶边 可空，为0
//@参数	宽度 可空，为屏幕宽度-左边
//@参数	高度 可空，为屏幕高度-顶边
//@别名	鼠标_限制(左边,顶边,宽度,高度)
BOOL X_Mouse_RestrictedActivities(LONG left=0, LONG top=0, LONG width=0, LONG height=0);

//@别名	鼠标_解除限制()
BOOL X_Mouse_UnRestrictedActivities();


/*@声明

//@备注	捕获指定窗口的鼠标
//@别名	鼠标_捕获(窗口句柄)
HWND SetCapture(HWND hWnd);

//@别名	鼠标_释放()
BOOL ReleaseCapture();

//@备注	取鼠标双击间隔时间
//@别名	鼠标_取双击间隔时间()
UINT GetDoubleClickTime();

//@备注	设置鼠标指针的可视性,只能在自身窗口隐藏鼠标
//@参数	是否显示 真 = 显示；假 = 隐藏
//@别名	鼠标_显示隐藏(是否显示)
int ShowCursor(BOOL bShow);

//@备注	鼠标左右键交换
//@参数	是否交换 真=左右键交换；假=恢复
//@别名	鼠标_左右键交换(是否交换)
BOOL SwapMouseButton(BOOL fSwap);


*/

//@分组}  鼠标操作
//@分组{  常量

//@别名   键代码_0键
#define X_VK_0	0x30
//@别名   键代码_1键
#define X_VK_1	0x31
//@别名   键代码_2键
#define X_VK_2	0x32
//@别名   键代码_3键
#define X_VK_3	0x33
//@别名   键代码_4键
#define X_VK_4	0x34
//@别名   键代码_5键
#define X_VK_5	0x35
//@别名   键代码_6键
#define X_VK_6	0x36
//@别名   键代码_7键
#define X_VK_7	0x37
//@别名   键代码_8键
#define X_VK_8	0x38
//@别名   键代码_9键
#define X_VK_9	0x39
//@别名   键代码_A键
#define X_VK_A  0x41
//@别名   键代码_B键
#define X_VK_B  0x42
//@别名   键代码_C键
#define X_VK_C  0x43
//@别名   键代码_D键
#define X_VK_D  0x44
//@别名   键代码_E键
#define X_VK_E  0x45
//@别名   键代码_F键
#define X_VK_F  0x46
//@别名   键代码_G键
#define X_VK_G  0x47
//@别名   键代码_H键
#define X_VK_H  0x48
//@别名   键代码_I键
#define X_VK_I  0x49
//@别名   键代码_J键
#define X_VK_J  0x4A
//@别名   键代码_K键
#define X_VK_K  0x4B
//@别名   键代码_L键
#define X_VK_L  0x4C
//@别名   键代码_M键
#define X_VK_M  0x4D
//@别名   键代码_N键
#define X_VK_N  0x4E
//@别名   键代码_O键
#define X_VK_O  0x4F
//@别名   键代码_P键
#define X_VK_P  0x50
//@别名   键代码_Q键
#define X_VK_Q  0x51
//@别名   键代码_R键
#define X_VK_R  0x52
//@别名   键代码_S键
#define X_VK_S  0x53
//@别名   键代码_T键
#define X_VK_T  0x54
//@别名   键代码_U键
#define X_VK_U  0x55
//@别名   键代码_V键
#define X_VK_V  0x56
//@别名   键代码_W键
#define X_VK_W  0x57
//@别名   键代码_X键
#define X_VK_X  0x58
//@别名   键代码_Y键
#define X_VK_Y  0x59
//@别名   键代码_Z键
#define X_VK_Z  0x5A
//@别名   键代码_Win键左
#define X_VK_LWIN  0x5B
//@别名   键代码_Win键右
#define X_VK_RWIN  0x5C
//@别名   键代码_0键_小键盘
#define X_VK_NUMPAD0	0x60
//@别名   键代码_1键_小键盘
#define X_VK_NUMPAD1	0x61
//@别名   键代码_2键_小键盘
#define X_VK_NUMPAD2	0x62
//@别名   键代码_3键_小键盘
#define X_VK_NUMPAD3	0x63
//@别名   键代码_4键_小键盘
#define X_VK_NUMPAD4	0x64
//@别名   键代码_5键_小键盘
#define X_VK_NUMPAD5	0x65
//@别名   键代码_6键_小键盘
#define X_VK_NUMPAD6	0x66
//@别名   键代码_7键_小键盘
#define X_VK_NUMPAD7	0x67
//@别名   键代码_8键_小键盘
#define X_VK_NUMPAD8	0x68
//@别名   键代码_9键_小键盘
#define X_VK_NUMPAD9	0x69
//@别名   键代码_F1键
#define X_VK_F1  0x70
//@别名   键代码_F2键
#define X_VK_F2  0x71
//@别名   键代码_F3键
#define X_VK_F3  0x72
//@别名   键代码_F4键
#define X_VK_F4  0x73
//@别名   键代码_F5键
#define X_VK_F5  0x74
//@别名   键代码_F6键
#define X_VK_F6  0x75
//@别名   键代码_F7键
#define X_VK_F7  0x76
//@别名   键代码_F8键
#define X_VK_F8  0x77
//@别名   键代码_F9键
#define X_VK_F9  0x78
//@别名   键代码_F10键
#define X_VK_F10 0x79
//@别名   键代码_F11键
#define X_VK_F11 0x7A
//@别名   键代码_F12键
#define X_VK_F12 0x7B
//@别名   键代码_左Shift键
#define X_VK_LSHIFT  0xA0
//@别名   键代码_右Shift键
#define X_VK_RSHIFT  0xA1
//@别名   键代码_左Ctrl键
#define X_VK_LCONTROL 0xA2
//@别名   键代码_右Ctrl键
#define X_VK_RCONTROL 0xA3
//@别名   键代码_左Alt键
#define X_VK_LMENU 0xA4
//@别名   键代码_右Alt键
#define X_VK_RMENU 0xA5
//@别名   键代码_PageUp键
#define X_VK_PRIOR 0x21
//@别名   键代码_空格键
#define X_VK_SPACE 0x20
//@别名   键代码_Esc键
#define X_VK_ESCAPE 0x1B
//@别名   键代码_Enter键
#define X_VK_RETURN 0x0D
//@别名   键代码_Tab键
#define X_VK_TAB 0x09
//@别名   键代码_Shift键
#define X_VK_SHIFT 0x10 
//@别名   键代码_Ctrl键
#define X_VK_CONTROL 0x11
//@别名   键代码_Alt键
#define X_VK_MENU 0x12
//@别名   键代码_PageDown键
#define X_VK_NEXT 0x22
//@别名   键代码_Home键
#define X_VK_HOME 0x24
//@别名   键代码_向左键
#define X_VK_LEFT 0x25
//@别名   键代码_向上键
#define X_VK_UP  0x26
//@别名   键代码_向右键
#define X_VK_RIGHT 0x27
//@别名   键代码_向下键
#define X_VK_DOWN 0x28

/*@声明

//@备注   标准的箭头和小沙漏
//@别名   鼠标指针_APPSTARTING
#define IDC_APPSTARTING
//@备注   标准的箭头
//@别名   鼠标指针_标准型
#define IDC_ARROW
//@备注   十字光标
//@别名   鼠标指针_十字型
#define IDC_CROSS
//@备注   手型
//@别名   鼠标指针_手型
#define IDC_HAND
//@备注   箭头和问号
//@别名   鼠标指针_帮助
#define IDC_HELP
//@备注   文本编辑
//@别名   鼠标指针_文本编辑型
#define IDC_IBEAM
//@备注   禁止圈
//@别名   鼠标指针_禁止型
#define IDC_NO
//@备注   四向箭头指向东、西、南、北
//@别名   鼠标指针_四向箭头
#define IDC_SIZEALL
//@备注   双箭头指向东北和西南
//@别名   鼠标指针_SIZENESW
#define IDC_SIZENESW
//@备注   双箭头指向南北
//@别名   鼠标指针_SIZENS
#define IDC_SIZENS
//@备注   双箭头指向西北和东南
//@别名   鼠标指针_SIZENWSE
#define IDC_SIZENWSE
//@备注   双箭头指向西和东
//@别名   鼠标指针_SIZEWE
#define IDC_SIZEWE
//@备注   向上垂直箭头
//@别名   鼠标指针_UPARROW
#define IDC_UPARROW
//@备注   沙漏
//@别名   鼠标指针_沙漏型
#define IDC_WAIT

*/

//@分组}  常量



#endif //XL_XEXPAND_MOUSEKEY_H
