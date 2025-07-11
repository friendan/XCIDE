#include "module_e_network.h"

#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")
#include <Winsock2.h>

namespace XuanYi
{
	UINT ConvertToIP(CXText HostName, CXVector<CXText> &IP_Arrays, BOOL IPV6)
	{
		IP_Arrays.clear();
		std::wstring hostname = HostName.getPtr();
		struct addrinfoW hints, *res, *iter;
		int status;
		char ipstr[INET6_ADDRSTRLEN];

		memset(&hints, 0, sizeof(hints));
		hints.ai_family = IPV6 ? AF_INET6 : AF_INET; // IPv4或IPv6
		hints.ai_socktype = SOCK_STREAM;

		if ((status = GetAddrInfoW(hostname.c_str(), NULL, &hints, &res)) != 0)
		{
			// std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
			return 0;
		}

		std::string ipAddress;
		for (iter = res; iter != NULL; iter = iter->ai_next)
		{
			void *addr;
			std::string ipver;

			if (iter->ai_family == AF_INET)
			{ // IPv4
				struct sockaddr_in *ipv4 = (struct sockaddr_in *)iter->ai_addr;
				addr = &(ipv4->sin_addr);
			}
			else
			{ // IPv6
				struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)iter->ai_addr;
				addr = &(ipv6->sin6_addr);
			}

			inet_ntop(iter->ai_family, addr, ipstr, sizeof(ipstr));
			std::cout << ipstr << std::endl;
			IP_Arrays.add(xcl_toText(CXTextA(ipstr)));
		}

		FreeAddrInfoW(res); // 释放addrinfo结构占用的内存

		return IP_Arrays.size();
	}

	CXText ConvertToHostName(const CXText &IP_Address)
	{
		struct addrinfoW hints, *res;
		int status;
		//char ipstr[INET6_ADDRSTRLEN];
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		if ((status = GetAddrInfoW(IP_Address.getPtr(), NULL, &hints, &res)) != 0)
		{
			// std::cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
			return CXText();
		}

		// 输出主机名
		wchar_t host[NI_MAXHOST];
		status = GetNameInfoW(res->ai_addr, res->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NAMEREQD);

		FreeAddrInfoW(res);

		return (CXText(host));
	}

	CXText GetHostName()
	{
#if !defined(_WIN32_WINNT_WIN7)

		wchar_t hostname[1024] = {0};
		if (::GetHostNameW(hostname, 1024) == 0)
		{
			return CXText(hostname);
		}_WIN32_WINNT_WIN7
#endif
		return L"";
	}
	UINT GetLocalIPAddress(CXVector<CXText> &IP_Arrays, BOOL IPV6)
	{
#if !defined(_WIN32_WINNT_WIN7)
		IP_Arrays.clear();
		ULONG flags = GAA_FLAG_INCLUDE_PREFIX | GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_DNS_INFO | GAA_FLAG_SKIP_DNS_SERVER | GAA_FLAG_SKIP_FRIENDLY_NAME | GAA_FLAG_SKIP_MULTICAST;
		PIP_ADAPTER_ADDRESSES pAddresses = NULL;
		PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
		ULONG outBufLen = 0;
		DWORD ret = 0;
		ret = GetAdaptersAddresses(IPV6 ? AF_INET6 : AF_INET, flags, NULL, pAddresses, &outBufLen);

		if (ret == ERROR_BUFFER_OVERFLOW)
		{
			pAddresses = (IP_ADAPTER_ADDRESSES *)malloc(outBufLen);
			if (pAddresses == NULL)
			{
				return 0;
			}
		}
		ret = GetAdaptersAddresses(IPV6 ? AF_INET6 : AF_INET, flags, NULL, pAddresses, &outBufLen);
		// std::cout << "GetAdaptersAddresses:" << ret << std::endl;
		if (ret == NO_ERROR)
		{

			while (pAddresses)
			{
				std::wcout << L"Adapter Name: " << pAddresses->AdapterName << std::endl;
				std::wcout << L"Description: " << pAddresses->Description << std::endl;
				std::cout << "IfType: " << pAddresses->IfType << std::endl;
				std::cout << "OperStatus: " << pAddresses->OperStatus << std::endl;
				std::cout << "Physical Address: " << pAddresses->PhysicalAddress << std::endl;
				std::cout << "==========================" << std::endl;

				// 状态为可操作的
				if ((pAddresses->IfType == MIB_IF_TYPE_ETHERNET || pAddresses->IfType == IF_TYPE_IEEE80211) &&
																	  pAddresses->OperStatus == IfOperStatusUp)

				{

					if (StrStrW(pAddresses->Description, L"Virtual")==NULL || StrStrW(pAddresses->Description, L"Bluetooth")==NULL )
					{
						
						pUnicast = pAddresses->FirstUnicastAddress;
					while (pUnicast) // 单播IP
					{
						CHAR IP[130] = {0};
						if (AF_INET == pUnicast->Address.lpSockaddr->sa_family) // IPV4 地址，使用 IPV4 转换
							inet_ntop(PF_INET, &((sockaddr_in *)pUnicast->Address.lpSockaddr)->sin_addr, IP, sizeof(IP));
						else if (AF_INET6 == pUnicast->Address.lpSockaddr->sa_family) // IPV6 地址，使用 IPV6 转换
							inet_ntop(PF_INET6, &((sockaddr_in6 *)pUnicast->Address.lpSockaddr)->sin6_addr, IP, sizeof(IP));

						std::cout << IP << std::endl;
						IP_Arrays.add(xcl_toText(CXTextA(IP)));

						pUnicast = pUnicast->Next;
						std::cout << "Next: " << pUnicast << std::endl;
					}
					}
					
				}

				pAddresses = pAddresses->Next;
			}
		}
		free(pAddresses);
		return IP_Arrays.size();
#endif
		return 0;
	}
}