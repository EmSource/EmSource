//-----------------------------------------------------------------------------
// File: DrumPad.h
//
// Desc: Header file for the DrumPad class.
//
// Copyright( c ) 1998-2001 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef _DRUMPAD_H_
#define _DRUMPAD_H_

#include <windows.h>
#include "dsutil.h"

//-----------------------------------------------------------------------------
// Name: class DrumPad
// Desc: Manages sound sample for play back
//-----------------------------------------------------------------------------
class DrumPad
{
public:
    DrumPad();
    ~DrumPad();

public:
    BOOL    Initialize( DWORD dwNumElements, HWND hwnd );

    BOOL    Load( DWORD dwID, const TCHAR* tcszFilename );
    BOOL    Play( DWORD dwID, DWORD paramX, DWORD paramY );
    const   TCHAR* GetName( DWORD dwID );

protected:
    VOID    CleanUp();

protected:
    CSoundManager* m_lpSoundManager;
    CSound **       m_lpSamples;
    DWORD           m_dwNumSamples;
    TCHAR **        m_lpNames;
    BOOL            m_bInit;
};

#endif _DRUMPAD_H_