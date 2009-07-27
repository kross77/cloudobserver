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
using System.Text.RegularExpressions;

namespace CloudObserverServicesHoster
{
    public partial class FormLoadServiceDLL : Form
    {
        private Assembly serviceDLLAssembly;
        private string serviceDLLFileName;
        private string serviceName;
        private bool isServiceHostingTestSucceed;

        public FormLoadServiceDLL()
        {
            InitializeComponent();

            isServiceHostingTestSucceed = false;
        }

        private void radioButtonLoadFromFile_CheckedChanged(object sender, EventArgs e)
        {
            buttonSelectDLLFile.Enabled = radioButtonLoadFromFile.Checked;
            if (radioButtonLoadFromFile.Checked) buttonSelectDLLFile.Focus();
        }

        private void buttonSelectDLLFile_Click(object sender, EventArgs e)
        {
            if (openFileDialogSelectDLLFile.ShowDialog() == DialogResult.OK)
            {
                serviceDLLFileName = openFileDialogSelectDLLFile.SafeFileName;
                textBoxDLLFile.Text = openFileDialogSelectDLLFile.FileName;
                loadServiceDetails();
            }
        }

        private void radioButtonLoadFromCOService_CheckedChanged(object sender, EventArgs e)
        {
            textBoxCOServiceURL.Enabled = radioButtonLoadFromCOService.Checked;
            buttonGetServicesList.Enabled = radioButtonLoadFromCOService.Checked;
            listBoxCOServiceServices.Enabled = radioButtonLoadFromCOService.Checked;
            if (radioButtonLoadFromCOService.Checked) textBoxCOServiceURL.Focus();
        }

        private void comboBoxServiceDetailsInterface_SelectedIndexChanged(object sender, EventArgs e)
        {
            isServiceHostingTestSucceed = false;
        }

        private void comboBoxServiceDetailsClass_SelectedIndexChanged(object sender, EventArgs e)
        {
            isServiceHostingTestSucceed = false;
            serviceName = serviceDLLAssembly.GetType(comboBoxServiceDetailsClass.Text).Name;
            int currentPosition = 1;
            int serviceNameLength = serviceName.Length;
            while (currentPosition < serviceNameLength)
            {
                if (Char.IsUpper(serviceName[currentPosition]))
                {
                    serviceName = serviceName.Insert(currentPosition, " ");
                    currentPosition++;
                    serviceNameLength++;
                }
                currentPosition++;
            }
            textBoxServiceDetailsName.Text = serviceName;
        }

        private void buttonTestServiceHosting_Click(object sender, EventArgs e)
        {
            try
            {
                serviceDLLAssembly = Assembly.LoadFile(textBoxDLLFile.Text);
                Type serviceType = serviceDLLAssembly.GetType(comboBoxServiceDetailsClass.Text);
                Type serviceContractType = serviceDLLAssembly.GetType(comboBoxServiceDetailsInterface.Text);
                string servicePath = "http://localhost:" + new Random().Next(1024, 65535) + "/" + serviceDLLAssembly.GetType(comboBoxServiceDetailsClass.Text).Name;
                ServiceHost serviceHost = new ServiceHost(serviceType, new Uri(servicePath));
                ServiceMetadataBehavior mexBehavior = new ServiceMetadataBehavior();
                mexBehavior.HttpGetEnabled = true;
                serviceHost.Description.Behaviors.Add(mexBehavior);
                serviceHost.AddServiceEndpoint(serviceContractType, new WSHttpBinding(), "");
                serviceHost.Open();
                serviceHost.Close();
                isServiceHostingTestSucceed = true;
                MessageBox.Show("Service hosting test succeed.", "Test Service Hosting", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception exception)
            {
                isServiceHostingTestSucceed = false;
                MessageBox.Show(exception.Message, "Testing Failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void buttonLoadService_Click(object sender, EventArgs e)
        {
            if (!isServiceHostingTestSucceed) buttonTestServiceHosting_Click(sender, e);
            if (isServiceHostingTestSucceed)
            {
                ((FormInstallService)Owner).loadServiceDLL(textBoxDLLFile.Text, comboBoxServiceDetailsInterface.Text, comboBoxServiceDetailsClass.Text);
                Close();
            }
        }

        private void loadServiceDetails()
        {
            isServiceHostingTestSucceed = false;
            comboBoxServiceDetailsInterface.Items.Clear();
            comboBoxServiceDetailsClass.Items.Clear();
            serviceDLLAssembly = Assembly.LoadFile(textBoxDLLFile.Text);
            foreach (Type type in serviceDLLAssembly.GetTypes())
            {
                if (type.IsInterface) comboBoxServiceDetailsInterface.Items.Add(type.FullName);
                if (type.IsClass) comboBoxServiceDetailsClass.Items.Add(type.FullName);
            }
            buttonTestServiceHosting.Enabled = true;
            buttonLoadService.Enabled = true;
            if (comboBoxServiceDetailsInterface.Items.Count > 0)
            {
                comboBoxServiceDetailsInterface.Enabled = true;
                comboBoxServiceDetailsInterface.SelectedIndex = 0;
            }
            else
            {
                comboBoxServiceDetailsInterface.Enabled = false;
                buttonTestServiceHosting.Enabled = false;
                buttonLoadService.Enabled = false;
                MessageBox.Show("No interfaces found in dll file.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            if (comboBoxServiceDetailsClass.Items.Count > 0)
            {
                comboBoxServiceDetailsClass.Enabled = true;
                comboBoxServiceDetailsClass.SelectedIndex = 0;
            }
            else
            {
                comboBoxServiceDetailsClass.Enabled = false;
                buttonTestServiceHosting.Enabled = false;
                buttonLoadService.Enabled = false;
                MessageBox.Show("No classes found in dll file.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            if (Regex.IsMatch(serviceDLLFileName, ".*Library.dll"))
            {
                string defaultInterfaceName = serviceDLLFileName.Substring(0, serviceDLLFileName.Length - 4) + ".I" + serviceDLLFileName.Substring(0, serviceDLLFileName.Length - 11);
                if (comboBoxServiceDetailsInterface.Items.Contains(defaultInterfaceName))
                    comboBoxServiceDetailsInterface.SelectedIndex = comboBoxServiceDetailsInterface.Items.IndexOf(defaultInterfaceName);
                string defaultClassName = serviceDLLFileName.Substring(0, serviceDLLFileName.Length - 4) + "." + serviceDLLFileName.Substring(0, serviceDLLFileName.Length - 11);
                if (comboBoxServiceDetailsClass.Items.Contains(defaultClassName))
                    comboBoxServiceDetailsClass.SelectedIndex = comboBoxServiceDetailsClass.Items.IndexOf(defaultClassName);
            }
        }
    }
}