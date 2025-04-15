//------------------------------------------------------------------------------
// File: PropSetter.cpp
//
// Desc: DirectShow sample code - TransViewer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "Transviewer.h"
#include "PropSetter.h"
#include <commdlg.h>

// This array contains human-readable names for the SMPTE wipes.
extern WipeNumInfo g_SMPTEWipes[];
extern int g_iNumWipes;

// Quiet warnings about unreachable code in dialog procedures
#pragma warning(disable: 4702)


//-----------------------------------------------------------------------------
// Name: AllocGetWindowText
// Desc: Helper function to get text from a window.
//
// This function allocates a buffer and returns it in pszText. The caller must
// call CoTaskMemFree on the buffer.
//-----------------------------------------------------------------------------

void AllocGetWindowText(HWND hwnd, TCHAR **pszText)
{
    *pszText = NULL;

    int len = GetWindowTextLength(hwnd) + 1;  // Account for trailing '\0' character 
    if (len > 1) 
    {
        *pszText = (TCHAR*)CoTaskMemAlloc(sizeof(TCHAR) * len);
        
        if (*pszText)
            GetWindowText(hwnd, *pszText, len);
    }
}


/************************************************************
 *
 * CBasePropSetter Class - base property setter class
 *
 ************************************************************/

CBasePropSetter::CBasePropSetter(IAMTimelineObj *pObject)
               : m_pObj(pObject), 
                 m_nID(IDD_PROPERTY)
{
    // There is a bug in the IPropertySetter::ClearProps method (in DirectX 8.0/8.1)
    // So if the object already has a property setter, we grab the existing
    // properties and get rid of the property setter. Then we create a new one.
    
    CComPtr<IPropertySetter> pPropTmp;
    HRESULT hr = m_pObj->GetPropertySetter(&pPropTmp);

    // The object has a property setter, so get the properties.
    if (SUCCEEDED(hr) && pPropTmp)
    {
        DEXTER_PARAM *pParam;
        DEXTER_VALUE *pValue;
        LONG count = 0;
        
        hr = pPropTmp->GetProps(&count, &pParam, &pValue);

        LONG num = 0;
        for (LONG i = 0; i < count; i++)
        {
            // Note - I am intentionally using only the first
            // value for each property!

            CComBSTR prop(pParam[i].Name);
            CComBSTR val(pValue[num].v.bstrVal);

            prop_list.push_back(prop);
            value_list.push_back(val);

            num += pParam[i].nValues;
        }
    }

    // Make a new property setter -- but don't set it on the object yet.
    hr = m_pProp.CoCreateInstance(CLSID_PropertySetter);

    if (FAILED(hr))
    {
        throw new hresult_exception(hr);
    }
}


CBasePropSetter::~CBasePropSetter()
{
    RemoveAll();
}


//-----------------------------------------------------------------------------
// Name: SetProperties 
// Desc: Move the properies from the lists into the transition object.
//-----------------------------------------------------------------------------

