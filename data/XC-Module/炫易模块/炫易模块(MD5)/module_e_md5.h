#pragma once
// Created by Huiyi on 2021/4/20.
//

//@模块名称 炫易模块(MD5)
//@版本   1.0
//@日期   2020-04-20
//@作者   Huiyi
//@模块备注 MD5校验封装
//	使用示例
//	ASCII情景
//	/*
//	md5.reset()
//	md5.update(A"text")
//	CXTextA md5.toString()
//	*/
//	Unicode情景
//	/*
//	md5.reset()
//	md5.update("text",textlen)
//	CXTextA md5.toString()
//	*/

//@依赖   module_base.h

#ifndef XCL_MD5_H
//@隐藏{
#define XCL_MD5_H
//@隐藏}
#include <string>
#include <fstream>
//@src  "md5.cpp"

/* Type define */
typedef unsigned char byte;
typedef unsigned int uint32;

#if XC_MODULE
#include "module_base.h"
#endif

//@别名	MD5类
class CXMD5 {
public:
    CXMD5();
    CXMD5(const void* input, size_t length);
    CXMD5(const std::string& str);
    CXMD5(std::ifstream& in);
    void update(const void* input, size_t length);
    void update(const byte* input, size_t length);
    void update(const std::string& str);
    void update(std::ifstream& in);
    const byte* digest();
    CXTextA toString();
    void reset();

private:
    void final();
    void transform(const byte block[64]);
    void encode(const uint32* input, byte* output, size_t length);
    void decode(const byte* input, uint32* output, size_t length);
	std::string bytesToHexString(const byte* input, size_t length);

    /* class uncopyable */
    CXMD5(const CXMD5&);
    CXMD5& operator=(const CXMD5&);

private:
    uint32 _state[4]; /* state (ABCD) */
    uint32 _count[2]; /* number of bits, modulo 2^64 (low-order word first) */
    byte _buffer[64]; /* input buffer */
    byte _digest[16]; /* message digest */
    bool _finished;   /* calculate finished ? */

    static const byte PADDING[64]; /* padding for calculate */
    static const char HEX[16];
    enum { BUFFER_SIZE = 1024 };
};


#endif //XCL_MD5_H
