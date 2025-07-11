#include "module_yyy.h"
#include <commdlg.h>
#include <MMSystem.h>
#include <conio.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Comdlg32.lib")

//查找子字符串, 不区分大小写
const wchar_t* wcsistr(const wchar_t* str, const wchar_t* substr)
{
	const wchar_t* p = str;
	const wchar_t* p2 = substr;
	while (*p)
	{
		const wchar_t* p1 = p;
		while (*p1 && *p2)
		{
			if (*p1 == *p2)
			{
				p1++;
				p2++;
				if (0 == *p2)
					return p;
			} else
			{
				wchar_t ch1 = *p1;
				wchar_t ch2 = *p2;

				// 如果字符是小写字母，则转换为大写字母
				if (ch1 >= L'a' && ch1 <= L'z') {
					ch1 -= L'a' - L'A';
				}
				if (ch2 >= L'a' && ch2 <= L'z') {
					ch2 -= L'a' - L'A';
				}

				if (ch1 == ch2) {
					p1++;
					p2++;
					if (0 == *p2)
						return p;
				} else
				{
					break;
				}
			}
		}
		p++;
	}
	return NULL;
}

int MyMemCmp2(unsigned char* a, unsigned char* b, int len)
{
	for (int i = 0; i < (len >> 2); i++)
	{
		if (((int*)a)[0] != ((int*)b)[0])
			return 1;
		a += 4; b += 4;
	}
	if ((len & 2) != 0)
	{
		if (((short*)a)[0] != ((short*)b)[0])
			return 1;
		a += 2; b += 2;
	}
	if ((len & 1) != 0 && a[0] != b[0])
		return 1;
	return 0;
}
int is_prefix(unsigned char* word, int wordlen, int pos)
{
	int i;
	int suffixlen = wordlen - pos;

	for (i = 0; i < suffixlen; i++) {
		if (word[i] != word[pos + i]) {
			return 0;
		}
	}
	return 1;
}
int suffix_length(unsigned char* word, int wordlen, int pos)
{
	int i;
	// increment suffix length i to the first mismatch or beginning
	// of the word
	for (i = 0; (word[pos - i] == word[wordlen - 1 - i]) && (i < pos); i++);
	return i;
}
void make_delta2(int* delta2, unsigned char* pat, int patlen)
{
	int p;
	int last_prefix_index = 1;

	// first loop, prefix pattern
	for (p = patlen - 1; p >= 0; p--) {
		if (is_prefix(pat, patlen, p + 1)) {
			last_prefix_index = p + 1;
		}
		delta2[p] = (patlen - 1 - p) + last_prefix_index;
	}

	// this is overly cautious, but will not produce anything wrong
	// second loop, suffix pattern
	for (p = 0; p < patlen - 1; p++) {
		int slen = suffix_length(pat, patlen, p);
		if (pat[p - slen] != pat[patlen - 1 - slen]) {
			delta2[patlen - 1 - slen] = patlen - 1 - p + slen;
		}
	}
}
void make_delta1(int* delta1, unsigned char* pat, int patlen)
{
	int i;

	for (i = 0; i < 256; i++) {
		delta1[i] = patlen;
	}
	for (i = 0; i < patlen - 1; i++) {
		delta1[pat[i]] = patlen - 1 - i;
	}
}

int boyer_moore(unsigned char* string, int stringlen, unsigned char* pat, int patlen)
{
	int i;
	int delta1[256];
	int* delta2 = (int*)malloc(patlen * sizeof(int));
	if (!delta2)
		return -1;
	make_delta1(delta1, pat, patlen);
	make_delta2(delta2, pat, patlen);
	int n_shifts = 0;

	i = patlen - 1;
	while (i < stringlen) {
		int j = patlen - 1;
		while (j >= 0 && (string[i] == pat[j])) {
			--i;
			--j;
		}
		if (j < 0) {
			free(delta2);
			return i + 1;
		}

		i += max(delta1[string[i]], delta2[j]);
	}
	free(delta2);
	return -1;
}
int mymemchr(unsigned char* pSrc, int nLen, unsigned char Des)
{
	register unsigned int longword, dmagic, * longword_ptr;
	unsigned char* cp;
	unsigned char* char_ptr = pSrc;
	for (int i = 0; i < (nLen & 3); i++)
		if (*char_ptr++ == Des)
			return char_ptr - pSrc - 1;

	dmagic = Des | (Des << 8) | (Des << 16) | (Des << 24);
	for (longword_ptr = (unsigned int*)char_ptr; longword_ptr < (unsigned int*)(pSrc + nLen); longword_ptr++)
	{
		longword = *longword_ptr ^ dmagic;
		if (((longword - 0x01010101) & ~longword & 0x80808080) != 0)
		{
			cp = (unsigned char*)(longword_ptr);
			if (cp[0] == Des)
				return cp - pSrc;
			if (cp[1] == Des)
				return cp - pSrc + 1;
			if (cp[2] == Des)
				return cp - pSrc + 2;
			if (cp[3] == Des)
				return cp - pSrc + 3;
		}
	}
	return -1;
}
int myinstring(unsigned char* src, int slen, unsigned char* des, int dlen)
{
	//	register unsigned char* naddr;
	//	int sl;int i;int j;
	int i;
	if (!src || !des || !slen || !dlen || dlen > slen)
		return -1;

	switch (dlen)
	{
	case 1:  // 短子串直接暴力搜索
		return mymemchr(src, slen, des[0]);
	case 2:
		for (i = 0; i < slen - 1; i++)
			if (((short*)(src + i))[0] == ((short*)des)[0])
				return i;
		return -1;
	case 3:
		for (i = 0; i < slen - 2; i++)
			if (((short*)(src + i))[0] == ((short*)des)[0])
				if (src[i + 2] == des[2])
					return i;
		return -1;
	case 4:
		for (i = 0; i < slen - 3; i++)
			if (((int*)(src + i))[0] == ((int*)des)[0])
				return i;
		return -1;
	case 5:
		for (i = 0; i < slen - 4; i++)
			if (((int*)(src + i))[0] == ((int*)des)[0])
				if (src[i + 4] == des[4])
					return i;
		return -1;
	case 6:
		for (i = 0; i < slen - 5; i++)
			if (((int*)(src + i))[0] == ((int*)des)[0])
				if (((short*)(src + i + 4))[0] == ((short*)(des + 4))[0])
					return i;
		return -1;
	default:// 长子串使用BM算法,
		return boyer_moore(src, slen, des, dlen);
	}
	return -1;
}

double 四舍五入(double value_, int pos)
{
	double factor = pow(10, pos); // 计算舍入因子
	double rounded_value = round(value_ * factor) / factor; // 进行四舍五入运算
	return rounded_value;
}

#ifdef XCL_MD5_H
BOOL GetBufMD5(unsigned char* pMd5String, unsigned char* rbuff, DWORD BufSize)
{
//	MD5_CTX context;
	unsigned char O[16];

//	MD5Init(&context);
//	MD5Update(&context, rbuff, BufSize);
//	MD5Final(&context);
	CXMD5  md5;
	md5.reset();
	md5.update(rbuff, BufSize);

	memcpy(O, (unsigned char*)md5.digest(), 16);
	sprintf_s((char*)pMd5String, 32,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
		O[0], O[1], O[2], O[3], O[4], O[5], O[6], O[7], O[8], O[9], O[10], O[11], O[12], O[13], O[14], O[15]);
	return TRUE;
}
#endif

//--------------------------------------------
int 取磁盘总空间(const wchar_t* pText)
{
	wchar_t DirName[MAX_PATH];
	if (NULL == pText)
	{
		if (GetCurrentDirectory(MAX_PATH, DirName) == 0)
			return -1;
		DirName[2] = 0;

	} else
	{
		if (0==*pText)
			return -1;

		DirName[0] = *pText;
		DirName[1] = ':';
		DirName[2] = 0;

	}
	//ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
	DWORD SectorsPerCluster, BytesPerSector, NumberOfFreeClusters, nNumerator;
	if (GetDiskFreeSpace(DirName, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &nNumerator))
	{
		int nRet = int(MulDiv(BytesPerSector * SectorsPerCluster, nNumerator, 1024));
		return nRet;
	}
	return -1;
}

int 取磁盘剩余空间(const wchar_t* pText)
{
	wchar_t DirName[MAX_PATH];
	if (NULL==pText)
	{
		if (GetCurrentDirectory(MAX_PATH, DirName) == 0)
			return -1;
		DirName[2] = 0;

	} else
	{
		if (0 == *pText)
			return -1;

		DirName[0] = *pText;
		DirName[1] = ':';
		DirName[2] = 0;

	}
	ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
	if (GetDiskFreeSpaceEx(DirName, &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes))
	{
		INT nRet = INT(FreeBytesAvailableToCaller.QuadPart / 1024);
		return nRet;
	}
	return -1;
}

CXText 取磁盘卷标(const wchar_t* pText)
{
	wchar_t DirName[MAX_PATH];
	if (NULL==pText)
	{
		if (GetCurrentDirectory(MAX_PATH, DirName) == 0)
			return L"";
		DirName[3] = 0;
	} else
	{
		if (0==*pText)
			return L"";

		DirName[0] = *pText;
		DirName[1] = ':';
		DirName[2] = '\\';
		DirName[3] = 0;
	}
	wchar_t strVolume[MAX_PATH];
	wchar_t FileSystemNameBuffer[64];
	DWORD VolumeSerialNumber;

	if (GetVolumeInformation(DirName, strVolume, MAX_PATH,
		&VolumeSerialNumber,
		NULL,
		NULL,
		FileSystemNameBuffer,
		64))
	{
		return strVolume;
	}
	return L"";
}

BOOL 置磁盘卷标(const wchar_t* pText)
{
	wchar_t DirName[MAX_PATH];
	if (NULL == pText)
	{
		if (GetCurrentDirectory(MAX_PATH, DirName) == 0)
			return FALSE;
		DirName[3] = 0;
	} else
	{
		if (0 ==*pText)
			return FALSE;

		DirName[0] = *pText;
		DirName[1] = ':';
		DirName[2] = '\\';
		DirName[3] = 0;
	}
	return SetVolumeLabel(DirName, pText);
}

BOOL 改变驱动器(const wchar_t* pText)
{
	wchar_t DirName[MAX_PATH];
	if (NULL== pText || 0==*pText)
		return FALSE;

	DirName[0] = *pText;
	DirName[1] = ':';
	DirName[2] = '\\';
	DirName[3] = 0;
	return SetCurrentDirectory(DirName);
}

BOOL 改变目录(const wchar_t* pDir)
{
	return SetCurrentDirectory(pDir);
}

CXText 取当前目录()
{
	wchar_t DirName[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, DirName);
	return DirName;
}

BOOL 创建目录(const wchar_t* pDir)
{
	if (NULL == pDir || 0 == *pDir) return FALSE;
	SECURITY_ATTRIBUTES SecAttrib;
	SecAttrib.nLength = sizeof(SECURITY_ATTRIBUTES);
	SecAttrib.lpSecurityDescriptor = NULL;
	SecAttrib.bInheritHandle = FALSE;
	return CreateDirectory(pDir, &SecAttrib);//创建目录
}

BOOL 移动文件(const wchar_t* pFileSrc, const wchar_t* pFileDest)
{
	BOOL result = MoveFile(pFileSrc, pFileDest);
	if (!result) {
		result = CopyFile(pFileSrc, pFileDest, 0);
		if (result)
			result = DeleteFile(pFileSrc);
	}
	return result;
}


INT64 取文件时间(const wchar_t* pFileName)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(pFileName, &FindFileData);
	struct tm tmVal = {0};
	tmVal.tm_year = 100;
	tmVal.tm_mon = 1;
	tmVal.tm_mday = 1;
	tmVal.tm_hour = 1;
	tmVal.tm_sec = 1;
	tmVal.tm_min = 1;
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		if (FileTimeToLocalFileTime(&FindFileData.ftLastWriteTime, &FindFileData.ftCreationTime))
		{
			SYSTEMTIME now;
			if (FileTimeToSystemTime(&FindFileData.ftCreationTime, &now)) {
				tmVal.tm_sec = now.wSecond;
				tmVal.tm_min = now.wMinute;
				tmVal.tm_hour = now.wHour;
				tmVal.tm_mday = now.wDay;
				tmVal.tm_mon = now.wMonth - 1;  // tm结构中月份范围是0-11
				tmVal.tm_year = now.wYear - 1900;  // tm结构中年份是从1900年开始计算的
				tmVal.tm_wday = now.wDayOfWeek;
			}
		}
	}
	return mktime(&tmVal);
}

int 取文件尺寸(const wchar_t* pFileName)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(pFileName, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		if (FindFileData.nFileSizeHigh == 0xFFFFFFFF)
			return -1;
		return FindFileData.nFileSizeLow;
	}
	return -1;
}

CXText  取临时文件名(const wchar_t* pName)
{
	wchar_t DirName[MAX_PATH];
	if (NULL== pName)
	{
		if (GetTempPath(MAX_PATH, DirName) == FALSE)
			DirName[0] = 0;
	} else
	{
		wcscpy_s(DirName, MAX_PATH, pName);
	}
	wchar_t* pText = NULL;
	wchar_t TempFileName[MAX_PATH];
	INT nLen = wcslen(DirName);
	if (DirName[nLen - 1] != '\\')
		DirName[nLen] = '\\';
	do {
		wsprintf(TempFileName, L"%s%x.tmp", DirName, GetTickCount());
	} while (PathFileExists(TempFileName));
	return TempFileName;
}

CXBytes 读入文件(const wchar_t* pFileName)
{
	CXFile q;
	CXBytes qq;
	if(q.openRead(pFileName)){
		qq = q.readDataBytes();
		q.close();
	}
	
	return qq;
}

BOOL 写到文件(const wchar_t* pFileName, CXBytes& data_)
{
	CXFile q;
	if (q.openWrite(pFileName))
	{
		UINT length = q.writeData((void*)data_.get(), data_.size());
		q.close();

		if (length == (UINT)data_.size()) return TRUE;
	}
	return FALSE;
}

CXBytes 到字节集(const CXText& value_) 
{
	CXBytes  byte_ = value_;
	return byte_;
}

CXBytes 到字节集(const CXTextA& value_) 
{
	CXBytes  byte_ = value_;
	return byte_;
}

CXBytes 取字节集左边(CXBytes& 欲取出其中数据的字节集, int 欲取出字节的数目)
{
	return 欲取出其中数据的字节集.getLeft(欲取出字节的数目);
}

CXBytes 取字节集右边(CXBytes& 欲取出其中数据的字节集, int 欲取出字节的数目)
{
	return 欲取出其中数据的字节集.getRight(欲取出字节的数目);
}

CXBytes 取字节集中间(CXBytes& 欲取出其中数据的字节集, int 起始取出位置, int 欲取出字节的数目)
{
	return 欲取出其中数据的字节集.getMid(起始取出位置, 欲取出字节的数目);
}

CXBytes 指针到字节集(void* 指针, int 大小)
{
	CXBytes mk;
	mk.add(指针, 大小);
	return mk;

}

CXBytes 取空白字节集(int 大小)
{
	CXBytes mk;
	mk.addSize(大小);
	return mk;

}

CXBytes 取重复字节集(int 重复次数, CXBytes 待重复的字节集)
{
	CXBytes mk;
	if (待重复的字节集.size() == 0) {
		mk.addSize(重复次数);
		return mk;
	}
	for (int i = 0; i < 重复次数; i++)
	{
		mk.add((void*)待重复的字节集.get(), 待重复的字节集.size());
	}
	return mk;
}

