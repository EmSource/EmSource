//-----------------------------------------------------------------------------
// Name: Windows XP DirectShow Sample -- VMRMix
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description: 
============
    This application shows capabilities of the new
    video mixing renderer (VMR) that is the default video 
    renderer in Windows XP.  In particular, it demonstrates 
    how to use the VMR in a mixing mode with several sources, 
    how to apply a bitmap image with a color key over the video, 
    and how to take advantage of the IVMRMixerControl interface 
    to manage source and destination rectangles and alpha-level 
    for each media stream.

Usage:
======
    Upon initialization, VMRMix asks the user to specify a 
    media folder that contains at least two valid media files, 
    after which it loads media settings from that folder.  
    The user is asked to specify playback options: 
    number of source files, size of the playback window, and 
    whether to display a static bitmap image.  When the user 
    clicks on the 'Play' button, a new window appears to mix 
    the selected streams.  The demonstration lasts until the 
    longest media file reaches the end.  You can interrupt the 
    demonstration  by closing the playback window.

Troubleshooting:
================
    This application was originally created as a stress test, 
    so it uses more system resources when displaying a maximum 
    number of streams and when using "full-screen" mode.  If 
    video is freezing or slows down, try selecting fewer sources 
    and turn off the "full-screen" option.


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
