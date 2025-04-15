//-----------------------------------------------------------------------------
// File: GameMenu.h
//
// Desc: Code for in-game menus
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once


//-----------------------------------------------------------------------------
// Name: class CMenuItem
// Desc: 
//-----------------------------------------------------------------------------
class CMenuItem
{
public:
    TCHAR       strLabel[80];
    DWORD       dwID;
    CMenuItem*  pParent;

    CMenuItem*  pChild[10];
    DWORD       dwNumChildren;

    DWORD       dwSelectedMenu;

public:
    HRESULT Render( CD3DFont* pFont );
    
    CMenuItem* Add( CMenuItem* );

    CMenuItem( TCHAR* strLabel, DWORD dwID );
    ~CMenuItem();
};

