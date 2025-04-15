//-----------------------------------------------------------------------------
// Name: ASYNC filter
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

Description
===========

This sample set contains three separate projects that work together.

	Base 	- Base library with I/O functionality
	Filter	- Source for Async Filter (which uses the Base library)
	Memfile	- Sample application that uses the async filter

Since these projects build on each other, you have two options when building
an individual project:

1) Use the Async.DSW Visual C++ workspace in the Async directory.  This
	workspace provides dependency information, such that building one
	project will also build any project on which it depends.  For example,
	if you build Memfile, it will also build the Base and Filter
	directories if they are out of date or have not yet been built.


2) Build each project individually by opening its Visual C++ workspace.

   To prevent linker errors, build the projects in the following order: 
		Base	(with asynbase.dsw)
		Filter	(with asyncflt.dsw)
		MemFile (with memfile.dsw)


User's Guide
============

This sample includes a small command-line application, Memfile.exe, 
that demonstrates the filter. The command-line arguments specify a 
media file and a bit rate, in kilobytes per second. The application 
reads the file into memory at the specified rate and plays the file. 
To do so, it creates an instance of the filter, adds the filter to the 
filter graph, and renders the filter's output pin.


Usage
=====

Memfile Filename BitRate 

The Async sample filter does not support AVI files, because it 
cannot connect to the AVI Splitter filter. The Async filter's output pin 
proposes MEDIATYPE_Stream and MEDIASUBTYPE_NULL for the media type. 
The input pin on the AVI Splitter filter does not accept MEDIASUBTYPE_NULL, 
and does not propose any types of its own. Therefore, the pin connection 
fails. The Async filter could be enhanced to offer MEDIASUBTYPE_Avi when 
appropriate. For example, it could examine the file format, or use the file 
extension.

