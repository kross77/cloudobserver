using CloudObserver.Services.CC;
using CloudObserver.Services.GW;
using CloudObserver.Services.RM;
using CloudObserver.Services.WB;
using System;
using System.Diagnostics;
using System.Threading;
using System.ServiceModel;

namespace CloudObserver.Services
{
    /// <summary>
    /// Contains some static helper methods to work with services.
    /// </summary>
    public static class ServicesHelper
    {
        /// <summary>
        /// A filename of the Cloud Observer Service Host application.
        /// </summary>
        private const string serviceHostProcessFileName = "csvchost.exe";

        /// <summary>
        /// The number of milliseconds for a service to start.
        /// </summary>
        private const int serviceStartTimeout = 2000;

        public static Type GetServiceContract(string serviceType)
        {
            switch (serviceType)
            {
                case "CC":
                    return typeof(ICloudController);
                case "GW":
                    return typeof(IGateway);
                case "RM":
                    return typeof(IResourceManager);
                case "WB":
                    return typeof(IWorkBlock);
                default:
                    throw new ArgumentException("Invalid service type.");
            }
        }

        public static Service CreateServiceInstance(string serviceAddress, string serviceType)
        {
            switch (serviceType)
            {
                case "CC":
                    return new CloudController(serviceAddress, serviceType);
                case "GW":
                    return new Gateway(serviceAddress, serviceType);
                case "RM":
                    return new ResourceManager(serviceAddress, serviceType);
                case "WB":
                    return new WorkBlock(serviceAddress, serviceType);
                default:
                    throw new ArgumentException("Invalid service type.");
            }
        }

        public static bool HostService(string serviceAddress, string serviceType)
        {
            ProcessStartInfo serviceHostProcessStartInfo = new ProcessStartInfo();
            serviceHostProcessStartInfo.FileName = serviceHostProcessFileName;
            serviceHostProcessStartInfo.Arguments = serviceAddress + ' ' + serviceType;
            serviceHostProcessStartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            Process serviceHostProcess = new Process();
            serviceHostProcess.StartInfo = serviceHostProcessStartInfo;
            serviceHostProcess.Start();

            Thread.Sleep(serviceStartTimeout);
            if (serviceHostProcess.HasExited)
                return false;

            return true;
        }

        public static bool ConnectServiceToController(string serviceAddress, string controllerAddress)
        {
            using (ChannelFactory<IService> channelFactory = new ChannelFactory<IService>(new BasicHttpBinding(), serviceAddress))
            {
                IService service = channelFactory.CreateChannel();
                try
                {
                    service.ConnectToController(controllerAddress);
                }
                catch (Exception)
                {
                    return false;
                }
                finally
                {
                    try
                    {
                        ((IClientChannel)service).Close();
                    }
                    catch (Exception)
                    {
                        ((IClientChannel)service).Abort();
                    }
                }
            }

            return true;
        }
    }
}
