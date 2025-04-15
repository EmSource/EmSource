//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- PSIParser Filter
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========

The parser filter works with the MPEG2 demux and parses the psi sections in the 
transport stream received from the demux. It has a property page to display 
the MPEG2 program information it parsed. To view a program, the user can 
enter audio and video pids, then the audio and video output pins of the Demux 
will be created and mapped, and a preview graph will be built and run. 

Implementation:

The parser filter has one input pin, which owns two objects (CPatProcessor 
and CPmtProcessor) to process pat section and pmt section.

Note:

Property page is for setting/getting local/private data/parameters and is not 
meant for graph control/modification. The property page was used in this sample 
for the purpose of convenience, to keep the sample simple, and is not a 
recommended practice.

Demonstration instructions:

Preview MPEG2 transport stream from capture device (1394 Mpeg2 camcorder, D-VHS)

a.	Plug in 1394 Mpeg2 AV/C device;
b.	Install Mpeg2 software decoder
c.	Register proppage.dll and PsiParser.ax
d.	Open graph editor and insert the capture device from Capture Source; 
	insert Mpeg2 demux and PsiParser filter from DirectShow filter
e.	Connect capture filter and Mpeg2 demux
f.	Use Mpeg2 Demux property page to create one PSI output Pin with PID=0x0000: 
	(under "Output Pin", enter new output pin name "PSI", select MPEG-2PSI as Media 
	Type and click "Create". Then go to "PID Mappings", select PID = 0x00000 as PID 
	and PSI as PIN, and select MPEG2 PSI Sections, then click "Map" button.)
g.	Refresh the graph to see the output PSI pin; connect it to PSI parser filter
h.	Play the capture device and run the graph
i.	Open the property page of PSI Parser, and click Refresh button
j.	Select a program by clicking on a program number, notice the information of 
	the elementary streams contained in the selected program will be displayed below
k.	Enter audio and video PID of a program, and click "View Program" to play the 
	A/V from the selected program
l.	Stop viewing by clicking "Stop Viewing" button.


Path
====
Source: <SDK root>\Samples\C++\DirectShow\Filters\PSIParser


User's Guide
============


Additional Documentation
========================

1) MPE2_Docs.doc contains:

A very brief intro to MPEG-2 Systems, including:

- How to configure the MPEG-2 demux. (Slightly expanded version 
      of what's in our docs now.)
- How to use the multicast filters (DSNetwork)
- How to use the PSI Parser

2) IMulticastConfig.doc: Ref pages for the multicast filters

3) IMpeg2Parser.doc: Ref pages for the PSI Parser
