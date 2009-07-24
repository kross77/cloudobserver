namespace CloudObserverServicesHoster
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
            this.radioButtonManualMode = new System.Windows.Forms.RadioButton();
            this.labelServices = new System.Windows.Forms.Label();
            this.listViewInstalledServices = new System.Windows.Forms.ListView();
            this.columnHeaderDLL = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderInterface = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderClass = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderPort = new System.Windows.Forms.ColumnHeader();
            this.buttonInstallService = new System.Windows.Forms.Button();
            this.buttonUninstallService = new System.Windows.Forms.Button();
            this.columnHeaderStatus = new System.Windows.Forms.ColumnHeader();
            this.SuspendLayout();
            // 
            // radioButtonManualMode
            // 
            this.radioButtonManualMode.AutoSize = true;
            this.radioButtonManualMode.Checked = true;
            this.radioButtonManualMode.Enabled = false;
            this.radioButtonManualMode.Location = new System.Drawing.Point(12, 12);
            this.radioButtonManualMode.Name = "radioButtonManualMode";
            this.radioButtonManualMode.Size = new System.Drawing.Size(92, 17);
            this.radioButtonManualMode.TabIndex = 0;
            this.radioButtonManualMode.TabStop = true;
            this.radioButtonManualMode.Text = "Manual mode:";
            this.radioButtonManualMode.UseVisualStyleBackColor = true;
            // 
            // labelServices
            // 
            this.labelServices.AutoSize = true;
            this.labelServices.Location = new System.Drawing.Point(12, 32);
            this.labelServices.Name = "labelServices";
            this.labelServices.Size = new System.Drawing.Size(51, 13);
            this.labelServices.TabIndex = 1;
            this.labelServices.Text = "Services:";
            // 
            // listViewInstalledServices
            // 
            this.listViewInstalledServices.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.listViewInstalledServices.CheckBoxes = true;
            this.listViewInstalledServices.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderDLL,
            this.columnHeaderInterface,
            this.columnHeaderClass,
            this.columnHeaderPort,
            this.columnHeaderStatus});
            this.listViewInstalledServices.FullRowSelect = true;
            this.listViewInstalledServices.Location = new System.Drawing.Point(12, 48);
            this.listViewInstalledServices.MultiSelect = false;
            this.listViewInstalledServices.Name = "listViewInstalledServices";
            this.listViewInstalledServices.ShowItemToolTips = true;
            this.listViewInstalledServices.Size = new System.Drawing.Size(645, 97);
            this.listViewInstalledServices.TabIndex = 2;
            this.listViewInstalledServices.UseCompatibleStateImageBehavior = false;
            this.listViewInstalledServices.View = System.Windows.Forms.View.Details;
            this.listViewInstalledServices.Resize += new System.EventHandler(this.listViewInstalledServices_Resize);
            this.listViewInstalledServices.ItemChecked += new System.Windows.Forms.ItemCheckedEventHandler(this.listViewInstalledServices_ItemChecked);
            this.listViewInstalledServices.SelectedIndexChanged += new System.EventHandler(this.listViewInstalledServices_SelectedIndexChanged);
            // 
            // columnHeaderDLL
            // 
            this.columnHeaderDLL.Text = "DLL";
            this.columnHeaderDLL.Width = 100;
            // 
            // columnHeaderInterface
            // 
            this.columnHeaderInterface.Text = "Interface";
            this.columnHeaderInterface.Width = 100;
            // 
            // columnHeaderClass
            // 
            this.columnHeaderClass.Text = "Class";
            this.columnHeaderClass.Width = 100;
            // 
            // columnHeaderPort
            // 
            this.columnHeaderPort.Text = "Port";
            this.columnHeaderPort.Width = 50;
            // 
            // buttonInstallService
            // 
            this.buttonInstallService.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonInstallService.Location = new System.Drawing.Point(12, 151);
            this.buttonInstallService.Name = "buttonInstallService";
            this.buttonInstallService.Size = new System.Drawing.Size(182, 23);
            this.buttonInstallService.TabIndex = 3;
            this.buttonInstallService.Text = "Install Service";
            this.buttonInstallService.UseVisualStyleBackColor = true;
            this.buttonInstallService.Click += new System.EventHandler(this.buttonInstallService_Click);
            // 
            // buttonUninstallService
            // 
            this.buttonUninstallService.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonUninstallService.Enabled = false;
            this.buttonUninstallService.Location = new System.Drawing.Point(200, 151);
            this.buttonUninstallService.Name = "buttonUninstallService";
            this.buttonUninstallService.Size = new System.Drawing.Size(182, 23);
            this.buttonUninstallService.TabIndex = 4;
            this.buttonUninstallService.Text = "Uninstall Service";
            this.buttonUninstallService.UseVisualStyleBackColor = true;
            // 
            // columnHeaderStatus
            // 
            this.columnHeaderStatus.Text = "Status";
            this.columnHeaderStatus.Width = 100;
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(669, 186);
            this.Controls.Add(this.buttonUninstallService);
            this.Controls.Add(this.buttonInstallService);
            this.Controls.Add(this.listViewInstalledServices);
            this.Controls.Add(this.labelServices);
            this.Controls.Add(this.radioButtonManualMode);
            this.MaximizeBox = false;
            this.Name = "FormMain";
            this.Text = "Cloud Observer Services Hoster";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton radioButtonManualMode;
        private System.Windows.Forms.Label labelServices;
        private System.Windows.Forms.ListView listViewInstalledServices;
        private System.Windows.Forms.Button buttonInstallService;
        private System.Windows.Forms.Button buttonUninstallService;
        private System.Windows.Forms.ColumnHeader columnHeaderDLL;
        private System.Windows.Forms.ColumnHeader columnHeaderInterface;
        private System.Windows.Forms.ColumnHeader columnHeaderClass;
        private System.Windows.Forms.ColumnHeader columnHeaderPort;
        private System.Windows.Forms.ColumnHeader columnHeaderStatus;
    }
}

