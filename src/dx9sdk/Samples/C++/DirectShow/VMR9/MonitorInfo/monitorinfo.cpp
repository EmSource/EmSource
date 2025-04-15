//------------------------------------------------------------------------------
// File: MonitorInfo.cpp
//
// Desc: DirectShow sample code - a simple monitor information tool which uses
//       the DirectX 9 Video Mixing Renderer's IVMRMonitorConfig9 interace.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include <dshow.h>
#include <tchar.h>
#include <atlbase.h>
#include <multimon.h>
#include <stdio.h>

// VMR9 Headers
#include <d3d9.h>
#include <vmr9.h>

#include "monitorinfo.h"
#include "vmrutil.h"

// Global DirectShow interfaces
IGraphBuilder     *g_pGB  = NULL;
IVMRMonitorConfig9 *g_pMon = NULL;


int PASCAL WinMain(HINSTANCE hInstC, HINSTANCE hInstP, LPSTR lpCmdLine, int nCmdShow)
{
    // Initialize COM
    if(FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
        return -1;

    // Verify that the VMR is present on this system
    if(!VerifyVMR9())
        return -1;

    if(SUCCEEDED(InitializeVMR9()))
    {
        // Display a message box with information about each attached monitor
        DisplayMonitorInfo(g_pMon);
    }
    
    // Clean up resources
    ReleaseVMR();
    CoUninitialize();
    return 0;
}


HRESULT InitializeVMR9(void)
{
    HRESULT hr;
    IBaseFilter* pVmr = NULL;
    IVMRMonitorConfig9* pMon = NULL;

    // Get the interface for DirectShow's GraphBuilder
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                         IID_IGraphBuilder, (void **)&g_pGB);
    if(FAILED(hr))
        return hr;

    // Create the VMR and add it to the filter graph.  
    // We will not add any other filters to this graph, but it is necessary
    // to create a filter graph to contain the VMR filter.
    hr = CoCreateInstance(CLSID_VideoMixingRenderer9, NULL,
                     CLSCTX_INPROC, IID_IBaseFilter, (void**)&pVmr);
    if (SUCCEEDED(hr)) 
    {
        hr = g_pGB->AddFilter(pVmr, L"Video Mixing Renderer 9");
        if (SUCCEEDED(hr)) 
        {
            // Get the monitor configuration/information interface
            hr = pVmr->QueryInterface(IID_IVMRMonitorConfig9, (void**)&pMon);
            if( SUCCEEDED(hr)) 
            {
                // Save the AddRef'ed interface
                g_pMon = pMon;
            }
        }

        // Release our interface to the VMR filter.  The filter graph
        // increments its reference count when it is added to a graph.
        pVmr->Release();
    }

    return hr;
}


void ReleaseVMR(void)
{
    // Destroy the filter graph
    SAFE_RELEASE(g_pMon);
    SAFE_RELEASE(g_pGB);
}


HRESULT DisplayMonitorInfo(IVMRMonitorConfig9 *pMon)
{
    USES_CONVERSION;
    const int MAXMON=4;          // Assume no more than four monitors
    const int SIZE_MONINFO=1024; // String size for each monitor's information

    HRESULT hr;
    VMR9MonitorInfo aMonInfo[MAXMON]={0};              // Array of info structures
    DWORD dwNumMonitors=0;                             // Number of attached monitors
    TCHAR szMonitorInfo[(MAXMON * SIZE_MONINFO) + 64]; // Main information string

    if (!pMon)
        return E_POINTER;

    // Initialize the information string
    szMonitorInfo[0] = TEXT('\0');

    // Read information about all attached monitors into an array
    hr = pMon->GetAvailableMonitors(aMonInfo, MAXMON, &dwNumMonitors);

    if (SUCCEEDED(hr))
    {
        // Begin the string with the number of available monitors
        wsprintf(szMonitorInfo, TEXT("This machine has %d attached monitor%s.\r\n\r\n\0"), 
                 dwNumMonitors, (dwNumMonitors > 1) ? TEXT("s") : TEXT(""));

        // Display monitor-specific information for each monitor
        for (DWORD i=0; i < dwNumMonitors; i++)
        {
            TCHAR szInfo[SIZE_MONINFO];
            VMR9MonitorInfo *pInfo = &(aMonInfo[i]);

            // Write monitor-specific info to a local string
            _sntprintf(szInfo, NUMELMS(szInfo)-1,
                     TEXT("Device: %s\r\n")
                     TEXT("Description:  %s\r\n")
                     TEXT("Display size: %d x %d\r\n")
                     TEXT("Flags:  0x%x %s\r\n\r\n")
                     TEXT("Monitor Index: %d\r\n")
                     TEXT("Vendor ID: %ld\r\n")
                     TEXT("Device ID: %ld\r\n")
                     TEXT("SubSys ID: %ld\r\n")
                     TEXT("Revision:  %ld\r\n")
                     TEXT("\r\n\r\n\0"),

                     W2T(pInfo->szDevice), 
                     W2T(pInfo->szDescription),
                     pInfo->rcMonitor.right - pInfo->rcMonitor.left, 
                     pInfo->rcMonitor.bottom - pInfo->rcMonitor.top,
                     pInfo->dwFlags,
                     (pInfo->dwFlags == MONITORINFOF_PRIMARY) ? 
                                        TEXT("[Primary Monitor]") : TEXT(""),
                     pInfo->uDevID, pInfo->dwVendorId,  
                     pInfo->dwDeviceId, 
                     pInfo->dwSubSysId, 
                     pInfo->dwRevision);

            szInfo[NUMELMS(szInfo)-1] = 0;  // Ensure NULL-termination

            // Add info about this monitor to the main information string.
            // If there are multiple monitors, this will add to the information
            // that was already added for the other monitor(s).
            _tcsncat(szMonitorInfo, szInfo, NUMELMS(szInfo));
        }

        // Display what we have learned about the attached monitors
        MessageBox(NULL, szMonitorInfo, TEXT("VMR9 Monitor Info"), MB_OK);
    }

    return hr;
}

