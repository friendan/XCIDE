//@模块名称  YYJSON对象
//@版本  2.0
//@日期  2024-12-12
//@作者  逸辰Arne
//@QQ    2186616866
//@模块备注 YYJSON对象调用

//@隐藏{
#pragma once
#include "module_base.h"
#include "lib/PrtAuto.hpp"
#include "lib/yyjson.h"

// 默认取JSON文本值错误都返回空文本,改成 0 则 null
#if 1
#define JSON_NULL_TEXT "";
#else
#define JSON_NULL_TEXT NULL;
#endif // true

CXTextA _uint64a(uint64_t nValue);
CXTextA _int64a(int64_t nValue);
CXTextA _doublea(double nValue);
CXTextA _readval(yyjson_mut_val* val);
CXTextA _readval(yyjson_val* val);
//@隐藏}

//@src "lib/yyjson.c"
//@src "module_yyjsonobj.cpp"

//@隐藏{
class CJsondocptr : public PtrAuto<yyjson_doc> {
public:
    CJsondocptr(yyjson_doc* doc) : PtrAuto<yyjson_doc>(doc) {
        fn_release(yyjson_doc_free);
    }
};
//@隐藏}


//@别名 YYJSON格式化选项
typedef uint32_t json_write_flag;
//@别名 YYJSON格式化选项_压缩
const json_write_flag JSON_WRITE_NOFLAG              = 0 << 0;
//@别名 YYJSON格式化选项_缩进
const json_write_flag JSON_WRITE_PRETTY              = 1 << 0;
//@别名 YYJSON格式化选项_输出A码
const json_write_flag JSON_WRITE_ESCAPE_UNICODE      = 1 << 1;
//@别名 YYJSON格式化选项_转义
const json_write_flag JSON_WRITE_ESCAPE_SLASHES      = 1 << 2;
//@别名 YYJSON格式化选项_字符表示无限
const json_write_flag JSON_WRITE_ALLOW_INF_AND_NAN   = 1 << 3;
//@别名 YYJSON格式化选项_空表示无限
const json_write_flag JSON_WRITE_INF_AND_NAN_AS_NULL = 1 << 4;


//@备注 本类中文本支持GBK与UTF8文本等单字节以字节0(NULL)为结尾的文本,解析输入的是什么编码,取属性时需自行对应
//@别名 JSON解析
class CJsonRead {
private:
    //@隐藏{
    CJsondocptr doc;
    yyjson_val* val;

    CXTextA as_text();
    //@隐藏}

public:
    //@隐藏{
    CJsonRead() : doc(NULL), val(NULL){};

    CJsonRead(const char* szJson) : doc(yyjson_read(szJson, strlen(szJson), 0)),
                                    val(*doc ? yyjson_doc_get_root(*doc) : NULL) {}

    CJsonRead(CJsondocptr& doc, yyjson_val* val) : doc(doc), val(val) {}

    ~CJsonRead(){};
    //@隐藏}

    //@备注 解析Json文本
    //@别名 解析(json)
    //@返回 成功true  失败false
    bool parse(const char* szJson);

    //@备注 在当前解析对象为 CJsonObject 时,使用 键名 取属性对象
    //@参数 键名 Key
    //@别名 取对象(键名)
    //@返回 JSON解析对象
    CJsonRead get(const char* key) {
        yyjson_val* obj = val ? yyjson_obj_get(val, key) : NULL;
        return CJsonRead(doc, obj);
    }

    //@隐藏{
    CJsonRead operator[](const char* key) {
        yyjson_val* obj = val ? yyjson_obj_get(val, key) : NULL;
        return CJsonRead(doc, obj);
    }
    //@隐藏}

    //@备注 在当前解析对象为 JSONArray 时,使用 序号 取属性对象
    //@参数 序号 Index
    //@别名 取成员(序号)
    //@返回 JSON解析对象
    CJsonRead get(size_t index) {
        yyjson_val* obj = val ? yyjson_arr_get(val, index) : NULL;
        return CJsonRead(doc, obj);
    }

    //@隐藏{
    CJsonRead operator[](int index) {
        yyjson_val* obj = val ? yyjson_arr_get(val, size_t(index)) : NULL;
        return CJsonRead(doc, obj);
    }

