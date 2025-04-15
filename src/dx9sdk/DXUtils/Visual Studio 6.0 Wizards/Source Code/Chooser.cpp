// chooser.cpp : Implements the CDialogChooser class
//

#include "stdafx.h"
#include <objbase.h>
#include "DxAppWiz.h"
#include "DXaw.h"
#include "chooser.h"
#include "cstm1dlg.h"
#include "cstm2dlg.h"
#include "cstm3dlg.h"
#include "cstm4dlg.h"
#include "cstm5dlg.h"
#include "cstm6dlg.h"
#include "cstm7dlg.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DOC_TRACK   0   // MDI/SDI based app track
#define DLG_TRACK   1   // dialog based app track

// define the steps, since these are array indices, their values matter
#define STEP_ZERO           0
#define STEP_DX             1
#define STEP_D3D            2
#define STEP_DINPUT         3
#define STEP_DMUSIC         4
#define STEP_DPLAY          5
#define STEP_DSOUND         6

// On construction, set up internal array with pointers to each step.
CDialogChooser::CDialogChooser()
{
    m_pDlg1Preview = NULL;
    m_pDlg2Preview = NULL;
    m_pDlg3Preview = NULL;
    m_pDlg4Preview = NULL;
    m_pDlg5Preview = NULL;

    m_bWindow      = TRUE;
    m_bMFCDialog   = FALSE;

	m_bDirect3D    = TRUE;
	m_bDirectInput = TRUE;
	m_bDirectMusic = TRUE;
	m_bDirectSound = FALSE;
	m_bDirectPlay  = FALSE;

    m_bUseMFC      = FALSE;

    m_bShowBlank    = FALSE;
    m_bShowTriangle = FALSE;
    m_bShowTeapot   = TRUE;

	m_bRegAccess	= TRUE;
	m_bIncludeMenu	= TRUE;

	m_pDlgs[STEP_ZERO] = NULL;

	m_pDlgs[STEP_DX]     = new CCustom1Dlg( this );
	m_pDlgs[STEP_D3D]    = new CCustom2Dlg( this );
	m_pDlgs[STEP_DINPUT] = new CCustom3Dlg( this );
	m_pDlgs[STEP_DMUSIC] = new CCustom4Dlg;
	m_pDlgs[STEP_DPLAY]  = new CCustom5Dlg( this );
	m_pDlgs[STEP_DSOUND] = new CCustom6Dlg;

    m_hBackgroundBitmap = ::LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_BACKGROUND) );

    m_hWinBlankPreview     = ::LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_WIN_BLANK) );
    m_hWinTeapotPreview    = ::LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_WIN_TEAPOT) );
    m_hWinTrianglePreview  = ::LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_WIN_TRIANGLE) );
    m_hWinGdiPreview       = ::LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_WIN_GDI) );

    m_hDlgBlankPreview     = ::LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_DLG_BLANK) );
    m_hDlgTeapotPreview    = ::LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_DLG_TEAPOT) );
    m_hDlgTrianglePreview  = ::LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_DLG_TRIANGLE) );
    m_hDlgGdiPreview       = ::LoadBitmap( g_hInstance, MAKEINTRESOURCE(IDB_DLG_GDI) );

    m_nCurrentPreviewID = IDB_WIN_TEAPOT;
	m_nCurrDlg = 0;
}

// Remember where the custom steps begin, so we can delete them in
//  the destructor
#define FIRST_CUSTOM_STEP 1
#define LAST_CUSTOM_STEP 6

// The destructor deletes entries in the internal array corresponding to
//  custom steps.
CDialogChooser::~CDialogChooser()
{
	for (int i = FIRST_CUSTOM_STEP; i <= LAST_CUSTOM_STEP; i++)
	{
		ASSERT(m_pDlgs[i] != NULL);
		delete m_pDlgs[i];
	}

    DeleteObject( m_hBackgroundBitmap );
    DeleteObject( m_hWinBlankPreview );
    DeleteObject( m_hWinTeapotPreview );
    DeleteObject( m_hWinTrianglePreview );
    DeleteObject( m_hWinGdiPreview );

    DeleteObject( m_hDlgBlankPreview );
    DeleteObject( m_hDlgTeapotPreview );
    DeleteObject( m_hDlgTrianglePreview );
    DeleteObject( m_hDlgGdiPreview );
}


