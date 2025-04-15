//-----------------------------------------------------------------------------
// 
// Sample Name: ActionBasic Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------


Description
===========
  The ActionBasic sample is intended to be an introduction to action mapping, 
  and illustrates a step by step approach to creating an action mapped 
  application.

Path
====
  Source:     DXSDK\Samples\C++\DirectInput\ActionBasic
  Executable: DXSDK\Samples\C++\DirectInput\Bin

User's Guide
============
  The sample features a chart displaying the list of detected devices plotted
  against a list of sample game actions. During initialization, the sample 
  attempts to map the actions to device objects. Triggered button actions will 
  be displayed as a highlighted cell on the same row as the generating device; 
  triggered axis actions also feature an arrow to indicate the axis position. 
  Actions which were not successfully mapped to an object on the device are 
  given a crosshatch-filled cell on the chart.

  To view the current action mappings for all the detected devices, click the
  "View Configuration" button, which will access the default configuration UI
  managed by DirectInput.


Programming Notes
=================
  The ActionBasic sample is intended to be an introduction to the action 
  mapping features of DirectInput. The source code is thoroughly commented and 
  labeled according to the primary steps to be followed when writing an action 
  mapped application. If you're already familiar with the fundamentals of 
  action mapping, you may want to refer to the ActionMapper sample, which shows 
  how the framework supplied with this SDK can simplify development.

  