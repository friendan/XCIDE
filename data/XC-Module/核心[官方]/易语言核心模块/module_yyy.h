#pragma once
#ifndef  XCL_YYY_H
//@隐藏{
#define  XCL_YYY_H
//@隐藏}

//@模块名称  易语言核心模块
//@版本  1.0
//@日期  2023-12-25
//@作者  XCGUI
//@QQ  154460336 
//@模块备注  对应:易语言-系统核心支持库, 部分接口由情缘封装
//以下接口见基础模块:
//环境变量操作, 取命令行(), 取运行目录(), 读环境变量(), 写环境变量() ,多项选择(), 取颜色值(), 置入代码()
//到文本(), 处理事件(), 延时(), 延迟(), 选择()

//@依赖  module_base.h


//@模块信息结束

#pragma warning(disable:4996)

#if XC_MOUDLE
#include "module_base.h"
#endif
#include <Regex>
#include <sstream>

//@src  "module_yyy.cpp"
//@src  "string.cpp"
//@src  "StringClassRegex.cpp"
//@src  "array.cpp"
//@src  "coding.cpp"
//@src  "base.cpp"


//@隐藏{

const wchar_t* wcsistr(const wchar_t* str, const wchar_t* substr);
int  MyMemCmp2(unsigned char* a, unsigned char* b, int len);
int  is_prefix(unsigned char* word, int wordlen, int pos);
int  suffix_length(unsigned char* word, int wordlen, int pos);
void make_delta2(int* delta2, unsigned char* pat, int patlen);
void make_delta1(int* delta1, unsigned char* pat, int patlen);
int  boyer_moore(unsigned char* string, int stringlen, unsigned char* pat, int patlen);
int  mymemchr(unsigned char* pSrc, int nLen, unsigned char Des);
int  myinstring(unsigned char* src, int slen, unsigned char* des, int dlen);

//@隐藏}

//@分组{ 算术运算

//以下为cmath库封装,参见 https://learn.microsoft.com/zh-cn/cpp/standard-library/cmath?view=msvc-170

/*@声明
//@备注   计算 arg 的弧（反）正弦主值
//@别名   运算_取反余弦(弧度值)
float acos(...);
//@别名   运算_取反余弦f(弧度值)
float acosf(float x);
//@别名   运算_取反正弦(弧度值)
float asin(float x);
//@别名   运算_取反正弦f(弧度值)
float asinf(float x);
//@别名   运算_取反正切(弧度值)
float atan(float x);
//@别名   运算_取反正切f(弧度值)
float atanf(float x);
//@别名   运算_取反正切2(x,y)
float atan2(float y, float x);
//@别名   运算_取反正切2f(x,y)
float atan2f(float y, float x);
//@别名   运算_取余弦(弧度值)
float cos(float x);
//@别名   运算_取余弦f(弧度值)
float cosf(float x);
//@别名   运算_取正弦(弧度值)
float sin(float x);
//@别名   运算_取正弦f(弧度值)
float sinf(float x);
//@别名   运算_取正切(弧度值)
float tan(float x);
//@别名   运算_取正切f(弧度值)
float tanf(float x);
//@别名   运算_取反双曲余弦(待取值)
float acosh(float x);
//@别名   运算_取反双曲余弦f(待取值)
float acoshf(float x);
//@别名   运算_取反双曲正弦h(待取值)
float asinh(float x);
//@别名   运算_取反双曲正弦hf(待取值)
float asinhf(float x);
//@别名   运算_反正切h(待取值)
float atanh(float x);
//@别名   运算_反正切hf(待取值)
float atanhf(float x);
//@别名   运算_取双曲余弦h(待取值)
float cosh(float x);
//@别名   运算_取双曲余弦hf(待取值)
float coshf(float x);
//@别名   运算_取双曲正弦h(待取值)
float sinh(float x);
//@别名   运算_取双曲正弦hf(待取值)
float sinhf(float x);
//@别名   运算_取双曲正切h(待取值)
float tanh(float x);
//@别名   运算_取双曲正切hf(待取值)
float tanhf(float x);
//@别名   运算_取E的N次方(幂)
float exp(float x);
//@别名   运算_取E的N次方f(幂)
float expf(float x);
//@别名   运算_取2的N次方(x)
float exp2(float x);
//@别名   运算_取2的N次方f(x)
float exp2f(float x);
//@别名   运算_取绝对值(x)
int abs(...);
//@别名   运算_取绝对值f(x)
double fabs(...);
//@别名   运算_求次方(x,幂)
double pow(...);
//@别名   运算_求平方根(x)
float sqrt(...);
*/


//@备注  返回按照指定的方式进行四舍五入运算的结果数值。
//@参数
//@参数  可以被省略。如果大于0，表示小数点右边应保留的位数；如果等于0，表示舍入到整数；如果小于0，表示小数点左边舍入到的位置。例如：四舍五入(1056.65, 1) 返回 1056.7； 四舍五入(1056.65, 0) 返回 1057； 四舍五入(1056.65, -1) 返回 1060。如果省略本参数，则默认为0。
//@别名  四舍五入(欲被四舍五入的数值, 被舍入的位置)
double 四舍五入(double value_, int pos=0);

//@备注 返回一个小数的整数部分。本命令与“取整”命令不相同之处为
//如果给定小数为负数，则本命令返回大于或等于该小数的第一个负整数，而“取整”命令则会返回小于或等于该小数的第一个负整数。例如，本命令将 - 7.8 转换成 - 7，而“取整”命令将 - 7.8 转换成 - 8。
//@别名 绝对取整(欲取整的小数)
inline int 绝对取整(double value_) { return (int)abs(value_); }

//@备注  返回一个小数的整数部分。本命令与“绝对取整”命令不相同之处为：
//如果给定小数为负数，则本命令返回小于或等于该小数的第一个负整数，而“绝对取整”命令则会返回大于或等于该小数的第一个负整数。例如，本命令将 - 7.8 转换成 - 8，而“绝对取整”命令将 - 7.8 转换成 - 7。
//@别名  取整(欲取整的小数)
inline int 取整(double value_) { return (int)value_; }


//@分组}

//#字节型； 2、#短整数型； 3、#整数型； 4、#长整数型； 5、#小数型； 6、#双精度小数型； 7、#逻辑型； 8、#日期时间型； 9、#子程序指针型； 10、#文本型


#define 且 &&
#define 或 ||
#define 取反(被反转的逻辑值) !被反转的逻辑值

//位运算
#define 位取反(欲取反的数值) ~欲取反的数值
#define 位与(位运算数值一,位运算数值二) (位运算数值一&位运算数值二)
#define 位或(位运算数值一,位运算数值二) (位运算数值一|位运算数值二)
#define 位异或(位运算数值一,位运算数值二) (位运算数值一^位运算数值二)
#define 左移(欲移动的整数,欲移动的位数) (欲移动的整数<<欲移动的位数)
#define 右移(欲移动的整数,欲移动的位数) (欲移动的整数>>欲移动的位数)
#define 合并整数(用作合并的整数1, 用作合并的整数2) ((用作合并的整数1 & 0xFFFF) | (用作合并的整数2 << 16))
#define 合并短整数(用作合并的整数1, 用作合并的整数2) ((用作合并的整数1 & 0xFF) | (用作合并的整数2 << 8))

/*@声明

//@备注 连续赋值(用作赋于的值, 被赋值的变量1, 被赋值的变量2, ...)
//参数数量不限, 参数必须是可赋值的变量
//例如: 连续赋值(10, 变量1, 变量2, 变量3) //相当于: 变量1=10, 变量2=10, 变量=10
void 连续赋值(...);
*/

//@隐藏{
template<typename TV, typename T>
void 连续赋值(TV value, T& var_)
{
	var_ = value;
}

template<typename TV, typename T, typename ... Args>
void 连续赋值(TV value, T& t, Args& ... args)
{
	连续赋值(value, t);
	连续赋值(value, args...);
}
//@隐藏}


//流程控制
// #define 如果(表达式) if(表达式){
// #define 否则 }else{
// #define 如果结束 }
// 
// #define 如果真(表达式) if(表达式){
// #define 如果真结束 }
// 
// #define 判断开始(表达式) if(表达式){
// #define 默认 }else{
// #define 判断(表达式) }else if(表达式){
// #define 判断结束 }


// #define 变量循环首(起始值,目标值,递增值,循环变量) for (int 循环变量 = 起始值; (递增值>0) ?  循环变量 <= 目标值 : 循环变量 >= 目标值; 循环变量 += 递增值){
// #define 变量循环尾() }
// #define 变量循环判断(循环变量, 目标值) (递增值>0) ?  循环变量 <= 目标值 : 循环变量 >= 目标值

// #define 判断循环首(表达式) while(表达式){
// #define 判断循环尾() }
// #define 循环判断首() do {
// #define 循环判断尾(表达式) } while(表达式);
// #define 计次循环首(循环次数,已循环次数记录变量) for(已循环次数记录变量=1;已循环次数记录变量<=循环次数;已循环次数记录变量++){
// #define 计次循环尾() }
// #define 变量循环首(起始值,目标值,递增值,循环变量) for(循环变量=起始值; 循环变量<=目标值;循环变量+=递增值){
// #define 变量循环尾() }
// #define 跳出循环() break;
// #define 到循环尾() continue;
// #define 返回(...) return __VA_ARGS__;
// #define 结束() exit(0);



//@分组{ 数组操作

//@备注 本命令可以重新定义指定数组的维数及各维的上限值。命令参数表中最后一个参数可以被重复添加。
//@参数 提供参数数据时只能提供变量数组。
//@参数 初始值为“假”。
//@参数
template<class T>
void 重定义数组(CXVector<T>& 欲重定义的数组变量, BOOL 是否保留以前的内容 = TRUE, int 数组对应维的上限值 = 0)
{
	int arrSize = 数组对应维的上限值;
	if (arrSize == 0) arrSize = 欲重定义的数组变量.size();
	if (是否保留以前的内容) {
		欲重定义的数组变量.clear();
	}
	欲重定义的数组变量.resize(arrSize);
}

//@备注  取指定数组变量的全部成员数目，如果该变量不为数组，返回-1，因此本命令也可以用作检查指定变量是否为数组变量。
//@参数  提供参数数据时只能提供变量及变量数组。参数值指定欲检查其成员数目的数组变量或者欲检查其是否为数组的变量。
#define  取数组成员数(动态数组_) (动态数组_.getSize())


//@备注 将数组数据复制到指定的数组变量，该数组变量内的所有数据和数组维定义信息将被全部覆盖。
//@参数 提供参数数据时只能提供变量数组。
//@参数 提供参数数据时只能提供数组数据。
template<class T>
void 复制数组(CXVector<T>& 复制到的数组变量, CXVector<T>& 待复制的数组数据)
{
	复制到的数组变量 = 待复制的数组数据;
}

//@备注 将数据加入到指定数组变量的尾部，并通过重新定义数组维数自动增加其成员数目。数组变量如为多维数组，加入完毕后将被转换为单维数组。
//@参数 提供参数数据时只能提供变量数组。
//@参数 提供参数数据时可以同时提供数组或非数组数据。参数值所指定成员数据的数据类型必须能够与第一个参数所指定的数组变量相匹配。
template<class T>
void 加入成员(CXVector<T>& 欲加入成员的数组变量, T 欲加入的成员数据)
{
	欲加入成员的数组变量.add(欲加入的成员数据);
}

//@备注 将数据插入到指定数组变量的指定位置，并通过重新定义数组维数自动增加其成员数目。数组变量如为多维数组，插入完毕后将被转换为单维数组。
//@参数 提供参数数据时只能提供变量数组。
//@参数 位置值从 0 开始，如果小于 0 或大于第一个参数所指定数组变量的成员数目 + 1，将不会插入任何数据。
//@参数 提供参数数据时可以同时提供数组或非数组数据。参数值所指定成员数据的数据类型必须能够与第一个参数所指定的数组变量相匹配。
template<class T>
void 插入成员(CXVector<T>& 欲插入成员的数组变量, int 欲插入的位置, T 欲插入的成员数据)
{
	欲插入成员的数组变量.insert(欲插入的位置, 欲插入的成员数据);
}

//@备注 删除指定数组变量中的成员，并通过重新定义数组维数自动减少其成员数目。数组变量如为多维数组，删除完毕后将被转换为单维数组。返回所实际删除的成员数目。
//@参数 提供参数数据时只能提供变量数组。
//@参数 位置值从 0 开始，如果小于 0 或大于第一个参数所指定数组变量的成员数目，将不会删除任何数据。
//@参数 可以被省略。本参数如果被省略，默认为 1 。
template<class T>
void 删除成员(CXVector<T>& 欲删除成员的数组变量, int 欲删除的位置, int 欲删除的成员数目 = 1)
{
	int c = 欲删除的位置 + 欲删除的成员数目;
	欲删除成员的数组变量.erase(欲删除的位置, c);
}

//@备注 删除指定数组变量中的所有成员，释放这些成员所占用的存储空间，重新定义该变量为单维 0 成员数组变量。
//@参数 提供参数数据时只能提供变量数组。
template<class T>
void 清除数组(CXVector<T>& 欲删除成员的数组变量)
{
	return 欲删除成员的数组变量.clear();
}