HRESULT CBasePropSetter::SetProperties()
{
    HRESULT hr;
    
    if (!prop_list.empty())
    {
        // Release the old property setter, if any.
        m_pObj->SetPropertySetter(NULL);

        // Set the property setter.
        m_pObj->SetPropertySetter(m_pProp);

        // Iterate through both lists.
        deque<CComBSTR>::iterator prop_iter, val_iter;
        
        val_iter = value_list.begin();
        
        for (prop_iter = prop_list.begin(); 
             prop_iter != prop_list.end(); 
             ++prop_iter, ++val_iter)
        {
            DEXTER_PARAM param;
            DEXTER_VALUE value;
            
            // Initialize the parameter. 
            param.Name = (*prop_iter).m_str;
            param.dispID = 0;
            param.nValues = 1;
            
            value.v.vt = VT_BSTR;
            value.v.bstrVal = (*val_iter).m_str;
            value.rt = 0;
            value.dwInterp = DEXTERF_JUMP;
            
            hr = m_pProp->AddProp(param, &value);

            // Nothing to de-allocate because we used the raw pointers
        }
    }

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: RemoveAll 
// Desc: Clear all properties.
//-----------------------------------------------------------------------------

void CBasePropSetter::RemoveAll()
{
    prop_list.clear();
    value_list.clear();
}


//-----------------------------------------------------------------------------
// Name: Remove 
// Desc: Remove one property, by index value
//-----------------------------------------------------------------------------

void CBasePropSetter::Remove(int ix)
{
    prop_list.erase(prop_list.begin() + ix);
    value_list.erase(value_list.begin() + ix);
}


//-----------------------------------------------------------------------------
// Name: Add 
// Desc: Add a new property
//
// tszProp: Name of the property
// tszVal:  Value of the property
//-----------------------------------------------------------------------------

void CBasePropSetter::Add(const TCHAR* tszProp, const TCHAR* tszValue)
{
    CComBSTR prop(tszProp);
    CComBSTR val(tszValue);

    prop_list.push_back(prop);
    value_list.push_back(val);
}


//-----------------------------------------------------------------------------
// Name: Update
// Desc: Update an existing property
//
// ix:      Index of the property to update
// tszProp: Name of the property
// tszVal:  Value of the property
//-----------------------------------------------------------------------------

void CBasePropSetter::Update(int ix, const TCHAR* tszProp, const TCHAR* tszValue)
{
    CComBSTR prop(tszProp);
    CComBSTR val(tszValue);

    prop_list[ix] = prop;
    value_list[ix] = val;
}


//-----------------------------------------------------------------------------
// Name: FindVal
// Desc: Find a property by name, and return the value.
//
// tszProp:  Name of the property
// pbstrVal: Receives the value of the property (if found). 
//           Caller must release the returned string, by calling SysFreeString
//-----------------------------------------------------------------------------

HRESULT CBasePropSetter::FindVal(const TCHAR* szName, BSTR *pbstrVal)
{
    CComBSTR bstrName(szName);

    deque<CComBSTR>::iterator prop_iter, val_iter;
    
    val_iter = value_list.begin();
    
    for (prop_iter = prop_list.begin(); 
         prop_iter != prop_list.end(); 
         ++prop_iter, ++val_iter)
    {
        if ((*prop_iter) == bstrName)
        {
            *pbstrVal = (*val_iter).Copy();
            return S_OK;
        }
    }

    *pbstrVal = 0;
    return E_FAIL;
}


//-----------------------------------------------------------------------------
// Name: SetWindowTextFromProp
// Desc: Sets the text of window to the value of a specified property.
//
// hwnd:   Handle to the window
// szName: Name of the property.
//-----------------------------------------------------------------------------

HRESULT CBasePropSetter::SetWindowTextFromProp(HWND hwnd, const TCHAR* szName)
{
    USES_CONVERSION;
    BSTR bstrVal;

    HRESULT hr = FindVal(szName, &bstrVal);
    if (SUCCEEDED(hr))
    {
        SetWindowText(hwnd, OLE2T(bstrVal));
        SysFreeString(bstrVal);
    }

    return hr;
}


//-----------------------------------------------------------------------------
// Name: AddPropFromWindowText
// Desc: Adds a new property, using a window's text as the property value.
//
// hwnd:   Handle to the window
// szName: Name of the property to add.
//-----------------------------------------------------------------------------

HRESULT CBasePropSetter::AddPropFromWindowText(HWND hwnd, const TCHAR* szName)
{
   TCHAR *tszProp = 0;
                
    AllocGetWindowText(hwnd, &tszProp);

    if (tszProp == 0)
    {
        return E_OUTOFMEMORY;
    }

    Add(szName, tszProp);
    CoTaskMemFree(tszProp);
    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: GetNumericVal
// Desc: Gets the value of a property, for numeric properties.
//
// szName: Name of the property
// pdwVal: Receives the value
// iBase:  Radix (10 or 16)
//-----------------------------------------------------------------------------

HRESULT CBasePropSetter::GetNumericVal(const TCHAR *szName, DWORD *pdwVal, int iBase = 10)
{
    if ((iBase != 10) && (iBase != 16))
    {
        return E_INVALIDARG;
    }

    BSTR bstrVal;

    HRESULT hr = FindVal(szName, &bstrVal);
    if (SUCCEEDED(hr))
    {
        USES_CONVERSION;

        TCHAR* tstr = OLE2T(bstrVal);
        if (!tstr)
            return E_FAIL;
 
#ifdef UNICODE 
        char strTmp[16]; 
        wcstombs(strTmp, (const wchar_t *) tstr, sizeof(strTmp)); 
        (*pdwVal) = strtol(strTmp, 0, iBase); 
#else 
        (*pdwVal) = strtol(tstr, 0, iBase); 
#endif 

        SysFreeString(bstrVal);    
    }

    return hr;
}


//-----------------------------------------------------------------------------
// Name: SetNumericVal
// Desc: Sets a numeric value for a property
//
// szName: Name of the property
// dwVal:  Value of the property
// iBase:  Radix (10 or 16)
//-----------------------------------------------------------------------------

HRESULT CBasePropSetter::SetNumericVal(const TCHAR *szName, DWORD dwVal, int iBase = 10)
{
    TCHAR szVal[16];

    if (iBase == 16)
    {
        wsprintf(szVal, TEXT("%#06X\0"), dwVal);
    }
    else if (iBase == 10)
    {
        wsprintf(szVal, TEXT("%d\0"), dwVal);
    }
    else
    {
        return E_INVALIDARG;
    }

    Add(szName, szVal); 
    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: ShowDialog()
// Desc: Offers a dialog for the user to set properties on the transition.
//-----------------------------------------------------------------------------
BOOL CBasePropSetter::ShowDialog(HINSTANCE hinst, HWND hwnd)
{
    // Cache these...
    m_hinst = hinst;
    m_hwnd = hwnd;

    // Show the dialog.
    return (IDOK == DialogBoxParam(hinst, MAKEINTRESOURCE(m_nID), 
            hwnd, DialogProc, (LPARAM)this));
}


//-----------------------------------------------------------------------------
// Name: PropertyDlgProc()
// Desc: DialogProc for the property dialog. This is a static class method.
//
// lParam: Pointer to the CBasePropSetter object. The object specifies this in
//         ShowDialog() when it calls DialogBoxParam. We store it as user data
//         in the window, for next time around. (Note: The DirectShow 
//         CBasePropertyPage class uses the same technique.)
//-----------------------------------------------------------------------------
INT_PTR CALLBACK CBasePropSetter::DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    CBasePropSetter *pProp = 0;  // Pointer to the prop 

    if (msg == WM_INITDIALOG)
    {
        // Get the pointer to the prop setter object and store it in 
        // the window's user data

        SetWindowLongPtr(hDlg, DWLP_USER, lParam);

        pProp = (CBasePropSetter*)lParam;
        if (pProp)
        {
            pProp->m_hDlg = hDlg;
            pProp->OnInitDialog();
        }

        return FALSE;
    }


    // Get the prop setter object from the window's user data
    pProp = (CBasePropSetter*) GetWindowLongPtr(hDlg, DWLP_USER);

    if (msg == WM_COMMAND)
    {
        switch (LOWORD(wParam))
        {
            case IDOK:
                if (pProp) 
                    pProp->OnOK();
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;

            case IDCANCEL:
                if (pProp) 
                    pProp->OnCancel();
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
        }
    }

    // Default: Let the object handle the message.
    if (pProp) 
    {
        return pProp->OnReceiveMsg(hDlg, msg, wParam, lParam);
    }
    else 
    {
        return FALSE;
    }
}


/************************************************************
 *
 *      CPropSetter Class  -- generic property setter
 *
 ************************************************************/

HRESULT CPropSetter::OnInitDialog()
{
    USES_CONVERSION;

    // Stick all the property names in a list
    HWND hList = GetDlgItem(m_hDlg, IDC_PROPLIST);

    deque<CComBSTR>::iterator iter;

    for (iter = prop_list.begin(); iter != prop_list.end(); ++iter)
    {
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)OLE2T(*iter));
    }
    
    SendMessage(hList, LB_SETCURSEL, 0, 0); 
    return S_OK;
}


