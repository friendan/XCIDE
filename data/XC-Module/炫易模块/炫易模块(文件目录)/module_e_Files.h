#pragma once
// Created by Huiyi on 2021/4/20.
//
//@模块名称 炫易模块(文件目录)
//@版本   1.3
//@日期   2022-10-05
//@作者   Huiyi
//@模块备注 封装文件系统相关函数
//项目gitee地址 https://gitee.com/LoveA/XL_XExpand
//大部分代码已经历过粗略测试
//如发现BUG可提交issues
//https://gitee.com/LoveA/XL_XExpand/issues
//反馈QQ群:594165459

//@依赖   module_base.h,module_com.h, module_yyy.h, module_e_crypto.h, module_e_md5.h

#ifndef XL_XEXPAND_FILES_H
//@隐藏{
#define XL_XEXPAND_FILES_H    //防止复用

//#if XC_MODULE
#include "module_base.h"
#include "module_com.h"
#include "module_yyy.h"
//#endif

#include <dbghelp.h>
#include <winver.h>
#include "times.h"
#pragma  comment(lib, "Version.lib")
#pragma  comment(lib, "Urlmon.lib")


//@隐藏}

//@src  "times.cpp"
//@src  "FileDir.cpp"


// TODO: 文件目录
//@分组{  文件目录

//@返回   返回指定文件的版本号
//@别名   文件_取文件版本A (文件路径)
CXTextA X_File_GetFileVersionA(CXTextA szModuleName);
//@返回   返回指定文件的版本号
//@别名   文件_取文件版本 (文件路径)
CXText X_File_GetFileVersion(CXText szModuleName);

//@备注   检测最后一个字符是否为"\"如果不是则加上，某些支持库或组件要求必须结尾有\等符号才能识别为目录
//@参数   传入要检测和处理的目录路径
//@别名   目录_处理A(要处理的目录)
CXTextA X_Files_DirHandleA(CXTextA dirName);
//@备注   检测最后一个字符是否为"\"如果不是则加上，某些支持库或组件要求必须结尾有\等符号才能识别为目录
//@参数   传入要检测和处理的目录路径
//@别名   目录_处理(要处理的目录)
CXText X_Files_DirHandle(CXText dirName);

//@备注   创建多级目录
//@别名   目录_创建A(目录名)
bool X_Files_DirCreateA(CXTextA dirName);
//@备注   创建多级目录
//@别名   目录_创建(目录名)
bool X_Files_DirCreate(CXText dirName);

//@别名   目录_是否存在A(目录名)
bool X_Files_DirTfSetA(CXTextA dirName);
//@别名   目录_是否存在(目录名)
bool X_Files_DirTfSet(CXText dirName);

//@备注   复制目录到指定的路径(需要自行初始化COM)
//@参数   如：C:\001\002
//@参数   复制至：d:\2543\545
//@别名   目录_复制(源目录,目标目录)
bool X_Files_DirCopy(CXText sourceFile, CXText targetFile);
//@备注   复制目录到指定的路径(需要自行初始化COM)
//@参数   如：C:\001\002
//@参数   复制至：d:\2543\545
//@别名   目录_复制A(源目录,目标目录)
bool X_Files_DirCopyA(CXTextA sourceFile, CXTextA targetFile);

//@备注   成功则打开文件所在目录并选中文件，失败返回假
//@别名   目录_定位A(欲定位的目录,编辑模式)
bool X_Files_DirLocationA(CXTextA dirName, bool editMode = false);
//@备注   成功则打开文件所在目录并选中文件，失败返回假
//@别名   目录_定位(欲定位的目录,编辑模式)
bool X_Files_DirLocation(CXText dirName, bool editMode = false);

//@别名   目录_改名A(原目录,新目录)
bool X_Files_DirRenameA(CXTextA oldDir, CXTextA newDir);
//@别名   目录_改名(原目录,新目录)
bool X_Files_DirRename(CXText oldDir, CXText newDir);

//@备注   把某个目录下的所有文件复制到另一个目录里
//@参数   源目录，目录不以\结尾会自动添加
//@参数   目标目录，目录不以\结尾会自动添加
//@参数   可空。默认为直接覆盖
//@别名   目录_更新(源目录,目标目录,是否覆盖文件)
void X_Files_DirUpdate(CXText sourceFile, CXText targetFile, bool cover = true);
//@备注   把某个目录下的所有文件复制到另一个目录里
//@参数   源目录，目录不以\结尾会自动添加
//@参数   目标目录，目录不以\结尾会自动添加
//@参数   可空。默认为直接覆盖
//@别名   目录_更新A(源目录,目标目录,是否覆盖文件)
void X_Files_DirUpdateA(CXTextA sourceFile, CXTextA targetFile, bool cover = true);

//@备注   检索指定文件的完整路径和文件名
//@别名   目录_获取完整路径名称(文件名)
CXText X_Files_DirGetFullPathName(CXText fileName);
//@备注   检索指定文件的完整路径和文件名
//@别名   目录_获取完整路径名称A(文件名)
CXTextA X_Files_DirGetFullPathNameA(CXTextA fileName);

//@别名   目录_监控文件修改(要监视的目录的完整路径,监视整个目录树)
void X_Files_DirMonitoringChanges(CXText changeDir, bool bWatchSubtree = false);
//@别名   目录_监控文件修改A(要监视的目录的完整路径,监视整个目录树)
void X_Files_DirMonitoringChangesA(CXTextA changeDir, bool bWatchSubtree = false);

//@备注   有系统属性返回真，没有返回假
//@别名   目录_检查系统属性A(目录名)
bool X_Files_DirPathIsSystemFolderA(CXTextA pathName);
//@备注   有系统属性返回真，没有返回假
//@别名   目录_检查系统属性(目录名)
bool X_Files_DirPathIsSystemFolder(CXText pathName);

//@备注   通过csidl值标识检索文件的显示名称(需要自行初始化COM)
//@参数   常量_CSIDL_
//@别名   目录_检索文件的显示名称A(csidl)
CXTextA X_Files_DirSHGetFileNameA(int csidl);
//@备注   通过csidl值标识检索文件的显示名称(需要自行初始化COM)
//@参数   常量_CSIDL_
//@别名   目录_检索文件的显示名称(csidl)
CXText X_Files_DirSHGetFileName(int csidl);

//@别名   目录_浏览(标题,显示文件,初始目录,地址栏,新样式,父窗口句柄)
CXText X_Files_DirBrowseForFolder(CXText title = L"请选择一个文件夹",
    bool showFiles = false, CXText initialDirectory = L"",
    bool addressBar = false, bool newStyle = false, HWND phWnd = 0);
//@别名   目录_浏览A(标题,显示文件,初始目录,地址栏,新样式,父窗口句柄)
CXTextA X_Files_DirBrowseForFolderA(CXTextA title = "请选择一个文件夹",
    bool showFiles = false, CXTextA initialDirectory = "",
    bool addressBar = false, bool newStyle = false, HWND phWnd = 0);

//@备注   取一个文件夹下级子目录.成功返回子目录数量,失败返回0.
//@参数   如：D:\Program Files；目录分割符请用\，路径不以\结尾会自动添加
//@参数   用来装载返回的子目录路径
//@参数   假=不带，真=带
//@参数   为真时枚举所有目录,默认不枚举
//@参数   默认为假；真=按字母a-z排序  假=不排序
//@别名   目录_枚举子目录A(父文件夹路径,子目录数组,是否带路径,继续向下枚举,是否按字母排序)
int X_Files_DirEnumDirListA(CXTextA parentPath, CXVector<CXTextA>& retList, bool addPath = false, bool enume = false, bool isSort = false);
//@备注   取一个文件夹下级子目录.成功返回子目录数量,失败返回0.
//@参数   如：D:\Program Files；目录分割符请用\，路径不以\结尾会自动添加
//@参数   用来装载返回的子目录路径
//@参数   假=不带，真=带
//@参数   默认为假；真=按字母a-z排序  假=不排序
//@别名   目录_枚举子目录(父文件夹路径,子目录数组,是否带路径,是否按字母排序)
int X_Files_DirEnumDirList(CXText parentPath, CXVector<CXText>& retList, bool addPath = false, bool enume = false, bool isSort = false);

//@备注   【严格】检查目录是否合规范，不和规范的目录返回假。判断标准:盘符:\目录
//@参数   需要检查的完整的目录路径，不接受相对路径
//@参数   如果设置为真，如果是盘符根目录返回假。默认为真。
//@别名   目录_是否符合规范(要检查的目录,是否禁止为根目录)
bool X_File_DirIsItNormative(CXText dirName, bool banRootPath = true);
//@备注   【严格】检查目录是否合规范，不和规范的目录返回假。判断标准:盘符:\目录
//@参数   要检查的目录  需要检查的完整的目录路径，不接受相对路径
//@参数   是否禁止为根目录  如果设置为真，如果是盘符根目录返回假。默认为真。
//@别名   目录_是否符合规范A(要检查的目录,是否禁止为根目录)
bool X_File_DirIsItNormativeA(CXTextA dirName, bool banRootPath = true);

