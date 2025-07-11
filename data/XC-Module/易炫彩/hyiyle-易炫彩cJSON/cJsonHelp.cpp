//#include "cJSON.h"
#include "module_cJSON.h"

cJSONH::cJSONH(void) {
	Create();
}
cJSONH::cJSONH(const char*str){
	Create();
	Parse(str);
};
//@ 销毁自身
cJSONH::~cJSONH(void) {
	if (root!=NULL) {
		cJSON_Delete(root);
	}
}

//@ 取错误文本
const char* cJSONH::GetErrorString() {
	return LastError;
}

//@ 创建对象
bool cJSONH::Create() {
	if (root != NULL) {
		cJSON_Delete(root);
	}
	root = cJSON_CreateObject();
	if (root == NULL) {
		LastError = cJSON_GetErrorPtr();
		return false;
	}
	return true;
}

//@ 释放数据
void cJSONH::Delete() {
	cJSON_Delete(root);
	root = NULL;
}

//@ 解析数据
bool cJSONH::Parse(const char* JsonStr) {
	if (root != NULL) {
		cJSON_Delete(root);
	}
	root = cJSON_Parse(JsonStr);
	if (root == NULL) {
		LastError = cJSON_GetErrorPtr();
		return false;
	}
	IfInitialize = true;
	return true;
}

//@ 取对象指针
cJSON* cJSONH::GetObject() {
	return root;
}

//@ 设置对象指针
void cJSONH::SetObject(cJSON* Object) {
	if (root!=NULL) {
		cJSON_Delete(root);
	}
	root = Object;
}

//@ 创建对象
cJSON* cJSONH::CreateObject() {
	return cJSON_CreateObject();
}

//@ 创建数组对象
cJSON* cJSONH::CreateArray() {
	return cJSON_CreateArray();
}

//@ 创建空对象
cJSON* cJSONH::CreateNull() {
	return cJSON_CreateNull();
}

//@ 创建逻辑对象
cJSON* cJSONH::CreateBool(bool boolean) {
	return cJSON_CreateBool(boolean);
}

//@ 创建文本对象
cJSON* cJSONH::CreateString(const char* string) {
	return cJSON_CreateString(string);
}

//@ 创建数值对象
cJSON* cJSONH::CreateNumber(double num) {
	return cJSON_CreateNumber(num);
}

//@ 取Json数据文本
CXTextA cJSONH::GetJsonforString(const char* path,bool formatted) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL) {
		return "{}";
	}
	else {
		CXTextA r;
		if (formatted) {
			auto str=cJSON_Print(ltp);
			r = str;
			cJSON_free(str);
			return r;
		}
		else {
			auto str=cJSON_PrintUnformatted(ltp);
			r = str;
			cJSON_free(str);
			return r;
		}
	}
}

//@ 取类型
int cJSONH::GetItemType(const char* path){
	cJSON* ltp = PathParsed(root, path);
	if (ltp==NULL) {
		return 0;
	}
	return ltp->type;
}

//@ 取父级
cJSON* cJSONH::GetParent(const char* path) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL) {
		return 0;
	}
	return ltp->prev;
}

//@ 取成员数
int cJSONH::GetArraySize(const char* path) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL) {
		return 0;
	}
	return cJSON_GetArraySize(ltp);
}

//@ 分离
cJSON* cJSONH::DetachItem(const char* path, const char* ItemName,bool Case) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL) {
		return NULL;
	}
	if (Case) {
		return cJSON_DetachItemFromObject(ltp,ItemName);
	}
	else {
		return cJSON_DetachItemFromObjectCaseSensitive(ltp, ItemName);
	}
}

//@ 移除属性
void cJSONH::DeleteItem(const char* path, const char* Item) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp != NULL) {
		cJSON_DeleteItemFromObject(ltp, Item);
	}
}

//@ 移除成员
void cJSONH::DeleteItemFromArray(const char* path, int which) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp != NULL) {
		cJSON_DeleteItemFromArray(ltp, which);
	}
}

//@ 清空
void cJSONH::Clear(const char* path) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp==NULL) {
		return;
	}
	cJSON_Delete(ltp);
}

//@ 取属性
cJSON* cJSONH::GetAttributes(const char* path) {
	return PathParsed(root, path);
}

//@ 取属性名
const char* cJSONH::GetItemName(const char* path) {
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL || ltp->string == NULL) {
		return "";
	}
	return ltp->string;
}

//@ 添加成员
cJSON_bool cJSONH::AddItemToArray(const char* path, cJSON* item) {
	if (item!=NULL)
	{
		return false;
	}
	cJSON* ltp = PathParsed(root, path);
	if (ltp == NULL || ltp->string == NULL) {
		return false;
	}
	return cJSON_AddItemReferenceToArray(ltp, item);
}