INT_PTR CPropSetter::OnReceiveMsg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) 
    {
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDC_ADDNEW:
                    m_iSelection = LB_ERR;
                    DialogBoxParam(m_hinst, MAKEINTRESOURCE(IDD_EDITPROP), hDlg, 
                                   EditDlgProc, (LPARAM)this);
                    break;

                case IDC_EDIT:
                    m_iSelection = (int) SendMessage(GetDlgItem(hDlg, IDC_PROPLIST), 
                                                     LB_GETCURSEL, 0, 0);
                    if (m_iSelection == LB_ERR) {
                        MessageBox(hDlg, TEXT("No property is selected."), 
                                   TEXT("Error"), MB_OK | MB_ICONWARNING);
                    }
                    else {
                        DialogBoxParam(m_hinst, MAKEINTRESOURCE(IDD_EDITPROP), hDlg, 
                                       EditDlgProc, (LPARAM)this);
                    }

                    break;

                case IDC_REMOVE:

                    m_iSelection  = (int) SendMessage(GetDlgItem(hDlg, IDC_PROPLIST), 
                                                      LB_GETCURSEL, 0, 0);
                    if (m_iSelection == LB_ERR) {
                        MessageBox(hDlg, TEXT("No property is selected."), TEXT("Error"), 
                                   MB_OK | MB_ICONWARNING);
                    }
                    else {
                        HWND hList = GetDlgItem(hDlg, IDC_PROPLIST);
                        SendMessage(hList, LB_DELETESTRING, m_iSelection, 0);
                        SendMessage(hList, LB_SETCURSEL, 0, m_iSelection);

                        Remove(m_iSelection);
                        EnableWindow(GetDlgItem(hDlg, IDC_ADDNEW), TRUE);
                    }
                    break;
            }
        }

        default:
            return FALSE;  // Did not handle message
    }

    return TRUE;
}


//-----------------------------------------------------------------------------
// Name: PropertyDlgProc()
// Desc: DialogProc for the add/edit dialog.
//
// lParam: Pointer to the CPropSetter object
//
// If this->m_iSelection is LB_ERR, the user is adding a new property. 
// Otherwise, it specifies which property to edit.
//-----------------------------------------------------------------------------

INT_PTR CALLBACK CPropSetter::EditDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hList,     // Listbox in the parent dialog
                hEditProp, // Property Name edit box
                hEditVal;  // Property Value edit box 

    static int iSelection; // Current selection in the listbox.
    static CPropSetter *pProp;

    switch (msg) 
    {
        case WM_INITDIALOG:
        {
            pProp = (CPropSetter*)lParam;

            hList = GetDlgItem(GetParent(hDlg), IDC_PROPLIST);
            hEditProp = GetDlgItem(hDlg, IDC_PROPNAME);
            hEditVal = GetDlgItem(hDlg, IDC_PROPVAL);
            iSelection = pProp->m_iSelection;

            if (iSelection == LB_ERR) 
            {
                // We're adding a new property.
                SetWindowText(hDlg, TEXT("Add Property"));
            }
            else 
            {
                // We're editing an existing property. Display the name/value
                USES_CONVERSION;
                SetWindowText(hDlg, TEXT("Edit Property"));
                SetWindowText(hEditProp, OLE2T(pProp->Name(iSelection)));
                SetWindowText(hEditVal, OLE2T(pProp->Val(iSelection)));
            }

            return FALSE;
        }
        
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDOK:   // Accept property change or new property
                {
                    TCHAR *tszProp, *tszValue;
                
                    AllocGetWindowText(hEditProp, &tszProp);
                    AllocGetWindowText(hEditVal, &tszValue);
                
                    if (tszProp && tszValue)
                    {
                        if (iSelection == LB_ERR) // Add a new property
                        {
                            pProp->Add(tszProp, tszValue);

                            SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)tszProp);
                            SendMessage(hList, LB_SETCURSEL, pProp->Count() - 1, 0);
                        }
                        else    // Update an existing property
                        {
                            pProp->Update(iSelection, tszProp, tszValue);

                            SendMessage(hList, LB_DELETESTRING, iSelection, 0);
                            SendMessage(hList, LB_INSERTSTRING, iSelection, (LPARAM)tszProp);
                            SendMessage(hList, LB_SETCURSEL, iSelection, 0); 
                        }
                    }

                    CoTaskMemFree(tszProp);
                    CoTaskMemFree(tszValue);
                
                }
                // Fall through

                case IDCANCEL:
                    EndDialog( hDlg, LOWORD(wParam) );
                    break;
            }
        }
        
        default:
            return FALSE;  // Did not handle message
    }

    return TRUE;
}


