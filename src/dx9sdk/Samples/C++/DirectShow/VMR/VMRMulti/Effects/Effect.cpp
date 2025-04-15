//-----------------------------------------------------------------------------
// File: Effect.cpp
//
//  Generic transition effect class.
//
//	Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#define D3D_OVERLOADS

#include "..\project.h"

#include <mmsystem.h>
#include "Effect.h"
#include "..\D3DHelpers\d3dtextr.h"

//
//	Implementation of CEffect 
//

//-----------------------------------------------------------------------------
//	constructor
//-----------------------------------------------------------------------------
CEffect::CEffect( eEffect effect )
	: m_dwStartTransitionTime(0L)
	, m_lPlayTime(0L)
	, m_dwEndTransitionTime(0L)
	, m_stage(eEffectStageDefault)
	, m_pmovieList(NULL)
	, m_effect(effect)
	, m_dwStartedAt(NULL)
	, m_bComplete( FALSE)
	, m_bZOrderUpdated( FALSE )
{
	;
}

//-----------------------------------------------------------------------------
//	destructor
//-----------------------------------------------------------------------------
CEffect::~CEffect()
{
	;
}

//-----------------------------------------------------------------------------
//	Initialize
//	configures video effect, setting start time, play time, and ending time,
//	as well as making necessary computations
//-----------------------------------------------------------------------------
HRESULT CEffect::Initialize( CMovieList *plist,
							 DWORD dwStartTransitionTime, 
							 LONG lPlayTime, 
							 DWORD dwEndTransitionTime)
{
	if( !plist )
	{
		return E_INVALIDARG;
	}
	m_pmovieList = plist;
	m_dwStartTransitionTime = dwStartTransitionTime;
	m_dwEndTransitionTime = dwEndTransitionTime;
	m_lPlayTime = lPlayTime;
	m_stage = eEffectStageStarting;
	m_dwStartedAt = timeGetTime();

	HRESULT hr = ComposeDefaultScene();

	return hr;
}

//-----------------------------------------------------------------------------
//	Compose
//	reads current time and manages stages; calling correspondent composing functions
//-----------------------------------------------------------------------------
HRESULT CEffect::Compose()
{
	HRESULT hr = S_OK;
	if( !m_pmovieList )
	{
		return E_INVALIDARG;
	}
	LONG dwElapsedTime = timeGetTime() - m_dwStartedAt;

	switch( m_stage)
	{
	case eEffectStageDefault:		// default scene, i.e. uninitialized stage; set to starting
		hr = ComposeDefaultScene();
		m_stage = eEffectStageStarting;
		m_dwStartedAt = timeGetTime();
		hr = ComposeStartTransition();
		break;

	case eEffectStageStarting:
		if( dwElapsedTime > (LONG)m_dwStartTransitionTime )
		{
			m_stage = eEffectStagePlaying; // switch to the next stage
			m_dwStartedAt = timeGetTime();
			hr = ComposeScene();
		}
		else
		{
			hr = ComposeStartTransition();
		}
		break;

	case eEffectStagePlaying:
		if( m_lPlayTime < 0L )
		{
			hr = ComposeScene();
		}
		else if( dwElapsedTime > m_lPlayTime )
		{
			m_stage = eEffectStageFinishing; // switch to the next stage
			m_dwStartedAt = timeGetTime();
			hr = ComposeEndTransition();
		}
		else
		{
			hr = ComposeScene();
		}
		break;

	case eEffectStageFinishing:
		if( dwElapsedTime <= (LONG)m_dwEndTransitionTime )
		{
			hr = ComposeEndTransition();
		}
		else
		{
			m_bComplete = TRUE;
			// ok, effect is completed, return to default coordinates
			for(int i=0; i< m_pmovieList->GetSize(); i++)
			{
				CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
				if( !pmovie )
				{
					return E_FAIL;
				}
				for( int j=0; j<4; j++)
				{
					pmovie->m_Vcur[j] = pmovie->m_Vdef[j];
				}
			}
		}
		break;
	}

	if( m_bZOrderUpdated )		// if composing functions changed z-order of movie frames,
								// calculate z-order
	{
		m_pmovieList->SortByZ();
		m_bZOrderUpdated = FALSE;
	}
	return hr;
}

