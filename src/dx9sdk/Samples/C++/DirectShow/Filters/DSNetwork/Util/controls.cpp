//------------------------------------------------------------------------------
// File: Controls.cpp
//
// Desc: DirectShow sample code - implementation of DSNetwork sample filters
//       Thin Win32 wrapper methods
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "projpch.h"
#include <commctrl.h>
#include "controls.h"

/*++
        CControlBase
--*/

CControlBase::CControlBase (
    HWND    hwnd,
    DWORD   id
    )
{
    ASSERT (hwnd) ;

    m_hwnd = GetDlgItem (hwnd, id) ;
    m_id = id ;
}

HWND
CControlBase::GetHwnd (
    )
{
    return m_hwnd ;
}

DWORD
CControlBase::GetId (
    )
{
    return m_id ;
}

/*++
        CEditControl
--*/

CEditControl::CEditControl (
    HWND    hwnd,
    DWORD   id
    ) : CControlBase (hwnd, id)
{
    ASSERT (hwnd) ;
}

void
CEditControl::SetText (
    CHAR * szText
    )
{
    ASSERT (szText) ;
    SetWindowTextA (GetHwnd (), szText) ;
}

void
CEditControl::SetTextW (
    WCHAR * szText
    )
{
    ASSERT (szText) ;
    SetWindowTextW (GetHwnd (), szText) ;
}

void
CEditControl::SetText (
    INT val
    )
{
    CHAR achbuffer [32] ;
    SetText (_itoa (val, achbuffer, 10)) ;
}

int
CEditControl::GetText (
    INT *   val
    )
{
    CHAR    achbuffer [32] ;

    ASSERT (val) ;
    if (!val)
        return 0;
        
    * val = 0 ;

    if (GetText (achbuffer, 31)) {
        * val = atoi (achbuffer) ;
    }

    return * val ;
}

int
CEditControl::GetText (
    CHAR *  ach,
    int     MaxChars
    )
{
    ASSERT (ach) ;
    return GetWindowTextA (GetHwnd (), ach, MaxChars) ;
}

BOOL
CEditControl::IsEmpty (
    )
{
    CHAR    c [2] ;
    return GetWindowTextA (GetHwnd (), c, 2) == 0 ;
}

int
CEditControl::GetTextW (
    WCHAR * ach,
    int     MaxChars
    )
{
    ASSERT (ach) ;
    return GetWindowTextW (GetHwnd (), ach, MaxChars) ;
}


int CEditControl::ResetContent ()
{
    return SendMessage (GetHwnd (), WM_CLEAR, 0, 0) ;
}

/*++
        CComboBox
--*/

CCombobox::CCombobox (
    HWND    hwnd,
    DWORD   id
    ) : CControlBase (hwnd, id)
{
}

int
CCombobox::Append (
    CHAR *  sz
    )
{
    return SendMessage (GetHwnd (), CB_ADDSTRING, 0, (LPARAM) sz) ;
}

int
CCombobox::Append (
    INT val
    )
{
    CHAR    achbuffer [32] ;        //  no numbers are longer

    return Append (_itoa (val, achbuffer, 10)) ;
}

int
CCombobox::Insert (
    CHAR *  sz,
    int     index)
{
    return SendMessage (GetHwnd (), CB_INSERTSTRING, (WPARAM) index, (LPARAM) sz) ;
}

int
CCombobox::Insert (
    INT val,
    int index
    )
{
    CHAR    achbuffer [32] ;        //  no numbers are longer

    return Insert (_itoa (val, achbuffer, 10), index) ;
}


int
CCombobox::GetText (
    CHAR *  ach,
    int     MaxChars
    )
{
    int index ;
    int count ;

    index = GetCurrentItemIndex () ;
    if (index == CB_ERR) {
        //  might be that it's not a dropdown list - in which case we get;
        //  try to get just the edit control's text; if that fails, return
        //  a failure, otherwise we're ok
        count = GetWindowTextA (GetHwnd (), ach, MaxChars) ;
        if (count == 0) {
            return CB_ERR ;
        }

        return count ;
    }

    if (SendMessage (GetHwnd (), CB_GETLBTEXTLEN, (WPARAM) index, 0) + 1 > MaxChars) {
        return CB_ERR ;
    }

    return SendMessage (GetHwnd (), CB_GETLBTEXT, (WPARAM) index, (LPARAM) ach) ;
}

int
CCombobox::GetText (
    int * val
    )
{
    CHAR    achbuffer [32] ;

    ASSERT (val) ;
    if (!val)
        return 0;
        
    * val = 0 ;

    if (GetText (achbuffer, 32)) {
        * val = atoi (achbuffer) ;
    }

    return * val ;
}


int
CCombobox::Focus (
    int index
    )
{
    return SendMessage (GetHwnd (), CB_SETCURSEL, (WPARAM) index, 0) ;
}

int
CCombobox::ResetContent (
    )
{
    return SendMessage (GetHwnd (), CB_RESETCONTENT, 0, 0) ;
}

int
CCombobox::SetItemData (
    DWORD   val,
    int     index
    )
{
    return SendMessage (GetHwnd (), CB_SETITEMDATA, (WPARAM) index, (LPARAM) val) ;
}

int
CCombobox::GetCurrentItemIndex (
    )
{
    return SendMessage (GetHwnd (), CB_GETCURSEL, 0, 0) ;
}

int
CCombobox::GetItemData (
    DWORD * pval,
    int     index
    )
{
    int i ;

    ASSERT (pval) ;
    if (!pval)
        return 0;

    i = SendMessage (GetHwnd (), CB_GETITEMDATA, (WPARAM) index, 0) ;
    if (i == CB_ERR) {
        return CB_ERR ;
    }

    * pval = i ;
    return i ;
}

int
CCombobox::GetCurrentItemData (
    DWORD * pval
    )
{
    int index ;

    index = GetCurrentItemIndex () ;
    if (index == CB_ERR) {
        return CB_ERR ;
    }

    return GetItemData (pval, index) ;
}

int
CCombobox::Find (
    CHAR * sz
    )
{
    ASSERT (sz) ;
    return SendMessage (GetHwnd (), CB_FINDSTRING, (WPARAM) -1, (LPARAM) sz) ;
}

int
CCombobox::FindW (
    WCHAR * sz
    )
{
    ASSERT (sz) ;
    return SendMessageW (GetHwnd (), CB_FINDSTRING, (WPARAM) -1, (LPARAM) sz) ;
}


