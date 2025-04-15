//------------------------------------------------------------------------------
// File: DSRecv.cpp
//
// Desc: DirectShow sample code - implementation of DSNetwork sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "precomp.h"
#include "le.h"
#include "nutil.h"
#include "dsnetifc.h"
#include "buffpool.h"
#include "netrecv.h"
#include "dsrecv.h"
#include "mspool.h"
#include "alloc.h"

//  ---------------------------------------------------------------------------
//  ---------------------------------------------------------------------------

CNetOutputPin::CNetOutputPin (
    IN  TCHAR *         szName,
    IN  CBaseFilter *   pFilter,
    IN  CCritSec *      pLock,
    OUT HRESULT *       pHr,
    IN  LPCWSTR         pszName
    ) : CBaseOutputPin  (szName,
                         pFilter,
                         pLock,
                         pHr,
                         pszName
                         )
{
}

CNetOutputPin::~CNetOutputPin (
    )
{
}

HRESULT
CNetOutputPin::GetMediaType (
    IN  int             iPosition,
    OUT CMediaType *    pmt
    )
{
    HRESULT hr ;

    if (iPosition == 0) {
        ASSERT (pmt) ;
        pmt -> InitMediaType () ;

        pmt -> SetType      (& MEDIATYPE_Stream) ;
        pmt -> SetSubtype   (& MEDIASUBTYPE_MPEG2_TRANSPORT) ;

        hr = S_OK ;
    }
    else {
        hr = VFW_S_NO_MORE_ITEMS ;
    }

    return hr ;
}

HRESULT
CNetOutputPin::CheckMediaType (
    IN  const CMediaType * pmt
    )
{
    HRESULT hr ;

    ASSERT (pmt) ;

    if (pmt -> majortype    == MEDIATYPE_Stream &&
        pmt -> subtype      == MEDIASUBTYPE_MPEG2_TRANSPORT) {

        hr = S_OK ;
    }
    else {
        hr = S_FALSE ;
    }

    return hr ;
}

HRESULT
CNetOutputPin::InitAllocator (
    OUT IMemAllocator ** ppAlloc
    )
{
    (* ppAlloc) = NET_RECV (m_pFilter) -> GetRecvAllocator () ;
    (* ppAlloc) -> AddRef () ;

    return S_OK ;
}

HRESULT
CNetOutputPin::DecideBufferSize (
    IN  IMemAllocator *         pIMemAllocator,
    OUT ALLOCATOR_PROPERTIES *  pProp
    )
{
    HRESULT hr ;

    if (pIMemAllocator == NET_RECV (m_pFilter) -> GetRecvAllocator ()) {
        //  we're the allocator; get the properties and succeed
        hr = NET_RECV (m_pFilter) -> GetRecvAllocator () -> GetProperties (pProp) ;
    }
    else {
        //  this is not our allocator; fail the call
        hr = E_FAIL ;
    }

    return hr ;
}

//  ---------------------------------------------------------------------------
//  ---------------------------------------------------------------------------

CNetworkReceiverFilter::CNetworkReceiverFilter (
    IN  TCHAR *     tszName,
    IN  LPUNKNOWN   punk,
    OUT HRESULT *   phr
    ) : CBaseFilter         (
                             tszName,
                             punk,
                             & m_crtFilterLock,
                             CLSID_DSNetSend
                             ),
        CPersistStream      (punk,
                             phr
                             ),
        m_pOutput           (NULL),
        m_pIMemAllocator    (NULL),
        m_ulIP              ((unsigned long) UNDEFINED),
        m_ulNIC             ((unsigned long) UNDEFINED),
        m_pBufferPool       (NULL),
        m_pNetReceiver      (NULL),
        m_pMSPool           (NULL),
        m_pNetRecvAlloc     (NULL)
{
    //  instantiate the output pin
    m_pOutput = new CNetOutputPin (
                            NAME ("CNetOutputPin"),
                            this,
                            & m_crtFilterLock,
                            phr,
                            L"MPEG-2 Transport"
                            ) ;
    if (m_pOutput == NULL ||
        FAILED (* phr)) {

        (* phr) = (FAILED (* phr) ? * phr : E_OUTOFMEMORY) ;
        return ;
    }

    //  the buffer pool
    m_pBufferPool = new CBufferPool (POOL_SIZE, MAX_IOBUFFER_LENGTH, phr) ;
    if (m_pBufferPool == NULL ||
        FAILED (*phr)) {

        (* phr) = (FAILED (* phr) ? * phr : E_OUTOFMEMORY) ;
        return ;
    }

    //  the receiver object
    m_pNetReceiver = new CNetReceiver (m_pBufferPool, this, phr) ;
    if (m_pNetReceiver == NULL ||
        FAILED (*phr)) {

        (* phr) = (FAILED (* phr) ? * phr : E_OUTOFMEMORY) ;
        return ;
    }

    //  the media sample pool
    m_pMSPool = new CTSMediaSamplePool (MEDIA_SAMPLE_POOL_SIZE, this, phr) ;
    if (m_pMSPool == NULL ||
        FAILED (*phr)) {

        (* phr) = (FAILED (* phr) ? * phr : E_OUTOFMEMORY) ;
        return ;
    }

    //  IMemAllocator
    m_pNetRecvAlloc = new CNetRecvAlloc (m_pBufferPool, m_pMSPool, this) ;
    if (m_pNetRecvAlloc == NULL) {
        (* phr) = E_OUTOFMEMORY ;
        return ;
    }
}

