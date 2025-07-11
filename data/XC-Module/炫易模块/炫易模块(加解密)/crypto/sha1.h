#pragma once
#ifndef XL_XEXPAND_CYRPTO_SHA1_H
#define XL_XEXPAND_CYRPTO_SHA1_H 
#include "macro.h"
#include "HashBase.h"

class X_CSHA1 : public X_CHashBase
{
public:
	X_CSHA1(void);
	~X_CSHA1(void);

public:
	inline unsigned int HashDigestSize(void)
	{
		return 20;
	}

private:
	unsigned int BaseData[5];
	unsigned int CalcData[16];

public:
	bool InitHash(unsigned char* pBaseData = 0);
	bool CalcHash(unsigned char* pBufferIn, int BufferInSize, unsigned char* pDigestOut);

public:
	void GetBaseData(unsigned char* pBaseDataOut);

private:
	void SetBaseData(unsigned char* pBaseDataIn);
	void SetCalcData(unsigned char* pCalcDataIn);

private:
	void Sha1Calc();
};

#endif