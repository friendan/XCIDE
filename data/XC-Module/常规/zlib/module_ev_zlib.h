//@模块名称 zlib
//@版本  0.1.0
//@日期  2022-08-08
//@作者  欧阳逸洛
//@QQ  154460336
//@模块备注  兼容易语言、火山
//@依赖  module_base.h

#ifdef  _WIN64
//@lib "x64\zlibstat.lib"
#else
//@lib "x86\zlibstat.lib"
#endif

//@src "module_ev_zlib.cpp"

#ifdef  XC_MODULE
#include "module_base.h"
#endif


//@隐藏{
#pragma once
//#include "../xpl_wrap_utils/utils.hpp"
#define ZLIB_WINAPI

//@隐藏}



/*@声明

*/

//@别名 压缩数据2(数据,压缩结果,压缩等级)
BOOL ev_compress2(CXBytes& src, CXBytes& dest, int level = -1);
//@别名 压缩数据(数据,压缩等级)
CXBytes ev_compress(CXBytes& src, int level = -1);

//@别名 解压数据2(数据,解压结果,压缩等级)
BOOL ev_uncompress2(CXBytes& src, CXBytes& dest);
//@别名 解压数据(数据)
CXBytes ev_uncompress(CXBytes& src);

//@别名  crc32(数据)
int ev_crc32(CXBytes& src);