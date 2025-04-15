//-----------------------------------------------------------------------------
// 
// Sample Name: DirectShow Sample -- Synth Filter
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------


Description
===========
Source filter that generates audio waveforms.

This filter illustrates dynamic graph building. It can 
switch between uncompressed PCM audio and compressed MS_ADPCM 
(Microsoft Adaptive Delta Pulse Code Modulation) format.

This filter appears in GraphEdit as "Audio Synthesizer Filter."

For more information about dynamic graph building, see 
Dynamic Graph Building.


Path
=====
Source: (SDK root)\Samples\C++\DirectShow\Filters\Synth


User's Guide
============
The Synth filter enables the user to set the waveform, frequency, 
number of channels, and other properties through the property page. 
To set either the upper or lower endpoint of the swept frequency range, 
hold down SHIFT while adjusting the frequency slider. The filter also 
supports a custom interface, ISynth2, for setting these properties.

To demonstrate the dynamic graph building feature, do the following: 

1) Build the filter and register it with the Regsvr32 utility. 
2) Launch GraphEdit. 
3) Insert the Audio Synthesizer filter. It appears in the 
   DirectShow Filters category. 
4) Render the filter's output pin. 
5) Click the Play button. 
6) Open the filter's property page. 
7) In the Output Format area, select PCM or Microsoft ADPCM.

For more detailed information about this sample, see the DirectShow
samples folder in the DirectX SDK documentation.

docu