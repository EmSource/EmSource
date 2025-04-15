//-----------------------------------------------------------------------------
// 
// Sample Name: DirectMusic tutorial 2
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// GM/GS® Sound Set Copyright ©1996, Roland Corporation U.S.
// 
//-----------------------------------------------------------------------------



Description
===========
    This tutorial is a guide to setting up a DirectMusic performance and 
    retrieving an object—in this case, a 3-D buffer—from an audiopath so that 
    sound parameters can be changed. The tutorial is presented in the following 
    steps: 
        Step 1: Create the Audiopath 
        Step 2: Retrieve the Buffer 
        Step 3: Change Buffer Parameters 


Path
====
  Source:     DXSDK\Samples\C++\DirectMusic\Tutorials\Tutorial2


Programming Notes
=================
    Step 1: Create the Audiopath
    
    The simplest way to create an audiopath is by passing a flag to 
    IDirectMusicPerformance8::InitAudio. The tutorial sample passes the 
    DMUS_APATH_DYNAMIC_STEREO flag, causing InitAudio to set up a default 
    audiopath that supports stereo sounds: 
    
            g_pPerformance->InitAudio( 
              NULL,        // IDirectMusic interface not needed.
              NULL,        // IDirectSound interface not needed.
              NULL,        // Window handle.
              DMUS_APATH_DYNAMIC_STEREO, // Default audiopath type.
              64,          // Number of performance channels.
              DMUS_AUDIOF_ALL,     // Features on synthesizer.
              NULL         // Audio parameters; use defaults.
            );
    
    The default audiopath is suitable for sounds that do not have to be 
    located in space, such as background music or narration. However, if an 
    application implements 3-D sound effects, it will play each sound source 
    on its own audiopath, so that 3-D parameters can be set individually.
    
    The sample creates one such audiopath as follows:
    
            IDirectMusicAudioPath8* p3DAudioPath = NULL;
            g_pPerformance->CreateStandardAudioPath( 
              DMUS_APATH_DYNAMIC_3D,  // Path type.
              64,                     // Number of performance channels.
              TRUE,                   // Activate now.
              &p3DAudioPath           // Pointer that receives audiopath.
            );
            
    A segment can now be played on this audiopath as follows:
    
            g_pPerformance->PlaySegmentEx(
              g_pSegment,  // Segment to play.
              NULL,        // Used for songs; not implemented.
              NULL,        // For transitions. 
              0,           // Flags.
              0,           // Start time; 0 is immediate.
              NULL,        // Pointer that receives segment state.
              NULL,        // Object to stop.
              p3DAudioPath // Audiopath.
            );  
            
    Step 2: Retrieve the Buffer
    
    By using the IDirectMusicAudioPath8::GetObjectInPath method, you can retrieve 
    interfaces to objects that form part of the path. In the case of the 
    DMUS_APATH_DYNAMIC_3D standard audiopath type, such objects could include the 
    secondary buffer itself, the primary buffer, the DirectSound listener, or any 
    DMOs set on buffers after the audiopath was created. The tutorial sample obtains 
    the IDirectSound3DBuffer8 interface to the buffer:
    
            IDirectSound3DBuffer8* pDSB = NULL;
             
            p3DAudioPath->GetObjectInPath( 
              DMUS_PCHANNEL_ALL,  // Performance channel.
              DMUS_PATH_BUFFER,   // Stage in the path.
              0,                  // Index of buffer in chain.
              GUID_NULL,          // Class of object.
              0,                  // Index of object in buffer; ignored.
              IID_IDirectSound3DBuffer, // GUID of desired interface.
              (LPVOID*) &pDSB     // Pointer that receives interface.
            );
            
    The parameters to IDirectMusicAudioPath8::GetObjectInPath can be a little tricky 
    to set up properly. For information on which parameters are relevant for objects 
    at different stages in the path, see Retrieving Objects from an Audiopath. 
    
    In this case, you are retrieving a secondary buffer that is used by all performance 
    channels on this audiopath. Set the dwPChannel parameter to DMUS_PCHANNEL_ALL. 
    
    Because the buffer you want is the first and in this case the only buffer in 
    the chain, you pass 0 as dwBuffer. The DMUS_PATH_BUFFER stage contains only 
    buffer objects, and not the DMOs attached to those buffers; therefore dwIndex is ignored.
    
    Step 3: Change Buffer Parameters
    
    Now that you have the IDirectSound3DBuffer8 interface, you can use it to move the 
    sound in space. The tutorial sample application does so when the user closes a series 
    of message boxes. For example, the following code immediately moves the sound to the left:
    
            pDSB->SetPosition( -0.1f, 0.0f, 0.0f, DS3D_IMMEDIATE );
    
    The first three parameters specify the new position of the sound source in relation 
    to the default listener. The default listener is at coordinates (0.0, 0.0, 0.0), 
    facing toward the positive z-axis, with the top of the head toward the positive y-axis. 
    Distance units are meters by default. Because the x-axis is positive from left to right, 
    the new position of the sound is 10 centimeters directly to the left of the listener. 
    For more information, see Coordinates of 3-D Space and Listener Orientation. 
    
    The last parameter of the IDirectSound3DBuffer8::SetPosition method specifies whether 
    the change is to be made immediately or deferred until all changes are committed. For 
    more information, see Deferred Settings.
