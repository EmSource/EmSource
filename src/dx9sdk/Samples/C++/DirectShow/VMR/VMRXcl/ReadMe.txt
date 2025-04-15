//-----------------------------------------------------------------------------
// Name: Windows XP DirectShow Sample -- VMRXCL
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description: 
============
    This application shows capabilities of the new
    video mixing renderer (VMR) that is the default video 
    renderer in Windows XP.  In particular, it demonstrates 
    how to use the VMR in exclusive DirectDraw mode and 
    how to implement a user-provided (customized) Allocator-Presenter
    for the VMR.  Also, it contains useful utilities to manage 
    bitmaps (as textures) and TrueType fonts for text over video.

    This sample requires a video adapter than can be set to 640x480 resolution
    at 32-bit display depth.  Some older video cards support only 16-bit and
    24-bit resolutions, which would prevent this sample from running properly.


Usage:
======
    Upon initialization, VMRXCL asks you to specify a video file.
    The application switches to DirectDraw exclusive mode, after setting
    the display mode to 640 x 480 x 32bpp.  A bitmap-based menu on the 
    left side of the screen provides interactivity.
    (From top to bottom, the menu items are: 
	- Show statistics
	- Pause
	- Run
	- Rotate in XY plane
	- Rotate in YX plane
	- 'Twist' non-linear effect
	- Exit

    Right click over the menu button to activate its text hint.
    Left click to hide text hints.

Troubleshooting:
================
    Depending on the capabilities of your video driver, text may be disabled.
    You may also experience glitches with bitmaps applied over the video.

NOTE: 
=====
    The speed of the 3D animation is directly related to the frame rate of
    the video file being played.


Windows Media support in VMR samples
------------------------------------

Because of the Windows Media Format SDK (and WMStub.lib) dependency,
along with the extra filter connection and key provider code required,
the DirectShow SDK Video Mixing Renderer samples do not fully support
rendering and playback of Windows Media content (ASF, WMA, WMV) by default.

Many of these samples allow you to render ASF/WMA/WMV files with the legacy
DirectShow ASF Reader filter, which is adequate for simple playback.  This method,
however, does not offer the benefits of the newer Windows Media ASF Reader filter
and does not support "dekeying" of keyed Windows Media content.

For more detailed information, see "Using DirectShow->Windows Media Applications"
in the DirectX SDK documentation.
