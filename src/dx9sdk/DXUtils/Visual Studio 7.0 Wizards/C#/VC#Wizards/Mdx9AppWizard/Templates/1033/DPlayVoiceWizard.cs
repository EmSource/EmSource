//----------------------------------------------------------------------------
// File: VoiceConnect.cs
//
// Desc: The main file for VoiceConnect that shows how use DirectPlay along 
//       with DirectPlayVoice to allow talking in a conference situation.
//
// Copyright (c) Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
using System;
using Microsoft.DirectX;
using Voice = Microsoft.DirectX.DirectPlay.Voice;
using Microsoft.DirectX.DirectPlay;
using Microsoft.DirectX.DirectSound;
using System.Windows.Forms;
using System.Collections;




/// <summary>
/// Summary description for NetVoice.
/// </summary>
public class VoiceWizard
{
    private Voice.Client client;
    private Voice.Server server;
    private DPlayVoiceConfigForm mConfigForm;
    private Voice.ClientConfig mClientConfig;
    private bool mHalfDuplex, mInSession, mIsHost;


    

    public VoiceWizard()
    {
        mClientConfig = new Voice.ClientConfig();
        mClientConfig.BufferAggressiveness = Voice.BufferAggressiveness.Default;
        mClientConfig.BufferQuality = Voice.BufferQuality.Default;
        mClientConfig.Flags = Voice.ClientConfigFlags.AutoVoiceActivated | Voice.ClientConfigFlags.AutoRecordVolume;
        mClientConfig.Threshold = Voice.Threshold.Default;
        mClientConfig.NotifyPeriod = 0;
        mClientConfig.PlaybackVolume = (int) Voice.PlaybackVolume.Default;
        mClientConfig.RecordVolume = (int) Voice.RecordVolume.Last;

        mConfigForm = new DPlayVoiceConfigForm();
        mInSession = false;
        mIsHost = false;
    }




    public bool HalfDuplex
    {
        get 
        {
            return mHalfDuplex;
        }
    }
    
    
    
    
    public bool IsHost
    {
        get 
        {
            return mIsHost;
        }
    }
    
    
    
    
    public bool InSession
    {
        get 
        {
            return mInSession;
        }
    }
    
    
    
    
    public void InitVoiceClient(Peer dpp, Voice.Client dpvc, Form wnd)
    {
        try
        {
            TestAudioSetup(wnd);
    	
            //Audio Setup was successful, open the configuration form	
            mConfigForm.ShowDialog(mClientConfig, false);

            mClientConfig = mConfigForm.ClientConfig;
            client = dpvc;

            //connect to the voice session
            ConnectToVoiceSession(dpp, wnd);
        }
        catch(Exception e)
        {
            MessageBox.Show("Error attempting to connect to a Voice Server.  This sample will now exit.", "Exiting", MessageBoxButtons.OK, MessageBoxIcon.Information);
            throw e;
        }
    }
    
    
    

    public void InitVoiceHost(Peer host, Voice.Server dpvs, Voice.Client dpvc, Form wnd)
    {
        try
        {

            server = dpvs;
            client = dpvc;

            TestAudioSetup(wnd);

            //Audio Setup was successful, open the configuration form	
            mConfigForm.ShowDialog(mClientConfig, dpvs.CompressionTypes, false);
            if (mConfigForm.DialogResult == DialogResult.Cancel)
                throw new Exception("Voice configuration cancelled");

            mClientConfig = mConfigForm.ClientConfig;

            //create the voice session
            CreateVoiceSession(host, Voice.SessionType.Peer, mConfigForm.CompressionGuid);

            //Connect to the voice session
            ConnectToVoiceSession(host, wnd);
        }
        catch(Exception e)
        {
            MessageBox.Show("Error attempting to start Voice Server Session.  This sample will now exit.", "Exiting", MessageBoxButtons.OK, MessageBoxIcon.Information);
            throw e;
        }
    }
    
    
    

    public void ShowClientSetupDialog(IntPtr hWnd)
    {
        try
        {
            using(mConfigForm = new DPlayVoiceConfigForm())
            {
                mConfigForm.ShowDialog(mClientConfig, mInSession);
                mClientConfig = mConfigForm.ClientConfig;
                client.ClientConfig = mClientConfig;
            }
        }
        catch(Exception e)
        {
            throw e;
        }
    }
    
    
    