//@备注 对指定数值数组变量内的所有数组成员进行快速排序，不影响数组的维定义信息，排序结果存放回该数组变量。
//@参数 提供参数数据时只能提供变量数组。
//@参数 可以被省略。如果参数值为真，排序方向为从小到大，否则为从大到小。如果本参数被省略，默认值为真。
template<class T> 
void 数组排序(CXVector<T>& 数值数组变量, BOOL 排序方向是否为从小到大 = TRUE)
{
	if(排序方向是否为从小到大)
		std::sort(数值数组变量.begin(), 数值数组变量.end());
	else
		std::sort(数值数组变量.begin(), 数值数组变量.end(), std::greater<T>());
}

//@备注 将指定数值数组变量内的所有成员值全部设置为零，不影响数组的维定义信息。
//@参数 提供参数数据时只能提供变量数组。
template<class T>
void 数组清零(CXVector<T>& 数值数组变量)
{
	int size = 数值数组变量.size();
	数值数组变量.clear();
	数值数组变量.resize(size);
}
//@分组}


//@分组{ 环境存取-见基础模块
//@分组}

//@分组{ 拼音操作
//@分组}

//@分组{ 文本操作
CXBytes 十六进制文本转为字节集(const wchar_t* b);
CXText  字节集转为16进制文本(CXBytes& b);

/*@声明

//@备注 取文本型数据的长度，不包含结束0。
//@参数 参数值指定欲检查其长度的文本数据。
//@别名 取文本长度(文本数据)
UINT wcslen(const wchar_t* str);

//@备注 返回一个文本，其中包含指定文本中从左边算起指定数量的字符。
//@别名  取文本左边(欲取其部分的文本,欲取出字符的数目)
CXText  text_getLeft(const wchar_t* pText, UINT length);

//@备注 返回一个文本，其中包含指定文本中从右边算起指定数量的字符。
//@别名 取文本右边(欲取其部分的文本,欲取出字符的数目)
CXText  text_getRight(const wchar_t* pText, UINT length);

//@备注 返回一个文本，其中包含指定文本中从指定位置算起指定数量的字符。
//@别名  取文本中间(欲取其部分的文本, 起始取出位置, 欲取出字符的数目)
CXText  text_getSub2(const wchar_t* pText, UINT pos1, UINT count);

*/

//@备注  返回一个文本，其中包含有与指定字符代码相关的字符。
CXText  字符(wchar_t 欲取其字符的字符代码);

//@备注 返回文本中指定位置处字符的代码。如果指定位置超出文本长度，返回0。
int 取代码(const wchar_t* 欲取字符代码的文本, int 欲取其代码的字符位 = 0);

//@备注  返回一个整数值，指定一文本在另一文本中最先出现的位置，位置值从 0 开始。如果未找到，返回 - 1。
//@参数
//@参数
//@参数  可以被省略。位置值从 0 开始。如果本参数被省略，默认为 0 。
//@参数  初始值为“假”。为真不区分大小写，为假区分。
//@别名  寻找文本(被搜寻的文本, 欲寻找的文本, 起始搜寻位置, 是否不区分大小写)
int 寻找文本(const wchar_t* pText, const wchar_t* pSubStr, int pos = 0, BOOL dx = FALSE);

//@备注  返回一个整数值，指定一文本在另一文本中最后出现的位置，位置值从 0 开始。如果未找到，返回 - 1。
//@参数 
//@参数
//@参数  可以被省略。位置值从 0 开始。如果本参数被省略，默认为从被搜寻文本的尾部开始。
//@参数  初始值为“假”。为真不区分大小写，为假区分。
//@别名  倒找文本(被搜寻的文本, 欲寻找的文本, 起始搜寻位置, 是否不区分大小写)
int 倒找文本(const wchar_t* pText, const wchar_t* pSubStr, int pos = 0, BOOL dx = FALSE);

//@备注  将文本中的小写英文字母变换为大写，返回变换后的结果文本。
//@别名  到大写(欲变换的文本)
CXText 到大写(const wchar_t* pText);

//@备注  将文本中的大写英文字母变换为小写，返回变换后的结果文本。
//@别名  到小写(欲变换的文本)
CXText 到小写(const wchar_t* pText);

//@备注  将文本中的半角字母、空格或数字变换为全角，返回变换后的结果文本。
//@别名  到全角(欲变换的文本)
CXText 到全角(const wchar_t* pText);

//@备注  将文本中的全角字母、空格或数字变换为半角，返回变换后的结果文本。
CXText 到半角(const wchar_t* pText);

/*@声明

//@备注 返回一个文本，其中包含被删除了首部全角或半角空格的指定文本。
//@别名 删首空(欲删除空格的文本)
CXText text_trim_left(const wchar_t* pText);

//@备注  返回一个文本，其中包含被删除了尾部全角或半角空格的指定文本。
//@别名  删尾空(欲删除空格的文本)
CXText text_trim_right(const wchar_t* pText);

//@备注 返回一个文本，其中包含被删除了首部及尾部全角或半角空格的指定文本。
//@别名  删首尾空(欲删除空格的文本)
CXText text_trim(const wchar_t* pText);

*/

//@备注  返回一个文本，其中包含被删除了所有全角或半角空格的指定文本。
//@别名  删全部空(欲删除空格的文本)
CXText 删全部空(const wchar_t* pText);

//@备注  将指定文本的某一部分用其它的文本替换。
//@参数
//@参数  替换的起始位置，1为首位置，2为第2个位置，如此类推。
//@参数
//@参数  可以被省略。如果本参数被省略，则删除文本中的指定部分。
//@别名  文本替换_易语言(欲被替换的文本, 起始替换位置, 替换长度, 用作替换的文本)
CXText 文本替换_易语言(const wchar_t* pText, int pos, int length, const wchar_t* pReplaceText);


//@备注  返回一个文本，该文本中指定的子文本已被替换成另一子文本，并且替换发生的次数也是被指定的。
//@参数
//@参数
//@参数  可以被省略。如果本参数被省略，默认为空文本。
//@参数  可以被省略。参数值指定被替换子文本的起始搜索位置。如果省略，默认从 0 开始。
//@参数  可以被省略。参数值指定对子文本进行替换的次数。如果省略，默认进行所有可能的替换。
//@参数  初始值为“真”。为真区分大小写，为假不区分。
//@别名  子文本替换(欲被替换的文本, 欲被替换的子文本, 用作替换的子文本, 进行替换的起始位置, 替换进行的次数, 是否区分大小写)
CXText 子文本替换(const wchar_t* pText, const wchar_t* pSubText, const wchar_t* pReplaceText, int pos = 0, int count = 0, bool dx = TRUE);

//@备注 返回具有指定数目半角空格的文本。
CXText 取空白文本(int 大小);

//@备注  返回一个文本，其中包含指定次数的文本重复结果。
//@参数  重复次数
//@参数  该文本将用于建立返回的文本。如果为空，将返回一个空文本。
//@别名  取重复文本(重复次数, 待重复文本)
CXText 取重复文本(int count, const wchar_t* pText);

//@备注  如果返回值小于0，表示文本一小于文本二；如果等于0，表示文本一等于文本二；如果大于0，表示文本一大于文本二。如果比较时区分大小写，也可以使用比较运算符进行同样的操作。
//@参数
//@参数
//@参数  初始值为“真”。为真区分大小写，为假不区分。
//@别名  文本比较 (待比较文本一, 待比较文本二, 是否区分大小写)
int 文本比较(const wchar_t* str1, const wchar_t* str2, BOOL dx);

//@备注  将指定文本进行分割，返回分割后的一维文本数组。
//@参数  如果参数值是一个长度为零的文本，则返回一个空数组，即没有任何成员的数组。
//@参数  可以被省略。参数值用于标识子文本边界。如果被省略，则默认使用半角逗号字符作为分隔符。如果是一个长度为零的文本，则返回的数组仅包含一个成员，即完整的“待分割文本”。
//@别名  分割文本(待分割文本, 用作分割的文本)
CXVector<CXText> 分割文本(const wchar_t* pText, const wchar_t* pSplit);

//@备注  返回指定内存指针所指向地址处的文本，注意调用本命令前一定要确保所提供的内存指针真实有效，且指向一个以零字符结束的文本串。本命令的最佳使用场合就是在易语言回调子程序和易语言DLL公开子程序用作获取外部数据。本命令为高级命令。
//@参数  本参数提供指向一个以零字符结束的文本串内存指针值。
//@别名  指针到文本(内存文本指针)
CXText 指针到文本(void* 内存文本指针);

//@分组} //文本操作



//@分组{  文本操作(移植炫易模块)

//@参数   随机长度
//@别名   文本_取随机文本A (长度)
CXTextA X_String_GetRandStrA(int len);
//@参数   随机长度
//@别名   文本_取随机文本 (长度)
CXText X_String_GetRandStr(int len);

//@参数   字符串
//@别名   文本_转小写A (文本)
CXTextA X_String_ToLowerA(CXTextA str);
//@参数   字符串
//@别名   文本_转小写 (文本)
CXText X_String_ToLower(CXText str);

//@参数   字符串
//@别名   文本_转大写A (文本)
CXTextA X_String_ToUpperA(CXTextA str);
//@参数   字符串
//@别名   文本_转大写 (文本)
CXText X_String_ToUpper(CXText str);

//@别名   文本_文本比较A (待比较文本一,待比较文本二,是否区分大小写)
int X_String_StrCmpA(CXTextA str1, CXTextA str2, bool ifnotcasesensitive = false);
//@别名   文本_文本比较 (待比较文本一,待比较文本二,是否区分大小写)
int X_String_StrCmp(CXText str1, CXText str2, bool ifnotcasesensitive = false);

//@别名   文本_取中间文本A(源文本,前文本,后文本,起始位置,是否不区分大小写)
CXTextA X_String_GetMiddleTextA(CXTextA text, CXTextA start, CXTextA end, int begin = 0, bool ifnotcasesensitive = false);
//@别名   文本_取中间文本(源文本,前文本,后文本,起始位置,是否不区分大小写)
CXText X_String_GetMiddleText(CXText text, CXText start, CXText end, int begin = 0, bool ifnotcasesensitive = false);

//@别名   文本_删首尾空A(文本)
CXTextA X_String_TrimA(CXTextA str);
//@别名   文本_删首尾空(文本)
CXText X_String_Trim(CXText str);

//@别名   文本_子文本替换A (源字符串,被替换字符串,用作替换的字符串,起始位置,最大替换次数)
CXTextA X_String_SubreplaceA(CXTextA resource_str, CXTextA sub_str, CXTextA new_str = "", int begin = 0, int MaxRep = -1);
//@别名   文本_子文本替换 (源字符串,被替换字符串,用作替换的字符串,起始位置,最大替换次数)
CXText X_String_Subreplace(CXText resource_str, CXText sub_str, CXText new_str = L"", int begin = 0, int MaxRep = -1);

//@别名   文本_倒找文本A(源字符串,被寻找字符串,起始位置)
int X_String_RfindA(CXTextA source, CXTextA str, int pos = -1);
//@别名   文本_倒找文本(源字符串,被寻找字符串,起始位置)
int X_String_Rfind(CXText source, CXText str, int pos = -1);

//@别名   文本_取左边A ()
CXTextA X_String_GetLeftA(CXTextA text, CXTextA str, int pos = -1);
//@别名   文本_取左边 ()
CXText X_String_GetLeft(CXText text, CXText str, int pos = -1);

//@别名   文本_取右边A ()
CXTextA X_String_GetRightA(CXTextA text, CXTextA str, int pos = -1);
//@别名   文本_取右边 ()
CXText X_String_GetRight(CXText text, CXText str, int pos = -1);

//@别名   文本_分割文本A (文本,分割字符,返回数组)
CXVector<CXTextA> X_String_SplitWithStlA(CXTextA str, CXTextA pattern);
//@别名   文本_分割文本 (文本,分割字符,返回数组)
CXVector<CXText> X_String_SplitWithStl(CXText str, CXText pattern);

//@别名   文本_是否UTF8(欲判断的文本)
bool X_String_WIsUtf8A(const CXTextA& string);

//@别名   文本_逐字分割(被分割的文本,接收的容器)
int  X_String_SplitWitNum(CXText string, CXVector<CXText>& rList);
//@别名   文本_逐字分割A(被分割的文本,接收的容器)
int  X_String_SplitWitNumA(CXTextA string, CXVector<CXTextA>& rList);

//@备注   用于判断文本是否为标准数值格式(不支持科学计数法)
//@别名   文本_是否为数值(待判断文本)
bool X_String_IsNumber(CXText string);

/*@声明
//@别名   文本_数值到文本(欲转换的数值)
CXText X_String_NumberToText(...);
//@别名   文本_数值到文本A(欲转换的数值)
CXTextA X_String_NumberToTextA(...);
*/
//@别名   文本_文本到整型(欲转换的文本)
int X_String_TextToInt(CXText str);
//@别名   文本_文本到长整型(欲转换的文本)
long X_String_TextToLong(CXText str);
//@别名   文本_文本到双长整型(欲转换的文本)
LONGLONG X_String_TextToLongLong(CXText str);
//@别名   文本_文本到整型A(欲转换的文本)
int X_String_TextToIntA(CXTextA str);
//@别名   文本_文本到长整型A(欲转换的文本)
long X_String_TextToLongA(CXTextA str);
//@别名   文本_文本到双长整型A(欲转换的文本)
LONGLONG X_String_TextToLongLongA(CXTextA str);
//@隐藏{
CXText X_String_NumberToText(int x);
CXText X_String_NumberToText(long x);
CXText X_String_NumberToText(long long x);
CXText X_String_NumberToText(float x);
CXText X_String_NumberToText(double x);
CXText X_String_NumberToText(long double x);
CXText X_String_NumberToText(unsigned int x);
CXText X_String_NumberToText(unsigned long x);
CXText X_String_NumberToText(unsigned long long x);
CXTextA X_String_NumberToTextA(int x);
CXTextA X_String_NumberToTextA(long x);
CXTextA X_String_NumberToTextA(long long x);
CXTextA X_String_NumberToTextA(float x);
CXTextA X_String_NumberToTextA(double x);
CXTextA X_String_NumberToTextA(long double x);
CXTextA X_String_NumberToTextA(unsigned int x);
CXTextA X_String_NumberToTextA(unsigned long x);
CXTextA X_String_NumberToTextA(unsigned long long x);
//@隐藏}

