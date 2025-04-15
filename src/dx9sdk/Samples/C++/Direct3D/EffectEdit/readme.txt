//-----------------------------------------------------------------------------
// Name: EffectEdit Direct3D Sample
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


Description
===========
   The EffectEdit sample implements a tool that allows easy experimentation 
   with D3DX Effects.  D3DX Effects provide a convenient way to package 
   multiple techniques for rendering an object, including render states,
   vertex shaders, pixel shaders, and multiple passes.  See the DirectX SDK
   documentation for more information about D3DX Effects.  In EffectEdit, you
   can load effect files, edit them, and see an object rendered with the
   effect.  Changes to the effect are reflected immediately on the rendered
   object.

   Note that not all effect files will work well with EffectEdit.  Effects
   that need a lot of parameters to be set by the app will probably not work
   well.  EffectEdit only sets a limited number of parameters:

   Parameters with the WORLD semantic will contain the world matrix
   Parameters with the VIEW semantic will contain the view matrix
   Parameters with the PROJECTION semantic will contain the projection matrix
   Parameters with the WORLDVIEW semantic will contain the world*view matrix
   Parameters with the VIEWPROJECTION semantic will contain the view*projection 
      matrix
   Parameters with the WORLDVIEWPROJECTION semantic will contain the 
      world*view*projection matrix
   Parameters with the NAME annotation will cause a texture with the given 
      name to be loaded
   Parameters with the FUNCTION annotation will cause a procedural texture 
      with the given name to be loaded and used to initialize the texture
   Parameters with the TARGET annotation will cause the procedural texture 
      to use the specified instruction set (Default is "tx_1_0")
   Parameters with the WIDTH annotation will cause the texture to have the
      specified width
   Parameters with the HEIGHT annotation will cause the texture to have the
      specified height
   An integer parameter named "BCLR" will be used to define the background 
      color of the scene
   A string parameter named "BIMG" will be used to define a background image 
      for the scene
   A string parameter named "XFile" will be used to load an XFile containing 
      the object to be rendered

   
Path
====
   Source:     DXSDK\Samples\C++\Direct3D\EffectEdit
   Executable: DXSDK\Samples\C++\Direct3D\Bin


User's Guide
============
   The user interface is a window divided into four "panes".  You can press
   Ctrl-Tab to change the keyboard focus between these panes.

   The "Effect file source code" pane shows the source code for the current 
   effect and provides text editing capability.  

   The "Effect compilation results" pane shows the results of compiling the
   current effect.  You can double-click on errors to jump to the offending
   line in the source code pane.  If there are no errors, the results pane
   will say "Compilation successful!" and you should see the rendered object.

   The "Rendered scene" pane shows the rendered object, using the current
   effect.  You can drag the left mouse button to rotate the object, the
   right mouse button to move the object, and click the scroll wheel to 
   zoom the object.

   The "Rendering options" pane lets you change various aspects of how the 
   object is rendered.  The "Reset Camera" button moves the camera back to the
   default position and orientation.



Programming Notes
=================
   EffectEdit is an MFC application, using the single-document model.
   CEffectDoc is the class representing the document, which is mainly just 
   the text contents of the effect.  CMainFrame manages the display of the
   four different views used on this document, and the splitter windows
   that control the panes containing the views.  CTextView is the text
   editor, CErrorsView is the compilation results, COptionsView is the
   rendering options, and CRenderView is the rendered output.  Only the
   last class really uses Direct3D and D3DX code.  CRenderView is derived
   from both CFormView and CD3DApplication, so it can use familiar methods
   like FrameMove, InitDeviceObjects, etc.
   
   This sample makes use of common DirectX code (consisting of helper functions,
   etc.) that is shared with other samples on the DirectX SDK. All common
   headers and source code can be found in the following directory:
      DXSDK\Samples\C++\Common

