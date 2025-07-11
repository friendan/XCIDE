//
// Created by Huiyi on 2022/10/08.
//
#include "module_e_MouseKey.h"

//鼠标_取位置
POINT X_Mouse_GetPOINT() {
	POINT r;
	GetCursorPos(&r);
	return r;
}

//鼠标_按键
void X_Mouse_CKey(UINT key,UINT control) {
	int iea = 0;
	int ieb = 0;
	if(key==1 || key==0){
		iea = 2;
		ieb = 4;
	}
	else if (key==3) {
		iea = 32;
		ieb = 64;
	}
	else if (key == 2) {
		iea =8;
		ieb = 16;
	}
	if (iea == 0 || ieb == 0) { return; }
	if (control == 3) {
		mouse_event(iea, 0, 0, 0, 0);
	}
	if (control == 4) {
		mouse_event(iea, 0, 0, 0, 0);
	}
	if (control == 1 || control == 0) {
		mouse_event(iea, 0, 0, 0, 0);
		mouse_event(ieb, 0, 0, 0, 0);
	}
	if (control == 2) {
		mouse_event(iea, 0, 0, 0, 0);
		mouse_event(ieb, 0, 0, 0, 0);
		Sleep(GetDoubleClickTime()); //X_Program_Sleep(GetDoubleClickTime());
		mouse_event(iea, 0, 0, 0, 0);
		mouse_event(ieb, 0, 0, 0, 0);
	}
}

//鼠标_带轨迹移动
void X_Mouse_VisualMove(POINT pStart, POINT pEnd, int speed, HWND hWnd) {
	POINT ps = pStart;
	POINT pe = pEnd;
	if (hWnd) {
		POINT lpoint = {0};
		ClientToScreen(hWnd, &lpoint);
		pe.x += lpoint.x;
		pe.y += lpoint.y;
	}
	speed = speed <= 0 ? 1: speed;
	bool l_while=false;
	SetCursorPos(ps.x, ps.y);
	while (!l_while) {
		POINT lpxy = {0};
		ps = X_Mouse_GetPOINT();
		if (pe.x> ps.x) {
			lpxy.x = 1;
		}
		if (pe.x < ps.x) {
			lpxy.x = -1;
		}
		if (pe.x == ps.x) {
			lpxy.x = 0;
		}
		if (pe.y > ps.y) {
			lpxy.y = 1;
		}
		if (pe.y < ps.y) {
			lpxy.y = -1;
		}
		if (pe.y == ps.y) {
			lpxy.y = 0;
		}
		X_Mouse_RelativeMove(lpxy);
		if (ps.x==pe.x && ps.y == pe.y) {
			l_while = true;
		}
		Sleep(speed);//X_Program_Sleep(speed);
		//X_System_DoEvents();
		xcl_doMessage();
	}
}

//鼠标_相对移动
void X_Mouse_RelativeMove(POINT p) {
	POINT l=X_Mouse_GetPOINT();
	SetCursorPos(l.x+p.x,l.y+p.y);
}

//鼠标_移动
void X_Mouse_Move(HWND hWnd,POINT p) {
	POINT l = { 0,0 };
	if (hWnd) { ClientToScreen(hWnd, &l); }
	SetCursorPos(p.x + l.x, p.y +l.y);
}

//鼠标_单击
void X_Mouse_Click(HWND hWnd,POINT p,int type ) {
	POINT l = X_Mouse_GetPOINT();
	if (type>0 && type<4) {
		int tags[] = {6, 24, 3};
		int tag = tags[type - 1];
		X_Mouse_Move(hWnd, p);
		mouse_event(tag, p.x, p.y, 0, 0);
		X_Mouse_Move(0, l);
	}
}

