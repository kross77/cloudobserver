namespace CloudObserver.Hoster
{
    partial class FormInstallService
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
            this.buttonTestServiceHosting = new System.Windows.Forms.Button();
            this.buttonInstallService = new System.Windows.Forms.Button();
            this.buttonSelectDLLFile = new System.Windows.Forms.Button();
            this.textBoxDLLFile = new System.Windows.Forms.TextBox();
            this.labelDLLFile = new System.Windows.Forms.Label();
            this.openFileDialogSelectDLLFile = new System.Windows.Forms.OpenFileDialog();
            this.checkBoxCopyDLL = new System.Windows.Forms.CheckBox();
            this.comboBoxService = new System.Windows.Forms.ComboBox();
            this.labelService = new System.Windows.Forms.Label();
            this.comboBoxContract = new System.Windows.Forms.ComboBox();
            this.labelContract = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonTestServiceHosting
            // 
            this.buttonTestServiceHosting.Enabled = false;
            this.buttonTestServiceHosting.Location = new System.Drawing.Point(195, 95);
            this.buttonTestServiceHosting.Name = "buttonTestServiceHosting";
            this.buttonTestServiceHosting.Size = new System.Drawing.Size(140, 23);
            this.buttonTestServiceHosting.TabIndex = 8;
            this.buttonTestServiceHosting.Text = "Test Service Hosting";
            this.buttonTestServiceHosting.UseVisualStyleBackColor = true;
            this.buttonTestServiceHosting.Click += new System.EventHandler(this.buttonTestServiceHosting_Click);
            // 
            // buttonInstallService
            // 
            this.buttonInstallService.Enabled = false;
            this.buttonInstallService.Location = new System.Drawing.Point(341, 95);
            this.buttonInstallService.Name = "buttonInstallService";
            this.buttonInstallService.Size = new System.Drawing.Size(141, 23);
            this.buttonInstallService.TabIndex = 9;
            this.buttonInstallService.Text = "Install Service";
            this.buttonInstallService.UseVisualStyleBackColor = true;
            this.buttonInstallService.Click += new System.EventHandler(this.buttonInstallService_Click);
            // 
            // buttonSelectDLLFile
            // 
            this.buttonSelectDLLFile.Location = new System.Drawing.Point(457, 12);
            this.buttonSelectDLLFile.Name = "buttonSelectDLLFile";
            this.buttonSelectDLLFile.Size = new System.Drawing.Size(25, 23);
            this.buttonSelectDLLFile.TabIndex = 2;
            this.buttonSelectDLLFile.Text = "...";
            this.buttonSelectDLLFile.UseVisualStyleBackColor = true;
            this.buttonSelectDLLFile.Click += new System.EventHandler(this.buttonSelectDLLFile_Click);
            // 
            // textBoxDLLFile
            // 
            this.textBoxDLLFile.Enabled = false;
            this.textBoxDLLFile.Location = new System.Drawing.Point(67, 14);
            this.textBoxDLLFile.Name = "textBoxDLLFile";
            this.textBoxDLLFile.Size = new System.Drawing.Size(384, 20);
            this.textBoxDLLFile.TabIndex = 1;
            // 
            // labelDLLFile
            // 
            this.labelDLLFile.AutoSize = true;
            this.labelDLLFile.Location = new System.Drawing.Point(12, 17);
            this.labelDLLFile.Name = "labelDLLFile";
            this.labelDLLFile.Size = new System.Drawing.Size(49, 13);
            this.labelDLLFile.TabIndex = 0;
            this.labelDLLFile.Text = "DLL File:";
            // 
            // openFileDialogSelectDLLFile
            // 
            this.openFileDialogSelectDLLFile.Filter = "Dynamic Link Library (*.dll)|*.dll";
            this.openFileDialogSelectDLLFile.Title = "Select DLL File";
            // 
            // checkBoxCopyDLL
            // 
            this.checkBoxCopyDLL.AutoSize = true;
            this.checkBoxCopyDLL.Checked = true;
            this.checkBoxCopyDLL.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxCopyDLL.Location = new System.Drawing.Point(12, 99);
            this.checkBoxCopyDLL.Name = "checkBoxCopyDLL";
            this.checkBoxCopyDLL.Size = new System.Drawing.Size(177, 17);
            this.checkBoxCopyDLL.TabIndex = 7;
            this.checkBoxCopyDLL.Text = "Copy DLL file into local directory";
            this.checkBoxCopyDLL.UseVisualStyleBackColor = true;
            // 
            // comboBoxService
            // 
            this.comboBoxService.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxService.Enabled = false;
            this.comboBoxService.FormattingEnabled = true;
            this.comboBoxService.Location = new System.Drawing.Point(64, 41);
            this.comboBoxService.Name = "comboBoxService";
            this.comboBoxService.Size = new System.Drawing.Size(418, 21);
            this.comboBoxService.Sorted = true;
            this.comboBoxService.TabIndex = 4;
            this.comboBoxService.SelectedIndexChanged += new System.EventHandler(this.comboBoxService_SelectedIndexChanged);
            // 
            // labelService
            // 
            this.labelService.AutoSize = true;
            this.labelService.Location = new System.Drawing.Point(12, 44);
            this.labelService.Name = "labelService";
            this.labelService.Size = new System.Drawing.Size(46, 13);
            this.labelService.TabIndex = 3;
            this.labelService.Text = "Service:";
            // 
            // comboBoxContract
            // 
            this.comboBoxContract.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxContract.Enabled = false;
            this.comboBoxContract.FormattingEnabled = true;
            this.comboBoxContract.Location = new System.Drawing.Point(68, 68);
            this.comboBoxContract.Name = "comboBoxContract";
            this.comboBoxContract.Size = new System.Drawing.Size(414, 21);
            this.comboBoxContract.Sorted = true;
            this.comboBoxContract.TabIndex = 6;
            this.comboBoxContract.SelectedIndexChanged += new System.EventHandler(this.comboBoxContract_SelectedIndexChanged);
            // 
            // labelContract
            // 
            this.labelContract.AutoSize = true;
            this.labelContract.Location = new System.Drawing.Point(12, 71);
            this.labelContract.Name = "labelContract";
            this.labelContract.Size = new System.Drawing.Size(50, 13);
            this.labelContract.TabIndex = 5;
            this.labelContract.Text = "Contract:";
            // 
            // FormInstallService
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(494, 130);
            this.Controls.Add(this.comboBoxService);
            this.Controls.Add(this.labelService);
            this.Controls.Add(this.comboBoxContract);
            this.Controls.Add(this.labelContract);
            this.Controls.Add(this.checkBoxCopyDLL);
            this.Controls.Add(this.buttonTestServiceHosting);
            this.Controls.Add(this.buttonInstallService);
            this.Controls.Add(this.buttonSelectDLLFile);
            this.Controls.Add(this.textBoxDLLFile);
            this.Controls.Add(this.labelDLLFile);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormInstallService";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Install Service";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonTestServiceHosting;
        private System.Windows.Forms.Button buttonInstallService;
        private System.Windows.Forms.Button buttonSelectDLLFile;
        private System.Windows.Forms.TextBox textBoxDLLFile;
        private System.Windows.Forms.Label labelDLLFile;
        private System.Windows.Forms.OpenFileDialog openFileDialogSelectDLLFile;
        private System.Windows.Forms.CheckBox checkBoxCopyDLL;
        private System.Windows.Forms.ComboBox comboBoxService;
        private System.Windows.Forms.Label labelService;
        private System.Windows.Forms.ComboBox comboBoxContract;
        private System.Windows.Forms.Label labelContract;

    }
}