//@备注   删除一个存在的目录及其中的所有子目录和下属文件
//@别名   目录_删除目录(欲删除的目录)
bool X_Files_DirRemove(CXText dirName);
//@备注   删除一个存在的目录及其中的所有子目录和下属文件
//@别名   目录_删除目录A(欲删除的目录)
bool X_Files_DirRemoveA(CXTextA dirName);

//@备注   删除指定目录下所有文件，包括文件夹
//@参数   欲清空的目录  如：删除D:\Program Files(也就是Program Files)目录下的全部文件；，目录不以\结尾会自动添加
//@别名   目录_强力清空(欲清空的目录)
void X_Files_DirRemovePro(CXText dirName);
//@备注   删除指定目录下所有文件，包括文件夹
//@参数   欲清空的目录  如：删除D:\Program Files(也就是Program Files)目录下的全部文件；，目录不以\结尾会自动添加
//@别名   目录_强力清空A(欲清空的目录)
void X_Files_DirRemoveProA(CXTextA dirName);

//@备注   删除指定目录下所有文件，子目录或子目录下的文件不会被删除(部分情况下需要自行初始化COM)
//@参数   要删除文件的目录    如：删除D:\Program Files(也就是Program Files)目录下的全部文件，目录不以\结尾会自动添加
//@参数   文件类型    默认为清空所有文件；或者清空指定格式(*.txt或*.exe)等等
//@别名   目录_清空(要删除文件的目录,文件类型)
void X_Files_DirEmpty(CXText dirName, CXText fileType = L"*.*");
//@备注   删除指定目录下所有文件，子目录或子目录下的文件不会被删除(部分情况下需要自行初始化COM)
//@参数   要删除文件的目录    如：删除D:\Program Files(也就是Program Files)目录下的全部文件，目录不以\结尾会自动添加
//@参数   文件类型    默认为清空所有文件；或者清空指定格式(*.txt或*.exe)等等
//@别名   目录_清空A(要删除文件的目录,文件类型)
void X_Files_DirEmptyA(CXTextA dirName, CXTextA fileType = "*.*");

//@备注   本命令返回指定的Windows系统特定目录，所返回目录名以“\”符号结束，如失败返回空文本(部分情况下需要自行初始化COM)
//@参数   欲获取目录类型 留空为桌面，参见常量: 常量_特定目录_/GIVENDIR_
//@参数   csidl 常量_CSIDL_/CSIDL_* 不为空时 欲获取目录类型 视为无效
//@别名   目录_取特定目录(欲获取目录类型,csidl)
CXText X_Files_GetGivenDir(int dirType, int csidl = -1);
//@备注   本命令返回指定的Windows系统特定目录，所返回目录名以“\”符号结束，如失败返回空文本(部分情况下需要自行初始化COM)
//@参数   欲获取目录类型 留空为桌面，参见常量: 常量_特定目录_/GIVENDIR_
//@参数   csidl 常量_CSIDL_/CSIDL_* 不为空时 欲获取目录类型 视为无效
//@别名   目录_取特定目录A(欲获取目录类型,csidl)
CXTextA X_Files_GetGivenDirA(int dirType, int csidl = -1);

//@备注   (部分情况下需要自行初始化COM)
//@返回   如C:\WINDOWS\system32
//@别名   目录_取system32目录()
CXText X_Files_GetSystem32Path();
//@备注   (部分情况下需要自行初始化COM)
//@返回   如C:\WINDOWS\system32
//@别名   目录_取system32目录A()
CXTextA X_Files_GetSystem32PathA();

//@备注   (部分情况下需要自行初始化COM)
//@返回   如C:\WINDOWS
//@别名   目录_取Windows目录()
CXText X_Files_GetWindowsPath();
//@备注   (部分情况下需要自行初始化COM)
//@返回   如C:\WINDOWS
//@别名   目录_取Windows目录A()
CXTextA X_Files_GetWindowsPathA();

//@备注   取x86的system文件夹(部分情况下需要自行初始化COM)
//@返回   如C:\WINDOWS\SysWOW64
//@别名   目录_取x86系统目录()
CXText X_Files_GetSystemX86Path();
//@备注   取x86的system文件夹(部分情况下需要自行初始化COM)
//@返回   如C:\WINDOWS\SysWOW64
//@别名   目录_取x86系统目录A(目录路径)
CXTextA X_Files_GetSystemX86PathA();

//@返回   返回创建的时间
//@别名   目录_取创建时间(目录路径)
CDateTimeTM X_Files_GetDirCreateTime(CXText dirName);
//@返回   返回创建的时间
//@别名   目录_取创建时间A(目录路径)
CDateTimeTM X_Files_GetDirCreateTimeA(CXTextA dirName);

//@备注   遍历目录计算尺寸,文件过多可能导致计算缓慢
//@别名   目录_取大小(目录路径)
INT64 X_Files_GetDirSize(CXText dirName);
//@备注   遍历目录计算尺寸,文件过多可能导致计算缓慢
//@别名   目录_取大小A(目录路径)
INT64 X_Files_GetDirSizeA(CXTextA dirName);

//@返回   成功返回当前目录
//@别名   目录_取当前目录()
CXText X_Files_GetCurrentDir();
//@返回   成功返回当前目录
//@别名   目录_取当前目录A()
CXTextA X_Files_GetCurrentDirA();

//@返回   返回指定文件或目录的上一级目录路径；路径后面包含\
//@参数   文件或目录名 如：C:\001\002\0.txt则返回C:\001\002\；
//@别名   目录_取父路径(文件或目录名)
CXText X_Files_GetFatherDir(CXText dirPath);
//@返回   返回指定文件或目录的上一级目录路径；路径后面包含\
//@参数   文件或目录名 如：C:\001\002\0.txt则返回C:\001\002\；
//@别名   目录_取父路径A(文件或目录名)
CXTextA X_Files_GetFatherDirA(CXTextA dirPath);

//@备注   取出Temp目录
//@返回   如:C:\DOUME~1\ADMINI~1\LOALS~1\Temp\
//@别名   目录_取临时目录()
CXText X_Files_GetSystemTempDir();
//@备注   取出Temp目录
//@返回   如:C:\DOUME~1\ADMINI~1\LOALS~1\Temp\
//@别名   目录_取临时目录A()
CXTextA X_Files_GetSystemTempDirA();

//@返回   如果是目录: C:\001\002 则返回 002；  如果是文件: C:\001\002\0.txt 则返回 0.txt
//@参数   如果参数尾部包含\,将会被去掉
//@别名   目录_取尾部目录名或文件名(文件或目录名)
CXText X_Files_GetPathTailNameOrFileName(CXText pathName);
//@返回   如果是目录: C:\001\002 则返回 002；  如果是文件: C:\001\002\0.txt 则返回 0.txt
//@参数   如果参数尾部包含\,将会被去掉
//@别名   目录_取尾部目录名或文件名A(文件或目录名)
CXTextA X_Files_GetPathTailNameOrFileNameA(CXTextA pathName);

//@参数   使用FileSystemObject取目录文件数, 适合有大量文件的目录(需要自行初始化COM)
//@别名   目录_取文件数(目录名)
int X_Files_GetDirFileNum(CXText pathName);
//@参数   使用FileSystemObject取目录文件数, 适合有大量文件的目录(需要自行初始化COM)
//@别名   目录_取文件数A(目录名)
int X_Files_GetDirFileNumA(CXTextA pathName);

//@别名   目录_取消系统属性(目录名)
bool X_Files_PathUnmakeSystemFolder(CXText dirName);
//@别名   目录_取消系统属性A(目录名)
bool X_Files_PathUnmakeSystemFolderA(CXTextA dirName);

//@备注   给一个文件夹正确的属性，成为一个系统文件夹
//@别名   目录_设置系统属性(目录名)
bool X_Files_PathMakeSystemFolder(CXText dirName);
//@备注   给一个文件夹正确的属性，成为一个系统文件夹
//@别名   目录_设置系统属性A(目录名)
bool X_Files_PathMakeSystemFolderA(CXTextA dirName);

//@备注   获取系统桌面的路径
//@别名   目录_取桌面目录()
CXText X_Files_GetDesktopDir();
//@备注   获取系统桌面的路径
//@别名   目录_取桌面目录A()
CXTextA X_Files_GetDesktopDirA();

