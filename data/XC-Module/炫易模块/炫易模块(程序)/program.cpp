#include "module_e_Program.h"

//程序_延时
void X_Program_Sleep(long time,int unit){
    //Sleep(time);
    long lt = time;
    int lu = unit;
    if(unit==0 && time==0) {
        lt = 5000 *60 * 60;
        lu = 5000 *60 * 60;
    }
    else if (lu > 3 || lu <= 0) {
        lu = 1;
    }
    else if (lu == 1) {
        lu = 1000;
    }
    else if (lu == 2) {
        lu = 1000*60;
    }
    else if (lu == 3) {
        lu = 1000 * 60*60;
    }
    LARGE_INTEGER ltime={0};
    ltime.QuadPart = -10 * lt* 1000 * lu;
    HANDLE htime=CreateWaitableTimerA(0, false, 0);
    SetWaitableTimer(htime, &ltime, 0, 0, 0, false);
    while (MsgWaitForMultipleObjects(1, &htime,false,1,255)!=0) {
		xcl_doMessage();
    }
    CloseHandle(htime);
}

//程序_是否64位
BOOL X_Program_If64() {
    char* test = nullptr;
    char* start = (char*)&test;
    char* end = (char*)(&test + 1);
    if (4 == (end - start))
    {
        return FALSE;
    }
    if (8 == (end - start))
    {
        return TRUE;
    }
    return FALSE;
}

CXText X_Program_CreateGUID(GUID& guid_)
{
	WCHAR szGuid[40];
	CoCreateGuid(&guid_);
	int result = StringFromGUID2(guid_, szGuid, sizeof(szGuid));
	return szGuid;
}

///////////////////////////////////////////////////////////////
CXText 程序_取cmd路径()
{
	wchar_t   buf[MAX_PATH] = { 0 };
	int size = GetEnvironmentVariable(L"ComSpec", buf, MAX_PATH);
	return buf;
}

// 卸载原外壳占用内存   
BOOL UnloadShell(HANDLE ProcHnd, unsigned long BaseAddr)
{
#ifdef DEBUG
	return TRUE;
#else
	typedef unsigned long(__stdcall* pfZwUnmapViewOfSection)(unsigned long, unsigned long);
	pfZwUnmapViewOfSection ZwUnmapViewOfSection = NULL;
	BOOL res = FALSE;
	HMODULE m = LoadLibrary(L"ntdll.dll");
	if (m)
	{
		ZwUnmapViewOfSection = (pfZwUnmapViewOfSection)GetProcAddress(m, "NtUnmapViewOfSection");// "ZwUnmapViewOfSection");
		if (ZwUnmapViewOfSection)
		{
			int ret = ZwUnmapViewOfSection((unsigned long)ProcHnd, BaseAddr);
			res = (ret == 0);
		}
		FreeLibrary(m);
	}
	return res;
#endif
}

int RShift(DWORD value_, int numberOfBitsToShift)
{
	double ret = (double)value_ / pow(2.0, (double)numberOfBitsToShift);
	return (int)ret;
}

int  Protect(DWORD characteristics)
{
	BYTE arr[8] = { 1,16,2,32,4,64,4,64 };
	int index = RShift(characteristics, 29);
	return arr[index];
}

