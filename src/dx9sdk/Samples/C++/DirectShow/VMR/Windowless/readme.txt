//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Windowless
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

Description
===========

This sample is an interactive video player, which uses the
Windows XP Video Mixing Renderer's Windowless Mode to render video.

It offers features similar to the PlayWnd player sample in the
main DirectShow samples directory.

You may capture the image currently being displayed in the 
video window by clicking the right mouse button or by selecting
"Capture current frame" on the Image menu.  The image is provided
by the Video Mixing Renderer, using the reliable GetCurrentImage()
method on the IVMRWindowlessControl interface.


This sample requires Windows XP (or greater) functionality 
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
