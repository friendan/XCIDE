//
// Created by Huiyi on 2021/5/17.
//
#include "module_e_System.h"

//打开项A
HKEY X_System_Class_Reg::OpenA(CXTextA Path,bool Create) {
    HKEY hResult;
    int index = Path.find("\\");
	std::string str(Path.substr(0,((index== std::string::npos)?0:index)));
   // str = X_String_ToUpperA(str.c_str()).get();
	text_upperA((char*)str.c_str());

    HKEY root;
    if(strcmp(str.c_str(),"HKEY_CLASSES_ROOT")==0){
        root = HKEY_CLASSES_ROOT;
    } else if(strcmp(str.c_str(),"HKEY_CURRENT_USER")==0){
        root = HKEY_CURRENT_USER;
    } else if(strcmp(str.c_str(),"HKEY_LOCAL_MACHINE")==0){
        root = HKEY_LOCAL_MACHINE;
    } else if(strcmp(str.c_str(),"HKEY_USERS")==0){
        root = HKEY_USERS;
    } else if(strcmp(str.c_str(),"HKEY_CURRENT_CONFIG")==0){
        root = HKEY_CURRENT_CONFIG;
    } else {
        return 0;
    }
    LSTATUS status;
    if (Create){
        int n= Path.size()-str.length()-1;
        status = RegCreateKeyA (root, Path.substr(Path.size()-n,n),&hResult);
    } else {
        int n= Path.size()-str.length()-1;
        status = RegOpenKeyA(root, Path.substr(Path.size()-n,n),&hResult);
    }
    if (ERROR_SUCCESS != status)
    {
        return 0;
    } else {
        return hResult;
    }
}
//打开项W
HKEY X_System_Class_Reg::Open(CXText Path, bool Create) {
    HKEY hResult;
    int index = Path.find(L"\\");
    std::wstring str(Path.substr(0, ((index == std::wstring::npos) ? 0 : index)));
    //str = X_String_ToUpper(str.c_str()).get();
	text_upper((wchar_t*)str.c_str());

	HKEY root;
    if (lstrcmpW(str.c_str(), L"HKEY_CLASSES_ROOT") == 0) {
        root = HKEY_CLASSES_ROOT;
    }
    else if (lstrcmpW(str.c_str(), L"HKEY_CURRENT_USER") == 0) {
        root = HKEY_CURRENT_USER;
    }
    else if (lstrcmpW(str.c_str(), L"HKEY_LOCAL_MACHINE") == 0) {
        root = HKEY_LOCAL_MACHINE;
    }
    else if (lstrcmpW(str.c_str(), L"HKEY_USERS") == 0) {
        root = HKEY_USERS;
    }
    else if (lstrcmpW(str.c_str(), L"HKEY_CURRENT_CONFIG") == 0) {
        root = HKEY_CURRENT_CONFIG;
    }
    else {
        return 0;
    }
    LSTATUS status;
    if (Create) {
        int n = Path.size() - str.length() - 1;
        status = RegCreateKeyW(root, Path.substr(Path.size() - n, n), &hResult);
    }
    else {
        int n = Path.size() - str.length() - 1;
        status = RegOpenKeyW(root, Path.substr(Path.size() - n, n), &hResult);
    }
    if (ERROR_SUCCESS != status)
    {
        return 0;
    }
    else {
        return hResult;
    }
}


//枚举子项A
int X_System_Class_Reg::GetItemListA(CXTextA Path,CXVector<CXTextA> &ItemList){
    ItemList.clear();
    HKEY reg = OpenA(Path);
    if (reg == NULL){
        return NULL;
    }
    char regname[256];
    int i=0;
    while (RegEnumKeyA(reg,i,regname,256)==NULL){
        ItemList.add(regname);
        i++;
    }
    RegCloseKey(reg);
    return(ItemList.size());
}
//枚举子项W
int X_System_Class_Reg::GetItemList(CXText Path, CXVector<CXText>& ItemList) {
    ItemList.clear();
    HKEY reg = Open(Path);
    if (reg == NULL) {
        return NULL;
    }
    wchar_t regname[256];
    int i = 0;
    while (RegEnumKeyW(reg, i, regname, 256) == NULL) {
        ItemList.add(regname);
        i++;
    }
    RegCloseKey(reg);
    return(ItemList.size());
}