//@参数   取一个文件夹下面的子目录数量(需要自行初始化COM)
//@别名   目录_取子目录数(父文件夹路径)
int X_Files_GetSonDirNum(CXText pathName);
//@参数   取一个文件夹下面的子目录数量(需要自行初始化COM)
//@别名   目录_取子目录数A(父文件夹路径)
int X_Files_GetSonDirNumA(CXTextA pathName);

//@别名   目录_是否为空(欲判断的目录路径)
bool X_Files_IsItEmpty(CXText dirName);
//@别名   目录_是否为空A(欲判断的目录路径)
bool X_Files_IsItEmptyA(CXTextA dirName);

//@备注   判断一个目录下有无下级子目录
//@别名   目录_是否有子目录(当前目录)
bool X_Files_WhetherSonDir(CXText dirName);
//@备注   判断一个目录下有无下级子目录
//@别名   目录_是否有子目录A(当前目录)
bool X_Files_WhetherSonDirA(CXTextA dirName);

//@备注   将目标目录的文件和源目录中的文件进行对比，将不同的文件同步到目标目录里
//@参数   源目录 源目录，目录不以\结尾会自动添加
//@参数   目标目录 欲更新目标的目录，目录不以\结尾会自动添加
//@别名   目录_同步更新(源目录,目标目录)
void X_Files_DirSyncUpdate(CXText sourcePath, CXText targetPath);


//------

//@备注   成功则打开文件所在目录并选中文件，失败返回假(需要自行初始化COM)
//@别名   文件_定位A(欲定位的文件,编辑模式)
bool X_Files_FileLocationA(CXTextA fileName, bool editMode = false);
//@备注   成功则打开文件所在目录并选中文件，失败返回假(需要自行初始化COM)
//@别名   文件_定位(欲定位的文件,编辑模式)
bool X_Files_FileLocation(CXText fileName, bool editMode = false);

//@别名   文件_改名A(原文件名,新文件名)
bool X_Files_FileRenameA(CXTextA oldFile, CXTextA newFile);
//@别名   文件_改名(原文件名,新文件名)
bool X_Files_FileRename(CXText oldFile, CXText newFile);

//@备注   成功返回真，失败返回假
//@参数   被复制文件名
//@参数   复制到文件名
//@参数   可空。默认为直接覆盖
//@别名   文件_复制A(原文件,新文件,是否覆盖文件)
bool X_Files_FileCopyA(CXTextA oldFile, CXTextA newFile, bool cover = true);
//@备注   成功返回真，失败返回假
//@参数   被复制文件名
//@参数   复制到文件名
//@参数   可空。默认为直接覆盖
//@别名   文件_复制(原文件,新文件,是否覆盖文件)
bool X_Files_FileCopy(CXText oldFile, CXText newFile, bool cover = true);

//@备注   复制、移动、重命名或删除文件系统对象(需要自行初始化COM)
//@参数   命令类型            1、移动；2、复制；3、删除；4、重命名
//@参数   源文件名            操作文件名
//@参数   目标文件或目录名称   目录名称
//@参数   文件操作选项        1、不询问；2、不提示；4、不显示进度
//@别名   文件_文件操作(命令类型,源文件名,目标文件或目录名称,文件操作选项)
bool X_Files_FileOperation(int CommendType, CXText fileName, CXText targetDir = L"", int fileOption = 0);
//@备注   复制、移动、重命名或删除文件系统对象(需要自行初始化COM)
//@参数   命令类型            1、移动；2、复制；3、删除；4、重命名
//@参数   源文件名            操作文件名
//@参数   目标文件或目录名称   目录名称
//@参数   文件操作选项        1、不询问；2、不提示；4、不显示进度
//@别名   文件_文件操作A(命令类型,源文件名,目标文件或目录名称,文件操作选项)
bool X_Files_FileOperationA(int CommendType, CXTextA fileName, CXTextA targetDir = "", int fileOption = 0);

//@备注   将指定文件删除到回收站,成功返回真,失败返回假
//@参数   欲删除的文件名  欲删除的全路径文件名
//@参数   删除方式选项    1: 不询问删除;  2: 不提示错误;  4: 不显示进度。如果被省略，默认值为 0 
//@别名   文件_删除到回收站(欲删除的文件名,删除方式选项)
bool X_Files_FileDelToRecycle(CXText fileName, int delType = 0);
//@备注   将指定文件删除到回收站,成功返回真,失败返回假
//@参数   欲删除的文件名  欲删除的全路径文件名
//@参数   删除方式选项    1: 不询问删除;  2: 不提示错误;  4: 不显示进度。如果被省略，默认值为 0 
//@别名   文件_删除到回收站A(欲删除的文件名,删除方式选项)
bool X_Files_FileDelToRecycleA(CXTextA fileName, int delType = 0);

//@备注   枚举某个目录下的指定类型文件；成功返回文件数量
//@参数   欲寻找的目录  文件目录
//@参数   文件数组     用于装载文件数组的变量；把寻找到的文件都放在这个数组里，并返回；
//@参数   欲寻找的文件名 如果寻找全部文件可以填入*.*，或*.txt只找txt文件, 多个后缀中间用“|”隔开
//@参数   是否带路径   默认为假； 真=带目录路径，如C:\012.txt； 假=不带，如 012.txt；
//@参数   是否按字母排序 默认为假；真=按字母a-z排序  假=不排序
//@参数   是否遍历子目录 留空默认为假；为真时文件数组不主动清空
//@别名   文件_枚举(欲寻找的目录,文件数组,欲寻找的文件名,是否带路径,是否按字母排序,是否遍历子目录)
int X_Files_FileEnums(CXText dirName, CXVector<CXText>& rFileList, CXText fileName = L"*.*", bool addPath = false, bool sort = false, bool enumSon = false);
//@备注   枚举某个目录下的指定类型文件；成功返回文件数量
//@参数   欲寻找的目录  文件目录
//@参数   欲寻找的文件名 如果寻找全部文件可以填入*.*，或*.txt只找txt文件, 多个后缀中间用“|”隔开
//@参数   文件数组    用于装载文件数组的变量；把寻找到的文件都放在这个数组里，并返回；
//@参数   是否带路径   默认为假； 真=带目录路径，如C:\012.txt； 假=不带，如 012.txt；
//@参数   是否按字母排序 默认为假；真=按字母a-z排序  假=不排序
//@参数   是否遍历子目录 留空默认为假；为真时文件数组不主动清空
//@别名   文件_枚举A(欲寻找的目录,文件数组,欲寻找的文件名,是否带路径,是否按字母排序,是否遍历子目录)
int X_Files_FileEnumsA(CXTextA dirName, CXVector<CXTextA>& rFileList, CXTextA fileName = "*.*",
    bool addPath = false, bool sort = false, bool enumSon = false);

//@返回   返回一个文件的后缀名, 如：.jpg  如果没有后缀, 返回空
//@别名   文件_取扩展名(文件名)
CXText X_Files_GetFileExtension(CXText fileName);
//@返回   返回一个文件的后缀名, 如：.jpg  如果没有后缀, 返回空
//@别名   文件_取扩展名A(文件名)
CXTextA X_Files_GetFileExtensionA(CXTextA fileName);

//@备注   判断指定的文件是否存在
//@别名   文件_是否存在(文件名)
bool X_Files_FileIfIsSet(CXText fileName);
//@备注   判断指定的文件是否存在
//@别名   文件_是否存在A(文件名)
bool X_Files_FileIfIsSetA(CXTextA fileName);

//@备注   将文件读入到内存,注意：为维持文件原始结构,底层为单字节,如果是文本文件请使用 取文本指针A()
//@返回   返回字节集接收尺寸(文件尺寸)
//@别名   文件_读入文件(文件名,返回字节集)
int X_Files_ReadFile(CXText fileName, CXBytes& fileByte);
//@备注   将文件读入到内存,注意：为维持文件原始结构,底层为单字节,如果是文本文件请使用 取文本指针A()
//@返回   返回字节集接收尺寸(文件尺寸)
//@别名   文件_读入文件A(文件名,返回字节集)
int X_Files_ReadFileA(CXTextA fileName, CXBytes& fileByte);

//@参数   遍历可执行映像的PE导出表获取函数名称
//@别名   文件_遍历PE导出表(文件名,导出函数列表)
int X_Files_ErgodicExportTables(CXText fileName, CXVector<CXText>& rExportFuncList);
//@参数   遍历可执行映像的PE导出表获取函数名称
//@别名   文件_遍历PE导出表A(文件名,导出函数列表)
int X_Files_ErgodicExportTablesA(CXTextA fileName, CXVector<CXTextA>& rExportFuncList);

