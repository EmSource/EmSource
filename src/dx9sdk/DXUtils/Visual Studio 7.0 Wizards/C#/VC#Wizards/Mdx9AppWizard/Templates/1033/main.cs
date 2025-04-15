using System;
using System.Drawing;
using Microsoft.DirectX;
using Container = System.ComponentModel.Container;
[!if !GRAPHICSTYPE_DIRECT3D]
using System.Windows.Forms;
[!endif]

[!if USE_DIRECTPLAY && !GRAPHICSTYPE_DIRECT3D]
public delegate void MessageDelegate(byte message); // Delegate for messages arriving via DirectPlay.
public delegate void AudioDelegate(); // Delegate to handle audio playback.
public delegate void PeerCloseCallback(); // This delegate will be called when the session terminated event is fired.
[!endif]
/// <summary>
/// The main windows form for the application.
/// </summary>
public class MainClass[!if !GRAPHICSTYPE_DIRECT3D] : System.Windows.Forms.Form[!endif]
{

[!if GRAPHICSTYPE_NOGRAPHICS || GRAPHICSTYPE_DIRECTDRAW && !VISUALTYPE_BLANK]
    private const float spriteSize = 50;
[!endif]
[!if USE_DIRECTINPUT && !GRAPHICSTYPE_DIRECT3D]
    private InputClass input = null;
[!endif]
[!if GRAPHICSTARGET_PICTUREBOX && !GRAPHICSTYPE_DIRECT3D]
    private System.Windows.Forms.PictureBox pbTarget;
    private System.Windows.Forms.GroupBox groupBox1;
[!endif]
[!if USE_AUDIO && !GRAPHICSTYPE_DIRECT3D]
    public AudioClass audio = null;
[!endif]
[!if !GRAPHICSTYPE_DIRECT3D]
    public Point destination = new Point(10, 10);
[!endif]
    private GraphicsClass graphics = null;
[!if !GRAPHICSTYPE_DIRECT3D]
    private Container components = null;
    private Control target = null; // Target for rendering operations.
[!endif]
[!if USE_DIRECTPLAY && !GRAPHICSTYPE_DIRECT3D]
    private PlayClass play = null;

    private const byte msgUp = 0;
    private const byte msgDown = 1;
    private const byte msgLeft = 2;
    private const byte msgRight = 3;
[!if USE_AUDIO]
    private const byte msgAudio = 8;
    private const byte msgSound = 9;
[!endif]
[!endif]

    /// <summary>
    // Main entry point of the application.
    /// </summary>
    public static void Main()
    {
        MainClass m = new MainClass();
[!if !GRAPHICSTYPE_DIRECT3D]
        Application.Exit();
[!endif]
    }

    public MainClass()
    {
[!if !GRAPHICSTYPE_DIRECT3D]
        //
        // Required for Windows Form Designer support
        //
        InitializeComponent();
[!endif]
[!if GRAPHICSTARGET_PICTUREBOX && !GRAPHICSTYPE_DIRECT3D]
        target = pbTarget;
[!endif]
[!if !GRAPHICSTARGET_PICTUREBOX && !GRAPHICSTYPE_DIRECT3D]
        target = this;
[!endif]
[!if USE_AUDIO && !GRAPHICSTYPE_DIRECT3D]
        audio = new AudioClass(this);
[!endif]
[!if USE_DIRECTPLAY && !GRAPHICSTYPE_DIRECT3D]
        try
        {
            play = new PlayClass(this);
        }
        catch(DirectXException)
        {
            return;
        }
[!endif]
[!if USE_DIRECTINPUT && !GRAPHICSTYPE_DIRECT3D]
        input = new InputClass(this[!if USE_AUDIO], audio[!endif][!if USE_DIRECTPLAY], play[!endif]);
[!endif]
[!if !GRAPHICSTYPE_DIRECT3D]
        graphics = new GraphicsClass(target);
        Show();
        StartLoop();
[!endif]
[!if GRAPHICSTYPE_DIRECT3D]
        try
        {
            graphics = new GraphicsClass();
        }
        catch(DirectXException)
        {
            return;
        }
        if( graphics.CreateGraphicsSample() )
            graphics.Run();
[!endif]
    }
[!if !GRAPHICSTYPE_DIRECT3D]
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    protected override void Dispose( bool disposing )
    {
        if( disposing )
        {
            if (components != null) 
            {
                components.Dispose();
            }
        }
        base.Dispose( disposing );
    }

    /// <summary>
    // This is the main loop of the application.
    /// </summary>
    private void StartLoop()
    {
[!if VISUALTYPE_BLANK]
        string text = string.Empty;
[!endif]
        while(Created)
        {
[!if USE_DIRECTINPUT && !USE_DIRECTPLAY]
            Point p = input.GetInputState();

            destination.X += p.X;
            destination.Y += p.Y;
[!endif]
[!if USE_DIRECTINPUT && USE_DIRECTPLAY]
            input.GetInputState();
[!endif]                
[!if GRAPHICSTYPE_DIRECTDRAW && VISUALTYPE_BLANK]
            text = "X: " + destination.X + " Y: " + destination.Y;
            graphics.RenderGraphics(text);
[!endif]
[!if GRAPHICSTYPE_NOGRAPHICS || GRAPHICSTYPE_DIRECTDRAW && !VISUALTYPE_BLANK]
            CheckBounds();
            graphics.RenderGraphics(destination);
[!endif]
            Application.DoEvents();
        }
    }
[!endif]
[!if !GRAPHICSTYPE_DIRECT3D]
    #region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        this.SuspendLayout();
[!if GRAPHICSTARGET_PICTUREBOX]
        this.pbTarget = new System.Windows.Forms.PictureBox();
        this.groupBox1 = new System.Windows.Forms.GroupBox();
        
