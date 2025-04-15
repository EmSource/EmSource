
/*++

    Copyright (c) 2000-2002  Microsoft Corporation.  All Rights Reserved.

    Module Name:

        nutil.h

    Abstract:


    Notes:

--*/


#ifndef __nutil_h
#define __nutil_h

BOOL
IsMulticastIP (
    IN DWORD dwIP   //  network order
    ) ;

BOOL
IsUnicastIP (
    IN DWORD dwIP   //  network order
    ) ;

//  ---------------------------------------------------------------------------
//  CInterface - enumerates the network interfaces on the host
//  ---------------------------------------------------------------------------

class CInterface
{
    enum {
        NUM_NIC_FIRST_GUESS = 3,    //  1 NIC, 1 loopback, 1 extra
        MAX_SUPPORTED_IFC   = 32
    } ;

    INTERFACE_INFO *    m_pNIC ;
    ULONG               m_cNIC ;
    HANDLE              m_hHeap ;

    public :

        CInterface (
            ) ;

        ~CInterface (
            ) ;

        BOOL
        IsInitialized (
            ) ;

        HRESULT
        Initialize (
            ) ;

        INTERFACE_INFO *
        operator [] (
            ULONG i
            ) ;
} ;

extern CInterface  g_NIC ;

#endif  //  __nutil_h