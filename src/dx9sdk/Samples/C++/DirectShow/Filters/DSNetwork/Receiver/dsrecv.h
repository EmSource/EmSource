
/*++

    Copyright (c) 2000-2002  Microsoft Corporation.  All Rights Reserved.

    Module Name:

        dsrecv.h

    Abstract:


    Notes:

--*/

#define NET_RECEIVE_FILTER_NAME         L"MPEG-2 Multicast Receiver\0"
#define NET_RECEIVE_PROP_PAGE_NAME      L"Net Receive Properties\0"

extern AMOVIESETUP_FILTER g_sudRecvFilter ;

class CNetOutputPin ;
class CNetworkReceiverFilter ;
class CBuffer ;
class CBufferPool ;
class CNetReceiver ;
class CTSMediaSamplePool ;
class CNetRecvAlloc ;

/*++
    Class Name:

        CNetOutputPin

    Abstract:

        Filter output pin.

--*/
class CNetOutputPin :
    public CBaseOutputPin
{
    public :

        CNetOutputPin (
            IN  TCHAR *         szName,
            IN  CBaseFilter *   pFilter,
            IN  CCritSec *      pLock,
            OUT HRESULT *       pHr,
            IN  LPCWSTR         pszName
            ) ;

        ~CNetOutputPin () ;

        HRESULT
        GetMediaType (
            IN  int             iPosition,
            OUT CMediaType *    pmt
            ) ;

        HRESULT
        CheckMediaType (
            IN  const CMediaType * pmt
            ) ;

        HRESULT
        DecideBufferSize (
            IN  IMemAllocator *,
            OUT ALLOCATOR_PROPERTIES *
            ) ;

        virtual
        HRESULT
        InitAllocator (
            OUT IMemAllocator ** ppAlloc
            ) ;
} ;

//  ---------------------------------------------------------------------------

class CNetworkReceiverFilter :
    public CBaseFilter,
    public IMulticastConfig,
    public ISpecifyPropertyPages,
    public CPersistStream
/*++
    Class Name:

        CNetworkReceiverFilter

    Abstract:

        Object implements our filter.
--*/
{
    enum {
        POOL_SIZE               = 24,       //  buffer pool size
        MEDIA_SAMPLE_POOL_SIZE  = 10,       //  media samples in our pool
    } ;

    CCritSec                m_crtFilterLock ;   //  filter lock
    CNetOutputPin *         m_pOutput ;         //  output pin
    IMemAllocator *         m_pIMemAllocator ;  //  mem allocator
    CNetReceiver *          m_pNetReceiver ;    //  receiver object
    ULONG                   m_ulIP ;            //  multicast ip; network order
    USHORT                  m_usPort ;          //  multicast port; network order
    ULONG                   m_ulNIC ;           //  NIC; network order
    CBufferPool *           m_pBufferPool ;     //  buffer pool object
    CTSMediaSamplePool *    m_pMSPool ;         //  media sample pool
    CNetRecvAlloc *         m_pNetRecvAlloc ;   //  allocator

    public :

        CNetworkReceiverFilter (
            IN  TCHAR *     tszName,
            IN  LPUNKNOWN   punk,
            OUT HRESULT *   phr
            ) ;

        ~CNetworkReceiverFilter (
            ) ;

        void LockFilter ()              { m_crtFilterLock.Lock () ; }
        void UnlockFilter ()            { m_crtFilterLock.Unlock () ; }

        DECLARE_IUNKNOWN ;
        DECLARE_IMULTICASTCONFIG () ;

        //  --------------------------------------------------------------------
        //  CBaseFilter methods

        int GetPinCount ()              { return 1 ; }

        CBasePin *
        GetPin (
            IN  int Index
            ) ;

        CNetRecvAlloc *
        GetRecvAllocator (
            )
        {
            return m_pNetRecvAlloc ;
        }

        STDMETHODIMP
        NonDelegatingQueryInterface (
            IN  REFIID  riid,
            OUT void ** ppv
            ) ;

        static
        CUnknown *
        CreateInstance (
            IN  LPUNKNOWN   punk,
            OUT HRESULT *   phr
            ) ;

        STDMETHODIMP
        GetPages (
            IN OUT CAUUID * pPages
            ) ;

        AMOVIESETUP_FILTER *
        GetSetupData (
            )
        {
            return & g_sudRecvFilter ;
        }

        STDMETHODIMP
        Pause (
            ) ;

        STDMETHODIMP
        Stop (
            ) ;

        //  --------------------------------------------------------------------
        //  CPersistStream

        HRESULT
        WriteToStream (
            IN  IStream *   pIStream
            ) ;

        HRESULT
        ReadFromStream (
            IN  IStream *   pIStream
            ) ;

        int SizeMax ()  { return (sizeof m_ulIP + sizeof m_usPort + sizeof m_ulNIC) ; }

        STDMETHODIMP
        GetClassID (
            OUT CLSID * pCLSID
            ) ;

        //  class methods

        void
        ProcessBuffer (
            IN  CBuffer *
            ) ;
} ;