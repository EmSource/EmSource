using System;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.DirectInput;

/// <summary>
/// This class is where the DirectInput routines
/// for the application resides.
/// </summary>
public class InputClass
{

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

[!if USE_DIRECTPLAY]
    private bool pressedUp = false;
    private bool pressedDown = false;
    private bool pressedLeft = false;
    private bool pressedRight = false;
[!endif]

    private Control owner = null;
    private Device localDevice = null;
[!if USE_AUDIO]
    private AudioClass audio = null;
[!endif]
[!if USE_DIRECTPLAY]
    private PlayClass play = null;
[!endif]

    public InputClass(Control owner[!if USE_AUDIO], AudioClass audio[!endif][!if USE_DIRECTPLAY], PlayClass play[!endif])
    {
        this.owner = owner;
[!if USE_AUDIO]
        this.audio = audio;
[!endif]
[!if USE_DIRECTPLAY]
        this.play = play;
[!endif]

        localDevice = new Device(SystemGuid.Keyboard);
        localDevice.SetDataFormat(DeviceDataFormat.Keyboard);
        localDevice.SetCooperativeLevel(owner, CooperativeLevelFlags.Foreground | CooperativeLevelFlags.NonExclusive);         
    }
    
    public Point GetInputState()
    {
        KeyboardState state = null;
        Point p = new Point(0);

        try
        {
            state = localDevice.GetCurrentKeyboardState();
        }
        catch(InputException)
        {
            do
            {
                Application.DoEvents();
                try{ localDevice.Acquire(); }
                catch (InputLostException)
                { continue; }
                catch(OtherApplicationHasPriorityException)
                { continue; }

                break;

            }while( true );
        }

        if(null == state)
            return p;

        if(state[Key.Down]) 
        {
[!if USE_DIRECTPLAY]
            pressedDown = true;
            play.WriteMessage(msgDown);
[!else]
            [!if GRAPHICSTYPE_DIRECT3D]p.X = -1;[!endif]
            [!if !GRAPHICSTYPE_DIRECT3D]p.Y = 1;[!endif]
[!endif]
        }
[!if USE_DIRECTPLAY]
        else if (pressedDown == true)
        {
            pressedDown = false;
            play.WriteMessage(msgCancelDown);
        }
[!endif]                
        if(state[Key.Up])
        {
[!if USE_DIRECTPLAY]
            pressedUp = true;
            play.WriteMessage(msgUp);
[!else]
            [!if GRAPHICSTYPE_DIRECT3D]p.X = 1;[!endif]
            [!if !GRAPHICSTYPE_DIRECT3D]p.Y = -1;[!endif]
[!endif]
        }
[!if USE_DIRECTPLAY]
        else if (pressedUp == true)
        {
            pressedUp = false;
            play.WriteMessage(msgCancelUp);
        }
[!endif]
        if(state[Key.Left]) 
        {
[!if USE_DIRECTPLAY]
            pressedLeft = true;
            play.WriteMessage(msgLeft);
[!else]
            [!if GRAPHICSTYPE_DIRECT3D]p.Y = 1;[!endif]
            [!if !GRAPHICSTYPE_DIRECT3D]p.X = -1;[!endif]               
[!endif]
        }
[!if USE_DIRECTPLAY]
        else if (pressedLeft == true)
        {
            pressedLeft = false;
            play.WriteMessage(msgCancelLeft);
        }
[!endif]
        if(state[Key.Right]) 
        {
[!if USE_DIRECTPLAY]
            pressedRight  = true;
            play.WriteMessage(msgRight);
[!else]
            [!if GRAPHICSTYPE_DIRECT3D]p.Y = -1;[!endif]
            [!if !GRAPHICSTYPE_DIRECT3D]p.X = 1;[!endif]                
[!endif]
        }
[!if USE_DIRECTPLAY]
        else if (pressedRight == true)
        {
            pressedRight = false;
            play.WriteMessage(msgCancelRight);
        }
[!endif]
[!if USE_AUDIO]
        if(state[Key.Q]) 
        {
[!if USE_DIRECTPLAY]
            play.WriteMessage(msgSound);
[!else]
            audio.PlaySound();
[!endif]
        }

        if(state[Key.W])
        {
[!if USE_DIRECTPLAY]
            play.WriteMessage(msgAudio);
[!else]
            audio.PlayAudio();
[!endif]
        }
[!endif]

        return p;
    }
}