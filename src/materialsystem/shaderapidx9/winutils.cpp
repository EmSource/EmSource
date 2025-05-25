//======Copyright 1996-2006, Valve Corporation, All rights reserved. ======//
//
// winutils.cpp
//
//===========================================================================//

#include "winutils.h"

#ifndef _WIN32

#ifdef USE_SDL
#include "SDL.h"
#endif

void GlobalMemoryStatus( MEMORYSTATUS *pOut )
{
	//cheese: return 2GB physical
	pOut->dwTotalPhys = (1<<31);
}

void Sleep( unsigned int ms )
{
	DebuggerBreak();
	ThreadSleep( ms );
}

bool IsIconic( VD3DHWND hWnd )
{
	// FIXME for now just act non-minimized all the time
	//DebuggerBreak();
	return false;
}

BOOL ClientToScreen( VD3DHWND hWnd, LPPOINT pPoint )
{
	DebuggerBreak();
	return true;
}

void* GetCurrentThread()
{
	DebuggerBreak();
	return 0;
}

void SetThreadAffinityMask( void *hThread, int nMask )
{
	DebuggerBreak();
}

void GetClientRect( void *hWnd, RECT *destRect )
{
	// the only useful answer this call can offer, is the size of the canvas.
	// actually getting the window bounds is not useful.
	// so, see if a D3D device is up and running, and if so,
	// dig in and find out its backbuffer size and use that.

	int width, height;
#ifdef USE_SDL
    SDL_GetWindowSize( (SDL_Window*)hWnd, &width, &height );
#else
#error
#endif
	Assert( width!=0 && height!=0 );

	destRect->left = 0;
	destRect->top = 0;
	destRect->right = width;
	destRect->bottom = height;		
}

#endif
