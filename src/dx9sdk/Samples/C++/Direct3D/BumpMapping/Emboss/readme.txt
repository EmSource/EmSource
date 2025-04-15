//-----------------------------------------------------------------------------
// Name: Emboss Direct3D Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========
   The Emboss sample demonstrates an alternative approach to standard
   Direct3D bump mapping. Embossing is done by subtracting the height map
   from itself and having texture coordinates that are slightly changed.

   Not all cards support Direct3D bump mapping. Refer to the Microsoft DirectX® 
   software development kit (SDK) documentation for more information.


Path
====
   Source:     DXSDK\Samples\C++\Direct3D\BumpMapping\Emboss
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
      <CTRL+E>    Turns emboss effect on/off. 


Programming Notes
=================
   This sample makes use of common DirectX code (consisting of helper functions,
   etc.) that is shared with other samples on the DirectX SDK. All common
   headers and source code can be found in the following directory:
     DXSDK\Samples\C++\Common
