//----------------------------------------------------------------------------
//  File:   CMultiSAP.cpp
//
//  Desc:   DirectShow sample code
//          Implementation of CMultiSAP
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#include "project.h"
#include <stdio.h>

//-------------------------------------------------------------------------
//  constructor
//-------------------------------------------------------------------------
CMultiSAP::CMultiSAP(HWND hwndApplication, HRESULT *phr)
            : CUnknown(NAME("Allocator Presenter"), NULL),
            m_hwndApp(hwndApplication),
            m_hMonitor(NULL),
            m_lpDDObj(NULL),
            m_lpBackBuffer(NULL),
            m_pSparkle(NULL),
            m_dwFrameNum(0),
            m_dwThreadID(0),
            m_hThread(NULL),
            m_hQuitEvent(NULL),
            m_pWC(NULL),
            m_pAlloc(NULL),
            m_pPresenter(NULL),
            m_pEffect(NULL),
            m_pdwNextSelectedMovie(NULL),
            m_bErrorMessage( false )

{
    ASSERT(phr);
    
    m_achErrorMessage[0] = 0;
    m_achErrorTitle[0] = 0;

    m_hQuitEvent = CreateEvent( NULL, FALSE, FALSE, TEXT("CMultiSAP_Quit"));
    if( !m_hQuitEvent )
    {
        OutputDebugString(TEXT("Failed to create quit event\n"));
        *phr = E_POINTER;
    }
    
    AddRef();
}

//-------------------------------------------------------------------------
//  destructor
//-------------------------------------------------------------------------
CMultiSAP::~CMultiSAP()
{
    
    delete m_pD3DHelper;
    m_pD3DHelper = NULL;
    
    delete m_pSparkle;
    m_pSparkle = NULL;
    m_lpDDObj = NULL;    
    m_pWC = NULL;
    m_pPresenter = NULL;
    m_lpBackBuffer = NULL;

    if (m_pAlloc) 
    {
        m_pAlloc->FreeSurface(0);
        m_pAlloc = NULL;
    }   
}

//-------------------------------------------------------------------------
//  DeleteAllMovies
//  pings movies to quit, and once this happens, cleans movie list
//-------------------------------------------------------------------------
void CMultiSAP::DeleteAllMovies()
{
    if (m_hQuitEvent) 
    {       
        if (m_hThread) 
        {            
            SetEvent(m_hQuitEvent);
            WaitForSingleObject(m_hThread, INFINITE);
            CloseHandle(m_hThread);
        }
        
        CloseHandle(m_hQuitEvent);
    }
    
    while( m_movieList.GetSize() )
    {
        CMovie *pmovie = m_movieList.GetMovieByIndex(0);
        if (pmovie)
            m_movieList.Delete( pmovie->m_dwUserID );
    }
}

//-------------------------------------------------------------------------
//  Initialize
//  configures D3D environment and creates composing thread
//-------------------------------------------------------------------------
HRESULT CMultiSAP::Initialize()
{
    HRESULT hr = CoInitialize(NULL);
    if (hr == S_FALSE)
        CoUninitialize();

    hr = InitializeEnvironment();
    if (SUCCEEDED(hr)) 
    {   
        m_hThread = CreateThread(NULL, 0, ComposeThreadProc, this, 0, &m_dwThreadID);
        if (!m_hThread)
            hr = E_FAIL;
    }
    
    return hr;
}