CXBytes 子字节集替换(CXBytes 欲被替换的字节集, CXBytes 欲被替换的子字节集, CXBytes 用作替换的子字节集, int 进行替换的起始位置, int 替换进行的次数)
{
	// 被封七号 改
	CXBytes fh;
	LPBYTE pSrc = (LPBYTE)欲被替换的字节集.get();
	INT nSLen = 欲被替换的字节集.size();
	if (nSLen <= 0 || !pSrc) return fh;

	LPBYTE pDes = (LPBYTE)欲被替换的子字节集.get();
	INT nDLen = 欲被替换的子字节集.size();

	//pSrc += 2 * sizeof(INT);
	INT nCount = 替换进行的次数;
	if (替换进行的次数 == -1)
		nCount = 0x7FFFFFFF; // 最大替换次数21亿

	INT nStart;
	if (进行替换的起始位置 == -1 || 进行替换的起始位置 <= 0)
		nStart = 0;
	else
		nStart = 进行替换的起始位置;

	if (nDLen <= 0 || !pDes || nCount <= 0 || nStart >= nSLen || nDLen > nSLen) // 关键参数不合法，直接返回原字节集
		return 欲被替换的字节集;

	//pDes += 2 * sizeof(INT);
	LPBYTE pSub = NULL;
	INT nSubLen = 0;
	nSubLen = 用作替换的子字节集.size();
	if (nSubLen < 0)
		nSubLen = 0;
	else
		pSub = (LPBYTE)用作替换的子字节集.get();

	// 开始计算
	INT nPos;
	LPBYTE pFirst = pSrc;
	LPBYTE pSearch = pSrc + nStart;
	INT nSYLen = nSLen;
	LPBYTE pLast = pSrc + nSLen;

	for (; nCount > 0; nCount--)
	{
		nPos = myinstring(pSearch, nSYLen, pDes, nDLen);
		if (nPos == -1)
			break;
		if (pSearch + nPos - pFirst > 0)
			fh.add((void*)pFirst, (int)(pSearch + nPos - pFirst));
		//tbr.add(pFirst, pSearch + nPos - pFirst);

		if (nSubLen > 0)
			fh.add((void*)pSub, nSubLen);
		//tbr.add(pSub, nSubLen);


		pSearch += nPos + nDLen;
		pFirst = pSearch;
		nSYLen -= nPos + nDLen;
	}

	if (pLast - pFirst > 0)
		fh.add((void*)pFirst, (int)(pLast - pFirst));
	//tbr.add(pFirst, pLast - pFirst);
	return fh;
}

CXVector<CXBytes> 分割字节集(CXBytes 待分割字节集, CXBytes 用作分割的字节集, int 要返回的子字节集数目)
{
	// 被封七号 改
	CXVector<CXBytes> gg;
	INT nCount = 要返回的子字节集数目 == 0 ? 0x7FFFFFFF : 要返回的子字节集数目;//要返回的子字节集数目

	LPBYTE pSrc = (LPBYTE)待分割字节集.get();//原字节集
	if (!pSrc)
		return gg;
	INT nSLen = 待分割字节集.size();//原字节集长度
	if (nSLen <= 0)
		return gg;
	//pSrc += 2 * sizeof(INT);

	LPBYTE pSub = NULL;//用作分割的字节集
	INT nSubLen = 0;//用作分割的字节集长度
	BYTE bMark[] = { 0,0 };
	if (用作分割的字节集.size() == NULL)
	{
		pSub = bMark;
		nSubLen = 1;
	} else
	{

		pSub = (LPBYTE)用作分割的字节集.get();
		nSubLen = 用作分割的字节集.size();

	}

	if (nSubLen == 0)
		nCount = -1;//返回一个成员

	// 开始计算
	INT nPos;
	INT nSYLen = nSLen;//原字节集长度
	LPBYTE pFirst = pSrc;//原字节集
	LPBYTE cp = pSrc;//原字节集
	要返回的子字节集数目 = 0;
	for (; nCount > 0; nCount--)
	{
		nPos = myinstring(cp, nSYLen, pSub, nSubLen);
		if (nPos == -1)
			break;
		cp += nPos;
		//tbr.add(pFirst, cp - pFirst);
		CXBytes jj;
		int ui = (int)(cp - pFirst);
		jj.add((LPBYTE)(pFirst), (int)(cp - pFirst));
		gg.add(jj);
		cp += nSubLen;
		nSYLen -= nPos + nSubLen;
		pFirst = cp;
		要返回的子字节集数目 += 1;
	}
	LPBYTE pLast = pSrc + nSLen;
	if (pLast - pFirst > 0 && nCount != 0) {
		CXBytes jj_;
		jj_.add((LPBYTE)(pFirst), (int)(pLast - pFirst));
		gg.add(jj_);
		要返回的子字节集数目 += 1;
	}

	return gg;  // 返回内容数组。
}

int 倒找字节集(CXBytes& 被搜寻的字节集, CXBytes 欲寻找的字节集, int 起始搜寻位置)
{ // 被封七号 改

	if (被搜寻的字节集.size() == NULL || 欲寻找的字节集.size() == NULL)
		return -1;

	INT nLen = 被搜寻的字节集.size();
	INT nSubLen = 欲寻找的字节集.size();
	if (nLen <= 0 || nSubLen <= 0 || nSubLen > nLen) return -1;

	register unsigned char* pSrc = (unsigned char*)被搜寻的字节集.get();
	int off = 起始搜寻位置;
	if (off == NULL)
		off = nLen - nSubLen;
	else
	{
		off = 起始搜寻位置;
		if (off < 0)
			return -1;
		if (off <= nLen)
			nLen = off;
		off = nLen - nSubLen;
	}

	if (off < 0) return -1;

	register unsigned char* pDes = (unsigned char*)欲寻找的字节集.get();
	int i;
	//int j;
	// 短子串直接暴力搜索
	if (nSubLen == 1)
	{
		for (i = off; i >= 0; i--)
			if (pSrc[i] == pDes[0])
				return i;

		return -1;
	} else if (nSubLen == 2)
	{
		for (i = off; i >= 0; i--)
			if (((short*)(pSrc + i))[0] == ((short*)pDes)[0])
				return i;

		return -1;
	} else if (nSubLen == 3)
	{
		for (i = off; i >= 0; i--)
			if (((short*)(pSrc + i))[0] == ((short*)pDes)[0])
				if (pSrc[i + 2] == pDes[2])
					return i;

		return -1;
	} else if (nSubLen == 4)
	{
		for (i = off; i >= 0; i--)
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0])
				return i;

		return -1;
	} else if (nSubLen == 5)
	{
		for (i = off; i >= 0; i--)
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0])
				if (pSrc[i + 4] == pDes[4])
					return i;

		return -1;
	} else if (nSubLen == 6)
	{
		for (i = off; i >= 0; i--)
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0])
				if (((short*)(pSrc + i + 4))[0] == ((short*)(pDes + 4))[0])
					return i;

		return -1;
	}

	// 	for (i = off; i >= 0; i--)
	// 		if (MyMemCmp2(pSrc+i, pDes, nSubLen)==0)
	//  			return i + 1;
	// 
	// 	return -1;
		// 长子串使用 Sunday算法,
	register unsigned int next[256];
	for (i = 0; i < 256; i++)
		next[i] = nSubLen;
	for (i = nSubLen; i > 0; i--)
		next[pDes[i - 1]] = i;

	register unsigned char* naddr = pSrc + off;
	for (; naddr >= pSrc; naddr -= next[naddr[-1]])
		if (MyMemCmp2(naddr, pDes, nSubLen) == 0)
			return naddr - pSrc;

	return -1;
}

CXBytes 字节集替换(CXBytes& 欲替换其部分的字节集, int 起始替换位置, int 替换长度, CXBytes 用作替换的字节集)
{
	// 抄自黑月核心库 被封七号
	CXBytes fh;
	if (替换长度 == 0)
		return 欲替换其部分的字节集;
	if (欲替换其部分的字节集.size() == NULL)
		return 欲替换其部分的字节集;
	if (起始替换位置 < 0)
		起始替换位置 = 0;
	if (用作替换的字节集.size() < 替换长度 && 用作替换的字节集.size() >= 1)
		替换长度 = 用作替换的字节集.size();
	// 新长度 = 源长度 - 替换长度 + 子串长度
	// 起始点 + 替换长度 <= 源长度
	if (用作替换的字节集.size() >= 1) {
		if (起始替换位置 == 0) {
			fh.add((void*)用作替换的字节集.get(), 替换长度);
			int dz = (int)欲替换其部分的字节集.get();
			fh.add((void*)(dz + 替换长度), 欲替换其部分的字节集.size() - 替换长度);
			return fh;
		} else {
			fh.add((void*)欲替换其部分的字节集.get(), 起始替换位置);//2开始
			fh.add((void*)用作替换的字节集.get(), 替换长度);
			int dz = (int)欲替换其部分的字节集.get();
			dz += 起始替换位置 + 替换长度;
			fh.add((void*)(dz), 欲替换其部分的字节集.size() - 起始替换位置 - 替换长度);
			return fh;
		}
	} else {
		if (起始替换位置 == 0) {
			int dz = (int)欲替换其部分的字节集.get();
			dz += 替换长度;
			fh.add((void*)(dz), 欲替换其部分的字节集.size() - 替换长度);
			return fh;
		} else {
			fh.add((void*)欲替换其部分的字节集.get(), 起始替换位置);//2开始
			int dz = (int)欲替换其部分的字节集.get();
			dz += 起始替换位置 + 替换长度;
			fh.add((void*)(dz), 欲替换其部分的字节集.size() - 起始替换位置 - 替换长度);
			return fh;

		}
	}
	return fh;
}

int 寻找字节集(CXBytes& 被搜寻的字节集, CXBytes& 欲寻找的字节集, int 起始搜寻位置)
{
	return 被搜寻的字节集.findBytes(欲寻找的字节集, 起始搜寻位置);
}

CXText 子文本替换_(CXText 欲被替换的文本, CXText 欲被替换的子文本, CXText 用作替换的子文本, int 进行替换的起始位置, int 替换进行的次数, bool 是否区分大小写)
{// 被封七号 改
	CXText fh;
	int wbcd = 欲被替换的文本.size();
	if (wbcd == 0) return fh;
	//开始替换位置
	INT nStart = 进行替换的起始位置;
	int nSubLen = 用作替换的子文本.size();
	INT nDLen = 欲被替换的子文本.size();
	//替换次数
	INT nCount = 替换进行的次数;
	if (替换进行的次数 == -1)
		nCount = 0x7FFFFFFF;// 最大替换次数21亿

	if (nDLen <= 0 || nCount <= 0) // 关键参数不合法，直接返回原文本
		return 欲被替换的文本;
	int nPos = 0;
	if (进行替换的起始位置 > 0)
		fh.append2(欲被替换的文本, 进行替换的起始位置);
	wchar_t* pSub = (wchar_t*)欲被替换的文本.get();
	for (; nCount > 0; nCount--)
	{
		nPos = 欲被替换的文本.find2(欲被替换的子文本, 进行替换的起始位置);
		if (nPos == -1)
			break;
		fh.append2(pSub + 进行替换的起始位置, nPos - 1);

		if (nSubLen > 0)
			fh.append(用作替换的子文本);

		进行替换的起始位置 = nPos + nDLen;

	}
	if (进行替换的起始位置 < wbcd)
		fh.append2(pSub + 进行替换的起始位置, wbcd - 进行替换的起始位置);
	// 复制计算结果
	return fh;
}

CXBytes 十六进制文本转为字节集(const wchar_t* b)
{
	CXBytes zjj;
	zjj.addHex(b);
	return zjj;
}

CXText 字节集转为16进制文本(CXBytes& b)
{
	CXText wb;
	wb = b.toHex();
	return wb;
}

CXText  字符(wchar_t 欲取其字符的字符代码)
{
	CXText  ret;
	ret = 欲取其字符的字符代码;
	return ret;
}

int 取代码(const wchar_t* 欲取字符代码的文本, int 欲取其代码的字符位)
{
	const wchar_t* p = 欲取字符代码的文本;
	int index = 0;
	while (*p)
	{
		if (index == 欲取其代码的字符位)
			return (int)(*p);
		index++;
		p++;
	}
	return 0;
}


int 寻找文本(const wchar_t* pText, const wchar_t* pSubStr, int pos, BOOL dx)
{
	const wchar_t* pStart = pText + pos;
	const wchar_t* ret = NULL;
	if (dx) //不区分大小写
		ret = wcsistr(pStart, pSubStr);
	else // 区分大小写
		ret = wcsstr(pStart, pSubStr);
	if (ret)
		return ret - pText;
	return -1;
}

int 倒找文本(const wchar_t* pText, const wchar_t* pSubStr, int pos, BOOL dx)
{
	if (NULL == pText || NULL == pSubStr || 0 == *pText) return -1; //空文本直接返回
	if (0 == *pSubStr) return 0;
	if (pos < 0) return -1;

	INT nDesLen = wcslen(pSubStr);
	if (0 == pos)
	{
		pos = wcslen(pText) - nDesLen;
	} else
	{
		pos = pos - nDesLen;
		if (pos < 0) return -1;
	}
	int index = 0;
	const wchar_t* cp = pText;
	while (*cp)
	{
		if (index >= pos)
			break;

		index++;
		cp++;
	}

	if (dx) //不区分大小写
	{
		while (cp >= pText)
		{
			if (0 == _wcsnicmp(cp, pSubStr, nDesLen))
				return cp - pText;
			cp--;
		}
	} else  // 区分大小写
	{
		const wchar_t* s1, * s2;
		while (cp >= pText)
		{
			s1 = cp;
			s2 = pSubStr;
			while (*s1 && *s2 && !(*s1 - *s2))
				s1++, s2++;
			if (!*s2)
				return cp - pText;
			cp--;
		}
	}
	return -1;
}

CXText 到大写(const wchar_t* pText)
{
	if (NULL == pText) return L"";

	CXText ret = pText;
	text_upper((wchar_t*)ret.get());
	return ret;
}

CXText 到小写(const wchar_t* pText)
{
	if (NULL == pText) return L"";

	CXText ret = pText;
	text_lower((wchar_t*)ret.get());
	return ret;
}

CXText 到全角(const wchar_t* pText)
{
	if (NULL == pText) return L"";
	size_t nLen = wcslen(pText);
	if (nLen == 0) return NULL;

	const wchar_t* pszLast = pText + nLen;
	const wchar_t* pszFirst = pText;
	wchar_t* pszSrc = (wchar_t*)malloc( (nLen + 1)*2 );
	wchar_t* pszTmp = pszSrc;
	size_t sSublen;
	for (;;)
	{
		const wchar_t* pPos = wcsstr(pszFirst, L"\\");
		if (!pPos) break;
		sSublen = pPos - pszFirst;
		if (sSublen > 0)
		{
			wmemcpy(pszTmp, pszFirst, sSublen);
		}

		*(short*)(pszTmp + sSublen) = *(short*)L"＼";
		pszTmp += sSublen + 1;
		pszFirst = pPos + 1;
	}
	sSublen = pszLast - pszFirst;
	if (sSublen > 0)
	{
		wmemcpy(pszTmp, pszFirst, sSublen);
		pszTmp += sSublen;
	}
	pszTmp[0] = '\0';

	nLen = wcslen(pszSrc);

	CXText  ret;
	ret.resize(nLen);
	LCMapStringW(2052, LCMAP_FULLWIDTH, pszSrc, nLen, (wchar_t*)ret.get(), nLen);
	free(pszSrc);
	return ret;
}

CXText 到半角(const wchar_t* pText)
{
	if (NULL == pText) return L"";
	size_t nLen = wcslen(pText);
	if (nLen == 0)  return L"";

	const wchar_t* pszLast = pText + nLen;
	const wchar_t* pszFirst = pText;
	wchar_t* pszSrc = (wchar_t*)malloc( (nLen + 1)*2);
	wchar_t* pszTmp = pszSrc;
	size_t sSublen;
	for (;;)
	{
		const wchar_t* pPos = wcsstr(pszFirst, L"＼");
		if (!pPos) break;
		sSublen = pPos - pszFirst;
		if (sSublen > 0)
		{
			wmemcpy(pszTmp, pszFirst, sSublen);
		}
		pszTmp[sSublen] = '\\';
		pszTmp += sSublen + 1;
		pszFirst = pPos + 1;
	}
	sSublen = pszLast - pszFirst;
	if (sSublen > 0)
	{
		wmemcpy(pszTmp, pszFirst, sSublen);
		pszTmp += sSublen;
	}
	pszTmp[0] = '\0';

	nLen = wcslen(pszSrc);
	//INT nBufLen = nLen + 1;
	//char* pBJText = (char*)E_MAlloc(nBufLen);

	CXText  ret;
	ret.resize(nLen);
	LCMapString(2052, LCMAP_HALFWIDTH, pszSrc, nLen, (wchar_t*)ret.get(), nLen);
	free(pszSrc);
	return ret;
}

CXText 删全部空(const wchar_t* pText)
{
	if (NULL == pText) return L"";

	CXText  ret;
	const wchar_t* p = pText;
	while (*p)
	{
		if (' ' == *p || '\t' == *p)
		{
		} else
		{
			ret += *p;
		}
		p++;
	}
	return ret;
}

CXText 文本替换_易语言(const wchar_t* pText, int pos, int length, const wchar_t* pReplaceText)
{
	if (NULL == pText || NULL== pReplaceText) return L"";

	CXText  ret = pText;
	if(pReplaceText)
		ret.replace(pos, (pos + length), pReplaceText);
	else
		ret.replace(pos, (pos + length), L"");
	return ret;
}

