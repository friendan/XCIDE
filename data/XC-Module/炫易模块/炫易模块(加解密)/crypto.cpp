#include "module_e_crypto.h"

//取MD5_asciiA
CXTextA X_Check_GetMD5_AsciiA (const char* str) {
    CXMD5 lmd5;
    lmd5.reset();
    lmd5.update(str);
    return lmd5.toString();
}
//取MD5_asciiW
CXText X_Check_GetMD5_Ascii(const char* str) {
    return A2W(X_Check_GetMD5_AsciiA(str));
}

//取MD5_UnicodeA
CXTextA X_Check_GetMD5_UnicodeA (CXText data)
{
	CXMD5 md5;
    md5.reset();
    md5.update(data.get (),data.size ());
    return md5.toString();
}
//取MD5_UnicodeW
CXText X_Check_GetMD5_Unicode(CXText data) {
    return A2W(X_Check_GetMD5_UnicodeA(data));
}

//取MD5_字节集A
CXTextA X_Check_GetMD5_BytesA (CXBytes & data) {
	CXMD5 md5;
    md5.reset();
    md5.update((void*)data.get(),data.size ());
    return md5.toString();
}
//取MD5_字节集W
CXText X_Check_GetMD5_Bytes(CXBytes &data) {
    return A2W(X_Check_GetMD5_BytesA(data));
}

//Base64_编码A
CXTextA X_Check_BASE64_EnCodeA (CXTextA str) {
    std::string sr(str.get());
    return base64_encode(sr);
}
//Base64_编码W
CXText X_Check_BASE64_EnCode(CXText str) {
    return A2W(X_Check_BASE64_EnCodeA(W2A(str)));
}

//Base64_解码A
CXTextA X_Check_GetMD5_DeCodeA (CXTextA str){
	std::string sr(str.get());
    return base64_decode(sr);
}
//Base64_解码W
CXText X_Check_GetMD5_DeCode (CXText str)
{
    return A2W(X_Check_GetMD5_DeCodeA(W2A(str)));
}

//Base64_编码_字节集A
CXTextA X_Check_BASE64_EnCode_BytesA (CXBytes &data) {
    return base64_encode(data.get(), data.size());
}
//Base64_编码_字节集W
CXText X_Check_BASE64_EnCode_Bytes(CXBytes &data) {
    return A2W(X_Check_BASE64_EnCode_BytesA(data));
}
//Base64_编码_字节集指针A
CXTextA X_Check_BASE64_EnCode_BYTEA(const BYTE* data,size_t len) {
    return base64_encode(data, len);
}
//Base64_编码_字节集指针
CXText X_Check_BASE64_EnCode_BYTE(const BYTE* data, size_t len) {
    return A2W(base64_encode(data, len).c_str());
}


CXBytes X_Check_BASE64_DeCodeA(CXTextA data){
    std::string str = base64_decode(data.getPtr(),data.size());
    CXBytes result;
    result.add((void*)str.c_str(), str.size());
    return result;
}

CXBytes X_Check_BASE64_DeCode(CXText data) {

    CXTextA data2 = W2A(data);

    std::string str = base64_decode(data2.getPtr(),data2.size());
    CXBytes result;
    result.add((void*)str.c_str(), str.size());
    return result;
}



// //Base64_解码_字节集A
// CXTextA X_Check_GetMD5_DeCode_BytesA (CXBytes &data) {
//     return base64_decode(data.getTextPtrA(),false);
// }
// //Base64_解码_字节集W
// CXText X_Check_GetMD5_DeCode_Bytes (CXBytes& data) {
//     return A2W_(X_Check_GetMD5_DeCode_BytesA(data));
// }