/************************************************************
 *
 *  CWipeProp Class  -- Property setter for SMPTE wipes
 *
 ************************************************************/

CWipeProp::CWipeProp(IAMTimelineObj *pObj)
         : CBasePropSetter(pObj), m_dwBorderColor(0)
{
    this->m_nID = IDD_SMPTE;
}


HRESULT CWipeProp::OnInitDialog()
{
    // Get the current SMPTE wipe number.
    DWORD dwWipeNum = 0;
    HRESULT hr = GetNumericVal(TEXT("MaskNum"), &dwWipeNum);

    // Populate the list of SMPTE wipe names
    int iSel = 0;

    for (int i = 0; i < g_iNumWipes; i++)
    {
        SendDlgItemMessage(m_hDlg, IDC_SMPTE_MASKNUM, CB_ADDSTRING, 
            0, (LPARAM)g_SMPTEWipes[i].szName);

        // This one matches the current MaskNum property ... 
        // remember this value for when we set the list box selection.
        if (g_SMPTEWipes[i].num == (int) dwWipeNum)
        {
            iSel = i;
        }

    }

    // Set the list box selection.
    SendDlgItemMessage(m_hDlg, IDC_SMPTE_MASKNUM, CB_SETCURSEL, iSel, 0);

    // Set the remaining properties...
    SetWindowTextFromProp(GetDlgItem(m_hDlg, IDC_SMPTE_SOFTNESS), TEXT("BorderSoftness"));
    SetWindowTextFromProp(GetDlgItem(m_hDlg, IDC_SMPTE_WIDTH), TEXT("BorderWidth"));

    SetWindowTextFromProp(GetDlgItem(m_hDlg, IDC_SMPTE_OFFSETX), TEXT("OffsetX"));
    SetWindowTextFromProp(GetDlgItem(m_hDlg, IDC_SMPTE_OFFSETY), TEXT("OffsetY"));
    SetWindowTextFromProp(GetDlgItem(m_hDlg, IDC_SMPTE_REPLICATEX), TEXT("ReplicateX"));
    SetWindowTextFromProp(GetDlgItem(m_hDlg, IDC_SMPTE_REPLICATEY), TEXT("ReplicateY"));

    // The next two are floating-point values. A better UI would take % values
    // from 0 - 100 and convert to 0.0 - 1.0.

    SetWindowTextFromProp(GetDlgItem(m_hDlg, IDC_SMPTE_SCALEX), TEXT("ScaleX"));
    SetWindowTextFromProp(GetDlgItem(m_hDlg, IDC_SMPTE_SCALEY), TEXT("ScaleY"));

    // For the color, we convert the string "0xRRGGBB" to a DWORD, convert
    // to B-G-R format, and use that to paint the color swatch.

    DWORD dwColor = 0;
    hr = GetNumericVal(TEXT("BorderColor"), &dwColor, 16);
    if (SUCCEEDED(hr))
    {
        m_dwBorderColor = SwapRGB(dwColor); 
    }

    return S_OK;
}


HRESULT CWipeProp::OnOK()  
{
    RemoveAll();
    
    // Look up the correct 'MaskNum' property from the list box selection.
    int iSel = (int) SendDlgItemMessage(m_hDlg, IDC_SMPTE_MASKNUM, CB_GETCURSEL, 0, 0);
    if (iSel != LB_ERR)
    {
        SetNumericVal(TEXT("MaskNum"), g_SMPTEWipes[iSel].num);
    }

    AddPropFromWindowText(GetDlgItem(m_hDlg, IDC_SMPTE_SOFTNESS), TEXT("BorderSoftness"));
    AddPropFromWindowText(GetDlgItem(m_hDlg, IDC_SMPTE_WIDTH), TEXT("BorderWidth"));
    
    AddPropFromWindowText(GetDlgItem(m_hDlg, IDC_SMPTE_OFFSETX), TEXT("OffsetX"));
    AddPropFromWindowText(GetDlgItem(m_hDlg, IDC_SMPTE_OFFSETY), TEXT("OffsetY"));
    AddPropFromWindowText(GetDlgItem(m_hDlg, IDC_SMPTE_REPLICATEX), TEXT("ReplicateX"));
    AddPropFromWindowText(GetDlgItem(m_hDlg, IDC_SMPTE_REPLICATEY), TEXT("ReplicateY"));
    
    // The next two are floating-point values. A better UI would take % values
    // from 0 - 100 and convert to 0.0 - 1.0.
    
    AddPropFromWindowText(GetDlgItem(m_hDlg, IDC_SMPTE_SCALEX), TEXT("ScaleX"));
    AddPropFromWindowText(GetDlgItem(m_hDlg, IDC_SMPTE_SCALEY), TEXT("ScaleY"));
    
    // For the color, convert the B-G-R DWORD value to an "0xRRGGBB" string
    
    SetNumericVal(TEXT("BorderColor"), SwapRGB(m_dwBorderColor), 16);
    
    return S_OK;
}