//-----------------------------------------------------------------------------
//	ComposeDefaultScene
//	Calculates m_Vdef, default arrangement common for all effects: frames
//	are aligned  by height and lined-up horizontally
//-----------------------------------------------------------------------------
HRESULT CEffect::ComposeDefaultScene()
{
	if( !m_pmovieList )
	{
		return E_INVALIDARG;
	}

	// set up default alignment
	// default scene: all movies are lined up horizontally; calculate m_Vdef and copy it to m_Vcur
	RECT rDest = m_pmovieList->GetDefaultTarget();

	float W = (float) (rDest.right - rDest.left);
	float H;
	float w;
	float h;
	float sum_aspect_ratio = 0.f;
	float aspect_ratio = 0.f;
	float total_w;
	float horizon = (float)(rDest.top + rDest.bottom) / 2.f;
	DDSURFACEDESC2 ddsd;
	RECT  rcSrc;
	float fWid;
	float fHgt;
	HRESULT hr = S_OK;

	if( m_pmovieList->GetSize() == 0 )
	{
		return S_OK;
	}

	for( int i=0; i< m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		if( FALSE == pmovie->m_bUseInTheScene )
		{
			continue;
		}
		w = (float)pmovie->m_VideoSize.cx;
		h = (float)pmovie->m_VideoSize.cy;
		
		if( 0.f == w || 0.f == h )  // if GetVideoSize returns zero (for some media formats),
									// let's try out luck with 4x3 aspect ratio 
		{
			w = 4.f;
			h = 3.f;
		}
		if( h<=0.f )
		{
			return E_FAIL;
		}

		sum_aspect_ratio += w/h;
	}

	if( fabs(sum_aspect_ratio) < 0.000000001f )
	{
		return E_FAIL;
	}

	H = W / sum_aspect_ratio;
	total_w = 0.f;

	for( i=0; i< m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		if( FALSE == pmovie->m_bUseInTheScene )
		{
			continue;
		}
		w = (float)pmovie->m_VideoSize.cx;
		h = (float)pmovie->m_VideoSize.cy;

		if( h<=0.f )
		{
			return E_FAIL;
		}
		aspect_ratio = w/h;

		w = aspect_ratio * H;

		INITDDSTRUCT(ddsd);

		if( !pmovie->m_lpDDTexture )
		{
			return E_FAIL;
		}
		
		hr = pmovie->m_lpDDTexture->GetSurfaceDesc(&ddsd);
		if( FAILED(hr))
		{
			return hr;
		}
		fWid = (float)ddsd.dwWidth;
		fHgt = (float)ddsd.dwHeight;

		rcSrc.left = 0;
		rcSrc.top = 0;
		rcSrc.right = pmovie->m_VideoSize.cx;
		rcSrc.bottom = pmovie->m_VideoSize.cy;

		pmovie->m_Vdef[0].x = total_w;
		pmovie->m_Vdef[0].y = horizon - H/2.f;
		pmovie->m_Vdef[0].z = 0.5f;
		pmovie->m_Vdef[0].clr = RGB(0x00,0x70,0x7F);
		pmovie->m_Vdef[0].rhw = 2.0f;
		pmovie->m_Vdef[0].tu = (float)rcSrc.left / fWid;
		pmovie->m_Vdef[0].tv = (float)rcSrc.top / fHgt;

		pmovie->m_Vdef[1].x = total_w + w;
		pmovie->m_Vdef[1].y = horizon - H/2.f;
		pmovie->m_Vdef[1].z = 0.5f;
		pmovie->m_Vdef[1].clr = RGB(0x00,0x70,0x7F);
		pmovie->m_Vdef[1].rhw = 2.0f;
		pmovie->m_Vdef[1].tu = (float)rcSrc.right / fWid;
		pmovie->m_Vdef[1].tv = (float)rcSrc.top / fHgt;


		pmovie->m_Vdef[2].x = total_w;
		pmovie->m_Vdef[2].y = horizon + H/2.f;
		pmovie->m_Vdef[2].z = 0.5f;
		pmovie->m_Vdef[2].clr = RGB(0x00,0x70,0x7F);
		pmovie->m_Vdef[2].rhw = 2.0f;
		pmovie->m_Vdef[2].tu = (float)rcSrc.left / fWid;
		pmovie->m_Vdef[2].tv = (float)rcSrc.bottom / fHgt;

		pmovie->m_Vdef[3].x = total_w + w;
		pmovie->m_Vdef[3].y = horizon + H/2.f;
		pmovie->m_Vdef[3].z = 0.5f;
		pmovie->m_Vdef[3].clr = RGB(0x00,0x70,0x7F);
		pmovie->m_Vdef[3].rhw = 2.0f;
		pmovie->m_Vdef[3].tu = (float)rcSrc.right / fWid;
		pmovie->m_Vdef[3].tv = (float)rcSrc.bottom / fHgt;

		total_w += w;
	}// for

	return S_OK;
}

//-----------------------------------------------------------------------------
//	ComposeScene
//	for the base effect, all three stages imply the same default arrangement
//-----------------------------------------------------------------------------
HRESULT CEffect::ComposeScene()
{
	return CopyDefaultCoordinates();
}


//-----------------------------------------------------------------------------
//	ComposeStartTransition
//	for the base effect, all three stages imply the same default arrangement
//-----------------------------------------------------------------------------
HRESULT CEffect::ComposeStartTransition()
{
	return CopyDefaultCoordinates();
}

//-----------------------------------------------------------------------------
//	ComposeEndTransition
//	for the base effect, all three stages imply the same default arrangement
//-----------------------------------------------------------------------------
HRESULT CEffect::ComposeEndTransition()
{
	return CopyDefaultCoordinates();
}

//-----------------------------------------------------------------------------
//	Finish
//	Pings effect to iterrupt current stage and start ending phase 
//	(when playing time in -1, which is infinite, or user requested some action,
//	 like adding new movie or changing selection)
//-----------------------------------------------------------------------------
void CEffect::Finish()
{
	m_stage = eEffectStageFinishing;
	m_dwStartedAt = timeGetTime();
}


//-----------------------------------------------------------------------------
//	Invalidate
//-----------------------------------------------------------------------------
HRESULT CEffect::Invalidate()
{
	return ComposeDefaultScene();
}

//-----------------------------------------------------------------------------
//	CopyDefaultCoordinates
//	set currect frame's coordinates to default.
//-----------------------------------------------------------------------------
HRESULT CEffect::CopyDefaultCoordinates()
{
	HRESULT hr = S_OK;
	if( !m_pmovieList )
	{
		return E_FAIL;
	}

	for( int i=0; i< m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		for( int j=0; j<4; j++)
		{
			pmovie->m_Vcur[j] = pmovie->m_Vdef[j];
		}
	}

	return hr;
}

//
//	implementation of effects
//

// Fountain effect

//-----------------------------------------------------------------------------
//	constructor
//-----------------------------------------------------------------------------
CEffectFountain::CEffectFountain() :
	CEffect(eEffectFountain)
{
		;
}

