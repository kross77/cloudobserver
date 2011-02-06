using CloudObserver.Kernel.Contents;
using System;
using System.ServiceModel;
using System.Text;

namespace CloudObserver.Kernel.Services
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class WorkBlock : IWorkBlock
    {
        private Content content;
        private string ip;
        private string deviceAddress;
        private string controllerAddress;

        public WorkBlock(string ipAddress)
        {
            ip = ipAddress;
            deviceAddress = "http://" + ip + ":4773/";
        }

        public string IWannaRead(int[] ids)
        {
            StringBuilder stringBuilder = new StringBuilder();
            StringBuilder contentTypesBuilder = new StringBuilder();
            for (int i = 0; i < ids.Length; i++)
            {
                string address;
                string contentType;
                GetStreamInformation(ids[i], out address, out contentType);
                stringBuilder.Append(address);
                contentTypesBuilder.Append(contentType);
                if (i < ids.Length - 1)
                {
                    stringBuilder.Append(',');
                    contentTypesBuilder.Append(',');
                }
            }
            return stringBuilder.ToString() + "," + contentTypesBuilder.ToString();
        }

        public string IWannaWrite(int id, string contentType)
        {
            if (content != null)
                content.Close();

            switch (contentType)
            {
                case "video/x-flv":
                    content = new FLVContent(id, contentType, ip, GetFreePort(), GetFreePort());
                    break;
                default:
                    content = new UnknownContent(id, contentType, ip, GetFreePort(), GetFreePort());
                    break;
            }

            content.Open();
            RegisterStream(id, content.SenderAddress, contentType);

            return content.ReceiverAddress;
        }

        private int GetFreePort()
        {
            using (ChannelFactory<IResourcesManager> channelFactory = new ChannelFactory<IResourcesManager>(new BasicHttpBinding(), deviceAddress + "rm"))
            {
                IResourcesManager resourcesManager = channelFactory.CreateChannel();
                try
                {
                    return resourcesManager.GetFreePort();
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
        }

        private void RegisterStream(int id, string address, string contentType)
        {
            using (ChannelFactory<ICloudController> channelFactory = new ChannelFactory<ICloudController>(new BasicHttpBinding(), controllerAddress))
            {
                ICloudController cloudController = channelFactory.CreateChannel();
                try
                {
                    cloudController.RegisterStream(id, address, contentType);
                }
                finally
                {
                    try
                    {
                        ((IClientChannel)cloudController).Close();
                    }
                    catch (Exception)
                    {
                        ((IClientChannel)cloudController).Abort();
                    }
                }
            }
        }

        private void GetStreamInformation(int id, out string address, out string contentType)
        {
            using (ChannelFactory<ICloudController> channelFactory = new ChannelFactory<ICloudController>(new BasicHttpBinding(), controllerAddress))
            {
                ICloudController cloudController = channelFactory.CreateChannel();
                try
                {
                    cloudController.GetStreamInformation(id, out address, out contentType);
                }
                finally
                {
                    try
                    {
                        ((IClientChannel)cloudController).Close();
                    }
                    catch (Exception)
                    {
                        ((IClientChannel)cloudController).Abort();
                    }
                }
            }
        }

        public void ConnectToController(string controllerAddress)
        {
            this.controllerAddress = controllerAddress;
        }
    }
}
