using CloudObserver.Services.RM;
using System;
using System.Collections.Generic;
using System.ServiceModel;

namespace CloudObserver.Services.CC
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class CloudController : Service, ICloudController
    {
        private List<string> cc;
        private List<string> gw;
        private List<string> rm;
        private List<string> wb;

        public CloudController(string serviceAddress, string serviceType)
            : base(serviceAddress, serviceType)
        {
            cc = new List<string>();
            gw = new List<string>();
            rm = new List<string>();
            wb = new List<string>();
        }

        public void ConnectService(string serviceAddress, string serviceType, out DateTime globalTime)
        {
            switch (serviceType)
            {
                case "CC":
                    cc.Add(serviceAddress);
                    break;
                case "GW":
                    gw.Add(serviceAddress);
                    break;
                case "RM":
                    rm.Add(serviceAddress);
                    break;
                case "WB":
                    wb.Add(serviceAddress);
                    break;
                default:
                    throw new ArgumentException("Invalid service type.");
            }
            globalTime = DateTime.UtcNow;
        }

        public string GetWorkBlock()
        {
            if (rm.Count == 0)
                return string.Empty;
            Random random = new Random();
            string resourceManagerAddress = rm[random.Next(rm.Count)];

            string workBlockAddress;
            using (ChannelFactory<IResourceManager> channelFactory = new ChannelFactory<IResourceManager>(new BasicHttpBinding(), resourceManagerAddress))
            {
                IResourceManager resourceManager = channelFactory.CreateChannel();
                try
                {
                    workBlockAddress = resourceManager.CreateWorkBlock();
                }
                catch (Exception)
                {
                    workBlockAddress = string.Empty;
                }
                finally
                {
                    try
                    {
                        ((IClientChannel)resourceManager).Close();
                    }
                    catch (Exception)
                    {
                        ((IClientChannel)resourceManager).Abort();
                    }
                }
            }

            return workBlockAddress;
        }
    }
}
