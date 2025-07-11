#pragma once

#ifdef  XC_MOUDLE
#endif

//@模块名称  简单外部函数声明示例
//@版本  1.0  
//@日期  2020-11-20
//@作者  XCGUI  
//@模块备注  这是一个示例模块


//对于已存在的函数需注释起来, 不然会造成重复, 例如系统API, 例如下面示例:


/*@声明  

@备注  测试简易模块函数
@ 测试简易模块函数
@参数  参数1参数说明
@参数  参数2参数说明
@返回  返回a+b
@别名  测试函数名a(参数a, 参数b)
int  test_a(int a, int b);


@备注  测试简易模块函数b
@ 测试简易模块函数b
@参数  参数1参数说明
@参数  参数2参数说明
@返回  返回a+b
@别名  测试函数名b(参数a, 参数b)
int  test_b(int a, int b);

*/


//--------------------------------------------------------------
//声明DLL中的函数:

//下面宏判断 x64 或 x86 加载不同的lib

#ifdef  _WIN64
//@lib "xcgui.lib"
#else
//@lib "xcgui_64.lib"
#endif

//@备注 获取元素ID
//@参数 hXCGUI 对象句柄
//@返回 返回元素ID.
//@别名 窗口组件_取ID(对象句柄)
extern "C" int WINAPI XWidget_GetID(HXCGUI hXCGUI);
	


//extern "C": 声明是一个C函数