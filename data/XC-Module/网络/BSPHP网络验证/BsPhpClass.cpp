#include"module_BsPhpClass.h"


std::string BSPHP_ServerUrl;
std::string BSPHP_MesKey;
std::string BSPHP_SeSsL;
std::string BSPHP_PcHWID;
std::string BSPHP_BSPHP_PASSWORD;
void BSPHP_SetServerUrl(const wchar_t* url)
{
	BSPHP_ServerUrl = W2A_(url);
}

void BSPHP_SetMesKey(const wchar_t* key)
{
	BSPHP_MesKey = W2A_(key);
}

void BSPHP_SetMaxoror(const wchar_t* maxoror)
{
	BSPHP_PcHWID = W2A_(maxoror);
}

//#include"stdafx.h"
#define IsHexNum(c) ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))

std::string BSPHP_Utf8ToStringT(LPSTR str)
{
	_ASSERT(str);
	USES_CONVERSION;
	WCHAR *buf;
	int length = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	buf = new WCHAR[length + 1];
	ZeroMemory(buf, (length + 1) * sizeof(WCHAR));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, buf, length);

	return (std::string(W2A(buf)));
}
std::string BSPHP_UrlDecode(LPCTSTR url)
{
	_ASSERT(url);
	USES_CONVERSION;
	LPSTR _url = T2A(const_cast<LPTSTR>(url));
	int i = 0;
	int length = (int)strlen(_url);
	char *buf = new char[length];
	ZeroMemory(buf, length);
	char* p = buf;
	char tmp[4];
	while (i < length)
	{
		if (i <= length - 3 && _url[i] == '%' && IsHexNum(_url[i + 1]) && IsHexNum(_url[i + 2]))
		{
			memset(tmp, 0, sizeof(tmp));
			memcpy(tmp, _url + i + 1, 2);
			sscanf_s((const char*)tmp, "%hhx", p++);
			i += 3;
		}
		else
		{
			*(p++) = _url[i++];
		}
	}
	return std::string(buf);
	//return Utf8ToStringT(buf);
}

std::string BSPHP_time_Format(time_t tm_in, const char* pFormat)
{
	if (pFormat == NULL)
		return pFormat;

	char szBuffer[maxTimeBufferSize];
	struct tm ptmTemp;
	if (_localtime64_s(&ptmTemp, &tm_in) != 0)
		AtlThrow(E_INVALIDARG);

	if (!strftime(szBuffer, maxTimeBufferSize, pFormat, &ptmTemp))
		szBuffer[0] = '\0';
	return szBuffer;
}

std::string BSPHP_GetTime() {
	std::string Time;
	CTime tm; tm = CTime::GetCurrentTime();
	//Time = tm.Format("%Y-%m-%d %X");
	Time = BSPHP_time_Format(tm.GetTime(), "%Y-%m-%d %X");
	return Time;
}

//账号登录
CXText BSPHP_Login(const wchar_t* UserName, const wchar_t* PassWorld) {
	CHttpClient Http;
	std::string Data;
	std::string RetData;
	Data = "&api=login.lg&date=";
	Data += BSPHP_GetTime();
	Data += "&mutualkey=";
	Data += BSPHP_MesKey;
	Data += "&user=";
	Data += W2A_(UserName);
	Data += "&pwd=";
	Data += W2A_(PassWorld);
	Data += "&BSphpSeSsL=";
	Data += BSPHP_SeSsL;
	Data += "&maxoror=";
	Data += BSPHP_PcHWID;

	Http.HttpPost(BSPHP_ServerUrl.c_str(), Data.c_str(), RetData);
	//MessageBox(0, RetData.c_str(), "0", MB_OK);
	return A2W_(RetData.c_str(), (int)RetData.size());
}

//获取初始化网络测试
BOOL BSPHP_Internet() {
	CHttpClient Http;
	std::string Data;
	std::string RetData;
	Data = "&api=internet.in&date=";
	Data += BSPHP_GetTime();
	Data += "&mutualkey=";
	Data += BSPHP_MesKey;

	Http.HttpPost(BSPHP_ServerUrl.c_str(), Data.c_str(), RetData);
	if (RetData == "1") {
		return true;
	}
	return false;
}

