using System;
using System.ComponentModel;
using System.Configuration.Install;
using System.ServiceProcess;

namespace CloudObserverLite
{
    [RunInstaller(true)]
    public class CloudServerInstaller : Installer
    {
        public CloudServerInstaller()
        {
            ServiceProcessInstaller serviceProcessInstaller = new ServiceProcessInstaller();
            serviceProcessInstaller.Account = ServiceAccount.NetworkService;
            this.Installers.Add(serviceProcessInstaller);

            ServiceInstaller serviceInstaller = new ServiceInstaller();
            serviceInstaller.ServiceName = CloudServer.SERVICE_NAME;
            serviceInstaller.StartType = ServiceStartMode.Automatic;
            this.Installers.Add(serviceInstaller);
        }
    }
}
