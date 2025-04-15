//-----------------------------------------------------------------------------
// Name: Windows XP DirectShow Sample -- TxtPlayer
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


This sample demonstrates using the Video Mixing Renderer and
a custom allocator-presenter to render alpha-blended text over
a running video.

NOTE: This sample requires Windows XP (or greater) functionality 
and will exit on other systems.

Usage:
	TxtPlayer </P filename>

	/P: Optional filename to automatically render and play at startup



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
