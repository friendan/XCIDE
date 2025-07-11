//
// Created by Huiyi on 2021/4/25.
//
#include "module_yyy.h"

//数组寻找成员_文本
int X_Array_FindArrayMembers (CXVector<CXTextA> arr,const char *str)
{
    int ret = -1;
    for (int i = 0;i<arr.size();i++)
    {
        if(strcmp(arr[i].get(),str)==0)
        {
            ret=i;
            break;
        }
    }
    return ret;
}




//数组_排序_文本A
void X_String_SortA(CXVector <CXTextA> &arr,bool asc,bool caseSensitive){
    std::vector<CXTextA> *as = arr.getVector();
    std::sort(as->begin(), as->end(), [&](CXTextA& a, CXTextA& b)->bool {
        if (caseSensitive)
        {
            CXTextA la = X_String_ToLowerA(a);
            CXTextA lb = X_String_ToLowerA(b);
            return asc ? strcmp(la, lb) < 0 : strcmp(la, lb) > 0;
        }
        return asc?strcmp(a,b)<0: strcmp(a, b) > 0;
        });
}
//数组_排序_文本W
void X_String_Sort(CXVector <CXText>& arr, bool asc, bool caseSensitive) {
    std::vector<CXText>* as = arr.getVector();
    std::sort(as->begin(), as->end(), [&](CXText& a, CXText& b)->bool {
        if (caseSensitive)
        {
            CXText la = X_String_ToLower(a);
            CXText lb = X_String_ToLower(b);
            return asc ? lstrcmpW(la, lb) < 0 : lstrcmpW(la, lb) > 0;
        }
        return asc ? lstrcmpW(a, b) < 0 : lstrcmpW(a, b) > 0;
        });
}