    CJsonRead operator[](INT64 index) {
        yyjson_val* obj = val ? yyjson_arr_get(val, size_t(index)) : NULL;
        return CJsonRead(doc, obj);
    }
    //@隐藏}

    //@备注 取当前解析对象的长度CJsonObject-键对值数量,JSONArray-成员数量,文本和字节集-数据长度 原函数 yyjson_get_len
    //@别名 长度()
    //@返回 根据当前对象类型返回 数据长度 或 数据数量
    inline size_t len() {
        return val ? yyjson_get_len(val) : NULL;
    }

    //@备注 取键名 = 取属性名 取当前对象object,序号对应的键名,GBK与UTF8文本等单字节以字节0(NULL)为结尾的文本,输入的时候或解析的时候是什么编码.这里就同样是
    //@别名 取键名(序号)
    //@返回 键名(Key) 文本
    const char* get_key(size_t index);

    //@备注 取属性名 = 取键名 取当前对象object,序号对应的属性名,GBK与UTF8文本等单字节以字节0(NULL)为结尾的文本,输入的时候或解析的时候是什么编码.这里就同样是
    //@别名 取属性名(序号)
    //@返回 属性名(name) 文本
    inline const char* get_name(size_t index) {
        return get_key(index);
    }

    //@备注 取当前解析对象的类型描述文本
    //@别名 类型()
    //@返回 描述文本 纯英文描述,兼容GBK
    inline const char* type() {
        return val ? yyjson_get_type_desc(val) : JSON_NULL_TEXT;
    }

    //@备注 以文本值方式取出当前对象属性
    //@别名 取文本值()
    //@返回 UTF8编码文本
    inline const char* as_str() {
        const char* str = val ? yyjson_get_str(val) : NULL;
        return str ? str : JSON_NULL_TEXT;
    }

    //@备注 以逻辑值方式取出当前对象属性 yyjson_get_bool
    //@别名 取逻辑值()
    //@返回 逻辑值
    inline bool as_bool() {
        return val ? yyjson_get_bool(val) : NULL;
    }

    //@备注 以数值方式取出当前对象属性 yyjson_get_num
    //@别名 取数值()
    //@返回 双浮点型数值
    inline double as_num() {
        return val ? yyjson_get_num(val) : NULL;
    }

    //@备注 以整数值方式取出当前对象属性 yyjson_get_int
    //@别名 取整数值()
    //@返回 整数值(int)
    inline int as_int() {
        return val ? yyjson_get_int(val) : NULL;
    }

    //@备注 以小数方式取出当前对象属性 yyjson_get_real
    //@别名 取小数值()
    //@返回 双浮点型数值
    inline double as_real() {
        return val ? yyjson_get_real(val) : NULL;
    }

    //@备注 以长整型方式取出当前对象属性 yyjson_get_sint
    //@别名 取长整型值()
    //@返回 长整型
    inline uint64_t as_sint64() {
        return val ? yyjson_get_sint(val) : NULL;
    }

    //@备注 以无符号长整型方式取出当前对象属性 yyjson_get_uint
    //@别名 取无符号长整型值()
    //@返回 长整型
    inline uint64_t as_uint64() {
        return val ? yyjson_get_uint(val) : NULL;
    }

    //@备注 以字节集方式取出当前对象属性 yyjson_get_raw 注意,这不是通用方法,只有对象类型为 raw 时才有效,例: { "raw":asdafwx } 没有双引号标记的字符串
    //@别名 取RAW()
    //@返回 字节集
    inline CXBytes as_bytes() {
        CXBytes cxbytes = CXBytes();
        const char* bytes = val ? yyjson_get_raw(val) : NULL;
        if (bytes) {
            cxbytes.set(bytes, yyjson_get_len(val));
        }
        return cxbytes;
    }

    //@备注 判断当前对象属性值是否存在
    //@别名 是否存在()
    //@返回 存在true  不存在false
    bool exist() const { return val != NULL; }

    //@隐藏{
    // 隐式转换..不指定取值时,默认文本解析值
    inline operator CXTextA() { return as_text(); }
    //@隐藏}
};

//@隐藏{
class CJsonmutdocptr : public PtrAuto<yyjson_mut_doc> {
public:
    CJsonmutdocptr(yyjson_mut_doc* doc) : PtrAuto<yyjson_mut_doc>(doc) {
        fn_release(yyjson_mut_doc_free);
    }
};
//@隐藏}