//枚举键名A
int X_System_Class_Reg::GetKeyListA(CXTextA name,CXVector<StructRegKeyA> &List){
    List.clear();
    HKEY hKey = OpenA(name);
    static HKEY hLastKey = hKey;
    LONG lResult = 0;
    DWORD dwIndex = 0;
    HKEY hCurKey = hKey;
    DWORD dwKeyType;
    DWORD dwKeyDataLength, dwKeyNameLen;
    LPBYTE pbbinKeyData = NULL;
    char *tcKeyName = NULL;
    if(lResult != ERROR_SUCCESS){
        return 0;
    }
    DWORD lNoOfValues = 0;
    DWORD lLongestKeyNameLen = 1;
    DWORD lLongestDataLen = 1;

    lResult = RegQueryInfoKeyA(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &lNoOfValues, &lLongestKeyNameLen, &lLongestDataLen,NULL, NULL);

    if(lResult != ERROR_SUCCESS){
        return 0;
    }
    hLastKey = hKey;
    lLongestKeyNameLen++;
    lLongestDataLen++;
    tcKeyName = new char[lLongestKeyNameLen];
    pbbinKeyData = new BYTE[lLongestDataLen];
    StructRegKeyA rtmp;
    while(true)
    {
        memset(pbbinKeyData, 0, lLongestDataLen);
        memset(tcKeyName, 0, lLongestKeyNameLen);
        dwKeyType = dwKeyDataLength = dwKeyNameLen = 0;
        dwKeyNameLen = lLongestKeyNameLen;
        dwKeyDataLength = lLongestDataLen;
        lResult = RegEnumValueA (hKey, dwIndex, tcKeyName, &dwKeyNameLen, NULL, &dwKeyType, pbbinKeyData, &dwKeyDataLength);
        if(lResult == ERROR_NO_MORE_ITEMS){
            break;
        }
        rtmp.Key = tcKeyName;
        char *c = (char*)pbbinKeyData;
        rtmp.Value = c;
        rtmp.Type = dwKeyType;
        List.add(rtmp);
        dwIndex++;
    }
    RegCloseKey(hKey);
    delete tcKeyName;
    delete pbbinKeyData;
    return List.size();
}
//枚举键名W
int X_System_Class_Reg::GetKeyList(CXText name, CXVector<StructRegKey>& List) {
    List.clear();
    HKEY hKey = Open(name);
    static HKEY hLastKey = hKey;
    LONG lResult = 0;
    DWORD dwIndex = 0;
    HKEY hCurKey = hKey;
    DWORD dwKeyType;
    DWORD dwKeyDataLength, dwKeyNameLen;
    LPBYTE pbbinKeyData = NULL;
    wchar_t* tcKeyName = NULL;
    if (lResult != ERROR_SUCCESS) {
        return 0;
    }
    DWORD lNoOfValues = 0;
    DWORD lLongestKeyNameLen = 1;
    DWORD lLongestDataLen = 1;

    lResult = RegQueryInfoKeyA(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &lNoOfValues, &lLongestKeyNameLen, &lLongestDataLen, NULL, NULL);

    if (lResult != ERROR_SUCCESS) {
        return 0;
    }
    hLastKey = hKey;
    lLongestKeyNameLen++;
    lLongestDataLen++;
    tcKeyName = new wchar_t[lLongestKeyNameLen];
    pbbinKeyData = new BYTE[lLongestDataLen];
    StructRegKey rtmp;
    while (true)
    {
        memset(pbbinKeyData, 0, lLongestDataLen);
        memset(tcKeyName, 0, lLongestKeyNameLen);
        dwKeyType = dwKeyDataLength = dwKeyNameLen = 0;
        dwKeyNameLen = lLongestKeyNameLen;
        dwKeyDataLength = lLongestDataLen;
        lResult = RegEnumValueW(hKey, dwIndex, tcKeyName, &dwKeyNameLen, NULL, &dwKeyType, pbbinKeyData, &dwKeyDataLength);
        if (lResult == ERROR_NO_MORE_ITEMS) {
            break;
        }
        rtmp.Key = tcKeyName;
        rtmp.Value = (wchar_t*)pbbinKeyData;
        rtmp.Type = dwKeyType;
        List.add(rtmp);
        dwIndex++;
    }
    RegCloseKey(hKey);
    delete tcKeyName;
    delete pbbinKeyData;
    return List.size();
}

