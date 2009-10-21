namespace SoundStreaming.StreamingServiceHoster
{
    partial class FormMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.numericUpDownBufferLength = new System.Windows.Forms.NumericUpDown();
            this.labelBufferLength = new System.Windows.Forms.Label();
            this.checkBoxAlwaysOnTop = new System.Windows.Forms.CheckBox();
            this.linkLabelCheckService = new System.Windows.Forms.LinkLabel();
            this.textBoxServiceUri = new System.Windows.Forms.TextBox();
            this.labelServiceUri = new System.Windows.Forms.Label();
            this.checkBoxLocalhost = new System.Windows.Forms.CheckBox();
            this.textBoxIpAddress = new System.Windows.Forms.TextBox();
            this.labelIpAddress = new System.Windows.Forms.Label();
            this.groupBoxDiagnostics = new System.Windows.Forms.GroupBox();
            this.progressBarLastReadPosition = new System.Windows.Forms.ProgressBar();
            this.labelLastReadPosition = new System.Windows.Forms.Label();
            this.progressBarBufferPosition = new System.Windows.Forms.ProgressBar();
            this.labelBufferPosition = new System.Windows.Forms.Label();
            this.labelState = new System.Windows.Forms.Label();
            this.buttonStartStopService = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownBufferLength)).BeginInit();
            this.groupBoxDiagnostics.SuspendLayout();
            this.SuspendLayout();
            // 
            // numericUpDownBufferLength
            // 
            this.numericUpDownBufferLength.Location = new System.Drawing.Point(335, 15);
            this.numericUpDownBufferLength.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numericUpDownBufferLength.Minimum = new decimal(new int[] {
            2048,
            0,
            0,
            0});
            this.numericUpDownBufferLength.Name = "numericUpDownBufferLength";
            this.numericUpDownBufferLength.Size = new System.Drawing.Size(83, 20);
            this.numericUpDownBufferLength.TabIndex = 16;
            this.numericUpDownBufferLength.Value = new decimal(new int[] {
            2048,
            0,
            0,
            0});
            this.numericUpDownBufferLength.ValueChanged += new System.EventHandler(this.numericUpDownBufferLength_ValueChanged);
            // 
            // labelBufferLength
            // 
            this.labelBufferLength.AutoSize = true;
            this.labelBufferLength.Location = new System.Drawing.Point(259, 17);
            this.labelBufferLength.Name = "labelBufferLength";
            this.labelBufferLength.Size = new System.Drawing.Size(70, 13);
            this.labelBufferLength.TabIndex = 15;
            this.labelBufferLength.Text = "Buffer length:";
            // 
            // checkBoxAlwaysOnTop
            // 
            this.checkBoxAlwaysOnTop.AutoSize = true;
            this.checkBoxAlwaysOnTop.Location = new System.Drawing.Point(520, 43);
            this.checkBoxAlwaysOnTop.Name = "checkBoxAlwaysOnTop";
            this.checkBoxAlwaysOnTop.Size = new System.Drawing.Size(92, 17);
            this.checkBoxAlwaysOnTop.TabIndex = 22;
            this.checkBoxAlwaysOnTop.Text = "Always on top";
            this.checkBoxAlwaysOnTop.UseVisualStyleBackColor = true;
            this.checkBoxAlwaysOnTop.CheckedChanged += new System.EventHandler(this.checkBoxAlwaysOnTop_CheckedChanged);
            // 
            // linkLabelCheckService
            // 
            this.linkLabelCheckService.AutoSize = true;
            this.linkLabelCheckService.Location = new System.Drawing.Point(437, 44);
            this.linkLabelCheckService.Name = "linkLabelCheckService";
            this.linkLabelCheckService.Size = new System.Drawing.Size(77, 13);
            this.linkLabelCheckService.TabIndex = 21;
            this.linkLabelCheckService.TabStop = true;
            this.linkLabelCheckService.Text = "Check Service";
            this.linkLabelCheckService.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabelCheckService_LinkClicked);
            // 
            // textBoxServiceUri
            // 
            this.textBoxServiceUri.Location = new System.Drawing.Point(86, 41);
            this.textBoxServiceUri.Name = "textBoxServiceUri";
            this.textBoxServiceUri.ReadOnly = true;
            this.textBoxServiceUri.Size = new System.Drawing.Size(345, 20);
            this.textBoxServiceUri.TabIndex = 20;
            // 
            // labelServiceUri
            // 
            this.labelServiceUri.AutoSize = true;
            this.labelServiceUri.Location = new System.Drawing.Point(12, 44);
            this.labelServiceUri.Name = "labelServiceUri";
            this.labelServiceUri.Size = new System.Drawing.Size(68, 13);
            this.labelServiceUri.TabIndex = 19;
            this.labelServiceUri.Text = "Service URI:";
            // 
            // checkBoxLocalhost
            // 
            this.checkBoxLocalhost.AutoSize = true;
            this.checkBoxLocalhost.Location = new System.Drawing.Point(185, 16);
            this.checkBoxLocalhost.Name = "checkBoxLocalhost";
            this.checkBoxLocalhost.Size = new System.Drawing.Size(68, 17);
            this.checkBoxLocalhost.TabIndex = 14;
            this.checkBoxLocalhost.Text = "localhost";
            this.checkBoxLocalhost.UseVisualStyleBackColor = true;
            this.checkBoxLocalhost.CheckedChanged += new System.EventHandler(this.checkBoxLocalhost_CheckedChanged);
            // 
            // textBoxIpAddress
            // 
            this.textBoxIpAddress.Location = new System.Drawing.Point(79, 14);
            this.textBoxIpAddress.Name = "textBoxIpAddress";
            this.textBoxIpAddress.Size = new System.Drawing.Size(100, 20);
            this.textBoxIpAddress.TabIndex = 13;
            this.textBoxIpAddress.Leave += new System.EventHandler(this.textBoxIpAddress_Leave);
            // 
            // labelIpAddress
            // 
            this.labelIpAddress.AutoSize = true;
            this.labelIpAddress.Location = new System.Drawing.Point(12, 17);
            this.labelIpAddress.Name = "labelIpAddress";
            this.labelIpAddress.Size = new System.Drawing.Size(61, 13);
            this.labelIpAddress.TabIndex = 12;
            this.labelIpAddress.Text = "IP Address:";
            // 
            // groupBoxDiagnostics
            // 
            this.groupBoxDiagnostics.Controls.Add(this.progressBarLastReadPosition);
            this.groupBoxDiagnostics.Controls.Add(this.labelLastReadPosition);
            this.groupBoxDiagnostics.Controls.Add(this.progressBarBufferPosition);
            this.groupBoxDiagnostics.Controls.Add(this.labelBufferPosition);
            this.groupBoxDiagnostics.Location = new System.Drawing.Point(12, 67);
            this.groupBoxDiagnostics.Name = "groupBoxDiagnostics";
            this.groupBoxDiagnostics.Size = new System.Drawing.Size(600, 77);
            this.groupBoxDiagnostics.TabIndex = 23;
            this.groupBoxDiagnostics.TabStop = false;
            this.groupBoxDiagnostics.Text = "Diagnostics:";
            // 
            // progressBarLastReadPosition
            // 
            this.progressBarLastReadPosition.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.progressBarLastReadPosition.Location = new System.Drawing.Point(6, 61);
            this.progressBarLastReadPosition.Name = "progressBarLastReadPosition";
            this.progressBarLastReadPosition.Size = new System.Drawing.Size(588, 10);
            this.progressBarLastReadPosition.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBarLastReadPosition.TabIndex = 3;
            // 
            // labelLastReadPosition
            // 
            this.labelLastReadPosition.AutoSize = true;
            this.labelLastReadPosition.Location = new System.Drawing.Point(6, 45);
            this.labelLastReadPosition.Name = "labelLastReadPosition";
            this.labelLastReadPosition.Size = new System.Drawing.Size(119, 13);
            this.labelLastReadPosition.TabIndex = 2;
            this.labelLastReadPosition.Text = "Last read position: 0 / 0";
            // 
            // progressBarBufferPosition
            // 
            this.progressBarBufferPosition.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.progressBarBufferPosition.Location = new System.Drawing.Point(6, 32);
            this.progressBarBufferPosition.Name = "progressBarBufferPosition";
            this.progressBarBufferPosition.Size = new System.Drawing.Size(588, 10);
            this.progressBarBufferPosition.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBarBufferPosition.TabIndex = 1;
            // 
            // labelBufferPosition
            // 
            this.labelBufferPosition.AutoSize = true;
            this.labelBufferPosition.Location = new System.Drawing.Point(6, 16);
            this.labelBufferPosition.Name = "labelBufferPosition";
            this.labelBufferPosition.Size = new System.Drawing.Size(103, 13);
            this.labelBufferPosition.TabIndex = 0;
            this.labelBufferPosition.Text = "Buffer position: 0 / 0";
            // 
            // labelState
            // 
            this.labelState.AutoSize = true;
            this.labelState.ForeColor = System.Drawing.SystemColors.ControlText;
            this.labelState.Location = new System.Drawing.Point(520, 17);
            this.labelState.Name = "labelState";
            this.labelState.Size = new System.Drawing.Size(35, 13);
            this.labelState.TabIndex = 18;
            this.labelState.Text = "State:";
            // 
            // buttonStartStopService
            // 
            this.buttonStartStopService.Location = new System.Drawing.Point(424, 12);
            this.buttonStartStopService.Name = "buttonStartStopService";
            this.buttonStartStopService.Size = new System.Drawing.Size(90, 23);
            this.buttonStartStopService.TabIndex = 17;
            this.buttonStartStopService.UseVisualStyleBackColor = true;
            this.buttonStartStopService.Click += new System.EventHandler(this.buttonStartStopService_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(624, 156);
            this.Controls.Add(this.numericUpDownBufferLength);
            this.Controls.Add(this.labelBufferLength);
            this.Controls.Add(this.checkBoxAlwaysOnTop);
            this.Controls.Add(this.linkLabelCheckService);
            this.Controls.Add(this.textBoxServiceUri);
            this.Controls.Add(this.labelServiceUri);
            this.Controls.Add(this.checkBoxLocalhost);
            this.Controls.Add(this.textBoxIpAddress);
            this.Controls.Add(this.labelIpAddress);
            this.Controls.Add(this.groupBoxDiagnostics);
            this.Controls.Add(this.labelState);
            this.Controls.Add(this.buttonStartStopService);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "FormMain";
            this.Text = "Streaming Service Hoster";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownBufferLength)).EndInit();
            this.groupBoxDiagnostics.ResumeLayout(false);
            this.groupBoxDiagnostics.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown numericUpDownBufferLength;
        private System.Windows.Forms.Label labelBufferLength;
        private System.Windows.Forms.CheckBox checkBoxAlwaysOnTop;
        private System.Windows.Forms.LinkLabel linkLabelCheckService;
        private System.Windows.Forms.TextBox textBoxServiceUri;
        private System.Windows.Forms.Label labelServiceUri;
        private System.Windows.Forms.CheckBox checkBoxLocalhost;
        private System.Windows.Forms.TextBox textBoxIpAddress;
        private System.Windows.Forms.Label labelIpAddress;
        private System.Windows.Forms.GroupBox groupBoxDiagnostics;
        private System.Windows.Forms.ProgressBar progressBarLastReadPosition;
        private System.Windows.Forms.Label labelLastReadPosition;
        private System.Windows.Forms.ProgressBar progressBarBufferPosition;
        private System.Windows.Forms.Label labelBufferPosition;
        private System.Windows.Forms.Label labelState;
        private System.Windows.Forms.Button buttonStartStopService;
    }
}

