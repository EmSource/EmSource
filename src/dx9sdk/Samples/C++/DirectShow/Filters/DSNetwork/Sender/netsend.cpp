//------------------------------------------------------------------------------
// File: NetSend.cpp
//
// Desc: DirectShow sample code - implementation of DSNetwork sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "precomp.h"
#include "dsnetifc.h"
#include "netsend.h"
#include "dssend.h"

//  ----------------------------------------------------------------------------

CNetSender::CNetSender (
    IN  DWORD       dwIOBufferLength,
    OUT HRESULT *   phr
    ) : m_hSocket               (INVALID_SOCKET),
        m_dwPTTransmitLength    (dwIOBufferLength)
{
    int i ;
    ASSERT(phr);

    //  we want winsock 2.0
    ZeroMemory (& m_wsaData, sizeof m_wsaData) ;

    i = WSAStartup (MAKEWORD(2, 0), & m_wsaData) ;
    if (i) {
        (* phr) = E_FAIL ;
        return ;
    }
}

CNetSender::~CNetSender (
    )
{
    //  should have left the multicast prior to being deleted
    ASSERT (m_hSocket == INVALID_SOCKET) ;

    WSACleanup () ;
}

HRESULT
CNetSender::Send (
    IN  BYTE *  pbBuffer,
    IN  DWORD   dwLength
    )
{
    HRESULT hr ;
    DWORD   dw ;
    DWORD   dwSnarf ;
    int     i ;

    //
    //  Note we do nothing to serialize on the receiver.  Depending on the
    //  distance, receiving host config and operations environment, receiver
    //  might get these out of order, duplicates, or miss them altogether.
    //  This is a quick/dirty sample, so we punt that schema.  Besides, we
    //  anticipate usage of this code to be such that the sender and receivers
    //  are on the same segment, so there's very little likelyhood the receiver
    //  will need to deal with this situation.
    //

    ASSERT (pbBuffer) ;

    if (m_hSocket != INVALID_SOCKET) {

        //  we have a valid socket to send on; loop through the buffer, snarf
        //  the max we can and send it off; we're doing synchronous sends

        while (dwLength > 0) {

            //  snarf what's left of the buffer, or the send quantum we're
            //  setup for
            dwSnarf = Min <DWORD> (m_dwPTTransmitLength, dwLength) ;

            //  then send
            i = sendto (
                    m_hSocket,
                    (const char *) pbBuffer,
                    dwSnarf,
                    0,
                    (LPSOCKADDR) & m_saddrDest,
                    sizeof m_saddrDest
                    ) ;

            if (i != (int) dwSnarf) {
                dw = GetLastError () ;
                return HRESULT_FROM_WIN32 (dw) ;
            }

            //  increment decrement
            pbBuffer += dwSnarf ;
            dwLength -= dwSnarf ;
        }

        hr = S_OK ;
    }
    else {
        hr = E_UNEXPECTED ;
    }

    return hr ;
}

HRESULT
CNetSender::JoinMulticast (
    IN  ULONG   ulIP,
    IN  USHORT  usPort,
    IN  ULONG   ulNIC,
    IN  ULONG   ulTTL
    )
{
    BOOL                t ;
    int                 i ;
    struct sockaddr_in  saddr ;
    DWORD               dw ;

    LeaveMulticast () ;
    ASSERT (m_hSocket == INVALID_SOCKET) ;

    m_hSocket = WSASocket (
        AF_INET,
        SOCK_DGRAM,
        0,
        NULL,
        0,
        WSA_FLAG_MULTIPOINT_C_LEAF | WSA_FLAG_MULTIPOINT_D_LEAF) ;

    if (m_hSocket == INVALID_SOCKET) {
        goto JoinFail ;
    }

    t = TRUE ;
    i = setsockopt (
                    m_hSocket,
                    SOL_SOCKET,
                    SO_REUSEADDR,
                    (char *) & t,
                    sizeof t
                    ) ;
    if (i == SOCKET_ERROR) {
        goto JoinFail ;
    }

    ZeroMemory (& saddr, sizeof saddr) ;
    saddr.sin_family            = AF_INET ;
    saddr.sin_port              = usPort ;      //  want data on this UDP port
    saddr.sin_addr.S_un.S_addr  = INADDR_ANY ;  //  don't care about NIC we're bound to

    i = bind (
            m_hSocket,
            (LPSOCKADDR) & saddr,
            sizeof saddr
            ) ;
    if (i == SOCKET_ERROR) {
        goto JoinFail ;
    }

    i = setsockopt (
            m_hSocket,
            IPPROTO_IP,
            IP_MULTICAST_TTL,
            (char *) & ulTTL,
            sizeof ulTTL
            ) ;
    if (i == SOCKET_ERROR) {
        goto JoinFail ;
    }

    i = setsockopt (
            m_hSocket,
            IPPROTO_IP,
            IP_MULTICAST_IF,
            (char *) & ulNIC,
            sizeof ulNIC
            ) ;
    if (i == SOCKET_ERROR) {
        goto JoinFail ;
    }

    ZeroMemory (& m_saddrDest, sizeof m_saddrDest) ;
    m_saddrDest.sin_family              = AF_INET ;
    m_saddrDest.sin_port                = usPort ;
    m_saddrDest.sin_addr.S_un.S_addr    = ulIP ;

    return TRUE ;

    JoinFail:

    dw = WSAGetLastError () ;
    if (dw == NOERROR) {
        //  make sure an error is propagated out
        dw = ERROR_GEN_FAILURE ;
    }

    LeaveMulticast () ;

    return HRESULT_FROM_WIN32 (dw) ;
}

HRESULT
CNetSender::LeaveMulticast (
    )
{
    if (m_hSocket != INVALID_SOCKET) {
        closesocket (m_hSocket) ;
        m_hSocket = INVALID_SOCKET ;
    }

    return S_OK ;
}

