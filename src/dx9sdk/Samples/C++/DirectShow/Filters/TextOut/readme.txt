//-----------------------------------------------------------------------------
// 
// Sample Name: DirectShow Sample -- TextOut Filter
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------


Description
===========
This filter is a renderer that displays text data. 


Path
======
Source: (SDK root)\Samples\C++\DirectShow\Filters\TextOut


User's Guide
============
The DirectShow SDK includes an AVI file named Clocktxt.avi, 
which contains three streams: audio, video, and text. 
The text stream consists of NULL-terminated text strings. 
You can use the Text Display filter to render these text strings.

To use this filter, perform the following steps: 

1) Build and register the filter. 
2) Launch GraphEdit. 
3) Add the Text Display filter to the filter graph. 
4) Render the Clocktxt.avi file. 
5) Run the filter graph. 

