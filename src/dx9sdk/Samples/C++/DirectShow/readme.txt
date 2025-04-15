=============================================================================
DirectShow SDK Samples README
=============================================================================

The DirectShow SDK samples are subdivided into directories according to 
their major function:

    BaseClasses
    BDA
    Capture
    Common (shared source files)
    DMO
    DVD
    Editing
    Filters
    Misc
    Players
    VideoControl
    VMR
    VMR9

There are also several Visual Basic 6.0 samples in the Extras\DirectShow\VB Samples
directory.  Even if you don't develop applications with Visual Basic, we recommend
that you review the Visual Basic sample executables.  Applications like
SlideShow and Trimmer demonstrate many DirectShow Editing Servies (DES)
capabilities that are not demonstrated in C++ samples.  The DexterVB tool
(Timeline Explorer) is also useful for exploring and visualizing XML timelines
used with DES.

See the "What's New" section below for information on new features in this release.


Setting up the build environment
--------------------------------
In your Visual C++ build environment, be sure to set your Include and Lib 
directories to point to the DirectX 9 SDK's include and lib paths.
The DirectX SDK directories must be the first directories in the search path.
Otherwise, you may encounter linker errors, since you would continue using
the headers and libraries supplied with Visual C++ or with an earlier version
of the Platform SDK.

Visual C++ project files are included for four targets:
    Win32 Release, Win32 Debug, Win32 Release Unicode, Win32 Debug Unicode

For general information about building the DirectX SDK samples, see 
"Compiling DirectX Samples and Other DirectX Applications" 
in the "Programming DirectX with C/C++" section of the DirectX 9 documentation.

For DirectShow build information, see "Setting Up The Build Environment" in the 
DirectShow "Getting Started" section of the DirectX documentation.


Building the Samples
--------------------

There are multiple ways to build the SDK samples, and we provide project
files and workspaces for both Visual C++ 6.0 and Visual Studio.NET:

    1) Using the main DShow.DSW workspace (or DShow.SLN solution) for Visual C++
    2) Using a workspace/solution provided for a category of samples
    3) Building individual projects with their VC++ workspaces/solutions

1) Using the Visual C++ Workspace or Visual Studio.NET Solution files:

The easiest way to build all samples is to open DShow.DSW (or DShow.SLN),
which is installed to the DirectShow samples root directory.  This workspace
includes references to each of the project files for the individual samples.
You can select a project (in the FileView pane) and right-click to display a
build menu for the project.  Select 'Build' to build a project and its 
dependencies.  Note that if you select 'Build (selection only), you will not
automatically build any dependencies (like the base classes, if required).  

You can also build or rebuild all of the projects together by selecting
'Build->Batch Build' from the Visual C++ main menu.  Projects included in
this workspace know their dependencies and will build them if needed.

Some of the projects listed in the FileView pane do not build applications,
but instead build support libraries used by other projects within the main
workspace.  For example, the GargleDMO sample depends on the 'ControlBase'
and 'MedParamBase' projects that are contained within the workspace.  
If you build GargleDMO, Visual C++ will automatically build the 
ControlBase and MedParamBase libraries if they need to be built, and those
libraries will be linked into the GargleDMO DLL.


2) Using a workspace/solution provided for a category of samples:

We have also provided workspace/solution files for the sample subdirectories,
so that you can build all of the samples of a particular type.
For example, if you want to build only the Capture samples, you can
open Capture\Capture.DSW (or Capture.SLN) and build the desired samples 
individually or as part of a batch build.


3) Building Individual Projects:

You can open any of the provided project or workspace files in Visual C++
if you want to build, modify, or debug an individual sample.  If you build
outside of the DShow.DSW workspace, however, you might need to first build the
DirectShow Base Classes, which are installed to the "BaseClasses" directory.