//-----------------------------------------------------------------------------
//	ComposeStartTransition
//	the same as default arrangement
//-----------------------------------------------------------------------------
HRESULT CEffectFountain::ComposeStartTransition()
{
	HRESULT hr = CopyDefaultCoordinates();
	return hr;
}

//-----------------------------------------------------------------------------
//	ComposeScene
//	frame is moving along the circle on x-y plane
//-----------------------------------------------------------------------------
HRESULT CEffectFountain::ComposeScene()
{
	HRESULT hr = S_OK;
	if( !m_pmovieList )
	{
		return E_FAIL;
	}

	DWORD dwCurTime = timeGetTime() - m_dwStartedAt;
	RECT rcTarget = m_pmovieList->GetDefaultTarget();

	float scx = (float)( rcTarget.left + rcTarget.right ) / 2.f; // center of the render target
	float scy = (float)( rcTarget.top + rcTarget.bottom ) / 2.f;

	float beta = dwCurTime * 3.1415926535f / 5000.f; // rotation angle of the center of the frame in x,y plane
	float a = 1.f; // speed of changing the size of the frame

	float fcx = 0.f; // center of the frame
	float fcy = 0.f;
	float framewidth2 = 1.f; // sizes of the default frame, divided by 2
	float frameheight2 = 1.f;
	float scale = 1.f; // scaling coefficient for the frame

	for( int i=0; i< m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		if( FALSE == pmovie->m_bUseInTheScene )
		{
			continue;
		}
		
		framewidth2 = (pmovie->m_Vdef[1].x - pmovie->m_Vdef[0].x) / 2.f;
		frameheight2 = (pmovie->m_Vdef[2].y - pmovie->m_Vdef[0].y) / 2.f;
		fcx = (pmovie->m_Vdef[0].x + pmovie->m_Vdef[1].x) / 2.f;
		fcy = (pmovie->m_Vdef[0].y + pmovie->m_Vdef[2].y) / 2.f;
		a = 3.1415926535f /(2000.f + 10.f * (float)( (int)fcx % 100 ));
		fcx = scx + (float)(fabs( fcx - scx ) * cos( beta ));
		fcy = scy + (float)(fabs( fcy - scy ) * sin( beta ));
		scale = 1.55f + 1.45f * (float)cos (a * dwCurTime + 1.95984f);

		pmovie->m_Vcur[0].x = fcx - scale * framewidth2;
		pmovie->m_Vcur[0].y = fcy - scale * frameheight2;
		pmovie->m_Vcur[0].z = pmovie->m_Vdef[0].z;
		pmovie->m_Vcur[0].tu = pmovie->m_Vdef[0].tu;
		pmovie->m_Vcur[0].tv = pmovie->m_Vdef[0].tv;
		pmovie->m_Vcur[0].rhw = pmovie->m_Vdef[0].rhw;
		pmovie->m_Vcur[0].clr = pmovie->m_Vdef[0].clr;
		pmovie->m_Vrnd[0] = pmovie->m_Vcur[0];

		pmovie->m_Vcur[1].x = fcx + scale * framewidth2;
		pmovie->m_Vcur[1].y = fcy - scale * frameheight2;
		pmovie->m_Vcur[1].z = pmovie->m_Vdef[1].z;
		pmovie->m_Vcur[1].tu = pmovie->m_Vdef[1].tu;
		pmovie->m_Vcur[1].tv = pmovie->m_Vdef[1].tv;
		pmovie->m_Vcur[1].rhw = pmovie->m_Vdef[1].rhw;
		pmovie->m_Vcur[1].clr = pmovie->m_Vdef[1].clr;
		pmovie->m_Vrnd[1] = pmovie->m_Vcur[1];

		pmovie->m_Vcur[2].x = fcx - scale * framewidth2;
		pmovie->m_Vcur[2].y = fcy + scale * frameheight2;
		pmovie->m_Vcur[2].z = pmovie->m_Vdef[2].z;
		pmovie->m_Vcur[2].tu = pmovie->m_Vdef[2].tu;
		pmovie->m_Vcur[2].tv = pmovie->m_Vdef[2].tv;
		pmovie->m_Vcur[2].rhw = pmovie->m_Vdef[2].rhw;
		pmovie->m_Vcur[2].clr = pmovie->m_Vdef[2].clr;
		pmovie->m_Vrnd[2] = pmovie->m_Vcur[2];

		pmovie->m_Vcur[3].x = fcx + scale * framewidth2;
		pmovie->m_Vcur[3].y = fcy + scale * frameheight2;
		pmovie->m_Vcur[3].z = pmovie->m_Vdef[3].z;
		pmovie->m_Vcur[3].tu = pmovie->m_Vdef[3].tu;
		pmovie->m_Vcur[3].tv = pmovie->m_Vdef[3].tv;
		pmovie->m_Vcur[3].rhw = pmovie->m_Vdef[3].rhw;
		pmovie->m_Vcur[3].clr = pmovie->m_Vdef[3].clr;
		pmovie->m_Vrnd[3] = pmovie->m_Vcur[3];

	}
	return S_OK;
}

