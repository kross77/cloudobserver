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
            this.buttonInstallService = new System.Windows.Forms.Button();
            this.buttonUninstallService = new System.Windows.Forms.Button();
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
            this.listViewInstalledServices.FullRowSelect = true;
            this.listViewInstalledServices.Location = new System.Drawing.Point(12, 48);
            this.listViewInstalledServices.MultiSelect = false;
            this.listViewInstalledServices.Name = "listViewInstalledServices";
            this.listViewInstalledServices.Size = new System.Drawing.Size(370, 97);
            this.listViewInstalledServices.TabIndex = 2;
            this.listViewInstalledServices.UseCompatibleStateImageBehavior = false;
            this.listViewInstalledServices.SelectedIndexChanged += new System.EventHandler(this.listViewInstalledServices_SelectedIndexChanged);
            // 
            // buttonInstallService
            // 
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
            this.buttonUninstallService.Enabled = false;
            this.buttonUninstallService.Location = new System.Drawing.Point(200, 151);
            this.buttonUninstallService.Name = "buttonUninstallService";
            this.buttonUninstallService.Size = new System.Drawing.Size(182, 23);
            this.buttonUninstallService.TabIndex = 4;
            this.buttonUninstallService.Text = "Uninstall Service";
            this.buttonUninstallService.UseVisualStyleBackColor = true;
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(394, 186);
            this.Controls.Add(this.buttonUninstallService);
            this.Controls.Add(this.buttonInstallService);
            this.Controls.Add(this.listViewInstalledServices);
            this.Controls.Add(this.labelServices);
            this.Controls.Add(this.radioButtonManualMode);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
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
    }
}

