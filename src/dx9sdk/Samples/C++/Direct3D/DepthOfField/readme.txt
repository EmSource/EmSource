//-----------------------------------------------------------------------------
// Name: Depth Of Field Direct3D Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========
   This sample shows a technique for creating a depth-of-field effect with
   Direct3D, in which objects are only in focus at a given distance from the
   camera, and are out of focus at other distances.
   
Path
====
   Source:     DXSDK\Samples\C++\Direct3D\DepthOfField
   Executable: DXSDK\Samples\C++\Direct3D\Bin


User's Guide
============
   The following keys are implemented. The dropdown menus can be used for the
   same controls.
      <Enter>     Starts and stops the scene
      <Space>     Advances the scene by a small increment
      <F1>        Shows help or available commands.
      <F2>        Prompts user to select a new rendering device or display mode
      <Alt+Enter> Toggles between fullscreen and windowed modes
      <Esc>       Exits the app.
	

Programming Notes
=================
   
   This sample makes use of common DirectX code (consisting of helper functions,
   etc.) that is shared with other samples on the DirectX SDK. All common
   headers and source code can be found in the following directory:
      DXSDK\Samples\C++\Common

