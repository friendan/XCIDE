#include "module_yyy.h"

//八到十
int X_Base_OctToDec(int octalNumber) {
    int decimalNumber = 0, i = 0, rem;
    while (octalNumber != 0) {
        rem = octalNumber % 10;
        octalNumber /= 10;
        decimalNumber += rem * (int)pow(8, i);
        ++i;
    }
    return decimalNumber;
}

//进制_二到十
double X_Base_BinToDec(const CXText& binStr) {
	double sum=0;//定义转化为十进制的数字为sum
	for (int i = 0; i < (int)binStr.size(); i++) {
		if (binStr[i] <L'0' && binStr[i]> L'1') {
			return 0;//直接退出
		}
		else if (binStr[i] == L'1') {
			int j = (int)pow(2, binStr.size() - i - 1);//这里考虑好二进制转化成十进制公示里面i和次方的关系
			sum += j;
		}
	}
	return sum;
}
//进制_二到十A
double X_Base_BinToDecA(const CXTextA& binStr) {
	double sum = 0;//定义转化为十进制的数字为sum
	for (int i = 0; i < (int)binStr.size(); i++) {
		if (binStr[i] < '0' && binStr[i]> '1') {
			return 0;//直接退出
		}
		else if (binStr[i] == '1') {
			int j = (int)pow(2, binStr.size() - i - 1);//这里考虑好二进制转化成十进制公示里面i和次方的关系
			sum += j;
		}
	}
	return sum;
}

//进制_到十进制A
LONGLONG X_Base_ToDecA(const CXTextA& str,int base) {
	return strtoll(str,NULL, base);
}
//进制_到十进制
LONGLONG X_Base_ToDec(const CXText& str, int base) {
	return wcstoll(str, NULL, base);
}

//@别名 进制_三十六到十(三十六进制文本)
LONGLONG X_Base_TsToDec(const CXText& str) {
	return wcstoll(str, NULL, 36);
}
//@别名 进制_三十六到十A(三十六进制文本)
LONGLONG X_Base_TsToDecA(const CXTextA& str){
	return strtoll(str, NULL, 36);
}

//@别名 进制_十到N进制A(欲转换的值,目标进制)
CXTextA X_Base_DecToNA(LONGLONG num, int base) {
	LONGLONG n = num;
	char bin[500];
	int len;
	memset(bin, 0, sizeof(bin));
	len = 0;
	int shang = 0;
	int i = 0;
	while (n >= 1) {
		shang = n % base;
		n /= base;
		bin[len] = 48 + shang;
		if (bin[len] > 57) {
			bin[len] += 7;
		}
		len++;
	}
	_strrev(bin); //反转字符串
	return bin;
}
//@别名 进制_十到N进制A(欲转换的值,目标进制)
CXText X_Base_DecToN(LONGLONG num, int base) {
	LONGLONG n = num;
	wchar_t bin[500];
	int len;
	memset(bin, 0, sizeof(bin));
	len = 0;
	int shang = 0;
	int i = 0;
	while (n >= 1) {
		shang = n % base;
		n /= base;
		bin[len] = 48 + shang;
		if (bin[len]>57) {
			bin[len] += 7;
		}
		len++;
	}
	_wcsrev(bin); //反转字符串
	return bin;
}

//进制_十到八进制
LONGLONG X_Base_DecToOct(LONGLONG num) {
	CXTextA r = X_Base_DecToNA(num,8);
	return strtoll(r,NULL,10);
}

//进制_十到二
CXTextA X_Base_DecToBinA(double x) {
	CXTextA r;
	int a[1000], b[1000];
	int num1 = (int)x;
	double num2 = x - num1;
	int iter = 0;
	//整数
	while (num1 > 0) {
		a[iter++] = num1 % 2;
		num1 /= 2;
	}
	for (int i = iter - 1, z = 4 - iter % 4 + 1; i >= 0; i--, z++)
	{
		char tia[10]={0};
		_itoa_s(a[i], tia,10);
		r += tia;
		if (z % 4 == 0) {
			//r += " ";
		}
	}
	bool adds = false;
	//小数
	iter = 0;
	while (fabs(num2 - 0.0) > 0.000001) {//double类型，num2==0.0
		if (!adds) { adds = true; r += ".";}
		b[iter] = (int)(num2 * 2);
		num2 = num2 * 2 - b[iter];
		iter++;
	}
	for (int i = 0; i < iter; i++)
	{
		char tia[10] = { 0 };
		_itoa_s(b[i], tia, 10);
		r += tia;
		r += tia;
		if ((i + 1) % 4 == 0) {
			//r += " ";
		}
	}
	return r;
}
//进制_十到二A
CXText X_Base_DecToBin(double x) {
	CXText r;
	int a[1000], b[1000];
	int num1 = (int)x;
	double num2 = x - num1;
	int iter = 0;
	//整数
	while (num1 > 0) {
		a[iter++] = num1 % 2;
		num1 /= 2;
	}
	for (int i = iter - 1, z = 4 - iter % 4 + 1; i >= 0; i--, z++)
	{
		wchar_t tia[10] = { 0 };
		_itow_s(a[i], tia, 10);
		r += tia;
		if (z % 4 == 0) {
			//r += " ";
		}
	}
	bool adds = false;
	//小数
	iter = 0;
	while (fabs(num2 - 0.0) > 0.000001) {//double类型，num2==0.0
		if (!adds) { adds = true; r += L"."; }
		b[iter] = (int)(num2 * 2);
		num2 = num2 * 2 - b[iter];
		iter++;
	}
	for (int i = 0; i < iter; i++)
	{
		wchar_t tia[10] = { 0 };
		_itow_s(b[i], tia, 10);
		r += tia;
		r += tia;
		if ((i + 1) % 4 == 0) {
			//r += " ";
		}
	}
	return r;
}

