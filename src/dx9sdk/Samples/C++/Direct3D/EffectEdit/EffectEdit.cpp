// EffectEdit.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "EffectEdit.h"

#include "MainFrm.h"
#include "EffectDoc.h"
#include "UIElements.h"
#include "RenderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEffectEditCommandLineInfo

CEffectEditCommandLineInfo::CEffectEditCommandLineInfo()
{
    m_bUseExternalEditor = FALSE;
}


void CEffectEditCommandLineInfo::ParseParam(const TCHAR* pszParam,BOOL bFlag,BOOL bLast)
{
    TCHAR* pstrExtEd = TEXT("ee");
    if( bFlag && CompareString( LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, pszParam, -1, pstrExtEd, -1 ) == CSTR_EQUAL )
        m_bUseExternalEditor = TRUE;
    else
        CCommandLineInfo::ParseParam( pszParam, bFlag, bLast );
}


/////////////////////////////////////////////////////////////////////////////
// CEffectEditDocManager::DoPromptFileName - overridden to allow modification
// of initial dir
BOOL CEffectEditDocManager::DoPromptFileName(CString& fileName, UINT nIDSTitle,
            DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate)
{
    CFileDialog dlgFile(bOpenFileDialog);

    CString title;
    VERIFY(title.LoadString(nIDSTitle));

    dlgFile.m_ofn.Flags |= lFlags;

    TCHAR strMedia[MAX_PATH];
    BOOL bDefaultToMediaDir = AfxGetApp()->GetProfileInt( TEXT("Settings"), 
        TEXT("DefaultToDXSDKMediaDir"), TRUE );
    if( bDefaultToMediaDir )
    {
        DXUtil_GetDXSDKMediaPathCch( strMedia, MAX_PATH );       
        dlgFile.m_ofn.lpstrInitialDir = strMedia;
        TCHAR strMedia2[MAX_PATH];
        lstrcpy( strMedia2, strMedia );
        _tcsncat( strMedia2, TEXT("EffectEdit"), MAX_PATH );
        strMedia2[MAX_PATH-1] = 0;
        DWORD dw;
        dw = GetFileAttributes( strMedia2 );
        if( dw != ((DWORD)-1) && (dw & FILE_ATTRIBUTE_DIRECTORY) != 0 )
            dlgFile.m_ofn.lpstrInitialDir = strMedia2;
    }

    CString strFilter;

    // Can't do the usual _AfxAppendFilterSuffix thing because that function
    // is local to docmgr.cpp
    strFilter += TEXT("Effect Files (*.fx)");
    strFilter += (TCHAR)'\0';   // next string please
    strFilter += _T("*.fx");
    strFilter += (TCHAR)'\0';   // last string
    dlgFile.m_ofn.nMaxCustFilter++;

    // append the "*.*" all files filter
    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
    strFilter += allFilter;
    strFilter += (TCHAR)'\0';   // next string please
    strFilter += _T("*.*");
    strFilter += (TCHAR)'\0';   // last string
    dlgFile.m_ofn.nMaxCustFilter++;

    dlgFile.m_ofn.lpstrFilter = strFilter;
    dlgFile.m_ofn.lpstrTitle = title;
    dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

    INT_PTR nResult = dlgFile.DoModal();
    fileName.ReleaseBuffer();
    return nResult == IDOK;
};


/////////////////////////////////////////////////////////////////////////////
// CEffectEditApp

BEGIN_MESSAGE_MAP(CEffectEditApp, CWinApp)
    //{{AFX_MSG_MAP(CEffectEditApp)
    ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    ON_COMMAND(ID_VIEW_CHOOSEFONT, OnViewChooseFont)
    ON_COMMAND(ID_VIEW_TABS, OnViewTabOptions)
    ON_COMMAND(ID_FILE_DEFAULTTODXSDKMEDIAFOLDER, OnFileDefaultToDxsdkMediaFolder)
    ON_UPDATE_COMMAND_UI(ID_FILE_DEFAULTTODXSDKMEDIAFOLDER, OnUpdateFileDefaultToDxsdkMediaFolder)
    //}}AFX_MSG_MAP
    // Standard file based document commands
    ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEffectEditApp construction