//-------------------------------------------------------------------------
//  CreateDefaultAllocatorPresenter
//
//  Why do we need default AP? In this sample, we use the same DirectDrawObject
//  for each VMR invovled in presenation. 
//-------------------------------------------------------------------------
HRESULT
CMultiSAP::CreateDefaultAllocatorPresenter()
{
    HRESULT hr = S_OK;
    IVMRMonitorConfig * pMonConf = NULL;
    
    __try 
    {
        CHECK_HR(hr = CoCreateInstance(CLSID_AllocPresenter, NULL,
                                       CLSCTX_INPROC_SERVER,
                                       IID_IVMRSurfaceAllocator,
                                       (LPVOID*)&m_pAlloc));
        
        CHECK_HR(hr = m_pAlloc->QueryInterface(IID_IVMRImagePresenter,
            (LPVOID*)&m_pPresenter));
        
        CHECK_HR(hr = m_pAlloc->QueryInterface(IID_IVMRWindowlessControl,
            (LPVOID*)&m_pWC));

        // Important! At this point, we advised out custom window AND now we
        // have access to DDrawObject related to it.
        
        CHECK_HR(hr = m_pWC->SetVideoClippingWindow(m_hwndApp));
  
        CHECK_HR(hr = m_pAlloc->QueryInterface(IID_IVMRMonitorConfig,
                                              (LPVOID*)&pMonConf));
        VMRMONITORINFO vmrMonInf;
        ZeroMemory( &vmrMonInf, sizeof(VMRMONITORINFO));
        DWORD nDevices = 0;

        CHECK_HR(hr = pMonConf->GetAvailableMonitors( &vmrMonInf, 1, &nDevices));
        m_hMonitor = vmrMonInf.hMon;
    }
    __finally 
    {        
        if (FAILED(hr)) 
        {
            SAFERELEASE( pMonConf );
            m_pWC = NULL;
            m_pPresenter = NULL;
            m_pAlloc = NULL;
        }
    }

    SAFERELEASE( pMonConf );
    
    return hr;
}

//-------------------------------------------------------------------------
//  InitializeEnvironment
//  creates default allocator-presenter and sets D3D environment
//-------------------------------------------------------------------------
HRESULT CMultiSAP::InitializeEnvironment()
{
    HRESULT hr;
//    m_hMonitor = MonitorFromWindow(m_hwndApp, MONITOR_DEFAULTTOPRIMARY);
    
    hr = CreateDefaultAllocatorPresenter();
    if (hr != S_OK)
        return hr;
    
    BITMAPINFOHEADER  bi = 
    {
        sizeof(BITMAPINFOHEADER), // biSize
            640,                      // biWidth
            480,                      // biHeight
            1,                        // biPlanes
            0,                        // biBitCount
            BI_RGB,                   // biCompression
            0,                        // biSizeImage,
            0,                        // biXpelsPerMeter
            0,                        // biYPelsPerMeter
            0,                        // biClrUsed
            0                         // biClrImportant
    };
    VMRALLOCATIONINFO ai = 
    {
        AMAP_3D_TARGET,             // dwFlags
        &bi,                        // lpHdr
        NULL,                       // lpPicFmt
        {4, 3},                     // szAspectRatio
        1,                          // dwMinBuffers
        1,                          // dwMaxBuffers
        0,                          // dwInterlaceFlags
        {640, 480}                  // szNativeSize
    };
    
    DWORD dwBuffers = 0;
    LPDIRECTDRAWSURFACE7 lpDDSurf;
    hr = m_pAlloc->AllocateSurface(0, &ai, &dwBuffers, &lpDDSurf);
    if (hr != DD_OK)
        return hr;
    
    DDSURFACEDESC2 ddsd = {sizeof(DDSURFACEDESC2)};
    hr = lpDDSurf->GetSurfaceDesc(&ddsd);
    if (hr != DD_OK) {
        return hr;
    }
    
    //
    // Overlay surfaces have these flags set, we need to remove
    // these flags prior to calling GetAttachedSurface
    //
    ddsd.ddsCaps.dwCaps &= ~(DDSCAPS_FRONTBUFFER | DDSCAPS_VISIBLE);
    
    hr = lpDDSurf->GetAttachedSurface(&ddsd.ddsCaps, &m_lpBackBuffer);
    
    
    m_lpBackBuffer->GetDDInterface((LPVOID *)&m_lpDDObj);
    
    //
    // get the h/w caps for this device
    //
    INITDDSTRUCT(m_ddHWCaps);
    m_lpDDObj->GetCaps(&m_ddHWCaps, NULL);   
    
    //
    // Create the device. The device is created off of our back buffer, which
    // becomes the render target for the newly created device. Note that the
    // z-buffer must be created BEFORE the device
    //    
    m_pD3DHelper = new CD3DHelper(m_lpBackBuffer, &hr);
    if(m_pD3DHelper == NULL || hr != DD_OK)
    {
        if(m_pD3DHelper == NULL)
        {
            hr = E_OUTOFMEMORY;
        }
        delete m_pD3DHelper;
    }
    
    SetRect(&m_rcDst, 0, 0, 640, 480);
    
#ifdef SPARKLE
    m_pSparkle = new CSparkle(m_lpDDObj);
    if (m_pSparkle)
        m_pSparkle->InitializeSparkle();
#endif
    
    return hr;
}

