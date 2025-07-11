#pragma once
// Created by Huiyi on 2021/4/20.
//
//@模块名称 炫易模块(系统)
//@版本   1.4
//@日期   2022-10-15
//@作者   Huiyi
//@模块备注 封装系统相关处理函数
//项目gitee地址 https://gitee.com/LoveA/XL_XExpand
//大部分代码已经历过粗略测试
//如发现BUG可提交issues
//https://gitee.com/LoveA/XL_XExpand/issues
//反馈QQ群:594165459

//@修订
//@日期   2024-1-25
//@修订人 peerless

//@依赖   module_base.h

#ifndef XL_XEXPAND_SYSTEM_H
//@隐藏{
#define XL_XEXPAND_SYSTEM_H    //防止复用

#if XC_MODULE
#include "module_base.h"
#endif

#include <errors.h>
#pragma comment (lib,"Quartz.lib")
#include "osplatformutil.h"
//@隐藏}

#include <Shlobj.h>
#pragma comment(lib, "Shell32.lib")


//cmd回显函数
typedef bool (*X_System_RunCmd_res) (const char* cmd);

//@src  "system.cpp"
//@src  "SystemClassReg.cpp"

//@分组{  环境系统

//@别名   系统_是否64位()
bool X_System_SysIs64();

//@备注   仅对编译环境有效    对应 常量_系统类型_\X_OS_
//@别名   系统_取系统类型()
int X_System_WIsOs();

//@别名   系统_取屏幕宽度()
int X_System_ScreenWidth();
//@别名   系统_取屏幕高度()
int X_System_ScreenHeight();

//@备注   设置屏幕分辨率
//@返回   0设置成功;1重启后生效;-2不支持的分辨率;-1驱动无效或不支持
//@参数   色深  新的色深 留空为不改变原先设定
//@参数   屏幕宽度    新的屏幕宽度 留空为不改变原先设定
//@参数   屏幕高度    新的屏幕高度 留空为不改变原先设定
//@参数   屏幕刷新率   新的屏幕刷新率 留空为不改变原先设定
//@参数   设置模式    1:临时, 退出软件或重启后恢复原来的配置; 2:全局, 设置后将一直使用新分辨率.
//@参数   显示器索引   索引值是从0开始
//@别名   系统_置屏幕分辨率(色深,屏幕宽度,屏幕高度,屏幕刷新率,设置模式,显示器索引)
DWORD X_System_SetScreenResolution(WORD dmBitsPerPel = 0, WORD dmPelsWidth = 0, WORD dmPelsHeight = 0, WORD dmDisplayFrequency = 0, int model = 1, DWORD iModeNum = 0);

//@备注 创建快捷方式(需要自行初始化COM)
//@参数 实际路径 指定快捷方式指向的实际文件路径
//@参数 快捷方式路径 快捷方式文件本身的完整路径
//@参数 图标路径 快捷方式图标的完整路径
//@参数 描述信息 快捷方式描述信息
//@参数 快捷键 为0表示不设置快捷键
//@返回 操作是否成功
//@别名 系统_创建快捷方式(实际路径,快捷方式路径,图标路径,描述信息,快捷键)
BOOL X_System_CreateFileShortcut(CXText lpszTargetFilePath, CXText lpszLnkPath, CXText IconPath=L"", CXText lpszDescription = L"", WORD wHotkey = 0);
//@备注 创建快捷方式A(需要自行初始化COM)
//@参数 实际路径 指定快捷方式指向的实际文件路径
//@参数 快捷方式路径 快捷方式文件本身的完整路径
//@参数 图标路径 快捷方式图标的完整路径
//@参数 描述信息 快捷方式描述信息
//@参数 快捷键 为0表示不设置快捷键
//@返回 操作是否成功
//@别名 系统_创建快捷方式A(实际路径,快捷方式路径,图标路径,描述信息,快捷键)
BOOL X_System_CreateFileShortcutA(CXTextA lpszTargetFilePath, CXTextA lpszLnkPath, CXTextA IconPath = "", CXTextA lpszDescription = "", WORD wHotkey = 0);