//RC4加密
CXBytes X_Check_RC4EncryptionA(const CXBytes& data,CXTextA Key) {
    X_CRC4 rc4;
    CXBytes r;
    if (!rc4.InitKey((unsigned char*)Key.get(), Key.size() )) {
        return r;
    }
    int blen = data.size();
    unsigned char* pData = new unsigned char[blen];
    if (rc4.EncryptData((unsigned char*)data.get(), data.size(), pData, blen)) {
        r.add(pData, blen);
    }
    delete[]pData;
    return r;
}
//RC4加密
CXBytes X_Check_RC4Encryption(const CXBytes& data, CXText Key) {
    X_CRC4 rc4;
    CXBytes r;
    if (!rc4.InitKey((unsigned char*)Key.get(), Key.size()*2)) {
        return r;
    }
    int blen = data.size();
    unsigned char* pData = new unsigned char[blen];
    if (rc4.EncryptData((unsigned char*)data.get(), data.size(), pData, blen)) {
        r.add(pData, blen);
    }
    delete[]pData;
    return r;
}

//RC4解密
CXBytes X_Check_RC4Decryption(const CXBytes& data, CXText Key) {
    X_CRC4 rc4;
    CXBytes r;
    if (!rc4.InitKey((unsigned char*)Key.get(), Key.size()*2)) {
        return r;
    }
    int blen = data.size();
    unsigned char* pData = new unsigned char[blen];
    if (rc4.DecryptData((unsigned char*)data.get(), data.size(), pData, blen)) {
        r.add(pData, blen);
    }
    delete[]pData;
    return r;
}
//RC4解密
CXBytes X_Check_RC4DecryptionA(const CXBytes& data, CXTextA Key) {
    X_CRC4 rc4;
    CXBytes r;
    if (!rc4.InitKey((unsigned char*)Key.get(), Key.size())) {
        return r;
    }
    int blen = data.size();
    unsigned char* pData = new unsigned char[blen];
    if (rc4.DecryptData((unsigned char*)data.get(), data.size(), pData, blen)) {
        r.add(pData, blen);
    }
    delete[]pData;
    return r;
}

//校验_取sha1
CXTextA X_Check_GetSHA1A(const BYTE* data, int dataLen) {
    X_CSHA1 sha1;
    sha1.InitHash();
    unsigned char out[20] = { 0 };
    sha1.CalcHash((unsigned char*)data, dataLen, out);
    static const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;
    for (std::string::size_type i = 0; i < sizeof(out); ++i) {
        ss << hex[(unsigned char)out[i] >> 4] << hex[(unsigned char)out[i] & 0xf];
    }
    return ss.str();
}
//校验_取sha1
CXText X_Check_GetSHA1(const BYTE* data, int dataLen) {
    X_CSHA1 sha1;
    sha1.InitHash();
    unsigned char out[20] = { 0 };
    sha1.CalcHash((unsigned char*)data, dataLen, out);
    static const std::wstring hex = L"0123456789ABCDEF";
    std::wstringstream ss;
    for (std::wstring::size_type i = 0; i < sizeof(out); ++i) {
        ss << hex[(unsigned char)out[i] >> 4] << hex[(unsigned char)out[i] & 0xf];
    }
    return ss.str();
}

//@别名   校验_取sha256A(原始数据,数据长度)
CXTextA X_Check_GetSHA256A(const BYTE* data, int dataLen) {
    X_CSHA256 sha;
    sha.InitHash();
    unsigned char out[32] = { 0 };
    sha.CalcHash((unsigned char*)data, dataLen, out);
    static const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;
    for (std::string::size_type i = 0; i < sizeof(out); ++i) {
        ss << hex[(unsigned char)out[i] >> 4] << hex[(unsigned char)out[i] & 0xf];
    }
    return ss.str();
}
//@别名   校验_取sha256(原始数据,数据长度)
CXText X_Check_GetSHA256(const BYTE* data, int dataLen) {
    X_CSHA256 sha;
    sha.InitHash();
    unsigned char out[32] = { 0 };
    sha.CalcHash((unsigned char*)data, dataLen, out);
    static const std::wstring hex = L"0123456789ABCDEF";
    std::wstringstream ss;
    for (std::wstring::size_type i = 0; i < sizeof(out); ++i) {
        ss << hex[(unsigned char)out[i] >> 4] << hex[(unsigned char)out[i] & 0xf];
    }
    return ss.str();
}

