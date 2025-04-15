//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- VMR9Allocator
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========

This sample is designed to show how to render streaming media (MPEG, ASF, AVI
and other formats) into a D3D Scene using the Video Mixing Renderer 9 filter.

The sample creates an object that implements IVMRSurfaceAllocator9 and
IVMRImagePresenter9.  The object takes over surface and texture allocation
and rendering of the decoded frames into a Direct3D9 scene environment.
For simplicity, the VMR9Allocator has just one 3D plane with 2 shaded vertices
that is being rotated.

The GUI allows for resizing the window and selecting different movie sources.
The code shows how to properly allocate and present the streaming media and
how to restore the surfaces in case the devices are lost.



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