//-----------------------------------------------------------------------------
//	ComposeEndTransition
//	move to default arrangement
//-----------------------------------------------------------------------------
HRESULT CEffectFountain::ComposeEndTransition()
{
	HRESULT hr = S_OK;
	if( !m_pmovieList )
	{
		return E_FAIL;
	}
	if( m_dwEndTransitionTime < 1L)
	{
		return E_FAIL;
	}
	DWORD dwCurT = timeGetTime() - m_dwStartedAt;

	float cx, cy;
	float rcx, rcy;
	float defcx, defcy;
	float w2, h2;
	float rw2, rh2;
	float defw2, defh2;


	for( int i=0; i<m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		if( FALSE == pmovie->m_bUseInTheScene )
		{
			continue;
		}
		rcx = ( pmovie->m_Vrnd[0].x + pmovie->m_Vrnd[1].x ) / 2.f;
		rcy = ( pmovie->m_Vrnd[0].y + pmovie->m_Vrnd[2].y ) / 2.f;

		defcx = ( pmovie->m_Vdef[0].x + pmovie->m_Vdef[1].x ) / 2.f;
		defcy = ( pmovie->m_Vdef[0].y + pmovie->m_Vdef[2].y ) / 2.f;

		rw2 = ( pmovie->m_Vrnd[1].x - pmovie->m_Vrnd[0].x ) / 2.f;
		rh2 = ( pmovie->m_Vrnd[2].y - pmovie->m_Vrnd[0].y ) / 2.f;

		defw2 = ( pmovie->m_Vdef[1].x - pmovie->m_Vdef[0].x ) / 2.f;
		defh2 = ( pmovie->m_Vdef[2].y - pmovie->m_Vdef[0].y ) / 2.f;

		w2 = (float)dwCurT * (defw2 - rw2) / m_dwEndTransitionTime + rw2;
		h2 = (float)dwCurT * (defh2 - rh2) / m_dwEndTransitionTime + rh2;

		cx = (float)dwCurT * (defcx - rcx) / m_dwEndTransitionTime + rcx;
		cy = (float)dwCurT * (defcy - rcy) / m_dwEndTransitionTime + rcy;

		for( int j=0; j<4; j++)
		{
			pmovie->m_Vcur[i] = pmovie->m_Vdef[i];
		}
		pmovie->m_Vcur[0].x = cx - w2; 
		pmovie->m_Vcur[0].y = cy - h2;

		pmovie->m_Vcur[1].x = cx + w2; 
		pmovie->m_Vcur[1].y = cy - h2;

		pmovie->m_Vcur[2].x = cx - w2; 
		pmovie->m_Vcur[2].y = cy + h2;

		pmovie->m_Vcur[3].x = cx + w2; 
		pmovie->m_Vcur[3].y = cy + h2;
	}
	return S_OK;
}

// CEffectStillArrangement

//-----------------------------------------------------------------------------
//	constructor
//-----------------------------------------------------------------------------
CEffectStillArrangement::CEffectStillArrangement() 
		: CEffect( eEffectStillArrangement )

{
	m_bNeedToCopyBuffer = true;
	m_bTargetCalculated = false;
}

