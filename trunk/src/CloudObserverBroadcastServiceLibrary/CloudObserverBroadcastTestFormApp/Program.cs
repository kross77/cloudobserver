using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using CloudObserverBroadcastTestFormApp.CloudObserverBroadcastService;

namespace CloudObserverBroadcastTestFormApp
{
    static class Program
    {
        [STAThread]
        static public void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            FormMain TestForm = new FormMain();
            Application.Run(TestForm);
        }
    }
}