//@ 设置属性
cJSON_bool cJSONH::SetObjectValue(const char* Path, cJSON* Value) {
	if (root == NULL) {
		return false;
	}
	cJSON_bool ret = false;
	std::vector<JSONTYPESTUCT> bankstr = PathParsedOrCreate(Path);
	return SetValueOfJsonArr(root, bankstr, cJSON_Object, (void*)Value);
}

//@ 获取属性
cJSON* cJSONH::GetObject(const char* Path) {
	return PathParsed(root, Path);
}

//@ 数组添加成员
cJSON_bool cJSONH::AddArrayItem(const char* Path, cJSON* Item) {
	if(Item==NULL)
	{
		return false;
	}
	cJSON_bool ret = false;
	std::vector<JSONTYPESTUCT> bankstr = PathParsedOrCreate(Path);
	return SetValueOfJsonArr (root, bankstr, cJSON_Array, (void*)Item);
}

//@ 是否存在
bool cJSONH::IfThereIs(const char* Path) {
	return PathParsed (root, Path) != NULL;
}

//@ 设置文本数据
cJSON_bool cJSONH::SetStringValue(const char* Path, const char* String) {
	if (root == NULL) {
		return false;
	}
	cJSON_bool ret = false;
	std::vector<JSONTYPESTUCT> bankstr = PathParsedOrCreate(Path);
	return SetValueOfJsonArr(root, bankstr,cJSON_String,(void*)String);
}

//@ 取文本数据
const char* cJSONH::GetStringValue(const char* Path) {
	cJSON* ret = PathParsed(root, Path);
	if (ret != NULL) {
		return ret->valuestring;
	}
	else {
		return "";
	}
	return "";
}

//@ 设置数值数据
cJSON_bool cJSONH::SetNumberValue(const char* Path, double num) {
	if (root == NULL) {
		return false;
	}
	cJSON_bool ret = false;
	std::vector<JSONTYPESTUCT> bankstr = PathParsedOrCreate(Path);
	return SetValueOfJsonArr(root, bankstr, cJSON_Number, (void*)&num);
}

//@ 取数值数据
double cJSONH::GetNumberValue(const char* Path) {
	cJSON* ret = PathParsed(root, Path);
	if (ret != NULL) {
		return ret->valueint;
	}
	else {
		return 0;
	}
	return 0;
}

//@ 设置逻辑数据
cJSON_bool cJSONH::SetBoolValue(const char* Path, cJSON_bool bl) {
	if (root == NULL) {
		return false;
	}
	cJSON_bool ret = false;
	std::vector<JSONTYPESTUCT> bankstr = PathParsedOrCreate(Path);
	return SetValueOfJsonArr(root, bankstr, cJSON_False, (void*)&bl);
	
}

//@ 取逻辑数据
cJSON_bool cJSONH::GetBoolValue(const char* Path) {
	cJSON* ret = PathParsed(root, Path);
	if (ret != NULL) {
		return ret->type == cJSON_True;
	}
	else {
		return 0;
	}
	return 0;
}

//@ 取属性名列表
int cJSONH::GetAllObjectName(CXVector<CXTextA> &retnamearr,const char* Path) {
	cJSON* ret = PathParsed(root, Path);
	if (ret != NULL) {
		retnamearr.clear();
		ObjectNameList(ret, retnamearr);
		return retnamearr.size();
	}
	else {
		retnamearr.clear();
		return 0;
	}
	retnamearr.clear();
	return 0;
}

//@ 复制对象
cJSON* cJSONH::copy(const char* Path) {
	cJSON* ret = PathParsed(root, Path);
	if (ret != NULL) {
		return cJSON_Duplicate(ret,true);
	}
	else {
		return 0;
	}
}


//						==================
//				==================================
//						==================

