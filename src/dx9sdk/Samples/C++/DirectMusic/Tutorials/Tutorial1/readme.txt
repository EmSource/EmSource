//-----------------------------------------------------------------------------
// 
// Sample Name: DirectMusic tutorial 1
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// GM/GS® Sound Set Copyright ©1996, Roland Corporation U.S.
// 
//-----------------------------------------------------------------------------



Description
===========
    This tutorial is a step-by-step guide to the most basic tasks in DirectX Audio: 
    initializing a DirectMusic performance and playing an audio file. The tutorial is 
    presented in the following steps: 
        Step 1: Initialize 
        Step 2: Load a File 
        Step 3: Play the File 
        Step 4: Close Down 


Path
====
  Source:     DXSDK\Samples\C++\DirectMusic\Tutorials\Tutorial1


Programming Notes
=================
    Step 1: Initialize
    
    The following includes are needed for any application that uses the DirectMusic API. 
    Including Dmusici.h also cause the other necessary header files for DirectMusic and 
    DirectSound to be included.
    
            #define INITGUID
            #include <dmusici.h>
    
    The tutorial uses three interface pointers, which are declared as follows:
    
            IDirectMusicLoader8*  g_pLoader   = NULL;
            IDirectMusicPerformance8* g_pPerformance  = NULL;
            IDirectMusicSegment8*   g_pSegment  = NULL;
    
    All the code in this simple application is included in the WinMain function. The 
    application has no main window, so it can proceed straight to the creation of COM and 
    two objects: the loader and the performance:.
    
            INT APIENTRY WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, INT nCmdShow )
            {
              CoInitialize(NULL);
              
              CoCreateInstance(CLSID_DirectMusicLoader, NULL, 
                   CLSCTX_INPROC, IID_IDirectMusicLoader8,
                   (void**)&g_pLoader);
            
              CoCreateInstance(CLSID_DirectMusicPerformance, NULL,
                   CLSCTX_INPROC, IID_IDirectMusicPerformance8,
                   (void**)&g_pPerformance );
    
    The next step is to initialize the performance and the synthesizer. The 
    IDirectMusicPerformance8::InitAudio method performs the following tasks: 
    
    - Creates a DirectMusic and a DirectSound object. In most cases you don't need an 
    interface to those objects, and you can pass NULL in the first two parameters. 
    
    - Associates an application window with the DirectSound object. Normally the handle 
    of the main application window is passed as the third parameter, but the tutorial 
    application doesn't have a window, so it passes NULL instead. 
    
    - Sets up a default audiopath of a standard type. The tutorial requests a path of type 
    DMUS_APATH_SHARED_STEREOPLUSREVERB, which is suitable for music. 
    
    - Allocates a number of performance channels to the audiopath. Wave files require only 
    a single performance channel, and MIDI files require up to 16. Segments created in 
    DirectMusic Producer might need more. No harm is done by asking for extra channels. 
    
    - Specifies capabilities and resources of the synthesizer. This can be done in one of 
    two ways: by setting flags or by supplying a DMUS_AUDIOPARAMS structure with more 
    detailed information. Most applications set the DMUS_AUDIOF_ALL flag and let 
    
    DirectMusic create the synthesizer with default parameters. 
    In the tutorial, the call to InitAudio is very simple:
    
              g_pPerformance->InitAudio( 
                NULL,      // IDirectMusic interface not needed.
                NULL,      // IDirectSound interface not needed.
                NULL,      // Window handle.
                DMUS_APATH_SHARED_STEREOPLUSREVERB,  // Default audiopath type.
                64,        // Number of performance channels.
                DMUS_AUDIOF_ALL,   // Features on synthesizer.
                NULL       // Audio parameters; use defaults.
              );

    Step 2: Load a File
    
    The DirectMusic performance and synthesizer are now ready to process sound data. To get 
    the data, the loader needs to know where to find it. Although a full path can be provided 
    each time a file is loaded, it is more convenient to establish a default directory. Do this 
    by using the IDirectMusicLoader8::SetSearchDirectory method.
    
    In the sample code, the path to the default Windows media directory is given. You can 
    change the value of wstrSearchPath to get files from a different folder.
    
    The following code is from the WinMain function in the tutorial sample:
    
              // Find the Windows media directory.
             
              CHAR strPath[MAX_PATH];
              GetWindowsDirectory( strPath, MAX_PATH );
              strcat( strPath, "\\media" );
             
             // Convert to Unicode.
             
              WCHAR wstrSearchPath[MAX_PATH];
              MultiByteToWideChar( CP_ACP, 0, strPath, -1, 
                     wstrSearchPath, MAX_PATH );
             
              // Set the search directory.
             
              g_pLoader->SetSearchDirectory( 
                GUID_DirectMusicAllTypes, // Types of files sought.
                wstrSearchPath,     // Where to look.
                FALSE         // Don't clear object data.
              );
    
    In the call to SetSearchDirectory, the fClear parameter is set to FALSE because there is 
    no danger of accidentally reloading objects from the wrong directory. This is likely to 
    happen only if the application is loading identically named objects from different folders.
    
    Now that the loader knows where to look for the file, it can load it as a segment:
    
              WCHAR wstrFileName[MAX_PATH] = L"The Microsoft Sound.wav";
             
              if (FAILED(g_pLoader->LoadObjectFromFile(
                CLSID_DirectMusicSegment, // Class identifier.
                IID_IDirectMusicSegment8, // ID of desired interface.
                wstrFileName,     // Filename.
                (LPVOID*) &g_pSegment   // Pointer that receives interface.
              )))
              {
                MessageBox( NULL, "Media not found, sample will now quit.", 
                      "DMusic Tutorial", MB_OK );
                return 0;
              }
    
    Step 3: Play the File
    
    The wave file loaded in the previous step is now available to the performance through its 
    IDirectMusicSegment8 interface. 
    
    Before a segment can be played, its band must be downloaded to the synthesizer. As long 
    as you don't unload the band, this step has to be taken only once for each segment that 
    uses a unique band.
    
    The following code from the WinMain function in the sample downloads the band to the 
    performance. Alternatively, it could be downloaded to an audiopath. As long as only a 
    single synthesizer is in use, it doesn't matter which destination object you choose:
    
              g_pSegment->Download( g_pPerformance );
    
    To play the file, pass the segment interface to IDirectMusicPerformance8::PlaySegmentEx. 
    This method offers many options for playback, but to play a segment immediately on the 
    default audiopath, all the parameters except the first can be NULL or 0:
    
              g_pPerformance->PlaySegmentEx(
                g_pSegment,  // Segment to play.
                NULL,    // Used for songs; not implemented.
                NULL,    // For transitions. 
                0,     // Flags.
                0,     // Start time; 0 is immediate.
                NULL,    // Pointer that receives segment state.
                NULL,    // Object to stop.
                NULL   // Audiopath, if not default.
              );                
              MessageBox( NULL, "Click OK to Exit.", "Play Audio", MB_OK );
              
    Step 4: Close Down
    
    To exit an audio application cleanly, you must perform four main steps: 
    
    - Stop any playing segments by calling IDirectMusicPerformance8::Stop. 
    
    - Close down the performance. The IDirectMusicPerformance8::CloseDown method 
    performs miscellaneous cleanup tasks and releases internal references to objects. 
    
    - Release all interfaces. 
    
    - Close COM. 
    
    The following sample code from the WinMain function in the tutorial sample 
    is called when the dialog box is closed.
    
              g_pPerformance->Stop(
                NULL, // Stop all segments.
                NULL, // Stop all segment states.
                0,  // Do it immediately.
                0   // Flags.
              );
             
              g_pPerformance->CloseDown();
             
              g_pLoader->Release(); 
              g_pPerformance->Release();
              g_pSegment->Release();
             
              CoUninitialize();
                
              return 0;  // Return value for WinMain.
            }      // End of WinMain.
    