CXText 子文本替换(const wchar_t* pText, const wchar_t* pSubText, const wchar_t* pReplaceText, int pos, int count, bool dx)
{
	if (NULL == pText || NULL== pSubText || NULL== pReplaceText) return L"";
	if (pos < 0) pos = 0;

	int index = 0;
	const wchar_t* p = pText;
	while (*p)
	{
		if (index >= pos)
			break;

		index++;
		p++;
	}
	if (NULL == *p) return L"";

	CXText  retText;
	if (index > 0)
		retText.append2(pText, p - pText);

	int subLen = wcslen(pSubText);
	int len = wcslen(pReplaceText);
	int rpCount = 0;
	const wchar_t* ret = NULL;
	while (*p)
	{
		if (dx) //区分大小写
			ret = wcsstr(p, pSubText);
		else
			ret = wcsistr(p, pSubText);
		if (NULL == ret)
			break;
		if ((ret - p) > 0)
			retText.append2(p, ret - p);
		retText += pReplaceText;
		p = ret + subLen;
		rpCount++;
		if (count>0 && rpCount >= count)
			break;
	}
	if (*p)
	{
		retText += p;
	}
	return retText;
}

CXText 取空白文本(int 大小)
{
	CXText mk;
	mk.resize(大小, ' ');
	return mk;
}

CXText 取重复文本(int count, const wchar_t* pText)
{
	if (count <= 0 || NULL == pText || 0 == *pText)
		return L"";

	CXText retText;
	for (int i = 0; i < count; i++)
		retText += pText;
	return retText;
}

int 文本比较(const wchar_t* str1, const wchar_t* str2, BOOL dx)
{
	if (dx)
		return _wcsicmp(str1, str2);
	return wcscmp(str1, str2);
}

CXVector<CXText> 分割文本(const wchar_t* pText, const wchar_t* pSplit)
{
	CXVector<CXText> rets = text_split2(pText, pSplit);
	return rets;
}

CXText 指针到文本(void* 内存文本指针)
{
	CXText source;
	source.append((const wchar_t*)内存文本指针);
	return source;
}
//------------------------------------
INT64 到时间(const wchar_t* pText)
{
	struct tm tm = { 0 };
	wchar_t* endptr;
	const wchar_t* ptr = pText;

	// 尝试将文本直接作为时间戳转换
	errno = 0;
	INT64 timestamp = wcstoull(pText, &endptr, 10);
	if (errno == 0 && *endptr == L'\0') {
		// 成功转换为数字，假设这是时间戳
		return timestamp;
	}

	// 设置默认时间为1970年1月1日
	tm.tm_year = 1970 - 1900;
	tm.tm_mon = 0;
	tm.tm_mday = 1;

	// 解析年份
	tm.tm_year = (wchar_t)wcstoul(ptr, &endptr, 10) - 1900;
	if (*endptr != L'年' && *endptr != L'/' && *endptr != L'-' && *endptr != L'.' && *endptr != L'\0') {
		return mktime(&tm); // 返回默认时间戳
	}
	ptr = endptr + 1;

	// 解析月份
	tm.tm_mon = (wchar_t)wcstoul(ptr, &endptr, 10) - 1;
	if (*endptr != L'月' && *endptr != L'/' && *endptr != L'-' && *endptr != L'\0') {
		return mktime(&tm);
	}
	ptr = endptr + 1;

	// 解析日期
	tm.tm_mday = (wchar_t)wcstoul(ptr, &endptr, 10);
	if (*endptr != L'日' && *endptr != L' ' && *endptr != L'/' && *endptr != L'-' && *endptr != L'\0') {
		return mktime(&tm);
	}
	ptr = endptr + 1;

	// 解析小时
	if (*ptr != L'\0') {
		tm.tm_hour = (wchar_t)wcstoul(ptr, &endptr, 10);
		if (*endptr != L'时' && *endptr != L':' && *endptr != L'/' && *endptr != L'-' && *endptr != L'\0') {
			return mktime(&tm);
		}
		ptr = endptr + 1;
	}

	// 解析分钟
	if (*ptr != L'\0') {
		tm.tm_min = (wchar_t)wcstoul(ptr, &endptr, 10);
		if (*endptr != L'分' && *endptr != L':' && *endptr != L'\0') {
			return mktime(&tm);
		}
		ptr = endptr + 1;
	}

	// 解析秒
	if (*ptr != L'\0') {
		tm.tm_sec = (wchar_t)wcstoul(ptr, &endptr, 10);
		if (*endptr != L'秒' && *endptr != L'\0') {
			return mktime(&tm);
		}
	}

	// 转换为时间戳
	return mktime(&tm);
}


INT64 增减时间(INT64 date, int flag, int addValue)
{
	struct tm  st;
	_localtime64_s(&st, &date);
	switch (flag)
	{
	case 1://#年份
		st.tm_year += addValue;
		break;
	case 2://#季度
		st.tm_mon += (addValue * 3);
		break;
	case 3://#月份
		st.tm_mon += addValue ;
		break;
	case 4://#周
		st.tm_mday += (addValue*7);
		break;
	case 5://#日
		st.tm_mday += addValue;
		break;
	case 6://#小时
		st.tm_hour += addValue;
		break;
	case 7://#分钟
		st.tm_min += addValue;
		break;
	case 8://#秒。
		st.tm_sec += addValue;
		break;
	}
	return mktime(&st);
}

double 取时间间隔(INT64 time1, INT64  time2, int flag)
{
	switch (flag)
	{
	case 1://#年份
	{	struct tm  st1, st2;
		_localtime64_s(&st1, &time1);
		_localtime64_s(&st2, &time2);
		return st1.tm_year - st2.tm_year;
	}
	case 2://#季度
	{
		struct tm  st1, st2;
		_localtime64_s(&st1, &time1);
		_localtime64_s(&st2, &time2);
		return ((st1.tm_year - st2.tm_year) * 12 - st2.tm_mon + st1.tm_mon) / 3;
	}
	case 3://#月份
	{
		struct tm  st1, st2;
		_localtime64_s(&st1, &time1);
		_localtime64_s(&st2, &time2);
		return (st1.tm_year - st2.tm_year) * 12 - st2.tm_mon + st1.tm_mon;
	}
	case 4://#周
	{
		double diff = difftime(time1, time2);
		double day_=(diff / 3600 / 24)+6; //+6不满一周 也算一周
		return (day_ / 7);
	}
	case 5://#日
	{
		double diff = difftime(time1, time2);
		double day_ = (diff / 3600 / 24);
		return day_;
	}
	case 6://#小时
	{
		double diff = difftime(time1, time2);
		return diff / 3600;
	}
	case 7://#分钟
	{
		double diff = difftime(time1, time2);
		return diff / 60;
	}
	case 8://#秒。
	{
		return difftime(time1, time2);
	}
	}
	return 0;
}