//鼠标_改指针
void X_Mouse_SetCursor(HWND hWnd, CXText sCursorPath, LPWSTR Cursor) {
	HCURSOR L = NULL;
	if (lstrcmpW(sCursorPath, L"")) {
		L = LoadCursorFromFileW(sCursorPath);
	}
	else {
		L = LoadCursorW(0, Cursor);
	}
	SetClassLongPtrW(hWnd, (-12), (LONG_PTR)L);
}
//鼠标_改指针A
void X_Mouse_SetCursorA(HWND hWnd, CXTextA sCursorPath, LPWSTR Cursor) {
	HCURSOR L = NULL;
	if (strcmp(sCursorPath, "")) {
		L = LoadCursorFromFileA(sCursorPath);
	}
	else {
		L = LoadCursorW(0, (LPWSTR)Cursor);
	}
	SetClassLongPtrA(hWnd, (-12), (LONG_PTR)L);
}
POINT m_MemoryP = { 0,0 };
//鼠标_记位
POINT X_Mouse_MemoryPOINT() {
	m_MemoryP = X_Mouse_GetPOINT();
	return m_MemoryP;
}
//鼠标_归位
void X_Mouse_Reset() {
	X_Mouse_Move(NULL, m_MemoryP);
}
bool  m_bstatus = false;
HHOOK m_pMouseHook=NULL;
LRESULT MouseHooklu(
	int nCode,
	WPARAM wParam,
	LPARAM lParam) {
	if(m_bstatus){
		return 1;
	}
	if (wParam>=513 && wParam<=515) {//鼠标左键按下,鼠标左键放开,鼠标左键双击
		return 1;
	}
	if (wParam >= 516 && wParam <= 518) {//鼠标右键按下,鼠标右键放开,鼠标右键双击
		return 1;
	}
	return CallNextHookEx(m_pMouseHook, nCode, wParam, lParam);
}

//鼠标_锁定
void X_Mouse_Lock(bool status) {
	X_Mouse_UnLock();
	m_bstatus = status;
	m_pMouseHook = SetWindowsHookExA(WH_MOUSE_LL, (HOOKPROC)MouseHooklu, GetModuleHandleA(0), 0); // 载入鼠标钩子
}

//鼠标_解锁
void X_Mouse_UnLock(){
	if (m_pMouseHook!=nullptr) {
		UnhookWindowsHookEx(m_pMouseHook);
		m_pMouseHook = NULL;
	}	
}

POINT GetControlPoint(HWND hWnd) {
	HWND lwnd = (hWnd == 0) ? GetFocus() : hWnd;
	POINT r = { 0,0 };
	ClientToScreen(lwnd, &r);
	return r;
}

//鼠标_取窗口坐标
POINT X_Mouse_GetWindowPoint(HWND hWnd) {
	POINT p1={0},mp = { 0 };
	if(hWnd){
		p1 = GetControlPoint(hWnd);
	}
	GetCursorPos(&mp);
	mp.x = mp.x - p1.x;
	mp.y = mp.y - p1.y;
	return mp; 
}

//鼠标_取指针移动速度
int  X_Mouse_GetMotionSpeed() {
	int iMouseSpeed;
	SystemParametersInfoW(SPI_GETMOUSESPEED, 0, &iMouseSpeed, 0);
	return  iMouseSpeed; 
}

//鼠标_设置指针移动速度
BOOL  X_Mouse_SetMotionSpeed(UINT num) {
	return SystemParametersInfoW(SPI_SETMOUSESPEED, 0, &num, SPIF_UPDATEINIFILE|SPIF_SENDCHANGE);
}

//鼠标_限制
BOOL X_Mouse_RestrictedActivities(LONG left, LONG top, LONG width, LONG height) {
	RECT rect={ left ,top,0,0 };
	if (!width) {
		int sw = GetSystemMetrics(SM_CXSCREEN);
		rect.right = sw- left;
	}
	else {
		rect.right = width + left;
	}
	if (!height) {
		int sh = GetSystemMetrics(SM_CYSCREEN);
		rect.bottom = sh - height;
	}
	else {
		rect.bottom = height + top;
	}
	return ClipCursor(&rect);
}
//鼠标_解除限制
BOOL X_Mouse_UnRestrictedActivities() {
	return ClipCursor(NULL); 
}