//-----------------------------------------------------------------------------
//	CalculateTarget
//	calculates frame's coordinates for playing stage; we need to know them
//  earlier, to provide smooth movement at the starting stage
//-----------------------------------------------------------------------------
HRESULT CEffectStillArrangement::CalculateTarget()
{
	HRESULT hr = S_OK;
	if( !m_pmovieList )
	{
		return E_FAIL;
	}

	int i;
	RECT rcRT; // render target
	float w; // width of a frame
	float h; // height of a frame
	float h_unselected = 0.f;

	float AR_sum = 0.f; // sum of aspect ratios for unselected frames
	float w_sum = 0.f;
	float curleft = 0.f; // left of the current unselected frame

	rcRT = m_pmovieList->GetDefaultTarget();
	float W = (float) (rcRT.right - rcRT.left);
	float H = (float) (rcRT.bottom - rcRT.top);
	float fAR = 1.f; // aspect ratio of the frame

	// calculate target rectangle for uncelected movies, so that it fits
	// [l t r b] = [0.1W, 0.78H, 0.9W, 0.98H] where W and H are sizes of the render target 
	h_unselected = 0.2f * H;
	for( i=0; i<m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		if( pmovie->m_dwUserID == m_pmovieList->GetSelectedMovieID() ) // skip selected
		{
			continue;
		}
		if( FALSE == pmovie->m_bUseInTheScene )
		{
			continue;
		}
		fAR = (pmovie->m_Vdef[1].x - pmovie->m_Vdef[0].x) / (pmovie->m_Vdef[2].y - pmovie->m_Vdef[0].y);
		AR_sum += fAR;
		w_sum += h_unselected * fAR;
	}
	if( w_sum > 0.8f * W ) // exceeded width of allowed recrangle for unselected movies
	{
		w_sum = 0.8f * W;
		h_unselected = w_sum / AR_sum;
	}

	// ok, now go through all the movies and set the right spot
	curleft = (float)(float) (rcRT.right + rcRT.left) / 2.f - w_sum / 2.f;

	for( i=0; i<m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		if( FALSE == pmovie->m_bUseInTheScene )
		{
			continue;
		}

		fAR = (pmovie->m_Vdef[1].x - pmovie->m_Vdef[0].x) / (pmovie->m_Vdef[2].y - pmovie->m_Vdef[0].y);
		
		if( pmovie->m_dwUserID == m_pmovieList->GetSelectedMovieID() ) 
		{
			// selected movie goes to the center of render target (moved up 10%), keeps it AP and occupies
			// 0.5 of the total area of the render target
			h = (float)sqrt( W * H / (2.f * fAR) ) / 2.f;
			w = fAR * h;

			// center of the frame
			float cx = (float) (rcRT.right + rcRT.left) / 2.f;
			float cy = (float) (rcRT.top + rcRT.bottom) / 2.f;

			pmovie->m_Vrnd[0].x = cx - w;
			pmovie->m_Vrnd[0].y = cy - 1.3f * h;
			pmovie->m_Vrnd[0].z = 0.1f;
			pmovie->m_Vrnd[0].tu = pmovie->m_Vdef[0].tu;
			pmovie->m_Vrnd[0].tv = pmovie->m_Vdef[0].tv;
			pmovie->m_Vrnd[0].rhw = pmovie->m_Vdef[0].rhw;
			pmovie->m_Vrnd[0].clr = pmovie->m_Vdef[0].clr;

			pmovie->m_Vrnd[1].x = cx + w;
			pmovie->m_Vrnd[1].y = cy - 1.3f * h;
			pmovie->m_Vrnd[1].z = 0.1f;
			pmovie->m_Vrnd[1].tu = pmovie->m_Vdef[1].tu;
			pmovie->m_Vrnd[1].tv = pmovie->m_Vdef[1].tv;
			pmovie->m_Vrnd[1].rhw = pmovie->m_Vdef[1].rhw;
			pmovie->m_Vrnd[1].clr = pmovie->m_Vdef[1].clr;

			pmovie->m_Vrnd[2].x = cx - w;
			pmovie->m_Vrnd[2].y = cy + 0.7f * h;
			pmovie->m_Vrnd[2].z = 0.1f;
			pmovie->m_Vrnd[2].tu = pmovie->m_Vdef[2].tu;
			pmovie->m_Vrnd[2].tv = pmovie->m_Vdef[2].tv;
			pmovie->m_Vrnd[2].rhw = pmovie->m_Vdef[2].rhw;
			pmovie->m_Vrnd[2].clr = pmovie->m_Vdef[2].clr;

			pmovie->m_Vrnd[3].x = cx + w;
			pmovie->m_Vrnd[3].y = cy + 0.7f * h;
			pmovie->m_Vrnd[3].z = 0.1f;
			pmovie->m_Vrnd[3].tu = pmovie->m_Vdef[3].tu;
			pmovie->m_Vrnd[3].tv = pmovie->m_Vdef[3].tv;
			pmovie->m_Vrnd[3].rhw = pmovie->m_Vdef[3].rhw;
			pmovie->m_Vrnd[3].clr = pmovie->m_Vdef[3].clr;
		} // if it is a selected movie
		else // this is unselected movie
		{
			w = fAR * h_unselected;

			pmovie->m_Vrnd[0].x = curleft;
			pmovie->m_Vrnd[0].y = 0.78f * H + rcRT.top;
			pmovie->m_Vrnd[0].z = pmovie->m_Vdef[0].z;
			pmovie->m_Vrnd[0].tu = pmovie->m_Vdef[0].tu;
			pmovie->m_Vrnd[0].tv = pmovie->m_Vdef[0].tv;
			pmovie->m_Vrnd[0].rhw = pmovie->m_Vdef[0].rhw;
			pmovie->m_Vrnd[0].clr = pmovie->m_Vdef[0].clr;

			pmovie->m_Vrnd[1].x = curleft + w;
			pmovie->m_Vrnd[1].y = 0.78f * H + rcRT.top;
			pmovie->m_Vrnd[1].z = pmovie->m_Vdef[1].z;
			pmovie->m_Vrnd[1].tu = pmovie->m_Vdef[1].tu;
			pmovie->m_Vrnd[1].tv = pmovie->m_Vdef[1].tv;
			pmovie->m_Vrnd[1].rhw = pmovie->m_Vdef[1].rhw;
			pmovie->m_Vrnd[1].clr = pmovie->m_Vdef[1].clr;

			pmovie->m_Vrnd[2].x = curleft;
			pmovie->m_Vrnd[2].y = 0.78f * H + rcRT.top + h_unselected;
			pmovie->m_Vrnd[2].z = pmovie->m_Vdef[2].z;
			pmovie->m_Vrnd[2].tu = pmovie->m_Vdef[2].tu;
			pmovie->m_Vrnd[2].tv = pmovie->m_Vdef[2].tv;
			pmovie->m_Vrnd[2].rhw = pmovie->m_Vdef[2].rhw;
			pmovie->m_Vrnd[2].clr = pmovie->m_Vdef[2].clr;

			pmovie->m_Vrnd[3].x = curleft + w;
			pmovie->m_Vrnd[3].y = 0.78f * H + rcRT.top + h_unselected;
			pmovie->m_Vrnd[3].z = pmovie->m_Vdef[3].z;
			pmovie->m_Vrnd[3].tu = pmovie->m_Vdef[3].tu;
			pmovie->m_Vrnd[3].tv = pmovie->m_Vdef[3].tv;
			pmovie->m_Vrnd[3].rhw = pmovie->m_Vdef[3].rhw;
			pmovie->m_Vrnd[3].clr = pmovie->m_Vdef[3].clr;

			curleft += w;
		} // else; that is unselected movie's frame
	} // for all movies in the list

	m_bTargetCalculated = true;
	return hr;
}

