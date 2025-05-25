//================ Copyright (c) 1996-2009 Valve Corporation. All Rights Reserved. =================
//
//
//
//==================================================================================================

#ifndef WINUTILS_H
#define WINUTILS_H

#pragma once

#include "togl/rendermechanism.h"

#ifndef ZeroMemory
#define ZeroMemory( ptr, size ) memset( ptr, 0, size )
#endif

#if !defined(_WIN32)
	void Sleep( unsigned int ms );
	bool IsIconic( VD3DHWND hWnd );
	BOOL ClientToScreen( VD3DHWND hWnd, LPPOINT pPoint );
	void* GetCurrentThread();
	void SetThreadAffinityMask( void *hThread, int nMask );
	void GlobalMemoryStatus( MEMORYSTATUS *pOut );
	void GetClientRect( void *hWnd, RECT *destRect );
#endif

#endif // WINUTILS_H
