#pragma once

//@模块名称  BSPHP网络验证
//@版本  1.0
//@日期  2022-12-21
//@作者  XCGUI  
//@模块备注  BSPHP 网络验证 https://www.bsphp.com/
// 更多BSPHP-PRO api接口请关注帮助中心 http://www.bsphp.com/index.php?act=chm&id=69

#include "HttpClient.h"   
#include <atltime.h>

//@src   "AES.cpp"
//@src   "AES_Base64.cpp"
//@src   "HttpClient.cpp"  
//@src   "BsPhpClass.cpp"


//@备注  获取初始化网络测试
//@别名  BSPHP_初始化()
BOOL BSPHP_Internet();

//@备注  初始化返回信息
//@别名  BSPHP_初始化信息()
CXText BSPHP_Internetinfo();

//@备注  获取公告
//@别名  BSPHP_取公告()
CXText BSPHP_GetGG();

//@备注  获取连接串 session
//@别名  BSPHP_取session()
CXText BSPHP_GetBSphpSeSsL();

//@备注  账号登录
//@别名  BSPHP_登录(用户名, 密码)
CXText  BSPHP_Login(const wchar_t* UserName, const wchar_t* PassWorld);

//@备注  注册账号
//@别名  BSPHP_注册(用户名, 密码, QQ)
CXText BSPHP_Reg(const wchar_t* UserName, const wchar_t* PassWorld, const wchar_t* QQ);

//@备注  充值续费
//@别名  BSPHP_充值(用户名, 密码, 卡号, 卡密)
CXText BSPHP_Pay(const wchar_t* UserName, const wchar_t* PassWorld, const wchar_t* KH, const wchar_t* KM);

//@备注  修改密码
//@别名  BSPHP_修改密码(用户名, 旧密码, 新密码)
CXText BSPHP_ModifyPassword(const wchar_t* UserName, const wchar_t* PassWorldOld, const wchar_t* PassWorldNew);


void BSPHP_SetAesKey(const wchar_t* aeskey);
void BSPHP_SetServerUrl(const wchar_t* url);
void BSPHP_SetMesKey(const wchar_t* key);

//@备注  设置标记, 绑定本地机器
//@别名  BSPHP_置标记(标记)
void BSPHP_SetMaxoror(const wchar_t* maxoror);

//@隐藏{
std::string BSPHP_GetTime();
std::string BSPHP_time_Format(time_t tm_in, const char* pFormat);
//@隐藏}

