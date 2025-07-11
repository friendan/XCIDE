//
// Created by HuiYi on 2022/9/21.
//
#include "module_e_Files.h"
#include <commdlg.h>
#include "Shlobj.h"
#include <fstream>
#pragma  comment(lib,"Dbghelp.lib")

//------------------------------
//辅助函数

//取MD5_字节集A
CXTextA Check_GetMD5_BytesA(CXBytes& data)
{
#ifdef XCL_MD5_H
	CXMD5 md5;
	md5.reset();
	md5.update((void*)data.get(), data.size());
	return md5.toString();
#else
	xcl_log("*使用到MD5功能, 需要加载MD5模块");
	return "";
#endif
}

//取MD5_字节集W
CXText Check_GetMD5_Bytes(CXBytes& data) {
	return A2W(Check_GetMD5_BytesA(data));
}

//-----------------------------
//目录_处理A
CXTextA X_Files_DirHandleA(CXTextA dirName) {
    if (dirName[dirName.size() - 1] !='\\' && dirName[dirName.size() - 1] != '/') {
        return dirName+'\\';
    }
    return dirName;
}
//目录_处理W
CXText X_Files_DirHandle(CXText dirName) {
    if (dirName[dirName.size() - 1] !=L'\\' && dirName[dirName.size() - 1] != L'/') {
        return dirName+L'\\';
    }
    return dirName;
}

//目录_创建A
bool X_Files_DirCreateA(CXTextA dirName) {
    CXVector<CXTextA> dlist = X_String_SplitWithStlA(dirName, "\\");
    if (!dlist.size()) {
        return 0;
    }
    bool cf = true;
    CXTextA path = "";
    for (int i = 0; i < dlist.size(); i++)
    {
        if (i != 0)
        {
            path += "\\";
        }
        path += dlist[i];
        if (!X_Files_DirTfSetA(path))
        {
            if (CreateDirectoryA(path, 0) <1)
            {
                cf = false;
                break;
            }
        }
    }
    return cf;
}
//目录_创建W
bool X_Files_DirCreate(CXText dirName) {
    CXVector<CXText> dlist = X_String_SplitWithStl(dirName,L"\\");
    if (!dlist.size()) {
        return 0;
    }
    bool cf = true;
    CXText path = L"";
    for (int i = 0; i < dlist.size(); i++)
    {
        if (i!=0)
        {
            path += L"\\";
        }
        path += dlist[i];
        if (!X_Files_DirTfSet(path))
        {
            if (CreateDirectoryW(path, 0) <1)
            {
                cf = false;
                break;
            }
        }
    }
    return cf;
}

//目录_是否存在A
bool X_Files_DirTfSetA(CXTextA dirName) {
    return PathIsDirectoryA(dirName) == FILE_ATTRIBUTE_DIRECTORY;
}
//目录_是否存在W
bool X_Files_DirTfSet(CXText dirName) {
    return PathIsDirectoryW(dirName) == FILE_ATTRIBUTE_DIRECTORY;
}

//目录_定位A
bool X_Files_DirLocationA(CXTextA dirName, bool editMode) {
    return X_Files_FileLocationA(dirName, editMode);
}
//目录_定位W
bool X_Files_DirLocation(CXText dirName, bool editMode) {
    return X_Files_FileLocation(dirName, editMode);
}

//目录_复制A
bool X_Files_DirCopyA(CXTextA sourceFile, CXTextA targetFile) {
    BOOL r;
    CXComObject SFO;
    r = SFO.Create(L"scripting.FileSystemObject");
    if (r >0) {
        CXText sourceFileW = A2W(sourceFile);
        CXText targetFileW= A2W(targetFile);
        SFO.Method(L"CopyFolder", sourceFileW, targetFileW);
        r = X_Files_DirTfSet(targetFileW);
    }
    return r > 0;
}
//目录_复制W
bool X_Files_DirCopy(CXText sourceFile, CXText targetFile) {
    BOOL r;
    CXComObject SFO;
    r = SFO.Create(L"scripting.FileSystemObject");
    if (r > 0) {
        SFO.Method(L"CopyFolder", sourceFile.get(), targetFile.get());
        r = X_Files_DirTfSet(targetFile);
    }
    return r > 0;
}

