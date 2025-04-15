//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- PlayWndASF
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

Usage
=====

    playwndasf <media filename>


Using Windows Media 9 Series (Corona)
=====================================

If you have installed the Windows Media Format 9 SDK (code named 'Corona'),
then you should review the DSPlay sample in that SDK instead.  Starting with
Windows Media 9 Series, the WMStub.lib and key provider implementation are no longer
necessary.  The DSPlay sample also demonstrates Corona-specific features
and implementation details that are not present in this PlayWndASF sample.


If you are not using the WMF 9 SDK, then the following note applies:

================================================================================
NOTE: To link and run this sample, you must install the Windows Media Format SDK 7.1.1.

After downloading the Format SDK, you can extract a public version of the
WMStub.LIB library, which should be copied to the Samples\C++\DirectShow\Common folder.
This library is necessary for enabling Windows Media content.

Without this library in the Common folder, you will receive a linker error:
    LNK1104: cannot open file '..\..\common\wmstub.lib'

If you remove the WMStub.lib from the project's linker settings, the linker
will fail with this unresolved reference:
       WMCreateCertificate

================================================================================


Description
===========

    This sample is an interactive audio/video media file player with limited
    support for Digital Rights Management.  It uses DirectShow to play 
    Windows Media files (ASF, WMA, WMV) encoded with or without DRM protection. 
    
    If the media has a video component, PlayWndASF will read the video's
    default size and adjust the player's client area to allow the video
    to play at its preferred default size (taking into account the size of
    caption bar & borders).

    You may mute the audio by pressing 'M'.  You may toggle full-screen mode
    by pressing 'F'.  You can pause/resume playback with 'P' and stop/rewind
    with 'S'.  To close the media clip, hit ESC, F12, X, or Q.

    If the media is audio-only, the player will display a small default window.

    You can specify a media file as the only command line argument:
    	Ex:  PlayWndASF \\myserver\mediafiles\video\sample.asf

    If no file is specified, the application will automatically display the
    Windows OpenFile dialog so that you can choose a file.

    Use the menu bar or the close button to exit the application.


Accessing media files:

    The media file may exist in your hard disk, CD-ROM, or on a network server.

 If the file is on a network server:
    You may read a media file from a network server if you provide the full URL.
    For example, "PlayWndASF http://myserver/mediafiles/video/myvideo.asf" will
    read the file from the server into system memory.  This approach will fail
    if the media file is too large to fit in memory.


Limitations:

    This sample will only render media files that are supported by the
    DirectShow subsystem.  If you attempt to play a video (AVI, QuickTime, MPEG)
    that is encoded with an unsupported Codec, you will only see a black
    screen or no visible change to the display, although you should hear the
    associated audio component if it uses a supported format.

    This sample will not play .ASX files.


User Input:

    Simple user input is supported through the keyboard or through the 
    application's main menu bar.

    Keyboard                    Action
    --------                    ------
    P                           Play/Pause toggle
    S                           Stop and Rewind to beginning
    M                           Audio mute toggle
    F                           Full-screen mode toggle
    Spacebar                    Step one frame
    Quit to menu (closes file)  ESC or Q or X or F12


NOTES
=====
This sample uses Windows Media headers and libraries, which are provided
in the Samples\C++\DirectShow\Common samples directory.

This sample enforces a minimum window size to prevent video window problems
when small videos are resized.  You may not resize a video to play in a window 
that is smaller than the defined minimum size.


Support for Digital Rights Management (DRM)
===========================================
You will need to acquire and link with a DRM stub library in order to
render and play content that is protected by DRM.  You cannot play DRM-encoded
content if you link with the default WMStub.lib library in the 
Windows Media Format SDK, since it does not support DRM.

More information on DRM is available on the Microsoft web site at
http://www.microsoft.com/windows/windowsmedia/drm.asp.