int  取某月天数(int year_, int month_)
{
	if (month_ <= 0 || month_ > 12 || year_ < 100 || year_>9999)
		return 0;
	DWORD nMonDay[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((year_ % 400 == 0) || (year_ % 100 != 0) && (year_ % 4 == 0))//闰年
		nMonDay[1] = 29; //二月
	return nMonDay[month_ - 1];
}

CXText  时间到文本(INT64  time_, int flag)
{
	tm tm_;
	_localtime64_s(&tm_, &time_);
	wchar_t buf[32] = { 0 };
	if (1==flag) //#全部转换
	{
		wcsftime(buf, 32, L"%Y年%m月%d日%H时%M分%S秒", &tm_);//wcsftime(buf, 32, L"%Y-%m-%d %H:%M:%S", &tm_);
	} else if (2 == flag) //#日期部分
	{
		wcsftime(buf, 32, L"%Y年%m月%d日", &tm_);//wcsftime(buf, 32, L"%Y-%m-%d", &tm_);
	} else if (3==flag) //#时间部分
	{
		wcsftime(buf, 32, L"%H时%M分%S秒", &tm_);//wcsftime(buf, 32, L"%H:%M:%S", &tm_);
	}
	return buf;
}

int 取时间部分(INT64  time_, int flag)
{
	tm tm_;
	_localtime64_s(&tm_, &time_);
	switch (flag)
	{
	case 1://#年份
		return tm_.tm_year + 1900;
	case 2://#季度
	{
		int nMonth = tm_.tm_mon/3;
		if (nMonth % 3) nMonth++;
		return nMonth;
	}
	case 3://#月份
		return tm_.tm_mon +1;
	case 4://#自年首周数
	{
		int nCountDay = tm_.tm_yday / 7;
		if (nCountDay % 7) nCountDay++;
		return nCountDay;
	}
	case 5://#日
		return tm_.tm_mday;
	case 6://#小时
		return tm_.tm_hour;
	case 7://#分钟
		return tm_.tm_min;
	case 8://#秒。
		return tm_.tm_sec;
	case 9://#星期几
		return tm_.tm_wday+1;
	case 10://#自年首天数
		return tm_.tm_yday+1;
	}
	return 0;
}

int  取年份(INT64 time_)
{
	tm tm_;
	_localtime64_s(&tm_, &time_);
	return tm_.tm_year + 1900;
}

int 取月份(INT64 time_)
{
	tm tm_;
	_localtime64_s(&tm_, &time_);
	return tm_.tm_mon + 1;
}

int 取日(INT64 time_)
{
	tm tm_;
	_localtime64_s(&tm_, &time_);
	return tm_.tm_mday;
}

int 取星期几(INT64 time_)
{
	tm tm_;
	_localtime64_s(&tm_, &time_);
	return tm_.tm_wday + 1;
}

int 取小时(INT64 time_)
{
	tm tm_;
	_localtime64_s(&tm_, &time_);
	return tm_.tm_hour;
}

int 取分钟(INT64 time_)
{
	tm tm_;
	_localtime64_s(&tm_, &time_);
	return tm_.tm_min;
}

int 取秒(INT64 time_)
{
	tm tm_;
	_localtime64_s(&tm_, &time_);
	return tm_.tm_sec;
}

INT64 指定时间(int year_, int mon_, int day_, int hour_, int min_, int sec_)
{
	struct tm time_info {};
	time_info.tm_year = year_ - 1900;  // 年份相对于1900年的差值
	time_info.tm_mon = mon_ - 1;       // 月份是从0开始计数的，所以需要减1
	time_info.tm_mday = day_;          // 日期
	time_info.tm_hour = hour_;         // 小时
	time_info.tm_min = min_;           // 分钟
	time_info.tm_sec = sec_;           // 秒

	return mktime(&time_info);  // 将tm结构转换为时间戳
}

INT64 取现行时间()
{
	__time64_t time_;
	_time64(&time_);
	return time_;
}

INT64 取现行时间_毫秒() {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER li;
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    __int64 timestamp = li.QuadPart / 10000 - 11644473600000LL;
    return timestamp;
}
BOOL 置现行时间(INT64 time_)
{
	struct tm timeInfo;
	_localtime64_s(&timeInfo, &time_);

	SYSTEMTIME sysTime;
	sysTime.wYear = timeInfo.tm_year + 1900;
	sysTime.wMonth = timeInfo.tm_mon + 1;
	sysTime.wDay = timeInfo.tm_mday;
	sysTime.wHour = timeInfo.tm_hour;
	sysTime.wMinute = timeInfo.tm_min;
	sysTime.wSecond = timeInfo.tm_sec;
	sysTime.wMilliseconds = 0;
	return SetLocalTime(&sysTime);
}

INT64 取日期(INT64 time_)
{
	tm tm_;
	_localtime64_s(&tm_, &time_);

	struct tm time_info {};
	time_info.tm_year = tm_.tm_year;  // 年份相对于1900年的差值
	time_info.tm_mon = tm_.tm_mon;    // 月份是从0开始计数的，所以需要减1
	time_info.tm_mday = tm_.tm_mday;  // 日期
	return mktime(&time_info);
}

INT64 取时间(INT64 time_)
{
	tm tm_;
	_localtime64_s(&tm_, &time_);

	struct tm time_info {};
	time_info.tm_year = 100;
	time_info.tm_mon = 0;
	time_info.tm_mday =1;

	time_info.tm_hour = tm_.tm_hour;         // 小时
	time_info.tm_min = tm_.tm_min;           // 分钟
	time_info.tm_sec = tm_.tm_sec;           // 秒
	return mktime(&time_info);
}

//-------------------------------------
BOOL ReadChnNum(__out CXText& retText, const wchar_t* pStrSrc, const wchar_t* pNumStr, const wchar_t* pNumLeven, INT nNum, INT& nPre)
{
	pNumLeven += ((5 - nNum) * 2);
	BOOL bAllZero = TRUE;
	for (INT i = 0; i < nNum; i++)
	{
		INT nOffset = pStrSrc[i] - 48;
		const wchar_t* pStr = pNumStr + nOffset * 2;

		if (nOffset != 0)
		{
			if (nPre == 0)
				retText += L"零";
			retText += pStr;

			pStr = pNumLeven + i * 2;
			retText += pStr;
			bAllZero = FALSE;
		}
		nPre = nOffset;
	}
	return bAllZero;
}

void IntNumToChn(CXText& retText, double dNum, BOOL bSml, INT& nPre)
{
	wchar_t bigChn[] = L"零\0壹\0贰\0叁\0肆\0伍\0陆\0柒\0捌\0玖\0";//48-57
	wchar_t smlChn[] = L"零\0一\0二\0三\0四\0五\0六\0七\0八\0九\0";
	wchar_t strNumLeven1[] = L"万\0仟\0佰\0拾\0\0";
	wchar_t strNumLeven2[] = L"万\0千\0百\0十\0\0";

	wchar_t str[MAX_PATH];
	const wchar_t* pText = NULL;
	swprintf_s(str, L"%.0f", dNum);
	INT nLen = wcslen(str);
	if (nLen > 13)
	{
		retText = L"溢出";
		return;
	}
	const wchar_t* pNum;
	const wchar_t* pNumLeven;
	if (bSml)
	{
		pNum = smlChn;
		pNumLeven = strNumLeven2;
	} else
	{
		pNum = bigChn;
		pNumLeven = strNumLeven1;
	}

	const wchar_t* pSrc = str;
	if (*pSrc == 45)
	{
		pSrc++;
		retText += L"负";
	}
	//万仟佰拾亿-仟佰拾万-仟佰拾个
	nPre = -1;
	if (nLen > 8)
	{
		INT nNum = nLen - 8;
		ReadChnNum(retText, pSrc, pNum, pNumLeven, nNum, nPre);
		retText += L"亿";
		pSrc += nNum;
		BOOL nAll0 = ReadChnNum(retText, pSrc, pNum, pNumLeven, 4, nPre);
		retText += L"万";
		pSrc += 4;
		ReadChnNum(retText, pSrc, pNum, pNumLeven, 4, nPre);
	} else if (nLen > 4)
	{
		INT nNum = nLen - 4;
		ReadChnNum(retText, pSrc, pNum, pNumLeven, nNum, nPre);
		retText += L"万";
		pSrc += nNum;
		ReadChnNum(retText, pSrc, pNum, pNumLeven, 4, nPre);
	} else
	{
		ReadChnNum(retText, pSrc, pNum, pNumLeven, nLen, nPre);
	}
}

void FloatNumToChn(CXText& retText, double dNum, BOOL bSml)//这里不能代入0值
{
	wchar_t bigChn[] = L"零\0壹\0贰\0叁\0肆\0伍\0陆\0柒\0捌\0玖\0";//48-57
	wchar_t smlChn[] = L"零\0一\0二\0三\0四\0五\0六\0七\0八\0九\0";
	wchar_t str[MAX_PATH];
	dNum = fabs(dNum);

	swprintf_s(str, L"%.2lf", dNum);
	const wchar_t* pSrc = str;
	while (*pSrc != 0 && *pSrc != '.')
		pSrc++;
	if (*pSrc == 0)
		return;
	pSrc++;

	const wchar_t* pNum;
	if (bSml)
		pNum = smlChn;
	else
		pNum = bigChn;

	retText += L"点";

	INT nOffset = pSrc[0] - 48;
	const wchar_t* pStr = pNum + nOffset * 2;
	retText += pStr;
	nOffset = pSrc[1] - 48;
	if (nOffset)
	{
		pStr = pNum + nOffset * 2;
		retText += pStr;
	}
}

CXText  数值到大写(double value_, BOOL dx)
{
	CXText retText;
	double dInt;
	double dFloat = modf(value_, &dInt);
	INT nLen = 3;
	if (dInt != 0)
	{
		INT nPre = 1;
		IntNumToChn(retText, dInt, dx, nPre);
	} else
	{
		retText += L"零";
	}

	if (dFloat != 0)
	{
		FloatNumToChn(retText, dFloat, dx);
	}
	return retText;
}

void FloatNumToRMB(CXText& retText, double dNum, BOOL bSml)//这里不能代入0值
{
	wchar_t bigChn[] = L"零\0壹\0贰\0叁\0肆\0伍\0陆\0柒\0捌\0玖\0";//48-57
	wchar_t smlChn[] = L"零\0一\0二\0三\0四\0五\0六\0七\0八\0九\0";
	wchar_t str[MAX_PATH];
	dNum = fabs(dNum);

	swprintf_s(str, L"%.2lf", dNum);
	const wchar_t* pSrc = str;
	while (*pSrc != 0 && *pSrc != '.')
		pSrc++;
	if (*pSrc == 0)
		return ;
	pSrc++;

	const wchar_t* pNum;
	if (bSml)
		pNum = smlChn;
	else
		pNum = bigChn;

	INT nOffset = pSrc[0] - 48;
	if (nOffset)
	{
		const wchar_t* pStr = pNum + nOffset * 2;
		retText += pStr;
		retText += L"角";
	}
	nOffset = pSrc[1] - 48;
	if (nOffset)
	{
		const wchar_t* pStr = pNum + nOffset * 2;
		retText += pStr;
		retText += L"分";
	}
}

CXText 数值到金额(double value_, BOOL dx)
{
	CXText retText;
	if (value_ < 0)
		return retText;
	double dInt;
	double dFloat = modf(value_, &dInt);
	if (0 == dInt && 0 == dFloat)
	{
		retText += L"零";
		return retText;
	}
	INT nLen = 64;
	INT nPre = 1;
	if (dInt != 0)
	{
		IntNumToChn(retText, dInt, dx, nPre);
		retText += L"元";
	}
	if (dFloat != 0)
	{
		if (dInt != 0)
			retText += L"零";
		FloatNumToRMB(retText, dFloat, dx);
	} else
	{
		retText += L"整";
	}

	return retText;
}

void LTrimZeroChr(wchar_t* str)
{
	wchar_t* z = NULL;
	wchar_t* p = NULL;
	//找小数点
	for (; *str; str++)
	{
		if (*str == '.')
		{
			p = str++;
			break;
		}
	}
	//
	if (p) //存在小数点
	{
		for (; *str; str++)
		{
			if (*str == '0')
			{
				if (!z)
				{
					z = str;
				}
			} else
			{
				z = NULL;
			}
		}
		//
		if (z)
		{
			if (z == p + 1) //以小数点结尾则删除小数点
			{
				*p = '\0';
			} else
			{
				*z = '\0';
			}
		}
	}
}

CXText  数值到格式文本(double value_, int flag, BOOL split)
{
	wchar_t str[MAX_PATH] = {0};
	wchar_t strFomar[MAX_PATH] = {0};
 	if (99==flag)
 	{
 		wcscpy_s(strFomar, L"%f");
 	} else
	{
		INT nNum = flag;
		if (nNum < 0)
			nNum = 0;
		if (nNum > 8)
			nNum = 8;
		swprintf_s(&strFomar[1], MAX_PATH-1,  L".%dlf", nNum);
		strFomar[0] = '%';
	}

	swprintf_s(str, strFomar, value_);
	if (99 == flag)
 		LTrimZeroChr(str);

	if (split)
	{
		wcscpy_s(strFomar, str);
		const wchar_t* pStr = strFomar;
		while (*pStr != 0 && *pStr != '.')
			pStr++;
		INT nNum = pStr - strFomar;
		pStr = strFomar;
		if (strFomar[0] == '-')
		{
			nNum--;
			pStr++;
		}
		if (nNum > 3)
		{
			INT nMax = nNum / 3;
			INT nMod = nNum % 3;
			if (nMod)
				nMax++;
			INT i = 0;
			wchar_t* pSrc = strFomar;
			wchar_t* pDest = str;

			while (i < nMax)
			{
				if (i == 0 && nMod)
					pStr += nMod;
				else
					pStr += 3;
				nNum = pStr - pSrc;

				if (i == nMax - 1)
				{
					wcscat_s(pDest, MAX_PATH-(pDest-(wchar_t*)str),pSrc);
					break;
				}
				wcsncpy_s(pDest, MAX_PATH-(pDest -(wchar_t*)str), pSrc, nNum);
				pDest += nNum;
				*pDest = ',';
				pDest++;
				*pDest = 0;

				pSrc += nNum;
				pStr = pSrc;
				i++;
			}
		}
	}
	return str;
}

CXText  取十六进制文本(int value_)
{
	wchar_t buf[16] = { 0 };
	_itow_s(value_, buf, 16, 16);
	return buf;
}

CXText  取八进制文本(int value_)
{
	wchar_t buf[16] = { 0 };
	_itow_s(value_, buf, 16, 8);
	return buf;
}

int 十六进制(const wchar_t* pHex)
{
	return wcstol(pHex, (wchar_t**)&pHex, 16);
}

int 二进制(const wchar_t* pBinary)
{
	return wcstol(pBinary, (wchar_t**)&pBinary, 2);
}

//----------------------------------------------
CMyMemFile::CMyMemFile(UINT nGrowBytes)
{
	m_nGrowBytes = nGrowBytes;
	m_nPosition = 0;
	m_nBufferSize = 0;
	m_nFileSize = 0;
	m_lpBuffer = NULL;
	m_bAutoDelete = TRUE;
}

CMyMemFile::CMyMemFile(BYTE* lpBuffer, UINT nBufferSize, UINT nGrowBytes)
{
	m_nGrowBytes = nGrowBytes;
	m_nPosition = 0;
	m_nBufferSize = nBufferSize;
	m_nFileSize = nGrowBytes == 0 ? nBufferSize : 0;
	m_lpBuffer = lpBuffer;
	m_bAutoDelete = FALSE;
}

void CMyMemFile::Attach(BYTE* lpBuffer, UINT nBufferSize, UINT nGrowBytes)
{
	m_nGrowBytes = nGrowBytes;
	m_nPosition = 0;
	m_nBufferSize = nBufferSize;
	m_nFileSize = nGrowBytes == 0 ? nBufferSize : 0;
	m_lpBuffer = lpBuffer;
	m_bAutoDelete = FALSE;
}

BYTE* CMyMemFile::Detach()
{
	BYTE* lpBuffer = m_lpBuffer;
	m_lpBuffer = NULL;
	m_nFileSize = 0;
	m_nBufferSize = 0;
	m_nPosition = 0;

	return lpBuffer;
}

CMyMemFile::~CMyMemFile()
{
	// Close should have already been called, but we check anyway
	if (m_lpBuffer)
		Close();
	m_nGrowBytes = 0;
	m_nPosition = 0;
	m_nBufferSize = 0;
	m_nFileSize = 0;
}

BYTE* CMyMemFile::Alloc(DWORD nBytes)
{
	return (BYTE*)malloc((UINT)nBytes);
}

BYTE* CMyMemFile::Realloc(BYTE* lpMem, DWORD nBytes)
{
	return (BYTE*)realloc(lpMem, (UINT)nBytes);
}

void CMyMemFile::Free(BYTE* lpMem)
{
	free(lpMem);
}

DWORD CMyMemFile::GetPosition() const
{
	return m_nPosition;
}

void CMyMemFile::GrowFile(DWORD dwNewLen)
{
	if (dwNewLen > m_nBufferSize)
	{
		// grow the buffer
		DWORD dwNewBufferSize = (DWORD)m_nBufferSize;

		// watch out for buffers which cannot be grown!
		if (m_nGrowBytes == 0)
			return;

		// determine new buffer size
		while (dwNewBufferSize < dwNewLen)
			dwNewBufferSize += m_nGrowBytes;

		// allocate new buffer
		BYTE* lpNew;
		if (m_lpBuffer == NULL)
			lpNew = Alloc(dwNewBufferSize);
		else
			lpNew = Realloc(m_lpBuffer, dwNewBufferSize);

		if (lpNew == NULL)
			return;

		m_lpBuffer = lpNew;
		m_nBufferSize = dwNewBufferSize;
	}
}

void CMyMemFile::SetLength(DWORD dwNewLen)
{
	if (dwNewLen > m_nBufferSize)
		GrowFile(dwNewLen);

	if (dwNewLen < m_nPosition)
		m_nPosition = dwNewLen;

	m_nFileSize = dwNewLen;
}

UINT CMyMemFile::Read(void* lpBuf, UINT nCount)
{
	if (nCount == 0)
		return 0;

	if (m_nPosition > m_nFileSize)
		return 0;

	UINT nRead;
	if (m_nPosition + nCount > m_nFileSize)
		nRead = (UINT)(m_nFileSize - m_nPosition);
	else
		nRead = nCount;

	memcpy((BYTE*)lpBuf, (BYTE*)m_lpBuffer + m_nPosition, nRead);
	m_nPosition += nRead;
	return nRead;
}

void CMyMemFile::Write(const void* lpBuf, UINT nCount)
{
	if (nCount == 0)
		return;

	if (m_nPosition + nCount > m_nBufferSize)
		GrowFile(m_nPosition + nCount);

	memcpy((BYTE*)m_lpBuffer + m_nPosition, (BYTE*)lpBuf, nCount);
	m_nPosition += nCount;

	if (m_nPosition > m_nFileSize)
		m_nFileSize = m_nPosition;
}

LONG CMyMemFile::Seek(LONG lOff, UINT nFrom)
{
	LONG lNewPos = m_nPosition;
	if (nFrom == begin)
		lNewPos = lOff;
	else if (nFrom == current)
		lNewPos += lOff;
	else if (nFrom == end)
		lNewPos = m_nFileSize + lOff;
	else
		return -1;

	if (lNewPos < 0)
		return -1;

	m_nPosition = lNewPos;
	return m_nPosition;
}

void CMyMemFile::Close()
{
#ifdef _DEBUG
	assert((m_lpBuffer == NULL && m_nBufferSize == 0) || !m_bAutoDelete || IsBadWritePtr(m_lpBuffer, (UINT)m_nBufferSize));
	assert(m_nFileSize <= m_nBufferSize);
#endif
	m_nGrowBytes = 0;
	m_nPosition = 0;
	m_nBufferSize = 0;
	m_nFileSize = 0;
	if (m_lpBuffer && m_bAutoDelete)
		Free(m_lpBuffer);
	m_lpBuffer = NULL;
}

void CMyMemFile::Abort()
{
	Close();
}

// only CMyMemFile supports "direct buffering" interaction with CArchive
UINT CMyMemFile::GetBufferPtr(UINT nCommand, UINT nCount,
	void** ppBufStart, void** ppBufMax)
{
	if (nCommand == bufferCheck)
		return 1;   // just a check for direct buffer support

	if (nCommand == bufferCommit)
	{
		// commit buffer
		m_nPosition += nCount;
		if (m_nPosition > m_nFileSize)
			m_nFileSize = m_nPosition;
		return 0;
	}

	// when storing, grow file as necessary to satisfy buffer request
	if (nCommand == bufferWrite && m_nPosition + nCount > m_nBufferSize)
		GrowFile(m_nPosition + nCount);

	// store buffer max and min
	*ppBufStart = m_lpBuffer + m_nPosition;

	// end of buffer depends on whether you are reading or writing
	if (nCommand == bufferWrite)
		*ppBufMax = m_lpBuffer + min(m_nBufferSize, m_nPosition + nCount);
	else
	{
		if (nCount == (UINT)-1)
			nCount = m_nBufferSize - m_nPosition;
		*ppBufMax = m_lpBuffer + min(m_nFileSize, m_nPosition + nCount);
		m_nPosition += LPBYTE(*ppBufMax) - LPBYTE(*ppBufStart);
	}

	// return number of bytes in returned buffer space (may be <= nCount)
	return LPBYTE(*ppBufMax) - LPBYTE(*ppBufStart);
}

DWORD CMyMemFile::GetFileSize()
{
	return m_nFileSize;
}


typedef void (*PDESTROY)(void);
FILEELEMENT* pFileList = NULL;
PDESTROY HFileDestroyAddress = NULL;
//extern "C" PDESTROY HFileDestroyAddress;

CRITICAL_SECTION csFileMan;
BOOL bIsCSinit = FALSE;

void enterfm()
{
	if (!bIsCSinit)
	{
		InitializeCriticalSection(&csFileMan);
		bIsCSinit = TRUE;
	}
	EnterCriticalSection(&csFileMan);
}
void leavefm()
{
	if (bIsCSinit)
		LeaveCriticalSection(&csFileMan);
}

void CloseEfile(FILEELEMENT* pFile)
{
	FILEELEMENT* pObjFile = pFileList;
	FILEELEMENT* pPreFile = NULL;

	enterfm();
	while (pObjFile)
	{
		if (pObjFile == pFile)
		{
			if (pPreFile)
			{//在表中
				pPreFile->pLast = pObjFile->pLast;
			} else
			{ //表首
				pFileList = (FILEELEMENT*)pObjFile->pLast;
				if (pFileList == NULL)
					HFileDestroyAddress = NULL;

			}
			if (pObjFile->FileHandle)
			{
				if (pObjFile->nType == 1 || pObjFile->nType == 3)
					CloseHandle((HANDLE)pObjFile->FileHandle);
				else if (pObjFile->nType == 2)
					delete (CMyMemFile*)pObjFile->FileHandle;
			}
			memset(pObjFile, 0, sizeof(FILEELEMENT));
			delete pObjFile;
			break;

		}
		pPreFile = pObjFile;
		pObjFile = (FILEELEMENT*)pObjFile->pLast;
	}
	leavefm();
}

void ResetFileIO()
{
	enterfm();
	FILEELEMENT* pObjFile = pFileList;
	pFileList = NULL;
	HFileDestroyAddress = NULL;

	while (pObjFile)
	{

		if (pObjFile->FileHandle)
		{
			if (pObjFile->nType == 1 || pObjFile->nType == 3)
				CloseHandle((HANDLE)pObjFile->FileHandle);
			else if (pObjFile->nType == 2)
				delete (CMyMemFile*)pObjFile->FileHandle;
		}

		FILEELEMENT* pPreFile = pObjFile;
		pObjFile = (FILEELEMENT*)pObjFile->pLast;
		memset(pPreFile, 0, sizeof(FILEELEMENT));
		delete pPreFile;
	}
	leavefm();
}

void AddFileMangerList(FILEELEMENT* pFile)
{
	enterfm();
	if (pFileList == NULL)//首个
		HFileDestroyAddress = (PDESTROY)ResetFileIO;
	pFile->pLast = pFileList;
	pFileList = pFile;
	leavefm();
}

vint 打开文件(const wchar_t* pFileName, int openType, int shareType)
{
	DWORD dwDesiredAccess, dwShareMode, dwCreationDisposition;

	if (0==openType)
	{//#读写
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
	} else
	{
		switch (openType)
		{
		case 1://#读入
			dwDesiredAccess = GENERIC_READ;
			dwCreationDisposition = OPEN_EXISTING;
			break;
		case 2://#写出
			dwDesiredAccess = GENERIC_WRITE;
			dwCreationDisposition = OPEN_EXISTING;
			break;
		case 4://#重写
			dwDesiredAccess = GENERIC_WRITE;
			dwCreationDisposition = CREATE_ALWAYS;
			break;
		case 5://#改写
			dwDesiredAccess = GENERIC_WRITE;
			dwCreationDisposition = OPEN_ALWAYS;
			break;
		case 6://#改读
			dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			dwCreationDisposition = OPEN_ALWAYS;
			break;
		default://#读写
			dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			dwCreationDisposition = OPEN_EXISTING;
			break;
		}
	}

	if (0==shareType)
		dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE);
	else
	{
		if (shareType == 2)
			dwShareMode = FILE_SHARE_WRITE;
		else if (shareType == 3)
			dwShareMode = FILE_SHARE_READ;
		else if (shareType == 4)
			dwShareMode = 0;
		else
			dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE);
	}

	HANDLE hFile = CreateFile(pFileName,
		dwDesiredAccess,
		dwShareMode,
		NULL,
		dwCreationDisposition,
		FILE_ATTRIBUTE_ARCHIVE,
		0);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		FILEELEMENT* pFile = new FILEELEMENT;
		pFile->nType = 1;
		pFile->FileHandle = hFile;
		AddFileMangerList(pFile);
		return (vint)pFile;
	}
	return 0;
}

vint 打开内存文件()
{
	CMyMemFile* pMemFile = new CMyMemFile();
	if (pMemFile)
	{
		FILEELEMENT* pFile = new FILEELEMENT;
		pFile->nType = 2;
		pFile->FileHandle = pMemFile;
		AddFileMangerList(pFile);
		return (vint)pFile;
	}
	return 0;
}

void 关闭文件(vint fileno_)
{
	if (fileno_)
		CloseEfile((FILEELEMENT*)fileno_);
}

