//导出函数格式为: extern "C" int WINAPI dll_add(int a, int b)
//导出名称为: dll_add
函数 编译方式C 导出 整型 WINAPI dll_add(整型 a, 整型 b)
	返回 a + b

//导出函数格式为: extern "C" int WINAPI dll_add_中文名(int a, int b)
//导出名称为: dll_add_中文名, 中文名称为UTF8编码, 所以直接看是乱码
函数 编译方式C 导出 整型 WINAPI dll_add_中文名(整型 a, 整型 b)
	返回 a + b

//通过def文件导出函数
//项目设置->常规->自动生成DEF文件

函数 整型 入口函数_动态库()
	调试输出("动态库程序", 模块句柄)

	如果 DLL_进程附加 == 被调用原因
		调试输出("DLL_进程附加")
	否则 DLL_线程附加 == 被调用原因
		调试输出("DLL_线程附加")
	否则 DLL_线程分离 == 被调用原因
		调试输出("DLL_线程分离")
	否则 DLL_进程分离 == 被调用原因
		调试输出("DLL_进程分离")
	返回 真 //成功返回真


//动态库入口函数参考
//https://docs.microsoft.com/zh-cn/windows/win32/dlls/dllmain?redirectedfrom=MSDN