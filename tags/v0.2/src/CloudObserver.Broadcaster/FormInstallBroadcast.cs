using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CloudObserver.Broadcaster
{
    public partial class FormInstallBroadcast : Form
    {
        public FormInstallBroadcast()
        {
            InitializeComponent();

            Icon = Properties.Resources.BroadcasterIcon;
        }

        private void RefreshControlsState(object sender, EventArgs e)
        {
            radioButtonSourceLocalStorage.Enabled = (radioButtonTypeDirectBroadcasting.Checked && radioButtonFormatJpeg.Checked);
            if (!radioButtonSourceLocalStorage.Enabled && radioButtonSourceLocalStorage.Checked) radioButtonSourceCloudObserverCamera.Checked = true;
            buttonSourceLocalStorageFilesSelect.Enabled = radioButtonSourceLocalStorage.Enabled && radioButtonSourceLocalStorage.Checked;
            radioButtonSourceCloudObserverCamera.Enabled = radioButtonFormatJpeg.Checked;
            if (!radioButtonSourceCloudObserverCamera.Enabled && radioButtonSourceCloudObserverCamera.Checked) radioButtonSourceIPCamera.Checked = true;
            numericUpDownSourceCloudObserverCameraID.Enabled = radioButtonSourceCloudObserverCamera.Enabled && radioButtonSourceCloudObserverCamera.Checked;
            checkBoxActualRetransmission.Enabled = radioButtonSourceCloudObserverCamera.Enabled && radioButtonTypeVirtualClientService.Checked;
            if (radioButtonTypeDirectBroadcasting.Checked) checkBoxActualRetransmission.Checked = true;
            textBoxSourceIPCameraUri.Enabled = radioButtonSourceIPCamera.Checked;
            checkBoxProvideCredentials.Enabled = radioButtonSourceIPCamera.Checked;
            textBoxUserName.Enabled = checkBoxProvideCredentials.Enabled && checkBoxProvideCredentials.Checked;
            textBoxPassword.Enabled = checkBoxProvideCredentials.Enabled && checkBoxProvideCredentials.Checked;
        }

        private void buttonSourceLocalStorageSelect_Click(object sender, EventArgs e)
        {
            if (openFileDialogFilesSelect.ShowDialog() != DialogResult.OK) return;
            textBoxSourceLocalStorageFiles.Text = openFileDialogFilesSelect.FileName;
        }

        private void buttonInstall_Click(object sender, EventArgs e)
        {
            BroadcastSource broadcastSource = null;
            try
            {
                if (radioButtonSourceLocalStorage.Checked)
                {
                    if (textBoxSourceLocalStorageFiles.Text == "") throw new Exception("No files selected.");
                    broadcastSource = new BroadcastSource(openFileDialogFilesSelect.FileNames);
                }
                if (radioButtonSourceCloudObserverCamera.Checked)
                {
                    if (numericUpDownCameraID.Value == numericUpDownSourceCloudObserverCameraID.Value) throw new Exception("Input and output camera IDs are equal.");
                    broadcastSource = new BroadcastSource((int)numericUpDownSourceCloudObserverCameraID.Value, checkBoxActualRetransmission.Checked);
                }
                if (radioButtonSourceIPCamera.Checked)
                {
                    if (textBoxSourceIPCameraUri.Text == "") throw new Exception("URI is empty.");
                    broadcastSource = new BroadcastSource(textBoxSourceIPCameraUri.Text, checkBoxProvideCredentials.Checked, textBoxUserName.Text, textBoxPassword.Text);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            ((FormMain)Owner).InstallBroadcast(new Broadcast((int)numericUpDownCameraID.Value, GetBroadcastType(), GetBroadcastFormat(), broadcastSource, (int)numericUpDownMaxFPS.Value), checkBoxStartBroadcastImmediately.Checked);
            Close();
        }

        private BroadcastType GetBroadcastType()
        {
            if (radioButtonTypeDirectBroadcasting.Checked)
                return BroadcastType.DirectBroadcasting;
            else
                return BroadcastType.VirtualClientService;
        }

        private BroadcastFormat GetBroadcastFormat()
        {
            if (radioButtonFormatJpeg.Checked)
                return BroadcastFormat.JPEG;
            else
                if (radioButtonFormatMjpeg.Checked)
                    return BroadcastFormat.MJPEG;
                else
                    return BroadcastFormat.MPEG;
        }
    }
}