//-----------------------------------------------------------------------------
//	ComposeStartTransition
//	move to the default arrangement
//-----------------------------------------------------------------------------
HRESULT CEffectStillArrangement::ComposeStartTransition()
{
	HRESULT hr = S_OK;

	if( !m_pmovieList )
	{
		return E_FAIL;
	}
	if( m_dwStartTransitionTime < 1L)
	{
		return E_FAIL;
	}

	if( false == m_bTargetCalculated )
	{
		ComposeDefaultScene();
		hr = CalculateTarget();
		if( FAILED(hr))
		{
			return hr;
		}
	}

	m_bNeedToCopyBuffer = true;

	DWORD dwCurT = timeGetTime() - m_dwStartedAt;

	float cx, cy;
	float rcx, rcy;
	float defcx, defcy;
	float w2, h2;
	float rw2, rh2;
	float defw2, defh2;


	for( int i=0; i<m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		if( FALSE == pmovie->m_bUseInTheScene )
		{
			continue;
		}
		rcx = ( pmovie->m_Vrnd[0].x + pmovie->m_Vrnd[1].x ) / 2.f;
		rcy = ( pmovie->m_Vrnd[0].y + pmovie->m_Vrnd[2].y ) / 2.f;

		defcx = ( pmovie->m_Vdef[0].x + pmovie->m_Vdef[1].x ) / 2.f;
		defcy = ( pmovie->m_Vdef[0].y + pmovie->m_Vdef[2].y ) / 2.f;

		rw2 = ( pmovie->m_Vrnd[1].x - pmovie->m_Vrnd[0].x ) / 2.f;
		rh2 = ( pmovie->m_Vrnd[2].y - pmovie->m_Vrnd[0].y ) / 2.f;

		defw2 = ( pmovie->m_Vdef[1].x - pmovie->m_Vdef[0].x ) / 2.f;
		defh2 = ( pmovie->m_Vdef[2].y - pmovie->m_Vdef[0].y ) / 2.f;

		w2 = (float)dwCurT * (rw2 - defw2) / m_dwStartTransitionTime + defw2;
		h2 = (float)dwCurT * (rh2 - defh2) / m_dwStartTransitionTime + defh2;

		cx = (float)dwCurT * (rcx - defcx) / m_dwStartTransitionTime + defcx;
		cy = (float)dwCurT * (rcy - defcy) / m_dwStartTransitionTime + defcy;

		for( int j=0; j<4; j++)
		{
			pmovie->m_Vcur[j] = pmovie->m_Vdef[j];
		}
		pmovie->m_Vcur[0].x = cx - w2; 
		pmovie->m_Vcur[0].y = cy - h2;

		pmovie->m_Vcur[1].x = cx + w2; 
		pmovie->m_Vcur[1].y = cy - h2;

		pmovie->m_Vcur[2].x = cx - w2; 
		pmovie->m_Vcur[2].y = cy + h2;

		pmovie->m_Vcur[3].x = cx + w2; 
		pmovie->m_Vcur[3].y = cy + h2;
	}
	return S_OK;
}

//-----------------------------------------------------------------------------
//	ComposeScene
//	uses CalculateTarget() to calculate frame's coordinates; changes z-order 
//  to move selected movie to the back
//-----------------------------------------------------------------------------
HRESULT CEffectStillArrangement::ComposeScene()
{
	HRESULT hr = S_OK;
	if( !m_pmovieList )
	{
		return E_FAIL;
	}

	float fZOrder = 0.f;

	if( false == m_bTargetCalculated )
	{
		hr = CalculateTarget();
		if( FAILED(hr))
		{
			return hr;
		}
	}

	if( m_bNeedToCopyBuffer )
	{
		for( int i=0; i<m_pmovieList->GetSize(); i++)
		{
			CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
			if( !pmovie )
			{
				return E_FAIL;
			}
			if( FALSE == pmovie->m_bUseInTheScene )
			{
				continue;
			}
			fZOrder = 0.f;
			for( int j=0; j<4; j++)
			{
				pmovie->m_Vcur[j] = pmovie->m_Vrnd[j];
				fZOrder += pmovie->m_Vcur[j].z;
			}

			pmovie->m_fZ = fZOrder / 4.f;
		}
		m_bNeedToCopyBuffer = false;
		m_bZOrderUpdated = true;
	}
	return hr;
}

//-----------------------------------------------------------------------------
//	ComposeEndTransition
//	moves to default arrangement
//-----------------------------------------------------------------------------
HRESULT CEffectStillArrangement::ComposeEndTransition()
{
	HRESULT hr = S_OK;

	if( !m_pmovieList )
	{
		return E_FAIL;
	}
	if( m_dwEndTransitionTime < 1L)
	{
		return E_FAIL;
	}

	if( false == m_bTargetCalculated )
	{
		ComposeDefaultScene();
		hr = CalculateTarget();
		if( FAILED(hr))
		{
			return hr;
		}
	}
	m_bNeedToCopyBuffer = true;

	DWORD dwCurT = timeGetTime() - m_dwStartedAt;

	float cx, cy;
	float rcx, rcy;
	float defcx, defcy;
	float w2, h2;
	float rw2, rh2;
	float defw2, defh2;


	for( int i=0; i<m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		if( FALSE == pmovie->m_bUseInTheScene )
		{
			continue;
		}
		rcx = ( pmovie->m_Vrnd[0].x + pmovie->m_Vrnd[1].x ) / 2.f;
		rcy = ( pmovie->m_Vrnd[0].y + pmovie->m_Vrnd[2].y ) / 2.f;

		defcx = ( pmovie->m_Vdef[0].x + pmovie->m_Vdef[1].x ) / 2.f;
		defcy = ( pmovie->m_Vdef[0].y + pmovie->m_Vdef[2].y ) / 2.f;

		rw2 = ( pmovie->m_Vrnd[1].x - pmovie->m_Vrnd[0].x ) / 2.f;
		rh2 = ( pmovie->m_Vrnd[2].y - pmovie->m_Vrnd[0].y ) / 2.f;

		defw2 = ( pmovie->m_Vdef[1].x - pmovie->m_Vdef[0].x ) / 2.f;
		defh2 = ( pmovie->m_Vdef[2].y - pmovie->m_Vdef[0].y ) / 2.f;

		w2 = (float)dwCurT * (defw2 - rw2) / m_dwEndTransitionTime + rw2;
		h2 = (float)dwCurT * (defh2 - rh2) / m_dwEndTransitionTime + rh2;

		cx = (float)dwCurT * (defcx - rcx) / m_dwEndTransitionTime + rcx;
		cy = (float)dwCurT * (defcy - rcy) / m_dwEndTransitionTime + rcy;

		for( int j=0; j<4; j++ )
		{
			pmovie->m_Vcur[j] = pmovie->m_Vdef[j];
		}
		pmovie->m_Vcur[0].x = cx - w2; 
		pmovie->m_Vcur[0].y = cy - h2;

		pmovie->m_Vcur[1].x = cx + w2; 
		pmovie->m_Vcur[1].y = cy - h2;

		pmovie->m_Vcur[2].x = cx - w2; 
		pmovie->m_Vcur[2].y = cy + h2;

		pmovie->m_Vcur[3].x = cx + w2; 
		pmovie->m_Vcur[3].y = cy + h2;
	}
	return S_OK;
}