CNetworkReceiverFilter::~CNetworkReceiverFilter ()
{
    delete m_pNetReceiver ;
    delete m_pOutput ;
    RELEASE_AND_CLEAR (m_pIMemAllocator) ;
    delete m_pBufferPool ;
    delete m_pMSPool ;
    delete m_pNetRecvAlloc ;
}

CBasePin *
CNetworkReceiverFilter::GetPin (
    IN  int Index
    )
{
    CBasePin *  pPin ;

    LockFilter () ;

    if (Index == 0) {
        pPin = m_pOutput ;
    }
    else {
        pPin = NULL ;
    }

    UnlockFilter () ;

    return pPin ;
}

STDMETHODIMP
CNetworkReceiverFilter::Pause (
    )
{
    HRESULT hr ;

    LockFilter () ;

    if (m_ulIP == UNDEFINED ||
        m_ulNIC == UNDEFINED) {

        hr = E_FAIL ;
    }
    else if  (m_State == State_Stopped) {

        //  --------------------------------------------------------------------
        //  stopped -> pause transition; get the filter up and running

        //  activate the receiver; joins the multicast group and starts the
        //  thread
        hr = m_pNetReceiver -> Activate (m_ulIP, m_usPort, m_ulNIC) ;

        if (SUCCEEDED (hr)) {
            m_State = State_Paused ;

            if (m_pOutput &&
                m_pOutput -> IsConnected ()) {
                m_pOutput -> Active () ;
            }
        }
    }
    else {
        //  --------------------------------------------------------------------
        //  run -> pause transition; do nothing but set the state

        m_State = State_Paused ;

        hr = S_OK ;
    }

    UnlockFilter () ;

    return hr ;
}

STDMETHODIMP
CNetworkReceiverFilter::Stop (
    )
{
    LockFilter () ;

    //  synchronous call to stop the receiver (leaves the multicast group
    //  and terminates the thread)
    m_pNetReceiver -> Stop () ;

    //  if we have an output pin (we should) stop it
    if (m_pOutput) {
        m_pOutput -> Inactive () ;
    }

    m_State = State_Stopped ;

    UnlockFilter () ;

    return S_OK ;
}

CUnknown *
CNetworkReceiverFilter::CreateInstance (
    IN  LPUNKNOWN   punk,
    OUT HRESULT *   phr
    )
{
    CNetworkReceiverFilter * pnf ;

    (* phr) = S_OK ;

    pnf = new CNetworkReceiverFilter (
                    NAME ("CNetworkReceiverFilter"),
                    punk,
                    phr
                    ) ;
    if (pnf == NULL ||
        FAILED (* phr)) {
        (* phr) = (FAILED (* phr) ? (* phr) : E_OUTOFMEMORY) ;
        DELETE_RESET (pnf) ;
    }

    return pnf ;
}

STDMETHODIMP
CNetworkReceiverFilter::NonDelegatingQueryInterface (
    IN  REFIID  riid,
    OUT void ** ppv
    )
{
    //  property pages

    if (riid == IID_ISpecifyPropertyPages) {

        return GetInterface (
                    (ISpecifyPropertyPages *) this,
                    ppv
                    ) ;
    }

    //  multicast config

    else if (riid == IID_IMulticastConfig) {

        return GetInterface (
                    (IMulticastConfig *) this,
                    ppv
                    ) ;
    }

    //  we do persist

    else if (riid == IID_IPersistStream) {

        return GetInterface (
                    (IPersistStream *) this,
                    ppv
                    ) ;
    }

    //  fallback - call the baseclass

    else {
        return CBaseFilter::NonDelegatingQueryInterface (riid, ppv) ;
    }
}