//-------------------------------------------------------------------------
//  RepositionMovie
//  Updates video position in windowless mode
//-------------------------------------------------------------------------
void CMultiSAP::RepositionMovie()
{
    RECT rcPos;
    
    GetMoviePosition(&rcPos);
    PutMoviePosition(rcPos);
}

//-------------------------------------------------------------------------
//  GetMoviePosition
//-------------------------------------------------------------------------
void CMultiSAP::GetMoviePosition( RECT * prc)
{
    GetClientRect(m_hwndApp, prc);
}

//-------------------------------------------------------------------------
//  PutMoviePosition
//-------------------------------------------------------------------------
void CMultiSAP::PutMoviePosition(RECT rc)
{
    CAutoLock Lock(&m_AppImageLock);
    m_pWC->SetVideoPosition(NULL, &rc);
}

//-------------------------------------------------------------------------
//  RePaint
//-------------------------------------------------------------------------
void CMultiSAP::RePaint()
{
    m_pWC->RepaintVideo(NULL, NULL);
}

//-------------------------------------------------------------------------
//  SetFocus
//  add sound management here
//-------------------------------------------------------------------------
void CMultiSAP::SetFocus()
{
    CMovie *pmovie = m_movieList.GetSelectedMovie();

    if(pmovie && pmovie->m_Fg)
    {
        // Tell the resource manager that we are being made active.  This
        // will then cause the sound to switch to THE SELECTED MEDIA SOURCE.  
        // This is especially
        // important when playing audio only files as there is no other
        // playback window.
        IResourceManager* pResourceManager;
        
        HRESULT hr = pmovie->m_Fg->QueryInterface(IID_IResourceManager, 
                                                 (void**)&pResourceManager);
        
        if(SUCCEEDED(hr))
        {
            IUnknown* pUnknown;
            
            hr = pmovie->m_Fg->QueryInterface(IID_IUnknown, (void**)&pUnknown);
            
            if(SUCCEEDED(hr))
            {
                pResourceManager->SetFocus(pUnknown);
                pUnknown->Release();
            }
            
            pResourceManager->Release();
        }
    }
}

//-------------------------------------------------------------------------
//  ReleaseFocus
//  add sound management here
//-------------------------------------------------------------------------
void CMultiSAP::ReleaseFocus()
{
    CMovie *pmovie = m_movieList.GetSelectedMovie();

    if(pmovie && pmovie->m_Fg)
    {
        // Tell the resource manager that we are being made active.  This
        // will then cause the sound to switch to THE SELECTED MEDIA SOURCE.  
        // This is especially
        // important when playing audio only files as there is no other
        // playback window.
        IResourceManager* pResourceManager;
        
        HRESULT hr = pmovie->m_Fg->QueryInterface(IID_IResourceManager, 
                                                 (void**)&pResourceManager);
        
        if(SUCCEEDED(hr))
        {
            IUnknown* pUnknown;
            
            hr = pmovie->m_Fg->QueryInterface(IID_IUnknown, (void**)&pUnknown);
            
            if(SUCCEEDED(hr))
            {
                pResourceManager->ReleaseFocus(pUnknown);
                pUnknown->Release();
            }
            
            pResourceManager->Release();
        }
    }
}

//
//  COMMAND FUNCTIONS
//