Note: The DirectMedia 6 SDK installed binaries for the BaseClasses
(as strmbase.lib and the debug build as strmbasd.lib), which were compiled versions
of the base classes previously installed into the SDK's classes\base directory.  
DirectX now ships the source code for these base classes as a sample project,
which allows you to modify the classes and build them with Visual C++.
Since many of the samples (especially the sample filters) need to link with 
STRMBASE.LIB (or STRMBASD.LIB), you must first build the base classes 
to allow you to build other sample filters and applications that use them.

Don't forget to build both Debug and Release versions of the BaseClasses
project if you intend to build both Debug and Release versions of the samples.


Building Windows Media-related samples
--------------------------------------

Building the Windows Media-enabled samples (AudioBox, ASFCopy, Jukebox, PlayWndASF)
requires the Microsoft Windows Media Format SDK and a valid software certificate.  
The SDK download page is located at:

    http://msdn.microsoft.com/workshop/imedia/windowsmedia/sdk/wmsdk.asp
    
with links to the SDK itself and information for obtaining a certificate.
Once installed, the WMStub.lib and WMVCore.lib libraries should be copied into the
[\DXSDK\Samples\C++\DirectShow\Common] folder in your DirectX SDK installation.

Because of the dependency on the Windows Media Format SDK, the project files
for the affected samples are omitted from the main DirectShow Visual C++ 
workspace files (dshow.dsw, dshow.sln) to prevent build issues.


Windows Media support in SDK samples
------------------------------------

Because of the Windows Media Format SDK (and WMStub.lib) dependency, along with
the extra filter connection and key provider code required, most of the
DirectShow SDK samples (particularly the VMR samples) do not fully support
rendering and playback of Windows Media content (ASF, WMA, WMV) by default.
If you attempt to open a Windows Media file using one of these samples, you will
be presented with a message box indicating the lack of Windows Media support, 
with a pointer to the samples that do properly support Windows Media files.

The following samples provide the necessary extra code and project settings
to enable proper Windows Media support (including unlocking of "keyed" files):

        - ASFCopy   - AudioBox  
        - Jukebox   - PlayWndASF

Many of the other samples allow you to render ASF/WMA/WMV files with the legacy
DirectShow ASF Reader filter, which is adequate for simple playback.  This method,
however, does not offer the benefits of the newer Windows Media ASF Reader filter
and does not support "dekeying" of keyed Windows Media content.

For more detailed information, see "Using DirectShow->Windows Media Applications"
in the DirectX SDK documentation.


Using Windows Media 9 Series (Corona)
-------------------------------------

If you have installed the Windows Media Format 9 SDK (code named 'Corona'),
then you should also review the SDK samples in that SDK (particularly the
DSCopy and DSPlay samples).  Beginning with Windows Media 9 Series and
the Windows Media Format 9 SDK, the WMStub.lib and key provider implementation code
are no longer necessary.  This simplifies the sample code and removes the need
to download and link with a WMStub library.

There are two samples in the DirectShow samples tree - Jukebox and Audiobox -
that demonstrate some of the implementation differences between pre- and post-Corona
systems.  These two samples have additional build targets for "WMF9" that
remove the WMStub linking and define a preprocessor constant (TARGET_WMF9) 
which disables the key-providing code.  These extra build targets are provided 
to demonstrate compatibility with both system configurations.  

For more details, see the Windows Media Format 9 SDK documentation.


Building for Windows XP
-----------------------
If you want to target Windows XP specifically to use its new features, 
you must set WINVER=0x501 in the sample project file.  You must also 
install the Windows XP Platform SDK, however, to ensure that you have the 
latest header files.  For example, wxutil.cpp in the BaseClasses directory
uses the new TIME_KILL_SYNCHRONOUS flag only if (WINVER >= 0x501).  This flag 
is conditionally defined in the Windows XP Platform SDK in mmsystem.h, 
but only if WINVER is also set to 0x501 when compiling.  

To prevent build issues, upgrade to the latest version of the Platform SDK.


VMR9 Hardware requirements
--------------------------

The VMR9 samples require a video card with a minimum of 16MB of video RAM.
If your card has less than the minimum RAM, you may see failures when
building filter graphs.  If that occurs, try lowering your display resolution.