//PROCESS_INFORMATION: 进程结构
BOOL 程序_内存中运行EXE(const CXBytes& 欲执行的程序, const wchar_t* 命令行, const wchar_t* 外壳程序路径, BOOL 等待程序运行完毕,
	int 窗口显示方式, PROCESS_INFORMATION* 进程信息)
{
	const BYTE* data = 欲执行的程序.get();

	IMAGE_DOS_HEADER  dos_header = { 0 };
	memmove(&dos_header, data, sizeof(IMAGE_DOS_HEADER));
	if (dos_header.e_magic != 23117)
		return FALSE;

#ifdef _WIN64

	IMAGE_NT_HEADERS  nt_header = { 0 };
	memmove(&nt_header, data + dos_header.e_lfanew, sizeof(IMAGE_NT_HEADERS));
	if (nt_header.Signature != 17744)
		return FALSE;
#else
	IMAGE_NT_HEADERS32  nt_header = { 0 };
	memmove(&nt_header, data + dos_header.e_lfanew, sizeof(IMAGE_NT_HEADERS32));
	if (nt_header.Signature != 17744)
		return FALSE;
#endif
	STARTUPINFO  startupInfo_ = { 0 };
	startupInfo_.cb = sizeof(STARTUPINFO);
	if (窗口显示方式 >= 1 && 窗口显示方式 <= 6)
	{
		startupInfo_.dwFlags = 1;
		switch (窗口显示方式)
		{
		case 1: startupInfo_.wShowWindow = SW_HIDE; break;
		case 2: startupInfo_.wShowWindow = SW_SHOW; break;
		case 3: startupInfo_.wShowWindow = SW_SHOWMINIMIZED; break;
		case 4: startupInfo_.wShowWindow = SW_SHOWMAXIMIZED; break;
		case 5: startupInfo_.wShowWindow = SW_SHOWNA; break;
		case 6: startupInfo_.wShowWindow = SW_SHOWMINNOACTIVE; break;
		}
	}

	PROCESS_INFORMATION pi = { 0 };

	CXText  cmd;
	if (外壳程序路径 && *外壳程序路径)
		cmd = 外壳程序路径;
	else
		cmd = 程序_取cmd路径();

	if (命令行 && *命令行)
	{
		cmd += L" ";
		cmd += 命令行;
	}

	vint  addr = 0;
	int  offset = 0;
	BOOL ret = 0;
	IMAGE_SECTION_HEADER  section_header = { 0 };
	BYTE* imageBase = NULL;
	if (!CreateProcess(0, (wchar_t*)(cmd.get()), 0, 0, FALSE, CREATE_SUSPENDED, 0, 0, &startupInfo_, &pi))
		return FALSE;
#ifdef _WIN64
	CONTEXT  context = { 0 };
	context.ContextFlags = CONTEXT_FULL;
	if (!GetThreadContext(pi.hThread, &context))
		goto  skip_err;

	if (!ReadProcessMemory(pi.hProcess, (void*)(vint)(context.Rip + 8), &addr, 8, 0))
		goto  skip_err;
#else
	WOW64_CONTEXT  context = { 0 };
	context.ContextFlags = 65538; // CONTEXT_FULL;
	if (!Wow64GetThreadContext(pi.hThread, &context))
		goto  skip_err;

	if (!ReadProcessMemory(pi.hProcess, (void*)(vint)(context.Ebx + 8), &addr, 4, 0))
		goto  skip_err;
#endif

	if (0 == addr)
		goto  skip_err;

#ifndef DEBUG
	if (!UnloadShell(pi.hProcess, addr))
		return FALSE;
#endif

	imageBase = (BYTE*)VirtualAllocEx(pi.hProcess, (void*)(vint)nt_header.OptionalHeader.ImageBase, nt_header.OptionalHeader.SizeOfImage, 12288, 4);
	if (NULL == imageBase)
		imageBase = (BYTE*)VirtualAllocEx(pi.hProcess, 0, nt_header.OptionalHeader.SizeOfImage, 12288, 4);
	if (NULL == imageBase)
		goto  skip_err;

	if (!WriteProcessMemory(pi.hProcess, imageBase, data, nt_header.OptionalHeader.SizeOfHeaders, 0))
		goto  skip_err;

#ifdef _WIN64
	offset = dos_header.e_lfanew + sizeof(IMAGE_NT_HEADERS);
	for (int i = 0; i < nt_header.FileHeader.NumberOfSections; i++)
	{
		memmove(&section_header, data + offset + i * 40, sizeof(IMAGE_SECTION_HEADER));
		if (section_header.PointerToRawData + 1 > (DWORD)欲执行的程序.getSize())
			goto  skip_err;

		ret = WriteProcessMemory(pi.hProcess, imageBase + section_header.VirtualAddress, data + section_header.PointerToRawData, section_header.SizeOfRawData, 0);
		if (0 == ret)
			goto  skip_err;

		//XCL_log(L"Protect:" , Protect(section_header.Characteristics));
		ret = VirtualProtectEx(pi.hProcess, imageBase + section_header.VirtualAddress, section_header.Misc.VirtualSize, Protect(section_header.Characteristics), (PDWORD)&addr);
		if (0 == ret)
			goto  skip_err;
	}
#else
	offset = dos_header.e_lfanew + sizeof(IMAGE_NT_HEADERS32);
	for (int i = 0; i < nt_header.FileHeader.NumberOfSections; i++)
	{
		memmove(&section_header, data + offset + i * 40, sizeof(IMAGE_SECTION_HEADER));
		if (section_header.PointerToRawData + 1 > (DWORD)欲执行的程序.getSize())
			goto  skip_err;

		ret = WriteProcessMemory(pi.hProcess, imageBase + section_header.VirtualAddress, data + section_header.PointerToRawData, section_header.SizeOfRawData, 0);
		if (0 == ret)
			goto  skip_err;

		//XCL_log(L"Protect:" , Protect(section_header.Characteristics));
		ret = VirtualProtectEx(pi.hProcess, imageBase + section_header.VirtualAddress, section_header.Misc.VirtualSize, Protect(section_header.Characteristics), (PDWORD)&addr);
		if (0 == ret)
			goto  skip_err;
	}
#endif

#ifdef _WIN64
	addr = (vint)imageBase;
	ret = WriteProcessMemory(pi.hProcess, (void*)(vint)(context.Rip+8), &addr, 8, 0);
	if (0 == ret)
	{
		//DWORD err = GetLastError();
		goto  skip_err;
	}
	context.Rip = (DWORD64)(imageBase + nt_header.OptionalHeader.AddressOfEntryPoint);
	ret = SetThreadContext(pi.hThread, &context);
	if (0 == ret)
	{
		//DWORD err = GetLastError();
		goto  skip_err;
	}
#else
	addr = (vint)imageBase;
	ret = WriteProcessMemory(pi.hProcess, (void*)(vint)(context.Ebx + 8), &addr, 4, 0);
	if (0 == ret)
	{
		//DWORD err = GetLastError();
		goto  skip_err;
	}
	context.Eax = (DWORD)((vint)imageBase + nt_header.OptionalHeader.AddressOfEntryPoint);
	ret = Wow64SetThreadContext(pi.hThread, &context);
	if (0 == ret)
	{
		//DWORD err = GetLastError();
		goto  skip_err;
	}
#endif
	ret = ResumeThread(pi.hThread);
	if (0 == ret)
	{
		//DWORD err = GetLastError();
		goto  skip_err;
	}

	// 等待进程退出
	if (等待程序运行完毕)
		WaitForSingleObject(pi.hProcess, INFINITE);
	if (进程信息)
	{
		*进程信息 = pi;
	} else
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	return TRUE;

skip_err:
	// 关闭进程和线程句柄
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return FALSE;
}