//@备注 本类中文本支持GBK与UTF8文本等单字节以字节0(NULL)为结尾的文本,输入的时候或解析的时候是什么编码,输出的时候同样是编码
//@别名 JSON对象
class CJsonObject {
private:
    //@隐藏{
    CJsonmutdocptr mut_doc;
    yyjson_mut_val* mut_root;
    const char* mut_key;
    yyjson_mut_val* mut_val;
    size_t mut_lv;

    void check_key_val();
    bool add_key_val(yyjson_mut_val* val);
    CJsonObject(CJsonmutdocptr doc, yyjson_mut_val* root, const char* key, yyjson_mut_val* val = NULL) : mut_doc(doc), mut_root(root), mut_lv(1), mut_key(key), mut_val(val) {
        check_key_val();
    }

    //@隐藏}
public:
    //@隐藏{
    CJsonObject() : mut_doc(yyjson_mut_doc_new(NULL)),
                    mut_root(yyjson_mut_obj(*mut_doc)),
                    mut_key(NULL),
                    mut_val(NULL),
                    mut_lv(0) {}

    CJsonObject(CJsonmutdocptr doc, yyjson_mut_val* root) : mut_doc(doc),
                                                            mut_root(root),
                                                            mut_key(NULL),
                                                            mut_val(NULL),
                                                            mut_lv(1) {}

    ~CJsonObject() {}
    //@隐藏}

    //@备注 取出属性名对应的对象
    //@别名 取对象(属性名)
    //@返回 JSON对象
    CJsonObject get_obj(const char* key);

    //@备注 检查当前对象是否存在指定属性名
    //@别名 属性名是否存在(键名)
    bool has_key(const char* key) const;

    //@备注 检查当前对象是否存在指定键名
    //@别名 键名是否存在(键名)
    bool has_name(const char* key) const {
        return has_key(key);
    }

    //@隐藏{
    inline CJsonObject operator[](const char* key) {
        return get_obj(key);
    }
    //@隐藏}

    //@备注 在当前对象为 JSONArray 时,取出序号对应的对象(序号从 0 开始)
    //@别名 取成员对象(序号)
    //@返回 JSON对象
    CJsonObject get_obj(size_t index);

    //@隐藏{
    inline CJsonObject operator[](size_t index) {
        return get_obj(index);
    }

    CJsonObject operator[](int index) {
        return get_obj(int(index));
    }
    //@隐藏}

    //@备注 在当前对象为空属性,或为 JSONArray 时,添加一个新的成员在最后
    //@别名 添加成员_文本型(文本)
    //@返回 逻辑型 是否成功
    bool add_str(const char* str);

    //@备注 例如添加GBK编码的文本,以 \0 为结束符 的一段字节集  在当前对象为空属性,或为 JSONArray 时,添加一个新的成员在最后
    //@别名 添加成员_RAW(非标准文本)
    //@返回 逻辑型 是否成功
    bool add_raw(const char* raw);

    //@备注 在当前对象为空属性,或为 JSONArray 时,添加一个新的成员在最后
    //@别名 添加成员_对象(JSON对象)
    //@返回 逻辑型 是否成功
    bool add_obj(const CJsonObject& object);

    //@备注 在当前对象为空属性,或为 JSONArray 时,添加一个新的成员在最后
    //@别名 添加成员_整型(整数)
    //@返回 逻辑型 是否成功
    bool add_int(int intn);

    //@备注 在当前对象为空属性,或为 JSONArray 时,添加一个新的成员在最后
    //@别名 添加成员_小数(小数)
    //@返回 逻辑型 是否成功
    bool add_double(double f);

    //@备注 在当前对象为空属性,或为 JSONArray 时,添加一个新的成员在最后
    //@别名 添加成员_无符号长整数(无符号长整数)
    //@返回 逻辑型 是否成功
    bool add_uint(uint64_t uintn);

    //@备注 在当前对象为空属性,或为 JSONArray 时,添加一个新的成员在最后
    //@别名 添加成员_长整数(长整数)
    //@返回 逻辑型 是否成功
    bool add_sint(int64_t intn);

