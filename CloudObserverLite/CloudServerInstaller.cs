using System;
using System.Collections;
using System.ComponentModel;
using System.Configuration.Install;
using System.ServiceProcess;

namespace CloudObserverLite
{
    [RunInstaller(true)]
    public class CloudServerInstaller : Installer
    {
        private ServiceProcessInstaller serviceProcessInstaller;
        private ServiceInstaller serviceInstaller;

        public CloudServerInstaller()
        {
            serviceProcessInstaller = new ServiceProcessInstaller();
            serviceProcessInstaller.Account = ServiceAccount.NetworkService;
            this.Installers.Add(serviceProcessInstaller);

            serviceInstaller = new ServiceInstaller();
            serviceInstaller.ServiceName = CloudServer.SERVICE_NAME;
            serviceInstaller.StartType = ServiceStartMode.Automatic;
            this.Installers.Add(serviceInstaller);
        }

        protected override void OnAfterInstall(IDictionary savedState)
        {
            base.OnAfterInstall(savedState);

            using (ServiceController serviceController = new ServiceController(this.serviceInstaller.ServiceName, Environment.MachineName))
                serviceController.Start();
        }
    }
}