//////////////////////////////////////////////////////
void 程序_内存中运行EXE线程方式(const CXBytes& data_)
{
	PIMAGE_DOS_HEADER dosHeader;
	PIMAGE_NT_HEADERS ntHeader;
	//	PIMAGE_FILE_HEADER fileHeader;
	//	PIMAGE_EXPORT_DIRECTORY exportDirectory;
	PIMAGE_SECTION_HEADER  pSectionHeader;
	PIMAGE_IMPORT_DESCRIPTOR importDescriptor;
	PIMAGE_THUNK_DATA thunkData;
	PIMAGE_IMPORT_BY_NAME ordAndName;
	PIMAGE_BASE_RELOCATION baseRelocation;

	//CXFile  file_;
	//file_.openRead(file);

	//CXBytes data_ = file_.readDataBytes();
	LPBYTE lpBaseAddress = (LPBYTE)data_.get();

	//获取一些基本变量
	dosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
	int lfanew = dosHeader->e_lfanew;
	ntHeader = (PIMAGE_NT_HEADERS)(lpBaseAddress + lfanew);
	int sizeOfImage = ntHeader->OptionalHeader.SizeOfImage;
	int sizeOfHeader = ntHeader->OptionalHeader.SizeOfHeaders;
	pSectionHeader = (PIMAGE_SECTION_HEADER)(lpBaseAddress + lfanew + sizeof(IMAGE_NT_HEADERS));

	//创建内存空间
	LPBYTE loca = (LPBYTE)VirtualAlloc(NULL, sizeOfImage, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	//拷贝内存空间
	LPBYTE virseek = (LPBYTE)loca;
	memcpy(loca, lpBaseAddress, sizeOfHeader);
	if (sizeOfHeader % 0x1000 != 0)
	{
		virseek += 0x1000;
	}
	virseek += (sizeOfHeader / 0x1000) * 0x1000;
	LPBYTE sectionStartAddr = lpBaseAddress + sizeOfHeader;
	for (int i = 0; i < (ntHeader->FileHeader.NumberOfSections); i++, pSectionHeader++)
	{
		int sectionSize = pSectionHeader->Misc.VirtualSize / 0x1000;
		if (pSectionHeader->Misc.VirtualSize % 0x1000 != 0)
		{
			sectionSize++;
		}
		memcpy(virseek, sectionStartAddr, pSectionHeader->SizeOfRawData);
		sectionStartAddr += pSectionHeader->SizeOfRawData;
		virseek += sectionSize * 0x1000;
	}

	//修复IAT表
	ntHeader = (PIMAGE_NT_HEADERS)(loca + lfanew);
	int vAddr = ntHeader->OptionalHeader.DataDirectory[1].VirtualAddress;
	importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(loca + vAddr);
	while (importDescriptor->Name)
	{
		HMODULE moduleHandle = LoadLibraryA((LPCSTR)(loca + importDescriptor->Name));
		thunkData = (PIMAGE_THUNK_DATA)(importDescriptor->FirstThunk + loca);
		DWORD* indexAddr = (DWORD*)(importDescriptor->FirstThunk + loca);
		while (thunkData->u1.AddressOfData)
		{
			if (IMAGE_SNAP_BY_ORDINAL(thunkData->u1.AddressOfData))
			{
				LPCSTR addr = (LPCSTR)thunkData->u1.AddressOfData - 0x80000000;
				*indexAddr = (DWORD)GetProcAddress(moduleHandle, addr);
			} else {
				ordAndName = (PIMAGE_IMPORT_BY_NAME)(loca + thunkData->u1.AddressOfData);
				*indexAddr = (DWORD)GetProcAddress(moduleHandle, (LPCSTR)(ordAndName->Name));
			}
			thunkData++;
			indexAddr++;
		}
		importDescriptor++;
	}

	//修复重定位表
	baseRelocation = (PIMAGE_BASE_RELOCATION)(loca + (ntHeader->OptionalHeader.DataDirectory[5].VirtualAddress));

	int num;
	WORD* data;
	while (baseRelocation->VirtualAddress + baseRelocation->SizeOfBlock != 0)
	{
		data = (WORD*)((LPBYTE)baseRelocation + 0x8);
		num = (baseRelocation->SizeOfBlock - 0x8) / sizeof(WORD);
		for (int i = 0; i < num; i++)

		{
			if ((DWORD)(data[i] & 0x0000F000) == 0x00003000)
			{
				DWORD* addr = (DWORD*)(loca + baseRelocation->VirtualAddress + (data[i] & 0x00000FFF));
				*addr += (DWORD)(loca - ntHeader->OptionalHeader.ImageBase);
			}
		}
		baseRelocation = (PIMAGE_BASE_RELOCATION)((LPBYTE)baseRelocation + baseRelocation->SizeOfBlock);
	}

	HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)(loca + ntHeader->OptionalHeader.AddressOfEntryPoint), 0, 0, 0);
	if (hThread)
	{
		DWORD d = WaitForSingleObject(hThread, INFINITE);
		VirtualFree(loca, 0, MEM_RELEASE);
		CloseHandle(hThread);
	} else
	{
		VirtualFree(loca, 0, MEM_RELEASE);
	}
}