//-------------------------------------------------------------------------
//      Name:   CmdAddMovie
//      Desc:   Processes command "add movie" from the parent dialog
//      Parameters:     (sMovieInfo *)lParam;
//      Return: 
//      Other:   1. Create CMovie
//               2. Add movie to the end of the list
//               3. Start playing
//-------------------------------------------------------------------------
void CMultiSAP::CmdAddMovie(sMovieInfo* pMovInf)
{
    
    HRESULT hr = S_OK;
    RECT rc;
    CMovie *pmovie = NULL;

    CAutoLock Lock(&m_AppImageLock);

    CmdAddEffect(eEffectFading,2000, 300, 400, TRUE); // set next videoeffect "fading"
    
    if( m_pEffect ) // ping video effect change
    {
        m_pEffect->Finish();
    }
    
    if( !pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdAddMovie()\n"));
        return;
    }
    
    if( 0 == m_movieList.GetSize() )
    {
        ShowWindow( m_hwndApp, SW_SHOW);
    }
    
    pmovie = new CMovie;
    if( !pmovie )
    {
        OutputDebugStringA("Failed to allocate new movie in CmdAddMovie()\n");
        return;
    }
    pmovie->Initialize(pMovInf, this);

    if( FALSE == m_movieList.Add( pmovie ))
    {
        OutputDebugStringA("Failed to add new movie to the list in CmdAddMovie()\n");
        pmovie->Release();
        delete pmovie;
        return;
    }
        
    try
    {
        if( !m_movieList.GetMovie( pMovInf->pdwUserID) )
            throw;
        hr = m_movieList.GetMovie( pMovInf->pdwUserID)->OpenMovie();
    }
    catch(...)
    {
        pmovie->Release();
        delete pmovie;
        OutputDebugString(TEXT("Unhandled exception when trying to open the movie\n"));
        hr = E_POINTER;
    }
    
    if( FAILED(hr))
    {
        m_movieList.Delete( pMovInf->pdwUserID );

        if( m_bErrorMessage )
        {
            MessageBox(NULL, m_achErrorMessage, m_achErrorTitle, MB_ICONEXCLAMATION);
            m_bErrorMessage = false;
        }
        else
        {
#ifdef UNICODE
            swprintf( m_achErrorMessage, TEXT("Direct3D object returned error code 0x%08x.\r\n"), hr);
#else
            sprintf( m_achErrorMessage, TEXT("Direct3D object returned error code 0x%08x.\r\n"), hr);
#endif
            _tcsncat( m_achErrorMessage,  TEXT("Please use DirectX Error Lookup tool and verify DirectX\r\n")\
                                          TEXT("capabilities of your video driver. We are sorry for inconvenience.\r\n")\
                                          TEXT("You may want to try a different media file, or try a different video driver."), 2048);

            _tcsncpy( m_achErrorTitle, TEXT("Error when trying to render media file"), MAX_PATH);

            MessageBox(NULL, m_achErrorMessage, m_achErrorTitle, MB_ICONEXCLAMATION);
            m_bErrorMessage = false;
        }
        return;
    }

    GetMoviePosition(&rc);
    PutMoviePosition(rc);

    if( m_pEffect )
    {
        m_pEffect->Invalidate();
    }
    try
    {
        hr = PlayMovie(pMovInf->pdwUserID);
    }
    catch(...)
    {
        OutputDebugString(TEXT("Failed to start movie\n"));
        m_movieList.Delete( pMovInf->pdwUserID );
        hr = E_FAIL;
    }

    if( FAILED(hr))
    {
        m_movieList.Delete( pMovInf->pdwUserID );
    }
}

//-------------------------------------------------------------------------
//      Name:   CmdPlayMovie
//      Desc:   Processes command "play movie" from the parent dialog
//      Parameters:     (sMovieInfo *)lParam;
//      Return: 
//      Other:  just find this movie in the list and call its PlayMovie()
//-------------------------------------------------------------------------
void CMultiSAP::CmdPlayMovie(sMovieInfo* pMovInf)
{
    HRESULT hr = S_OK;
    
    if( NULL == pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdPlayMovie()\n"));
        return;
    }
    
    hr = PlayMovie( pMovInf->pdwUserID );
    if( FAILED(hr))
    {
        OutputDebugString(TEXT("Failed to play movie\n"));
    }
    
    return;
}

//-------------------------------------------------------------------------
//  CmdPauseMovie
//-------------------------------------------------------------------------
void CMultiSAP::CmdPauseMovie(sMovieInfo * pMovInf)
{
    int nVMR = -1;
    
    if( NULL == pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdPauseMovie()\n"));
        return;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdPauseMovie() received unrecognized UserID\n"));
        return;
    }
    
    OAFilterState State = pmovie->GetStateMovie();
    BOOL fPlaying = (State & State_Running);
    BOOL fPaused  = (State & State_Paused);
    
    if (fPlaying) 
    {
        pmovie->PauseMovie();
    }
    else if (fPaused) 
    {
        pmovie->PlayMovie();
    }
    
    return;
}

