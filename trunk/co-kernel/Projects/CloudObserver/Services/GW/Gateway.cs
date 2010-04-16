using CloudObserver.Services.CC;
using System;
using System.ServiceModel;

namespace CloudObserver.Services.GW
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class Gateway : Service, IGateway
    {
        public Gateway(string serviceAddress, string serviceType) : base(serviceAddress, serviceType) { }

        public string GetWorkBlock()
        {
            string workBlockAddress;

            using (ChannelFactory<ICloudController> channelFactory = new ChannelFactory<ICloudController>(new BasicHttpBinding(), ControllerAddress))
            {
                ICloudController cloudController = channelFactory.CreateChannel();
                try
                {
                    workBlockAddress = cloudController.GetWorkBlock();
                }
                catch (Exception)
                {
                    return string.Empty;
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

            return workBlockAddress;
        }
    }
}
