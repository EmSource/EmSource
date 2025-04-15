//-----------------------------------------------------------------------------
// 
// Sample Name: MultiMapper Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------


Description
===========
  The MultiMapper application demonstrates the DirectInput Mapper in a 
  windowed application.

Path
====
  Source:     DXSDK\Samples\C++\DirectInput\MultiMapper
  Executable: DXSDK\Samples\C++\DirectInput\Bin

User's Guide
============
  The application begins by asking for the number of users who will interact 
  with the application. You can select 1 through 4 players. The output within
  the application window simply shows sample game actions as they apply to
  the various input devices attached to the system.

  The application automatically assigns a name to each player (in the form of
  "Player n," where n is a number between 1 and 4, inclusive. 

  Press the D key to invoke the default user interface, which users can use to 
  reconfigure their devices, reassign devices to other players, and view
  the current mapping of actions to device controls.

  Press the Esc key to close the application.

Programming Notes
=================
  This application assumes the general structure of a typical DirectX game. It 
  is intended to showcase best-practice coding conventions for the latest 
  DirectInput features, and to that end does not attempt to demonstrate any 
  graphics or sound techniques that you would expect from a full-fledged game 
  sample or retail DirectX application. 

  The MultiMapper application demonstrates the following major aspects of the 
  DirectInput Mapper technology. 
    Declaring an initial action map for a game.
    Device enumeration through the IDirectInput8::EnumDevicesBySemantics method.
    Building and setting action maps for devices. 
    Using a simpler input loop by way of the DirectInput Mapper.
    Managing simultaneous inputs from multiple devices and players.
    Handling dynamic device ownership changes.
    Recovering user settings on subsequent invocations of the application.

  Most of these tasks are performed by the CInputDeviceManager helper class used 
  by the application, though the input loop, the application display code, and 
  general initialization are done outside the context of the helper class.