//目录_更新W
void X_Files_DirUpdate(CXText sourceFile, CXText targetFile, bool cover) {
    X_Files_DirUpdateA(W2A(sourceFile), W2A(targetFile), cover);
}
//目录_更新A
void X_Files_DirUpdateA(CXTextA sourceFile, CXTextA targetFile,bool cover) {
    //拷贝防止浅拷贝
    CXTextA lsourceFile = sourceFile;
    CXTextA ltargetFile = targetFile;
    long hFile;
    //目录路径补全
    if (lsourceFile[lsourceFile.size()-1]!='\\') {
        lsourceFile += '\\';
    }
    if (ltargetFile[ltargetFile.size() - 1] != '\\') {
        ltargetFile += '\\';
    }
    //新目录不存在创建
    if (!X_Files_DirTfSetA(targetFile))
    {
        X_Files_DirCreateA(targetFile);
    }
    struct _finddata_t fileinfo;
    if ((hFile = _findfirst((lsourceFile + "*.*").get(), &fileinfo)) != -1) {
        do
        {
            if (strcmp(fileinfo.name, ".")==0 || strcmp(fileinfo.name, "..") == 0) {
                continue;
            }
            if ((fileinfo.attrib & _A_SUBDIR)) {
                X_Files_DirUpdateA(lsourceFile+fileinfo.name,ltargetFile+fileinfo.name,cover);
            }
            else {
                X_Files_FileCopyA(lsourceFile+fileinfo.name, ltargetFile + fileinfo.name, cover);
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

//目录_获取完整路径名称W
CXText X_Files_DirGetFullPathName(CXText fileName) {
    CXText ret;
    DWORD dwBufLen = GetFullPathNameW(fileName,0, NULL, NULL);
    if (dwBufLen>0) {
        wchar_t* pBuffer = new wchar_t[dwBufLen];
        GetFullPathNameW (fileName, dwBufLen, pBuffer,NULL);
        ret = pBuffer;
        delete[] pBuffer;
    }
    return ret;
}
//目录_获取完整路径名称W
CXTextA X_Files_DirGetFullPathNameA(CXTextA fileName) {
    CXTextA ret;
    DWORD dwBufLen = GetFullPathNameA(fileName, 0, NULL, NULL);
    if (dwBufLen > 0) {
        char* pBuffer = new char[dwBufLen];
        GetFullPathNameA(fileName, dwBufLen, pBuffer, NULL);
        ret = pBuffer;
        delete[] pBuffer;
    }
    return ret;
}

//目录_监控文件修改A
void X_Files_DirMonitoringChangesA(CXTextA changeDir, bool bWatchSubtree) {
    HANDLE hChangeHandle = FindFirstChangeNotificationA(changeDir, bWatchSubtree,
        FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE);
    if (hChangeHandle == INVALID_HANDLE_VALUE) { return; }
    DWORD dwResult = WaitForMultipleObjects(1, &hChangeHandle, false, INFINITE);
    FindCloseChangeNotification(hChangeHandle);
}
//目录_监控文件修改W
void X_Files_DirMonitoringChanges(CXText changeDir, bool bWatchSubtree) {
    HANDLE hChangeHandle = FindFirstChangeNotificationW(changeDir, bWatchSubtree, 
        FILE_NOTIFY_CHANGE_FILE_NAME| FILE_NOTIFY_CHANGE_SIZE|FILE_NOTIFY_CHANGE_LAST_WRITE);
    if (hChangeHandle == INVALID_HANDLE_VALUE) { return; }
    DWORD dwResult = WaitForMultipleObjects(1,&hChangeHandle,false, INFINITE);
    FindCloseChangeNotification(hChangeHandle);
}

//目录_检查系统属性W
bool X_Files_DirPathIsSystemFolder(CXText pathName) {
    return pathName==L""?
        false: PathIsSystemFolderW(pathName,NULL) > 0;
}
//目录_检查系统属性A
bool X_Files_DirPathIsSystemFolderA(CXTextA pathName) {
    return pathName == "" ?
        false : PathIsSystemFolderA(pathName, NULL) > 0;
}

//目录_检索文件的显示名称W
CXText X_Files_DirSHGetFileName(int csidl) {
    CXText r;
    LPITEMIDLIST pidl;
    HRESULT hr = SHGetFolderLocation(NULL, csidl,NULL,0,&pidl);
    if (hr==S_OK && pidl!=NULL) {
        SHFILEINFO info = { 0 };
        DWORD_PTR dwptr=SHGetFileInfoW((LPCWSTR)pidl,0, &info,sizeof(info), SHGFI_DISPLAYNAME|SHGFI_PIDL);
        if (dwptr!=NULL)
        {
            r= info.szDisplayName;
        }
        ILFree(pidl);
    }
    return r;
}
//目录_检索文件的显示名称A
CXTextA X_Files_DirSHGetFileNameA(int csidl) {
    CXTextA r;
    LPITEMIDLIST pidl;
    HRESULT hr = SHGetFolderLocation(NULL, csidl, NULL, 0, &pidl);
    if (hr == S_OK && pidl != NULL) {
        SHFILEINFOA info = { 0 };
        DWORD_PTR dwptr = SHGetFileInfoA((LPCSTR)pidl, 0, &info, sizeof(info), SHGFI_DISPLAYNAME | SHGFI_PIDL);
        if (dwptr != NULL)
        {
            r = info.szDisplayName;
        }
        ILFree(pidl);
    }
    return r;
}

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData) {
    if (uMsg == BFFM_INITIALIZED) { SendMessageW(hwnd, BFFM_SETSELECTIONW, 1, lpData); }
    return 1;
}
//目录_浏览W
CXText X_Files_DirBrowseForFolder(CXText title,bool showFiles, CXText initialDirectory,bool addressBar,bool newStyle,HWND phWnd) {
    BROWSEINFOW bi= { 0 };
    bi.hwndOwner = phWnd;
    bi.lpszTitle = title;
    UINT dwFlags = showFiles? BIF_BROWSEINCLUDEFILES:0;
    dwFlags = addressBar ? dwFlags|BIF_EDITBOX: dwFlags;
    dwFlags = newStyle ? dwFlags| BIF_NEWDIALOGSTYLE : dwFlags;
    bi.ulFlags = dwFlags;
    bi.lParam = (LPARAM)initialDirectory.get();
    bi.lpfn = BrowseCallbackProc;
    LPITEMIDLIST pidl = SHBrowseForFolderW(&bi);
    if (pidl!=NULL)
    {
        wchar_t* szPath=new wchar_t[MAX_PATH];
        szPath[0] = L'0';
        SHGetPathFromIDListW(pidl,szPath);
        CXText r = szPath;
        CoTaskMemFree(pidl);
        return r;
    }
    return L"";
}
//目录_浏览A
CXTextA X_Files_DirBrowseForFolderA(CXTextA title, bool showFiles, CXTextA initialDirectory, bool addressBar, bool newStyle, HWND phWnd) {
    BROWSEINFOA bi = { 0 };
    bi.hwndOwner = phWnd;
    bi.lpszTitle = title;
    UINT dwFlags = showFiles ? BIF_BROWSEINCLUDEFILES : 0;
    dwFlags = addressBar ? dwFlags | BIF_EDITBOX : dwFlags;
    dwFlags = newStyle ? dwFlags | BIF_NEWDIALOGSTYLE : dwFlags;
    bi.ulFlags = dwFlags;
    bi.lParam = (LPARAM)initialDirectory.get();
    bi.lpfn = BrowseCallbackProc;
    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);
    if (pidl != NULL)
    {
        char* szPath = new char[MAX_PATH];
        szPath[0] = '0';
        SHGetPathFromIDListA(pidl, szPath);
        CXTextA r = szPath;
        CoTaskMemFree(pidl);
        return r;
    }
    return "";
}

//目录_枚举子目录A
int X_Files_DirEnumDirListA(CXTextA parentPath,CXVector<CXTextA> &retList,bool addPath,bool enume,bool isSort) {
    if (parentPath=="") { return 0; }
    CXTextA lparentPath = parentPath;
    if (lparentPath[lparentPath.size() - 1] != '\\') {
        lparentPath += '\\';
    }
    intptr_t hFile;
    struct _finddata_t fileinfo;
    if ((hFile = _findfirst((lparentPath + "*.*").get(), &fileinfo)) != -1) {
        do
        {
            if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0) {
                continue;
            }
            if ((fileinfo.attrib & _A_SUBDIR)) {
                retList.add(addPath? lparentPath + fileinfo.name: fileinfo.name);
                if (enume)
                {
                    X_Files_DirEnumDirListA(lparentPath + fileinfo.name, retList, addPath, enume, isSort);
                }
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
    if (isSort) {
        X_String_SortA(retList);
    }
    return retList.size();
}
//目录_枚举子目录W
int X_Files_DirEnumDirList(CXText parentPath, CXVector<CXText>& retList, bool addPath,bool enume, bool isSort) {
    if (parentPath == L"") { return 0; }
    CXTextA lparentPath = W2A(parentPath);
    if (lparentPath[lparentPath.size() - 1] != '\\') {
        lparentPath += '\\';
    }
    intptr_t hFile;
    struct _finddata_t fileinfo;
    if ((hFile = _findfirst((lparentPath + "*.*").get(), &fileinfo)) != -1) {
        do
        {
            if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0) {
                continue;
            }
            if ((fileinfo.attrib & _A_SUBDIR)) {
                retList.add(addPath ? A2W(lparentPath + fileinfo.name) : A2W(fileinfo.name));
                if (enume) {
                    X_Files_DirEnumDirList(A2W(lparentPath + fileinfo.name), retList, addPath, enume, isSort);
                }
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
    if (isSort) {
        X_String_Sort(retList);
    }
    return retList.size();
}

//目录_是否符合规范W
bool X_File_DirIsItNormative(CXText dirName, bool banRootPath) {
    if (dirName == L"") { return false; }
    CXText ldirName = dirName;
    ldirName = X_String_Subreplace(ldirName, L"\\\\", L"\\");
    ldirName = X_String_Subreplace(ldirName, L"//", L"/");
    wint_t wDl = towupper(ldirName[0]);
    //判断盘符是否正确
    if (wDl < 65 || wDl>90) { return false; }
    bool ret = ldirName.find(L":\\") != std::wstring::npos;
    if (!ret) {
        ret = ldirName.find(L":/") != std::wstring::npos;
        if (!ret) { return false; }
    }
    if (banRootPath) {
        ldirName = X_String_Subreplace(ldirName, L"\\\\", L"\\");
        ldirName = X_String_Subreplace(ldirName, L"//", L"/");
        return ldirName.size() > 3;
    }
    return true;
}
//目录_是否符合规范A
bool X_File_DirIsItNormativeA(CXTextA dirName, bool banRootPath) {
    if (dirName == "") { return false; }
    CXTextA ldirName = dirName;
    ldirName = X_String_SubreplaceA(ldirName, "\\\\", "\\");
    ldirName = X_String_SubreplaceA(ldirName, "//", "/");
    int wDl = toupper(ldirName[0]);
    //判断盘符是否正确
    if (wDl < 65 || wDl>90) { return false; }
    bool ret = ldirName.find(":\\") != std::string::npos;
    if (!ret) {
        ret = ldirName.find(":/") != std::string::npos;
        if (!ret) { return false; }
    }
    if (banRootPath) {
        ldirName = X_String_SubreplaceA(ldirName, "\\\\", "\\");
        ldirName = X_String_SubreplaceA(ldirName, "//", "/");
        return ldirName.size() > 3;
    }
    return true;
}

//目录_强力清空W
void X_Files_DirRemovePro(CXText dirName) {
    if (dirName == L"") { return; }
    CXText lDirName= dirName;
    if (lDirName[lDirName.size() - 1] != L'\\') { lDirName += L'\\'; }
    if(!X_File_DirIsItNormative(lDirName,true)){
        xcl_log(L"目录_强力清空 - 传入的目录不合规范，这样会导致不可预料的情况甚至格盘！请重新提供符合规范的目录路径！注意：不可以直接使用磁盘根目录！");
        return;
    }
    if (!X_Files_DirTfSet(lDirName)) {
        xcl_log(L"该目录不存在，请检查路径后重试"); return;
    }
    X_Files_DirRemove(lDirName);
    X_Files_DirCreate(lDirName);
}
//目录_强力清空A
void X_Files_DirRemoveProA(CXTextA dirName) {
    if (dirName == "") { return; }
    CXTextA lDirName= dirName;
    if (lDirName[lDirName.size() - 1] != '\\') { lDirName += '\\'; }
    if (!X_File_DirIsItNormativeA(lDirName, true)) {
        xcl_log(L"目录_强力清空 - 传入的目录不合规范，这样会导致不可预料的情况甚至格盘！请重新提供符合规范的目录路径！注意：不可以直接使用磁盘根目录！");
        return;
    }
    if (!X_Files_DirTfSetA(lDirName)) {
        xcl_log(L"该目录不存在，请检查路径后重试"); return;
    }
    X_Files_DirRemoveA(lDirName);
    X_Files_DirCreateA(lDirName);
}

//目录_删除目录A
bool X_Files_DirRemoveA(CXTextA dirName) {
    return X_Files_DirRemove(A2W(dirName));
}
//目录_删除目录W
bool X_Files_DirRemove(CXText dirName) {
    if (dirName==L""){return false;}
    CXText ldirName = dirName;
    if (dirName[dirName.size()-1]!=L'\\') { ldirName+=L'\\'; }
    HANDLE hFind;
    WIN32_FIND_DATAW FindData = {0};
    hFind = FindFirstFileW(ldirName+L"*.*",&FindData);
    if (hFind == INVALID_HANDLE_VALUE) { return false; }
    do {
        if (lstrcmpW(FindData.cFileName, L".") == 0 || lstrcmpW(FindData.cFileName, L"..") == 0) {
            continue;
        }
        if ((FindData.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY)== FILE_ATTRIBUTE_DIRECTORY) {
            //DIR
            X_Files_DirRemove(ldirName+ FindData.cFileName);
        }
        if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)== FILE_ATTRIBUTE_ARCHIVE) {
            //file
            DWORD dwFileAttributes = FindData.dwFileAttributes | (~FILE_ATTRIBUTE_READONLY);
            SetFileAttributesW(ldirName+ FindData.cFileName, dwFileAttributes);
        }
        DeleteFileW(ldirName + FindData.cFileName);
    } while (FindNextFileW(hFind, &FindData));
    FindClose(hFind);
    return RemoveDirectoryW(ldirName) > 0;
}

//目录_清空目录W
void X_Files_DirEmpty(CXText dirName, CXText fileType) {
    if (dirName == L"") { return; }
    CXText lDir = dirName;
    if (lDir[lDir.size()-1]!=L'\\') { lDir += L"\\"; }
    CXText lFType = fileType==L""?L"*.*": fileType;
    if(!X_File_DirIsItNormative(lDir,true)){
        xcl_log(L"目录_清空 - 传入的目录不合规范，这样会导致不可预料的情况甚至格盘！请重新提供符合规范的目录路径！注意：不可以直接使用磁盘根目录！");
        return;
    }
    if (!X_Files_DirTfSet(lDir)) {
        xcl_log(L"该目录不存在，请检查路径后重试");
        return;
    }
    CXVector<CXText> fileList;
    X_Files_FileEnums(lDir, fileList, fileType, true);
    for (int i = 0; i < fileList.size();i++) {
        X_Files_FileDelToRecycle(fileList[i],1);
    }
}
//目录_清空目录A
void X_Files_DirEmptyA(CXTextA dirName, CXTextA fileType) {
    if (dirName == "") { return; }
    CXTextA lDir = dirName;
    if (lDir[lDir.size() - 1] != '\\') { lDir += "\\"; }
    CXTextA lFType = fileType == "" ? "*.*" : fileType;
    if (!X_File_DirIsItNormativeA(lDir, true)) {
        xcl_log(L"目录_清空 - 传入的目录不合规范，这样会导致不可预料的情况甚至格盘！请重新提供符合规范的目录路径！注意：不可以直接使用磁盘根目录！");
        return;
    }
    if (!X_Files_DirTfSetA(lDir)) {
        xcl_log(L"该目录不存在，请检查路径后重试");
        return;
    }
    CXVector<CXTextA> fileList;
    X_Files_FileEnumsA(lDir, fileList, fileType, true);
    for (int i = 0; i < fileList.size(); i++) {
        X_Files_FileDelToRecycleA(fileList[i], 1);
    }
}

//目录_取特定目录W
CXText X_Files_GetGivenDir(int dirType,int csidl) {
    CXText ret;
    if (csidl!=-1) {
        wchar_t* szPath=new wchar_t[MAX_PATH];
        memset(szPath,0, MAX_PATH);
        BOOL err = SHGetSpecialFolderPathW(NULL, szPath, csidl, FALSE);
        if (err <1) { delete[] szPath; return L""; }
        ret = szPath; delete[] szPath;
        return ret;
    }
    int index = (dirType <= 0 || dirType > 13) ? 3 : dirType;
    int llist[] = { CSIDL_PERSONAL, CSIDL_FAVORITES, CSIDL_DESKTOPDIRECTORY,
    CSIDL_FONTS, CSIDL_STARTMENU, CSIDL_PROGRAMS, CSIDL_STARTUP, CSIDL_APPDATA,
    CSIDL_WINDOWS, CSIDL_SYSTEM };
    int iCsidl = llist[index - 1];
    if (index <= 10) {
        return X_Files_GetGivenDir(0, iCsidl);
    }
    if (index==11) {
        wchar_t* szPath = new wchar_t[MAX_PATH];
        memset(szPath,0, MAX_PATH);
        GetTempPathW(MAX_PATH, szPath);
        ret = szPath;
        delete[] szPath;
        return ret;
    }
    if (index==12) {
        return X_Files_GetGivenDir(CSIDL_INTERNET_CACHE);
    }
    if (index == 13) {
        return X_Files_GetGivenDir(CSIDL_COMMON_APPDATA);
    }
    return L"";
}
//目录_取特定目录A
CXTextA X_Files_GetGivenDirA(int dirType, int csidl) {
    CXTextA ret;
    if (csidl != -1) {
        char* szPath = new char[MAX_PATH];
        memset(szPath, 0, MAX_PATH);
        BOOL err = SHGetSpecialFolderPathA(NULL, szPath, csidl, FALSE);
        if (err < 1) { delete[] szPath; return ""; }
        ret = szPath; delete[] szPath;
        return ret;
    }
    int index = (dirType <= 0 || dirType > 13) ? 3 : dirType;
    int llist[] = { CSIDL_PERSONAL, CSIDL_FAVORITES, CSIDL_DESKTOPDIRECTORY,
    CSIDL_FONTS, CSIDL_STARTMENU, CSIDL_PROGRAMS, CSIDL_STARTUP, CSIDL_APPDATA,
    CSIDL_WINDOWS, CSIDL_SYSTEM };
    int iCsidl = llist[index - 1];
    if (index <= 10) {
        return X_Files_GetGivenDirA(0, iCsidl);
    }
    if (index == 11) {
        char* szPath = new char[MAX_PATH];
        memset(szPath, 0, MAX_PATH);
        GetTempPathA(MAX_PATH, szPath);
        ret = szPath;
        delete[] szPath;
        return ret;
    }
    if (index == 12) {
        return X_Files_GetGivenDirA(CSIDL_INTERNET_CACHE);
    }
    if (index == 13) {
        return X_Files_GetGivenDirA(CSIDL_COMMON_APPDATA);
    }
    return "";
}

//目录_取system32目录W
CXText X_Files_GetSystem32Path() {
    return X_Files_GetGivenDir(0, CSIDL_SYSTEM);
}
//目录_取system32目录A
CXTextA X_Files_GetSystem32PathA() {
    return X_Files_GetGivenDirA(0, CSIDL_SYSTEM);
}

//目录_取Windows目录W
CXText X_Files_GetWindowsPath() {
    return X_Files_GetGivenDir(0, CSIDL_WINDOWS);
}
//目录_取Windows目录A
CXTextA X_Files_GetWindowsPathA() {
    return X_Files_GetGivenDirA(0, CSIDL_WINDOWS);
}

//目录_取x86系统目录W
CXText X_Files_GetSystemX86Path(){
    return X_Files_GetGivenDir(0, CSIDL_SYSTEMX86);
}
//目录_取x86系统目录A
CXTextA X_Files_GetSystemX86PathA() {
    return X_Files_GetGivenDirA(0, CSIDL_SYSTEMX86);
}

//目录_取创建时间W
CDateTimeTM X_Files_GetDirCreateTime(CXText dirName) {
    CDateTimeTM retime;
    struct _stat filetime;
    if (_wstat(dirName, &filetime)!=0) {
        return retime;
    }
    time_t t = filetime.st_mtime + 28800;//相加是确保时区是正确，否则与标准时间差八小时
    struct tm p ;
    gmtime_s(&p ,&t);
    retime.m_tm = p;
    return retime;
}
//目录_取创建时间A
CDateTimeTM X_Files_GetDirCreateTimeA(CXTextA dirName) {
    CDateTimeTM retime;
    struct _stat filetime;
    if (_stat(dirName, &filetime) != 0) {
        return retime;
    }
    time_t t = filetime.st_mtime + 28800;//相加是确保时区是正确，否则与标准时间差八小时
    struct tm p;
    gmtime_s(&p, &t);
    retime.m_tm = p;
    return retime;
}

//目录_取大小W
INT64 X_Files_GetDirSize(CXText dirName) {
    if (dirName == L"") { return 0; }
    CXText lDir = dirName;
    INT64 addSize=0;
    if (lDir[lDir.size() - 1] != L'\\') { lDir += L'\\'; }
    WIN32_FIND_DATAW FindData;
    CXText l_name = lDir +L"*.*";
    HANDLE hFind = FindFirstFileW(l_name, &FindData);
    do {
        if (lstrcmpW(FindData.cFileName, L".") == 0 || lstrcmpW(FindData.cFileName, L"..") == 0) { continue; }
        if ((FindData.dwFileAttributes& FILE_ATTRIBUTE_ARCHIVE)== FILE_ATTRIBUTE_ARCHIVE) {
            //file
            INT64 lf = FindData.nFileSizeHigh;
            lf <<= 32;
            lf += FindData.nFileSizeLow;
            addSize += lf;
            
        }
        if ((FindData.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
            //DIR
            addSize += X_Files_GetDirSize(lDir+ FindData.cFileName);
        }
    } while (FindNextFileW(hFind, &FindData));
    FindClose(hFind);
    return addSize;
}
//目录_取大小A
INT64 X_Files_GetDirSizeA(CXTextA dirName) {
    if (dirName == "") { return 0; }
    CXTextA lDir = dirName;
    INT64 addSize = 0;
    if (lDir[lDir.size() - 1] != '\\') { lDir += '\\'; }
    WIN32_FIND_DATAA FindData;
    CXTextA l_name = lDir + "*.*";
    HANDLE hFind = FindFirstFileA(l_name, &FindData);
    do {
        if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0) { continue; }
        if ((FindData.dwFileAttributes | FILE_ATTRIBUTE_ARCHIVE)== FILE_ATTRIBUTE_ARCHIVE) {
            //file
            INT64 lf = FindData.nFileSizeHigh;
            lf <<= 32;
            lf += FindData.nFileSizeLow;
            addSize += lf;

        }
        if ((FindData.dwFileAttributes| FILE_ATTRIBUTE_DIRECTORY)== FILE_ATTRIBUTE_DIRECTORY) {
            //DIR
            addSize += X_Files_GetDirSizeA(lDir + FindData.cFileName);
        }
    } while (FindNextFileA(hFind, &FindData));
    FindClose(hFind);
    return addSize;
}

//目录_取当前目录W
CXText X_Files_GetCurrentDir() {
    DWORD dwSize=GetCurrentDirectoryW(0,0);
    if (dwSize <= 0) { return L""; }
    wchar_t* szDiry = new wchar_t[dwSize];
    GetCurrentDirectoryW(dwSize, szDiry);
    CXText r = szDiry;
    delete[] szDiry;
    return r;
}
//目录_取当前目录A
CXTextA X_Files_GetCurrentDirA() {
    DWORD dwSize = GetCurrentDirectoryA(0, 0);
    if (dwSize <= 0) { return ""; }
    char* szDiry = new char[dwSize];
    GetCurrentDirectoryA(dwSize, szDiry);
    CXTextA r = szDiry;
    delete[] szDiry;
    return r;
}

//目录_取父路径W
CXText X_Files_GetFatherDir(CXText dirPath) {
    if (dirPath == L"") { return L"";}
    CXText lFile = dirPath;
    if (lFile[lFile.size() - 1] == L'\\') { lFile = lFile.substr(0, lFile.size()-1); }
    std::wstring lstr = lFile.get();
    return lFile.substr(0, lstr.rfind(L'\\')+1);
}
//目录_取父路径A
CXTextA X_Files_GetFatherDirA(CXTextA dirPath) {
    if (dirPath == "") { return ""; }
    CXTextA lFile = dirPath;
    if (lFile[lFile.size() - 1] == '\\') { lFile = lFile.substr(0, lFile.size() - 1); }
    std::string lstr = lFile.get();
    return lFile.substr(0, lstr.rfind('\\') + 1);
}

//目录_取临时目录W
CXText X_Files_GetSystemTempDir() {
    return X_Files_GetGivenDir(11);
}
//目录_取临时目录A
CXTextA X_Files_GetSystemTempDirA() {
    return X_Files_GetGivenDirA(11);
}

//目录_取尾部目录名或文件名W
CXText X_Files_GetPathTailNameOrFileName(CXText pathName){
    wchar_t* buffer = new wchar_t[MAX_PATH];
    memset(buffer,0, MAX_PATH);
    auto success=GetFileTitleW(pathName, buffer, MAX_PATH);
    CXText lpath = buffer;delete[] buffer;
    CXText extp = X_Files_GetFileExtension(pathName);
    if (extp!=L"" && lpath.find(extp) == std::wstring::npos) {
        lpath += extp;
    }
    return success==0? lpath:L"";
}
//目录_取尾部目录名或文件名A
CXTextA X_Files_GetPathTailNameOrFileNameA(CXTextA pathName) {
    char* buffer = new char[MAX_PATH];
    memset(buffer, 0, MAX_PATH);
    auto success = GetFileTitleA(pathName, buffer, MAX_PATH);
    CXTextA lpath = buffer; delete[] buffer;
    CXTextA extp = X_Files_GetFileExtensionA(pathName);
    if (extp != "" && lpath.find(extp) == std::string::npos) {
        lpath += extp;
    }
    return success == 0 ? lpath : "";
}

//目录_取文件数W
int X_Files_GetDirFileNum(CXText pathName) {
    CXComObject FSO;
    FSO.Create(L"Scripting.FileSystemObject");
    IDispatch* vcGetFolder = FSO.Method(L"GetFolder", pathName);
    CXComObject GetFolder(vcGetFolder);
    IDispatch* vcFiles = GetFolder.Get(L"Files");
    CXComObject files(vcFiles);
    return files.Get(L"count");
}
//目录_取文件数A
int X_Files_GetDirFileNumA(CXTextA pathName) {
    return X_Files_GetDirFileNum(A2W(pathName));
}

//目录_取消系统属性W
bool X_Files_PathUnmakeSystemFolder(CXText dirName){
    return dirName==L"" ? false:
        PathUnmakeSystemFolderW(dirName) > 0;
}
//目录_取消系统属性W
bool X_Files_PathUnmakeSystemFolderA(CXTextA dirName){
    return dirName == "" ? false :
        PathUnmakeSystemFolderA(dirName) > 0;
}

//目录_设置系统属性W
bool X_Files_PathMakeSystemFolder(CXText dirName) {
    return dirName == L"" ? false :
        PathMakeSystemFolderW(dirName) > 0;
}
//目录_设置系统属性A
bool X_Files_PathMakeSystemFolderA(CXTextA dirName) {
    return dirName == "" ? false :
        PathMakeSystemFolderA(dirName) > 0;
}

//目录_取桌面目录W
CXText X_Files_GetDesktopDir() {
    return X_Files_GetGivenDir(0, CSIDL_DESKTOPDIRECTORY);
}
//目录_取桌面目录A
CXTextA X_Files_GetDesktopDirA() {
    return X_Files_GetGivenDirA(0, CSIDL_DESKTOPDIRECTORY);
}

//目录_取子目录数W
int X_Files_GetSonDirNum(CXText pathName) {
    CXComObject FSO;
    FSO.Create(L"Scripting.FileSystemObject");
    IDispatch* vcGetFolder = FSO.Method(L"GetFolder", pathName);
    CXComObject GetFolder(vcGetFolder);
    IDispatch* vcFiles = GetFolder.Get(L"SubFolders");
    CXComObject files(vcFiles);
    return files.Get(L"count");
}
//目录_取子目录数A
int X_Files_GetSonDirNumA(CXTextA pathName) {
    return X_Files_GetSonDirNum(A2W(pathName));
}

//目录_是否为空W
bool X_Files_IsItEmpty(CXText dirName) {
    return PathIsDirectoryEmptyW(dirName) > 0;
}
//目录_是否为空A
bool X_Files_IsItEmptyA(CXTextA dirName) {
    return PathIsDirectoryEmptyA(dirName) > 0;
}

//目录_是否有子目录W
bool X_Files_WhetherSonDir(CXText dirName){
    if (dirName == L"") { return 0; }
    CXText lDir = dirName;
    if (lDir[lDir.size() - 1] != L'\\') { lDir += L'\\'; }
    WIN32_FIND_DATAW FindData;
    CXText l_name = lDir + L"*.*";
    HANDLE hFind = FindFirstFileW(l_name, &FindData);
    bool rets=false;
    do {
        if (lstrcmpW(FindData.cFileName, L".") == 0 || lstrcmpW(FindData.cFileName, L"..") == 0) {
            continue;
        }
        if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)== FILE_ATTRIBUTE_DIRECTORY) {
            //DIR
            rets = true;
            break;
        }

    } while (FindNextFileW(hFind, &FindData));
    FindClose(hFind);
    return rets;
}
//目录_是否有子目录A
bool X_Files_WhetherSonDirA(CXTextA dirName) {
    if (dirName == "") { return 0; }
    CXTextA lDir = dirName;
    if (lDir[lDir.size() - 1] != '\\') { lDir += '\\'; }
    WIN32_FIND_DATAA FindData;
    CXTextA l_name = lDir + "*.*";
    HANDLE hFind = FindFirstFileA(l_name, &FindData);
    bool rets = false;
    do {
        if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0) {
            continue;
        }
        if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
            //DIR
            rets = true;
            break;
        }

    } while (FindNextFileA(hFind, &FindData));
    FindClose(hFind);
    return rets;
}

