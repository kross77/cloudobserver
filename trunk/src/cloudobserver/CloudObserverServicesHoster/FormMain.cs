using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

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
    }
}