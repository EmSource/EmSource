//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- MultiVMR9 - DLLHelper
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


This helper library demonstrates how to implement a user-provided (customized) 
allocator-presenter for the Video Mixing Renderer 9 in a multigraph environment. 

It seemed logical to extract several abstraction layers that could be overriden 
by client applications:

- Wizard: an object that implements actual allocation-presenting and contains 
  references to all connected filter graphs. The wizard is responsible for 
  interaction with client application as well as connecting and disconnecting graphs. 
  Object is implemented by IMultiVMR9Wizard interface. 

- Rendering Engine: an object that contains all Direct3D data and performs 
  actual rendering asynchronously from calls to IVMRImagePresenter9::PresentImage. 
  Object is implemented by IMultiVMR9RenderEngine interface.

- Mixer Control: an object that performs scene composition and defines geometry 
  of Direct3D objects. By default, this object acts as IVMRMixerControl9 in a 
  single graph (see sample MultiPlayer in the MultiVMR9\MultiPlayer folder), 
  but can be overriden to perform any sort of 3D transformation (as in the sample 
  GamePlayer in the MultiVMR9\GamePlayer folder). Object is implemented 
  by IMultiVMR9MixerControl interface.

- User Interface Layer: an object that is responsible for interaction with the user 
  in the video playback window. User Interface Layer is always drawn over the scene 
  rendered by mixer control. The message processing function of the video window 
  sends all of the appropriate messages to this object. Object is implemented by 
  IMultiVMR9UILayer interface. By default, MultiVMR9.dll does not use this object, 
  so if client application needs user interaction, it must provide an
  IMultiVMR9UILayer object.


NOTE: This sample requires DirectX 9 (or greater) functionality 
and will exit on other systems.

NOTE: You must build and register this DLL with 'regsvr32' before you can run
the associated MultiPlayer and GamePlayer samples.

