//------------------------------------------------------------------------------
// File: GamePlayer.h
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#pragma warning(push)
#pragma warning(disable:4702)
#include <list>
#pragma warning(pop)

#include "MultigraphSession.h"
#include "CustomMixer.h"
#include "CustomUILayer.h"

using namespace std;

// CGamePlayerApp:
// See GamePlayer.cpp for the implementation of this class
//

/******************************Public*Routine******************************\
* class CGamePlayerApp
*
* application class
\**************************************************************************/
class CGamePlayerApp : public CWinApp
{
public:
    CGamePlayerApp();
    BOOL VerifyVMR9(void);

// Overrides
    public:
    virtual BOOL InitInstance();

// Implementation

    DECLARE_MESSAGE_MAP()
};

extern CGamePlayerApp theApp;

///////////////////////////////////// CGamePlayerSession //////////////////////////
/*********************************************************************************\
* class CGamePlayerSession
* wrapper for the part of the sample related to using MultiVMR9.dll
\*********************************************************************************/
class CGamePlayerSession : public CMultigraphSession
{
public:
    CGamePlayerSession();
    virtual ~CGamePlayerSession();

    virtual HRESULT Initialize();

private:
    CGameMixer*             m_pMixer;
    CGameUILayer*           m_pUI;

};

