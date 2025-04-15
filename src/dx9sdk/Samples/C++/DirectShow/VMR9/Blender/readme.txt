//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Blender9
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


This sample is an interactive video player, which uses the
Windowless mode of the DirectX 9 Video Mixing Renderer 9 to blend
multiple video streams in an MFC dialog-based application.

After loading two user-selected video files, Blender will 
display both video streams in a portion of the dialog, using
the video mixing capability of the VMR9.  Alpha values are
set by default to allow both streams to be partially visible.

You can manipulate the X, Y, width, height, and alpha blending 
values for each video stream.  You may also flip or mirror
each video stream by clicking its associated check box.


NOTE: This sample requires DirectX 9 (or greater) functionality 
and will exit on other systems.


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

