namespace CSharp_Client
{
    partial class AppForm
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
            this.StreamRadioButton = new System.Windows.Forms.RadioButton();
            this.FileRadioButton = new System.Windows.Forms.RadioButton();
            this.StreamTextBox = new System.Windows.Forms.TextBox();
            this.FileTextBox = new System.Windows.Forms.TextBox();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.StartButton = new System.Windows.Forms.Button();
            this.StopButton = new System.Windows.Forms.Button();
            this.FPSTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // StreamRadioButton
            // 
            this.StreamRadioButton.AutoSize = true;
            this.StreamRadioButton.Location = new System.Drawing.Point(13, 14);
            this.StreamRadioButton.Name = "StreamRadioButton";
            this.StreamRadioButton.Size = new System.Drawing.Size(84, 17);
            this.StreamRadioButton.TabIndex = 0;
            this.StreamRadioButton.TabStop = true;
            this.StreamRadioButton.Text = "FromStream:";
            this.StreamRadioButton.UseVisualStyleBackColor = true;
            this.StreamRadioButton.CheckedChanged += new System.EventHandler(this.StreamRadioButton_CheckedChanged);
            // 
            // FileRadioButton
            // 
            this.FileRadioButton.AutoSize = true;
            this.FileRadioButton.Checked = true;
            this.FileRadioButton.Location = new System.Drawing.Point(13, 42);
            this.FileRadioButton.Name = "FileRadioButton";
            this.FileRadioButton.Size = new System.Drawing.Size(67, 17);
            this.FileRadioButton.TabIndex = 1;
            this.FileRadioButton.TabStop = true;
            this.FileRadioButton.Text = "FromFile:";
            this.FileRadioButton.UseVisualStyleBackColor = true;
            this.FileRadioButton.CheckedChanged += new System.EventHandler(this.FileRadioButton_CheckedChanged);
            // 
            // StreamTextBox
            // 
            this.StreamTextBox.Location = new System.Drawing.Point(106, 11);
            this.StreamTextBox.Name = "StreamTextBox";
            this.StreamTextBox.Size = new System.Drawing.Size(359, 20);
            this.StreamTextBox.TabIndex = 2;
            // 
            // FileTextBox
            // 
            this.FileTextBox.Location = new System.Drawing.Point(106, 39);
            this.FileTextBox.Name = "FileTextBox";
            this.FileTextBox.Size = new System.Drawing.Size(359, 20);
            this.FileTextBox.TabIndex = 3;
            // 
            // pictureBox
            // 
            this.pictureBox.Location = new System.Drawing.Point(10, 65);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(675, 295);
            this.pictureBox.TabIndex = 4;
            this.pictureBox.TabStop = false;
            // 
            // StartButton
            // 
            this.StartButton.Location = new System.Drawing.Point(582, 10);
            this.StartButton.Name = "StartButton";
            this.StartButton.Size = new System.Drawing.Size(103, 20);
            this.StartButton.TabIndex = 5;
            this.StartButton.Text = "StartReceiving";
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // StopButton
            // 
            this.StopButton.Location = new System.Drawing.Point(582, 38);
            this.StopButton.Name = "StopButton";
            this.StopButton.Size = new System.Drawing.Size(103, 21);
            this.StopButton.TabIndex = 6;
            this.StopButton.Text = "StopReceiving";
            this.StopButton.UseVisualStyleBackColor = true;
            this.StopButton.Click += new System.EventHandler(this.StopButton_Click);
            // 
            // FPSTextBox
            // 
            this.FPSTextBox.Location = new System.Drawing.Point(521, 11);
            this.FPSTextBox.Name = "FPSTextBox";
            this.FPSTextBox.Size = new System.Drawing.Size(43, 20);
            this.FPSTextBox.TabIndex = 7;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(475, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(27, 13);
            this.label1.TabIndex = 8;
            this.label1.Text = "FPS";
            // 
            // AppForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(697, 372);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.FPSTextBox);
            this.Controls.Add(this.StopButton);
            this.Controls.Add(this.StartButton);
            this.Controls.Add(this.pictureBox);
            this.Controls.Add(this.FileTextBox);
            this.Controls.Add(this.StreamTextBox);
            this.Controls.Add(this.FileRadioButton);
            this.Controls.Add(this.StreamRadioButton);
            this.Name = "AppForm";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.AppForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton StreamRadioButton;
        private System.Windows.Forms.RadioButton FileRadioButton;
        private System.Windows.Forms.TextBox StreamTextBox;
        private System.Windows.Forms.TextBox FileTextBox;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.Button StartButton;
        private System.Windows.Forms.Button StopButton;
        private System.Windows.Forms.TextBox FPSTextBox;
        private System.Windows.Forms.Label label1;
    }
}

