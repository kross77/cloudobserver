using System;
using System.IO;
using System.Windows;
using Microsoft.Win32;
using DirectShowLib;

namespace CloudObserverWriterClient
{
    public partial class WindowMain : Window
    {
        private DsCapturer capturer = null;
        private bool capturing = false;

        private DsDevice[] videoInputDevices = null;
        private DsDevice[] audioInputDevices = null;

        public WindowMain()
        {
            InitializeComponent();

            EnumerateVideoInputDevices();
            EnumerateAudioInputDevices();
        }

        /*private void buttonBrowse_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Matroska Files (*.mkv)|*.mkv";
            if (saveFileDialog.ShowDialog() == true)
                textBoxTargetFile.Text = saveFileDialog.FileName;
        }*/

        private void buttonCapture_Click(object sender, RoutedEventArgs e)
        {
            if (capturing)
            {
                capturer.StopCapture();

                buttonCapture.Content = "Start Capture";
            }
            else
            {
            //    if (File.Exists(textBoxTargetFile.Text))
            //        if (MessageBox.Show("Target file already exists. Rewrite?", "Attention", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
            //            File.Delete(textBoxTargetFile.Text);
            //        else
            //            return;

                buttonCapture.Content = "Starting...";
                buttonCapture.IsEnabled = false;

                string tAddress = textBoxTargetAddress.Text;
                int tPort = int.Parse(textBoxTargetPort.Text);

                capturer = new DsCapturer(videoInputDevices[comboBoxVideoSources.SelectedIndex], audioInputDevices[comboBoxAudioSources.SelectedIndex],tAddress, tPort);
                capturer.StartCapture();

                buttonCapture.Content = "Stop Capture";
                buttonCapture.IsEnabled = true;
            }
            capturing = !capturing;
        }

        private void EnumerateVideoInputDevices()
        {
            videoInputDevices = DsDevice.GetDevicesOfCat(FilterCategory.VideoInputDevice);
            foreach (DsDevice device in videoInputDevices)
                comboBoxVideoSources.Items.Add(device.Name);
            if (videoInputDevices.Length > 0)
            {
                comboBoxVideoSources.IsEnabled = true;
                comboBoxVideoSources.SelectedIndex = 0;
            }
        }

        private void EnumerateAudioInputDevices()
        {
            audioInputDevices = DsDevice.GetDevicesOfCat(FilterCategory.AudioInputDevice);
            foreach (DsDevice device in audioInputDevices)
                comboBoxAudioSources.Items.Add(device.Name);
            if (audioInputDevices.Length > 0)
            {
                comboBoxAudioSources.IsEnabled = true;
                comboBoxAudioSources.SelectedIndex = 0;
            }
        }
    }
}