//@参数   遍历可执行映像的PE导入表获取函数名称
//@别名   文件_遍历PE导入表(文件名,导出函数列表)
int X_Files_ErgodicImportTables(CXText fileName, CXVector<CXText>& rExportFuncList);
//@参数   遍历可执行映像的PE导入表获取函数名称
//@别名   文件_遍历PE导入表A(文件名,导出函数列表)
int X_Files_ErgodicImportTablesA(CXTextA fileName, CXVector<CXTextA>& rExportFuncList);

//@备注   判断一个指定的文件路径是否为目录
//@返回   是目录返回真, 不是目录或文件路径不存在返回假
//@别名   文件_是否为目录(文件名)
bool  X_Files_FileIsDir(CXText fileName);
//@备注   判断一个指定的文件路径是否为目录
//@返回   是目录返回真, 不是目录或文件路径不存在返回假
//@别名   文件_是否为目录A(文件名)
bool  X_Files_FileIsDirA(CXTextA fileName);

//@备注   取得文件所在目录的路径
//@返回   如 C:\012\3600.exe 成功将返回 C:\012\
//@别名   文件_取目录(文件名)
CXText X_Files_GetFileDir(CXText fileName);
//@备注   取得文件所在目录的路径
//@返回   如 C:\012\3600.exe 成功将返回 C:\012\
//@别名   文件_取目录A(文件名)
CXTextA X_Files_GetFileDirA(CXTextA fileName);

//@备注   删除指定路径的文件
//@别名   文件_删除(文件名)
bool X_Files_DeleteFile(CXText fileName);
//@备注   删除指定路径的文件
//@别名   文件_删除A(文件名)
bool X_Files_DeleteFileA(CXTextA fileName);

//@备注   瞬间创建一个指定大小的文件
//@别名   文件_创建(文件名,要创建的大小)
bool X_Files_FileCreate(CXText fileName, DWORD fileSize = 0);
//@备注   瞬间创建一个指定大小的文件
//@别名   文件_创建A(文件名,要创建的大小)
bool X_Files_FileCreateA(CXTextA fileName, DWORD fileSize = 0);

//@备注   根据一个文件名创建出该文件名所包含的所有目录
//@别名   文件_创建文件目录(文件名)
bool X_Files_CreateFileDir(CXText fileName);
//@备注   根据一个文件名创建出该文件名所包含的所有目录
//@别名   文件_创建文件目录A(文件名)
bool X_Files_CreateFileDirA(CXTextA fileName);

//@备注   文件必须存在
//@参数   成功返回文件句柄，失败返回-1
//@别名   文件_打开(文件名)
HANDLE X_File_FileOpen(CXText fileName);
//@备注   文件必须存在
//@参数   成功返回文件句柄，失败返回-1
//@别名   文件_打开A(文件名)
HANDLE X_File_FileOpenA(CXTextA fileName);

//@别名   文件_到短文件名(文件名)
CXText X_File_GetShortPathName(CXText fileName);
//@别名   文件_到短文件名A(文件名)
CXTextA X_File_GetShortPathNameA(CXTextA fileName);

//@别名   文件_到长文件名(文件名)
CXText X_File_GetLongPathName(CXText fileName);
//@别名   文件_到长文件名A(文件名)
CXTextA X_File_GetLongPathNameA(CXTextA fileName);

//@备注   成功则打开文件或文件夹所在目录并选中(部分情况下需自行初始化COM)
//@别名   文件_定位多个(所在文件夹,欲定位的文件或文件夹)
bool X_Files_FileLocationMultiples(CXText dirName, CXVector<CXText>fileList);
//@备注   成功则打开文件或文件夹所在目录并选中(部分情况下需自行初始化COM)
//@别名   文件_定位多个A(所在文件夹,欲定位的文件或文件夹)
bool X_Files_FileLocationMultiplesA(CXTextA dirName, CXVector<CXTextA>fileList);

//@备注   改变一个文件的后缀名
//@参数   文件名 需要处理的原始文件名
//@参数   新扩展名 后缀必须包含"."，如“.rar”,否则失败
//@别名   文件_改扩展名(文件名,新扩展名)
bool X_Files_FileRenameExtension(CXText fileName, CXText newExtension);
//@备注   改变一个文件的后缀名
//@参数   文件名 需要处理的原始文件名
//@参数   新扩展名 后缀必须包含"."，如“.rar”,否则失败
//@别名   文件_改扩展名A(文件名,新扩展名)
bool X_Files_FileRenameExtensionA(CXTextA fileName, CXTextA newExtension);

//@备注   关闭后,将文件号设置为0
//@别名   文件_关闭(文件号)
void X_File_FileClose(HANDLE& hFile);

//@隐藏{
//TODO:实现周期过长,延后
//@备注   关联指定后缀名到指定文件 (打开该后缀名文件,该后缀名文件路径将作为参数传递给指定文件)
//@参数   程序路径    可空，关联到程序的路径，如果留空将取消关联
//@参数   后缀  欲关联的后缀名,多个后缀用|分开 (如: asp|htm|html)
//@参数   ICO图标路径 被关联文件的图标 可空为执行文件(程序)图标，也可以直接指向一个其它一个可执行的文件
//@参数   文件类型    关联文件的说明 被关联文件属性中的文件类型
//@参数   关联名 可空为后缀
//@别名   文件_关联(程序路径,后缀,ICO图标路径,文件类型,关联名)
void X_File_FilerRelation(CXText fileName, CXText suffix, CXText ICOPath = L"", CXText fileType = L"", CXText relationName = L"");
//@隐藏}

//@备注   将两个文件进行合并,生成一个新的文件
//@参数   前一个文件名,最后生成的文件名也是它.
//@参数   要追加的文件名.
//@参数   如果空,以第一个文件名为准
//@别名   文件_合并A(合并文件名,被合并文件名,生成文件名)
bool X_File_FileMergeA(CXTextA file1, CXTextA file2, CXTextA newFile = "");
//@备注   将两个文件进行合并,生成一个新的文件
//@参数   前一个文件名,最后生成的文件名也是它.
//@参数   要追加的文件名.
//@参数   如果空,以第一个文件名为准
//@别名   文件_合并(合并文件名,被合并文件名,生成文件名)
bool X_File_FileMerge(CXText file1, CXText file2, CXText newFile = L"");

//@备注   根据文件句柄获取文件所在路径
//@返回   失败返回空文本
//@别名   文件_句柄取路径(文件句柄)
CXText X_File_HendleGetPath(HANDLE hFile);
//@备注   根据文件句柄获取文件所在路径
//@返回   失败返回空文本
//@别名   文件_句柄取路径A(文件句柄)
CXTextA X_File_HendleGetPathA(HANDLE hFile);

//@备注   成功返回MIME类型
//@别名   文件_取MIME类型(文件句柄)
CXText X_File_GetFileMIMEType(CXText fileName);
//@备注   成功返回MIME类型
//@别名   文件_取MIME类型A(文件句柄)
CXTextA X_File_GetFileMIMETypeA(CXTextA fileName);

//@备注   直接取超大文件
//@参数   文件名 文件的完整路径
//@参数   格式化 格式化以B、KB、GB返回
//@别名   文件_取尺寸(文件名,格式化)
CXText X_File_GetFileVolume(CXText fileName, bool format = false);
//@备注   直接取超大文件
//@参数   文件名 文件的完整路径
//@参数   格式化 格式化以B、KB、GB返回
//@别名   文件_取尺寸A(文件名,格式化)
CXTextA X_File_GetFileVolumeA(CXTextA fileName, bool format = false);

//@返回   返回一个文件的长度，单位是字节
//@别名   文件_取大小()
DWORD X_File_GetFileSize(CXText fileName);
//@返回   返回一个文件的长度，单位是字节
//@别名   文件_取大小A()
DWORD X_File_GetFileSizeA(CXTextA fileName);

//@返回   常量_文件类型_ / FILE_TYPR_
//@别名   文件_取格式(文件字节集,返回文本格式)
int X_File_GetFileForm(CXBytes& FileByte, CXText& retFileType);
//@返回   常量_文件类型_ / X_FILE_TYPR_
//@别名   文件_取格式A(文件字节集,返回文本格式)
int X_File_GetFileFormA(CXBytes& FileByte, CXTextA& retFileType);
//@隐藏{
int X_File_GetFileFormA(CXBytes& FileByte);
int X_File_GetFileForm(CXBytes& FileByte);
//@隐藏}

//@返回   取得此后缀文档打开方式，失败则返回空文本
//@参数   文件后缀，如"txt","*.txt",".txt"三者都可以
//@别名   文件_取关联(后缀)
CXText X_File_GetRelation(CXText suffix);
//@返回   取得此后缀文档打开方式，失败则返回空文本
//@参数   文件后缀，如"txt","*.txt",".txt"三者都可以
//@别名   文件_取关联A(后缀)
CXTextA X_File_GetRelationA(CXTextA suffix);

