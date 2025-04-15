//-----------------------------------------------------------------------------
// 
// Sample Name: DeviceView Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------


Description
===========
  This sample shows how the DIDevImage framework provided with this SDK can be
  used to create a custom device configuration interface. 
  
  It's not really necessary to create a device configuration UI, though. 
  DirectInput provided a highly customizable UI which is called by the
  IDirectInput::ConfigureDevices method. The source code for the default UI
  is also provided with this SDK (samples\cpp\DirectInput\diconfig). That UI, 
  as well as the DIDevImage framework, call the 
  IDirectInputDevice::GetImageInfo method to retrieve the device images. 
  
  The value of the DIDevImage framework is that it takes care of the
  bookkeeping involved with bitmaps, and handles some nice extras like
  tooltips and image scaling. The source code for the DIDevImage framework
  (samples\cpp\common\src\didevimg.cpp) is also freely modifyible should you
  need some extra functionality. In any case, if for some reason you need to 
  create a device configuration utility for your project, you have
  plenty of options and lots of source code to help you.
  


Path
====
  Source:     DXSDK\Samples\C++\DirectInput\DeviceView
  Executable: DXSDK\Samples\C++\DirectInput\Bin


User's Guide
============
  When you run the application, it will display a tab for each DirectInput device
  on your system.  For each device, you can look through multiple views (if existing)
  by entering a value for the current view (or using the attached spin control).  
 
  To select a device object, click the mouse over the object's callout string, or
  activate the desired device object. This will highlight the current callout, and
  display the object's image overlay (if available). 
  
  Hiding callouts for unmapped device objects makes the current mapping more visible.
  To hide unmapped objects, check the "Hide Unmapped" checkbox.

Programming Notes
=================
  This sample is built heavily upon the DIDevImage framework, which handles the
  device image loading, scaling, and rendering. The steps needed to use the
  framework are simple:

  1. Instantiate an object of the CDIDevImage class.
  2. Initialize the object by passing a pointer to an IDirectInputDevice object 
     to the Init() method.
  3. Set the desired callout strings through a series of calls to the 
     SetCalloutText() method.
  4. Render the image to your client application by passing a device context to the
     RenderToDC() method, or a Direct3D surface to the Render() method.
  5. Highlight, tooltip, or hide callout strings by passing the appropriate flags
     to the SetCalloutState() method.

  The framework has some optimizations for quick renderings, but your application
  should not call the Render() method for each frame. Instead, try to call the
  framework's Render() method only when the device image changes due to user input.

  Read the inline comments included with the framework source code for information
  on using some of the more advanced features, such as transparent backgrounds for
  D3D surfaces.