=============================================================================
What's New in DirectShow for DirectX 9.0
=============================================================================
November, 2002
=============================================================================

New runtime features
--------------------

- Video Mixing Renderer Filter 9 (VMR-9). - This new, redistributable 
  rendering filter is similar in concept and design to the VMR that is 
  available for Microsoft Windows XP Home Edition and Windows XP Professional. 
  The VMR-9 is more powerful than the original VMR (now called "VMR-7") 
  because it is fully compatible with the DirectX 9.0 graphics capabilities 
  and it offers improved support for deinterlacing and ProcAmp control 
  (brightness, contrast, hue, and saturation).

- New deinterlacing support in the DV Video Decoder filter. The DV Decoder 
  filter now supports interlaced output, as well as deinterlaced output. 
  Earlier versions of the decoder always deinterlace the video. 
  With the new version, the interlaced video can be preserved and 
  saved to file, or the video can be deinterlaced by the VMR, 
  for improved rendering quality.

- New deinterlacing support in DirectX Video Acceleration. 

- AVStream driver development and runtime support on all platforms 
  prior to Windows XP has been improved for close functional parity 
  with Windows XP. A few AVStream and core Kernel Streaming 
  behavioral differences still exist that are documented in the SDK.

- New encoder application programming interface (API) specification.
  The Encoder API defines a standard, format-neutral way in which software 
  or hardware encoders can communicate with applications and device drivers. 
  IGetCapabilitiesKey is a new interface that filters can implement 
  in order to enable applications to query for the filter's capabilities.

- MPEG-2 Sections and Tables Filter. This new filter enables an application 
  to get PSI tables from an MPEG-2 transport stream. 

- Microsoft TV Technologies now supports DVB-T (terrestrial) and DVB-C (cable), 
  in addition to DVB-S (satellite). For more information, see the SDK documentation.

- The Analog TV Tuner filter now supports adding new channel frequencies via the registry. 
  This feature extends the existing mechanism for adding channel frequency overrides. 
  For more information, see International Analog TV Tuning in the SDK. 

- DirectShow Editing Services (DES) now supports plug-in video resizing filters. 
  For more information, see Providing a Custom Video Resizer in the SDK. 
  
- The DVD Graph Builder enables applications to use the VMR-9 through the 
  IDvdGraphBuilder::RenderDvdVideoVolume method.  The DVD Navigator now supports 
  playback of audio during fast forward; users can now watch a movie at speeds 
  higher than 1x without raising the pitch of the audio track, if the decoder 
  supports this feature.  The DVD navigator now provides faster DVD menu navigation.

- Video renderer no longer displays frame counters on debug builds.


DirectShow SDK updates
----------------------

- Significant enhancements to the GraphEdit utility, including
  Windows Media Certification (dekeying of non-DRM WM graphs), 
  Filter Favorites menu, improved connect/disconnect from remote graphs, 
  save/restore options, frame stepping, and color coding of connected filters.
  XGR files are no longer supported by GraphEdit.

- Sample source code has been improved to enhance security, reliability,
  and readability.  Support for Visual Studio.NET has also been added 
  (VC.NET projects, solutions, etc.)

- Managed code for audio and video file playback.
  The Microsoft.DirectX.AudioVideoPlayback managed code namespace provides 
  playback and simple control of audio and video media. For more information, 
  refer to the DirectX documentation for the managed DirectX components.  

- Numerous bug fixes and refinements for SDK samples and tools

- New Unicode Debug/Release build targets for Visual C++ 6.0 and 
  Visual Studio.NET projects

- New and revised content in the SDK documentation

- New ProfileEnum tool (in Bin\DXUtils) lists the Windows Media system profiles
  that are available for use on your system.  This tool is helpful if you
  are creating Windows Media files (ASF,WMA,WMV) through DirectShow interfaces.

- The AMCap sample application now supports MPEG-2 program stream input, 
  for example from analog TV Tuners that stream MPEG-2 content. A third-party 
  DirectShow-compatible MPEG-2 decoder is still required to decode the streams. 

