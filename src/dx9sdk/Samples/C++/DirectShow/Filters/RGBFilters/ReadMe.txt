//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- RGBFilters
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

Description
===========
This DLL (RGBFilters.dll) is a self-registering DLL that
provides several useful filters for testing purposes.
The filters provided are listed below:

AlphaRenderer - a rendering filter that will perform an
alpha blend onto a checkerboard background, which is based 
on the incoming video alpha. This uses the new media subtype 
MEDIASUBTYPE_ARGB32.

AlphaSource - a source filter that outputs the new media subtype 
MEDIASUBTYPE_ARGB32, to test alpha support downstream.
This filter also supports seeking.

RateSource - a source filter that outputs video at a specified 
frame rate. This is useful for testing a variety of frame rates.
This filter also supports seeking.

Source8, Source555, Source565, Source24, Source32 -
These source filters output various RGB color formats to allow
testing of connectability of downstream filters.
These filters also support seeking.

Trans8, Trans555, Trans565, Trans24, Trans32, and Trans32a -
These transform-in-place filters are very simple.  They
do nothing in the transform - they merely demand a certain
input media type. These filters are useful to test upstream
filter connectability.

TransSmpte - This video trans-in-place filter will add a SMPTE
frame timestamp to the incoming video, if you desire the video 
to have timestamps on it. You can write this video to disk
(you might want to run it through a compressor first).  
Video with timestamps can be very useful when testing 
frame-accurate filters.


User's Guide
============
To use these filters, register this dll with the program
RegSvr32.exe, which is normally included in your windows
system directory. These filters will then be available for use
within the GraphEdit application.