    //@备注 在当前对象为空属性,或为 JSONArray 时,添加一个新的成员在最后
    //@别名 添加成员_逻辑值(逻辑值)
    //@返回 逻辑型 是否成功
    bool add_bool(bool b);

    //@备注 在当前对象为空属性,或为 JSONArray 时,添加一个新的成员在最后
    //@别名 添加成员_NULL值()
    //@返回 逻辑型 是否成功
    bool add_null();

    //@备注 设置当前属性值值为指定文本,,GBK与UTF8文本等单字节以字节0(NULL)为结尾的文本,这里输入的什么编码.原样输出
    //@别名 置文本(UTF8文本)
    //@返回 逻辑型 是否成功
    bool set_str(const char* str);

    //@备注 设置当前属性值值为RAW,与置文本的区别是值没有双引号: 例{ "name": raw } ,可以是一段不可显示的字节集,但以字节 0 为结束符,可能造成截断
    //@别名 置RAW(非标准字符串)
    //@返回 逻辑型 是否成功
    bool set_raw(const char* raw);

    //@备注 将当前对象移除节点树
    //@别名 移除()
    //@返回 逻辑型 是否成功
    bool remove();

    //@备注 将当前对象移除节点树,防呆设计.名字叫删除,其实没有删除数据,只是移除节点,数据在对象使用完毕的时候会一起释放
    //@别名 删除()
    //@返回 逻辑型 是否成功
    inline bool del() {
        return remove();
    }

    //@备注 这个是用来设置为一个空数组 [],主要用于类型转换,和就是想真么显示 如果添加已有数组,请 置对象() 方法
    //@别名 置空数组()
    //@返回 逻辑型 是否成功
    bool set_aar();

    //@隐藏{
    bool set_obj();
    //@隐藏}

    //@备注 设置当前属性值值为指定JSON对象
    //@参数 参数可留空,可用于强制转换类型,同时会将原数据移出节点,属性变成 {}
    //@别名 置对象(JSON对象)
    //@返回 逻辑型 是否成功
    bool set_obj(const CJsonObject& object);

    //@备注 设置当前属性值值为指定整数
    //@别名 置整数(整数)
    //@返回 逻辑型 是否成功
    bool set_int(int n);

    //@备注 设置当前属性值值为指定小数
    //@别名 置小数(小数)
    //@返回 逻辑型 是否成功
    bool set_double(double f);

    //@备注 设置当前属性值值为指定无符号长整数,如果你真的需要大于 9223372036854775807 的数字...
    //@别名 置无符号长整数(无符号长整数)
    //@返回 逻辑型 是否成功
    bool set_uint(uint64_t uintn);

    //@备注 设置当前属性值值为指定长整数
    //@别名 置长整数(长整数)
    //@返回 逻辑型 是否成功
    bool set_sint(int64_t intn);

    //@备注 设置当前属性值值为指定逻辑值
    //@别名 置逻辑值(逻辑值)
    //@返回 逻辑型 是否成功
    bool set_bool(bool b);

    //@备注 设置当前属性值值为null,注意这不是移除属性,是设置 { "name":null }
    //@别名 置NULL()
    //@返回 逻辑型 是否成功
    bool set_null();

    //@备注 以文本方式输出当前对象,文字编码按输入时的原样写出,支持GBK与UTF8文本等单字节以字节0(NULL)为结尾的文本
	//@参数 请参考"YYJSON格式化选项"所提供的常量值,可使用其组合值.
    //@别名 到JSON文本(选项)
    //@返回 JSON文本
    CXTextA writetext(json_write_flag flg = JSON_WRITE_PRETTY);

    //@隐藏{
    bool operator=(const char* str) {
        return set_str(str);
    }

    bool operator=(int n) {
        return set_int(n);
    }

    bool operator=(double f) {
        return set_double(f);
    }

    bool operator=(CJsonObject& object) {
        return set_obj(object);
    }
    //@隐藏}

    //@备注 取当前对象的长度CJsonObject-键对值数量,JSONArray-成员数量,文本和字节集-数据长度
    //@别名 长度()
    //@返回 根据当前对象类型返回 数据长度 或 数据数量
    inline size_t len() {
        return yyjson_mut_get_len(mut_lv == 0 ? mut_root : mut_val);
    }