        // 
        // pbTarget
        // 
        this.pbTarget.Anchor = (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right);
        this.pbTarget.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
        this.pbTarget.Location = new System.Drawing.Point(136, 8);
        this.pbTarget.Name = "pbTarget";
        this.pbTarget.Size = new System.Drawing.Size(264, 264);
        this.pbTarget.TabIndex = 0;
        this.pbTarget.TabStop = false;
        // 
        // groupBox1
        // 
        this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left);
        this.groupBox1.Location = new System.Drawing.Point(8, 8);
        this.groupBox1.Name = "groupBox1";
        this.groupBox1.Size = new System.Drawing.Size(112, 264);
        this.groupBox1.TabIndex = 1;
        this.groupBox1.TabStop = false;
        this.groupBox1.Text = "Insert Your UI";

        this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                        this.groupBox1,
                                                                        this.pbTarget});
[!endif]
        // 
        // MainClass
        // 
        this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
        this.ClientSize = new System.Drawing.Size(408, 294);
        this.KeyPreview = true;
        this.Name = "MainClass";
        this.Text = "[!output PROJECT_NAME]";
[!if !USE_DIRECTINPUT]
        this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainClass_KeyDown);
[!endif]
[!if GRAPHICSTYPE_NOGRAPHICS || GRAPHICSTYPE_DIRECTDRAW && !VISUALTYPE_BLANK]
        this.Resize += new System.EventHandler(this.Repaint);
        this.Activated += new System.EventHandler(this.Repaint);
[!endif]
        this.ResumeLayout(false);
    }
    #endregion
[!endif]
[!if !USE_DIRECTINPUT]

[!if !GRAPHICSTYPE_DIRECT3D]
    /// <summary>
    // Handles keyboard events.
    /// </summary>
    private void MainClass_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
    {
        switch (e.KeyCode)
        {
            case Keys.Up:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgUp);
[!else]
                destination.Y--;
[!endif]
                break;
            }
            case Keys.Down:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgDown);
[!else]
                destination.Y++; 
[!endif]
                break;
            }
            case Keys.Left:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgLeft);
[!else]
                destination.X--; 
[!endif]
                break;
            }
            case Keys.Right:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgRight);
[!else]
                destination.X++; 
[!endif]
                break;
            }
[!if USE_AUDIO]
            case Keys.Q:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgSound);
[!else]
                audio.PlaySound();
[!endif]
                break;
            }
            case Keys.W:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgAudio);
[!else]
                audio.PlayAudio();
[!endif]
                break;
            }
[!endif]
        }
[!if GRAPHICSTYPE_NOGRAPHICS  || GRAPHICSTYPE_DIRECTDRAW && !VISUALTYPE_BLANK]
        CheckBounds();
        graphics.RenderGraphics(destination);
[!endif]
    }
[!endif]
[!endif]
[!if GRAPHICSTYPE_NOGRAPHICS || GRAPHICSTYPE_DIRECTDRAW && !VISUALTYPE_BLANK]

    /// <summary>
    // Checks the boundaries of graphics
    // objects to ensure they stay in bounds.
    /// </summary>
    private void CheckBounds()
    {
        if (destination.X < 0)
            destination.X = 0;
        if (destination.X > target.ClientSize.Width - spriteSize)
            destination.X = target.ClientSize.Width  - (int)spriteSize;
        if (destination.Y < 0)
            destination.Y = 0;
        if (destination.Y > target.ClientSize.Height - spriteSize)
            destination.Y = target.ClientSize.Height - (int)spriteSize;
    }

    private void Repaint(object sender, System.EventArgs e)
    {
        if (graphics != null)
            graphics.RenderGraphics(destination);       
    }
[!endif]
[!if USE_DIRECTPLAY && !GRAPHICSTYPE_DIRECT3D]

    public void MessageArrived(byte message)
    {
        switch (message)
        {
            case msgUp:
            {
                destination.Y--;
                break;
            }
            case msgDown:
            {
                destination.Y++;
                break;
            }
            case msgLeft:
            {
                destination.X--;
                break;
            }
            case msgRight:
            {
                destination.X++;
                break;
            }
[!if USE_AUDIO]
            case msgAudio:
            {
                audio.PlayAudio();
                break;
            }
            case msgSound:
            {
                this.BeginInvoke(new AudioDelegate(audio.PlayAudio));
                break;
            }
[!endif]
        }
    }

    /// <summary>
    // When the peer closes, the code here is executed.
    /// </summary>
    public void PeerClose()
    {
        // The session was terminated, go ahead and shut down
        this.Dispose();
    }
[!endif]
}
