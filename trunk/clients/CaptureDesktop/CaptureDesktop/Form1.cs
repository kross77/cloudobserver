using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CaptureDesktop
{
    public partial class MainForm : Form
    {
        
        public MainForm()
        {
            InitializeComponent();
        }

        private void btnCapture_Click(object sender, EventArgs e)
        {
            if (1 == CaptureDesktop.Instance.State)
            {
                CaptureDesktop.Instance.Stop();
                btnCapture.Text = "Start capture";
            }
            else
            {
                CaptureDesktop.Instance.Start(100);
                btnCapture.Text = "Stop capture";
            }
        }

        private void btnCaptureSettings_Click(object sender, EventArgs e)
        {
            FormCaptureSettings formSettings = new FormCaptureSettings();
            formSettings.ShowDialog();
        }
    }
}
