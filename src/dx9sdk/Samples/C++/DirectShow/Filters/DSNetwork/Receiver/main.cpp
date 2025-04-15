//------------------------------------------------------------------------------
// File: Main.cpp
//
// Desc: DirectShow sample code - implementation of DSNetwork sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "precomp.h"
#include "dsnetifc.h"
#include "proprecv.h"
#include "netrecv.h"
#include "dsrecv.h"


AMOVIESETUP_FILTER g_sudRecvFilter = 
{
    & CLSID_DSNetReceive,
    NET_RECEIVE_FILTER_NAME,
    MERIT_DO_NOT_USE,
    0,                         //  0 pins registered
    NULL
};


