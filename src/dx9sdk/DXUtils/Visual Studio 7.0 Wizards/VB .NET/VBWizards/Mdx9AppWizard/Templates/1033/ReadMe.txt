========================================================================
    Managed DirectX Application Wizard : "[!output PROJECT_NAME]" Project Overview
========================================================================

The Managed DirectX Application Wizard has created this "[!output PROJECT_NAME]" project for you as a starting point.

This file contains a summary of what you will find in each of the files that make up your project.

[!output PROJECT_NAME].vbproj
    This is the main project file for projects generated using the Managed DirectX Application Wizard. 
    It contains information about the version of the product that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Managed DirectX Application Wizard.

[!if USE_DIRECTINPUT]
dinput.vb
    This contains functionality for using Managed DirectInput.
[!endif]
[!if GRAPHICSTYPE_NOGRAPHICS]

graphics.vb
    This file contains routines for drawing to the screen via GDI+.
[!endif]
[!if GRAPHICSTYPE_DIRECT3D]

d3dapp.vb
d3denumeration.vb
d3dfont.vb
d3dutil.vb
D3DSettingForm.vb
    These files contain base classes for setting up and rendering to Managed Direct3D devices.
[!endif]
[!if VISUALTYPE_TRIANGLE && GRAPHICSTYPE_DIRECT3D]

D3DTriangle.vb
    This file contains code to render a triangle to a Managed Direct3D device.
[!endif]
[!if VISUALTYPE_D3DBLANK && GRAPHICSTYPE_DIRECT3D]

D3DBlank.vb
    This file contains template code that can be easily modified to render to a Managed Direct3D device.
[!endif]
[!if VISUALTYPE_TEAPOT && GRAPHICSTYPE_DIRECT3D]

D3DMesh.vb
    This file contains code to renders a teapot mesh to a Managed Direct3D device.
[!endif]
[!if GRAPHICSTYPE_DIRECTDRAW]

ddraw.vb
    This file contains code to render graphics to the screen using Managed DirectDraw.
[!endif]
[!if USE_AUDIO]

audio.vb
    This file contains code to playback wav and multimedia files.
[!endif]
[!if USE_DIRECTPLAY]

dplay.vb
DPlayConnect.vb
    These files contain helper classes that setup Managed DirectPlay connections.
[!endif]
[!if USE_VOICE]

DPlayVoiceWizard.vb
    This file contains helper classes to connect using Managed DirectPlayVoice.
[!endif]