#ifndef JSON_WRAP_H
//@隐藏{
#define JSON_WRAP_H
#include "json.h"
//@隐藏}

//@模块名称 JSON操作
//@版本  1.0
//@日期  2020-10-23
//@作者  XCGUI
//@QQ  154460336
//@模块备注  用户可自行更改增加修改接口, JSONCPP
//@依赖  module_base.h


//@隐藏{
typedef  Json::Value   CJsonValue;
//@隐藏}

/*@声明
//@src  "json_reader.cpp"
//@src  "json_value.cpp"
//@src  "json_writer.cpp"

//@别名  JSON值类
class CJsonValue
{
public:
	//@别名  取类型()
	ValueType type();
	//@别名  是否为空()
	bool empty();
	//@别名  取成员数()
	UINT size();
	//@别名  清空()
	void clear();
	
	//@备注  获取值对象
	//@参数  key   名称
	//@返回  值对象
	//@别名  取对象(名称)
	CJsonValue get(const char* key);
	
	//@别名 取文本()
	string  getString(const char* key);
	//@别名  取整型()
	int  getInt(const char* key);
	//@别名  取无符号整型()
	double getUInt(const char* key);
	//@别名  取浮点型()
	double getDouble(const char* key);
	//@别名  取布尔型()
	double getBool(const char* key);
	//@别名  取数组文本()
	string getArrayString(int index);
	//@别名  取数组整型()
	int     getArrayInt(int index);
	//@别名  取数组无符号整型()
	UINT getArrayUInt(int index);
	//@别名  取数组浮点型()
	double getArrayDouble(int index);
	//@别名  取数组布尔型()
	bool    getArrayBool(int index);
  
	//@别名  置内容()
	void set(...); //set(char* key, T value) 设置内容, 值自动匹配
	//@别名  插入内容()
	bool insert(...);  //insert(int index,  T value) 数组操作, 值自动匹配类型
	//@别名  添加内容()
	CJsonValue append(...);  //append(T value) 数组操作, 值自动匹配类型
	//@别名  移除()
	void remove(const char* key);
	//@别名   移除索引()
	bool removeIndex(int index);
	
	//@别名  判断文本()
	bool isString();
	//@别名  判断整型()
	bool isInt();
	//@别名  判断无符号整型()
	bool isUInt();
	//@别名  判断浮点型()
	bool isDouble();
	//@别名  判断数组()
	bool isArray();
	//@别名  判断布尔型()
	bool isBool();
	//@别名  判断对象()
	bool isObject();
	//@别名  判断空()
	bool isNull();

	//@别名 到单文本指针()
	const char* asCString();

	//@别名 到文本()
	String asString();
	//@别名  到整型()
	Int asInt();
	//@别名  到正整型()
	UInt asUInt();
	//@别名  到浮点型()
	float asFloat();
	//@别名  到双浮点型()
	double asDouble();
	//@别名  到逻辑型()
	bool asBool();

	//@别名  到长整型()
	Int64 asInt64();
	//@别名  到正长整型()
	UInt64 asUInt64();

};
*/

//@别名  JSON读取类
class CJsonReader
{
public:
	CJsonReader() { _reader = NULL; }
	~CJsonReader() { delete _reader; }
	//@别名  解析()
	bool parse(const char* pString, CJsonValue &root)
	{
		Json::CharReaderBuilder builder;
		if (NULL == _reader)
			_reader = builder.newCharReader();
		return _reader->parse(pString, pString + strlen(pString), &root, &_err);
	}
	//@别名  取错误()
	const char* getErr() { return _err.c_str(); }
	JSONCPP_STRING   _err;
	Json::CharReader* _reader;
};


#endif // JSON_WRAP_H