INT_PTR CWipeProp::OnReceiveMsg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static COLORREF acrCustomClr[16];

    switch (msg)
    {
        case WM_DRAWITEM:
            // Paint the color swatch
            if (wParam == IDC_SMPTE_COLOR)
            {
                HBRUSH solidBrush = CreateSolidBrush(m_dwBorderColor);

                DRAWITEMSTRUCT *pDraw = (DRAWITEMSTRUCT*)lParam;
                FillRect(pDraw->hDC, &pDraw->rcItem, solidBrush);
                FrameRect(pDraw->hDC, &pDraw->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));

                DeleteObject(solidBrush);

                return TRUE;
            }
            break;

        case WM_COMMAND:        
            switch (LOWORD(wParam))
            {
                case IDC_SMPTE_PICK_COLOR:
                {
                    // Show the Choose Color dialog to pick a new color swatch
                    CHOOSECOLOR cc;
        
                    ZeroMemory(&cc, sizeof(CHOOSECOLOR));
                    cc.lStructSize = sizeof(CHOOSECOLOR);
                    cc.hwndOwner = m_hDlg;
                    cc.lpCustColors = (LPDWORD)acrCustomClr;
                    cc.Flags = CC_RGBINIT;
                    cc.rgbResult = m_dwBorderColor;
        
                    if (ChooseColor(&cc))
                    {
                        m_dwBorderColor = cc.rgbResult;
                        InvalidateRect(GetDlgItem(hDlg, IDC_SMPTE_COLOR), 0, FALSE);
                    }
                }
                return TRUE;

            } // inner switch            
            break;
    }

    // default
    return FALSE;
}


/************************************************************
 *
 *  CKeyProp Class  -- Property setter for the Key transition
 *
 ************************************************************/

CKeyProp::CKeyProp(IAMTimelineObj *pObj)
        : CBasePropSetter(pObj), m_dwColor(0), m_iKey(0)
{

    this->m_nID = IDD_KEY;
}


HRESULT CKeyProp::OnInitDialog()
{
    HRESULT hr;

    // KeyType Property
    DWORD dwKey = DXTKEY_RGB;
    hr = GetNumericVal(TEXT("KeyType"), &dwKey);
    if (SUCCEEDED(hr))
    {
        m_iKey = dwKey;
    }

    // Hue Property
    SetWindowTextFromProp(GetDlgItem(m_hDlg, IDC_KEY_HUE), TEXT("Hue"));

    // Luminance Property
    SetWindowTextFromProp(GetDlgItem(m_hDlg, IDC_KEY_LUMA), TEXT("Luminance"));

    // Similarity Property
    SetWindowTextFromProp(GetDlgItem(m_hDlg, IDC_KEY_SIMILAR), TEXT("Similarity"));

    // RGB Property
    DWORD dwColor = 0;
    hr = GetNumericVal(TEXT("RGB"), &dwColor, 16);
    if (SUCCEEDED(hr))
    {
        m_dwColor = SwapRGB(dwColor); 
    }

    // Invert Property
    DWORD dwInvert = 0;
    hr = GetNumericVal(TEXT("Invert"), &dwInvert);
    if (SUCCEEDED(hr))
    {
        CheckDlgButton(m_hDlg, IDC_KEY_INVERT, (dwInvert ? BST_CHECKED : BST_UNCHECKED));
    }

    // Populate the list of key types in order of the key-type enums

    HWND hList = GetDlgItem(m_hDlg, IDC_KEY_TYPE);

    const int iNumKeys = 5;
    TCHAR* szKeyNames[] = {
        TEXT("Chroma"), TEXT("Non-Red"), TEXT("Luminance"), TEXT("Alpha"), TEXT("Hue")
    };

    for (int i = 0; i < iNumKeys; i++)
    {
        SendMessage(hList, CB_ADDSTRING, 0, (LPARAM)szKeyNames[i]);
    }

    // Select the current key type
    SendMessage(hList, CB_SETCURSEL, m_iKey, 0);

    UpdateControls();

    return S_OK;
}


HRESULT CKeyProp::OnOK()
{
    RemoveAll();

    // Set properties
    AddPropFromWindowText(GetDlgItem(m_hDlg, IDC_KEY_HUE), TEXT("Hue"));
    AddPropFromWindowText(GetDlgItem(m_hDlg, IDC_KEY_LUMA), TEXT("Luminance"));
    AddPropFromWindowText(GetDlgItem(m_hDlg, IDC_KEY_SIMILAR), TEXT("Similarity"));

    SetNumericVal(TEXT("RGB"), SwapRGB(m_dwColor), 16);
    SetNumericVal(TEXT("KeyType"), m_iKey);

    if (IsDlgButtonChecked(m_hDlg, IDC_KEY_INVERT) == BST_CHECKED)
    {
        SetNumericVal(TEXT("Invert"), TRUE);
    }
    else
    {
        SetNumericVal(TEXT("Invert"), FALSE);
    }

   return S_OK;
}


INT_PTR CKeyProp::OnReceiveMsg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static COLORREF acrCustomClr[16];

    switch (msg)
    {
        case WM_DRAWITEM:

            // Paint the color swatch
            if (wParam == IDC_KEY_COLOR)
            {
                DRAWITEMSTRUCT *pDraw = (DRAWITEMSTRUCT*)lParam;
            
                if (IsWindowEnabled(GetDlgItem(m_hDlg, IDC_KEY_PICK_COLOR)))
                {
                    HBRUSH solidBrush = CreateSolidBrush(m_dwColor);
                    FillRect(pDraw->hDC, &pDraw->rcItem, solidBrush);
                    DeleteObject(solidBrush);
                }
                else  // Color is disabled for this key type
                {
                    // Gray the color swatch
                    FillRect(pDraw->hDC, &pDraw->rcItem, (HBRUSH)GetStockObject(LTGRAY_BRUSH));

                    // 'X' out the swatch
                    MoveToEx(pDraw->hDC, 0, 0, 0);
                    LineTo(pDraw->hDC, pDraw->rcItem.right, pDraw->rcItem.bottom);
                    MoveToEx(pDraw->hDC, pDraw->rcItem.right, 0, 0);
                    LineTo(pDraw->hDC, 0, pDraw->rcItem.bottom);
                }

                FrameRect(pDraw->hDC, &pDraw->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));
                return TRUE;
            }

            break;

        case WM_COMMAND:        
            switch (LOWORD(wParam))
            {
                case IDC_KEY_TYPE:
                    if (HIWORD(wParam) == CBN_SELCHANGE)
                    {
                        m_iKey = (int) SendMessage(GetDlgItem(m_hDlg, IDC_KEY_TYPE), 
                                                   CB_GETCURSEL, 0, 0);
                        if (m_iKey== CB_ERR)
                        {
                            m_iKey = DXTKEY_RGB;
                        }

                        UpdateControls();
                        return TRUE;
                    }
                    break;

                case IDC_KEY_PICK_COLOR:
                {
                    CHOOSECOLOR cc;
                
                    ZeroMemory(&cc, sizeof(CHOOSECOLOR));
                    cc.lStructSize = sizeof(CHOOSECOLOR);
                    cc.hwndOwner = m_hDlg;
                    cc.lpCustColors = (LPDWORD)acrCustomClr;
                    cc.Flags = CC_RGBINIT;
                    cc.rgbResult = m_dwColor;
                
                    if (ChooseColor(&cc))
                    {
                        m_dwColor = cc.rgbResult;
                        InvalidateRect(GetDlgItem(hDlg, IDC_KEY_COLOR), 0, FALSE);
                    }
                }

                return TRUE;

            } // inner switch            
            break;
    }

    // default
    return FALSE;
}


