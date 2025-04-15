//-----------------------------------------------------------------------------
// 
// Sample Name: DrumPad Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//-----------------------------------------------------------------------------



Description
===========
DrumPad Sample transforms every input device on your computer to a 
simple audio drum machine (using Action Mapping and DirectX Audio).  
(joysticks, joypads, keyboard, mouse).  You can load different 
sound files to be played for each "drum".


Path
====
  Source:     DXSDK\Samples\C++\DirectInput\DrumPad
  Executable: DXSDK\Samples\C++\DirectInput\Bin

User's Guide
============
DrumPad has 8 "sound" slots, which are action mapped to controls on 
each input device on your system.  It attempts to load default sound
files from the ..\..\media directory - but you can load any sound 
file into each of the slots.

- To play the sounds, hit buttons on your joystick/joypad/keyboard/mouse.
  You should see the corresponding green box light up on the right.

- any number of devices can used simultaneously.

- To load a sound into one of the slots ("Bass Drum" "Snare Drum", 
  "User 1" etc), click on the corresponding button on the left,
  this will bring up a OpenFile Dialog box.

- To see which "sound" slot is mapped to which button, click "View Device 
  Mappings"



Programming Notes
=================
DrumPad uses action mapping to have DirectInput map each sound action
to a control.  The sound actions include

  eB_BASS_DRUM
  eB_SNARE_DRUM
  eB_HIHAT_OPEN
  eB_HIHAT_CLOSE
  eB_CRASH
  eB_USER1
  eB_USER2
  eB_USER3

each action is mapped to DirectInput Action Mapping Constants, which
include genre-specific joystick actions (the sample uses an arbitrary 
genre), and keyboard and mouse buttons.  You observe how everything
is mapped by seeing the Device Mappings during runtime.

The audio is done by encapsulating an array of DirectSoundBuffers or
DirectMusicSegments.  The game loop polls the devices and process
the input (by calling the DrumPad class and playing a sound).



