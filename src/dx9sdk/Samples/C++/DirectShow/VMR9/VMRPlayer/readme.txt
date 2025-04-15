//-----------------------------------------------------------------------------
// Name: Windows XP DirectShow Sample -- VMRPlayer9
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========

This sample demonstrates using the Windowless mode of the 
DirectX 9 Video Mixing Renderer 9 to blend one or two running videos 
and a static image.  

Begin by opening a primary video stream from the File menu.  If you
would like to render a second file that will be alpha-blended with
the primary file, then open a secondary video stream from the File menu.

To control size, position, and alpha blending properties of the 
primary or secondary video, choose "Primary Stream" or "Secondary Stream"
from the VMR Properties menu.  By default, the Primary stream will have
an alpha value of 1.0 and the secondary stream will blend with an 
alpha value of 0.5.  The properties dialogs are implemented as modal dialogs.

You may also overlay an alpha-blended static image by opening the 
"Static App Image" option on the VMR Properties menu.  Enable the
"Display App Image" checkbox to cause the image to appear.  By default,
the image will be centered and will blend with an alpha value of 0.5.


NOTE: This sample requires DirectX 9 (or greater) functionality 
and will exit on other systems.


Usage:
======
    VMRPlayer </P filename>

	/P: Optional filename to automatically render and play at startup



Windows Media is not supported in most VMR9 samples
---------------------------------------------------

Because of the Windows Media Format SDK (and WMStub.lib) dependency,
along with the extra filter connection and key provider code required,
the DirectShow SDK Video Mixing Renderer 9 samples do not support
rendering and playback of Windows Media content (ASF, WMA, WMV) by default.

If you attempt to open a Windows Media file with these samples, you will be 
presented with a message box indicating the lack of Windows Media support, 
with a pointer to the samples that do properly support Windows Media files.

The following samples provide the necessary extra code and project settings
to enable proper Windows Media support (including unlocking of "keyed" files):

        - ASFCopy   - AudioBox  
        - Jukebox   - PlayWndASF

For more detailed information, see "Using DirectShow->Windows Media Applications"
in the DirectX SDK documentation.