- Because using RenderFile() with monikers is no longer supported, the 
  PlayCapMoniker sample demonstrates an alternate method (AddSourceFilter()).


New DirectShow samples
----------------------

- Audiobox: Audio-only media player, similar to the Jukebox sample.
  It supports Favorites and playback of Windows Media Audio and MP3 files.

- CaptureTex: Blends Texture3D and PlayCap to display incoming live
  video on a rotating Direct3D surface

- CaptureTex9: Extends the CaptureTex sample to render live incoming video 
  onto a Direct3D9 surface (a waving flag).

- CompressView: Demonstrates how to recompress an audio or video file 
  using a different compression type.

- DSNetwork Filters: Implements an IP source filter and an IP rendering filter.
  This filter set allows you to transmit/receive MPEG-2 data on a network.

- GrabBitmaps: Shows how to grab bitmaps from a video stream. 

- Metronome Filter: Sample filter that shows how to implement a reference clock. 

- PlayDVD: A simple windowed DVD player based on the PlayWnd sample.

- PlayWndASF: Added limited DRM support to the previous PlayWndASF sample.

- PSIParser Filter: Shows how to retrieve program information from an
  MPEG-2 transport stream. 

- PushSource Filters: Set of three source filters that output a single
  bitmap, a series of bitmaps, or a live desktop capture video stream.

- RenderLog: Creates a text log of DirectShow's progress while rendering a
  media file. If you receive an error when you call IGraphBuilder::RenderFile, 
  you can use this tool to create and view the log. 

- RGBFilters: Set of several sample source and transform filters useful for testing. 

- Texture3D9: Extends the Texture3D sample to play video on a DirectX 9 
  texture surface, utilizing Direct3D9 features for more efficient rendering.

- TransViewer: Enables you to preview all of the DirectShow Editing Services 
  transitions installed on your system. 


New VMR-7 samples
-----------------

- Blender: Demonstrates how to mix, blend, and manipulate two video streams. 

- MonitorInfo: Displays simple information about the available monitors
  (using a VMR interface).

- Pip: Demonstrates how to create picture-in-picture effects using the VMR. 

- Text: Displays alpha-blended text over running video. 

- Ticker: Extends the Text sample to draw horizontally scrolling text
  across the bottom of the video.  You can scroll text as a static bitmap
  or as a dynamically generated bitmap created from user input.

- VMRMulti: Plays multiple video files over an animated Direct3D background. 
  Each video stream is individually seekable.

- VMRXclBasic: Shows how to play video in full-screen exclusive mode.

- Watermark: Places an alpha-blended bitmap over the video and adds effects
  (alpha strobe, scrolling, bitmap animation).

- Windowless: Demonstrates basic playback using the VMR's Windowless mode. 


New VMR-9 samples
-----------------

- VMR-9 versions of eight VMR-7 samples:
    - Blender9, MonitorInfo9, Pip9, Text9, Ticker9, 
      VMRPlayer9, Watermark9, and Windowless9
  
- VMR9Allocator: Renders video onto a rotating Direct3D surface

- BitmapMix: Uses the VMR9 to render video onto a Direct3D9 surface while
  blending a bitmap that can be moved via mouse input

- MultiVMR9: Demonstrates using a custom VMR9 Allocator-Presenter in a
  multi-graph environment.  There are three folders in this project, including
  a support DLL, a MultiPlayer sample, and a 3D GamePlayer sample that integrates
  video playback into a Direct3D game environment.
  

Removed Samples
---------------

- JukeboxASF has been removed.  Its Windows Media support has been merged 
  into the Jukebox sample. 

Sample media files
------------------

The video codec used in highway.avi and ruby.avi has been changed to Cinepak.
This was done to enable playback on clean installations of Windows XP SP1,
which no longer ships the Indeo codecs.


=============================================================================
What's New in DirectShow for DirectX 8.1
=============================================================================
September, 2001
=============================================================================

There have been considerable improvements made to the DirectShow content
for the DirectX 8.1 SDK.  Below is a brief summary of the updates.


