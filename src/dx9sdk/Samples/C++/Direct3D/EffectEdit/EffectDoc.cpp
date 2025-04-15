// EffectDoc.cpp : implementation of the CEffectDoc class
//

#include "stdafx.h"
#include "EffectEdit.h"

#include "EffectDoc.h"
#include "UIElements.h"
#include "RenderView.h"
#include "TextView.h"
#include "ErrorsView.h"
#include "OptionsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char* g_strCodeDefault = 
    "// Sample effect file\r\n"
    "\r\n"
    "// Here is a texture parameter\r\n"
    "texture tex0 < string name = \"tiger.bmp\"; >;\r\n"
    "\r\n"
    "// Here is a vector parameter representing the direction\r\n"
    "// vector from a light source.  The UIDirectional annotation\r\n"
    "// tells EffectEdit to create a user interface element that can\r\n"
    "// be used to interactively change the light direction.\r\n"
    "float3 lightDir\r\n"
    "<\r\n"
    "    string UIDirectional = \"Light Direction\";\r\n"
    "> = {0.577, -0.577, 0.577};\r\n"
    "\r\n"
    "string XFile = \"tiger.x\";   // Model to load\r\n"
    "string BIMG  = \"lake.bmp\";  // Background image\r\n"
    "DWORD  BCLR = 0xff202080;  // Background color (if no image)\r\n"
    "\r\n"
    "technique tec0\r\n"
    "{\r\n"
    "    pass p0\r\n"
    "    {\r\n"
    "        // Set up reasonable material defaults\r\n"
    "        MaterialAmbient = {1.0, 1.0, 1.0, 1.0}; \r\n"
    "        MaterialDiffuse = {1.0, 1.0, 1.0, 1.0}; \r\n"
    "        MaterialSpecular = {1.0, 1.0, 1.0, 1.0}; \r\n"
    "        MaterialPower = 40.0f;\r\n"
    "        \r\n"
    "        // Set up one directional light\r\n"
    "        LightType[0]      = DIRECTIONAL;\r\n"
    "        LightDiffuse[0]   = {1.0, 1.0, 1.0, 1.0};\r\n"
    "        LightSpecular[0]  = {1.0, 1.0, 1.0, 1.0}; \r\n"
    "        LightAmbient[0]   = {0.1, 0.1, 0.1, 1.0};\r\n"
    "        LightDirection[0] = <lightDir>; // Use the vector parameter defined above\r\n"
    "        LightRange[0]     = 100000.0;\r\n"
    "        \r\n"
    "        // Turn lighting on and use light 0\r\n"
    "        LightEnable[0] = True;\r\n"
    "        Lighting = True;\r\n"
    "        SpecularEnable = True;\r\n"
    "        \r\n"
    "        // Set up texture stage 0\r\n"
    "        Texture[0] = <tex0>; // Use the texture parameter defined above\r\n"
    "        ColorOp[0] = Modulate;\r\n"
    "        ColorArg1[0] = Texture;\r\n"
    "        ColorArg2[0] = Diffuse;\r\n"
    "        AlphaOp[0] = Modulate;\r\n"
    "        AlphaArg1[0] = Texture;\r\n"
    "        AlphaArg2[0] = Diffuse;\r\n"
    "        MinFilter[0] = Linear;\r\n"
    "        MagFilter[0] = Linear;\r\n"
    "        MipFilter[0] = Linear;\r\n"
    "        \r\n"
    "        // Disable texture stage 1\r\n"
    "        ColorOp[1] = Disable;\r\n"
    "        AlphaOp[1] = Disable;\r\n"
    "    }\r\n"
    "}\r\n"
    "";

/////////////////////////////////////////////////////////////////////////////
// CEffectDoc

IMPLEMENT_DYNCREATE(CEffectDoc, CDocument)

