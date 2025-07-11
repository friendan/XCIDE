//#include "StdAfx.h"  //vs中需要引入这一行代码
#include "module_DD.h"

CDD::CDD(void) //构造函数
{
	m_hModule = NULL;
}

CDD::~CDD(void) //析造函数
{
	if (m_hModule)
	{
		::FreeLibrary(m_hModule);
	}
}

int CDD::init(const wchar_t *dllfile)//DWORD 进程名取ID(const wchar_t *进程名);
{
	
	m_hModule = ::LoadLibraryW(dllfile);

	if ( m_hModule==NULL)
	{
		return -12; 
	}

	DD2_btn = (pDD_btn )GetProcAddress(m_hModule,"DD_btn"); 
	DD2_whl = (pDD_whl )GetProcAddress(m_hModule,"DD_whl"); 
	DD2_key = (pDD_key )GetProcAddress(m_hModule,"DD_key"); 
	DD2_mov = (pDD_mov)GetProcAddress(m_hModule,"DD_mov"); 
	DD2_str  = (pDD_str)GetProcAddress(m_hModule,"DD_str"); 
	DD2_todc  = (pDD_todc)GetProcAddress(m_hModule,"DD_todc"); 
	DD2_movR = (pDD_movR)GetProcAddress(m_hModule,"DD_movR"); 

	if ( DD2_btn && DD2_whl && DD2_key && DD2_mov && DD2_str  && DD2_todc && DD2_movR)
	{
		return DD2_btn(0); //初始化成功返回1
	}
	else
	{
		return -13;
	}
}

//下面这些函数之所以要套一层,是为了炫语言能识别出这些是函数
// 火山中 可以直间用嵌入方式封装到火山格式
//Mouse button
int CDD::DD_btn(int x)
 {
	return DD2_btn(x);
	
	
}

//Mouse wheel
int CDD::DD_whl(int x)
{
	return DD2_whl(x);
	
	
}

//模拟键盘按键
void CDD::DD_key(int x,int y)
{
	DD2_key(x,y);
	
	
}

//鼠标绝对移动
int CDD::DD_mov(int x,int y)
{
	return DD2_mov(x,y);
	
	
}

//鼠标增量移动
int CDD::DD_movR(int x,int y)
{
	return DD2_movR(x,y);
	
	
}

//直接输入键盘上可见字符和空格Input visible char
int CDD::DD_str(char * x)
{
	return DD2_str(x);
	
	
}

////VK to ddcode
int CDD::DD_todc(int x)
{
	return DD2_todc(x);
	
	
}