//////////////////////////////////////////////////////////////////////////
typedef IMAGE_SECTION_HEADER(*PIMAGE_SECTION_HEADERS)[1];

// 计算对齐后的大小   
size_t GetAlignedSize(size_t Origin, size_t Alignment)
{
	return (Origin + Alignment - 1) / Alignment * Alignment;
}


// 计算加载pe并对齐需要占用多少内存   
// 未直接使用OptionalHeader.SizeOfImage作为结果是因为据说有的编译器生成的exe这个值会填0   
size_t CalcTotalImageSize(PIMAGE_DOS_HEADER MzH
	, size_t FileLen
	, PIMAGE_NT_HEADERS peH
	, PIMAGE_SECTION_HEADERS peSecH)
{
	size_t res;
	// 计算pe头的大小   
	res = GetAlignedSize(peH->OptionalHeader.SizeOfHeaders
		, peH->OptionalHeader.SectionAlignment
	);

	// 计算所有节的大小   
	for (int i = 0; i < peH->FileHeader.NumberOfSections; ++i)
	{
		// 超出文件范围   
		if (peSecH[i]->PointerToRawData + peSecH[i]->SizeOfRawData > FileLen)
			return 0;
		else if (peSecH[i]->VirtualAddress)//计算对齐后某节的大小   
		{
			if (peSecH[i]->Misc.VirtualSize)
			{
				res = GetAlignedSize(peSecH[i]->VirtualAddress + peSecH[i]->Misc.VirtualSize
					, peH->OptionalHeader.SectionAlignment
				);
			} else
			{
				res = GetAlignedSize(peSecH[i]->VirtualAddress + peSecH[i]->SizeOfRawData
					, peH->OptionalHeader.SectionAlignment
				);
			}
		} else if (peSecH[i]->Misc.VirtualSize < peSecH[i]->SizeOfRawData)
		{
			res += GetAlignedSize(peSecH[i]->SizeOfRawData
				, peH->OptionalHeader.SectionAlignment
			);
		} else
		{
			res += GetAlignedSize(peSecH[i]->Misc.VirtualSize
				, peH->OptionalHeader.SectionAlignment
			);
		}// if_else   
	}// for   

	return res;
}


