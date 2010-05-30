using CloudObserver.Kernel.Policies;
using System;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.ServiceModel;
using System.ServiceModel.Description;
using System.Threading;

namespace CloudObserver.Kernel.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class ResourcesManager : IResourcesManager
    {
        private const string serviceHostProcessFileName = "cosvchst.exe";
        private const int serviceStartTimeout = 2000;

        private int workBlocksCounter = 0;

        private string ipAddress;
        private string deviceAddress;

        private int port = 4773;

        public ResourcesManager(string ipAddress)
        {
            this.ipAddress = ipAddress;
            deviceAddress = "http://" + ipAddress + ":4773/";

            ServiceHost policyRetriever = new ServiceHost(typeof(PolicyRetriever), new Uri("http://" + ipAddress + ":843/"));
            policyRetriever.AddServiceEndpoint(typeof(IPolicyRetriever), new WebHttpBinding(), "").Behaviors.Add(new WebHttpBehavior());
            try
            {
                policyRetriever.Open();
            }
            catch
            {
            }
        }

        public bool StartCloudObserver()
        {
            if (!HostService(deviceAddress, "CC"))
                return false;

            if (!ConnectDeviceToController(deviceAddress, deviceAddress))
                return false;
            
            return true;
        }

        public bool SupportCloudObserver(string controllerAddress)
        {
            if (!ConnectDeviceToController(deviceAddress, controllerAddress))
                return false;

            return true;
        }

        public string HostWorkBlock()
        {
            string workBlockAddress = deviceAddress + "wb-" + workBlocksCounter++;
            if (!HostService(workBlockAddress, "WB"))
                return string.Empty;

            return workBlockAddress;
        }

        private bool HostService(string serviceAddress, string serviceType)
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

        private bool ConnectDeviceToController(string deviceAddress, string controllerAddress)
        {
            using (ChannelFactory<ICloudController> channelFactory = new ChannelFactory<ICloudController>(new BasicHttpBinding(), controllerAddress))
            {
                ICloudController controller = channelFactory.CreateChannel();
                try
                {
                    controller.ConnectDevice(deviceAddress);
                }
                catch (Exception)
                {
                    return false;
                }
                finally
                {
                    try
                    {
                        ((IClientChannel)controller).Close();
                    }
                    catch (Exception)
                    {
                        ((IClientChannel)controller).Abort();
                    }
                }
            }

            return true;
        }

        public int GetFreePort()
        {
            port++;
            while (!IsPortFree(port))
                port++;

            return port;
        }

        private bool IsPortFree(int port)
        {
            try
            {
                Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                socket.Bind(new IPEndPoint(IPAddress.Loopback, port));
                socket.Close();

                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }
    }
}
