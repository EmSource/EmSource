//----------------------------------------------------------------------------
//  File:   Movie.h
//
//  Desc:   DirectShow sample code
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------
#ifndef HEADER_MOVIE_FOR_MULTISAP
#define HEADER_MOVIE_FOR_MULTISAP

struct sMovieInfo;
class CMultiSAP;
class CEffect;
const int MaxNumberOfMovies = 8;

//----------------------------------------------------------------------------
//  Class:  CMovie
//  Desc:   basic functional support for a single movie graph filter to be
//          plugged in multi-filter system with custom allocator-presenter (CMultiSAP)
//----------------------------------------------------------------------------
class CMovie
{
public:
    CMovie();
    ~CMovie();

    // DirectShow specific members
    //

    CMultiSAP * m_pAP;      // pointer to custom allocator-presenter (which is CMultiSAP in this sample)

    // Custom AP takes control over surface allocation and presenting. When custom AP receives a call to
    // IVMRSurfaceAllocator::AllocateSurface, it allocates primary surface with at least one
    // back buffer.  Primary surface is to be flipped every time we present image, to let upstream
    // filters write into the back buffer while presenting
    CComPtr<IDirectDrawSurface7>    m_lpDDDecode;   // Front buffer
    CComPtr<IDirectDrawSurface7>    m_lpDDTexture;  // Back buffer

    CComPtr<IBaseFilter>                m_Bf;       // VMR
    CComPtr<IFilterGraph>               m_Fg;       // filter graph
    CComPtr<IGraphBuilder>              m_Gb;       // graph builder
    CComPtr<IMediaControl>              m_Mc;       // media control
    CComPtr<IMediaSeeking>              m_Ms;       // media seeking
    CComPtr<IMediaEvent>                m_Me;       // media event processing
    CComPtr<IVMRSurfaceAllocatorNotify> m_SAN;      // allows to advise and unadvise custom AP, as well as  
                                                    // to call functions of the default AP


    // Movie specific members
    //
    WCHAR           m_achPath[MAX_PATH];    // path to the source media file
    HANDLE          m_MediaEvent;           // VMR event handle
    GUID            m_TimeFormat;           // time format of the current movie
    DWORD_PTR       m_dwUserID;             // Unique identifier for this movie. When several sources
                                            // are connected to the same allocator-presenter (AP),
                                            // dwUserID is the way to differentiate which movie is calling AP
    bool            m_bInitialized;         // true when movie is connected to custom AP
    LONGLONG        m_llDuration;           // duration of the movie
    BOOL            m_bDirectedFlips;       // TRUE if flag AMAP_DIRECTED_FLIP is specified in AllocateSurface()
                                            // see help on "IVMRSurfaceAllocator::AllocateSurface" for details
    DWORD           m_dwFrameCount;         // frame counter


    // Videoframe geometry specific members
    //
    RECT            m_rcSrc;                // rectangle of the source
    RECT            m_rcDst;                // rectangle of the render target
    SIZE            m_VideoSize;            // orifinal video size
    SIZE            m_VideoAR;              // original aspect ratio
    // this sample uses flexible vertex format; see declaration of Vertex in DDrawSupport.h
    // each frame is represented with four vertices: (l,t)-(r,t)-(l,b)-(r,b) that allows
    // triangle strip DDraw primitives
    // the following three vertex buffers are used:
    Vertex          m_Vdef[4];  // "default" coordinates of the frame, i.e. frame location in the beginning
                                // and in the end of each video effect. In this sample, frames are lined-up
                                // horizontally in the middle of the render target
    Vertex          m_Vcur[4];  // coordinates of the frame for particular effect in time t.
    Vertex          m_Vrnd[4];  // auxiliary buffer, its use depends on implementation of CEffect
    float           m_fZ;       // when rendering several movies in 3D, we need a z-order of frames
    BYTE            m_bAlpha;   // alpha-level of the frame
    BOOL            m_bUseInTheScene;   // TRUE if movie is used in the current scene; this flag is needed
                                        // when we add movies and want to postpone this event to the
                                        // end of the current video effect, which provides "smooth" picture
    BOOL            m_bDelete;          // TRUE if user specified to delete this movie; movie remains in the list
                                        // to the end of the current effect
    BOOL            m_bPresented;       // TRUE if this movie engaged at least one call of PresentImage

    // configuring functions
    void            Initialize( sMovieInfo * pMovInf, CMultiSAP * pSAP);
    HRESULT         AddVideoMixingRendererToFG();
    HRESULT         FindInterfaceFromFilterGraph(REFIID iid, LPVOID *lp);
    void            Release();
    HRESULT         CheckVMRConnection();

    // basic operations
    HRESULT         OpenMovie();    
    HRESULT         PlayMovie();                    
    HRESULT         PauseMovie();                   
    HRESULT         StopMovie();                    
    HRESULT         CloseMovie();                   
    BOOL            SeekToPosition(REFTIME rt,BOOL bFlushData);             
    BOOL            PutMoviePosition(LONG x, LONG y, LONG cx, LONG cy);     
    BOOL            FrameStepMovie();                                       
    BOOL            SetTimeFormat(GUID Format);                             

    // data/state access functions
    OAFilterState   GetStateMovie();                
    REFTIME         GetCurrentPosition();                                   
    HANDLE          GetMovieEventHandle();          
    long            GetMovieEventCode();            
    BOOL            GetMoviePosition(LONG *x, LONG *y, LONG *cx, LONG *cy); 
    BOOL            GetNativeMovieSize(LONG *cx, LONG *cy);                 
    BOOL            CanMovieFrameStep();                                    
    REFTIME         GetDuration();                                          
    BOOL            IsTimeFormatSupported(GUID Format);                     
    BOOL            IsTimeSupported();                                      
    GUID            GetTimeFormat();    

};


//----------------------------------------------------------------------------
//  Class:  CMovieList
//  Desc:   list of CMovies in the presentation
//----------------------------------------------------------------------------

class CMovieList
{
    CCritSec    m_AppImageLock;
    RECT        m_rcDefaultTarget;              // all the coordinate calculations are done for some
                                                // const render target rectangle that to be resized when 
                                                // delivering image to the display, to regard sizes of
                                                // video playback window
    int         m_nsize;                        // nimber of movies in the list
    DWORD       m_dwSelectedMovieID;            // UserID of the selected movie
    CMovie *    m_ppMovies[ MaxNumberOfMovies ];// since number of movies is so small, we use statically
                                                // allocated array to store pointers to them
public:
    CMovieList();
    ~CMovieList();

    // list operations
    BOOL SelectMovie( DWORD_PTR pdwID);
    BOOL Add( CMovie *pmovie);
    BOOL Delete( DWORD_PTR dwID);
    void SortByZ();

    // "Get" functions
    RECT GetDefaultTarget();
    CMovie * GetMovie( DWORD_PTR dwID );
    CMovie * GetMovieByIndex( int n );
    CMovie * GetSelectedMovie();
    CMovie * GetMovieFromRTPoint( float xRT, float yRT);
    DWORD_PTR GetSelectedMovieID();
    int GetSize()
    {
        return m_nsize;
    }

    void ActivateAll();                 // allows all the movies from the list to be part of presentation
    void RemoveDeletedMovies();         // removes all the movies signed as "delete" from the list
    void SetDefaultTarget( RECT rcDT);  // sets default target rectangle
};

#endif