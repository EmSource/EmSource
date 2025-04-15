// DXaw.cpp : implementation file
//

#include "stdafx.h"
#include "DxAppWiz.h"
#include "DXaw.h"
#include "chooser.h"

#include <atlbase.h>
#include <initguid.h>
#include <ObjModel\bldauto.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\blddefs.h>

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CDirectXAppWiz::InitCustomAppWiz()
{
	// Create a new dialog chooser; CDialogChooser's constructor initializes
	//  its internal array with pointers to the steps.
	m_pChooser = new CDialogChooser;

	// Set the maximum number of steps.
	SetNumberOfSteps(-1);

	// TODO: Add any other custom AppWizard-wide initialization here.
}

// This is called just before the custom AppWizard is unloaded.
void CDirectXAppWiz::ExitCustomAppWiz()
{
	// Deallocate memory used for the dialog chooser
	ASSERT(m_pChooser != NULL);
	delete m_pChooser;
	m_pChooser = NULL;

	// TODO: Add code here to deallocate resources used by the custom AppWizard
}

// This is called when the user clicks "Create..." on the New Project dialog
//  or "Next" on one of the custom AppWizard's steps.
CAppWizStepDlg* CDirectXAppWiz::Next(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Next(pDlg);
}

// This is called when the user clicks "Back" on one of the custom
//  AppWizard's steps.
CAppWizStepDlg* CDirectXAppWiz::Back(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Back(pDlg);
}

void CDirectXAppWiz::CustomizeProject(IBuildProject* pProject)
{
    HRESULT hr;
    int i;

    IConfigurations* pConfigs = NULL;
    IConfiguration* pConfig   = NULL;

    if( pProject == NULL )
        return;

    hr = pProject->get_Configurations( &pConfigs );
    if( FAILED(hr) || pConfigs == NULL )
        goto LCleanup;

    LONG lCount;

    hr = pConfigs->get_Count( &lCount );
    if( FAILED(hr) )
        goto LCleanup;

    for( i=1; i<lCount+1; i++ )
    {
        VARIANT var;
        ZeroMemory( &var, sizeof(var) ); 
        var.vt   = VT_I4;
        var.lVal = i;

        hr = pConfigs->Item( var, &pConfig );
        if( FAILED(hr) || pConfigs == NULL )
            goto LCleanup;

        // Add all libs
        BSTR bstrTool = SysAllocString( L"link.exe" );
        BSTR bstrSettings = SysAllocString( L"dsound.lib dinput8.lib dxerr9.lib d3dx9.lib d3d9.lib d3dxof.lib dxguid.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comctl32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib" );
        hr = pConfig->AddToolSettings( bstrTool, bstrSettings, var );
        SysFreeString( bstrTool );
        SysFreeString( bstrSettings );

        // Set MFC or not
        bstrTool = SysAllocString( L"mfc" );
        if( m_pChooser->m_bUseMFC )
            bstrSettings = SysAllocString( L"2" );
        else
            bstrSettings = SysAllocString( L"0" );
        hr = pConfig->AddToolSettings( bstrTool, bstrSettings, var );
        SysFreeString( bstrTool );
        SysFreeString( bstrSettings );

        // Add _WIN32_DCOM if using DPlay
        if( m_pChooser->m_bDirectPlay )
        {
            bstrTool = SysAllocString( L"cl.exe" );
            bstrSettings = SysAllocString( L"/D_WIN32_DCOM" );
            hr = pConfig->AddToolSettings( bstrTool, bstrSettings, var );
            SysFreeString( bstrSettings );
            SysFreeString( bstrTool );
        }


        bstrTool = SysAllocString( L"cl.exe" );
        bstrSettings = SysAllocString( L"/W4" );
        hr = pConfig->AddToolSettings( bstrTool, bstrSettings, var );
        SysFreeString( bstrSettings );
        SysFreeString( bstrTool );

        pConfig->Release();
        pConfig = NULL;

        if( FAILED(hr) )
            goto LCleanup;
    }

LCleanup:
    if( pConfigs )
        pConfigs->Release();

    if( pConfig )
        pConfig->Release();

    if( FAILED(hr) )
    {
        MessageBox( NULL, "Failed setting Project config", "Failure", MB_OK );
    }
}

void CDirectXAppWiz::ProcessTemplate( LPCTSTR lpszInput, DWORD dwSize, OutputStream* pOutput )
{
    CCustomAppWiz::ProcessTemplate( lpszInput, dwSize, pOutput );
}

// Here we define one instance of the CDirectXAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global DirectXaw.
CDirectXAppWiz DirectXaw;


