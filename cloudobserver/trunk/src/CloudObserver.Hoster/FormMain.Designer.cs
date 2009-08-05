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
            this.buttonAddRemoveServices = new System.Windows.Forms.Button();
            this.labelServices = new System.Windows.Forms.Label();
            this.listViewServices = new System.Windows.Forms.ListView();
            this.columnHeaderType = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderName = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderAddress = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderBindings = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderStatus = new System.Windows.Forms.ColumnHeader();
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
            this.checkBoxAutoDetect = new System.Windows.Forms.CheckBox();
            this.numericUpDownControllerServicePort = new System.Windows.Forms.NumericUpDown();
            this.labelControllerServicePort = new System.Windows.Forms.Label();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.groupBoxPoliciesManagement.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPort)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownControllerServicePort)).BeginInit();
            this.SuspendLayout();
            // 
            // checkBoxHostControllerService
            // 
            this.checkBoxHostControllerService.AutoSize = true;
            this.checkBoxHostControllerService.Location = new System.Drawing.Point(12, 14);
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
            this.labelControllerServiceUri.Location = new System.Drawing.Point(12, 43);
            this.labelControllerServiceUri.Name = "labelControllerServiceUri";
            this.labelControllerServiceUri.Size = new System.Drawing.Size(115, 13);
            this.labelControllerServiceUri.TabIndex = 6;
            this.labelControllerServiceUri.Text = "Controller Service URI:";
            // 
            // textBoxControllerServiceUri
            // 
            this.textBoxControllerServiceUri.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxControllerServiceUri.Location = new System.Drawing.Point(133, 40);
            this.textBoxControllerServiceUri.Name = "textBoxControllerServiceUri";
            this.textBoxControllerServiceUri.Size = new System.Drawing.Size(350, 20);
            this.textBoxControllerServiceUri.TabIndex = 7;
            this.textBoxControllerServiceUri.Text = "http://";
            // 
            // checkBoxAutomaticServicesManagement
            // 
            this.checkBoxAutomaticServicesManagement.AutoSize = true;
            this.checkBoxAutomaticServicesManagement.Checked = true;
            this.checkBoxAutomaticServicesManagement.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxAutomaticServicesManagement.Enabled = false;
            this.checkBoxAutomaticServicesManagement.Location = new System.Drawing.Point(12, 71);
            this.checkBoxAutomaticServicesManagement.Name = "checkBoxAutomaticServicesManagement";
            this.checkBoxAutomaticServicesManagement.Size = new System.Drawing.Size(179, 17);
            this.checkBoxAutomaticServicesManagement.TabIndex = 9;
            this.checkBoxAutomaticServicesManagement.Text = "Automatic services management";
            this.checkBoxAutomaticServicesManagement.UseVisualStyleBackColor = true;
            // 
            // buttonAddRemoveServices
            // 
            this.buttonAddRemoveServices.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddRemoveServices.Location = new System.Drawing.Point(407, 67);
            this.buttonAddRemoveServices.Name = "buttonAddRemoveServices";
            this.buttonAddRemoveServices.Size = new System.Drawing.Size(157, 23);
            this.buttonAddRemoveServices.TabIndex = 10;
            this.buttonAddRemoveServices.Text = "Add/Remove services";
            this.buttonAddRemoveServices.UseVisualStyleBackColor = true;
            this.buttonAddRemoveServices.Click += new System.EventHandler(this.buttonInstalledServices_Click);
            // 
            // labelServices
            // 
            this.labelServices.AutoSize = true;
            this.labelServices.Location = new System.Drawing.Point(12, 91);
            this.labelServices.Name = "labelServices";
            this.labelServices.Size = new System.Drawing.Size(51, 13);
            this.labelServices.TabIndex = 11;
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
            this.listViewServices.Location = new System.Drawing.Point(12, 107);
            this.listViewServices.MultiSelect = false;
            this.listViewServices.Name = "listViewServices";
            this.listViewServices.Size = new System.Drawing.Size(552, 245);
            this.listViewServices.TabIndex = 12;
            this.listViewServices.UseCompatibleStateImageBehavior = false;
            this.listViewServices.View = System.Windows.Forms.View.Details;
            // 
            // columnHeaderType
            // 
            this.columnHeaderType.Text = "Type";
            this.columnHeaderType.Width = 150;
            // 
            // columnHeaderName
            // 
            this.columnHeaderName.Text = "Name";
            this.columnHeaderName.Width = 150;
            // 
            // columnHeaderAddress
            // 
            this.columnHeaderAddress.Text = "Address";
            this.columnHeaderAddress.Width = 108;
            // 
            // columnHeaderBindings
            // 
            this.columnHeaderBindings.Text = "Bindings";
            this.columnHeaderBindings.Width = 80;
            // 
            // columnHeaderStatus
            // 
            this.columnHeaderStatus.Text = "Status";
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
            this.groupBoxPoliciesManagement.Location = new System.Drawing.Point(570, 38);
            this.groupBoxPoliciesManagement.Name = "groupBoxPoliciesManagement";
            this.groupBoxPoliciesManagement.Size = new System.Drawing.Size(130, 314);
            this.groupBoxPoliciesManagement.TabIndex = 13;
            this.groupBoxPoliciesManagement.TabStop = false;
            this.groupBoxPoliciesManagement.Text = "Policies management:";
            // 
            // buttonAdd
            // 
            this.buttonAdd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonAdd.Enabled = false;
            this.buttonAdd.Location = new System.Drawing.Point(6, 285);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(56, 23);
            this.buttonAdd.TabIndex = 5;
            this.buttonAdd.Text = "Add";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click);
            // 
            // buttonRemove
            // 
            this.buttonRemove.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonRemove.Enabled = false;
            this.buttonRemove.Location = new System.Drawing.Point(68, 285);
            this.buttonRemove.Name = "buttonRemove";
            this.buttonRemove.Size = new System.Drawing.Size(56, 23);
            this.buttonRemove.TabIndex = 6;
            this.buttonRemove.Text = "Remove";
            this.buttonRemove.UseVisualStyleBackColor = true;
            this.buttonRemove.Click += new System.EventHandler(this.buttonRemove_Click);
            // 
            // numericUpDownPort
            // 
            this.numericUpDownPort.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.numericUpDownPort.Enabled = false;
            this.numericUpDownPort.Location = new System.Drawing.Point(41, 259);
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
            this.labelPort.Location = new System.Drawing.Point(6, 261);
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
            this.listBoxControlledPorts.Size = new System.Drawing.Size(118, 173);
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
            this.labelExternalIP.Location = new System.Drawing.Point(456, 15);
            this.labelExternalIP.Name = "labelExternalIP";
            this.labelExternalIP.Size = new System.Drawing.Size(61, 13);
            this.labelExternalIP.TabIndex = 3;
            this.labelExternalIP.Text = "External IP:";
            // 
            // textBoxExternalIP
            // 
            this.textBoxExternalIP.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxExternalIP.Location = new System.Drawing.Point(523, 12);
            this.textBoxExternalIP.Name = "textBoxExternalIP";
            this.textBoxExternalIP.ReadOnly = true;
            this.textBoxExternalIP.Size = new System.Drawing.Size(90, 20);
            this.textBoxExternalIP.TabIndex = 4;
            this.textBoxExternalIP.Leave += new System.EventHandler(this.textBoxExternalIP_Leave);
            this.textBoxExternalIP.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxExternalIP_KeyPress);
            // 
            // checkBoxAutoDetect
            // 
            this.checkBoxAutoDetect.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.checkBoxAutoDetect.AutoSize = true;
            this.checkBoxAutoDetect.Checked = true;
            this.checkBoxAutoDetect.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxAutoDetect.Location = new System.Drawing.Point(619, 14);
            this.checkBoxAutoDetect.Name = "checkBoxAutoDetect";
            this.checkBoxAutoDetect.Size = new System.Drawing.Size(81, 17);
            this.checkBoxAutoDetect.TabIndex = 5;
            this.checkBoxAutoDetect.Text = "Auto-detect";
            this.checkBoxAutoDetect.UseVisualStyleBackColor = true;
            this.checkBoxAutoDetect.CheckedChanged += new System.EventHandler(this.checkBoxAutoDetect_CheckedChanged);
            // 
            // numericUpDownControllerServicePort
            // 
            this.numericUpDownControllerServicePort.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.numericUpDownControllerServicePort.Location = new System.Drawing.Point(398, 13);
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
            this.numericUpDownControllerServicePort.TabIndex = 2;
            this.numericUpDownControllerServicePort.Value = new decimal(new int[] {
            9000,
            0,
            0,
            0});
            this.numericUpDownControllerServicePort.ValueChanged += new System.EventHandler(this.numericUpDownControllerServicePort_ValueChanged);
            // 
            // labelControllerServicePort
            // 
            this.labelControllerServicePort.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.labelControllerServicePort.AutoSize = true;
            this.labelControllerServicePort.Location = new System.Drawing.Point(363, 15);
            this.labelControllerServicePort.Name = "labelControllerServicePort";
            this.labelControllerServicePort.Size = new System.Drawing.Size(29, 13);
            this.labelControllerServicePort.TabIndex = 1;
            this.labelControllerServicePort.Text = "Port:";
            // 
            // buttonConnect
            // 
            this.buttonConnect.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonConnect.Location = new System.Drawing.Point(489, 38);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 8;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(712, 364);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.numericUpDownControllerServicePort);
            this.Controls.Add(this.labelControllerServicePort);
            this.Controls.Add(this.checkBoxAutoDetect);
            this.Controls.Add(this.textBoxExternalIP);
            this.Controls.Add(this.labelExternalIP);
            this.Controls.Add(this.groupBoxPoliciesManagement);
            this.Controls.Add(this.listViewServices);
            this.Controls.Add(this.labelServices);
            this.Controls.Add(this.buttonAddRemoveServices);
            this.Controls.Add(this.checkBoxAutomaticServicesManagement);
            this.Controls.Add(this.textBoxControllerServiceUri);
            this.Controls.Add(this.labelControllerServiceUri);
            this.Controls.Add(this.checkBoxHostControllerService);
            this.MinimumSize = new System.Drawing.Size(728, 400);
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
        private System.Windows.Forms.Button buttonAddRemoveServices;
        private System.Windows.Forms.Label labelServices;
        private System.Windows.Forms.ListView listViewServices;
        private System.Windows.Forms.ColumnHeader columnHeaderType;
        private System.Windows.Forms.ColumnHeader columnHeaderName;
        private System.Windows.Forms.ColumnHeader columnHeaderAddress;
        private System.Windows.Forms.ColumnHeader columnHeaderBindings;
        private System.Windows.Forms.ColumnHeader columnHeaderStatus;
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
        private System.Windows.Forms.CheckBox checkBoxAutoDetect;
        private System.Windows.Forms.NumericUpDown numericUpDownControllerServicePort;
        private System.Windows.Forms.Label labelControllerServicePort;
        private System.Windows.Forms.Button buttonConnect;
    }
}

