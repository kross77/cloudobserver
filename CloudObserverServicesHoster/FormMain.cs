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
using System.Xml;

namespace CloudObserverServicesHoster
{
    public partial class FormMain : Form
    {
        private const int MAX_RECEIVED_MESSAGE_SIZE = 2147483647;
        private const int MAX_ARRAY_LENGTH = 2147483647;

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
                string servicePath = "http://localhost:" + e.Item.SubItems[3].Text + "/" + serviceType.Name;

                ServiceHost serviceHost = new ServiceHost(serviceType, new Uri(servicePath));

                ServiceMetadataBehavior serviceMetadataBehavior = serviceHost.Description.Behaviors.Find<ServiceMetadataBehavior>();
                if (serviceMetadataBehavior == null)
                {
                    serviceMetadataBehavior = new ServiceMetadataBehavior();
                    serviceMetadataBehavior.HttpGetEnabled = true;
                    serviceHost.Description.Behaviors.Add(serviceMetadataBehavior);
                }
                else
                    serviceMetadataBehavior.HttpGetEnabled = true;

                ServiceDebugBehavior serviceDebugBehavior = serviceHost.Description.Behaviors.Find<ServiceDebugBehavior>();
                if (serviceDebugBehavior == null)
                {
                    serviceDebugBehavior = new ServiceDebugBehavior();
                    serviceDebugBehavior.IncludeExceptionDetailInFaults = true;
                    serviceHost.Description.Behaviors.Add(serviceDebugBehavior);
                }
                else
                    serviceDebugBehavior.IncludeExceptionDetailInFaults = true;

                BasicHttpBinding binding = (BasicHttpBinding)GetBinding(e.Item.SubItems[4].Text);
                binding.BypassProxyOnLocal = true;
                binding.MaxReceivedMessageSize = MAX_RECEIVED_MESSAGE_SIZE;
                binding.OpenTimeout = TimeSpan.FromMinutes(5);
                binding.CloseTimeout = TimeSpan.FromMinutes(5);
                binding.ReceiveTimeout = TimeSpan.FromMinutes(30);
                binding.SendTimeout = TimeSpan.FromMinutes(30);
                binding.ReaderQuotas.MaxArrayLength = MAX_ARRAY_LENGTH;
                serviceHost.AddServiceEndpoint(serviceContractType, binding, "");

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