//校验_取sha512A
CXTextA X_Check_GetSHA512A(const BYTE* data, int dataLen) {
    X_CSHA512 sha;
    sha.InitHash();
    unsigned char out[64] = { 0 };
    sha.CalcHash((unsigned char*)data, dataLen, out);
    static const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;
    for (std::string::size_type i = 0; i < sizeof(out); ++i) {
        ss << hex[(unsigned char)out[i] >> 4] << hex[(unsigned char)out[i] & 0xf];
    }
    return ss.str();
}
//校验_取sha512
CXText X_Check_GetSHA512(const BYTE* data, int dataLen) {
    X_CSHA512 sha;
    sha.InitHash();
    unsigned char out[64] = { 0 };
    sha.CalcHash((unsigned char*)data, dataLen, out);
    static const std::wstring hex = L"0123456789ABCDEF";
    std::wstringstream ss;
    for (std::wstring::size_type i = 0; i < sizeof(out); ++i) {
        ss << hex[(unsigned char)out[i] >> 4] << hex[(unsigned char)out[i] & 0xf];
    }
    return ss.str();
}

//PKCS7填充
AESKeyLength _X_Check_AES_PKCS7_Padding(const BYTE* data, int dataLen,
    BYTE*& lData, DWORD* lDataLen, const BYTE* pKey, 
    int keySize, BYTE*& lKey,
    const BYTE* pIV = NULL, int IVSize = NULL, BYTE** lIV = NULL) {
    int bit = 0;
    AESKeyLength l= AESKeyLength::AES_128;
    if (keySize<=16) {
        bit = 16;
        l = AESKeyLength::AES_128;
    }
    else if (keySize <= 24) {
        //AES192
        bit = 24;
        l = AESKeyLength::AES_192;
    }
    else if (keySize <= 32) {
        //AES256
        bit = 32;
        l = AESKeyLength::AES_256;
    }
    else { return l; }
    //填充data
    int ds = dataLen% bit;
    if (lData != NULL) {
        delete []lData;
    }
    if (ds!=0) {
        ds = bit - ds;
    }
    lData = new BYTE[dataLen + ds];
    memset(lData,0, dataLen + ds);
    *lDataLen = dataLen + ds;
    memcpy(lData, data, dataLen);
    for (int i = 0; i < ds; i++) {
        lData[dataLen + i] = ds;
    }
    //填充key
    ds = keySize % bit;
    if (lKey != NULL) {
        delete[]lKey;
    }
    if (ds != 0) {
        ds = bit - ds;
    }
    lKey = new BYTE[keySize + ds];
    memset(lKey, 0, keySize + ds);
    memcpy(lKey, pKey, keySize);
    //for (int i = 0; i < ds; i++) {
    //    lKey[keySize + i] = ds;
    //}
    if (pIV != NULL) {
        *lIV = new BYTE[IVSize + ds];
        memset(*lIV, 0, IVSize + ds);
        if (pIV != NULL) {
            memcpy(*lIV, pIV, IVSize);
        }
    }
    
    return l;
}
//zero填充
AESKeyLength _X_Check_AES_ZERO_Padding(const BYTE* data, int dataLen,
    BYTE*& lData, DWORD* lDataLen, 
    const BYTE* pKey, int keySize, BYTE*& lKey,
    const BYTE* pIV = NULL, int IVSize = NULL, BYTE** lIV = NULL) {
    int bit = 0;
    AESKeyLength l = AESKeyLength::AES_128;
    if (keySize <= 16) {
        bit = 16;
        l = AESKeyLength::AES_128;
    }
    else if (keySize <= 24) {
        //AES192
        bit = 24;
        l = AESKeyLength::AES_192;
    }
    else if (keySize <= 32) {
        //AES256
        bit = 32;
        l = AESKeyLength::AES_256;
    }
    else { return l; }
    //填充data
    int ds = dataLen % bit;
    if (lData != NULL) {
        delete[]lData;
    }
    if (ds != 0) {
        ds = bit - ds;
    }
    lData = new BYTE[dataLen + ds];
    memset(lData, 0, dataLen + ds);
    *lDataLen = dataLen + ds;
    memcpy(lData, data, dataLen);
    //填充key
    ds = keySize % bit;
    if (lKey != NULL) {
        delete[]lKey;
    }
    if (ds != 0) {
        ds = bit - ds;
    }
    lKey = new BYTE[keySize + ds];
    memset(lKey, 0, keySize + ds);
    memcpy(lKey, pKey, keySize);
    if (pIV != NULL) {
        *lIV = new BYTE[IVSize + ds];
        memset(*lIV, 0, IVSize + ds);
        if (pIV != NULL) {
            memcpy(*lIV, pIV, IVSize);
        }
    }
    return l;
}
//X923填充
AESKeyLength _X_Check_AES_X923_Padding(const BYTE* data, int dataLen, 
    BYTE*& lData, DWORD* lDataLen,
    const BYTE* pKey, int keySize, BYTE*& lKey,
    const BYTE* pIV = NULL, int IVSize = NULL, BYTE** lIV = NULL) {
    int bit = 0;
    AESKeyLength l = AESKeyLength::AES_128;
    if (keySize <= 16) {
        bit = 16;
        l = AESKeyLength::AES_128;
    }
    else if (keySize <= 24) {
        //AES192
        bit = 24;
        l = AESKeyLength::AES_192;
    }
    else if (keySize <= 32) {
        //AES256
        bit = 32;
        l = AESKeyLength::AES_256;
    }
    else { return l; }
    //填充data
    int ds = dataLen % bit;
    if (lData != NULL) {
        delete[]lData;
    }
    if (ds != 0) {
        ds = bit - ds;
    }
    lData = new BYTE[dataLen + ds];
    memset(lData, 0, dataLen + ds);
    *lDataLen = dataLen + ds;
    memcpy(lData, data, dataLen);
    if (ds > 0) {
        lData[dataLen + ds - 1] = ds;
    }
    //填充key
    ds = keySize % bit;
    if (lKey != NULL) {
        delete[]lKey;
    }
    if (ds != 0) {
        ds = bit - ds;
    }
    lKey = new BYTE[keySize + ds];
    memset(lKey, 0, keySize + ds);
    memcpy(lKey, pKey, keySize);
    //if (ds > 0) {
    //    lKey[keySize + ds - 1] = ds;
    //}
    if (pIV != NULL) {
        *lIV = new BYTE[IVSize + ds];
        memset(*lIV, 0, IVSize + ds);
        if (pIV != NULL) {
            memcpy(*lIV, pIV, IVSize);
        }
    }
    
    return l;
}
//ISO7816-4填充
AESKeyLength _X_Check_AES_ISO78164_Padding(const BYTE* data, int dataLen,
    BYTE*& lData, DWORD* lDataLen, 
    const BYTE* pKey, int keySize, BYTE*& lKey,
    const BYTE* pIV = NULL, int IVSize = NULL, BYTE** lIV = NULL) {
    int bit = 0;
    AESKeyLength l = AESKeyLength::AES_128;
    if (keySize <= 16) {
        bit = 16;
        l = AESKeyLength::AES_128;
    }
    else if (keySize <= 24) {
        //AES192
        bit = 24;
        l = AESKeyLength::AES_192;
    }
    else if (keySize <= 32) {
        //AES256
        bit = 32;
        l = AESKeyLength::AES_256;
    }
    else { return l; }
    //填充data
    int ds = dataLen % bit;
    if (lData != NULL) {
        delete[]lData;
    }
    if (ds != 0) {
        ds = bit - ds;
    }
    lData = new BYTE[dataLen + ds];
    memset(lData, 0, dataLen + ds);
    *lDataLen = dataLen + ds;
    memcpy(lData, data, dataLen);
    if (ds > 0) {
        lData[dataLen] = 0x80;
    }
    //填充key
    ds = keySize % bit;
    if (lKey != NULL) {
        delete[]lKey;
    }
    if (ds != 0) {
        ds = bit - ds;
    }
    lKey = new BYTE[keySize + ds];
    memset(lKey, 0, keySize + ds);
    memcpy(lKey, pKey, keySize);
    //if (ds > 0) {
    //    lKey[keySize] = 0x80;
    //}
    if (pIV != NULL) {
        *lIV = new BYTE[IVSize + ds];
        memset(*lIV, 0, IVSize + ds);
        if (pIV != NULL) {
            memcpy(*lIV, pIV, IVSize);
        }
    }
    
    return l;
}
//ISO10126填充
AESKeyLength _X_Check_AES_ISO10126_Padding(const BYTE* data, int dataLen,
    BYTE*& lData, DWORD* lDataLen,
    const BYTE* pKey, int keySize, BYTE*& lKey,
    const BYTE* pIV=NULL, int IVSize = NULL, BYTE** lIV = NULL) {
    int bit = 0;
    AESKeyLength l = AESKeyLength::AES_128;
    if (keySize <= 16) {
        bit = 16;
        l = AESKeyLength::AES_128;
    }
    else if (keySize <= 24) {
        //AES192
        bit = 24;
        l = AESKeyLength::AES_192;
    }
    else if (keySize <= 32) {
        //AES256
        bit = 32;
        l = AESKeyLength::AES_256;
    }
    else { return l; }
    //填充data
    int ds = dataLen % bit;
    if (lData != NULL) {
        delete[]lData;
    }
    if (ds != 0) {
        ds = bit - ds;
    }
    
    lData = new BYTE[dataLen + ds];
    memset(lData, 0, dataLen + ds);
    *lDataLen = dataLen + ds;
    memcpy(lData, data, dataLen);
    for (int i = 0; i < ds; i++) {
        srand((unsigned)time(NULL));
        lData[dataLen + i] = (rand() % (200 - 10 + 1)) + 10;
    }
    if (ds > 0) {
        lData[dataLen + ds - 1] = ds;
    }
    //填充key
    ds = keySize % bit;
    if (lKey != NULL) {
        delete[]lKey;
    }
    if (ds != 0) {
        ds = bit - ds;
    }
    lKey = new BYTE[keySize + ds];
    memset(lKey, 0, keySize + ds);
    memcpy(lKey, pKey, keySize);
    //for (int i = 0; i < ds; i++) {
    //    srand((unsigned)time(NULL));
    //    lKey[keySize + i] = (rand() % (200 - 10 + 1)) + 10;
    //}
    //if (ds > 0) {
    //    lKey[keySize + ds - 1] = ds;
    //}

    if (pIV!=NULL) {
        *lIV= new BYTE[IVSize + ds];
        memset(*lIV, 0, IVSize + ds);
        if (pIV!=NULL) {
            memcpy(*lIV, pIV, IVSize);
        }
    }
    
    return l;
}
int _X_Check_DeCrypto_AES_Calculate_Padding(int Padding, unsigned char*& c, int cLen) {
    int dl = 0;
    int uc = (int)(c[cLen - 1]);
    if ((uc <= cLen && uc < 16) || uc == 0x80) {
        if (Padding == X_AES_ISO78164_PADDING) {
            if (uc == 0x80) {
                dl = 1;
            }
            else {
                int windex = 1;
                uc = (int)(c[cLen - windex]);
                while (uc != 0x80) {
                    dl++;
                    windex++;
                    uc = (int)(c[cLen - windex]);
                }
                dl++;
            }
        }
        else {
            bool IfRedundancy;
            std::map<unsigned char, int>tm;
            int delIndex = 0;
            int i = 0;
            if (uc == 1) {
                IfRedundancy = true;
                goto IfRedundancy;
            }
            IfRedundancy = false;
            delIndex = cLen - uc;//删除标志位开始索引
            for (i = 0; i < (uc - 1); i++) {
                if (tm[c[delIndex + i]] == i) {
                    tm[c[delIndex + i]]++;
                    IfRedundancy = true;
                    dl++;
                }
                else {
                    IfRedundancy = false;
                    dl = 0;
                    break;
                }
            }
        IfRedundancy:
            if (IfRedundancy) {
                //有多余填充,补上标志位
                dl++;
            }
        }
    }
    return dl;
}
AESKeyLength _X_Check_AES_PaddingS(int Padding, const BYTE* data, int dataLen,
    BYTE*& lData, DWORD *lDataLen, 
    const BYTE* pKey, int keySize, BYTE*& lKey,
    const BYTE* pIV = NULL, int IVSize = NULL, BYTE** lIV = NULL) {
    AESKeyLength aesKeyLen;
    switch (Padding)
    {
    case X_AES_PKCS7_PADDING:
        aesKeyLen = _X_Check_AES_PKCS7_Padding(data, dataLen, lData, lDataLen, pKey, keySize, lKey, pIV, IVSize, lIV);
        break;
    case X_AES_ZERO_PADDING:
        aesKeyLen = _X_Check_AES_ZERO_Padding(data, dataLen, lData, lDataLen, pKey, keySize, lKey, pIV, IVSize, lIV);
        break;
    case X_AES_X923_PADDING:
        aesKeyLen = _X_Check_AES_X923_Padding(data, dataLen, lData, lDataLen, pKey, keySize, lKey, pIV, IVSize, lIV);
        break;
    case X_AES_ISO10126_PADDING:
        aesKeyLen = _X_Check_AES_ISO10126_Padding(data, dataLen, lData, lDataLen, pKey, keySize, lKey, pIV, IVSize, lIV);
        break;
    case X_AES_ISO78164_PADDING:
        aesKeyLen = _X_Check_AES_ISO78164_Padding(data, dataLen, lData, lDataLen, pKey, keySize, lKey, pIV, IVSize, lIV);
        break;
    default:
        return AESKeyLength::AES_ERROR;
    }
    return aesKeyLen;
}

