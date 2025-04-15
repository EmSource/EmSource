//-----------------------------------------------------------------------------
// File: StagedPeer.h
//
// Desc: 
//
// Copyright (C) 2000 Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef STAGEDPEER_H
#define STAGEDPEER_H

#define MAX_PLAYER_NAME     14

struct APP_PLAYER_INFO
{
    LONG  lRefCount;                         // Ref count so we can cleanup when all threads 
                                             // are done w/ this object
    DPNID dpnidPlayer;			             // dpnid of the player
    DWORD dwFlags;                           // Player flags
    DWORD dwSlotIndex;                       // Index of the slot associated with this player
    char  strPlayerName[MAX_PLAYER_NAME];  // String name of the player 
};

#endif // STAGEDPEER_H
