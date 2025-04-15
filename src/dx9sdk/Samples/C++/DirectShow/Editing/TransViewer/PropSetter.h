// ---------------------------------------------------------------------------
// File: PropSetter.h
// 
// Desc: Contains classes for property-setting dialogs, to be used with
//       the DES transition object.
//      
// Copyright (c) 2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#pragma once

// If building this sample with Visual C++ 6.0's headers, this
// include generates several warnings.  Suppress the warnings, since
// this header is beyond our control.
#pragma warning(push, 1)
#include <deque>
#pragma warning(pop)

// Struct to hold SMPTE wipe names and numbers

struct WipeNumInfo {
    int num;
    TCHAR* szName;
};



/*******************************************************************
 *
 *  CBasePropSetter Class  
 *
 *  Base class for managing a property dialog. To use:
 *  - Override OnReceiveMsg, OnInitDialog, OnOK
 *  - Set the m_nID member in the derived class constructor.
 *
 *******************************************************************/

class CBasePropSetter
{

protected:

    deque<CComBSTR> prop_list;  // List of properties
    deque<CComBSTR> value_list; // List of values

    CComPtr<IPropertySetter> m_pProp;   // Property-setter
    CComPtr<IAMTimelineObj> m_pObj;     // Object to receive the properties.

    HINSTANCE   m_hinst;    // application instance
    HWND        m_hwnd;     // parent window
    HWND        m_hDlg;     // this dialog window
    int         m_nID;      // Resource ID of the dialog window 
                            // (Set this in the constructor!)

protected:

    static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
    virtual INT_PTR OnReceiveMsg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        return FALSE;
    }

    virtual HRESULT OnInitDialog() { return S_OK; }
    virtual HRESULT OnOK() { return S_OK; }
    virtual HRESULT OnCancel() { return S_OK; }

    // Methods to add, remove, update properties
    int Count() { return ((int) prop_list.size()); }

    void Add(const TCHAR* tszProp, const TCHAR* tszValue);
    void Update(int ix, const TCHAR* tszProp, const TCHAR* tszValue);
    void Remove(int ix);
    void RemoveAll();

    BSTR& Name(int ix) { return prop_list[ix].m_str; }
    BSTR& Val(int ix) { return value_list[ix].m_str; }

    // Find a property value by name
    HRESULT FindVal(const TCHAR* szName, BSTR *pbstrVal);

    // Copy a property into a window
    HRESULT SetWindowTextFromProp(HWND hwnd, const TCHAR* szName);

    // Set a property from the text in a window.
    HRESULT AddPropFromWindowText(HWND hwnd, const TCHAR* szName);

    // Set and retrieve numeric (DWORD) properties
    HRESULT GetNumericVal(const TCHAR *szName, DWORD *pdwVal, int iBase);
    HRESULT SetNumericVal(const TCHAR *szName, DWORD dwVal, int iBase);

public:
    CBasePropSetter(IAMTimelineObj *pObject);
    virtual ~CBasePropSetter();

    HRESULT SetProperties();
    BOOL ShowDialog(HINSTANCE hinst, HWND hwnd);
};


/*******************************************************************
 *
 *  CPropSetter Class  -- Generic property setter, use as the default.
 *
 *******************************************************************/


class CPropSetter : public CBasePropSetter
{

protected:

    INT_PTR OnReceiveMsg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
    HRESULT OnInitDialog();

    // Dialog proc for the edit page ...
    static INT_PTR CALLBACK EditDlgProc(HWND hDlg, UINT msg, WPARAM wparam, LPARAM lParam);

    int  m_iSelection; // which property to edit?

public:
    CPropSetter(IAMTimelineObj *pObj)
        : CBasePropSetter(pObj)
    {
        m_iSelection = LB_ERR;
    }
};


/*******************************************************************
 *
 *  CWipeProp Class  -- SMPTE Wipe properties
 *
 *******************************************************************/


class CWipeProp : public CBasePropSetter
{
private:

    DWORD m_dwBorderColor;

protected:

    INT_PTR OnReceiveMsg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
    HRESULT OnInitDialog();
    HRESULT OnOK();

public:
    CWipeProp(IAMTimelineObj *pObj);
};


/************************************************************
 *
 *  CKeyProp Class  -- Properties for chroma/alpha keying
 *
 ************************************************************/

class CKeyProp : public CBasePropSetter
{

private:

    DWORD m_dwColor;  // RGB color
    int   m_iKey;   // Key type

    void UpdateControls();

protected:

    INT_PTR OnReceiveMsg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
    HRESULT OnInitDialog();
    HRESULT OnOK();

public:
    CKeyProp(IAMTimelineObj *pObj);
};


/******************************************************************
 *
 *  CPipProp Class  -- Compositor (Picture-in-Picture) properties
 *
 *  A picture-in-picture transition is defined by the two rectangles,
 *  source (how much of the source image to display) and destination
 *  (positioned of the PiP within the video frame). 
 
 *  This dialog uses two rectangle widgets, which the user can resize
 *  to set the source and destination rectangles. Click the widget to
 *  select it, then grab the anchors on the rectangle corners to resize
 *  the rectangle.
 *
 ******************************************************************/

class CPipProp : public CBasePropSetter
{

private:

    // Sizeable rectangle widget
    class Sizer : public RECT
    {

    private:
        RECT m_Anchor[4];   // Anchors for the user to grab

        void SetAnchors();
        void SetRegion();

    public:

        RECT m_BoundingRect;  // Bounding rectangle - can't go outside this

        bool m_bSelected;   // User selected us?
        bool m_bGrabbed;    // User is grabbing an anchor to resize us?
        bool m_bInHotZone;  // Mouse is hovering over a hot zone (any anchor)

        int m_iGrabbedAnchor;  // Which anchor is grabbed (only if m_bGrabbed is true)

        HRGN m_hRgn;        // Region to redraw

    public:
        Sizer();
        ~Sizer();

        void Init(RECT& rcBound, RECT& rcVid, RECT& rcTarget);
        void Draw(HDC hdc);

        BOOL TestHit(int x, int y);
        BOOL TestMouseMove(int x, int y);
        void Unclick() { m_bGrabbed = false; }

        // Maps our rectangle by projecting the bounding rectangle onto rcTarget
        void MapToRect(RECT& rcTarget, RECT *pResult);
    };

    Sizer m_Src;    // Source rectangle
    Sizer m_Dest;   // Destination rectangle

protected:

    INT_PTR OnReceiveMsg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
    HRESULT OnInitDialog();
    HRESULT OnOK();
    void OnPaint();
    void Repaint();
    void Repaint(HRGN rgn);


public:
    CPipProp(IAMTimelineObj *pObj);

};