//@别名 str返回 Str，注意本命令对首字为汉字的文本无效
//@别名 文本_首字母改大写(英文文本)
CXText X_String_LastToUpper(CXText str);
//@别名 str返回 Str，注意本命令对首字为汉字的文本无效
//@别名 文本_首字母改大写A(英文文本)
CXTextA X_String_LastToUpperA(CXTextA str);

//@分组}  文本操作(移植炫易模块)


//@分组{ 时间操作

//@备注  将指定文本转换为时间戳并返回。如果给定文本不符合书写格式要求或者时间值错误导致不能进行转换，将返回-1。如果给定参数本身就是时间数据，将直接返回该时间。
//@参数  文本内容应按以下格式之一提供，年份后的时间部分可以省略：
//  1、1973年11月15日12时30分25秒
//  2、1973/11/15 12:30:25
//  3、1973/11/15/12/30/25
//  4、1973/11/15/12:30:25
//  5、1973-11-15-12-30-25
//  6、1973-11-15-12:30:25
//  7、1973.11.15 12:30:25
//  8、19731115123025
//@返回 时间戳, 失败返回-1
//@别名 到时间(欲转换的文本)
INT64 到时间(const wchar_t* pText);

//@备注  返回一个时间，这一时间被加上或减去了一段间隔。如果改变后的时间无效，将自动靠近最近的有效时间。
//@参数
//@参数  参数值指定增加或减少时间的哪一部分，可以为以下常量： 1、#年份； 2、#季度； 3、#月份； 4、#周； 5、#日； 6、#小时； 7、#分钟； 8、#秒。
//@参数  相对于被增加部分的增加或减少数值。
//@别名  增减时间(时间, 被增加部分, 增加值)
INT64 增减时间(INT64 date,  int flag,  int addValue);

//@备注  返回一个数值，表示“时间1”减去“时间2”之后的间隔数目。注意：每个星期以星期天为第一天。
//@参数
//@参数
//@参数  参数值指定取时间间隔的单位，可以为以下常量： 1、#年份； 2、#季度； 3、#月份； 4、#周； 5、#日； 6、#小时； 7、#分钟； 8、#秒。
//@别名  取时间间隔(时间1, 时间2, 取间隔部分)
double 取时间间隔(INT64 time1, INT64  time2, int flag);

//@备注  返回指定月份所包含的天数。如果给定的月份无效，返回0。
//@参数  参数值从 100 到 9999。
//@参数  参数值从 1 到 12。
//@别名  取某月天数(年份, 月份)
int  取某月天数(int year_, int month_);

//@备注  将指定时间转换为文本并返回。
//@参数
//@参数  可以被省略。参数值可以为以下常量： 1、#全部转换； 2、#日期部分； 3、#时间部分。如果省略了本参数，默认为“#全部转换”。
//@别名  时间到文本(欲转换到文本的时间, 转换部分)
CXText  时间到文本(INT64  time_, int flag= 1);

//@备注  返回一个包含已知时间指定部分的整数。
//@参数
//@参数  参数值可以为以下常量： 1、#年份； 2、#季度； 3、#月份； 4、#自年首周数； 5、#日； 6、#小时； 7、#分钟； 8、#秒； 9、#星期几； 10、#自年首天数。其中：自年首周数、自年首天数均从 1 开始。
//@别名  取时间部分(欲取其部分的时间, 欲取的时间部分)
int 取时间部分(INT64  time_, int flag);

//@备注  返回一个值为 100 到 9999 之间的整数，表示指定时间中的年份。
//@参数
//@别名  取年份(时间)
int  取年份(INT64 time_);

//@备注  返回一个值为 1 到 12 之间的整数，表示指定时间中的月份。
//@别名  取月份(时间）)
int 取月份(INT64 time_);

//@备注  返回一个值为 1 到 31 之间的整数，表示一个月中的某一日。
//@别名  取日(时间)
int 取日(INT64 time_);

//@备注  返回一个值为 1 到 7 之间的整数，表示一个星期中的某一日。星期日为 1，星期一为 2，依此类推。
//@别名  取星期几(时间)
int 取星期几(INT64 time_);

//@备注  返回一个值为 0 到 23 之间的整数，表示一天中的某一小时。
//@别名  取小时(时间)
int 取小时(INT64 time_);

//@备注  返回一个值为 0 到 59 之间的整数，表示一小时中的某一分钟。
//@别名  取分钟(时间)
int 取分钟(INT64 time_);

//@备注  返回一个值为 0 到 59 之间的整数，表示一分钟中的某一秒。
//@别名  取秒(时间)
int 取秒(INT64 time_);

//@备注  返回包含指定年、月、日、小时、分、秒的时间。如果指定了无效时间，将自动使用最相近的有效时间代替。
//@参数  
//@参数  可以被省略。如果本参数被省略，默认为 1 月。
//@参数  可以被省略。如果本参数被省略，默认为 1 日。
//@参数  可以被省略。如果本参数被省略，默认为 0 时。
//@参数  可以被省略。如果本参数被省略，默认为 0 分钟。
//@参数  可以被省略。如果本参数被省略，默认为 0 秒。
//@别名  指定时间(年, 月, 日, 小时, 分钟, 秒)
INT64 指定时间(int year_=1,int mon_=1, int day_=0, int hour_=0, int min_=0,int sec_=0);

//@备注 返回当前系统日期及时间。
//@别名 取现行时间()
INT64 取现行时间();

INT64 取现行时间_毫秒();
//@备注 设置当前系统日期及时间。成功返回真，失败返回假。
//@别名  置现行时间(欲设置的时间)
BOOL 置现行时间(INT64 time_);

//@备注  返回一个日期时间型数据的日期部分，其小时、分钟、秒被固定设置为0时0分0秒。
//@别名  取日期(时间)
INT64 取日期(INT64 time_);

//@备注  返回一个日期时间型数据的时间部分，其年、月、日被固定设置为2000年1月1日。
//@别名  取时间(时间)
INT64 取时间(INT64 time_);
//@分组}


//@分组{ 数值转换

/*@声明
//@备注  返回包含于文本内的数值，文本中是一个适当类型的数值，支持全角书写方式。本命令也可用作将其他类型的数据转换为双精度小数。
template<class T> double 到数值(T value_);
*/

//@隐藏{
inline double 到数值(int value_) { return (double)value_; }
inline double 到数值(INT64 value_) { return (double)value_; }
inline double 到数值(BYTE value_) { return (double)value_; }
inline double 到数值(SHORT value_) { return (double)value_; }
inline double 到数值(float value_) { return (double)value_; }
inline double 到数值(double value_) { return (double)value_; }
inline double 到数值(const char* value_) { return atof(value_); }
inline double 到数值(const wchar_t* value_) { return _wtof(value_); }
//@隐藏}

//@备注  将数值转换为简体或繁体的大写形式，返回转换后的文本。
//@参数
//@参数  初始值为“假”。如果参数值为假，则转换为繁体。
//@别名  数值到大写(欲转换形式的数值, 是否转换为简体)
CXText  数值到大写(double value_, BOOL dx=FALSE);

//@备注  将数值转换为金额的简体或繁体大写形式，返回转换后的文本。
//@参数
//@参数  初始值为“假”。如果参数值为假，则转换为繁体。
//@别名  数值到金额(欲转换形式的数值, 是否转换为简体)
CXText  数值到金额(double value_, BOOL dx = FALSE);

//@备注  返回一个文本，代表指定数值被格式转换后的结果。
//@参数
//@参数  可以被省略。如果大于0，表示小数点右边应四舍五入保留的位数；如果等于0，表示舍入到整数；如果小于0，表示小数点左边舍入到的位置。例如：数值到格式文本(1056.65, 1, 假) 返回 “1056.7”； 数值到格式文本(1056.65, 0, 假) 返回 “1057”； 数值到格式文本(1056.65, -1, 假) 返回 “1060”。如果省略本参数，则默认为保留所有实际存在的小数位。
//@参数  初始值为“假”。如果参数值为真，数值文本的每个千分位上都将被自动插入一个逗号进行分隔。
//@别名  数值到格式文本(欲转换为文本的数值, 小数保留位数, 是否进行千分位分隔)
CXText  数值到格式文本(double value_, int flag=99,  BOOL split = FALSE);

//@备注  返回一个文本，代表指定数值的十六进制形式。
//@别名  取十六进制文本(欲取进制文本的数值)
CXText  取十六进制文本(int value_);

//@备注  返回一个文本，代表指定数值的八进制形式。
//@别名  取八进制文本(欲取进制文本的数值)
CXText  取八进制文本(int value_);


/*@声明
//@备注  返回包含于文本内的字节值，文本中是一个适当类型的数值，支持全角书写方式。本命令也可用作将其他类型的数据转换为字节。
//@别名 到字节(待转换的文本或数值)
template<class T> BYTE 到字节(T value_);
*/
//@隐藏{
template<class T> BYTE 到字节(T value_) { return (BYTE)value_; }
inline BYTE  到字节(const wchar_t* value_) { if (value_ && *value_) return (BYTE)*value_; return 0; }
inline BYTE  到字节(const char* value_) { if (value_ && *value_) return (BYTE)*value_; return 0; }
//@隐藏}


/*@声明
//@备注  返回包含于文本内的短整数值，文本中是一个适当类型的数值，支持全角书写方式。本命令也可用作将其他类型的数据转换为短整数。
//@别名  到短整数(待转换的文本或数值)
template<class T> SHORT 到短整数(T value_);
*/
//@隐藏{
template<class T> SHORT 到短整数(T value_) { return (SHORT)value_; }
inline SHORT 到短整数(const wchar_t* value_) { if (value_ && *value_) return (SHORT)_wtoi(value_); return 0; }
inline SHORT 到短整数(const char* value_) { if (value_ && *value_) return (SHORT)atoi(value_); return 0; }
//@隐藏}

/*@声明
//@备注  返回包含于文本内的整数值，文本中是一个适当类型的数值，支持全角书写方式。本命令也可用作将其他类型的数据转换为整数。
//@别名  到整数(待转换的文本或数值)
template<class T> int 到整数(T value_);
*/
//@隐藏{
template<class T> SHORT 到整数(T value_) { return (int)value_; }
inline int 到整数(const wchar_t* value_) { if (value_ && *value_) return _wtoi(value_); return 0; }
inline int 到整数(const char* value_) { if (value_ && *value_) return atoi(value_); return 0; }
inline int 到整数(const CXTextA& value_) { return atoi(value_.getPtr()); }
inline int 到整数(const CXText& value_) { return _wtoi(value_.getPtr()); }

inline int 到整数(const CXTextA* value_) { if(value_)  return atoi(value_->getPtr()); return 0;}
inline int 到整数(const CXText* value_) { if(value_) return _wtoi(value_->getPtr()); return 0;}
//@隐藏}

/*@声明
//@备注  返回包含于文本内的长整数值，文本中是一个适当类型的数值，支持全角书写方式。本命令也可用作将其他类型的数据转换为长整数。
//@别名  到长整数(待转换的文本或数值)
template<class T> INT64 到长整数(T value_);
*/
//@隐藏{
template<class T> INT64 到长整数(T value_) { return (INT64)value_; }
inline INT64 到长整数(const wchar_t* value_) { if (value_ && *value_) return _wtoi64(value_); return 0; }
inline INT64 到长整数(const char* value_) { if (value_ && *value_) return _atoi64(value_); return 0; }
//@隐藏}

/*@声明
//@备注  返回包含于文本内的小数值，文本中是一个适当类型的数值，支持全角书写方式。本命令也可用作将其他类型的数据转换为小数。
//@别名  到小数(待转换的文本或数值)
template<class T> float 到小数(T value_);
*/
//@隐藏{
template<class T> float 到小数(T value_) { return (float)value_; }
inline float 到小数(const wchar_t* value_) { if (value_ && *value_) return (float)_wtof(value_); return 0; }
inline float 到小数(const char* value_) { if (value_ && *value_) return (float)atof(value_); return 0; }
//@隐藏}

//@备注  计算返回所指定十六进制文本常量对应的整数值.本命令在编译时被直接预处理为整数型参量值, 不影响程序执行效率.
//@参数  本参数指定欲转换为整数的十六进制文本常量。
//@别名  十六进制(十六进制文本常量)
int 十六进制(const wchar_t* pHex);

//@备注  计算返回所指定二进制文本常量对应的整数值.本命令在编译时被直接预处理为整数型参量值, 不影响程序执行效率.
//@参数  本参数指定欲转换为整数的二进制文本常量。
//@别名  二进制(二进制文本常量)
int 二进制(const wchar_t* pBinary);

//@分组}


//@分组{ 字节集操作


/*@声明
//@备注  取字节集型数据的长度。
//@参数  参数值指定欲检查其长度的字节集数据。
//@别名  取字节集长度(字节集数据)
int 取字节集长度(CXBytes& 字节集数据);
*/

//@隐藏{
#define 取字节集长度(字节集_)  字节集_.size()
//@隐藏}