//校验_AES加密_ECB
CXBytes X_Check_EnCrypto_AES_ECB(const CXBytes& data, const CXBytes& Key, int Padding) {
    return X_Check_EnCrypto_AES_ECB_Ex(data.get(), data.size(), Key.get(), Key.size(), Padding);
}
//校验_AES加密_ECB_Ex
CXBytes X_Check_EnCrypto_AES_ECB_Ex(const BYTE* data, int dataLen, const BYTE* pKey, int keySize, int Padding) {
    CXBytes r;
    BYTE* lData = NULL;
    DWORD ldataLen;
    BYTE* lKey = NULL;
    AESKeyLength aesKeyLen;
    aesKeyLen=_X_Check_AES_PaddingS(Padding, data, dataLen, lData, &ldataLen, pKey, keySize, lKey);
    if (aesKeyLen== AESKeyLength::AES_ERROR) {
        return r;
    }
    if (lData == NULL || lKey == NULL) {
        if (!lData) {
            delete[]lData;
        }
        if (!lKey) {
            delete[]lKey;
        }return r;
    }
    AES a(aesKeyLen);
    auto c = a.EncryptECB(lData, ldataLen, lKey);
    r.add(c, ldataLen);
    if (lData !=NULL) {
        delete[]lData;
    }
    if (lKey != NULL) {
        delete[]lKey;
    }
    if (c != NULL) {
        delete[]c;
    }
    return r;
}