//取键名类型A
int X_System_Class_Reg::GetKeyTypeA(CXTextA name, CXTextA KeyName){
    int ret = -1;
    HKEY hRoot = OpenA(name);

    char cTmpname [1024];
    int i = 0;
    DWORD dwNameLen = 1024;
    DWORD dwType = 0;
    BYTE dwData[1024];
    DWORD dwDataLen =1024;

    while (RegEnumValueA(hRoot,i,cTmpname,&dwNameLen,0,&dwType,dwData,&dwDataLen)!=ERROR_NO_MORE_ITEMS) {
        if (strcmp (cTmpname,KeyName)==0)
        {
            ret = dwType;
            break;
        }
		dwNameLen = 1024;
		dwDataLen = 1024;
        ++i;
    }
    RegCloseKey(hRoot);
    return ret;
}
//取键名类型W
int X_System_Class_Reg::GetKeyType(CXText name, CXText KeyName) {
    int ret = -1;
    HKEY hRoot = Open(name);
    wchar_t cTmpname[1024];
    int i = 0;
    DWORD dwNameLen = 1024;
    DWORD dwType = 0;
    BYTE dwData[1024];
    DWORD dwDataLen = 1024;

    while (RegEnumValueW(hRoot, i, cTmpname, &dwNameLen, 0, &dwType, dwData, &dwDataLen) != ERROR_NO_MORE_ITEMS) {
        if (lstrcmpW(cTmpname, KeyName) == 0)
        {
            ret = dwType;
            break;
        }
		dwNameLen = 1024;
		dwDataLen = 1024;
        ++i;
    }
    RegCloseKey(hRoot);
    return ret;
}

//是否存在A
bool X_System_Class_Reg::IfExistA(CXTextA name, CXTextA KeyName){
    HKEY hRoot = OpenA(name);
    if (strcmp(KeyName,"")==0){
        RegCloseKey (hRoot);
        return hRoot!=0;
    }
    LSTATUS msg = RegQueryValueExA(hRoot,KeyName, nullptr, nullptr, nullptr, nullptr);
    return msg == ERROR_SUCCESS;
}
//是否存在W
bool X_System_Class_Reg::IfExist(CXText name, CXText KeyName) {
    HKEY hRoot = Open(name);
    if (lstrcmpW(KeyName, L"") == 0) {
        RegCloseKey(hRoot);
        return hRoot != 0;
    }
    LSTATUS msg = RegQueryValueExW(hRoot, KeyName, nullptr, nullptr, nullptr, nullptr);
    return msg == ERROR_SUCCESS;
}

//刷新项A
bool X_System_Class_Reg::ReProjectA(CXTextA name){
    HKEY hRoot = OpenA(name);
    if(hRoot == 0){
        return false;
    }
    LSTATUS msg = RegFlushKey (hRoot);
    RegCloseKey (hRoot);
    return msg==ERROR_SUCCESS;
}
//刷新项W
bool X_System_Class_Reg::ReProject(CXText name) {
    HKEY hRoot = Open(name);
    if (hRoot == 0) {
        return false;
    }
    LSTATUS msg = RegFlushKey(hRoot);
    RegCloseKey(hRoot);
    return msg == ERROR_SUCCESS;
}

