//------------------------------------------------------------------------------
// File: MonitorInfo.h
//
// Desc: DirectShow sample code - header file for VMR monitor info tool
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

//
// Function prototypes
//
void ReleaseVMR(void);

HRESULT InitializeVMR9(void);
HRESULT DisplayMonitorInfo(IVMRMonitorConfig9 *pMon);

//
// Macros
//
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }

//
// Resource constants
//
#define IDI_MONITORINFO                 100
