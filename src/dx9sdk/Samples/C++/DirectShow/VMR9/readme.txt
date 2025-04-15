Windows XP Video Mixing Renderer 9 Samples
------------------------------------------

These samples demonstrate using the DirectX 9 Video Mixing Renderer
and provide examples of many of the VMR9's new features and capabilities.
All of these examples are written with C++.

Because the VMR9 is not the default video renderer, using RenderFile()
will not guarantee that the VMR9 will be used as the renderer on a
DirectX 9 system.  To ensure that the VMR9 is used as the renderer
in your filter graphs, a utility method (RenderFileToVMR9) is implemented
in the inc\vmrutil.h header and is used by most of the VMR9 samples.  
Review the vmrutil.h methods for further details.


These samples require the DirectX 9 runtimes, but they do not 
require Windows XP.


Windows Media is not supported in most VMR9 samples
---------------------------------------------------

Because of the Windows Media Format SDK (and WMStub.lib) dependency,
along with the extra filter connection and key provider code required,
the DirectShow SDK Video Mixing Renderer 9 samples do not support
rendering and playback of Windows Media content (ASF, WMA, WMV) by default.

If you attempt to open a Windows Media file with these samples, you will be 
presented with a message box indicating the lack of Windows Media support, 
with a pointer to the samples that do properly support Windows Media files.

The following samples provide the necessary extra code and project settings
to enable proper Windows Media support (including unlocking of "keyed" files):

        - ASFCopy   - AudioBox  
        - Jukebox   - PlayWndASF

For more detailed information, see "Using DirectShow->Windows Media Applications"
in the DirectX SDK documentation.


Hardware requirements
---------------------

The VMR9 samples require a video card with a minimum of 16MB of video RAM.
If your card has less than the minimum RAM, you may see failures when
building filter graphs.  If that occurs, try lowering your display resolution.
