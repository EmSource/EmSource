
/*++

    Copyright (c) 2000  Microsoft Corporation.  All Rights Reserved.

    Module Name:

        controls.h

    Abstract:

        Class declarations for thin win32 control message wrappers.

    Notes:

--*/

#ifndef controls_h
#define controls_h

class CControlBase
{
    HWND    m_hwnd ;
    DWORD   m_id ;

    protected :

        CControlBase (
            HWND    hwnd,
            DWORD   id
            ) ;

    public :

        HWND
        GetHwnd (
            ) ;

        DWORD
        GetId (
            ) ;

        virtual
        int
        ResetContent (
            ) = 0 ;
} ;

class CEditControl :
    public CControlBase
{
    public :

        CEditControl (
            HWND    hwnd,
            DWORD   id
            ) ;

        void
        SetText (
            CHAR *
            ) ;

        void
        SetText (
            INT val
            ) ;

        void
        SetTextW (
            WCHAR *
            ) ;

        int
        GetText (
            CHAR *,
            int MaxChars
            ) ;

        int
        GetText (
            INT *   val
            ) ;

        int
        GetTextW (
            WCHAR *,
            int MaxChars
            ) ;

        int
        ResetContent (
            ) ;

        BOOL
        IsEmpty (
            ) ;
} ;

class CCombobox :
    public CControlBase
{
    public :

        CCombobox (
            HWND    hwnd,
            DWORD   id) ;

        int
        Append (
            CHAR *
            ) ;

        int
        Append (
            INT val
            ) ;

        int
        Insert (
            CHAR *,
            int index = 0
            ) ;

        int
        Insert (
            INT val,
            int index = 0
            ) ;

        int
        GetText (
            CHAR *,
            int MaxChars
            ) ;

        int
        GetText (
            int *
            ) ;

        int
        ResetContent (
            ) ;

        int
        Focus (
            int index = 0
            ) ;

        int
        SetItemData (
            DWORD val,
            int index
            ) ;

        int
        GetCurrentItemData (
            DWORD *
            ) ;

        int
        GetItemData (
            DWORD *,
            int index
            ) ;

        int
        GetCurrentItemIndex (
            ) ;

        int
        Find (
            CHAR *
            ) ;

        int
        FindW (
            WCHAR *
            ) ;
} ;

#endif  // controls_h