    public void ChangeVoiceClientSettings(Voice.ClientConfig config)
    {
        try
        {
            client.ClientConfig = config;
        }
        catch(Exception e)
        {
            throw e;
        }

    }
    
    
    

    public void HostMigrate(Voice.Server dpvs)
    {
        server = dpvs;
        mIsHost = true;
    }




    protected void CreateVoiceSession(Peer dpp, Voice.SessionType type, Guid compressionType)
    {
        try
        {
            //set up session description for the voice server
            Voice.SessionDescription sessionDesc = new Voice.SessionDescription();
            sessionDesc.BufferAggressiveness = Voice.BufferAggressiveness.Default;
            sessionDesc.BufferQuality = Voice.BufferQuality.Default;
            sessionDesc.Flags = 0;
            sessionDesc.SessionType = type;
            sessionDesc.GuidCompressionType = compressionType;

            //start the session
            try 
            {
                server.StartSession(sessionDesc);
                mIsHost = true;
                mInSession = true;
            }
            catch(DirectXException dxe)
            {
                throw dxe;
            }
        }
        catch(Exception e)
        {
            throw e;
        }
    }
    
    
    

    protected void TestAudioSetup(Form wnd)
    {
        try 
        {

            Voice.Test test = new Voice.Test();
            try
            {
                test.CheckAudioSetup(DSoundHelper.DefaultPlaybackDevice, DSoundHelper.DefaultCaptureDevice, wnd, Voice.TestFlags.QueryOnly);
            }
            catch(DirectXException)
            {
                try
                {
                    test.CheckAudioSetup(DSoundHelper.DefaultPlaybackDevice, DSoundHelper.DefaultCaptureDevice, wnd, Voice.TestFlags.AllowBack);
                }
                catch(DirectXException dxeUser)
                {
                    throw dxeUser;
                }
            }

        }
        catch(Exception e)
        {
            throw e;
        }
    }




    protected void ConnectToVoiceSession(Peer dpp, Form wnd)
    {
        try 
        {
            Voice.SoundDeviceConfig soundConfig = new Voice.SoundDeviceConfig();

            //Set sound config to defaults
            soundConfig.GuidPlaybackDevice  = DSoundHelper.DefaultVoicePlaybackDevice; 
            soundConfig.GuidCaptureDevice = DSoundHelper.DefaultVoiceCaptureDevice; 
            soundConfig.Window = wnd;
    		
            //TODO: add error message for specific failures?
    		
            //Connect to voice session
            client.Connect(soundConfig, mClientConfig, Voice.VoiceFlags.Sync);

            //set state
            mInSession = true;

            //set transmit targets to all players
            int[] xmitTargets = new int[1];
            xmitTargets[0] = (int) PlayerID.AllPlayers;
            client.TransmitTargets = xmitTargets;

            //get sound device config to check for half-duplex
            soundConfig = client.SoundDeviceConfig;
            mHalfDuplex =  ((soundConfig.Flags &  Voice.SoundConfigFlags.HalfDuplex) != 0);

        }
        catch(Exception e)
        {
            throw e;
        }
    }
}




/// <summary>
/// Summary description for DPlayVoiceConfigForm.
/// </summary>
public class DPlayVoiceConfigForm : System.Windows.Forms.Form
{
    private System.Windows.Forms.GroupBox groupBoxPlaybackVolume;
    private System.Windows.Forms.GroupBox groupBoxClient;
    private System.Windows.Forms.GroupBox groupBoxRecordVolume;
    private System.Windows.Forms.GroupBox groupBoxThreshold;
    private System.Windows.Forms.GroupBox groupBox2;
    private System.Windows.Forms.ComboBox CompressionTypeComboBox;
    private System.Windows.Forms.RadioButton radioButtonPlaybackDefault;
    private System.Windows.Forms.RadioButton radioButtonPlaybackSet;
    private System.Windows.Forms.TrackBar trackBarPlaybackVolume;
    private System.Windows.Forms.RadioButton radioButtonRecordVolumeSet;
    private System.Windows.Forms.RadioButton radioButtonRecordVolumeAuto;

