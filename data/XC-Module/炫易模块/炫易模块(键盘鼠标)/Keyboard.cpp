//
// Created by Huiyi on 2021/5/26.
//
#include "module_e_MouseKey.h"

//键盘_单击
void X_Keyboard_Onclick(BYTE key, int type) {
	if(type==1){
		keybd_event(key, 0, 0, 0);
	}
	else if (type ==2) {
		keybd_event(key, 0, 2, 0);
	}
	else {
		keybd_event(key, 0, 0, 0);
		xcl_doMessage();//X_System_DoEvents();
		keybd_event(key, 0, 2, 0);
	}
}

//键盘_键代码取键名
CXText X_Keyboard_GetName(BYTE key) {
	UINT kcode = key;
	UINT scanCode = MapVirtualKeyW(kcode, MAPVK_VK_TO_VSC);
	if((kcode>32&& kcode <41) 
		|| (kcode > 45 && kcode < 46)
		|| kcode==111
		|| kcode== 144){
		scanCode = scanCode | 256;
	}
	wchar_t szString[256];
	GetKeyNameTextW(scanCode<<16, szString, 256);
	return szString;
}
//键盘_键代码取键名A
CXTextA X_Keyboard_GetNameA(BYTE key) {
	UINT kcode = key;
	UINT scanCode = MapVirtualKeyA(kcode, MAPVK_VK_TO_VSC);
	if ((kcode > 32 && kcode < 41)
		|| (kcode > 45 && kcode < 46)
		|| kcode == 111
		|| kcode == 144) {
		scanCode = scanCode | 256;
	}
	char szString[256];
	GetKeyNameTextA(scanCode << 16, szString, 256);
	return szString;
}

HHOOK hKeyboardHooklu = NULL;
bool bKeyboardHookluStatus = false;
LRESULT KeyboardHooklu(
	int nCode,
	WPARAM wParam,
	LPARAM lParam){
	if (nCode == NULL) {
		PMSG msg= (PMSG)wParam;
		if (bKeyboardHookluStatus) { return 1; }
		int key = (int)msg->hwnd;
		if (key == X_VK_ESCAPE || 
			key == X_VK_TAB ||
			key == X_VK_F4) {
			return 1;
		}
		else if (key == 44 ||
			key == 145 ||
			key == 19) {
			return 1;
		}
		else if (key == 91 ||
			key == 92 ||
			key == 93) {
			return 1;
		}
		else if (key > 159 && key<166) {
			return 1;
		}
		return 0;
	}
	return CallNextHookEx(hKeyboardHooklu,nCode, wParam, lParam);
}
//键盘_锁定
void X_Keyboard_Lock(bool status) {
	if (hKeyboardHooklu != NULL) {
		UnhookWindowsHookEx(hKeyboardHooklu);
	}
	bKeyboardHookluStatus = status;
	hKeyboardHooklu = SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)KeyboardHooklu, (HINSTANCE)GetModuleHandleA(NULL),NULL);
	xcl_log(hKeyboardHooklu);
}
//键盘_解锁
void X_Keyboard_UnLock() {
	if (hKeyboardHooklu != NULL) {
		UnhookWindowsHookEx(hKeyboardHooklu);
		hKeyboardHooklu = NULL;
	}

}

//键盘_取大小写状态
bool X_Keyboard_IfisUppercase() {
	return GetKeyState(20)>0;
}

//键盘_取功能键名
CXText X_Keyboard_GetFkeysName(int fkeyStat) {
	const wchar_t* fns[] = {L"Ctrl键",L"Shift键",L"Ctrl键+Shift键",L"Alt键",L"Ctrl键+Alt键",L"Shift键+Alt键",L"Ctrl键+Shift键+Alt键"};
	CXText keyName = L"";
	if (fkeyStat>0 && fkeyStat<8) {
		keyName = fns[fkeyStat - 1];
	}
	return keyName;
}
//键盘_取功能键名A
CXTextA X_Keyboard_GetFkeysNameA(int fkeyStat){
	const char* fns[] = { "Ctrl键","Shift键","Ctrl键+Shift键","Alt键","Ctrl键+Alt键","Shift键+Alt键","Ctrl键+Shift键+Alt键" };
	CXTextA keyName = "";
	if (fkeyStat > 0 && fkeyStat < 8) {
		keyName = fns[fkeyStat - 1];
	}
	return keyName;
}

