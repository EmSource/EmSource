//-----------------------------------------------------------------------------
// 
// Sample Name: PlayMotif Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// GM/GS® Sound Set Copyright ©1996, Roland Corporation U.S.
// 
//-----------------------------------------------------------------------------



Description
===========
  The PlayMotif sample demonstrates how a motif played as a secondary 
  segment can be aligned to the rhythm of the primary segment in various ways.

Path
====
  Source:     DXSDK\Samples\C++\DirectMusic\PlayMotif
  Executable: DXSDK\Samples\C++\DirectMusic\Bin

User's Guide
============
  Play the default segment, or load another DirectMusic Producer segment 
  that contains motifs. Select one of the patterns in the list box and 
  one of the Align Option buttons, and then click Play Motif. Note how 
  the motif does not begin playing until an appropriate boundary in the 
  primary segment has been reached.

Programming Notes
=================
  The PlayMotif sample is very similar in form to the PlayAudio sample.  For 
  detailed programming notes on the basics this sample, refer to Programming 
  Notes section of the PlayAudio sample.
  
  The PlayMotif differs by letting the user play any of motifs contained 
  inside the segment. Here's how:
  
  * When loading the file it does the same steps as the PlayAudio 
    sample, but also:  See LoadSegmentFile()
        1. It loops thru each style in the segment, searching it for 
           motifs.  It calls IDirectMusicSegment8::GetParam() passing 
           in GUID_IDirectMusicStyle and a increasing style index to get 
           each of the styles.  When this returns error then there are 
           no more styles.
        2. For each style, it calls IDirectMusicStyle::EnumMotif() passing
           in a increase motif index.  This retrieves the motif name at that
           index.  When the call returns S_FALSE, there are no more motifs in the 
           style.
        3. With the motif name it calls IDirectMusicStyle::GetMotif()
           to get a IDirectMusicSegment pointer to the motif, and
           stores this in the dlg listbox.
           
   * When "Play Motif" is clicked.  See OnPlayMotif().
        1. It gets the desired alignment option from the UI.  
        2. It gets the selected motif from the listbox, and a 
           its MOTIF_NODE* item data.  The MOTIF_NODE keeps
           a count of the number of plays currently occurring, as well
           as a pointer to the IDirectMusicSegment of the motif.
           This count is updated when a DMUS_NOTIFICATION_SEGSTART
           notification is returned (see below for details).
        3. It calls IDirectMusicPerformance::PlaySegment passing in
           the motif's IDirectMusicSegment and flags which have 
           DMUS_SEGF_SECONDARY as well as any alignment option.
       
   * When DirectMusic notifications occur, it is similar to PlayAudio but 
     now the app also takes note of any motif starting or stopping and
     updates the play count.  If the play count is greater than zero then
     it updates the UI to show that the motif is playing.  Most games
     would not need this functionality, but here's how its done: 
     See ProcessDirectMusicMessages().
        - Call IDirectMusicPerformance8::GetNotificationPMsg() in a loop
           to process each PMsg that has occurred.
        - Switch off the pPMsg->dwNotificationOption. 
        - If it is a DMUS_NOTIFICATION_SEGSTART.  This tells 
          us that a segment has ended.  It may be for a motif or the primary
          or some embedded segment in the primary segment.  
        - If it is a DMUS_NOTIFICATION_SEGEND.  This tells 
          us that a segment has ended.  It may be for a motif or the primary
          or some embedded segment in the primary segment.  
        - For either SEGSTART or SEGEND the code is similar:
            1. Call QueryInterface on the pPMsg->punkUser, quering for a 
               IDirectMusicSegmentState8.
            2. Using the IDirectMusicSegmentState8, call GetSegment to 
               get a IDirectMusicSegment* of the segment it refers to.  
               This call may fail is the segment may have gone away before this
               notification was handled.
            3. Call QueryInterface IDirectMusicSegment to get a IDirectMusicSegment8
            4. Compare this pointer to the IDirectMusicSegment8 pointer 
               in g_pMusicSegment, to see if this was the primary segment.
               If it has, then update the UI. If its not then compare it
               to each of the motif's segment pointers.  If a match is found
               update the play count accordingly, and update the UI based
               on the resulting play count.
            5. Cleanup all the interfaces.

  