Improvements to existing samples
--------------------------------
There have been many enhancements and refinements to the existing
DirectX 8.0 samples for this release, including:

- New features and functionality
- Numerous bug fixes, including Windows XP support issues
- UNICODE and IA64 support
- ASF-enabled versions of the PlayWnd and Jukebox samples
- Clean compilation with Warning Level 4
- Improved video window repainting for Jukebox-style MFC applications
- Updated resource files and version information blocks
- Digital Video sample (Capture\DVApp) was rewritten to take 
  advantage of the ICaptureGraphBuilder2 interface to build its graphs.


New DirectShow samples
----------------------
- Audio Capture         (Capture\AudioCap)
- DMO-enabled Player    (Players\PlayDMO)
- DMO Enumerator        (Misc\DMOEnum)
- Filter Mapper         (Misc\Mapper)
- Grabber Sample Filter (Filters\Grabber) (modified from DirectX 8 SampleGrabber)
- JukeboxASF            (Players\JukeboxASF)
- PlayCap with Moniker  (Capture\PlayCapMoniker)
- PlayWndASF            (Players\PlayWndASF)
- Still Image Viewer    (Players\StillView)
- Utility source code and routines in the DirectShow\Common directory


New DirectShow samples for Windows XP
-------------------------------------
Windows XP provides new functionality that is not present in downlevel
operating systems (Windows 9x, Windows 2000).  The VMR and VideoControl
directories provide samples to demonstrate using the new Video Mixing
Renderer and the new Microsoft Video Control (for use with the Windows
Driver Model and Broadcast Driver Architecture).

The new samples include:

- Video Control - C++, Visual Basic, and HTML samples of rendering
  ATSC, DVB, and Analog television in a Windows application.  The
  new Video Control encapsulates much of the new functionality and
  aids developers in creating television-enabled applications.

- Video Mixing Renderer (VMR):
  - Cube
  - Renderless
  - Text Player
  - VMR Mix
  - VMR Player
  - VMR Exclusive Mode (VMRXcl)

See the VideoControl and VMR directories for more detailed information 
about these new samples.


Updated Documentation
---------------------
The DirectShow documentation has been significantly enhanced for 
DirectX 8.1.  It adds information for the new features available in
Windows XP and expands on previously presented material for the
Microsoft TV Technologies.


Modified SampleGrabber filter source code
-----------------------------------------
There have been several requests for Microsoft to publish the source
code for the popular SampleGrabber filter.  To that end, we now provide
a modified (simpler) version of the sample grabber filter, which uses 
a new GUID and new CLSID to prevent collisions with the original 
DirectX 8.0 filter.  You can review and modify the source code for this 
filter and use it in your own applications.  See the Filters\Grabber 
directory for more information.


Windows XP support in header files
----------------------------------
DirectX 8.1 provides support for the following Windows platforms:
    - Windows 98, Windows 98 Second Edition, Windows Millennium Edition
    - Windows 2000
    - Windows XP

To enable Windows XP features and to utilize the new portions of the
affected headers, set the Windows version to 0x501 (the Windows XP
version) in your Visual C++ project files.


Runtime improvements
--------------------
The DirectX 8.1 binaries and redist files benefit from various bug fixes
made since the DirectX 8.0 release, including a large subset of the 
modifications that were made for Windows XP.


Revised GraphEdit application
-----------------------------
The GraphEdit utility received several improvements, particularly 
with respect to its user interface, menus, and toolbar.  Additionally,

- Graph resizing code (View->xxx %) handles all sizes correctly, and 
  you can resize your graphs using the menu, keyboard +/- keys, and 
  Ctrl+MouseWheel.  

- You can optionally disable the seek bar (and its timed updates), which 
  has been known to cause difficulty when debugging filters with GraphEdit.  

- To preserve screen real estate, source and file writer filters displayed 
  in GraphEdit will now only display their simple root filenames as the 
  filter name, instead of displaying the fully qualified path name.  
  For example, a file source for the file 
  "C:\DXSDK\samples\Media\lake.mpg" would display as "lake.mpg".