//校验_AES解密_ECB
CXBytes X_Check_DeCrypto_AES_ECB(const CXBytes& data, const CXBytes& Key, int Padding) {
    return X_Check_DeCrypto_AES_ECB_Ex(data.get(), data.size(), Key.get(), Key.size(), Padding);
}
//校验_AES解密_ECB_Ex
CXBytes X_Check_DeCrypto_AES_ECB_Ex(const BYTE* data, int dataLen, const BYTE* pKey, int keySize, int Padding) {
    CXBytes r;
    BYTE* lData = NULL;
    DWORD ldataLen;
    BYTE* lKey = NULL;
    AESKeyLength aesKeyLen;
    aesKeyLen = _X_Check_AES_PaddingS(Padding, data, dataLen, lData, &ldataLen, pKey, keySize, lKey);
    if (aesKeyLen == AESKeyLength::AES_ERROR) {
        return r;
    }
    //memset(lData,0, ldataLen);
    if (lData == NULL || lKey == NULL) {
        if (!lData) {
            delete[]lData;
        }
        if (!lKey) {
            delete[]lKey;
        }return r;
    }
    AES a(aesKeyLen);
    unsigned char* c = a.DecryptECB(lData, ldataLen, lKey);
    //删除多余填充区
    int dl = _X_Check_DeCrypto_AES_Calculate_Padding(Padding,c, ldataLen);
    r.add(c, ldataLen- dl);
    if (lData!=NULL) {
        delete[]lData;
    }
    if (lKey!=NULL) {
        delete[]lKey;
    }
    if (c!=NULL) {
        delete[]c;
    }
    return r;
}

