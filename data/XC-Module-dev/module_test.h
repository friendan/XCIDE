#pragma once

#ifdef  XC_MOUDLE
#endif

//@模块名称  示例模块1
//@版本  1.0  
//@日期  2020-11-20
//@作者  XCGUI  
//@模块备注  这是一个示例模块


//@分组{ 全局变量

//@备注  测试全局变量
//@别名  全局变量_var
static int  test_var=10;

CXMap < std::wstring , int >  g_map1;
CXVector < std::wstring>  g_vector1;
int   array[100]={0};
//@分组}


//@分组{  函数类型定义

typedef int (__cdecl*fun_test)(int,int);
typedef int (__stdcall*fun_test2)(int,int);

//@分组}
//@分组{  分组1

//@备注  我是备注
// 我是备注换行
//@参数  参数1说明
//@参数  参数2说明
//@返回值  返回值说明
//@别名  测试_函数_别名(参数1, 参数2)
int Test_abc123(int a, int b)
{
	return a+b;
}

void Test_void2(void)
{
	return ;
}
void Test_void3(void* cc)
{
	return ;
}
//@分组}


//@分组{  与C++类型混合测试
CXMap < std::wstring , int > Test_get_map()
{
	CXMap<std::wstring, int>  ret_map;
	ret_map[L"aaa"] =1;
	ret_map[L"bbb"]=2;
	ret_map[L"ccc"]=3;
	return ret_map;
}

CXVector < std::wstring > Test_get_vector()
{
	CXVector<std::wstring>  ret_vector;
	ret_vector.add(L"111");
	ret_vector.add(L"222");
	ret_vector.add(L"333");
	return ret_vector;
}

static int* Test_map1(CXMap<std::wstring, int>* ret_map)
{
	OutputDebugString(L"call->Test_map1()\n");
}

static int* Test_map2(CXMap<std::string, int>* ret_map)
{
	OutputDebugString(L"call->Test_map2()\n");
}

static void Test_map(CXMap<std::wstring, int>& ret_map)
{
	ret_map[L"aaa"] =1;
	ret_map[L"bbb"]=2;
	ret_map[L"ccc"]=3;
}

static void Test_vector(CXVector<std::wstring>& ret_vector)
{
	OutputDebugString(L"call->Test_vector()\n");
	ret_vector.add(L"aaa");
	ret_vector.add(L"bbb");
	ret_vector.add(L"ccc");
}

static void Test_string(std::string& ret)
{
	OutputDebugString(L"call->Test_string()\n");
	ret = "Test_string()";
}
static void Test_wstring(std::wstring& ret)
{
	OutputDebugString(L"call->Test_wstring()\n");
	ret = L"Test_wstring()";
}
//@分组}

//COLORREF tts3(unsigned int aa, LPSTR a, LPCTSTR  b, LPWSTR c, size_t d,  LONG  e,unsigned int  f,  PDWORD_PTR g, LPCVOID h);


//@分组{ 宏定义
	
//@备注  测试备注
//@别名  测试别名
#define  SW_SSAA  123

//@备注  测试备注1
//测试备注2
//测试备注3
//测试备注4
#define  SW_SSAA2  123

//@分组}
	

//@分组{ 枚举
//@备注  枚举备注1
//@别名  枚举类型别名1
enum myss_aa_123{
	
//@备注  枚举备注2
//@别名  枚举别名2
	myss_aa1=0,

//@备注  枚举备注3
//@别名  枚举别名3	
	myss_aa2=10,
	
	myss_aa3= myss_aa1 + myss_aa2,
	myss_aa4= myss_aa1 | myss_aa2,
	myss_aa5 = myss_aa1 & myss_aa2,
	myss_aa6 = (myss_aa2 | myss_aa2),
};

//@启用枚举前缀

//@别名  测试枚举1
enum my_enmu_test1{
	//@别名  成功
	my_enmu_test1_ok,
	//@别名  失败
	my_enmu_test1_faile,
};

//@禁用枚举前缀

//@别名  测试枚举2
enum my_enmu_test2{
	//@别名  成功
	my_enmu_test2_ok,
	//@别名  失败
	my_enmu_test2_faile,
};

//@分组}


extern "C" BOOL __stdcall _fmt_const_123 (int const,int consts,int values,int nCount);

extern "C" BOOL __stdcall xx_Init_123 (int hInstance,int dwGlobalFlags,int hDefaultCursor,int lpszDefaultClassName,int lpDefaultTheme,int dwDefaultThemeLen,int lpDefaultI18N,int dwDefaultI18NLen);


//@参数  a, 整型
//123
//456
//@参数  f  函数指针
int sqlite3_exec_123(char const **a, int (*f)(char**));

int sqlite3_exec_1234(char const **a, int (*)(char**, int));


/*@声明

@分组{  声明_已实现的外部接口

@备注  我是备注  在@声明内部可以省略 注释符号"\\"
@参数  参数1说明
@参数  参数2说明
@返回值  返回值说明
@别名   声明_已存在的函数(参数a, 参数b)
int  fun_test5786(int a, int b);

@分组}

*/