//写字节集A
bool X_System_Class_Reg::WriteByteA(CXTextA name, CXTextA KeyName,CXBytes WriteByte,int Tyte){
    HKEY hRoot = OpenA(name);
    LSTATUS msg = ERROR_SUCCESS;
    if(hRoot == 0){
        return false;
    }
    DWORD dwType = Tyte;
    msg = RegSetValueExA(hRoot,KeyName,0,dwType,(BYTE*)WriteByte.get(),WriteByte.size() );
    RegCloseKey (hRoot);
    return msg == ERROR_SUCCESS;
}
//写字节集W
bool X_System_Class_Reg::WriteByte(CXText name, CXText KeyName, CXBytes WriteByte, int Tyte) {
    HKEY hRoot = Open(name);
    LSTATUS msg = ERROR_SUCCESS;
    if (hRoot == 0) {
        return false;
    }
    DWORD dwType = Tyte;
    msg = RegSetValueExW(hRoot, KeyName, 0, dwType, (BYTE*)WriteByte.get(), WriteByte.size());
    RegCloseKey(hRoot);
    return msg == ERROR_SUCCESS;
}

//取字节集A
CXBytes X_System_Class_Reg::GetBytesA(CXTextA name, CXTextA KeyName,int& Type){
    HKEY hRoot = OpenA(name);
    CXBytes ret;
    LSTATUS msg = ERROR_SUCCESS;
    if(hRoot == 0){
        return ret;
    }
    DWORD dwDataLen = 0;
    DWORD dwDataType = 0;
    msg = RegQueryValueExA(hRoot,KeyName,0,&dwDataType,NULL,&dwDataLen);
    BYTE* Data = (BYTE*)malloc(dwDataLen);
    msg = RegQueryValueExA(hRoot,KeyName,0,&dwDataType,Data,&dwDataLen);
    Type = dwDataType;
    if (msg == ERROR_SUCCESS){
        ret.set(Data,dwDataLen);
    }
    free(Data);
    RegCloseKey(hRoot);
    return ret;
}
//取字节集W
CXBytes X_System_Class_Reg::GetBytes(CXText name, CXText KeyName, int& Type) {
    HKEY hRoot = Open(name);
    CXBytes ret;
    LSTATUS msg = ERROR_SUCCESS;
    if (hRoot == 0) {
        return ret;
    }
    DWORD dwDataLen = 0;
    DWORD dwDataType = 0;
    msg = RegQueryValueExW(hRoot, KeyName, 0, &dwDataType, NULL, &dwDataLen);
    BYTE* Data = (BYTE*)malloc(dwDataLen);
    msg = RegQueryValueExW(hRoot, KeyName, 0, &dwDataType, Data, &dwDataLen);
    Type = dwDataType;
    if (msg == ERROR_SUCCESS) {
        ret.set(Data, dwDataLen);
    }
    free(Data);
    RegCloseKey(hRoot);
    return ret;
}

//写DWORDA
bool X_System_Class_Reg::WriteDWORDA(CXTextA name, CXTextA KeyName,int num){
    CXBytes lps;
    lps.addInt(num);
    return WriteByteA(name,KeyName,lps,X_REG_DWORD);
}
//写DWORDW
bool X_System_Class_Reg::WriteDWORD(CXText name, CXText KeyName, int num) {
    CXBytes lps;
    lps.addInt(num);
    return WriteByte(name, KeyName, lps, X_REG_DWORD);
}

//取DWORD值A
int X_System_Class_Reg::GetDWORDA (CXTextA name, CXTextA KeyNam) {
    int type = 0;
    CXBytes lps = GetBytesA (name,KeyNam,type);
    if (type == X_REG_DWORD) {
        return lps.getInt();
    }
    return 0;
}
//取DWORD值W
int X_System_Class_Reg::GetDWORD(CXText name, CXText KeyNam) {
    int type = 0;
    CXBytes lps = GetBytes(name, KeyNam, type);
    if (type == X_REG_DWORD) {
        return lps.getInt();
    }
    return 0;
}