//@ 由路径数组设置数据值,不存在的路径会自动创建
BOOL cJSONH::SetValueOfJsonArr(cJSON* root, std::vector<JSONTYPESTUCT> jsonarr,int type,void* dataaddress) {
	cJSON* ltps = NULL;
	cJSON* cpm = root;
	BOOL ret = false;
	//取出表达式除了最后一个以外的对象指针
	for (size_t i = 0; i < jsonarr.size() - 1; i++) {
		if (jsonarr[i].Type == cJSON_Object)
		{
			//Object
			ltps = cJSON_GetObjectItem(cpm, jsonarr[i].name);
			if (ltps == NULL)
			{
				ltps = cJSON_CreateObject();
				if (cJSON_AddItemToObject(cpm, jsonarr[i].name, ltps))
				{
					cpm = ltps;
				}
				else {
					return false;
				}
			}
			else {
				cpm = ltps;
			}
		}
		else if (jsonarr[i].Type == cJSON_Array)
		{
			//arr
			ltps = cJSON_GetObjectItem(cpm, jsonarr[i].name);
			if (ltps == NULL) {
				ltps = cJSON_CreateArray();
				ret = cJSON_AddItemToObject (cpm, jsonarr[i].name, ltps);
				if (!ret) {
					return ret;
				}
				
			}
			cpm = ltps;
			int aindex = atoi(jsonarr[i+1].name) + 1;
			int asize = cJSON_GetArraySize(cpm);
			if (asize < aindex) {
				cJSON_bool ift;
				for (int k = asize; k < aindex; k++) {
					ltps = cJSON_CreateObject();
					ift = cJSON_AddItemToArray(cpm, ltps);
					if (!ift) {
						return ift;
					}
					//cpm = ltps;
				}
			}
			cpm = cJSON_GetArrayItem(cpm, aindex - 1);
			free(jsonarr[i].name);
			if (cpm == NULL) {
				return false;
			}
			i++;
		}
		free(jsonarr[i].name);
	}
	//设置或创建上面取出的地址对象
	int sindex = jsonarr.size() - 1;
	ltps = cJSON_GetObjectItem(cpm, jsonarr[sindex].name);
	if (ltps == NULL) {
		//不存在
		if (type == cJSON_String) {
			ltps = cJSON_CreateString((const char*)dataaddress);
			cJSON_AddItemToObject(cpm, jsonarr[sindex].name, ltps);
			//(const char*)dataaddress
			ret = true;
		}
		else if (type == cJSON_Number) {
			ltps = cJSON_CreateNumber(*(double*)dataaddress);
			cJSON_AddItemToObject(cpm, jsonarr[sindex].name, ltps);
			ret = true;
		}
		else if (type == cJSON_Object) {
			ret = cJSON_AddItemToObject(cpm, jsonarr[sindex].name, (cJSON*)dataaddress);
			//cJSON_ReplaceItemInObject(cpm, jsonarr[sindex].name,(cJSON*)dataaddress);
			//cJSON_AddNumberToObject(cpm, jsonarr[sindex].name, *(double*)dataaddress);
		}
		else if (type == cJSON_Array) {
			ret = cJSON_AddItemToArray(cpm, (cJSON*)dataaddress);
		}
		else if (type == cJSON_True || type == cJSON_False) {
			ltps = cJSON_CreateBool(*(cJSON_bool*)dataaddress);
			ret = cJSON_AddItemToObject(cpm, jsonarr[sindex].name, ltps);
		}
	}
	else {
		//存在
		if (type == cJSON_String) {
			std::string fcps = (const char*)dataaddress;
			free(ltps->valuestring);
			ltps->valuestring = (char*)malloc(fcps.length() + 1);
			if (ltps->valuestring!=NULL) {
				//strcpy(ltps->valuestring, fcps.c_str());
				strcpy_s(ltps->valuestring, fcps.length() + 1, fcps.c_str());
				ret = true;
			}
		}
		else if (type == cJSON_Number) {
			ltps->valuedouble = *(double*)dataaddress;
			ret = true;
		}
		else if (type == cJSON_Object) {
			ret = cJSON_ReplaceItemInObject(cpm, jsonarr[sindex].name, (cJSON*)dataaddress);
		}
		else if (type == cJSON_Array) {
			//ret = cJSON_AddItemToArray(cpm, (cJSON*)dataaddress);
			ret = cJSON_ReplaceItemInArray(cpm, atoi(jsonarr[sindex].name) , (cJSON*)dataaddress);
		}
		else if (type == cJSON_True || type == cJSON_False) {
			ltps->valueint = *(cJSON_bool*)dataaddress;
			ret = true;
		}
		
	}
	free(jsonarr[sindex].name);
	return ret;
}

//@ 由路径取对应节点
cJSON* cJSONH::PathParsed(cJSON* root, const char* path) {
	std::string stpath = path;
	if (path == NULL) {
		return root;
	}
	size_t StrLen			///< 路径长度
		= stpath.length();
	if (StrLen == 0) {
		return root;
	}
	
	size_t OldSubscript		///< 上一个标记点位置
		= 0;
	size_t pos		///< 标记点当前位置
		= 0;
	bool inArray=false;		///< 上一个标记点是否是数组头 [
	cJSON* ctmp = root;
	bool hasName = false;
	bool hasIndex = true;
	size_t namePos = 0,nameLen,indexPos = 0;
	
	while (pos <= StrLen)
	{
		char wchar = stpath[pos];
		if (wchar == '\\') {
			char nextchar = stpath[pos + 1];
			if (nextchar == '.'
			|| nextchar == '['
			|| nextchar == ']'
			|| nextchar == '\\'
			) {
				stpath.erase(pos,1);
				--StrLen;
			}
		}
		else if (wchar == '.' || pos == StrLen)	//.或者结尾
		{
			hasName = namePos < pos;
			if (hasName) {
				nameLen = pos - namePos;
				//printf( ".:%s\n", stpath.substr(namePos, nameLen).c_str());
				ctmp = cJSON_GetObjectItem(ctmp, stpath.substr(namePos, nameLen).c_str());
			}
			namePos = pos + 1;
		}
		else if (wchar == '[')
		{
			indexPos = pos + 1;
			hasIndex = true;
			hasName = namePos < pos;
			if (hasName) {
				nameLen = pos - namePos;
				//printf("[:%s\n", stpath.substr(namePos, nameLen).c_str());
				ctmp = cJSON_GetObjectItem(ctmp, stpath.substr(namePos, nameLen).c_str());
			}
			namePos = pos + 1;
		}
		else if (wchar == ']')
		{
			if (hasIndex) {
				nameLen = pos - indexPos;
				//printf("]:%d\n", atoi(stpath.substr(namePos, nameLen).c_str()));
				ctmp = cJSON_GetArrayItem(ctmp, atoi(stpath.substr(namePos, nameLen).c_str()));
			}
			namePos = pos + 1;
		}
		if (ctmp==NULL) {
			return NULL;
		}
		++pos;
		//OldSubscript = Subscript;
		
	}
	return ctmp;
}