    //@备注 取键名 = 取属性名 取当前对象object,序号对应的键名 ,GBK与UTF8文本等单字节以字节0(NULL)为结尾的文本,输入的时候或解析的时候是什么编码.这里就同样是
    //@别名 取键名(序号)
    //@返回 键名(Key)
    const char* get_key(size_t index);

    //@备注 取属性名 = 取键名 取当前对象object,序号对应的属性名,GBK与UTF8文本等单字节以字节0(NULL)为结尾的文本,输入的时候或解析的时候是什么编码.这里就同样是
    //@别名 取属性名(序号)
    //@返回 属性名(name)
    inline const char* get_name(size_t index) {
        return get_key(index);
    }

    //@备注 取当前对象的类型描述文本
    //@别名 类型()
    //@返回 描述文本 纯英文描述,兼容GBK
    inline const char* type() {
        return yyjson_mut_get_type_desc(mut_lv == 0 ? mut_root : mut_val);
    }

    //@备注 以文本值方式取出当前对象属性
    //@别名 取文本值()
    //@返回 GBK与UTF8文本等单字节以字节0(NULL)为结尾的文本,输入的时候或解析的时候是什么编码.这里就同样是
    inline const char* as_str() {
        const char* str = mut_val ? yyjson_mut_get_str(mut_val) : NULL;
        return str ? str : JSON_NULL_TEXT;
    }

    //@备注 以逻辑值方式取出当前对象属性 yyjson_get_bool
    //@别名 取逻辑值()
    //@返回 逻辑值
    inline bool as_bool() {
        return mut_val ? yyjson_mut_get_bool(mut_val) : NULL;
    }

    //@备注 以数值方式取出当前对象属性 yyjson_get_num
    //@别名 取数值()
    //@返回 双浮点型数值
    inline double as_num() {
        return mut_val ? yyjson_mut_get_num(mut_val) : NULL;
    }

    //@备注 以整数值方式取出当前对象属性 yyjson_get_int
    //@别名 取整数值()
    //@返回 整数值(int)
    inline int as_int() {
        return mut_val ? yyjson_mut_get_int(mut_val) : NULL;
    }

    //@备注 以小数方式取出当前对象属性 yyjson_get_real
    //@别名 取小数值()
    //@返回 双浮点型数值
    inline double as_real() {
        return mut_val ? yyjson_mut_get_real(mut_val) : NULL;
    }

    //@备注 以长整型方式取出当前对象属性 yyjson_get_sint
    //@别名 取长整型值()
    //@返回 长整型
    inline uint64_t as_sint64() {
        return mut_val ? yyjson_mut_get_sint(mut_val) : NULL;
    }

    //@备注 以无符号长整型方式取出当前对象属性 yyjson_get_uint
    //@别名 取无符号长整型值()
    //@返回 长整型
    inline uint64_t as_uint64() {
        return mut_val ? yyjson_mut_get_uint(mut_val) : NULL;
    }

    //@备注 以字节集方式取出当前对象属性 yyjson_mut_get_raw 注意,这不是通用方法,只有对象类型为 raw 时才有效,例: { "raw":asdafwx } 没有双引号标记的字符串
    //@别名 取RAW()
    //@返回 字节集
    inline CXBytes as_bytes() {
        CXBytes cxbytes = CXBytes();
        const char* bytes = mut_val ? yyjson_mut_get_raw(mut_val) : NULL;
        if (bytes) {
            cxbytes.set(bytes, yyjson_mut_get_len(mut_val));
        }
        return cxbytes;
    }

    //@备注 以字节集方式取出当前对象属性 yyjson_get_raw 注意,这不是通用方法,只有对象类型为 raw 时才有效,例: { "raw":asdafwx } 没有双引号标记的字符串
    //@别名 取通用文本()
    //@返回 文本型 通用文本,数值自动转换文本,逻辑值显示true false, null值,如果是对象则为空
    CXTextA as_text();

    //@备注 解析Json文本,解析成功会移除当前对象节点树,改为解析节点信息.原节点的数据如果有其他指向,还是可以使用的
    //@别名 解析(json)
    //@返回 成功true  失败false
    bool parse(const char* szJson);

    //@备注 判断当前对象属性值是否存在
    //@别名 是否存在()
    //@返回 存在true  不存在false
    bool exist() const { return mut_lv == 0 || mut_val != NULL; }
};