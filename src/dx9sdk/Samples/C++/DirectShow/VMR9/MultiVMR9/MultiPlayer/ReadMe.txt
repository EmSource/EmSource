//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- MultiVMR9 MultiPlayer sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


This MFC-based sample implements the default functionality of MultiVMR9.dll, 
so make sure that MultiVMR9.dll is built and registered with regsvr32.exe. 

MultiPlayer looks much like the property page of the VMR9 in the mixing mode; 
the only evident difference is that this application supports several filter graphs 
at once.  The application starts with a configuration dialog.


1. Controls related to the application:

- To add a new source, hit '+' button and select some media file. 
  (Note: this application has not been tested on MPEG2 streams.)
  
- Use 'FPS' slider to set desired frames per second rate. 
  Default value is 30; possible range is 5-100 
  
- To exit application, hit 'Close' 

- To change the color of the background, hit 'brush' button and select the color 
 

2. Controls related to the selected item of the combo box:

To delete the source, hit '-'

- Use sliders to change x,y positions and vertical and horizontal sizes 

- Use slider to change z-order of the source (0 is foremost) 

- Use slider to change alpha-level of the source 

- Use 'Timeline' slider and buttons 'Play' and 'Pause' to control state 
  and seek the stream. 
  
- Use 'rulers' button to restore aspect ratio of selected source 
 

NOTE: This application does NOT support multiple monitors.  Your desktop display
must be set to 32 bit display depth.

NOTE: This sample requires DirectX 9 (or greater) functionality 
and will exit on other systems.

NOTE: You must build MultiVMR9.dll and register it with 'regsvr32' before
you can run this application.