// 加载pe到内存并对齐所有节   
BOOL AlignPEToMem(void* Buf, long Len, PIMAGE_NT_HEADERS& peH, PIMAGE_SECTION_HEADERS& peSecH, void*& Mem, size_t& ImageSize)
{
	PIMAGE_DOS_HEADER SrcMz;// DOS头   
	PIMAGE_NT_HEADERS SrcPeH;// PE头   
	PIMAGE_SECTION_HEADERS SrcPeSecH;// 节表   

	SrcMz = (PIMAGE_DOS_HEADER)Buf;

	if (Len < sizeof(IMAGE_DOS_HEADER))
		return FALSE;

	if (SrcMz->e_magic != IMAGE_DOS_SIGNATURE)
		return FALSE;

	if (Len < SrcMz->e_lfanew + (long)sizeof(IMAGE_NT_HEADERS))
		return FALSE;

	SrcPeH = (PIMAGE_NT_HEADERS)((size_t)SrcMz + SrcMz->e_lfanew);
	if (SrcPeH->Signature != IMAGE_NT_SIGNATURE)
		return FALSE;

	if ((SrcPeH->FileHeader.Characteristics & IMAGE_FILE_DLL) ||
		((SrcPeH->FileHeader.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) == 0) ||
		(SrcPeH->FileHeader.SizeOfOptionalHeader != sizeof(IMAGE_OPTIONAL_HEADER)))
	{
		return FALSE;
	}


	SrcPeSecH = (PIMAGE_SECTION_HEADERS)((size_t)SrcPeH + sizeof(IMAGE_NT_HEADERS));
	ImageSize = CalcTotalImageSize(SrcMz, Len, SrcPeH, SrcPeSecH);

	if (ImageSize == 0)
		return FALSE;

	Mem = VirtualAlloc(NULL, ImageSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE); // 分配内存   
	if (Mem != NULL)
	{
		// 计算需要复制的PE头字节数   
		unsigned long l = SrcPeH->OptionalHeader.SizeOfHeaders;
		for (int i = 0; i < SrcPeH->FileHeader.NumberOfSections; ++i)
		{
			if ((SrcPeSecH[i]->PointerToRawData) &&
				(SrcPeSecH[i]->PointerToRawData < l))
			{
				l = SrcPeSecH[i]->PointerToRawData;
			}
		}
		memmove(Mem, SrcMz, l);
		peH = (PIMAGE_NT_HEADERS)((size_t)Mem + ((PIMAGE_DOS_HEADER)Mem)->e_lfanew);
		peSecH = (PIMAGE_SECTION_HEADERS)((size_t)peH + sizeof(IMAGE_NT_HEADERS));

		void* Pt = (void*)((size_t)Mem
			+ GetAlignedSize(peH->OptionalHeader.SizeOfHeaders
				, peH->OptionalHeader.SectionAlignment)
			);

		for (int i = 0; i < peH->FileHeader.NumberOfSections; ++i)
		{
			// 定位该节在内存中的位置   
			if (peSecH[i]->VirtualAddress)
				Pt = (void*)((size_t)Mem + peSecH[i]->VirtualAddress);

			if (peSecH[i]->SizeOfRawData)
			{
				// 复制数据到内存   
				memmove(Pt, (const void*)((size_t)(SrcMz)+peSecH[i]->PointerToRawData), peSecH[i]->SizeOfRawData);
				if (peSecH[i]->Misc.VirtualSize < peSecH[i]->SizeOfRawData)
					Pt = (void*)((size_t)Pt + GetAlignedSize(peSecH[i]->SizeOfRawData, peH->OptionalHeader.SectionAlignment));
				else // pt 定位到下一节开始位置   
					Pt = (void*)((size_t)Pt + GetAlignedSize(peSecH[i]->Misc.VirtualSize, peH->OptionalHeader.SectionAlignment));
			} else
			{
				Pt = (void*)((size_t)Pt + GetAlignedSize(peSecH[i]->Misc.VirtualSize, peH->OptionalHeader.SectionAlignment));
			}
		}
	}
	return TRUE;
}

typedef void* (__stdcall* pfVirtualAllocEx)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD);
pfVirtualAllocEx MyVirtualAllocEx = NULL;

BOOL IsNT()
{
	HMODULE hModule = GetModuleHandle(TEXT("Kernel32.dll"));

	MyVirtualAllocEx = (pfVirtualAllocEx)GetProcAddress(hModule, "VirtualAllocEx");
	return MyVirtualAllocEx != NULL;
}

// 生成外壳程序命令行  
// char* PrepareShellExe(char* CmdParam, unsigned long BaseAddr, unsigned long ImageSize)
// {
// 	if (IsNT())
// 	{
// 		char* Buf = new char[256];
// 		memset(Buf, 0, 256);
// 		GetModuleFileNameA(0, Buf, 256);
// 		strcat_s(Buf, 256, CmdParam);
// 		//memset(Buf , 0,256);
// 		//strcpy(Buf,"C:\\WINDOWS\\system32\\notepad.exe");
// 
// 		//svchost.exe
// 		return Buf; // 请记得释放内存;-)   
// 	} else
// 	{
// 		// Win98下的处理请参考原文;-)   
// 		// http://community.csdn.net/Expert/topic/4416/4416252.xml?temp=8.709133E-03   
// 		return NULL;
// 	}
// }


// 是否包含可重定向列表   
BOOL HasRelocationTable(PIMAGE_NT_HEADERS peH)
{
	return (peH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress)
		&& (peH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size);
}