    /// <summary>
    /// Application Specific members
    /// </summary>
    private Guid mSelectedCompressionGuid;
    private System.Windows.Forms.RadioButton radioButtonThresholdAuto;
    private System.Windows.Forms.RadioButton radioButtonThresholdSet;
    private System.Windows.Forms.RadioButton radioButtonThresholdDefault;
    private System.Windows.Forms.TrackBar trackBarThreshold;
    private System.Windows.Forms.TrackBar trackBarRecordVolume;
    private System.Windows.Forms.GroupBox groupBoxServer;
    
    private Voice.ClientConfig mConfig;
    private Voice.CompressionInformation[] mCompressionInfo;
    private System.Windows.Forms.Button buttonOK;
    private System.Windows.Forms.Button buttonCancel;

    private bool mIsHost;
    private System.Windows.Forms.RadioButton radioButtonRecordVolumeDefault;
    private bool mInSession;




    public Guid CompressionGuid
    {
        get 
        {
            return mSelectedCompressionGuid;
        }
    }
    
    
    

    public Voice.ClientConfig ClientConfig
    {
        get 
        {
            return mConfig;
        }
    }




    public DialogResult ShowDialog(Voice.ClientConfig config, bool inSession)
    {
        mConfig = config;
        mCompressionInfo = null;
        mIsHost = false;
        mInSession = inSession;
        UpdateControls();
        return this.ShowDialog();
    }
    
    
    
    
    public DialogResult ShowDialog(Voice.ClientConfig config, Voice.CompressionInformation[] cInfo, bool inSession)
    {
        mConfig = config;
        mCompressionInfo = cInfo;
        mIsHost = true;
        mInSession = inSession;
        UpdateControls();
        return this.ShowDialog();
    }




    public DPlayVoiceConfigForm()
    {
        InitializeComponent();
    }




    private void UpdateControls()
    {
        if (mConfig.PlaybackVolume == (int) Voice.PlaybackVolume.Default)
        {
            radioButtonPlaybackDefault.Checked = true;
        }
        else
        {
            radioButtonPlaybackSet.Checked = true;
            trackBarPlaybackVolume.Value = (int) ((mConfig.PlaybackVolume - (int) Volume.Min)
                * 100.0f / (Volume.Max-Volume.Min));
        }

        // Set the record controls
        if ((mConfig.Flags & Voice.ClientConfigFlags.AutoRecordVolume) != 0)
        {
            radioButtonRecordVolumeAuto.Checked = true;
        }
        else if (mConfig.RecordVolume == (int) Voice.PlaybackVolume.Default)
        {
            radioButtonRecordVolumeDefault.Checked = true;
        }
        else
        {
            radioButtonRecordVolumeSet.Checked = true;
            trackBarRecordVolume.Value = (int) ((mConfig.RecordVolume - (int) Volume.Min)
                * 100.0f / (Volume.Max-Volume.Min));
        }

        // Set the threshold controls
        if ((mConfig.Flags & Voice.ClientConfigFlags.AutoVoiceActivated) != 0)
        {
            radioButtonThresholdAuto.Checked = true;
        }
        else if (mConfig.Threshold == Voice.Threshold.Default)
        {
            radioButtonThresholdDefault.Checked = true;
        }
        else
        {
            radioButtonThresholdSet.Checked = true;
            trackBarThreshold.Value = (int) (((int) mConfig.Threshold - (int) Voice.Threshold.Min)
                * 100.0f / ((int) Voice.Threshold.Max - (int) Voice.Threshold.Min));
        }

        if (mIsHost && !mInSession)
        {
            foreach (Voice.CompressionInformation ci in mCompressionInfo)
            {
                CompressionTypeComboBox.Items.Add(ci.Name);
                if (ci.GuidType == Voice.CompressionGuid.Default) CompressionTypeComboBox.SelectedIndex = CompressionTypeComboBox.Items.Count - 1;
            }
    		
            mSelectedCompressionGuid = mCompressionInfo[0].GuidType;
    		
        }
        else
        {
            //We are are either not the host player or we are in session
            //so we disable all the server only options
            CompressionTypeComboBox.Enabled = false;
            groupBoxServer.Enabled = false;
        }
   }