//@备注   获取文件类型(需自行初始化COM库)
//@返回   如.exe文件，则返回“应用程序”，失败则返回空
//@别名   文件_取类型(文件名)
CXText X_File_GetFileType(CXText fileName);
//@备注   获取文件类型(需自行初始化COM库)
//@返回   如.exe文件，则返回“应用程序”，失败则返回空
//@别名   文件_取类型A(文件名)
CXTextA X_File_GetFileTypeA(CXTextA fileName);

//@返回   如 C:\001\002\01\0104.txt 返回 C
//@别名   文件_取路径盘符(文件名)
CXText X_File_GetPathDriveLetter(CXText fileName);
//@返回   如 C:\001\002\01\0104.txt 返回 C
//@别名   文件_取路径盘符A(文件名)
CXTextA X_File_GetPathDriveLetterA(CXTextA fileName);

//@参数   文件名 取时间的文件路径
//@参数   创建时间 存放创建时间的变量
//@参数   最后修改时间 存放最后修改时间的变量
//@参数   最后访问时间 存放最后访问时间的变量
//@别名   文件_取时间(文件名,创建时间,最后修改时间,最后访问时间)
bool X_File_FileGetTime(CXText fileName,
    CDateTimeTM& createTime,
    CDateTimeTM& accessTime,
    CDateTimeTM& writeTime);
//@参数   文件名 取时间的文件路径
//@参数   创建时间 存放创建时间的变量
//@参数   最后修改时间 存放最后修改时间的变量
//@参数   最后访问时间 存放最后访问时间的变量
//@别名   文件_取时间A(文件名,创建时间,最后修改时间,最后访问时间)
bool X_File_FileGetTimeA(CXTextA fileName,
    CDateTimeTM& createTime,
    CDateTimeTM& accessTime,
    CDateTimeTM& writeTime);
//@隐藏{
bool X_File_FileGetTime(CXText fileName, CDateTimeTM& createTime, CDateTimeTM& accessTime);
bool X_File_FileGetTimeA(CXTextA fileName, CDateTimeTM& createTime, CDateTimeTM& accessTime);
bool X_File_FileGetTime(CXText fileName, CDateTimeTM& createTime);
bool X_File_FileGetTimeA(CXTextA fileName, CDateTimeTM& createTime);
bool X_File_FileGetTime(CXText fileName);
bool X_File_FileGetTimeA(CXTextA fileName);
//@隐藏}

//@备注   获取一个文件在磁盘上实际占据的字节数，如文件右键属性中的大小，显示就是实际压缩过的尺寸
//@别名   文件_取真实尺寸(文件名)
ULONGLONG X_File_GetFileRealSize(CXText fileName);
//@备注   获取一个文件在磁盘上实际占据的字节数，如文件右键属性中的大小，显示就是实际压缩过的尺寸
//@别名   文件_取真实尺寸A(文件名)
ULONGLONG X_File_GetFileRealSizeA(CXTextA fileName);

//@返回   返回一个文件或目录的属性。此属性值参考以下常量：常量_文件属性_  / FILE_ATTRIBUTE_ 。要判断是否设置了某个属性，在返回值与想要得知的属性值之间使用“|”运算符进行比较。如果所得的结果不为零，则表示设置了这个属性值。如果取文件属性失败，将返回 -1
//@别名   文件_取属性(文件名)
DWORD X_File_GetFileAttributes(CXText fileName);
//@返回   返回一个文件或目录的属性。此属性值参考以下常量：常量_文件属性_  / FILE_ATTRIBUTE_ 。要判断是否设置了某个属性，在返回值与想要得知的属性值之间使用“|”运算符进行比较。如果所得的结果不为零，则表示设置了这个属性值。如果取文件属性失败，将返回 -1
//@别名   文件_取属性A(文件名)
DWORD X_File_GetFileAttributesA(CXTextA fileName);

//@备注   获取文件的图标句柄(需要自行初始化COM)
//@别名   文件_取图标句柄(文件名)
HANDLE X_File_GetFileIconHand(CXText fileName);
//@备注   获取文件的图标句柄(需要自行初始化COM)
//@别名   文件_取图标句柄A(文件名)
HANDLE X_File_GetFileIconHandA(CXTextA fileName);


//@备注   本命令用作将一个或数个字节集顺序写到指定文件中，文件原有内容被覆盖。成功返回真，失败返回假
//@参数   文件名 欲写入文件的路径
//@参数   欲写入文件的数据
//@别名   文件_写到文件(文件名,欲写入文件的数据)
bool X_File_WriteFile(CXText fileName, CXBytes& filebytes);
//@备注   本命令用作将一个或数个字节集顺序写到指定文件中，文件原有内容被覆盖。成功返回真，失败返回假
//@参数   文件名 欲写入文件的路径
//@参数   欲写入文件的数据
//@别名   文件_写到文件A(文件名,欲写入文件的数据)
bool X_File_WriteFileA(CXTextA fileName, CXBytes& filebytes);

//@返回   如：C:\123.exe 成功返回123
//@别名   文件_取文件名(文件名,带后缀)
CXText X_File_GetFileName(CXText fileName, bool addSuffix = false);
//@返回   如：C:\123.exe 成功返回123
//@别名   文件_取文件名A(文件名,带后缀)
CXTextA X_File_GetFileNameA(CXTextA fileName, bool addSuffix = false);

//@备注   去掉指定文件路径的后缀
//@别名   文件_去扩展名(文件名)
bool X_File_FileDelSuffix(CXText fileName);
//@备注   去掉指定文件路径的后缀
//@别名   文件_去扩展名A(文件名)
bool X_File_FileDelSuffixA(CXTextA fileName);

//@备注   支持通配符删除，写法如：删除文件("局_项数组:\","*.*")
//@返回   返回删除文件总数(有些文件由于某种原因可能未被删除)
//@参数   目录名 最后不带"\",但可自动加上.
//@参数   后缀 如"*.BAT"或“ABC*.INI"，可以使用多字符 (*) 和单字符 (?) 通配符
//@参数   遍历子目录 默认为假，不包含；真，包含。
//@别名   文件_删除某类文件(目录名,后缀,遍历子目录)
int X_File_DelWTypeFiles(CXText dirName, CXText Suffix, bool enumSon = false);
//@备注   支持通配符删除，写法如：删除文件("局_项数组:\","*.*")
//@返回   返回删除文件总数(有些文件由于某种原因可能未被删除)
//@参数   目录名 最后不带"\",但可自动加上.
//@参数   后缀 如"*.BAT"或“ABC*.INI"，可以使用多字符 (*) 和单字符 (?) 通配符
//@参数   遍历子目录 默认为假，不包含；真，包含。
//@别名   文件_删除某类文件A(目录名,后缀,遍历子目录)
int X_File_DelWTypeFilesA(CXTextA dirName, CXTextA Suffix, bool enumSon = false);

//@别名   文件_是否被占用(文件名)
bool X_File_FileWhetItIsLocked(CXText fileName);
//@别名   文件_是否被占用A(文件名)
bool X_File_FileWhetItIsLockedA(CXTextA fileName);

//@参数   判断一个可执行映像是否为64位
//@别名   文件_是否为64位()
bool X_File_FileIfIsX64(CXText fileName);
//@参数   判断一个可执行映像是否为64位
//@别名   文件_是否为64位A()
bool X_File_FileIfIsX64A(CXTextA fileName);

//@别名   文件_文件名是否可用(文件名)
bool X_File_FileNameAvailable(CXText fileName);
//@别名   文件_文件名是否可用A(文件名)
bool X_File_FileNameAvailableA(CXTextA fileName);

//@备注   返回两个目录中相差的文件数
//@别名   文件_相差数(服务器文件夹,本地文件夹)
int X_File_GetFileDifferNum(CXText ServerDir, CXText LocalDir);
//@备注   返回两个目录中相差的文件数
//@别名   文件_相差数A(服务器文件夹,本地文件夹)
int X_File_GetFileDifferNumA(CXTextA ServerDir, CXTextA LocalDir);

//@备注   移除指定文件的属性信息
//@参数   文件路径 文件的绝对路径
//@参数   欲移除的属性值 参见 常量_文件属性_ / FILE_ATTRIBUTE_
//@别名   文件_移除属性(文件路径,欲移除的属性值)
bool X_File_FileRemoveAttribute(CXText filePath, DWORD delAttribute);
//@备注   移除指定文件的属性信息
//@参数   文件路径 文件的绝对路径
//@参数   欲移除的属性值 参见 常量_文件属性_ / FILE_ATTRIBUTE_
//@别名   文件_移除属性A(文件路径,欲移除的属性值)
bool X_File_FileRemoveAttributeA(CXTextA filePath, DWORD delAttribute);

