//-----------------------------------------------------------------------------
// 
// Sample Name: SoundFx Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//-----------------------------------------------------------------------------


Description
===========
  The SoundFx sample shows how to use standard effects with DirectSound and
  how to manipulate FX parameters.  It is similar to the AudioFX sample 
  but does not use an audiopath.

Path
====
  Source:     DXSDK\Samples\C++\DirectSound\SoundFx
  Executable: DXSDK\Samples\C++\DirectSound\Bin


User's Guide
============
  Load a sound file. Enable one or more FXs by checking the checkboxes on the 
  left, under the column "Enable".  Click Play to hear the effects applied.
  Adjust parameters for any FX by using the frame on the right.
  Choose which effect to adjust by choosing an option under the "Adjust"
  column on the left.  If you are adjusting parametesr for an active
  FX while sound is playing, you will hearing the difference immediately.

Programming Notes
=================
  For a simpler example of how to setup a DirectSound buffer with a 
  single fixed DirectSound effect, see the AmplitudeModulate sample. 
  


  