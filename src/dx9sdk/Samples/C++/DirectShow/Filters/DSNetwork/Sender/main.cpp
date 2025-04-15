//------------------------------------------------------------------------------
// File: Main.cpp
//
// Desc: DirectShow sample code - implementation of DSNetwork sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "precomp.h"
#include "dsnetifc.h"
#include "propsend.h"
#include "netsend.h"
#include "dssend.h"


AMOVIESETUP_FILTER g_sudSendFilter = 
{
    & CLSID_DSNetSend,
    NET_SEND_FILTER_NAME,
    MERIT_DO_NOT_USE,
    0,                          //  0 pins registered
    NULL
};


