//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Jukebox
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

Description
===========

The video jukebox application scans a directory for media files and displays 
a list of the relevant file names.  The user can play an individual file or play 
all of the media files in order.  The jukebox also displays information about the 
filter graphs that it creates, including the names of the filters, the names of their
corresponding pins, and the event codes that are generated.


Using Windows Media 9 Series (Corona)
=====================================

If you have installed the Windows Media Format 9 SDK (code named 'Corona'),
then you can benefit from enhancements in the WMF9 SDK.  Starting with
Windows Media 9 Series, the WMStub.lib and key provider implementation are no longer
necessary.  Therefore, certain portions of this sample are conditionally compiled
with "#ifndef TARGET_WMF9", and new build targets are provided to remove the linking
of the WMStub library when targeting Corona systems.

To target Corona, build the WMF9-specific targets in the Visual C++ project.
For example, select "Win32 WMF9 Release" target (instead of "Win32 Release")
and Rebuild All.  These configurations define the "TARGET_WMF9" preprocessor
constant and do not link with WMStub.lib.


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


Note:  This sample requires Microsoft Foundation Class Library 4.2 (Mfc42.dll).


User's Guide
============

If a directory name is specified as a command-line argument, the jukebox scans 
that directory at startup.  Otherwise, it scans the default SDK media directory, 
which is located at Samples\Multimedia\Media under the SDK root directory.  
The jukebox displays a list of all the media files in the directory, from which 
the user can select a file to play.

When you select a video file from the files list, Jukebox will display its
first video frame in the "Video Screen" window.  If you select an audio-only
file, the video screen will be painted gray.

The jukebox offers the following user-interface elements:

Play, Stop, Pause, and FrameStep buttons: Use these buttons to control graph
    playback.  (The FrameStep button might be disabled, if the graph does not
    support the IVideoFrameStep interface.) 

Thru and Loop buttons: Click the Thru button to play through the entire file list, 
    starting from the current selection.  Click the Loop button to loop the same 
    file repeatedly.  These two buttons are mutually exclusive. 

Mute button: Mutes the audio. 

Filters, Input Pins, and Output Pins: When the jukebox creates a graph, 
    it displays a list of the filters in the graph.  If the user selects one 
    of the filter names, the jukebox displays a list of the filter's input pins 
    and a list of the filter's output pins. 

Display Events: If this box is checked, the jukebox displays the event codes 
    that it receives.  To clear the list, click the Clear button. 

Properties button: To view a filter's property pages, select the filter name 
    and click the Properties button.  If the filter does not support 
    a property page, the button is disabled. 
