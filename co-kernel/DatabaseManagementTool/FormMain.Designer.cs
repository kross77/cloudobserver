namespace DatabaseManagementTool
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
            this.listBoxActionsLog = new System.Windows.Forms.ListBox();
            this.buttonSetupDefaultValues = new System.Windows.Forms.Button();
            this.buttonClearDatabase = new System.Windows.Forms.Button();
            this.labelServerName = new System.Windows.Forms.Label();
            this.labelDatabaseName = new System.Windows.Forms.Label();
            this.comboBoxServerName = new System.Windows.Forms.ComboBox();
            this.comboBoxDatabaseName = new System.Windows.Forms.ComboBox();
            this.labelActionsLog = new System.Windows.Forms.Label();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listBoxActionsLog
            // 
            this.listBoxActionsLog.FormattingEnabled = true;
            this.listBoxActionsLog.HorizontalScrollbar = true;
            this.listBoxActionsLog.Location = new System.Drawing.Point(12, 105);
            this.listBoxActionsLog.Name = "listBoxActionsLog";
            this.listBoxActionsLog.Size = new System.Drawing.Size(370, 277);
            this.listBoxActionsLog.TabIndex = 6;
            // 
            // buttonSetupDefaultValues
            // 
            this.buttonSetupDefaultValues.Enabled = false;
            this.buttonSetupDefaultValues.Location = new System.Drawing.Point(12, 390);
            this.buttonSetupDefaultValues.Name = "buttonSetupDefaultValues";
            this.buttonSetupDefaultValues.Size = new System.Drawing.Size(370, 23);
            this.buttonSetupDefaultValues.TabIndex = 7;
            this.buttonSetupDefaultValues.Text = "Setup Default Values";
            this.buttonSetupDefaultValues.UseVisualStyleBackColor = true;
            this.buttonSetupDefaultValues.Click += new System.EventHandler(this.buttonSetupDefaultValues_Click);
            // 
            // buttonClearDatabase
            // 
            this.buttonClearDatabase.Enabled = false;
            this.buttonClearDatabase.Location = new System.Drawing.Point(12, 419);
            this.buttonClearDatabase.Name = "buttonClearDatabase";
            this.buttonClearDatabase.Size = new System.Drawing.Size(370, 23);
            this.buttonClearDatabase.TabIndex = 8;
            this.buttonClearDatabase.Text = "Clear Database";
            this.buttonClearDatabase.UseVisualStyleBackColor = true;
            this.buttonClearDatabase.Click += new System.EventHandler(this.buttonClearDatabase_Click);
            // 
            // labelServerName
            // 
            this.labelServerName.AutoSize = true;
            this.labelServerName.Location = new System.Drawing.Point(12, 15);
            this.labelServerName.Name = "labelServerName";
            this.labelServerName.Size = new System.Drawing.Size(70, 13);
            this.labelServerName.TabIndex = 0;
            this.labelServerName.Text = "Server name:";
            // 
            // labelDatabaseName
            // 
            this.labelDatabaseName.AutoSize = true;
            this.labelDatabaseName.Location = new System.Drawing.Point(12, 42);
            this.labelDatabaseName.Name = "labelDatabaseName";
            this.labelDatabaseName.Size = new System.Drawing.Size(85, 13);
            this.labelDatabaseName.TabIndex = 2;
            this.labelDatabaseName.Text = "Database name:";
            // 
            // comboBoxServerName
            // 
            this.comboBoxServerName.FormattingEnabled = true;
            this.comboBoxServerName.Items.AddRange(new object[] {
            ".\\sqlexpress"});
            this.comboBoxServerName.Location = new System.Drawing.Point(88, 12);
            this.comboBoxServerName.Name = "comboBoxServerName";
            this.comboBoxServerName.Size = new System.Drawing.Size(298, 21);
            this.comboBoxServerName.TabIndex = 1;
            this.comboBoxServerName.Text = ".\\sqlexpress";
            // 
            // comboBoxDatabaseName
            // 
            this.comboBoxDatabaseName.FormattingEnabled = true;
            this.comboBoxDatabaseName.Items.AddRange(new object[] {
            "CloudObserverDatabase"});
            this.comboBoxDatabaseName.Location = new System.Drawing.Point(103, 39);
            this.comboBoxDatabaseName.Name = "comboBoxDatabaseName";
            this.comboBoxDatabaseName.Size = new System.Drawing.Size(283, 21);
            this.comboBoxDatabaseName.TabIndex = 3;
            this.comboBoxDatabaseName.Text = "CloudObserverDatabase";
            // 
            // labelActionsLog
            // 
            this.labelActionsLog.AutoSize = true;
            this.labelActionsLog.Location = new System.Drawing.Point(12, 89);
            this.labelActionsLog.Name = "labelActionsLog";
            this.labelActionsLog.Size = new System.Drawing.Size(60, 13);
            this.labelActionsLog.TabIndex = 5;
            this.labelActionsLog.Text = "Actons log:";
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(311, 66);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect.TabIndex = 4;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(394, 454);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.labelActionsLog);
            this.Controls.Add(this.comboBoxDatabaseName);
            this.Controls.Add(this.comboBoxServerName);
            this.Controls.Add(this.labelDatabaseName);
            this.Controls.Add(this.labelServerName);
            this.Controls.Add(this.buttonClearDatabase);
            this.Controls.Add(this.buttonSetupDefaultValues);
            this.Controls.Add(this.listBoxActionsLog);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "FormMain";
            this.Text = "Database Management Tool";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelServerName;
        private System.Windows.Forms.ComboBox comboBoxServerName;
        private System.Windows.Forms.Label labelDatabaseName;
        private System.Windows.Forms.ComboBox comboBoxDatabaseName;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.Label labelActionsLog;
        private System.Windows.Forms.ListBox listBoxActionsLog;
        private System.Windows.Forms.Button buttonSetupDefaultValues;
        private System.Windows.Forms.Button buttonClearDatabase;
    }
}

