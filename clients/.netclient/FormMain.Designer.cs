namespace CloudObserver.Client
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
            this.buttonStartStopCapturing = new System.Windows.Forms.Button();
            this.textBoxControllerServiceUri = new System.Windows.Forms.TextBox();
            this.labelControllerServiceUri = new System.Windows.Forms.Label();
            this.buttonStartStopPlaying = new System.Windows.Forms.Button();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonStartStopCapturing
            // 
            this.buttonStartStopCapturing.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonStartStopCapturing.Enabled = false;
            this.buttonStartStopCapturing.Location = new System.Drawing.Point(12, 41);
            this.buttonStartStopCapturing.Name = "buttonStartStopCapturing";
            this.buttonStartStopCapturing.Size = new System.Drawing.Size(297, 23);
            this.buttonStartStopCapturing.TabIndex = 3;
            this.buttonStartStopCapturing.Text = "Start Capturing";
            this.buttonStartStopCapturing.UseVisualStyleBackColor = true;
            this.buttonStartStopCapturing.Click += new System.EventHandler(this.buttonStartStopCapturing_Click);
            // 
            // textBoxControllerServiceUri
            // 
            this.textBoxControllerServiceUri.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxControllerServiceUri.Location = new System.Drawing.Point(133, 14);
            this.textBoxControllerServiceUri.Name = "textBoxControllerServiceUri";
            this.textBoxControllerServiceUri.Size = new System.Drawing.Size(398, 20);
            this.textBoxControllerServiceUri.TabIndex = 1;
            this.textBoxControllerServiceUri.Text = "http://localhost:9000/ControllerService";
            // 
            // labelControllerServiceUri
            // 
            this.labelControllerServiceUri.AutoSize = true;
            this.labelControllerServiceUri.Location = new System.Drawing.Point(12, 17);
            this.labelControllerServiceUri.Name = "labelControllerServiceUri";
            this.labelControllerServiceUri.Size = new System.Drawing.Size(115, 13);
            this.labelControllerServiceUri.TabIndex = 0;
            this.labelControllerServiceUri.Text = "Controller Service URI:";
            // 
            // buttonStartStopPlaying
            // 
            this.buttonStartStopPlaying.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonStartStopPlaying.Enabled = false;
            this.buttonStartStopPlaying.Location = new System.Drawing.Point(315, 41);
            this.buttonStartStopPlaying.Name = "buttonStartStopPlaying";
            this.buttonStartStopPlaying.Size = new System.Drawing.Size(297, 23);
            this.buttonStartStopPlaying.TabIndex = 4;
            this.buttonStartStopPlaying.Text = "Start Playing";
            this.buttonStartStopPlaying.UseVisualStyleBackColor = true;
            this.buttonStartStopPlaying.Click += new System.EventHandler(this.buttonStartStopPlaying_Click);
            // 
            // buttonConnect
            // 
            this.buttonConnect.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonConnect.Location = new System.Drawing.Point(537, 12);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 2;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(624, 76);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.buttonStartStopPlaying);
            this.Controls.Add(this.textBoxControllerServiceUri);
            this.Controls.Add(this.labelControllerServiceUri);
            this.Controls.Add(this.buttonStartStopCapturing);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormMain";
            this.Text = "Cloud Observer Client (sound only)";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonStartStopCapturing;
        private System.Windows.Forms.TextBox textBoxControllerServiceUri;
        private System.Windows.Forms.Label labelControllerServiceUri;
        private System.Windows.Forms.Button buttonStartStopPlaying;
        private System.Windows.Forms.Button buttonConnect;
    }
}

