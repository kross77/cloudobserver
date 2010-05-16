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
using System.Xml;



namespace CloudDsWpfClient
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        private Microsoft.Win32.OpenFileDialog openFileDialog1 = new Microsoft.Win32.OpenFileDialog();
        private string fileName = null, bulderName = null, audioInputName = null, hostAddress = null, hostPort = null;
        private bool capturing;
        ICloudGraphBuilder graph = null;
        
        XmlDocument xDoc = new XmlDocument();


        public Window1()
        {
            InitializeComponent();
            EnumerateAudioInputDevices();
            EnumarateDestinationTargets();
        }
        private void EnumerateAudioInputDevices()
        {

            List<string> listName = CloudGraphFactory.EnumerateAudioInputDevices();
            foreach (string name in listName)
            {
                comboBoxAudioSources.Items.Add(name);
            }

        }
        private void EnumarateDestinationTargets()
        {
            comboBoxDestination.Items.Add("Cloud server");
            comboBoxDestination.Items.Add("Local File");
            comboBoxDestination.Items.Add("Local Socket");


        }

        private void comboBoxAudioSources_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = (ComboBox)sender;
            audioInputName = (string)cb.Items[cb.SelectedIndex];
        }

        private void comboBoxDestination_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //XmlDocument xDoc = new XmlDocument();
            xDoc.LoadXml("<?xml version='1.0' ?>" +
                "<CloudClientGraph></CloudClientGraph>");
            XmlElement xElem;
            XmlText xText;
            Nullable<bool> result;
            
            ComboBox cb = (ComboBox) sender;
            switch (cb.SelectedIndex)
            {
                case 0: //cloud server
                    MessageBox.Show("not support now");
                    cb.SelectedIndex = -1;
                    break;
                case 1: //locale file (file name)
                    // Show open file dialog box
                    result = openFileDialog1.ShowDialog();

                    // Process open file dialog box results
                    if (result == true)
                    {
                        // Open document
                        fileName = openFileDialog1.FileName;
                        bulderName = "CloudFileWriter";

                        xElem = xDoc.CreateElement("Builder");
                        xText = xDoc.CreateTextNode(bulderName);
                        xDoc.DocumentElement.AppendChild(xElem);
                        xDoc.DocumentElement.LastChild.AppendChild(xText);

                        xElem = xDoc.CreateElement("FileName");
                        xText = xDoc.CreateTextNode(fileName);
                        xDoc.DocumentElement.AppendChild(xElem);
                        xDoc.DocumentElement.LastChild.AppendChild(xText);

                        XmlNodeList xBuilder = xDoc.GetElementsByTagName("Builder");
                        XmlNodeList xFileName = xDoc.GetElementsByTagName("FileName");

                        labelDestinationProperties.Content = "CloudClientBuilder:\n    " + xBuilder[0].InnerText
                            + "\n\nFileName:\n    " + xFileName[0].InnerText;

                        
                    }

                    break;
                case 2: // file throught socket (socket and file name)
                    // Show open file dialog box
                    result = openFileDialog1.ShowDialog();

                    // Process open file dialog box results
                    if (result == true)
                    {
                        // Open document
                        fileName = openFileDialog1.FileName;
                        bulderName = "CloudSocketRenderer";

                        xElem = xDoc.CreateElement("Builder");
                        xText = xDoc.CreateTextNode(bulderName);
                        xDoc.DocumentElement.AppendChild(xElem);
                        xDoc.DocumentElement.LastChild.AppendChild(xText);

                        xElem = xDoc.CreateElement("FileName");
                        xText = xDoc.CreateTextNode(fileName);
                        xDoc.DocumentElement.AppendChild(xElem);
                        xDoc.DocumentElement.LastChild.AppendChild(xText);

                        if (-1 == SetHostAddress())
                        {
                            MessageBox.Show("wrong host address");
                            return;
                        }

                        xElem = xDoc.CreateElement("HostAddress");
                        xText = xDoc.CreateTextNode(hostAddress);
                        xDoc.DocumentElement.AppendChild(xElem);
                        xDoc.DocumentElement.LastChild.AppendChild(xText);

                        xElem = xDoc.CreateElement("HostPort");
                        xText = xDoc.CreateTextNode(hostPort);
                        xDoc.DocumentElement.AppendChild(xElem);
                        xDoc.DocumentElement.LastChild.AppendChild(xText);


                        XmlNodeList xBuilder = xDoc.GetElementsByTagName("Builder");
                        XmlNodeList xFileName = xDoc.GetElementsByTagName("FileName");
                        XmlNodeList xHostAddress = xDoc.GetElementsByTagName("HostAddress");
                        XmlNodeList xHostPort = xDoc.GetElementsByTagName("HostPort");

                        labelDestinationProperties.Content =
                            "CloudClientBuilder:\n    " + xBuilder[0].InnerText
                            + "\n\nFileName:\n    " + xFileName[0].InnerText +
                            "\n\nDestinationAddress:\n    " + xHostAddress[0].InnerText + ":" + xHostPort[0].InnerText;
                    }

                    break;
                default:
                    break;
            }
        }
        private int SetHostAddress()
        {
            ConfigWindow configWindow = new ConfigWindow();
            
            configWindow.ShowDialog();
            if ("" == (hostAddress = configWindow.GetHostAddress()))
                return -1;
            if ("" == (hostPort = configWindow.GetHostPort()))
                return -1;
            return 0;
        }
        private void buttonStart_Click(object sender, RoutedEventArgs e)
        {
            XmlElement xElem;
            XmlText xText;

            if (capturing)
            {
                graph.Stop();
                buttonStart.Content = "Start";
            }
            else
            {
                if (comboBoxAudioSources.SelectedIndex == -1)
                {
                    MessageBox.Show("Choose Input Device\n");
                    return;
                }
                if (null == bulderName)
                {
                    MessageBox.Show("Choose GraphBuilder\n");
                    return;
                }
                buttonStart.Content = "Starting...";
                buttonStart.IsEnabled = false;

                xElem = xDoc.CreateElement("AudioInput");
                xText = xDoc.CreateTextNode(audioInputName);
                xDoc.DocumentElement.AppendChild(xElem);
                xDoc.DocumentElement.LastChild.AppendChild(xText);

                graph = CloudGraphFactory.Create(xDoc);
                graph.Start();

                buttonStart.Content = "Stop Capture";
                buttonStart.IsEnabled = true;
            }
            capturing = !capturing;
        }
    }
}
