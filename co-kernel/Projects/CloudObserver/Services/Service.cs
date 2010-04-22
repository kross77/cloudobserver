//using CloudObserver.Services.CC;
//using System;
//using System.ServiceModel;

//namespace CloudObserver.Services
//{
//    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
//    public abstract class Service : IService
//    {
//        protected string ServiceAddress;
//        protected string ServiceType;

//        protected string ControllerAddress;
//        protected DateTime GlobalTime;

//        public Service(string serviceAddress, string serviceType)
//        {
//            ServiceAddress = serviceAddress;
//            ServiceType = serviceType;
//        }

//        public bool ConnectToController(string controllerAddress)
//        {
//            ControllerAddress = controllerAddress;

//            using (ChannelFactory<ICloudController> channelFactory = new ChannelFactory<ICloudController>(new BasicHttpBinding(), ControllerAddress))
//            {
//                ICloudController cloudController = channelFactory.CreateChannel();
//                try
//                {
//                    cloudController.ConnectService(ServiceAddress, ServiceType, out GlobalTime);
//                }
//                catch (Exception)
//                {
//                    return false;
//                }
//                finally
//                {
//                    try
//                    {
//                        ((IClientChannel)cloudController).Close();
//                    }
//                    catch (Exception)
//                    {
//                        ((IClientChannel)cloudController).Abort();
//                    }
//                }
//            }

//            return true;
//        }
//    }
//}
