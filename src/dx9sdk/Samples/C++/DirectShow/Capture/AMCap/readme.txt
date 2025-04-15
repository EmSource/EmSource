//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- AMCap
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========
This sample application demonstrates the following tasks related to 
audio and video capture:

- Capture to a file
- Live preview
- Allocation of the capture file
- Display of device property pages
- Device enumeration
- Stream control

AMCap replaces the Video For Windows VidCap sample.


NOTE: If you are capturing video on a FAT32 disk drive, then you will
be limited to 4GB file sizes.  If your capture file size reaches 4GB,
you will see an error message indicating that there is no more disk space
(ERROR_DISK_FULL).  Even though your disk may have more space available, 
the file size cannot exceed 4GB and capturing will stop.

