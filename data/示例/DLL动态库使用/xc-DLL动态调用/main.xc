
//int add(int a, int b);
//#函数类型 整型(WINAPI *DLL中函数格式_相加1)(整型, 整型) //声明函数格式

def 调用DLL中函数_方式1()
	HMODULE  DLL模块句柄 = 动态库载入("xc-DLL导出def.dll")  //加载DLL
	
	//声明函数格式 可以写在函数外面, 也可以写在函数里面
	#函数类型 整型(WINAPI * DLL中函数格式_相加)(整型, 整型) //声明函数格式
	
	DLL中函数格式_相加 函数_相加 = (DLL中函数格式_相加)取函数地址(DLL模块句柄, A"dll_add") //取函数地址
	调试输出(函数_相加(1, 2)) //调用函数
	
	//中文函数名 需要转换编码
	函数_相加 = (DLL中函数格式_相加)取函数地址(DLL模块句柄, W2U("dll_add_中文名"))
	调试输出(函数_相加(1, 2))
	
	动态库释放(DLL模块句柄) //不使用了 释放DLL
	占位

//调用函数() 用法见文档
def 调用DLL中函数_方式2()
	HMODULE  DLL模块句柄 = 动态库载入("xc-DLL导出def.dll")  //加载DLL
	
	变整型 函数地址 = (变整型)取函数地址(DLL模块句柄, A"dll_add") //取函数地址
	调试输出(调用函数stdcall(函数地址, 1, 2))

	函数地址 = (变整型)取函数地址(DLL模块句柄, W2U("dll_add_中文名")) //中文函数名 需要转换编码
	调试输出(调用函数stdcall(函数地址, 1, 2))

	动态库释放(DLL模块句柄) //不使用了 释放DLL
	占位

函数 整型 入口函数_窗口()
	调用DLL中函数_方式1()
	调用DLL中函数_方式2()
	返回 0

//炫语言手册:   http://www.xcgui.com/doc/

//动态库入口函数参考: https://docs.microsoft.com/zh-cn/windows/win32/dlls/dllmain?redirectedfrom=MSDN

