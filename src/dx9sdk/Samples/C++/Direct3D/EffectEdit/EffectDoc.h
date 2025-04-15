// EffectDoc.h : interface of the CEffectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EFFECTDOC_H__9320DC20_5E33_4D01_A644_02765D9BE875__INCLUDED_)
#define AFX_EFFECTDOC_H__9320DC20_5E33_4D01_A644_02765D9BE875__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COptionsView;
class CErrorsView;
class CRenderView;
class CTextView;

class CEffectDoc : public CDocument
{
protected: // create from serialization only
    CEffectDoc();
    DECLARE_DYNCREATE(CEffectDoc)

// Attributes
public:
    CString GetCode() { return m_strCode; }
    void SetCode(CString str);

    CRenderView* GetRenderView();
    CTextView* GetTextView();
    COptionsView* GetOptionsView();
    CErrorsView* GetErrorsView();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CEffectDoc)
    public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
    //}}AFX_VIRTUAL

// Implementation
public:
    int GetSelectedLine();
    void SelectLine( int iLine );
    CString GetErrorString();
    void Compile( bool bForceCompile = false );
    BOOL GetShowStats();
    void ShowStats( BOOL bShowStats );
    virtual ~CEffectDoc();
    BOOL UsingExternalEditor() { return m_bUsingExternalEditor; }
    BOOL GetLastModifiedTime( CTime* pTime );
    void ReloadFromFile();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    BOOL m_bUsingExternalEditor;
    BOOL m_bUsingShaderOptimization;
    BOOL m_bFirstTime;
    int m_iLineSelected;
    bool m_bNeedToCompile;
    CString m_strCode;
    CString m_strErrors;
    CStringList m_techniqueNameList;
    //{{AFX_MSG(CEffectDoc)
    afx_msg void OnEditUseExternalEditor();
    afx_msg void OnUpdateEditUseExternalEditor(CCmdUI* pCmdUI);
    afx_msg void OnEditUseShaderOptimization();
    afx_msg void OnUpdateEditUseShaderOptimization(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EFFECTDOC_H__9320DC20_5E33_4D01_A644_02765D9BE875__INCLUDED_)
