using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;

namespace CloudObserverServicesHoster
{
    public partial class FormInstallService : Form
    {
        private string servicesFilePath = Application.StartupPath + "/services.xml";

        public FormInstallService()
        {
            InitializeComponent();

            if (File.Exists(servicesFilePath)) LoadServices(File.OpenRead(servicesFilePath));
        }

        private void LoadServices(Stream input)
        {
            XmlTextReader servicesFileReader = new XmlTextReader(input);
            while (servicesFileReader.Read())
                if (servicesFileReader.NodeType == XmlNodeType.Element)
                    if (servicesFileReader.Name == "Service")
                    {
                        ListViewItem newServiceItem = listViewLoadedServices.Items.Add(servicesFileReader.GetAttribute("DLL"));
                        newServiceItem.SubItems.Add(servicesFileReader.GetAttribute("Interface"));
                        newServiceItem.SubItems.Add(servicesFileReader.GetAttribute("Class"));
                    }
            input.Close();
        }

        private void SaveServices(Stream output)
        {
            XmlTextWriter servicesFileWriter = null;
            try
            {
                servicesFileWriter = new XmlTextWriter(output, Encoding.Unicode);
                servicesFileWriter.WriteStartDocument();
                servicesFileWriter.WriteStartElement("Services");
                foreach (ListViewItem serviceItem in listViewLoadedServices.Items)
                {
                    servicesFileWriter.WriteStartElement("Service");
                    servicesFileWriter.WriteAttributeString("DLL", serviceItem.SubItems[0].Text);
                    servicesFileWriter.WriteAttributeString("Interface", serviceItem.SubItems[1].Text);
                    servicesFileWriter.WriteAttributeString("Class", serviceItem.SubItems[2].Text);
                    servicesFileWriter.WriteEndElement();
                }
                servicesFileWriter.WriteEndElement();
                servicesFileWriter.WriteEndDocument();
            }
            finally
            {
                if (servicesFileWriter != null)
                    servicesFileWriter.Close(); 
            }
        }

        private void buttonLoadServiceDLL_Click(object sender, EventArgs e)
        {
            new FormLoadServiceDLL().ShowDialog(this);
        }

        public void loadServiceDLL(string serviceDLLFile, string serviceInterface, string serviceClass)
        {
            ListViewItem newServiceItem = listViewLoadedServices.Items.Add(serviceDLLFile);
            newServiceItem.SubItems.Add(serviceInterface);
            newServiceItem.SubItems.Add(serviceClass);
        }

        private void FormInstallService_FormClosing(object sender, FormClosingEventArgs e)
        {
            SaveServices(File.Create(servicesFilePath));
        }

        private void buttonInstall_Click(object sender, EventArgs e)
        {
            ListViewItem selectedServiceItem = listViewLoadedServices.SelectedItems[0];
            ((FormMain)Owner).InstallService(selectedServiceItem.SubItems[0].Text, selectedServiceItem.SubItems[1].Text, selectedServiceItem.SubItems[2].Text, Decimal.ToInt32(numericUpDownServicePort.Value));
            Close();
        }

        private void listViewLoadedServices_SelectedIndexChanged(object sender, EventArgs e)
        {
            buttonInstall.Enabled = (listViewLoadedServices.SelectedItems.Count > 0);
        }
    }
}