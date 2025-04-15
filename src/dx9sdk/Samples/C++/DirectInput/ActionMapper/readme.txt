//-----------------------------------------------------------------------------
// 
// Sample Name: ActionMapper Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------


Description
===========
  The ActionMapper sample is built upon the action mapping framework provided
  with the SDK. The program illustrates how this framework can simplify the
  bookkeepping required for an action mapped application.

Path
====
  Source:     DXSDK\Samples\C++\DirectInput\ActionMapper
  Executable: DXSDK\Samples\C++\DirectInput\Bin

User's Guide
============
  The interface displays information about a theoretical game state; the 
  attached input devices can be used to trigger game actions, which are then
  displayed as changes in game state. To view or change the way input devices
  are mapped to game actions, click the "Configure Input" button. 


Programming Notes
=================
  The sample is built around the CInputDeviceManager class, which defines a 
  framework for the DirectInput action mapping facilites. Feel free to use this
  class in your own applications for simplifying development. For an 
  introduction to action mapping which does not rely on the framework class, 
  refer to the ActionBasic sample included with this SDK.

  Most of this sample's functionality is encapsulated in the CMyApplication 
  class. This class is responsible for initializing DirectInput, enumerating
  input devices, handling user input, and rendering output. These steps are
  discussed in depth by the DirectInput documentation.

  