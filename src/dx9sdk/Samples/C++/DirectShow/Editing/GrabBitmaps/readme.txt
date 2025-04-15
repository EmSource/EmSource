//-----------------------------------------------------------------------------
// Name: DirectShow Editing Sample - GrabBitmaps
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

Description
===========

This C++ console app shows how to use the sample grabber filter
and a COM object callback to capture media samples in a running
video file.

GrabBitmaps performs the following steps:
    - Open a specified AVI file
    - Create a filter graph with a sample grabber filter
    - Read five frames at approximately one-second intervals
    - Write the frames to bitmap (.BMP) files in the current directory

Usage: GrabBitmaps <filename>


Sample output:

Grabbing bitmaps from c:\movie.avi.
Found a sample at time 0 ms     [Bitmap00000.bmp]
Found a sample at time 998 ms   [Bitmap00998.bmp]
Found a sample at time 1996 ms  [Bitmap01996.bmp]
Found a sample at time 2994 ms  [Bitmap02994.bmp]
Found a sample at time 3992 ms  [Bitmap03992.bmp]
Sample grabbing complete.