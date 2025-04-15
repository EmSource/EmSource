//-----------------------------------------------------------------------------
// 
// Sample Name: Mouse Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------


Description
===========
  The Mouse sample obtains and displays mouse data.

Path
====
  Source:     DXSDK\Samples\C++\DirectInput\Mouse
  Executable: DXSDK\Samples\C++\DirectInput\Bin

User's Guide
============
  Select the desired cooperative level and data style and click "Create Device" 
  to create and acquire a DirectInput device for the system mouse. Once the 
  device is acquired, any mouse movement or button clicks will received by the 
  application and displayed on the data line. Click "Release Device" to release 
  the device in order to make changes to the options.

Programming Notes
=================
  The application creates a DirectInputDevice using any of the allowed 
  combinations of cooperative level and data style. Once the device is 
  acquired, the device data is retrieved through one of two input methods
  corresponding to the data style. 

  Regardless of device options, when the user clicks "Create Device" the
  program first creates an IDirectInput8 object. This DirectInput object is
  used to create to create an IDirectInputDevice8 object, which corresponds
  to the physical device. The DirectInputDevice object is used to set the data
  format, set the cooperative level, and acquire the device. For buffered
  data input there is an extra step to set the desired data buffer size. After 
  the device is acquired, the program sets a timer to signal the input methods.

  

