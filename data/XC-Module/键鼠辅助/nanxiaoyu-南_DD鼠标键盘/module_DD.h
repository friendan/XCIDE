// Created by  南小鱼封装 (QQ 128492656)
//
//下面是定义显示的模块名称
//@模块名称  南_DD鼠标键盘
//@版本  0.1
//@日期  2023-03-13
//@作者  南小鱼 (QQ 128492656) 封装 
//@模块备注  封装免费项目DD虚拟键盘鼠标
// 项目地址 https://github.com/ddxoft/master
// 帮助网页 http://www.ddxoft.com/help/
// 普通游戏和桌面操作自动化，所有鼠标键盘模拟操作都只需 DD_btn , DD_mov , DD_whl，DD_movR 四个操控鼠标的函数和 DD_key 一个操控键盘的函数即可完成 .
// Simple简易版本不需要安装驱动, General通用版与hid版本需要安装驱动,驱动文件在模块目录下的压缩包中.
//@依赖   无


#pragma once

#ifdef  XC_MODULE
#include "module_base.h"
#endif


#include "DD.h"
//===========================================
// 源文件 开始
//@src "DD.cpp"

#ifdef _WIN64
//@复制文件 @当前模块路径 "dd32695.x64.dll"
//@复制文件 @当前模块路径 "hid.64.dll"

#else
//@复制文件 @当前模块路径 "dd32695.x32.dll"
//@复制文件 @当前模块路径 "hid.32.dll"

#endif

// 源文件 结束



/*@声明

//@备注  DD虚拟键盘鼠标类封装
//@别名 DD鼠标键盘类
class CDD
{

	
	//@备注  功能： 模拟鼠标点击
	//@参数 x 1 =左键按下 ，2 =左键放开 4 =右键按下 ，8 =右键放开  16 =中键按下 ，32 =中键放开  64 =4键按下 ，128 =4键放开  256 =5键按下 ，512 =5键放开
	//@别名 DD鼠标按键(x)
	 int DD_btn(int x) ;        //Mouse button
	
	
	//@备注 功能: 模拟鼠标滚轮
	///例子: 向前滚一格, DD_whl(1)
	//@参数  1=前 , 2 = 后
	//@别名 DD鼠标滚轮(x)
	int DD_whl(int x) ;		 //Mouse wheel
	
	
	
	//@备注 功能： 模拟键盘按键
	///例子： 模拟单键WIN，
	///DD_key(601, 1);DD_key(601, 2);
	///组合键：ctrl+alt+del
	///DD_key(600,1);	
	///DD_key(602,1);	
	///DD_key(706,1);	
	///DD_key(706,2);
	///DD_key(602,2);
	///DD_key(600,2);
	//@参数  请查看[DD虚拟键盘码表],文件在本模块目录下
	//@参数  1=按下，2=放开
	//@别名 DD键盘按键(x,y)
		void DD_key(int x,int y) ;		 //Mouse move abs.
	


	//@备注  功能： 模拟鼠标绝对移动
	///例子： 把鼠标移动到分辨率1920*1080 的屏幕正中间，
	///int x = 1920/2 ; int y = 1080/2;
	///DD_mov(x,y) ;
	//@参数  以屏幕左上角为原点位置的横向值
	//@参数  以屏幕左上角为原点位置的纵向值
	//@别名 DD鼠标绝对移动(x,y)
	 int DD_mov(int x,int y);
	
	

	//@备注  功能： 直接输入键盘上可见字符和空格
	///例子： DD_str("MyEmail@aa.bb.cc !@#$")
	//@参数  输入A型文本 字符串, (注意，这个参数不是int32 类型)
	//@别名 DD键盘输入(x)
	int DD_str(char * x);			 //Keyboard
	
	//@备注  功能： 将windows的虚拟键码值转为DD的虚拟键值
	///参数： windows的虚拟键码值 (例 VK_LWIN   代表的左边的win键 转为 DD键值为 601 )
	///例： ddcode = DD_todc(VK_LWIN)
	//@参数  要转换的win代码键值
	//@别名 DD_VK键值转DD键值(x)
	int DD_todc(int x);		 //Input visible char
	
	
	//@备注 功能： 模拟鼠标相对移动
	///例子： 把鼠标向左移动10像素
	///DD_movR(-10,0) ;
	//@参数  以当前鼠标坐标为原点位置的横向值
	//@参数  以当前鼠标坐标为原点位置的纵向值
	//@别名 DD鼠标相对移动(x,y)
	int DD_movR(int x,int y) ;	 //VK to ddcode



	//备注  功能： dll模块指针变量
	//别名 DD_dll模块指针
	//HINSTANCE m_hModule;
	
	//@备注  功能： 初始化
	///dd驱动分为三个版本 
	///Simple简易版 不需要安装 文件名是 DD94687.32.dll与 DD94687.64.dll
	///General通用版 需要安装,安装包在模块目录下 文件名是 DD32.dll与 DD64.dll
	///HID版 需要安装,安装包在模块目录下 文件名是 DDHID32.dll与 DDHID.64.dll
	//@参数  输入dd鼠标键盘dll文件的完整地址
	//@返回  成功返回1 不成功返回其它值 键鼠功能无法使用
	//@别名 DD初始化(dll)
	int init(const wchar_t *dllfile);

};
*/  //声明结束
 