void CKeyProp::UpdateControls()
{
    // Not all of the key types support all of the properties on this transition.
    // Decide which controls need to be enabled ...

    bool bHue = false, bInvert = false, bLuma = false, bRGB = false, bSim = false;

    switch (m_iKey)
    {
        case DXTKEY_RGB:  // (Chroma)
            bInvert = true;
            bSim = true;
            bRGB = true;
            break;

        case DXTKEY_NONRED:
            bInvert = true;
            bSim = true;
            break;

        case DXTKEY_LUMINANCE:
            bInvert = true;
            bLuma = true;
            break;

        case DXTKEY_ALPHA:  // No properties apply to alpha key
            break;

        case DXTKEY_HUE:
            bHue = true;
            bInvert = true;
            break;   
    }

    EnableWindow(GetDlgItem(m_hDlg, IDC_KEY_HUE), bHue);
    EnableWindow(GetDlgItem(m_hDlg, IDC_KEY_INVERT), bInvert);
    EnableWindow(GetDlgItem(m_hDlg, IDC_KEY_LUMA), bLuma);
    EnableWindow(GetDlgItem(m_hDlg, IDC_KEY_PICK_COLOR), bRGB);
    EnableWindow(GetDlgItem(m_hDlg, IDC_KEY_SIMILAR), bSim);

    InvalidateRect(m_hDlg, 0, FALSE);
}


/**********************************************************
 *
 *  CPipProp::Sizer Class 
 *
 *  Sizeable widget control, used by the CPipProp class
 *
 **********************************************************/

CPipProp::Sizer::Sizer()
    : m_bSelected(false), m_bGrabbed(false), m_bInHotZone(false), m_hRgn(0)
{ 

}

CPipProp::Sizer::~Sizer()
{
    if (m_hRgn)
    {
        DeleteObject(m_hRgn);
    }
}


//-----------------------------------------------------------------------------
// Name: MapToRect
// Desc: Maps the Sizer rectangle to a destination rectangle, by projecting
//       the bounding rectangle onto the destination rect and scaling
//
// rcTarget: The destination rectangle. Scaling will be relative to this rectangle.
//           This rectangle must be in client coordinates, ie left = 0, top = 0
//
// pResult:  Receives the scaled rectangle.
//-----------------------------------------------------------------------------

void CPipProp::Sizer::MapToRect(RECT& rcTarget, RECT *pResult)
{
    _ASSERTE((rcTarget.left == 0) && (rcTarget.top == 0));

    LONG lWidth = m_BoundingRect.right - m_BoundingRect.left;
    LONG lHeight = m_BoundingRect.bottom - m_BoundingRect.top;

    float scaleX = (float)(rcTarget.right) / lWidth;
    float scaleY = (float)(rcTarget.bottom) / lHeight;

    // Normalize to the bounding rectangle

    int x1 = left - m_BoundingRect.left, y1 = top - m_BoundingRect.top,
        x2 = right - m_BoundingRect.left, y2 = bottom - m_BoundingRect.top;
    
    // Scale
    SetRect(pResult, (int)(x1 * scaleX), (int)(y1 * scaleY), 
                     (int)(x2 * scaleX), (int)(y2 * scaleY));
}

//-----------------------------------------------------------------------------
// Name: Init
// Desc: Initializes the Sizer rectangle and the bounding rectangle. 
//
// rcBound:  Specifies the bounding rectangle.
// rcVid:    Specifies the original video rectangle
// rcTarget: Specifies the original target rectangle (sub rectangle within rcVid)
//
// Note:     This method performs the inverse operation as MapToRect. It finds
//           the Sizer rectangle by projecting rcVid onto rcBound and scaling
//           rcTarget accordingly.
//-----------------------------------------------------------------------------

void CPipProp::Sizer::Init(RECT& rcBound, RECT& rcVid, RECT& rcTarget)
{
    _ASSERTE((rcVid.left == 0) && (rcVid.top == 0));
    
    CopyRect(&m_BoundingRect, &rcBound);

    float fWidth = (float)(m_BoundingRect.right - m_BoundingRect.left);
    float fHeight = (float)(m_BoundingRect.bottom - m_BoundingRect.top);

    float scaleX = fWidth / rcVid.right,
          scaleY = fHeight / rcVid.bottom;

    // Scale
    int x1 = (int)(scaleX * rcTarget.left), y1 = (int)(scaleY * rcTarget.top),
        x2 = (int)(scaleX * rcTarget.right), y2 = (int)(scaleY * rcTarget.bottom);

    // Normalize to the bounding rectangle
    SetRect(this, x1 + rcBound.left, y1 + rcBound.top, 
            x2 + rcBound.left, y2 + rcBound.top);
    
    SetAnchors();
    SetRegion();
} 


