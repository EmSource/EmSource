//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: SSE Math primitives.
//
//=====================================================================================//

#include <math.h>
#include <float.h>	// needed for flt_epsilon
#include "basetypes.h"
#include "tier0/dbg.h"
#include "mathlib/mathlib.h"
#include "mathlib/vector.h"
#include "sse.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static const uint32 _sincos_masks[]	  = { (uint32)0x0,  (uint32)~0x0 };
static const uint32 _sincos_inv_masks[] = { (uint32)~0x0, (uint32)0x0 };

//-----------------------------------------------------------------------------
// Macros and constants required by some of the SSE assembly:
//-----------------------------------------------------------------------------

#ifdef _WIN32
	#define _PS_EXTERN_CONST(Name, Val) \
		const __declspec(align(16)) float _ps_##Name[4] = { Val, Val, Val, Val }

	#define _PS_EXTERN_CONST_TYPE(Name, Type, Val) \
		const __declspec(align(16)) Type _ps_##Name[4] = { Val, Val, Val, Val }; \

	#define _EPI32_CONST(Name, Val) \
		static const __declspec(align(16)) __int32 _epi32_##Name[4] = { Val, Val, Val, Val }

	#define _PS_CONST(Name, Val) \
		static const __declspec(align(16)) float _ps_##Name[4] = { Val, Val, Val, Val }
#elif POSIX
	#define _PS_EXTERN_CONST(Name, Val) \
		const float _ps_##Name[4] __attribute__((aligned(16))) = { Val, Val, Val, Val }

	#define _PS_EXTERN_CONST_TYPE(Name, Type, Val) \
		const Type _ps_##Name[4]  __attribute__((aligned(16))) = { Val, Val, Val, Val }; \

	#define _EPI32_CONST(Name, Val) \
		static const int32 _epi32_##Name[4]  __attribute__((aligned(16))) = { Val, Val, Val, Val }

 	#define _PS_CONST(Name, Val) \
 		static const float _ps_##Name[4]  __attribute__((aligned(16))) = { Val, Val, Val, Val }
#endif

_PS_EXTERN_CONST(am_0, 0.0f);
_PS_EXTERN_CONST(am_1, 1.0f);
_PS_EXTERN_CONST(am_m1, -1.0f);
_PS_EXTERN_CONST(am_0p5, 0.5f);
_PS_EXTERN_CONST(am_1p5, 1.5f);
_PS_EXTERN_CONST(am_pi, (float)M_PI);
_PS_EXTERN_CONST(am_pi_o_2, (float)(M_PI / 2.0));
_PS_EXTERN_CONST(am_2_o_pi, (float)(2.0 / M_PI));
_PS_EXTERN_CONST(am_pi_o_4, (float)(M_PI / 4.0));
_PS_EXTERN_CONST(am_4_o_pi, (float)(4.0 / M_PI));
_PS_EXTERN_CONST_TYPE(am_sign_mask, int32, (int)0x80000000);
_PS_EXTERN_CONST_TYPE(am_inv_sign_mask, int32, ~0x80000000);
_PS_EXTERN_CONST_TYPE(am_min_norm_pos,int32, 0x00800000);
_PS_EXTERN_CONST_TYPE(am_mant_mask, int32, (int)0x7f800000);
_PS_EXTERN_CONST_TYPE(am_inv_mant_mask, int32, ~0x7f800000);

_EPI32_CONST(1, 1);
_EPI32_CONST(2, 2);

_PS_CONST(sincos_p0, 0.15707963267948963959e1f);
_PS_CONST(sincos_p1, -0.64596409750621907082e0f);
_PS_CONST(sincos_p2, 0.7969262624561800806e-1f);
_PS_CONST(sincos_p3, -0.468175413106023168e-2f);

#ifdef PFN_VECTORMA
void  __cdecl _SSE_VectorMA( const float *start, float scale, const float *direction, float *dest );
#endif

//-----------------------------------------------------------------------------
// SSE implementations of optimized routines:
//-----------------------------------------------------------------------------


#ifdef POSIX
//#define _PS_CONST(Name, Val) static const ALIGN16 float _ps_##Name[4] ALIGN16_POST = { Val, Val, Val, Val }
#define _PS_CONST_TYPE(Name, Type, Val) static const ALIGN16 Type _ps_##Name[4] ALIGN16_POST = { Val, Val, Val, Val }

_PS_CONST_TYPE(sign_mask, int, (int)0x80000000);
_PS_CONST_TYPE(inv_sign_mask, int, ~0x80000000);


#define _PI32_CONST(Name, Val)  static const ALIGN16 int _pi32_##Name[4]  ALIGN16_POST = { Val, Val, Val, Val }

