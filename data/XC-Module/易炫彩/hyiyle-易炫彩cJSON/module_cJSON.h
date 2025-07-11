#ifndef cJSONHelp__h
//@隐藏{
#define cJSONHelp__h
#include "cJson.h"
//@隐藏}


//@模块名称 易炫彩cJSON
//@版本  1.1
//@日期  2020-11-17
//@作者  Huiyi
//@模块备注  基于cJSON的封装版本
// 简化了操作流程,支持简易表达式
// 如:json[2].name
// 支持表达式自动创建对象
// 使用相关问题可前往QQ群: 594165459 反馈

//@隐藏{
typedef struct JSONTYPESTUCT
{
	//@别名  类型
	int Type;
	//@别名  内容
	char* name;
}_JSONTYPESTUCT, * PHJSONTYPESTUCT;

//@隐藏}

//@src "cJson.c"
#include "module_base.h"


//@分组{	cJSON常量
#define cJSON_Invalid (0)
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)
#define cJSON_Raw    (1 << 7)
//@分组}

//@别名 cJSON类
class cJSONH {

public:

	//@备注 创建一个空的JSON对象 如果已经存在一个旧对象则会清空所有数据
	//@返回 返回bool结果
	//@别名 创建()
	bool Create();
	
	//@备注  释放对象
    //@别名  释放()
	void Delete();
	
	//@备注  取对象指针
    //@返回  返回类内绑定的JSON对象指针
    //@别名  取对象指针()
	cJSON* GetObject();

    //@备注  设置对象指针,如果之前存在对象,旧对象会自动释放
    //@参数  Object  要设置的指针
    //@别名  置对象指针(cJSON指针)
	void SetObject(cJSON* Object);
	
	//@备注  获取最后的错误文本
    //@返回  最后一次的错误信息
    //@别名  取错误文本()
	const char* GetErrorString();

	//@备注  创建一个空的cJSON对象	静态方法
    //@返回  创建的对象指针
    //@别名  创建对象()
	cJSON* CreateObject();

	//@备注  创建一个空的cJSON数组对象	静态方法
    //@返回  创建的数组对象指针
    //@别名  创建数组对象()
	cJSON* CreateArray();

	//@备注  创建一个cJSON NULL 对象	静态方法
    //@返回  创建的对象指针
    //@别名  创建空对象()
	cJSON* CreateNull();

	//@备注  创建一个cJSON bool 对象	静态方法
    //@返回  创建的对象指针
    //@别名  创建逻辑对象()
	cJSON* CreateBool(bool);

	//@备注  建一个cJSON string 对象	静态方法
	//@参数  string  用于创建对象的字符串
    //@返回  创建的对象指针
    //@别名  创建文本对象()
	cJSON* CreateString(const char* string = "");

	//@备注  创建一个cJSON数值对象	静态方法
    //@返回  创建的对象指针
    //@别名  创建数值对象()
	cJSON* CreateNumber(double num = 0);

	//@备注  从字节流解析Json,如果之前已经解析过,则会自动释放
	//@参数  JsonStr  指向json字符串的变量
    //@返回  解析结果
    //@别名  解析()
	bool Parse(const char* JsonStr);

	//@备注  获取转成文本后的Json数据
	//@参数  formatted  是否对返回的信息进行格式化
    //@返回  编排成文本形式的Json数据
    //@别名  取Json文本()
	CXTextA GetJsonforString(const char* path = "",bool formatted=false);

	//@备注  获取键值的类型
	//@参数  Path  属性所在路径 例如:root.arr[0].key
    //@返回  类型常量,对应 cJSON_
    //@别名  取类型()
	int GetItemType(const char* path = "");

	//@备注  获取父级对象指针
	//@参数  Path  属性所在路径 例如:root.arr[0].key
    //@返回  父级对象指针地址,内部指针,不会构造.
    //@别名  取父()
	cJSON* GetParent(const char* path = "");

	//@备注  获取数组成员数量
	//@参数  Path  属性所在路径 例如:root.arr[0].key
    //@返回  属性下数组成员数量
    //@别名  取成员数()
	int GetArraySize(const char* path = "");

	//@备注  分离节点
	//@参数  Path  		属性所在路径 例如:root.arr[0].key
	//@参数  ItemName 	属性名
	//@参数: Case 		属性名是否大小写敏感
    //@返回  分离的节点指针
    //@别名  分离()
	cJSON* DetachItem(const char* path, const char* ItemName="", bool Case=false);

