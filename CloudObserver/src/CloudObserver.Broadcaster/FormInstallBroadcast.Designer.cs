namespace CloudObserver.Broadcaster
{
    partial class FormInstallBroadcast
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
            this.labelCameraID = new System.Windows.Forms.Label();
            this.numericUpDownCameraID = new System.Windows.Forms.NumericUpDown();
            this.groupBoxType = new System.Windows.Forms.GroupBox();
            this.radioButtonTypeVirtualClientService = new System.Windows.Forms.RadioButton();
            this.radioButtonTypeDirectBroadcasting = new System.Windows.Forms.RadioButton();
            this.groupBoxFormat = new System.Windows.Forms.GroupBox();
            this.radioButtonFormatMpeg = new System.Windows.Forms.RadioButton();
            this.radioButtonFormatMjpeg = new System.Windows.Forms.RadioButton();
            this.radioButtonFormatJpeg = new System.Windows.Forms.RadioButton();
            this.groupBoxSource = new System.Windows.Forms.GroupBox();
            this.textBoxPassword = new System.Windows.Forms.TextBox();
            this.labelPassword = new System.Windows.Forms.Label();
            this.textBoxUserName = new System.Windows.Forms.TextBox();
            this.labelUserName = new System.Windows.Forms.Label();
            this.checkBoxProvideCredentials = new System.Windows.Forms.CheckBox();
            this.checkBoxActualRetransmission = new System.Windows.Forms.CheckBox();
            this.numericUpDownSourceCloudObserverCameraID = new System.Windows.Forms.NumericUpDown();
            this.buttonSourceLocalStorageFilesSelect = new System.Windows.Forms.Button();
            this.radioButtonSourceIPCamera = new System.Windows.Forms.RadioButton();
            this.textBoxSourceIPCameraUri = new System.Windows.Forms.TextBox();
            this.radioButtonSourceCloudObserverCamera = new System.Windows.Forms.RadioButton();
            this.textBoxSourceLocalStorageFiles = new System.Windows.Forms.TextBox();
            this.radioButtonSourceLocalStorage = new System.Windows.Forms.RadioButton();
            this.labelMaxFPS = new System.Windows.Forms.Label();
            this.numericUpDownMaxFPS = new System.Windows.Forms.NumericUpDown();
            this.checkBoxStartBroadcastImmediately = new System.Windows.Forms.CheckBox();
            this.buttonInstall = new System.Windows.Forms.Button();
            this.openFileDialogFilesSelect = new System.Windows.Forms.OpenFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCameraID)).BeginInit();
            this.groupBoxType.SuspendLayout();
            this.groupBoxFormat.SuspendLayout();
            this.groupBoxSource.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSourceCloudObserverCameraID)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMaxFPS)).BeginInit();
            this.SuspendLayout();
            // 
            // labelCameraID
            // 
            this.labelCameraID.AutoSize = true;
            this.labelCameraID.Location = new System.Drawing.Point(12, 14);
            this.labelCameraID.Name = "labelCameraID";
            this.labelCameraID.Size = new System.Drawing.Size(60, 13);
            this.labelCameraID.TabIndex = 0;
            this.labelCameraID.Text = "Camera ID:";
            // 
            // numericUpDownCameraID
            // 
            this.numericUpDownCameraID.Location = new System.Drawing.Point(78, 12);
            this.numericUpDownCameraID.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numericUpDownCameraID.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownCameraID.Name = "numericUpDownCameraID";
            this.numericUpDownCameraID.Size = new System.Drawing.Size(80, 20);
            this.numericUpDownCameraID.TabIndex = 1;
            this.numericUpDownCameraID.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // groupBoxType
            // 
            this.groupBoxType.Controls.Add(this.radioButtonTypeVirtualClientService);
            this.groupBoxType.Controls.Add(this.radioButtonTypeDirectBroadcasting);
            this.groupBoxType.Location = new System.Drawing.Point(12, 38);
            this.groupBoxType.Name = "groupBoxType";
            this.groupBoxType.Size = new System.Drawing.Size(146, 65);
            this.groupBoxType.TabIndex = 2;
            this.groupBoxType.TabStop = false;
            this.groupBoxType.Text = "Type:";
            // 
            // radioButtonTypeVirtualClientService
            // 
            this.radioButtonTypeVirtualClientService.AutoSize = true;
            this.radioButtonTypeVirtualClientService.Location = new System.Drawing.Point(6, 42);
            this.radioButtonTypeVirtualClientService.Name = "radioButtonTypeVirtualClientService";
            this.radioButtonTypeVirtualClientService.Size = new System.Drawing.Size(120, 17);
            this.radioButtonTypeVirtualClientService.TabIndex = 1;
            this.radioButtonTypeVirtualClientService.Text = "Virtual Client service";
            this.radioButtonTypeVirtualClientService.UseVisualStyleBackColor = true;
            this.radioButtonTypeVirtualClientService.CheckedChanged += new System.EventHandler(this.RefreshControlsState);
            // 
            // radioButtonTypeDirectBroadcasting
            // 
            this.radioButtonTypeDirectBroadcasting.AutoSize = true;
            this.radioButtonTypeDirectBroadcasting.Checked = true;
            this.radioButtonTypeDirectBroadcasting.Location = new System.Drawing.Point(6, 19);
            this.radioButtonTypeDirectBroadcasting.Name = "radioButtonTypeDirectBroadcasting";
            this.radioButtonTypeDirectBroadcasting.Size = new System.Drawing.Size(117, 17);
            this.radioButtonTypeDirectBroadcasting.TabIndex = 0;
            this.radioButtonTypeDirectBroadcasting.TabStop = true;
            this.radioButtonTypeDirectBroadcasting.Text = "Direct broadcasting";
            this.radioButtonTypeDirectBroadcasting.UseVisualStyleBackColor = true;
            this.radioButtonTypeDirectBroadcasting.CheckedChanged += new System.EventHandler(this.RefreshControlsState);
            // 
            // groupBoxFormat
            // 
            this.groupBoxFormat.Controls.Add(this.radioButtonFormatMpeg);
            this.groupBoxFormat.Controls.Add(this.radioButtonFormatMjpeg);
            this.groupBoxFormat.Controls.Add(this.radioButtonFormatJpeg);
            this.groupBoxFormat.Location = new System.Drawing.Point(12, 109);
            this.groupBoxFormat.Name = "groupBoxFormat";
            this.groupBoxFormat.Size = new System.Drawing.Size(146, 88);
            this.groupBoxFormat.TabIndex = 3;
            this.groupBoxFormat.TabStop = false;
            this.groupBoxFormat.Text = "Format:";
            // 
            // radioButtonFormatMpeg
            // 
            this.radioButtonFormatMpeg.AutoSize = true;
            this.radioButtonFormatMpeg.Enabled = false;
            this.radioButtonFormatMpeg.Location = new System.Drawing.Point(6, 65);
            this.radioButtonFormatMpeg.Name = "radioButtonFormatMpeg";
            this.radioButtonFormatMpeg.Size = new System.Drawing.Size(119, 17);
            this.radioButtonFormatMpeg.TabIndex = 2;
            this.radioButtonFormatMpeg.Text = "MPEG (unavailable)";
            this.radioButtonFormatMpeg.UseVisualStyleBackColor = true;
            this.radioButtonFormatMpeg.CheckedChanged += new System.EventHandler(this.RefreshControlsState);
            // 
            // radioButtonFormatMjpeg
            // 
            this.radioButtonFormatMjpeg.AutoSize = true;
            this.radioButtonFormatMjpeg.Location = new System.Drawing.Point(6, 42);
            this.radioButtonFormatMjpeg.Name = "radioButtonFormatMjpeg";
            this.radioButtonFormatMjpeg.Size = new System.Drawing.Size(64, 17);
            this.radioButtonFormatMjpeg.TabIndex = 1;
            this.radioButtonFormatMjpeg.Text = "M-JPEG";
            this.radioButtonFormatMjpeg.UseVisualStyleBackColor = true;
            this.radioButtonFormatMjpeg.CheckedChanged += new System.EventHandler(this.RefreshControlsState);
            // 
            // radioButtonFormatJpeg
            // 
            this.radioButtonFormatJpeg.AutoSize = true;
            this.radioButtonFormatJpeg.Checked = true;
            this.radioButtonFormatJpeg.Location = new System.Drawing.Point(6, 19);
            this.radioButtonFormatJpeg.Name = "radioButtonFormatJpeg";
            this.radioButtonFormatJpeg.Size = new System.Drawing.Size(52, 17);
            this.radioButtonFormatJpeg.TabIndex = 0;
            this.radioButtonFormatJpeg.TabStop = true;
            this.radioButtonFormatJpeg.Text = "JPEG";
            this.radioButtonFormatJpeg.UseVisualStyleBackColor = true;
            this.radioButtonFormatJpeg.CheckedChanged += new System.EventHandler(this.RefreshControlsState);
            // 
            // groupBoxSource
            // 
            this.groupBoxSource.Controls.Add(this.textBoxPassword);
            this.groupBoxSource.Controls.Add(this.labelPassword);
            this.groupBoxSource.Controls.Add(this.textBoxUserName);
            this.groupBoxSource.Controls.Add(this.labelUserName);
            this.groupBoxSource.Controls.Add(this.checkBoxProvideCredentials);
            this.groupBoxSource.Controls.Add(this.checkBoxActualRetransmission);
            this.groupBoxSource.Controls.Add(this.numericUpDownSourceCloudObserverCameraID);
            this.groupBoxSource.Controls.Add(this.buttonSourceLocalStorageFilesSelect);
            this.groupBoxSource.Controls.Add(this.radioButtonSourceIPCamera);
            this.groupBoxSource.Controls.Add(this.textBoxSourceIPCameraUri);
            this.groupBoxSource.Controls.Add(this.radioButtonSourceCloudObserverCamera);
            this.groupBoxSource.Controls.Add(this.textBoxSourceLocalStorageFiles);
            this.groupBoxSource.Controls.Add(this.radioButtonSourceLocalStorage);
            this.groupBoxSource.Location = new System.Drawing.Point(164, 12);
            this.groupBoxSource.Name = "groupBoxSource";
            this.groupBoxSource.Size = new System.Drawing.Size(443, 124);
            this.groupBoxSource.TabIndex = 4;
            this.groupBoxSource.TabStop = false;
            this.groupBoxSource.Text = "Source:";
            // 
            // textBoxPassword
            // 
            this.textBoxPassword.Enabled = false;
            this.textBoxPassword.Location = new System.Drawing.Point(357, 98);
            this.textBoxPassword.Name = "textBoxPassword";
            this.textBoxPassword.PasswordChar = '*';
            this.textBoxPassword.Size = new System.Drawing.Size(80, 20);
            this.textBoxPassword.TabIndex = 12;
            // 
            // labelPassword
            // 
            this.labelPassword.AutoSize = true;
            this.labelPassword.Location = new System.Drawing.Point(295, 101);
            this.labelPassword.Name = "labelPassword";
            this.labelPassword.Size = new System.Drawing.Size(56, 13);
            this.labelPassword.TabIndex = 11;
            this.labelPassword.Text = "Password:";
            // 
            // textBoxUserName
            // 
            this.textBoxUserName.Enabled = false;
            this.textBoxUserName.Location = new System.Drawing.Point(209, 98);
            this.textBoxUserName.Name = "textBoxUserName";
            this.textBoxUserName.Size = new System.Drawing.Size(80, 20);
            this.textBoxUserName.TabIndex = 10;
            // 
            // labelUserName
            // 
            this.labelUserName.AutoSize = true;
            this.labelUserName.Location = new System.Drawing.Point(143, 101);
            this.labelUserName.Name = "labelUserName";
            this.labelUserName.Size = new System.Drawing.Size(60, 13);
            this.labelUserName.TabIndex = 9;
            this.labelUserName.Text = "UserName:";
            // 
            // checkBoxProvideCredentials
            // 
            this.checkBoxProvideCredentials.AutoSize = true;
            this.checkBoxProvideCredentials.Enabled = false;
            this.checkBoxProvideCredentials.Location = new System.Drawing.Point(21, 100);
            this.checkBoxProvideCredentials.Name = "checkBoxProvideCredentials";
            this.checkBoxProvideCredentials.Size = new System.Drawing.Size(116, 17);
            this.checkBoxProvideCredentials.TabIndex = 8;
            this.checkBoxProvideCredentials.Text = "Provide credentials";
            this.checkBoxProvideCredentials.UseVisualStyleBackColor = true;
            this.checkBoxProvideCredentials.CheckedChanged += new System.EventHandler(this.RefreshControlsState);
            // 
            // checkBoxActualRetransmission
            // 
            this.checkBoxActualRetransmission.AutoSize = true;
            this.checkBoxActualRetransmission.Checked = true;
            this.checkBoxActualRetransmission.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxActualRetransmission.Enabled = false;
            this.checkBoxActualRetransmission.Location = new System.Drawing.Point(312, 46);
            this.checkBoxActualRetransmission.Name = "checkBoxActualRetransmission";
            this.checkBoxActualRetransmission.Size = new System.Drawing.Size(125, 17);
            this.checkBoxActualRetransmission.TabIndex = 7;
            this.checkBoxActualRetransmission.Text = "Actual retransmission";
            this.checkBoxActualRetransmission.UseVisualStyleBackColor = true;
            // 
            // numericUpDownSourceCloudObserverCameraID
            // 
            this.numericUpDownSourceCloudObserverCameraID.Enabled = false;
            this.numericUpDownSourceCloudObserverCameraID.Location = new System.Drawing.Point(226, 46);
            this.numericUpDownSourceCloudObserverCameraID.Maximum = new decimal(new int[] {
            2147483647,
            0,
            0,
            0});
            this.numericUpDownSourceCloudObserverCameraID.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownSourceCloudObserverCameraID.Name = "numericUpDownSourceCloudObserverCameraID";
            this.numericUpDownSourceCloudObserverCameraID.Size = new System.Drawing.Size(80, 20);
            this.numericUpDownSourceCloudObserverCameraID.TabIndex = 6;
            this.numericUpDownSourceCloudObserverCameraID.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // buttonSourceLocalStorageFilesSelect
            // 
            this.buttonSourceLocalStorageFilesSelect.Location = new System.Drawing.Point(413, 19);
            this.buttonSourceLocalStorageFilesSelect.Name = "buttonSourceLocalStorageFilesSelect";
            this.buttonSourceLocalStorageFilesSelect.Size = new System.Drawing.Size(24, 21);
            this.buttonSourceLocalStorageFilesSelect.TabIndex = 5;
            this.buttonSourceLocalStorageFilesSelect.Text = "...";
            this.buttonSourceLocalStorageFilesSelect.UseVisualStyleBackColor = true;
            this.buttonSourceLocalStorageFilesSelect.Click += new System.EventHandler(this.buttonSourceLocalStorageSelect_Click);
            // 
            // radioButtonSourceIPCamera
            // 
            this.radioButtonSourceIPCamera.AutoSize = true;
            this.radioButtonSourceIPCamera.Location = new System.Drawing.Point(6, 73);
            this.radioButtonSourceIPCamera.Name = "radioButtonSourceIPCamera";
            this.radioButtonSourceIPCamera.Size = new System.Drawing.Size(171, 17);
            this.radioButtonSourceIPCamera.TabIndex = 4;
            this.radioButtonSourceIPCamera.Text = "IP camera web interface (URI):";
            this.radioButtonSourceIPCamera.UseVisualStyleBackColor = true;
            this.radioButtonSourceIPCamera.CheckedChanged += new System.EventHandler(this.RefreshControlsState);
            // 
            // textBoxSourceIPCameraUri
            // 
            this.textBoxSourceIPCameraUri.Enabled = false;
            this.textBoxSourceIPCameraUri.Location = new System.Drawing.Point(183, 72);
            this.textBoxSourceIPCameraUri.Name = "textBoxSourceIPCameraUri";
            this.textBoxSourceIPCameraUri.Size = new System.Drawing.Size(254, 20);
            this.textBoxSourceIPCameraUri.TabIndex = 3;
            // 
            // radioButtonSourceCloudObserverCamera
            // 
            this.radioButtonSourceCloudObserverCamera.AutoSize = true;
            this.radioButtonSourceCloudObserverCamera.Location = new System.Drawing.Point(6, 46);
            this.radioButtonSourceCloudObserverCamera.Name = "radioButtonSourceCloudObserverCamera";
            this.radioButtonSourceCloudObserverCamera.Size = new System.Drawing.Size(214, 17);
            this.radioButtonSourceCloudObserverCamera.TabIndex = 2;
            this.radioButtonSourceCloudObserverCamera.Text = "Cloud Observer camera (retransmission):";
            this.radioButtonSourceCloudObserverCamera.UseVisualStyleBackColor = true;
            this.radioButtonSourceCloudObserverCamera.CheckedChanged += new System.EventHandler(this.RefreshControlsState);
            // 
            // textBoxSourceLocalStorageFiles
            // 
            this.textBoxSourceLocalStorageFiles.Location = new System.Drawing.Point(185, 20);
            this.textBoxSourceLocalStorageFiles.Name = "textBoxSourceLocalStorageFiles";
            this.textBoxSourceLocalStorageFiles.ReadOnly = true;
            this.textBoxSourceLocalStorageFiles.Size = new System.Drawing.Size(222, 20);
            this.textBoxSourceLocalStorageFiles.TabIndex = 1;
            // 
            // radioButtonSourceLocalStorage
            // 
            this.radioButtonSourceLocalStorage.AutoSize = true;
            this.radioButtonSourceLocalStorage.Checked = true;
            this.radioButtonSourceLocalStorage.Location = new System.Drawing.Point(6, 20);
            this.radioButtonSourceLocalStorage.Name = "radioButtonSourceLocalStorage";
            this.radioButtonSourceLocalStorage.Size = new System.Drawing.Size(173, 17);
            this.radioButtonSourceLocalStorage.TabIndex = 0;
            this.radioButtonSourceLocalStorage.TabStop = true;
            this.radioButtonSourceLocalStorage.Text = "Local Storage (loop broadcast):";
            this.radioButtonSourceLocalStorage.UseVisualStyleBackColor = true;
            this.radioButtonSourceLocalStorage.CheckedChanged += new System.EventHandler(this.RefreshControlsState);
            // 
            // labelMaxFPS
            // 
            this.labelMaxFPS.AutoSize = true;
            this.labelMaxFPS.Location = new System.Drawing.Point(355, 144);
            this.labelMaxFPS.Name = "labelMaxFPS";
            this.labelMaxFPS.Size = new System.Drawing.Size(120, 13);
            this.labelMaxFPS.TabIndex = 5;
            this.labelMaxFPS.Text = "Max frames per second:";
            // 
            // numericUpDownMaxFPS
            // 
            this.numericUpDownMaxFPS.Location = new System.Drawing.Point(481, 142);
            this.numericUpDownMaxFPS.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.numericUpDownMaxFPS.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownMaxFPS.Name = "numericUpDownMaxFPS";
            this.numericUpDownMaxFPS.Size = new System.Drawing.Size(120, 20);
            this.numericUpDownMaxFPS.TabIndex = 6;
            this.numericUpDownMaxFPS.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // checkBoxStartBroadcastImmediately
            // 
            this.checkBoxStartBroadcastImmediately.AutoSize = true;
            this.checkBoxStartBroadcastImmediately.Checked = true;
            this.checkBoxStartBroadcastImmediately.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxStartBroadcastImmediately.Location = new System.Drawing.Point(365, 172);
            this.checkBoxStartBroadcastImmediately.Name = "checkBoxStartBroadcastImmediately";
            this.checkBoxStartBroadcastImmediately.Size = new System.Drawing.Size(155, 17);
            this.checkBoxStartBroadcastImmediately.TabIndex = 7;
            this.checkBoxStartBroadcastImmediately.Text = "Start broadcast immediately";
            this.checkBoxStartBroadcastImmediately.UseVisualStyleBackColor = true;
            // 
            // buttonInstall
            // 
            this.buttonInstall.Location = new System.Drawing.Point(526, 168);
            this.buttonInstall.Name = "buttonInstall";
            this.buttonInstall.Size = new System.Drawing.Size(75, 23);
            this.buttonInstall.TabIndex = 8;
            this.buttonInstall.Text = "Install";
            this.buttonInstall.UseVisualStyleBackColor = true;
            this.buttonInstall.Click += new System.EventHandler(this.buttonInstall_Click);
            // 
            // openFileDialogFilesSelect
            // 
            this.openFileDialogFilesSelect.Filter = "JPEG (*.jpg; *jpeg)|*.jpg;*jpeg";
            this.openFileDialogFilesSelect.Multiselect = true;
            // 
            // FormInstallBroadcast
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(619, 209);
            this.Controls.Add(this.buttonInstall);
            this.Controls.Add(this.checkBoxStartBroadcastImmediately);
            this.Controls.Add(this.numericUpDownMaxFPS);
            this.Controls.Add(this.labelMaxFPS);
            this.Controls.Add(this.groupBoxSource);
            this.Controls.Add(this.groupBoxFormat);
            this.Controls.Add(this.groupBoxType);
            this.Controls.Add(this.numericUpDownCameraID);
            this.Controls.Add(this.labelCameraID);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormInstallBroadcast";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Install Broadcast";
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCameraID)).EndInit();
            this.groupBoxType.ResumeLayout(false);
            this.groupBoxType.PerformLayout();
            this.groupBoxFormat.ResumeLayout(false);
            this.groupBoxFormat.PerformLayout();
            this.groupBoxSource.ResumeLayout(false);
            this.groupBoxSource.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSourceCloudObserverCameraID)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMaxFPS)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelCameraID;
        private System.Windows.Forms.NumericUpDown numericUpDownCameraID;
        private System.Windows.Forms.GroupBox groupBoxType;
        private System.Windows.Forms.RadioButton radioButtonTypeVirtualClientService;
        private System.Windows.Forms.RadioButton radioButtonTypeDirectBroadcasting;
        private System.Windows.Forms.GroupBox groupBoxFormat;
        private System.Windows.Forms.RadioButton radioButtonFormatMpeg;
        private System.Windows.Forms.RadioButton radioButtonFormatMjpeg;
        private System.Windows.Forms.RadioButton radioButtonFormatJpeg;
        private System.Windows.Forms.GroupBox groupBoxSource;
        private System.Windows.Forms.RadioButton radioButtonSourceIPCamera;
        private System.Windows.Forms.TextBox textBoxSourceIPCameraUri;
        private System.Windows.Forms.RadioButton radioButtonSourceCloudObserverCamera;
        private System.Windows.Forms.TextBox textBoxSourceLocalStorageFiles;
        private System.Windows.Forms.RadioButton radioButtonSourceLocalStorage;
        private System.Windows.Forms.Button buttonSourceLocalStorageFilesSelect;
        private System.Windows.Forms.NumericUpDown numericUpDownSourceCloudObserverCameraID;
        private System.Windows.Forms.TextBox textBoxPassword;
        private System.Windows.Forms.Label labelPassword;
        private System.Windows.Forms.TextBox textBoxUserName;
        private System.Windows.Forms.Label labelUserName;
        private System.Windows.Forms.CheckBox checkBoxProvideCredentials;
        private System.Windows.Forms.CheckBox checkBoxActualRetransmission;
        private System.Windows.Forms.Label labelMaxFPS;
        private System.Windows.Forms.NumericUpDown numericUpDownMaxFPS;
        private System.Windows.Forms.CheckBox checkBoxStartBroadcastImmediately;
        private System.Windows.Forms.Button buttonInstall;
        private System.Windows.Forms.OpenFileDialog openFileDialogFilesSelect;
    }
}