//------------------------------------------------------------------------------
// File: PropRecv.cpp
//
// Desc: DirectShow sample code - implementation of DSNetwork sample filters
//       Class implementation to get/set/display property pages.
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "precomp.h"
#include "resrecv.h"
#include "dsnetifc.h"
#include "proprecv.h"
#include "controls.h"
#include "nutil.h"

//  error conditions
static
void
MessageBoxError (
    IN  TCHAR * title,
    IN  TCHAR * szfmt,
    ...
    )
{
    TCHAR   achbuffer [256] ;
    va_list va ;

    va_start (va, szfmt) ;
    wvsprintf (achbuffer, szfmt, va) ;

    MessageBox (NULL, achbuffer, title, MB_OK | MB_ICONEXCLAMATION) ;
}

//  ---------------------------------------------------------------------------

CNetRecvProp::CNetRecvProp (
    IN  TCHAR *     pClassName,
    IN  IUnknown *  pIUnknown,
    IN  REFCLSID    rclsid,
    OUT HRESULT *   pHr
    ) : CBasePropertyPage   (
                             pClassName,
                             pIUnknown,
                             IDD_IPMULTICAST_RECV_CONFIG,
                             IDS_IPMULTICAST_RECV_CONFIG
                             ),
        m_hwnd              (NULL),
        m_pIMulticastConfig (NULL)
{
    ASSERT(pHr);
    if (pHr)
        * pHr = S_OK ;
}

void
CNetRecvProp::Refresh_ (
    )
{
    //  synchronize the display to our config

    CCombobox       NICs (m_hwnd, IDC_NIC) ;
    CEditControl    IP (m_hwnd, IDC_IP) ;
    CEditControl    Port (m_hwnd, IDC_PORT) ;
    ULONG           ul, ul2 ;
    USHORT          us ;
    HRESULT         hr ;
    int             i, k ;
    char            ach [16] ;

    //  -----------------------------------------------------------------------
    //  NIC

    hr = m_pIMulticastConfig -> GetNetworkInterface (& ul) ;
    if (FAILED (hr)) {
        return ;
    }

    for (i = 0;;i++) {
        k = NICs.GetItemData (& ul2, i) ;
        if (k == CB_ERR) {
            //  should not happen; undefine it
            m_pIMulticastConfig -> SetNetworkInterface ((unsigned long) UNDEFINED) ;
            for (i = 0;;i++) {
                NICs.GetItemData (& ul2, i) ;
                if (ul2 == UNDEFINED) {
                    NICs.Focus (i) ;
                    break ;
                }
            }

            break ;
        }

        if (ul2 == ul) {
            NICs.Focus (i) ;
            break ;
        }
    }

    //  -----------------------------------------------------------------------
    //  group

    hr = m_pIMulticastConfig -> GetMulticastGroup (& ul, & us) ;
    if (FAILED (hr)) {
        return ;
    }

    if (ul != UNDEFINED) {
        IP.SetText (inet_ntoa (* (struct in_addr *) & ul)) ;
    }
    else {
        IP.SetText (UNDEFINED_STR) ;
    }

    us = ntohs (us) ;
    Port.SetText (_itoa (us, ach, 10)) ;

    return ;
}

HRESULT
CNetRecvProp::OnActivate (
    )
{
    CCombobox           NICs (m_hwnd, IDC_NIC) ;
    int                 iIndex ;
    INTERFACE_INFO *    pIfc ;
    DWORD               i ;

    //  populate the NICs

    //  setup the NICs

    ASSERT (g_NIC.IsInitialized ()) ;

    for (i = 0, pIfc = g_NIC [i] ;
         pIfc ;
         i++, pIfc = g_NIC [i]) {

        if ((pIfc -> iiFlags & IFF_UP) &&
            (pIfc -> iiFlags & IFF_MULTICAST)) {

            iIndex = NICs.Append (inet_ntoa (pIfc -> iiAddress.AddressIn.sin_addr)) ;
            if (iIndex == CB_ERR) {
                return E_FAIL ;
            }

            NICs.SetItemData (* (DWORD *) (& pIfc -> iiAddress.AddressIn.sin_addr), iIndex) ;
        }
    }

    //  wildcard
    iIndex = NICs.Append (ANY_IFC) ;
    if (iIndex == CB_ERR) {
        return E_FAIL ;
    }
    NICs.SetItemData (INADDR_ANY, iIndex) ;

    //  undefined
    iIndex = NICs.Append (UNDEFINED_STR) ;
    if (iIndex == CB_ERR) {
        return E_FAIL ;
    }
    NICs.SetItemData ((unsigned long) UNDEFINED, iIndex) ;

    Refresh_ () ;

    return S_OK ;
}

