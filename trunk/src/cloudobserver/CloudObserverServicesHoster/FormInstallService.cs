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
        private string settingsFilePath = Application.ExecutablePath + "/settings.xml";

        public FormInstallService()
        {
            InitializeComponent();

            loadSettings(settingsFilePath);
        }

        private void loadSettings(string settingsXMLFilePath)
        {
            //
        }

        private void listBoxLoadedServices_SelectedIndexChanged(object sender, EventArgs e)
        {
            buttonInstall.Enabled = (listViewLoadedServices.SelectedIndices.Count >= 0);
        }

        private void buttonLoadServiceDLL_Click(object sender, EventArgs e)
        {
            new FormLoadServiceDLL().ShowDialog(this);
        }

        public void loadServiceDLL(string serviceDLLFile, string serviceInterface, string serviceClass)
        {
            int newItemIndex = listViewLoadedServices.Items.Add(serviceDLLFile).Index;
            listViewLoadedServices.Items[newItemIndex].SubItems.Add(serviceInterface);
            listViewLoadedServices.Items[newItemIndex].SubItems.Add(serviceClass);
        }
    }
}