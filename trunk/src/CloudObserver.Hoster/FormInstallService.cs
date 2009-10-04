using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.Reflection;
using System.ServiceModel;
using System.ServiceModel.Description;

namespace CloudObserver.Hoster
{
    public partial class FormInstallService : Form
    {
        private Assembly serviceDLLAssembly;
        private string serviceDLLFileName;
        private bool isServiceHostingTestSucceed;

        public FormInstallService()
        {
            InitializeComponent();

            Icon = Properties.Resources.HosterIcon;

            isServiceHostingTestSucceed = false;
        }

        private void buttonSelectDLLFile_Click(object sender, EventArgs e)
        {
            if (openFileDialogSelectDLLFile.ShowDialog() == DialogResult.OK)
            {
                serviceDLLFileName = openFileDialogSelectDLLFile.SafeFileName;
                textBoxDLLFile.Text = openFileDialogSelectDLLFile.FileName;
                LoadServiceDetails();
            }
        }

        private void comboBoxService_SelectedIndexChanged(object sender, EventArgs e)
        {
            isServiceHostingTestSucceed = false;
        }

        private void comboBoxContract_SelectedIndexChanged(object sender, EventArgs e)
        {
            isServiceHostingTestSucceed = false;
        }

        private void buttonTestServiceHosting_Click(object sender, EventArgs e)
        {
            isServiceHostingTestSucceed = TestServiceHosting(true);
        }

        private void buttonInstallService_Click(object sender, EventArgs e)
        {
            if (!isServiceHostingTestSucceed) isServiceHostingTestSucceed = TestServiceHosting(false);
            if (isServiceHostingTestSucceed)
            {
                ((FormAddRemoveServices)Owner).loadServiceDLL(comboBoxService.Text, comboBoxContract.Text, textBoxDLLFile.Text);
                Close();
            }
        }

        private bool TestServiceHosting(bool showMessageOnSucceed)
        {
            try
            {
                serviceDLLAssembly = Assembly.LoadFile(textBoxDLLFile.Text);
                Type serviceType = serviceDLLAssembly.GetType(comboBoxService.Text);
                Type serviceContractType = serviceDLLAssembly.GetType(comboBoxContract.Text);
                string servicePath = "http://localhost:" + new Random().Next(1024, 65535) + "/" + serviceDLLAssembly.GetType(comboBoxService.Text).Name;
                ServiceHost serviceHost = new ServiceHost(serviceType, new Uri(servicePath));
                ServiceMetadataBehavior mexBehavior = new ServiceMetadataBehavior();
                mexBehavior.HttpGetEnabled = true;
                serviceHost.Description.Behaviors.Add(mexBehavior);
                serviceHost.AddServiceEndpoint(serviceContractType, new BasicHttpBinding(), "");
                serviceHost.Open();
                serviceHost.Close();
                if (showMessageOnSucceed) MessageBox.Show("Service hosting test succeed.", "Test Service Hosting", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return true;
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Testing Failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
        }

        private void LoadServiceDetails()
        {
            isServiceHostingTestSucceed = false;
            comboBoxService.Items.Clear();
            comboBoxContract.Items.Clear();
            serviceDLLAssembly = Assembly.LoadFile(textBoxDLLFile.Text);
            foreach (Type type in serviceDLLAssembly.GetTypes())
            {
                if (type.IsClass) comboBoxService.Items.Add(type.FullName);
                if (type.IsInterface) comboBoxContract.Items.Add(type.FullName);
            }
            buttonTestServiceHosting.Enabled = true;
            buttonInstallService.Enabled = true;
            if (comboBoxContract.Items.Count > 0)
            {
                comboBoxContract.Enabled = true;
                comboBoxContract.SelectedIndex = 0;
            }
            else
            {
                comboBoxContract.Enabled = false;
                buttonTestServiceHosting.Enabled = false;
                buttonInstallService.Enabled = false;
                MessageBox.Show("No interfaces found in dll file.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            if (comboBoxService.Items.Count > 0)
            {
                comboBoxService.Enabled = true;
                comboBoxService.SelectedIndex = 0;
            }
            else
            {
                comboBoxService.Enabled = false;
                buttonTestServiceHosting.Enabled = false;
                buttonInstallService.Enabled = false;
                MessageBox.Show("No classes found in dll file.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            if (Regex.IsMatch(serviceDLLFileName, "CloudObserver.Services.*Service.dll"))
            {
                string defaultClassName = serviceDLLFileName.Substring(0, serviceDLLFileName.Length - 4);
                if (comboBoxService.Items.Contains(defaultClassName))
                    comboBoxService.SelectedIndex = comboBoxService.Items.IndexOf(defaultClassName);
                string defaultInterfaceName = serviceDLLFileName.Substring(0, serviceDLLFileName.Length - 4) + "Contract";
                if (comboBoxContract.Items.Contains(defaultInterfaceName))
                    comboBoxContract.SelectedIndex = comboBoxContract.Items.IndexOf(defaultInterfaceName);
            }
        }
    }
}