//-------------------------------------------------------------------------
//  CmdEjectMovie
//  
//  Function only sets "bDelete" flag for the movie and pings
//  videoeffect change
//-------------------------------------------------------------------------
void CMultiSAP::CmdEjectMovie(sMovieInfo * pMovInf)
{
    if( NULL == pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdPauseMovie()\n"));
        return;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdPauseMovie() received unrecognized UserID\n"));
        return;
    }   
    pmovie->m_bDelete = TRUE;

    CmdAddEffect(eEffectFading,2000, 300, 400, TRUE);
    
    if( m_pEffect )
    {
        m_pEffect->Finish();
    }
}

//-------------------------------------------------------------------------
//  CmdStopMovie
//-------------------------------------------------------------------------     
void CMultiSAP::CmdStopMovie(sMovieInfo * pMovInf)
{
    if( NULL == pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdStopMovie()\n"));
        return;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdStopMovie() received unrecognized UserID\n"));
        return;
    }
    
    pmovie->StopMovie();
    
    return;
}

//-------------------------------------------------------------------------
//  CmdExpandMovie
//  processes command "change selection" from the list box
//-------------------------------------------------------------------------
void CMultiSAP::CmdExpandMovie(sMovieInfo * pMovInf)
{
    CAutoLock Lock(&m_AppImageLock);

    if( NULL == pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdExpandMovie()\n"));
        return;
    }

    m_pdwNextSelectedMovie = pMovInf->pdwUserID;

    if( m_pEffect )
    {
        m_pEffect->Finish();
    }

    CmdAddEffect(eEffectFountain, 10, 10, 10, TRUE);

    return;
}

//-------------------------------------------------------------------------
//  CmdProcessDoubleClick
//  processes command "change selection" from the playback window
//-------------------------------------------------------------------------
void CMultiSAP::CmdProcessDoubleClick( int xPos, int yPos)
{
    if( !m_pEffect || eEffectStagePlaying != m_pEffect->GetStage() )
    {
        return;
    }

    RECT rect;
    GetClientRect( m_hwndApp, &rect );

    RECT rectRT = m_movieList.GetDefaultTarget();

    // given xPos, yPos are in client coordinates of the window;
    // transform then to client coordinates of the render target and find the movie

    float xPosRT = (float)xPos / (float)(WIDTH(&rect)) * (float)(WIDTH(&rectRT));
    float yPosRT = (float)yPos / (float)(HEIGHT(&rect)) * (float)(HEIGHT(&rectRT));

    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovieFromRTPoint( xPosRT, yPosRT);

    if( pmovie && pmovie->m_dwUserID != m_movieList.GetSelectedMovieID() )
    {
        m_pdwNextSelectedMovie = pmovie->m_dwUserID;
        if( m_pEffect )
        {
            m_pEffect->Finish();
        }

        CmdAddEffect(eEffectFountain, 10, 10, 10, TRUE);

        return;
    }
}

//-------------------------------------------------------------------------
//  CmdGetMovieState
//  
//  returns media control state of the movie (running, paused, or stopped)
//-------------------------------------------------------------------------
OAFilterState CMultiSAP::CmdGetMovieState(sMovieInfo* pMovInf)
{   
    if( !pMovInf )
    {
        OutputDebugString(TEXT("CmdNotifySelected received a wrong parameter\n"));
        return 0;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdNotifySelected received unrecognized UserID\n"));
        ZeroMemory( pMovInf, sizeof(sMovieInfo));
        return 0;
    }
    
    return pmovie->GetStateMovie();
}


//-------------------------------------------------------------------------
//  CmdSetMoviePosition
//
//  sets media position for the movie
//-------------------------------------------------------------------------
void CMultiSAP::CmdSetMoviePosition(sMovieInfo * pMovInf, REFTIME rtPos)
{
    if( !pMovInf )
    {
        OutputDebugString(TEXT("CmdNotifySelected received a wrong parameter\n"));
        return;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdNotifySelected received unrecognized UserID\n"));
        ZeroMemory( pMovInf, sizeof(sMovieInfo));
        return;
    }
    
    pmovie->SeekToPosition(rtPos, TRUE);
    return;
}