BOOL BIsAlpha(TCHAR c)
{
    if( ((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) )
        return TRUE;
    return FALSE;
}


// Use the internal array to determine the next step.
CAppWizStepDlg* CDialogChooser::Next(CAppWizStepDlg* pDlg)
{
	ASSERT(0 <= m_nCurrDlg && m_nCurrDlg < LAST_DLG);
	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);

	// If the current step is the "project type" step, the AppWizard "track" may
	//  have changed.
	if( m_nCurrDlg == STEP_ZERO )
	{
        TCHAR strBuffer[MAX_PATH];
        ZeroMemory( strBuffer, sizeof(TCHAR)*MAX_PATH );

        CString strRoot;
        DirectXaw.m_Dictionary.Lookup( "root", strRoot );
        CString tmp;
        tmp = strRoot.GetAt(0);
        tmp.MakeUpper();
        strRoot.SetAt( 0, tmp[0] );

        int i = 0;
        int j = 0;
        while( i < strRoot.GetLength() )
        {
            TCHAR ch = strRoot.GetAt(i);
            if( !BIsAlpha(ch) && ch != '_' )
            {
                if( i+1 < strRoot.GetLength() )
                {
                    tmp = strRoot.GetAt(i+1);
                    tmp.MakeUpper();
                    strRoot.SetAt( i+1, tmp[0] );
                }
            }
            else
            {
                strBuffer[j++] = ch;
            }
            i++;
        }
        strBuffer[j++] = 0;
        DirectXaw.m_Dictionary["CRoot"] = CString(strBuffer);

        GUID guid;
        ZeroMemory( &guid, sizeof(GUID) );
        CoCreateGuid( &guid );

        CString strGuidStruct;
        CString strGuidMsg;
        strGuidMsg.Format( TEXT("{%0.8X-%0.4X-%0.4X-%0.2X%0.2X-%0.2X%0.2X%0.2X%0.2X%0.2X%0.2X}"), 
                guid.Data1, guid.Data2, guid.Data3, 
                guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
                guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7] );
        DirectXaw.m_Dictionary["GUIDMSG"] = strGuidMsg;

        strGuidStruct.Format( TEXT("{ 0x%0.8x, 0x%0.4x, 0x%0.4x, { 0x%0.2x, 0x%0.2x, 0x%0.2x, 0x%0.2x, 0x%0.2x, 0x%0.2x, 0x%0.2x, 0x%0.2x } }"), 
                guid.Data1, guid.Data2, guid.Data3, 
                guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
                guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7] );
        DirectXaw.m_Dictionary["GUIDSTRUCT"] = strGuidStruct;
    }

    BOOL bFound = FALSE;

    while( !bFound )
    {
        m_nCurrDlg++;

        switch( m_nCurrDlg )
        {
        case STEP_DX:
            bFound = TRUE;
            break;

        case STEP_D3D:
            if( m_bDirect3D )   
                bFound = TRUE;
            break;

        case STEP_DINPUT:
            if( m_bDirectInput )   
                bFound = TRUE;
            break;
/*
        case STEP_DMUSIC:
            if( m_bDirectMusic )   
                bFound = TRUE;
            break;
*/
        case STEP_DPLAY:
            if( m_bDirectPlay )   
                bFound = TRUE;
            break;
/*
        case STEP_DSOUND:
            if( m_bDirectSound )   
                bFound = TRUE;
            break;
*/
        }
    }

    if( m_nCurrDlg > LAST_DLG )
        m_nCurrDlg = STEP_DX;

    switch( m_nCurrDlg )
    {
        case STEP_DX:
            SetPreviewBitmap( m_pDlg1Preview );
            break;
        case STEP_D3D:
            SetPreviewBitmap( m_pDlg2Preview );
            break;
        case STEP_DINPUT:
            SetPreviewBitmap( m_pDlg3Preview );
            break;
        case STEP_DMUSIC:
            SetPreviewBitmap( m_pDlg4Preview );
            break;
        case STEP_DPLAY:
            SetPreviewBitmap( m_pDlg5Preview );
            break;
        case STEP_DSOUND:
            break;
    }

	return m_pDlgs[m_nCurrDlg];
}