BEGIN_MESSAGE_MAP(CEffectDoc, CDocument)
    //{{AFX_MSG_MAP(CEffectDoc)
    ON_COMMAND(ID_EDIT_USEEXTERNALEDITOR, OnEditUseExternalEditor)
    ON_UPDATE_COMMAND_UI(ID_EDIT_USEEXTERNALEDITOR, OnUpdateEditUseExternalEditor)
    ON_COMMAND(ID_EDIT_USESHADEROPTIMIZATION, OnEditUseShaderOptimization)
    ON_UPDATE_COMMAND_UI(ID_EDIT_USESHADEROPTIMIZATION, OnUpdateEditUseShaderOptimization)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEffectDoc construction/destruction

CEffectDoc::CEffectDoc()
{
    m_bUsingExternalEditor = FALSE;
    m_bFirstTime = TRUE;
    m_strCode = g_strCodeDefault;
    m_bNeedToCompile = true;
    m_iLineSelected = -1;

    m_bUsingShaderOptimization = AfxGetApp()->GetProfileInt( TEXT("Settings"), TEXT("UseShaderOptimization"), TRUE );
}

CEffectDoc::~CEffectDoc()
{
}

BOOL CEffectDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    if( m_bFirstTime )
    {
        m_strCode = g_strCodeDefault;
        m_bFirstTime = FALSE;
    }
    else
    {
        m_strCode.Empty();
    }
    m_bNeedToCompile = true;
    m_iLineSelected = -1;

    GetRenderView()->ResetCamera();

    return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEffectDoc serialization

void CEffectDoc::Serialize(CArchive& ar)
{
    // Note: file is always stored as ANSI text, not Unicode
    if (ar.IsStoring())
    {
        CHAR ch[2] = { 0, 0 };
        TCHAR tch[2] = { 0, 0 };
        for( INT ich = 0; ich < m_strCode.GetLength(); ich++ )
        {
            tch[0] = m_strCode[ich];
            DXUtil_ConvertGenericStringToAnsiCch( ch, tch, 2 );
            ar.Write( ch, 1 );
        }
    }
    else
    {
        m_strCode.Empty();

        BOOL bKeepTabs = AfxGetApp()->GetProfileInt( TEXT("Settings"), TEXT("Keep Tabs"), FALSE );
        int numSpaces = AfxGetApp()->GetProfileInt( TEXT("Settings"), TEXT("Num Spaces"), 4 );

        CHAR ch[2] = { 0, 0 };
        TCHAR tch[2] = { 0, 0 };

        while( ar.Read( ch, 1 ) )
        {
            DXUtil_ConvertAnsiStringToGenericCch( tch, ch, 2 );
            if( tch[0] == TEXT('\t') && !bKeepTabs )
            {
                for( int iSpace = 0; iSpace < numSpaces; iSpace++ )
                    m_strCode += TEXT(' ');
            }
            else
            {
                m_strCode += tch[0];
            }
        }
        m_bNeedToCompile = true;
        GetRenderView()->RequestUIReset();
    }
}

/////////////////////////////////////////////////////////////////////////////
// CEffectDoc diagnostics

#ifdef _DEBUG
void CEffectDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CEffectDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEffectDoc commands

void CEffectDoc::SetCode(CString str)
{
    if( m_strCode != str )
    {
        SetModifiedFlag();
        m_strCode = str;
        m_bNeedToCompile = true;
    }
}

void CEffectDoc::Compile( bool bForceCompile )
{
    if( !bForceCompile && !m_bNeedToCompile )
        return;

    CRenderView* pRenderView = GetRenderView();
    CErrorsView* pErrorsView = GetErrorsView();
    COptionsView* pOptionsView = GetOptionsView();
    if( pRenderView != NULL )
    {
        int iTechnique;
        BOOL bTryLater;
        CString strCode;
        if( m_bUsingExternalEditor )
        {
            strCode = GetPathName();
        }
        else
        {
            strCode = m_strCode;
        }
        pRenderView->CompileEffect( strCode, m_bUsingShaderOptimization, m_bUsingExternalEditor,
            m_strErrors, m_techniqueNameList, &iTechnique, &bTryLater );

        if( !bTryLater )
        {
            m_bNeedToCompile = false;

            if( pErrorsView != NULL )
                pErrorsView->ParseErrors();

            if( pOptionsView != NULL )
                pOptionsView->SetTechniqueNameList( m_techniqueNameList, iTechnique );
        }
    }
}