//-------------------------------------------------------------------------
//  CmdGetMoviePosition
//
//  gets media position of the movie
//-------------------------------------------------------------------------
REFTIME CMultiSAP::CmdGetMoviePosition(sMovieInfo * pMovInf)
{
    if( !pMovInf )
    {
        OutputDebugString(TEXT("CmdNotifySelected received a wrong parameter\n"));
        return (REFTIME)0;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdNotifySelected received unrecognized UserID\n"));
        ZeroMemory( pMovInf, sizeof(sMovieInfo));
        return (REFTIME)0;
    }
    
    return pmovie->GetCurrentPosition();
}

//-------------------------------------------------------------------------
//  CmdGetMovieDuration
// 
//  gets movie's duration, in   REFTIME
//-------------------------------------------------------------------------
REFTIME CMultiSAP::CmdGetMovieDuration(sMovieInfo * pMovInf)
{
    if( !pMovInf )
    {
        OutputDebugString(TEXT("CmdNotifySelected received a wrong parameter\n"));
        return (REFTIME)0;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdNotifySelected received unrecognized UserID\n"));
        ZeroMemory( pMovInf, sizeof(sMovieInfo));
        return (REFTIME)0;
    }
    
    return pmovie->GetDuration();
}

//-------------------------------------------------------------------------
//  CmdGetMovieFramesFlipped
//
//  returns number of delivered frames
//-------------------------------------------------------------------------
DWORD CMultiSAP::CmdGetMovieFramesFlipped(sMovieInfo* pMovInf) 
{   
    if( !pMovInf )
    {
        OutputDebugString(TEXT("CmdNotifySelected received a wrong parameter\n"));
        return 0;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdNotifySelected received unrecognized UserID\n"));
        return 0;
    }
    
    return pmovie->m_dwFrameCount;
}

//-------------------------------------------------------------------------
//  CmdAddEffect
//
//  adds new videoeffect to the effect queue
//-------------------------------------------------------------------------
void CMultiSAP::CmdAddEffect( eEffect effect, 
                              DWORD dwStartTime, 
                              LONG lPlayTime, 
                              DWORD dwEndTime, 
                              BOOL bAddFirst /*= FALSE*/)
{
    BOOL bRes = TRUE;
    CEffect *pEffect = NULL;

    switch( effect )
    {
        case eEffectDefault:
            pEffect = new CEffect(eEffectDefault);
            break;
        case eEffectStillArrangement:
            pEffect = new CEffectStillArrangement;
            break;
        case eEffectFading:
            pEffect = new CEffectFading;
            break;
        case eEffectFountain:
            pEffect = new CEffectFountain;
            break;
        default:
            OutputDebugStringA("Unsupported effect in CMultiSAP::CmdAddEffect\n");
            return;
    }

    if( !pEffect )
    {
        OutputDebugStringA("Failed to allocate new effect in CMultiSAP::CmdAddEffect\n");
        return;
    }

    HRESULT hr = pEffect->Initialize( &m_movieList, dwStartTime, lPlayTime, dwEndTime );
    if( FAILED( hr))
    {
        OutputDebugStringA("Failed to initialize a new effect\n");
        delete pEffect;
        return;
    }

    if( bAddFirst )
    {
        bRes = m_EffectQueue.AddLast( pEffect );
    }
    else
    {
        bRes = m_EffectQueue.AddFirst( pEffect );
    }
    if( FALSE == bRes )
    {
        OutputDebugStringA("Failed to add a new effect to the queue\n");
        delete pEffect;
        return;
    }
}

//-------------------------------------------------------------------------
//      Name:   CmdQuit
//      Desc:   correct termination of this thread upon the request from the dialog
//      Parameters:     
//      Return: 
//      Other:  (1) Stop all movies
//              (2) Set quit event
//-------------------------------------------------------------------------
void CMultiSAP::CmdQuit(sMovieInfo * pMovInf)
{
    for( int i=0; i<m_movieList.GetSize(); i++)
    {
        CMovie *pmovie = m_movieList.GetMovieByIndex(i);
        if( pmovie )
        {
            pmovie->PauseMovie();
            pmovie->StopMovie();
        }
    }
    
    return;
}