//TODO:未完成
//@隐藏{
//@参数   欲执行的cmd命令行
//@参数   回显的函数指针 函数原型(bool func(const char* str) 返回True中断 返回False继续) 可空
//@别名   系统_取DOS执行结果A (cmd命令行,回调指针)
CXTextA X_System_RunCmdA(CXTextA cmd, void* func = nullptr);
//@隐藏}

//@别名   注册表键类型A
struct StructRegKeyA {
    //@别名   键名
    CXTextA Key;
    //@别名   值
    CXTextA Value;
    //@别名   类型
    int Type;
};

//@别名   注册表键类型
struct StructRegKey {
    //@别名   键名
    CXText Key;
    //@别名   值
    CXText Value;
    //@别名   类型
    int Type;
};

//@别名   注册表操作类
class X_System_Class_Reg {
private:
    //@别名   打开项A()
    HKEY OpenA(CXTextA Path, bool Create = false);

    //@别名   打开项()
    HKEY Open(CXText Path, bool Create = false);

public:

    //@参数   项名称
    //@参数   获取的子项数组
    //@别名   枚举子项A(项名称,子项列表)
    //@返回   获取到的子项个数(ItemList的元素个数)
    int GetItemListA(CXTextA name, CXVector<CXTextA>& ItemList);
    //@参数   项名称
    //@参数   获取的子项数组
    //@别名   枚举子项(项名称,子项列表)
    //@返回   获取到的子项个数(ItemList的元素个数)
    int GetItemList(CXText name, CXVector<CXText>& ItemList);

    //@参数   项名称
    //@参数   获取的返回数据数组
    //@别名   枚举键名A(项名称,返回列表)
    //@返回   获取到的键名个数(List的元素个数)
    int GetKeyListA(CXTextA name, CXVector<StructRegKeyA>& List);
    //@参数   项名称
    //@参数   获取的返回数据数组
    //@别名   枚举键名(项名称,返回列表)
    //@返回   获取到的键名个数(List的元素个数)
    int GetKeyList(CXText name, CXVector<StructRegKey>& List);

    //@备注   对应常量 常量_注册表键类型_/X_REG_
    //@参数   项名称
    //@参数   查询的键名
    //@别名   取键名类型A(项名称,键名)
	//@返回   常量_注册表键类型
    int GetKeyTypeA(CXTextA name, CXTextA KeyName);
    //@备注   对应常量 常量_注册表键类型_/X_REG_
    //@参数   项名称
    //@参数   查询的键名
    //@别名   取键名类型(项名称,键名)
	//@返回   常量_注册表键类型
    int GetKeyType(CXText name, CXText KeyName);

    //@备注   判断指定注册项名称(键名)是否存在存在返回真,否则返回假
    //@参数   欲判断的项名称
    //@参数   欲判断的键名.如果为空则只判断项名称是否存在
    //@返回   存在返回真,否则返回假
    //@别名   是否存在A (项名称,键名)
    bool IfExistA(CXTextA name, CXTextA KeyName);
    //@备注   判断指定注册项名称(键名)是否存在存在返回真,否则返回假
    //@参数   欲判断的项名称
    //@参数   欲判断的键名.如果为空则只判断项名称是否存在
    //@返回   存在返回真,否则返回假
    //@别名   是否存在 (项名称,键名)
    bool IfExist(CXText name, CXText KeyName);

    //@备注   将对项和它的子项作出的改动实际写入磁盘
    //@别名   刷新项A (项名称)
    bool ReProjectA(CXTextA name);
    //@备注   将对项和它的子项作出的改动实际写入磁盘
    //@别名   刷新项 (项名称)
    bool ReProject(CXText name);

    //@参数   项名称
    //@参数   键名
    //@参数   欲写入的字节集
    //@参数   写入的类型   对应 常量_注册表键类型_/X_REG_   可空
    //@别名   写入字节集A(项名称,键名,写入字节集,类型)
    bool WriteByteA(CXTextA name, CXTextA KeyName, CXBytes WriteByte, int Tyte = 0);
    //@参数   项名称
    //@参数   键名
    //@参数   欲写入的字节集
    //@参数   写入的类型   对应 常量_注册表键类型_/X_REG_   可空
    //@别名   写入字节集(项名称,键名,写入字节集,类型)
    bool WriteByte(CXText name, CXText KeyName, CXBytes WriteByte, int Tyte = 0);