STDMETHODIMP
CNetworkReceiverFilter::GetPages (
    IN OUT CAUUID * pPages
    )
{
    HRESULT hr ;

    pPages -> cElems = 1 ;

    pPages -> pElems = (GUID *) CoTaskMemAlloc (pPages -> cElems * sizeof GUID) ;

    if (pPages -> pElems) {
        (pPages -> pElems) [0] = CLSID_IPMulticastRecvProppage ;
        hr = S_OK ;
    }
    else {
        hr = E_OUTOFMEMORY ;
    }

    return hr ;
}

STDMETHODIMP
CNetworkReceiverFilter::SetNetworkInterface (
    IN  ULONG   ulNIC
    )
{
    HRESULT hr ;

    LockFilter () ;

    if (m_State != State_Stopped) {
        hr = E_UNEXPECTED ;
    }
    else if (IsUnicastIP (ulNIC) ||
        ulNIC == INADDR_ANY) {

        m_ulNIC = ulNIC ;
        hr = S_OK ;
    }
    else {
        hr = E_INVALIDARG ;
    }

    UnlockFilter () ;

    return hr ;
}

STDMETHODIMP
CNetworkReceiverFilter::GetNetworkInterface (
    OUT ULONG * pulNIC
    )
{
    HRESULT hr ;

    LockFilter () ;

    if (pulNIC) {
        (* pulNIC) = m_ulNIC ;
        hr = S_OK ;
    }
    else {
        hr = E_INVALIDARG ;
    }

    UnlockFilter () ;

    return hr ;
}

STDMETHODIMP
CNetworkReceiverFilter::SetMulticastGroup (
    IN  ULONG   ulIP,
    IN  USHORT  usPort
    )
{
    HRESULT hr ;

    LockFilter () ;

    if (m_State != State_Stopped) {
        hr = E_UNEXPECTED ;
    }
    else if (IsMulticastIP (ulIP)) {

        m_ulIP      = ulIP ;
        m_usPort    = usPort ;

        hr = S_OK ;
    }
    else {
        hr = E_INVALIDARG ;
    }

    UnlockFilter () ;

    return hr ;
}

STDMETHODIMP
CNetworkReceiverFilter::GetMulticastGroup (
    OUT ULONG *     pIP,
    OUT USHORT  *   pPort
    )
{
    HRESULT hr ;

    LockFilter () ;

    if (pIP &&
        pPort) {

        (* pIP)     = m_ulIP ;
        (* pPort)   = m_usPort ;

        hr = S_OK ;
    }
    else {
        hr = E_INVALIDARG ;
    }

    UnlockFilter () ;

    return hr ;
}

STDMETHODIMP
CNetworkReceiverFilter::GetClassID (
    OUT CLSID * pCLSID
    )
{
    (* pCLSID) = CLSID_DSNetReceive ;
    return S_OK ;
}

HRESULT
CNetworkReceiverFilter::WriteToStream (
    IN  IStream *   pIStream
    )
{
    HRESULT hr ;

    LockFilter () ;

    hr = pIStream -> Write ((BYTE *) & m_ulIP, sizeof m_ulIP, NULL) ;
    if (SUCCEEDED (hr)) {
        hr = pIStream -> Write ((BYTE *) & m_usPort, sizeof m_usPort, NULL) ;
        if (SUCCEEDED (hr)) {
            hr = pIStream -> Write ((BYTE *) & m_ulNIC, sizeof m_ulNIC, NULL) ;
        }
    }

    UnlockFilter () ;

    return hr ;
}

HRESULT
CNetworkReceiverFilter::ReadFromStream (
    IN  IStream *   pIStream
    )
{
    HRESULT hr ;

    LockFilter () ;

    hr = pIStream -> Read ((BYTE *) & m_ulIP, sizeof m_ulIP, NULL) ;
    if (SUCCEEDED (hr)) {
        hr = pIStream -> Read ((BYTE *) & m_usPort, sizeof m_usPort, NULL) ;
        if (SUCCEEDED (hr)) {
            hr = pIStream -> Read ((BYTE *) & m_ulNIC, sizeof m_ulNIC, NULL) ;
        }
    }

    UnlockFilter () ;

    return hr ;
}

void
CNetworkReceiverFilter::ProcessBuffer (
    IN  CBuffer *   pBuffer
    )
{
    HRESULT         hr ;
    IMediaSample2 * pIMediaSample ;

    ASSERT (pBuffer) ;

    hr = m_pMSPool -> GetMediaSampleSynchronous (
                            pBuffer,
                            pBuffer -> GetBuffer (),
                            pBuffer -> GetPayloadLength (),
                            & pIMediaSample
                            ) ;
    if (SUCCEEDED (hr)) {
        ASSERT (pIMediaSample) ;
        m_pOutput -> Deliver (pIMediaSample) ;
        pIMediaSample -> Release () ;
    }
}

