//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Gargle Filter
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
============

Audio effect filter.

The Gargle filter modulates the waveform passing through it 
by multiplying the waveform by another waveform that is 
mathematically generated within the filter. The modulating 
waveform is, by default, a triangular wave. The property sheet 
also offers the alternative of a square wave. You can set the 
frequency of the modulating wave through the filter's property 
sheet. At low modulation frequencies, the effect sounds like 
a tremolo. At higher modulation frequencies, it sounds like a 
distortion, adding extra frequencies above and below the original 
unmodulated sound.


Path
=====

Source: <SDK root>\Samples\C++\DirectShow\Filters\Gargle