//-----------------------------------------------------------------------------
// Name: SetRegion
// Desc: Sets the redraw region, equal to the Sizer rect plus the anchors
//-----------------------------------------------------------------------------

void CPipProp::Sizer::SetRegion()
{
    if (m_hRgn)
    {
        DeleteObject(m_hRgn);
    }
    
    m_hRgn = CreateRectRgnIndirect(this);
    for (int i = 0; i < 4; i++)
    {
        CombineRgn(m_hRgn, m_hRgn, CreateRectRgnIndirect(&m_Anchor[i]), RGN_OR);
    }
}


//-----------------------------------------------------------------------------
// Name: SetAnchors
// Desc: Sets the anchor positions
//-----------------------------------------------------------------------------

void CPipProp::Sizer::SetAnchors()
{
    int x1 = left, x2 = right, y1 = top, y2 = bottom;

    SetRect(&m_Anchor[0], x1 - 2, y1 - 4, x1 + 4, y1 + 4);
    SetRect(&m_Anchor[1], x2 - 2, y1 - 4, x2 + 4, y1 + 4);
    SetRect(&m_Anchor[2], x2 - 2, y2 - 4, x2 + 4, y2 + 4);
    SetRect(&m_Anchor[3], x1 - 2, y2 - 4, x1 + 4, y2 + 4);
}


//-----------------------------------------------------------------------------
// Name: Draw
// Desc: Draws the widget
//-----------------------------------------------------------------------------

