#if !defined(AFX_CHOOSER_H__4CD8A2A0_2E61_4500_8935_13CA99BBD87E__INCLUDED_)
#define AFX_CHOOSER_H__4CD8A2A0_2E61_4500_8935_13CA99BBD87E__INCLUDED_

// chooser.h : declaration of the CDialogChooser class
//             This class keeps track of what dialogs to pop up when.

#define LAST_DLG 6

class CDialogChooser
{
public:
	CDialogChooser();
	~CDialogChooser();

	// All calls by mfcapwz.dll to CDirectXAppWiz::Next
	//  & CDirectXAppWiz::Back are delegated to these member
	//  functions, which keep track of what dialog is up
	//  now, and what to pop up next.
	CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
    VOID InitDialogs();

    void UpdatePreviewAndSteps( CStatic* pStatic );
    VOID SetPreviewBitmap( CStatic* pStatic );

    CStatic* m_pDlg1Preview;
    CStatic* m_pDlg2Preview;
    CStatic* m_pDlg3Preview;
    CStatic* m_pDlg4Preview;
    CStatic* m_pDlg5Preview;

    HBITMAP m_hBackgroundBitmap;

    HBITMAP m_hWinBlankPreview;
    HBITMAP m_hWinTeapotPreview;
    HBITMAP m_hWinTrianglePreview;
    HBITMAP m_hWinGdiPreview;

    HBITMAP m_hDlgBlankPreview;
    HBITMAP m_hDlgTeapotPreview;
    HBITMAP m_hDlgTrianglePreview;
    HBITMAP m_hDlgGdiPreview;

    INT     m_nCurrentPreviewID;
    BOOL    m_nSteps;

    BOOL    m_bUseMFC;

    BOOL    m_bWindow;
    BOOL    m_bMFCDialog;

    BOOL    m_bShowBlank;
    BOOL    m_bShowTriangle;
    BOOL    m_bShowTeapot;

	BOOL    m_bDirect3D;
	BOOL	m_bDirectInput;
	BOOL	m_bDirectMusic;
	BOOL	m_bDirectPlay;
	BOOL	m_bDirectSound;

	BOOL	m_bRegAccess;
	BOOL	m_bIncludeMenu;

protected:
	// Current step's index into the internal array m_pDlgs
	int m_nCurrDlg;

	// Internal array of pointers to the steps
	CAppWizStepDlg* m_pDlgs[LAST_DLG + 1];
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSER_H__4CD8A2A0_2E61_4500_8935_13CA99BBD87E__INCLUDED_)
