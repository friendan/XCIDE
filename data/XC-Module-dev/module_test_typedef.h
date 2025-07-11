#pragma once

#ifdef  XC_MOUDLE
#endif

//@模块名称  测试模块4
//@版本  1.0
//@日期  2022-03-02
//@作者  XCGUI  
//@模块备注  这是一个测试模块


 int  test_var1 = 10 //123
 , test_var2 = 20 ;


#ifndef XC_API
#define  XC_API extern "C"
#endif

typedef struct myst myst;
typedef struct lua_Debug lua_Debug;

class CA222;
class CA222* ca_;


XC_API  int  add();

//extern "C" XLAPI IBookT* XLAPIENTRY xlCreateXMLBookW();


class CA222
{
public:
	int  m_a;
	int  add(int a, int b)
	{
		return a+b;
	}
	int  add2(int a, int b);
};



//@分组{ 定义变量
int      int_a;
int      int_b=100;
int*     int_ptr;
RECT*    rect_ptr;
CXMap<int, int>         map_1;
CXVector<int>           vector_1;
//@分组}

//@分组{ 类型定义
typedef  int                  typedef_int;
typedef  int*                 typedef_int_ptr;
typedef  RECT*                typedef_rect_ptr;
typedef  CXMap<int, int>      typedef_map;
typedef  CXVector<int>        typedef_vector;


typedef struct lua_State     lua_State;
typedef struct struct_lua_   typedef_struct_lua_;
//typedef RECT          typedef_struct_rect;
//typedef RECT*         typedef_struct_rect_ptr;
//@分组}



//@分组{  函数类型

//测试函数类型
//需要区分 [函数类型] 与 [函数类型指针]
//作为指针才可以调用函数

typedef int f(int);
typedef int __stdcall f2(int);
typedef int* __stdcall f3(int);

typedef int (f4)(int);
typedef int (*f5)(int);
typedef int (__stdcall f6)(int);
typedef int (__stdcall *f7)(int);
typedef int* (__stdcall *f8)(int);
//@分组}


//@分组{ 函数参数-匿名函数
//匿名函数类型, 当为函数参数时, 否则跳过解析
int  funArg1( int  (*)(char*) );
int  funArg2( int  (*f)(char*) );
//int  funArg3( int  (f)(char*) );
int  funArg4( int  (__stdcall)(char*) );
int  funArg5( int  (__stdcall *)(char*) );
int  funArg6( int* (__stdcall *f)(char*) );
//@分组}

//@分组{  函数
int  fun();
int* fun2(int a, int b);
int* WINAPI fun3();
CXMap<int, char> WINAPI fun4();

//virtual int WINAPI funv1();
//virtual int WINAPI funv2() const = 0;
//@分组}
