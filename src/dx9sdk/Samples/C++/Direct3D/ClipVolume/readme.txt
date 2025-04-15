//-----------------------------------------------------------------------------
// Name: ClipVolume Direct3D Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========
   The ClipVolume sample demonstrates a technique for using shaders to 
   "subtract" a sphere from an arbitrary model when rendering.  This technique 
   could be useful in visualization applications to see inside complex objects.  
   The sample also shows how to perform two-sided lighting.


Path
====
   Source:     DXSDK\Samples\C++\Direct3D\ClipVolume
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

   The mouse is also used in this sample to rotate the teapot


Programming Notes
=================
   The sample creates two D3DXMESH objects, one for the teapot and one for 
   the sphere.  A vertex shader and pixel shader are used when rendering the
   teapot, and a different vertex shader is used to render the sphere.  

   The sphere's vertex shader doesn't do anything unusual -- it just performs 
   the standard world-view-projection transformation on the vertex position, 
   and sets the diffuse color to be dark blue with 50% alpha.  Note that the
   sphere is drawn for illustration purposes only.  The rendering of the 
   sphere is not necessary to get the clipping effect shown in the sample.

   The teapot's vertex shader does three tasks:

   -  First, it does the standard transformation of the vertex positions through 
      the world-view-projection matrices.  

   -  It then computes each vertex's distance from the sphere center (stored in 
      the c12 register), compares that distance from the sphere's radius (stored 
      in c12.w), and stores the difference in oT0.  The same float value goes 
      into all four (xyzw) parts of oT0.  We write all four parts since texkill 
      (see the pixel shader) reads all four parts, so we don't want any 
      uninitialized fields in oT0.  Note that oT0's data will be negative inside 
      the sphere radius, and positive outside the radius.

   -  The last thing the vertex shader does is to perform two-sided diffuse 
      lighting on the teapot.  It transforms the vertex normal through the
      rotation matrix, and sets r3.x to 1 if the vertex is front-facing, or
      0 if the vertex is back-facing.  It then uses a mad instruction to set
      r5 to c92 + (r3.x * c91), so it will be red  (c92) if r3.x is 0, or 
      green (c91 + c92) if r3.x is 1.  Finally, r5 is multiplied by the 
      light intensity at that vertex, which is the absolute value of r3.z.

   The teapot's pixel shader simply uses the texkill instruction to not
   render any pixel if any texture coordinate is less than zero.  We have
   set up the x texture coordinate to be negative for all vertices/pixels
   inside the sphere, so this prevents any pixels inside the sphere from being
   rendered.
   
   This sample makes use of common DirectX code (consisting of helper functions,
   etc.) that is shared with other samples on the DirectX SDK. All common
   headers and source code can be found in the following directory:
      DXSDK\Samples\C++\Common

