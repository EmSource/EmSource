//----------------------------------------------------------------------------
//	File:	VMRMulti.h
//
//	Desc:	DirectShow sample code
//
//	Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#ifndef __INC_VMRMULTI_H
#define __INC_VMRMULTI_H



class CTransEffectBase {

public:

    HRESULT GetTime(FLOAT* lpfCurrTime) = 0;

    HRESULT GetEffectName(TCHAR* lpszName, DWORD dwLen) = 0;

    HRESULT InititalizeEffect(FLOAT fEffectDuration,
                              LPDIRECTDRAWSURFACE7 lpddTexFrom,
                              LPDIRECTDRAWSURFACE7 lpddTexTo) = 0;

    HRESULT RenderEffect(LPDIRECT3DDEVICE7 pd3dDevice, RECT lpDest) = 0;

    HRESULT GetEffectDuration(FLOAT* lpfTime) = 0;

    HRESULT IsEffectCompleted() = 0;

}
#endif
