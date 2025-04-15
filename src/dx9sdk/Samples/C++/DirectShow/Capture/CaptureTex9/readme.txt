//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- CaptureTex9
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========
This sample combines features of the Texture3D9 and PlayCap samples
to render live incoming video onto a waving flag.

CaptureTex9 will enumerate any existing video capture devices
attached to the system and will load the first device found.
A DirectShow renderer object will be created to render the incoming
video stream onto a Direct3D9 surface, taking advantage of new
Direct3D9 features.


KNOWN ISSUE: For some triangle strip Direct3D primitives, the texture 
maps incorrectly with some popular graphics cards.  This driver 
error causes the first pixel (0,0) to fill the entire surface.  For the 
CaptureTex9 sample, this error will prevent the proper display of 
live video on some video cards.

