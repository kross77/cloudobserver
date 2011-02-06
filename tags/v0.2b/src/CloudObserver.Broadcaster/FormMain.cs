using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.ServiceModel;
using CloudObserver.Services;

namespace CloudObserver.Broadcaster
{
    public partial class FormMain : Form
    {
        private List<Broadcast> broadcasts;
        private ControllerServiceContract controllerServiceClient;

        public FormMain()
        {
            InitializeComponent();

            Icon = Properties.Resources.BroadcasterIcon;

            broadcasts = new List<Broadcast>();
        }

        private void textBoxControllerServiceUri_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Enter) buttonConnect_Click(sender, e);
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            Cursor = Cursors.WaitCursor;
            try
            {
                controllerServiceClient = ChannelFactory<ControllerServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(textBoxControllerServiceUri.Text));
            }
            catch (Exception)
            {
                Cursor = Cursors.Arrow;
                MessageBox.Show("Can't access controller service.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            textBoxControllerServiceUri.ReadOnly = true;
            buttonConnect.Enabled = false;
            buttonConnect.Text = "Connected";
            listViewBroadcasts.Enabled = true;
            buttonInstallBroadcast.Enabled = true;
            if (listViewBroadcasts.SelectedItems.Count > 0) listViewBroadcasts.Focus(); else buttonInstallBroadcast.Focus();
            Cursor = Cursors.Arrow;
        }

        private void listViewBroadcasts_SelectedIndexChanged(object sender, EventArgs e)
        {
            buttonUninstallBroadcast.Enabled = (listViewBroadcasts.SelectedItems.Count > 0);
        }

        private void listViewBroadcasts_ItemChecked(object sender, ItemCheckedEventArgs e)
        {
            ListViewItem.ListViewSubItem statusSubItem = e.Item.SubItems[5];
            if (e.Item.Checked)
            {
                statusSubItem.Text = "starting...";
                statusSubItem.ForeColor = Color.DarkGreen;
                //broadcasts[e.Item.Index].Start();
                statusSubItem.Text = "running...";
                statusSubItem.ForeColor = Color.Green;
            }
            else
            {
                statusSubItem.Text = "stopping...";
                statusSubItem.ForeColor = Color.DarkOrange;
                //broadcasts[e.Item.Index].Stop();
                statusSubItem.Text = "stopped";
                statusSubItem.ForeColor = Color.Orange;
            }
        }

        private void listViewBroadcasts_Resize(object sender, EventArgs e)
        {
            listViewBroadcasts.Columns[3].Width = listViewBroadcasts.Width - 430;
        }

        private void buttonInstallBroadcast_Click(object sender, EventArgs e)
        {
            new FormInstallBroadcast().ShowDialog(this);
        }

        private void buttonUninstallBroadcast_Click(object sender, EventArgs e)
        {
            foreach (int index in listViewBroadcasts.SelectedIndices)
            {
                listViewBroadcasts.Items.RemoveAt(index);
            }
        }

        public void InstallBroadcast(Broadcast broadcast, bool startImmediately)
        {
            broadcasts.Add(broadcast);
            broadcast.SetControllerServiceClient(controllerServiceClient);
            if (startImmediately) broadcast.Start();
            ListViewItem newBroadcastItem = new ListViewItem(broadcast.GetCameraID().ToString());
            newBroadcastItem.Checked = broadcast.Running;
            newBroadcastItem.SubItems.Add("");
            newBroadcastItem.SubItems.Add("");
            newBroadcastItem.SubItems.Add(broadcast.GetBroadcastSource().ToString());
            newBroadcastItem.SubItems.Add("NA/" + broadcast.GetMaxFPS().ToString());
            if (broadcast.Running)
                newBroadcastItem.SubItems.Add("running...").ForeColor = Color.Green;
            else
                newBroadcastItem.SubItems.Add("ready").ForeColor = Color.Yellow;
            newBroadcastItem.UseItemStyleForSubItems = false;
            listViewBroadcasts.Items.Add(newBroadcastItem);
        }
    }
}