//校验_AES加密_CBC
CXBytes X_Check_EnCrypto_AES_CBC(const CXBytes& data, const CXBytes& Key, const CXBytes& IV, int Padding ) {
    return X_Check_EnCrypto_AES_CBC_Ex(data.get(), data.size(),Key.get(),Key.size(),IV.get(),IV.size(), Padding);
}
//校验_AES加密_CBC_Ex
CXBytes X_Check_EnCrypto_AES_CBC_Ex(const BYTE* data, int dataLen, 
    const BYTE* pKey, int keySize,
    const BYTE* pIV, int IVSize, int Padding ) {
    CXBytes r;
    BYTE* lData = NULL;
    DWORD ldataLen;
    BYTE* lKey = NULL;
    BYTE* lIv = NULL;
    AESKeyLength aesKeyLen;
    aesKeyLen = _X_Check_AES_PaddingS(Padding, data, dataLen, lData, &ldataLen, pKey, keySize, lKey,pIV,IVSize,&lIv);
    if (aesKeyLen == AESKeyLength::AES_ERROR) {
        return r;
    }
    if (lData == NULL || lKey == NULL) {
        if (!lData) {
            delete[]lData;
        }
        if (!lKey) {
            delete[]lKey;
        }
        if (!lIv) {
            delete[]lIv;
        }return r;
    }
    AES a(aesKeyLen);
    auto c = a.EncryptCBC(lData, ldataLen, lKey, lIv);
    r.add(c, ldataLen);
    if (lData != NULL) {
        delete[]lData;
    }
    if (lKey != NULL) {
        delete[]lKey;
    }
    if (lIv != NULL) {
        delete[]lIv;
    }
    if (c != NULL) {
        delete[]c;
    }
    return r;
}