_PI32_CONST(1, 1);
_PI32_CONST(inv1, ~1);
_PI32_CONST(2, 2);
_PI32_CONST(4, 4);
_PI32_CONST(0x7f, 0x7f);
_PS_CONST(1  , 1.0f);
_PS_CONST(0p5, 0.5f);

_PS_CONST(minus_cephes_DP1, -0.78515625);
_PS_CONST(minus_cephes_DP2, -2.4187564849853515625e-4);
_PS_CONST(minus_cephes_DP3, -3.77489497744594108e-8);
_PS_CONST(sincof_p0, -1.9515295891E-4);
_PS_CONST(sincof_p1,  8.3321608736E-3);
_PS_CONST(sincof_p2, -1.6666654611E-1);
_PS_CONST(coscof_p0,  2.443315711809948E-005);
_PS_CONST(coscof_p1, -1.388731625493765E-003);
_PS_CONST(coscof_p2,  4.166664568298827E-002);
_PS_CONST(cephes_FOPI, 1.27323954473516); // 4 / M_PI

typedef union xmm_mm_union {
	__m128 xmm;
	__m64 mm[2];
} xmm_mm_union;

#define COPY_MM_TO_XMM(mm0_, mm1_, xmm_) { xmm_mm_union u; u.mm[0]=mm0_; u.mm[1]=mm1_; xmm_ = u.xmm; }

typedef __m128 v4sf;  // vector of 4 float (sse1)
typedef __m64 v2si;   // vector of 2 int (mmx)

#endif


// SSE Version of VectorTransform
void VectorTransformSSE(const float *in1, const matrix3x4_t& in2, float *out1)
{
	Assert( s_bMathlibInitialized );
	Assert( in1 != out1 );

#if defined( _WIN32 ) && !defined( _WIN64 )
	__asm
	{
		mov eax, in1;
		mov ecx, in2;
		mov edx, out1;

		movss xmm0, [eax];
		mulss xmm0, [ecx];
		movss xmm1, [eax+4];
		mulss xmm1, [ecx+4];
		movss xmm2, [eax+8];
		mulss xmm2, [ecx+8];
		addss xmm0, xmm1;
		addss xmm0, xmm2;
		addss xmm0, [ecx+12]
 		movss [edx], xmm0;
		add ecx, 16;

		movss xmm0, [eax];
		mulss xmm0, [ecx];
		movss xmm1, [eax+4];
		mulss xmm1, [ecx+4];
		movss xmm2, [eax+8];
		mulss xmm2, [ecx+8];
		addss xmm0, xmm1;
		addss xmm0, xmm2;
		addss xmm0, [ecx+12]
		movss [edx+4], xmm0;
		add ecx, 16;

		movss xmm0, [eax];
		mulss xmm0, [ecx];
		movss xmm1, [eax+4];
		mulss xmm1, [ecx+4];
		movss xmm2, [eax+8];
		mulss xmm2, [ecx+8];
		addss xmm0, xmm1;
		addss xmm0, xmm2;
		addss xmm0, [ecx+12]
		movss [edx+8], xmm0;
	}
#else
	out1[0] = DotProduct(in1, in2[0]) + in2[0][3];
	out1[1] = DotProduct(in1, in2[1]) + in2[1][3];
	out1[2] = DotProduct(in1, in2[2]) + in2[2][3];
#endif
}

void VectorRotateSSE( const float *in1, const matrix3x4_t& in2, float *out1 )
{
	Assert( s_bMathlibInitialized );
	Assert( in1 != out1 );

#if defined( _WIN32 ) && !defined( _WIN64 )
	__asm
	{
		mov eax, in1;
		mov ecx, in2;
		mov edx, out1;

		movss xmm0, [eax];
		mulss xmm0, [ecx];
		movss xmm1, [eax+4];
		mulss xmm1, [ecx+4];
		movss xmm2, [eax+8];
		mulss xmm2, [ecx+8];
		addss xmm0, xmm1;
		addss xmm0, xmm2;
 		movss [edx], xmm0;
		add ecx, 16;

		movss xmm0, [eax];
		mulss xmm0, [ecx];
		movss xmm1, [eax+4];
		mulss xmm1, [ecx+4];
		movss xmm2, [eax+8];
		mulss xmm2, [ecx+8];
		addss xmm0, xmm1;
		addss xmm0, xmm2;
		movss [edx+4], xmm0;
		add ecx, 16;

		movss xmm0, [eax];
		mulss xmm0, [ecx];
		movss xmm1, [eax+4];
		mulss xmm1, [ecx+4];
		movss xmm2, [eax+8];
		mulss xmm2, [ecx+8];
		addss xmm0, xmm1;
		addss xmm0, xmm2;
		movss [edx+8], xmm0;
	}
#else
	out1[0] = DotProduct( in1, in2[0] );
	out1[1] = DotProduct( in1, in2[1] );
	out1[2] = DotProduct( in1, in2[2] );
#endif
}

