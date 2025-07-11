
#pragma once

//typedef int (FAR WINAPI *pDD_btn)(int btn);
//typedef int (FAR WINAPI *pDD_whl)(int whl);
//typedef int (FAR WINAPI *pDD_key)(int keycode,int flag);
//typedef int (FAR WINAPI *pDD_mov)( int x,int y);
//typedef int (FAR WINAPI *pDD_str)(PCHAR str);
//typedef int (FAR WINAPI *pDD_todc)(int vk);
//typedef int (FAR WINAPI *pDD_movR)( int dx,int dy);

//下面的写法是为了 兼容dll的声明方式
typedef int(*pDD_btn)(int btn);
typedef int(*pDD_whl)(int whl);
typedef int(*pDD_key)(int keycode, int flag);
typedef int(*pDD_mov)(int x, int y);
typedef int(*pDD_str)(char *str);
typedef int(*pDD_todc)(int vk);
typedef int(*pDD_movR)(int dx, int dy);

class CDD 
{
	
public:
	CDD(void);
	~CDD(void);
public:
	pDD_btn      DD2_btn ;        //Mouse button
	pDD_whl      DD2_whl ;		 //Mouse wheel
	pDD_key      DD2_key ;		 //Keyboard
	pDD_mov    DD2_mov ;		 //Mouse move abs.
	pDD_str       DD2_str;			 //Input visible char
	pDD_todc    DD2_todc;		 //VK to ddcode
	pDD_movR   DD2_movR ;	 //Mouse move rel.


public:
	HMODULE m_hModule ;//HINSTANCE m_hModule  这个不需要在外部调用语言中公开 
	int init(const wchar_t *dllfile);

//下面这些函数之所以要套一层,是为了炫语言能识别出这些是函数
// 火山中 可以直间用嵌入方式封装到火山格式	
//Mouse button
int DD_btn(int x);


//Mouse wheel
int DD_whl(int x);


//模拟键盘按键
void DD_key(int x,int y);


//鼠标绝对移动
int DD_mov(int x,int y);


//鼠标增量移动
int DD_movR(int x,int y);


//直接输入键盘上可见字符和空格Input visible char
int DD_str(char * x);


////VK to ddcode
int DD_todc(int x);


};