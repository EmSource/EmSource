//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- PushSource Filter Set
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

Description
============

Set of three source filters that provide the following source data as a video stream:

    CPushSourceBitmap    - Single bitmap  (loaded from current directory)
    CPushSourceBitmapSet - Set of bitmaps (loaded from current directory)
    CPushSourceDesktop   - Copy of current desktop image (GDI only)
     

Path
====

Source: (SDK root)\Samples\C++\DirectShow\Filters\PushSource

User's Guide
============

This filter appears in GraphEdit as "PushSource Bitmap Filter", 
"PushSource BitmapSet Filter", and "PushSource Desktop Filter".

To use a filter, load it into GraphEdit and render its output pin.  This will
connect a video renderer (and possibly a Color Space Convertor filter) and allow
you to display the output.  If you want to render the output to an AVI file,
load the AVI Mux, load a File Writer Filter, provide an output name to the
File Writer, and render the PushSource filter's output pin.  You can also
load and connect video compressors, video effects, etc.

NOTE: The desktop capture filter does not support hardware overlays, so it 
will not capture video rendered to an overlay surface or cursors displayed via
hardware overlay.  It uses GDI to convert the current desktop image into a 
bitmap, which is passed to the output pin as a media sample.

