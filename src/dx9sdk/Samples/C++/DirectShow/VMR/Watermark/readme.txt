//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Watermark
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========

This sample is an interactive video player, which uses the
Windows XP Video Mixing Renderer's Windowless Mode to blend
video and a static image.

Watermark demonstrates the VMR's ability to alpha blend a
static image with the running video stream (or with multiple
video streams).  In addition to displaying a watermark (logo)
in the bottom right corner of the window, this sample also
demonstrates how to flip, mirror, manipulate alpha, and move
a bitmap around in the application's video window.

To create an animated logo, a multiple-image bitmap is loaded
which contains five similar images.  When the animation effect
is activated, Watermark displays these images sequentially in 
response to timer events.


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
