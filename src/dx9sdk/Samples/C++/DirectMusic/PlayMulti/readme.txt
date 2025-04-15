//-----------------------------------------------------------------------------
// 
// Sample Name: PlayMulti Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// GM/GS® Sound Set Copyright ©1996, Roland Corporation U.S.
// 
//-----------------------------------------------------------------------------



Description
===========
  The PlayMulti sample demonstrates how to play multiple secondary segments
  along side a primary segment.
  
Path
====
  Source:     DXSDK\Samples\C++\DirectMusic\PlayMulti
  Executable: DXSDK\Samples\C++\DirectMusic\Bin

User's Guide
============
  Primary segments contain underlying form, tempo and (potentially) harmonic 
  information.  Normally secondary segments are layered over the primary 
  segment and are synchronized based on the primary segment (already playing). 
  Controlling secondary segments are authored so that they have tracks that will 
  replace or override certain primary tracks.

  To begin, load either new DirectMusic segments or use the segments loaded by default.  
  Click Play on the primary segment, and then for the secondary segments select the 
  play boundary of the secondary segment and if you want the secondary segment 
  to be controlling or looped.  Click Play to play the secondary segment.  You may 
  play or stop any of the segments at any time and in any order.  
  Click Stop All to stop all of the sound.