//写二进制值A
bool X_System_Class_Reg::WriteBINA(CXTextA name, CXTextA KeyName,int num){
    CXBytes lps;
    lps.addInt(num);
    return WriteByteA(name,KeyName,lps,X_REG_BINARY);
}
//写二进制值W
bool X_System_Class_Reg::WriteBIN(CXText name, CXText KeyName, int num) {
    CXBytes lps;
    lps.addInt(num);
    return WriteByte(name, KeyName, lps, X_REG_BINARY);
}

//取二进制值A
int X_System_Class_Reg::GetBINA (CXTextA name, CXTextA KeyNam) {
    int type = 0;
    CXBytes lps = GetBytesA (name,KeyNam,type);
    if (type == X_REG_BINARY) {
        return lps.getInt();
    }
    return 0;
}
//取二进制值W
int X_System_Class_Reg::GetBIN(CXText name, CXText KeyNam) {
    int type = 0;
    CXBytes lps = GetBytes(name, KeyNam, type);
    if (type == X_REG_BINARY) {
        return lps.getInt();
    }
    return 0;
}

//写文本值A
bool X_System_Class_Reg::WriteStringA (CXTextA name, CXTextA KeyNam,CXTextA Str) {
    CXBytes lps;
    lps.addTextA(Str);
    return  WriteByteA (name,KeyNam,lps,X_REG_SZ);
}
//写文本值W
bool X_System_Class_Reg::WriteString(CXText name, CXText KeyNam, CXText Str) {
    CXBytes lps;
    lps.addText(Str);
    return  WriteByte(name, KeyNam, lps, X_REG_SZ);
}

//读文本值A
CXTextA X_System_Class_Reg::GetStringA (CXTextA name, CXTextA KeyNam) {
    int type = 0;
    CXBytes lps = GetBytesA (name,KeyNam,type);
    if (type == X_REG_SZ) {
        return lps.getTextPtrA();
    }
    return "";
}
//读文本值W
CXText X_System_Class_Reg::GetString(CXText name, CXText KeyNam) {
    int type = 0;
    CXBytes lps = GetBytes(name, KeyNam, type);
    if (type == X_REG_SZ) {
        return lps.getTextPtr();
    }
    return L"";
}

//删除键A
bool X_System_Class_Reg::DelKeyA(CXTextA name, CXTextA KeyName){
    HKEY hRoot = OpenA(name);
    LSTATUS msg = ERROR_SUCCESS;
    if(hRoot == 0){
        return false;
    }
    msg = RegDeleteValueA(hRoot,KeyName);
    RegCloseKey (hRoot);
    return msg == ERROR_SUCCESS;
}
//删除键W
bool X_System_Class_Reg::DelKey(CXText name, CXText KeyName) {
    HKEY hRoot = Open(name);
    LSTATUS msg = ERROR_SUCCESS;
    if (hRoot == 0) {
        return false;
    }
    msg = RegDeleteValueW(hRoot, KeyName);
    RegCloseKey(hRoot);
    return msg == ERROR_SUCCESS;
}

//写可扩充字符串值A
bool X_System_Class_Reg::WriteExpandStrA(CXTextA name, CXTextA KeyName, CXTextA str) {
    CXBytes lps;
    lps.addTextA(str);
    lps.addByte(0);
    return WriteByteA(name, KeyName, lps, 2);
}
//写可扩充字符串值W
bool X_System_Class_Reg::WriteExpandStr(CXText name, CXText KeyName, CXText str) {
    CXBytes lps;
    lps.addText(str);
    lps.addByte(L'\0');
    return WriteByte(name, KeyName, lps, 2);
}