#pragma pack(push, 1)   
typedef struct
{
#if _WIN64
	unsigned long long VirtualAddress;
	unsigned long SizeOfBlock;
#else
	unsigned long VirtualAddress;
	unsigned long SizeOfBlock;
#endif
} *PImageBaseRelocation;
#pragma pack(pop)   

// 重定向PE用到的地址   
void DoRelocation(PIMAGE_NT_HEADERS peH, void* OldBase, void* NewBase)
{
#if _WIN64
	unsigned long long Delta = (unsigned long long)NewBase - peH->OptionalHeader.ImageBase;
#else
	unsigned long Delta = (unsigned long)NewBase - peH->OptionalHeader.ImageBase;
#endif
	PImageBaseRelocation p = (PImageBaseRelocation)((size_t)OldBase
		+ peH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);

	while (p->VirtualAddress + p->SizeOfBlock)
	{
		unsigned short* pw = (unsigned short*)((size_t)p + sizeof(*p));
		for (unsigned int i = 1; i <= (p->SizeOfBlock - sizeof(*p)) / 2; ++i)
		{
			if (((*pw) & 0xF000) == 0x3000)
			{
#if _WIN64
				unsigned long long* t = (unsigned long long*)((unsigned long long)(OldBase) + p->VirtualAddress + ((*pw) & 0x0FFF));
#else
				unsigned long* t = (unsigned long*)((unsigned long)(OldBase)+p->VirtualAddress + ((*pw) & 0x0FFF));
#endif
				* t += Delta;
			}
			++pw;
		}
		p = (PImageBaseRelocation)pw;
	}
}

// 创建外壳进程并获取其基址、大小和当前运行状态  
BOOL CreateChild(const wchar_t* Cmd, const wchar_t* pShellProgram, int wShowWindow, CONTEXT& Ctx, __out PROCESS_INFORMATION& processInfo,
	vint& BaseAddr, vint& ImageSize)
{
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	MEMORY_BASIC_INFORMATION MemInfo = { 0 };
	si.cb = sizeof(si);

	CXText  strCmd;
	if (pShellProgram && *pShellProgram)
		strCmd = pShellProgram;
	else
		strCmd = 程序_取cmd路径();

	if (Cmd && *Cmd)
	{
		strCmd += L" ";
		strCmd += Cmd;
	}

	if (0 != wShowWindow)
	{
		si.dwFlags = 1;
		si.wShowWindow = wShowWindow;
	}

	BOOL res = CreateProcess(NULL, (wchar_t*)strCmd.getPtr(), NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi); // 以挂起方式运行进程;   
	if (res) {
		processInfo = pi;
		// 获取外壳进程运行状态，[ctx.Ebx+8]内存处存的是外壳进程的加载基址，ctx.Eax存放有外壳进程的入口地址   
		Ctx.ContextFlags = CONTEXT_FULL;
		GetThreadContext(pi.hThread, &Ctx);
		//SIZE_T  old = 0;
#if _WIN64
		ReadProcessMemory(pi.hProcess, (void*)(Ctx.Rip + 8), &BaseAddr, 8, 0); // 读取加载基址
#else
		ReadProcessMemory(pi.hProcess, (void*)(Ctx.Ebx + 8), &BaseAddr, 4, 0); // 读取加载基址   
#endif
		void* p = (void*)BaseAddr;

		// 计算外壳进程占有的内存   
		while (VirtualQueryEx(pi.hProcess, p, &MemInfo, sizeof(MemInfo)))
		{
			if (MemInfo.State = MEM_FREE) break;
			p = (void*)((vint)p + MemInfo.RegionSize);
		}
		ImageSize = (vint)p - BaseAddr;
	}
	return res;
}

// 创建外壳进程并用目标进程替换它然后执行   

