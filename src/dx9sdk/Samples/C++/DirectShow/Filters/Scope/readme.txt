//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Scope Filter (Oscilloscope)
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

Description
============

Renderer filter that displays sound data as waveforms.

Path
====

Source: (SDK root)\Samples\C++\DirectShow\Filters\Scope

User's Guide
============

To use this filter, open GraphEdit and render an audio file (or a video file 
with an audio stream).  Disconnect the audio renderer temporarily and insert 
the Infinite-Pin Tee (InfTee Filter Sample) sample filter.  Reconnect the audio 
renderer.  Then connect the Infinite-Pin Tee filter's second output pin to 
the Scope filter.  Now run the graph.

The Scope window is implemented as a dialog box, not as an actual window. 
Developers creating control panels to alter filter parameters in real-time 
might want to use a technique like this instead of property pages.

The Scope filter demonstrates setting up a separate thread to process data. 
In this case, the data is just copied to a separate buffer on the 
IMemInputPin::Receive method, and then it is drawn on the Scope window 
on the separate thread.

The Scope filter also enables you to monitor audio output to determine 
if you are clipping, so that you can adjust the gain.

This filter appears in GraphEdit as "Oscilloscope".
