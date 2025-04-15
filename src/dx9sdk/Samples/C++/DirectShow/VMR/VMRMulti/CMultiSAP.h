//----------------------------------------------------------------------------
//  File:   CMultiSAP.h
//
//  Desc:   DirectShow sample code
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------
#ifndef HEADER_CMULTISAP
#define HEADER_CMULTISAP


// #define MAXMOVIES 7
struct sDialogInfo;

#define CHK_RANGE( n, size, err, expr)\
if( n<0 || n> size-1 ) { return err; } else { return (expr); }

//----------------------------------------------------------------------------
//  Class:  CMultiSAP
//  Desc:   sample of custom Allocator-presenter 
//----------------------------------------------------------------------------
class CMultiSAP :
        public CUnknown,
        public IVMRSurfaceAllocator,
        public IVMRImagePresenter,
        public IAMGraphBuilderCallback
{
    
private:
    CCritSec         m_AppImageLock;
    HWND             m_hwndApp;             // target video playback window
    RECT             m_rcDst;               // client size of the window
    CMovieList       m_movieList;           // list of movies in the presentation
    DWORD            m_DlgTID;              // thread ID of the parent dialog (the one that gets user input)
    DWORD            m_dwThreadID;          // ID of the thread where custom AP manager resides
    HANDLE           m_hThread;             // handle to the thread where custom AP manager resides
    HANDLE           m_hQuitEvent;          // handle to the quit event
        
    CEffectQueue     m_EffectQueue;         // presentation is a sequence of videoeffects
    CEffect*         m_pEffect;             // current videoeffect
    DWORD_PTR        m_pdwNextSelectedMovie;// 

    HMONITOR                    m_hMonitor;     // monitor handle
    CComPtr<IDirectDraw7>       m_lpDDObj;      // DirectDraw object
    CD3DHelper*                 m_pD3DHelper;   // object that performs most DirectDraw stuff
    CSparkle*                   m_pSparkle;     // sparkle effect on the background
    DWORD                       m_dwFrameNum;   // number of frames drawn

    TCHAR                       m_achErrorMessage[2048];
    TCHAR                       m_achErrorTitle[MAX_PATH];
    bool                        m_bErrorMessage;
    
    // DirectShow specific members
    DDCAPS                          m_ddHWCaps;     // hardware capabilities
    CComPtr<IVMRWindowlessControl>  m_pWC;          // windowless control
    CComPtr<IVMRSurfaceAllocator>   m_pAlloc;       // DEFAULT allocator presenter
    CComPtr<IVMRImagePresenter>     m_pPresenter;   // image presenter
    CComPtr<IDirectDrawSurface7>    m_lpBackBuffer; // back buffer
 
    
    // Allocator-presenter specific functions
    //
    HRESULT CreateDefaultAllocatorPresenter();

    HRESULT InitializeEnvironment();

    HRESULT AllocateSurfaceWorker(  CMovie *pmovie,
                                    DWORD dwFlags,
                                    LPBITMAPINFOHEADER lpHdr,
                                    LPDDPIXELFORMAT lpPixFmt,
                                    LPSIZE lpAspectRatio,
                                    DWORD dwMinBackBuffers,
                                    DWORD dwMaxBackBuffers,
                                    DWORD* lpdwBackBuffer,
                                    LPDIRECTDRAWSURFACE7* lplpSurface,
                                    DDSURFACEDESC2* pddsdDisplay);

    HRESULT AllocateOverlaySurface(
                            LPDIRECTDRAWSURFACE7* lplpSurf,
                            DWORD dwFlags,
                            DDSURFACEDESC2* pddsd,
                            DWORD dwMinBuffers,
                            DWORD dwMaxBuffers,
                            DWORD* lpdwBuffer
                            );

    HRESULT AllocateOffscreenSurface(
                                        LPDIRECTDRAWSURFACE7* lplpSurf,
                                        DWORD dwFlags,
                                        DDSURFACEDESC2* pddsd,
                                        DWORD dwMinBuffers,
                                        DWORD dwMaxBuffers,
                                        DWORD* lpdwBuffer,
                                        BOOL fAllowBackBuffer
                                        );

    HRESULT CreateBackBuffers(  LPDIRECTDRAWSURFACE7 lpSurf7FB,
                                DDSURFACEDESC2* pddsd,
                                LPDWORD lpdwBackBuffer);
        
    // Interaction with parent dialog    

    DWORD WaitForDialog();
        
        
public:
    CMultiSAP(HWND hwndApplication, HRESULT *phr);
    ~CMultiSAP();
    
    static DWORD WINAPI ComposeThreadProc(LPVOID lpParameter);
    DWORD ComposeThread();

    //
    // Interface implementation
    //
 
    DECLARE_IUNKNOWN STDMETHODIMP NonDelegatingQueryInterface(REFIID, void**);
    
    // IVMRSurfaceAllocator implementation
    //
    STDMETHODIMP AllocateSurface(   DWORD_PTR w,
                                    VMRALLOCATIONINFO *lpAllocInfo,
                                    DWORD* lpdwActualBackBuffers,
                                    LPDIRECTDRAWSURFACE7* lplpSurface);

    STDMETHODIMP FreeSurface( DWORD_PTR w );

    STDMETHODIMP PrepareSurface(    DWORD_PTR w, 
                                    LPDIRECTDRAWSURFACE7 lplpSurface,
                                    DWORD dwSurfaceFlags);

    STDMETHODIMP AdviseNotify(IVMRSurfaceAllocatorNotify* lpIVMRSurfAllocNotify);
    
    
    // IVMRImagePresenter implementation

    STDMETHODIMP StartPresenting(DWORD_PTR w);

    STDMETHODIMP StopPresenting(DWORD_PTR w);

    STDMETHODIMP PresentImage(DWORD_PTR w, VMRPRESENTATIONINFO* p);
    
    // IAMGraphBuilderCallback implementation

    STDMETHODIMP SelectedFilter( IMoniker *pMon );

    STDMETHODIMP CreatedFilter( IBaseFilter *pBf );
    
    // commands from the parent dialog
    void CmdAddMovie( sMovieInfo* pMovInf );
    void CmdPlayMovie( sMovieInfo* pMovInf );
    void CmdPauseMovie( sMovieInfo* pMovInf );
    void CmdEjectMovie( sMovieInfo* pMovInf );
    void CmdStopMovie( sMovieInfo* pMovInf );
    void CmdExpandMovie( sMovieInfo* pMovInf );

    void CmdAddEffect(  eEffect effect, 
                        DWORD dwStartTime, 
                        LONG lPlayTime, 
                        DWORD dwEndTime, 
                        BOOL bAddFirst = FALSE);
    void CmdProcessDoubleClick( int xPos, int yPos);
    
    REFTIME CmdGetMovieDuration( sMovieInfo* pMovInf );
    REFTIME CmdGetMoviePosition( sMovieInfo* pMovInf );
    void CmdSetMoviePosition( sMovieInfo* pMovInf, REFTIME rtPos );
    
    DWORD CmdGetMovieFramesFlipped( sMovieInfo* pMovInf );
    OAFilterState CmdGetMovieState( sMovieInfo* pMovInf );
    
    void CmdQuit(sMovieInfo* pMovInf);
    
    // Scene composition and rendering
    void ComposeAndRender();
    
    // app specific functions
    HRESULT Initialize();
    void RePaint();
    void RepositionMovie();
    void GetMoviePosition( RECT * rc);
    void PutMoviePosition( RECT rc);

    // Command functions
    
    HRESULT OpenMovie( DWORD_PTR dwID )
    {
        CMovie *pmovie = m_movieList.GetMovie( dwID );
        if( pmovie )
        {
            return pmovie->OpenMovie();
        }
        return E_INVALIDARG;
    }
    
    HRESULT PlayMovie( DWORD_PTR dwID)
    {
        CMovie *pmovie = m_movieList.GetMovie( dwID );
        if( pmovie )
        {
            return pmovie->PlayMovie();
        }
        return E_INVALIDARG;
    }
    
    HANDLE GetMovieEventHandle( DWORD_PTR dwID)
    {
        CMovie *pmovie = m_movieList.GetMovie( dwID );
        if( pmovie )
        {
            return pmovie->GetMovieEventHandle();
        }
        return NULL;
    }
    
    LONG GetMovieEventCode( DWORD_PTR dwID)
    {
        CMovie *pmovie = m_movieList.GetMovie( dwID );
        if( pmovie )
        {
            return pmovie->GetMovieEventCode();
        }
        return NULL;
    }
    
    HANDLE          GetQuitEvent()  { return m_hQuitEvent; }
    int             GetSize()       { return m_movieList.GetSize(); }
    HWND            GetWnd()        { return m_hwndApp; }
    LPDIRECTDRAW7   GetDDObject()   { return m_lpDDObj; }
    HMONITOR        GetMonitor()    { return m_hMonitor; }
    
    DWORD           GetCurrentFrameNumber() { return m_dwFrameNum;}
    
    void            SetFocus();
    void            ReleaseFocus();
    void            DeleteAllMovies();
};

#endif