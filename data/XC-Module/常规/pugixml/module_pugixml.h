#pragma once
#ifndef   XC_PUGIXML_WRAP_H
#define  XC_PUGIXML_WRAP_H

#include "pugiconfig.h"
#include "pugixml.h"
using namespace pugi;

//@模块名称 pugixml
//@版本  1.0
//@日期  2020-10-23
//@作者  XCGUI
//@模块备注  pugixml
//@依赖  module_base.h

/*@声明
//@src "pugixml.cpp"

//@别名 XML解析结果类
class xml_parse_result
{
	//@别名 状态
	int status;  //解析结果状态
};
//@别名  XML属性类
class xml_attribute
{
	//@别名  值()
	const wchar_t* value();
};
//@别名 XML文本类
class xml_text
{
	//@别名 获取()
	const wchar_t* get();
};

//@别名  XML节点类
class xml_node
{
	//@别名  名称()
	const wchar_t* name();
	
	//@别名 属性(名称)
	xml_attribute attribute(wchar_t* name);
	
	//@别名 下一个()
	xml_node next_sibling();
	
	//@别名 上一个()
	xml_node previous_sibling();
	
	//@别名  第一个子节点()
	xml_node first_child();
	
	//@别名 最后一个()
	xml_node last_child();
	
	//@别名  值()
	const wchar_t* value();
	
	//@别名 文本()
	xml_text text();
};

class xml_document : public xml_node
{
};
*/

//@别名 XML文档类
class CDoc :public xml_document
{
public:
	//@别名 载入(内容, 大小)
	xml_parse_result load_buffer(const wchar_t* contents, size_t size)
	{
		return xml_document::load_buffer(contents, size*2);
	}
/*@声明
	//@别名 载入文件(文件路径)
	xml_parse_result load_file(const wchar_t* path);
*/
	//save_file
	//reset
};

#endif