//目录_同步更新W
void X_Files_DirSyncUpdate(CXText sourcePath, CXText targetPath) {
    if (sourcePath == L"" || targetPath == L"") { return; }
    CXText lOldPath = sourcePath;
    if (lOldPath[lOldPath.size() - 1] != L'\\') { lOldPath += L'\\'; }
    CXText lNewPath = targetPath;
    if (lNewPath[lNewPath.size() - 1] != L'\\') { lNewPath += L'\\'; }
    X_Files_DirCreate(lNewPath);
    WIN32_FIND_DATAW FindData;
    CXText l_name = lOldPath + L"*.*";
    HANDLE hFind = FindFirstFileW(l_name, &FindData);
	xcl_doMessage();
    do {
        if (lstrcmpW(FindData.cFileName, L".") == 0 || lstrcmpW(FindData.cFileName, L"..") == 0) {
            continue;
        }
        if ((FindData.dwFileAttributes&FILE_ATTRIBUTE_ARCHIVE)== FILE_ATTRIBUTE_ARCHIVE) {
            //file
            l_name = lOldPath+ FindData.cFileName;
            if (!X_Files_FileIfIsSet(l_name)) {
                //文件不存在
                CopyFileW(l_name, lNewPath + FindData.cFileName, FALSE);
                continue;
            }
            CXBytes fileByteOld;
            X_Files_ReadFile(l_name, fileByteOld);
            CXBytes fileByteNew;
            X_Files_ReadFile(lNewPath + FindData.cFileName, fileByteNew);
            if (lstrcmpW(
                Check_GetMD5_Bytes(fileByteOld), 
                Check_GetMD5_Bytes(fileByteNew)
            )!=0) {
                CopyFileW(l_name, lNewPath + FindData.cFileName, FALSE);
            }
        }
        if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)== FILE_ATTRIBUTE_DIRECTORY) {
            //DIR
            X_Files_DirSyncUpdate(lOldPath+ FindData.cFileName, lNewPath + FindData.cFileName);
        }
    } while (FindNextFileW(hFind, &FindData));
    FindClose(hFind);
}
//目录_同步更新A
void X_Files_DirSyncUpdate(CXTextA sourcePath, CXTextA targetPath) {
    if (sourcePath == "" || targetPath == "") { return; }
    CXTextA lOldPath = sourcePath;
    if (lOldPath[lOldPath.size() - 1] != '\\') { lOldPath += '\\'; }
    CXTextA lNewPath = targetPath;
    if (lNewPath[lNewPath.size() - 1] != '\\') { lNewPath += '\\'; }
    X_Files_DirCreateA(lNewPath);
    WIN32_FIND_DATAA FindData;
    CXTextA l_name = lOldPath + "*.*";
    HANDLE hFind = FindFirstFileA(l_name, &FindData);
    xcl_doMessage();
    do {
        if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0) {
            continue;
        }
        if ((FindData.dwFileAttributes& FILE_ATTRIBUTE_ARCHIVE) == FILE_ATTRIBUTE_ARCHIVE) {
            //file
            l_name = lOldPath + FindData.cFileName;
            if (!X_Files_FileIfIsSetA(l_name)) {
                //文件不存在
                CopyFileA(l_name, lNewPath + FindData.cFileName, FALSE);
                continue;
            }
            CXBytes fileByteOld;
            X_Files_ReadFileA(l_name, fileByteOld);
            CXBytes fileByteNew;
            X_Files_ReadFileA(lNewPath + FindData.cFileName, fileByteNew);
            if (strcmp(
                Check_GetMD5_BytesA(fileByteOld),
                Check_GetMD5_BytesA(fileByteNew)
            ) != 0) {
                CopyFileA(l_name, lNewPath + FindData.cFileName, FALSE);
            }
        }
        if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)== FILE_ATTRIBUTE_DIRECTORY) {
            //DIR
            X_Files_DirSyncUpdate(lOldPath + FindData.cFileName, lNewPath + FindData.cFileName);
        }
    } while (FindNextFileA(hFind, &FindData));
    FindClose(hFind);
}

//----------------------------------------------------

//文件取版本号A
CXTextA X_File_GetFileVersionA(CXTextA szModuleName) {
    CXTextA RetStr = "";
    UINT sz = GetFileVersionInfoSizeA(szModuleName, 0);
    if (sz <= 0)
    {
        return RetStr;
    }
    char* pBuf = new char[sz];
    VS_FIXEDFILEINFO* pVsInfo;
    if (GetFileVersionInfoA(szModuleName, 0, sz, pBuf)) {
        if (VerQueryValueA(pBuf, (LPCSTR)"\\", (void**)&pVsInfo, &sz)) {
            sprintf_s(pBuf, sz, "%d.%d.%d.%d",
                HIWORD(pVsInfo->dwFileVersionMS),
                LOWORD(pVsInfo->dwFileVersionMS),
                HIWORD(pVsInfo->dwFileVersionLS),
                LOWORD(pVsInfo->dwFileVersionLS));
            RetStr = pBuf;
        }
    }
    delete[] pBuf;
    return RetStr;
}
//文件取版本号W
CXText X_File_GetFileVersion(CXText szModuleName) {
    CXText RetStr;
    UINT sz = GetFileVersionInfoSizeW(szModuleName, 0);
    if (sz <= 0)
    {
        return L"";
    }
    wchar_t* pBuf = new wchar_t[sz];
    VS_FIXEDFILEINFO* pVsInfo;
    if (GetFileVersionInfoW(szModuleName, 0, sz, pBuf)) {
        if (VerQueryValueW(pBuf, (LPCWSTR)L"\\", (void**)&pVsInfo, &sz)) {
            //sprintf(pBuf, "%d.%d.%d.%d");
            wsprintfW(pBuf, L"%d.%d.%d.%d",
                HIWORD(pVsInfo->dwFileVersionMS),
                LOWORD(pVsInfo->dwFileVersionMS),
                HIWORD(pVsInfo->dwFileVersionLS),
                LOWORD(pVsInfo->dwFileVersionLS));
            RetStr = pBuf;
        }
    }
    delete[] pBuf;
    return RetStr;
}

//文件_改名A
bool X_Files_DirRenameA(CXTextA oldDir, CXTextA newDir) {
    return rename(oldDir, newDir) == 0;
}
//文件_改名W
bool X_Files_DirRename(CXText oldDir, CXText newDir) {
    return rename(W2A(oldDir), W2A(newDir)) == 0;
}

//文件_定位A
bool X_Files_FileLocationA(CXTextA fileName, bool editMode) {
    if (!PathFileExistsA(fileName)) {
        return false;
    }
    PIDLIST_ABSOLUTE pidl = ILCreateFromPathA(fileName);
    if (pidl == NULL) {
        return false;
    }
    HRESULT hr = SHOpenFolderAndSelectItems(pidl, NULL, NULL, editMode ? OFASI_EDIT : NULL);
    ILFree(pidl);
    return hr == S_OK;
}
//文件_定位W
bool X_Files_FileLocation(CXText fileName,bool editMode) {
    if (!PathFileExistsW(fileName)) {
        return false;
    }
    PIDLIST_ABSOLUTE pidl = ILCreateFromPathW(fileName);
    if (pidl==NULL) {
        return false;
    }
    HRESULT hr = SHOpenFolderAndSelectItems(pidl,NULL,NULL, editMode? OFASI_EDIT:NULL);
    ILFree(pidl);
    return hr==S_OK;
}

