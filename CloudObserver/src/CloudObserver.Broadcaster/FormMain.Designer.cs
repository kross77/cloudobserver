namespace CloudObserver.Broadcaster
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
            this.buttonConnect = new System.Windows.Forms.Button();
            this.textBoxControllerServiceUri = new System.Windows.Forms.TextBox();
            this.labelControllerServiceUri = new System.Windows.Forms.Label();
            this.listViewBroadcasts = new System.Windows.Forms.ListView();
            this.columnHeaderCameraID = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderType = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderFormat = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderSource = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderFPS = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderStatus = new System.Windows.Forms.ColumnHeader();
            this.labelBroadcasts = new System.Windows.Forms.Label();
            this.buttonInstallBroadcast = new System.Windows.Forms.Button();
            this.buttonUninstallBroadcast = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonConnect
            // 
            this.buttonConnect.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonConnect.Location = new System.Drawing.Point(597, 12);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 2;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // textBoxControllerServiceUri
            // 
            this.textBoxControllerServiceUri.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxControllerServiceUri.Location = new System.Drawing.Point(133, 14);
            this.textBoxControllerServiceUri.Name = "textBoxControllerServiceUri";
            this.textBoxControllerServiceUri.Size = new System.Drawing.Size(458, 20);
            this.textBoxControllerServiceUri.TabIndex = 1;
            this.textBoxControllerServiceUri.Text = "http://";
            this.textBoxControllerServiceUri.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxControllerServiceUri_KeyPress);
            // 
            // labelControllerServiceUri
            // 
            this.labelControllerServiceUri.AutoSize = true;
            this.labelControllerServiceUri.Location = new System.Drawing.Point(12, 17);
            this.labelControllerServiceUri.Name = "labelControllerServiceUri";
            this.labelControllerServiceUri.Size = new System.Drawing.Size(115, 13);
            this.labelControllerServiceUri.TabIndex = 0;
            this.labelControllerServiceUri.Text = "Controller Service URI:";
            // 
            // listViewBroadcasts
            // 
            this.listViewBroadcasts.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.listViewBroadcasts.CheckBoxes = true;
            this.listViewBroadcasts.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderCameraID,
            this.columnHeaderType,
            this.columnHeaderFormat,
            this.columnHeaderSource,
            this.columnHeaderFPS,
            this.columnHeaderStatus});
            this.listViewBroadcasts.Enabled = false;
            this.listViewBroadcasts.FullRowSelect = true;
            this.listViewBroadcasts.Location = new System.Drawing.Point(12, 53);
            this.listViewBroadcasts.MultiSelect = false;
            this.listViewBroadcasts.Name = "listViewBroadcasts";
            this.listViewBroadcasts.Size = new System.Drawing.Size(660, 220);
            this.listViewBroadcasts.TabIndex = 4;
            this.listViewBroadcasts.UseCompatibleStateImageBehavior = false;
            this.listViewBroadcasts.View = System.Windows.Forms.View.Details;
            this.listViewBroadcasts.Resize += new System.EventHandler(this.listViewBroadcasts_Resize);
            this.listViewBroadcasts.ItemChecked += new System.Windows.Forms.ItemCheckedEventHandler(this.listViewBroadcasts_ItemChecked);
            this.listViewBroadcasts.SelectedIndexChanged += new System.EventHandler(this.listViewBroadcasts_SelectedIndexChanged);
            // 
            // columnHeaderCameraID
            // 
            this.columnHeaderCameraID.Text = "Camera ID";
            this.columnHeaderCameraID.Width = 65;
            // 
            // columnHeaderType
            // 
            this.columnHeaderType.Text = "Type";
            this.columnHeaderType.Width = 150;
            // 
            // columnHeaderFormat
            // 
            this.columnHeaderFormat.Text = "Format";
            // 
            // columnHeaderSource
            // 
            this.columnHeaderSource.Text = "Source";
            this.columnHeaderSource.Width = 230;
            // 
            // columnHeaderFPS
            // 
            this.columnHeaderFPS.Text = "FPS (real/max)";
            this.columnHeaderFPS.Width = 90;
            // 
            // columnHeaderStatus
            // 
            this.columnHeaderStatus.Text = "Status";
            // 
            // labelBroadcasts
            // 
            this.labelBroadcasts.AutoSize = true;
            this.labelBroadcasts.Location = new System.Drawing.Point(12, 37);
            this.labelBroadcasts.Name = "labelBroadcasts";
            this.labelBroadcasts.Size = new System.Drawing.Size(63, 13);
            this.labelBroadcasts.TabIndex = 3;
            this.labelBroadcasts.Text = "Broadcasts:";
            // 
            // buttonInstallBroadcast
            // 
            this.buttonInstallBroadcast.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonInstallBroadcast.Enabled = false;
            this.buttonInstallBroadcast.Location = new System.Drawing.Point(316, 279);
            this.buttonInstallBroadcast.Name = "buttonInstallBroadcast";
            this.buttonInstallBroadcast.Size = new System.Drawing.Size(175, 23);
            this.buttonInstallBroadcast.TabIndex = 5;
            this.buttonInstallBroadcast.Text = "Install Broadcast";
            this.buttonInstallBroadcast.UseVisualStyleBackColor = true;
            this.buttonInstallBroadcast.Click += new System.EventHandler(this.buttonInstallBroadcast_Click);
            // 
            // buttonUninstallBroadcast
            // 
            this.buttonUninstallBroadcast.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonUninstallBroadcast.Enabled = false;
            this.buttonUninstallBroadcast.Location = new System.Drawing.Point(497, 279);
            this.buttonUninstallBroadcast.Name = "buttonUninstallBroadcast";
            this.buttonUninstallBroadcast.Size = new System.Drawing.Size(175, 23);
            this.buttonUninstallBroadcast.TabIndex = 6;
            this.buttonUninstallBroadcast.Text = "Uninstall Broadcast";
            this.buttonUninstallBroadcast.UseVisualStyleBackColor = true;
            this.buttonUninstallBroadcast.Click += new System.EventHandler(this.buttonUninstallBroadcast_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(684, 314);
            this.Controls.Add(this.buttonUninstallBroadcast);
            this.Controls.Add(this.buttonInstallBroadcast);
            this.Controls.Add(this.listViewBroadcasts);
            this.Controls.Add(this.labelBroadcasts);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.textBoxControllerServiceUri);
            this.Controls.Add(this.labelControllerServiceUri);
            this.MinimumSize = new System.Drawing.Size(700, 350);
            this.Name = "FormMain";
            this.Text = "Cloud Observer Broadcaster";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.TextBox textBoxControllerServiceUri;
        private System.Windows.Forms.Label labelControllerServiceUri;
        private System.Windows.Forms.ListView listViewBroadcasts;
        private System.Windows.Forms.Label labelBroadcasts;
        private System.Windows.Forms.ColumnHeader columnHeaderCameraID;
        private System.Windows.Forms.ColumnHeader columnHeaderType;
        private System.Windows.Forms.ColumnHeader columnHeaderFormat;
        private System.Windows.Forms.ColumnHeader columnHeaderSource;
        private System.Windows.Forms.ColumnHeader columnHeaderFPS;
        private System.Windows.Forms.ColumnHeader columnHeaderStatus;
        private System.Windows.Forms.Button buttonInstallBroadcast;
        private System.Windows.Forms.Button buttonUninstallBroadcast;
    }
}

