//------------------------------------------------------------------------------
// File: MultiVMR9.cpp
//
// Desc: DirectShow sample code - Implementation of DLL Exports.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "resource.h"
#include "MultiVMR9.h"

#include <stdio.h>
#include <tchar.h>

#include "Wizard.h"
#include "RenderEngine.h"
#include "UILayer.h"
#include "MixerControl.h"

HINSTANCE g_hInst = NULL;

class CCFMultiVMR9Wizard;
class CCFMultiVMR9RenderEngine;
class CCFMultiVMR9UILayer;
class CCFMultiVMR9MixerControl;

static CCFMultiVMR9Wizard       g_WizardFactory;
static CCFMultiVMR9RenderEngine g_RenderEngineFactory;
static CCFMultiVMR9UILayer      g_UILayerFactory;
static CCFMultiVMR9MixerControl g_MixerControlFactory;

// the com module's lock count + object count
long g_CountWizard = 0; 
long g_CountRenderEngine = 0; 
long g_CountUILayer = 0; 
long g_CountMixerControl = 0; 

// forward declarations
void MultiVMRRegisterClass( const CLSID& clsid, TCHAR *achClassName, BOOL bRegister);
LONG recursiveDeleteKey(HKEY hKeyParent, TCHAR* achKeyChild);

// DLL Entry Point
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (DLL_PROCESS_ATTACH == dwReason )
    {
        g_hInst = hInstance;
    }
    return(TRUE);
}

//
// stub entry points
//

STDAPI
DllRegisterServer( void )
{
    // now go register components; they are in HKEY_CLASSES_ROOT\CLSID\{uuid}
    MultiVMRRegisterClass( CLSID_MultiVMR9Wizard,       TEXT("MultiVMR9 Wizard"), TRUE);
    MultiVMRRegisterClass( CLSID_MultiVMR9RenderEngine, TEXT("MultiVMR9 Render Engine"), TRUE);
    MultiVMRRegisterClass( CLSID_MultiVMR9UILayer,      TEXT("MultiVMR9 UI Layer"), TRUE);
    MultiVMRRegisterClass( CLSID_MultiVMR9MixerControl, TEXT("MultiVMR9 Mixer Control"), TRUE);

    return S_OK;
}

STDAPI
DllUnregisterServer( void )
{
    // now go register components; they are in HKEY_CLASSES_ROOT\CLSID\{uuid}
    MultiVMRRegisterClass( CLSID_MultiVMR9Wizard,       TEXT("MultiVMR9 Wizard"), FALSE);
    MultiVMRRegisterClass( CLSID_MultiVMR9RenderEngine, TEXT("MultiVMR9 Render Engine"), FALSE);
    MultiVMRRegisterClass( CLSID_MultiVMR9UILayer,      TEXT("MultiVMR9 UI Layer"), FALSE);
    MultiVMRRegisterClass( CLSID_MultiVMR9MixerControl, TEXT("MultiVMR9 Mixer Control"), FALSE);

    return S_OK;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID * ppv)
{
    if (CLSID_MultiVMR9Wizard == rclsid )
    {
        return g_WizardFactory.QueryInterface(riid, ppv);
    }
    else if( CLSID_MultiVMR9RenderEngine == rclsid )
    {
        return g_RenderEngineFactory.QueryInterface(riid, ppv);
    }
    else if( CLSID_MultiVMR9UILayer == rclsid )
    {
        return g_UILayerFactory.QueryInterface(riid, ppv);
    }
    else if( CLSID_MultiVMR9MixerControl == rclsid )
    {
        return g_MixerControlFactory.QueryInterface(riid, ppv);
    }
    else
    {
        *ppv = NULL;
        return CLASS_E_CLASSNOTAVAILABLE;
    }
}

STDAPI DllCanUnloadNow(void)
{
    HRESULT hr = S_FALSE;

    if( 0 == g_CountWizard &&
        0 == g_CountRenderEngine &&
        0 == g_CountUILayer &&
        0 == g_CountMixerControl )
    {
        hr = S_OK;
    }
    return hr;
}


