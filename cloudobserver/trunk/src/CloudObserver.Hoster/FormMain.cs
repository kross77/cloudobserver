using System;
using System.Net;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.ServiceModel.Description;
using CloudObserver.Services;
using CloudObserver.Policies;

namespace CloudObserver.Hoster
{
    public partial class FormMain : Form
    {
        private ServiceHost controllerServiceHost;
        private int controllerServicePort;

        private Regex IPRegex;
        private Dictionary<int, int> controlledPorts;
        private Dictionary<int, ServiceHost> policyRetrievers;

        private const int MAX_RECEIVED_MESSAGE_SIZE = 2147483647;
        private const int MAX_ARRAY_LENGTH = 2147483647;

        public FormMain()
        {
            InitializeComponent();

            IPRegex = new Regex(@"^(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9])$");
            controlledPorts = new Dictionary<int, int>();
            policyRetrievers = new Dictionary<int,ServiceHost>();

            textBoxExternalIP.Text = GetExternalIP();
        }

        private void checkBoxHostControllerService_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxHostControllerService.Checked)
            {
                textBoxControllerServiceUri.ReadOnly = true;
                RefreshControllerServiceUri();
                numericUpDownControllerServicePort.Enabled = true;
                HostControllerService();
            }
            else
            {
                TerminateControllerService();
                textBoxControllerServiceUri.ReadOnly = false;
                textBoxControllerServiceUri.Text = "http://";
                numericUpDownControllerServicePort.Enabled = false;
            }
        }

        private void checkBoxModify_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxModify.Checked)
            {
                textBoxExternalIP.ReadOnly = false;
            }
            else
            {
                textBoxExternalIP.ReadOnly = true;
                textBoxExternalIP.Text = GetExternalIP();
            }
        }

        private string GetExternalIP()
        {
            return new WebClient().DownloadString(@"http://www.whatismyip.com/automation/n09230945.asp");
        }

        private void HostControllerService()
        {
            if (controllerServiceHost != null) TerminateControllerService();
            controllerServiceHost = CreateServiceHost(textBoxControllerServiceUri.Text);
            controllerServicePort = (int)numericUpDownControllerServicePort.Value;
            if (checkBoxAutomaticPoliciesManagement.Checked) BindPort((int)(numericUpDownControllerServicePort.Value));
            controllerServiceHost.Open();
        }

        private void TerminateControllerService()
        {
            if (controllerServiceHost != null)
            {
                controllerServiceHost.Close();
                controllerServiceHost = null;
                if (checkBoxAutomaticPoliciesManagement.Checked) ReleasePort(controllerServicePort);
            }
        }

        private ServiceHost CreateServiceHost(string address)
        {
            ServiceHost serviceHost = new ServiceHost(typeof(ControllerService), new Uri(address));

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

            BasicHttpBinding binding = new BasicHttpBinding();
            binding.BypassProxyOnLocal = true;
            binding.MaxReceivedMessageSize = MAX_RECEIVED_MESSAGE_SIZE;
            binding.OpenTimeout = TimeSpan.FromMinutes(5);
            binding.CloseTimeout = TimeSpan.FromMinutes(5);
            binding.ReceiveTimeout = TimeSpan.FromMinutes(30);
            binding.SendTimeout = TimeSpan.FromMinutes(30);
            binding.ReaderQuotas.MaxArrayLength = MAX_ARRAY_LENGTH;
            serviceHost.AddServiceEndpoint(typeof(ControllerServiceContract), binding, "");
            return serviceHost;
        }
        
        private void textBoxExternalIP_Leave(object sender, EventArgs e)
        {
            if (!IPRegex.IsMatch(textBoxExternalIP.Text)) textBoxExternalIP.Text = "0.0.0.0";
            else
                if (checkBoxHostControllerService.Checked)
                {
                    TerminateControllerService();
                    RefreshControllerServiceUri();
                    HostControllerService();
                }
        }

        private void RefreshControllerServiceUri()
        {
            if (checkBoxHostControllerService.Checked)
                textBoxControllerServiceUri.Text = "http://" + textBoxExternalIP.Text + ":" + numericUpDownControllerServicePort.Value.ToString() + "/ControllerService";
        }

        private void numericUpDownControllerServicePort_ValueChanged(object sender, EventArgs e)
        {
            if (checkBoxHostControllerService.Checked)
            {
                TerminateControllerService();
                RefreshControllerServiceUri();
                HostControllerService();
            }
        }

        private void BindPort(int port)
        {
            if ((!controlledPorts.ContainsKey(port)) || (controlledPorts[port] == 0))
            {
                listBoxControlledPorts.Items.Add(port);
                controlledPorts[port] = 1;
                policyRetrievers[port] = new ServiceHost(typeof(PolicyRetriever), new Uri("http://" + textBoxExternalIP.Text + ":" + port + "/"));
                policyRetrievers[port].AddServiceEndpoint(typeof(PolicyRetrieverContract), new WebHttpBinding(), "").Behaviors.Add(new WebHttpBehavior());
                policyRetrievers[port].Open();
            }
            else
                controlledPorts[port]++;
        }

        private void ReleasePort(int port)
        {
            controlledPorts[port]--;
            if (controlledPorts[port] == 0)
            {
                listBoxControlledPorts.Items.Remove(port);
                policyRetrievers[port].Close();
                policyRetrievers[port] = null;
            }
        }

        private void textBoxExternalIP_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Enter)
                textBoxExternalIP_Leave(sender, e);
        }

        private void checkBoxAutomaticPoliciesManagement_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxAutomaticPoliciesManagement.Checked)
            {
                numericUpDownPort.Enabled = false;
                buttonAdd.Enabled = false;
                buttonRemove.Enabled = false;
                listBoxControlledPorts.Items.Clear();
                controlledPorts.Clear();
                foreach (ServiceHost policyRetriever in policyRetrievers.Values)
                    policyRetriever.Close();
                policyRetrievers.Clear();
                ScanPorts();
            }
            else
            {
                controlledPorts.Clear();
                foreach (ServiceHost policyRetriever in policyRetrievers.Values)
                    policyRetriever.Close();
                policyRetrievers.Clear();
                listBoxControlledPorts.Items.Clear();
                numericUpDownPort.Enabled = true;
                buttonAdd.Enabled = true;
            }
        }

        private void ScanPorts()
        {
            if (controllerServiceHost != null) BindPort(controllerServicePort);
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            int port = (int)numericUpDownPort.Value;
            if (!listBoxControlledPorts.Items.Contains(port))
                BindPort(port);
        }

        private void listBoxControlledPorts_SelectedIndexChanged(object sender, EventArgs e)
        {
            buttonRemove.Enabled = (listBoxControlledPorts.SelectedIndex >= 0);
        }

        private void buttonRemove_Click(object sender, EventArgs e)
        {
            ReleasePort((int)listBoxControlledPorts.SelectedItem);
        }
    }
}