//文件_改名A
bool X_Files_FileRenameA(CXTextA oldFile, CXTextA newFile) {
    return rename(oldFile, newFile) == 0;
}
//文件_改名W
bool X_Files_FileRename(CXText oldFile, CXText newFile) {
    return rename(W2A(oldFile), W2A(newFile))==0;
}

//文件_复制A
bool X_Files_FileCopyA(CXTextA oldFile, CXTextA newFile, bool cover) {
    return CopyFileA(oldFile, newFile, cover) > 0;
}
//文件_复制W
bool X_Files_FileCopy(CXText oldFile, CXText newFile, bool cover) {
    return CopyFileW(oldFile, newFile,cover) > 0;
}

//文件_文件操作W
bool X_Files_FileOperation(int CommendType, CXText fileName, CXText targetDir, int fileOption) {
    if (CommendType < 1 || CommendType>4) { xcl_log(L"请严格传递命令类型！"); return false; }
    SHFILEOPSTRUCT FileOp;
    FileOp.wFunc = CommendType;
    std::wstring wpf = fileName.get();
    wpf += L'\0';
    FileOp.pFrom = wpf.c_str();
    std::wstring wto= targetDir.get();
    if (FileOp.wFunc != FO_DELETE) {
        if (targetDir == L"") { xcl_log(L"目标文件或目录名称不能传递空值！"); return false; }
        wto += L'\0';
        FileOp.pTo = wto.c_str();
    }
    FileOp.fFlags = FOF_ALLOWUNDO;
    if ((CommendType| 1)!=0) {
        FileOp.fFlags |= FOF_NOCONFIRMATION;
    }
    if ((CommendType | 2) != 0) {
        FileOp.fFlags |= FOF_NOERRORUI;
    }
    if ((CommendType | 4) != 0) {
        FileOp.fFlags |= FOF_SILENT;
    }
    int iRet = SHFileOperationW(&FileOp);
    if (iRet!=0) {
        xcl_log("LastError:", GetLastError());
    }
    if (FileOp.hNameMappings != 0) {SHFreeNameMappings(FileOp.hNameMappings);}
    return iRet == NULL && FileOp.fAnyOperationsAborted==NULL;
    
}
//文件_文件操作A
bool X_Files_FileOperationA(int CommendType, CXTextA fileName, CXTextA targetDir, int fileOption) {
    if (CommendType < 1 || CommendType>4) { xcl_log(L"请严格传递命令类型！"); return false; }
    SHFILEOPSTRUCTA FileOp;
    FileOp.wFunc = CommendType;
    std::string sph = fileName.get();
    sph += '\0';
    FileOp.pFrom = sph.c_str();
    std::string spto = targetDir.get();
    if (FileOp.wFunc != FO_DELETE) {
        if (targetDir == "") { xcl_log(L"目标文件或目录名称不能传递空值！"); }
        spto += '\0';
        FileOp.pTo = spto.c_str();
    }
    FileOp.fFlags = FOF_ALLOWUNDO;
    if ((CommendType | 1) != 0) {
        FileOp.fFlags |= FOF_NOCONFIRMATION;
    }
    if ((CommendType | 2) != 0) {
        FileOp.fFlags |= FOF_NOERRORUI;
    }
    if ((CommendType | 4) != 0) {
        FileOp.fFlags |= FOF_SILENT;
    }
    int iRet = SHFileOperationA(&FileOp);
    if (iRet != 0) {
        xcl_log("LastError:", GetLastError());
    }
    if (FileOp.hNameMappings != 0) { SHFreeNameMappings(FileOp.hNameMappings); }
    return iRet == NULL && FileOp.fAnyOperationsAborted == NULL;
}

//文件_删除到回收站W
bool X_Files_FileDelToRecycle(CXText fileName,int delType) {
    return X_Files_FileOperation(3, fileName,L"", delType);
}
//文件_删除到回收站A
bool X_Files_FileDelToRecycleA(CXTextA fileName, int delType) {
    return X_Files_FileOperationA(3, fileName, "", delType);
}

//文件_枚举W
int X_Files_FileEnums(CXText dirName,CXVector<CXText> &rFileList, CXText fileName,bool addPath,bool sort,bool enumSon){
    if (!enumSon) { rFileList.clear(); }
    if (dirName == L"") { return 0; }
    CXText lDir = dirName;
    if (lDir[lDir.size() - 1] != L'\\') { lDir += L'\\'; }
    CXVector<CXText> lpfx = X_String_SplitWithStl(fileName,L"|");
    int lpfxNum = lpfx.size();
    for (int i = 0; i < lpfxNum; i++) {
        WIN32_FIND_DATAW FindData;
        CXText l_name = lDir + lpfx[i];
        HANDLE hFind = FindFirstFileW(l_name, &FindData);
        do {
            if (lstrcmpW(FindData.cFileName, L".") == 0 || lstrcmpW(FindData.cFileName, L"..") == 0) {
                continue;
            }
            if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)== FILE_ATTRIBUTE_ARCHIVE) {
                //file
                l_name = FindData.cFileName;
                if (addPath) {  l_name= lDir+ l_name; }
                rFileList.add(l_name);
            }
        } while (FindNextFileW(hFind, &FindData));
        FindClose(hFind);
    }
    if (enumSon) {
        WIN32_FIND_DATAW FindData;
        CXText l_name = lDir + L"*.*";
        HANDLE hFind = FindFirstFileW(l_name, &FindData);
        do {
            if (lstrcmpW(FindData.cFileName, L".") == 0 || lstrcmpW(FindData.cFileName, L"..") == 0) {
                continue;
            }
            if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
                l_name = lDir + FindData.cFileName;
                X_Files_FileEnums(l_name, rFileList, fileName, addPath, sort, enumSon);
            }
        } while (FindNextFileW(hFind, &FindData));
        FindClose(hFind);
    }
    if (sort) {
        X_String_Sort(rFileList);
    }
    return rFileList.size();
}
//文件_枚举A
int X_Files_FileEnumsA(CXTextA dirName, CXVector<CXTextA>& rFileList, CXTextA fileName, bool addPath, bool sort, bool enumSon) {
    if (!enumSon) { rFileList.clear(); }
    if (dirName == "") { return 0; }
    CXTextA lDir = dirName;
    if (lDir[lDir.size() - 1] != '\\') { lDir += '\\'; }
    CXVector<CXTextA> lpfx = X_String_SplitWithStlA(fileName, "|");
    int lpfxNum = lpfx.size();
    for (int i = 0; i < lpfxNum; i++) {
        WIN32_FIND_DATAA FindData;
        CXTextA l_name = lDir + lpfx[i];
        HANDLE hFind = FindFirstFileA(l_name, &FindData);
        do {
            if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0) {
                continue;
            }
            if (FindData.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE) {
                //file
                l_name = FindData.cFileName;
                if (addPath) { l_name = lDir + l_name; }
                rFileList.add(l_name);
            }
        } while (FindNextFileA(hFind, &FindData));
        FindClose(hFind);
    }
    if (enumSon) {
        WIN32_FIND_DATAA FindData;
        CXTextA l_name = lDir + "*.*";
        HANDLE hFind = FindFirstFileA(l_name, &FindData);
        do {
            if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0) {
                continue;
            }
            if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
                l_name = lDir + FindData.cFileName;
                X_Files_FileEnumsA(l_name, rFileList, fileName, addPath, sort, enumSon);
            }
        } while (FindNextFileA(hFind, &FindData));
        FindClose(hFind);
    }
    if (sort) {
        X_String_SortA(rFileList);
    }
    return rFileList.size();
}

//文件_取扩展名W
CXText X_Files_GetFileExtension(CXText fileName) {
    return PathFindExtensionW(fileName);
}
//文件_取扩展名A
CXTextA X_Files_GetFileExtensionA(CXTextA fileName) {
    return PathFindExtensionA(fileName);
}