//校验_AES解密_CBC
CXBytes X_Check_DeCrypto_AES_CBC(const CXBytes& data, const CXBytes& Key, const CXBytes& IV, int Padding) {
    return X_Check_DeCrypto_AES_CBC_Ex(data.get(), data.size(), Key.get(), Key.size(),IV.get(),IV.size(), Padding);
}
//校验_AES解密_CBC_Ex
CXBytes X_Check_DeCrypto_AES_CBC_Ex(const BYTE* data, int dataLen, 
    const BYTE* pKey, int keySize, 
    const BYTE* pIV, int IVSize, int Padding) {
    CXBytes r;
    BYTE* lData = NULL;
    DWORD ldataLen;
    BYTE* lKey = NULL;
    BYTE* lIv = NULL;
    AESKeyLength aesKeyLen;
    aesKeyLen = _X_Check_AES_PaddingS(Padding, data, dataLen, lData, &ldataLen, pKey, keySize, lKey, pIV, IVSize, &lIv);
    if (aesKeyLen == AESKeyLength::AES_ERROR) {
        return r;
    }
    //memset(lData,0, ldataLen);
    if (lData == NULL || lKey == NULL) {
        if (!lData) {
            delete[]lData;
        }
        if (!lKey) {
            delete[]lKey;
        }
        if (!lIv) {
            delete[]lIv;
        }return r;
    }
    AES a(aesKeyLen);
    unsigned char* c = a.DecryptCBC(lData, ldataLen, lKey,lIv);
    //删除多余填充区
    int dl = _X_Check_DeCrypto_AES_Calculate_Padding(Padding, c, ldataLen);
    r.add(c, ldataLen - dl);
    if (lData != NULL) {
        delete[]lData;
    }
    if (lKey != NULL) {
        delete[]lKey;
    }
    if (!lIv) {
        delete[]lIv;
    }
    if (c != NULL) {
        delete[]c;
    }
    return r;
}

