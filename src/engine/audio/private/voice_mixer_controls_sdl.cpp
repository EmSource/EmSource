//========= Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//


#include "tier0/platform.h"
#include "ivoicerecord.h"
#include "voice_mixer_controls.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


class CMixerControls : public IMixerControls
{
public:
	CMixerControls() {}
	virtual			~CMixerControls() {}
	
	virtual void	Release() {}
	virtual bool	GetValue_Float(Control iControl, float &value ) {return false;}
	virtual bool	SetValue_Float(Control iControl, float value) {return false;}
	virtual bool	SelectMicrophoneForWaveInput() {return false;}
	virtual const char *GetMixerName() {return "SDL"; }
	
private:
};

IMixerControls* g_pMixerControls = NULL;
void InitMixerControls()
{
	if ( !g_pMixerControls )
	{
		g_pMixerControls = new CMixerControls;
	}
}

void ShutdownMixerControls()
{
	delete g_pMixerControls;
	g_pMixerControls = NULL;
}

