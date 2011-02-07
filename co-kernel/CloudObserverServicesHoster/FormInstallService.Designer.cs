namespace CloudObserverServicesHoster
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
            this.labelServices = new System.Windows.Forms.Label();
            this.buttonLoadAdditionalServices = new System.Windows.Forms.Button();
            this.labelPort = new System.Windows.Forms.Label();
            this.numericUpDownPort = new System.Windows.Forms.NumericUpDown();
            this.buttonInstall = new System.Windows.Forms.Button();
            this.listViewServices = new System.Windows.Forms.ListView();
            this.columnHeaderService = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderContract = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderLibrary = new System.Windows.Forms.ColumnHeader();
            this.labelEndpoints = new System.Windows.Forms.Label();
            this.listViewEndpoints = new System.Windows.Forms.ListView();
            this.columnHeaderBinding = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderAddress = new System.Windows.Forms.ColumnHeader();
            this.groupBoxEndpointDetails = new System.Windows.Forms.GroupBox();
            this.comboBoxEndpointBinding = new System.Windows.Forms.ComboBox();
            this.labelEndpointBinding = new System.Windows.Forms.Label();
            this.labelEndpointAddress = new System.Windows.Forms.Label();
            this.textBoxEndpointAddress = new System.Windows.Forms.TextBox();
            this.labelEndpointAddressNote = new System.Windows.Forms.Label();
            this.checkBoxUseDefaultServicesNames = new System.Windows.Forms.CheckBox();
            this.buttonAddEndpoint = new System.Windows.Forms.Button();
            this.labelName = new System.Windows.Forms.Label();
            this.textBoxName = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPort)).BeginInit();
            this.groupBoxEndpointDetails.SuspendLayout();
            this.SuspendLayout();
            // 
            // labelServices
            // 
            this.labelServices.AutoSize = true;
            this.labelServices.Location = new System.Drawing.Point(12, 58);
            this.labelServices.Name = "labelServices";
            this.labelServices.Size = new System.Drawing.Size(51, 13);
            this.labelServices.TabIndex = 3;
            this.labelServices.Text = "Services:";
            // 
            // buttonLoadAdditionalServices
            // 
            this.buttonLoadAdditionalServices.Location = new System.Drawing.Point(200, 177);
            this.buttonLoadAdditionalServices.Name = "buttonLoadAdditionalServices";
            this.buttonLoadAdditionalServices.Size = new System.Drawing.Size(182, 23);
            this.buttonLoadAdditionalServices.TabIndex = 6;
            this.buttonLoadAdditionalServices.Text = "Load Additional Services";
            this.buttonLoadAdditionalServices.UseVisualStyleBackColor = true;
            this.buttonLoadAdditionalServices.Click += new System.EventHandler(this.buttonLoadServiceDLL_Click);
            // 
            // labelPort
            // 
            this.labelPort.AutoSize = true;
            this.labelPort.Location = new System.Drawing.Point(12, 418);
            this.labelPort.Name = "labelPort";
            this.labelPort.Size = new System.Drawing.Size(95, 13);
            this.labelPort.TabIndex = 10;
            this.labelPort.Text = "Port (1024-65535):";
            // 
            // numericUpDownPort
            // 
            this.numericUpDownPort.Location = new System.Drawing.Point(113, 416);
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
            this.numericUpDownPort.Size = new System.Drawing.Size(56, 20);
            this.numericUpDownPort.TabIndex = 11;
            this.numericUpDownPort.Value = new decimal(new int[] {
            9000,
            0,
            0,
            0});
            // 
            // buttonInstall
            // 
            this.buttonInstall.Enabled = false;
            this.buttonInstall.Location = new System.Drawing.Point(175, 413);
            this.buttonInstall.Name = "buttonInstall";
            this.buttonInstall.Size = new System.Drawing.Size(207, 23);
            this.buttonInstall.TabIndex = 12;
            this.buttonInstall.Text = "Install";
            this.buttonInstall.UseVisualStyleBackColor = true;
            this.buttonInstall.Click += new System.EventHandler(this.buttonInstall_Click);
            // 
            // listViewServices
            // 
            this.listViewServices.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderService,
            this.columnHeaderContract,
            this.columnHeaderLibrary});
            this.listViewServices.FullRowSelect = true;
            this.listViewServices.Location = new System.Drawing.Point(12, 74);
            this.listViewServices.Name = "listViewServices";
            this.listViewServices.ShowItemToolTips = true;
            this.listViewServices.Size = new System.Drawing.Size(370, 97);
            this.listViewServices.TabIndex = 4;
            this.listViewServices.UseCompatibleStateImageBehavior = false;
            this.listViewServices.View = System.Windows.Forms.View.Details;
            this.listViewServices.SelectedIndexChanged += new System.EventHandler(this.listViewLoadedServices_SelectedIndexChanged);
            // 
            // columnHeaderService
            // 
            this.columnHeaderService.Text = "Service";
            this.columnHeaderService.Width = 122;
            // 
            // columnHeaderContract
            // 
            this.columnHeaderContract.Text = "Contract";
            this.columnHeaderContract.Width = 122;
            // 
            // columnHeaderLibrary
            // 
            this.columnHeaderLibrary.Text = "Library";
            this.columnHeaderLibrary.Width = 122;
            // 
            // labelEndpoints
            // 
            this.labelEndpoints.AutoSize = true;
            this.labelEndpoints.Location = new System.Drawing.Point(12, 203);
            this.labelEndpoints.Name = "labelEndpoints";
            this.labelEndpoints.Size = new System.Drawing.Size(57, 13);
            this.labelEndpoints.TabIndex = 7;
            this.labelEndpoints.Text = "Endpoints:";
            // 
            // listViewEndpoints
            // 
            this.listViewEndpoints.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderBinding,
            this.columnHeaderAddress});
            this.listViewEndpoints.FullRowSelect = true;
            this.listViewEndpoints.Location = new System.Drawing.Point(12, 219);
            this.listViewEndpoints.MultiSelect = false;
            this.listViewEndpoints.Name = "listViewEndpoints";
            this.listViewEndpoints.ShowItemToolTips = true;
            this.listViewEndpoints.Size = new System.Drawing.Size(370, 97);
            this.listViewEndpoints.TabIndex = 8;
            this.listViewEndpoints.UseCompatibleStateImageBehavior = false;
            this.listViewEndpoints.View = System.Windows.Forms.View.Details;
            // 
            // columnHeaderBinding
            // 
            this.columnHeaderBinding.Text = "Binding";
            this.columnHeaderBinding.Width = 183;
            // 
            // columnHeaderAddress
            // 
            this.columnHeaderAddress.Text = "Address";
            this.columnHeaderAddress.Width = 183;
            // 
            // groupBoxEndpointDetails
            // 
            this.groupBoxEndpointDetails.Controls.Add(this.labelEndpointAddressNote);
            this.groupBoxEndpointDetails.Controls.Add(this.textBoxEndpointAddress);
            this.groupBoxEndpointDetails.Controls.Add(this.labelEndpointAddress);
            this.groupBoxEndpointDetails.Controls.Add(this.comboBoxEndpointBinding);
            this.groupBoxEndpointDetails.Controls.Add(this.labelEndpointBinding);
            this.groupBoxEndpointDetails.Enabled = false;
            this.groupBoxEndpointDetails.Location = new System.Drawing.Point(12, 322);
            this.groupBoxEndpointDetails.Name = "groupBoxEndpointDetails";
            this.groupBoxEndpointDetails.Size = new System.Drawing.Size(370, 85);
            this.groupBoxEndpointDetails.TabIndex = 9;
            this.groupBoxEndpointDetails.TabStop = false;
            this.groupBoxEndpointDetails.Text = "Endpoint details:";
            // 
            // comboBoxEndpointBinding
            // 
            this.comboBoxEndpointBinding.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxEndpointBinding.FormattingEnabled = true;
            this.comboBoxEndpointBinding.Items.AddRange(new object[] {
            "BasicHttpBinding",
            "WSHttpBinding"});
            this.comboBoxEndpointBinding.Location = new System.Drawing.Point(57, 19);
            this.comboBoxEndpointBinding.Name = "comboBoxEndpointBinding";
            this.comboBoxEndpointBinding.Size = new System.Drawing.Size(307, 21);
            this.comboBoxEndpointBinding.TabIndex = 1;
            // 
            // labelEndpointBinding
            // 
            this.labelEndpointBinding.AutoSize = true;
            this.labelEndpointBinding.Location = new System.Drawing.Point(6, 22);
            this.labelEndpointBinding.Name = "labelEndpointBinding";
            this.labelEndpointBinding.Size = new System.Drawing.Size(45, 13);
            this.labelEndpointBinding.TabIndex = 0;
            this.labelEndpointBinding.Text = "Binding:";
            // 
            // labelEndpointAddress
            // 
            this.labelEndpointAddress.AutoSize = true;
            this.labelEndpointAddress.Location = new System.Drawing.Point(6, 49);
            this.labelEndpointAddress.Name = "labelEndpointAddress";
            this.labelEndpointAddress.Size = new System.Drawing.Size(48, 13);
            this.labelEndpointAddress.TabIndex = 2;
            this.labelEndpointAddress.Text = "Address:";
            // 
            // textBoxEndpointAddress
            // 
            this.textBoxEndpointAddress.Location = new System.Drawing.Point(60, 46);
            this.textBoxEndpointAddress.Name = "textBoxEndpointAddress";
            this.textBoxEndpointAddress.Size = new System.Drawing.Size(304, 20);
            this.textBoxEndpointAddress.TabIndex = 3;
            // 
            // labelEndpointAddressNote
            // 
            this.labelEndpointAddressNote.AutoSize = true;
            this.labelEndpointAddressNote.Location = new System.Drawing.Point(6, 69);
            this.labelEndpointAddressNote.Name = "labelEndpointAddressNote";
            this.labelEndpointAddressNote.Size = new System.Drawing.Size(322, 13);
            this.labelEndpointAddressNote.TabIndex = 4;
            this.labelEndpointAddressNote.Text = "NOTE: full address is \'localhost:<port>/<service-name>/<address>\'";
            // 
            // checkBoxUseDefaultServicesNames
            // 
            this.checkBoxUseDefaultServicesNames.AutoSize = true;
            this.checkBoxUseDefaultServicesNames.Checked = true;
            this.checkBoxUseDefaultServicesNames.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxUseDefaultServicesNames.Location = new System.Drawing.Point(12, 38);
            this.checkBoxUseDefaultServicesNames.Name = "checkBoxUseDefaultServicesNames";
            this.checkBoxUseDefaultServicesNames.Size = new System.Drawing.Size(352, 17);
            this.checkBoxUseDefaultServicesNames.TabIndex = 2;
            this.checkBoxUseDefaultServicesNames.Text = "Use default services names (disabling will prevent multi-service install)";
            this.checkBoxUseDefaultServicesNames.UseVisualStyleBackColor = true;
            // 
            // buttonAddEndpoint
            // 
            this.buttonAddEndpoint.Location = new System.Drawing.Point(12, 177);
            this.buttonAddEndpoint.Name = "buttonAddEndpoint";
            this.buttonAddEndpoint.Size = new System.Drawing.Size(182, 23);
            this.buttonAddEndpoint.TabIndex = 5;
            this.buttonAddEndpoint.Text = "Add Endpoint";
            this.buttonAddEndpoint.UseVisualStyleBackColor = true;
            this.buttonAddEndpoint.Click += new System.EventHandler(this.buttonAddEndpoint_Click);
            // 
            // labelName
            // 
            this.labelName.AutoSize = true;
            this.labelName.Location = new System.Drawing.Point(12, 15);
            this.labelName.Name = "labelName";
            this.labelName.Size = new System.Drawing.Size(38, 13);
            this.labelName.TabIndex = 0;
            this.labelName.Text = "Name:";
            // 
            // textBoxName
            // 
            this.textBoxName.Enabled = false;
            this.textBoxName.Location = new System.Drawing.Point(56, 12);
            this.textBoxName.Name = "textBoxName";
            this.textBoxName.Size = new System.Drawing.Size(326, 20);
            this.textBoxName.TabIndex = 1;
            // 
            // FormInstallService
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(394, 448);
            this.Controls.Add(this.textBoxName);
            this.Controls.Add(this.labelName);
            this.Controls.Add(this.buttonAddEndpoint);
            this.Controls.Add(this.checkBoxUseDefaultServicesNames);
            this.Controls.Add(this.groupBoxEndpointDetails);
            this.Controls.Add(this.listViewEndpoints);
            this.Controls.Add(this.labelEndpoints);
            this.Controls.Add(this.listViewServices);
            this.Controls.Add(this.buttonInstall);
            this.Controls.Add(this.numericUpDownPort);
            this.Controls.Add(this.labelPort);
            this.Controls.Add(this.buttonLoadAdditionalServices);
            this.Controls.Add(this.labelServices);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormInstallService";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Install Service";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormInstallService_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPort)).EndInit();
            this.groupBoxEndpointDetails.ResumeLayout(false);
            this.groupBoxEndpointDetails.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelServices;
        private System.Windows.Forms.Button buttonLoadAdditionalServices;
        private System.Windows.Forms.Label labelPort;
        private System.Windows.Forms.NumericUpDown numericUpDownPort;
        private System.Windows.Forms.Button buttonInstall;
        private System.Windows.Forms.ListView listViewServices;
        private System.Windows.Forms.ColumnHeader columnHeaderService;
        private System.Windows.Forms.ColumnHeader columnHeaderContract;
        private System.Windows.Forms.ColumnHeader columnHeaderLibrary;
        private System.Windows.Forms.Label labelEndpoints;
        private System.Windows.Forms.ListView listViewEndpoints;
        private System.Windows.Forms.ColumnHeader columnHeaderBinding;
        private System.Windows.Forms.ColumnHeader columnHeaderAddress;
        private System.Windows.Forms.GroupBox groupBoxEndpointDetails;
        private System.Windows.Forms.ComboBox comboBoxEndpointBinding;
        private System.Windows.Forms.Label labelEndpointBinding;
        private System.Windows.Forms.Label labelEndpointAddress;
        private System.Windows.Forms.Label labelEndpointAddressNote;
        private System.Windows.Forms.TextBox textBoxEndpointAddress;
        private System.Windows.Forms.CheckBox checkBoxUseDefaultServicesNames;
        private System.Windows.Forms.Button buttonAddEndpoint;
        private System.Windows.Forms.Label labelName;
        private System.Windows.Forms.TextBox textBoxName;
    }
}