
//DLL导入表, 降低动态调用DLL难度
//格式如下: [DLL名称, 编译方式C, 回调函数]
#DLL导入表["xc-DLL导出def.DLL", 编译方式C, DLL回调]   //指定DLL名称, 编译方式C, 可指定回调函数, 动态修改DLL路径
	函数 整型 WINAPI DLL_add(整型 参数1, 整型 参数2) : dll_add     //add 原始名称, 如果没有那么就没有别名
	函数 整型 WINAPI DLL_add_中文名(整型 参数1, 整型 参数2) : dll_add_中文名

函数  文本型  DLL回调(文本型 路径)
	//可在此处修改DLL文件路径
	返回  路径

函数 整型 入口函数_窗口()

	整型  ret = DLL_add(1, 3)
	调试输出2("返回值=", ret)
	
	ret = DLL_add_中文名(1, 3)
	调试输出2("返回值=", ret)
	返回 0

//炫语言手册:   http://www.xcgui.com/doc/
//动态库入口函数参考: https://docs.microsoft.com/zh-cn/windows/win32/dlls/dllmain?redirectedfrom=MSDN