void 关闭所有文件()
{
	if (pFileList)
		ResetFileIO();
}

BOOL IsInFileMangerList(FILEELEMENT* pFile)
{
	FILEELEMENT* pObjFile = pFileList;

	while (pObjFile)
	{
		if (pObjFile == pFile)
			return TRUE;
		if (pObjFile == (FILEELEMENT*)pObjFile->pLast)
			break;
		pObjFile = (FILEELEMENT*)pObjFile->pLast;
	}
	return FALSE;
}

BOOL 锁住文件(vint fileno_, int pos, int length, int time_)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return FALSE;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return FALSE;
	if (pFile->nType != 1)//内存文件
		return TRUE;
	HANDLE hFile = (HANDLE)pFile->FileHandle;
	//PMDATA_INF pArgInf = &ArgInf;
	OVERLAPPED Overlapped;
	memset(&Overlapped, 0, sizeof(OVERLAPPED));
	Overlapped.Offset = pos;
	DWORD dwFlags = LOCKFILE_FAIL_IMMEDIATELY;
	if (0!=time_)
	{
		if (time_ == -1)
			dwFlags = 0;
		else if (time_ > 0)
		{
			DWORD dwStart = ::GetTickCount();
			BOOL bRet;
			INT nVal;
			do
			{
				bRet = LockFileEx(hFile, LOCKFILE_FAIL_IMMEDIATELY, 0, length, 0, &Overlapped);
				nVal = GetTickCount() - dwStart;
			} while (bRet == FALSE && nVal <= time_);

			return bRet;
		}
	}
	return LockFileEx(hFile,
		dwFlags,
		0,
		length,
		0,
		&Overlapped);
}

BOOL 解锁文件(vint fileno_, int pos, int length)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return FALSE;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return FALSE;
	if (pFile->nType != 1)//内存文件
		return TRUE;
	HANDLE hFile = (HANDLE)pFile->FileHandle;
	return UnlockFile(hFile, pos, 0, length, 0);
}

BOOL 移动读写位置(vint fileno_, int pos, int length)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return FALSE;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return FALSE;
	//PMDATA_INF pArgInf = &ArgInf;
	BOOL bRet = FALSE;
	if (pFile->nType == 1 || pFile->nType == 3)//磁盘文件 加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwMoveMethod;
		switch (pos)
		{
		case 2://#文件尾
			dwMoveMethod = FILE_END;
			break;
		case 3://#现行位置
			dwMoveMethod = FILE_CURRENT;
			break;
		default://#文件首
			dwMoveMethod = FILE_BEGIN;
			break;
		}
		bRet = SetFilePointer(hFile, length, NULL, dwMoveMethod);

	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		DWORD dwMoveMethod;
		switch (pos)
		{
		case 2://#文件尾
			dwMoveMethod = CMyMemFile::end;
			break;
		case 3://#现行位置
			dwMoveMethod = CMyMemFile::current;
			break;
		default://#文件首
			dwMoveMethod = CMyMemFile::begin;
		}
		bRet = (pMemFile->Seek(length, dwMoveMethod) != -1);
	}
	return bRet;
}

BOOL 移到文件首(vint fileno_)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return FALSE;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return FALSE;

	BOOL bRet = FALSE;
	if (pFile->nType == 1 || pFile->nType == 3)//磁盘文件 加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		bRet = SetFilePointer(hFile, 0, NULL, FILE_BEGIN) != HFILE_ERROR;

	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		bRet = (pMemFile->Seek(0, CMyMemFile::begin) != -1);

	}
	return bRet;
}

BOOL 移到文件尾(vint fileno_)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return FALSE;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return FALSE;

	BOOL bRet = FALSE;
	if (pFile->nType == 1 || pFile->nType == 3)//磁盘文件 加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		bRet = SetFilePointer(hFile, 0, NULL, FILE_END);

	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		bRet = (pMemFile->Seek(0, CMyMemFile::end) != -1);

	}
	return bRet;
}

void E_RC4_updatetable(int len, unsigned char* keytable)
{
	int i;
	unsigned char tmp;
	unsigned char x = keytable[256];
	unsigned char y = keytable[257];
	for (i = 0; i < len; i++)
	{
		x = (x + 1);
		tmp = keytable[x];
		y = (y + tmp);
		keytable[x] = keytable[y];//交换s[x]和s[y]
		keytable[y] = tmp;
	}
	keytable[256] = x;
	keytable[257] = y;
}
void E_RC4(unsigned char* data, int datalen, unsigned char* keytable)
{
	int i;
	unsigned char tmp;
	unsigned char x = keytable[256];
	unsigned char y = keytable[257];
	for (i = 0; i < datalen; i++)
	{
		x = (x + 1);
		tmp = keytable[x];
		y = (y + tmp);
		keytable[x] = keytable[y];//交换s[x]和s[y]
		keytable[y] = tmp;
		data[i] ^= keytable[(unsigned char)(keytable[x] + tmp)];
	}
	keytable[256] = x;
	keytable[257] = y;
}
void E_RC4_init(unsigned char* keytable, unsigned char* key, int keylen)
{
	int i = 0, j = 0;
	unsigned char k[256] = { 0 };
	unsigned char tmp = 0;
	for (i = 0; i < 256; i++) {
		keytable[i] = i;
		k[i] = key[i % keylen];
	}
	for (i = 0; i < 256; i++) {
		tmp = keytable[i];
		j = (j + tmp + k[i]) % 256;
		keytable[i] = keytable[j];//交换s[i]和s[j]
		keytable[j] = tmp;
	}
	keytable[256] = 0;
	keytable[257] = 0;
}

#define ERC4_TLEN 258
#define ERC4_CHUNK 4096
BOOL E_RC4_Calc(int pos, unsigned char* pData, int nDlen, unsigned char* pKeytable, int nCryptStart, unsigned char* pMD5)
{
	int nCTLen, nCTRemain;
	int nTableLen, nTableIndex;
	int nChunk, nOChunk;
	int nF, nB;
	unsigned char pTableTMP[ERC4_TLEN];
	unsigned char* pTableData, * pTableData2;
	unsigned char pNewPass[40]; // 4 + 32 + 4

	memcpy(pTableTMP, pKeytable, ERC4_TLEN);

	nCTLen = nCryptStart;
	nCTRemain = nCTLen - pos;
	if (nCTRemain > 0)
	{
		pData += nCTRemain;
		nDlen -= nCTRemain;
		if (nDlen <= 0)
			return FALSE;
		pos = nCTLen;
	}

	E_RC4_updatetable(4 * (pos / ERC4_CHUNK), pTableTMP);
	nTableLen = 4 * (nDlen / ERC4_CHUNK) + 8;
	if (nTableLen % 4 > 0)
		nTableLen = nTableLen + nTableLen % 4;

	pTableData = new unsigned char[nTableLen];
	memset(pTableData, 0, nTableLen);
	pTableData2 = pTableData;
	E_RC4(pTableData, nTableLen, pTableTMP);

	nTableIndex = pos / ERC4_CHUNK;
	nChunk = pos % ERC4_CHUNK;
	if (nChunk >= 0)
	{
		nF = *((int*)pTableData);
		nB = nTableIndex ^ nF;

		*((int*)pNewPass) = nF;
		memcpy(pNewPass + 4, pMD5, 32);
		*((int*)(pNewPass + 36)) = nB;

		nTableIndex++;
		pTableData += 4;

		E_RC4_init(pTableTMP, pNewPass, 40);
		E_RC4_updatetable(nChunk + 36, pTableTMP);

		nOChunk = min(ERC4_CHUNK - nChunk, nDlen);
		E_RC4(pData, nOChunk, pTableTMP);

		nDlen -= nOChunk;
		pData += nOChunk;
	}

	while (nDlen > 0)
	{
		nF = *((int*)pTableData);
		nB = nTableIndex ^ nF;

		*((int*)pNewPass) = nF;
		memcpy(pNewPass + 4, pMD5, 32);
		*((int*)(pNewPass + 36)) = nB;

		nTableIndex++;
		pTableData += 4;

		E_RC4_init(pTableTMP, pNewPass, 40);
		E_RC4_updatetable(nChunk + 36, pTableTMP);

		if (nDlen <= ERC4_CHUNK)
		{
			E_RC4(pData, nDlen, pTableTMP);
			pData += nDlen;
			nDlen = 0;
			break;
		}
		E_RC4(pData, ERC4_CHUNK, pTableTMP);
		nDlen -= ERC4_CHUNK;
		pData += ERC4_CHUNK;
	}

	delete[]pTableData2;
	return TRUE;
}

CXBytes  读入字节集(vint fileno_, int length)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return NULL;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return NULL;
	if (length <= 0)
		return NULL;
	CXBytes  retBytes;

	LPBYTE pbRet = NULL;
	if (pFile->nType == 1)//磁盘文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		retBytes.resize(length);
		INT nRet = ReadFile(hFile, (BYTE*)retBytes.get(), length, &dwNumOfByteRead, 0);
		if (nRet == FALSE)
		{
			retBytes.clear();
		}
	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		retBytes.resize(length);
		DWORD dwNumOfByteRead = pMemFile->Read((void*)retBytes.get(), length);
		if (dwNumOfByteRead == 0)
		{
			retBytes.clear();
			return NULL;
		}
	} else if (pFile->nType == 3) //加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		LPBYTE pData = retBytes.resize(length); //new BYTE[nLen];
		INT nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		INT nRet = ReadFile(hFile, pData, length, &dwNumOfByteRead, 0);
		if (nRet == FALSE)
		{
			retBytes.clear();
		}
		length = dwNumOfByteRead;
		E_RC4_Calc(nPos, pData, length, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
	}
	return retBytes;
}

BOOL 写出字节集(vint fileno_, CXBytes& bytes_)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return NULL;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return NULL;

	BOOL bRet = FALSE;
	if (pFile->nType == 1)//磁盘文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		bRet = TRUE;
		if (WriteFile(hFile, bytes_.get(), bytes_.size(), &dwNumOfByteRead, NULL) == FALSE)
		{
			bRet = FALSE;
		}
	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		bRet = TRUE;
		pMemFile->Write(bytes_.get(), bytes_.size());
	} else if (pFile->nType == 3) //加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		bRet = TRUE;

		int length = bytes_.size();
		LPBYTE pData = new unsigned char[length];
		memcpy(pData, bytes_.get(), length);

		int nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		E_RC4_Calc(nPos, pData, length, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
		if (WriteFile(hFile, pData, length, &dwNumOfByteRead, NULL) == FALSE)
		{
			bRet = FALSE;
		}
		delete[]pData;
	}
	return bRet;
}

CXTextA  读入文本A(vint fileno_, int length)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	CXTextA  retText;
	if (pFile == NULL)
		return retText;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return retText;

	if (pFile->nType == 1)//磁盘文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		if (orgLoc == HFILE_ERROR)
		{
			SetFilePointer(hFile, 0, NULL, FILE_END);
			return retText;
		}
		if(length<=0)
			length = GetFileSize(hFile, NULL) - orgLoc;
		if (length <= 0) return retText;

		DWORD dwNumOfByteRead;
		char* buffer = (char*)malloc(length);
		if (FALSE == ReadFile(hFile, buffer, length, &dwNumOfByteRead, 0))
		{
			SetFilePointer(hFile, 0, NULL, FILE_END);
		} else
		{
			char* p = buffer;
			for (DWORD i =0;i< dwNumOfByteRead; i++)
			{
				if (0 == *p || 26 == *p)
					break;
				else
					retText += *p;
				p++;
			}
		}
		free(buffer);
	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;

		INT orgLoc = pMemFile->GetPosition();
		DWORD dwNumOfByteRead;

		LPSTR pBufStart, pBufMax;
		if (length <= 0) length = -1;
		dwNumOfByteRead = pMemFile->GetBufferPtr(CMyMemFile::bufferRead, length, (void**)&pBufStart, (void**)&pBufMax);

		char* p = pBufStart;
		for (DWORD i = 0; i < dwNumOfByteRead; i++)
		{
			if (0 == *p || 26 == *p)
				break;
			else
				retText += *p;
			p++;
		}
	}if (pFile->nType == 3)//加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		if (orgLoc == HFILE_ERROR)
		{
			SetFilePointer(hFile, 0, NULL, FILE_END);
			return retText;
		}

		if (length <= 0)
			length = GetFileSize(hFile, NULL) - orgLoc;
		if (length <= 0) return retText;

		char* buffer = (char*)malloc(length);
		DWORD dwNumOfByteRead;
		INT nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		INT nRet = ReadFile(hFile, buffer, length, &dwNumOfByteRead, 0);
		if (nRet == FALSE)
		{
			SetFilePointer(hFile, 0, NULL, FILE_END);
		} else
		{
			E_RC4_Calc(nPos, (unsigned char*)buffer, dwNumOfByteRead, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
			char* p = buffer;
			for (DWORD i = 0; i < dwNumOfByteRead; i++)
			{
				if (0 == *p || 26 == *p)
					break;
				else
					retText += *p;
				p++;
			}
		}
		free(buffer);
	}
	return retText;
}

BOOL 写出文本A(vint fileno_, const wchar_t* pText)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return NULL;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return NULL;

	BOOL bRet = FALSE;
	int length = wcslen(pText);
	if (pFile->nType == 1)//磁盘文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		int length = wcslen(pText);
		if (length > 0)
		{
			if (WriteFile(hFile, pText, length, &dwNumOfByteRead, NULL))
			{
				return TRUE;
			}
		}
	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		if (length > 0)
		{
			pMemFile->Write(pText, length);
			return TRUE;
		}
	} else if (pFile->nType == 3)//加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;

		char* buffer = (char*)malloc(length);
		memcpy(buffer, pText, length);

		INT nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		E_RC4_Calc(nPos, (unsigned char*)buffer, length, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
		if (WriteFile(hFile, buffer, length, &dwNumOfByteRead, NULL))
		{
			free(buffer);
			return TRUE;
		}
		free(buffer);
	}
	return FALSE;
}

CXTextA 读入一行(vint fileno_)
{
	CXTextA retText;
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return retText;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return retText;

	if (pFile->nType == 1)//磁盘文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		if (orgLoc == HFILE_ERROR)
		{
			SetFilePointer(hFile, 0, NULL, FILE_END);
			return retText;
		}

		DWORD dwNumOfByteRead;
		char ch;
		while (ReadFile(hFile, &ch, 1, &dwNumOfByteRead, 0) && dwNumOfByteRead > 0) {
			if (ch == '\n' || ch == '\r') {
				// 遇到换行符或回车符，停止读取
				if (ch == '\r')
					ReadFile(hFile, &ch, 1, &dwNumOfByteRead, 0);
				break;
			}
			retText += ch;
		}
	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		INT orgLoc = pMemFile->GetPosition();

		DWORD dwNumOfByteRead;
		LPSTR pBufStart, pBufMax;
		while (1)
		{
			dwNumOfByteRead = pMemFile->GetBufferPtr(CMyMemFile::bufferRead, 1, (void**)&pBufStart, (void**)&pBufMax);
			if (1 == dwNumOfByteRead)
			{
				if ('\n' == *pBufStart || '\r' == *pBufStart) {
					if ('\r' == *pBufStart)
						dwNumOfByteRead = pMemFile->GetBufferPtr(CMyMemFile::bufferRead, 1, (void**)&pBufStart, (void**)&pBufMax);
					break;
				}
				retText += *pBufStart;
			}
		}
	} else if (pFile->nType == 3)//加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		if (orgLoc == HFILE_ERROR)
		{
			SetFilePointer(hFile, 0, NULL, FILE_END);
			return retText;
		}

		DWORD dwNumOfByteRead;
		char ch;
		while (ReadFile(hFile, &ch, 1, &dwNumOfByteRead, 0) && dwNumOfByteRead > 0) {
			if (ch == '\n' || ch == '\r') {
				// 遇到换行符或回车符，停止读取
				if (ch == '\r')
					ReadFile(hFile, &ch, 1, &dwNumOfByteRead, 0);
				break;
			}
			retText += ch;
		}

		E_RC4_Calc(orgLoc, (unsigned char*)retText.get(), retText.size(), pFile->strTable, pFile->nCryptStart, pFile->strMD5);
	}
	return retText;
}

