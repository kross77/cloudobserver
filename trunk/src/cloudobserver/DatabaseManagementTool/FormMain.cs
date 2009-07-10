using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Linq;
using CloudObserverDatabaseLibrary;

namespace DatabaseManagementTool
{
    public partial class FormMain : Form
    {
        CloudObserverDatabase database;
        string databaseName, connection;

        public FormMain()
        {
            InitializeComponent();
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            switch (buttonConnect.Text)
            {
                case "Connect":
                    comboBoxServerName.Enabled = false;
                    comboBoxDatabaseName.Enabled = false;
                    buttonSetupDefaultValues.Enabled = true;
                    buttonClearDatabase.Enabled = true;
                    databaseName = "'" + comboBoxServerName.Text + "." + comboBoxDatabaseName.Text + "'";
                    connection = "Data Source=" + comboBoxServerName.Text + ";Initial Catalog=" + comboBoxDatabaseName.Text + ";Integrated Security=True";
                    database = new CloudObserverDatabase(connection);
                    AddLog("Database " + databaseName + " connected.");
                    buttonConnect.Text = "Disconnect";
                    break;
                case "Disconnect":
                    AddLog("Database " + databaseName + " disconnected.");
                    database = null;
                    databaseName = "";
                    connection = "";
                    comboBoxServerName.Enabled = true;
                    comboBoxDatabaseName.Enabled = true;
                    buttonSetupDefaultValues.Enabled = false;
                    buttonClearDatabase.Enabled = false;
                    buttonConnect.Text = "Connect";
                    break;
            }
        }

        private void buttonSetupDefaultValues_Click(object sender, EventArgs e)
        {
            AddLog("Setting default values into " + databaseName + "...");
            //users
            AddLog("  creating users...");
            int user1 = database.RegisterUser("user1@mail.ru", "1", "User 1");
            AddLog("  'User 1' registered (email: 'user1@mail.ru', password: '1').");
            int user2 = database.RegisterUser("user2@mail.ru", "2", "User 2");
            AddLog("  'User 2' registered (email: 'user2@mail.ru', password: '2').");
            AddLog("  creating users compelete.");

            //groups
            AddLog("  creating groups...");
            int cloudObserverGroup = database.RegisterGroup("Cloud Observer", false);
            AddLog("  private 'Cloud Observer' group registered.");
            int testGroup = database.RegisterGroup("Test Group", true);
            AddLog("  public 'Test Group' group registered.");
            AddLog("  creating groups complete.");

            //group members
            AddLog("  adding group members...");
            database.AddGroupMember(user1, cloudObserverGroup, 0);
            AddLog("  'User 1' was added into 'Cloud Observer' group.");
            database.AddGroupMember(user2, cloudObserverGroup, 0);
            AddLog("  'User 2' was added into 'Cloud Observer' group.");
            database.AddGroupMember(user1, testGroup, 0);
            AddLog("  'User 1' was added into 'Test Group' group.");
            AddLog("  adding group members complete.");

            //cameras
            AddLog("  creating cameras...");
            int defaultCamera = database.RegisterCamera("localhost::52009/defaultCamera", "Default Camera");
            AddLog("  'Default Camera' camera registered (path: 'localhost').");
            int testCamera = database.RegisterCamera("localhost::52009/testCamera", "Test Camera");
            AddLog("  'Test Camera' camera registered (path: 'localhost').");
            AddLog("  creating cameras complete.");

            //group cameras
            AddLog("  adding group cameras...");
            database.AddGroupCamera(defaultCamera, cloudObserverGroup);
            AddLog("  'Default Camera' camera was added into 'Cloud Observer' group.");
            database.AddGroupCamera(testCamera, testGroup);
            AddLog("  'Test Camera' camera was added into 'Test Group' group.");
            AddLog("  adding group cameras complete.");

            //frames
            AddLog("  adding frames...");
            database.AddFrame(testCamera, new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame001), XElement.Parse(global::DatabaseManagementTool.Properties.Resources.DefaultMarker));
            database.AddFrame(testCamera, new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame002), XElement.Parse(global::DatabaseManagementTool.Properties.Resources.DefaultMarker));
            database.AddFrame(testCamera, new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame003), XElement.Parse(global::DatabaseManagementTool.Properties.Resources.DefaultMarker));
            database.AddFrame(testCamera, new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame004), XElement.Parse(global::DatabaseManagementTool.Properties.Resources.DefaultMarker));
            database.AddFrame(testCamera, new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame005), XElement.Parse(global::DatabaseManagementTool.Properties.Resources.DefaultMarker));
            database.AddFrame(testCamera, new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame006), XElement.Parse(global::DatabaseManagementTool.Properties.Resources.DefaultMarker));
            database.AddFrame(testCamera, new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame007), XElement.Parse(global::DatabaseManagementTool.Properties.Resources.DefaultMarker));
            database.AddFrame(testCamera, new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame008), XElement.Parse(global::DatabaseManagementTool.Properties.Resources.DefaultMarker));
            database.AddFrame(testCamera, new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame009), XElement.Parse(global::DatabaseManagementTool.Properties.Resources.DefaultMarker));
            database.AddFrame(testCamera, new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame010), XElement.Parse(global::DatabaseManagementTool.Properties.Resources.DefaultMarker));
            AddLog("  10 default frames was added from 'Default Camera' camera.");
            AddLog("  adding frames complete.");

            AddLog("Setting default values into " + databaseName + " complete.");
        }

        private void buttonClearDatabase_Click(object sender, EventArgs e)
        {
            database.ClearDatabase();
            listBoxActionsLog.Items.Add("Database " + databaseName + " is now empty.");
        }

        private void AddLog(string s)
        {
            listBoxActionsLog.Items.Add(s);
        }
    }
}
