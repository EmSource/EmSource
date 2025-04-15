// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(STDAFX_H_INCLUDED_)
#define STDAFX_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

$$IF(DINPUT)
#define DIRECTINPUT_VERSION 0x0800
$$ENDIF
#include <windows.h>
#include <basetsd.h>
#include <math.h>
#include <stdio.h>
#include <DXErr9.h>
#include <tchar.h>
$$IF(DINPUT)
#include <dinput.h>
$$ENDIF
$$IF(DPLAY)
#include <dplay8.h>
#include <dplobby8.h>
$$ENDIF
$$IF(ACTIONMAPPER)
#include "DIUtil.h"
$$ENDIF
$$IF(DMUSIC)
#include "DMUtil.h"
$$ENDIF
$$IF(DSOUND)
#include "DSUtil.h"
$$ENDIF
$$IF(DPLAY)
#include "NetConnect.h"
$$ENDIF
$$IF(DPLAYVOICE)
#include "NetVoice.h"
$$ENDIF
#include "DXUtil.h"
#include "resource.h"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(STDAFX_H_INCLUDED_)
