//------------------------------------------------------------------------------
// File: Main.cpp
//
// Desc: DirectShow sample code - implementation of DSNetwork sample filters
//       Contains filter registration information
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "precomp.h"
#include <initguid.h>

#include "dsnetifc.h"
#include "dsrecv.h"
#include "proprecv.h"
#include "dssend.h"
#include "propsend.h"


CFactoryTemplate g_Templates [] = 
{
    //  receiver filter
    {   NET_RECEIVE_FILTER_NAME,
        & CLSID_DSNetReceive,
        CNetworkReceiverFilter::CreateInstance,
        NULL,
        & g_sudRecvFilter
    },

    //  receiver property page
    {   NET_RECEIVE_PROP_PAGE_NAME,
        & CLSID_IPMulticastRecvProppage,
        CNetRecvProp::CreateInstance,
        NULL,
        NULL
    },

    //  sender filter
    {   NET_SEND_FILTER_NAME,
        & CLSID_DSNetSend,
        CNetworkSend::CreateInstance,
        NULL,
        & g_sudSendFilter
    },

    //  sender property page
    {   NET_SEND_PROP_PAGE_NAME,
        & CLSID_IPMulticastSendProppage,
        CNetSendProp::CreateInstance,
        NULL,
        NULL
    }
};

int g_cTemplates = sizeof (g_Templates) / sizeof (g_Templates[0]);


//  register and unregister entry points

//
// DllRegisterSever
//
STDAPI DllRegisterServer()
{
    return AMovieDllRegisterServer2 (TRUE);
}

//
// DllUnregsiterServer
//
STDAPI DllUnregisterServer()
{
    return AMovieDllRegisterServer2 (FALSE);
}

//
// DllEntryPoint
//
extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE, ULONG, LPVOID);

BOOL APIENTRY DllMain(HANDLE hModule, 
                      DWORD  dwReason, 
                      LPVOID lpReserved)
{
	return DllEntryPoint((HINSTANCE)(hModule), dwReason, lpReserved);
}