//文件_是否存在W
bool X_Files_FileIfIsSet(CXText fileName) {
    WIN32_FIND_DATAW FindData;
    HANDLE hFind = FindFirstFileW(fileName, &FindData);
    if (hFind==INVALID_HANDLE_VALUE) {
        return false;
    }
    FindClose(hFind);
    return ((FindData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)== FILE_ATTRIBUTE_ARCHIVE)
        || ((FindData.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY);
}
//文件_是否存在A
bool X_Files_FileIfIsSetA(CXTextA fileName) {
    WIN32_FIND_DATAA FindData;
    HANDLE hFind = FindFirstFileA(fileName, &FindData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return false;
    }
    FindClose(hFind);
    return FindData.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE || FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY;
}

//文件_读入文件W
int X_Files_ReadFile(CXText fileName, CXBytes &fileByte) {
    fileByte.clear();
    FILE* fp;
    errno_t err = _wfopen_s(&fp,fileName, L"rb");
    if (err!=NULL) {
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size <= 0) {
        fclose(fp);
        return 0;
    }
    fseek(fp, 0, SEEK_SET);
    unsigned char* buffer = new unsigned char[size];
    fread_s(buffer, size, size,1 ,fp);
    fileByte.add(buffer,size);
    delete buffer;
    fclose(fp);
    return fileByte.size();
}
//文件_读入文件A
int X_Files_ReadFileA(CXTextA fileName, CXBytes& fileByte) {
    fileByte.clear();
    FILE* fp;
    errno_t err = fopen_s(&fp, fileName, "rb");
    if (err != NULL) {
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size <= 0) {
        fclose(fp);
        return 0;
    }
    fseek(fp, 0, SEEK_SET);
    unsigned char* buffer = new unsigned char[size];
    fread_s(buffer, size, size, 1, fp);
    fileByte.add(buffer, size);
    delete buffer;
    fclose(fp);
    return fileByte.size();
}

//文件_是否为目录W
bool  X_Files_FileIsDir(CXText fileName){
    DWORD dwFileAttributes = GetFileAttributesW(fileName);
    return dwFileAttributes==INVALID_FILE_ATTRIBUTES?false:
        (dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY);
}
//文件_是否为目录A
bool  X_Files_FileIsDirA(CXTextA fileName) {
    DWORD dwFileAttributes = GetFileAttributesA(fileName);
    return dwFileAttributes == INVALID_FILE_ATTRIBUTES ? false :
        (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY);
}

//文件_遍历PE导出表W
int X_Files_ErgodicExportTables(CXText fileName, CXVector<CXText>&rExportFuncList) {
    rExportFuncList.clear();
    HANDLE hFile = CreateFileW(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) { return 0; }
    HANDLE hMapping = CreateFileMappingW(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapping == NULL) { CloseHandle(hFile); return 0; }
    PIMAGE_DOS_HEADER ImageBase = (PIMAGE_DOS_HEADER)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    if (ImageBase == NULL) { CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    short int wMagic = ImageBase->e_magic;
    if (wMagic != IMAGE_DOS_SIGNATURE) { UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    LONG lfanew = ImageBase->e_lfanew;
    IMAGE_NT_HEADERS* pNtAddr = (IMAGE_NT_HEADERS*)((vint)ImageBase + lfanew);
    DWORD dwSignature = pNtAddr->Signature;
    if (dwSignature!=IMAGE_NT_SIGNATURE){ UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    wMagic = pNtAddr->OptionalHeader.Magic;
    int Offset = 0;
    switch (wMagic) {
    case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
        Offset= 120; //X86
        break;
    case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
        Offset = 136; //X64
        break;
    default:
        xcl_log("该文件不是一个可执行映像");
        break;
    }
    if (Offset==0){ UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    //  ImageRvaToVa(pNtAddr, ImageBase, ((XCLPTR)pNtAddr+ Offset), NULL);
    //XCLPTR ImportData = (XCLPTR)pNtAddr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    IMAGE_EXPORT_DIRECTORY* ImportData = (IMAGE_EXPORT_DIRECTORY*)ImageRvaToVa(pNtAddr, ImageBase, *(DWORD*)((vint)pNtAddr + Offset), NULL);
    int dwNumberOfNames=0;
    if (ImportData != NULL) {
        dwNumberOfNames = ImportData->NumberOfNames;
    }
    if (dwNumberOfNames>0) {
        //地址表:AddressOfFunctions
        //名称表:AddressOfNames
        //序号表:AddressOfNameOrdinals
        PDWORD nameAddr = (PDWORD)ImageRvaToVa(pNtAddr, ImageBase, ImportData->AddressOfNames, 0);
        for (int i = 0; i < dwNumberOfNames; i++){
            PCHAR funcName=(PCHAR)ImageRvaToVa(pNtAddr, ImageBase, (DWORD)nameAddr[i], 0);
            rExportFuncList.add(A2W(funcName));
        }
    }
    UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile);
    return rExportFuncList.size();
}
//文件_遍历PE导出表A
int X_Files_ErgodicExportTablesA(CXTextA fileName, CXVector<CXTextA>& rExportFuncList) {
    rExportFuncList.clear();
    HANDLE hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) { return 0; }
    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapping == NULL) { CloseHandle(hFile); return 0; }
    PIMAGE_DOS_HEADER ImageBase = (PIMAGE_DOS_HEADER)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    if (ImageBase == NULL) { CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    short int wMagic = ImageBase->e_magic;
    if (wMagic != IMAGE_DOS_SIGNATURE) { UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    LONG lfanew = ImageBase->e_lfanew;
    IMAGE_NT_HEADERS* pNtAddr = (IMAGE_NT_HEADERS*)((vint)ImageBase + lfanew);
    DWORD dwSignature = pNtAddr->Signature;
    if (dwSignature != IMAGE_NT_SIGNATURE) { UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    wMagic = pNtAddr->OptionalHeader.Magic;
    int Offset = 0;
    switch (wMagic) {
    case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
        Offset = 120;
        break;
    case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
        Offset = 136;
        break;
    default:
        xcl_log("该文件不是一个可执行映像");
        break;
    }
    if (Offset == 0) { UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    //  ImageRvaToVa(pNtAddr, ImageBase, ((XCLPTR)pNtAddr+ Offset), NULL);
    //XCLPTR ImportData = (XCLPTR)pNtAddr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
    IMAGE_EXPORT_DIRECTORY* ImportData = (IMAGE_EXPORT_DIRECTORY*)ImageRvaToVa(pNtAddr, ImageBase, *(DWORD*)((vint)pNtAddr + Offset), NULL);
    int dwNumberOfNames = 0;
    if (ImportData != NULL) {
        dwNumberOfNames = ImportData->NumberOfNames;
    }
    if (dwNumberOfNames > 0) {
        //地址表:AddressOfFunctions
        //名称表:AddressOfNames
        //序号表:AddressOfNameOrdinals
        PDWORD nameAddr = (PDWORD)ImageRvaToVa(pNtAddr, ImageBase, ImportData->AddressOfNames, 0);
        for (int i = 0; i < dwNumberOfNames; i++) {
            rExportFuncList.add((PCHAR)ImageRvaToVa(pNtAddr, ImageBase, (DWORD)nameAddr[i], 0));
        }
    }
    UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile);
    return rExportFuncList.size();
}

//文件_遍历PE导入表W
int X_Files_ErgodicImportTables(CXText fileName, CXVector<CXText>& rExportFuncList) {
    rExportFuncList.clear();
    HANDLE hFile = CreateFileW(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return 0;
    }
    HANDLE hMapping = CreateFileMappingW(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapping == NULL) {
        CloseHandle(hFile); return 0;
    }
    HANDLE ImageBase = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    if (ImageBase == NULL) {
        CloseHandle(hMapping); CloseHandle(hFile); return 0;
    }
    short int wMagic = *(short int*)ImageBase;
    if (wMagic != IMAGE_DOS_SIGNATURE) {
        UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0;
    }
    //IMAGE_DOS_HEADER => e_lfanew
    int lfanew = *(int*)((vint)ImageBase + 60);
	vint pNtAddr = ((vint)ImageBase + lfanew);
    //IMAGE_NT_HEADERS => Signature
    int dwSignature = *(int*)(pNtAddr);
    if (dwSignature != IMAGE_NT_SIGNATURE) {
        UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0;
    }
    //IMAGE_NT_HEADERS => OptionalHeader.Magic
    wMagic = *(short int*)(pNtAddr + 24);
    int Offset;
    if (wMagic == IMAGE_NT_OPTIONAL_HDR32_MAGIC) { Offset = 128; }
    else if (wMagic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) { Offset = 144; }
    else { xcl_log(L"非标准可执行镜像"); }
    if (Offset == 0) {
        UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0;
    }
	vint ImportData = (vint)ImageRvaToVa((PIMAGE_NT_HEADERS)pNtAddr, ImageBase, *(int*)(pNtAddr + Offset), NULL);
    while (ImportData != NULL && *((int*)ImportData) != 0) {
        char* szName = (char*)ImageRvaToVa((PIMAGE_NT_HEADERS)pNtAddr, ImageBase, *(int*)(ImportData + 12), NULL);
        rExportFuncList.add(A2W(szName));
        ImportData += sizeof(IMAGE_IMPORT_DESCRIPTOR);
    }
    UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile);
    return rExportFuncList.size();
}
//文件_遍历PE导入表A
int X_Files_ErgodicImportTablesA(CXTextA fileName, CXVector<CXTextA>& rExportFuncList) {
    rExportFuncList.clear();
    HANDLE hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return 0;
    }
    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapping == NULL) {
        CloseHandle(hFile); return 0;
    }
    HANDLE ImageBase = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    if (ImageBase == NULL) {
        CloseHandle(hMapping); CloseHandle(hFile); return 0;
    }
    short int wMagic = *(short int*)ImageBase;
    if (wMagic != IMAGE_DOS_SIGNATURE) {
        UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0;
    }
    //IMAGE_DOS_HEADER => e_lfanew
    int lfanew = *(int*)((vint)ImageBase + 60);
	vint pNtAddr = ((vint)ImageBase + lfanew);
    //IMAGE_NT_HEADERS => Signature
    int dwSignature = *(int*)(pNtAddr);
    if (dwSignature != IMAGE_NT_SIGNATURE) {
        UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0;
    }
    //IMAGE_NT_HEADERS => OptionalHeader.Magic
    wMagic = *(short int*)(pNtAddr + 24);
    int Offset;
    if (wMagic == IMAGE_NT_OPTIONAL_HDR32_MAGIC) { Offset = 128; }
    else if (wMagic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) { Offset = 144; }
    else { xcl_log(L"非标准可执行镜像"); }
    if (Offset == 0) {
        UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0;
    }
	vint ImportData = (vint)ImageRvaToVa((PIMAGE_NT_HEADERS)pNtAddr, ImageBase, *(int*)(pNtAddr + Offset), NULL);
    while (ImportData != NULL && *((int*)ImportData) != 0) {
        char* szName = (char*)ImageRvaToVa((PIMAGE_NT_HEADERS)pNtAddr, ImageBase, *(int*)(ImportData + 12), NULL);
        rExportFuncList.add(szName);
        ImportData += sizeof(IMAGE_IMPORT_DESCRIPTOR);
    }
    UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile);
    return rExportFuncList.size();
}

//文件_取目录
CXText X_Files_GetFileDir(CXText fileName) {
    if (X_Files_FileIsDir(fileName)) { return fileName; }
    return fileName.substr(0,X_String_Rfind(fileName, L"\\")+1);
}
//文件_取目录A
CXTextA X_Files_GetFileDirA(CXTextA fileName) {
    if (X_Files_FileIsDirA(fileName)) { return fileName; }
    return fileName.substr(0, X_String_RfindA(fileName, "\\") + 1);
}

//文件_删除W
bool X_Files_DeleteFile(CXText fileName) { return DeleteFileW(fileName) > 0; }
//文件_删除A
bool X_Files_DeleteFileA(CXTextA fileName) { return DeleteFileA(fileName) > 0; }

//文件_创建W
bool X_Files_FileCreate(CXText fileName,DWORD fileSize) {
    HANDLE hFile;
    HANDLE hMapFile;
    hFile = CreateFileW(fileName,GENERIC_WRITE | GENERIC_READ,FILE_SHARE_READ,
        NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    if (hFile == INVALID_HANDLE_VALUE){
        return false;
    }
    hMapFile = CreateFileMappingW(hFile,NULL,PAGE_READWRITE,0,fileSize,NULL);
    if (hMapFile == NULL){
        CloseHandle(hFile);
        return false;
    }
    CloseHandle(hMapFile);
    CloseHandle(hFile);
    return true;
}
//文件_创建A
bool X_Files_FileCreateA(CXTextA fileName, DWORD fileSize) {
    HANDLE hFile;
    HANDLE hMapFile;
    hFile = CreateFileA(fileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return false;
    }
    hMapFile = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, fileSize, NULL);
    if (hMapFile == NULL) {
        CloseHandle(hFile);
        return false;
    }
    CloseHandle(hMapFile);
    CloseHandle(hFile);
    return true;
}
//文件_创建文件目录W
bool X_Files_CreateFileDir(CXText fileName) {
    return X_Files_DirCreate(X_Files_GetFileDir(fileName));
}
//文件_创建文件目录A
bool X_Files_CreateFileDirA(CXTextA fileName) {
    return X_Files_DirCreateA(X_Files_GetFileDirA(fileName));
}

////文件_创建映射对象W
//void X_Files_CreateFileMapping(CXText mappingObjName, CXText mappingObjValue) {
//    HANDLE handle = CreateFileMappingW(INVALID_HANDLE_VALUE, 0, 4, 0, 4, mappingObjName);
//
//}

//文件_打开W
HANDLE X_File_FileOpen(CXText fileName) {
    return CreateFileW(fileName, GENERIC_READ|GENERIC_WRITE,0,0, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN,0);
}
//文件_打开A
HANDLE X_File_FileOpenA(CXTextA fileName) {
    return CreateFileA(fileName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0);
}

//文件_到短文件名W
CXText X_File_GetShortPathName(CXText fileName) {
    DWORD dwSize = GetShortPathNameW(fileName,0,0);
    if (dwSize <= 0) { return L""; }
    wchar_t* szPath=new wchar_t[dwSize];
    GetShortPathNameW(fileName, szPath, dwSize);
    CXText ret = szPath;
    delete szPath;
    return ret;
}
//文件_到短文件名A
CXTextA X_File_GetShortPathNameA(CXTextA fileName) {
    DWORD dwSize = GetShortPathNameA(fileName, 0, 0);
    if (dwSize <= 0) { return ""; }
    char* szPath = new char[dwSize];
    dwSize=GetShortPathNameA(fileName, szPath, dwSize);
    CXTextA ret = szPath;
    delete szPath;
    return ret;
}

//文件_到长文件名W
CXText X_File_GetLongPathName(CXText fileName) {
    DWORD dwSize = GetLongPathNameW(fileName, 0, 0);
    if (dwSize <= 0) { return L""; }
    wchar_t* szPath = new wchar_t[dwSize];
    GetLongPathNameW(fileName, szPath, dwSize);
    CXText ret = szPath;
    delete szPath;
    if (lstrcmpW(X_String_Trim(ret), L"") != 0) { return ret; }
    return fileName;
}
//文件_到长文件名A
CXTextA X_File_GetLongPathNameA(CXTextA fileName) {
    DWORD dwSize = GetLongPathNameA(fileName, 0, 0);
    if (dwSize <= 0) { return ""; }
    char* szPath = new char[dwSize];
    GetLongPathNameA(fileName, szPath, dwSize);
    CXTextA ret = szPath;
    if (strcmp(X_String_TrimA(ret), "") != 0) { return ret; }
    return fileName;
}

//文件_定位多个W
bool X_Files_FileLocationMultiples(CXText dirName, CXVector<CXText>fileList) {
    if (PathIsDirectoryW(dirName) <=0) { return false; }
    LPITEMIDLIST pidl = ILCreateFromPathW(dirName);
    if (pidl == NULL) { return false; }
    size_t cidl = fileList.size();
    std::vector<LPCITEMIDLIST> apidl;
    for (size_t i = 0; i < cidl; i++) {
        LPCITEMIDLIST tidl = ILCreateFromPathW(fileList[i]);
        if (tidl == NULL) { continue; }
        apidl.push_back(tidl);
    }
    cidl = apidl.size();
	if(cidl == 0) {return false;}
    auto hr= SHOpenFolderAndSelectItems(pidl, cidl, (LPCITEMIDLIST*)&apidl[0], 0);
    for (size_t i = 0; i < cidl; i++) {ILFree((LPITEMIDLIST)apidl[i]);}
    ILFree(pidl);
    return hr==S_OK;
}
//文件_定位多个A
bool X_Files_FileLocationMultiplesA(CXTextA dirName, CXVector<CXTextA>fileList) {
    if (PathIsDirectoryA(dirName) <= 0) { return false; }
    LPITEMIDLIST pidl = ILCreateFromPathA(dirName);
    if (pidl == NULL) { return false; }
    size_t cidl = fileList.size();
    std::vector<LPCITEMIDLIST> apidl;
    for (size_t i = 0; i < cidl; i++) {
        LPCITEMIDLIST tidl = ILCreateFromPathA(fileList[i]);
        if (tidl == NULL) { continue; }
        apidl.push_back(tidl);
    }
    cidl = apidl.size();
	if(cidl == 0) {return false;}
    auto hr = SHOpenFolderAndSelectItems(pidl, cidl, (LPCITEMIDLIST*)&apidl[0], 0);
    for (size_t i = 0; i < cidl; i++) { ILFree((LPITEMIDLIST)apidl[i]); }
    ILFree(pidl);
    return hr == S_OK;
}

//文件_改扩展名W
bool X_Files_FileRenameExtension(CXText fileName,CXText newExtension) {
    LPWSTR suffix = PathFindExtensionW(newExtension);
    if (lstrlenW(suffix) > 0) {
        wchar_t* NewPath = new wchar_t[fileName.size()+1];
        wcscpy_s(NewPath, fileName.size()+1, fileName.get());
        PathRenameExtensionW(NewPath, newExtension);
        bool r = X_Files_FileRename(fileName, NewPath);
        delete NewPath;
        return r;
    }
    return false;
}
//文件_改扩展名A
bool X_Files_FileRenameExtensionA(CXTextA fileName, CXTextA newExtension) {
    LPSTR suffix = PathFindExtensionA(newExtension);
    if (strlen(suffix) > 0) {
        char* NewPath = new char[fileName.size() + 1];
        strcpy_s(NewPath, fileName.size() + 1, fileName.get());
        PathRenameExtensionA(NewPath, newExtension);
        bool r = X_Files_FileRenameA(fileName, NewPath);
        delete NewPath;
        return r;
    }
    return false;
}

//文件_关闭
void X_File_FileClose(HANDLE &hFile) {
    if (hFile == NULL) { return; }
    CloseHandle(hFile);
    hFile = NULL;
}

//文件_关联W
void X_File_FilerRelation(CXText fileName, CXText suffix, CXText ICOPath, CXText fileType, CXText relationName) {
    //CXVector<CXText> allSuffix = X_String_SplitWithStl(suffix,L"|");
    //if (lstrcmpW(fileName, L"") == 0) {
    //    //取消关联
    //    for (int i = 0; i < allSuffix.size(); i++) {
    //        X_System_Class_Reg reg;
    //        xcl_log(reg.GetString(L"HKEY_CLASSES_ROOT", L"."+allSuffix[i]));
    //    }
    //}
}

//文件_合并A
bool X_File_FileMergeA(CXTextA file1, CXTextA file2, CXTextA newFile) {
    if (strcmp(newFile, "") == 0) {
        std::ofstream wf;
        wf.open(file1, std::ios::binary| std::ios::app);
        if (!wf.is_open()) { return false; }
        CXBytes f;
        X_Files_ReadFileA(file2, f);
        wf.write((char*)f.get(),f.size());
        wf.close();
        return true;
    }
    std::ofstream f;
    f.open(newFile, std::ios::out|std::ios::binary);
    if (!f.is_open()) { return false; }
    CXBytes fb;
    X_Files_ReadFileA(file1, fb);
    f.write((char*)fb.get(), fb.size());
    X_Files_ReadFileA(file2, fb);
    f.write((char*)fb.get(), fb.size());
    f.close();
    return true;
}
//文件_合并W
bool X_File_FileMerge(CXText file1, CXText file2, CXText newFile) {
    if (lstrcmpW(newFile, L"") == 0) {
        std::ofstream wf;
        wf.open(file1, std::ios::binary | std::ios::app);
        if (!wf.is_open()) { return false; }
        CXBytes f;
        X_Files_ReadFile(file2, f);
        wf.write((char*)f.get(), f.size());
        wf.close();
        return true;
    }
    std::ofstream f;
    f.open(newFile, std::ios::out | std::ios::binary);
    if (!f.is_open()) { return false; }
    CXBytes fb;
    X_Files_ReadFile(file1, fb);
    f.write((char*)fb.get(), fb.size());
    X_Files_ReadFile(file2, fb);
    f.write((char*)fb.get(), fb.size());
    f.close();
    return true;
}

//文件_句柄取路径W
CXText X_File_HendleGetPath(HANDLE hFile) {
    wchar_t path[MAX_PATH];
    DWORD dwSize = GetFinalPathNameByHandleW(hFile, path, MAX_PATH, 0);
    CXText r = path;
    r = r.substr(r.find(L":") - 1, r.size() - 3);
    return r;
}
//文件_句柄取路径A
CXTextA X_File_HendleGetPathA(HANDLE hFile) {
    char path [MAX_PATH];
    DWORD dwSize = GetFinalPathNameByHandleA(hFile, path, MAX_PATH, 0);
    CXTextA r = path;
    r = r.substr(r.find(":") - 1, r.size() - 3);
    return r;
}

//文件_取MIME类型W
CXText X_File_GetFileMIMEType(CXText fileName) {
    LPWSTR pwzMimeOut=NULL;
    auto hr = FindMimeFromData(NULL,fileName,NULL,0,NULL, FMFD_URLASFILENAME,&pwzMimeOut,0);
    if (hr == S_OK && pwzMimeOut != NULL) {
        CXText r = pwzMimeOut;
        CoTaskMemFree(pwzMimeOut);
        return r;
    }
    return L"";
}
//文件_取MIME类型A
CXTextA X_File_GetFileMIMETypeA(CXTextA fileName) {
    return W2A(X_File_GetFileMIMEType(A2W(fileName)));
}

//文件_取尺寸W
CXText X_File_GetFileVolume(CXText fileName, bool format) {
    WIN32_FIND_DATAW fileInfo;
    HANDLE hFind;
    DWORD fileSize;
    hFind = FindFirstFileW(fileName, &fileInfo);
    if (hFind == INVALID_HANDLE_VALUE) { return L""; }
    fileSize = fileInfo.nFileSizeLow;
    FindClose(hFind);
    CXText r;
    if (!format) {
        r = std::to_wstring(fileSize).c_str();
        return r;
    }
    wchar_t sbuffer[25];
    memset(sbuffer, 0, 25);
    StrFormatByteSizeW(fileSize, sbuffer,25);
    r = sbuffer;
    r=X_String_Subreplace(r,L"字节",L"B");
    return r;
}
//文件_取尺寸A
CXTextA X_File_GetFileVolumeA(CXTextA fileName, bool format) {
    WIN32_FIND_DATAA fileInfo;
    HANDLE hFind;
    DWORD fileSize;
    hFind = FindFirstFileA(fileName, &fileInfo);
    if (hFind == INVALID_HANDLE_VALUE) { return ""; }
    fileSize = fileInfo.nFileSizeLow;
    FindClose(hFind);
    CXTextA r;
    if (!format) {
        r = std::to_string(fileSize).c_str();
        return r;
    }
    char sbuffer[25];
    memset(sbuffer, 0, 25);
    StrFormatByteSizeA(fileSize, sbuffer, 25);
    r = sbuffer;
    r = X_String_SubreplaceA(r, "字节", "B");
    return r;
}

//文件_取大小W
DWORD X_File_GetFileSize(CXText fileName) {
    WIN32_FIND_DATAW fileInfo;
    HANDLE hFind;
    DWORD fileSize;
    hFind = FindFirstFileW(fileName, &fileInfo);
    if (hFind == INVALID_HANDLE_VALUE) { return 0; }
    fileSize = fileInfo.nFileSizeLow;
    FindClose(hFind);
    return fileSize;
}
//文件_取大小A
DWORD X_File_GetFileSizeA(CXTextA fileName) {
    WIN32_FIND_DATAA fileInfo;
    HANDLE hFind;
    DWORD fileSize;
    hFind = FindFirstFileA(fileName, &fileInfo);
    if (hFind == INVALID_HANDLE_VALUE) { return 0; }
    fileSize = fileInfo.nFileSizeLow;
    FindClose(hFind);
    return fileSize;
}

//文件_取格式W
int X_File_GetFileForm(CXBytes &FileByte,CXText &retFileType) {
    CXBytes a=FileByte.getLeft(2);
    if (strcmp(a.getTextPtrA(),"MZ")==0) {
        retFileType = L"exe/dll";
        return X_FILE_TYPR_EXEORDLL;
    }
    a = FileByte.getLeft(3);
    if (strcmp(a.getTextPtrA(), "Rar") == 0) {
        retFileType = L"rar";
        return X_FILE_TYPR_RAR;
    }
    a = FileByte.getLeft(2);
    if (strcmp(a.getTextPtrA(), "PK") == 0) {
        retFileType = L"zip";
        return X_FILE_TYPR_ZIP;
    }
    a = FileByte.getLeft(2);
    if (strcmp(a.getTextPtrA(), "7z") == 0) {
        retFileType = L"7z";
        return X_FILE_TYPR_7Z;
    }
    a = FileByte.getLeft(24);
    CXBytes b = FileByte.getLeft(3);
    const BYTE sts[] = {255, 216, 255};
    if (strcmp(a.getTextPtrA(), "Content-Type: image/jpeg") == 0 || memcmp(b, sts, 3)==0) {
        retFileType = L"jpg";
        return X_FILE_TYPR_JPG;
    }
    a = FileByte.getLeft(6);
    if (strcmp(a.getTextPtrA(), "GIF89a") == 0) {
        retFileType = L"GIF89a";
        return X_FILE_TYPR_GIF;
    }
    a = FileByte.getLeft(3);
    if (strcmp(a.getTextPtrA(), "FWS") == 0) {
        retFileType = L"SWF";
        return X_FILE_TYPR_SWF;
    }
    return -1;
}
//文件_取格式W
int X_File_GetFileForm(CXBytes& FileByte) {
    CXText a;
    return X_File_GetFileForm(FileByte, a);
}
//文件_取格式A
int X_File_GetFileFormA(CXBytes& FileByte, CXTextA &retFileType) {
    CXBytes a = FileByte.getLeft(2);
    if (strcmp(a.getTextPtrA(), "MZ") == 0) {
        retFileType = "exe/dll";
        return X_FILE_TYPR_EXEORDLL;
    }
    a = FileByte.getLeft(3);
    if (strcmp(a.getTextPtrA(), "Rar") == 0) {
        retFileType = "rar";
        return X_FILE_TYPR_RAR;
    }
    a = FileByte.getLeft(2);
    if (strcmp(a.getTextPtrA(), "PK") == 0) {
        retFileType = "zip";
        return X_FILE_TYPR_ZIP;
    }
    a = FileByte.getLeft(2);
    if (strcmp(a.getTextPtrA(), "7z") == 0) {
        retFileType = "7z";
        return X_FILE_TYPR_7Z;
    }
    a = FileByte.getLeft(24);
    CXBytes b = FileByte.getLeft(3);
    const BYTE sts[] = { 255, 216, 255 };
    if (strcmp(a.getTextPtrA(), "Content-Type: image/jpeg") == 0 || memcmp(b, sts, 3) == 0) {
        retFileType = "jpg";
        return X_FILE_TYPR_JPG;
    }
    a = FileByte.getLeft(6);
    if (strcmp(a.getTextPtrA(), "GIF89a") == 0) {
        retFileType = "GIF89a";
        return X_FILE_TYPR_GIF;
    }
    a = FileByte.getLeft(3);
    if (strcmp(a.getTextPtrA(), "FWS") == 0) {
        retFileType = "SWF";
        return X_FILE_TYPR_SWF;
    }
    return -1;
}
//文件_取格式A
int X_File_GetFileFormA(CXBytes& FileByte) {
    CXTextA a;
    return X_File_GetFileFormA(FileByte, a);
}

//文件_取关联A
CXTextA X_File_GetRelationA(CXTextA suffix){
    CXTextA ls = suffix;
    ls = X_String_SubreplaceA(ls,"*");
    ls = X_String_SubreplaceA(ls,".");
    ls = "."+ ls;
    int nRet = FALSE;
    HKEY hExtKey;
    char szPath[1024];
    DWORD dwSize = sizeof(szPath);
    if (RegOpenKeyA(HKEY_CLASSES_ROOT, ls, &hExtKey) != ERROR_SUCCESS) { return ""; }
    memset(szPath, 0, dwSize);
    RegQueryValueExA(hExtKey, NULL, NULL, NULL, (LPBYTE)szPath, &dwSize);
    RegCloseKey(hExtKey);
    if (strlen(szPath) < 1) { return ""; }
    CXTextA exec = szPath; exec += "\\shell";
    if (RegOpenKeyA(HKEY_CLASSES_ROOT, exec, &hExtKey) != ERROR_SUCCESS) { return ""; }
    memset(szPath,0, dwSize);
    dwSize = sizeof(szPath);
    RegQueryValueExA(hExtKey, "open", NULL, NULL, (LPBYTE)szPath, &dwSize);
    CXTextA openType = strcmp(szPath,"")==0?"open": szPath;
    RegCloseKey(hExtKey);
    if (RegOpenKeyExA(HKEY_CLASSES_ROOT, exec + "\\" + openType + "\\command",0,KEY_READ, &hExtKey) != ERROR_SUCCESS) { return ""; }
    dwSize = sizeof(szPath);
    CXTextA r;
    memset(szPath, 0, dwSize);
    if(RegQueryValueExA(hExtKey, NULL, NULL, NULL, (LPBYTE)szPath, &dwSize)==ERROR_SUCCESS){
        r = szPath;
    }
    RegCloseKey(hExtKey);
    return r;
}
//文件_取关联W
CXText X_File_GetRelation(CXText suffix) {
    CXText ls = suffix;
    ls = X_String_Subreplace(ls, L"*");
    ls = X_String_Subreplace(ls, L".");
    ls = L"." + ls;
    int nRet = FALSE;
    HKEY hExtKey;
    wchar_t szPath[1024];
    DWORD dwSize = sizeof(szPath);
    if (RegOpenKeyW(HKEY_CLASSES_ROOT, ls, &hExtKey) != ERROR_SUCCESS) { return L""; }
    memset(szPath, 0, dwSize);
    RegQueryValueExW(hExtKey, NULL, NULL, NULL, (LPBYTE)szPath, &dwSize);
    RegCloseKey(hExtKey);
    if (lstrlenW(szPath) < 1) { return L""; }
    CXText exec = szPath; exec += L"\\shell";
    if (RegOpenKeyW(HKEY_CLASSES_ROOT, exec, &hExtKey) != ERROR_SUCCESS) { return L""; }
    memset(szPath, 0, dwSize);
    dwSize = sizeof(szPath);
    RegQueryValueExW(hExtKey, L"open", NULL, NULL, (LPBYTE)szPath, &dwSize);
    CXText openType = lstrcmpW(szPath, L"") == 0 ? L"open" : szPath;
    RegCloseKey(hExtKey);
    if (RegOpenKeyExW(HKEY_CLASSES_ROOT, exec + L"\\" + openType + L"\\command", 0, KEY_READ, &hExtKey) != ERROR_SUCCESS) { return L""; }
    dwSize = sizeof(szPath);
    CXText r;
    memset(szPath, 0, dwSize);
    if (RegQueryValueExW(hExtKey, NULL, NULL, NULL, (LPBYTE)szPath, &dwSize) == ERROR_SUCCESS) {
        r = szPath;
    }
    RegCloseKey(hExtKey);
    return r;
}

//文件_取类型A
CXTextA X_File_GetFileTypeA(CXTextA fileName){
    SHFILEINFOA Fileinfo;
    SHGetFileInfoA(fileName, 0, &Fileinfo, 348, 1024);
    return Fileinfo.szTypeName;
}
//文件_取类型W
CXText X_File_GetFileType(CXText fileName) {
    SHFILEINFOW Fileinfo;
    SHGetFileInfoW(fileName, 0, &Fileinfo, 348, 1024);
    return Fileinfo.szTypeName;
}

//文件_取路径盘符W
CXText X_File_GetPathDriveLetter(CXText fileName){
    if (fileName.size() < 2) { return L""; }
    if (fileName[1]!=L':') { return L""; }
    CXText b = X_String_ToUpper(fileName.substr(0, 1));
    if (b[0] < L'A' || b[0]>L'Z') { return L""; };
    return b;
}
//文件_取路径盘符A
CXTextA X_File_GetPathDriveLetterA(CXTextA fileName) {
    if (fileName.size() < 2) { return ""; }
    if (fileName[1] != ':') { return ""; }
    CXTextA b = X_String_ToUpperA(fileName.substr(0, 1));
    xcl_log(b);
    if (b[0] < 'A' || b[0]>'Z') { return ""; };
    return b;
}

//文件_取时间W
bool X_File_FileGetTime(CXText fileName, 
    CDateTimeTM &createTime,
    CDateTimeTM &accessTime,
    CDateTimeTM &writeTime) {
    createTime.m_tm = { 0 };
    accessTime.m_tm = { 0 };
    writeTime.m_tm = { 0 };
    if (!X_Files_FileIfIsSet(fileName)) { return false; }
    HANDLE hFile = CreateFileW(fileName, GENERIC_READ,          // open for reading
        FILE_SHARE_READ,       // share for reading
        NULL,                            // default security
        OPEN_EXISTING,          // existing file only
        FILE_FLAG_BACKUP_SEMANTICS, // normal file
        NULL);
    if (hFile == INVALID_HANDLE_VALUE) { return false; }
    FILETIME CreateTime, AccessTime, WriteTime;
    BOOL isRes = GetFileTime(hFile, &CreateTime, &AccessTime, &WriteTime);
    CloseHandle(hFile);
    if (isRes == FALSE) { return false; }
    SYSTEMTIME ltime;
    bool err;
    err=FileTimeToSystemTime(&CreateTime,&ltime)==TRUE;
    X_Time_SystemToCSysDateTime(ltime,createTime);
    err=FileTimeToSystemTime(&AccessTime, &ltime)==TRUE&&err?true:false;
    X_Time_SystemToCSysDateTime(ltime, accessTime);
    err = FileTimeToSystemTime(&WriteTime, &ltime) == TRUE && err ? true : false;
    X_Time_SystemToCSysDateTime(ltime, writeTime);
    return true;
}
//文件_取时间A
bool X_File_FileGetTimeA(CXTextA fileName,
    CDateTimeTM& createTime,
    CDateTimeTM& accessTime,
    CDateTimeTM& writeTime) {
    createTime.m_tm = { 0 };
    accessTime.m_tm = { 0 };
    writeTime.m_tm = { 0 };
    if (!X_Files_FileIfIsSetA(fileName)) { return false; }
    HANDLE hFile = CreateFileA(fileName, GENERIC_READ,          // open for reading
        FILE_SHARE_READ,       // share for reading
        NULL,                            // default security
        OPEN_EXISTING,          // existing file only
        FILE_FLAG_BACKUP_SEMANTICS, // normal file
        NULL); 
    if (hFile == INVALID_HANDLE_VALUE) { return false; }
    FILETIME CreateTime, AccessTime, WriteTime;
    BOOL isRes = GetFileTime(hFile, &CreateTime, &AccessTime, &WriteTime);
    CloseHandle(hFile);
    if (isRes == FALSE) { return false; }
    SYSTEMTIME ltime;
    bool err;
    err = FileTimeToSystemTime(&CreateTime, &ltime) == TRUE;
    X_Time_SystemToCSysDateTime(ltime, createTime);
    err = FileTimeToSystemTime(&AccessTime, &ltime) == TRUE && err ? true : false;
    X_Time_SystemToCSysDateTime(ltime, accessTime);
    err = FileTimeToSystemTime(&WriteTime, &ltime) == TRUE && err ? true : false;
    X_Time_SystemToCSysDateTime(ltime, writeTime);
    return true;
}
//文件_取时间W
bool X_File_FileGetTime(CXText fileName,
    CDateTimeTM& createTime,
    CDateTimeTM& accessTime) {
    CDateTimeTM a;
    return X_File_FileGetTime(fileName, createTime, accessTime,a);
}
//文件_取时间A
bool X_File_FileGetTimeA(CXTextA fileName,
    CDateTimeTM& createTime,
    CDateTimeTM& accessTime) {
    CDateTimeTM a;
    return X_File_FileGetTimeA(fileName, createTime, accessTime, a);
}
//文件_取时间W
bool X_File_FileGetTime(CXText fileName,
    CDateTimeTM& createTime) {
    CDateTimeTM a;
    CDateTimeTM b;
    return X_File_FileGetTime(fileName, createTime, b, a);
}
//文件_取时间A
bool X_File_FileGetTimeA(CXTextA fileName,
    CDateTimeTM& createTime) {
    CDateTimeTM a;
    CDateTimeTM b;
    return X_File_FileGetTimeA(fileName, createTime, b, a);
}
//文件_取时间W
bool X_File_FileGetTime(CXText fileName) {
    CDateTimeTM a;
    CDateTimeTM b;
    CDateTimeTM c;
    return X_File_FileGetTime(fileName, c, b, a);
}
//文件_取时间A
bool X_File_FileGetTimeA(CXTextA fileName) {
    CDateTimeTM a;
    CDateTimeTM b;
    CDateTimeTM c;
    return X_File_FileGetTimeA(fileName, c, b, a);
}

//文件_取真实尺寸W
ULONGLONG X_File_GetFileRealSize(CXText fileName) {
    DWORD dwFileSizeHigh;
    DWORD dwFileSizeLow = GetCompressedFileSizeW(fileName, &dwFileSizeHigh);
    ULONGLONG FileSize;
    if (dwFileSizeLow == INVALID_FILE_SIZE && dwFileSizeHigh == 0) {return 0;}
    if(dwFileSizeLow!=0){
        FileSize = (ULONGLONG)((__int64)dwFileSizeLow | ((__int64)dwFileSizeHigh << 32));
    }
    return FileSize;
}
//文件_取真实尺寸A
ULONGLONG X_File_GetFileRealSizeA(CXTextA fileName) {
    DWORD dwFileSizeHigh;
    DWORD dwFileSizeLow = GetCompressedFileSizeA(fileName, &dwFileSizeHigh);
    ULONGLONG FileSize;
    if (dwFileSizeLow == INVALID_FILE_SIZE && dwFileSizeHigh == 0) { return 0; }
    if (dwFileSizeLow != 0) {
        FileSize = (ULONGLONG)((__int64)dwFileSizeLow | ((__int64)dwFileSizeHigh << 32));
    }
    return FileSize;
}

//文件_取属性W
DWORD X_File_GetFileAttributes(CXText fileName) {
    return GetFileAttributesW(fileName);
}
//文件_取属性W
DWORD X_File_GetFileAttributesA(CXTextA fileName) {
    return GetFileAttributesA(fileName);
}

//文件_取图标句柄
HANDLE X_File_GetFileIconHand(CXText fileName) {
    SHFILEINFOW sInfo;
    SHGetFileInfoW(fileName, 128, &sInfo, 348, 256);
    return sInfo.hIcon;
}
//文件_取图标句柄A
HANDLE X_File_GetFileIconHandA(CXTextA fileName) {
    SHFILEINFOA sInfo;
    SHGetFileInfoA(fileName, 128, &sInfo, 348, 256);
    return sInfo.hIcon;
}

//文件_写到文件
bool X_File_WriteFile(CXText fileName,  CXBytes& filebytes) {
    std::ofstream wf;
    wf.open(fileName, std::ios::out| std::ios::binary);
    if (!wf.is_open()) { return false; }
    int index = 0;
    int addnum = filebytes.size();
    int iBuffLen = addnum< 2048 ? addnum : 2048;
    while (addnum>0) {
        char* buff = new char[addnum];
        CXBytes b =filebytes.getMid(index, iBuffLen);
        wf.write((char*)b.get(),b.size());
        index = (index+ iBuffLen)> filebytes.size()? filebytes.size(): index + iBuffLen;
        addnum = (filebytes.size()- index)>2048? 2048: filebytes.size() - index;
        delete buff;
    }
    wf.close();
    return true;
}
//文件_写到文件A
bool X_File_WriteFileA(CXTextA fileName, CXBytes& filebytes) {
    std::ofstream wf;
    wf.open(fileName, std::ios::out | std::ios::binary);
    if (!wf.is_open()) { return false; }
    int index = 0;
    int addnum = filebytes.size();
    int iBuffLen = addnum < 2048 ? addnum : 2048;
    while (addnum > 0) {
        char* buff = new char[addnum];
        CXBytes b = filebytes.getMid(index, iBuffLen);
        wf.write((char*)b.get(), b.size());
        index = (index + iBuffLen) > filebytes.size() ? filebytes.size() : index + iBuffLen;
        addnum = (filebytes.size() - index) > 2048 ? 2048 : filebytes.size() - index;
        delete buff;
    }
    wf.close();
    return true;
}

////文件_取文件版本信息
//CXText X_File_GetFileVerInfo(CXText fileName,int Type) {
//    DWORD dwHandle;
//    CXText wzBuf;
//    DWORD dwInfoSize = GetFileVersionInfoSizeW(fileName, &dwHandle);
//    if (dwInfoSize > 0) {
//        LPVOID pData = malloc(dwInfoSize);
//        if (GetFileVersionInfoW(fileName,NULL, dwInfoSize, pData)) {
//            const wchar_t* aryType[] = { L"\\", L"CompanyName", L"FileDescription", L"InternalName",
//            L"LegalCopyright", L"LegalTrademarks", L"OriginalFilename",
//            L"ProductName", L"Comments", L"PrivateBuild", L"SpecialBuild", L"" };
//            if (Type<0 || (Type+1) > sizeof(aryType)) {
//                wzBuf = X_File_GetFileVersion(fileName);
//            }
//            else {
//                const wchar_t* wzSubBlock = L"\VarFileInfo\Translation";
//                LPVOID pwzBuf;
//                UINT nBufLen;
//                if (VerQueryValueW(pData, wzSubBlock, &pwzBuf, &nBufLen)!=FALSE) {
//                    short int dwLangCodePage=*(short int*)(pwzBuf);
//
//                }
//            }
//        }
//
//    }
//    return wzBuf;
//}

//文件_取文件名W
CXText X_File_GetFileName(CXText fileName,bool addSuffix) {
    CXText pn = PathFindFileNameW(fileName);
    if (lstrcmpW(pn.substr(pn.size() - 2, 1), L"\\") == 0) {
        return L"";
    }
    return addSuffix? pn:
        pn.substr(0, pn.size()- X_Files_GetFileExtension(pn).size());
}
//文件_取文件名A
CXTextA X_File_GetFileNameA(CXTextA fileName, bool addSuffix) {
    CXTextA pn = PathFindFileNameA(fileName);
    if (strcmp(pn.substr(pn.size() - 2, 1), "\\") == 0) {
        return "";
    }
    return addSuffix ? pn :
        pn.substr(0, pn.size() - X_Files_GetFileExtensionA(pn).size());
}

//文件_去扩展名W
bool X_File_FileDelSuffix(CXText fileName) {
    auto suffix=X_Files_GetFileExtension(fileName);
    if (lstrcmpW(suffix, L"") == 0) { return false; }
    return rename(W2A(fileName), W2A(fileName.substr(0, fileName.size() - suffix.size())))==0;
}
//文件_去扩展名A
bool X_File_FileDelSuffixA(CXTextA fileName) {
    auto suffix = X_Files_GetFileExtensionA(fileName);
    if (strcmp(suffix, "") == 0) { return false; }
    return rename(fileName, fileName.substr(0, fileName.size() - suffix.size())) == 0;
}

//文件_删除某类文件W
int X_File_DelWTypeFiles(CXText dirName,CXText Suffix,bool enumSon) {
    int delNum = 0;
    if (dirName == L"") { return 0; }
    if (Suffix.find(L".") == std::wstring::npos) { return 0; }
    CXText lDir = dirName;
    if (lDir[lDir.size() - 1] != L'\\') { lDir += L'\\'; }
    WIN32_FIND_DATAW FindData;
    CXText l_name = lDir + Suffix;
    HANDLE hFind = FindFirstFileW(l_name, &FindData);
    do {
        if (lstrcmpW(FindData.cFileName, L".") == 0 || lstrcmpW(FindData.cFileName, L"..") == 0) {
            continue;
        }
        if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) == FILE_ATTRIBUTE_ARCHIVE) {
            //file
            l_name = lDir +FindData.cFileName;
            if (X_Files_DeleteFile(l_name)) { delNum+=1; }
        }
    } while (FindNextFileW(hFind, &FindData));
    FindClose(hFind);
    if(enumSon){
        WIN32_FIND_DATAW FindData;
        CXText l_name = lDir + L"*.*";
        HANDLE hFind = FindFirstFileW(l_name, &FindData);
        do {
            if (lstrcmpW(FindData.cFileName, L".") == 0 || lstrcmpW(FindData.cFileName, L"..") == 0) {
                continue;
            }
            if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
                //DIR
                CXText nd = lDir + FindData.cFileName;
                delNum += X_File_DelWTypeFiles(nd, Suffix, enumSon);
            }
        } while (FindNextFileW(hFind, &FindData));
        FindClose(hFind);
    }
    return delNum;
}
//文件_删除某类文件A
int X_File_DelWTypeFilesA(CXTextA dirName, CXTextA Suffix, bool enumSon) {
    int delNum = 0;
    if (dirName == "") { return 0; }
    if (Suffix.find(".") == std::wstring::npos) { return 0; }
    CXTextA lDir = dirName;
    if (lDir[lDir.size() - 1] != L'\\') { lDir += L'\\'; }
    WIN32_FIND_DATAA FindData;
    CXTextA l_name = lDir + Suffix;
    HANDLE hFind = FindFirstFileA(l_name, &FindData);
    do {
        if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0) {
            continue;
        }
        if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) == FILE_ATTRIBUTE_ARCHIVE) {
            //file
            l_name = lDir + FindData.cFileName;
            if (X_Files_DeleteFileA(l_name)) { delNum += 1; }
        }
    } while (FindNextFileA(hFind, &FindData));
    FindClose(hFind);
    if (enumSon) {
        WIN32_FIND_DATAA FindData;
        CXTextA l_name = lDir + "*.*";
        HANDLE hFind = FindFirstFileA(l_name, &FindData);
        do {
            if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0) {
                continue;
            }
            if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
                //DIR
                CXTextA nd = lDir + FindData.cFileName;
                delNum += X_File_DelWTypeFilesA(nd, Suffix, enumSon);
            }
        } while (FindNextFileA(hFind, &FindData));
        FindClose(hFind);
    }
    return delNum;
}

