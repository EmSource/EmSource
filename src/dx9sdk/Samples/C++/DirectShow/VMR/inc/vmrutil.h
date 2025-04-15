//------------------------------------------------------------------------------
// File: VMRUtil.h
//
// Desc: DirectShow sample code - header file for VMR sample applications
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#ifndef __INC_VMRUTIL_H__
#define __INC_VMRUTIL_H__

#pragma once

//----------------------------------------------------------------------------
//  VerifyVMR
// 
//  Verifies that VMR COM objects exist on the system and that the VMR
//  can be instantiated.
//
//  Returns: false if the VMR can't be created
//----------------------------------------------------------------------------

BOOL VerifyVMR(void)
{
    HRESULT hr;

    // Verify that the VMR exists on this system
    IBaseFilter* pBF = NULL;
    hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL,
                          CLSCTX_INPROC,
                          IID_IBaseFilter,
                          (LPVOID *)&pBF);
    if(SUCCEEDED(hr))
    {
        pBF->Release();
        return TRUE;
    }
    else
    {
        MessageBox(NULL, 
            TEXT("This application requires the Video Mixing Renderer, which is present\r\n")
            TEXT("only on Windows XP systems with hardware video acceleration enabled.\r\n\r\n")

            TEXT("The Video Mixing Renderer (VMR) is not enabled when viewing a \r\n")
            TEXT("remote Windows XP machine through a Remote Desktop session.\r\n")
            TEXT("You can run VMR-enabled applications only on your local machine.\r\n\r\n")

            TEXT("To verify that hardware acceleration is enabled on a Windows XP\r\n")
            TEXT("system, follow these steps:\r\n")
            TEXT("-----------------------------------------------------------------------\r\n")
            TEXT(" - Open 'Display Properties' in the Control Panel\r\n")
            TEXT(" - Click the 'Settings' tab\r\n")
            TEXT(" - Click on the 'Advanced' button at the bottom of the page\r\n")
            TEXT(" - Click on the 'Troubleshooting' tab in the window that appears\r\n")
            TEXT(" - Verify that the 'Hardware Acceleration' slider is at the rightmost position\r\n")

            TEXT("\r\nThis sample will now exit."),

            TEXT("Video Mixing Renderer capabilities are required"), MB_OK);

        return FALSE;
    }
}


#endif

