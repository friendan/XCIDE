#include "AES.h"  
#include "AES_Base64.h"

char g_bsphp_key[17] = "asdfwetyhjuytrfd";
char g_bsphp_iv[17] = "gfdertfghjkuyrtg";


void BSPHP_SetAesKey(const wchar_t* aeskey)
{
	CXTextA text= W2A_(aeskey);
	memcpy((char*)g_bsphp_key, text.get(), 17);
}

//AES加密
std::string EncryptionAES(const std::string& strSrc)
{
	int length = (int)strSrc.length();
	int block_num = (int)length / BLOCK_SIZE + 1;
	//明文  
	char* szDataIn = new char[block_num * BLOCK_SIZE + 1];
	memset(szDataIn, 0x00, block_num * BLOCK_SIZE + 1);
	strcpy_s(szDataIn, block_num * BLOCK_SIZE + 1, strSrc.c_str());
	
	//进行PKCS7Padding填充。  
	int k = length % BLOCK_SIZE;
	int j = length / BLOCK_SIZE;
	int padding = BLOCK_SIZE - k;
	for (int i = 0; i < padding; i++)
	{
		szDataIn[j * BLOCK_SIZE + k + i] = padding;
	}
	szDataIn[block_num * BLOCK_SIZE] = '\0';

	//加密后的密文  
	char *szDataOut = new char[block_num * BLOCK_SIZE + 1];
	memset(szDataOut, 0, block_num * BLOCK_SIZE + 1);

	//进行进行AES的CBC模式加密  
	AES aes;
	aes.MakeKey(g_bsphp_key, g_bsphp_iv, 16, 16);
	aes.Encrypt(szDataIn, szDataOut, block_num * BLOCK_SIZE, AES::CBC);
	CXTextA str = XCL_base64_encode((const char*)szDataOut, block_num * BLOCK_SIZE);
	//std::string str = base64_encode((const unsigned char*)szDataOut, block_num * BLOCK_SIZE);
	delete[] szDataIn;
	delete[] szDataOut;
	return str.get();
}

std::string DecryptionAES(const std::string& strSrc) //AES解密  
{
	CXTextA strData = XCL_base64_decode(strSrc.c_str(), (int)strSrc.size());
	//std::string strData = base64_decode(strSrc.c_str());
	int length = (int)strData.size();
	//密文  
	char *szDataIn = new char[length + 1];
	memcpy(szDataIn, strData.get(), length + 1);
	//明文  
	char *szDataOut = new char[length + 1];
	memcpy(szDataOut, strData.get(), length + 1);

	//进行AES的CBC模式解密  
	AES aes;
	aes.MakeKey(g_bsphp_key, g_bsphp_iv, 16, 16);
	aes.Decrypt(szDataIn, szDataOut, length, AES::CBC);
	//去PKCS7Padding填充  
	if (0 < szDataOut[length - 1] && szDataOut[length - 1] <= 0x16)
	{
		int tmp = szDataOut[length - 1];
		for (int i = length - 1; i >= length - tmp; i--)
		{
			if (szDataOut[i] != tmp)
			{
				memset(szDataOut, 0, length);
				cout << "去填充失败！解密出错！！" << endl;
				break;
			}
			else
				szDataOut[i] = 0;
		}
	}
	std::string strDest(szDataOut);
	delete[] szDataIn;
	delete[] szDataOut;
	return strDest;
}