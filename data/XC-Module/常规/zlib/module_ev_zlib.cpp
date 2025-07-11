#ifdef XPL_DEV
#include "dev/pch.h"

#endif

#include "module_ev_zlib.h"
#include "include/zlib.h"

BOOL ev_compress2(CXBytes& src, CXBytes& dest, int level)
{
	uLong srcLen = (uLong)src.size();
	if (srcLen <= 0){
		dest.clear();
		return FALSE;
	}
		
	uLongf destLen = compressBound(srcLen);
	constexpr uLong header_len = sizeof(DWORD) * 2;
	dest.alloc((INT)(header_len + destLen));
	if (compress2((Bytef*)dest.get() + header_len, &destLen, (Bytef*)src.get(), srcLen, level) == Z_OK)
	{
		if (dest.size() > (INT)(header_len + destLen))
			dest.resize(header_len + destLen);
		DWORD* headers = (DWORD*)dest.get();
		headers[0] = (DWORD)54398733;
		headers[1] = (DWORD)srcLen;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


CXBytes ev_compress(CXBytes& src, int level)
{
	CXBytes dest;
	ev_compress2(src, dest, level);
	return dest;
}

 BOOL ev_uncompress2(CXBytes& src, CXBytes& dest)
{
	constexpr uLong header_len = sizeof(DWORD) * 2;
	uLong srcLen = (uLong)src.size() - (uLong)header_len;
	if (srcLen <= 0)
		return FALSE;
	const DWORD* headers = (DWORD*)src.get();
	if (headers[0] == 54398733)
	{
		uLongf destLen = headers[1];
		dest.alloc((INT)(destLen));
		if (uncompress((Bytef*)dest.get(), &destLen, (Bytef*)(headers + 2), srcLen) == Z_OK)
		{
			if(destLen == headers[1])
				return TRUE;
		}
		dest.clear();
	}
	return FALSE;
}

CXBytes ev_uncompress(CXBytes& src)
{
	CXBytes dest;
	ev_uncompress2(src, dest);
	return dest;
}

int ev_crc32(CXBytes& src)
{
	int temp;
	temp = (int)crc32(0, (Bytef*)src.get(), src.size());
	return temp;
}