    //@参数   项名称
    //@参数   键名
    //@参数   取出数据的类型
    //@别名   取字节集A(项名称,键名,写入字节集,类型)
    CXBytes GetBytesA(CXTextA name, CXTextA KeyName, int& Type);
    //@参数   项名称
    //@参数   键名
    //@参数   取出数据的类型
    //@别名   取字节集(项名称,键名,写入字节集,类型)
    CXBytes GetBytes(CXText name, CXText KeyName, int& Type);

    //@别名   写可扩充字符串值A(项名称,键名,写入值)
    bool WriteExpandStrA(CXTextA name, CXTextA KeyName, CXTextA str);
    //@别名   写可扩充字符串值(项名称,键名,写入值)
    bool WriteExpandStr(CXText name, CXText KeyName, CXText str);

    //@别名   写DWORD值A(项名称,键名,值)
    bool WriteDWORDA(CXTextA name, CXTextA KeyName, int num);
    //@别名   写DWORD值(项名称,键名,值)
    bool WriteDWORD(CXText name, CXText KeyName, int num);

    //@别名   取DWORD值A(项名称,键名)
    int GetDWORDA(CXTextA name, CXTextA KeyNam);
    //@别名   取DWORD值(项名称,键名)
    int GetDWORD(CXText name, CXText KeyNam);

    //@别名   写二进制值A(项名称,键名,值)
    bool WriteBINA(CXTextA name, CXTextA KeyName, int num);
    //@别名   写二进制值(项名称,键名,值)
    bool WriteBIN(CXText name, CXText KeyName, int num);

    //@别名   取二进制值A(项名称,键名)
    int GetBINA(CXTextA name, CXTextA KeyNam);
    //@别名   取二进制值(项名称,键名)
    int GetBIN(CXText name, CXText KeyNam);

    //@别名   写文本值A(项名称,键名,内容)
    bool WriteStringA(CXTextA name, CXTextA KeyNam, CXTextA Str);
    //@别名   写文本值(项名称,键名,内容)
    bool WriteString(CXText name, CXText KeyNam, CXText Str);

    //@别名   取文本值A(项名称,键名)
    CXTextA GetStringA(CXTextA name, CXTextA KeyNam);
    //@别名   取文本值(项名称,键名)
    CXText GetString(CXText name, CXText KeyNam);

    //@别名   删除键A(项名称,键名)
    bool DelKeyA(CXTextA name, CXTextA KeyName);
    //@别名   删除键(项名称,键名)
    bool DelKey(CXText name, CXText KeyName);

};



//@分组}  环境系统
//@分组{  常量

//@别名   常量_系统类型_未知
#define X_OS_NULL 0
//@别名   常量_系统类型_Windows
#define X_OS_WINDOWS 1
//@别*名   常量_系统类型_Windows64
//#*define ML_OS_WINDOWS64 2
//@别名   常量_系统类型_Linux
#define X_OS_LINUX 3
//@别名   常量_系统类型_MacOS
#define X_OS_MACOS 4
//@别名   常量_系统类型_Android
#define X_OS_ANDROID 5
//@别名   常量_系统类型_Cygwin
#define X_OS_CYGWIN 6
//@别名   常量_系统类型_SunOs
#define X_OS_SUNOS 7
//@别名   常量_系统类型_FreeBSD
#define X_OS_FREEBSD 8
//@别名   常量_系统类型_OpenBSD
#define X_OS_OPENBSD 9
//@别名   常量_系统类型_Aix
#define X_OS_AIX 10

//@别名   常量_注册表键类型_键不存在
#define X_REG_NULL -1
//@别名   常量_注册表键类型_字节集
#define X_REG_NONE 0
//@别名   常量_注册表键类型_字符串值
#define X_REG_SZ 1
//@别名   常量_注册表键类型_可扩充字符串值
#define X_REG_REG_EXPAND_SZ 2
//@别名   常量_注册表键类型_二进制
#define X_REG_BINARY 3
//@别名   常量_注册表键类型_DWORD
#define X_REG_DWORD 4
//@别名   常量_注册表键类型_多字符串值
#define X_REG_MULTI_SZ 7

//@分组}  常量



#endif //XL_XEXPAND_SYSTEM_H
