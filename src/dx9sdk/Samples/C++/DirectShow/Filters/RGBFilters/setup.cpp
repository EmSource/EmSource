//------------------------------------------------------------------------------
// File: Setup.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "iRGBFilters.h"
#include "RGBFilters_i.c"

#include "AlphaRenderer\AlphaRenderer.h"
#include "RateSource\RateSource.h"
#include "AlphaSource\AlphaSource.h"
#include "Source8Bit\Source8Bit.h"
#include "Source555\Source555.h"
#include "Source565\Source565.h"
#include "Source24\Source24.h"
#include "Source32\Source32.h"
#include "TransNulls\TransNull8.h"
#include "TransNulls\TransNull555.h"
#include "TransNulls\TransNull565.h"
#include "TransNulls\TransNull24.h"
#include "TransNulls\TransNull32.h"
#include "TransNulls\TransNull32a.h"
#include "TransSmpte\TransSmpte.h"


// List of class IDs and creator functions for the class factory. This
// provides the link between the OLE entry point in the DLL and an object
// being created. The class factory will call the static CreateInstance.
// We provide a set of filters in this one DLL.

CFactoryTemplate g_Templates[] = 
{
    { L"AlphaRenderer", &CLSID_AlphaRenderer, CAlphaRenderer::CreateInstance,NULL, &sudAlphaRenderer },
    { L"RateSource",    &CLSID_RateSource,    CRateSource::CreateInstance,   NULL, &sudRateSource },
    { L"SourceARGB",    &CLSID_AlphaSource,   CAlphaSource::CreateInstance,  NULL, &sudAlphaSource },
    { L"Source8Bit",    &CLSID_Source8Bit,    CSource8Bit::CreateInstance,   NULL, &sudSource8Bit },
    { L"Source555Bit",  &CLSID_Source555Bit,  CSource555Bit::CreateInstance, NULL, &sudSource555Bit },
    { L"Source565Bit",  &CLSID_Source565Bit,  CSource565Bit::CreateInstance, NULL, &sudSource565Bit },
    { L"Source24Bit",   &CLSID_Source24Bit,   CSource24Bit::CreateInstance,  NULL, &sudSource24Bit },
    { L"Source32Bit",   &CLSID_Source32Bit,   CSource32Bit::CreateInstance,  NULL, &sudSource32Bit },
    { L"TransNull8",    &CLSID_TransNull8,    CTransNull8::CreateInstance,   NULL, &sudTransNull8 },
    { L"TransNull555",  &CLSID_TransNull555,  CTransNull555::CreateInstance, NULL, &sudTransNull555 },
    { L"TransNull8",    &CLSID_TransNull565,  CTransNull565::CreateInstance, NULL, &sudTransNull565 },
    { L"TransNull24",   &CLSID_TransNull24,   CTransNull24::CreateInstance,  NULL, &sudTransNull24 },
    { L"TransNull32",   &CLSID_TransNull32,   CTransNull32::CreateInstance,  NULL, &sudTransNull32 },
    { L"TransNull32a",  &CLSID_TransNull32a,  CTransNull32a::CreateInstance, NULL, &sudTransNull32a },
    { L"TransSmpte",    &CLSID_TransSmpte,    CTransSmpte::CreateInstance,   NULL, &sudTransSmpte }
};
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);


//
// DllRegisterServer
//
STDAPI DllRegisterServer()
{
    return AMovieDllRegisterServer2( TRUE );

} // DllRegisterServer


//
// DllUnregisterServer
//
STDAPI DllUnregisterServer()
{
    return AMovieDllRegisterServer2( FALSE );

} // DllUnregisterServer