//@备注  将指定数据转换为字节集后返回转换结果。
//@参数  提供参数数据时可以同时提供数组或非数组数据。参数值只能为基本数据类型数据或数值型数组。
//@别名  到字节集(欲转换为字节集的数据)
template<class T>
CXBytes 到字节集(T value_) { 
	CXBytes  byte_ = value_; 
	return byte_; 
}

//@隐藏{
CXBytes 到字节集(const CXText& value_);
CXBytes 到字节集(const CXTextA& value_);
//@隐藏}

//@备注  取出字节集中指定位置指定数据类型的数据, 请直接使用字节集接口
//@参数  
//@参数  参数值可以为以下常量： 1、#字节型； 2、#短整数型； 3、#整数型； 4、#长整数型； 5、#小数型； 6、#双精度小数型； 7、#逻辑型； 8、#日期时间型； 9、#子程序指针型； 10、#文本型。转换后的数据将自动进行有效性校验及转换处理。
//@参数  可以被省略。指定从字节集的什么地方开始取数据，索引值从1开始。如果被省略，默认为数值1。如果为本参数提供一个整数型变量，则命令执行后将自动修改该变量内容，将其索引值移动到下一个读入位置。如果移动后到达字节集的末尾，将修改该变量的内容为 - 1。
//@别名  取字节集数据(欲取出其中数据的字节集,欲取出数据的类型,起始索引位置)
inline void 取字节集数据_请直接使用字节集接口(CXBytes& 欲取出其中数据的字节集, int 欲取出数据的类型, int 起始索引位置 = 0) {}

//@备注  返回一个字节集，其中包含指定字节集中从左边算起指定数量的字节。
//@别名  取字节集左边(欲取其部分的字节集,欲取出字节的数目)
CXBytes 取字节集左边(CXBytes& 欲取出其中数据的字节集, int 欲取出字节的数目);

//@备注  返回一个字节集，其中包含指定字节集中从右边算起指定数量的字节。
//@别名  取字节集右边(欲取其部分的字节集, 欲取出字节的数目)
CXBytes 取字节集右边(CXBytes& 欲取出其中数据的字节集, int 欲取出字节的数目);

//@备注  返回一个字节集，其中包含指定字节集中从指定位置算起指定数量的字节。
//@别名  取字节集中间(欲取其部分的字节集, 起始取出位置, 欲取出字节的数目)
CXBytes 取字节集中间(CXBytes& 欲取出其中数据的字节集, int 起始取出位置, int 欲取出字节的数目);

//@备注  返回一字节集在另一字节集中最先出现的位置，位置值从 0 开始。如果未找到，返回 -1
//@参数
//@参数
//@参数  可以被省略。0为首位置，1为第2个位置，如此类推，如果被省略，则“寻找字节集”命令默认从首部开始，“倒找字节集”命令默认从尾部开始。
//@返回  所在位置索引, 如果没有找到返回-1
//@别名  寻找字节集(被搜寻的字节集,欲寻找的字节集,起始搜寻位置)
int 寻找字节集(CXBytes& 被搜寻的字节集, CXBytes& 欲寻找的字节集, int 起始搜寻位置 = 0);

//@备注  返回一字节集在另一字节集中最先出现的位置，位置值从 0 开始。如果未找到，返回 -1
//@参数
//@参数
//@参数 可以被省略。0为首位置，1为第2个位置，如此类推，如果被省略，则“寻找字节集”命令默认从首部开始，“倒找字节集”命令默认从尾部开始。
//@别名  倒找字节集(被搜寻的字节集,欲寻找的字节集,起始搜寻位置)
int 倒找字节集(CXBytes& 被搜寻的字节集, CXBytes 欲寻找的字节集, int 起始搜寻位置 = 0);

//@备注  将指定字节集的某一部分用其它的字节集替换，然后返回替换后的结果。
//@参数  欲替换其部分的字节集 类型为字节集
//@参数  起始替换位置,类型为整数型,替换的起始位置，0为首位置，1为第2个位置，如此类推。
//@参数  替换长度 类型为整数型 
//@参数  类型为字节集，如果本参数为空，则删除字节集中的指定部分 
//@别名  字节集替换(被搜寻的字节集,欲寻找的字节集,起始搜寻位置)
CXBytes 字节集替换(CXBytes& 欲替换其部分的字节集, int 起始替换位置, int 替换长度, CXBytes 用作替换的字节集);

//@备注  返回一个字节集，该字节集中指定的子字节集已被替换成另一子字节集，并且替换发生的次数也是被指定的
//@参数
//@参数
//@参数  省略。如果省略本参数，则默认为空字节集。
//@参数  被替换子字节集的起始搜索位置。如果省略，默认从0开始。
//@参数  对子字节集进行替换的次数。如果省略，默认进行所有可能的替换。
//@别名  子字节集替换(欲被替换的字节集,欲被替换的子字节集,用作替换的子字节集,进行替换的起始位置,替换进行的次数)
CXBytes 子字节集替换(CXBytes 欲被替换的字节集, CXBytes 欲被替换的子字节集, CXBytes 用作替换的子字节集, int 进行替换的起始位置 = -1, int 替换进行的次数 = -1);

//@备注  返回具有特定数目 0 字节的字节集。
CXBytes 取空白字节集(int 大小);

//@备注  返回一个字节集，其中包含指定次数的字节集重复结果
//@参数
//@参数  如果为空，将返回一个空字节集
//@别名  取重复字节集(重复次数, 待重复的字节集)
CXBytes 取重复字节集(int 重复次数, CXBytes 待重复的字节集);

//@备注  将指定字节集进行分割，返回分割后的一维字节集数组
//@参数  如果参数值是一个长度为零的字节集，则返回一个空数组，即没有任何成员的数组。
//@参数  用于标识子字节集边界。本参数如果被省略，则默认使用字节 0 作为分隔符。
//@参数  如果被省略，则默认返回所有的子字节集。
//@别名  分割字节集(待分割字节集,用作分割的字节集,要返回的子字节集数目)
CXVector<CXBytes> 分割字节集(CXBytes 待分割字节集, CXBytes 用作分割的字节集, int 要返回的子字节集数目 = 0);

//@备注  返回指定内存指针所指向地址处的一段数据，注意调用本命令前一定要确保所提供的内存地址段真实有效。本命令的最佳使用场合就是在易语言回调子程序和易语言DLL公开子程序用作获取外部数据。本命令为高级命令。
//@参数  本参数提供指向一个内存地址的指针值。
//@参数  本参数提供该内存地址处所需获取的数据长度。
//@别名  指针到字节集(内存数据指针, 内存数据长度)
CXBytes 指针到字节集(void* 指针, int 大小);

//@备注  返回指定内存指针所指向地址处的一个整数(INT)，注意调用本命令前一定要确保所提供的内存地址段真实有效。本命令为高级命令。
//@参数  本参数提供指向一个内存地址的指针值。
//@别名  指针到整数(内存数据指针)
inline int 指针到整数(void* value_) { return *((int*)value_); }

//@备注  返回指定内存指针所指向地址处的一个小数(FLOAT)，注意调用本命令前一定要确保所提供的内存地址段真实有效。本命令为高级命令。
//@参数  本参数提供指向一个内存地址的指针值。
//@别名  指针到小数(内存数据指针)
inline float 指针到小数(void* value_) { return *((float*)value_); }

//@备注  返回指定内存指针所指向地址处的一个双精度小数(DOUBLE)，注意调用本命令前一定要确保所提供的内存地址段真实有效。本命令为高级命令。
//@参数  本参数提供指向一个内存地址的指针值。
//@别名  指针到双精度小数(内存数据指针)
inline double 指针到双精度小数(void* value_) { return *((double*)value_); }
//@分组}


//@分组{ 磁盘操作

//@备注  返回以 1024 字节（KB）为单位的指定磁盘全部空间。如果失败，返回 - 1。
//@参数  可以被省略。类似“A”、“B”、“C”等，只取用给定文本的第一个字符。如果本参数被省略，默认使用当前驱动器。
//@别名  取磁盘总空间(磁盘驱动器字符);
int 取磁盘总空间(const wchar_t* pText);

//@备注  返回以 1024 字节（KB）为单位的指定磁盘现行剩余空间。如果失败，返回 - 1。
//@参数  类似“A”、“B”、“C”等，只取用给定文本的第一个字符。如果本参数被省略，默认使用当前驱动器。
//@别名  取磁盘剩余空间(磁盘驱动器字符)
int 取磁盘剩余空间(const wchar_t* pText);

//@备注  返回指定磁盘的卷标文本。
//@参数  可以被省略。类似“A”、“B”、“C”等，只取用给定文本的第一个字符。如果本参数被省略，默认使用当前驱动器。
//@别名  取磁盘卷标(磁盘驱动器字符)
CXText 取磁盘卷标(const wchar_t* pText);

//@备注  设置指定磁盘的卷标文本。成功返回真，失败返回假。
//@参数  可以被省略。类似“A”、“B”、“C”等，只取用给定文本的第一个字符。如果本参数被省略，默认使用当前驱动器。
//@参数
//@别名  置磁盘卷标(磁盘驱动器字符)
BOOL 置磁盘卷标(const wchar_t* pText);

//@备注  改变当前的缺省驱动器。成功返回真，失败返回假。
//@参数  参数值指明一个存在的驱动器。类似“A”、“B”、“C”等，只取用给定文本的第一个字符。如果使用零长度的文本，则当前的驱动器不会改变。
//@别名  改变驱动器(欲改变到的驱动器)
BOOL 改变驱动器(const wchar_t* pText);

//@备注  改变当前的目录，但不会改变缺省驱动器位置。成功返回真，失败返回假。
//@参数  参数值指明哪个目录将成为新的缺省目录，可能会包含驱动器。如果没有指定驱动器，则在当前的驱动器上改变缺省目录。
//@别名  改变目录(欲改变到的目录)
BOOL 改变目录(const wchar_t* pDir);

//@备注  返回一个文本，用来代表当前的目录。如果失败，返回空文本。
//@别名  取当前目录()
CXText 取当前目录();

//@备注  创建一个新的目录。成功返回真，失败返回假。
//@别名  创建目录(欲创建的目录名称)
BOOL 创建目录(const wchar_t* pDir);

//@备注  删除一个存在的目录及其中的所有子目录和下属文件，请务必谨慎使用本命令
//@别名  删除目录(欲删除的目录名称)
inline BOOL 删除目录(CXText 欲删除的目录名称) {	return xcl_deleteFolder(欲删除的目录名称);}

//@备注  成功返回真，失败返回假
//@别名  复制文件(被复制的文件名,复制到的文件名)
inline BOOL 复制文件(CXText 被复制的文件名, CXText 复制到的文件名) { return CopyFile(被复制的文件名, 复制到的文件名, FALSE); }

//@备注  将文件从一个位置移动到另外一个位置。成功返回真，失败返回假。
//@别名  移动文件(被移动的文件, 移动到的位置)
BOOL 移动文件(const wchar_t* pFileSrc, const wchar_t* pFileDest);

//@备注  成功返回真，失败返回假。
//@别名  删除文件(欲删除的文件名)
inline BOOL 删除文件(const wchar_t* pFile) { return DeleteFile(pFile); }

//@备注  重新命名一个文件或目录。成功返回真，失败返回假
//@别名  文件更名(欲更名的原文件或目录名, 欲更改为的现文件或目录名)
inline BOOL 文件更名(const wchar_t* pSrc, const wchar_t* pDest) {	return MoveFile(pSrc, pDest);}

//@备注  判断指定的磁盘文件是否真实存在。如存在返回真，否则返回假。
//@别名  文件是否存在(欲测试的文件名称)
inline BOOL 文件是否存在(const wchar_t* pFileName) { return PathFileExists(pFileName); }

//@备注  返回一个文本，用以表示所找到的文件名或目录名，它必须与所要求的名称格式或文件属性相匹配。支持使用多字符(*) 和单字符(? ) 通配符来指定多重文件。在某子程序中第一次调用本命令时，必须指定“欲寻找文件”参数，否则将返回空文本(“”)。在第一次调用以后如果想得到其它匹配的文件名，再一次调用本命令，且不要提供欲寻找文件名参数。如果已没有合乎条件的文件，本命令会返回一个空文本。一旦返回值为空文本，要再次调用本命令时，就必须指定“欲寻找文件”参数。不必访问完所有当前匹配的文件名，就可以使用一个新的“欲寻找文件”进行新的寻找。
//@参数  可以被省略。可以使用多字符(*) 和单字符(? ) 通配符来指定多重文件。在非首次寻找文件时，参数值必须为空或被省略。
//@参数  可以被省略。参数值可以为以下常量值或其和： 1、#只读文件； 2、#隐藏文件； 4、#系统文件； 16、#子目录； 32、#存档文件 。通过将这些常量值加起来可以一次设置多个文件属性。如果省略本参数，默认为搜寻除子目录外的所有文件。
//@别名  寻找文件(欲寻找的文件或目录名称, 欲寻找文件的属性)
inline CXText  寻找文件_未实现(const wchar_t* pName, int flag) { return L""; }

//@备注  返回指定文件被创建或最后修改后的日期和时间。如果该文件不存在，将返回100年1月1日
//@别名  取文件时间(文件名)
INT64 取文件时间(const wchar_t* pFileName);

//@备注 返回一个文件的长度，单位是字节。如果该文件不存在，将返回 -1
//@别名 取文件尺寸(文件名)
int 取文件尺寸(const wchar_t* pFileName);

