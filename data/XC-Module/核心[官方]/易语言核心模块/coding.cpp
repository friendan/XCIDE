//
// Created by Huiyi on 2021/4/25.
//
#include "module_yyy.h"
#include <sstream>

//unicode转ascii
CXTextA X_Coding_WToA (const wchar_t* wp, size_t m_encode)
{
    int len = WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
    char	*l_char = (char*)malloc(len + 1);
    WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), l_char, len, NULL, NULL);
    l_char [len] = '\0';
    CXTextA rets = l_char;
    free(l_char);
    return  rets;
}

//ascii转unicode
CXText X_Coding_AToW(const char* c, size_t m_encode)
{
    int len = MultiByteToWideChar(m_encode, 0, c, strlen(c), NULL, 0);
    wchar_t*	l_wchar = new wchar_t [len + 1];
    MultiByteToWideChar(m_encode, 0, c, strlen(c), l_wchar, len);
    l_wchar [len] = '\0';
    CXText rets = l_wchar;
    delete [] l_wchar;
    return rets;
}

//Utf8转Gbk
CXTextA X_Coding_Utf82Gbk(const char* utf8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t* wstr = new wchar_t [len+1];
    memset(wstr, 0, len+1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = (char*)malloc(len+1);
    memset(str, 0, len+1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    if(wstr) { delete [] wstr; }
    CXTextA rets = str;
    free (str);
    return rets;
}

//Unicode转Utf8
CXTextA X_Coding_UnicodeToUtf8(const wchar_t* unicode)
{
    int len;
    len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
    char *szUtf8 = (char*)malloc(len + 1);
    memset(szUtf8, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
    CXTextA rets = szUtf8;
    free(szUtf8);
    return rets;
}

//GBK转Utf8
CXTextA X_Coding_GBKToUtf8(const char* str)
{
    return X_Coding_UnicodeToUtf8(X_Coding_AToW(str).get());
}

//编码_usc2到ansi
CXTextA X_Coding_Usc2ToAnsiA(const CXTextA& instr, CXTextA separator) {
    if (separator.size() == 0) { separator = "%"; }
    std::wstring str;
    char* pElementText;
    int iTextLen;
    wchar_t temp;
    //string to wide string
    for (int i = 0; i < instr.size(); i++)
    {
        if (instr[i] == separator[0])
        {
            if (instr[i + 1] == 'u' && (instr.size() - i) > 5) {
                char temp1 = instr[i + 2] <= '9' ? instr[i + 2] - '0' : instr[i + 2] - 'a' + 10;
                char temp2 = instr[i + 3] <= '9' ? instr[i + 3] - '0' : instr[i + 3] - 'a' + 10;
                char temp3 = instr[i + 4] <= '9' ? instr[i + 4] - '0' : instr[i + 4] - 'a' + 10;
                char temp4 = instr[i + 5] <= '9' ? instr[i + 5] - '0' : instr[i + 5] - 'a' + 10;
                temp = temp1 << 12 | temp2 << 8 | temp3 << 4 | temp4;
                str.push_back(temp);
                i = i + 5;
            }
            else
            {
                str = L"This is not uscii string!";
                break;
            }
        }
        else
        {
            str.push_back(instr[i]);
        }
    }
    // wide char to multi char
    iTextLen = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
    pElementText = new char[iTextLen + 1];
    memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
    WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, pElementText, iTextLen, NULL, NULL);
    CXTextA strText;
    strText = pElementText;
    delete[] pElementText;
    return strText;
}
//编码_usc2到ansi
CXText X_Coding_Usc2ToAnsi(const CXText& instr, CXText separator) {
    if (separator.size() == 0) { separator = L"%"; }
	std::wstring str;
	wchar_t temp;
	for (int i = 0; i < instr.size(); i++)
	{
		if (instr[i] == L'%')
		{
			if (instr[i + 1] == L'u' && (instr.size() - i) > 5) {
				char temp1 = instr[i + 2] <= L'9' ? instr[i + 2] - L'0' : instr[i + 2] - L'a' + 10;
				char temp2 = instr[i + 3] <= L'9' ? instr[i + 3] - L'0' : instr[i + 3] - L'a' + 10;
				char temp3 = instr[i + 4] <= L'9' ? instr[i + 4] - L'0' : instr[i + 4] - L'a' + 10;
				char temp4 = instr[i + 5] <= L'9' ? instr[i + 5] - L'0' : instr[i + 5] - L'a' + 10;
				temp = temp1 << 12 | temp2 << 8 | temp3 << 4 | temp4;
				str.push_back(temp);
				i = i + 5;
			}
			else {
				str = L"This is not uscii string!";
				break;
			}
		}
		else
		{
			str.push_back(instr[i]);
		}
	}
    str += L'\0';
	return str;
}


//文本转十六进制
CXText X_Coding_StringToHex(CXText& str, CXText separator) {
    CXText  text;
    wchar_t  hexs[17] = L"0123456789ABCDEF";
    wchar_t ch;
    BYTE* tc = (BYTE*)str.get();
    int l = str.size() * 2;
    for (int i = 0; i < l ; i++)
    {
        BYTE index = (tc[i] >> 4) & 0xf;

        ch = hexs[index];
        text += ch;

        index = tc[i] & 0xf;
        ch = hexs[index];

        text += ch;
    }
    text += L'\0';
    return text;
}
//文本转十六进制A
CXTextA X_Coding_StringToHexA(CXTextA& str, CXTextA separator) {
    static const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;
    std::string* stra = str.getString();
    for (int i = 0; i < str.size(); ++i) {
        ss << hex[(unsigned char)(*stra)[i] >> 4] << hex[(unsigned char)(*stra)[i] & 0xf];
        if (i< (str.size()-1)) {
            ss << separator.get();
        }
    }
    return ss.str();
}

//十六进制转文本
CXText X_Coding_HexToString(CXText& str) {
    CXText result;
    for (int i = 0; i < str.size(); i += 2) {//十六进制两个字符为原始字符一个字符
        CXText byte = str.substr(i, 2);//每次切两个字符
        //将十六进制的string转成long再强转成int再转成char
        wchar_t chr = (wchar_t)wcstol(byte, NULL, 16);
        result+=chr;//将处理完的字符压入result中
    }
    return result;
}
//十六进制转文本
CXTextA X_Coding_HexToStringA(CXTextA& str) {
    CXTextA result;
    for (int i = 0; i < str.size(); i += 2) {//十六进制两个字符为原始字符一个字符
        CXTextA byte = str.substr(i, 2);//每次切两个字符
        //将十六进制的string转成long再强转成int再转成char
        char chr = (char)strtol (byte, NULL, 16);
        result += chr;//将处理完的字符压入result中
    }
    return result;
}

//编码_ansi到usc2
CXText X_Coding_AnsiToUsc2(const CXText& instr,CXText separator) {
	int len = instr.size();
    static const std::wstring hex = L"0123456789ABCDEF";
    std::wstringstream ss;
    for (int i = 0; i < len; i++) {
        ss << separator<<L"u00" << hex[(wchar_t)instr[i] >> 4] << hex[(wchar_t)instr[i] & 0xf];
    }
    return ss.str();
}
//编码_ansi到usc2A
CXTextA X_Coding_AnsiToUsc2A(const CXTextA& instr, CXTextA separator) {
	int len = instr.size();
    static const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;
    for (int i = 0; i < len; i++) {
        ss << separator << L"u00" << hex[(unsigned char)instr[i] >> 4] << hex[(unsigned char)instr[i] & 0xf];
    }
    return ss.str();
}