//文件_是否被占用W
bool X_File_FileWhetItIsLocked(CXText fileName) {
    if (!X_Files_FileIfIsSet(fileName)) { return false; }
    HANDLE hFile = CreateFileW(fileName, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == INVALID_HANDLE_VALUE) {
        return true;
    }
    CloseHandle(hFile);
    return false;
}
//文件_是否被占用A
bool X_File_FileWhetItIsLockedA(CXTextA fileName) {
    if (!X_Files_FileIfIsSetA(fileName)) { return false; }
    HANDLE hFile = CreateFileA(fileName, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == INVALID_HANDLE_VALUE) {
        return true;
    }
    CloseHandle(hFile);
    return false;
}

//文件_是否是稀疏文件W
bool X_File_FileIsSparseFile(CXText fileName) {
    DWORD Attributes = GetFileAttributesW(fileName);
    if (Attributes < 0) { return false; }
    return (Attributes | FILE_ATTRIBUTE_SPARSE_FILE) == 512;
}
//文件_是否是稀疏文件A
bool X_File_FileIsSparseFileA(CXTextA fileName) {
    DWORD Attributes = GetFileAttributesA(fileName);
    if (Attributes < 0) { return false; }
    return (Attributes | FILE_ATTRIBUTE_SPARSE_FILE) == 512;
}