BOOL 写文本行A(vint fileno_, const char* pText)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return NULL;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return NULL;
	if (NULL == pText) return FALSE;

	BOOL bRet = FALSE;
	if (pFile->nType == 1)//磁盘文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		if (0 == *pText)
		{
			WriteFile(hFile, "\r\n", 2, &dwNumOfByteRead, NULL);
		} else
		{
			if (!WriteFile(hFile, pText, strlen(pText), &dwNumOfByteRead, NULL))
				return FALSE;
			WriteFile(hFile, "\r\n", 2, &dwNumOfByteRead, NULL);
		}
	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		if (0 == *pText)
		{
			pMemFile->Write("\r\n", 2);
		} else
		{
			pMemFile->Write(pText, strlen(pText));
			pMemFile->Write("\r\n", 2);
		}
	} else if (pFile->nType == 3) //加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;

		unsigned char pszRN[2] = {'\r', '\n'};
		int nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		if (0 == *pText)
		{
			E_RC4_Calc(nPos, pszRN, 2, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
			WriteFile(hFile, pszRN, 2, &dwNumOfByteRead, NULL);
		} else
		{
			CXTextA  str = pText;
			E_RC4_Calc(nPos, (unsigned char*)str.get(), str.size(), pFile->strTable, pFile->nCryptStart, pFile->strMD5);
			if (WriteFile(hFile, (unsigned char*)str.get(), str.size(), &dwNumOfByteRead, NULL))
			{
				nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
				E_RC4_Calc(nPos, pszRN, 2, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
				WriteFile(hFile, pszRN, 2, &dwNumOfByteRead, NULL);
			}
		}
	}
	return TRUE;
}

BOOL 读入数据(vint fileno_, CXBytes& bytes)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return NULL;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return NULL;

	CXBytes  retBytes;
	if (pFile->nType == 1)//磁盘文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		if (orgLoc == HFILE_ERROR)
		{
			SetFilePointer(hFile, 0, NULL, FILE_END);
			return NULL;
		}
		INT length = GetFileSize(hFile, NULL) - orgLoc;

		DWORD dwNumOfByteRead;
		retBytes.resize(length);
		INT nRet = ReadFile(hFile, (BYTE*)retBytes.get(), length, &dwNumOfByteRead, 0);
		if (nRet == FALSE)
		{
			retBytes.clear();
		}
	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		INT orgLoc = pMemFile->GetPosition();
		INT length = pMemFile->GetFileSize() - orgLoc;

		DWORD dwNumOfByteRead = pMemFile->Read((void*)retBytes.get(), length);
		if (dwNumOfByteRead == 0)
		{
			retBytes.clear();
			return NULL;
		}
	} else if (pFile->nType == 3) //加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		if (orgLoc == HFILE_ERROR)
		{
			SetFilePointer(hFile, 0, NULL, FILE_END);
			return NULL;
		}
		INT length = GetFileSize(hFile, NULL) - orgLoc;

		DWORD dwNumOfByteRead;
		LPBYTE pData = retBytes.resize(length); //new BYTE[nLen];
		INT nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		INT nRet = ReadFile(hFile, pData, length, &dwNumOfByteRead, 0);
		if (nRet == FALSE)
		{
			retBytes.clear();
		}
		length = dwNumOfByteRead;
		E_RC4_Calc(nPos, pData, length, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
	}
	return TRUE;
}

BOOL 写出数据(vint fileno_, CXBytes& bytes)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return FALSE;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return FALSE;
	if (bytes.empty()) return FALSE;

	if (pFile->nType == 1)//磁盘文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		if (!WriteFile(hFile, bytes.get(), bytes.size(), &dwNumOfByteRead, NULL))
			return FALSE;
	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		pMemFile->Write(bytes.get(), bytes.size());
	} else if (pFile->nType == 3) //加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;

		unsigned char pszRN[2] = { '\r', '\n' };
		int nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		CXBytes  bytes_ = bytes;
		E_RC4_Calc(nPos, (unsigned char*)bytes_.get(), bytes_.size(), pFile->strTable, pFile->nCryptStart, pFile->strMD5);
		if (!WriteFile(hFile, (unsigned char*)bytes_.get(), bytes_.size(), &dwNumOfByteRead, NULL))
			return FALSE;
	}
	return TRUE;
}

BOOL 是否在文件尾(vint fileno_, BOOL bIsReadEnd)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return TRUE;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return TRUE;

	INT nRet = TRUE;
	if (pFile->nType == 1 || pFile->nType == 3)//磁盘文件 加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwHi;
		UINT nLen = ::GetFileSize(hFile, &dwHi);
		UINT nLoc = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		if (nLoc != HFILE_ERROR)
		{
			if (nLoc < nLen)
			{
				nRet = FALSE;
				if (bIsReadEnd)
				{
					INT nData;
					LPSTR pStr = (LPSTR)&nData;
					DWORD dwByteTop;
					BOOL bRet = ReadFile(hFile, pStr, sizeof(BYTE), &dwByteTop, 0);
					SetFilePointer(hFile, nLoc, NULL, FILE_BEGIN);
					if (pFile->nType == 3) //加密文件
						E_RC4_Calc(nLoc, (unsigned char*)pStr, sizeof(BYTE), pFile->strTable, pFile->nCryptStart, pFile->strMD5);

					if (bRet && (*pStr == 0 || *pStr == 26))
						nRet = TRUE;
				}
			}
		}
	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		UINT nLen = pMemFile->GetFileSize();
		UINT nLoc = pMemFile->GetPosition();
		if (nLoc < nLen)
		{
			nRet = FALSE;
			if (bIsReadEnd)
			{
				INT nData;
				LPSTR pStr = (LPSTR)&nData;
				BOOL bRet = pMemFile->Read(pStr, sizeof(BYTE));
				pMemFile->Seek(nLoc, CMyMemFile::begin);
				if (bRet && (*pStr == 0 || *pStr == 26))
					nRet = TRUE;
			}
		}
	}
	return nRet;
}

int  取读写位置(vint fileno_)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return -1;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return -1;
	INT nRet = HFILE_ERROR;

	if (pFile->nType == 1 || pFile->nType == 3)//磁盘文件 加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		nRet = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		nRet = pMemFile->GetPosition();
	}
	return nRet;
}

int 取文件长度(vint fileno_)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return -1;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return -1;
	INT nRet = -1;
	if (pFile->nType == 1 || pFile->nType == 3)//磁盘文件 加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwHi;
		nRet = ::GetFileSize(hFile, &dwHi);
	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;
		nRet = pMemFile->GetFileSize();
	}
	return nRet;
}

BOOL 删除数据(vint fileno_, int length)
{
	FILEELEMENT* pFile = (FILEELEMENT*)fileno_;
	if (pFile == NULL)
		return NULL;
	if (IsInFileMangerList(pFile) == FALSE)//检测句柄合法性
		return NULL;
	//PMDATA_INF pArgInf = &ArgInf;
	if (length <= 0)
		return FALSE;

	BOOL bRet = FALSE;
	if (pFile->nType == 1)//磁盘文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		if (orgLoc == HFILE_ERROR)
			return FALSE;


		bRet = TRUE;
		DWORD dwNumOfByteRead;
		INT nBkLen = GetFileSize(hFile, NULL) - orgLoc - length;
		LPBYTE pBkData = NULL;
		if (nBkLen > 0)//有残余数据
		{
			pBkData = new BYTE[nBkLen];
			INT nLen = length;
			SetFilePointer(hFile, nLen, NULL, FILE_CURRENT);//后移到
			if (ReadFile(hFile, pBkData, nBkLen, &dwNumOfByteRead, 0) == FALSE)
			{
				delete[] pBkData;
				return FALSE;
			}
			SetFilePointer(hFile, orgLoc, NULL, FILE_BEGIN);//恢复原位置
			if (WriteFile(hFile, pBkData, nBkLen, &dwNumOfByteRead, NULL))
			{
				//				if(FlushFileBuffers(hFile)==FALSE)
				//					bRet = FALSE;
			} else
				bRet = FALSE;
			delete[] pBkData;
		}
		if (bRet)
			SetEndOfFile(hFile);

	} else if (pFile->nType == 2)//内存文件
	{
		CMyMemFile* pMemFile = (CMyMemFile*)pFile->FileHandle;

		INT orgLoc = pMemFile->GetPosition();

		INT nBkLen = pMemFile->GetFileSize() - orgLoc - length;
		LPBYTE pBkData = NULL;

		bRet = TRUE;
		if (nBkLen > 0)//有残余数据
		{
			pMemFile->Seek(length, CMyMemFile::current);
			pBkData = new BYTE[nBkLen];
			pMemFile->Read(pBkData, nBkLen);
			pMemFile->Seek(orgLoc, CMyMemFile::begin);//恢复
			pMemFile->Write(pBkData, nBkLen);
			orgLoc = pMemFile->GetPosition();
			delete[] pBkData;
		}
		pMemFile->SetLength(orgLoc);
	} else if (pFile->nType == 3)//加密文件
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		if (orgLoc == HFILE_ERROR)
			return FALSE;

		bRet = TRUE;
		DWORD dwNumOfByteRead;
		INT nBkLen = GetFileSize(hFile, NULL) - orgLoc - length;
		INT nPos;
		LPBYTE pBkData = NULL;
		if (nBkLen > 0)//有残余数据
		{
			pBkData = new BYTE[nBkLen];
			INT nLen = length;
			SetFilePointer(hFile, nLen, NULL, FILE_CURRENT);//后移到
			nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
			if (ReadFile(hFile, pBkData, nBkLen, &dwNumOfByteRead, 0) == FALSE)
			{
				delete[] pBkData;
				return FALSE;
			}
			nBkLen = dwNumOfByteRead;
			E_RC4_Calc(nPos, (unsigned char*)pBkData, nBkLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);

			SetFilePointer(hFile, orgLoc, NULL, FILE_BEGIN);//恢复原位置
			nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
			E_RC4_Calc(nPos, (unsigned char*)pBkData, nBkLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
			if (!WriteFile(hFile, pBkData, nBkLen, &dwNumOfByteRead, NULL))
				bRet = FALSE;

			delete[] pBkData;
		}
		if (bRet)
			SetEndOfFile(hFile);
	}
	return bRet;
}

void swap_hex(unsigned char* str, int len)
{
	for (int i = 0; i < len / 2; i += sizeof(WORD))
	{
		WORD temp = *(WORD*)(str + len - i - sizeof(WORD));
		*(WORD*)(str + len - i - sizeof(WORD)) = *(WORD*)(str + i);
		*(WORD*)(str + i) = temp;
	}
}

vint  打开加密文件(const wchar_t* pFileName, int openMode, int shareMode, const wchar_t* pass, int length)
{
	if (NULL == pFileName || 0 == *pFileName) return 0;

	DWORD dwDesiredAccess, dwShareMode, dwCreationDisposition;
	switch (openMode)
	{
	case 1://#读入
		dwDesiredAccess = GENERIC_READ;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	case 2://#写出
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	case 4://#重写
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = CREATE_ALWAYS;
		break;
	case 5://#改写
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = OPEN_ALWAYS;
		break;
	case 6://#改读
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_ALWAYS;
		break;
	default://#读写
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	}
	
	if (shareMode == 2)
		dwShareMode = FILE_SHARE_WRITE;
	else if (shareMode == 3)
		dwShareMode = FILE_SHARE_READ;
	else if (shareMode == 4)
		dwShareMode = 0;
	else
		dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE);

	HANDLE hFile = CreateFile(pFileName,
		dwDesiredAccess,
		dwShareMode,
		NULL,
		dwCreationDisposition,
		FILE_ATTRIBUTE_ARCHIVE,
		0);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		FILEELEMENT* pFile = new FILEELEMENT;
		if (!pass || !*(pass))
		{
			pFile->nType = 1; // 普通无密码文件
		} else
		{
			int nKeylen = wcslen(pass)*2;
			pFile->nType = 3; // 有密码文件
#ifdef XCL_MD5_H
			GetBufMD5(pFile->strMD5, (unsigned char*)pass, nKeylen);
#else
			xcl_log("*打开加密文件() 需要包含MD5模块");
#endif
			swap_hex(pFile->strMD5, 32); //反转MD5

			memset(pFile->strTable, 0, 258);
			E_RC4_init(pFile->strTable, (unsigned char*)pass, nKeylen);

			//明文区长度
			if (length<0)
				pFile->nCryptStart = 0;
			else
				pFile->nCryptStart = length;
		}

		pFile->FileHandle = hFile;
		AddFileMangerList(pFile);
		return (vint)pFile;
	}
	return 0;
}

BOOL  运行(const wchar_t* pCommandline, BOOL bWait, int nShow)
{
	STARTUPINFO startupinfo;
	PROCESS_INFORMATION pinfo;

	startupinfo.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&startupinfo);
	startupinfo.hStdOutput = NULL;
	startupinfo.hStdError = NULL;
	startupinfo.dwFlags = STARTF_USESHOWWINDOW;

	switch (nShow)
	{
	case 1:
		startupinfo.wShowWindow = SW_HIDE;
		break;
	case 3:
		startupinfo.wShowWindow = SW_SHOWMINIMIZED;
		break;
	case 4:
		startupinfo.wShowWindow = SW_SHOWMAXIMIZED;
		break;
	case 5:
		startupinfo.wShowWindow = SW_SHOWNOACTIVATE;
		break;
	case 6:
		startupinfo.wShowWindow = SW_SHOWMINNOACTIVE;
		break;
	default:
		startupinfo.wShowWindow = SW_SHOW;
	}

	// Create process
	BOOL bRet = CreateProcess(NULL, (wchar_t*)pCommandline, NULL, NULL, TRUE, NULL, NULL, NULL, &startupinfo, &pinfo);
	if (bRet)
	{
		if (bWait)
			WaitForSingleObject(pinfo.hProcess, INFINITE);
		CloseHandle(pinfo.hProcess);
		CloseHandle(pinfo.hThread);
	}
	return bRet;
}


CXText  取剪辑板文本()
{
	CXText retText;
	if (OpenClipboard(NULL))
	{
		HANDLE hClip = GetClipboardData(CF_UNICODETEXT);
		if (hClip)
		{
			const wchar_t* pStr = (const wchar_t*)GlobalLock(hClip);
			if (pStr && *pStr)
				retText = pStr;
			GlobalUnlock(hClip);
		}
		CloseClipboard();
	}
	return retText;
}

BOOL 置剪辑板文本(const wchar_t* pText)
{
	BOOL bRet = FALSE;
	if (pText && *pText && OpenClipboard(NULL))
	{
		EmptyClipboard();
		INT nLen = wcslen(pText) + 1;
		HGLOBAL hClip = GlobalAlloc(0x42, nLen*2);
		if (hClip)
		{
			LPWSTR pStr = (LPWSTR)GlobalLock(hClip);
			wmemcpy(pStr, pText, nLen);
			GlobalUnlock(hClip);
			SetClipboardData(CF_UNICODETEXT, hClip);
			bRet = TRUE;
		}
		CloseClipboard();
	}
	return bRet;
}

BOOL 置剪辑板位图(const CXBytes& buffer)
{
	BOOL bRet = FALSE;
	if (OpenClipboard(NULL))
	{
		// 创建兼容性位图
		BITMAPFILEHEADER FileHeader;
		BITMAPINFOHEADER InfoHeader;
		BITMAPFILEHEADER* pFileHeader = &FileHeader;
		BITMAPINFOHEADER* pInfoHeader = &InfoHeader;
		HDC hdcScreen = GetDC(NULL);                  // 获取屏幕DC
		HDC hdcMemDC = CreateCompatibleDC(hdcScreen); // 创建内存DC

		// 解析位图文件头和信息头
		if (buffer.size() < sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER))
		{
			ReleaseDC(NULL, hdcScreen);
			DeleteDC(hdcMemDC);
			return NULL; // 数据不足
		}
		memcpy(pFileHeader, &buffer[0], sizeof(BITMAPFILEHEADER));
		memcpy(pInfoHeader, &buffer[sizeof(BITMAPFILEHEADER)], sizeof(BITMAPINFOHEADER));

		// 创建兼容位图
		HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, pInfoHeader->biWidth, pInfoHeader->biHeight);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMemDC, hBitmap);

		// 复制位图数据到兼容位图
		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(bmi));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = pInfoHeader->biWidth;
		bmi.bmiHeader.biHeight = pInfoHeader->biHeight;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = pInfoHeader->biBitCount;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = 0; // 可设为0，因为下面是逐行复制

		// 跳过文件头和信息头，获取到位图数据的起始位置
		const BYTE* pBits = buffer.getPtr() + pFileHeader->bfOffBits;

		// 逐行复制位图数据，从底部开始复制到兼容位图的设备上下文
		for (int y = pInfoHeader->biHeight - 1; y >= 0; --y)
		{
			int srcY = (pInfoHeader->biHeight - 1 - y); // 计算源数据中的行索引
			BYTE* pDstLine = (BYTE*)bmi.bmiColors + (srcY * bmi.bmiHeader.biWidth * (bmi.bmiHeader.biBitCount / 8));
			SetDIBits(hdcMemDC, hBitmap, srcY, 1, pBits, &bmi, DIB_RGB_COLORS);
			// 或者使用下面的代码行直接操作像素数据（如果biBitCount是24或32）
			// memcpy(pDstLine, pBits, bmi.bmiHeader.biWidth * (bmi.bmiHeader.biBitCount / 8));
			pBits += ((pInfoHeader->biWidth * pInfoHeader->biBitCount + 31) / 32) * 4; // 移到下一行数据的开始位置
		}

		// 清理
		SelectObject(hdcMemDC, hOldBitmap);
		DeleteDC(hdcMemDC);
		ReleaseDC(NULL, hdcScreen);

		EmptyClipboard();
		// 置入位图句柄到剪贴板，不需要DeleteObject(hBitmap); 它属于剪贴板了
		if (!SetClipboardData(CF_BITMAP, hBitmap)) {
			// 置入失败，释放hBitmap
			DeleteObject(hBitmap);
			return FALSE;
		}
		bRet = TRUE;

		CloseClipboard();
	}
	return bRet;
}

