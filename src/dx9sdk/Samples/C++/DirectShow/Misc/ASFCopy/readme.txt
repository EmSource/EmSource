//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- ASFCopy
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

Description
===========

Transcodes one or more files to an ASF file.


Using Windows Media 9 Series (Corona)
=====================================

If you have installed the Windows Media Format 9 SDK (code named 'Corona'),
then you should review the DSCopy sample in that SDK instead.  Starting with
Windows Media 9 Series, the WMStub.lib and key provider implementation are no longer
necessary.  The DSCopy sample also demonstrates Corona-specific features
and implementation details that are not present in this ASFCopy sample.


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


Usage:
===========

ASFCopy [/v] /p profile file1 [file2 ...] target

The following command-line switches are supported:
    /p Specifies the profile number. 
    /v Verbose mode. 

Specify an ASF profile using the /p switch.  If you omit this switch, ASFCopy 
displays a list of the standard system profiles.

Specify the name of one or more source files, and the name of the target file. 
If you specify more than one source file, the application multiplexes all of 
the source files.  You must specify a profile that matches the streams 
contained in the source files, or else the application will not work correctly. 
For example, if you specify Video for Web Servers (56 Kbps), the combined 
source files must have exactly one video stream and one audio stream.



NOTE: This sample uses Windows Media headers and libraries, which are provided
in the DirectShow\Common samples directory.