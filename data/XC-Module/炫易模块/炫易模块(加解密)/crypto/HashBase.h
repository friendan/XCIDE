#pragma once
#ifndef XL_XEXPAND_CYRPTO_HASHBASE_H
#define XL_XEXPAND_CYRPTO_HASHBASE_H 

class  X_CHashBase
{
public:
	X_CHashBase(void);
	virtual ~X_CHashBase(void);

public:
	virtual inline unsigned int HashDigestSize(void) = 0;

public:
	virtual bool InitHash(unsigned char* pBaseData = 0) = 0;
	virtual bool CalcHash(unsigned char* pBufferIn, int ulBufferInSize, unsigned char* pDigestOut) = 0;
};

#endif