//校验_AES加密_CFB
CXBytes X_Check_EnCrypto_AES_CFB(const CXBytes& data, const CXBytes& Key, const CXBytes& IV, int Padding) {
    return X_Check_EnCrypto_AES_CFB_Ex(data.get(), data.size(), Key.get(), Key.size(), IV.get(), IV.size(), Padding);
}
//校验_AES加密_CFB_Ex
CXBytes X_Check_EnCrypto_AES_CFB_Ex(const BYTE* data, int dataLen,
    const BYTE* pKey, int keySize,
    const BYTE* pIV, int IVSize, int Padding) {
    CXBytes r;
    BYTE* lData = NULL;
    DWORD ldataLen;
    BYTE* lKey = NULL;
    BYTE* lIv = NULL;
    AESKeyLength aesKeyLen;
    aesKeyLen = _X_Check_AES_PaddingS(Padding, data, dataLen, lData, &ldataLen, pKey, keySize, lKey, pIV, IVSize, &lIv);
    if (aesKeyLen == AESKeyLength::AES_ERROR) {
        return r;
    }
    if (lData == NULL || lKey == NULL) {
        if (!lData) {
            delete[]lData;
        }
        if (!lKey) {
            delete[]lKey;
        }
        if (!lIv) {
            delete[]lIv;
        }return r;
    }
    AES a(aesKeyLen);
    auto c = a.EncryptCFB(lData, ldataLen, lKey, lIv);
    r.add(c, ldataLen);
    if (lData != NULL) {
        delete[]lData;
    }
    if (lKey != NULL) {
        delete[]lKey;
    }
    if (lIv != NULL) {
        delete[]lIv;
    }
    if (c != NULL) {
        delete[]c;
    }
    return r;
}

//校验_AES解密_CFB
CXBytes X_Check_DeCrypto_AES_CFB(const CXBytes& data, const CXBytes& Key, const CXBytes& IV, int Padding) {
    return X_Check_DeCrypto_AES_CFB_Ex(data.get(), data.size(), Key.get(), Key.size(), IV.get(), IV.size(), Padding);
}
//校验_AES解密_CFB_Ex
CXBytes X_Check_DeCrypto_AES_CFB_Ex(const BYTE* data, int dataLen,
    const BYTE* pKey, int keySize,
    const BYTE* pIV, int IVSize, int Padding) {
    CXBytes r;
    BYTE* lData = NULL;
    DWORD ldataLen;
    BYTE* lKey = NULL;
    BYTE* lIv = NULL;
    AESKeyLength aesKeyLen;
    aesKeyLen = _X_Check_AES_PaddingS(Padding, data, dataLen, lData, &ldataLen, pKey, keySize, lKey, pIV, IVSize, &lIv);
    if (aesKeyLen == AESKeyLength::AES_ERROR) {
        return r;
    }
    //memset(lData,0, ldataLen);
    if (lData == NULL || lKey == NULL) {
        if (!lData) {
            delete[]lData;
        }
        if (!lKey) {
            delete[]lKey;
        }
        if (!lIv) {
            delete[]lIv;
        }return r;
    }
    AES a(aesKeyLen);
    unsigned char* c = a.DecryptCFB(lData, ldataLen, lKey, lIv);
    //删除多余填充区
    int dl = _X_Check_DeCrypto_AES_Calculate_Padding(Padding, c, ldataLen);
    r.add(c, ldataLen - dl);
    if (lData != NULL) {
        delete[]lData;
    }
    if (lKey != NULL) {
        delete[]lKey;
    }
    if (!lIv) {
        delete[]lIv;
    }
    if (c != NULL) {
        delete[]c;
    }
    return r;
}

//废弃
//校验_Blowfish加密
CXBytes __X_Check_EnCrypto_Blowfish(const BYTE* pKey, int KeySize, const BYTE*pData, int DataSize) {
    //X_CBLOWFISH Blowfish;
    //Blowfish.InitKey((unsigned char*)pKey, KeySize);
    //int outlen = 0;
    //BYTE* out = new BYTE[DataSize * 2];
    //Blowfish.EncryptData((unsigned char*)pData, DataSize, out, DataSize * 2);
    CXBytes r;
    //delete[]out;
    //return r;
	return r;
}