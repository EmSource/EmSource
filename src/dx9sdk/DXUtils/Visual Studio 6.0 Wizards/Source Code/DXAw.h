#if !defined(AFX_DXaw_H__9B3197F6_35EF_468F_B166_A96948907835__INCLUDED_)
#define AFX_DXaw_H__9B3197F6_35EF_468F_B166_A96948907835__INCLUDED_

// DXaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see DirectX.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CDirectXAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
    virtual void CustomizeProject(IBuildProject* pProject);
    virtual void ProcessTemplate( LPCTSTR lpszInput, DWORD dwSize, OutputStream* pOutput );

protected:
	CDialogChooser* m_pChooser;
};

// This declares the one instance of the CDirectXAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global DXaw.  (Its definition is in DXaw.cpp.)
extern CDirectXAppWiz DirectXaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DXaw_H__9B3197F6_35EF_468F_B166_A96948907835__INCLUDED_)
