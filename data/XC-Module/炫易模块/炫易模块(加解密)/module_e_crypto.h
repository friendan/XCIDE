// Created by Huiyi on 2021/4/20.
//
//@模块名称 炫易模块(加解密)
//@版本   1.4
//@日期   2022-10-18
//@作者   Huiyi
//@模块备注 封装加解密相关函数
//项目gitee地址 https://gitee.com/LoveA/XL_XExpand
//大部分代码已经历过粗略测试
//如发现BUG可提交issues
//https://gitee.com/LoveA/XL_XExpand/issues
//反馈QQ群:594165459

//@依赖   module_base.h, module_e_md5.h

#pragma once

#ifndef XL_XEXPAND_CYRPTO_H
//@隐藏{
#define XL_XEXPAND_CYRPTO_H    //防止复用

#if XC_MODULE
#include "module_base.h"
#include "module_e_md5.h"
#endif
//@隐藏}
#include <sstream>
//@src  "crypto.cpp"
//@src  "crypto/HashBase.cpp"

#include "base64/base64.h"
//@src  "base64/base64.cpp"
#include "crypto/rc4.h"
//@src  "crypto/rc4.cpp"
#include "crypto/sha1.h"
//@src  "crypto/sha1.cpp"
#include "crypto/sha256.h"
//@src  "crypto/sha256.cpp"
#include "crypto/sha512.h"
//@src  "crypto/sha512.cpp"
#include "crypto/aes.h"
//@src  "crypto/aes.cpp"




//@分组{  AES常量

//@备注   填充至符合块大小的整数倍，填充值为填充数量数。
//@别名   数据填充_PKCS7_PADDING
#define X_AES_PKCS7_PADDING 1
//@备注   填充至符合块大小的整数倍，填充值为 0。
//@别名   数据填充_ZERO_PADDING
#define X_AES_ZERO_PADDING 2
//@备注   填充至符合块大小的整数倍，填充值最后一个字节为填充的数量数，其他字节填 0。
//@别名   数据填充_X923_PADDING
#define X_AES_X923_PADDING 3
//@备注   填充至符合块大小的整数倍，填充值最后一个字节为填充的数量数，其他字节随机处理。
//@别名   数据填充_ISO10126_PADDING
#define X_AES_ISO10126_PADDING 4
//@备注   填充至符合块大小的整数倍，填充值第一个字节为 0x80，其他字节填 0。
//@别名   数据填充_ISO78164_PADDING
#define X_AES_ISO78164_PADDING 5


//@分组}
// TODO: 加密解密
//@分组{  加密解密



//@别名   校验_取MD5_AsciiA(文本)
CXTextA X_Check_GetMD5_AsciiA (const char* str);
//@别名   校验_取MD5_Ascii(文本)
CXText X_Check_GetMD5_Ascii(const char* str);

//@别名   校验_取MD5_UnicodeA(文本)
CXTextA X_Check_GetMD5_UnicodeA (CXText data);
//@别名   校验_取MD5_Unicode(文本)
CXText X_Check_GetMD5_Unicode(CXText data);

//@别名   校验_取MD5_字节集A(字节集)
CXTextA X_Check_GetMD5_BytesA (CXBytes& data);
//@别名   校验_取MD5_字节集(字节集)
CXText X_Check_GetMD5_Bytes (CXBytes& data);

//@别名   校验_Base64_编码A (文本)
CXTextA X_Check_BASE64_EnCodeA (CXTextA data);
//@别名   校验_Base64_编码 (文本)
CXText X_Check_BASE64_EnCode (CXText data);

//@别名   校验_Base64_解码A (文本)
CXBytes X_Check_BASE64_DeCodeA (CXTextA data);
//@别名   校验_Base64_解码 (文本)
CXBytes X_Check_BASE64_DeCode(CXText data);

//@别名   校验_Base64_编码_字节集A (字节集)
CXTextA X_Check_BASE64_EnCode_BytesA (CXBytes &data);
//@别名   校验_Base64_编码_字节集 (字节集)
CXText X_Check_BASE64_EnCode_Bytes(CXBytes& data);
//@别名   校验_Base64_编码_字节集指针A(字节集指针,长度)
CXTextA X_Check_BASE64_EnCode_BYTEA(const BYTE* data, size_t len);
//@别名   校验_Base64_编码_字节集指针(字节集指针,长度)
CXText X_Check_BASE64_EnCode_BYTE(const BYTE* data, size_t len);



//@别名   校验_RC4加密A(待加密字节集,秘钥)
CXBytes X_Check_RC4EncryptionA(const CXBytes& data, CXTextA Key);
//@别名   校验_RC4加密(待加密字节集,秘钥)
CXBytes X_Check_RC4Encryption(const CXBytes& data, CXText Key);

//@别名   校验_RC4解密A(加密数据,秘钥)
CXBytes X_Check_RC4DecryptionA(const CXBytes& data, CXTextA Key);
//@别名   校验_RC4解密(加密数据,秘钥)
CXBytes X_Check_RC4Decryption(const CXBytes& data, CXText Key);

