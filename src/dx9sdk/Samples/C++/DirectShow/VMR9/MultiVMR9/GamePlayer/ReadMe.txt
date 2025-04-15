//-----------------------------------------------------------------------------
// Name: DirectShow Sample -- MultiVMR9 GamePlayer sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


This sample illustrates how to integrate video powered by VMR9 into a
Direct3D environment (perhaps in a 3D game).  The application uses the same 
MultiVMR9.dll, but overrides IMultiVMR9MixerControl and IMultiVMR9UILayer. 

Before building this sample, make sure that MultiVMR9.dll is built and 
registered with regsvr32.exe. Please note that slow machines and older video cards 
can demonstrate significant performance drop. Machines like Pentium-III 500MHz and up 
with video cards no older that 2 years would be sufficient.


Usage

1. Run GamePlayer

2. Select a few (3-5) mpeg1 or AVI movies and hit "start".

3. A new window should appear, displaying a girl walking along the wall.

4. In a few seconds, the girl starts passing videos on the wall.

5. To focus on the highlighted movie, hit the yellow button in the lower right corner.

6. To stop the presentation, go back to initial dialog and hit "stop" and "exit".


NOTE: This sample requires DirectX 9 (or greater) functionality 
and will exit on other systems.

NOTE: You must build MultiVMR9.dll and register it with 'regsvr32' before
you can run this application.

NOTE: This sample will not build UNICODE due to a D3DX header dependency.