// CEffectFading

//-----------------------------------------------------------------------------
//	constructor
//-----------------------------------------------------------------------------
CEffectFading::CEffectFading() 
	: CEffect( eEffectFading )
{
	m_bTargetCalculated = false;
}

//-----------------------------------------------------------------------------
//	CalculateTarget
//	here target is a pixel-size rectangle in the middle of the screen (at this point, 
//					adding new frame won't look flashy)
//-----------------------------------------------------------------------------
HRESULT CEffectFading::CalculateTarget()
{
	HRESULT hr = S_OK;

	if( !m_pmovieList )
	{
		return E_FAIL;
	}

	RECT rcRT = m_pmovieList->GetDefaultTarget();

	float cx = (float)(rcRT.left + rcRT.right)/2.f;
	float cy = (float)(rcRT.top + rcRT.bottom)/2.f;

	for( int i=0; i<m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}

		for( int j=0; j<4; j++)
		{
			pmovie->m_Vrnd[j] = pmovie->m_Vdef[j];
		}

		pmovie->m_Vrnd[0].x = cx - 2.f;
		pmovie->m_Vrnd[0].y = cy - 2.f;

		pmovie->m_Vrnd[1].x = cx + 2.f;
		pmovie->m_Vrnd[1].y = cy - 2.f;

		pmovie->m_Vrnd[2].x = cx - 2.f;
		pmovie->m_Vrnd[2].y = cy + 2.f;

		pmovie->m_Vrnd[3].x = cx + 2.f;
		pmovie->m_Vrnd[3].y = cy + 2.f;
	}// for all movies

	m_bTargetCalculated	= true;
	
	return hr;
}

//-----------------------------------------------------------------------------
//	ComposeStartTransition
//	moves from default to target
//-----------------------------------------------------------------------------
HRESULT CEffectFading::ComposeStartTransition()
{
	HRESULT hr = S_OK;

	if( !m_pmovieList )
	{
		return E_FAIL;
	}
	if( false == m_bTargetCalculated )
	{
		ComposeDefaultScene();
		hr = CalculateTarget();
		if( FAILED(hr))
		{
			return hr;
		}
	}

	DWORD dwCurT = timeGetTime() - m_dwStartedAt;

	float cx, cy;
	float rcx, rcy;
	float defcx, defcy;
	float w2, h2;
	float rw2, rh2;
	float defw2, defh2;


	for( int i=0; i<m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		if( FALSE == pmovie->m_bUseInTheScene )
		{
			continue;
		}
		rcx = ( pmovie->m_Vrnd[0].x + pmovie->m_Vrnd[1].x ) / 2.f;
		rcy = ( pmovie->m_Vrnd[0].y + pmovie->m_Vrnd[2].y ) / 2.f;

		defcx = ( pmovie->m_Vdef[0].x + pmovie->m_Vdef[1].x ) / 2.f;
		defcy = ( pmovie->m_Vdef[0].y + pmovie->m_Vdef[2].y ) / 2.f;

		rw2 = ( pmovie->m_Vrnd[1].x - pmovie->m_Vrnd[0].x ) / 2.f;
		rh2 = ( pmovie->m_Vrnd[2].y - pmovie->m_Vrnd[0].y ) / 2.f;

		defw2 = ( pmovie->m_Vdef[1].x - pmovie->m_Vdef[0].x ) / 2.f;
		defh2 = ( pmovie->m_Vdef[2].y - pmovie->m_Vdef[0].y ) / 2.f;

		w2 = (float)dwCurT * (rw2 - defw2) / m_dwStartTransitionTime + defw2;
		h2 = (float)dwCurT * (rh2 - defh2) / m_dwStartTransitionTime + defh2;

		cx = (float)dwCurT * (rcx - defcx) / m_dwStartTransitionTime + defcx;
		cy = (float)dwCurT * (rcy - defcy) / m_dwStartTransitionTime + defcy;

		for( int j=0; j<4; j++)
		{
			pmovie->m_Vcur[j] = pmovie->m_Vdef[j];
		}
		pmovie->m_Vcur[0].x = cx - w2; 
		pmovie->m_Vcur[0].y = cy - h2;

		pmovie->m_Vcur[1].x = cx + w2; 
		pmovie->m_Vcur[1].y = cy - h2;

		pmovie->m_Vcur[2].x = cx - w2; 
		pmovie->m_Vcur[2].y = cy + h2;

		pmovie->m_Vcur[3].x = cx + w2; 
		pmovie->m_Vcur[3].y = cy + h2;
	}
	return S_OK;

}