CEffectEditApp::CEffectEditApp()
{
    m_bRenderContinuously = true;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEffectEditApp object

CEffectEditApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEffectEditApp initialization

BOOL CEffectEditApp::InitInstance()
{
    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#if(_MFC_VER < 0x0700)
#ifdef _AFXDLL
    Enable3dControls();         // Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif
#endif
    // Change the registry key under which our settings are stored.
    SetRegistryKey(_T("Microsoft"));

    LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

    if( !AfxInitRichEdit() )
        return FALSE;

    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views.

    m_pDocManager = new CEffectEditDocManager;
    
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CEffectDoc),
        RUNTIME_CLASS(CMainFrame),       // main SDI frame window
        RUNTIME_CLASS(CRenderView));
    AddDocTemplate(pDocTemplate);

    // Parse command line for standard shell commands, DDE, file open
    CEffectEditCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // Dispatch commands specified on the command line
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    if( cmdInfo.UseExternalEditor() )
        m_pMainWnd->PostMessage(WM_COMMAND, ID_EDIT_USEEXTERNALEDITOR );

    return TRUE;
}

void CEffectEditApp::OnFileDefaultToDxsdkMediaFolder()
{
    BOOL bDefaultToMediaDir = GetProfileInt( TEXT("Settings"), TEXT("DefaultToDXSDKMediaDir"), TRUE );
    bDefaultToMediaDir = !bDefaultToMediaDir;
    WriteProfileInt( TEXT("Settings"), TEXT("DefaultToDXSDKMediaDir"), bDefaultToMediaDir );
}

