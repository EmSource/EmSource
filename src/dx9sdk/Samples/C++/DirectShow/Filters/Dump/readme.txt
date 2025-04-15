//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- Dump Filter
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========

Renderer filter that writes the media samples it receives 
to a text file.


Path
=====
Source: <SDK root>\Samples\C++\DirectShow\Filters\Dump


User's Guide
============
This sample illustrates the use of the base filter class CBaseFilter 
and the rendered input pin class CRenderedInputPin. This sample also 
uses the IFileSinkFilter interface. The Dump filter demonstrates how 
to override the Receive method of the rendered input pin class to 
process actual media samples. The Dump filter delivers the EC_COMPLETE 
notification to the filter graph when it receives a call to 
CDumpInputPin::EndOfStream on its input pin.

This filter is a useful debugging tool. For example, you can verify, 
bit by bit, the results of a transform filter. You can build a graph 
manually by using GraphEdit, and connect the Dump filter to the output 
of a transform filter or any other output pin. You can also connect a 
tee filter and put the Dump filter on one leg of the tee filter and the 
typical output on another leg to monitor the results in a real-time 
scenario.

The Dump filter has a single input pin, which is dumped to a file. 
The filter prompts the user for a file name when it is instantiated 
and closes the file when it is freed.