//文件_是否为64位W
bool X_File_FileIfIsX64(CXText fileName) {
    HANDLE hFile = CreateFileW(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) { return 0; }
    HANDLE hMapping = CreateFileMappingW(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapping == NULL) { CloseHandle(hFile); return 0; }
    PIMAGE_DOS_HEADER ImageBase = (PIMAGE_DOS_HEADER)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    if (ImageBase == NULL) { CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    short int wMagic = ImageBase->e_magic;
    if (wMagic != IMAGE_DOS_SIGNATURE) { UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    LONG lfanew = ImageBase->e_lfanew;
    IMAGE_NT_HEADERS* pNtAddr = (IMAGE_NT_HEADERS*)((vint)ImageBase + lfanew);
    DWORD dwSignature = pNtAddr->Signature;
    if (dwSignature != IMAGE_NT_SIGNATURE) { UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    wMagic = pNtAddr->OptionalHeader.Magic;
    int Offset = 0;
    bool is64 = false;
    switch (wMagic) {
    case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
        is64=false; //X86
        break;
    case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
        is64=true; //X64
        break;
    default:
        xcl_log("该文件不是一个可执行映像");
        break;
    }
    UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile);
    return is64;
}
//文件_是否为64位A
bool X_File_FileIfIsX64A(CXTextA fileName) {
    HANDLE hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) { return 0; }
    HANDLE hMapping = CreateFileMappingW(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMapping == NULL) { CloseHandle(hFile); return 0; }
    PIMAGE_DOS_HEADER ImageBase = (PIMAGE_DOS_HEADER)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    if (ImageBase == NULL) { CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    short int wMagic = ImageBase->e_magic;
    if (wMagic != IMAGE_DOS_SIGNATURE) { UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    LONG lfanew = ImageBase->e_lfanew;
    IMAGE_NT_HEADERS* pNtAddr = (IMAGE_NT_HEADERS*)((vint)ImageBase + lfanew);
    DWORD dwSignature = pNtAddr->Signature;
    if (dwSignature != IMAGE_NT_SIGNATURE) { UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile); return 0; }
    wMagic = pNtAddr->OptionalHeader.Magic;
    int Offset = 0;
    bool is64 = false;
    switch (wMagic) {
    case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
        is64 = false; //X86
        break;
    case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
        is64 = true; //X64
        break;
    default:
        xcl_log("该文件不是一个可执行映像");
        break;
    }
    UnmapViewOfFile(ImageBase); CloseHandle(hMapping); CloseHandle(hFile);
    return is64;
}

//文件_文件名是否可用
bool X_File_FileNameAvailable(CXText fileName) {
    int dwLen = fileName.size();
    if (dwLen > _MAX_PATH) { return false; }
    CXVector<CXText>aryChar;
    bool r=true;
    dwLen = X_String_SplitWitNum(L"\\/:*?\"<>|", aryChar);
    for (int i = 0; i < dwLen;i++) {
        if (fileName.find(aryChar[i]) !=std::wstring::npos) {
            r = false;
            break;
        }
    }
    return r;
}
//文件_文件名是否可用A
bool X_File_FileNameAvailableA(CXTextA fileName) {
    int dwLen = fileName.size();
    if (dwLen > MAX_PATH) { return false; }
    CXVector<CXTextA>aryChar;
    bool r=true;
    dwLen = X_String_SplitWitNumA("\\/:*?\"<>|", aryChar);
    for (int i = 0; i < dwLen; i++) {
        if (fileName.find(aryChar[i]) != std::string::npos) {
            r = false;
            break;
        }
    }
    return r;
}

//文件_相差数W
int X_File_GetFileDifferNum(CXText ServerDir, CXText LocalDir) {
    if (ServerDir.size() < 2 || LocalDir.size() < 2) { return 0; }
    CXText sDir = ServerDir;
    CXText lDir = LocalDir;
    if (lDir[lDir.size() - 1] != L'\\') { lDir += L'\\'; }
    if (sDir[sDir.size() - 1] != L'\\') { sDir += L'\\'; }
    WIN32_FIND_DATAW FindData;
    CXText l_name = sDir + L"*.*";
    HANDLE hFind = FindFirstFileW(l_name, &FindData);
    int ds = 0;
    do {
        if (lstrcmpW(FindData.cFileName, L".") == 0 || lstrcmpW(FindData.cFileName, L"..") == 0) {
            continue;
        }
        if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
            //DIR
            ds+=X_File_GetFileDifferNum(sDir + FindData.cFileName, lDir + FindData.cFileName);
            continue;
        }
        l_name = lDir + FindData.cFileName;
        if (!X_Files_FileIfIsSet(l_name)) { ds += 1; }
    } while (FindNextFileW(hFind, &FindData));
    FindClose(hFind);
    return ds;
}
//文件_相差数A
int X_File_GetFileDifferNumA(CXTextA ServerDir, CXTextA LocalDir) {
    if (ServerDir.size() < 2 || LocalDir.size() < 2) { return 0; }
    CXTextA sDir = ServerDir;
    CXTextA lDir = LocalDir;
    if (lDir[lDir.size() - 1] != '\\') { lDir += '\\'; }
    if (sDir[sDir.size() - 1] != '\\') { sDir += '\\'; }
    WIN32_FIND_DATAA FindData;
    CXTextA l_name = sDir + "*.*";
    HANDLE hFind = FindFirstFileA(l_name, &FindData);
    int ds = 0;
    do {
        if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0) {
            continue;
        }
        if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
            //DIR
            ds += X_File_GetFileDifferNumA(sDir + FindData.cFileName, lDir + FindData.cFileName);
            continue;
        }
        l_name = lDir + FindData.cFileName;
        if (!X_Files_FileIfIsSetA(l_name)) { ds += 1; }
    } while (FindNextFileA(hFind, &FindData));
    FindClose(hFind);
    return ds;
}

