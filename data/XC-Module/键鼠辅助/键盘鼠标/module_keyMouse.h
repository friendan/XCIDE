#ifndef  XCL_KEY_MOUSE_H
//@隐藏{
#define  XCL_KEY_MOUSE_H
//@隐藏}

//@模块名称  键盘鼠标
//@版本  1.0  
//@日期  2023-12-17
//@作者  XCGUI  
//@模块备注 键盘鼠标操作模块
//虚拟键代码: https://learn.microsoft.com/zh-cn/windows/win32/inputdev/virtual-key-codes
// VK_0 - VK_9 与右边字符相同 ASCII '0' - '9' (0x30 - 0x39)
// 0x40 : 未使用
// VK_A - VK_Z 与右边字符相同 ASCII 'A' - 'Z' (0x41 - 0x5A)

//@依赖  module_base.h


//@分组{  接口

/*@声明

//@备注 检索指定虚拟键的状态。 状态指定键是向上、向下还是切换， (打开、关闭—每次按下键时交替) 。
//当线程从其消息队列读取密钥消息时，此函数返回的密钥状态会发生变化。 状态不反映与硬件关联的中断级别状态。 使用 GetAsyncKeyState 函数检索该信息。
//例如: Shift按下 if(0x800 & GetKeyState(VK_SHIFT))
//@参数 虚拟键码
//@返回 返回值指定虚拟键状态
//如果高阶位为 1，则键关闭; 否则，它已启动
//如果低序位为 1，则切换键。 如果某个键（如 CAPS LOCK 键）处于打开状态，则会将其切换。 如果低序位为 0，则键处于关闭状态并取消键。 切换键的指示灯 (，如果键盘上的任何) 在切换键时将亮起，在取消切换键时处于关闭状态。
SHORT WINAPI GetKeyState(__in int nVirtKey);

//@备注 确定调用函数时键是向上还是向下，以及上次调用 GetAsyncKeyState 后是否按下了该键。
//GetAsyncKeyState 函数适用于鼠标按钮。 但是，它会检查物理鼠标按钮的状态，而不是物理按钮映射到的逻辑鼠标按钮
//例如: Shift按下 if(0x800 & GetAsyncKeyState(VK_SHIFT))
//@参数 虚拟键码
//@返回 返回值指定虚拟键状态
SHORT WINAPI GetAsyncKeyState(__in int vKey);

//@备注 合成鼠标运动和按钮单击, MSDN:https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-mouse_event
//@参数 控制鼠标运动和按钮单击的各个方面。 此参数可以是以下值的某些组合。值参加MSDN
//@参数 x相对或绝对的移动量
//@参数 y相对或绝对的移动量
//@参数 如果有滚轮事件则代表滚轮的变化量，可正负，一圈为120(WHEEL_DELTA),如果没有滚轮事件，该值应当设为0
//@参数 给0就行; 与鼠标事件关联的附加值。 应用程序调用 GetMessageExtraInfo 以获取此额外信息。
VOID WINAPI mouse_event(__in DWORD dwFlags,	__in DWORD dx, __in DWORD dy, __in DWORD dwData, __in ULONG_PTR dwExtraInfo);

//@备注 合成键击。 系统可以使用这种合成的击键来生成 WM_KEYUP 或 WM_KEYDOWN 消息。 键盘驱动程序的中断处理程序调用 keybd_event 函数。
//keybd_event(VK_SHIFT,0,0,0);//按下Shift键
//keybd_event('A',0,0,0);//按下a键
//keybd_event('A',0,KEYEVENTF_KEYUP,0);//松开a键
//keybd_event(0x4B,MapVirtualKey(0x4B,0),0,0); // 按下
//Sleep(50);
//keybd_event(0x4B,MapVirtualKey(0x4B,0),KEYEVENTF_KEYUP,0); // 抬起
//@参数 虚拟键代码。 代码必须是 1 到 254 范围内的值
//@参数 键的硬件扫描代码。
//@参数 控制函数操作的各个方面。 此参数可使用以下一个或多个值
//KEYEVENTF_EXTENDEDKEY 0x0001 如果指定，则扫描代码前面有一个前缀字节，其值0xE0 (224) 。
//KEYEVENTF_KEYUP 0x0002 如果指定，则释放密钥。 如果未指定，则键被按下。
//@参数 与键笔划关联的附加值。
VOID WINAPI keybd_event(__in BYTE bVk, __in BYTE bScan, __in DWORD dwFlags, __in ULONG_PTR dwExtraInfo);


//@备注 将(映射)虚拟键代码转换为扫描代码或字符值，或将扫描代码转换为虚拟键代码。
//MSDN:https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-mapvirtualkeyw
//@参数 虚拟键码或扫描键的代码。 此值的解释方式取决于 uMapType 参数的值。
//@参数 要执行的转换。 此参数的值取决于 uCode 参数的值
//MAPVK_VK_TO_VSC  0	uCode 参数是一个虚拟键代码，并转换为扫描代码。 如果它是不区分左键和右键的虚拟键代码，则返回左侧扫描代码。 如果没有转换，则函数返回 0。
//MAPVK_VSC_TO_VK  1	uCode 参数是扫描代码，并转换为不区分左键和右键的虚拟键代码。 如果没有转换，则函数返回 0。
//MAPVK_VK_TO_CHAR 2	uCode 参数是一个虚拟键代码，在返回值的低序字中转换为未移位的字符值。 (音调符号) 的死键通过设置返回值的顶部位来指示。 如果没有转换，则函数返回 0。 请参阅“备注”。
//MAPVK_VSC_TO_VK_EX 3	uCode 参数是扫描代码，并转换为区分左键和右键的虚拟键代码。 如果没有转换，则函数返回 0。
//MAPVK_VK_TO_VSC_EX 4	Windows Vista 及更高版本：uCode 参数是一个虚拟键代码，并转换为扫描代码。 如果它是不区分左键和右键的虚拟键代码，则返回左侧扫描代码。 如果扫描代码是扩展扫描代码， 则 uCode 值的高字节可以包含指定扩展扫描代码0xe0或0xe1。 如果没有转换，则函数返回 0。
//@返回 返回值为扫描代码、虚拟键代码或字符值，具体取决于 uCode 和 uMapType 的值。 如果没有转换，则返回值为零。
//若要指定用于转换指定代码的键盘布局的句柄，请使用 MapVirtualKeyEx 函数。
UINT WINAPI MapVirtualKey(__in UINT uCode,	__in UINT uMapType);


//@备注 检索表示键的名称的字符串。
int WINAPI GetKeyNameText(__in LONG lParam, __out LPWSTR lpString,	__in int cchSize);

//@备注 合成键击、鼠标动作和按钮单击。
//@参数 pInputs-数组中的结构数。
//@参数 INPUT-结构的数组。 每个结构都表示要插入键盘或鼠标输入流的事件。类型为: INPUT_MOUSEINPUT 或 INPUT_MOUSEINPUT 或 INPUT_HARDWAREINPUT
//@参数 INPUT-结构的大小（以字节为单位）。 如果 cbSize 不是 INPUT 结构的大小，则函数将失败。
//@返回 函数返回成功插入键盘或鼠标输入流的事件数。 如果函数返回零，则表示输入已被另一个线程阻止
UINT WINAPI SendInput(__in UINT cInputs,__in INPUT* pInputs,  __in int cbSize); 

//@分组}


//@分组{  结构体

#define INPUT_MOUSE     0
#define INPUT_KEYBOARD  1
#define INPUT_HARDWARE  2
struct MOUSEINPUT {
	LONG    dx;
	LONG    dy;
	DWORD   mouseData;
	DWORD   dwFlags;
	DWORD   time;
	ULONG_PTR dwExtraInfo;
};

struct KEYBDINPUT {
	WORD    wVk;
	WORD    wScan;
	DWORD   dwFlags;
	DWORD   time;
	ULONG_PTR dwExtraInfo;
};

struct HARDWAREINPUT {
	DWORD   uMsg;
	WORD    wParamL;
	WORD    wParamH;
};

struct INPUT_MOUSEINPUT {
	DWORD   type;
	MOUSEINPUT      mi;
};
struct INPUT_KEYBDINPUT {
	DWORD   type;
	KEYBDINPUT      ki;
};
struct INPUT_HARDWAREINPUT {
	DWORD   type;
	HARDWAREINPUT   hi;
};

//@分组}

//@分组{  虚拟键码(见基础模块)


//@分组}

#endif //XC_BASE_H