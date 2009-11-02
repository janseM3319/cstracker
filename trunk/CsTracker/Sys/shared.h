/*
 * COPYRIGHT:   See COPYING in the top level directory
 * PROJECT:     ReactOS Ancillary Function Driver
 * FILE:        include/afd/shared.h
 * PURPOSE:     Shared definitions for AFD.SYS and MSAFD.DLL
 */
#ifndef __AFD_SHARED_H
#define __AFD_SHARED_H

#define AFD_MAX_EVENTS                  10
#define AFD_PACKET_COMMAND_LENGTH	15
#define AfdCommand "AfdOpenPacketXX"

//////////////////////////////////////////////////////////////////////////
//自定义结构
//////////////////////////////////////////////////////////////////////////
//IO Control Code
#define StartMonitor	CTL_CODE(FILE_DEVICE_UNKNOWN,0x811,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define StopMonitor		CTL_CODE(FILE_DEVICE_UNKNOWN,0x812,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define SetMonitor		CTL_CODE(FILE_DEVICE_UNKNOWN,0x813,METHOD_BUFFERED,FILE_ANY_ACCESS)




/* Extra definition of WSABUF for AFD so that I don't have to include any
 * userland winsock headers. */
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef int*	PINT;

typedef struct _AFD_WSABUF {
    UINT  len;
    PCHAR buf;
} AFD_WSABUF, *PAFD_WSABUF;

typedef struct _AFD_CREATE_PACKET {
    DWORD				EndpointFlags;
    DWORD				GroupID;
    DWORD				SizeOfTransportName;
    WCHAR				TransportName[1];
} AFD_CREATE_PACKET, *PAFD_CREATE_PACKET;

typedef struct _AFD_INFO {
    ULONG			        InformationClass;
    union {
        ULONG			        Ulong;
        LARGE_INTEGER	                LargeInteger;
    }					Information;
    ULONG				Padding;
} AFD_INFO, *PAFD_INFO;



typedef struct _AFD_LISTEN_DATA {
    BOOLEAN				UseSAN;
    ULONG				Backlog;
    BOOLEAN				UseDelayedAcceptance;
} AFD_LISTEN_DATA, *PAFD_LISTEN_DATA;



typedef struct _AFD_ACCEPT_DATA {
    ULONG				UseSAN;
    ULONG				SequenceNumber;
    ULONG				ListenHandle;
} AFD_ACCEPT_DATA, *PAFD_ACCEPT_DATA;



typedef struct _AFD_PENDING_ACCEPT_DATA {
    ULONG				SequenceNumber;
    ULONG				SizeOfData;
    ULONG				ReturnSize;
} AFD_PENDING_ACCEPT_DATA, *PAFD_PENDING_ACCEPT_DATA;

typedef struct _AFD_DEFER_ACCEPT_DATA {
    ULONG				SequenceNumber;
    BOOLEAN				RejectConnection;
} AFD_DEFER_ACCEPT_DATA, *PAFD_DEFER_ACCEPT_DATA;

typedef struct  _AFD_RECV_INFO {
    PAFD_WSABUF				BufferArray;
    ULONG				BufferCount;
    ULONG				AfdFlags;
    ULONG				TdiFlags;
} AFD_RECV_INFO , *PAFD_RECV_INFO ;

typedef struct _AFD_RECV_INFO_UDP {
    PAFD_WSABUF				BufferArray;
    ULONG				BufferCount;
    ULONG				AfdFlags;
    ULONG				TdiFlags;
    PVOID				Address;
    PINT				AddressLength;
} AFD_RECV_INFO_UDP, *PAFD_RECV_INFO_UDP;

typedef struct  _AFD_SEND_INFO {
    PAFD_WSABUF				BufferArray;
    ULONG				BufferCount;
    ULONG				AfdFlags;
    ULONG				TdiFlags;
} AFD_SEND_INFO , *PAFD_SEND_INFO ;

typedef struct _AFD_SEND_INFO_UDP {
    PAFD_WSABUF				BufferArray;
    ULONG				BufferCount;
    ULONG				AfdFlags;
    ULONG				Padding[9];
    ULONG				SizeOfRemoteAddress;
    PVOID				RemoteAddress;
} AFD_SEND_INFO_UDP, *PAFD_SEND_INFO_UDP;


typedef struct _AFD_EVENT_SELECT_INFO {
    HANDLE				EventObject;
    ULONG				Events;
} AFD_EVENT_SELECT_INFO, *PAFD_EVENT_SELECT_INFO;

typedef struct _AFD_ENUM_NETWORK_EVENTS_INFO {
    HANDLE Event;
    ULONG PollEvents;
    NTSTATUS EventStatus[AFD_MAX_EVENTS];
} AFD_ENUM_NETWORK_EVENTS_INFO, *PAFD_ENUM_NETWORK_EVENTS_INFO;

typedef struct _AFD_DISCONNECT_INFO {
    ULONG				DisconnectType;
    LARGE_INTEGER			Timeout;
} AFD_DISCONNECT_INFO, *PAFD_DISCONNECT_INFO;