CString CEffectDoc::GetErrorString()
{
    return m_strErrors;
}

void CEffectDoc::SelectLine(int iLine)
{
    m_iLineSelected = iLine;
    UpdateAllViews( NULL );
    m_iLineSelected = -1;
}

int CEffectDoc::GetSelectedLine()
{
    return m_iLineSelected;
}

CRenderView* CEffectDoc::GetRenderView()
{
   POSITION pos = GetFirstViewPosition();
   while (pos != NULL)
   {
      CView* pView = GetNextView(pos);
      if( pView->IsKindOf( RUNTIME_CLASS( CRenderView ) ) )
      {
          return (CRenderView*)pView;
      }
   }
   return NULL;
}

CTextView* CEffectDoc::GetTextView()
{
   POSITION pos = GetFirstViewPosition();
   while (pos != NULL)
   {
      CView* pView = GetNextView(pos);
      if( pView->IsKindOf( RUNTIME_CLASS( CTextView ) ) )
      {
          return (CTextView*)pView;
      }
   }
   return NULL;
}

COptionsView* CEffectDoc::GetOptionsView()
{
   POSITION pos = GetFirstViewPosition();
   while (pos != NULL)
   {
      CView* pView = GetNextView(pos);
      if( pView->IsKindOf( RUNTIME_CLASS( COptionsView ) ) )
      {
          return (COptionsView*)pView;
      }
   }
   return NULL;
}

CErrorsView* CEffectDoc::GetErrorsView()
{
   POSITION pos = GetFirstViewPosition();
   while (pos != NULL)
   {
      CView* pView = GetNextView(pos);
      if( pView->IsKindOf( RUNTIME_CLASS( CErrorsView ) ) )
      {
          return (CErrorsView*)pView;
      }
   }
   return NULL;
}


BOOL CEffectDoc::GetShowStats()
{
    CRenderView* pRenderView = GetRenderView();
    if( pRenderView != NULL )
        return pRenderView->GetShowStats();
    else
        return FALSE;
}


void CEffectDoc::ShowStats( BOOL bShowStats )
{
    CRenderView* pRenderView = GetRenderView();
    if( pRenderView != NULL )
        pRenderView->ShowStats( bShowStats );
}

void CEffectDoc::OnEditUseExternalEditor()
{
    if( !m_bUsingExternalEditor )
    {
        // Before going external, make sure current file is saved
        if( IsModified() || GetPathName().IsEmpty() )
        {
            if( IDCANCEL == MessageBox( GetTextView()->GetSafeHwnd(), TEXT("You will need to save this effect to a file before changing to external editing mode.  Press OK to save."), TEXT("EffectEdit"), MB_OKCANCEL ) )
                return;
            if( !DoFileSave() )
                return;
        }
    }
    m_bUsingExternalEditor = !m_bUsingExternalEditor;
    GetTextView()->SetExternalEditorMode( m_bUsingExternalEditor );
}

void CEffectDoc::OnUpdateEditUseExternalEditor(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck( m_bUsingExternalEditor );
}

BOOL CEffectDoc::GetLastModifiedTime( CTime* pTime )
{
    WIN32_FILE_ATTRIBUTE_DATA data;
    if( GetPathName().IsEmpty() )
        return FALSE;
    if( !GetFileAttributesEx( GetPathName(), GetFileExInfoStandard, &data ) )
        return FALSE;
    *pTime = data.ftLastWriteTime;

    return TRUE;
}

void CEffectDoc::ReloadFromFile()
{
    OnOpenDocument( GetPathName() );
    Compile();
}

void CEffectDoc::OnEditUseShaderOptimization()
{
    m_bUsingShaderOptimization = !m_bUsingShaderOptimization;
    AfxGetApp()->WriteProfileInt( TEXT("Settings"), TEXT("UseShaderOptimization"), m_bUsingShaderOptimization );
    m_bNeedToCompile = TRUE;
    Compile();
}

void CEffectDoc::OnUpdateEditUseShaderOptimization(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck( m_bUsingShaderOptimization );
}

