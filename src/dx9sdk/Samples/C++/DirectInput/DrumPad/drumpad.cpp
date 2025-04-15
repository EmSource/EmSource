//-----------------------------------------------------------------------------
// File: DrumPad.cpp
//
// Desc: Implementation of DrumPad class
//
// Copyright( c ) 1998-2001 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <tchar.h>

#include "drumpad.h"
#include "dxutil.h"



//-----------------------------------------------------------------------------
// Name: DrumPad()
// Desc: Constructor
//-----------------------------------------------------------------------------
DrumPad::DrumPad()
{
    m_lpSoundManager = NULL;
    m_lpSamples      = NULL;
    m_lpNames        = NULL;
    m_dwNumSamples   = 0;
    m_bInit          = FALSE;
}




//-----------------------------------------------------------------------------
// Name: ~DrumPad()
// Desc: Destructor
//-----------------------------------------------------------------------------
DrumPad::~DrumPad()
{
    CleanUp();
}




//-----------------------------------------------------------------------------
// Name: CleanUp()
// Desc: Reset the object
//-----------------------------------------------------------------------------
VOID DrumPad::CleanUp()
{
    DWORD i;
 
    // free the samples
    for( i = 0; i < m_dwNumSamples; i++ )
    {
        SAFE_DELETE( m_lpSamples[i] );
        SAFE_DELETE_ARRAY( m_lpNames[i] );
    }

    SAFE_DELETE_ARRAY( m_lpSamples );
    SAFE_DELETE_ARRAY( m_lpNames );

    // free the sound manager
    SAFE_DELETE( m_lpSoundManager );

    m_bInit = FALSE;
}




//-----------------------------------------------------------------------------
// Name: Initialize()
// Desc: Initialize the number of samples and the window 
//-----------------------------------------------------------------------------
BOOL DrumPad::Initialize( DWORD dwNumElements, HWND hwnd )
{
    // start clean
    CleanUp();

    // allocate new sound manager
    m_lpSoundManager = new CSoundManager;
    if( NULL == m_lpSoundManager )
        return FALSE;

    // initialize to stereo, Freq = 22050 Hz, 16 bit samples
    if( FAILED( m_lpSoundManager->Initialize( hwnd, DSSCL_PRIORITY ) ) )
        return FALSE;   
    if( FAILED( m_lpSoundManager->SetPrimaryBufferFormat( 2, 22050, 16 ) ) )
        return FALSE;

    // allocate array for the sample
    m_lpSamples = new CSound*[ dwNumElements ];
    if( NULL == m_lpSamples )
    {
        CleanUp();
        return FALSE;
    }

    // allocate array to hold filename
    m_lpNames = new TCHAR*[ dwNumElements ];
    if( NULL == m_lpNames )
    {
        CleanUp();
        return FALSE;
    }

    ZeroMemory( m_lpSamples, sizeof(CSound*) * dwNumElements );
    ZeroMemory( m_lpNames, sizeof(TCHAR*) * dwNumElements );
    m_dwNumSamples = dwNumElements;
    m_bInit = TRUE;

    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: Load()
// Desc: Load a sample for playback
//-----------------------------------------------------------------------------
BOOL DrumPad::Load( DWORD id, const TCHAR* tcszFilename )
{
    if( !m_bInit )
        return FALSE;

    if( id >= m_dwNumSamples )
        return FALSE;

    if( NULL == tcszFilename )
        return FALSE;

    HRESULT hr;
    CWaveFile waveFile;
    CSound* lpSound = NULL;

    if( -1 == GetFileAttributes(tcszFilename) )
        return FALSE;
    
    // Load the wave file
    if( FAILED( hr = waveFile.Open(( TCHAR* ) tcszFilename, NULL, WAVEFILE_READ ) ) )
    {
        waveFile.Close();
        return FALSE;
    }
    waveFile.Close();

    // create the sample object
    if( FAILED( m_lpSoundManager->Create( &lpSound, (TCHAR*) tcszFilename, 
                                          DSBCAPS_STICKYFOCUS, GUID_NULL ) ) )
        return FALSE;

    // clean up existing sample
    SAFE_DELETE( m_lpSamples[id] );

    // clean up the name for the existing sample
    SAFE_DELETE_ARRAY( m_lpNames[id] )

    m_lpSamples[id] = lpSound;
    m_lpNames[id] = new TCHAR[ _tcslen( tcszFilename ) + 2 ];
    _tcscpy( m_lpNames[id], tcszFilename );

    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: Play()
// Desc: Play back a sample
//-----------------------------------------------------------------------------
BOOL DrumPad::Play( DWORD id, DWORD paramX, DWORD paramY )
{
    if( !m_bInit )
        return FALSE;

    if( id >= m_dwNumSamples )
        return FALSE;

    if( NULL == m_lpSamples[id] )
        return FALSE;

    // stop, reset, and play
    m_lpSamples[id]->Stop();
    m_lpSamples[id]->Reset();
    m_lpSamples[id]->Play( 0, 0 );

    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: GetName()
// Desc: Get the filename associated with index
//-----------------------------------------------------------------------------
const TCHAR* DrumPad::GetName( DWORD id )
{
    if( !m_bInit )
        return NULL;

    if( id >= m_dwNumSamples )
        return NULL;

    return m_lpNames[id];
}