//@备注  返回一个文件或目录的属性。此属性值由以下常量或其和构成： 1、#只读文件； 2、#隐藏文件；  4、#系统文件； 16、#子目录；32、#存档文件 。要判断是否设置了某个属性，在返回值与想要得知的属性值之间使用“位与”命令进行比较。如果所得的结果不为零，则表示设置了这个属性值。如果取文件属性失败
//@别名  取文件属性(文件名)
inline int 取文件属性(const wchar_t* pFileName) {	return GetFileAttributes(pFileName);}

//@备注  为一个文件设置属性信息。成功返回真
//@参数 
//@参数  参数值可以为以下常量值或其和： 1、#只读文件； 2、#隐藏文件； 4、#系统文件； 32、#存档文件 。通过将这些常量值加起来可以一次设置多个文件属性。
//@别名  置文件属性(欲设置其属性的文件名称,欲设置为的属性值)
inline BOOL 置文件属性(const wchar_t* pFileName, int 欲设置为的属性值) { return SetFileAttributes(pFileName, 欲设置为的属性值); }

//@备注  返回一个在指定目录中确定不存在的 .TMP 全路径文件名称。
//@参数  可以被省略。如果省略本参数，默认将使用系统的标准临时目录。
//@别名  取临时文件名(目录名)
CXText  取临时文件名(const wchar_t* pName);

//@备注  返回一个字节集，其中包含指定文件的所有数据
//@别名  读入文件(文件名)
CXBytes 读入文件(const wchar_t* pFileName);

//@备注  本命令用作将一个或数个字节集顺序写到指定文件中，文件原有内容被覆盖。成功返回真，失败返回假
//@别名  写到文件(文件名, 欲写入文件的数据)
BOOL 写到文件(const wchar_t* pFileName, CXBytes& data_);
//@分组}


//@分组{ 文件读写

struct FILEELEMENT
{
	INT   nType;
	void* FileHandle;
	void* pLast;
	INT    nCryptStart;
	unsigned char strMD5[36];
	unsigned char strTable[258];
};

class CMyMemFile
{
public:
	// Constructors
	CMyMemFile(UINT nGrowBytes = 1024);
	CMyMemFile(BYTE* lpBuffer, UINT nBufferSize, UINT nGrowBytes = 0);

	// Operations
	void Attach(BYTE* lpBuffer, UINT nBufferSize, UINT nGrowBytes = 0);
	BYTE* Detach();

	// Advanced Overridables
protected:
	virtual BYTE* Alloc(DWORD nBytes);
	virtual BYTE* Realloc(BYTE* lpMem, DWORD nBytes);
	//	virtual BYTE* Memcpy(BYTE* lpMemTarget, const BYTE* lpMemSource, UINT nBytes);
	virtual void Free(BYTE* lpMem);
	virtual void GrowFile(DWORD dwNewLen);

	// Implementation
protected:
	UINT m_nGrowBytes;
	DWORD m_nPosition;
	DWORD m_nBufferSize;
	DWORD m_nFileSize;
	BYTE* m_lpBuffer;
	BOOL m_bAutoDelete;

public:
	DWORD GetFileSize();
	virtual ~CMyMemFile();

	virtual DWORD GetPosition() const;
	//BOOL GetStatus(CFileStatus& rStatus) const;
	enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };
	virtual LONG Seek(LONG lOff, UINT nFrom);
	virtual void SetLength(DWORD dwNewLen);
	virtual UINT Read(void* lpBuf, UINT nCount);
	virtual void Write(const void* lpBuf, UINT nCount);
	virtual void Abort();
	//	virtual void Flush();
	virtual void Close();
	enum BufferCommand { bufferRead, bufferWrite, bufferCommit, bufferCheck };
	virtual UINT GetBufferPtr(UINT nCommand, UINT nCount = 0,
		void** ppBufStart = NULL, void** ppBufMax = NULL);

	// Unsupported APIs
//	virtual CFile* Duplicate() const;
//	virtual void LockRange(DWORD dwPos, DWORD dwCount);
//	virtual void UnlockRange(DWORD dwPos, DWORD dwCount);

};


//@备注  打开一个普通文件，以对文件进行输入或输出。成功返回被打开文件的文件号，失败返回 0。
//@参数
//@参数  可以被省略。参数值说明对文件的操作方式，如果省略本参数，默认为“#读写”。方式值可以为以下常量之一：
//1、#读入：从指定文件读入数据，如果该文件不存在则失败；
//2、#写出：写出数据到指定文件，如果该文件不存在则失败；
//3、#读写：从文件中读入数据或者写出数据到文件，如果该文件不存在则失败；
//4、#重写：写出数据到指定文件。如果该文件不存在则先创建一个新文件，如果已经存在就先清除其中的所有数据；
//5、#改写：写出数据到指定文件。如果该文件不存在则创建一个新文件，如果已经存在就直接打开；
//6、#改读：从文件中读入数据或者写出数据到文件。如果该文件不存在则创建一个新文件，如果已经存在就直接打开。
//@参数  可以被省略。参数值指定限制其它进程操作此文件的方式。如果省略本参数，默认为“#无限制”。方式值可以为以下常量之一：
//1、#无限制：允许其它进程任意读写此文件；
//2、#禁止读：禁止其它进程读此文件；
//3、#禁止写：禁止其它进程写此文件；
//4、#禁止读写：禁止其它进程读写此文件。
//@别名  打开文件(欲打开的文件名称, 打开方式, 共享方式)
vint 打开文件(const wchar_t* pFileName, int openType, int shareType);

//@备注  建立一个内存文件，以计算机内存为存储介质对数据进行文件式的快速输入或输出。成功返回被打开文件的文件号，失败返回 0。
//@别名  打开内存文件()
vint 打开内存文件();

//@备注  关闭被打开的各种类型文件。
//@参数  参数值指明欲关闭的文件号，该文件号由“打开文件”命令所返回。
//@别名  关闭文件(欲关闭的文件号)
void 关闭文件(vint fileno_);

//@备注  关闭所有现行被打开的文件。
//@别名  关闭所有文件()
void 关闭所有文件();

//@备注  在有若干个进程访问同一个文件的环境中，使用本命令拒绝其它用户对被打开文件中的某个区域进行读写访问。成功返回真，失败返回假。
//@参数  该文件号由“打开文件”命令所返回。
//@参数  位置值从 0 开始。
//@参数
//@参数  可以被省略。本参数指定加锁失败后反复进行重试的毫秒数。如果被省略，默认为 0 ，即一旦失败立即返回。如果参数值提供为 - 1 ，则反复进行重试，直到加锁成功为止。
//@别名  锁住文件(欲加锁或解锁的文件号, 欲加锁或解锁的位置, 欲加锁或解锁的长度, 加锁重试时间)
BOOL 锁住文件(vint fileno_, int pos, int length, int time_);

//@备注  解除由“锁住文件”命令对文件所进行的锁定。成功返回真，失败返回假。注意：本命令调用时所提供的参数值必须与调用“锁住文件”命令时所提供的参数值完全一致。
//@参数  该文件号由“打开文件”命令所返回。
//@参数  位置值从 0 开始。
//@参数
//@别名  解锁文件(欲加锁或解锁的文件号, 欲加锁或解锁的位置, 欲加锁或解锁的长度)
BOOL 解锁文件(vint fileno_, int pos, int length);

//@备注  在被打开的文件中，设置下一个读或写操作的位置。成功返回真，失败返回假。
//@参数  该文件号由“打开文件”命令所返回。
//@参数  可以被省略。参数值指定从文件中开始移动的位置。可以为以下常量之一：1、#文件首； 2、#文件尾； 3、#现行位置。如果本参数被省略，默认值为“#文件首”。
//@参数  参数值指定相对于起始移动位置的移动长度。
//@别名  移动读写位置(欲进行操作的文件号, 起始移动位置, 移动距离)
BOOL 移动读写位置(vint fileno_, int pos, int length);

//@备注  在被打开的文件中，设置下一个读或写操作的位置到文件首。成功返回真，失败返回假。
//@参数  该文件号由“打开文件”命令所返回。
//@别名  移到文件首()
BOOL 移到文件首(vint fileno_);

//@备注  在被打开的文件中，设置下一个读或写操作的位置到文件尾。成功返回真，失败返回假。
//@参数  该文件号由“打开文件”命令所返回。
//@别名  移到文件尾(欲进行操作的文件号)
BOOL 移到文件尾(vint fileno_);

//@备注  本命令用作从文件中当前读写位置读取并返回一段字节集数据，实际读入长度（即返回的字节集的尺寸）可能会小于欲读入长度。如果读入失败，将返回一个空字节集并且自动将当前文件读写位置移到文件尾部。
//@参数  该文件号由“打开文件”命令所返回。
//@参数
//@别名  读入字节集(欲读入数据的文件号, 欲读入数据的长度)
CXBytes  读入字节集(vint fileno_, int length);

//@备注  本命令用作写出一段或数段字节集数据到文件中当前读写位置处。成功返回真，失败返回假。命令参数表中最后一个参数可以被重复添加。
//@参数  该文件号由“打开文件”命令所返回。
//@别名  写出字节集(欲写出数据的文件号,  欲写出的字节集数据)
BOOL 写出字节集(vint fileno_, CXBytes& bytes_);

//@备注 本命令用作从文件中当前读写位置读取并返回一段文本数据，实际读入长度（即返回文本的尺寸）可能会小于欲读入长度。如果该数据中存在字节 0 或 26（文本结束标志），将仅返回该字节之前的数据。如果读入失败，将返回一个空文本并且自动将当前文件读写位置移到文件尾部。
//@参数 该文件号由“打开文件”命令所返回。
//@参数 可以被省略。如果本参数被省略，默认读入文件中的所有文本数据。
//@别名 读入文本(欲读入文本数据的文件号, 欲读入文本数据的长度)
CXTextA  读入文本A(vint fileno_, int length);

//@备注  本命令用作写出一段或数段文本数据到文件中当前读写位置处。成功返回真，失败返回假。命令参数表中最后一个参数可以被重复添加。
//@参数  该文件号由“打开文件”命令所返回。
//@参数  参数值如果不为文本类型数据，将自动进行转换，如果无法转换（即数据类型为字节集、子程序指针、库或用户自定义数据类型），则不写出此数据。
//@别名  写出文本A(欲写出文本的文件号, 欲写出的文本)
BOOL 写出文本A(vint fileno_, const char* pText);

//@备注  本命令用作从文件中当前读写位置读取并返回一行文本数据，行末的回车及换行符将被抛弃。如果读入失败，将返回一个空文本并且自动将当前文件读写位置移到文件尾部。
//@参数  该文件号由“打开文件”命令所返回。
//@别名  读入一行(欲读入文本数据的文件号)
CXTextA 读入一行(vint fileno);

//@备注  本命令用作写出一行或多行文本数据到文件中当前读写位置处，每行的尾部将被自动加上回车及换行符。成功返回真，失败返回假。命令参数表中最后一个参数可以被重复添加。
//@参数  该文件号由“打开文件”命令所返回。
//@参数  参数值如果不为文本类型数据，将自动进行转换，如果无法转换（即数据类型为字节集、子程序指针、库或用户自定义数据类型），则不写出此数据。
//@别名  写文本行A(欲写出文本的文件号, 欲写出的文本)
BOOL 写文本行A(vint fileno_, const char* pText);

//@备注  本命令应该与“写出数据”命令配合使用，用作从文件中当前读写位置读取格式数据到指定的一系列变量或数组变量中。成功返回真，失败返回假。本命令为中级命令。命令参数表中最后一个参数可以被重复添加。
//@参数  该文件号由“打开文件”命令所返回。
//@参数  提供参数数据时只能提供变量及变量数组。如果变量的数据类型为用户自定义或库定义数据类型，命令将会失败。
//@别名  读入数据(欲读入数据的文件号, 存放所读入数据的变量)
BOOL 读入数据(vint fileno_, CXBytes& bytes);

//@备注 本命令应该与“读入数据”命令配合使用，用作写出一系列变量或数组变量的格式数据到文件中当前读写位置处。成功返回真，失败返回假。
//具体各种数据类型数据的写出格式为：
//1、数值型、逻辑型、日期时间型、子程序指针型： 为其所对应的实际数据；
//2、文本型：   为文本数据 + 字节 0 ；
//3、字节集型： 为字节集数据长度（整数） + 字节集实际数据；
//4、以上各种数据类型的数组型数据： 为非数组情况下数据格式的顺序排列。本命令为中级命令。命令参数表中最后一个参数可以被重复添加。
//@参数  该文件号由“打开文件”命令所返回。
//@参数  提供参数数据时可以同时提供数组或非数组数据。如果被写出数据的数据类型为用户自定义或库定义数据类型，命令将会失败。
//@别名  写出数据(欲写出数据的文件号, 欲写出的数据)
BOOL 写出数据(vint fileno_, CXBytes& bytes);

//@备注  如果指定被打开文件的读写位置已经处于该文件数据的尾部，则返回真，否则返回假。
//@参数  参数值指明欲操作的文件号，该文件号必须由“打开文件”命令所返回。
//@参数  可以被省略。如果本参数值为真而且下一即将读入的字节为字节值 0 或 26 等文本终止标记符或者当前读写位置已处于该文件数据的尾部，命令将返回真。如果本参数被省略或为假，将不进行此检查。
//@别名  是否在文件尾(文件号)
BOOL 是否在文件尾(vint fileno_, BOOL bIsReadEnd = FALSE);

