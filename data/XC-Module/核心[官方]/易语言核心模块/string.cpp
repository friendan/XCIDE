//
// Created by Huiyi on 2021/4/25.
//
#include "module_yyy.h"

//取随机文本A
CXTextA X_String_GetRandStrA (int len)
{
    CXTextA rets;
    //码表
    const char * map = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int maplen = (int)strlen(map);
    srand((unsigned)time(NULL));
    for (int i=0;i<len;i++)
    {
        int mapindex = rand() % maplen;
        //范围在maplen与1之间
        rets += map [mapindex];
    }
    return rets;
}
//取随机文本
CXText X_String_GetRandStr (int len)
{
    CXText rets;
    //码表
    const wchar_t * map = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int maplen = lstrlenW(map);
    srand((unsigned)time(NULL));
    for (int i=0;i<len;i++)
    {
        int mapindex = rand() % maplen;
        //范围在maplen与1之间
        rets += map [mapindex];
    }
    return rets;
}

//到小写A
CXTextA X_String_ToLowerA(CXTextA str)
{
    CXTextA ret;
    for (int i=0;i<(int)str.size();i++)
    {
        ret += tolower(str[i]);
    }
    return ret;
}
//到小写
CXText X_String_ToLower(CXText str)
{
    CXText ret;
    for (int i=0;i<(int)str.size();i++)
    {
        ret += towlower(str[i]);
    }
    return ret;
}

//到大写A
CXTextA X_String_ToUpperA(CXTextA str)
{
    CXTextA ret;
    for (int i=0;i<(int)str.size();i++)
    {
        ret += toupper(str[i]);
    }
    return ret;
}
//到大写W
CXText X_String_ToUpper(CXText str)
{
    CXText ret;
    for (int i=0;i<(int)str.size();i++)
    {
        ret += towupper(str[i]);
    }
    return ret;
}

//分割文本A
CXVector<CXTextA> X_String_SplitWithStlA(CXTextA str, CXTextA pattern)
{
	CXVector<CXTextA> rets =	text_split2A(str, pattern);
	return rets;
}
//分割文本W
CXVector<CXText> X_String_SplitWithStl(CXText str, CXText pattern)
{
	CXVector<CXText> rets = text_split2(str, pattern);
	return rets;
}

//取中间文本A
CXTextA X_String_GetMiddleTextA(CXTextA text,CXTextA start,CXTextA end,int begin,bool ifnotcasesensitive)
{
    if (ifnotcasesensitive){
        text = X_String_ToLowerA(text);
        start = X_String_ToLowerA(start);
        end = X_String_ToLowerA(end);
    }
    //取前文本位置
    int iStart = text.find2(start,begin);
    if (iStart==std::string::npos){
        return "";
    }
    //取后文本位置
    int iEnd = text.find2(end,iStart + start.size());
    if (iEnd==std::string::npos){
        return "";
    }
    //截取文本
    return text.substr(iStart + start.size(), iEnd - iStart - start.size());
}
//取中间文本W
CXText X_String_GetMiddleText(CXText text,CXText start,CXText end,int begin,bool ifnotcasesensitive)
{
    if (ifnotcasesensitive){
        text = X_String_ToLower(text);
        start = X_String_ToLower(start);
        end = X_String_ToLower(end);
    }
    //取前文本位置
    int iStart = text.find2(start,begin);
    if (iStart==std::wstring::npos){
        return L"";
    }
    //取后文本位置
    int iEnd = text.find2(end,iStart+ start.size() );
    if (iEnd==std::wstring::npos){
        return L"";
    }
    //截取文本
    return text.substr(iStart+start.size(), iEnd- iStart- start.size());
}

//删首尾空A
CXTextA X_String_TrimA(CXTextA str)
{
	std::string l = str.get();
    if( !l.empty() )
    {
        l.erase(0, l.find_first_not_of(' '));
        l.erase(l.find_last_not_of(' ') + 1);
    }
    return l;
}
//删首尾空W
CXText X_String_Trim(CXText str)
{
    std::wstring l = str.get();
    if( !l.empty() )
    {
        l.erase(0, l.find_first_not_of(' '));
        l.erase(l.find_last_not_of(' ') + 1);
    }
    return l;
}

