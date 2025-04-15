//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Text
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


This sample is an interactive video player, which uses the
Windows XP Video Mixing Renderer's Windowless Mode to blend
video and text.

It uses the VMR's IVMRMixerBitmap interface to blend text onto
the bottom portion of the video window, in a style similar to
closed-captioning text.  The text is written onto a dynamically
created bitmap, which is then blended with the running video.  

The text string updates automatically every two seconds, but 
you can also advance the text by pressing the space bar.  You may
adjust the font and color of the blended text by choosing the 
Set Font menu option.


NOTE: This sample requires Windows XP (or greater) functionality 
and will exit on other systems.

KNOWN ISSUE: Some popular video drivers incorrectly advertise the 
D3DPTEXTURECAPS_NONPOW2CONDITIONAL flag, which indicates that the driver 
supports non-power-of-2 textures.  Because of this driver bug, you may 
see garbled text in the place of the alpha-blended text bitmap.  


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