void CEffectEditApp::OnUpdateFileDefaultToDxsdkMediaFolder(CCmdUI* pCmdUI)
{
    BOOL bDefaultToMediaDir = GetProfileInt( TEXT("Settings"), TEXT("DefaultToDXSDKMediaDir"), TRUE );
    pCmdUI->SetCheck( bDefaultToMediaDir );
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    CString m_strVersion;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
        // No message handlers
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    TCHAR szFile[MAX_PATH];
    CString strVersion;
    UINT cb;
    DWORD dwHandle;
    BYTE FileVersionBuffer[1024];
    VS_FIXEDFILEINFO* pVersion = NULL;

    GetModuleFileName(NULL, szFile, MAX_PATH);

    cb = GetFileVersionInfoSize(szFile, &dwHandle/*ignored*/);
    if (cb > 0)
    {
        if (cb > sizeof(FileVersionBuffer))
            cb = sizeof(FileVersionBuffer);

        if (GetFileVersionInfo(szFile, 0, cb, FileVersionBuffer))
        {
            pVersion = NULL;
            if (VerQueryValue(FileVersionBuffer, "\\", (VOID**)&pVersion, &cb)
                && pVersion != NULL) 
            {
                strVersion.Format("Version %d.%02d.%02d.%04d", 
                    HIWORD(pVersion->dwFileVersionMS),
                    LOWORD(pVersion->dwFileVersionMS), 
                    HIWORD(pVersion->dwFileVersionLS), 
                    LOWORD(pVersion->dwFileVersionLS));
            }
        }
    }

    //{{AFX_DATA_INIT(CAboutDlg)
    m_strVersion = strVersion;
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    DDX_Text(pDX, IDC_VERSION, m_strVersion);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CEffectEditApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CEffectEditApp message handlers


BOOL CEffectEditApp::OnIdle(LONG lCount) 
{

    if( m_bRenderContinuously )
    {
        CWinApp::OnIdle(lCount);
        m_pMainWnd->SendMessage(WM_COMMAND, ID_VIEW_RENDER);
        return TRUE; // always request more time
    }
    else
    {
        return CWinApp::OnIdle(lCount);
    }
}

void CEffectEditApp::ActivateTextView()
{
    ((CMainFrame*)m_pMainWnd)->ActivateTextView();
}

void CEffectEditApp::ActivateErrorsView()
{
    ((CMainFrame*)m_pMainWnd)->ActivateErrorsView();
}

void CEffectEditApp::ActivateOptionsView()
{
    ((CMainFrame*)m_pMainWnd)->ActivateOptionsView();
}

void CEffectEditApp::SelectLine(int iLine)
{
    ((CMainFrame*)m_pMainWnd)->SelectLine(iLine);
}

void CEffectEditApp::OnViewChooseFont() 
{
    CFontDialog fontDialog;
    DWORD dwFontSize = GetProfileInt( TEXT("Settings"), TEXT("FontSize"), 9 );
    CString strFontName = GetProfileString( TEXT("Settings"), TEXT("FontName"), TEXT("Courier") );

    HDC hdc = GetDC(NULL);
    fontDialog.m_lf.lfHeight = -MulDiv(dwFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
    ReleaseDC( NULL, hdc );
    fontDialog.m_lf.lfWeight = FW_NORMAL;
    lstrcpy( fontDialog.m_lf.lfFaceName, strFontName );
    fontDialog.m_cf.Flags |= CF_INITTOLOGFONTSTRUCT;
    fontDialog.m_cf.Flags &= ~CF_EFFECTS;

    if( IDOK == fontDialog.DoModal() )
    {
        CFont font;
        if( NULL != font.CreateFontIndirect(&fontDialog.m_lf) )
        {
            font.DeleteObject();
            int newSize = fontDialog.GetSize() / 10;
            CString strNewFontName = fontDialog.GetFaceName();
            WriteProfileInt( TEXT("Settings"), TEXT("FontSize"), newSize );
            WriteProfileString( TEXT("Settings"), TEXT("FontName"), strNewFontName );

            ((CMainFrame*)m_pMainWnd)->TextViewUpdateFont();
        }
    }
}

void CEffectEditApp::OnViewTabOptions() 
{
    CTabOptionsDialog tabDialog;

    BOOL bKeepTabs = GetProfileInt( TEXT("Settings"), TEXT("Keep Tabs"), FALSE );
    INT numSpaces = GetProfileInt( TEXT("Settings"), TEXT("Num Spaces"), 4 );
    
    tabDialog.m_numSpaces = numSpaces;
    
    if( bKeepTabs )
        tabDialog.m_TabsOrSpacesRadio = 0;
    else
        tabDialog.m_TabsOrSpacesRadio = 1;

    if( IDOK == tabDialog.DoModal() )
    {
        numSpaces = tabDialog.m_numSpaces;
        if( tabDialog.m_TabsOrSpacesRadio == 0 )
            bKeepTabs = TRUE;
        else
            bKeepTabs = FALSE;

        WriteProfileInt( TEXT("Settings"), TEXT("Keep Tabs"), bKeepTabs );
        WriteProfileInt( TEXT("Settings"), TEXT("Num Spaces"), numSpaces );
    }
}

/////////////////////////////////////////////////////////////////////////////
// CTabOptionsDialog dialog


CTabOptionsDialog::CTabOptionsDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CTabOptionsDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CTabOptionsDialog)
    m_numSpaces = 0;
    m_TabsOrSpacesRadio = -1;
    //}}AFX_DATA_INIT
}


void CTabOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CTabOptionsDialog)
    DDX_Text(pDX, IDC_NUMSPACES, m_numSpaces);
    DDV_MinMaxUInt(pDX, m_numSpaces, 1, 8);
    DDX_Radio(pDX, IDC_TABS, m_TabsOrSpacesRadio);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabOptionsDialog, CDialog)
    //{{AFX_MSG_MAP(CTabOptionsDialog)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabOptionsDialog message handlers
