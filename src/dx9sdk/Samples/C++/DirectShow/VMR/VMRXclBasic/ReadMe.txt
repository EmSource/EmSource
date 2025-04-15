//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- VMR XCL Basic
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


This application is a simple, step by step sample that demonstrates 
how to play a video in exclusive mode using the VMR and DirectShow.

The application will prompt for a file name to play and then play it
until the video is done or until the user exits the application by 
pressing Esc or Alt+F4.

This sample requires a video adapter than can be set to 640x480 resolution
at 32-bit display depth.  Some older video cards support only 16-bit and
24-bit resolutions, which would prevent this sample from running properly.


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
