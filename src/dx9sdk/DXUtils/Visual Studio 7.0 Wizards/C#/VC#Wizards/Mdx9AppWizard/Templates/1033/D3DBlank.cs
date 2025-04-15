using System;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Direct3D=Microsoft.DirectX.Direct3D;

public delegate void MessageDelegate(byte message); // Delegate for messages arriving via DirectPlay.
public delegate void AudioDelegate(); // Delegate to handle audio playback.
public delegate void PeerCloseCallback();           // This delegate will be called when the session terminated event is fired.

public class GraphicsClass : GraphicsSample
{
[!if GRAPHICSTARGET_PICTUREBOX]
    private System.Windows.Forms.PictureBox target = null;
    private System.Windows.Forms.GroupBox groupBox1;
[!endif]
    private D3DXFont drawingFont = null;
    private Point destination = new Point(0, 0);
[!if USE_AUDIO]
    private AudioClass audio = null;
[!endif]
[!if USE_DIRECTINPUT]
    private InputClass input = null;
[!endif]
[!if USE_DIRECTPLAY]

    private PlayClass play = null;

    private const byte msgUp = 0;
    private const byte msgDown = 1;
    private const byte msgLeft = 2;
    private const byte msgRight = 3;
    private const byte msgCancelUp = 4;
    private const byte msgCancelDown = 5;
    private const byte msgCancelLeft = 6;
    private const byte msgCancelRight = 7;
[!if USE_AUDIO]
    private const byte msgAudio = 8;
    private const byte msgSound = 9;
[!endif]
[!endif]

    public GraphicsClass()
    {            
        this.Text = "[!output PROJECT_NAME]";
[!if USE_AUDIO]
        audio = new AudioClass(this);
[!endif]
[!if USE_DIRECTPLAY]
         play = new PlayClass(this);
[!endif]
[!if USE_DIRECTINPUT && USE_AUDIO]
        input = new InputClass(this, audio[!if USE_DIRECTPLAY], play[!endif]);
[!endif]
[!if USE_DIRECTINPUT && !USE_AUDIO]
        input = new InputClass(this[!if USE_DIRECTPLAY], play[!endif]);
[!endif]
[!if !USE_DIRECTINPUT]
        this.KeyDown += new KeyEventHandler(this.OnPrivateKeyDown);
        this.KeyUp += new KeyEventHandler(this.OnPrivateKeyUp);
[!endif]
        drawingFont = new D3DXFont( "Arial", System.Drawing.FontStyle.Bold );
[!if GRAPHICSTARGET_PICTUREBOX]

        target = new System.Windows.Forms.PictureBox();
        groupBox1 = new System.Windows.Forms.GroupBox();
        target.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
        target.Location = new System.Drawing.Point(155, 20);
        target.Name = "pictureBox1";
        target.Size = new System.Drawing.Size(220, 260);
        target.TabIndex = 0;
        target.TabStop = false;
        target.Anchor = (AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right);
        groupBox1.Anchor = (AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left);
        groupBox1.Location = new System.Drawing.Point(8, 20);
        groupBox1.Name = "groupBox1";
        groupBox1.Size = new System.Drawing.Size(110, 260);
        groupBox1.TabIndex = 1;
        groupBox1.TabStop = false;
        groupBox1.Text = "Insert Your UI";

        this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                        this.groupBox1,
                                                                        this.target});
        this.RenderTarget = target;
[!endif]
    }

[!if !USE_DIRECTINPUT]
    /// <summary>
    /// Event Handler for windows messages
    /// </summary>
    private void OnPrivateKeyDown(object sender, KeyEventArgs e)
    {
        switch (e.KeyCode)
        {
            case Keys.Up:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgUp);
[!else]
                destination.X = 1;
[!endif]
                break;
            }
            case Keys.Down:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgDown);
[!else]
                destination.X = -1;
[!endif]
                break;
            }
            case Keys.Left:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgLeft);
[!else]
                destination.Y = 1;
[!endif]
                break;
            }
            case Keys.Right:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgRight);
[!else]
                destination.Y = -1;
[!endif]
                break;
            }
[!if USE_AUDIO]
            case Keys.W:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgSound);
[!else]
                audio.PlaySound();
[!endif]
                break;
            }
            case Keys.Q:
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
    }
    private void OnPrivateKeyUp(object sender, KeyEventArgs e)
    {
        switch (e.KeyCode)
        {
            case Keys.Up:
[!if USE_DIRECTPLAY]
            {
                play.WriteMessage(msgCancelUp);
                break;
            }
[!endif]
            case Keys.Down:
[!if USE_DIRECTPLAY]
            {
                play.WriteMessage(msgCancelDown);
                break;
            }
[!endif]
[!if !USE_DIRECTPLAY]
                destination.X = 0;
                break;
[!endif]
            case Keys.Left:
[!if USE_DIRECTPLAY]
            {
                play.WriteMessage(msgCancelLeft);
                break;
            }
[!endif]
            case Keys.Right:
            {
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgCancelRight);
[!endif]
[!if !USE_DIRECTPLAY]                   
                destination.Y = 0;
[!endif]
                break;
            }
        }
    }
[!endif]

    /// <summary>
    /// Called once per frame, the call is the entry point for 3d rendering. This 
    /// function sets up render states, clears the viewport, and renders the scene.
    /// </summary>
    protected override void Render()
    {
[!if USE_DIRECTINPUT && !USE_DIRECTPLAY]]

        destination = input.GetInputState();
[!endif]
[!if USE_DIRECTINPUT && USE_DIRECTPLAY]

        input.GetInputState();
[!endif]

        //Clear the backbuffer to a Blue color 
        device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Blue, 1.0f, 0);
        //Begin the scene
        device.BeginScene();
[!if !USE_DIRECTINPUT && !USE_DIRECTPLAY]
        drawingFont.DrawText(5, 5, Color.White.ToArgb(), "X: " + destination.X + " Y: " + destination.Y);

[!endif]
[!if USE_DIRECTINPUT && USE_DIRECTPLAY]
        drawingFont.DrawText(5, 5, Color.White.ToArgb(), "X: " + destination.X + " Y: " + destination.Y);

[!endif]
        //
        // TODO: Insert application rendering code here.
        //
        device.EndScene();
    }

    /// <summary>
    /// Initialize scene objects.
    /// </summary>
    protected override void InitializeDeviceObjects()
    {
        drawingFont.InitializeDeviceObjects(device);

        //
        // TODO: Insert application device initialization code here.
        //
    }

    /// <summary>
    /// Called when a device needs to be restored.
    /// </summary>
    protected override void RestoreDeviceObjects(System.Object sender, System.EventArgs e)
    {
        //
        // TODO: Insert application device restoration code here.
        //
    }
[!if USE_DIRECTPLAY]
    public void MessageArrived(byte message)
    {
        switch (message)
        {
            case msgUp:
            {
                destination.X = 1;
                break;
            }
            case msgDown:
            {
                destination.X = -1;
                break;
            }
            case msgLeft:
            {
                destination.Y = 1;
                break;
            }
            case msgRight:
            {
                destination.Y = -1;
                break;
            }
            case msgCancelUp:
            case msgCancelDown:
            {
                destination.X = 0;
                break;
            }
            case msgCancelLeft:
            case msgCancelRight:
            {
                destination.Y = 0;
                break;
            }
[!if USE_AUDIO]
            case msgAudio:
            {
                this.BeginInvoke(new AudioDelegate(audio.PlayAudio));
                break;
            }
            case msgSound:
            {
                audio.PlaySound();
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