// Use the internal array to determine the previous step.
CAppWizStepDlg* CDialogChooser::Back(CAppWizStepDlg* pDlg)
{
	ASSERT(1 <= m_nCurrDlg && m_nCurrDlg <= LAST_DLG);
	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);

    BOOL bFound = FALSE;

    while( !bFound )
    {
        m_nCurrDlg--;

        switch( m_nCurrDlg )
        {
        case STEP_ZERO:
        case STEP_DX:
            bFound = TRUE;
            break;

        case STEP_D3D:
            if( m_bDirect3D )   
                bFound = TRUE;
            break;

        case STEP_DINPUT:
            if( m_bDirectInput )   
                bFound = TRUE;
            break;
/*
        case STEP_DMUSIC:
            if( m_bDirectMusic )   
                bFound = TRUE;
            break;
*/
        case STEP_DPLAY:
            if( m_bDirectPlay )   
                bFound = TRUE;
            break;
/*
        case STEP_DSOUND:
            if( m_bDirectSound )   
                bFound = TRUE;
            break;
*/
        }
    }

    if( m_nCurrDlg < 0 )
        m_nCurrDlg = STEP_DX;

    switch( m_nCurrDlg )
    {
        case STEP_DX:
            SetPreviewBitmap( m_pDlg1Preview );
            break;
        case STEP_D3D:
            SetPreviewBitmap( m_pDlg2Preview );
            break;
        case STEP_DINPUT:
            SetPreviewBitmap( m_pDlg3Preview );
            break;
        case STEP_DMUSIC:
            SetPreviewBitmap( m_pDlg4Preview );
            break;
        case STEP_DPLAY:
            SetPreviewBitmap( m_pDlg5Preview );
            break;
        case STEP_DSOUND:
            break;
    }

	return m_pDlgs[m_nCurrDlg];
}


VOID CDialogChooser::InitDialogs()
{
    if( m_bDirect3D )
        m_pDlgs[STEP_D3D]->OnDismiss();
    else
        ((CCustom2Dlg*) m_pDlgs[STEP_D3D])->RemoveAllKeys();

    if( m_bDirectInput )
        m_pDlgs[STEP_DINPUT]->OnDismiss();
    else
        ((CCustom3Dlg*) m_pDlgs[STEP_DINPUT])->RemoveAllKeys();

    if( m_bDirectPlay )
        m_pDlgs[STEP_DPLAY]->OnDismiss();
    else
        ((CCustom5Dlg*) m_pDlgs[STEP_DPLAY])->RemoveAllKeys();
}

void CDialogChooser::UpdatePreviewAndSteps( CStatic* pStatic )
{
    int nPreviewID = IDB_DLG_GDI;

    if( m_bDirect3D )
    {
        if( m_bMFCDialog )
        {
            if( m_bShowBlank )
                nPreviewID = IDB_DLG_BLANK;
            else if( m_bShowTriangle )
                nPreviewID = IDB_DLG_TRIANGLE;
            else if( m_bShowTeapot )
                nPreviewID = IDB_DLG_TEAPOT;
        }
        else
        {
            if( m_bShowBlank )
                nPreviewID = IDB_WIN_BLANK;
            else if( m_bShowTriangle )
                nPreviewID = IDB_WIN_TRIANGLE;
            else if( m_bShowTeapot )
                nPreviewID = IDB_WIN_TEAPOT;
        }
    }
    else
    {
        if( m_bMFCDialog )
        {
            nPreviewID = IDB_DLG_GDI;
        }
        else
        {
            nPreviewID = IDB_WIN_GDI;
        }
    }

    m_nCurrentPreviewID = nPreviewID;

    SetPreviewBitmap( pStatic );

    m_nSteps = 1;

    if( m_bDirect3D )
        m_nSteps++;

    if( m_bDirectInput )
        m_nSteps++;

    if( m_bDirectPlay )
        m_nSteps++;

	SetNumberOfSteps(m_nSteps);    

    if( m_bMFCDialog )
        m_bUseMFC = TRUE;
    else
        m_bUseMFC = FALSE;
}


VOID CDialogChooser::SetPreviewBitmap( CStatic* pStatic )
{
    if( pStatic == NULL )
        return;

    HBITMAP hBitmap = NULL;
    switch( m_nCurrentPreviewID )
    {
        case IDB_WIN_BLANK:
            hBitmap = m_hWinBlankPreview;
            break;
        case IDB_WIN_TEAPOT:
            hBitmap = m_hWinTeapotPreview;
            break;
        case IDB_WIN_TRIANGLE:
            hBitmap = m_hWinTrianglePreview;
            break;
        case IDB_WIN_GDI:
            hBitmap = m_hWinGdiPreview;
            break;

        case IDB_DLG_BLANK:
            hBitmap = m_hDlgBlankPreview;
            break;
        case IDB_DLG_TEAPOT:
            hBitmap = m_hDlgTeapotPreview;
            break;
        case IDB_DLG_TRIANGLE:
            hBitmap = m_hDlgTrianglePreview;
            break;
        case IDB_DLG_GDI:
            hBitmap = m_hDlgGdiPreview;
            break;
    }

    if( hBitmap && pStatic )
    {
        pStatic->SetBitmap( hBitmap );
        pStatic->InvalidateRect(NULL, FALSE );
    }
}