//子文本替换A
CXTextA X_String_SubreplaceA(CXTextA resource_str, CXTextA sub_str, CXTextA new_str,int begin,int MaxRep)
{
    int i=begin;
	std::string dst_str = resource_str.substr(begin,resource_str.size()-begin).get();
	std::string::size_type pos = 0;
    while((pos = dst_str.find(sub_str)) != std::string::npos)   //替换所有指定子串
    {
        if (MaxRep > 0 && i >= MaxRep)
        {
            break;
        }
        dst_str.replace(pos, sub_str.size(), new_str);
        i++;
    }
    return dst_str;
}
//子文本替换W
CXText X_String_Subreplace(CXText resource_str, CXText sub_str, CXText new_str,int begin,int MaxRep)
{
    int i=begin;
    std::wstring dst_str = resource_str.substr (begin,resource_str.size()-begin).get();
    std::wstring::size_type pos = 0;
    while((pos = dst_str.find(sub_str)) != std::wstring::npos)   //替换所有指定子串
    {
        if (MaxRep > 0 && i >= MaxRep)
        {
            break;
        }
        dst_str.replace(pos, sub_str.size(), new_str);
        i++;
    }
    return dst_str;
}

//倒找文本A
int X_String_RfindA(CXTextA source ,CXTextA str,int pos)
{
    int iPos = pos>-1?pos:source.size();
    std::string mStr = source.get();
    return (int)mStr.rfind(str,iPos);
}
//倒找文本W
int X_String_Rfind(CXText source ,CXText str,int pos){
    int iPos = pos>-1?pos:source.size();
    std::wstring mStr = source.get();
    return (int)mStr.rfind(str,iPos);
}

//文本取左边A
CXTextA X_String_GetLeftA(CXTextA text,CXTextA str,int pos)
{
    pos = pos>-1?pos:0;
    int index = text.find2(str,pos);
    index = index!=std::string::npos?index:-1;
    return text.substr(0,index);
}
//文本取左边W
CXText X_String_GetLeft(CXText text,CXText str,int pos)
{
    pos = pos>-1?pos:0;
    int index = text.find2(str,pos);
    index = index!=std::wstring::npos?index:-1;
    return text.substr(0,index);
}

//文本取右边A
CXTextA X_String_GetRightA(CXTextA text,CXTextA str,int pos)
{
    if (str.size() > text.size()) { return ""; };
	std::string l(text);
    pos = pos>-1?pos:text.size();
    int index = (int)l.rfind(str,pos);
    index = index!=std::string::npos?index+1:text.size();
    return text.substr(index,text.size()-index);
}
//文本取右边W
CXText X_String_GetRight(CXText text,CXText str,int pos)
{
    if (str.size() > text.size()) { return L""; };
    std::wstring l(text);
    pos = pos>-1?pos:text.size();
    int index = (int)l.rfind(str,pos);
    index = index!=std::wstring::npos?index+ str.size() :text.size();
    return text.substr(index,text.size()-index);
}

//文本比较A
int X_String_StrCmpA(CXTextA str1,CXTextA str2,bool ifnotcasesensitive){
    if (ifnotcasesensitive) {
        str1=X_String_ToLowerA(str1);
        str2=X_String_ToLowerA(str2);
    }
    return strcmp(str1.get(),str2.get());
}
//文本比较W
int X_String_StrCmp(CXText str1,CXText str2,bool ifnotcasesensitive){
    if (ifnotcasesensitive) {
        str1=X_String_ToLower(str1);
        str2=X_String_ToLower(str2);
    }
    return wcscmp(str1.get(),str2.get());
}
//文本_是否UTF8
bool X_String_WIsUtf8A(const CXTextA& string) {
    int c, i, ix, n, j;
    for (i = 0, ix = string.size(); i < ix; i++)
    {
        c = (unsigned char)string[i];
        //if (c==0x09 || c==0x0a || c==0x0d || (0x20 <= c && c <= 0x7e) ) n = 0; // is_printable_ascii
        if (0x00 <= c && c <= 0x7f) n = 0; // 0bbbbbbb
        else if ((c & 0xE0) == 0xC0) n = 1; // 110bbbbb
        else if (c == 0xed && i < (ix - 1) && ((unsigned char)string[i + 1] & 0xa0) == 0xa0) return false; //U+d800 to U+dfff
        else if ((c & 0xF0) == 0xE0) n = 2; // 1110bbbb
        else if ((c & 0xF8) == 0xF0) n = 3; // 11110bbb
        //else if (($c & 0xFC) == 0xF8) n=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
        //else if (($c & 0xFE) == 0xFC) n=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
        else return false;
        for (j = 0; j < n && i < ix; j++) { // n bytes matching 10bbbbbb follow ?
            if ((++i == ix) || (((unsigned char)string[i] & 0xC0) != 0x80))
                return false;
        }
    }
    return true;
}