//@备注   移动指定文件到指定的文件位置
//@别名   文件_移动(欲移动的文件名,移动到的文件名)
bool X_File_FileMove(CXText filePath, CXText newFile);
//@备注   移动指定文件到指定的文件位置
//@别名   文件_移动A(欲移动的文件名,移动到的文件名)
bool X_File_FileMoveA(CXTextA filePath, CXTextA newFile);

//@备注   执行文件夹或文件或命令
//@参数   文件名 欲操作(文件)或(文件夹的名称)或(网址)
//@参数   命令行 执行文件的命令行，没有则设为空
//@参数   窗口方式 0、普通激活方式；1、隐藏窗口；2、最小化窗口、3、最大化窗口
//@别名   文件_执行(文件名,命令行,窗口方式)
bool X_File_FileExecute(CXText fileName, CXText Commend = L"", int windType = 0);
//@备注   执行文件夹或文件或命令
//@参数   文件名 欲操作(文件)或(文件夹的名称)或(网址)
//@参数   命令行 执行文件的命令行，没有则设为空
//@参数   窗口方式 0、普通激活方式；1、隐藏窗口；2、最小化窗口、3、最大化窗口
//@别名   文件_执行A(文件名,命令行,窗口方式)
bool X_File_FileExecuteA(CXTextA fileName, CXTextA Commend = "", int windType = 0);


//@别名   文件_置时间(文件名,创建时间,最后修改时间,最后访问时间)
bool X_File_SetFileTime(CXText filePath, CDateTimeTM CreateTime,
    CDateTimeTM AccessTime, CDateTimeTM WriteTime);
//@别名   文件_置时间A(文件名,创建时间,最后修改时间,最后访问时间)
bool X_File_SetFileTimeA(CXTextA filePath, CDateTimeTM CreateTime,
    CDateTimeTM AccessTime, CDateTimeTM WriteTime);

//@隐藏{
bool X_File_SetFileTime(CXText filePath, CDateTimeTM CreateTime, CDateTimeTM AccessTime);
bool X_File_SetFileTime(CXText filePath, CDateTimeTM CreateTime);
bool X_File_SetFileTimeA(CXTextA filePath, CDateTimeTM CreateTime, CDateTimeTM AccessTime);
bool X_File_SetFileTimeA(CXTextA filePath, CDateTimeTM CreateTime);
//@隐藏}

//@别名   文件_重启电脑后替换(旧路径,新路径,删除旧文件)
bool X_File_MoveFileOnReboot(CXText oldFile, CXText newFile, bool removeOldFile);
//@别名   文件_重启电脑后替换A(旧路径,新路径,删除旧文件)
bool X_File_MoveFileOnRebootA(CXTextA oldFile, CXTextA newFile, bool removeOldFile);

//@分组}  文件目录
//@分组{  常量

