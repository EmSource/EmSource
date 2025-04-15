//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- MultiVMR9 sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


This sample set demonstrates using a custom VMR9 Allocator-Presenter in a
multi-graph environment.  There are three sample folders:

- DLL: Helper library which demonstrates how to implement a user-provided 
 (customized) allocator-presenter for the Video Mixing Renderer 9 in a 
 multigraph environment. 

- MultiPlayer: Alows you to load and control multiple media files.  You can
  seek each stream and control its position, FPS, aspect ratio, Z order,
  and alpha value.

- GamePlayer: Illustrates how to integrate video powered by VMR9 into a
  Direct3D environment (perhaps in a 3D game).  Note that this sample will not
  build UNICODE due to a D3DX header dependency.



NOTE: This sample requires DirectX 9 (or greater) functionality 
and will exit on other systems.

NOTE: You must build MultiVMR9.dll and register it with 'regsvr32' before
you can run the applications.


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
