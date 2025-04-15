//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- AudioBox
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

Description
===========

This MFC application is an audio-only media player similar to Jukebox.
You can select a media directory and play all audio media files,
including Windows Media Files.  Options include seeking, muting audio,
randomizing file selection, adjusting volume, and looping the current 
media file.

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


