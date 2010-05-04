using System;
using System.Collections.Generic;
using System.ServiceModel;
using System.Text;

namespace CloudObserver.Services.GW
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class Gateway : IGateway
    {
        private Dictionary<int, Content> contents;

        private string ip;
        private int port;

        public Gateway(string ipAddress)
        {
            contents = new Dictionary<int, Content>();

            ip = ipAddress;
            port = 4774;
        }

        public string IWannaRead(int[] ids, out string contentTypes)
        {
            StringBuilder stringBuilder = new StringBuilder();
            StringBuilder contentTypesBuilder = new StringBuilder();
            for (int i = 0; i < ids.Length; i++)
                if (contents.ContainsKey(ids[i]))
                {
                    stringBuilder.Append(contents[ids[i]].SenderAddress);
                    contentTypesBuilder.Append(contents[ids[i]].ContentType);
                    if (i < ids.Length - 1)
                    {
                        stringBuilder.Append(',');
                        contentTypesBuilder.Append(',');
                    }
                }
            contentTypes = contentTypesBuilder.ToString();
            return stringBuilder.ToString();
        }

        public string IWannaWrite(int id)
        {
            return IWannaWriteCustom(id, "audio/mpeg");
        }

        public string IWannaWriteCustom(int id, string contentType)
        {
            if (contents.ContainsKey(id))
                contents[id].Close();

            Content content = new Content(id, ip, ref port);
            content.Open();
            content.ContentType = contentType;
            contents[id] = content;
            return content.ReceiverAddress;
        }

        //public Gateway(string serviceAddress, string serviceType) : base(serviceAddress, serviceType) { }

        //public string GetWorkBlock()
        //{
        //    string workBlockAddress;

        //    using (ChannelFactory<ICloudController> channelFactory = new ChannelFactory<ICloudController>(new BasicHttpBinding(), ControllerAddress))
        //    {
        //        ICloudController cloudController = channelFactory.CreateChannel();
        //        try
        //        {
        //            workBlockAddress = cloudController.GetWorkBlock();
        //        }
        //        catch (Exception)
        //        {
        //            return string.Empty;
        //        }
        //        finally
        //        {
        //            try
        //            {
        //                ((IClientChannel)cloudController).Close();
        //            }
        //            catch (Exception)
        //            {
        //                ((IClientChannel)cloudController).Abort();
        //            }
        //        }
        //    }

        //    return workBlockAddress;
        //}
    }
}
