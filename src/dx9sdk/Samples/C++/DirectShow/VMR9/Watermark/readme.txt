//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Watermark9
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========

This sample is an interactive video player, which uses the
Windowless mode of the DirectX 9 Video Mixing Renderer 9 to blend
video and a static image.

Watermark demonstrates the VMR9's ability to alpha blend a
static image with the running video stream (or with multiple
video streams).  In addition to displaying a watermark (logo)
in the bottom right corner of the window, this sample also
demonstrates how to flip, mirror, manipulate alpha, and move
a bitmap around in the application's video window.

To create an animated logo, a multiple-image bitmap is loaded
which contains five similar images.  When the animation effect
is activated, Watermark displays these images sequentially in 
response to timer events.


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
