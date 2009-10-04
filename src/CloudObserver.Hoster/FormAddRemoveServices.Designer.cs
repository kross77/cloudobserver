namespace CloudObserver.Hoster
{
    partial class FormAddRemoveServices
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
            this.listViewInstalledServices = new System.Windows.Forms.ListView();
            this.columnHeaderService = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderContract = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderLibrary = new System.Windows.Forms.ColumnHeader();
            this.labelInstalledServices = new System.Windows.Forms.Label();
            this.buttonUninstallService = new System.Windows.Forms.Button();
            this.buttonInstallService = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listViewInstalledServices
            // 
            this.listViewInstalledServices.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.listViewInstalledServices.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderService,
            this.columnHeaderContract,
            this.columnHeaderLibrary});
            this.listViewInstalledServices.FullRowSelect = true;
            this.listViewInstalledServices.Location = new System.Drawing.Point(12, 25);
            this.listViewInstalledServices.Name = "listViewInstalledServices";
            this.listViewInstalledServices.ShowItemToolTips = true;
            this.listViewInstalledServices.Size = new System.Drawing.Size(360, 148);
            this.listViewInstalledServices.TabIndex = 1;
            this.listViewInstalledServices.UseCompatibleStateImageBehavior = false;
            this.listViewInstalledServices.View = System.Windows.Forms.View.Details;
            this.listViewInstalledServices.SelectedIndexChanged += new System.EventHandler(this.listViewInstalledServices_SelectedIndexChanged);
            // 
            // columnHeaderService
            // 
            this.columnHeaderService.Text = "Service";
            this.columnHeaderService.Width = 119;
            // 
            // columnHeaderContract
            // 
            this.columnHeaderContract.Text = "Contract";
            this.columnHeaderContract.Width = 119;
            // 
            // columnHeaderLibrary
            // 
            this.columnHeaderLibrary.Text = "Library";
            this.columnHeaderLibrary.Width = 118;
            // 
            // labelInstalledServices
            // 
            this.labelInstalledServices.AutoSize = true;
            this.labelInstalledServices.Location = new System.Drawing.Point(12, 9);
            this.labelInstalledServices.Name = "labelInstalledServices";
            this.labelInstalledServices.Size = new System.Drawing.Size(93, 13);
            this.labelInstalledServices.TabIndex = 0;
            this.labelInstalledServices.Text = "Installed Services:";
            // 
            // buttonUninstallService
            // 
            this.buttonUninstallService.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonUninstallService.Enabled = false;
            this.buttonUninstallService.Location = new System.Drawing.Point(195, 179);
            this.buttonUninstallService.Name = "buttonUninstallService";
            this.buttonUninstallService.Size = new System.Drawing.Size(177, 23);
            this.buttonUninstallService.TabIndex = 3;
            this.buttonUninstallService.Text = "Uninstall Service";
            this.buttonUninstallService.UseVisualStyleBackColor = true;
            this.buttonUninstallService.Click += new System.EventHandler(this.buttonUninstallService_Click);
            // 
            // buttonInstallService
            // 
            this.buttonInstallService.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonInstallService.Location = new System.Drawing.Point(12, 179);
            this.buttonInstallService.Name = "buttonInstallService";
            this.buttonInstallService.Size = new System.Drawing.Size(177, 23);
            this.buttonInstallService.TabIndex = 2;
            this.buttonInstallService.Text = "Install Service";
            this.buttonInstallService.UseVisualStyleBackColor = true;
            this.buttonInstallService.Click += new System.EventHandler(this.buttonInstallService_Click);
            // 
            // FormAddRemoveServices
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(384, 214);
            this.Controls.Add(this.buttonUninstallService);
            this.Controls.Add(this.buttonInstallService);
            this.Controls.Add(this.listViewInstalledServices);
            this.Controls.Add(this.labelInstalledServices);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(400, 250);
            this.Name = "FormAddRemoveServices";
            this.Text = "Installed Services";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormInstalledServices_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView listViewInstalledServices;
        private System.Windows.Forms.ColumnHeader columnHeaderService;
        private System.Windows.Forms.ColumnHeader columnHeaderContract;
        private System.Windows.Forms.ColumnHeader columnHeaderLibrary;
        private System.Windows.Forms.Label labelInstalledServices;
        private System.Windows.Forms.Button buttonUninstallService;
        private System.Windows.Forms.Button buttonInstallService;
    }
}