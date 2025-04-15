//-----------------------------------------------------------------------------
// Name: LightingVS Direct3D Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========
   The LightingVS sample is an extension of the Lighting sample that adds
   vertex shader implementations of lighting.  It lets you add multiple lights
   and compare the output and performance between the vertex shader lights
   and the fixed-function pipeline lights.

   
Path
====
   Source:     DXSDK\Samples\C++\Direct3D\LightingVS
   Executable: DXSDK\Samples\C++\Direct3D\Bin


User's Guide
============
   The following keys are implemented. The dropdown menus can be used for the
   same controls.
      <Enter>     Starts and stops the scene
      <Space>     Advances the scene by a small increment
      <F2>        Prompts user to select a new rendering device or display mode
      <Alt+Enter> Toggles between fullscreen and windowed modes
      <Esc>       Exits the app.
	

Programming Notes
=================
   This sample's vertex shaders are contained in an effect file called 
   LightingVS.fx that is in the media directory.
   
   This sample makes use of common DirectX code (consisting of helper functions,
   etc.) that is shared with other samples on the DirectX SDK. All common
   headers and source code can be found in the following directory:
      DXSDK\Samples\C++\Common

