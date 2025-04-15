//-----------------------------------------------------------------------------
// Name: MotionBlur Direct3D Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========
   The MotionBlur sample demonstrates a vertex shader that creates a motion
   blur effect by stretching some vertices along the direction of motion and 
   fading their transparency.


Path
====
   Source:     DXSDK\Samples\C++\Direct3D\MotionBlur
   Executable: DXSDK\Samples\C++\Direct3D\Bin


User's Guide
============
   The following keys are implemented. The dropdown menus can be used for the
   same controls.
      <Up Arrow>  Increase the motion blur trail length
      <Down Arrow> Decrease the motion blur trail length
      <Enter>     Starts and stops the scene
      <Space>     Advances the scene by a small increment
      <F1>        Shows help or available commands.
      <F2>        Prompts user to select a new rendering device or display mode
      <Alt+Enter> Toggles between fullscreen and windowed modes
      <Esc>       Exits the app.

   The mouse is also used in this sample to rotate the teapot


Programming Notes
=================
   The sample shows two spheres, both represented by the same D3DXMESH object.
   The spheres move in an ellipse, and each sphere remembers the matrix for its
   current position and last-computed position.  Each sphere is rendered once
   using the "normal" (ordinary) shader, and once using the motion-blur shader.

   The motion-blur shader starts by transforming the vertex position (v0) 
   through the last-frame world matrix (c0) and the current-frame world matrix 
   (c4), and stores the results in r0 and r1.  The normal vector (v1) is also 
   transformed through the current-frame world matrix (c4) and the result is
   stored in r2.

   r3 gets the motion delta vector from r0 to r1, and is normalized.  Then 
   r4.x gets set to the dot product of the vertex normal and the motion delta 
   vector.  So the closer the vertex normal is to the motion delta vector, the 
   larger r4.x will be for that vertex.  If r4.x is less than zero, the vertex
   normal points away from the motion delta vector.  We will only blur these 
   vertices.

   In the next section, r4.y gets set to 1 if r4.x is less than zero (c20.y), or
   0 if r4.x is zero or positive.  So the motion blur will only be applied to 
   vertices whose normal faces away from the direction of motion.  If r4.y is
   zero, r1 is unchanged.  If r4.y is 1, r1 will get -r3 (the motion direction)
   added to it.

   Next r1 is transformed through the rotation and projection matrices, and the
   result goes into oPos.

   Finally, the diffuse color is computed and stored in oD0, with oD0's alpha
   being set to 0 if r4.x (the dot product of the vertex normal and the 
   direction of motion) is negative, or 1 otherwise.  This makes the blur fade 
   out as it gets further from the real object.
   
   This sample makes use of common DirectX code (consisting of helper functions,
   etc.) that is shared with other samples on the DirectX SDK. All common
   headers and source code can be found in the following directory:
     DXSDK\Samples\C++\Common

