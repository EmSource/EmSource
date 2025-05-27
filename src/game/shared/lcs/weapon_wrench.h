//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef WEAPON_WRENCH_H
#define WEAPON_WRENCH_H
#ifdef _WIN32
#pragma once
#endif


#include "weapon_csbase.h"


#if defined( CLIENT_DLL )

	#define CWrench C_Wrench
	#define CWrenchGG C_WrenchGG

#endif


// ----------------------------------------------------------------------------- //
// CWrench class definition.
// ----------------------------------------------------------------------------- //

class CWrench : public CWeaponCSBase
{
public:
	DECLARE_CLASS( CWrench, CWeaponCSBase );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

	
	CWrench();

	// We say yes to this so the weapon system lets us switch to it.
	virtual bool HasPrimaryAmmo();
	virtual bool CanBeSelected();
	
	virtual void Precache();

	void Spawn();
	bool SwingOrStab( CSWeaponMode weaponMode );
	void PrimaryAttack();
	void SecondaryAttack();
	void WeaponAnimation( int iAnimation );

	virtual bool Deploy();

	bool CanDrop();

	void WeaponIdle();

	virtual CSWeaponID GetCSWeaponID( void ) const		{ return WEAPON_WRENCH; }

private:
	CWrench( const CWrench & ) {}

#ifndef CLIENT_DLL

	bool m_swingLeft;

#endif

};

class CWrenchGG : public CWrench
{
public:
	DECLARE_CLASS( CWrenchGG, CWrench );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

	virtual CSWeaponID GetCSWeaponID( void ) const		{ return WEAPON_WRENCH_GG; }
};

#endif // WEAPON_WRENCH_H
