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
            this.labelLoadedServices = new System.Windows.Forms.Label();
            this.buttonLoadServiceDLL = new System.Windows.Forms.Button();
            this.labelServicePort = new System.Windows.Forms.Label();
            this.numericUpDownServicePort = new System.Windows.Forms.NumericUpDown();
            this.buttonInstall = new System.Windows.Forms.Button();
            this.listViewLoadedServices = new System.Windows.Forms.ListView();
            this.columnHeaderServiceDLL = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderServiceInterface = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderServiceClass = new System.Windows.Forms.ColumnHeader();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownServicePort)).BeginInit();
            this.SuspendLayout();
            // 
            // labelLoadedServices
            // 
            this.labelLoadedServices.AutoSize = true;
            this.labelLoadedServices.Location = new System.Drawing.Point(12, 9);
            this.labelLoadedServices.Name = "labelLoadedServices";
            this.labelLoadedServices.Size = new System.Drawing.Size(88, 13);
            this.labelLoadedServices.TabIndex = 0;
            this.labelLoadedServices.Text = "Loaded services:";
            // 
            // buttonLoadServiceDLL
            // 
            this.buttonLoadServiceDLL.Location = new System.Drawing.Point(278, 128);
            this.buttonLoadServiceDLL.Name = "buttonLoadServiceDLL";
            this.buttonLoadServiceDLL.Size = new System.Drawing.Size(104, 23);
            this.buttonLoadServiceDLL.TabIndex = 2;
            this.buttonLoadServiceDLL.Text = "Load Service DLL";
            this.buttonLoadServiceDLL.UseVisualStyleBackColor = true;
            this.buttonLoadServiceDLL.Click += new System.EventHandler(this.buttonLoadServiceDLL_Click);
            // 
            // labelServicePort
            // 
            this.labelServicePort.AutoSize = true;
            this.labelServicePort.Location = new System.Drawing.Point(12, 131);
            this.labelServicePort.Name = "labelServicePort";
            this.labelServicePort.Size = new System.Drawing.Size(67, 13);
            this.labelServicePort.TabIndex = 3;
            this.labelServicePort.Text = "Service port:";
            // 
            // numericUpDownServicePort
            // 
            this.numericUpDownServicePort.Location = new System.Drawing.Point(85, 128);
            this.numericUpDownServicePort.Maximum = new decimal(new int[] {
            99999,
            0,
            0,
            0});
            this.numericUpDownServicePort.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDownServicePort.Name = "numericUpDownServicePort";
            this.numericUpDownServicePort.Size = new System.Drawing.Size(56, 20);
            this.numericUpDownServicePort.TabIndex = 4;
            this.numericUpDownServicePort.Value = new decimal(new int[] {
            9000,
            0,
            0,
            0});
            // 
            // buttonInstall
            // 
            this.buttonInstall.Enabled = false;
            this.buttonInstall.Location = new System.Drawing.Point(147, 128);
            this.buttonInstall.Name = "buttonInstall";
            this.buttonInstall.Size = new System.Drawing.Size(125, 23);
            this.buttonInstall.TabIndex = 5;
            this.buttonInstall.Text = "Install";
            this.buttonInstall.UseVisualStyleBackColor = true;
            this.buttonInstall.Click += new System.EventHandler(this.buttonInstall_Click);
            // 
            // listViewLoadedServices
            // 
            this.listViewLoadedServices.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderServiceDLL,
            this.columnHeaderServiceInterface,
            this.columnHeaderServiceClass});
            this.listViewLoadedServices.FullRowSelect = true;
            this.listViewLoadedServices.Location = new System.Drawing.Point(12, 25);
            this.listViewLoadedServices.Name = "listViewLoadedServices";
            this.listViewLoadedServices.ShowItemToolTips = true;
            this.listViewLoadedServices.Size = new System.Drawing.Size(370, 97);
            this.listViewLoadedServices.TabIndex = 6;
            this.listViewLoadedServices.UseCompatibleStateImageBehavior = false;
            this.listViewLoadedServices.View = System.Windows.Forms.View.Details;
            this.listViewLoadedServices.SelectedIndexChanged += new System.EventHandler(this.listViewLoadedServices_SelectedIndexChanged);
            // 
            // columnHeaderServiceDLL
            // 
            this.columnHeaderServiceDLL.Text = "DLL";
            this.columnHeaderServiceDLL.Width = 122;
            // 
            // columnHeaderServiceInterface
            // 
            this.columnHeaderServiceInterface.Text = "Interface";
            this.columnHeaderServiceInterface.Width = 122;
            // 
            // columnHeaderServiceClass
            // 
            this.columnHeaderServiceClass.Text = "Class";
            this.columnHeaderServiceClass.Width = 122;
            // 
            // FormInstallService
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(394, 163);
            this.Controls.Add(this.listViewLoadedServices);
            this.Controls.Add(this.buttonInstall);
            this.Controls.Add(this.numericUpDownServicePort);
            this.Controls.Add(this.labelServicePort);
            this.Controls.Add(this.buttonLoadServiceDLL);
            this.Controls.Add(this.labelLoadedServices);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormInstallService";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Install Service";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormInstallService_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownServicePort)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelLoadedServices;
        private System.Windows.Forms.Button buttonLoadServiceDLL;
        private System.Windows.Forms.Label labelServicePort;
        private System.Windows.Forms.NumericUpDown numericUpDownServicePort;
        private System.Windows.Forms.Button buttonInstall;
        private System.Windows.Forms.ListView listViewLoadedServices;
        private System.Windows.Forms.ColumnHeader columnHeaderServiceDLL;
        private System.Windows.Forms.ColumnHeader columnHeaderServiceInterface;
        private System.Windows.Forms.ColumnHeader columnHeaderServiceClass;
    }
}