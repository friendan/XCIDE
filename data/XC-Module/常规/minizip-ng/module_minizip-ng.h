//@模块名称 minizip-ng
//@版本  0.1.0
//@日期  2022-08-09
//@作者  欧阳逸洛
//@QQ   154460336
//@模块备注   zip压缩与解压
//包装 https://github.com/zlib-ng/minizip-ng
//@依赖  module_base.h

#ifdef  _WIN64
//@复制文件 @当前模块路径 "x64\bz2.dll"
//@复制文件 @当前模块路径 "x64\libminizip-ng.dll"
//@复制文件 @当前模块路径 "x64\lzma.dll"
//@复制文件 @当前模块路径 "x64\zlib-ng2.dll"
//@复制文件 @当前模块路径 "x64\zstd.dll"
//@lib "x64\bz2.lib"
//@lib "x64\libminizip-ng.lib"
//@lib "x64\lzma.lib"
//@lib "x64\zlib-ng.lib"
//@lib "x64\zstd.lib"
#ifdef XPL_DEV
#pragma comment(lib,"x64/bz2.lib")
#pragma comment(lib,"x64/libminizip-ng.lib")
#pragma comment(lib,"x64/lzma.lib")
#pragma comment(lib,"x64/zlib-ng.lib")
#pragma comment(lib,"x64/zstd.lib")
#endif // XPL_DEV
#else

//@复制文件 @当前模块路径 "x86\bz2.dll"
//@复制文件 @当前模块路径 "x86\libminizip-ng.dll"
//@复制文件 @当前模块路径 "x86\lzma.dll"
//@复制文件 @当前模块路径 "x86\zlib-ng2.dll"
//@复制文件 @当前模块路径 "x86\zstd.dll"
//@lib "x86\bz2.lib"
//@lib "x86\libminizip-ng.lib"
//@lib "x86\lzma.lib"
//@lib "x86\zlib-ng.lib"
//@lib "x86\zstd.lib"
#ifdef XPL_DEV
#pragma comment(lib,"x86/bz2.lib")
#pragma comment(lib,"x86/libminizip-ng.lib")
#pragma comment(lib,"x86/lzma.lib")
#pragma comment(lib,"x86/zlib-ng.lib")
#pragma comment(lib,"x86/zstd.lib")
#endif // XPL_DEV

#endif


//@隐藏{
#pragma once
//#include "../xpl_wrap_utils/utils.hpp"
#define MZ_COMPAT_VERSION 120
#define HAVE_LZMA
#define HAVE_BZIP2
#define HAVE_WZAES
#define HAVE_PKCRYPT
#define HAVE_ZLIB
#define HAVE_ZSTD

#include "include/minizip-ng/mz.h"
#include "include/minizip-ng/mz_compat.h"
#include "include/minizip-ng/mz_crypt.h"
#include "include/minizip-ng/mz_strm.h"
#include "include/minizip-ng/mz_strm_os.h"
#ifdef HAVE_BZIP2
#include "include/minizip-ng/mz_strm_bzip.h"
#endif
#ifdef HAVE_PKCRYPT
#include "include/minizip-ng/mz_strm_pkcrypt.h"
#endif
#include "include/minizip-ng/mz_strm_buf.h"
#include "include/minizip-ng/mz_strm_mem.h"
#include "include/minizip-ng/mz_os.h"
#include "include/minizip-ng/mz_strm_split.h"
#ifdef HAVE_WZAES
#include "include/minizip-ng/mz_strm_wzaes.h"
#endif
#ifdef HAVE_LZMA
#include "include/minizip-ng/mz_strm_lzma.h"
#endif
#ifdef HAVE_ZLIB
#include "include/minizip-ng/mz_strm_zlib.h"
#endif
#ifdef HAVE_ZSTD
#include "include/minizip-ng/mz_strm_zstd.h"
#endif
#include "include/minizip-ng/mz_zip.h"
#include "include/minizip-ng/mz_zip_rw.h"
//@隐藏}

//@解析头文件
#include "xpl_def/mz.h"
//@解析头文件
#include "xpl_def/mz_compat.h"
//@解析头文件
#include "xpl_def/mz_crypt.h"
//@解析头文件
#include "xpl_def/mz_strm.h"
//@解析头文件
#include "xpl_def/mz_strm_os.h"
//@解析头文件
#include "xpl_def/mz_strm_bzip.h"
//@解析头文件
#include "xpl_def/mz_strm_pkcrypt.h"
//@解析头文件
#include "xpl_def/mz_strm_buf.h"
//@解析头文件
#include "xpl_def/mz_strm_mem.h"
//@解析头文件
#include "xpl_def/mz_os.h"
//@解析头文件
#include "xpl_def/mz_strm_split.h"
//@解析头文件
#include "xpl_def/mz_strm_wzaes.h"
//@解析头文件
#include "xpl_def/mz_strm_lzma.h"
//@解析头文件
#include "xpl_def/mz_strm_zlib.h"
//@解析头文件
#include "xpl_def/mz_strm_zstd.h"
//@解析头文件
#include "xpl_def/mz_zip.h"
//@解析头文件
#include "xpl_def/mz_zip_rw.h"


/*@声明

*/