/*@声明

//@备注   表示Windows桌面的虚拟文件夹，名称空间的根。
//@别名   常量_CSIDL_桌面_虚拟目录
#define CSIDL_DESKTOP 0

//@备注   Internet Explorer的虚拟文件夹。
//@别名   常量_CSIDL_IE
#define CSIDL_INTERNET 1

//@备注   包含用户程序组的文件系统目录（本身就是文件系统目录）。典型的路径是C:\Documents and Settings\用户名\Start Menu\Programs。
//@别名   常量_CSIDL_开始菜单程序
#define CSIDL_PROGRAMS 2

//@备注   包含控制面板应用程序图标的虚拟文件夹。
//@别名   常量_CSIDL_控制面板程序图标
#define CSIDL_CONTROLS 3

//@备注   包含已安装打印机的虚拟文件夹。
//@别名   常量_CSIDL_已安装打印机
#define CSIDL_PRINTERS 4

//@备注   代表“我的文档”桌面项目的虚拟文件夹。
//@别名   常量_CSIDL_我的文档_虚拟目录
#define CSIDL_PERSONAL 5

//@备注   文件系统目录，用作用户喜欢的项目的公共存储库。典型路径是C:\Documents and Settings\用户名\Favorites。
//@别名   常量_CSIDL_公共存储库
#define CSIDL_FAVORITES 6

//@备注   与用户的启动程序组相对应的文件系统目录。每当相关联的用户登录时，系统都会启动这些程序。典型路径是C:\Documents and Settings\用户名\Start Menu\Programs\Startup。
//@别名   常量_CSIDL_启动目录
#define CSIDL_STARTUP 7

//@备注   文件系统目录，其中包含用户最近使用的文档的快捷方式。典型路径是C:\Documents and Settings\用户名\My Latest Documents。要在此文件夹中创建快捷方式，请使用SHAddToRecentDocs。除了创建快捷方式外，此功能还可以更新命令行管理程序的近期文档列表，并将快捷方式添加到“开始”菜单的“我的近期文档”子菜单中。
//@别名   常量_CSIDL_最近使用的文档
#define CSIDL_RECENT 8

//@备注   包含“发送到”菜单项的文件系统目录。典型路径是C:\Documents and Settings\用户名\SendTo。
//@别名   常量_CSIDL_发送到
#define CSIDL_SENDTO 9

//@备注   包含用户回收站中对象的虚拟文件夹。
//@别名   常量_CSIDL_回收站
#define CSIDL_BITBUCKET 10

//@备注   包含“开始”菜单项的文件系统目录。典型路径是C:\Documents and Settings\用户名\开始菜单。
//@别名   常量_CSIDL_开始菜单
#define CSIDL_STARTMENU 11

//@备注   用作音乐文件的公共存储库的文件系统目录。典型路径是C:\Documents and Settings\User\My Documents\My Music。
//@别名   常量_CSIDL_我的音乐
#define CSIDL_MYMUSIC 13

//@备注   用于在桌面上物理存储文件对象的文件系统目录（不要与桌面文件夹本身混淆）。典型路径是C:\Documents and Settings\用户名\Desktop。
//@别名   常量_CSIDL_桌面_物理目录
#define CSIDL_DESKTOPDIRECTORY 16

//@备注   代表“我的电脑”的虚拟文件夹，其中包含本地计算机上的所有内容：存储设备，打印机和控制面板。该文件夹还可以包含映射的网络驱动器。
//@别名   常量_CSIDL_我的电脑_虚拟目录
#define CSIDL_DRIVES 17

//@备注   表示网络邻居的虚拟文件夹，网络邻居是网络名称空间层次结构的根。
//@别名   常量_CSIDL_网络邻居_虚拟目录
#define CSIDL_NETWORK 18

//@备注   一个文件系统目录，其中包含“网上邻居”虚拟文件夹中可能存在的链接对象。它与CSIDL_NETWORK不同，后者表示网络名称空间的根。典型路径是C:\Documents and Settings\用户名\NetHood。
//@别名   常量_CSIDL_网上邻居_链接对象
#define CSIDL_NETHOOD 19

//@备注   包含字体的虚拟文件夹。典型的路径是C:\Windows\Fonts。
//@别名   常量_CSIDL_字体虚拟目录
#define CSIDL_FONTS 20

//@备注   用作文档模板的公共存储库的文件系统目录。典型的路径是C:\Documents and Settings\用户名\Templates。
//@别名   常量_CSIDL_公共文档模板
#define CSIDL_TEMPLATES 21

//@备注   文件系统目录，其中包含出现在“开始”菜单上的所有用户的程序和文件夹。典型的路径是C:\Documents and Settings\All Users\Start Menu。
//@别名   常量_CSIDL_开始菜单_程序与文件夹
#define CSIDL_COMMON_STARTMENU 22

//@备注   文件系统目录，其中包含出现在“开始”菜单上的所有用户的通用程序组的目录。典型的路径是C:\Documents and Settings\All Users\Start Menu\Programs。
//@别名   常量_CSIDL_开始菜单_通用程序组
#define CSIDL_COMMON_PROGRAMS 23

//@备注   文件系统目录，其中包含出现在所有用户的“启动”文件夹中的程序。典型的路径是C:\Documents and Settings\All Users\Start Menu\Programs\Startup。
//@别名   常量_CSIDL_开始菜单_启动程序
#define CSIDL_COMMON_STARTUP 24

//@备注   文件系统目录，其中包含为所有用户显示在桌面上的文件和文件夹。典型路径是C:\Documents and Settings\All Users\Desktop。
//@别名   常量_CSIDL_桌面目录
#define CSIDL_COMMON_DESKTOPDIRECTORY 25

//@备注   文件系统目录，用作特定于应用程序的数据的公共存储库。典型路径是C:\Documents and Settings\用户名\Application Data。
//@别名   常量_CSIDL_应用数据
#define CSIDL_APPDATA 26

//@备注   包含可以在“打印机”虚拟文件夹中存在的链接对象的文件系统目录。典型的路径是C:\Documents and Settings\用户名\PrintHood。
//@别名   常量_CSIDL_打印机链接对象
#define CSIDL_PRINTHOOD 27

//@备注   用户的配置文件文件夹。典型的路径是C:\Users\username。应用程序不应在此级别创建文件或文件夹；他们应该将其数据放在CSIDL_APPDATA或CSIDL_LOCAL_APPDATA所引用的位置下。但是，如果要创建新的“已知文件夹”，则由CSIDL_PROFILE引用的配置文件根目录是合适的。
//@别名   常量_CSIDL_用户应用配置
#define CSIDL_LOCAL_APPDATA 28

//@备注   与用户的非本地化启动程序组相对应的文件系统目录。Windows Vista可以识别此值以实现向后兼容，但是文件夹本身不再存在。
//@别名   常量_CSIDL_非本地启动目录_已废弃
#define CSIDL_ALTSTARTUP 29

//@备注   与所有用户的非本地化启动程序组相对应的文件系统目录。Windows Vista可以识别此值以实现向后兼容，但是文件夹本身不再存在。
//@别名   常量_CSIDL_非本地程序目录_已废弃
#define CSIDL_COMMON_ALTSTARTUP 30

//@备注   文件系统目录，用作所有用户共有的收藏夹项的通用存储库。
//@别名   常量_CSIDL_公用收藏夹
#define CSIDL_COMMON_FAVORITES 31

//@备注   用作Internet临时文件的公共存储库的文件系统目录。典型路径是C:\Documents and Settings\用户名\Local Settings\Temporary Internet Files。
//@别名   常量_CSIDL_IE临时目录
#define CSIDL_INTERNET_CACHE 32

//@备注   用作Internet cookie通用存储库的文件系统目录。典型路径是C:\Documents and Settings\用户名\Cookies。
//@别名   常量_CSIDL_IECookie目录
#define CSIDL_COOKIES 33

//@备注   用作Internet历史记录项目的公共存储库的文件系统目录。
//@别名   常量_CSIDL_IE历史记录
#define CSIDL_HISTORY 34

//@备注   包含所有用户的应用程序数据的文件系统目录。典型的路径是C:\Documents and Settings\All Users\Application Data。该文件夹用于非特定于用户的应用程序数据。例如，应用程序可以在CSIDL_COMMON_APPDATA文件夹中存储拼写检查字典，剪贴画数据库或日志文件。此信息将不会漫游，并且使用计算机的任何人都可以使用。
//@别名   常量_CSIDL_用户应用数据
#define CSIDL_COMMON_APPDATA 35

//@备注   Windows目录或SYSROOT。这对应于％windir％或％SYSTEMROOT％环境变量。典型路径是C:\Windows。
//@别名   常量_CSIDL_Windows目录
#define CSIDL_WINDOWS 36

//@备注   Windows系统文件夹。典型路径是C:\Windows\System32。
//@别名   常量_CSIDL_Windows系统文件夹
#define CSIDL_SYSTEM 37

//@备注   程序文件文件夹。典型的路径是C:\Program Files。
//@别名   常量_CSIDL_程序文件目录
#define CSIDL_PROGRAM_FILES 38

//@备注   用作映像文件的公共存储库的文件系统目录。典型路径是C:\Documents and Settings\用户名\My Documents\My Pictures。
//@别名   常量_CSIDL_照片存储库
#define CSIDL_MYPICTURES 39

//@备注   用户的配置文件文件夹。典型的路径是C:\Users\username。应用程序不应在此级别创建文件或文件夹；他们应该将其数据放在CSIDL_APPDATA或CSIDL_LOCAL_APPDATA所引用的位置下。但是，如果要创建新的“已知文件夹”，则由CSIDL_PROFILE引用的配置文件根目录是合适的。
//@别名   常量_CSIDL_用户配置
#define CSIDL_PROFILE 40

//@备注   x86 system directory on RISC
//@别名   常量_CSIDL_RISCX86SYSTEM
#define CSIDL_SYSTEMX86 41

//@备注   x86 C:\Program Files on RISC
//@别名   常量_CSIDL_RISCX86PROGRAMFILES
#define CSIDL_PROGRAM_FILESX86 42

//@备注   跨应用程序共享的组件的文件夹。典型路径是C:\Program Files\Common。仅对Windows XP有效。
//@别名   常量_CSIDL_跨应用程序共享组件
#define CSIDL_PROGRAM_FILES_COMMON 43

//@备注   x86 Program Files\Common on RISC
//@别名   常量_CSIDL_FILES_COMMONX86
#define CSIDL_PROGRAM_FILES_COMMONX86 44

//@备注   包含可供所有用户使用的模板的文件系统目录。典型的路径是C:\Documents and Settings\All Users\Templates。
//@别名   常量_CSIDL_公共模板
#define CSIDL_COMMON_TEMPLATES 45

//@备注   文件系统目录，其中包含所有用户通用的文档。典型的路径是C:\Documents and Settings\All Users\Documents。
//@别名   常量_CSIDL_通用文档_ALLUSER
#define CSIDL_COMMON_DOCUMENTS 46

//@备注   包含计算机所有用户的管理工具的文件系统目录。All Users\Start Menu\Programs\Administrative Tools
//@别名   常量_CSIDL_管理工具_ALLUSER
#define CSIDL_COMMON_ADMINTOOLS 47

//@备注   用于存储单个用户的管理工具的文件系统目录。MMC将自定义的控制台保存到此目录，并且将与用户漫游。<user name>\Start Menu\Programs\Administrative Tools
//@别名   常量_CSIDL_管理工具
#define CSIDL_ADMINTOOLS 48

//@备注   表示网络连接的虚拟文件夹，其中包含网络和拨号连接。
//@别名   常量_CSIDL_网络连接_虚拟文件夹
#define CSIDL_CONNECTIONS 49

//------------
#define FILE_READ_DATA            ( 0x0001 )    // file & pipe
#define FILE_LIST_DIRECTORY       ( 0x0001 )    // directory

#define FILE_WRITE_DATA           ( 0x0002 )    // file & pipe
#define FILE_ADD_FILE             ( 0x0002 )    // directory

#define FILE_APPEND_DATA          ( 0x0004 )    // file
#define FILE_ADD_SUBDIRECTORY     ( 0x0004 )    // directory
#define FILE_CREATE_PIPE_INSTANCE ( 0x0004 )    // named pipe


#define FILE_READ_EA              ( 0x0008 )    // file & directory

#define FILE_WRITE_EA             ( 0x0010 )    // file & directory

#define FILE_EXECUTE              ( 0x0020 )    // file
#define FILE_TRAVERSE             ( 0x0020 )    // directory

#define FILE_DELETE_CHILD         ( 0x0040 )    // directory

#define FILE_READ_ATTRIBUTES      ( 0x0080 )    // all

#define FILE_WRITE_ATTRIBUTES     ( 0x0100 )    // all

#define FILE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)

#define FILE_GENERIC_READ         


#define FILE_GENERIC_WRITE        


#define FILE_GENERIC_EXECUTE      

#define FILE_SHARE_READ                 0x00000001
#define FILE_SHARE_WRITE                0x00000002
#define FILE_SHARE_DELETE               0x00000004
//#define FILE_ATTRIBUTE_DEVICE               0x00000040
//#define FILE_ATTRIBUTE_OFFLINE              0x00001000
//#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000
#define FILE_ATTRIBUTE_INTEGRITY_STREAM     0x00008000
//#define FILE_ATTRIBUTE_VIRTUAL              0x00010000
#define FILE_ATTRIBUTE_NO_SCRUB_DATA        0x00020000
#define FILE_ATTRIBUTE_EA                   0x00040000
#define FILE_ATTRIBUTE_PINNED               0x00080000
#define FILE_ATTRIBUTE_UNPINNED             0x00100000
#define FILE_ATTRIBUTE_RECALL_ON_OPEN       0x00040000
#define FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS 0x00400000
#define TREE_CONNECT_ATTRIBUTE_PRIVACY      0x00004000
#define TREE_CONNECT_ATTRIBUTE_INTEGRITY    0x00008000
#define TREE_CONNECT_ATTRIBUTE_GLOBAL       0x00000004
#define TREE_CONNECT_ATTRIBUTE_PINNED       0x00000002
#define FILE_ATTRIBUTE_STRICTLY_SEQUENTIAL  0x20000000
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010
#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020
#define FILE_NOTIFY_CHANGE_CREATION     0x00000040
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100
#define FILE_ACTION_ADDED                   0x00000001
#define FILE_ACTION_REMOVED                 0x00000002
#define FILE_ACTION_MODIFIED                0x00000003
#define FILE_ACTION_RENAMED_OLD_NAME        0x00000004
#define FILE_ACTION_RENAMED_NEW_NAME        0x00000005
#define MAILSLOT_NO_MESSAGE             ((DWORD)-1)
#define MAILSLOT_WAIT_FOREVER           ((DWORD)-1)
#define FILE_CASE_SENSITIVE_SEARCH          0x00000001
#define FILE_CASE_PRESERVED_NAMES           0x00000002
#define FILE_UNICODE_ON_DISK                0x00000004
#define FILE_PERSISTENT_ACLS                0x00000008
#define FILE_FILE_COMPRESSION               0x00000010
#define FILE_VOLUME_QUOTAS                  0x00000020
#define FILE_SUPPORTS_SPARSE_FILES          0x00000040
#define FILE_SUPPORTS_REPARSE_POINTS        0x00000080
#define FILE_SUPPORTS_REMOTE_STORAGE        0x00000100
#define FILE_RETURNS_CLEANUP_RESULT_INFO    0x00000200
#define FILE_SUPPORTS_POSIX_UNLINK_RENAME   0x00000400
#define FILE_SUPPORTS_BYPASS_IO             0x00000800
#define FILE_SUPPORTS_STREAM_SNAPSHOTS      0x00001000
#define FILE_SUPPORTS_CASE_SENSITIVE_DIRS   0x00002000

#define FILE_VOLUME_IS_COMPRESSED           0x00008000
#define FILE_SUPPORTS_OBJECT_IDS            0x00010000
#define FILE_SUPPORTS_ENCRYPTION            0x00020000
#define FILE_NAMED_STREAMS                  0x00040000
#define FILE_READ_ONLY_VOLUME               0x00080000
#define FILE_SEQUENTIAL_WRITE_ONCE          0x00100000
#define FILE_SUPPORTS_TRANSACTIONS          0x00200000
#define FILE_SUPPORTS_HARD_LINKS            0x00400000
#define FILE_SUPPORTS_EXTENDED_ATTRIBUTES   0x00800000
#define FILE_SUPPORTS_OPEN_BY_FILE_ID       0x01000000
#define FILE_SUPPORTS_USN_JOURNAL           0x02000000
#define FILE_SUPPORTS_INTEGRITY_STREAMS     0x04000000
#define FILE_SUPPORTS_BLOCK_REFCOUNTING     0x08000000
#define FILE_SUPPORTS_SPARSE_VDL            0x10000000
#define FILE_DAX_VOLUME                     0x20000000
#define FILE_SUPPORTS_GHOSTING              0x40000000

//#define CREATE_NEW          1
//#define CREATE_ALWAYS       2
//#define OPEN_EXISTING       3
//#define OPEN_ALWAYS         4
//#define TRUNCATE_EXISTING   5

#define FILE_FLAG_WRITE_THROUGH         0x80000000
#define FILE_FLAG_OVERLAPPED            0x40000000
#define FILE_FLAG_NO_BUFFERING          0x20000000
#define FILE_FLAG_RANDOM_ACCESS         0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN       0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE       0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS      0x02000000
#define FILE_FLAG_POSIX_SEMANTICS       0x01000000
#define FILE_FLAG_SESSION_AWARE         0x00800000
#define FILE_FLAG_OPEN_REPARSE_POINT    0x00200000
#define FILE_FLAG_OPEN_NO_RECALL        0x00100000
#define FILE_FLAG_FIRST_PIPE_INSTANCE   0x00080000

BOOL WINAPI ReadDirectoryChangesW(HANDLE hDirectory,LPVOID lpBuffer,DWORD nBufferLength,BOOL bWatchSubtree,DWORD dwNotifyFilter,LPDWORD lpBytesReturned,LPOVERLAPPED lpOverlapped,LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

*/


