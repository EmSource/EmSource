//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Ball Filter
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

Description
============

Video source filter that produces an image of a bouncing ball. 

This sample illustrates format negotiation and the use of the 
source filter base classes CSource and CSourceStream. 


Path
=====
Source: (SDK root)\Samples\C++\DirectShow\Filters\Ball


User's Guide
============

The code in Fball.h and Fball.cpp manages the filter interfaces. 
Those two files contain approximately the minimum code required 
for a source filter. The Ball.h and Ball.cpp files contain the 
code that bounces the ball.

This filter has a single output pin, which provides a video stream 
that shows a ball bouncing around in the frame. The Ball filter 
also accepts quality management requests from the downstream filter, 
which illustrates a simple quality management strategy. This filter 
implements the IQualityControl interface for that purpose.

The color of the ball corresponds to the current display bit depth:

    8 bit  - red balls
    16 bit - blue
    24 bit - green
    32 bit - yellow

