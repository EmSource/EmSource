// DxAppWiz.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "DxAppWiz.h"
#include "DXaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE DirectXDLL = { NULL, NULL };

HINSTANCE g_hInstance;

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    g_hInstance = hInstance;

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("DIRECTX.AWX Initializing!\n");
		
		// Extension DLL one-time initialization
		AfxInitExtensionModule(DirectXDLL, hInstance);

		// Insert this DLL into the resource chain
		new CDynLinkLibrary(DirectXDLL);

		// Register this custom AppWizard with MFCAPWZ.DLL
		SetCustomAppWizClass(&DirectXaw);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("DIRECTX.AWX Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(DirectXDLL);
	}
	return 1;   // ok
}
