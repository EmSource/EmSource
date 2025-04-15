//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Picture-In-Picture
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


This sample is an interactive video player, which uses the
Windows XP Video Mixing Renderer's Windowless Mode to blend
multiple video streams in a window.

After loading two media files, you can use the keyboard and 
function keys to move and resize the secondary media stream.
You may also flip, mirror, and swap the streams with or without
an animation effect.


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