#if defined( _WIN32 ) && !defined( _WIN64 )
void _declspec(naked) _SSE_VectorMA( const float *start, float scale, const float *direction, float *dest )
{
	// FIXME: This don't work!! It will overwrite memory in the write to dest
	Assert(0);

	Assert( s_bMathlibInitialized );
	_asm {  // Intel SSE only routine
		mov	eax, DWORD PTR [esp+0x04]	; *start, s0..s2
		mov ecx, DWORD PTR [esp+0x0c]	; *direction, d0..d2
		mov edx, DWORD PTR [esp+0x10]	; *dest
		movss	xmm2, [esp+0x08]		; x2 = scale, 0, 0, 0
#ifdef ALIGNED_VECTOR
		movaps	xmm3, [ecx]				; x3 = dir0,dir1,dir2,X
		pshufd	xmm2, xmm2, 0			; x2 = scale, scale, scale, scale
		movaps	xmm1, [eax]				; x1 = start1, start2, start3, X
		mulps	xmm3, xmm2				; x3 *= x2
		addps	xmm3, xmm1				; x3 += x1
		movaps	[edx], xmm3				; *dest = x3
#else
		movups	xmm3, [ecx]				; x3 = dir0,dir1,dir2,X
		pshufd	xmm2, xmm2, 0			; x2 = scale, scale, scale, scale
		movups	xmm1, [eax]				; x1 = start1, start2, start3, X
		mulps	xmm3, xmm2				; x3 *= x2
		addps	xmm3, xmm1				; x3 += x1
		movups	[edx], xmm3				; *dest = x3
#endif
	}
}
#endif

#ifdef _WIN32
#ifdef PFN_VECTORMA
void _declspec(naked) __cdecl _SSE_VectorMA( const Vector &start, float scale, const Vector &direction, Vector &dest )
{
	// FIXME: This don't work!! It will overwrite memory in the write to dest
	Assert(0);

	Assert( s_bMathlibInitialized );
	_asm 
	{  
		// Intel SSE only routine
		mov	eax, DWORD PTR [esp+0x04]	; *start, s0..s2
		mov ecx, DWORD PTR [esp+0x0c]	; *direction, d0..d2
		mov edx, DWORD PTR [esp+0x10]	; *dest
		movss	xmm2, [esp+0x08]		; x2 = scale, 0, 0, 0
#ifdef ALIGNED_VECTOR
		movaps	xmm3, [ecx]				; x3 = dir0,dir1,dir2,X
		pshufd	xmm2, xmm2, 0			; x2 = scale, scale, scale, scale
		movaps	xmm1, [eax]				; x1 = start1, start2, start3, X
		mulps	xmm3, xmm2				; x3 *= x2
		addps	xmm3, xmm1				; x3 += x1
		movaps	[edx], xmm3				; *dest = x3
#else
		movups	xmm3, [ecx]				; x3 = dir0,dir1,dir2,X
		pshufd	xmm2, xmm2, 0			; x2 = scale, scale, scale, scale
		movups	xmm1, [eax]				; x1 = start1, start2, start3, X
		mulps	xmm3, xmm2				; x3 *= x2
		addps	xmm3, xmm1				; x3 += x1
		movups	[edx], xmm3				; *dest = x3
#endif
	}
}
float (__cdecl *pfVectorMA)(Vector& v) = _VectorMA;
#endif
#endif


// SSE DotProduct -- it's a smidgen faster than the asm DotProduct...
//   Should be validated too!  :)
//   NJS: (Nov 1 2002) -NOT- faster.  may time a couple cycles faster in a single function like 
//   this, but when inlined, and instruction scheduled, the C version is faster.  
//   Verified this via VTune
/*
vec_t DotProduct (const vec_t *a, const vec_t *c)
{
	vec_t temp;

	__asm
	{
		mov eax, a;
		mov ecx, c;
		mov edx, DWORD PTR [temp]
		movss xmm0, [eax];
		mulss xmm0, [ecx];
		movss xmm1, [eax+4];
		mulss xmm1, [ecx+4];
		movss xmm2, [eax+8];
		mulss xmm2, [ecx+8];
		addss xmm0, xmm1;
		addss xmm0, xmm2;
		movss [edx], xmm0;
		fld DWORD PTR [edx];
		ret
	}
}
*/