/* AFD Packet Endpoint Flags */
#define AFD_ENDPOINT_CONNECTIONLESS	0x1
#define AFD_ENDPOINT_MESSAGE_ORIENTED	0x10
#define AFD_ENDPOINT_RAW		0x100
#define AFD_ENDPOINT_MULTIPOINT		0x1000
#define AFD_ENDPOINT_C_ROOT		0x10000
#define AFD_ENDPOINT_D_ROOT	        0x100000

/* AFD Info Flags */
#define AFD_INFO_BLOCKING_MODE		0x02L
#define AFD_INFO_SENDS_IN_PROGRESS  0x04L
#define AFD_INFO_RECEIVE_WINDOW_SIZE	0x06L
#define AFD_INFO_SEND_WINDOW_SIZE	0x07L
#define AFD_INFO_GROUP_ID_TYPE	        0x10L
#define AFD_INFO_RECEIVE_CONTENT_SIZE   0x11L

/* AFD Share Flags */
#define AFD_SHARE_UNIQUE		0x0L
#define AFD_SHARE_REUSE			0x1L
#define AFD_SHARE_WILDCARD		0x2L
#define AFD_SHARE_EXCLUSIVE		0x3L

/* AFD Disconnect Flags */
#define AFD_DISCONNECT_SEND		0x01L
#define AFD_DISCONNECT_RECV		0x02L
#define AFD_DISCONNECT_ABORT	0x04L

/* AFD Event Flags */
#define AFD_EVENT_RECEIVE		0x1L
#define AFD_EVENT_OOB_RECEIVE		0x2L
#define AFD_EVENT_SEND			0x4L
#define AFD_EVENT_DISCONNECT		0x8L
#define AFD_EVENT_ABORT			0x10L
#define AFD_EVENT_CLOSE			0x20L
#define AFD_EVENT_CONNECT		0x40L
#define AFD_EVENT_ACCEPT		0x80L
#define AFD_EVENT_CONNECT_FAIL		0x100L
#define AFD_EVENT_QOS			0x200L
#define AFD_EVENT_GROUP_QOS		0x400L

/* AFD SEND/RECV Flags */
#define AFD_SKIP_FIO			0x1L
#define AFD_OVERLAPPED			0x2L
#define AFD_IMMEDIATE                   0x4L

/* IOCTL Generation */
#define FSCTL_AFD_BASE                  FILE_DEVICE_NETWORK
#define _AFD_CONTROL_CODE(Operation,Method) \
  ((FSCTL_AFD_BASE)<<12 | (Operation<<2) | Method)

/* AFD Commands */
#define AFD_BIND			0
#define AFD_CONNECT			1
#define AFD_START_LISTEN		2
#define AFD_WAIT_FOR_LISTEN		3
#define AFD_ACCEPT			4
#define AFD_RECV			5
#define AFD_RECV_DATAGRAM		6
#define AFD_SEND			7
#define AFD_SEND_DATAGRAM		8
#define AFD_SELECT			9
#define AFD_DISCONNECT			10
#define AFD_GET_SOCK_NAME		11
#define AFD_GET_PEER_NAME               12
#define AFD_GET_TDI_HANDLES		13
#define AFD_SET_INFO			14
#define AFD_GET_CONTEXT			16
#define AFD_SET_CONTEXT			17
#define AFD_SET_CONNECT_DATA		18
#define AFD_SET_CONNECT_OPTIONS		19
#define AFD_SET_DISCONNECT_DATA		20
#define AFD_SET_DISCONNECT_OPTIONS	21
#define AFD_GET_CONNECT_DATA		22
#define AFD_GET_CONNECT_OPTIONS		23
#define AFD_GET_DISCONNECT_DATA		24
#define AFD_GET_DISCONNECT_OPTIONS	25
#define AFD_SET_CONNECT_DATA_SIZE       26
#define AFD_SET_CONNECT_OPTIONS_SIZE    27
#define AFD_SET_DISCONNECT_DATA_SIZE    28
#define AFD_SET_DISCONNECT_OPTIONS_SIZE 29
#define AFD_GET_INFO			30
#define AFD_EVENT_SELECT		33
#define AFD_ENUM_NETWORK_EVENTS         34
#define AFD_DEFER_ACCEPT		35
#define AFD_GET_PENDING_CONNECT_DATA	41

/* AFD IOCTLs */

#define IOCTL_AFD_BIND \
  _AFD_CONTROL_CODE(AFD_BIND, METHOD_NEITHER)
#define IOCTL_AFD_CONNECT \
  _AFD_CONTROL_CODE(AFD_CONNECT, METHOD_NEITHER)
#define IOCTL_AFD_START_LISTEN \
  _AFD_CONTROL_CODE(AFD_START_LISTEN, METHOD_NEITHER)
#define IOCTL_AFD_WAIT_FOR_LISTEN \
  _AFD_CONTROL_CODE(AFD_WAIT_FOR_LISTEN, METHOD_BUFFERED )
#define IOCTL_AFD_ACCEPT \
  _AFD_CONTROL_CODE(AFD_ACCEPT, METHOD_BUFFERED )
