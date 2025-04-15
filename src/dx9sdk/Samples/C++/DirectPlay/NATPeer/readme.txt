//-----------------------------------------------------------------------------
// 
// Sample Name: NAT Peer Sample
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

  The NAT Peer sample allows the user to specify the address and optional 
  password of an IDirectPlay8NATResolver server to be used for address resolution
  during calls to Host, EnumHosts, and Connect. 
  
Path
====
  Source:     DXSDK\Samples\C++\DirectPlay\NatPeer 
  Executable: DXSDK\Samples\C++\DirectPlay\Bin

User's Guide
============
  The program first displays a connection dialog where you can specify
  host/connect options, including an option to enable NAT address resolution. If
  enabled, the "Server Address" and "Password" are used by DirectPlay for 
  resolving the external addresses of players behind NATs which are not Universal
  Plug-and-Play (UPnP) compatible. If the user choose not to be the session host, 
  a second dialog is presented to find and connect to active sessions.

  Once in a session, it presents a simple game similiar to SimplePeer.  

Programming Notes
=================
  If the NAT address resolution option is checked, the "Server Address" and
  "Password" fields are added as components of the local device address under
  the DPNA_KEY_NAT_RESOLVER and DPNA_KEY_NAT_RESOLVER_USER_STRING keys.

  You may also specify multiple comma-delimited servers in the 
  DPNA_KEY_NAT_RESOLVER component. Each server is tried simultaneously for speed, 
  and the first response is used. If no server responds, the Host, Connect, or 
  EnumHosts call still succeeds; however, only local and Universal Plug-and-Play 
  connectivity information is used.

  Since hosting these resolving servers require resources, you may wish to prevent 
  arbitrary players from using the server.  This can be achieved with the 
  DPNA_KEY_NAT_RESOLVER_USER_STRING address component.  This value is passed directly 
  to the resolver for verification, and it can choose to respond or ignore as 
  appropriate.  Note that the user string is passed in clear text over the network, 
  so if the text could contain sensitive information, you should encrypt it in some 
  fashion.

  For an implementation of an IDirectPlay8NATResolver server and more information
  on NAT address resolution, check the NAT Resolver sample included with the SDK.
  
  