//初始化返回信息
CXText BSPHP_Internetinfo() {

	std::string Data;
	Data = "&api=internet.in&date=";
	Data += BSPHP_GetTime();
	Data += "&mutualkey=";
	Data += BSPHP_MesKey;

	std::string RetData;
	CHttpClient Http;
	Http.HttpPost(BSPHP_ServerUrl.c_str(), Data.c_str(), RetData);
	return A2W_(RetData.c_str(), (int)RetData.size());  //RetData.c_str();
}
//获取公告
CXText BSPHP_GetGG() {
	CHttpClient Http;
	std::string Data;
	std::string RetData;
	Data += "&api=gg.in&date=";
	Data += BSPHP_GetTime();
	Data += "&mutualkey=";
	Data += BSPHP_MesKey;
	Data += "&BSphpSeSsL=";
	Data += BSPHP_SeSsL;

	Http.HttpPost(BSPHP_ServerUrl.c_str(), Data.c_str(), RetData);
	return A2W_(RetData.c_str(), (int)RetData.size());// RetData.c_str();
}

//获取连接串 session
CXText BSPHP_GetBSphpSeSsL() {
	CHttpClient Http;
	std::string Data;
	Data += "&api=BSphpSeSsL.in&date=";
	Data += BSPHP_GetTime();
	Data += "&mutualkey=";
	Data += BSPHP_MesKey;

	Http.HttpPost(BSPHP_ServerUrl.c_str(), Data.c_str(), BSPHP_SeSsL);
	return  A2W_(BSPHP_SeSsL.c_str(), (int)BSPHP_SeSsL.size());
}

//注册账号
CXText BSPHP_Reg(const wchar_t* UserName, const wchar_t* PassWorld, const wchar_t* QQ) {
	CHttpClient Http;
	std::string Data;
	std::string RetData;
	Data = "&api=registration.lg&date=";
	Data += BSPHP_GetTime();
	Data += "&mutualkey=";
	Data += BSPHP_MesKey;
	Data += "&user=";
	Data += W2A_(UserName);
	Data += "&pwd=";
	Data += W2A_(PassWorld);
	Data += "&pwdb=";
	Data += W2A_(PassWorld);
	Data += "&BSphpSeSsL=";
	Data += BSPHP_SeSsL;
	Data += "&maxoror=";
	Data += BSPHP_PcHWID;
	Data += "&qq=";
	Data += W2A_(QQ);

	Http.HttpPost(BSPHP_ServerUrl.c_str(), Data.c_str(), RetData);
	return A2W_(RetData.c_str(), (int)RetData.size());
}

//充值续费
CXText BSPHP_Pay(const wchar_t* UserName, const wchar_t* PassWorld, const wchar_t* KH, const wchar_t* KM) {
	CHttpClient Http;
	std::string Data;
	std::string RetData;
	Data = "&api=chong.lg&date=";
	Data += BSPHP_GetTime();
	Data += "&mutualkey=";
	Data += BSPHP_MesKey;
	Data += "&user=";
	Data += W2A_(UserName);
	Data += "&userpwd=";
	Data += W2A_(PassWorld);
	Data += "&userset=1&BSphpSeSsL=";
	Data += BSPHP_SeSsL;
	Data += "&ka=";
	Data += W2A_(KH);
	Data += "&pwd=";
	Data += W2A_(KM);

	Http.HttpPost(BSPHP_ServerUrl.c_str(), Data.c_str(), RetData);
	return A2W_(RetData.c_str(), (int)RetData.size());
}

CXText BSPHP_ModifyPassword(const wchar_t* UserName, const wchar_t* PassWorldOld, const wchar_t* PassWorldNew)
{
	CHttpClient Http;
	std::string Data;
	std::string RetData;
	Data = "&api=password.lg&date=";
	Data += BSPHP_GetTime();
	Data += "&mutualkey=";
	Data += BSPHP_MesKey;
	Data += "&user=";
	Data += W2A_(UserName);
	Data += "&pwd=";
	Data += W2A_(PassWorldOld);
	Data += "&BSphpSeSsL=";
	Data += BSPHP_SeSsL;
	Data += "&pwda=";
	Data += W2A_(PassWorldNew);
	Data += "&pwdb=";
	Data += W2A_(PassWorldNew);

	Http.HttpPost(BSPHP_ServerUrl.c_str(), Data.c_str(), RetData);
	return A2W_(RetData.c_str(), (int)RetData.size());
}



//''更多BSPHP-PRO api接口请关注帮助中心 http://www.bsphp.com/index.php?act=chm&id=69