void CPipProp::Sizer::Draw(HDC hdc)
{
    HBRUSH hBrush=0;
    COLORREF color = RGB(0, 0, 0xFF);

    if (m_bSelected)
    {
        hBrush = CreateHatchBrush(HS_DIAGCROSS, color);
    }
    else
    {
        hBrush = CreateSolidBrush(color);
    }

    if (!hBrush)
        return;
        
    FrameRect(hdc, this, hBrush);

    if (m_bSelected)  // Draw the anchors
    {
        for (int i = 0; i < 4; i++)
        {
            FillRect(hdc, &m_Anchor[i], (HBRUSH)GetStockObject(BLACK_BRUSH));
        }
    }

    FrameRect(hdc, &m_BoundingRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

    DeleteObject(hBrush);
}


//-----------------------------------------------------------------------------
// Name: TestHit
// Desc: Check if the user clicked on the widget.
//
// x,y:  Mouse-down coordinates
//
// Return value: TRUE if the widget should be repainted, FALSE otherwise
//-----------------------------------------------------------------------------

BOOL CPipProp::Sizer::TestHit(int x, int y)
{
    POINT pt = { x, y };

    if (m_bInHotZone)
    {
        m_bGrabbed = true;
        return FALSE;
    }

    if (PtInRect(this, pt))
    {
        m_bSelected = ! m_bSelected;
        return TRUE;
    }
    else if (m_bSelected)  // Unselect and force repaint
    {
        m_bSelected = false;
        m_bGrabbed = false;
        return TRUE;
    }

    return FALSE;
}


//-----------------------------------------------------------------------------
// Name: TestMouseMove
// Desc: Respond to mouse moves
//
// x,y:  Mouse coordinates
//
// Return value: TRUE if the widget should be repainted, FALSE otherwise
//-----------------------------------------------------------------------------

BOOL CPipProp::Sizer::TestMouseMove(int x, int y)
{
    // If grabbing right now, resize the Sizer rectangle

    // We keep a minimum 2-pixel distance between opposite rectangle
    // sides. Otherwise it doesn't look like a rectangle any more.)

    if (m_bGrabbed)
    {
        SetRegion();

        switch (m_iGrabbedAnchor)
        {
            case 0:
                top = min(y, bottom - 2);
                left = min(x, right - 2);
                break;
            case 1:
                top = min(y, bottom - 2);
                right = max(x, left + 2);
                break;
            case 2:
                bottom = max(y, top + 2);
                right = max(x, left + 2);
                break;
            case 3:
                bottom = max(y, top + 2);
                left = min(x, right - 2);
                break;
            default:
                _ASSERTE(FALSE);
                break;
        }

        // Trim to the bounding rect
        IntersectRect(this, this, &m_BoundingRect);
        SetAnchors();

        return TRUE;
    }

    // If not grabbing and not selected, nothing to do.
    if (!m_bSelected) {
        return FALSE;
    }

    // If selected, look for hot zone. Is the mouse hovering over an anchor?

    bool bInHotZone = false;
    POINT pt = { x, y };

    for (int i = 0; i < 4; i++)
    {
        if (PtInRect(&m_Anchor[i], pt))
        {
            bInHotZone = true;
            m_iGrabbedAnchor = i;
            break;
        }
    }

    // Change the cursor to a diagonal arrow, to indicate "resizability"
    if (bInHotZone)
    {
        HCURSOR hCursor;
        if (m_iGrabbedAnchor == 0 || m_iGrabbedAnchor == 2)
        {
            hCursor = LoadCursor(0, IDC_SIZENWSE);
        }
        else 
        {
            hCursor = LoadCursor(0, IDC_SIZENESW);
        }
        SetCursor(hCursor);
    }
    else if (m_bInHotZone)
    {
        // We *were* in a hot zone, now we're not, so reset the cursor.
        SetCursor(LoadCursor(0, IDC_ARROW));
    }

    m_bInHotZone = bInHotZone;
    
    return FALSE;
}


/************************************************************
 *
 *  CPipProp Class -- Property setter for the Compositor transition 
 *                    (Picture-in-Picture)
 *
 ************************************************************/

CPipProp::CPipProp(IAMTimelineObj *pObj)
        : CBasePropSetter(pObj)
{
    this->m_nID = IDD_COMPOSITOR;
}


HRESULT CPipProp::OnInitDialog()
{
    // Set bounding boxes for the sizer control
    RECT rcSrcBound = { 10, 10, 110, 110 };  // WAG
    RECT rcDestBound = { 120, 10, 220, 110 };

    RECT rcSrc, rcDest, rcVid;

    // Get the video rectangle
    GetClientRect(GetDlgItem(m_hwnd, IDC_VIDWIN), &rcVid);

    // Set default Src and Dest rectangles
    CopyRect(&rcSrc, &rcVid);
    InflateRect(&rcSrc, - 10, - 10);
    CopyRect(&rcDest, &rcSrc);

    DWORD dwVal = 0;
    if (SUCCEEDED(GetNumericVal(TEXT("SrcOffsetY"), &dwVal)))
    {
        rcSrc.top = rcSrc.bottom = dwVal;
    }
    if (SUCCEEDED(GetNumericVal(TEXT("SrcOffsetX"), &dwVal)))
    {
        rcSrc.left = rcSrc.right = dwVal;
    }
    if (SUCCEEDED(GetNumericVal(TEXT("SrcHeight"), &dwVal)))
    {
        rcSrc.bottom += dwVal;
    }
    if (SUCCEEDED(GetNumericVal(TEXT("SrcWidth"), &dwVal)))
    {
        rcSrc.right += dwVal;
    }

    if (SUCCEEDED(GetNumericVal(TEXT("OffsetY"), &dwVal)))
    {
        rcDest.top = rcDest.bottom = dwVal;
    }
    if (SUCCEEDED(GetNumericVal(TEXT("OffsetX"), &dwVal)))
    {
        rcDest.left = rcDest.right = dwVal;
    }
    if (SUCCEEDED(GetNumericVal(TEXT("Height"), &dwVal)))
    {
        rcDest.bottom += dwVal;
    }
    if (SUCCEEDED(GetNumericVal(TEXT("Width"), &dwVal)))
    {
        rcDest.right += dwVal;
    }
    
    m_Src.Init(rcSrcBound, rcVid, rcSrc);
    m_Dest.Init(rcDestBound, rcVid, rcDest);

    return S_OK;
}


HRESULT CPipProp::OnOK()
{
    RemoveAll();

    RECT rcSrc, rcDest, rcVid;

    GetClientRect(GetDlgItem(m_hwnd, IDC_VIDWIN), &rcVid);
    m_Src.MapToRect(rcVid, &rcSrc);
    m_Dest.MapToRect(rcVid, &rcDest);

    SetNumericVal(TEXT("SrcOffsetY"), rcSrc.top);
    SetNumericVal(TEXT("SrcOffsetX"), rcSrc.left);
    SetNumericVal(TEXT("SrcHeight"), rcSrc.bottom - rcSrc.top );
    SetNumericVal(TEXT("SrcWidth"), rcSrc.right - rcSrc.left);

    SetNumericVal(TEXT("OffsetY"), rcDest.top);
    SetNumericVal(TEXT("OffsetX"), rcDest.left);
    SetNumericVal(TEXT("Height"), rcDest.bottom - rcDest.top );
    SetNumericVal(TEXT("Width"), rcDest.right - rcDest.left);

    return S_OK;
}


INT_PTR CPipProp::OnReceiveMsg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int x, y;

    switch (msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hDlg, &ps);
            EndPaint(hDlg, &ps);
            OnPaint();
        }
        return FALSE;

        case WM_LBUTTONDOWN:
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);
        
            {
                // We specifically want to hit-test both widgets!
                // Because when it fails the hit-test, it un-selects itself!
                // But only repaint once!
                BOOL bSrcHit = m_Src.TestHit(x, y);
            
                if (m_Dest.TestHit(x,y) || bSrcHit)
                {
                    Repaint();
                }
            }
            return TRUE;

        case WM_LBUTTONUP:
            m_Src.Unclick();
            m_Dest.Unclick();
            return TRUE;
           
        case WM_MOUSEMOVE:
            x = GET_X_LPARAM(lParam);
            y = GET_Y_LPARAM(lParam);

            if (m_Src.TestMouseMove(x, y))
            {
                Repaint(m_Src.m_hRgn);
            }
            else if (m_Dest.TestMouseMove(x, y))
            {
                Repaint(m_Dest.m_hRgn);
            }

            return TRUE;
    }

    // default
    return FALSE;
}


void CPipProp::Repaint()
{
    RECT rcClient;
    GetClientRect(GetDlgItem(m_hDlg, IDC_COMP_CANVAS), &rcClient);

    InvalidateRect(m_hDlg, &rcClient, TRUE);
    UpdateWindow(m_hDlg);
    OnPaint();
}


void CPipProp::Repaint(HRGN rgn)
{
    InvalidateRgn(m_hDlg, rgn, TRUE);
    UpdateWindow(m_hDlg);
    OnPaint();
}


void CPipProp::OnPaint()
{
    HDC hdc = GetDC(m_hDlg);

    m_Src.Draw(hdc);
    m_Dest.Draw(hdc);

    ReleaseDC(m_hDlg, hdc);
}

#pragma warning(default: 4702)


