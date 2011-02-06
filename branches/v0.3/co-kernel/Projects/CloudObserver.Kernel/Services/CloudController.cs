using System;
using System.Collections.Generic;
using System.ServiceModel;

namespace CloudObserver.Kernel.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class CloudController : ICloudController
    {
        private List<string> devices;

        private Dictionary<int, StreamInformation> streams;

        private string ipAddress;

        public CloudController(string ipAddress)
        {
            this.ipAddress = ipAddress;

            devices = new List<string>();

            streams = new Dictionary<int, StreamInformation>();
        }

        public void ConnectDevice(string ipAddress)
        {
            devices.Add(ipAddress);
        }

        public string GetWorkBlock()
        {
            if (devices.Count == 0)
                return string.Empty;

            Random random = new Random();
            string deviceAddress = devices[random.Next(devices.Count)];

            string workBlockAddress;
            using (ChannelFactory<IResourcesManager> channelFactory = new ChannelFactory<IResourcesManager>(new BasicHttpBinding(), deviceAddress + "rm"))
            {
                IResourcesManager resourcesManager = channelFactory.CreateChannel();
                try
                {
                    workBlockAddress = resourcesManager.HostWorkBlock();
                }
                catch (Exception)
                {
                    workBlockAddress = string.Empty;
                }
                finally
                {
                    try
                    {
                        ((IClientChannel)resourcesManager).Close();
                    }
                    catch (Exception)
                    {
                        ((IClientChannel)resourcesManager).Abort();
                    }
                }
            }

            using (ChannelFactory<IWorkBlock> channelFactory = new ChannelFactory<IWorkBlock>(new BasicHttpBinding(), workBlockAddress))
            {
                IWorkBlock workBlock = channelFactory.CreateChannel();
                try
                {
                    workBlock.ConnectToController("http://" + ipAddress + ":4773/");
                }
                catch (Exception)
                {
                }
                finally
                {
                    try
                    {
                        ((IClientChannel)workBlock).Close();
                    }
                    catch (Exception)
                    {
                        ((IClientChannel)workBlock).Abort();
                    }
                }
            }

            return workBlockAddress;
        }

        public void RegisterStream(int id, string address, string contentType)
        {
            streams[id] = new StreamInformation(address, contentType);
        }

        public void GetStreamInformation(int id, out string address, out string contentType)
        {
            if (streams.ContainsKey(id))
            {
                StreamInformation streamInformation = streams[id];
                address = streamInformation.Address;
                contentType = streamInformation.ContentType;
            }
            else
            {
                address = "none";
                contentType = "none";
            }
        }
    }
}
