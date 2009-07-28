using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.ServiceModel;
using System.ServiceModel.Description;

namespace CloudObserverServicesHoster
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private void listViewInstalledServices_SelectedIndexChanged(object sender, EventArgs e)
        {
            buttonUninstallService.Enabled = (listViewInstalledServices.SelectedItems.Count > 0);
        }

        private void buttonInstallService_Click(object sender, EventArgs e)
        {
            new FormInstallService().ShowDialog(this);
        }

        public void InstallService(string serviceDLL, string serviceInterface, string serviceClass, int servicePort, string serviceBinding)
        {
            ListViewItem newService = new ListViewItem(serviceDLL);
            newService.SubItems.Add(serviceInterface);
            newService.SubItems.Add(serviceClass);
            newService.SubItems.Add(servicePort.ToString());
            newService.SubItems.Add(serviceBinding);
            newService.SubItems.Add("loaded").ForeColor = Color.Blue;
            newService.UseItemStyleForSubItems = false;
            listViewInstalledServices.Items.Add(newService);
        }

        private void listViewInstalledServices_ItemChecked(object sender, ItemCheckedEventArgs e)
        {
            ListViewItem.ListViewSubItem serviceStatusSubItem = e.Item.SubItems[5];
            if (e.Item.Checked)
            {
                serviceStatusSubItem.Text = "starting...";
                serviceStatusSubItem.ForeColor = Color.DarkGreen;

                Assembly serviceDLLAssembly = Assembly.LoadFile(e.Item.SubItems[0].Text);
                Type serviceType = serviceDLLAssembly.GetType(e.Item.SubItems[2].Text);
                Type serviceContractType = serviceDLLAssembly.GetType(e.Item.SubItems[1].Text);
                string servicePath = "http://localhost:" + e.Item.SubItems[3].Text + "/" + serviceDLLAssembly.GetType(e.Item.SubItems[2].Text).Name;
                ServiceHost serviceHost = new ServiceHost(serviceType, new Uri(servicePath));
                ServiceMetadataBehavior mexBehavior = new ServiceMetadataBehavior();
                mexBehavior.HttpGetEnabled = true;
                serviceHost.Description.Behaviors.Add(mexBehavior);
                serviceHost.AddServiceEndpoint(serviceContractType, GetBinding(e.Item.SubItems[4].Text), "");
                e.Item.Tag = serviceHost;
                serviceHost.Open();

                serviceStatusSubItem.Text = "running..";
                serviceStatusSubItem.ForeColor = Color.Green;
            }
            else
            {
                serviceStatusSubItem.Text = "stopping...";
                serviceStatusSubItem.ForeColor = Color.DarkOrange;
                if (e.Item.Tag != null) ((ServiceHost)e.Item.Tag).Close();
                serviceStatusSubItem.Text = "stopped";
                serviceStatusSubItem.ForeColor = Color.Orange;
            }
        }

        private void buttonUninstallService_Click(object sender, EventArgs e)
        {
            listViewInstalledServices.SelectedItems[0].Remove();
        }

        private System.ServiceModel.Channels.Binding GetBinding(string bindingName)
        {
            switch (bindingName)
            {
                case "BasicHttpBinding":
                    return new BasicHttpBinding();
                case "WSHttpBinding":
                    return new WSHttpBinding();
                default:
                    return new BasicHttpBinding();
            }
        }
    }
}