BOOL 剪辑板中可有文本()
{
	BOOL bRet = FALSE;
	if (OpenClipboard(NULL))
	{
		HANDLE hClip = GetClipboardData(CF_UNICODETEXT);
		if (hClip)
			bRet = TRUE;
		CloseClipboard();
	}
	return bRet;
}

void 清除剪辑板()
{
	if (OpenClipboard(NULL))
	{
		EmptyClipboard();
		CloseClipboard();
	}
}

int 取屏幕宽度()
{
	return GetSystemMetrics(SM_CXSCREEN);
}

int 取屏幕高度()
{
	return GetSystemMetrics(SM_CYSCREEN);
}

int 取鼠标水平位置()
{
	POINT point;
	if (GetCursorPos(&point))
		return point.x;
	return 0;
}
int 取鼠标垂直位置()
{
	POINT point;
	if (GetCursorPos(&point))
		return point.y;
	return 0;
}

int 取颜色数()
{
	HDC hdc = ::GetDC(NULL);
	INT nRet = GetDeviceCaps(hdc, COLORRES);
	::ReleaseDC(NULL, hdc);
	return (1 << nRet);
}

int 信息框(const wchar_t* 提示信息, int 按钮, const wchar_t* 窗口标题, HWND 父窗口)
{
	return MessageBox(父窗口, 提示信息, 窗口标题, (UINT)按钮)-1;
}

void 鸣叫()
{
	::MessageBeep(0xffffffff);
}

HCURSOR __hCurOld = NULL;
void 置等待鼠标()
{
	if (__hCurOld == NULL)
	{
		HCURSOR hCur = LoadCursor(NULL, IDC_WAIT);
		__hCurOld = SetCursor(hCur);
	}
}

void 恢复鼠标()
{
	if (__hCurOld)
	{
		SetCursor(__hCurOld);
		__hCurOld = NULL;
	}
}