	//@备注  删除节点下属性
	//@参数  Path	属性所在父路径 例如:root.arr[0]
	//@参数  Item	属性名
    //@别名  删除()
	void DeleteItem(const char* path = "", const char* Item="");

 	//@简述  删除成员
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@参数  which [in]		成员下标
	//@别名  删除成员()
	void DeleteItemFromArray(const char* path = "", int which=0);

	//@简述  清空值，包括所有下级属性和成员
	//@参数  Path [in]		父属性路径 例如:root.arr[0]
	//@别名  清除()
	void Clear(const char* path = "");

	//@简述  取对象属性
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@返回  指向对应属性的指针
	//@别名  取属性()
	cJSON* GetAttributes(const char* path = "");

	//@简述  取自身属性名
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@返回  属性名字符串
	//@别名  取属性名()
	const char* GetItemName(const char* path = "");

	//@简述  添加数组成员
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@参数  item [in]		数组成员指针
	//@返回  bool
	//@别名  添加成员()
	cJSON_bool AddItemToArray(const char* path = "", cJSON* item = NULL);

	//@简述  设置对象属性
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@参数  Value [in]		属性指针
	//@返回  bool
	//@别名  置属性()
	cJSON_bool SetObjectValue(const char* Path = "", cJSON* Value=NULL);

	//@简述  获取对象属性
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@返回  路径所指向的属性指针
	//@别名  取属性()
	cJSON* GetObject(const char* Path = "");

	//@简述  添加成员
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@返回  路径所指向的属性指针
	//@别名  添加成员()
	cJSON_bool AddArrayItem(const char* Path = "",cJSON* Item=NULL);

	//@简述  属性是否存在
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@返回  bool
	//@别名  是否存在()
	bool IfThereIs(const char* Path = "");

	//@简述  获取对应属性的String值
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@返回  对应的字符串,失败返回空
	//@别名  取文本()
	const char* GetStringValue(const char* Path = "");

	//@简述  设置对应键值的文本值
	//@参数  Path [in]		属性路径 例如:root.arr[0].key	不存在会自行创建
	//@参数  String [in]		需要设置的值
	//@返回  bool
	//@别名  置文本()
	cJSON_bool SetStringValue(const char* Path = "", const char* String="");

	//@简述  设置对应键值的数值
	//@参数  Path [in]		属性路径 例如:root.arr[0].key	不存在会自行创建
	//@参数  num [in]		需要设置的值
	//@返回  bool
	//@别名  置数值()
	cJSON_bool SetNumberValue(const char* Path = "", double num=0);

	//@简述  取对应键值的数值
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@返回  double
	//@别名  取数值()
	double GetNumberValue(const char* Path = "");

	//@简述  设置对应键值的逻辑值
	//@参数  Path [in]		属性路径 例如:root.arr[0].key	不存在会自行创建
	//@参数  bl [in]		需要设置的值
	//@返回  bool
	//@别名  置逻辑值()
	cJSON_bool SetBoolValue(const char* Path = "", cJSON_bool bl=false);

	//@简述  取对应键值的逻辑值
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@返回  bool
	//@别名  取逻辑值()
	cJSON_bool GetBoolValue(const char* Path = "");

	//@简述  取所有属性名
	//@参数  Path [in]		属性路径 例如:root.arr[0].key
	//@参数  retnamearr [in_out]		存储数据的列表
	//@返回  retnamearr内子元素数目
	//@别名  枚举属性名()
	int GetAllObjectName(CXVector<CXTextA> &retnamearr,const char* Path="" );

	//@简述  复制节点对象
	//@参数  Path [in]		属性路径 例如:root.arr[0]
	//@返回  构造的新的对象，需要自己释放
	//@别名  复制()
	cJSON* copy (const char* Path = "");
	
//@隐藏{
	cJSONH();
	cJSONH(const char*);
	~cJSONH();
//@隐藏}
private:
	bool IfInitialize = false;
	cJSON* root = NULL;
	const char* LastError="";

	cJSON* PathParsed(cJSON* root, const char* path);
	std::vector<JSONTYPESTUCT> PathParsedOrCreate(const char* path);
	BOOL SetValueOfJsonArr(cJSON* root, std::vector<JSONTYPESTUCT> jsonarr, int type, void* dataaddress);
	void ObjectNameList(cJSON* object, CXVector<CXTextA>& retnamearr);
	
};

//@src "cJsonHelp.cpp"

#endif