//@备注  返回指定被打开文件的当前读 / 写位置，位置值从 0 开始。如果给定文件号无效或失败，返回 - 1 。
//@参数  参数值指明欲操作的文件号，该文件号必须由“打开文件”命令所返回。
//@别名  取读写位置(文件号)
int  取读写位置(vint fileno_);

//@备注  返回指定被打开文件的尺寸，该尺寸以字节为单位。如果给定文件号无效或失败，返回 - 1 。
//@参数  参数值指明欲操作的文件号，该文件号必须由“打开文件”命令所返回。
//@别名  取文件长度(文件号)
int  取文件长度(vint fileno_);

//@备注  本命令用作插入一段或数段字节集数据到文件中当前读写位置处。该文件被打开时必须给予"#读写"或"#改读"权限。成功返回真，失败返回假。命令参数表中最后一个参数可以被重复添加。
//@参数  该文件号由“打开文件”命令所返回。
//@参数
//@别名  插入字节集(欲写出数据的文件号, 欲写出的字节集数据)
inline BOOL 插入字节集(vint fileno_, CXBytes & bytes) { return 写出字节集(fileno_, bytes); }

//@备注  本命令用作插入一段或数段文本数据到文件中当前读写位置处。该文件被打开时必须给予"#读写"或"#改读"权限。成功返回真，失败返回假。命令参数表中最后一个参数可以被重复添加。
//@参数  该文件号由“打开文件”命令所返回。
//@参数  参数值如果不为文本类型数据，将自动进行转换，如果无法转换（即数据类型为字节集、子程序指针、库或用户自定义数据类型），则不写出此数据。
//@别名  插入文本A(欲写出文本的文件号, 欲写出的文本)
inline BOOL 插入文本A(vint fileno_, const char* pText) { return 写出文本A(fileno_, pText); }

//@备注  本命令用作插入一段或数段文本行到文件中当前读写位置处。该文件被打开时必须给予"#读写"或"#改读"权限。成功返回真，失败返回假。命令参数表中最后一个参数可以被重复添加。
//@参数  该文件号由“打开文件”命令所返回。
//@参数  参数值如果不为文本类型数据，将自动进行转换，如果无法转换（即数据类型为字节集、子程序指针、库或用户自定义数据类型），则不写出此数据。
//@别名  插入文本行A(欲写出文本的文件号, 欲写出的文本)
inline BOOL 插入文本行A(vint fileno_, const char* pText) { return 写文本行A(fileno_, pText); }

//@备注  本命令用作在文件中当前读写位置处删除一段字节数据，文件后面的数据顺序前移。该文件被打开时必须给予"#读写"或"#改读"权限。成功返回真，失败返回假。
//@参数  该文件号由“打开文件”命令所返回。
//@参数
//@别名  删除数据(文件号, 欲删除数据的字节数)
BOOL 删除数据(vint fileno_, int length);

//@备注  打开一个以指定密码加密的文件，以对此文件进行快速安全访问，支持大尺寸文件。成功返回被打开文件的文件号，失败返回 0。
//@参数
//@参数  可以被省略。参数值说明对文件的操作方式，如果省略本参数，默认为“#读写”。方式值可以为以下常量之一：
//@1、#读入：从指定文件读入数据，如果该文件不存在则失败；
//@2、#写出：写出数据到指定文件，如果该文件不存在则失败；
//@3、#读写：从文件中读入数据或者写出数据到文件，如果该文件不存在则失败；
//@4、#重写：写出数据到指定文件。如果该文件不存在则先创建一个新文件，如果已经存在就先清除其中的所有数据；
//@5、#改写：写出数据到指定文件。如果该文件不存在则创建一个新文件，如果已经存在就直接打开；
//@6、#改读：从文件中读入数据或者写出数据到文件。如果该文件不存在则创建一个新文件，如果已经存在就直接打开。
//@参数  可以被省略。参数值指定限制其它进程操作此文件的方式。如果省略本参数，默认为“#无限制”。方式值可以为以下常量之一：
//@1、#无限制：允许其它进程任意读写此文件；
//@2、#禁止读：禁止其它进程读此文件；
//@3、#禁止写：禁止其它进程写此文件；
//@4、#禁止读写：禁止其它进程读写此文件。
//@参数  可以被省略。如果即将打开的文件中不存在任何数据（即为空文件或将创建的新文件），本参数指定保护该文件时所将使用的密码，以后所有写入该文件中的数据都将使用此密码加密后写入。建议密码长度最少为6个字符以上，并且最好混合使用汉字、字母、数字、符号，以保证密码本身的安全性。如果即将打开的文件中已经存在数据，本参数提供访问此已有数据时所需要的正确密码，如果此数据没有加密，请提供空文本以表示不需要密码。注意系统不会去校验密码的正确性，如果提供错误的密码，读写已有文件数据将得到错误的结果，请千万注意。因此如果需要校验密码是否正确，请在加密后的文件中保存正确的密码文本或密码文本的数据摘要信息（见数据操作支持库一中的“取数据摘要”命令），然后在打开加密文件后读出该信息对密码进行验证。系统所使用的加密算法是国际标准的RC4算法，可以保证数据的安全性。如果本参数被省略，则默认为空文本，即无密码。
//@参数  可以被省略。本参数指定从文件首部开始不希望被加密部分的长度，系统在读写此区域内的数据时，不会使用密码对其进行加解密操作。此参数用作将加密文件分为明文区和密文区两部分，以方便某些应用程序同时保存一些明文数据。注意当打开已有加密数据的文件时，此参数值必须与新建此加密文件时所提供的参数值一致，否则会造成数据访问错误。如果本参数被省略，则默认值为0，即没有明文区。
//@别名  打开加密文件(欲打开的文件名称, 打开方式, 共享方式, 文件密码, 明文区长度)
vint 打开加密文件(const wchar_t* pFileName, int openMode =3, int shareMode = 1, const wchar_t* pass = NULL, int length =0);
//@分组}


//@分组{ 系统处理

//@备注  本命令运行指定的可执行文件或者外部命令。如果成功，返回真，否则返回假。
//@参数
//@参数  初始值为“假”。
//@参数  可以被省略。参数值可以为以下常量之一：1、#隐藏窗口； 2、#普通激活； 3、#最小化激活； 4、#最大化激活； 5、#普通不激活； 6、#最小化不激活。如果省略本参数，默认为“普通激活”方式。
//@别名  运行(欲运行的命令行, 是否等待程序运行完毕, 被运行程序窗口显示方式)
BOOL  运行(const wchar_t* pCommandline, BOOL bWait, int nShow);

//@备注  返回存放于当前 Windows 系统剪辑板中的文本。如果当前剪辑板中无文本数据，将返回空文本。
//@别名  取剪辑板文本()
CXText  取剪辑板文本();

//@备注  将指定文本存放到当前 Windows 系统剪辑板中去，剪辑板中的原有内容被覆盖。成功返回真，失败返回假。
//@参数
//@别名  置剪辑板文本(准备置入剪辑板的文本)
BOOL 置剪辑板文本(const wchar_t* pText);

//@备注  将指定位图存放到当前 Windows 系统剪辑板中去，剪辑板中的原有内容被覆盖。成功返回真，失败返回假。
//@参数  位图数据，为字节集类型数据，该数据必须为位图文件格式的字节集。
//@别名  置剪辑板位图(位图数据)
BOOL 置剪辑板位图(const CXBytes& bmpdata);

//@备注  如果当前 Windows 系统剪辑板中有文本数据，则返回真，否则返回假。
//@别名  剪辑板中可有文本()
BOOL 剪辑板中可有文本();

//@备注 清除当前 Windows 系统剪辑板中的所有数据。
//@别名 清除剪辑板()
void 清除剪辑板();

//@备注  返回屏幕当前显示区域的宽度，单位为像素点。
//@别名  取屏幕宽度()
int 取屏幕宽度();

//@备注  返回屏幕当前显示区域的高度，单位为像素点。
//@别名  取屏幕高度()
int 取屏幕高度();

//@备注  返回鼠标指针的当前水平位置，单位为像素点，相对于屏幕左边。
//@别名  取鼠标水平位置()
int 取鼠标水平位置();

//@备注  返回鼠标指针的当前垂直位置，单位为像素点，相对于屏幕顶边。
//@别名  取鼠标垂直位置()
int 取鼠标垂直位置();

//@备注  返回当前显示方式所提供的最大颜色显示数目。
//@别名  取颜色数()
int 取颜色数();

inline BOOL 输入框_未实现(){}

//@备注  在对话框中显示信息，等待用户单击按钮，并返回一个整数告诉用户单击哪一个按钮。该整数为以下常量值之一： 0、#确认钮； 1、#取消钮； 2、#放弃钮； 3、#重试钮； 4、#忽略钮； 5、#是钮； 6、#否钮。如果对话框有“取消”按钮，则按下 ESC 键与单击“取消”按钮的效果相同。
//@参数  提示信息只能为文本、数值、逻辑值或日期时间。如果提示信息为文本且包含多行，可在各行之间用回车符(即“字符(13)”)、换行符(即“字符(10)”) 或回车换行符的组合(即：“字符(13) + 字符(10)”) 来分隔。
//@参数  初始值为“0”。参数值由以下几组常量值组成，在将这些常量值相加以生成参数值时，每组值只能取用一个数字（第五组除外）：
//第一组（描述对话框中显示按钮的类型与数目）：
//0、#确认钮； 1、#确认取消钮； 2、#放弃重试忽略钮； 3、#取消是否钮；     4、#是否钮； 5、#重试取消钮
//第二组（描述图标的样式）：
//16、#错误图标； 32、#询问图标； 48、#警告图标； 64、#信息图标
//第三组（说明哪一个按钮是缺省默认值）：
//0、#默认按钮一； 256、#默认按钮二； 512、#默认按钮三； 768、#默认按钮四
//第四组（决定如何等待消息框结束）：
//0、#程序等待； 4096、#系统等待
//第五组（其它）：
//65536、#位于前台； 524288、#文本右对齐
//@参数  可以被省略。参数值指定显示在对话框标题栏中的文本。如果省略，默认为文本“信息：”。
//@参数  可以被省略。指定信息框的父窗口, 可以是一个"窗口"类型数据或者一个整数型窗口句柄.如果被省略, 默认为无.
//@别名  信息框(提示信息, 按钮, 窗口标题, 父窗口)
int 信息框(const wchar_t* 提示信息=NULL, int 按钮=0, const wchar_t* 窗口标题 = NULL, HWND 父窗口 = NULL);

//@备注  通过计算机媒体设备或者喇叭发出一个声音。
//@别名  鸣叫()
void 鸣叫();

//@备注  返回自 Windows 系统启动后到现在为止所经历过的毫秒数。
//@别名  取启动时间()
inline int 取启动时间() { return GetTickCount(); }

//@备注  本命令设置现行鼠标的形状为沙漏形，用作在即将长时间执行程序前提示操作者。
//@别名  置等待鼠标()
void 置等待鼠标();

//@备注  本命令恢复现行鼠标的原有形状，用作与“置等待鼠标”命令配对使用。
//@别名  恢复鼠标()
void 恢复鼠标();

//@备注  在 Windows 注册表中返回指定的文本类型注册表项值。如欲读取注册项默认值，请在项目名后加“\”号，如“test\”。与“取文本注册表项”命令不同的是本命令可以取任意位置处的注册表项。本命令为中级命令。
//@参数  可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户。
//@参数
//@参数  可以被省略。如果指定的注册表项不存在，将返回此默认文本。如果指定的注册表项不存在且本参数被省略，将返回一个长度为 0 的空文本。
//@别名  取文本注册项(根目录, 全路径注册项名, 默认文本)
CXText  取文本注册项(int root_, const wchar_t* fullPathItemName, const wchar_t* pDefaultText);

//@备注  在 Windows 注册表中返回指定的数值类型注册表项值。如欲读取注册项默认值，请在项目名后加“\”号，如“test\”。与“取数值注册表项”命令不同的是本命令可以取任意位置处的注册表项。本命令为中级命令。
//@参数  可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户。
//@参数
//@参数  可以被省略。如果指定的注册表项不存在，将返回此默认数值。如果指定的注册表项不存在且本参数被省略，将返回数值 0。
//@别名 取数值注册项(根目录, 全路径注册项名, 默认数值)
int  取数值注册项(int root_, const wchar_t* fullPathItemName, int defaultValue=0);

//@备注  在 Windows 注册表中返回指定的字节集类型注册表项值。如欲读取注册项默认值，请在项目名后加“\”号，如“test\”。与“取字节集注册表项”命令不同的是本命令可以取任意位置处的注册表项。本命令为中级命令。
//@参数  可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户。
//@参数
//@参数  可以被省略。如果指定的注册表项不存在，将返回此默认字节集。如果指定的注册表项不存在且本参数被省略，将返回空字节集。
//取字节集注册项(根目录, 全路径注册项名, 默认字节集)
CXBytes 取字节集注册项(int root_, const wchar_t* fullPathItemName, CXBytes* defaultValue = NULL);

/*@声明
//@备注  在 Windows 注册表中保存或建立指定的注册表项。如欲写入注册项默认值，请在项目名后加“\”号，如“test\”。成功返回真，否则返回假。与“写注册表项”命令不同的是本命令可以写任意位置处的注册表项。本命令为中级命令。
//@参数  可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户。
//@参数
//@参数  参数值指定欲写入到指定注册表项中的值，只能为数值、文本或者字节集，否则命令将失败。
//写注册项(根目录, 全路径注册项名, 欲写入值)
template<class T>
BOOL 写注册项(int root_, const wchar_t* fullPathItemName, T value_);
*/

