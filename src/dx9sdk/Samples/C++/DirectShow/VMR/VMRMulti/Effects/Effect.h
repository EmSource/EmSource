//-----------------------------------------------------------------------------
// File: Effect.h
//
//  Generic transition effect class.
//
//	Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef _EFFECT_H
#define _EFFECT_H

#include <windows.h>
#include <tchar.h>
#include <d3d.h>

#define HALF_BLEND_MASK TEXT("..\\..\\media\\halfblend.tga\0")

typedef struct _FRAMESIZE
{
        DWORD dwWidth;
        DWORD dwHeight;
} FRAMESIZE;

typedef struct _FRAMESCALE
{
        FLOAT fScaleW;
        FLOAT fScaleH;
} FRAMESCALE;

//-----------------------------------------------------------------------------
//	EffectStage
//	in this sample, each videoeffect has three stages: start, play, and end
//  start stage and end stage are necessary to provide smooth transition from one 
//  videoeffect to another
//-----------------------------------------------------------------------------
typedef enum
{
	eEffectStageDefault,
	eEffectStageStarting,
	eEffectStagePlaying,
	eEffectStageFinishing,

} EffectStage;

//-----------------------------------------------------------------------------
//	eEffect
//	enumeration of implemented video effects
//-----------------------------------------------------------------------------
typedef enum
{
	eEffectDefault,
	eEffectStillArrangement,
	eEffectFading,
	eEffectFountain
} eEffect;


class CMovieList;

//-----------------------------------------------------------------------------
//	CEffect
//
//	Base class for video effects. Each video effect consists of start stage, 
//	play stage and ending stage. starting and ending stages provide smooth transition 
//  from one videoeffect to another. Their purpose is animate movie frames to 
//  "default" position. Default position is defined  by ComposeDefaultScene() function.
//	All derived effect must provide that scene starts and ends at the default arrangement 
//-----------------------------------------------------------------------------
class CEffect
{
protected:
	EffectStage m_stage;			// current stage
	eEffect m_effect;				// what kind of effect is this
	BOOL m_bComplete;				// TRUE when effect is finished, this flag
									// is used by scene manager to start new effect
	BOOL m_bZOrderUpdated;			// TRUE if ComposeScene() changed Z-order of frames,
									// and Z-sorting is required

	DWORD m_dwStartTransitionTime;	// time of the first stage, in ms
	DWORD m_dwEndTransitionTime;	// time of the last stage, in ms
	LONG  m_lPlayTime;				// time of the middle stage, in ms; or -1 it effect is "eternal"
	DWORD m_dwStartedAt;			// moment when current stage started, in ms, obtained as timeGetTime()
	CMovieList * m_pmovieList;		// movie list provided for this videoeffect

	HRESULT ComposeDefaultScene();				// calculates "default" coordinates, where all effects start and end
	virtual HRESULT ComposeStartTransition();	// calculates frame's coordinates for starting stage
	virtual HRESULT ComposeScene();				// calculates frame's coordinates for playing stage
	virtual HRESULT ComposeEndTransition();		// calculates frame's coordinates for ending stage

public:
	CEffect( eEffect effect );
	virtual ~CEffect();
	
	HRESULT Invalidate();
	HRESULT Initialize(CMovieList *plist, DWORD dwStartTransitionTime, LONG lPlayTime, DWORD dwEndTransitionTime);
	HRESULT Compose();
	HRESULT CopyDefaultCoordinates();
	void Finish();

	// "get" functions 
	BOOL IsComplete()
	{
		return m_bComplete;
	}

	EffectStage GetStage()
	{
		return m_stage;
	}

	eEffect GetType()
	{
		return m_effect;
	}
};

//
//	Implementations of effects
//

//-----------------------------------------------------------------------------
//	CEffectStillArrangement
//  Activated channel in the middle of the screen; with inactive channels
//	are lined-up horizontally below it; starting and ending stages move frames
//	to the default arrangement (see CEffect::ComposeDefaultScene() )
//-----------------------------------------------------------------------------
class CEffectStillArrangement : public CEffect
{
	
	HRESULT CalculateTarget();
	bool m_bTargetCalculated;
	bool m_bNeedToCopyBuffer;

public:
	CEffectStillArrangement();

protected:
	HRESULT ComposeStartTransition();
	HRESULT ComposeScene();
	HRESULT ComposeEndTransition();
};

//-----------------------------------------------------------------------------
//	CEffectFading
//	Starting stage: move from default arrangement to the invisibly far center of the screen;
//  Playing stage: pixel-size rectangle in the middle of the screen (at this point, 
//					adding new frame won't look flashy)
//	Ending stage: return to default arrangement
//-----------------------------------------------------------------------------
class CEffectFading : public CEffect
{
	HRESULT CalculateTarget();
	bool m_bTargetCalculated;

public:
	CEffectFading();

protected:
	HRESULT ComposeStartTransition();
	HRESULT ComposeScene();
	HRESULT ComposeEndTransition();
};

//-----------------------------------------------------------------------------
//	CEffectFountain
//	Playing stage: frame is moving along the circle on x-y plane
//-----------------------------------------------------------------------------
class CEffectFountain : public CEffect
{
public:
	CEffectFountain();

protected:
	virtual HRESULT ComposeStartTransition();
	virtual HRESULT ComposeScene();
	virtual HRESULT ComposeEndTransition();
};

//-----------------------------------------------------------------------------
//	ScenarioNode
//  list node in CEffectQueue (see below)
//-----------------------------------------------------------------------------
typedef struct ScenarioNode
{
	CEffect *pEffect;
	ScenarioNode *pNext;

	ScenarioNode::ScenarioNode()
	{
		pEffect = NULL;
		pNext = NULL;
	}

} ScenarioNode;

//-----------------------------------------------------------------------------
//	CEffectQueue
//	Queue of videoeffects
//-----------------------------------------------------------------------------
class CEffectQueue
{
	ScenarioNode * m_pHead;
public:

	CEffectQueue();
	~CEffectQueue();

	BOOL AddFirst( CEffect *pEffect );
	BOOL AddLast( CEffect *pEffect );
	CEffect * Pop();
};


#endif