//@ 将路径转为数组
std::vector<JSONTYPESTUCT> cJSONH::PathParsedOrCreate(const char* path) {
	std::string stpath = path;
	std::vector<JSONTYPESTUCT> ret;
	JSONTYPESTUCT le;
	if (path == NULL) {
		return ret;
	}
	size_t StrLen			///< 路径长度
		= stpath.length();
	if (StrLen == 0) {
		return ret;
	}

	size_t OldSubscript		///< 上一个标记点位置
		= 0;
	size_t pos		///< 标记点当前位置
		= 0;
	bool inArray = false;		///< 上一个标记点是否是数组头 [
	bool hasName = false;
	bool hasIndex = true;
	size_t namePos = 0, nameLen, indexPos = 0;

	while (pos <= StrLen)
	{
		char wchar = stpath[pos];
		if (wchar == '\\') {
			char nextchar = stpath[pos + 1];
			if (nextchar == '.'
				|| nextchar == '['
				|| nextchar == ']'
				|| nextchar == '\\'
				) {
				stpath.erase(pos, 1);
				--StrLen;
			}
		}
		else if (wchar == '.' || pos == StrLen)	//.或者结尾
		{
			hasName = namePos < pos;
			if (hasName) {
				nameLen = pos - namePos;
				//printf( ".:%s\n", stpath.substr(namePos, nameLen).c_str());
				le.Type = cJSON_Object;
				int slen = stpath.substr(namePos, nameLen).length()+1;
				le.name = (char*)malloc(slen);
				if (le.name!=NULL) {
					//strcpy(le.name, stpath.substr(namePos, nameLen).c_str());
					strcpy_s(le.name, slen, stpath.substr(namePos, nameLen).c_str());
				}
				ret.push_back(le);
			}
			namePos = pos + 1;
		}
		else if (wchar == '[')
		{
			indexPos = pos + 1;
			hasIndex = true;
			hasName = namePos < pos;
			if (hasName) {
				nameLen = pos - namePos;
				//printf("[:%s\n", stpath.substr(namePos, nameLen).c_str());
				le.Type = cJSON_Array;
				int slen = stpath.substr(namePos, nameLen).length() + 1;
				le.name = (char*)malloc(slen);
				if (le.name != NULL) {
					//strcpy(le.name, stpath.substr(namePos, nameLen).c_str());
					strcpy_s(le.name, slen,stpath.substr(namePos, nameLen).c_str());
				}
				ret.push_back(le);
			}
			namePos = pos + 1;
		}
		else if (wchar == ']')
		{
			if (hasIndex) {
				nameLen = pos - indexPos;
				//printf("]:%d\n", atoi(stpath.substr(namePos, nameLen).c_str()));
				le.Type = cJSON_Number;
				int slen = stpath.substr(namePos, nameLen).length() + 1;
				le.name = (char*)malloc(slen);
				if (le.name != NULL) {
					//strcpy(le.name, stpath.substr(namePos, nameLen).c_str());
					strcpy_s(le.name, slen, stpath.substr(namePos, nameLen).c_str());

				}
				ret.push_back(le);
			}
			namePos = pos + 1;
		}
		++pos;
		//OldSubscript = Subscript;

	}
	return ret;
}

//@ 枚举属性名
void cJSONH::ObjectNameList (cJSON* object, CXVector<CXTextA>& retnamearr) {
		cJSON* current_element = NULL;
		std::string ltps;
		current_element = object->child;
		while ((current_element != NULL))
		{
			if (current_element->string != NULL) {
				ltps = current_element->string;
				retnamearr.add(current_element->string);
			}
			current_element = current_element->next;
		}
}