//@隐藏{
BOOL 写注册项(int root_, const wchar_t* fullPathItemName, int value_);
BOOL 写注册项(int root_, const wchar_t* fullPathItemName, const wchar_t* value_);
BOOL 写注册项(int root_, const wchar_t* fullPathItemName, CXBytes& value_);
//@隐藏}

//@备注  在 Windows 注册表中删除指定注册表项或注册表目录。如欲删除注册项默认值，请在项目名后加“\”号，如“test\”。成功返回真，否则返回假。注意在删除目录之前必须先删除该目录下所有的项目。本命令为中级命令。
//@参数  可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户。
//@参数
//删除注册项(根目录, 全路径注册项名)
BOOL 删除注册项(int root_, const wchar_t* fullPathItemName);

//@备注  如果指定注册表项存在，返回真，否则返回假。如欲检查注册项是否有默认值，请在项目名后加“\”号，如“test\”。本命令为中级命令。
//@参数  可以为以下常量值之一： 1、#根类； 2、#现行设置； 3、#现行用户； 4、#本地机器； 5、#所有用户。
//@参数  注册项是否存在(根目录, 全路径注册项名)
BOOL 注册项是否存在(int root_, const wchar_t* fullPathItemName);

//@备注  取回Windows系统的默认窗口背景颜色。
//@别名  取默认底色()
int  取默认底色();

//@备注  捕获指定窗口或屏幕上所有现有显示内容，返回相应图片数据。如果失败，返回空字节集。本命令为高级命令。
//@参数  可以被省略。指定欲捕获其显示内容的窗口。如果被省略，默认为捕获屏幕显示内容。
//@参数  可以被省略。指定图片的输出宽度。如果小于0，参数值指定的是最终图片输出宽度相对于所取得图片宽度的百分比（最小为10 % ）；如果等于0，则按图片原宽度输出；如果大于0，指定输出图片的绝对宽度。如果本参数被省略，默认值为0。
//@参数  可以被省略。指定图片的输出高度。如果小于0，参数值指定的是最终图片输出高度相对于所取得图片高度的百分比（最小为10 % ）；如果等于0，则按图片原高度输出；如果大于0，指定输出图片的绝对高度。如果本参数被省略，默认值为0。
//@别名  快照(窗口句柄, 输出宽度, 输出高度)
CXBytes  快照(HWND hWnd, int outWidth, int ouHeight);

//调用格式： 〈文本型〉 读配置项 （文本型 配置文件名，文本型 节名称，文本型 配置项名称，［文本型 默认文本］） - 系统核心支持库->系统处理
//英文名称：GetKeyText
//@备注  读取指定配置文件中指定项目的文本内容。
//@参数  指定配置文件的名称，通常以.ini作为文件名后缀。
//@参数  包含欲读入配置项所处节的名称。
//@参数  参数值指定欲读入配置项在其节中的名称。
//@参数  可以被省略。如果指定配置项不存在，将返回此默认文本。如果指定配置项不存在且本参数被省略，将返回空文本。
//@别名  读配置项(配置文件名, 节名称, 配置项名称, 默认文本)
CXText  读配置项(const wchar_t* pFileName, const wchar_t* pNodeName, const wchar_t* pItemName, const wchar_t* pDefaultText);

//@备注  将指定文本内容写入指定配置项中或者删除指定的配置项或节，如果指定配置文件不存在，将会自动创建。成功返回真，失败返回假。
//@参数  指定配置文件的名称，通常以.ini作为文件名后缀。
//@参数  包含欲写入配置项所处节的名称。
//@参数  可以被省略。参数值指定欲写入配置项在其节中的名称。如果参数值被省略，则删除指定节及其下的所有配置项。
//@参数  可以被省略。参数值指定欲写入到指定配置项中的文本。如果参数值被省略，则删除所指定配置项。
//@别名  写配置项(配置文件名, 节名称, 配置项名称)
BOOL 写配置项(const wchar_t* pFileName, const wchar_t* pNodeName, const wchar_t* pItemName, const wchar_t* pValue);

//@调用格式： 〈文本型数组〉 取配置节名 （文本型 配置文件名） - 系统核心支持库->系统处理
//@英文名称：GetSectionNames
//@备注  返回指定配置文件中所有已有节名的文本数组。
//@参数  指定配置文件的名称，通常以.ini作为文件名后缀。
//@别名  取配置节名(配置文件名)
CXVector<CXText> 取配置节名(const wchar_t* pFileName);

//@备注   返回当前操作系统的版本类别。返回值为以下值之一：
//0、未知； 1、Windows 32S； 2、Windows 9X(包含Win95、Win98、WinME等)； 3、Windows NT操作系统(包含WinNT、Win2000、WinXP等)；
//4、Linux； 5、Windows 10； 6、Windows Server 2016 Technical Preview； 7、Windows 8.1； 8、Windows Server 2012 R2； 9、Windows 8； 10、Windows Server 2012；
//11、Windows 7； 12、Windows Server 2008 R2； 13、Windows Server 2008； 14、Windows Vista。
//*对于已针对 Windows 8.1 或 Windows 10 进行清单的应用程序。 未针对Windows 8.1或Windows 10显示的应用程序将返回 Windows 8 OS 版本值 (6.2) 。 
// 若要为Windows 8.1或Windows 10显示应用程序，请参阅面向 Windows 的应用程序。
//@别名  取操作系统类别()
int 取操作系统类别();

//@备注  显示一个文件打开对话框，允许用户选择或输入多个所需要打开的已存在文件，返回用户所选择或输入后的结果文本数组。如果用户未输入或按“取消”按钮退出，则返回一个空文本数组。
//例如:  动态数组<文本型> arr = 多文件对话框(L"请输入欲打开的文件", L"文本文件(*.txt)|*.txt|所有文件(*.*)|*.*", 0, L"C:\\桌面文件");
//@参数  可以被省略。指定文件打开对话框的标题，如果被省略，则默认为“请输入欲打开的文件：”。
//@参数  可以被省略。例如："文本文件(*.txt)|*.txt|所有文件(*.*)|*.*", 如果被省略，则默认没有过滤器。
//@参数  可以被省略。如果上一参数提供了有效的过滤器文本，则本参数用作指定初始的过滤器，0为第一个过滤器。如果被省略，则默认值为0。
//@参数  可以被省略。指定当打开对话框时所自动跳转到的目录，如果被省略，则默认为当前目录。
//@参数  可以被省略。指定在对话框关闭后是否自动返回到进入对话框前的文件目录，如果被省略，则默认值为假。
//@参数  可以被省略。指定对话框的父窗口, 可以是一个"窗口"类型数据或者一个整数型窗口句柄.如果被省略, 默认为无.
//@返回  动态数组, 保存用户选择的文件
CXVector<CXText> 多文件对话框(const wchar_t* 标题 = L"请输入欲打开的文件：", const wchar_t* 过滤器 = L"", int 初始过滤器 = 0, const wchar_t* 初始目录 = L"",  BOOL 不改变目录 = FALSE, HWND 父窗口 = 0);

//@别名  返回所指定类型的程序名称.本命令为编译预处理命令.
//@参数  1:当前语句所处子程序名称; 2:当前语句所处程序集名称; 3:当前语句所处易语言程序的全路径文件名称(注意如果编译时易语言程序没有保存, 将为空); 4:当前语句所处程序配置信息中的程序名称;  5:当前语句所处程序配置信息中的作者名称; 6:当前语句所处易语言程序的无路径和后缀文件名称(注意如果编译时易语言程序没有保存, 将为空)。
inline CXText 取程序名称_未实现() { return L""; }

