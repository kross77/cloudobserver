namespace CaptureDesktop
{
    partial class MainForm
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
            this.btnCapture = new System.Windows.Forms.Button();
            this.btnCaptureSettings = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnCapture
            // 
            this.btnCapture.Location = new System.Drawing.Point(131, 12);
            this.btnCapture.Name = "btnCapture";
            this.btnCapture.Size = new System.Drawing.Size(84, 23);
            this.btnCapture.TabIndex = 0;
            this.btnCapture.Text = "start capture";
            this.btnCapture.UseVisualStyleBackColor = true;
            this.btnCapture.Click += new System.EventHandler(this.btnCapture_Click);
            // 
            // btnCaptureSettings
            // 
            this.btnCaptureSettings.Location = new System.Drawing.Point(12, 12);
            this.btnCaptureSettings.Name = "btnCaptureSettings";
            this.btnCaptureSettings.Size = new System.Drawing.Size(75, 23);
            this.btnCaptureSettings.TabIndex = 1;
            this.btnCaptureSettings.Text = "settings";
            this.btnCaptureSettings.UseVisualStyleBackColor = true;
            this.btnCaptureSettings.Click += new System.EventHandler(this.btnCaptureSettings_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(227, 56);
            this.Controls.Add(this.btnCaptureSettings);
            this.Controls.Add(this.btnCapture);
            this.Name = "MainForm";
            this.Text = "CloudCaptureDesctop";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnCapture;
        private System.Windows.Forms.Button btnCaptureSettings;
    }
}

