using System;
using System.IO;
using System.Net;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using System.Windows.Forms;
using System.Reflection;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.ServiceModel.Description;
using System.Threading;
using CloudObserver.Services;
using CloudObserver.Policies;

namespace CloudObserver.Hoster
{
    public partial class FormMain : Form
    {
        private string servicesFilePath = Application.StartupPath + "/services.xml";

        bool controllerServiceConnected = false;
        private int controllerServicePort;
        private string controllerServiceUri;
        private ServiceHost controllerServiceHost;
        private ControllerServiceContract controllerServiceClient;

        private List<ServiceHost> services;

        private PoliciesManager policiesManager;
        private Regex IPRegex;

        public FormMain()
        {
            InitializeComponent();

            Icon = Properties.Resources.HosterIcon;

            services = new List<ServiceHost>();

            textBoxExternalIP.Text = GetExternalIP();
            policiesManager = new PoliciesManager();
            policiesManager.SetExternalIP(textBoxExternalIP.Text);

            IPRegex = new Regex(@"^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[0-9][0-9]|[0-9])|localhost)$");
        }

        private void checkBoxHostControllerService_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxHostControllerService.Checked)
            {
                textBoxControllerServiceUri.ReadOnly = true;
                RefreshControllerServiceUri();
                HostControllerService();
            }
            else
            {
                TerminateControllerService();
                textBoxControllerServiceUri.ReadOnly = false;
                textBoxControllerServiceUri.Text = "http://";
            }
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

        private void textBoxExternalIP_Leave(object sender, EventArgs e)
        {
            if (!IPRegex.IsMatch(textBoxExternalIP.Text)) textBoxExternalIP.Text = "localhost";
            else
            {
                policiesManager.SetExternalIP(textBoxExternalIP.Text);
                if (checkBoxHostControllerService.Checked)
                {
                    TerminateControllerService();
                    RefreshControllerServiceUri();
                    HostControllerService();
                }
            }
        }

