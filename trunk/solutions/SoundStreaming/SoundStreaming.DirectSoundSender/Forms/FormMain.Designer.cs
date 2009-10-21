namespace SoundStreaming.DirectSoundSender
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
            this.checkBoxAddNoise = new System.Windows.Forms.CheckBox();
            this.textBoxServiceUri = new System.Windows.Forms.TextBox();
            this.labelServiceUri = new System.Windows.Forms.Label();
            this.buttonStartStopCapture = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // checkBoxAddNoise
            // 
            this.checkBoxAddNoise.AutoSize = true;
            this.checkBoxAddNoise.Location = new System.Drawing.Point(257, 44);
            this.checkBoxAddNoise.Name = "checkBoxAddNoise";
            this.checkBoxAddNoise.Size = new System.Drawing.Size(75, 17);
            this.checkBoxAddNoise.TabIndex = 9;
            this.checkBoxAddNoise.Text = "Add Noise";
            this.checkBoxAddNoise.UseVisualStyleBackColor = true;
            this.checkBoxAddNoise.CheckedChanged += new System.EventHandler(this.checkBoxAddNoise_CheckedChanged);
            // 
            // textBoxServiceUri
            // 
            this.textBoxServiceUri.Location = new System.Drawing.Point(88, 14);
            this.textBoxServiceUri.Name = "textBoxServiceUri";
            this.textBoxServiceUri.Size = new System.Drawing.Size(244, 20);
            this.textBoxServiceUri.TabIndex = 6;
            this.textBoxServiceUri.Text = "http://127.0.0.1:9000/StreamingService";
            this.textBoxServiceUri.TextChanged += new System.EventHandler(this.textBoxServiceUri_TextChanged);
            // 
            // labelServiceUri
            // 
            this.labelServiceUri.AutoSize = true;
            this.labelServiceUri.Location = new System.Drawing.Point(12, 17);
            this.labelServiceUri.Name = "labelServiceUri";
            this.labelServiceUri.Size = new System.Drawing.Size(68, 13);
            this.labelServiceUri.TabIndex = 5;
            this.labelServiceUri.Text = "Service URI:";
            // 
            // buttonStartStopCapture
            // 
            this.buttonStartStopCapture.Location = new System.Drawing.Point(12, 40);
            this.buttonStartStopCapture.Name = "buttonStartStopCapture";
            this.buttonStartStopCapture.Size = new System.Drawing.Size(239, 23);
            this.buttonStartStopCapture.TabIndex = 8;
            this.buttonStartStopCapture.Text = "Start Capture";
            this.buttonStartStopCapture.UseVisualStyleBackColor = true;
            this.buttonStartStopCapture.Click += new System.EventHandler(this.buttonStartStopCapture_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(344, 75);
            this.Controls.Add(this.checkBoxAddNoise);
            this.Controls.Add(this.textBoxServiceUri);
            this.Controls.Add(this.labelServiceUri);
            this.Controls.Add(this.buttonStartStopCapture);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "FormMain";
            this.Text = "DirectSound Sender";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox checkBoxAddNoise;
        private System.Windows.Forms.TextBox textBoxServiceUri;
        private System.Windows.Forms.Label labelServiceUri;
        private System.Windows.Forms.Button buttonStartStopCapture;
    }
}

