//-----------------------------------------------------------------------------
// 
// Sample Name: CustomFormat Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------


Description
===========
  The CustomFormat sample illustrates the use of a custom data format.

Path
====
  Source:     DXSDK\samples\C++\DirectInput\CustomFormat
  Executable: DXSDK\samples\C++\DirectInput\Bin

User's Guide
============
  Move the system mouse around the screen and click the mouse buttons to alter
  the display data. Note that for mice with 4 or more buttons, not all of the 
  buttons will be used by this sample.

Programming Notes
=================
  The comments walk through creating, initializing, and retriving data with a 
  custom data format. The best real world application of a custom data format 
  is adding support for a non-standard input device. By enumerating the device
  objects you can determine exactly what data is available. The data format
  you create dictates how the data you're interested in will be stored.

  For compatibility, this sample creates a new format to store mouse data. In
  reality, you'd almost certainly wish to use one of the provided c_dfDIMouse
  types, but the steps taken to create the custom format will be the same for
  any hardware device.