//键盘_取功能键状态
int X_Keyboard_GetFkeysStatus(CXText keyName) {
	int a = keyName.find(L"Ctrl键")==-1?0:1;
	int b = keyName.find(L"Shift键")==-1?0:2;
	int c = keyName.find(L"Alt键")==-1?0:4;
	return a + b + c;
}
//键盘_取功能键状态
int X_Keyboard_GetFkeysStatusA(CXTextA keyName) {
	int a = keyName.find("Ctrl键") == -1 ? 0 : 1;
	int b = keyName.find("Shift键") == -1 ? 0 : 2;
	int c = keyName.find("Alt键") == -1 ? 0 : 4;
	return a + b + c;
}

//键盘_取小键盘状态
bool X_Keyboard_GetKeypadStatus() {
	return GetKeyState(144)>0;
}

//生成键盘消息lParam
DWORD X_Keyboard_GenerateMessagelParam(
	short int RepeatCount,
	UINT scCode,
	bool isFunc,
	bool bContext,
	bool lastStatus,
	bool TransitionalState) {
	DWORD ret = scCode << 16;
	ret = ret | RepeatCount;
	if (isFunc) {
		ret |= 1 << 24;
	}
	if (bContext) {
		ret |= 1 << 29;
	}
	if (lastStatus) {
		ret |= 1 << 30;
	}
	if (TransitionalState) {
		ret |= 1 << 31;
	}
	return ret;
};

//键盘_消息
void X_Keyboard_Message(HWND hWnd,UINT key,int status,bool isFunc) {
	UINT uMsg = 0;
	UINT nScan = 0;
	DWORD lParam = 0;
	if(status == 3){//按下
		uMsg = isFunc ? WM_SYSKEYDOWN : WM_KEYDOWN;
		nScan = MapVirtualKeyA(key, MAPVK_VK_TO_VSC);
		lParam = X_Keyboard_GenerateMessagelParam(1, nScan, isFunc, false, false, false);
		PostMessageW(hWnd, uMsg, key, lParam);
	}
	else if (status == 4) {//放开
		uMsg = isFunc ? WM_SYSKEYUP:WM_KEYUP;
		nScan = MapVirtualKeyA(key, MAPVK_VK_TO_VSC);
		lParam = X_Keyboard_GenerateMessagelParam(1, nScan, isFunc, false, true, true);
		PostMessageW(hWnd, uMsg, key, lParam);
	}
	else if (status == 5) {//单击 => 按下 + 放开
		X_Keyboard_Message(hWnd, key, 3, isFunc);
		X_Keyboard_Message(hWnd, key, 4, isFunc);
	}
	else {
		if (key==58 || key == 59) {
			nScan = MapVirtualKeyA(VK_OEM_1, MAPVK_VK_TO_VSC);
		}
		else if (key == 43) {
			nScan = MapVirtualKeyA(VK_OEM_PLUS, MAPVK_VK_TO_VSC);
		}
		else if (key == 44) {
			nScan = MapVirtualKeyA(VK_OEM_COMMA, MAPVK_VK_TO_VSC);
		}
		else if (key == 45) {
			nScan = MapVirtualKeyA(VK_OEM_MINUS, MAPVK_VK_TO_VSC);
		}
		else if (key == 46) {
			nScan = MapVirtualKeyA(VK_OEM_PERIOD, MAPVK_VK_TO_VSC);
		}
		else if (key == 47 || key == 63) {
			nScan = MapVirtualKeyA(VK_OEM_2, MAPVK_VK_TO_VSC);
		}
		else if (key == 96 || key == 126) {
			nScan = MapVirtualKeyA(VK_OEM_3, MAPVK_VK_TO_VSC);
		}
		else if (key >= 97 && key <= 122) {
			nScan = MapVirtualKeyA(key - 32, MAPVK_VK_TO_VSC);
		}
		else {
			nScan = MapVirtualKeyA(key, MAPVK_VK_TO_VSC);
		}
		lParam = X_Keyboard_GenerateMessagelParam(1, nScan, isFunc, false, false, false);
		PostMessageW(hWnd, WM_CHAR, key, lParam);
	}
}

//键盘_组合按键
void X_Keyboard_CombinaCheck(UINT key, UINT fKey1, UINT fKey2, UINT fKey3) {
	if (!fKey3) {
		keybd_event(fKey3, 0, 0, 0);
	}
	if (!fKey2) {
		keybd_event(fKey2, 0, 0, 0);
	}
	keybd_event(fKey1, 0, 0, 0);
	keybd_event(key, 0, 0, 0);
	if (!fKey3) {
		keybd_event(fKey3, 0, 2, 0);
	}
	if (!fKey2) {
		keybd_event(fKey2, 0, 2, 0);
	}
	keybd_event(fKey1, 0, 2, 0);
	keybd_event(key, 0, 2, 0);
}

//键鼠_锁定
BOOL X_Keyboard_LockAll(bool status) {
	return BlockInput(status);
}



