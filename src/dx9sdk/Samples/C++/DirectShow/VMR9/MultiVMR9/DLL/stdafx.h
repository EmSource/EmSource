//------------------------------------------------------------------------------
// File: StdAfx.h
//
// Desc: DirectShow sample code - include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#pragma once

#ifndef STRICT
#define STRICT
#endif


#include "resource.h"

#include <streams.h>
#include <dshow.h>
#include <d3d9.h>
#include <vmr9.h>


#ifndef RELEASE
#define RELEASE(p) if( p ) { p->Release(); p=NULL; }
#endif

#ifndef CHECK_HR
#define CHECK_HR(hr, f) \
    if( FAILED(hr) ){ f; throw hr; }
#endif

// Global prototypes
void DbgMsg( char* szMessage, ... );

#pragma warning(disable:4786)
#pragma warning(disable:4245)