//
// Add entry to the registry about CLSID object 
//
void MultiVMRRegisterClass( 
                           const CLSID& clsid, 
                           TCHAR *achClassName,
                           BOOL bRegister)
{
    HRESULT hr = S_OK;
    TCHAR achModule[MAX_PATH];
    WCHAR wcModule[MAX_PATH];
    WCHAR wcKey[MAX_PATH];
    TCHAR achKey[MAX_PATH];
    TCHAR achThreadingModel[] = TEXT("Both");
    long err = 0;
    LPOLESTR wcCLSID = NULL;
    HKEY hKey = NULL;
    HKEY hSubKey = NULL;

    GetModuleFileName( g_hInst, achModule, sizeof(achModule) );

#ifdef UNICODE
    wcscpy( wcModule, achModule );
#else
    MultiByteToWideChar(CP_ACP, 0, achModule, -1, wcModule, MAX_PATH); 
#endif

    hr = StringFromCLSID(clsid, &wcCLSID);

    wcscpy( wcKey, L"CLSID\\");
    wcscat( wcKey, wcCLSID);

#ifdef UNICODE
    _tcscpy( achKey, wcKey);
#else
    WideCharToMultiByte(CP_ACP, 0, wcKey, -1, achKey, MAX_PATH, 0, 0);
#endif

    // first, delete wcKey if it exists
    err = recursiveDeleteKey( HKEY_CLASSES_ROOT, achKey);

    if( bRegister )
    {
        // create new key
        err = RegCreateKeyEx(   HKEY_CLASSES_ROOT,
                                achKey, 
                                NULL, 
                                NULL, 
                                REG_OPTION_NON_VOLATILE, 
                                KEY_ALL_ACCESS, 
                                NULL, 
                                &hKey, 
                                NULL);
        if (ERROR_SUCCESS == err)
        {
            err = RegSetValueEx( hKey, NULL, 0, REG_SZ,(BYTE *)achClassName, 
                                    sizeof(TCHAR) * ( _tcslen(achClassName)+1));
            err = RegCreateKeyEx(   hKey, 
                                    TEXT("InprocServer32"), 
                                    NULL,
                                    NULL,
                                    REG_OPTION_NON_VOLATILE, 
                                    KEY_ALL_ACCESS, 
                                    NULL, 
                                    &hSubKey, 
                                    NULL);
            if( ERROR_SUCCESS == err)
            {
                err = RegSetValueEx( hSubKey, NULL, 0, REG_SZ,(BYTE *)achModule, 
                                    sizeof(TCHAR) * ( _tcslen(achModule)+1));
                err = RegSetValueEx( hSubKey, TEXT("ThreadingModel"), 0, REG_SZ,(BYTE *)achThreadingModel, 
                                    sizeof(TCHAR) * ( _tcslen(achThreadingModel)+1));
                RegCloseKey( hSubKey );
            }
            RegCloseKey( hKey );
        }
    }
    CoTaskMemFree(wcCLSID);
}


//
// Delete a key and all of its descendents.
//
LONG recursiveDeleteKey(HKEY hKeyParent,     // Parent of key to delete
                        TCHAR* achKeyChild)  // Key to delete
{
    // Open the child.
    HKEY hKeyChild;
    LONG lRes = RegOpenKeyEx(hKeyParent, achKeyChild, 0,
                              KEY_ALL_ACCESS, &hKeyChild);
    if (lRes != ERROR_SUCCESS)
    {
        return lRes;
    }

    // Enumerate all of the decendents of this child.
    FILETIME time;
    TCHAR achBuffer[256];
    DWORD dwSize = 256;

    while (RegEnumKeyEx(hKeyChild, 0, achBuffer, &dwSize, NULL,
           NULL, NULL, &time) == ERROR_SUCCESS)
    {
        // Delete the decendents of this child.
        lRes = recursiveDeleteKey(hKeyChild, achBuffer);
        if (lRes != ERROR_SUCCESS)
        {
            // Cleanup before exiting.
            RegCloseKey(hKeyChild);
            return lRes;
        }
        dwSize = 256;
    }

    // Close the child.
    RegCloseKey(hKeyChild);

    // Delete this child.
    return RegDeleteKey(hKeyParent, achKeyChild);
}

#ifdef _DEBUG
    void DbgMsg( char* szMessage, ... )
    {
        char szFullMessage[MAX_PATH];
        char szFormatMessage[MAX_PATH];

        // format message
        va_list ap;
        va_start(ap, szMessage);
        _vsnprintf( szFormatMessage, MAX_PATH, szMessage, ap);
        va_end(ap);
        strncat( szFormatMessage, "\n", MAX_PATH);
        strcpy( szFullMessage, "~*~*~*~*~*~ ");
        strcat( szFullMessage, szFormatMessage );
        OutputDebugStringA( szFullMessage );
    }
#else
    void DbgMsg( char* szMessage, ... ){;}
#endif


