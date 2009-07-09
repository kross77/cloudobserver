using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
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
                    databaseName = comboBoxServerName.Text + "." + comboBoxDatabaseName.Text;
                    connection = "Data Source=" + comboBoxServerName.Text + ";Initial Catalog=" + comboBoxDatabaseName.Text + ";Integrated Security=True";
                    database = new CloudObserverDatabase(connection);
                    listBoxActionsLog.Items.Add("Database '" + databaseName + "' connected.");
                    buttonConnect.Text = "Disconnect";
                    break;
                case "Disconnect":
                    listBoxActionsLog.Items.Add("Database '" + databaseName + "' disconnected.");
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
            //users
            int user1 = database.RegisterUser("user1@mail.ru", "1", "User 1 Name");
            listBoxActionsLog.Items.Add("User 1 registered.");
            int user2 = database.RegisterUser("user2@mail.ru", "2", "User 2 Name");
            listBoxActionsLog.Items.Add("User 2 registered.");
            listBoxActionsLog.Items.Add("User creation finished.");
            listBoxActionsLog.Items.Add("");

            //groups
            int administrationGroup = database.RegisterGroup("Administration Group", false);
            listBoxActionsLog.Items.Add("Private Administration Group registered.");
            int testGroup = database.RegisterGroup("Test Group", true);
            listBoxActionsLog.Items.Add("Public Test Group created.");
            listBoxActionsLog.Items.Add("Group creation finished.");
            listBoxActionsLog.Items.Add("");

            //group members
            database.AddGroupMember(user1, administrationGroup, 0);
            listBoxActionsLog.Items.Add("User 1 entered into Administration Group.");
            database.AddGroupMember(user2, administrationGroup, 0);
            listBoxActionsLog.Items.Add("User 2 entered into Administration Group.");
            database.AddGroupMember(user1, testGroup, 0);
            listBoxActionsLog.Items.Add("User 1 entered into Test Group.");

            listBoxActionsLog.Items.Add("Default values loaded into '" + databaseName + "'.");

            //cameras

            //group cameras

            //frames
        }

        private void buttonClearDatabase_Click(object sender, EventArgs e)
        {
            database.ClearDatabase();
            listBoxActionsLog.Items.Add("Database " + databaseName + " is now empty.");
        }

        private void comboBoxPresets_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
