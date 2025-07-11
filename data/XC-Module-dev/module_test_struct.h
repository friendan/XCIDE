#pragma once

#ifdef  XC_MOUDLE
#endif

//@模块名称  示例模块_结构体
//@版本  1.0  
//@日期  2020-11-20
//@作者  XCGUI  
//@模块备注  这是一个测试模块\


//@别名  矩形123
class CRect123
//@隐藏{
: public RECT
//@隐藏}
{
	//@别名 添加()
	void Add(){}
};

typedef struct tagSt
{
	char struct_id[4];
	int  struct_version;
} st1, st2, *st3;


typedef  RECT RECT2;

struct tagABC
{
	char struct_id[4];
	int  struct_version;
};