//文本_逐字分割W
int  X_String_SplitWitNum(CXText string,CXVector<CXText> &rList) {
    rList.clear();
    for (int i = 0; i < (int)string.size(); i++) {
        wchar_t s[2];
        s [0] = string[i];
        s[1] = L'\0';
        rList.add(s);
    }
    return rList.size();
}
//文本_逐字分割A
int  X_String_SplitWitNumA(CXTextA string, CXVector<CXTextA>& rList) {
    rList.clear();
    for (int i = 0; i < (int)string.size(); i++) {
        char s[2];
        s[0] = (char)string[i];
        s[1] = '\0';
        rList.add(s);
    }
    return (int)rList.size();
}

//文本_是否为数值
bool X_String_IsNumber(CXText string) {
    if (lstrcmpW(string, L"") == 0) { return false; }
    if (string[0]==L'.' || string[string.size()-1]== L'.') { return false; }
    bool r = true;
    for (int i = 0; i < (int)string.size(); i++) {
        if (string[i]<L'0' || string[i] > L'9') {
            r = false;
            break;
        }
    }
    return r;
}
//文本_是否为数值A
bool X_String_IsNumberA(CXTextA string) {
    if (strcmp(string, "") == 0) { return false; }
    if (string[0] == '.' || string[string.size() - 1] == '.') { return false; }
    bool r = true;
    for (int i = 0; i < (int)string.size(); i++) {
        if (string[i] < '0' || string[i] > '9') {
            r = false;
            break;
        }
    }
    return r;
}

CXText X_String_NumberToText(int x) {return std::to_wstring(x).c_str();}
CXText X_String_NumberToText(long x) {return std::to_wstring(x).c_str();}
CXText X_String_NumberToText(long long x) {return std::to_wstring(x).c_str();}
CXText X_String_NumberToText(float x) {return std::to_wstring(x).c_str();}
CXText X_String_NumberToText(double x) {return std::to_wstring(x).c_str();}
CXText X_String_NumberToText(long double x) {return std::to_wstring(x).c_str();}
CXText X_String_NumberToText(unsigned int x) {return std::to_wstring(x).c_str();}
CXText X_String_NumberToText(unsigned long x){return std::to_wstring(x).c_str();}
CXText X_String_NumberToText(unsigned long long x){return std::to_wstring(x).c_str();}
CXTextA X_String_NumberToTextA(int x) { return std::to_string(x).c_str(); }
CXTextA X_String_NumberToTextA(long x) { return std::to_string(x).c_str(); }
CXTextA X_String_NumberToTextA(long long x) { return std::to_string(x).c_str(); }
CXTextA X_String_NumberToTextA(float x) { return std::to_string(x).c_str(); }
CXTextA X_String_NumberToTextA(double x) { return std::to_string(x).c_str(); }
CXTextA X_String_NumberToTextA(long double x) { return std::to_string(x).c_str(); }
CXTextA X_String_NumberToTextA(unsigned int x) { return std::to_string(x).c_str(); }
CXTextA X_String_NumberToTextA(unsigned long x) { return std::to_string(x).c_str(); }
CXTextA X_String_NumberToTextA(unsigned long long x) { return std::to_string(x).c_str(); }
int X_String_TextToInt(CXText str) {  return (!X_String_IsNumber(str))?0 : std::stoi(str.get()); }
long X_String_TextToLong(CXText str) { return (!X_String_IsNumber(str)) ? 0 : std::stol(str.get());}
LONGLONG X_String_TextToLongLong(CXText str) { return(!X_String_IsNumber(str)) ? 0 : std::stoll(str.get()); }
int X_String_TextToIntA(CXTextA str) { return (!X_String_IsNumberA(str)) ? 0 : std::stoi(str.get()); }
long X_String_TextToLongA(CXTextA str) { return (!X_String_IsNumberA(str)) ? 0 : std::stol(str.get()); }
LONGLONG X_String_TextToLongLongA(CXTextA str) { return (!X_String_IsNumberA(str)) ? 0 : std::stoll(str.get()); }

//文本_首字母改大写
CXText X_String_LastToUpper(CXText str) {
    if (!lstrcmpW(str,L"")) {
        return L"";
    }
    std::wstring s = str.get();
    s[0] = towupper(s[0]);
    return s.c_str();
}
//文本_首字母改大写A
CXTextA X_String_LastToUpperA(CXTextA str) {
    if (!strcmp(str, "")) {
        return "";
    }
    std::string s = str.get();
    s[0] = toupper(s[0]);
    return s.c_str();
}