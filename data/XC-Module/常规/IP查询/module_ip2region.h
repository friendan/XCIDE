//@模块名称 IP查询
//@版本  0.1.0
//@日期  2022-08-12
//@作者  欧阳逸洛
//@QQ    欧阳逸洛
//@模块备注 查询ip区域 包装 https://github.com/lionsoul2014/ip2region
//@依赖  module_base.h

#ifdef  _WIN64

#else

#endif

#include "module_base.h"
//@src "xdb_searcher.cpp"

//@隐藏{
#pragma once
#pragma warning(disable:4996) 

//#include "../xpl_wrap_utils/utils.hpp"

#include "xdb_searcher.h"

//@隐藏}

//@复制文件 @当前模块路径 "ip2region.xdb"

class Xdb {
public:

    //@别名 载入_从文件(xdb路径)
    BOOL load_content_from_file(const wchar_t* xdb_path) {
        auto path = W2A(xdb_path);
        close();
        searcher = std::make_unique<xdb_searcher_t>();
        c_buffer = xdb_load_content_from_file(path.get());
        if (c_buffer == NULL) {
            //printf("failed to load xdb content from `%s`\n", xdb_path);
            return FALSE;
        }
        // 2、使用全局的 c_buffer 变量创建一个完全基于内存的 xdb 查询对象
        int err = xdb_new_with_buffer(searcher.get(), c_buffer);
        if (err != 0) {
            //printf("failed to create content cached searcher with errcode=%d\n", err);
            return FALSE;
        }
        return TRUE;
    }

    //@别名 载入_从文件A(xdb路径)
    BOOL load_content_from_fileA(const char* xdb_path) {
        auto path = A2W(xdb_path);
        return load_content_from_file(path.get());
    }

    //@隐藏{
    //void search_by_string(const char* str_ip, std::function<void(const char* buf)> callback) {
    //    if (searcher) {
    //        char region_buffer[256];
    //        region_buffer[0] = '\0';
    //        if (0 == xdb_search_by_string(searcher.get(), str_ip, region_buffer, sizeof(region_buffer))) {
    //            callback(region_buffer);
    //        }
    //    }
    //}
    //@隐藏}

    //@别名 搜索A(ip)
    CXTextA search_by_textA(const char* str_ip) {
        if (searcher) {
            char region_buffer[256];
            region_buffer[0] = '\0';
            if (0 == xdb_search_by_string(searcher.get(), str_ip, region_buffer, sizeof(region_buffer))) {
                auto text = U2W(region_buffer);
                return W2A(text);
            }
        }
        return {};
    }
    
    //@别名 搜索(ip)
    CXText search_by_text(const wchar_t* str_ip) {
        if (searcher) {
            char region_buffer[256];
            region_buffer[0] = '\0';
            auto ip = W2A(str_ip);
            if (0 == xdb_search_by_string(searcher.get(), ip, region_buffer, sizeof(region_buffer))) {
                return U2W(region_buffer);
            }
        }
        return {};
    }

    //@别名 搜索2(ip)
    CXText search(int int_ip) {
        if (searcher) {
            char region_buffer[256];
            region_buffer[0] = '\0';
            if (0 == xdb_search(searcher.get(), int_ip, region_buffer, sizeof(region_buffer))) {
                return U2W(region_buffer);
            }
        }
        return {};
    }

    //@隐藏{
private:
    xdb_content_t* c_buffer = nullptr;
    std::unique_ptr<xdb_searcher_t> searcher;

    void close() {
        if (searcher) {
            xdb_close(searcher.get());
            searcher = nullptr;
        }

        if (c_buffer) {
            xdb_close_content(c_buffer);
            c_buffer = nullptr;
        }

    }

    //@隐藏}
};

/*@声明

*/