        private void textBoxExternalIP_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Enter)
                textBoxExternalIP_Leave(sender, e);
        }

        private void checkBoxAutoDetect_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxAutoDetect.Checked)
            {
                textBoxExternalIP.ReadOnly = true;
                textBoxExternalIP.Text = GetExternalIP();
            }
            else
            {
                textBoxExternalIP.ReadOnly = false;
            }
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            Cursor = Cursors.WaitCursor;
            try
            {
                controllerServiceClient = ChannelFactory<ControllerServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(controllerServiceUri));
            }
            catch (Exception)
            {
                Cursor = Cursors.Arrow;
                MessageBox.Show("Can't access controller service.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            buttonConnect.Enabled = false;
            buttonConnect.Text = "Connected";
            controllerServiceConnected = true;
            UpdateServices();
        }

        private void buttonAddRemoveServices_Click(object sender, EventArgs e)
        {
            new FormAddRemoveServices().ShowDialog(this);
        }

        private void listViewServices_Resize(object sender, EventArgs e)
        {
            listViewServices.Columns[2].Width = listViewServices.Width - 445;
        }

        private void listViewServices_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left) return;
            ListViewHitTestInfo hitTestInfo = listViewServices.HitTest(e.X, e.Y);
            ListViewItem.ListViewSubItem clickedSubItem = hitTestInfo.SubItem;
            if (clickedSubItem.Font.Underline) System.Diagnostics.Process.Start(clickedSubItem.Text);
        }

        private void checkBoxAutomaticPoliciesManagement_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxAutomaticPoliciesManagement.Checked)
            {
                numericUpDownPort.Enabled = false;
                buttonAdd.Enabled = false;
                buttonRemove.Enabled = false;
                listBoxControlledPorts.Items.Clear();
                policiesManager.Reset();
                policiesManager.ConnectPort(controllerServicePort);
                if (!listBoxControlledPorts.Items.Contains(controllerServicePort))
                    listBoxControlledPorts.Items.Add(controllerServicePort);
            }
            else
            {
                policiesManager.Reset();
                listBoxControlledPorts.Items.Clear();
                numericUpDownPort.Enabled = true;
                buttonAdd.Enabled = true;
            }
        }

        private void listBoxControlledPorts_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!checkBoxAutomaticPoliciesManagement.Checked)
                buttonRemove.Enabled = (listBoxControlledPorts.SelectedIndex >= 0);
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            int port = (int)numericUpDownPort.Value;
            policiesManager.ConnectPort(port);
            if (!listBoxControlledPorts.Items.Contains(port))
                listBoxControlledPorts.Items.Add(port);
        }

        private void buttonRemove_Click(object sender, EventArgs e)
        {
            policiesManager.DisconnectPort((int)listBoxControlledPorts.SelectedItem);
            listBoxControlledPorts.Items.Remove(listBoxControlledPorts.SelectedIndex);
        }

        public void UpdateServices()
        {
            Cursor = Cursors.WaitCursor;
            if (!controllerServiceConnected) return;
            foreach (ServiceHost serviceHost in services)
                serviceHost.Close();
            services.Clear();
            listViewServices.Items.Clear();

            if (File.Exists(servicesFilePath))
            {
                Stream input = File.OpenRead(servicesFilePath);
                XmlTextReader servicesFileReader = new XmlTextReader(input);
                while (servicesFileReader.Read())
                    if (servicesFileReader.NodeType == XmlNodeType.Element)
                        if (servicesFileReader.Name == "InstalledService")
                        {
                            Assembly serviceDLLAssembly = Assembly.LoadFile(servicesFileReader.GetAttribute("Library"));
                            Type serviceType = serviceDLLAssembly.GetType(servicesFileReader.GetAttribute("Service"));
                            Type serviceContractType = serviceDLLAssembly.GetType(servicesFileReader.GetAttribute("Contract"));
                            string serviceUri = "http://" + textBoxExternalIP.Text + ":" + numericUpDownControllerServicePort.Value.ToString() + "/" + serviceType.Name;
                            ServiceHost serviceHost = ServiceHoster.CreateServiceHost(serviceType, serviceContractType, serviceUri);
                            new Thread(OpenHost).Start(serviceHost);

                            controllerServiceClient.SetServiceUri(GetServiceType(serviceType.Name), serviceUri);
                            ChannelFactory<ServiceContract>.CreateChannel(new BasicHttpBinding(), new EndpointAddress(serviceUri)).SetControllerServiceUri(controllerServiceUri);

                            ListViewItem newService = new ListViewItem(serviceType.Name);
                            newService.Checked = true;
                            newService.SubItems.Add(serviceType.Name);
                            ListViewItem.ListViewSubItem serviceUriSubItem = newService.SubItems.Add(serviceUri);
                            serviceUriSubItem.Font = new Font(serviceUriSubItem.Font, FontStyle.Underline);
                            serviceUriSubItem.ForeColor = Color.Blue;
                            newService.SubItems.Add("Basic HTTP");
                            newService.SubItems.Add("running...").ForeColor = Color.Green;
                            newService.UseItemStyleForSubItems = false;
                            listViewServices.Items.Add(newService);

                            services.Add(serviceHost);
                        }
                input.Close();
            }
            Cursor = Cursors.Arrow;
        }

        private string GetExternalIP()
        {
            return new WebClient().DownloadString(@"http://www.whatismyip.com/automation/n09230945.asp");
        }

        private void HostControllerService()
        {
            if (controllerServiceHost != null) TerminateControllerService();
            controllerServicePort = (int)numericUpDownControllerServicePort.Value;
            controllerServiceUri = textBoxControllerServiceUri.Text;
            controllerServiceHost = ServiceHoster.CreateServiceHost(typeof(ControllerService), typeof(ControllerServiceContract), controllerServiceUri);

            if (checkBoxAutomaticPoliciesManagement.Checked)
            {
                policiesManager.ConnectPort(controllerServicePort);
                if (!listBoxControlledPorts.Items.Contains(controllerServicePort))
                    listBoxControlledPorts.Items.Add(controllerServicePort);
            }

            new Thread(OpenHost).Start(controllerServiceHost);
        }

        private void TerminateControllerService()
        {
            if (controllerServiceHost != null)
            {
                controllerServiceHost.Close();
                controllerServiceHost = null;
                if (checkBoxAutomaticPoliciesManagement.Checked)
                {
                    policiesManager.DisconnectPort(controllerServicePort);
                    listBoxControlledPorts.Items.Remove(controllerServicePort);
                }
            }
        }

        private void RefreshControllerServiceUri()
        {
            if (checkBoxHostControllerService.Checked)
            {
                controllerServicePort = (int)numericUpDownControllerServicePort.Value;
                controllerServiceUri = "http://" + textBoxExternalIP.Text + ":" + controllerServicePort.ToString() + "/ControllerService";
                textBoxControllerServiceUri.Text = controllerServiceUri;
            }
        }

        private void OpenHost(object serviceHost)
        {
            ((ServiceHost)serviceHost).Open();
        }

        private ServiceType GetServiceType(string serviceName)
        {
            switch (serviceName)
            {
                case "AccountsService":
                    return ServiceType.AccountsService;
                case "AuthenticationService":
                    return ServiceType.AuthenticationService;
                case "BroadcastService":
                    return ServiceType.BroadcastService;
                case "StorageService":
                    return ServiceType.StorageService;
                case "VirtualCamerasService":
                    return ServiceType.VirtualCamerasService;
                default:
                    return ServiceType.UnknownService;
            }
        }
    }
}