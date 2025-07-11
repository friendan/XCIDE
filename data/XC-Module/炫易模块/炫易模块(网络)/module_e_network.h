#pragma once

//
//@模块名称 炫易模块(网络)
//@版本   1.0
//@日期   2024-10-10
//@作者   hxznhf
//@模块备注 封装常用网络操作指令


//@依赖  module_base.h

//@隐藏{
#include "module_base.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

//@隐藏}

//@src "network.cpp"




//@别名 炫易
namespace XuanYi
{


//@分组{	网络功能

//@别名 转换为IP地址(主机名称,IP地址数组,IPV6)
//@备注 将主机名称（或Web域名）转换为IP地址
//@参数 HostName 主机名称
//@参数 IP_Arrays IP地址数组
//@参数 IPV6 是否转IPV6地址(默认否)
//@返回 转换后的IP地址数量
UINT ConvertToIP(CXText HostName, CXVector<CXText>& IP_Arrays, BOOL IPV6 = FALSE);


//@别名 转换为主机名(IP地址)
//@备注 将IP地址转换为主机名称
//@参数 IP_Address IP地址
//@返回 主机名称
CXText ConvertToHostName(const CXText& IP_Address);


//@别名 取主机名()
//@备注 获取主机名称, 需要WIN10 SDK才支持
CXText GetHostName();

//@别名 取本机IP地址(IP地址数组,IPV6)
//@备注 获取本机IP地址(不含环回地址、蓝牙设备、虚拟网卡等),  需要WIN10 SDK才支持
//@参数 IP_Arrays IP地址数组
//@参数 IPV6 是否转IPV6地址(默认否)
//@返回 本机IP地址数量
UINT GetLocalIPAddress(CXVector<CXText>& IP_Arrays,BOOL IPV6 = FALSE);


//@分组}

} // namespace XuanYi






