//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Blender
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


This sample is an interactive video player, which uses the
Windows XP Video Mixing Renderer's Windowless Mode to blend
multiple video streams in an MFC dialog-based application.

After loading two user-selected video files, Blender will 
display both video streams in a portion of the dialog, using
the video mixing capability of the VMR.  Alpha values are
set by default to allow both streams to be partially visible.

You can manipulate the X, Y, width, height, and alpha blending 
values for each video stream.  You may also flip or mirror
each video stream by clicking its associated check box.


NOTE: This sample requires Windows XP (or greater) functionality 
and will exit on other systems.


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
