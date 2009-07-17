using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
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

        public static byte[] BitmapToByteArray(Bitmap bitmap)
        {
            MemoryStream memoryStream = new MemoryStream();
            bitmap.Save(memoryStream, ImageFormat.Jpeg);
            return memoryStream.ToArray();
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
            buttonClearDatabase_Click(sender, e);
            AddLog("Setting default values into " + databaseName + "...");
            // users
            AddLog("  creating users...");
            int userA = database.UserAdd("a@mail.ru", "a", "User A", "User A Description", BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultUserIcon)));
            AddLog("  'User A' registered (email: 'a@mail.ru', password: 'a').");
            int userB = database.UserAdd("b@mail.ru", "b", "User B", "User B Description", BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultUserIcon)));
            AddLog("  'User B' registered (email: 'b@mail.ru', password: 'b').");
            AddLog("  creating users compelete.");

            // cameras
            AddLog("  creating cameras...");
            int defaultCamera = database.CameraAdd("Default Camera", "Default Camera Description", BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultCameraIcon)));
            AddLog("  'Default Camera' camera registered (path: '" + database.CameraGetPath(defaultCamera) + "').");
            int testCamera = database.CameraAdd("Test Camera", "Test Camera Description", BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultGroupIcon)));
            AddLog("  'Test Camera' camera registered (path: '" + database.CameraGetPath(testCamera) + "').");
            AddLog("  creating cameras complete.");

            //groups
            AddLog("  creating groups...");
            int cloudObserverGroup = database.GroupAdd("Cloud Observer", "Cloud Observer Group Description", BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultGroupIcon)), 2);
            AddLog("  private 'Cloud Observer' group registered.");
            int testGroup = database.GroupAdd("Test Group", "Test Group Description", BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultGroupIcon)), 1);
            AddLog("  public 'Test Group' group registered.");
            AddLog("  creating groups complete.");

            //group members
            AddLog("  adding group members...");
            database.GroupMemberAdd(userA, cloudObserverGroup, 0);
            AddLog("  'User A' was added into 'Cloud Observer' group.");
            database.GroupMemberAdd(userB, cloudObserverGroup, 0);
            AddLog("  'User B' was added into 'Cloud Observer' group.");
            database.GroupMemberAdd(userA, testGroup, 0);
            AddLog("  'User A' was added into 'Test Group' group.");
            AddLog("  adding group members complete.");

            //group cameras
            AddLog("  adding group cameras...");
            database.GroupCameraAdd(defaultCamera, cloudObserverGroup);
            AddLog("  'Default Camera' camera was added into 'Cloud Observer' group.");
            database.GroupCameraAdd(testCamera, testGroup);
            AddLog("  'Test Camera' camera was added into 'Test Group' group.");
            AddLog("  adding group cameras complete.");

            //frames
            AddLog("  adding frames...");
            database.FrameAdd(testCamera, BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame001)), "Default Marker");
            database.FrameAdd(testCamera, BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame002)), "Default Marker");
            database.FrameAdd(testCamera, BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame003)), "Default Marker");
            database.FrameAdd(testCamera, BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame004)), "Default Marker");
            database.FrameAdd(testCamera, BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame005)), "Default Marker");
            database.FrameAdd(testCamera, BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame006)), "Default Marker");
            database.FrameAdd(testCamera, BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame007)), "Default Marker");
            database.FrameAdd(testCamera, BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame008)), "Default Marker");
            database.FrameAdd(testCamera, BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame009)), "Default Marker");
            database.FrameAdd(testCamera, BitmapToByteArray(new Bitmap(global::DatabaseManagementTool.Properties.Resources.DefaultFrame010)), "Default Marker");
            AddLog("  10 default frames was added from 'Default Camera' camera.");
            AddLog("  adding frames complete.");

            AddLog("Setting default values into " + databaseName + " complete.");
        }

        private void buttonClearDatabase_Click(object sender, EventArgs e)
        {
            database.DatabaseClear();
            listBoxActionsLog.Items.Add("Database " + databaseName + " is now empty.");
        }

        private void AddLog(string s)
        {
            listBoxActionsLog.Items.Add(s);
        }
    }
}