	#region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        this.groupBoxPlaybackVolume = new System.Windows.Forms.GroupBox();
        this.trackBarPlaybackVolume = new System.Windows.Forms.TrackBar();
        this.radioButtonPlaybackSet = new System.Windows.Forms.RadioButton();
        this.radioButtonPlaybackDefault = new System.Windows.Forms.RadioButton();
        this.groupBoxClient = new System.Windows.Forms.GroupBox();
        this.groupBoxThreshold = new System.Windows.Forms.GroupBox();
        this.radioButtonThresholdAuto = new System.Windows.Forms.RadioButton();
        this.trackBarThreshold = new System.Windows.Forms.TrackBar();
        this.radioButtonThresholdSet = new System.Windows.Forms.RadioButton();
        this.radioButtonThresholdDefault = new System.Windows.Forms.RadioButton();
        this.groupBoxRecordVolume = new System.Windows.Forms.GroupBox();
        this.radioButtonRecordVolumeAuto = new System.Windows.Forms.RadioButton();
        this.trackBarRecordVolume = new System.Windows.Forms.TrackBar();
        this.radioButtonRecordVolumeSet = new System.Windows.Forms.RadioButton();
        this.radioButtonRecordVolumeDefault = new System.Windows.Forms.RadioButton();
        this.groupBoxServer = new System.Windows.Forms.GroupBox();
        this.groupBox2 = new System.Windows.Forms.GroupBox();
        this.CompressionTypeComboBox = new System.Windows.Forms.ComboBox();
        this.buttonOK = new System.Windows.Forms.Button();
        this.buttonCancel = new System.Windows.Forms.Button();
        this.groupBoxPlaybackVolume.SuspendLayout();
        ((System.ComponentModel.ISupportInitialize)(this.trackBarPlaybackVolume)).BeginInit();
        this.groupBoxClient.SuspendLayout();
        this.groupBoxThreshold.SuspendLayout();
        ((System.ComponentModel.ISupportInitialize)(this.trackBarThreshold)).BeginInit();
        this.groupBoxRecordVolume.SuspendLayout();
        ((System.ComponentModel.ISupportInitialize)(this.trackBarRecordVolume)).BeginInit();
        this.groupBoxServer.SuspendLayout();
        this.groupBox2.SuspendLayout();
        this.SuspendLayout();
        // 
        // groupBoxPlaybackVolume
        // 
        this.groupBoxPlaybackVolume.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                             this.trackBarPlaybackVolume,
                                                                                             this.radioButtonPlaybackSet,
                                                                                             this.radioButtonPlaybackDefault});
        this.groupBoxPlaybackVolume.Location = new System.Drawing.Point(8, 16);
        this.groupBoxPlaybackVolume.Name = "groupBoxPlaybackVolume";
        this.groupBoxPlaybackVolume.Size = new System.Drawing.Size(184, 100);
        this.groupBoxPlaybackVolume.TabIndex = 0;
        this.groupBoxPlaybackVolume.TabStop = false;
        this.groupBoxPlaybackVolume.Text = "Playback Volume";
        // 
        // trackBarPlaybackVolume
        // 
        this.trackBarPlaybackVolume.LargeChange = 25;
        this.trackBarPlaybackVolume.Location = new System.Drawing.Point(8, 48);
        this.trackBarPlaybackVolume.Maximum = 99;
        this.trackBarPlaybackVolume.Name = "trackBarPlaybackVolume";
        this.trackBarPlaybackVolume.Size = new System.Drawing.Size(168, 45);
        this.trackBarPlaybackVolume.TabIndex = 2;
        this.trackBarPlaybackVolume.TickFrequency = 5;
        this.trackBarPlaybackVolume.Scroll += new System.EventHandler(this.trackBarPlaybackVolume_Scroll);
        // 
        // radioButtonPlaybackSet
        // 
        this.radioButtonPlaybackSet.Location = new System.Drawing.Point(88, 18);
        this.radioButtonPlaybackSet.Name = "radioButtonPlaybackSet";
        this.radioButtonPlaybackSet.Size = new System.Drawing.Size(56, 16);
        this.radioButtonPlaybackSet.TabIndex = 1;
        this.radioButtonPlaybackSet.Text = "Set";
        // 
        // radioButtonPlaybackDefault
        // 
        this.radioButtonPlaybackDefault.Location = new System.Drawing.Point(16, 16);
        this.radioButtonPlaybackDefault.Name = "radioButtonPlaybackDefault";
        this.radioButtonPlaybackDefault.Size = new System.Drawing.Size(64, 20);
        this.radioButtonPlaybackDefault.TabIndex = 0;
        this.radioButtonPlaybackDefault.Text = "Default";
        // 
        // groupBoxClient
        // 
        this.groupBoxClient.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                     this.groupBoxThreshold,
                                                                                     this.groupBoxRecordVolume,
                                                                                     this.groupBoxPlaybackVolume});
        this.groupBoxClient.Location = new System.Drawing.Point(8, 8);
        this.groupBoxClient.Name = "groupBoxClient";
        this.groupBoxClient.Size = new System.Drawing.Size(584, 128);
        this.groupBoxClient.TabIndex = 1;
        this.groupBoxClient.TabStop = false;
        this.groupBoxClient.Text = "Client Options (adjust any time)";
        // 
        // groupBoxThreshold
        // 
        this.groupBoxThreshold.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                        this.radioButtonThresholdAuto,
                                                                                        this.trackBarThreshold,
                                                                                        this.radioButtonThresholdSet,
                                                                                        this.radioButtonThresholdDefault});
        this.groupBoxThreshold.Location = new System.Drawing.Point(392, 16);
        this.groupBoxThreshold.Name = "groupBoxThreshold";
        this.groupBoxThreshold.Size = new System.Drawing.Size(184, 100);
        this.groupBoxThreshold.TabIndex = 2;
        this.groupBoxThreshold.TabStop = false;
        this.groupBoxThreshold.Text = "Threshold";
        // 
        // radioButtonThresholdAuto
        // 
        this.radioButtonThresholdAuto.Location = new System.Drawing.Point(72, 14);
        this.radioButtonThresholdAuto.Name = "radioButtonThresholdAuto";
        this.radioButtonThresholdAuto.Size = new System.Drawing.Size(48, 24);
        this.radioButtonThresholdAuto.TabIndex = 13;
        this.radioButtonThresholdAuto.Text = "Auto";
        // 
        // trackBarThreshold
        // 
        this.trackBarThreshold.LargeChange = 25;
        this.trackBarThreshold.Location = new System.Drawing.Point(8, 48);
        this.trackBarThreshold.Maximum = 99;
        this.trackBarThreshold.Name = "trackBarThreshold";
        this.trackBarThreshold.Size = new System.Drawing.Size(168, 45);
        this.trackBarThreshold.TabIndex = 12;
        this.trackBarThreshold.TickFrequency = 5;
        this.trackBarThreshold.Scroll += new System.EventHandler(this.trackBarThreshold_Scroll);
        // 
        // radioButtonThresholdSet
        // 
        this.radioButtonThresholdSet.Location = new System.Drawing.Point(128, 18);
        this.radioButtonThresholdSet.Name = "radioButtonThresholdSet";
        this.radioButtonThresholdSet.Size = new System.Drawing.Size(40, 16);
        this.radioButtonThresholdSet.TabIndex = 11;
        this.radioButtonThresholdSet.Text = "Set";
        // 
        // radioButtonThresholdDefault
        // 
        this.radioButtonThresholdDefault.Location = new System.Drawing.Point(8, 16);
        this.radioButtonThresholdDefault.Name = "radioButtonThresholdDefault";
        this.radioButtonThresholdDefault.Size = new System.Drawing.Size(64, 20);
        this.radioButtonThresholdDefault.TabIndex = 10;
        this.radioButtonThresholdDefault.Text = "Default";
        // 
        // groupBoxRecordVolume
        // 
        this.groupBoxRecordVolume.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                           this.radioButtonRecordVolumeAuto,
                                                                                           this.trackBarRecordVolume,
                                                                                           this.radioButtonRecordVolumeSet,
                                                                                           this.radioButtonRecordVolumeDefault});
        this.groupBoxRecordVolume.Location = new System.Drawing.Point(200, 16);
        this.groupBoxRecordVolume.Name = "groupBoxRecordVolume";
        this.groupBoxRecordVolume.Size = new System.Drawing.Size(184, 100);
        this.groupBoxRecordVolume.TabIndex = 1;
        this.groupBoxRecordVolume.TabStop = false;
        this.groupBoxRecordVolume.Text = "Record Volume";
        // 
        // radioButtonRecordVolumeAuto
        // 
        this.radioButtonRecordVolumeAuto.Location = new System.Drawing.Point(72, 14);
        this.radioButtonRecordVolumeAuto.Name = "radioButtonRecordVolumeAuto";
        this.radioButtonRecordVolumeAuto.Size = new System.Drawing.Size(48, 24);
        this.radioButtonRecordVolumeAuto.TabIndex = 9;
        this.radioButtonRecordVolumeAuto.Text = "Auto";
        // 
        // trackBarRecordVolume
        // 
        this.trackBarRecordVolume.LargeChange = 25;
        this.trackBarRecordVolume.Location = new System.Drawing.Point(8, 48);
        this.trackBarRecordVolume.Maximum = 99;
        this.trackBarRecordVolume.Name = "trackBarRecordVolume";
        this.trackBarRecordVolume.Size = new System.Drawing.Size(168, 45);
        this.trackBarRecordVolume.TabIndex = 8;
        this.trackBarRecordVolume.TickFrequency = 5;
        this.trackBarRecordVolume.Scroll += new System.EventHandler(this.trackBarRecordVolume_Scroll);
        // 
        // radioButtonRecordVolumeSet
        // 
        this.radioButtonRecordVolumeSet.Location = new System.Drawing.Point(128, 18);
        this.radioButtonRecordVolumeSet.Name = "radioButtonRecordVolumeSet";
        this.radioButtonRecordVolumeSet.Size = new System.Drawing.Size(40, 16);
        this.radioButtonRecordVolumeSet.TabIndex = 7;
        this.radioButtonRecordVolumeSet.Text = "Set";
        // 
        // radioButtonRecordVolumeDefault
        // 
        this.radioButtonRecordVolumeDefault.Location = new System.Drawing.Point(8, 16);
        this.radioButtonRecordVolumeDefault.Name = "radioButtonRecordVolumeDefault";
        this.radioButtonRecordVolumeDefault.Size = new System.Drawing.Size(64, 20);
        this.radioButtonRecordVolumeDefault.TabIndex = 6;
        this.radioButtonRecordVolumeDefault.Text = "Default";
        // 
        // groupBoxServer
        // 
        this.groupBoxServer.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                     this.groupBox2});
        this.groupBoxServer.Location = new System.Drawing.Point(8, 144);
        this.groupBoxServer.Name = "groupBoxServer";
        this.groupBoxServer.Size = new System.Drawing.Size(584, 80);
        this.groupBoxServer.TabIndex = 2;
        this.groupBoxServer.TabStop = false;
        this.groupBoxServer.Text = "Server Options (set only when creating a new session)";
        // 
        // groupBox2
        // 
        this.groupBox2.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                this.CompressionTypeComboBox});
        this.groupBox2.Location = new System.Drawing.Point(8, 24);
        this.groupBox2.Name = "groupBox2";
        this.groupBox2.Size = new System.Drawing.Size(568, 48);
        this.groupBox2.TabIndex = 0;
        this.groupBox2.TabStop = false;
        this.groupBox2.Text = "Compression Type";
        // 
        // CompressionTypeComboBox
        // 
        this.CompressionTypeComboBox.Location = new System.Drawing.Point(16, 16);
        this.CompressionTypeComboBox.Name = "CompressionTypeComboBox";
        this.CompressionTypeComboBox.Size = new System.Drawing.Size(544, 21);
        this.CompressionTypeComboBox.TabIndex = 0;
        // 
        // buttonOK
        // 
        this.buttonOK.Location = new System.Drawing.Point(432, 240);
        this.buttonOK.Name = "buttonOK";
        this.buttonOK.TabIndex = 3;
        this.buttonOK.Text = "OK";
        this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
        // 
        // buttonCancel
        // 
        this.buttonCancel.Location = new System.Drawing.Point(517, 240);
        this.buttonCancel.Name = "buttonCancel";
        this.buttonCancel.TabIndex = 4;
        this.buttonCancel.Text = "Cancel";
        this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
        // 
        // DPlayVoiceConfigForm
        // 
        this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
        this.ClientSize = new System.Drawing.Size(600, 272);
        this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                      this.buttonCancel,
                                                                      this.buttonOK,
                                                                      this.groupBoxServer,
                                                                      this.groupBoxClient});
        this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
        this.Name = "DPlayVoiceConfigForm";
        this.Text = "DirectPlayVoice Configuration";
        this.groupBoxPlaybackVolume.ResumeLayout(false);
        ((System.ComponentModel.ISupportInitialize)(this.trackBarPlaybackVolume)).EndInit();
        this.groupBoxClient.ResumeLayout(false);
        this.groupBoxThreshold.ResumeLayout(false);
        ((System.ComponentModel.ISupportInitialize)(this.trackBarThreshold)).EndInit();
        this.groupBoxRecordVolume.ResumeLayout(false);
        ((System.ComponentModel.ISupportInitialize)(this.trackBarRecordVolume)).EndInit();
        this.groupBoxServer.ResumeLayout(false);
        this.groupBox2.ResumeLayout(false);
        this.ResumeLayout(false);

    }
	#endregion




    private void buttonOK_Click(object sender, System.EventArgs e)
    {

        //clear the config
        mConfig = new Voice.ClientConfig();

        mConfig.Flags = 0;

        // Set playback parameters
        if (radioButtonPlaybackDefault.Checked)
        {
            mConfig.PlaybackVolume = (int) Voice.PlaybackVolume.Default;
        }
        else 
        {
            mConfig.PlaybackVolume = (int) Volume.Min + (int) ((trackBarPlaybackVolume.Value / 100.0f) * 
                (Volume.Max-Volume.Min));
        }

        // Set recording parameters
        if (radioButtonRecordVolumeAuto.Checked)
        {
            mConfig.RecordVolume = 0;
            mConfig.Flags |= Voice.ClientConfigFlags.AutoRecordVolume;
        }
        else if (radioButtonRecordVolumeDefault.Checked)
        {
            mConfig.RecordVolume = (int) Voice.PlaybackVolume.Default;
        }
        else 
        {
            mConfig.RecordVolume = (int) Volume.Min + (int) ((trackBarRecordVolume.Value / 100.0f) * 
                (Volume.Max-Volume.Min));
        }

        // Set threshold parameters
        if (radioButtonThresholdAuto.Checked)
        {
            mConfig.Threshold = Voice.Threshold.Unused;
            mConfig.Flags |= Voice.ClientConfigFlags.AutoVoiceActivated;
        }
        else if (radioButtonThresholdDefault.Checked)
        {
            mConfig.Threshold = Voice.Threshold.Default;
            mConfig.Flags |= Voice.ClientConfigFlags.ManualVoiceActivated;
        }
        else 
        {
            mConfig.Threshold = (Voice.Threshold) ((int) Voice.Threshold.Min + (trackBarThreshold.Value / 100.0f * 
                ((int) Voice.Threshold.Max - (int) Voice.Threshold.Min)));
            mConfig.Flags |= Voice.ClientConfigFlags.ManualVoiceActivated;
        }

        //Can only be set at the beginning, when the host is not in a session
        if (mIsHost && !mInSession)
        {
            mSelectedCompressionGuid = mCompressionInfo[CompressionTypeComboBox.SelectedIndex].GuidType; 
        }

        this.DialogResult = DialogResult.OK;
        this.Hide();
    }




    private void trackBarPlaybackVolume_Scroll(object sender, System.EventArgs e)
    {
        radioButtonPlaybackSet.Checked = true;
    }




    private void trackBarRecordVolume_Scroll(object sender, System.EventArgs e)
    {
        radioButtonRecordVolumeSet.Checked = true;
    }
    
    
    

    private void trackBarThreshold_Scroll(object sender, System.EventArgs e)
    {
        radioButtonThresholdSet.Checked = true;
    }
    

    
    
    private void buttonCancel_Click(object sender, System.EventArgs e)
    {
        this.DialogResult = DialogResult.Cancel;
        this.Hide();
    }

}
