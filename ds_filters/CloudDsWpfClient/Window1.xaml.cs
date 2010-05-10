using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using DirectShowLib;
using CloudObserver.DirectShow.Graphs;



namespace CloudDsWpfClient
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        private DsDevice[] audioInputDevices = null;
        private Microsoft.Win32.OpenFileDialog openFileDialog1 = new Microsoft.Win32.OpenFileDialog();
        private string fileName;
        private bool capturing;
        FileWriterGraphBuilder graph = new FileWriterGraphBuilder();


        public Window1()
        {
            InitializeComponent();
            EnumerateAudioInputDevices();
            EnumarateDestinationTargets();
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
        private void EnumarateDestinationTargets()
        {
            comboBoxDestination.Items.Add("Cloud server");
            comboBoxDestination.Items.Add("Local File");
            comboBoxDestination.Items.Add("Local Socket");

           // comboBoxDestination.SelectedIndex = 0;
        }

        private void comboBoxAudioSources_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void comboBoxDestination_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = (ComboBox) sender;
            switch (cb.SelectedIndex)
            {
                case 0: //cloud server
                    MessageBox.Show("not support now");
                    cb.SelectedIndex = -1;
                    break;
                case 1: //locale file (file name)
                    // Show open file dialog box
                    Nullable<bool> result = openFileDialog1.ShowDialog();

                    // Process open file dialog box results
                    if (result == true)
                    {
                        // Open document
                        fileName = openFileDialog1.FileName;
                        labelDestinationProperties.Content = "Filter File writer:\nFile: " + fileName;
                    }

                    break;
                case 2: // file throught socket (socket and file name)
                    break;
                default:
                    break;
            }
        }

        private void buttonStart_Click(object sender, RoutedEventArgs e)
        {
            if (capturing)
            {
                graph.StartCapture();
                buttonStart.Content = "Start";
            }
            else
            {
                buttonStart.Content = "Starting...";
                buttonStart.IsEnabled = false;

                graph.CreateFilter(audioInputDevices[comboBoxAudioSources.SelectedIndex], fileName);
                graph.StartCapture();

                buttonStart.Content = "Stop Capture";
                buttonStart.IsEnabled = true;
            }
            capturing = !capturing;
        }
    }
}