#define IOCTL_AFD_RECV \
  _AFD_CONTROL_CODE(AFD_RECV, METHOD_NEITHER)
#define IOCTL_AFD_RECV_DATAGRAM \
  _AFD_CONTROL_CODE(AFD_RECV_DATAGRAM, METHOD_NEITHER)
#define IOCTL_AFD_SEND \
  _AFD_CONTROL_CODE(AFD_SEND, METHOD_NEITHER)
#define IOCTL_AFD_SEND_DATAGRAM \
  _AFD_CONTROL_CODE(AFD_SEND_DATAGRAM, METHOD_NEITHER)
#define IOCTL_AFD_SELECT \
  _AFD_CONTROL_CODE(AFD_SELECT, METHOD_BUFFERED )
#define IOCTL_AFD_DISCONNECT \
  _AFD_CONTROL_CODE(AFD_DISCONNECT, METHOD_NEITHER)
#define IOCTL_AFD_GET_SOCK_NAME \
  _AFD_CONTROL_CODE(AFD_GET_SOCK_NAME, METHOD_NEITHER)
#define IOCTL_AFD_GET_PEER_NAME \
  _AFD_CONTROL_CODE(AFD_GET_PEER_NAME, METHOD_NEITHER)
#define IOCTL_AFD_GET_TDI_HANDLES \
  _AFD_CONTROL_CODE(AFD_GET_TDI_HANDLES, METHOD_NEITHER)
#define IOCTL_AFD_SET_INFO \
  _AFD_CONTROL_CODE(AFD_SET_INFO, METHOD_NEITHER)
#define IOCTL_AFD_GET_CONTEXT \
  _AFD_CONTROL_CODE(AFD_GET_CONTEXT, METHOD_NEITHER)
#define IOCTL_AFD_SET_CONTEXT \
  _AFD_CONTROL_CODE(AFD_SET_CONTEXT, METHOD_NEITHER)
#define IOCTL_AFD_SET_CONNECT_DATA \
  _AFD_CONTROL_CODE(AFD_SET_CONNECT_DATA, METHOD_NEITHER)
#define IOCTL_AFD_SET_CONNECT_OPTIONS \
  _AFD_CONTROL_CODE(AFD_SET_CONNECT_OPTIONS, METHOD_NEITHER)
#define IOCTL_AFD_SET_DISCONNECT_DATA \
  _AFD_CONTROL_CODE(AFD_SET_DISCONNECT_DATA, METHOD_NEITHER)
#define IOCTL_AFD_SET_DISCONNECT_OPTIONS \
  _AFD_CONTROL_CODE(AFD_SET_DISCONNECT_OPTIONS, METHOD_NEITHER)
#define IOCTL_AFD_GET_CONNECT_DATA \
  _AFD_CONTROL_CODE(AFD_GET_CONNECT_DATA, METHOD_NEITHER)
#define IOCTL_AFD_GET_CONNECT_OPTIONS \
  _AFD_CONTROL_CODE(AFD_GET_CONNECT_OPTIONS, METHOD_NEITHER)
#define IOCTL_AFD_GET_DISCONNECT_DATA \
  _AFD_CONTROL_CODE(AFD_GET_DISCONNECT_DATA, METHOD_NEITHER)
#define IOCTL_AFD_GET_DISCONNECT_OPTIONS \
  _AFD_CONTROL_CODE(AFD_GET_DISCONNECT_OPTIONS, METHOD_NEITHER)
#define IOCTL_AFD_SET_CONNECT_DATA_SIZE \
  _AFD_CONTROL_CODE(AFD_SET_CONNECT_DATA_SIZE, METHOD_NEITHER)
#define IOCTL_AFD_SET_CONNECT_OPTIONS_SIZE \
  _AFD_CONTROL_CODE(AFD_SET_CONNECT_OPTIONS_SIZE, METHOD_NEITHER)
#define IOCTL_AFD_SET_DISCONNECT_DATA_SIZE \
  _AFD_CONTROL_CODE(AFD_SET_DISCONNECT_DATA_SIZE, METHOD_NEITHER)
#define IOCTL_AFD_SET_DISCONNECT_OPTIONS_SIZE \
  _AFD_CONTROL_CODE(AFD_SET_DISCONNECT_OPTIONS_SIZE, METHOD_NEITHER)
#define IOCTL_AFD_GET_INFO \
  _AFD_CONTROL_CODE(AFD_GET_INFO, METHOD_NEITHER)
#define IOCTL_AFD_EVENT_SELECT \
  _AFD_CONTROL_CODE(AFD_EVENT_SELECT, METHOD_NEITHER)
#define IOCTL_AFD_DEFER_ACCEPT \
  _AFD_CONTROL_CODE(AFD_DEFER_ACCEPT, METHOD_NEITHER)
#define IOCTL_AFD_GET_PENDING_CONNECT_DATA \
  _AFD_CONTROL_CODE(AFD_GET_PENDING_CONNECT_DATA, METHOD_NEITHER)
#define IOCTL_AFD_ENUM_NETWORK_EVENTS \
  _AFD_CONTROL_CODE(AFD_ENUM_NETWORK_EVENTS, METHOD_NEITHER)

#endif