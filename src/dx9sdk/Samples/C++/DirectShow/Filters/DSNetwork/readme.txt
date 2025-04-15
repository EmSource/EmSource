//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- DirectShow Network Filters
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description

The DSNetwork sample shows how to multicast an MPEG-2 transport stream. 
It includes two related filters: 

- MPEG-2 Multicast Sender: Sends a multicast stream. 
- MPEG-2 Multicast Receiver: Receives a multicast stream. 

Both filters support a custom interface, IMulticastConfig, for setting the 
multicast address and Network Interface Card (NIC) address. 


Path

Source: (SDK root)\Samples\C++\DirectShow\Filters\DSNetwork


User's Guide

To use this sample, compile and build the Visual Studio project. It creates 
a DLL named dsnet.ax in the Filter\Debug or Filter\Release subdirectories. 
Use the Regsvr32 utility to register the DLL.

You will need an MPEG-2 transport stream in push mode. This can be a 
digital television tuner, a 1394 MPEG-2 camcorder, or anything else that 
delivers an MPEG-2 transport stream (other than a file source). 
You will need two graphs, a sending graph and a receiving graph. 

For more information about the DSNetwork filters, refer to the SDK documentation.


We hope to provide a sample application in Beta 3 to better demonstrate 
these filters.
