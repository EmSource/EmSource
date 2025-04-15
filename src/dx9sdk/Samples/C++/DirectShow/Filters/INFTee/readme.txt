//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- InfTee Filter
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========
Infinite-pin tee filter. This filter has one input pin and 
a dynamic number of output pins. All data samples sent to 
the filter are delivered down all paths simultaneously, 
thereby teeing the input into multiple separate output streams.


Path
=====
Source: <SDK root>\Samples\C++\DirectShow\Filters\InfTee>


User's Guide
============
The filter sends the same data down all of the output pins; 
therefore, the pins must have negotiated the same media type 
during connection. The infinite-pin tee filter handles this 
negotiation so that the input pin and both output pins converge 
when using the same media type. If a suitable media type cannot 
be found, then the connection is rejected.

The filter always uses the suggested allocator; the filter that 
provides the data suggests the allocator. The data arriving at 
the input pin is not copied before it is sent to the output pins. 
The filter also ensures that the data is delivered to the downstream 
filters, to guarantee that both outputs receive timely service. 
In particular, if one of the outputs can block in the 
COutputQueue::Receive member function, then the tee spins off a 
thread to deliver the sample. If there were no thread to deliver 
the sample, then the thread that delivers the sample to the tee 
input pin might pass the data to a downstream filter; at that point, 
it might block, keeping data from the other downstream filter for 
long periods of time.
