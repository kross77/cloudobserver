namespace CloudObserver.Hoster
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
            this.checkBoxHostControllerService = new System.Windows.Forms.CheckBox();
            this.labelControllerServiceUri = new System.Windows.Forms.Label();
            this.textBoxControllerServiceUri = new System.Windows.Forms.TextBox();
            this.checkBoxAutomaticServicesManagement = new System.Windows.Forms.CheckBox();
            this.buttonInstalledServices = new System.Windows.Forms.Button();
            this.labelServices = new System.Windows.Forms.Label();
            this.listViewServices = new System.Windows.Forms.ListView();
            this.columnHeaderType = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderName = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderAddress = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderBindings = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderStatus = new System.Windows.Forms.ColumnHeader();
            this.buttonAddService = new System.Windows.Forms.Button();
            this.buttonRemoveService = new System.Windows.Forms.Button();
            this.groupBoxPoliciesManagement = new System.Windows.Forms.GroupBox();
            this.buttonAdd = new System.Windows.Forms.Button();
            this.buttonRemove = new System.Windows.Forms.Button();
            this.numericUpDownPort = new System.Windows.Forms.NumericUpDown();
            this.labelPort = new System.Windows.Forms.Label();
            this.listBoxControlledPorts = new System.Windows.Forms.ListBox();
            this.labelControlledPorts = new System.Windows.Forms.Label();
            this.checkBoxAutomaticPoliciesManagement = new System.Windows.Forms.CheckBox();
            this.labelExternalIP = new System.Windows.Forms.Label();
            this.textBoxExternalIP = new System.Windows.Forms.TextBox();
            this.checkBoxModify = new System.Windows.Forms.CheckBox();
            this.numericUpDownControllerServicePort = new System.Windows.Forms.NumericUpDown();
            this.labelControllerServicePort = new System.Windows.Forms.Label();
            this.groupBoxPoliciesManagement.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPort)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownControllerServicePort)).BeginInit();
            this.SuspendLayout();
            // 
            // checkBoxHostControllerService
            // 
            this.checkBoxHostControllerService.AutoSize = true;
            this.checkBoxHostControllerService.Location = new System.Drawing.Point(12, 12);
            this.checkBoxHostControllerService.Name = "checkBoxHostControllerService";
            this.checkBoxHostControllerService.Size = new System.Drawing.Size(208, 17);
            this.checkBoxHostControllerService.TabIndex = 0;
            this.checkBoxHostControllerService.Text = "Host controller service on this machine";
            this.checkBoxHostControllerService.UseVisualStyleBackColor = true;
            this.checkBoxHostControllerService.CheckedChanged += new System.EventHandler(this.checkBoxHostControllerService_CheckedChanged);
            // 
            // labelControllerServiceUri
            // 
            this.labelControllerServiceUri.AutoSize = true;
            this.labelControllerServiceUri.Location = new System.Drawing.Point(12, 41);
            this.labelControllerServiceUri.Name = "labelControllerServiceUri";
            this.labelControllerServiceUri.Size = new System.Drawing.Size(115, 13);
            this.labelControllerServiceUri.TabIndex = 4;
            this.labelControllerServiceUri.Text = "Controller Service URI:";
            // 
            // textBoxControllerServiceUri
            // 
            this.textBoxControllerServiceUri.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxControllerServiceUri.Location = new System.Drawing.Point(133, 38);
            this.textBoxControllerServiceUri.Name = "textBoxControllerServiceUri";
            this.textBoxControllerServiceUri.Size = new System.Drawing.Size(338, 20);
            this.textBoxControllerServiceUri.TabIndex = 5;
            this.textBoxControllerServiceUri.Text = "http://";
            // 
            // checkBoxAutomaticServicesManagement
            // 
            this.checkBoxAutomaticServicesManagement.AutoSize = true;
            this.checkBoxAutomaticServicesManagement.Location = new System.Drawing.Point(12, 68);
            this.checkBoxAutomaticServicesManagement.Name = "checkBoxAutomaticServicesManagement";
            this.checkBoxAutomaticServicesManagement.Size = new System.Drawing.Size(179, 17);
            this.checkBoxAutomaticServicesManagement.TabIndex = 6;
            this.checkBoxAutomaticServicesManagement.Text = "Automatic services management";
            this.checkBoxAutomaticServicesManagement.UseVisualStyleBackColor = true;
            // 
            // buttonInstalledServices
            // 
            this.buttonInstalledServices.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonInstalledServices.Location = new System.Drawing.Point(407, 64);
            this.buttonInstalledServices.Name = "buttonInstalledServices";
            this.buttonInstalledServices.Size = new System.Drawing.Size(157, 23);
            this.buttonInstalledServices.TabIndex = 7;
            this.buttonInstalledServices.Text = "Installed Services";
            this.buttonInstalledServices.UseVisualStyleBackColor = true;
            // 
            // labelServices
            // 
            this.labelServices.AutoSize = true;
            this.labelServices.Location = new System.Drawing.Point(9, 88);
            this.labelServices.Name = "labelServices";
            this.labelServices.Size = new System.Drawing.Size(51, 13);
            this.labelServices.TabIndex = 8;
            this.labelServices.Text = "Services:";
            // 
            // listViewServices
            // 
            this.listViewServices.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.listViewServices.CheckBoxes = true;
            this.listViewServices.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderType,
            this.columnHeaderName,
            this.columnHeaderAddress,
            this.columnHeaderBindings,
            this.columnHeaderStatus});
            this.listViewServices.FullRowSelect = true;
            this.listViewServices.Location = new System.Drawing.Point(12, 104);
            this.listViewServices.MultiSelect = false;
            this.listViewServices.Name = "listViewServices";
            this.listViewServices.Size = new System.Drawing.Size(552, 123);
            this.listViewServices.TabIndex = 9;
            this.listViewServices.UseCompatibleStateImageBehavior = false;
            this.listViewServices.View = System.Windows.Forms.View.Details;
            // 
            // columnHeaderType
            // 
            this.columnHeaderType.Text = "Type";
            this.columnHeaderType.Width = 100;
            // 
            // columnHeaderName
            // 
            this.columnHeaderName.Text = "Name";
            this.columnHeaderName.Width = 100;
            // 
            // columnHeaderAddress
            // 
            this.columnHeaderAddress.Text = "Address";
            this.columnHeaderAddress.Width = 188;
            // 
            // columnHeaderBindings
            // 
            this.columnHeaderBindings.Text = "Bindings";
            this.columnHeaderBindings.Width = 100;
            // 
            // columnHeaderStatus
            // 
            this.columnHeaderStatus.Text = "Status";
            // 
            // buttonAddService
            // 
            this.buttonAddService.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonAddService.Location = new System.Drawing.Point(12, 233);
            this.buttonAddService.Name = "buttonAddService";
            this.buttonAddService.Size = new System.Drawing.Size(100, 23);
            this.buttonAddService.TabIndex = 10;
            this.buttonAddService.Text = "Add Service";
            this.buttonAddService.UseVisualStyleBackColor = true;
            // 
            // buttonRemoveService
            // 
            this.buttonRemoveService.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonRemoveService.Enabled = false;
            this.buttonRemoveService.Location = new System.Drawing.Point(118, 233);
            this.buttonRemoveService.Name = "buttonRemoveService";
            this.buttonRemoveService.Size = new System.Drawing.Size(100, 23);
            this.buttonRemoveService.TabIndex = 11;
            this.buttonRemoveService.Text = "Remove Service";
            this.buttonRemoveService.UseVisualStyleBackColor = true;
            // 
            // groupBoxPoliciesManagement
            // 
            this.groupBoxPoliciesManagement.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxPoliciesManagement.Controls.Add(this.buttonAdd);
            this.groupBoxPoliciesManagement.Controls.Add(this.buttonRemove);
            this.groupBoxPoliciesManagement.Controls.Add(this.numericUpDownPort);
            this.groupBoxPoliciesManagement.Controls.Add(this.labelPort);
            this.groupBoxPoliciesManagement.Controls.Add(this.listBoxControlledPorts);
            this.groupBoxPoliciesManagement.Controls.Add(this.labelControlledPorts);
            this.groupBoxPoliciesManagement.Controls.Add(this.checkBoxAutomaticPoliciesManagement);
            this.groupBoxPoliciesManagement.Location = new System.Drawing.Point(570, 12);
            this.groupBoxPoliciesManagement.Name = "groupBoxPoliciesManagement";
            this.groupBoxPoliciesManagement.Size = new System.Drawing.Size(130, 250);
            this.groupBoxPoliciesManagement.TabIndex = 12;
            this.groupBoxPoliciesManagement.TabStop = false;
            this.groupBoxPoliciesManagement.Text = "Policies management:";
            // 
            // buttonAdd
            // 
            this.buttonAdd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonAdd.Enabled = false;
            this.buttonAdd.Location = new System.Drawing.Point(9, 221);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(54, 23);
            this.buttonAdd.TabIndex = 5;
            this.buttonAdd.Text = "Add";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click);
            // 
            // buttonRemove
            // 
            this.buttonRemove.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonRemove.Enabled = false;
            this.buttonRemove.Location = new System.Drawing.Point(69, 221);
            this.buttonRemove.Name = "buttonRemove";
            this.buttonRemove.Size = new System.Drawing.Size(55, 23);
            this.buttonRemove.TabIndex = 6;
            this.buttonRemove.Text = "Remove";
            this.buttonRemove.UseVisualStyleBackColor = true;
            this.buttonRemove.Click += new System.EventHandler(this.buttonRemove_Click);
            // 
            // numericUpDownPort
            // 
            this.numericUpDownPort.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.numericUpDownPort.Enabled = false;
            this.numericUpDownPort.Location = new System.Drawing.Point(41, 195);
            this.numericUpDownPort.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.numericUpDownPort.Minimum = new decimal(new int[] {
            1024,
            0,
            0,
            0});
            this.numericUpDownPort.Name = "numericUpDownPort";
            this.numericUpDownPort.Size = new System.Drawing.Size(52, 20);
            this.numericUpDownPort.TabIndex = 4;
            this.numericUpDownPort.Value = new decimal(new int[] {
            9000,
            0,
            0,
            0});
            // 
            // labelPort
            // 
            this.labelPort.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelPort.AutoSize = true;
            this.labelPort.Location = new System.Drawing.Point(6, 197);
            this.labelPort.Name = "labelPort";
            this.labelPort.Size = new System.Drawing.Size(29, 13);
            this.labelPort.TabIndex = 3;
            this.labelPort.Text = "Port:";
            // 
            // listBoxControlledPorts
            // 
            this.listBoxControlledPorts.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.listBoxControlledPorts.FormattingEnabled = true;
            this.listBoxControlledPorts.Location = new System.Drawing.Point(6, 55);
            this.listBoxControlledPorts.Name = "listBoxControlledPorts";
            this.listBoxControlledPorts.ScrollAlwaysVisible = true;
            this.listBoxControlledPorts.Size = new System.Drawing.Size(118, 134);
            this.listBoxControlledPorts.Sorted = true;
            this.listBoxControlledPorts.TabIndex = 2;
            this.listBoxControlledPorts.SelectedIndexChanged += new System.EventHandler(this.listBoxControlledPorts_SelectedIndexChanged);
            // 
            // labelControlledPorts
            // 
            this.labelControlledPorts.AutoSize = true;
            this.labelControlledPorts.Location = new System.Drawing.Point(6, 39);
            this.labelControlledPorts.Name = "labelControlledPorts";
            this.labelControlledPorts.Size = new System.Drawing.Size(83, 13);
            this.labelControlledPorts.TabIndex = 1;
            this.labelControlledPorts.Text = "Controlled ports:";
            // 
            // checkBoxAutomaticPoliciesManagement
            // 
            this.checkBoxAutomaticPoliciesManagement.AutoSize = true;
            this.checkBoxAutomaticPoliciesManagement.Checked = true;
            this.checkBoxAutomaticPoliciesManagement.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxAutomaticPoliciesManagement.Location = new System.Drawing.Point(6, 19);
            this.checkBoxAutomaticPoliciesManagement.Name = "checkBoxAutomaticPoliciesManagement";
            this.checkBoxAutomaticPoliciesManagement.Size = new System.Drawing.Size(73, 17);
            this.checkBoxAutomaticPoliciesManagement.TabIndex = 0;
            this.checkBoxAutomaticPoliciesManagement.Text = "Automatic";
            this.checkBoxAutomaticPoliciesManagement.UseVisualStyleBackColor = true;
            this.checkBoxAutomaticPoliciesManagement.CheckedChanged += new System.EventHandler(this.checkBoxAutomaticPoliciesManagement_CheckedChanged);
            // 
            // labelExternalIP
            // 
            this.labelExternalIP.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.labelExternalIP.AutoSize = true;
            this.labelExternalIP.Location = new System.Drawing.Point(344, 15);
            this.labelExternalIP.Name = "labelExternalIP";
            this.labelExternalIP.Size = new System.Drawing.Size(61, 13);
            this.labelExternalIP.TabIndex = 1;
            this.labelExternalIP.Text = "External IP:";
            // 
            // textBoxExternalIP
            // 
            this.textBoxExternalIP.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxExternalIP.Location = new System.Drawing.Point(411, 12);
            this.textBoxExternalIP.Name = "textBoxExternalIP";
            this.textBoxExternalIP.ReadOnly = true;
            this.textBoxExternalIP.Size = new System.Drawing.Size(90, 20);
            this.textBoxExternalIP.TabIndex = 2;
            this.textBoxExternalIP.Leave += new System.EventHandler(this.textBoxExternalIP_Leave);
            this.textBoxExternalIP.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxExternalIP_KeyPress);
            // 
            // checkBoxModify
            // 
            this.checkBoxModify.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.checkBoxModify.AutoSize = true;
            this.checkBoxModify.Location = new System.Drawing.Point(507, 12);
            this.checkBoxModify.Name = "checkBoxModify";
            this.checkBoxModify.Size = new System.Drawing.Size(57, 17);
            this.checkBoxModify.TabIndex = 3;
            this.checkBoxModify.Text = "Modify";
            this.checkBoxModify.UseVisualStyleBackColor = true;
            this.checkBoxModify.CheckedChanged += new System.EventHandler(this.checkBoxModify_CheckedChanged);
            // 
            // numericUpDownControllerServicePort
            // 
            this.numericUpDownControllerServicePort.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.numericUpDownControllerServicePort.Enabled = false;
            this.numericUpDownControllerServicePort.Location = new System.Drawing.Point(512, 39);
            this.numericUpDownControllerServicePort.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.numericUpDownControllerServicePort.Minimum = new decimal(new int[] {
            1024,
            0,
            0,
            0});
            this.numericUpDownControllerServicePort.Name = "numericUpDownControllerServicePort";
            this.numericUpDownControllerServicePort.Size = new System.Drawing.Size(52, 20);
            this.numericUpDownControllerServicePort.TabIndex = 14;
            this.numericUpDownControllerServicePort.Value = new decimal(new int[] {
            9000,
            0,
            0,
            0});
            this.numericUpDownControllerServicePort.ValueChanged += new System.EventHandler(this.numericUpDownControllerServicePort_ValueChanged);
            // 
            // labelControllerServicePort
            // 
            this.labelControllerServicePort.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelControllerServicePort.AutoSize = true;
            this.labelControllerServicePort.Location = new System.Drawing.Point(477, 41);
            this.labelControllerServicePort.Name = "labelControllerServicePort";
            this.labelControllerServicePort.Size = new System.Drawing.Size(29, 13);
            this.labelControllerServicePort.TabIndex = 13;
            this.labelControllerServicePort.Text = "Port:";
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(712, 274);
            this.Controls.Add(this.numericUpDownControllerServicePort);
            this.Controls.Add(this.labelControllerServicePort);
            this.Controls.Add(this.checkBoxModify);
            this.Controls.Add(this.textBoxExternalIP);
            this.Controls.Add(this.labelExternalIP);
            this.Controls.Add(this.groupBoxPoliciesManagement);
            this.Controls.Add(this.buttonRemoveService);
            this.Controls.Add(this.buttonAddService);
            this.Controls.Add(this.listViewServices);
            this.Controls.Add(this.labelServices);
            this.Controls.Add(this.buttonInstalledServices);
            this.Controls.Add(this.checkBoxAutomaticServicesManagement);
            this.Controls.Add(this.textBoxControllerServiceUri);
            this.Controls.Add(this.labelControllerServiceUri);
            this.Controls.Add(this.checkBoxHostControllerService);
            this.Name = "FormMain";
            this.Text = "Cloud Observer Hoster";
            this.groupBoxPoliciesManagement.ResumeLayout(false);
            this.groupBoxPoliciesManagement.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPort)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownControllerServicePort)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox checkBoxHostControllerService;
        private System.Windows.Forms.Label labelControllerServiceUri;
        private System.Windows.Forms.TextBox textBoxControllerServiceUri;
        private System.Windows.Forms.CheckBox checkBoxAutomaticServicesManagement;
        private System.Windows.Forms.Button buttonInstalledServices;
        private System.Windows.Forms.Label labelServices;
        private System.Windows.Forms.ListView listViewServices;
        private System.Windows.Forms.ColumnHeader columnHeaderType;
        private System.Windows.Forms.ColumnHeader columnHeaderName;
        private System.Windows.Forms.ColumnHeader columnHeaderAddress;
        private System.Windows.Forms.ColumnHeader columnHeaderBindings;
        private System.Windows.Forms.ColumnHeader columnHeaderStatus;
        private System.Windows.Forms.Button buttonAddService;
        private System.Windows.Forms.Button buttonRemoveService;
        private System.Windows.Forms.GroupBox groupBoxPoliciesManagement;
        private System.Windows.Forms.CheckBox checkBoxAutomaticPoliciesManagement;
        private System.Windows.Forms.Label labelPort;
        private System.Windows.Forms.ListBox listBoxControlledPorts;
        private System.Windows.Forms.Label labelControlledPorts;
        private System.Windows.Forms.Button buttonAdd;
        private System.Windows.Forms.Button buttonRemove;
        private System.Windows.Forms.NumericUpDown numericUpDownPort;
        private System.Windows.Forms.Label labelExternalIP;
        private System.Windows.Forms.TextBox textBoxExternalIP;
        private System.Windows.Forms.CheckBox checkBoxModify;
        private System.Windows.Forms.NumericUpDown numericUpDownControllerServicePort;
        private System.Windows.Forms.Label labelControllerServicePort;
    }
}

