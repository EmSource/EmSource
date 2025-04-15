using System;
using System.Windows.Forms;
using System.Drawing;

/// <summary>
/// This class is where the Drawing routines
/// for non-Direct3D and non-DirectDraw 
/// applications reside.
/// </summary>
public class GraphicsClass
{
    private const float spriteSize = 50;
    private Control owner = null;
    private Graphics graphicsWindow = null;
    
    public GraphicsClass(Control owner)
    {
        this.owner = owner;
    }

    public void RenderGraphics(Point destination)
    {
        if (!owner.Created)
            return;

        graphicsWindow = owner.CreateGraphics();
        graphicsWindow.Clear(Color.Blue);
        graphicsWindow.FillEllipse(Brushes.Black, destination.X, destination.Y, spriteSize, spriteSize);
    }
}