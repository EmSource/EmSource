//========= Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Memory allocation!
//
// $NoKeywords: $
//=============================================================================//

#ifndef TIER0_MEM_H
#define TIER0_MEM_H

#pragma once

#include <stddef.h>

#include "tier0/platform.h"

#if !defined(STATIC_TIER0) && !defined(_STATIC_LINKED)

#ifdef TIER0_DLL_EXPORT
#  define MEM_INTERFACE DLL_EXPORT
#else
#  define MEM_INTERFACE DLL_IMPORT
#endif

#else // BUILD_AS_DLL

#define MEM_INTERFACE extern

#endif // BUILD_AS_DLL



//-----------------------------------------------------------------------------
// DLL-exported methods for particular kinds of memory
//-----------------------------------------------------------------------------
MEM_INTERFACE void *MemAllocScratch( int nMemSize );
MEM_INTERFACE void MemFreeScratch();

//Only works with USE_MEM_DEBUG and memory allocation call stack tracking enabled.
MEM_INTERFACE int GetAllocationCallStack( void *mem, void **pCallStackOut, int iMaxEntriesOut );

MEM_INTERFACE void MemOutOfMemory( size_t nBytesAttempted );

#endif /* TIER0_MEM_H */
