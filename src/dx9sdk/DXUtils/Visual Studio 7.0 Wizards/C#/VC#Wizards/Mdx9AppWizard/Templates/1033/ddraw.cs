using System;
using System.Windows.Forms;
using System.Drawing;
using Microsoft.DirectX;
using Microsoft.DirectX.DirectDraw;

/// <summary>
/// This class is where the Drawing routines
/// for non-Direct3D and non-DirectDraw 
/// applications reside.
/// </summary>
public class GraphicsClass
{
    private Control owner = null;

[!if !VISUALTYPE_BLANK]
    private const int spriteSize = 50;
[!endif]
[!if VISUALTYPE_BLANK]
    private Surface surfaceText = null;
[!endif]
    private Device localDevice = null;
    private Clipper localClipper = null;
    private Surface surfacePrimary = null;
    private Surface surfaceSecondary = null;

    public GraphicsClass(Control owner)
    {
        this.owner = owner;

        localDevice = new Device();
        localDevice.SetCooperativeLevel(owner, CooperativeLevelFlags.Normal);
        
        CreateSurfaces();
    }

    private void CreateSurfaces()
    {
        SurfaceDescription desc = new SurfaceDescription();
        SurfaceCaps caps = new SurfaceCaps(); 

        localClipper = new Clipper(localDevice);
        localClipper.Window = owner;

        desc.SurfaceCaps.PrimarySurface = true;
        surfacePrimary = new Surface(desc, localDevice);
        surfacePrimary.Clipper = localClipper;
        
        desc.Clear();
        desc.SurfaceCaps.OffScreenPlain = true;
        desc.Width = surfacePrimary.SurfaceDescription.Width;
        desc.Height = surfacePrimary.SurfaceDescription.Height;
        
        surfaceSecondary = new Surface(desc, localDevice);            
[!if !VISUALTYPE_BLANK]
        surfaceSecondary.FillStyle = 0;
[!endif]

[!if VISUALTYPE_BLANK]
        desc.Clear();
        desc.SurfaceCaps.OffScreenPlain = true;
        desc.Width = 100;
        desc.Height = 50;
        surfaceText = new Surface(desc, localDevice);
        surfaceText.ForeColor = Color.Black;
[!endif]
    }

[!if !VISUALTYPE_BLANK]
    public void RenderGraphics(Point destination)
    {
        if (!owner.Created)
            return;

        Rectangle dest = new Rectangle(owner.PointToScreen(new Point(destination.X, destination.Y)),new Size(spriteSize, spriteSize));

        if (null == surfacePrimary || null == surfaceSecondary)
            return;

        try
        {
            surfaceSecondary.ColorFill(Color.Blue);
            surfaceSecondary.DrawEllipse(dest.Left, dest.Y, dest.Right, dest.Bottom);
            surfacePrimary.Draw(surfaceSecondary, DrawFlags.DoNotWait);
        }
        catch(SurfaceLostException)
        {
            // The surface can be lost if power saving
            // mode kicks in, or any other number of
            // reasons.
            CreateSurfaces();
        }
    }
[!endif]
[!if VISUALTYPE_BLANK]
    public void RenderGraphics(string text)
    {
        Rectangle r = new Rectangle(new Point(owner.Left, owner.Top), new Size(surfacePrimary.SurfaceDescription.Width, surfacePrimary.SurfaceDescription.Height));

        if (!owner.Created) 
            return;

        if (null == surfacePrimary || null == surfaceSecondary)
            return;

        try
        {
            surfaceSecondary.ColorFill(Color.Blue);
            surfaceText.ColorFill(Color.Blue);
            surfaceText.DrawText(0, 0, text, true);
            surfaceSecondary.Draw(new Rectangle(10, 40, 100, 50), surfaceText, DrawFlags.DoNotWait);
            surfacePrimary.Draw(r, surfaceSecondary, DrawFlags.DoNotWait);
        }
        catch(SurfaceLostException)
        {
            // The surface can be lost if power saving
            //mode kicks in, or any other number of
            //reasons.
            CreateSurfaces();
        }
    }
[!endif]
}