HRESULT
CNetRecvProp::OnSave_ (
    )
{
    CCombobox       NICs (m_hwnd, IDC_NIC) ;
    CEditControl    IP (m_hwnd, IDC_IP) ;
    CEditControl    Port (m_hwnd, IDC_PORT) ;
    int             i ;
    ULONG           ulIP ;
    USHORT          usPort ;
    ULONG           ulNIC ;
    HRESULT         hr ;
    char            ach [32] ;

    if (IP.IsEmpty () ||
        Port.IsEmpty ()) {

        return E_INVALIDARG ;
    }

    //  IP
    IP.GetText (ach, 32) ;
    ulIP = inet_addr (ach) ;
    if (ulIP == INADDR_NONE) {
        return E_FAIL ;
    }

    //  port
    Port.GetText (& i) ;
    i &= 0x0000ffff ;
    usPort = htons ((USHORT) i) ;

    //  NIC
    NICs.GetCurrentItemData (& ulNIC) ;

    hr = m_pIMulticastConfig -> SetMulticastGroup (ulIP, usPort) ;
    if (FAILED (hr)) {
        return hr ;
    }

    hr = m_pIMulticastConfig -> SetNetworkInterface (ulNIC) ;
    if (FAILED (hr)) {
        return hr ;
    }

    return S_OK ;
}

HRESULT
CNetRecvProp::OnApplyChanges (
    )
{
    return OnSave_ () ;
}

HRESULT
CNetRecvProp::OnConnect (
    IN  IUnknown *  pIUnknown
    )
{
    HRESULT hr ;

    ASSERT (pIUnknown) ;

    if (!g_NIC.IsInitialized ()) {
        hr = g_NIC.Initialize () ;
        if (FAILED (hr)) {
            return hr ;
        }
    }

    hr = pIUnknown -> QueryInterface (
                            IID_IMulticastConfig,
                            (void **) & m_pIMulticastConfig
                            ) ;

    return hr ;
}

HRESULT
CNetRecvProp::OnDeactivate (
    )
{
    return S_OK ;
}

HRESULT
CNetRecvProp::OnDisconnect (
    )
{
    RELEASE_AND_CLEAR (m_pIMulticastConfig) ;
    return S_OK ;
}

BOOL
CNetRecvProp::OnReceiveMessage (
    IN  HWND    hwnd,
    IN  UINT    uMsg,
    IN  WPARAM  wParam,
    IN  LPARAM  lParam
    )
{
    HRESULT hr ;

    switch (uMsg)
    {
        case WM_INITDIALOG:
        {
            ASSERT (m_hwnd == NULL) ;
            m_hwnd = hwnd ;
            return TRUE ;
        }

        case WM_DESTROY :
        {
            m_hwnd = NULL ;
            break ;
        }

        case WM_COMMAND:
        {
            switch (LOWORD (wParam)) {
                case IDC_SAVE :
                    hr = OnSave_ () ;
                    if (FAILED (hr)) {
                        MessageBoxError (TEXT("Failed to Save"), 
                                        TEXT("The returned error code is %08xh"), hr) ;
                    }
                    break ;
            } ;

            return TRUE ;
        }

    }

    return CBasePropertyPage::OnReceiveMessage (
                                hwnd,
                                uMsg,
                                wParam,
                                lParam
                                ) ;
}

CUnknown *
WINAPI
CNetRecvProp::CreateInstance (
    IN  IUnknown *  pIUnknown,
    IN  HRESULT *   pHr
    )
{
    CNetRecvProp *  pProp ;

    pProp = new CNetRecvProp (
                        NAME ("CNetRecvProp"),
                        pIUnknown,
                        CLSID_IPMulticastRecvProppage,
                        pHr
                        ) ;

    if (pProp == NULL) {
        * pHr = E_OUTOFMEMORY ;
    }

    return pProp ;
}

