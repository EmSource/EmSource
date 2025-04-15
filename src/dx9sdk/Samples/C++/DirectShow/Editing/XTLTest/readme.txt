//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- XTLTest
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========

Command-line tool for rendering and previewing video editing projects. 
This tool renders Microsoft DirectShow Editing Services (DES) project files.

To enable ASF support in this application, link the project to a Microsoft
Windows Media Format (WMF) SDK certificate (WMStub.lib) and #define USE_WMF_CERT 
when you compile the application. See the WMF SDK documentation for instructions 
on obtaining a certificate.

Note:  This application requires Internet Explorer 4.0 or later. If it is not 
present, the application displays the following error message: 
    Unexpected error - DirectShow not installed correctly. 
                       For more information, see IXml2Dex.


User's Guide
============

This sample application demonstrates the following tasks related to video editing:

- Previewing timelines and writing the rendered output to a file. 
- Setting timeline options when rendering timelines. 


Usage

xtltest.exe [switches] input.xtl

By default, the application previews the project. The following command-line 
switches are supported.

/C                  No clock. Render the project as quickly as possible, 
                        without synchronizing audio and video. 

/D                  Load source files dynamically. For more information, 
                        see IRenderEngine::SetDynamicReconnectLevel.  

/[double-double]    Set the rendering start and stop times. 
                        For example, /[3-4] renders one second of the timeline, 
                        starting 3 seconds into the project. 

/G filename.grf     Output a GraphEdit file in .grf format. 

/N                  No rendering. The project is not previewed or rendered to 
                        a file. This option is useful for validating the 
                        input file, or with the /G switch. 

/R                  Activate smart recompression. The application uses the 
                        first clip in the timeline for the compression format. 
                        Use the /W switch with this option. 
                        For more information, see "About the Render Engines". 

/W filename         Render the timeline to a file.  The file type is determined 
                        by the file extension. The application supports 
                        AVI and WAV files.  If the application is compiled 
                        with a WMF SDK certificate, it also supports ASF files. 
                        This option suppresses preview. 

/X filename.xtl     Save the project as an XML file. The new file is 
                        functionally identical to the input file, although 
                        the XML tags may differ. 



If the USE_WMF_CERT flag is defined, then the following switches also apply:

/P [number]         Choose an ASF compression profile. Available only if the 
                        application is compiled with a WMF SDK certificate. 

/P                  List available ASF profiles. Available only if the 
                        application is compiled with a WMF SDK certificate. 


NOTE: If you define USE_WMF_CERT, you must install the Windows Media
Format SDK to acquire the appropriate Windows Media header files
referenced by this sample.  The SDK download page is located at 

    http://msdn.microsoft.com/workshop/imedia/windowsmedia/sdk/wmsdk.asp, 

with links to the SDK itself and information for obtaining a certificate.
