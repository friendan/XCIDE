#ifndef TEST5_H
#define TEST5_H


// @参数  hRoot     [in] 主键句柄
// @参数  lpSubKey  [in] 子键路径字符串
// @参数  phkResult [out] 指向变量的指针，该变量接收打开或创建的键的句柄。如果该项不是预定义的注册表项之一，请在使用完句柄后调用 RegCloseKey 函数
// @返回  如果函数成功，则返回值ERROR_SUCCESS
// @别名  注册表_创建键(主键句柄, 子键路径字符串, 接收键句柄)
static LONG WINAPI XC_RegCreateKeyEx(HKEY hRoot, LPCWSTR pSubKey, PHKEY phkResult)
{
	return RegCreateKeyEx(hRoot, pSubKey, 0, NULL, 0, 0, NULL, phkResult, NULL);
}



//@模块名称  测试模块5 
//@版本  1.2.2
//@日期  2021-04-29
//@作者 
//@模块备注 

//@跳过   WNAPI,  WNAPI2  WNAPI3



extern "C"
{
	
	int  add1(int a);
	int  add2(int a);
	int  add3(int a);
}

extern "C" int  add5(int a);


static int testbytes(CXBytes ret)
{
	ret = L"123";
	return 0;
}



#endif