//@备注   文件或目录是存档文件或目录。应用程序使用此属性标记要备份或删除的文件。
#define  常量_文件属性_存档文件  FILE_ATTRIBUTE_ARCHIVE

//@备注   文件或目录已压缩。对于文件，这意味着文件中的所有数据都已压缩。对于目录，这意味着压缩是新创建的文件和子目录的默认值。
#define  常量_文件属性_已压缩  FILE_ATTRIBUTE_COMPRESSED

//@备注   句柄标识目录。
#define  常量_文件属性_文件夹  FILE_ATTRIBUTE_DIRECTORY

//@备注   文件或目录已加密。对于文件，这意味着所有数据流都已加密。对于目录，这意味着加密是新创建的文件和子目录的默认设置。
#define  常量_文件属性_加密文件  FILE_ATTRIBUTE_ENCRYPTED

//@备注   文件或目录被隐藏。它不包含在普通目录列表中。
#define  常量_文件属性_隐藏  FILE_ATTRIBUTE_HIDDEN

//@备注   此文件是存储在ROM中的操作系统文件。这些文件是只读的；它们不能被修改。  
#define  常量_文件属性_INROM  FILE_ATTRIBUTE_INROM

//@备注   文件或目录没有其他属性集。此属性仅在单独使用时有效。
#define  常量_文件属性_无属性  FILE_ATTRIBUTE_NORMAL

//@备注   文件或目录是只读的。应用程序可以读取文件，但不能写入或删除它。对于目录，应用程序无法删除它。
#define  常量_文件属性_只读 FILE_ATTRIBUTE_READONLY

//@备注   具有关联重分析点的文件或目录,或者是符号链接的文件
#define  常量_文件属性_重复分析点   FILE_ATTRIBUTE_REPARSE_POINT

//@备注   此文件是存储在ROM中的操作系统文件，直接从ROM执行，而不是首先复制到RAM。CreateFile函数不能用于访问此文件，而必须使用LoadLibrary和CreateProcess函数。
#define  常量_文件属性_系统模块  FILE_ATTRIBUTE_ROMMODULE

//@备注   该文件是一个DLL模块，它具有来自映像的模块部分中至少一个其他文件的静态引用。具有此属性的文件不能用同一DLL的RAM副本替换DLL的功能。具有此属性的文件还必须具有file_attribute_INROM和file_attribute_ROMODULE属性。
#define  常量_文件属性_静态参考只读存储器  FILE_ATTRIBUTE_ROMSTATICREF

//@备注   该文件是一个稀疏文件 
#define  常量_文件属性_稀疏文件  FILE_ATTRIBUTE_SPARSE_FILE

//@备注   该文件或目录是操作系统的一部分，或仅供操作系统使用。  
#define  常量_文件属性_系统文件  FILE_ATTRIBUTE_SYSTEM

//@备注   该文件正用于临时存储。文件系统尝试将所有数据保留在内存中，以便更快地访问，而不是将数据刷新回大容量存储。一旦不再需要临时文件，应用程序应将其删除。
#define  常量_文件属性_临时文件  FILE_ATTRIBUTE_TEMPORARY



//@别名   常量_特定目录_我的文档
#define GIVENDIR_MYDOCUMENTS 1

//@别名   常量_特定目录_我的收藏夹
#define GIVENDIR_MYFAVORITE 2

//@别名   常量_特定目录_系统桌面
#define GIVENDIR_SYSTEMDESKTOP 3

//@别名   常量_特定目录_系统字体
#define GIVENDIR_SYSTEMFONT 4

//@别名   常量_特定目录_开始菜单组
#define GIVENDIR_OPENINGMENU 5

//@别名   常量_特定目录_程序菜单组
#define GIVENDIR_PROGRAMMENU 6

//@别名   常量_特定目录_启动菜单组
#define GIVENDIR_STARTMENU 7

//@别名   常量_特定目录_程序数据目录
#define GIVENDIR_PROGRAMDATA 8

//@别名   常量_特定目录_Windows安装目录
#define GIVENDIR_WINDOWSINSTALL 9

//@别名   常量_特定目录_Windows系统目录
#define GIVENDIR_WINDOWSSYSTEM 10

//@别名   常量_特定目录_临时文件目录
#define GIVENDIR_TEMPORARYFILE 11

//@别名   常量_特定目录_系统缓存目录
#define GIVENDIR_SYSTEMCACHE 12

//@别名   常量_特定目录_文件系统目录
#define GIVENDIR_FILESYSTEM 13

//-------------

//@别名   常量_文件类型_EXE_DLL
#define X_FILE_TYPR_EXEORDLL 0

//@别名   常量_文件类型_RAR
#define X_FILE_TYPR_RAR 3

//@别名   常量_文件类型_ZIP
#define X_FILE_TYPR_ZIP 4

//@别名   常量_文件类型_7Z
#define X_FILE_TYPR_7Z 5

//@别名   常量_文件类型_JPG
#define X_FILE_TYPR_JPG 6

//@别名   常量_文件类型_GIF
#define X_FILE_TYPR_GIF 7

//@别名   常量_文件类型_SWF
#define X_FILE_TYPR_SWF 8


#ifndef FILE_INVALID_FILE_ID
#define FILE_INVALID_FILE_ID         -1
#endif


//@分组}  常量


#endif //XL_XEXPAND_FILES_H