BOOL AttachPE(const wchar_t* pCmdLine, const wchar_t* pShellProgram, int wShowWindow, PIMAGE_NT_HEADERS peH, PIMAGE_SECTION_HEADERS peSecH,
	void* Ptr, int ImageSize, __out PROCESS_INFORMATION& processInfo)
{
	BOOL  ret = FALSE;
	CONTEXT Ctx;
	vint Addr, Size;

	// 	char* s = PrepareShellExe(CmdParam, peH->OptionalHeader.ImageBase, ImageSize);
	// 	if (s == NULL)
	// 		return ret;

	if (CreateChild(pCmdLine, pShellProgram, wShowWindow, Ctx, processInfo, Addr, Size))
	{
		void* p = nullptr;
		//DWORD old=0;
		if ((peH->OptionalHeader.ImageBase == Addr) && (Size >= ImageSize))
		{
			// 外壳进程可以容纳目标进程并且加载地址一致   
			p = (void*)Addr;
			VirtualProtectEx(processInfo.hProcess, p, Size, PAGE_EXECUTE_READWRITE, 0); // &old);
		} else if (IsNT())
		{
			if (UnloadShell(processInfo.hProcess, Addr))
			{
				// 卸载外壳进程占有内存   
				p = MyVirtualAllocEx(processInfo.hProcess, (void*)peH->OptionalHeader.ImageBase, ImageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			}
			if ((p == nullptr) && HasRelocationTable(peH))
			{
				// 分配内存失败并且目标进程支持重定向   
				p = MyVirtualAllocEx(processInfo.hProcess, nullptr, ImageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
				if (p) DoRelocation(peH, Ptr, p); // 重定向   
			}
		}

		if (p)
		{
#if _WIN64
			WriteProcessMemory(processInfo.hProcess, (void*)(Ctx.Rip + 8), &p, sizeof(DWORD64), 0); //reinterpret_cast<PSIZE_T>(&old)); // 重置目标进程运行环境中的基址   
			peH->OptionalHeader.ImageBase = (DWORD64)p;
			if (WriteProcessMemory(processInfo.hProcess, p, Ptr, ImageSize, 0))// reinterpret_cast<PSIZE_T>(&old)))
			{
				// 复制PE数据到目标进程   
				Ctx.ContextFlags = CONTEXT_FULL;
				if ((DWORD64)p == Addr)
					Ctx.Rip = peH->OptionalHeader.ImageBase + peH->OptionalHeader.AddressOfEntryPoint; // 重置运行环境中的入口地址   
				else
					Ctx.Rip = (DWORD64)p + peH->OptionalHeader.AddressOfEntryPoint;
#else
			WriteProcessMemory(processInfo.hProcess, (void*)(Ctx.Ebx + 8), &p, sizeof(DWORD), 0); // &old); // 重置目标进程运行环境中的基址   
			peH->OptionalHeader.ImageBase = (unsigned long)p;
			if (WriteProcessMemory(processInfo.hProcess, p, Ptr, ImageSize,0))// &old))
			{
				// 复制PE数据到目标进程   
				Ctx.ContextFlags = CONTEXT_FULL;
				if ((unsigned long)p == Addr)
					Ctx.Eax = peH->OptionalHeader.ImageBase + peH->OptionalHeader.AddressOfEntryPoint; // 重置运行环境中的入口地址   
				else
					Ctx.Eax = (unsigned long)p + peH->OptionalHeader.AddressOfEntryPoint;
#endif

				SetThreadContext(processInfo.hThread, &Ctx);// 更新运行环境   
				ResumeThread(processInfo.hThread);// 执行   
				//CloseHandle(processInfo.hThread);
				ret = TRUE;
			} else
			{
				// 加载失败,杀掉外壳进程   
				TerminateProcess(processInfo.hProcess, 0);
				CloseHandle(processInfo.hThread);
				CloseHandle(processInfo.hProcess);
			}
			} else
		{
			// 加载失败,杀掉外壳进程   
			TerminateProcess(processInfo.hProcess, 0);
			CloseHandle(processInfo.hThread);
			CloseHandle(processInfo.hProcess);
		}
		}
	//delete[] s;
	return ret;
	}


/*******************************************************\
{ ******************************************************* }
{ *                 从内存中加载并运行exe               * }
{ ******************************************************* }
{ * 参数：                                                }
{ * Buffer: 内存中的exe地址                               }
{ * Len: 内存中exe占用长度                                }
{ * CmdParam: 命令行参数(不包含exe文件名的剩余命令行参数）}
{ * ProcessId: 返回的进程Id                               }
{ * 返回值： 如果成功则返回进程的Handle(ProcessHandle),   }
{            如果失败则返回INVALID_HANDLE_VALUE           }
{ ******************************************************* }
\*******************************************************/
//MemExecute
BOOL 程序_内存中运行EXE2(const CXBytes & data_, const wchar_t* pCmdLine, const wchar_t* pShellProgram,
	BOOL bWait, int showWindow, __out PROCESS_INFORMATION * pProcessInfo)
{
	BOOL  ret = FALSE;
	PIMAGE_NT_HEADERS peH;
	PIMAGE_SECTION_HEADERS peSecH;
	void* Ptr;
	size_t peSz;
	if (AlignPEToMem((void*)data_.get(), data_.getSize(), peH, peSecH, Ptr, peSz))
	{
		PROCESS_INFORMATION pi = { 0 };
		ret = AttachPE(pCmdLine, pShellProgram, showWindow, peH, peSecH, Ptr, peSz, pi);
		VirtualFree(Ptr, peSz, MEM_DECOMMIT);
		if (ret)
		{
			if (pProcessInfo)
			{
				*pProcessInfo = pi;
			} else
			{
				CloseHandle(pi.hThread);
				CloseHandle(pi.hProcess);
			}
		}
	}
	return ret;
}


////////////////////////////////////////////////////////////
BOOL 程序_禁止运行(const wchar_t* pFileName)
{
	std::vector<std::wstring>  list_;
	UINT   retType;
	if (reg_queryValueInt(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer)", L"DisallowRun", retType))
	{
		if (1 == retType)
		{
			HKEY hKey = 0;
			if (ERROR_SUCCESS == reg_openKey(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\DisallowRun)", hKey))
			{
				BOOL bResult = FALSE;
				CXText   name;
				CXBytes  data;
				UINT   retType;
				int index = 0;
				while (1)
				{
					int ret = reg_enumValue(hKey, index, name, data, retType);
					if (ERROR_NO_MORE_ITEMS == ret)
						break;

					if (REG_SZ == retType)
					{
						if (0 == wcscmp(data.getTextPtr(), pFileName))
						{
							bResult = TRUE;
							break;
						}
						list_.push_back(data.getTextPtr());
					}
					index++;
				}
				RegCloseKey(hKey);
				if (bResult)
				{
					return bResult;
				}
			}
		}
	}
	int ret = reg_deleteKey(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\DisallowRun)");
	ret = reg_createKey(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\DisallowRun)");
	if (ERROR_SUCCESS != ret)
		return FALSE;

	if(!reg_setValueInt(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer)", L"DisallowRun", 1))
		return FALSE;

	wchar_t buf[32] = { 0 };
	list_.push_back(pFileName);
	int count = list_.size();
	for (int i=0;i<count; i++)
	{
		_itow_s(i + 1, buf, 10);
		reg_setValueText(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\DisallowRun)", buf, list_[i].c_str());
	}
	return TRUE;

}

BOOL 程序_允许运行(const wchar_t* pFileName)
{
	UINT   retType;
	if (reg_queryValueInt(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer)", L"DisallowRun", retType))
	{
		if (1 != retType)
			return FALSE;
	}

	BOOL bResult = FALSE;
	HKEY hKey=0;
	if (ERROR_SUCCESS ==reg_openKey(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\DisallowRun)", hKey))
	{
		int count = 0;
		CXText   name;
		CXBytes  data;
		UINT   retType;
		int index = 0;
		while (1)
		{
			int ret = reg_enumValue(hKey, index, name, data, retType);
			if (ERROR_NO_MORE_ITEMS == ret)
				break;
			count++;
			if(REG_SZ == retType)
			{
				if (0 == wcscmp(data.getTextPtr(), pFileName))
				{
					if (ERROR_SUCCESS == reg_deleteVaule(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\DisallowRun)", name.get()))
					{
						bResult = TRUE;
					}
					break;
				}
			}
			index++;
		}
		if (1== count && bResult)
		{
			reg_deleteVaule(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer)", L"DisallowRun");
			reg_deleteKey(HKEY_CURRENT_USER, LR"(Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\DisallowRun)");
		}
		RegCloseKey(hKey);
	}
	return bResult;
}

BOOL 程序_禁止重复运行(const wchar_t* pName)
{
	if (NULL == pName) return FALSE;

	HANDLE hMutex = CreateMutex(NULL, TRUE, pName);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return TRUE;
	}

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	return FALSE;
}

CXText 程序_取安装目录(const wchar_t* pFileName)
{
	std::wstring  strPath = LR"(SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\App Paths\)";
	strPath += pFileName;
	CXText retText;
	if (reg_queryValueText(HKEY_LOCAL_MACHINE, strPath.c_str(), L"Path", retText))
	{
		if (!retText.empty())
		{
			wchar_t ch_ = retText.back();
			if (';' == ch_)
			{
				retText.resize(retText.size() - 1);
				ch_ = retText.back();
			}

			if ('\\' != ch_)
				retText += L"\\";
			return retText;
		}
	}else if (reg_queryValueText(HKEY_LOCAL_MACHINE, strPath.c_str(), L"", retText))
	{
		int pos = retText.rfind(L"\\");
		if (pos > 0)
		{
			retText.resize(pos+1);
			return retText;
		}
	} else
	{
		strPath = L"Applications\\";
		strPath += pFileName;
		strPath += L"\\shell\\open\\command\\";
		if (reg_queryValueText(HKEY_CLASSES_ROOT, strPath.c_str(), L"", retText))
		{
			if ('"' == retText.at(0))
			{
				retText.erase(0);
				int pos = retText.find(L"\"");
				if (pos > 0)
				{
					retText.resize(pos);

					int pos = retText.rfind(L"\\");
					if (pos > 0)
					{
						retText.resize(pos + 1);
						return retText;
					}
					return retText;
				}
			} else
			{
				return retText;
			}
		}
	}
	return L"";
}