//-----------------------------------------------------------------------------
//	ComposeEndTransition
//	moves from target to default
//-----------------------------------------------------------------------------
HRESULT CEffectFading::ComposeEndTransition()
{
	HRESULT hr = S_OK;

	if( !m_pmovieList )
	{
		return E_FAIL;
	}
	if( m_dwEndTransitionTime < 1L)
	{
		return E_FAIL;
	}

	if( false == m_bTargetCalculated )
	{
		hr = CalculateTarget();
		if( FAILED(hr))
		{
			return hr;
		}
	}

	DWORD dwCurT = timeGetTime() - m_dwStartedAt;

	float cx, cy;
	float rcx, rcy;
	float defcx, defcy;
	float w2, h2;
	float rw2, rh2;
	float defw2, defh2;


	for( int i=0; i<m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		if( FALSE == pmovie->m_bUseInTheScene )
		{
			continue;
		}
		rcx = ( pmovie->m_Vrnd[0].x + pmovie->m_Vrnd[1].x ) / 2.f;
		rcy = ( pmovie->m_Vrnd[0].y + pmovie->m_Vrnd[2].y ) / 2.f;

		defcx = ( pmovie->m_Vdef[0].x + pmovie->m_Vdef[1].x ) / 2.f;
		defcy = ( pmovie->m_Vdef[0].y + pmovie->m_Vdef[2].y ) / 2.f;

		rw2 = ( pmovie->m_Vrnd[1].x - pmovie->m_Vrnd[0].x ) / 2.f;
		rh2 = ( pmovie->m_Vrnd[2].y - pmovie->m_Vrnd[0].y ) / 2.f;

		defw2 = ( pmovie->m_Vdef[1].x - pmovie->m_Vdef[0].x ) / 2.f;
		defh2 = ( pmovie->m_Vdef[2].y - pmovie->m_Vdef[0].y ) / 2.f;

		w2 = (float)dwCurT * (defw2 - rw2) / m_dwEndTransitionTime + rw2;
		h2 = (float)dwCurT * (defh2 - rh2) / m_dwEndTransitionTime + rh2;

		cx = (float)dwCurT * (defcx - rcx) / m_dwEndTransitionTime + rcx;
		cy = (float)dwCurT * (defcy - rcy) / m_dwEndTransitionTime + rcy;

		for( int j=0; j<4; j++)
		{
			pmovie->m_Vcur[j] = pmovie->m_Vdef[j];
		}
		pmovie->m_Vcur[0].x = cx - w2; 
		pmovie->m_Vcur[0].y = cy - h2;

		pmovie->m_Vcur[1].x = cx + w2; 
		pmovie->m_Vcur[1].y = cy - h2;

		pmovie->m_Vcur[2].x = cx - w2; 
		pmovie->m_Vcur[2].y = cy + h2;

		pmovie->m_Vcur[3].x = cx + w2; 
		pmovie->m_Vcur[3].y = cy + h2;
	}
	return S_OK;
}

//-----------------------------------------------------------------------------
//	ComposeScene
//	uses 'target' as frame coordinates
//-----------------------------------------------------------------------------
HRESULT CEffectFading::ComposeScene()
{
	HRESULT hr = S_OK;
	if( !m_pmovieList )
	{
		return E_FAIL;
	}

	if( false == m_bTargetCalculated )
	{
		hr = CalculateTarget();
		if( FAILED(hr))
		{
			return hr;
		}
	}

	for( int i=0; i<m_pmovieList->GetSize(); i++)
	{
		CMovie * pmovie = m_pmovieList->GetMovieByIndex(i);
		if( !pmovie )
		{
			return E_FAIL;
		}
		for( int j=0; j<4; j++)
		{
			pmovie->m_Vcur[j] = pmovie->m_Vrnd[j];
		}
	}
	return hr;
}

// Management of effect queue

//-----------------------------------------------------------------------------
// constructor
//-----------------------------------------------------------------------------
CEffectQueue::CEffectQueue()
{
	m_pHead = NULL;
}

//-----------------------------------------------------------------------------
// destructor
//-----------------------------------------------------------------------------
CEffectQueue::~CEffectQueue()
{
	ScenarioNode * pnode = m_pHead;
	ScenarioNode * pnode_next = NULL;
	while( pnode )
	{
		pnode_next = pnode->pNext;
		delete pnode->pEffect;
		delete pnode;
		pnode = pnode_next;
	}
	m_pHead = NULL;
}

//-----------------------------------------------------------------------------
//	AddFirst
//  places new effect in the beginning of the list
//-----------------------------------------------------------------------------
BOOL CEffectQueue::AddFirst( CEffect *pEffect )
{
	if( !pEffect )
	{
		return FALSE;
	}
	ScenarioNode *pnode = NULL;
	pnode = new ScenarioNode;
	if( !pnode )
	{
		return FALSE;
	}
	pnode->pEffect = pEffect;
	if( !m_pHead )
	{
		pnode->pNext = NULL;
		m_pHead = pnode;
	}
	else
	{
		pnode->pNext = m_pHead;
		m_pHead = pnode;
	}
	return TRUE;
}

//-----------------------------------------------------------------------------
//	AddLast
//	adds new effect to the end of the list
//-----------------------------------------------------------------------------
BOOL CEffectQueue::AddLast( CEffect * pEffect)
{
	if( !pEffect )
	{
		return FALSE;
	}
	ScenarioNode *pnode = NULL;
	pnode = new ScenarioNode;
	if( !pnode )
	{
		return FALSE;
	}
	pnode->pEffect = pEffect;
	pnode->pNext = NULL;
	if( !m_pHead )
	{
		m_pHead = pnode;
		return TRUE;
	}

	ScenarioNode *pCurNode = m_pHead;
	while( pCurNode->pNext )
	{
		pCurNode = pCurNode->pNext;
	}
	pCurNode->pNext = pnode;
	return TRUE;
}

//-----------------------------------------------------------------------------
//	Pop
//	pops first effect from the list (which is head )
//-----------------------------------------------------------------------------
CEffect * CEffectQueue::Pop()
{
	CEffect *pEffectResult = NULL;
	ScenarioNode *pnode = NULL;
	if( !m_pHead )
	{
		return NULL;
	}
	pnode = m_pHead;
	m_pHead = m_pHead->pNext;
	pEffectResult = pnode->pEffect;
	delete pnode;
	return pEffectResult;
}