//@备注  快速交换两个变量的内容.本命令对于文本、字节集、自定义数据类型不会进行值数据拷贝, 仅交换其指针值, 因此速度要比通过赋值命令间接交换快得多.本命令要求这两个变量的数据类型必须完全一致, 为编译预处理命令.
//@参数  欲将其内容交换到变量2的变量1。
//@参数  欲将其内容交换到变量1的变量2。
template <typename T>
void 交换变量(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

//@备注  快速交换两个变量的内容.本命令对于文本、字节集、自定义数据类型不会进行值数据拷贝, 仅交换其指针值, 因此速度要比通过赋值命令间接交换快得多.本命令与"交换变量"不同的是: 本命令仅要求这两个变量的数据尺寸必须一致, 但是不对数据类型进行检查, 因此调用方必须确保交换后的变量能正常使用.用户可以使用本命令进行类似强制类型转换这样的操作.本命令为编译预处理命令.
//@参数  欲将其内容交换到变量2的变量1。
//@参数  欲将其内容交换到变量1的变量2。
template <typename T>
void 强制交互变量(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

//@备注 调用操作系统的GetLastError函数, 返回该API函数被调用后的返回值.
inline int 取最后错误() { return (int)GetLastError(); }

//@备注  返回所指定文本的Unicode格式字节集。
//@参数  提供将被转换到Unicode字节集的常量文本。
//@参数  可以被省略。本参数如果为真则转换到UTF - 16宽字符文本, 否则转换为UTF - 8文本.本参数如果被省略, 则默认值为真.
//@参数  可以被省略。本参数如果为真则在文本尾部添加结束零字符, 为假则不添加.本参数如果被省略, 则默认值为真.
//@别名  取统一文本(待转换常量文本, 转换到宽文本, 添加结束零字符)
CXBytes 取统一文本(const char* pText, BOOL toWideText, BOOL bTerminator);

//@备注  返回所指定文本转换到Unicode格式文本后的字符数目。
//@参数  提供将被转换到Unicode字节集的常量文本。
//@参数  可以被省略。本参数如果为真则转换到UTF - 16宽字符文本, 否则转换为UTF - 8文本.本参数如果被省略, 则默认值为真.
//@别名  取统一文本长度(待转换常量文本, 转换到宽文本)
int 取统一文本长度(const char* pText, BOOL toWideText);
//@分组}


//@分组{ 媒体播放

/*@声明

//@备注  可以播放.WAV、.MID 声音文件或相应格式的字节集声音数据、声音资源。成功返回真，失败返回假。
//@参数  参数值可以为.WAV、.MID 声音文件名称或相应格式的字节集声音数据、声音资源。
//@参数  可以被省略。为真表示指定音乐将被循环播放，否则仅只播放一次。如果本参数被省略，默认为仅播放一次。
//@别名  播放音乐(欲播放的音乐, 是否循环播放)
template<class T>
BOOL 播放音乐(T, BOOL bLoop = FALSE);
*/

//@隐藏{
BOOL 播放音乐(const wchar_t* pFileName, BOOL bLoop = FALSE);
BOOL 播放音乐(CXBytes& bytes_, BOOL bLoop =FALSE);
BOOL 播放音乐(int resID, BOOL bLoop = FALSE);
//@隐藏}

//@备注 停止正在播放的音乐。
//@别名 停止播放()
void 停止播放();

// 调用格式： 〈无返回值〉 播放MID （［整数型 播放次数］，［整数型 间隔时间］，通用型数组 / 非数组 欲播放的MIDI音乐，... ） - 系统核心支持库->媒体播放
// 英文名称：PlayMID


//@备注  可以自动连续播放多个 MP3 音乐文件。命令参数表中最后一个参数可以被重复添加。
//@参数  可以被省略。为 - 1 表示指定音乐将被循环播放，否则仅只播放指定的次数。如果本参数被省略，默认值为 1 。
//@参数  提供参数数据时可以同时提供数组或非数组数据。
//@别名 播放MP3(播放次数, 欲播放的MP3文件名)
void 播放MP3(int count, const wchar_t* pFileName);


//@分组}

//@分组{ 程序调试
//@分组}


//@分组{ 其他


//是否为空()

//载入图片()
//卸载图片()

//@备注 返回电脑中第一个物理硬盘的物理特征字，该特征字是仅硬件相关的，也就是说与任何软件系统都无关（包括操作系统）。
//用户可以使用此特征字来限制自己的程序仅在某一台计算机上运行，以保护自己软件的版权。
//本命令可以在任何 Windows 系统版本下运行。命令执行后如果返回 0 ，表示此次取硬盘特征字失败。
//由于有可能是因为暂时的 I / O 冲突造成，因此失败后可以等待一段随机时间后再试（可以参看例程）。
//如果重复尝试四五次后仍然失败，表明该硬盘无法取出特征字。
//@别名 取硬盘特征字()
int  取硬盘特征字();


//@备注  返回当前系统运行时环境所支持的语言版本类型，为以下常量值之一： 1、GBK中文； 2、英文； 3、BIG5中文； 4、日文。
//@别名  取系统语言()
int 取系统语言();

//@备注  将数据写出到指定的内存区域，注意调用本命令前一定要确保所提供的内存区域真实有效。本命令的最佳使用场合就是在易语言回调子程序和易语言DLL公开子程序中用作对外输出数据。本命令为高级命令。
//@参数  要写入的数据地址
//@参数  要写入的数据大小,字节为单位
//@参数  本参数提供欲写向内存区域首地址的指针值。
//@参数  可以被省略。本参数提供该内存区域的有效尺寸，如果欲写出数据超出此尺寸值，将被自动切除。参数值如果为 - 1 ，则表示此内存区域尺寸不受限制。如果本参数被省略，则默认值为 - 1。
//@别名  写到内存(欲写到内存的数据, 写入数据大小, 内存区域指针, 内存区域尺寸)
void 写到内存(void* data_, int dataSize, void* addr, int memSize_);

//DLL命令调用转向()


//@分组}

//@分组{ 数据库
//@分组}

//@分组{ 网络通信
//@分组}

//@分组{ 控制台操作

/*@声明
//@备注  在标准输出设备或标准错误设备上输出指定的内容，注意本命令只能在控制台程序中使用。命令参数表中最后一个参数可以被重复添加。
//@参数  可以被省略。本参数提供内容所输出到的设备，可以为以下常量值之一： 
//1、#标准输出设备； 2、#标准错误设备。如果省略本参数，默认为“#标准输出设备”。
//@参数  本参数只能为文本、数值、逻辑值或日期时间。
//如果内容为文本且包含多行，可在各行之间用回车符(即“字符(13)”)、换行符(即“字符(10)”) 或回车换行符的组合(即：“字符(13) + 字符(10)”) 来分隔。
//@别名  标准输出(输出方向, 欲输出内容)
void 标准输出(int 输出方向=1, ...);

*/

//@隐藏{
//template <typename... Args>
//void 标准输出(int 输出方向=1, Args... 输出内容) {
//	std::ostream& 输出流 = (输出方向 == 1) ? std::cout : std::cerr;
//	// 使用ostringstream来将所有的输出内容连接起来
//	std::ostringstream 输出缓冲;
//	(输出缓冲 << ... << 输出内容);
//	输出流 << 输出缓冲.str();
//}

// 递归终止函数，用于处理最后一个参数
template <typename T>
void 标准输出_输出参数(CXText& 输出缓冲, T 参数) {
	xcl_mkValue(输出缓冲, 参数);
}

// 递归函数，用于处理可变参数包中除最后一个参数外的其他参数
template <typename T, typename... Args>
void 标准输出_输出参数(CXText& 输出缓冲, T 参数, Args... 其余参数) {
	xcl_mkValue(输出缓冲, 参数);
	标准输出_输出参数(输出缓冲, 其余参数...);
}

// 修改后的标准输出函数
template <typename... Args>
void 标准输出(int 输出方向 = 1, Args... 输出内容) {

	CXText  输出缓冲;
	std::wostream& 输出流 = (输出方向 == 1) ? std::wcout : std::wcerr;
	标准输出_输出参数(输出缓冲, 输出内容...);
	输出流 << 输出缓冲.get();
}

//@隐藏}

//@备注  在标准输入设备上请求输入最多包含2048个字符的一行文本，返回用户所输入的内容。注意本命令只能在控制台程序中使用。
//@参数  可以被省略。本参数决定输入时是否显示所输入字符，为假不显示，为真显示。如果被省略，默认值为真，即回显。可以通过将本参数设置为假以输入密码等特殊信息。
//@别名  标准输入(是否回显)
CXTextA 标准输入(BOOL 是否回显 = TRUE);

//@分组}


//@分组{  其他

//@别名 正则表达式类A
class X_String_RegexA {
private:
	std::regex* m_regex;
	std::regex_constants::syntax_option_type m_option;
	CXTextA m_expression;
	std::string m_searchStr;
	bool m_icase;
	void reint();
public:
	X_String_RegexA();
	X_String_RegexA(CXTextA);
	X_String_RegexA(CXTextA, CXTextA);
	~X_String_RegexA();

	//@别名 置表达式(表达式)
	void SetEexpression(CXTextA exp);

	//@别名 置大小写模式(是否区分大小写)
	void SetICase(bool icase);

	//@别名 置匹配文本(用于匹配的文本)
	void SetSearchStr(CXTextA str);

	//@备注 用于检查文本是否复合表达式
	//@别名 验证文本()
	bool CheckStr();

	//@备注 取出该正则匹配到的文本
	//@参数 匹配索引 索引值从0开始
	//@参数 起始位置 起始匹配位置
	//@别名 匹配(匹配索引,起始位置)
	CXTextA Search(UINT index = 0, UINT begin = 0);

	//@备注 取出该正则匹配到的文本
	//@参数 匹配索引 索引值从0开始
	//@参数 子成员索引 索引值从0开始
	//@参数 起始位置 起始匹配位置
	//@别名 匹配子文本(匹配索引,子成员索引,起始位置)
	CXTextA SearchSub(UINT index, UINT SubIndex, UINT begin = 0);

	//@备注 取出该正则匹配到的文本
	//@参数 返回数组 用于接收结果的数组
	//@参数 匹配索引 索引值从0开始
	//@参数 起始位置 起始匹配位置
	//@别名 匹配所有(返回数组,匹配索引,起始位置)
	UINT SearchAll(CXVector<CXTextA>& ret, UINT index = 0, UINT begin = 0);

	//@别名 取匹配数量()
	UINT GetSearchCount();

	//@备注 替换在正则表达式查找中找到的文本
	//@返回 替换后的文本
	//@参数 用作替换的文本
	//@别名 替换(用作替换的文本)
	CXTextA Replace(CXTextA str);
};

//@别名 正则表达式类
class X_String_Regex {
private:
	std::wregex* m_regex;
	std::regex_constants::syntax_option_type m_option;
	CXText m_expression;
	std::wstring m_searchStr;
	bool m_icase;
	void reint();
public:
	X_String_Regex();
	X_String_Regex(CXText);
	X_String_Regex(CXText, CXText);
	~X_String_Regex();

	//@别名 置表达式(表达式)
	void SetEexpression(CXText exp);

	//@别名 置大小写模式(是否区分大小写)
	void SetICase(bool icase);

	//@别名 置匹配文本(用于匹配的文本)
	void SetSearchStr(CXText str);

	//@备注 用于检查文本是否复合表达式
	//@别名 验证文本()
	bool CheckStr();

	//@备注 取出该正则匹配到的文本
	//@参数 匹配索引 索引值从0开始
	//@参数 起始位置 起始匹配位置
	//@别名 匹配(匹配索引,起始位置)
	CXText Search(UINT index = 0, UINT begin = 0);

	//@备注 取出该正则匹配到的文本
	//@参数 匹配索引 索引值从0开始
	//@参数 子成员索引 索引值从0开始
	//@参数 起始位置 起始匹配位置
	//@别名 匹配子文本(匹配索引,子成员索引,起始位置)
	CXText SearchSub(UINT index, UINT SubIndex, UINT begin = 0);

	//@备注 取出该正则匹配到的文本
	//@参数 返回数组 用于接收结果的数组
	//@参数 匹配索引 索引值从0开始
	//@参数 起始位置 起始匹配位置
	//@别名 匹配所有(返回数组,匹配索引,起始位置)
	UINT SearchAll(CXVector<CXText>& ret, UINT index = 0, UINT begin = 0);

	//@别名 取匹配数量()
	UINT GetSearchCount();

	//@备注 替换在正则表达式查找中找到的文本
	//@返回 替换后的文本
	//@参数 用作替换的文本
	//@别名 替换(用作替换的文本)
	CXText Replace(CXText str);
};

//@分组}  其他



// TODO: 数组算法
//@分组{  数组算法


//@返回   返回文本在数组内的位置,-1为不存在
//@别名   数组_寻找成员_文本(文本数组,被搜寻文本)
int X_Array_FindArrayMembers(CXVector<std::string> arr, const char* str);

//@备注   c++sort排序
//@参数   要排序的数组
//@参数   真为升序排序,假为降序,默认真
//@参数   区分大小写,默认真
//@别名   数组_排序_文本A(要排序的数组,升序排序,区分大小写)
void X_String_SortA(CXVector <CXTextA>& arr, bool asc = true, bool caseSensitive = true);
//@备注   c++sort排序
//@参数   要排序的数组
//@参数   真为升序排序,假为降序,默认真
//@参数   区分大小写,默认真
//@别名   数组_排序_文本(要排序的数组,升序排序,区分大小写)
void X_String_Sort(CXVector <CXText>& arr, bool asc = true, bool caseSensitive = true);

//@隐藏{
//template<typename T>
//void X_Array_ReverseArray(CXVector<T> &array);
template<typename T>
void X_Array_ReverseArray(CXVector<T>& arr)
{
	//第一项和最后一项互换；第二项与倒数第二项互换；第三项与倒数第三项互换；以此类推，直到换到中间。
	//时间复杂度是O（n），因为对于有n个元素的数组a，需要交换n/2次。
	//空间复杂度是O（1），因为只开辟了2个int的空间。
	T temp;
	int n = arr.size();
	for (int i = 0; i < n / 2; ++i) {
		temp = arr[n - i - 1];
		arr[n - i - 1] = arr[i];
		arr[i] = temp;
	}
};
//@隐藏}
/*@声明
//@参数   待反转数组
//@别名   数组_反转数组()
void X_Array_ReverseArray(...);
*/


//@分组}  数组算法



// TODO: 编码字节
//@分组{  编码字节


//@参数   宽文本字节指针
//@参数   代码页 [可空]
//@别名   编码_WToA(宽文本字节,代码页)
CXTextA X_Coding_WToA(const wchar_t* wp, size_t m_encode = CP_ACP);

//@参数   文本指针
//@参数   代码页
//@别名   编码_AToW(文本字节,代码页)
CXText X_Coding_AToW(const char* c, size_t m_encode = CP_ACP);

//@参数   文本指针
//@别名   编码_Utf8转Gbk(utf8文本)
CXTextA X_Coding_Utf82Gbk(const char* utf8);

//@参数   文本指针
//@别名   编码_Unicode转Utf8(Unicode)
CXTextA X_Coding_UnicodeToUtf8(const wchar_t* unicode);

//@参数   文本指针
//@别名   编码_GBK转Utf8(文本)
CXTextA X_Coding_GBKToUtf8(const char* str);

//@参数   待编码文本 如%u0031%u0032%u0033
//@参数   分隔符 如%
//@别名   编码_usc2到ansiA(待编码文本,分隔符)
CXTextA X_Coding_Usc2ToAnsiA(const CXTextA& instr, CXTextA separator = "%");
//@参数   待编码文本 如%u0031%u0032%u0033
//@参数   分隔符 如%
//@别名   编码_usc2到ansi(待编码文本,分隔符)
CXText X_Coding_Usc2ToAnsi(const CXText& instr, CXText separator = L"%");

//@参数   待编码字符串 如:123
//@参数   分隔符 如%,返回%u0031%u0032%u0033
//@别名   编码_ansi到usc2(待编码文本,分隔符)
CXText X_Coding_AnsiToUsc2(const CXText& instr, CXText separator = L"%");
//@参数   待编码字符串 如:123
//@参数   分隔符 如%,返回%u0031%u0032%u0033
//@别名   编码_ansi到usc2A(待编码文本,分隔符)
CXTextA X_Coding_AnsiToUsc2A(const CXTextA& instr, CXTextA separator = "%");

//@参数   待编码文本 例如:炫彩IDE
//@参数   字符串分隔符 十六进制字符串间的分隔符,例如:","会返回 EC,C5,B2,CA,49,44,45
//@别名   编码_文本转十六进制文本(待编码文本,字符串分隔符)
CXText X_Coding_StringToHex(CXText& str, CXText separator = L"");
//@参数   待编码文本 例如:炫彩IDE
//@参数   字符串分隔符 十六进制字符串间的分隔符,例如:","会返回 EC,C5,B2,CA,49,44,45
//@别名   编码_文本转十六进制文本A(待编码文本,字符串分隔符)
CXTextA X_Coding_StringToHexA(CXTextA& str, CXTextA separator = "");

//@备注   宽字符与单字符在结果表现上并不一致!
//@别名   编码_十六进制文本转字符串(待编码文本)
CXText X_Coding_HexToString(CXText& str);
//@备注   宽字符与单字符在结果表现上并不一致!
//@别名   编码_十六进制文本转字符串A(待编码文本)
CXTextA X_Coding_HexToStringA(CXTextA& str);


//@分组}  编码字节
// TODO: 进制转换
//@分组{  进制转换

//@别名 进制_八到十(八进制值)
int X_Base_OctToDec(int octalNumber);
//@别名 进制_十到八进制(欲转换的值)
LONGLONG X_Base_DecToOct(LONGLONG num);

//@别名 进制_二到十(二进制文本)
double X_Base_BinToDec(const CXText& binStr);
//@别名 进制_二到十A(二进制文本)
double X_Base_BinToDecA(const CXTextA& binStr);

//@别名 进制_十到二(二进制数值)
CXText X_Base_DecToBin(double num);
//@别名 进制_十到二A(二进制数值)
CXTextA X_Base_DecToBinA(double num);

//@别名 进制_三十六到十(三十六进制文本)
LONGLONG X_Base_TsToDec(const CXText& str);
//@别名 进制_三十六到十A(三十六进制文本)
LONGLONG X_Base_TsToDecA(const CXTextA& str);

//@备注 可以将2到36进制的值转为10进制
//@参数 欲转换的值
//@参数 数值类型 2-36,空为自动识别,拥有0x前缀为16进制,否则默认10
//@别名 进制_到十进制A(欲转换的值,数值类型)
LONGLONG X_Base_ToDecA(const CXTextA& str, int base = 0);
//@备注 可以将2到36进制的值转为10进制
//@参数 欲转换的值
//@参数 数值类型 2-36,空为自动识别,拥有0x前缀为16进制,否则默认10
//@别名 进制_到十进制(欲转换的值,数值类型)
LONGLONG X_Base_ToDec(const CXText& str, int base = 0);

//@别名 进制_十到八进制A(欲转换的值,目标进制)
CXTextA X_Base_DecToNA(LONGLONG num, int base = 10);
//@别名 进制_十到N进制(欲转换的值,目标进制)
CXText X_Base_DecToN(LONGLONG num, int base = 10);


//@分组}  进制转换



#endif