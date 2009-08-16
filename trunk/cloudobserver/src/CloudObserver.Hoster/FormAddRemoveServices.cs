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

namespace CloudObserver.Hoster
{
    public partial class FormAddRemoveServices : Form
    {
        private string servicesFilePath = Application.StartupPath + "/services.xml";

        public FormAddRemoveServices()
        {
            InitializeComponent();

            Icon = Properties.Resources.HosterIcon;

            if (File.Exists(servicesFilePath))
                LoadServices(File.OpenRead(servicesFilePath));
        }

        private void FormInstalledServices_FormClosing(object sender, FormClosingEventArgs e)
        {
            SaveServices(File.Create(servicesFilePath));
            ((FormMain)Owner).UpdateServices();
        }

        private void listViewInstalledServices_SelectedIndexChanged(object sender, EventArgs e)
        {
            buttonUninstallService.Enabled = (listViewInstalledServices.SelectedItems.Count > 0);
            if (listViewInstalledServices.SelectedIndices.Count > 1)
            {
                buttonInstallService.Text = "Install Services";
                buttonUninstallService.Text = "Uninstall Services";
            }
            else
            {
                buttonInstallService.Text = "Install Service";
                buttonUninstallService.Text = "Uninstall Service";
            }
        }

        private void buttonInstallService_Click(object sender, EventArgs e)
        {
            new FormInstallService().ShowDialog(this);
        }

        private void buttonUninstallService_Click(object sender, EventArgs e)
        {
            foreach (int index in listViewInstalledServices.SelectedIndices)
                listViewInstalledServices.Items.RemoveAt(index);
        }

        public void loadServiceDLL(string service, string contract, string library)
        {
            ListViewItem newServiceItem = listViewInstalledServices.Items.Add(service);
            newServiceItem.SubItems.Add(contract);
            newServiceItem.SubItems.Add(library);
        }

        private void LoadServices(Stream input)
        {
            XmlTextReader servicesFileReader = new XmlTextReader(input);
            while (servicesFileReader.Read())
                if (servicesFileReader.NodeType == XmlNodeType.Element)
                    if (servicesFileReader.Name == "InstalledService")
                    {
                        ListViewItem newServiceItem = listViewInstalledServices.Items.Add(servicesFileReader.GetAttribute("Service"));
                        newServiceItem.SubItems.Add(servicesFileReader.GetAttribute("Contract"));
                        newServiceItem.SubItems.Add(servicesFileReader.GetAttribute("Library"));
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
                foreach (ListViewItem serviceItem in listViewInstalledServices.Items)
                {
                    servicesFileWriter.WriteStartElement("InstalledService");
                    servicesFileWriter.WriteAttributeString("Service", serviceItem.SubItems[0].Text);
                    servicesFileWriter.WriteAttributeString("Contract", serviceItem.SubItems[1].Text);
                    servicesFileWriter.WriteAttributeString("Library", serviceItem.SubItems[2].Text);
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
    }
}