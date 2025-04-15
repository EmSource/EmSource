//-----------------------------------------------------------------------------
// 
// Sample Name: NAT Resolver Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------


Description
===========
  Network Address Translators (NATs) are used to share a single Internet Protocol 
  (IP) address between multiple computers; this means that a computer's internal 
  IP address will be different from its external IP address. Players behind NATs
  which are not Universal Plug-and-Play compatible can determine their external
  address by connecting to a server outside the NAT; the source address seen
  by the server is the player's external address.

  The NAT Resolver sample shows how the IDirectPlay8NATResolver interface can be
  used to implement address resolution for players behind NATs. This interface
  acts as a simple server which accept queries and reflects the perceived address
  back to the caller.

  For players to use the NAT Resolver server you must add the server's location
  and the optional password to the player's device address; these values will
  then be used during a call to Host, Connect, or EnumHosts to perform address
  resolution for the calling player. 

Path
====
  Source:     DXSDK\Samples\C++\DirectPlay\NatResolver
  Executable: DXSDK\Samples\C++\DirectPlay\Bin

User's Guide
============
  On startup, the program creates an object of the DirectPlay8NATResolver
  interface and waits for queries. The sample always listens on all available
  IPv4 devices for incoming queries. If "Require password" is checked, any
  queries are first screened for the plain text password before allowing 
  DirectPlay to return the resolved address. 
  
  The dialog displays the list of addresses currently in use, as well as the
  number of incoming queries and outgoing responses.  

Programming Notes
=================
  DirectPlay handles most of the work, interrupting only to make sure an
  incoming query is from an authorized client. The Initialize() method sets
  up the message callback (for client authorization), and the Start() method
  starts the server on the requested device. 

  DirectPlay informs your program about client queries with 
  DPNMSG_NAT_RESOLVER_QUERY messages, which contain the client address and 
  given password. A successful return value from this callback instructs 
  DirectPlay to handle the address resolution; a failed return value cancels
  the resolution but continues executing the associated DirectPlay call. 
  Using the password mechanism allows you to deny access to your resolution 
  server for clients which are not part of your game.
