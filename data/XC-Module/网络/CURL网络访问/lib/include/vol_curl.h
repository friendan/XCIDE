#ifndef __VOL_CURL_H__
#define __VOL_CURL_H__

#include <curl.h>

class CCurlWraper
{
	private:
		CURL * pData;
		
	public:
		struct curl_slist * headers;
		struct curl_slist * proxyHeaders;
		struct curl_slist * connect_to;
		struct curl_slist * aliases;
		struct curl_slist * rcpts;
		struct curl_slist * ftpQuoteCmds;
		struct curl_slist * ftpPostQuoteCmds;
		struct curl_slist * ftpPreQuoteCmds;
	
		CCurlWraper() 
		{ 
			pData = curl_easy_init();
			headers = NULL;
			proxyHeaders = NULL;
			connect_to = NULL;
			aliases = NULL;
			rcpts = NULL;
			ftpQuoteCmds = NULL;
			ftpPostQuoteCmds = NULL;
			ftpPreQuoteCmds = NULL;
		}
		
		CURL * GetCurl() 
		{ 
			if (pData == NULL)	//避免被Cleanup主动释放后再次使用.
				pData = curl_easy_init();
			return pData;
		}
		
		void Cleanup()
		{
			if (pData)
			{
				curl_easy_pause(pData, CURLPAUSE_ALL);
				curl_easy_cleanup(pData);
				pData = NULL;
			}
		}
		
		void ClearHeaderList()
		{
			if (headers)
				curl_slist_free_all(headers);
			headers = NULL;
		}
		
		void ClearProxyHeaderList()
		{
			if (proxyHeaders)
				curl_slist_free_all(proxyHeaders);
			proxyHeaders = NULL;
		}
		
		void ClearConnectToList()
		{
			if (connect_to)
				curl_slist_free_all(connect_to);
			connect_to = NULL;
		}
		
		void ClearAliasesList()
		{
			if (aliases)
				curl_slist_free_all(aliases);
			aliases = NULL;
		}
		
		void ClearRcptsList()
		{
			if (rcpts)
				curl_slist_free_all(rcpts);
			rcpts = NULL;
		}
		
		void ClearFtpQuoteCmdsList()
		{
			if (ftpQuoteCmds)
				curl_slist_free_all(ftpQuoteCmds);
			ftpQuoteCmds = NULL;
		}
		
		void ClearFtpPostQuoteCmdsList()
		{
			if (ftpPostQuoteCmds)
				curl_slist_free_all(ftpPostQuoteCmds);
			ftpPostQuoteCmds = NULL;
		}
		
		void ClearFtpPreQuoteCmdsList()
		{
			if (ftpPreQuoteCmds)
				curl_slist_free_all(ftpPreQuoteCmds);
			ftpPreQuoteCmds = NULL;
		}
		
		void ClearAll()
		{
			ClearHeaderList();
			ClearProxyHeaderList();
			ClearConnectToList();
			ClearAliasesList();
			ClearRcptsList();
			ClearFtpQuoteCmdsList();
			ClearFtpPostQuoteCmdsList();
			ClearFtpPreQuoteCmdsList();
			Cleanup();
		}
		
		//回调函数相关
		CURLcode SetWriteFunction(INT_P userData, curl_write_callback writeCallback)
		{
			CURLcode ret = curl_easy_setopt(pData, CURLOPT_WRITEDATA, (void*)userData);
			if (ret != CURLE_OK)
			{
				return ret;
			}
			return curl_easy_setopt(pData, CURLOPT_WRITEFUNCTION, writeCallback);
		}
		
		CURLcode SetReadFunction(INT_P userData, curl_read_callback readCallback)
		{
			CURLcode ret = curl_easy_setopt(pData, CURLOPT_READDATA, (void*)userData);
			if (ret != CURLE_OK)
			{
				return ret;
			}
			return curl_easy_setopt(pData, CURLOPT_READFUNCTION, readCallback);
		}
		
		CURLcode SetSeekFunction(INT_P userData, curl_seek_callback seekCallback)
		{
			CURLcode ret = curl_easy_setopt(pData, CURLOPT_SEEKDATA, (void*)userData);
			if (ret != CURLE_OK)
			{
				return ret;
			}
			return curl_easy_setopt(pData, CURLOPT_SEEKFUNCTION, seekCallback);
		}
		
		CURLcode SetXferinfoFunction(INT_P userData, curl_xferinfo_callback progressCallback)
		{
			CURLcode ret = curl_easy_setopt(pData, CURLOPT_XFERINFODATA, (void*)userData);
			if (ret != CURLE_OK)
			{
				return ret;
			}
			return curl_easy_setopt(pData, CURLOPT_XFERINFOFUNCTION, progressCallback);
		}
		
		CURLcode SetHeaderFunction(INT_P userData, curl_read_callback headerCallback)
		{
			CURLcode ret = curl_easy_setopt(pData, CURLOPT_HEADERDATA, (void*)userData);
			if (ret != CURLE_OK)
			{
				return ret;
			}
			return curl_easy_setopt(pData, CURLOPT_HEADERFUNCTION, headerCallback);
		}

		~CCurlWraper()
		{
			ClearAll();
		}
};

class CCurlMimeWraper	//多用途扩展格式类
{
	public:
		curl_mime * mime;
		
		CCurlMimeWraper()
		{
			mime = NULL;
		}
		
		~CCurlMimeWraper()
		{
			if (mime)
				curl_mime_free(mime);
		}
};

class CCurlMimePartWraper
{
	public:
		curl_mimepart * part;	//curl_mimepart跟随mime生命周期
		struct curl_slist * headers;
		
		CCurlMimePartWraper()
		{
			part = NULL;
			headers = NULL;
		}
		
		void ClearHeaderList()
		{
			if (headers)
				curl_slist_free_all(headers);
			headers = NULL;
		}
		
		~CCurlMimePartWraper()
		{
			ClearHeaderList();
		}
};

#endif /* __VOL_CURL_H__ */