//@别名   校验_取sha1A(原始数据,数据长度)
CXTextA X_Check_GetSHA1A(const BYTE* data,int dataLen);
//@别名   校验_取sha1(原始数据,数据长度)
CXText X_Check_GetSHA1(const BYTE* data, int dataLen);

//@别名   校验_取sha256A(原始数据,数据长度)
CXTextA X_Check_GetSHA256A(const BYTE* data, int dataLen);
//@别名   校验_取sha256(原始数据,数据长度)
CXText X_Check_GetSHA256(const BYTE* data, int dataLen);

//@别名   校验_取sha512A(原始数据,数据长度)
CXTextA X_Check_GetSHA512A(const BYTE* data, int dataLen);
//@别名   校验_取sha512(原始数据,数据长度)
CXText X_Check_GetSHA512(const BYTE* data, int dataLen);

//AES128对应16位 AES192对应24位 AES256对应32位

//@备注   AES-ECB模式加密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES加密_ECB(明文,密码,填充模式)
CXBytes X_Check_EnCrypto_AES_ECB(const CXBytes& data, const CXBytes& Key, int Padding = X_AES_PKCS7_PADDING);
//@备注   AES-ECB模式加密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES加密_ECB_Ex(明文,明文长度,密码,密码长度,填充模式)
CXBytes X_Check_EnCrypto_AES_ECB_Ex(const BYTE* data, int dataLen, const BYTE* pKey, int keySize, int Padding= X_AES_PKCS7_PADDING);

//@备注   AES-ECB模式解密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES解密_ECB(密文,密码,填充模式)
CXBytes X_Check_DeCrypto_AES_ECB(const CXBytes& data, const CXBytes& pKey ,int Padding = X_AES_PKCS7_PADDING);
//@备注   AES-ECB模式解密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES解密_ECB_Ex(密文,密文长度,密码,密码长度,填充模式)
CXBytes X_Check_DeCrypto_AES_ECB_Ex(const BYTE* data, int dataLen, const BYTE* pKey, int keySize, int Padding = X_AES_PKCS7_PADDING);

//@备注   AES-CBC模式加密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES加密_CBC(明文,密码,IV,填充模式)
CXBytes X_Check_EnCrypto_AES_CBC(const CXBytes& data,const CXBytes& pKey, const CXBytes& pIV,int Padding = X_AES_PKCS7_PADDING);
//@备注   AES-CBC模式加密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES加密_CBC_Ex(明文,明文长度,密码,密码长度,IV,IV长度,填充模式)
CXBytes X_Check_EnCrypto_AES_CBC_Ex(const BYTE* data, int dataLen,
	const BYTE* pKey, int keySize,
	const BYTE* pIV=NULL, int IVSize=0,
	int Padding = X_AES_PKCS7_PADDING);

//@备注   AES-CBC模式解密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES解密_CBC(密文,密码,IV,填充模式)
CXBytes X_Check_DeCrypto_AES_CBC(const CXBytes& data, const CXBytes& pKey, const CXBytes& pIV, int Padding = X_AES_PKCS7_PADDING);
//@备注   AES-CBC模式解密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES解密_CBC_Ex(密文,密文长度,密码,密码长度,IV,IV长度,填充模式)
CXBytes X_Check_DeCrypto_AES_CBC_Ex(const BYTE* data, int dataLen,
	const BYTE* pKey, int keySize,
	const BYTE* pIV=NULL, int IVSize=0,
	int Padding = X_AES_PKCS7_PADDING);

//@备注   AES-CFB模式加密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES加密_CFB(明文,密码,IV,填充模式)
CXBytes X_Check_EnCrypto_AES_CFB(const CXBytes& data, const CXBytes& pKey, const CXBytes& pIV, int Padding = X_AES_PKCS7_PADDING);
//@备注   AES-CFB模式加密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES加密_CFB_Ex(明文,明文长度,密码,密码长度,IV,IV长度,填充模式)
CXBytes X_Check_EnCrypto_AES_CFB_Ex(const BYTE* data, int dataLen,
	const BYTE* pKey, int keySize,
	const BYTE* pIV = NULL, int IVSize = 0,
	int Padding = X_AES_PKCS7_PADDING);

//@备注   AES-CFB模式解密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES解密_CFB(密文,密码,IV,填充模式)
CXBytes X_Check_DeCrypto_AES_CFB(const CXBytes& data, const CXBytes& pKey, const CXBytes& pIV, int Padding = X_AES_PKCS7_PADDING);
//@备注   AES-CFB模式解密
//@参数   密码 最长32位
//@参数   密码长度
//@别名   校验_AES解密_CFB_Ex(密文,密文长度,密码,密码长度,IV,IV长度,填充模式)
CXBytes X_Check_DeCrypto_AES_CFB_Ex(const BYTE* data, int dataLen,
	const BYTE* pKey, int keySize,
	const BYTE* pIV = NULL, int IVSize = 0,
	int Padding = X_AES_PKCS7_PADDING);


//@分组}  加密解密


#endif //XL_XEXPAND_CYRPTO_H
