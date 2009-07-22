namespace CloudObserverServicesHoster
{
    partial class FormLoadServiceDLL
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
            this.radioButtonLoadFromFile = new System.Windows.Forms.RadioButton();
            this.radioButtonLoadFromCOService = new System.Windows.Forms.RadioButton();
            this.labelDLLFile = new System.Windows.Forms.Label();
            this.textBoxDLLFile = new System.Windows.Forms.TextBox();
            this.buttonSelectDLLFile = new System.Windows.Forms.Button();
            this.openFileDialogSelectDLLFile = new System.Windows.Forms.OpenFileDialog();
            this.groupBoxServiceDetails = new System.Windows.Forms.GroupBox();
            this.textBoxServiceDetailsName = new System.Windows.Forms.TextBox();
            this.labelServiceDetailsName = new System.Windows.Forms.Label();
            this.comboBoxServiceDetailsClass = new System.Windows.Forms.ComboBox();
            this.labelServiceDetailsClass = new System.Windows.Forms.Label();
            this.comboBoxServiceDetailsInterface = new System.Windows.Forms.ComboBox();
            this.labelServiceDetailsInterface = new System.Windows.Forms.Label();
            this.buttonLoadService = new System.Windows.Forms.Button();
            this.buttonTestServiceHosting = new System.Windows.Forms.Button();
            this.checkBoxCopyDLL = new System.Windows.Forms.CheckBox();
            this.labelCOServiceURL = new System.Windows.Forms.Label();
            this.textBoxCOServiceURL = new System.Windows.Forms.TextBox();
            this.listBoxCOServiceServices = new System.Windows.Forms.ListBox();
            this.buttonGetServicesList = new System.Windows.Forms.Button();
            this.groupBoxServiceDetails.SuspendLayout();
            this.SuspendLayout();
            // 
            // radioButtonLoadFromFile
            // 
            this.radioButtonLoadFromFile.AutoSize = true;
            this.radioButtonLoadFromFile.Checked = true;
            this.radioButtonLoadFromFile.Location = new System.Drawing.Point(12, 12);
            this.radioButtonLoadFromFile.Name = "radioButtonLoadFromFile";
            this.radioButtonLoadFromFile.Size = new System.Drawing.Size(91, 17);
            this.radioButtonLoadFromFile.TabIndex = 0;
            this.radioButtonLoadFromFile.TabStop = true;
            this.radioButtonLoadFromFile.Text = "Load from file:";
            this.radioButtonLoadFromFile.UseVisualStyleBackColor = true;
            this.radioButtonLoadFromFile.CheckedChanged += new System.EventHandler(this.radioButtonLoadFromFile_CheckedChanged);
            // 
            // radioButtonLoadFromCOService
            // 
            this.radioButtonLoadFromCOService.AutoSize = true;
            this.radioButtonLoadFromCOService.Location = new System.Drawing.Point(12, 61);
            this.radioButtonLoadFromCOService.Name = "radioButtonLoadFromCOService";
            this.radioButtonLoadFromCOService.Size = new System.Drawing.Size(190, 17);
            this.radioButtonLoadFromCOService.TabIndex = 4;
            this.radioButtonLoadFromCOService.Text = "Load from Cloud Observer Service:";
            this.radioButtonLoadFromCOService.UseVisualStyleBackColor = true;
            this.radioButtonLoadFromCOService.CheckedChanged += new System.EventHandler(this.radioButtonLoadFromCOService_CheckedChanged);
            // 
            // labelDLLFile
            // 
            this.labelDLLFile.AutoSize = true;
            this.labelDLLFile.Location = new System.Drawing.Point(12, 38);
            this.labelDLLFile.Name = "labelDLLFile";
            this.labelDLLFile.Size = new System.Drawing.Size(49, 13);
            this.labelDLLFile.TabIndex = 1;
            this.labelDLLFile.Text = "DLL File:";
            // 
            // textBoxDLLFile
            // 
            this.textBoxDLLFile.Enabled = false;
            this.textBoxDLLFile.Location = new System.Drawing.Point(67, 35);
            this.textBoxDLLFile.Name = "textBoxDLLFile";
            this.textBoxDLLFile.Size = new System.Drawing.Size(384, 20);
            this.textBoxDLLFile.TabIndex = 2;
            // 
            // buttonSelectDLLFile
            // 
            this.buttonSelectDLLFile.Location = new System.Drawing.Point(457, 33);
            this.buttonSelectDLLFile.Name = "buttonSelectDLLFile";
            this.buttonSelectDLLFile.Size = new System.Drawing.Size(25, 23);
            this.buttonSelectDLLFile.TabIndex = 3;
            this.buttonSelectDLLFile.Text = "...";
            this.buttonSelectDLLFile.UseVisualStyleBackColor = true;
            this.buttonSelectDLLFile.Click += new System.EventHandler(this.buttonSelectDLLFile_Click);
            // 
            // openFileDialogSelectDLLFile
            // 
            this.openFileDialogSelectDLLFile.Filter = "Dynamic Link Library (*.dll)|*.dll";
            this.openFileDialogSelectDLLFile.Title = "Select DLL File";
            // 
            // groupBoxServiceDetails
            // 
            this.groupBoxServiceDetails.Controls.Add(this.textBoxServiceDetailsName);
            this.groupBoxServiceDetails.Controls.Add(this.labelServiceDetailsName);
            this.groupBoxServiceDetails.Controls.Add(this.comboBoxServiceDetailsClass);
            this.groupBoxServiceDetails.Controls.Add(this.labelServiceDetailsClass);
            this.groupBoxServiceDetails.Controls.Add(this.comboBoxServiceDetailsInterface);
            this.groupBoxServiceDetails.Controls.Add(this.labelServiceDetailsInterface);
            this.groupBoxServiceDetails.Location = new System.Drawing.Point(12, 186);
            this.groupBoxServiceDetails.Name = "groupBoxServiceDetails";
            this.groupBoxServiceDetails.Size = new System.Drawing.Size(470, 99);
            this.groupBoxServiceDetails.TabIndex = 9;
            this.groupBoxServiceDetails.TabStop = false;
            this.groupBoxServiceDetails.Text = "Service Details";
            // 
            // textBoxServiceDetailsName
            // 
            this.textBoxServiceDetailsName.Enabled = false;
            this.textBoxServiceDetailsName.Location = new System.Drawing.Point(50, 19);
            this.textBoxServiceDetailsName.Name = "textBoxServiceDetailsName";
            this.textBoxServiceDetailsName.Size = new System.Drawing.Size(414, 20);
            this.textBoxServiceDetailsName.TabIndex = 1;
            // 
            // labelServiceDetailsName
            // 
            this.labelServiceDetailsName.AutoSize = true;
            this.labelServiceDetailsName.Location = new System.Drawing.Point(6, 22);
            this.labelServiceDetailsName.Name = "labelServiceDetailsName";
            this.labelServiceDetailsName.Size = new System.Drawing.Size(38, 13);
            this.labelServiceDetailsName.TabIndex = 0;
            this.labelServiceDetailsName.Text = "Name:";
            // 
            // comboBoxServiceDetailsClass
            // 
            this.comboBoxServiceDetailsClass.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxServiceDetailsClass.Enabled = false;
            this.comboBoxServiceDetailsClass.FormattingEnabled = true;
            this.comboBoxServiceDetailsClass.Location = new System.Drawing.Point(50, 72);
            this.comboBoxServiceDetailsClass.Name = "comboBoxServiceDetailsClass";
            this.comboBoxServiceDetailsClass.Size = new System.Drawing.Size(417, 21);
            this.comboBoxServiceDetailsClass.Sorted = true;
            this.comboBoxServiceDetailsClass.TabIndex = 5;
            this.comboBoxServiceDetailsClass.SelectedIndexChanged += new System.EventHandler(this.comboBoxServiceDetailsClass_SelectedIndexChanged);
            // 
            // labelServiceDetailsClass
            // 
            this.labelServiceDetailsClass.AutoSize = true;
            this.labelServiceDetailsClass.Location = new System.Drawing.Point(6, 75);
            this.labelServiceDetailsClass.Name = "labelServiceDetailsClass";
            this.labelServiceDetailsClass.Size = new System.Drawing.Size(35, 13);
            this.labelServiceDetailsClass.TabIndex = 4;
            this.labelServiceDetailsClass.Text = "Class:";
            // 
            // comboBoxServiceDetailsInterface
            // 
            this.comboBoxServiceDetailsInterface.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxServiceDetailsInterface.Enabled = false;
            this.comboBoxServiceDetailsInterface.FormattingEnabled = true;
            this.comboBoxServiceDetailsInterface.Location = new System.Drawing.Point(64, 45);
            this.comboBoxServiceDetailsInterface.Name = "comboBoxServiceDetailsInterface";
            this.comboBoxServiceDetailsInterface.Size = new System.Drawing.Size(400, 21);
            this.comboBoxServiceDetailsInterface.Sorted = true;
            this.comboBoxServiceDetailsInterface.TabIndex = 3;
            this.comboBoxServiceDetailsInterface.SelectedIndexChanged += new System.EventHandler(this.comboBoxServiceDetailsInterface_SelectedIndexChanged);
            // 
            // labelServiceDetailsInterface
            // 
            this.labelServiceDetailsInterface.AutoSize = true;
            this.labelServiceDetailsInterface.Location = new System.Drawing.Point(6, 48);
            this.labelServiceDetailsInterface.Name = "labelServiceDetailsInterface";
            this.labelServiceDetailsInterface.Size = new System.Drawing.Size(52, 13);
            this.labelServiceDetailsInterface.TabIndex = 2;
            this.labelServiceDetailsInterface.Text = "Interface:";
            // 
            // buttonLoadService
            // 
            this.buttonLoadService.Enabled = false;
            this.buttonLoadService.Location = new System.Drawing.Point(341, 291);
            this.buttonLoadService.Name = "buttonLoadService";
            this.buttonLoadService.Size = new System.Drawing.Size(141, 23);
            this.buttonLoadService.TabIndex = 12;
            this.buttonLoadService.Text = "Load Service";
            this.buttonLoadService.UseVisualStyleBackColor = true;
            this.buttonLoadService.Click += new System.EventHandler(this.buttonLoadService_Click);
            // 
            // buttonTestServiceHosting
            // 
            this.buttonTestServiceHosting.Enabled = false;
            this.buttonTestServiceHosting.Location = new System.Drawing.Point(195, 291);
            this.buttonTestServiceHosting.Name = "buttonTestServiceHosting";
            this.buttonTestServiceHosting.Size = new System.Drawing.Size(140, 23);
            this.buttonTestServiceHosting.TabIndex = 11;
            this.buttonTestServiceHosting.Text = "Test Service Hosting";
            this.buttonTestServiceHosting.UseVisualStyleBackColor = true;
            this.buttonTestServiceHosting.Click += new System.EventHandler(this.buttonTestServiceHosting_Click);
            // 
            // checkBoxCopyDLL
            // 
            this.checkBoxCopyDLL.AutoSize = true;
            this.checkBoxCopyDLL.Checked = true;
            this.checkBoxCopyDLL.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxCopyDLL.Location = new System.Drawing.Point(12, 295);
            this.checkBoxCopyDLL.Name = "checkBoxCopyDLL";
            this.checkBoxCopyDLL.Size = new System.Drawing.Size(177, 17);
            this.checkBoxCopyDLL.TabIndex = 10;
            this.checkBoxCopyDLL.Text = "Copy DLL file into local directory";
            this.checkBoxCopyDLL.UseVisualStyleBackColor = true;
            // 
            // labelCOServiceURL
            // 
            this.labelCOServiceURL.AutoSize = true;
            this.labelCOServiceURL.Location = new System.Drawing.Point(12, 87);
            this.labelCOServiceURL.Name = "labelCOServiceURL";
            this.labelCOServiceURL.Size = new System.Drawing.Size(147, 13);
            this.labelCOServiceURL.TabIndex = 5;
            this.labelCOServiceURL.Text = "Cloud Observer Service URL:";
            // 
            // textBoxCOServiceURL
            // 
            this.textBoxCOServiceURL.Enabled = false;
            this.textBoxCOServiceURL.Location = new System.Drawing.Point(165, 84);
            this.textBoxCOServiceURL.Name = "textBoxCOServiceURL";
            this.textBoxCOServiceURL.Size = new System.Drawing.Size(209, 20);
            this.textBoxCOServiceURL.TabIndex = 6;
            // 
            // listBoxCOServiceServices
            // 
            this.listBoxCOServiceServices.Enabled = false;
            this.listBoxCOServiceServices.FormattingEnabled = true;
            this.listBoxCOServiceServices.Location = new System.Drawing.Point(12, 111);
            this.listBoxCOServiceServices.Name = "listBoxCOServiceServices";
            this.listBoxCOServiceServices.Size = new System.Drawing.Size(470, 69);
            this.listBoxCOServiceServices.TabIndex = 8;
            // 
            // buttonGetServicesList
            // 
            this.buttonGetServicesList.Enabled = false;
            this.buttonGetServicesList.Location = new System.Drawing.Point(380, 82);
            this.buttonGetServicesList.Name = "buttonGetServicesList";
            this.buttonGetServicesList.Size = new System.Drawing.Size(102, 23);
            this.buttonGetServicesList.TabIndex = 7;
            this.buttonGetServicesList.Text = "Get Services List";
            this.buttonGetServicesList.UseVisualStyleBackColor = true;
            // 
            // FormLoadServiceDLL
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(494, 326);
            this.Controls.Add(this.buttonGetServicesList);
            this.Controls.Add(this.listBoxCOServiceServices);
            this.Controls.Add(this.textBoxCOServiceURL);
            this.Controls.Add(this.labelCOServiceURL);
            this.Controls.Add(this.checkBoxCopyDLL);
            this.Controls.Add(this.buttonTestServiceHosting);
            this.Controls.Add(this.groupBoxServiceDetails);
            this.Controls.Add(this.buttonLoadService);
            this.Controls.Add(this.buttonSelectDLLFile);
            this.Controls.Add(this.textBoxDLLFile);
            this.Controls.Add(this.labelDLLFile);
            this.Controls.Add(this.radioButtonLoadFromCOService);
            this.Controls.Add(this.radioButtonLoadFromFile);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormLoadServiceDLL";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Load Service DLL";
            this.groupBoxServiceDetails.ResumeLayout(false);
            this.groupBoxServiceDetails.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton radioButtonLoadFromFile;
        private System.Windows.Forms.RadioButton radioButtonLoadFromCOService;
        private System.Windows.Forms.Label labelDLLFile;
        private System.Windows.Forms.TextBox textBoxDLLFile;
        private System.Windows.Forms.Button buttonSelectDLLFile;
        private System.Windows.Forms.OpenFileDialog openFileDialogSelectDLLFile;
        private System.Windows.Forms.GroupBox groupBoxServiceDetails;
        private System.Windows.Forms.Label labelServiceDetailsInterface;
        private System.Windows.Forms.Button buttonLoadService;
        private System.Windows.Forms.ComboBox comboBoxServiceDetailsInterface;
        private System.Windows.Forms.ComboBox comboBoxServiceDetailsClass;
        private System.Windows.Forms.Label labelServiceDetailsClass;
        private System.Windows.Forms.Button buttonTestServiceHosting;
        private System.Windows.Forms.CheckBox checkBoxCopyDLL;
        private System.Windows.Forms.TextBox textBoxServiceDetailsName;
        private System.Windows.Forms.Label labelServiceDetailsName;
        private System.Windows.Forms.Label labelCOServiceURL;
        private System.Windows.Forms.TextBox textBoxCOServiceURL;
        private System.Windows.Forms.ListBox listBoxCOServiceServices;
        private System.Windows.Forms.Button buttonGetServicesList;
    }
}