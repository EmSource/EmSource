//-----------------------------------------------------------------------------
// 
// Sample Name: Throttle Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------


Description
===========
  The Throttle sample demonstrates how to monitor the send queue and scale the 
  rate of network communication. 

Path
====
  Source:     DXSDV\Samples\C++\DirectPlay\Throttle 
  Executable: DXSDV\Samples\C++\DirectPlay\Bin

User's Guide
============
  Start the Throttle Server and wait for a moment while it connects to the
  network. Once the server is ready to accept connection, the dialog UI will
  appear. While the server is running, you can adjust the "Server Load" slider
  to simulate CPU load on the server. The higher the load setting, the slower
  the server will handle incoming messages.

  After the server is running, launch Throttle Client. The client will prompt 
  for the hostname or IP address where the server is running (note that the 
  port number is fixed). After connecting, the server will indicate the added
  connection and show the amount of received data. 

  You can adjust the "Send Interval" slider on the client to set the delay 
  between successive Send() calls. With the default server and client settings, 
  the server receive buffer will quickly fill to capacity, and outgoing messages
  will begin populating the send queue on the client. When "Regulate Outgoing
  Rate" is checked, the program will attempt to scale the number of outgoing
  messages to keep the queue size below the "Max Queue Size" set by the slider.  

  Note how adjustments to any of the client or server controls causes a 
  corresponding change in the queue size and wait as reported in the "Outgoing 
  Data" groupbox. Multiple clients can be connected simultaneously to model a 
  typical multiplayer session.

Programming Notes
=================
  To understand why you may need to throttle outgoing data in your application,
  we should first have a nice frank discussion about DirectPlay architecture
  and service providers. 

  If you check the documentation for DPN_SP_CAPS you'll find a list of capabilites 
  and settings for service providers; the ones we're interested in are 
  dwNumThreads, dwBuffersPerThread, and dwSystemBufferSize. During your average 
  TCP/IP session, DirectPlay immediately delivers messages to the send target's 
  receive queue. As described in the DPN_SP_CAPS documentation, the threads
  grab messages from the system buffer and store them in their own message buffers
  until they can be received by your message handler.

  When the thread buffers fill up and the system buffer fills up, DirectPlay won't
  allow any further messages to be delivered; any messages destined for that target
  are then stored in the local send queue until enough space frees up on the remote 
  machine.

  You can adjust these parameters to suit your application, but increases in buffer
  size usually translate to increases in game lag, so it's usually best to leave
  these values for the service provider to decide and concentrate instead on 
  optimizing network communication.

  Usually the send queue is only needed for temporary spikes in network traffic, but
  if a player continues to send messages faster than the target can receive them, 
  the send queue will continue to grow; if no precautions are taken, this will
  probably bring your game to its knees since any outgoing messages will take
  several seconds (or minutes) to make their way through all the queues.

  One easy way to combat this is to place a timeout value on outgoing messages.
  You can give critical messages a higher timeout value and different prioritization.
  In extreme circumstances, you may still run into a problems where messages 
  consistently timeout before reaching the target, and for the most flexibility you
  should also monitor the send queue and adjust the rate of outgoing data
  accordingly. 

  This sample takes the simple approach of blocking a portion of outgoing data
  based on the current send queue size, but since the application is responsible 
  for blocking the data it would be possible to store a running total of blocked
  data and send an averaged block of data the next time space allows; in this way
  critical data is never lost and minor update data can be screened or combined
  to ease the output rate. 

  
