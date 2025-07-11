#pragma once

//@模块名称  WinSocket2
//@版本  1.0.0
//@日期  2023-04-5
//@作者  Bestkakkoii (QQ: 1642687802)
//@模块备注 封装自微软网路API
//@依赖  module_base.h


#include <in6addr.h>
#include <ws2tcpip.h>
#include <ws2spi.h>
#include <mswsock.h>
#include <mswsockdef.h>
#include <wsrm.h>
#include <wsnwlink.h>
#include <ws2atm.h>
#include <mstcpip.h>
#include <af_irda.h>
#include <nspapi.h>
#include <sporder.h>
#include <nsemail.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "mswsock.lib")

/*@声明

#define WSAAPI __stdcall

//@分组{ af_irda.h

typedef struct _SOCKADDR_IRDA {
  u_short irdaAddressFamily;
  u_char  irdaDeviceID[4];
  char    irdaServiceName[25];
} SOCKADDR_IRDA, *PSOCKADDR_IRDA, *LPSOCKADDR_IRDA;

//@分组}

//@分组{ in6addr.h

//
// IPv6 Internet address (RFC 2553)
// This is an 'on-wire' format structure.
//
typedef struct in6_addr_uchar {
    UCHAR       Byte[16];
} IN6_ADDR_UCHAR, *PIN6_ADDR_UCHAR, *LPIN6_ADDR_UCHAR;

typedef struct in6_addr_ushort {
    USHORT      Word[8];
} IN6_ADDR_USHORT, *PIN6_ADDR_USHORT, *LPIN6_ADDR_USHORT;

//@分组}


//@分组{ inaddr.h

//
// IPv4 Internet address
// This is an 'on-wire' format structure.
//
typedef struct in_addr_uchar {
    u_char s_b1;
    u_char s_b2;
    u_char s_b3;
    u_char s_b4;
} IN_ADDR_UCHAR, *PIN_ADDR_UCHAR, *LPIN_ADDR_UCHAR;

typedef struct in_addr_ulong {
    u_long S_addr;
} IN_ADDR_ULONG, *PIN_ADDR_ULONG, *LPIN_ADDR_ULONG;

typedef struct in_addr_ushort {
    u_short s_w1;
    u_short s_w2;
} IN_ADDR_USHORT, *PIN_ADDR_USHORT, *LPIN_ADDR_USHORT;

#define s_addr  S_addr //can be used for most tcp & ip code
#define s_host  s_b2 // host on imp
#define s_net   s_b1 // network 
#define s_imp   s_w2 // imp 
#define s_impno s_b4 // imp # 
#define s_lh    s_b3 // logical host 

//@分组}

//@分组{ mstcpip.h

typedef struct _ASSOCIATE_NAMERES_CONTEXT_INPUT {
  TRANSPORT_SETTING_ID TransportSettingId;
  UINT64               Handle;
} ASSOCIATE_NAMERES_CONTEXT_INPUT, *PASSOCIATE_NAMERES_CONTEXT_INPUT;

typedef enum _CONTROL_CHANNEL_TRIGGER_STATUS {
  CONTROL_CHANNEL_TRIGGER_STATUS_INVALID = 0,
  CONTROL_CHANNEL_TRIGGER_STATUS_SOFTWARE_SLOT_ALLOCATED = 1,
  CONTROL_CHANNEL_TRIGGER_STATUS_HARDWARE_SLOT_ALLOCATED = 2,
  CONTROL_CHANNEL_TRIGGER_STATUS_POLICY_ERROR = 3,
  CONTROL_CHANNEL_TRIGGER_STATUS_SYSTEM_ERROR = 4,
  CONTROL_CHANNEL_TRIGGER_STATUS_TRANSPORT_DISCONNECTED = 5,
  CONTROL_CHANNEL_TRIGGER_STATUS_SERVICE_UNAVAILABLE = 6
} CONTROL_CHANNEL_TRIGGER_STATUS, *PCONTROL_CHANNEL_TRIGGER_STATUS;

typedef struct _INET_PORT_RANGE {
  USHORT StartPort;
  USHORT NumberOfPorts;
} INET_PORT_RANGE, *PINET_PORT_RANGE, INET_PORT_RESERVATION, *PINET_PORT_RESERVATION;

typedef struct _INET_PORT_RESERVATION_INSTANCE {
  INET_PORT_RESERVATION       Reservation;
  INET_PORT_RESERVATION_TOKEN Token;
} INET_PORT_RESERVATION_INSTANCE, *PINET_PORT_RESERVATION_INSTANCE;

typedef struct _INET_PORT_RESERVATION_TOKEN {
  ULONG64 Token;
} INET_PORT_RESERVATION_TOKEN, *PINET_PORT_RESERVATION_TOKEN;

typedef struct _REAL_TIME_NOTIFICATION_SETTING_INPUT {
  TRANSPORT_SETTING_ID TransportSettingId;
  GUID                 BrokerEventGuid;
} REAL_TIME_NOTIFICATION_SETTING_INPUT, *PREAL_TIME_NOTIFICATION_SETTING_INPUT;

typedef struct _REAL_TIME_NOTIFICATION_SETTING_OUTPUT {
  CONTROL_CHANNEL_TRIGGER_STATUS ChannelStatus;
} REAL_TIME_NOTIFICATION_SETTING_OUTPUT, *PREAL_TIME_NOTIFICATION_SETTING_OUTPUT;

typedef struct _SOCKET_PEER_TARGET_NAME {
  SOCKET_SECURITY_PROTOCOL SecurityProtocol;
  SOCKADDR_STORAGE         PeerAddress;
  ULONG                    PeerTargetNameStringLen;
  wchar_t                  AllStrings[0];
} SOCKET_PEER_TARGET_NAME;

typedef enum _SOCKET_SECURITY_PROTOCOL {
  SOCKET_SECURITY_PROTOCOL_DEFAULT,
  SOCKET_SECURITY_PROTOCOL_IPSEC,
  SOCKET_SECURITY_PROTOCOL_IPSEC2,
  SOCKET_SECURITY_PROTOCOL_INVALID
} SOCKET_SECURITY_PROTOCOL;

typedef struct _SOCKET_SECURITY_QUERY_INFO {
  SOCKET_SECURITY_PROTOCOL SecurityProtocol;
  ULONG                    Flags;
  UINT64                   PeerApplicationAccessTokenHandle;
  UINT64                   PeerMachineAccessTokenHandle;
} SOCKET_SECURITY_QUERY_INFO;

typedef struct _SOCKET_SECURITY_QUERY_TEMPLATE {
  SOCKET_SECURITY_PROTOCOL SecurityProtocol;
  SOCKADDR_STORAGE         PeerAddress;
  ULONG                    PeerTokenAccessMask;
} SOCKET_SECURITY_QUERY_TEMPLATE;

typedef struct _SOCKET_SECURITY_SETTINGS {
  SOCKET_SECURITY_PROTOCOL SecurityProtocol;
  ULONG                    SecurityFlags;
} SOCKET_SECURITY_SETTINGS;

typedef struct _SOCKET_SECURITY_SETTINGS_IPSEC {
  SOCKET_SECURITY_PROTOCOL SecurityProtocol;
  ULONG                    SecurityFlags;
  ULONG                    IpsecFlags;
  GUID                     AuthipMMPolicyKey;
  GUID                     AuthipQMPolicyKey;
  GUID                     Reserved;
  UINT64                   Reserved2;
  ULONG                    UserNameStringLen;
  ULONG                    DomainNameStringLen;
  ULONG                    PasswordStringLen;
  wchar_t                  AllStrings[0];
} SOCKET_SECURITY_SETTINGS_IPSEC;

typedef enum _SOCKET_USAGE_TYPE {
  SYSTEM_CRITICAL_SOCKET = 1
} SOCKET_USAGE_TYPE;

typedef struct _TCP_INFO_v0 {
  TCPSTATE State;
  ULONG    Mss;
  ULONG64  ConnectionTimeMs;
  BOOLEAN  TimestampsEnabled;
  ULONG    RttUs;
  ULONG    MinRttUs;
  ULONG    BytesInFlight;
  ULONG    Cwnd;
  ULONG    SndWnd;
  ULONG    RcvWnd;
  ULONG    RcvBuf;
  ULONG64  BytesOut;
  ULONG64  BytesIn;
  ULONG    BytesReordered;
  ULONG    BytesRetrans;
  ULONG    FastRetrans;
  ULONG    DupAcksIn;
  ULONG    TimeoutEpisodes;
  UCHAR    SynRetrans;
} TCP_INFO_v0, *PTCP_INFO_v0;

typedef struct _TCP_INFO_v1 {
  TCPSTATE State;
  ULONG    Mss;
  ULONG64  ConnectionTimeMs;
  BOOLEAN  TimestampsEnabled;
  ULONG    RttUs;
  ULONG    MinRttUs;
  ULONG    BytesInFlight;
  ULONG    Cwnd;
  ULONG    SndWnd;
  ULONG    RcvWnd;
  ULONG    RcvBuf;
  ULONG64  BytesOut;
  ULONG64  BytesIn;
  ULONG    BytesReordered;
  ULONG    BytesRetrans;
  ULONG    FastRetrans;
  ULONG    DupAcksIn;
  ULONG    TimeoutEpisodes;
  UCHAR    SynRetrans;
  ULONG    SndLimTransRwin;
  ULONG    SndLimTimeRwin;
  ULONG64  SndLimBytesRwin;
  ULONG    SndLimTransCwnd;
  ULONG    SndLimTimeCwnd;
  ULONG64  SndLimBytesCwnd;
  ULONG    SndLimTransSnd;
  ULONG    SndLimTimeSnd;
  ULONG64  SndLimBytesSnd;
} TCP_INFO_v1, *PTCP_INFO_v1;

typedef struct _TCP_INITIAL_RTO_PARAMETERS {
  USHORT Rtt;
  UCHAR  MaxSynRetransmissions;
} TCP_INITIAL_RTO_PARAMETERS, *PTCP_INITIAL_RTO_PARAMETERS;

typedef enum _TCPSTATE {
  TCPSTATE_CLOSED,
  TCPSTATE_LISTEN,
  TCPSTATE_SYN_SENT,
  TCPSTATE_SYN_RCVD,
  TCPSTATE_ESTABLISHED,
  TCPSTATE_FIN_WAIT_1,
  TCPSTATE_FIN_WAIT_2,
  TCPSTATE_CLOSE_WAIT,
  TCPSTATE_CLOSING,
  TCPSTATE_LAST_ACK,
  TCPSTATE_TIME_WAIT,
  TCPSTATE_MAX
} TCPSTATE;

typedef struct _TIMESTAMPING_CONFIG {
  ULONG  Flags;
  USHORT TxTimestampsBuffered;
} TIMESTAMPING_CONFIG, *PTIMESTAMPING_CONFIG;

typedef struct TRANSPORT_SETTING_ID {
  GUID Guid;
} TRANSPORT_SETTING_ID, *PTRANSPORT_SETTING_ID;

//@分组}

//@分组{ mswsock.h


//@分组}

//@分组{ mswsockdef.h


//@分组}

//@分组{ nsemail.h


//@分组}

//@分组{ nspapi.h


//@分组}

//@分组{ socketapi.h


//@分组}

//@分组{ sporder.h


//@分组}

//@分组{ transportsettingcommon.h


//@分组}

//@分组{ winsock2.h

int __WSAFDIsSet(
  SOCKET fd,
  fd_set *unnamedParam2
);

SOCKET WSAAPI accept(
  SOCKET   s,
  sockaddr *addr,
  int      *addrlen
);

typedef struct _AFPROTOCOLS {
  INT iAddressFamily;
  INT iProtocol;
} AFPROTOCOLS, *PAFPROTOCOLS, *LPAFPROTOCOLS;

int WSAAPI bind(
  SOCKET         s,
  const sockaddr *name,
  int            namelen
);

typedef struct _BLOB {
  ULONG cbSize;
  BYTE  *pBlobData;
} BLOB, *LPBLOB;

int WSAAPI closesocket(
  SOCKET s
);

int WSAAPI connect(
  SOCKET         s,
  const sockaddr *name,
  int            namelen
);

typedef struct fd_set {
  u_int  fd_count;
  SOCKET fd_array[FD_SETSIZE];
} fd_set, FD_SET, *PFD_SET, *LPFD_SET;

hostent *WSAAPI gethostbyaddr(
  const char *addr,
  int        len,
  int        type
);

hostent *WSAAPI gethostbyname(
  const char *name
);

int WSAAPI gethostname(
   char *name,
   int  namelen
);

int WSAAPI GetHostNameW(
   PWSTR name,
   int   namelen
);

int WSAAPI getpeername(
       SOCKET   s,
       sockaddr *name,
  int      *namelen
);

protoent *WSAAPI getprotobyname(
  const char *name
);

protoent *WSAAPI getprotobynumber(
  int number
);

servent *WSAAPI getservbyname(
  const char *name,
  const char *proto
);

servent *WSAAPI getservbyport(
  int        port,
  const char *proto
);

int WSAAPI getsockname(
       SOCKET   s,
       sockaddr *name,
  int      *namelen
);

int WSAAPI getsockopt(
       SOCKET s,
       int    level,
       int    optname,
       char   *optval,
  int    *optlen
);

typedef struct hostent {
  char  *h_name;
  char  **h_aliases;
  short h_addrtype;
  short h_length;
  char  **h_addr_list;
} HOSTENT, *PHOSTENT, *LPHOSTENT;

unsigned __int32 htonf(
  float Value
);

u_long WSAAPI htonl(
  u_long hostlong
);

unsigned __int64 htonll(
  unsigned __int64 Value
);

u_short WSAAPI htons(
  u_short hostshort
);

unsigned long WSAAPI inet_addr(
  const char *cp
);

char *WSAAPI inet_ntoa(
  in_addr in
);

int WSAAPI ioctlsocket(
       SOCKET s,
       long   cmd,
  u_long *argp
);

typedef struct linger {
  u_short l_onoff;
  u_short l_linger;
} LINGER, *PLINGER, *LPLINGER;

int WSAAPI listen(
  SOCKET s,
  int    backlog
);

double ntohd(
  unsigned __int64 Value
);

float ntohf(
  unsigned __int32 Value
);

u_long WSAAPI ntohl(
  u_long netlong
);

unsigned __int64 ntohll(
  unsigned __int64 Value
);

u_short WSAAPI ntohs(
  u_short netshort
);

DWORD WSAAPI ProcessSocketNotifications(
  HANDLE                   completionPort,
  UINT32                   registrationCount,
  SOCK_NOTIFY_REGISTRATION *registrationInfos,
  UINT32                   timeoutMs,
  ULONG                    completionCount,
  OVERLAPPED_ENTRY         *completionPortEntries,
  UINT32                   *receivedEntryCount
);

typedef struct protoent {
  char  *p_name;
  char  **p_aliases;
  short p_proto;
} PROTOENT, *PPROTOENT, *LPPROTOENT;

int WSAAPI recv(
   SOCKET s,
   char   *buf,
   int    len,
   int    flags
);

int WSAAPI recvfrom(
                 SOCKET   s,
                 char     *buf,
                 int      len,
                 int      flags,
                 sockaddr *from,
  int      *fromlen
);

int WSAAPI select(
       int           nfds,
  fd_set        *readfds,
  fd_set        *writefds,
  fd_set        *exceptfds,
       const timeval *timeout
);

int WSAAPI send(
  SOCKET     s,
  const char *buf,
  int        len,
  int        flags
);

int WSAAPI sendto(
  SOCKET         s,
  const char     *buf,
  int            len,
  int            flags,
  const sockaddr *to,
  int            tolen
);

struct  servent {
        char    s_name;           // official service name 
        char    **s_aliases;  // alias list 
#ifdef _WIN64
        char    s_proto;          // protocol to use 
        short   s_port;                 // port # 
#else
        short   s_port;                 // port # 
        char    s_proto;          // protocol to use 
#endif
};

int WSAAPI setsockopt(
  SOCKET     s,
  int        level,
  int        optname,
  const char *optval,
  int        optlen
);

int WSAAPI shutdown(
  SOCKET s,
  int    how
);

typedef struct SOCK_NOTIFY_REGISTRATION {
  SOCKET socket;
  PVOID  completionKey;
  UINT16 eventFilter;
  UINT8  operation;
  UINT8  triggerFlags;
  DWORD  registrationResult;
} SOCK_NOTIFY_REGISTRATION;

SOCKET WSAAPI socket(
  int af,
  int type,
  int protocol
);

UINT32 SocketNotificationRetrieveEvents(
  OVERLAPPED_ENTRY *notification
);

typedef struct timeval {
  long tv_sec;
  long tv_usec;
} TIMEVAL, *PTIMEVAL, *LPTIMEVAL;

SOCKET WSAAPI WSAAccept(
       SOCKET          s,
      sockaddr        *addr,
  LPINT           addrlen,
       LPCONDITIONPROC lpfnCondition,
       DWORD_PTR       dwCallbackData
);

INT WSAAPI WSAAddressToStringA(
            LPSOCKADDR          lpsaAddress,
            DWORD               dwAddressLength,
  LPWSAPROTOCOL_INFOA lpProtocolInfo,
  LPSTR               lpszAddressString,
  LPDWORD             lpdwAddressStringLength
);

INT WSAAPI WSAAddressToStringW(
            LPSOCKADDR          lpsaAddress,
            DWORD               dwAddressLength,
  LPWSAPROTOCOL_INFOW lpProtocolInfo,
  LPWSTR              lpszAddressString,
  LPDWORD             lpdwAddressStringLength
);

HANDLE WSAAPI WSAAsyncGetHostByAddr(
  HWND       hWnd,
  u_int      wMsg,
  const char *addr,
  int        len,
  int        type,
  char       *buf,
  int        buflen
);

HANDLE WSAAPI WSAAsyncGetHostByName(
  HWND       hWnd,
  u_int      wMsg,
  const char *name,
  char       *buf,
  int        buflen
);

HANDLE WSAAPI WSAAsyncGetProtoByName(
   HWND       hWnd,
   u_int      wMsg,
   const char *name,
  char       *buf,
  int        buflen
);

HANDLE WSAAPI WSAAsyncGetProtoByNumber(
   HWND  hWnd,
   u_int wMsg,
   int   number,
  char  *buf,
   int   buflen
);

HANDLE WSAAPI WSAAsyncGetServByName(
   HWND       hWnd,
   u_int      wMsg,
   const char *name,
   const char *proto,
  char       *buf,
   int        buflen
);

HANDLE WSAAPI WSAAsyncGetServByPort(
   HWND       hWnd,
   u_int      wMsg,
   int        port,
   const char *proto,
  char       *buf,
   int        buflen
);

int WSAAPI WSAAsyncSelect(
  SOCKET s,
  HWND   hWnd,
  u_int  wMsg,
  long   lEvent
);

int WSAAPI WSACancelAsyncRequest(
  HANDLE hAsyncTaskHandle
);

int WSAAPI WSACancelBlockingCall();

int WSAAPI WSACleanup();

BOOL WSAAPI WSACloseEvent(
  WSAEVENT hEvent
);

typedef struct _WSACOMPLETION_WINDOWMESSAGE {
  WSACOMPLETIONTYPE Type;
  HWND   hWnd;
      UINT   uMsg;
      WPARAM context;
} WSACOMPLETION_WINDOWMESSAGE, *PWSACOMPLETION_WINDOWMESSAGE, *LPWSACOMPLETION_WINDOWMESSAGE;

typedef struct _WSACOMPLETION_EVENT {
  WSACOMPLETIONTYPE Type;
  LPWSAOVERLAPPED lpOverlapped;
} WSACOMPLETION_EVENT, *PWSACOMPLETION_EVENT, *LPWSACOMPLETION_EVENT;

typedef struct _WSACOMPLETION_APC {
  WSACOMPLETIONTYPE Type;
  LPWSAOVERLAPPED                    lpOverlapped;
  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpfnCompletionProc;
} WSACOMPLETION_APC, *PWSACOMPLETION_APC, *LPWSACOMPLETION_APC;

typedef struct _WSACOMPLETION_PARAMETERS {
  WSACOMPLETIONTYPE Type;
  LPWSAOVERLAPPED lpOverlapped;
      HANDLE          hPort;
      ULONG_PTR       Key;
} WSACOMPLETION_PARAMETERS, *PWSACOMPLETION_PARAMETERS, *LPWSACOMPLETION_PARAMETERS;

int WSAAPI WSAConnect(
  SOCKET         s,
  const sockaddr *name,
  int            namelen,
  LPWSABUF       lpCallerData,
  LPWSABUF       lpCalleeData,
  LPQOS          lpSQOS,
  LPQOS          lpGQOS
);

BOOL WSAConnectByList(
      SOCKET               s,
      PSOCKET_ADDRESS_LIST SocketAddress,
  LPDWORD              LocalAddressLength,
  LPSOCKADDR           LocalAddress,
  LPDWORD              RemoteAddressLength,
  LPSOCKADDR           RemoteAddress,
      const timeval        *timeout,
      LPWSAOVERLAPPED      Reserved
);

BOOL WSAConnectByNameA(
      SOCKET          s,
      LPCSTR          nodename,
      LPCSTR          servicename,
  LPDWORD         LocalAddressLength,
  LPSOCKADDR      LocalAddress,
  LPDWORD         RemoteAddressLength,
  LPSOCKADDR      RemoteAddress,
      const timeval   *timeout,
            LPWSAOVERLAPPED Reserved
);

BOOL WSAConnectByNameW(
      SOCKET          s,
      LPWSTR          nodename,
      LPWSTR          servicename,
  LPDWORD         LocalAddressLength,
  LPSOCKADDR      LocalAddress,
  LPDWORD         RemoteAddressLength,
  LPSOCKADDR      RemoteAddress,
      const timeval   *timeout,
            LPWSAOVERLAPPED Reserved
);



#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

WSAEVENT WSAAPI WSACreateEvent();

typedef struct WSAData {
        WORD                    wVersion;
        WORD                    wHighVersion;
#ifdef _WIN64
        unsigned short          iMaxSockets;
        unsigned short          iMaxUdpDg;
        char *                  lpVendorInfo;
        char                    szDescription[257];
        char                    szSystemStatus[129];
#else
        char                    szDescription[257];
        char                    szSystemStatus[129];
        unsigned short          iMaxSockets;
        unsigned short          iMaxUdpDg;
        char *                  lpVendorInfo;
#endif
} WSADATA, *LPWSADATA;

int WSAAPI WSADuplicateSocketA(
    SOCKET              s,
    DWORD               dwProcessId,
   LPWSAPROTOCOL_INFOA lpProtocolInfo
);

int WSAAPI WSADuplicateSocketW(
    SOCKET              s,
    DWORD               dwProcessId,
   LPWSAPROTOCOL_INFOW lpProtocolInfo
);

typedef enum _WSAEcomparator {
  COMP_EQUAL = 0,
  COMP_NOTLESS
} WSAECOMPARATOR, *PWSAECOMPARATOR, *LPWSAECOMPARATOR;

INT WSAAPI WSAEnumNameSpaceProvidersA(
   LPDWORD              lpdwBufferLength,
       LPWSANAMESPACE_INFOA lpnspBuffer
);

INT WSAAPI WSAEnumNameSpaceProvidersExA(
   LPDWORD                lpdwBufferLength,
       LPWSANAMESPACE_INFOEXA lpnspBuffer
);

INT WSAAPI WSAEnumNameSpaceProvidersExW(
   LPDWORD                lpdwBufferLength,
       LPWSANAMESPACE_INFOEXW lpnspBuffer
);

INT WSAAPI WSAEnumNameSpaceProvidersW(
   LPDWORD              lpdwBufferLength,
       LPWSANAMESPACE_INFOW lpnspBuffer
);

int WSAAPI WSAEnumNetworkEvents(
    SOCKET             s,
    WSAEVENT           hEventObject,
   LPWSANETWORKEVENTS lpNetworkEvents
);

int WSAAPI WSAEnumProtocolsA(
        LPINT               lpiProtocols,
       LPWSAPROTOCOL_INFOA lpProtocolBuffer,
   LPDWORD             lpdwBufferLength
);

int WSAAPI WSAEnumProtocolsW(
        LPINT               lpiProtocols,
       LPWSAPROTOCOL_INFOW lpProtocolBuffer,
   LPDWORD             lpdwBufferLength
);

int WSAAPI WSAEventSelect(
   SOCKET   s,
   WSAEVENT hEventObject,
   long     lNetworkEvents
);

int WSAAPI WSAGetLastError();

BOOL WSAAPI WSAGetOverlappedResult(
    SOCKET          s,
    LPWSAOVERLAPPED lpOverlapped,
   LPDWORD         lpcbTransfer,
    BOOL            fWait,
   LPDWORD         lpdwFlags
);

BOOL WSAAPI WSAGetQOSByName(
        SOCKET   s,
   LPWSABUF lpQOSName,
       LPQOS    lpQOS
);

INT WSAAPI WSAGetServiceClassInfoA(
        LPGUID                 lpProviderId,
        LPGUID                 lpServiceClassId,
   LPDWORD                lpdwBufSize,
       LPWSASERVICECLASSINFOA lpServiceClassInfo
);

INT WSAAPI WSAGetServiceClassInfoW(
        LPGUID                 lpProviderId,
        LPGUID                 lpServiceClassId,
   LPDWORD                lpdwBufSize,
       LPWSASERVICECLASSINFOW lpServiceClassInfo
);

INT WSAAPI WSAGetServiceClassNameByClassIdA(
        LPGUID  lpServiceClassId,
       LPSTR   lpszServiceClassName,
   LPDWORD lpdwBufferLength
);

INT WSAAPI WSAGetServiceClassNameByClassIdW(
        LPGUID  lpServiceClassId,
       LPWSTR  lpszServiceClassName,
   LPDWORD lpdwBufferLength
);

int WSAAPI WSAHtonl(
    SOCKET s,
    u_long hostlong,
   u_long *lpnetlong
);

int WSAAPI WSAHtons(
    SOCKET  s,
    u_short hostshort,
   u_short *lpnetshort
);

INT WSAAPI WSAInstallServiceClassA(
   LPWSASERVICECLASSINFOA lpServiceClassInfo
);

INT WSAAPI WSAInstallServiceClassW(
   LPWSASERVICECLASSINFOW lpServiceClassInfo
);

int WSAAPI WSAIoctl(
    SOCKET                             s,
    DWORD                              dwIoControlCode,
    LPVOID                             lpvInBuffer,
    DWORD                              cbInBuffer,
   LPVOID                             lpvOutBuffer,
    DWORD                              cbOutBuffer,
   LPDWORD                            lpcbBytesReturned,
    LPWSAOVERLAPPED                    lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

BOOL WSAAPI WSAIsBlocking();

SOCKET WSAAPI WSAJoinLeaf(
    SOCKET         s,
    const sockaddr *name,
    int            namelen,
    LPWSABUF       lpCallerData,
   LPWSABUF       lpCalleeData,
    LPQOS          lpSQOS,
    LPQOS          lpGQOS,
    DWORD          dwFlags
);

INT WSAAPI WSALookupServiceBeginA(
    LPWSAQUERYSETA lpqsRestrictions,
    DWORD          dwControlFlags,
   LPHANDLE       lphLookup
);

INT WSAAPI WSALookupServiceBeginW(
    LPWSAQUERYSETW lpqsRestrictions,
    DWORD          dwControlFlags,
   LPHANDLE       lphLookup
);

INT WSAAPI WSALookupServiceEnd(
   HANDLE hLookup
);

INT WSAAPI WSALookupServiceNextA(
        HANDLE         hLookup,
        DWORD          dwControlFlags,
   LPDWORD        lpdwBufferLength,
       LPWSAQUERYSETA lpqsResults
);

INT WSAAPI WSALookupServiceNextW(
        HANDLE         hLookup,
        DWORD          dwControlFlags,
   LPDWORD        lpdwBufferLength,
       LPWSAQUERYSETW lpqsResults
);

typedef struct _WSANAMESPACE_INFOA {
  GUID  NSProviderId;
  DWORD dwNameSpace;
  BOOL  fActive;
  DWORD dwVersion;
  LPSTR lpszIdentifier;
} WSANAMESPACE_INFOA, *PWSANAMESPACE_INFOA, *LPWSANAMESPACE_INFOA;

typedef struct _WSANAMESPACE_INFOEXA {
  GUID  NSProviderId;
  DWORD dwNameSpace;
  BOOL  fActive;
  DWORD dwVersion;
  LPSTR lpszIdentifier;
  BLOB  ProviderSpecific;
} WSANAMESPACE_INFOEXA, *PWSANAMESPACE_INFOEXA, *LPWSANAMESPACE_INFOEXA;

typedef struct _WSANAMESPACE_INFOEXW {
  GUID   NSProviderId;
  DWORD  dwNameSpace;
  BOOL   fActive;
  DWORD  dwVersion;
  LPWSTR lpszIdentifier;
  BLOB   ProviderSpecific;
} WSANAMESPACE_INFOEXW, *PWSANAMESPACE_INFOEXW, *LPWSANAMESPACE_INFOEXW;

typedef struct _WSANAMESPACE_INFOW {
  GUID   NSProviderId;
  DWORD  dwNameSpace;
  BOOL   fActive;
  DWORD  dwVersion;
  LPWSTR lpszIdentifier;
} WSANAMESPACE_INFOW, *PWSANAMESPACE_INFOW, *LPWSANAMESPACE_INFOW;

typedef struct _WSANETWORKEVENTS {
  long lNetworkEvents;
  int  iErrorCode[FD_MAX_EVENTS];
} WSANETWORKEVENTS, *LPWSANETWORKEVENTS;

typedef struct _WSANSClassInfoA {
  LPSTR  lpszName;
  DWORD  dwNameSpace;
  DWORD  dwValueType;
  DWORD  dwValueSize;
  LPVOID lpValue;
} WSANSCLASSINFOA, *PWSANSCLASSINFOA, *LPWSANSCLASSINFOA;

typedef struct _WSANSClassInfoW {
  LPWSTR lpszName;
  DWORD  dwNameSpace;
  DWORD  dwValueType;
  DWORD  dwValueSize;
  LPVOID lpValue;
} WSANSCLASSINFOW, *PWSANSCLASSINFOW, *LPWSANSCLASSINFOW;

INT WSAAPI WSANSPIoctl(
        HANDLE          hLookup,
        DWORD           dwControlCode,
        LPVOID          lpvInBuffer,
   DWORD           cbInBuffer,
       LPVOID          lpvOutBuffer,
        DWORD           cbOutBuffer,
       LPDWORD         lpcbBytesReturned,
        LPWSACOMPLETION lpCompletion
);

int WSAAPI WSANtohl(
    SOCKET s,
    u_long netlong,
   u_long *lphostlong
);

int WSAAPI WSANtohs(
    SOCKET  s,
    u_short netshort,
   u_short *lphostshort
);

typedef struct _WSAOVERLAPPED {
  DWORD    Internal;
  DWORD    InternalHigh;
  DWORD    Offset;
  DWORD    OffsetHigh;
  WSAEVENT hEvent;
} WSAOVERLAPPED, *LPWSAOVERLAPPED;

int WSAAPI WSAPoll(
   LPWSAPOLLFD fdArray,
        ULONG       fds,
        INT         timeout
);

typedef struct pollfd {
  SOCKET fd;
  SHORT  events;
  SHORT  revents;
} WSAPOLLFD, *PWSAPOLLFD, *LPWSAPOLLFD;

typedef struct _WSAPROTOCOL_INFOA {
  DWORD            dwServiceFlags1;
  DWORD            dwServiceFlags2;
  DWORD            dwServiceFlags3;
  DWORD            dwServiceFlags4;
  DWORD            dwProviderFlags;
  GUID             ProviderId;
  DWORD            dwCatalogEntryId;
  WSAPROTOCOLCHAIN ProtocolChain;
  int              iVersion;
  int              iAddressFamily;
  int              iMaxSockAddr;
  int              iMinSockAddr;
  int              iSocketType;
  int              iProtocol;
  int              iProtocolMaxOffset;
  int              iNetworkByteOrder;
  int              iSecurityScheme;
  DWORD            dwMessageSize;
  DWORD            dwProviderReserved;
  CHAR             szProtocol[256];
} WSAPROTOCOL_INFOA, *LPWSAPROTOCOL_INFOA;

typedef struct _WSAPROTOCOL_INFOW {
  DWORD            dwServiceFlags1;
  DWORD            dwServiceFlags2;
  DWORD            dwServiceFlags3;
  DWORD            dwServiceFlags4;
  DWORD            dwProviderFlags;
  GUID             ProviderId;
  DWORD            dwCatalogEntryId;
  WSAPROTOCOLCHAIN ProtocolChain;
  int              iVersion;
  int              iAddressFamily;
  int              iMaxSockAddr;
  int              iMinSockAddr;
  int              iSocketType;
  int              iProtocol;
  int              iProtocolMaxOffset;
  int              iNetworkByteOrder;
  int              iSecurityScheme;
  DWORD            dwMessageSize;
  DWORD            dwProviderReserved;
  WCHAR            szProtocol[256];
} WSAPROTOCOL_INFOW, *LPWSAPROTOCOL_INFOW;

typedef struct _WSAPROTOCOLCHAIN {
  int   ChainLen;
  DWORD ChainEntries[MAX_PROTOCOL_CHAIN];
} WSAPROTOCOLCHAIN, *LPWSAPROTOCOLCHAIN;

INT WSAAPI WSAProviderConfigChange(
   LPHANDLE                           lpNotificationHandle,
        LPWSAOVERLAPPED                    lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

typedef struct _WSAQuerySet2A {
  DWORD         dwSize;
  LPSTR         lpszServiceInstanceName;
  LPWSAVERSION  lpVersion;
  LPSTR         lpszComment;
  DWORD         dwNameSpace;
  LPGUID        lpNSProviderId;
  LPSTR         lpszContext;
  DWORD         dwNumberOfProtocols;
  LPAFPROTOCOLS lpafpProtocols;
  LPSTR         lpszQueryString;
  DWORD         dwNumberOfCsAddrs;
  LPCSADDR_INFO lpcsaBuffer;
  DWORD         dwOutputFlags;
  LPBLOB        lpBlob;
} WSAQUERYSET2A, *PWSAQUERYSET2A, *LPWSAQUERYSET2A;

typedef struct _WSAQuerySet2W {
  DWORD         dwSize;
  LPWSTR        lpszServiceInstanceName;
  LPWSAVERSION  lpVersion;
  LPWSTR        lpszComment;
  DWORD         dwNameSpace;
  LPGUID        lpNSProviderId;
  LPWSTR        lpszContext;
  DWORD         dwNumberOfProtocols;
  LPAFPROTOCOLS lpafpProtocols;
  LPWSTR        lpszQueryString;
  DWORD         dwNumberOfCsAddrs;
  LPCSADDR_INFO lpcsaBuffer;
  DWORD         dwOutputFlags;
  LPBLOB        lpBlob;
} WSAQUERYSET2W, *PWSAQUERYSET2W, *LPWSAQUERYSET2W;

typedef struct _WSAQuerySetA {
  DWORD         dwSize;
  LPSTR         lpszServiceInstanceName;
  LPGUID        lpServiceClassId;
  LPWSAVERSION  lpVersion;
  LPSTR         lpszComment;
  DWORD         dwNameSpace;
  LPGUID        lpNSProviderId;
  LPSTR         lpszContext;
  DWORD         dwNumberOfProtocols;
  LPAFPROTOCOLS lpafpProtocols;
  LPSTR         lpszQueryString;
  DWORD         dwNumberOfCsAddrs;
  LPCSADDR_INFO lpcsaBuffer;
  DWORD         dwOutputFlags;
  LPBLOB        lpBlob;
} WSAQUERYSETA, *PWSAQUERYSETA, *LPWSAQUERYSETA;

typedef struct _WSAQuerySetW {
  DWORD         dwSize;
  LPWSTR        lpszServiceInstanceName;
  LPGUID        lpServiceClassId;
  LPWSAVERSION  lpVersion;
  LPWSTR        lpszComment;
  DWORD         dwNameSpace;
  LPGUID        lpNSProviderId;
  LPWSTR        lpszContext;
  DWORD         dwNumberOfProtocols;
  LPAFPROTOCOLS lpafpProtocols;
  LPWSTR        lpszQueryString;
  DWORD         dwNumberOfCsAddrs;
  LPCSADDR_INFO lpcsaBuffer;
  DWORD         dwOutputFlags;
  LPBLOB        lpBlob;
} WSAQUERYSETW, *PWSAQUERYSETW, *LPWSAQUERYSETW;

int WSAAPI WSARecv(
        SOCKET                             s,
   LPWSABUF                           lpBuffers,
        DWORD                              dwBufferCount,
       LPDWORD                            lpNumberOfBytesRecvd,
   LPDWORD                            lpFlags,
        LPWSAOVERLAPPED                    lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

int WSAAPI WSARecvDisconnect(
    SOCKET   s,
   LPWSABUF lpInboundDisconnectData
);

int WSAAPI WSARecvFrom(
        SOCKET                             s,
   LPWSABUF                           lpBuffers,
        DWORD                              dwBufferCount,
       LPDWORD                            lpNumberOfBytesRecvd,
   LPDWORD                            lpFlags,
       sockaddr                           *lpFrom,
   LPINT                              lpFromlen,
        LPWSAOVERLAPPED                    lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

INT WSAAPI WSARemoveServiceClass(
   LPGUID lpServiceClassId
);

BOOL WSAAPI WSAResetEvent(
   WSAEVENT hEvent
);

int WSAAPI WSASend(
    SOCKET                             s,
    LPWSABUF                           lpBuffers,
    DWORD                              dwBufferCount,
   LPDWORD                            lpNumberOfBytesSent,
    DWORD                              dwFlags,
    LPWSAOVERLAPPED                    lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

int WSAAPI WSASendDisconnect(
   SOCKET   s,
   LPWSABUF lpOutboundDisconnectData
);

int WSAAPI WSASendMsg(
    SOCKET                             Handle,
    LPWSAMSG                           lpMsg,
    DWORD                              dwFlags,
   LPDWORD                            lpNumberOfBytesSent,
    LPWSAOVERLAPPED                    lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

int WSAAPI WSASendTo(
    SOCKET                             s,
    LPWSABUF                           lpBuffers,
    DWORD                              dwBufferCount,
   LPDWORD                            lpNumberOfBytesSent,
    DWORD                              dwFlags,
    const sockaddr                     *lpTo,
    int                                iTolen,
    LPWSAOVERLAPPED                    lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

typedef struct _WSAServiceClassInfoA {
  LPGUID            lpServiceClassId;
  LPSTR             lpszServiceClassName;
  DWORD             dwCount;
  LPWSANSCLASSINFOA lpClassInfos;
} WSASERVICECLASSINFOA, *PWSASERVICECLASSINFOA, *LPWSASERVICECLASSINFOA;

typedef struct _WSAServiceClassInfoW {
  LPGUID            lpServiceClassId;
  LPWSTR            lpszServiceClassName;
  DWORD             dwCount;
  LPWSANSCLASSINFOW lpClassInfos;
} WSASERVICECLASSINFOW, *PWSASERVICECLASSINFOW, *LPWSASERVICECLASSINFOW;

FARPROC WSAAPI WSASetBlockingHook(
  FARPROC lpBlockFunc
);

BOOL WSAAPI WSASetEvent(
   WSAEVENT hEvent
);

void WSAAPI WSASetLastError(
   int iError
);

INT WSAAPI WSASetServiceA(
   LPWSAQUERYSETA   lpqsRegInfo,
   WSAESETSERVICEOP essoperation,
   DWORD            dwControlFlags
);

INT WSAAPI WSASetServiceW(
   LPWSAQUERYSETW   lpqsRegInfo,
   WSAESETSERVICEOP essoperation,
   DWORD            dwControlFlags
);

SOCKET WSAAPI WSASocketA(
   int                 af,
   int                 type,
   int                 protocol,
   LPWSAPROTOCOL_INFOA lpProtocolInfo,
   GROUP               g,
   DWORD               dwFlags
);

SOCKET WSAAPI WSASocketW(
   int                 af,
   int                 type,
   int                 protocol,
   LPWSAPROTOCOL_INFOW lpProtocolInfo,
   GROUP               g,
   DWORD               dwFlags
);

int WSAAPI WSAStartup(
    WORD      wVersionRequested,
   LPWSADATA lpWSAData
);

INT WSAAPI WSAStringToAddressA(
             LPSTR               AddressString,
             INT                 AddressFamily,
   LPWSAPROTOCOL_INFOA lpProtocolInfo,
            LPSOCKADDR          lpAddress,
        LPINT               lpAddressLength
);

INT WSAAPI WSAStringToAddressW(
             LPWSTR              AddressString,
             INT                 AddressFamily,
   LPWSAPROTOCOL_INFOW lpProtocolInfo,
            LPSOCKADDR          lpAddress,
        LPINT               lpAddressLength
);

int WSAAPI WSAUnhookBlockingHook();

typedef struct _WSAVersion {
  DWORD          dwVersion;
  WSAECOMPARATOR ecHow;
} WSAVERSION, *PWSAVERSION, *LPWSAVERSION;

DWORD WSAAPI WSAWaitForMultipleEvents(
   DWORD          cEvents,
   const WSAEVENT *lphEvents,
   BOOL           fWaitAll,
   DWORD          dwTimeout,
   BOOL           fAlertable
);



//@分组}

//@分组{ ws2atm.h


//@分组}

//@分组{ ws2def.h


//@分组}

//@分组{ ws2ipdef.h


//@分组}

//@分组{ ws2spi.h


//@分组}

//@分组{ ws2tcpip.h


//@分组}

//@分组{ wsipv6ok.h


//@分组}

//@分组{ wsnwlink.h


//@分组}

//@分组{ wsrm.h


//@分组}

//@分组{ wtypesbase.h


//@分组}



//@分组{ windows.h
typedef unsigned int UINT_PTR, *PUINT_PTR;
typedef UINT_PTR        SOCKET;
//@分组}

*/