//文件_移除属性W
bool X_File_FileRemoveAttribute(CXText filePath, DWORD delAttribute) {
    DWORD dwFileAttributes = GetFileAttributesW(filePath);
    dwFileAttributes = dwFileAttributes|~delAttribute;
    return SetFileAttributesW(filePath, dwFileAttributes)>0;
}
//文件_移除属性A
bool X_File_FileRemoveAttributeA(CXTextA filePath, DWORD delAttribute) {
    DWORD dwFileAttributes = GetFileAttributesA(filePath);
    dwFileAttributes = dwFileAttributes | ~delAttribute;
    return SetFileAttributesA(filePath, dwFileAttributes)>0;
}

//文件_移动W
bool X_File_FileMove(CXText filePath, CXText newFile) {
    return MoveFileW(filePath, newFile)>0;
}
//文件_移动A
bool X_File_FileMoveA(CXTextA filePath, CXTextA newFile) {
    return MoveFileA(filePath, newFile) > 0;
}

//文件_执行W
bool X_File_FileExecute(CXText fileName, CXText Commend, int windType) {
    DWORD nShowCmd ;
    DWORD dl[] = { SW_SHOWNORMAL, SW_HIDE, SW_SHOWMINNOACTIVE, SW_SHOWMAXIMIZED };
    if (windType < 0 || windType>3) {
        nShowCmd = SW_SHOWNORMAL;
    }
    else {
        nShowCmd=dl[windType];
    }
    return ShellExecuteW(NULL, L"Open", fileName, Commend, L"", nShowCmd) != (HINSTANCE)ERROR_FILE_NOT_FOUND;
}
//文件_执行A
bool X_File_FileExecuteA(CXTextA fileName, CXTextA Commend, int windType) {
    DWORD nShowCmd;
    DWORD dl[] = { SW_SHOWNORMAL, SW_HIDE, SW_SHOWMINNOACTIVE, SW_SHOWMAXIMIZED };
    if (windType < 0 || windType>3) {
        nShowCmd = SW_SHOWNORMAL;
    }
    else {
        nShowCmd = dl[windType];
    }
    return ShellExecuteA(NULL, "Open", fileName, Commend, "", nShowCmd) != (HINSTANCE)ERROR_FILE_NOT_FOUND;
}

//文件_置时间W
bool X_File_SetFileTime(CXText filePath,CDateTimeTM CreateTime) {
    DWORD dwFlags;
    if(X_Files_FileIsDir(filePath)){ dwFlags=FILE_FLAG_BACKUP_SEMANTICS; }
    HANDLE hFile = CreateFileW(filePath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, dwFlags, 0);
    if (hFile == INVALID_HANDLE_VALUE) { return false; }
    time_t ct=mktime(&CreateTime.m_tm);
    FILETIME fct;
	xcl_timeToFileTime(ct,fct);
    auto isRes = SetFileTime(hFile, &fct, NULL, NULL);
    CloseHandle(hFile);
    return isRes>0;
}
//文件_置时间W
bool X_File_SetFileTime(CXText filePath, 
    CDateTimeTM CreateTime,
    CDateTimeTM AccessTime) {
    DWORD dwFlags;
    if (X_Files_FileIsDir(filePath)) { dwFlags = FILE_FLAG_BACKUP_SEMANTICS; }
    HANDLE hFile = CreateFileW(filePath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, dwFlags, 0);
    if (hFile == INVALID_HANDLE_VALUE) { return false; }
    time_t ct = mktime(&CreateTime.m_tm);
    FILETIME fct;
	xcl_timeToFileTime(ct, fct);
    time_t at = mktime(&AccessTime.m_tm);
    FILETIME fat;
	xcl_timeToFileTime(at, fat);
    auto isRes = SetFileTime(hFile, &fct, &fat, NULL);
    CloseHandle(hFile);
    return isRes > 0;
}
//文件_置时间W
bool X_File_SetFileTime(CXText filePath,
    CDateTimeTM CreateTime,
    CDateTimeTM AccessTime,
    CDateTimeTM WriteTime) {
    DWORD dwFlags;
    if (X_Files_FileIsDir(filePath)) { dwFlags = FILE_FLAG_BACKUP_SEMANTICS; }
    HANDLE hFile = CreateFileW(filePath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, dwFlags, 0);
    if (hFile == INVALID_HANDLE_VALUE) { return false; }
    time_t ct = mktime(&CreateTime.m_tm);
    FILETIME fct;
	xcl_timeToFileTime(ct, fct);
    time_t at = mktime(&AccessTime.m_tm);
    FILETIME fat;
	xcl_timeToFileTime(at, fat);
    time_t wt = mktime(&WriteTime.m_tm);
    FILETIME fwt;
	xcl_timeToFileTime(wt, fwt);
    auto isRes = SetFileTime(hFile, &fct, &fat, &fwt);
    CloseHandle(hFile);
    return isRes > 0;
}
//文件_置时间A
bool X_File_SetFileTimeA(CXTextA filePath, CDateTimeTM CreateTime) {
    DWORD dwFlags;
    if (X_Files_FileIsDirA(filePath)) { dwFlags = FILE_FLAG_BACKUP_SEMANTICS; }
    HANDLE hFile = CreateFileA(filePath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, dwFlags, 0);
    if (hFile == INVALID_HANDLE_VALUE) { return false; }
    time_t ct = mktime(&CreateTime.m_tm);
    FILETIME fct;
	xcl_timeToFileTime(ct, fct); //X_Time_TimetToFileTime(ct, &fct);
    auto isRes = SetFileTime(hFile, &fct, NULL, NULL);
    CloseHandle(hFile);
    return isRes > 0;
}
//文件_置时间A
bool X_File_SetFileTimeA(CXTextA filePath,
    CDateTimeTM CreateTime,
    CDateTimeTM AccessTime) {
    DWORD dwFlags;
    if (X_Files_FileIsDirA(filePath)) { dwFlags = FILE_FLAG_BACKUP_SEMANTICS; }
    HANDLE hFile = CreateFileA(filePath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, dwFlags, 0);
    if (hFile == INVALID_HANDLE_VALUE) { return false; }
    time_t ct = mktime(&CreateTime.m_tm);


    FILETIME fct;
	xcl_timeToFileTime(ct, fct); //X_Time_TimetToFileTime(ct, &fct);
    time_t at = mktime(&AccessTime.m_tm);
    FILETIME fat;
	xcl_timeToFileTime(at, fat); // X_Time_TimetToFileTime(at, &fat);
    auto isRes = SetFileTime(hFile, &fct, &fat, NULL);
    CloseHandle(hFile);
    return isRes > 0;
}
//文件_置时间W
bool X_File_SetFileTimeA(CXTextA filePath,
    CDateTimeTM CreateTime,
    CDateTimeTM AccessTime,
    CDateTimeTM WriteTime) {
    DWORD dwFlags;
    if (X_Files_FileIsDirA(filePath)) { dwFlags = FILE_FLAG_BACKUP_SEMANTICS; }
    HANDLE hFile = CreateFileA(filePath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, dwFlags, 0);
    if (hFile == INVALID_HANDLE_VALUE) { return false; }
    time_t ct = mktime(&CreateTime.m_tm);
    FILETIME fct;
	xcl_timeToFileTime(ct, fct);
    time_t at = mktime(&AccessTime.m_tm);
    FILETIME fat;
	xcl_timeToFileTime(at, fat);
    time_t wt = mktime(&WriteTime.m_tm);
    FILETIME fwt;
	xcl_timeToFileTime(wt, fwt);
    auto isRes = SetFileTime(hFile, &fct, &fat, &fwt);
    CloseHandle(hFile);
    return isRes > 0;
}

//文件_重启电脑后替换W
bool X_File_MoveFileOnReboot(CXText oldFile, CXText newFile,bool removeOldFile) {
    if (removeOldFile) { MoveFileExW(oldFile,NULL, MOVEFILE_DELAY_UNTIL_REBOOT); }
    return MoveFileExW(oldFile, newFile, MOVEFILE_DELAY_UNTIL_REBOOT)>0;
}
//文件_重启电脑后替换A
bool X_File_MoveFileOnRebootA(CXTextA oldFile, CXTextA newFile, bool removeOldFile) {
    if (removeOldFile) { MoveFileExA(oldFile, NULL, MOVEFILE_DELAY_UNTIL_REBOOT); }
    return MoveFileExA(oldFile, newFile, MOVEFILE_DELAY_UNTIL_REBOOT) > 0;
}