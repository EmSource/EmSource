//================ Copyright (c) 1996-2012 Valve Corporation. All Rights Reserved. =================
//
// dxabstract_types.h
//
//==================================================================================================

#ifndef DXABSTRACT_TYPES_H
#define DXABSTRACT_TYPES_H

#pragma once

#define TOGL_INTERFACE
#define TOGL_OVERLOAD
#define TOGL_CLASS
#define TOGL_GLOBAL
#define TOGLMETHODCALLTYPE
#define DXABSTRACT_BREAK_ON_ERROR() DebuggerBreak()
#define D3DXINLINE inline
#define D3D_OK									S_OK
#define D3DXSHADER_DEBUG                    (1 << 0)
#define D3DXSHADER_AVOID_FLOW_CONTROL       (1 << 9)


class TOGL_CLASS D3DXMATRIX : public D3DMATRIX
{
public:
	D3DXMATRIX operator*( const D3DXMATRIX &o ) const;
	operator FLOAT* ();
	float& operator()( int row, int column );
	const float& operator()( int row, int column ) const;
	bool operator != ( CONST D3DXMATRIX& src ) const;
};

// ------------------------------------------------------------------------------------------------------------------------------ //
// STRUCTURES
// ------------------------------------------------------------------------------------------------------------------------------ //

typedef struct TOGL_CLASS D3DXPLANE
{
	float& operator[]( int i );
	bool operator==( const D3DXPLANE &o );
	bool operator!=( const D3DXPLANE &o );
	operator float*();
	operator const float*() const;

	float a, b, c, d;
} D3DXPLANE;

class TOGL_CLASS D3DXVECTOR2
{
public:
    operator FLOAT* ();
    operator CONST FLOAT* () const;

	float x,y;
};

class TOGL_CLASS D3DXVECTOR3 : public D3DVECTOR
{
public:
	D3DXVECTOR3() {}
	D3DXVECTOR3( float a, float b, float c );
    operator FLOAT* ();
    operator CONST FLOAT* () const;
};

typedef enum _D3DXINCLUDE_TYPE
{
    D3DXINC_LOCAL,

    // force 32-bit size enum
    D3DXINC_FORCE_DWORD = 0x7fffffff

} D3DXINCLUDE_TYPE;

class TOGL_CLASS D3DXVECTOR4
{
public:
	D3DXVECTOR4() {}
	D3DXVECTOR4( float a, float b, float c, float d );

	float x,y,z,w;
};

//----------------------------------------------------------------------------
// D3DXMACRO:
// ----------
// Preprocessor macro definition.  The application pass in a NULL-terminated
// array of this structure to various D3DX APIs.  This enables the application
// to #define tokens at runtime, before the file is parsed.
//----------------------------------------------------------------------------

typedef struct _D3DXMACRO
{
    LPCSTR Name;
    LPCSTR Definition;

} D3DXMACRO, *LPD3DXMACRO;

#endif // DXABSTRACT_TYPES_H