CXText  取文本注册项(int root_, const wchar_t* fullPathItemName, const wchar_t* pDefaultText)
{
	if (NULL == fullPathItemName || 0 == *fullPathItemName) return pDefaultText;
	if(NULL== pDefaultText) pDefaultText = L"";

	std::wstring  itemName_ = fullPathItemName;
	const wchar_t* 根键名称 = nullptr;
	size_t ss = itemName_.rfind(L"\\");
	std::wstring route = itemName_.substr(0, ss);
	std::wstring name = itemName_.substr(ss + 1, itemName_.size() - ss - 1);
	HKEY 根键 = NULL;

	// 根据传入的根目录参数选择相应的根键
	switch (root_) {
	case 1: // #根类
		根键 = HKEY_CLASSES_ROOT;
		根键名称 = L"HKEY_CLASSES_ROOT";
		break;
	case 2: // #现行设置
		根键 = HKEY_CURRENT_CONFIG;
		根键名称 = L"HKEY_CURRENT_CONFIG";
		break;
	case 3: // #现行用户
		根键 = HKEY_CURRENT_USER;
		根键名称 = L"HKEY_CURRENT_USER";
		break;
	case 4: // #本地机器
		根键 = HKEY_LOCAL_MACHINE;
		根键名称 = L"HKEY_LOCAL_MACHINE";
		break;
	case 5: // #所有用户
		根键 = HKEY_USERS;
		根键名称 = L"HKEY_USERS";
		break;
	default:
		return pDefaultText;
	}

	HKEY phkResult = {};
	LSTATUS lResult = RegOpenKeyEx(根键, route.c_str(), 0, KEY_READ, &phkResult);
	if (lResult == ERROR_SUCCESS) {

		DWORD dataSize = 0;
		if (RegQueryValueEx(phkResult, name.c_str(), NULL, NULL, NULL, &dataSize) != ERROR_SUCCESS) {
			RegCloseKey(phkResult);
			return pDefaultText;
		}
		wchar_t* buffer = new wchar_t[dataSize + 1]; // 用于存储注册表值的缓冲区
		DWORD bufferSize = dataSize + 1; // 缓冲区的大小

		if (RegQueryValueEx(phkResult, name.c_str(), NULL, NULL, (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS) {
			RegCloseKey(phkResult);
			CXText retText = buffer;
			delete []buffer;
			return retText;
		} else {
			RegCloseKey(phkResult);
			delete[]buffer;
			return pDefaultText;
		}
	} else {
		RegCloseKey(phkResult);
		return pDefaultText;
	}
	return pDefaultText;
}

int 取数值注册项(int 根目录, const wchar_t* fullPathItemName, int defaultValue)
{
	if (NULL == fullPathItemName ||0== *fullPathItemName) return defaultValue;

	HKEY 根键 = NULL;
	const wchar_t* 根键名称 = nullptr;
	std::wstring 全路径注册项名 = fullPathItemName;
	size_t ss =  全路径注册项名.rfind(L"\\");
	std::wstring route = 全路径注册项名.substr(0, ss);
	std::wstring name = 全路径注册项名.substr(ss + 1, 全路径注册项名.size() - ss - 1);

	// 根据传入的根目录参数选择相应的根键
	switch (根目录) {
	case 1: // #根类
		根键 = HKEY_CLASSES_ROOT;
		根键名称 = L"HKEY_CLASSES_ROOT";
		break;
	case 2: // #现行设置
		根键 = HKEY_CURRENT_CONFIG;
		根键名称 = L"HKEY_CURRENT_CONFIG";
		break;
	case 3: // #现行用户
		根键 = HKEY_CURRENT_USER;
		根键名称 = L"HKEY_CURRENT_USER";
		break;
	case 4: // #本地机器
		根键 = HKEY_LOCAL_MACHINE;
		根键名称 = L"HKEY_LOCAL_MACHINE";
		break;
	case 5: // #所有用户
		根键 = HKEY_USERS;
		根键名称 = L"HKEY_USERS";
		break;
	default:
		return defaultValue;
	}

	HKEY phkResult = {};
	LSTATUS lResult = RegOpenKeyEx(根键, route.c_str(), 0, KEY_READ, &phkResult);
	if (lResult == ERROR_SUCCESS) {

		wchar_t buffer[4]; // 用于存储注册表值的缓冲区
		DWORD bufferSize = sizeof(buffer); // 缓冲区的大小
		if (RegQueryValueEx(phkResult, name.c_str(), NULL, NULL, (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS) {
			RegCloseKey(phkResult);
			return *reinterpret_cast<int*>(buffer);
		} else {
			RegCloseKey(phkResult);
			return defaultValue;
		}
	} else {
		RegCloseKey(phkResult);
		return defaultValue;
	}
	return defaultValue;
}

CXBytes 取字节集注册项(int root_, const wchar_t* fullPathItemName, CXBytes* defaultValue)
{
	HKEY 根键 = NULL;
	std::wstring 全路径注册项名 = fullPathItemName;
	const wchar_t* 根键名称 = nullptr;
	size_t ss = 全路径注册项名.rfind(L"\\");
	std::wstring route = 全路径注册项名.substr(0, ss);
	std::wstring name = 全路径注册项名.substr(ss + 1, 全路径注册项名.size() - ss - 1);

	// 根据传入的根目录参数选择相应的根键
	switch (root_) {
	case 1: // #根类
		根键 = HKEY_CLASSES_ROOT;
		根键名称 = L"HKEY_CLASSES_ROOT";
		break;
	case 2: // #现行设置
		根键 = HKEY_CURRENT_CONFIG;
		根键名称 = L"HKEY_CURRENT_CONFIG";
		break;
	case 3: // #现行用户
		根键 = HKEY_CURRENT_USER;
		根键名称 = L"HKEY_CURRENT_USER";
		break;
	case 4: // #本地机器
		根键 = HKEY_LOCAL_MACHINE;
		根键名称 = L"HKEY_LOCAL_MACHINE";
		break;
	case 5: // #所有用户
		根键 = HKEY_USERS;
		根键名称 = L"HKEY_USERS";
		break;
	default:
		return defaultValue ? *defaultValue : CXBytes();
	}

	HKEY phkResult = {};
	LSTATUS lResult = RegOpenKeyEx(根键, route.c_str(), 0, KEY_READ, &phkResult);
	if (lResult == ERROR_SUCCESS) {

		DWORD dataSize = 0;
		if (RegQueryValueEx(phkResult, name.c_str(), NULL, NULL, NULL, &dataSize) != ERROR_SUCCESS) {
			RegCloseKey(phkResult);
			return defaultValue ? *defaultValue : CXBytes();
		}
		char* buffer = new char[dataSize + 1]; // 用于存储注册表值的缓冲区
		DWORD bufferSize = dataSize + 1; // 缓冲区的大小

		if (RegQueryValueEx(phkResult, name.c_str(), NULL, NULL, (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS) {
			RegCloseKey(phkResult);

			CXBytes bytes_;
			for (size_t i = 0; i < dataSize; i++) {
				bytes_.addByte(buffer[i]);
			}
			delete[]buffer;
			return bytes_;
		} else {
			delete[]buffer;
			RegCloseKey(phkResult);
			return defaultValue ? *defaultValue : CXBytes();
		}
	} else {
		RegCloseKey(phkResult);
		return defaultValue ? *defaultValue : CXBytes();
	}
	return defaultValue ? *defaultValue : CXBytes();
}

BOOL 创建注册表路径(HKEY 根键, const std::wstring& 路径)
{
	std::vector<std::wstring> 子项列表;
	size_t pos = 0;
	size_t lastPos = 0;

	while ((pos = 路径.find('\\', lastPos)) != std::string::npos) {
		子项列表.push_back(路径.substr(lastPos, pos - lastPos));
		lastPos = pos + 1;
	}
	子项列表.push_back(路径.substr(lastPos));

	HKEY phkResult = 根键;
	LSTATUS lResult = ERROR_SUCCESS;

	for (const auto& 子项 : 子项列表) {
		lResult = RegCreateKeyEx(phkResult, 子项.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, &phkResult, nullptr);
		if (lResult != ERROR_SUCCESS) {
			return false;
		}
	}
	return true;
}

BOOL 写注册项(int root_, const wchar_t* fullPathItemName, int value_)
{
	if (NULL == fullPathItemName) return FALSE;
	HKEY 根键 = NULL;
	std::wstring  全路径注册项名 = fullPathItemName;
	size_t ss = 全路径注册项名.rfind(L"\\");
	std::wstring route = 全路径注册项名.substr(0, ss);
	std::wstring name = 全路径注册项名.substr(ss + 1, 全路径注册项名.size() - ss - 1);

	// 根据传入的根目录参数选择相应的根键
	switch (root_) {
	case 1: // #根类
		根键 = HKEY_CLASSES_ROOT;
		break;
	case 2: // #现行设置
		根键 = HKEY_CURRENT_CONFIG;
		break;
	case 3: // #现行用户
		根键 = HKEY_CURRENT_USER;
		break;
	case 4: // #本地机器
		根键 = HKEY_LOCAL_MACHINE;
		break;
	case 5: // #所有用户
		根键 = HKEY_USERS;
		break;
	default:
		return false;
	}

	if (!创建注册表路径(根键, route)) {
		return false;
	}
	HKEY phkResult = {};
	LSTATUS lResult = RegOpenKeyEx(根键, route.c_str(), 0, KEY_WRITE, &phkResult);
	if (lResult == ERROR_SUCCESS) {

		LSTATUS SS = RegSetValueEx(phkResult, name.c_str(), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value_), sizeof(value_));
		RegCloseKey(phkResult);
		if (SS == ERROR_SUCCESS) {
			return true;
		}
	}
	return false;
}

BOOL 写注册项(int root_, const wchar_t* fullPathItemName, const wchar_t* value_)
{
	if (NULL == fullPathItemName) return FALSE;
	if (NULL == value_) return FALSE;

	HKEY 根键 = NULL;
	std::wstring  全路径注册项名 = fullPathItemName;
	size_t ss = 全路径注册项名.rfind(L"\\");
	std::wstring route = 全路径注册项名.substr(0, ss);
	std::wstring name = 全路径注册项名.substr(ss + 1, 全路径注册项名.size() - ss - 1);

	// 根据传入的根目录参数选择相应的根键
	switch (root_) {
	case 1: // #根类
		根键 = HKEY_CLASSES_ROOT;
		break;
	case 2: // #现行设置
		根键 = HKEY_CURRENT_CONFIG;
		break;
	case 3: // #现行用户
		根键 = HKEY_CURRENT_USER;
		break;
	case 4: // #本地机器
		根键 = HKEY_LOCAL_MACHINE;
		break;
	case 5: // #所有用户
		根键 = HKEY_USERS;
		break;
	default:
		return false;
	}

	if (!创建注册表路径(根键, route)) {
		return false;
	}
	HKEY phkResult = {};
	LSTATUS lResult = RegOpenKeyEx(根键, route.c_str(), 0, KEY_WRITE, &phkResult);
	if (lResult == ERROR_SUCCESS) {

		LSTATUS SS = RegSetValueEx(phkResult, name.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(value_), wcslen(value_)*2+2);
		RegCloseKey(phkResult);
		if (SS == ERROR_SUCCESS) {
			return true;
		}
	}
	return false;
}

BOOL 写注册项(int root_, const wchar_t* fullPathItemName, CXBytes& value_)
{
	if (NULL == fullPathItemName) return FALSE;

	HKEY 根键 = NULL;
	std::wstring  全路径注册项名 = fullPathItemName;
	size_t ss = 全路径注册项名.rfind(L"\\");
	std::wstring route = 全路径注册项名.substr(0, ss);
	std::wstring name = 全路径注册项名.substr(ss + 1, 全路径注册项名.size() - ss - 1);

	// 根据传入的根目录参数选择相应的根键
	switch (root_) {
	case 1: // #根类
		根键 = HKEY_CLASSES_ROOT;
		break;
	case 2: // #现行设置
		根键 = HKEY_CURRENT_CONFIG;
		break;
	case 3: // #现行用户
		根键 = HKEY_CURRENT_USER;
		break;
	case 4: // #本地机器
		根键 = HKEY_LOCAL_MACHINE;
		break;
	case 5: // #所有用户
		根键 = HKEY_USERS;
		break;
	default:
		return FALSE;
	}

	if (!创建注册表路径(根键, route)) {
		return FALSE;
	}
	HKEY phkResult = {};
	LSTATUS lResult = RegOpenKeyEx(根键, route.c_str(), 0, KEY_WRITE, &phkResult);
	if (lResult == ERROR_SUCCESS) {

		LSTATUS SS = RegSetValueEx(phkResult, name.c_str(), 0, REG_BINARY, reinterpret_cast<const BYTE*>(value_.get()), value_.size());
		RegCloseKey(phkResult);
		if (SS == ERROR_SUCCESS) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOL 删除注册项(int root_, const wchar_t* fullPathItemName)
{
	if (NULL == fullPathItemName) return FALSE;

	HKEY 根键 = NULL;
	const wchar_t* 根键名称 = nullptr;
	std::wstring 全路径注册项名 = fullPathItemName;
	size_t ss = 全路径注册项名.rfind(L"\\");
	std::wstring route = 全路径注册项名.substr(0, ss);
	std::wstring name = 全路径注册项名.substr(ss + 1, 全路径注册项名.size() - ss - 1);

	// 根据传入的根目录参数选择相应的根键
	switch (root_) {
	case 1: // #根类
		根键 = HKEY_CLASSES_ROOT;
		根键名称 = L"HKEY_CLASSES_ROOT";
		break;
	case 2: // #现行设置
		根键 = HKEY_CURRENT_CONFIG;
		根键名称 = L"HKEY_CURRENT_CONFIG";
		break;
	case 3: // #现行用户
		根键 = HKEY_CURRENT_USER;
		根键名称 = L"HKEY_CURRENT_USER";
		break;
	case 4: // #本地机器
		根键 = HKEY_LOCAL_MACHINE;
		根键名称 = L"HKEY_LOCAL_MACHINE";
		break;
	case 5: // #所有用户
		根键 = HKEY_USERS;
		根键名称 = L"HKEY_USERS";
		break;
	default:
		return FALSE;
	}

	HKEY phkResult = {};
	LSTATUS lResult = RegOpenKeyEx(根键, route.c_str(), 0, KEY_WRITE, &phkResult);
	if (lResult == ERROR_SUCCESS) {
		LSTATUS SS = RegDeleteKeyEx(phkResult, name.c_str(), 0, 0);
		RegCloseKey(phkResult);
		if (SS == ERROR_SUCCESS) {
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

BOOL 注册项是否存在(int root_, const wchar_t* fullPathItemName)
{
	if (NULL == fullPathItemName) return FALSE;

	HKEY 根键 = NULL;
	const wchar_t* 根键名称 = nullptr;
	std::wstring 全路径注册项名 = fullPathItemName;
	size_t ss = 全路径注册项名.rfind(L"\\");
	std::wstring route = 全路径注册项名.substr(0, ss);
	std::wstring name = 全路径注册项名.substr(ss + 1, 全路径注册项名.size() - ss - 1);

	// 根据传入的根目录参数选择相应的根键
	switch (root_) {
	case 1: // #根类
		根键 = HKEY_CLASSES_ROOT;
		根键名称 = L"HKEY_CLASSES_ROOT";
		break;
	case 2: // #现行设置
		根键 = HKEY_CURRENT_CONFIG;
		根键名称 = L"HKEY_CURRENT_CONFIG";
		break;
	case 3: // #现行用户
		根键 = HKEY_CURRENT_USER;
		根键名称 = L"HKEY_CURRENT_USER";
		break;
	case 4: // #本地机器
		根键 = HKEY_LOCAL_MACHINE;
		根键名称 = L"HKEY_LOCAL_MACHINE";
		break;
	case 5: // #所有用户
		根键 = HKEY_USERS;
		根键名称 = L"HKEY_USERS";
		break;
	default:
		return false;
	}

	HKEY phkResult = {};
	if (RegOpenKeyEx(根键, 全路径注册项名.c_str(), 0, KEY_WRITE, &phkResult) == ERROR_SUCCESS) {
		RegCloseKey(phkResult);
		return TRUE;
	}
	LSTATUS lResult = RegOpenKeyEx(根键, route.c_str(), 0, KEY_WRITE, &phkResult);
	if (lResult == ERROR_SUCCESS) {
		HKEY shp = {};
		if (RegOpenKeyEx(phkResult, name.c_str(), 0, KEY_WRITE, &shp) == ERROR_SUCCESS) {
			RegCloseKey(shp);
			RegCloseKey(phkResult);
			return TRUE;
		}
		RegCloseKey(phkResult);
		return FALSE;
	}
	return FALSE;
}

int 取默认底色()
{
	return (int)GetSysColor(COLOR_WINDOW);
}


CXBytes  快照(HWND hWnd, int outWidth, int ouHeight)
{
	HDC hdc = GetDC(hWnd);
	if (hdc == NULL)
		return CXBytes();
	RECT rect;

	HWND HObjWnd = hWnd;
	if (HObjWnd == NULL)
		HObjWnd = GetDesktopWindow();
	if (GetWindowRect(HObjWnd, &rect) == FALSE)
	{
		ReleaseDC(hWnd, hdc);
		return CXBytes();
	}

	SIZE sz;
	sz.cx = rect.right - rect.left;
	sz.cy = rect.bottom - rect.top;
	int nWidth, nHeight;
	nWidth = sz.cx;
	nHeight = sz.cy;

	if (outWidth > 0)
		nWidth = outWidth;
	else if (outWidth < 0)
	{
		if (outWidth < -10)
			outWidth = -10;
		nWidth = (sz.cx * -1 * outWidth) / 100;
	}

	if (outWidth > 0)
		nHeight = outWidth;
	else if (outWidth < 0)
	{
		if (outWidth < -10)
			outWidth = -10;
		nHeight = (sz.cy * -1 * outWidth) / 100;
	}
	
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP   hBitmap, hOldBitmap;
	hBitmap = CreateCompatibleBitmap(hdc, nWidth, nHeight);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	//StretchBlt(hMemDC, 0, 0, nWidth, nHeight,hdc, rect.left, rect.top,rect.right,rect.bottom, SRCCOPY);
	SetStretchBltMode(hMemDC, HALFTONE);//防止缩放时失真
	StretchBlt(hMemDC, 0, 0, nWidth, nHeight, hdc, 0, 0, sz.cx, sz.cy, SRCCOPY);

	BITMAP bmp;
	::GetObject(hBitmap, sizeof(BITMAP), &bmp);
	//申请内存保存位图数据 
	CXBytes  bytedata;
	DWORD dwSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmp.bmWidthBytes * bmp.bmHeight;
	bytedata.resize(dwSize);

	LPBYTE pData = (LPBYTE)bytedata.get(); //(LPBYTE)E_MAlloc(dwSize + 2 * sizeof(INT));

	LPBITMAPFILEHEADER pBfh = (LPBITMAPFILEHEADER)pData;//位图文件头 
	memset(pBfh, 0, sizeof(BITMAPFILEHEADER));
	pBfh->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//到位图数据的偏移量 
	pBfh->bfSize = pBfh->bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//文件总的大小 
	pBfh->bfType = (WORD)0x4d42;

	pData += sizeof(BITMAPFILEHEADER);

	LPBITMAPINFOHEADER pBih = (LPBITMAPINFOHEADER)pData;//位图信息头 
	memset(pBih, 0, sizeof(BITMAPINFOHEADER));
	pBih->biSize = sizeof(BITMAPINFOHEADER);
	pBih->biWidth = bmp.bmWidth;//宽度 
	pBih->biHeight = bmp.bmHeight;//高度 
	pBih->biPlanes = 1;
	pBih->biBitCount = bmp.bmBitsPixel;//每个像素字节大小 
	pBih->biCompression = BI_RGB;
	pBih->biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//图像数据大小 
	pBih->biXPelsPerMeter = 0;
	pBih->biYPelsPerMeter = 0;
	pBih->biClrUsed = 0;
	pBih->biClrImportant = 0;
	pData += sizeof(BITMAPINFOHEADER);

	GetDIBits(hMemDC, hBitmap, 0, nHeight, pData, (LPBITMAPINFO)pBih, DIB_RGB_COLORS);//获取位图数据 

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hdc);
	DeleteObject(hBitmap);
	return bytedata;
}

CXText  读配置项(const wchar_t* pFileName, const wchar_t* pNodeName, const wchar_t* pItemName, const wchar_t* pDefaultText)
{
	int bufferSize = 512;
	wchar_t* valueBuffer = nullptr;
	DWORD bytesRead;

	do {
		if (valueBuffer != nullptr) {
			delete[] valueBuffer;
		}

		bufferSize *= 2;
		valueBuffer = new wchar_t[bufferSize];

		bytesRead = GetPrivateProfileString(pNodeName, pItemName, pDefaultText, valueBuffer, bufferSize, pFileName);
	} while (bytesRead == bufferSize - 1);

	if (删全部空(valueBuffer) == L"") {
		return pDefaultText;
	}
	return valueBuffer;
}

BOOL 写配置项(const wchar_t* pFileName, const wchar_t* pNodeName, const wchar_t* pItemName, const wchar_t* pValue)
{
	return WritePrivateProfileString(pNodeName, pItemName, pValue, pFileName);
}

CXVector<CXText> 取配置节名(const wchar_t* pFileName)
{
	CXVector<CXText> retArray;
	if (NULL == pFileName || 0 == *pFileName)
		return retArray;

	const int bufferSize = 32767;

	wchar_t sectionNames[bufferSize];
	DWORD bytesRead = GetPrivateProfileSectionNames(sectionNames, bufferSize, pFileName);
	std::vector<std::string> sectionNameList;
	if (bytesRead > 0) {
		// 解析 sectionNames 并存储到一个字符串数组
		const wchar_t* sectionNamePtr = sectionNames;
		while (*sectionNamePtr) {
			retArray.add(sectionNamePtr);
			sectionNamePtr += wcslen(sectionNamePtr) + 1;
		}
	} else {
		return {};
	}
	return retArray;
}

int 取操作系统类别()
{
	OSVERSIONINFOEX inf;
	inf.dwOSVersionInfoSize = sizeof(inf);
	GetVersionEx((LPOSVERSIONINFO)&inf);

	if (inf.dwMajorVersion == 10 && inf.dwMinorVersion == 0 && inf.wProductType == 1)
		return 5;
	if (inf.dwMajorVersion == 10 && inf.dwMinorVersion == 0 && inf.wProductType != 1)
		return 6;
	if (inf.dwMajorVersion == 6 && inf.dwMinorVersion == 3 && inf.wProductType == 1)
		return 7;
	if (inf.dwMajorVersion == 6 && inf.dwMinorVersion == 3 && inf.wProductType != 1)
		return 8;
	if (inf.dwMajorVersion == 6 && inf.dwMinorVersion == 2 && inf.wProductType == 1)
		return 9;
	if (inf.dwMajorVersion == 6 && inf.dwMinorVersion == 2 && inf.wProductType != 1)
		return 10;
	if (inf.dwMajorVersion == 6 && inf.dwMinorVersion == 1 && inf.wProductType == 1)
		return 11;
	if (inf.dwMajorVersion == 6 && inf.dwMinorVersion == 1 && inf.wProductType != 1)
		return 12;
	if (inf.dwMajorVersion == 6 && inf.dwMinorVersion == 0 && inf.wProductType != 1)
		return 13;
	if (inf.dwMajorVersion == 6 && inf.dwMinorVersion == 0 && inf.wProductType == 1)
		return 14;
	if (inf.dwPlatformId == VER_PLATFORM_WIN32s)
		return 1;
	if (inf.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
		return 2;
	if (inf.dwPlatformId == VER_PLATFORM_WIN32_NT)
		return 3;

	return 0;
}

CXVector<CXText> 多文件对话框(const wchar_t* 标题, const wchar_t* 过滤器,
	int 初始过滤器, const wchar_t* 初始目录, BOOL 不改变目录, HWND 父窗口)
{
	OPENFILENAME ofn;
	wchar_t fileNames[26000] = { 0 }; // 用于存储选择的文件名
	ZeroMemory(&ofn, sizeof(ofn));

	//拷贝过滤器到缓冲区， 过滤器由|进行分割，需要替换为\0
	int filterLen = wcslen(过滤器);
	wchar_t* filter = new wchar_t[filterLen + 2];
	wmemset(filter, 0, filterLen + 2);
	wcscpy(filter, 过滤器);
	for (int i = 0; i < filterLen; i++) {
		if (filter[i] == L'|') {
			filter[i] = L'\0';
		}
	}

	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileNames;
	ofn.nMaxFile = sizeof(fileNames);
	ofn.lpstrTitle = 标题;
	ofn.nFilterIndex = 初始过滤器;
	ofn.lpstrInitialDir = 初始目录;
	ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER;
	if (父窗口)
		ofn.hwndOwner = 父窗口;
	else
		ofn.hwndOwner = GetActiveWindow();

	if (不改变目录) {
		ofn.Flags |= OFN_NOCHANGEDIR;
	}
	CXVector<CXText>  retArray;
	if (GetOpenFileNameW(&ofn)) {

		//获取文件目录
		std::wstring fileDir;
		if (ofn.nFileOffset != 0)
		{
			fileDir.append(ofn.lpstrFile, ofn.nFileOffset);
			fileDir[ofn.nFileOffset-1] = '\\';
		}

		wchar_t* start = ofn.lpstrFile;
		if (ofn.nFileOffset != 0) //多选标志
		{
			start += ofn.nFileOffset;    // 移动到第一个文件名
		}

		// 遍历所有选中的文件
		while (*start) {

			std::wstring  filePath = fileDir;
			filePath += start;
			retArray.add(filePath);
			start += wcslen(start) + 1; // 跳转到下一个文件路径
		}
	} else {
		DWORD error = CommDlgExtendedError();
		if (error != 0) {
			xcl_log(L"打开文件对话框错误: ", error);
		}
	}
	delete[]filter;
	return retArray;
}

CXBytes  取统一文本(const char* pText, BOOL toWideText, BOOL bTerminator)
{
	CXBytes retBytes;
	if (toWideText) {
		CXText wstr = A2W(pText);
		if (bTerminator) {
			wstr += L"\0";
			retBytes.addWchar(0);
		}
		for (int i = 0; i < wstr.size(); i++) {
			retBytes.addWchar(wstr[i]);
		}
	} else {
		CXTextA str = A2U(pText);
		if (bTerminator) {
			str += "\0";
			retBytes.addByte(0);
		}
		for (int i = 0; i < str.size(); i++) {
			retBytes.addByte(str[i]);
		}
	}
	return retBytes;
}

int 取统一文本长度(const char* pText, BOOL toWideText)
{
	if (toWideText) {
		int length = (int)strlen(pText);
		return  MultiByteToWideChar(CP_ACP, 0, pText, length, NULL, 0);
	} else {
		CXTextA text = A2U(pText);
		return text.size();
	}
	return 0;
}

#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

BOOL 播放音乐(const wchar_t* pFileName, BOOL bLoop)
{
	DWORD dwSound = SND_ASYNC | SND_NODEFAULT;
	dwSound |= SND_FILENAME;
	if (bLoop)
		dwSound |= SND_LOOP;

	return PlaySound(pFileName, NULL, dwSound);
}

BOOL 播放音乐(CXBytes& bytes_, BOOL bLoop)
{
	DWORD dwSound = SND_ASYNC | SND_NODEFAULT;
	if (bLoop)
		dwSound |= SND_LOOP;
	dwSound |= SND_MEMORY;
	return PlaySound((LPCWSTR)bytes_.get(), NULL, dwSound);
}


BOOL 播放音乐(int resID, BOOL bLoop)
{
	DWORD dwSound = SND_ASYNC | SND_NODEFAULT;
	if (bLoop)
		dwSound |= SND_LOOP;

	dwSound |= SND_RESOURCE;
	LPCWSTR pszMusicData = MAKEINTRESOURCE(resID);
	HMODULE hmod = ::GetModuleHandle(NULL);
	return PlaySound(pszMusicData, hmod, dwSound);
}

void 停止播放()
{
	PlaySound(NULL, NULL, SND_PURGE);
}

void 播放MP3(int count, const wchar_t* pFileName)
{
	if (-1 == count)
	{
		PlaySound(pFileName, NULL, SND_LOOP | SND_ASYNC | SND_NODEFAULT);
	} else
	{
		for (int i = 0; i < count; i++)
		{
			PlaySound(pFileName, NULL, SND_ASYNC | SND_NODEFAULT);
		}
	}
}

int 取硬盘特征字()
{
	DWORD serialNumber=0;
	BOOL success = GetVolumeInformation(L"C:\\", NULL, 0, &serialNumber, NULL, NULL, NULL, 0);
	return serialNumber;
}

int 取系统语言()
{
	LCID lcid = GetSystemDefaultLCID();

	switch (lcid) {
	case 2052:  // GBK中文的 LCID
		return 1;
	case 1033:  // 英文的 LCID
		return 2;
	case 950:   // BIG5中文的 LCID
		return 3;
	case 1041:  // 日文的 LCID
		return 4;
	default:
		return 2;  // 默认为英文
	}
}

void 写到内存(void* data_, int dataSize, void* addr, int memSize_)
{
	if (dataSize > 0)
	{
		if (-1 != memSize_)
		{
			if (dataSize > memSize_)
				dataSize = memSize_;
		}
		memcpy(addr, data_, dataSize);
	}
}

CXTextA 标准输入(BOOL 是否回显)
{
	if (是否回显) {
		std::string ss;
		std::cin >> ss;
		return ss;
	}
	char str[1024]; // 声明一个字符数组来存储输入的密码
	int index = 0; // 用于跟踪密码字符的索引

	while (true) {
		int ch = _getch(); // 使用 _getch() 获取单个字符，不回显
		if (ch == 13) // 如果用户按下回车键，结束输入
			break;
		if (ch == 8) { // 如果用户按下退格键，删除最后一个字符
			if (index > 0) {
				--index;
				std::cout << "\b \b"; // 删除并移动光标
			}
		} else {
			str[index++] = ch; // 将字符存储在密码数组中
			std::cout << '*'; // 显示星号代替密码字符
		}
	}

	str[index] = '\0'; // 在密码数组末尾添加空字符以表示字符串的结束
	std::cout << std::endl;
	return str;
}
