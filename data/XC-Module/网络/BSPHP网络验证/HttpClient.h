#pragma once

#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H


#if XC_MOUDLE
#include "module_curl.h"
#include "module_base.h"
#endif

#define  IE_AGENT  "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727)"

// �����ɹ�
#define SUCCESS        0
// ����ʧ��
#define FAILURE        1
// ������ʱ
#define OUTTIME        2

class CHttpClient
{
public:
	CHttpClient(const char* strAgent = IE_AGENT);
	virtual ~CHttpClient(void);

	int HttpGet(const char* strUrl, const char* strPostData, std::string &strResponse);
	int HttpPost(const char* strUrl, const char* strPostData, std::string &strResponse);

private:
	int ExecuteRequest(const char* strMethod, const char* strUrl, const char* strPostData, std::string &strResponse);
	void Clear();

private:
	CURL���紫����   m_curl;
//	CInternetSession *m_pSession;
//	CHttpConnection *m_pConnection;
//	CHttpFile *m_pFile;
	//inline BYTE toHex(const BYTE &x);
	std::string UrlEncode(std::string sIn);
};

#endif // HTTPCLIENT_H