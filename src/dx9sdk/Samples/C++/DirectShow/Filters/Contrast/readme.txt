//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Contrast Filter
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========

Video transform filter that implements a contrast effect. 
This sample illustrates how to define and implement a simple 
custom interface. It also demonstrates how to use the 
CTransformFilter class to implement a simple effect filter.


Path
====
Source: <SDK root>\Samples\C++\DirectShow\Filters\Contrast


User's Guide
============
The Contrast filter is a simple transform filter that adjusts 
the contrast of the video stream that is passed through it. 
It provides a custom interface for adjusting the contrast. 
The Contrast filter also uses the CBasePropertyPage class to 
provide a property page for applications that do not provide 
a user interface.

The Contrast filter adjusts the contrast by using a trick with 
palettes. The color palette of an image effectively determines 
how the image is interpreted. By changing the palette, the filter 
can change the contrast without changing the image pixels themselves.
